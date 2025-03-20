#include "jobCreationUtility.h"
#include "scheduler.h"

void extractArgs(JobPtr job, char* cmdV[]) {
    int i = RUN_JOBNAME_INDEX;
    int countArgs = 0;
    
    while (cmdV[i] != NULL) {                   // While there's a value in inputBufferArr
        countArgs++;                            // After the job_name index
        i++;                                    // Count the number of args
    }

    job->jobArgs = (char**)malloc(sizeof(char*) * (countArgs + 1));
    if (job->jobArgs == NULL) return;           // Check for error

    i = RUN_JOBNAME_INDEX;
    for (int j = 0; j < countArgs; j++) {       // Loop through and 
        job->jobArgs[j] = strdup(cmdV[i]);      // create a copy of cmdV's char* string
        i++;                                    // Also move through the cmdV itself
    }
    job->jobArgs[countArgs] = NULL;             // Don't forget the null terminator at the end of any array
    
    job->nArgs = countArgs + 1;
    
}

void populateJobFromBuffer(JobPtr job, char* cmdV[]) {
    snprintf(job->jobId, JOB_ID_SIZE, "%s", gen_uuid(JOB_ID_SIZE));     // Copy the job ID
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
    job->arrivalTime = time(NULL);                              // Current Time in UNIX
    job->arrivalTimeStamp = *localtime(&job->arrivalTime);      // Full time struct
}