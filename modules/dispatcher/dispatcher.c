#include "dispatcher.h"

void getNextScheduledJob(JobPtr currentJobPtr, JobPtr jobPtr) {
    // Update job's state in readyQueue to be running
    updateJobStatus(&readyQueue[rqTail], TO_STRING(running));

    // Update storage pointer of currently running job
    *jobPtr = readyQueue[rqTail];
    memcpy(currentJobPtr, jobPtr, sizeof(struct Job));
    
    RunningJob = currentJobPtr;                     // Set RunningJob towards this job

    // Reset it as if it were removed
    clearJob(jobPtr, CLEAR_JOB);
    readyQueue[rqTail] = *jobPtr;
    decreaseRQCount(1);
}

void runJob(JobPtr currentJobPtr, JobPtr completedJobPtr) {
    int processStatus = 0;
    // Track the time and run the job
    time_t start = time(NULL);
    currentJobPtr->startTime = start;
    
    execute(currentJobPtr, &processStatus);
    
    time_t end = time(NULL);
    currentJobPtr->endTime = end;

    // switch (processStatus) {
    // case -1:
    //     updateJobStatus(currentJobPtr, "failed");
    //     break;
    // case 0:
    //     updateJobStatus(currentJobPtr, TO_STRING(waiting));
    //     break;
    // case 1:
    //     updateJobStatus(currentJobPtr, TO_STRING(complete));
    //     break;
    // default:
    //     break;
    // }
    updateJobStatus(currentJobPtr, TO_STRING(complete));

    // Store currently completed job to a new pointer
    memcpy(completedJobPtr, currentJobPtr, sizeof(struct Job));
}

void cycleNextJobInRQ(JobPtr jobPtr, JobPtr currentJobPtr, JobPtr completedJobPtr) {
    if (isNextJobInRQWaiting()) {
        appendToOutputBuffer("Executor: Running %d\n", rqTail);

        getNextScheduledJob(currentJobPtr, jobPtr);
        pthread_cond_signal(&rqNotFull);                                // Signal from dispatcher to scheduler

        runJob(currentJobPtr, completedJobPtr);
        calculateCompleteJobMetrics(completedJobPtr);

        appendToOutputBuffer("Executor: Completed %d\n", rqTail);

        decExpectedWaitingTime(completedJobPtr->CPUBurstTime);
        
        insertToCompletedQueue(completedJobPtr);
        incTotalCompletedJobs();
    } else
        safeIncRQTail();
}

void* dispatcher(void* message) {
    // One pointer for removing from RQ, one for during execution, one for adding to CQ
    JobPtr jobPtr = (JobPtr)malloc(sizeof(struct Job));
    JobPtr currentJobPtr = (JobPtr)malloc(sizeof(struct Job));
    JobPtr completedJobPtr = (JobPtr)malloc(sizeof(struct Job));

    setConsoleColor(YELLOW);

    printf("%s", (char*)message);

    pthread_cond_signal(&threadReady);

    pthread_mutex_lock(&rqLock);
    while (cmd != quit || !isRQEmpty()) {
        if (isRQEmpty()) pthread_cond_wait(&rqNotEmpty, &rqLock);

        cycleNextJobInRQ(jobPtr, currentJobPtr, completedJobPtr);

        pthread_mutex_unlock(&rqLock);
        
        if (isTestRunning() && isRQEmpty()) {
            setTestDone();

            appendToOutputBuffer( TEST_DONE_TEXT );

            calculateCompletedJobStats();
            storeStatsToFile(fp);
            if (fp) fclose(fp);
        }
        
        if(cmd == quit && (!isRQEmpty() || isAJobRunning())) {
            // Self-signal, when scheduler has exited
            signalDispatcher();
            appendToOutputBuffer(REMAINING_JOBS_FORMAT, 
                getRQCount(), getExpectedWaitingTime()
            ); 
            flushOutputBuffer();
        }       
    }

    
    if (totalSubmittedJobs > 0) {
        setConsoleColor(YELLOW);
        calculateCompletedJobStats();
        printStats();
    }

    clearStats();
    clearCompletedQueue(DELETE_JOB);
    clearReadyQueue(DELETE_JOB);

    setConsoleColor(YELLOW);
    printf(QUIT_DISPATCHER_TEXT);

    free(currentJobPtr);
    free(completedJobPtr);
    free(jobPtr);
    
    pthread_exit(NULL);
}