#include "base.h"

void clearJob(JobPtr job, int delete) {
    updateJobName(job, "");
    strcpy(job->jobId, "");

    if (delete == DELETE_JOB && job->jobArgs != NULL) {
        for (int i = 0; i < job->nArgs; i++) {
            free(job->jobArgs[i]);  // Free each string
        }
        free(job->jobArgs);         // Free the array itself
    }

    job->jobArgs = NULL;
    job->nArgs = 0;

    job->priority = DEFAULT_PRIORITY;
    job->arrivalTime = 0;
    memset(&job->arrivalTimeStamp, 0, sizeof(struct tm));
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

void updateJobStatus(JobPtr job, char* value) {
    strncpy(job->status, value, sizeof(job->status) - 1);
    job->status[sizeof(job->status) - 1] = '\0';
}

void updateJobName(JobPtr job, char* value) {
    strncpy(job->name, value, sizeof(job->name) - 1);
    job->name[sizeof(job->name) - 1] = '\0';
}

void sortQueue(u_int* currRQHead, char* policyName) {
    int j;
    JobPtr tempJob;
    tempJob = (JobPtr)malloc(sizeof(struct Job));

    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        j = i;
        while (j > 0 && getJobAttribute(&testReadyQueue[j], policyName) < getJobAttribute(&testReadyQueue[j - 1], policyName)) {
            *tempJob = testReadyQueue[j];
            testReadyQueue[j] = testReadyQueue[j - 1];
            testReadyQueue[j - 1] = *tempJob;
            j--;
        }
    }

    j = 0;
    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        if (testReadyQueue[i].queueNumber != DEFAULT_QUEUE_NUMBER) j++;
    }

    *currRQHead = (u_int) j;

    free(tempJob);
}

// Test for sorting queue based on the "fcfs" policy
void test_sortQueue_fcfs() {
    u_int currRQHead;
    
    // Call the sortQueue function with "fcfs" policy
    sortQueue(&currRQHead, "fcfs");

    // Assert the queue is sorted in ascending order by queueNumber
    for (int i = 0; i < MAX_TEST_JOB_NUMBER; i++) {
        CU_ASSERT_TRUE(testReadyQueue[i].queueNumber <= testReadyQueue[i + 1].queueNumber);
    }

    // Assert that currRQHead was correctly updated
    CU_ASSERT_EQUAL(currRQHead, totalCount); // Because all jobs have non-default queue numbers
}

// Test for sorting queue based on the "fcfs" policy
void test_sortQueue_sjf() {
    u_int currRQHead;
    
    // Call the sortQueue function with "fcfs" policy
    sortQueue(&currRQHead, "sjf");

    // Assert the queue is sorted in ascending order by queueNumber
    for (int i = 0; i < MAX_TEST_JOB_NUMBER; i++) {
        CU_ASSERT_TRUE(testReadyQueue[i].CPUBurstTime <= testReadyQueue[i + 1].CPUBurstTime);
    }

    // Assert that currRQHead was correctly updated
    CU_ASSERT_EQUAL(currRQHead, totalCount); // Because all jobs have non-default queue numbers
}

// Test for sorting queue based on the "fcfs" policy
void test_sortQueue_pri() {
    u_int currRQHead;
    
    // Call the sortQueue function with "fcfs" policy
    sortQueue(&currRQHead, "pri");

    // Assert the queue is sorted in ascending order by queueNumber
    for (int i = 0; i < MAX_TEST_JOB_NUMBER; i++) {
        CU_ASSERT_TRUE(testReadyQueue[i].priority <= testReadyQueue[i + 1].priority);
    }

    // Assert that currRQHead was correctly updated
    CU_ASSERT_EQUAL(currRQHead, totalCount); // Because all jobs have non-default queue numbers
}
