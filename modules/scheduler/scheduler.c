#include "scheduler.h"


int isSchedulerBusy() { return atomic_load(&schedulerBusy); }
void setSchedulerNotReady() { atomic_store(&schedulerBusy, 1); }
void setSchedulerReady() { atomic_store(&schedulerBusy, 0); }

void scheduleJob(JobPtr job) {
    
    if (isRQFull()) pthread_cond_wait(&rqNotFull, &rqLock);

    addJobToRQHead(job);
    sortJobsBasedOnPolicy(rqHead, rqTail, currSchedulePolicy);
    
    pthread_mutex_unlock(&rqLock);
    signalDispatcher();
}

void enqueueJobFromBuffer(char* cmdV[]) {
    JobPtr job = createJob(cmdV);
    enqueueJob(job);
}

void enqueueJob(JobPtr job) {
    updateJobStatus(job, TO_STRING(waiting));
    timeStampNewJob(job);
    scheduleJob(job);
    incExpectedWaitingTime(job->CPUBurstTime);
}

void scheduleTest() {
    int testStatus = 0;
    
    pthread_mutex_unlock(&rqLock);

    clearCompletedQueue(CLEAR_JOB);
    clearReadyQueue(CLEAR_JOB);
    clearStats();

    testStatus = createTest(inputBufferArr, &fp);
    
    if(testStatus == SUCCESS) setTestRunning();
    else checkTestStatus(testStatus);
}

void* scheduler(void* message) {
    clearReadyQueue(CLEAR_JOB);

    setConsoleColor(RED);
    printf("%s", (char*) message);

    pthread_cond_signal(&threadReady);
    setSchedulerReady();

    pthread_mutex_lock(&rqLock);
    pthread_mutex_lock(&inpBufLock);

    while (1) {
        if (isInputBufferEmpty()) pthread_cond_wait(&inpBufUpdate, &inpBufLock);
        if (cmd == quit) {
            pthread_mutex_unlock(&inpBufLock);
            
            pthread_mutex_unlock(&rqLock); 
            
            break;
        }

        if (cmd == set_policy && didSchedulePolicyChange()) {
            setSchedulerNotReady();

            sortJobsBasedOnPolicy(rqHead, rqTail, currSchedulePolicy);
            prevSchedulePolicy = currSchedulePolicy;
            
            setSchedulerReady();
            continue;
        }

        if (cmd == test) {
            setSchedulerNotReady();

            scheduleTest();

            clearInputBuffer();

            setSchedulerReady();

            continue;
        }

        // We reached here meaning, there was a new job passed onto inputBufferArr
        setSchedulerNotReady();

        enqueueJobFromBuffer(inputBufferArr);
        clearInputBuffer();
        
        setSchedulerReady();
    }

    setConsoleColor(RED);
    printf(QUIT_SCHEDULER_TEXT);
    
    if(!isRQEmpty()) {
        printf(REMAINING_JOBS_SCHEDULER_TEXT);
        printf(REMAINING_JOBS_FORMAT, 
            getRQCount(), getExpectedWaitingTime()
        ); 
    }

    // Signal the dispatcher to wake up and update itself
    signalDispatcher();

    clearInputBuffer();
    pthread_exit(NULL);
}

