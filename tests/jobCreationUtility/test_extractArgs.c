#include "base.h"

void extractArgs(JobPtr job, char* cmdV[]) {
    int i = RUN_JOBNAME_INDEX;
    int countArgs = 0;
    
    while (cmdV[i] != NULL) {
        countArgs++;
        i++;
    }

    job->jobArgs = (char**)malloc(sizeof(char*) * (countArgs + 1));
    if (job->jobArgs == NULL) return;

    i = RUN_JOBNAME_INDEX;
    for (int j = 0; j < countArgs; j++) {
        job->jobArgs[j] = strdup(cmdV[i]);
        i++;
    }
    job->jobArgs[countArgs] = NULL;
    
    job->nArgs = countArgs + 1;
    
}

void test_extractArgs() {
    testJob = (JobPtr)malloc(sizeof(struct Job));
    strcpy(testJob->name, testCmdV[3]);
    strcpy(testJob->name, "waiting");
    testJob->CPUBurstTime = atoi(testCmdV[1]);
    testJob->priority = atoi(testCmdV[2]);

    extractArgs(testJob, testCmdV);

    CU_ASSERT_STRING_EQUAL(testJob->jobArgs[0], testCmdV[3]);
    CU_ASSERT_STRING_EQUAL(testJob->jobArgs[1], testCmdV[4]);

}