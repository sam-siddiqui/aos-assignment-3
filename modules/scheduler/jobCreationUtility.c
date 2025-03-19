#include "jobCreationUtility.h"
#include "scheduler.h"

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

void populateJobFromBuffer(JobPtr job, char* cmdV[]) {
    snprintf(job->jobId, JOB_ID_SIZE, "%s", gen_uuid(JOB_ID_SIZE));
    updateJobName(job, cmdV[RUN_JOBNAME_INDEX]);
    updateJobStatus(job, TO_STRING(create));
    extractArgs(job, cmdV);

    job->CPUBurstTime = atoi(cmdV[RUN_BURSTTIME_INDEX]);
    job->priority = atoi(cmdV[RUN_PRI_INDEX]);
    job->executionTime = 0;
    job->queueNumber = incAndGetQueueNumber();
}

JobPtr createJob(char* cmdV[]) {
    JobPtr newJob = (JobPtr)malloc(sizeof(struct Job));
    populateJobFromBuffer(newJob, cmdV);

    return newJob;
}

void timeStampNewJob(JobPtr job) {
    job->arrivalTime = time(NULL);
    job->arrivalTimeStamp = *localtime(&job->arrivalTime);
}