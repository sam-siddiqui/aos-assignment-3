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

void test_clearJobSimple() {
    JobPtr newJob = (JobPtr)malloc(sizeof(struct Job));

    strcpy(newJob->name, "TestJob");
    strcpy(newJob->status, "waiting");
    newJob->CPUBurstTime = 5;
    newJob->priority = 2;

    clearJob(newJob, CLEAR_JOB);

    CU_ASSERT_STRING_EQUAL(newJob->name, "");
    CU_ASSERT_STRING_EQUAL(newJob->status, "create");
    CU_ASSERT_EQUAL(newJob->priority, DEFAULT_PRIORITY);
    CU_ASSERT_EQUAL(newJob->CPUBurstTime, DEFAULT_BURST_TIME);
    CU_ASSERT_EQUAL(newJob->startTime, 0);

}

void test_clearJob() {

    clearJob(testJob, CLEAR_JOB);

    CU_ASSERT_STRING_EQUAL(testJob->name, "");
    CU_ASSERT_STRING_EQUAL(testJob->status, "create");
    CU_ASSERT_EQUAL(testJob->priority, DEFAULT_PRIORITY);
    CU_ASSERT_EQUAL(testJob->CPUBurstTime, DEFAULT_BURST_TIME);
    CU_ASSERT_EQUAL(testJob->startTime, 0);
    CU_ASSERT_TRUE(testJob->jobArgs == NULL);
}