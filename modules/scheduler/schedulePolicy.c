#include "schedulePolicy.h"

int getJobAttribute(JobPtr job, char* policyName) {
    if (!isValidPolicy(policyName)) return job->queueNumber;
    
    // X Macro to repeat the if statement for every policy in SCH_POLICY
    #define X(name, strrep, attribute) if (match(policyName, strrep)) return job->attribute;
    SCH_POLICY(X)
    #undef X

    // default
    return job->queueNumber;
}

void sortQueue(u_int* currRQHead, char* policyName) {
    int j;
    JobPtr tempJob;
    tempJob = (JobPtr)malloc(sizeof(struct Job));

    // Insertion Sort of the Queue
    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        j = i;
        while (j > 0 && getJobAttribute(&readyQueue[j], policyName) < getJobAttribute(&readyQueue[j - 1], policyName)) {
            *tempJob = readyQueue[j];
            readyQueue[j] = readyQueue[j - 1];
            readyQueue[j - 1] = *tempJob;
            j--;
        }
    }

    j = 0;

    // Move head till the last job in the queue
    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        if (readyQueue[i].queueNumber != DEFAULT_QUEUE_NUMBER) j++;
    }

    *currRQHead = (u_int) j;

    free(tempJob);
}

int changePolicy(char* givenPolicy) {
    if (!isValidPolicy(givenPolicy)) return INVALID_POLICY;

    // X Macro to repeat the if line, as many policies there are
    #define X(name, strrep, _) if(match(givenPolicy, strrep)) currSchedulePolicy = name;
    SCH_POLICY(X)
    #undef X

    return SUCCESS;
}