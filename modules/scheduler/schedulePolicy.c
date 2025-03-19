#include "schedulePolicy.h"

int getJobAttribute(JobPtr job, char* policyName) {
    if (!isValidPolicy(policyName)) return job->queueNumber;
    
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
    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        if (readyQueue[i].queueNumber != DEFAULT_QUEUE_NUMBER) j++;
    }

    *currRQHead = (u_int) j;

    free(tempJob);
}

int changePolicy(char* givenPolicy) {
    if (!isValidPolicy(givenPolicy)) return INVALID_POLICY;

    #define X(name, strrep, _) if(match(givenPolicy, strrep)) currSchedulePolicy = name;
    SCH_POLICY(X)
    #undef X

    return SUCCESS;
}