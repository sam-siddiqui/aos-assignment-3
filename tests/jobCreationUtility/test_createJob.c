#include "base.h"

char* gen_uuid(int length) {
    char v[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // 3fb17ebc-bc38-4939-bc8b-74f2443281d4
    // 8 dash 4 dash 4 dash 4 dash 12

    char* buf;
    buf = (char*)malloc(length * sizeof(char));
    buf[0] = 0;

    // gen random for all spaces because lazy
    for (int i = 0; i < length; ++i) {
        buf[i] = v[rand() % 16];
    }

    // put dashes in place
    for (int dashCount = 0; dashCount < (int)(length / 4); dashCount++) {
        buf[rand() % length] = '-';
    }

    // needs end byte
    buf[length - 1] = '\0';

    return buf;
}

void updateJobStatus(JobPtr job, char* value) {
    strncpy(job->status, value, sizeof(job->status) - 1);
    job->status[sizeof(job->status) - 1] = '\0';
}

void updateJobName(JobPtr job, char* value) {
    strncpy(job->name, value, sizeof(job->name) - 1);
    job->name[sizeof(job->name) - 1] = '\0';
}

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

JobPtr createJob(char* cmdV[]) {
    JobPtr newJob = (JobPtr)malloc(sizeof(struct Job));
    snprintf(newJob->jobId, JOB_ID_SIZE, "%s", gen_uuid(JOB_ID_SIZE));
    updateJobName(newJob, cmdV[RUN_JOBNAME_INDEX]);
    updateJobStatus(newJob, TO_STRING(create));
    extractArgs(newJob, cmdV);

    newJob->CPUBurstTime = atoi(cmdV[RUN_BURSTTIME_INDEX]);
    newJob->priority = atoi(cmdV[RUN_PRI_INDEX]);
    newJob->executionTime = 0;
    newJob->queueNumber = incAndGetQueueNumber();

    return newJob;
}

void test_createJob() {
    JobPtr job = createJob(testCmdV);
    
    CU_ASSERT_EQUAL(5, job->CPUBurstTime);
    CU_ASSERT_EQUAL(2, job->priority);
    CU_ASSERT_STRING_EQUAL(job->name, "TestJob"); 
}