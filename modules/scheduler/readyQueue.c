#include "readyQueue.h"

int getRQCount() {return atomic_load(&currCount); }
void decreaseRQCount(int val) { atomic_fetch_sub(&currCount, val);}
void increaseRQCount(int val) { atomic_fetch_add(&currCount, val); }
int _getExpectedWaitingTime() {return atomic_load(&totalExpectedTime); }
void decExpectedWaitingTime(int val) { atomic_fetch_sub(&totalExpectedTime, val); }
void incExpectedWaitingTime(int val) { atomic_fetch_add(&totalExpectedTime, val); }

int getExpectedWaitingTime() { 
    // Based on the formula in the requirements.pdf
    if (isAJobRunning())
        return atomic_load(&totalExpectedTime) - (time(NULL) - RunningJob->startTime); 
    // Else get the actual value
    return _getExpectedWaitingTime();
}

void sortJobsBasedOnPolicy(u_int oldRQHead, u_int oldRQTail, enum Scheduling_Policy currSchedulePolicy) {
    u_int newRQHead = -1;

    // X Macro to populate the switch statement using preprocessor and SCH_POLICY
    switch (currSchedulePolicy) {
        #define X(name, strrep, _) \
        case name: \
             sortQueue(&newRQHead, strrep); \
             break;
        SCH_POLICY(X)
        #undef X
        default:
            break;
    }
    rqTail = 0;                             // Reset the tail and head
    rqHead = newRQHead;
}

void addJobToRQHead(JobPtr job) {
    increaseRQCount(1);
    readyQueue[rqHead] = *job;              // Add job's pointer to the queue
    safeIncRQHead();
}

void clearJob(JobPtr job, int delete) {
    updateJobName(job, "");
    strcpy(job->jobId, "");

    if (delete == DELETE_JOB && job->jobArgs != NULL) {         // If we're deleting
        for (int i = 0; i < job->nArgs; i++) {
            free(job->jobArgs[i]);  // Free each string
        }
        free(job->jobArgs);         // Free the array itself
    }

    job->jobArgs = NULL;
    job->nArgs = 0;

    job->priority = DEFAULT_PRIORITY;
    job->arrivalTime = 0;
    memset(&job->arrivalTimeStamp, 0, sizeof(struct tm));       // Zero out the struct
    job->executionTime = -1;
    job->CPUBurstTime = DEFAULT_BURST_TIME;
    job->startTime = 0;
    job->endTime = 0;
    job->queueNumber = DEFAULT_QUEUE_NUMBER;
    job->responseTime = -1;
    job->turnaroundTime = -1;
    job->waitTime = -1;
    updateJobStatus(job, TO_STRING(create));
}

void clearReadyQueue(int delete) {
     pthread_mutex_lock(&rqLock);

    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        clearJob(&readyQueue[i], delete);
    }
    
     pthread_mutex_unlock(&rqLock);
}