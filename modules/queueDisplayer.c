#include "queueDisplayer.h"
#include "./../shared.h"
#include "./utility.h"
#include "./scheduler/readyQueue.h"

char* getCurrPolicy() {
    switch (currSchedulePolicy) {
        // X Macro to link policy enum to their string version
        #define X(name, _, __) \
        case name: \
            return TO_STRING(name);
        SCH_POLICY(X)
        #undef X

        default:
            return "UNKNOWN";
    }
}


void printJobRow(char* idxString, JobPtr job) {
    printf(
        READY_QUEUE_TABLEROW_FORMAT,
        idxString, job->name, job->CPUBurstTime, job->queueNumber,
        job->priority, job->arrivalTimeStamp.tm_hour,
        job->arrivalTimeStamp.tm_min,
        job->arrivalTimeStamp.tm_sec, job->status
    );
}

void printRunningJob() {
    if (isAJobRunning() && !match(RunningJob->status, TO_STRING(complete))) {
        printJobRow(RUNNING_JOB_CURSOR_STRING, RunningJob);
    }
}

int isReadyJob(JobPtr job) {
    return match(job->status, "") || match(job->status, TO_STRING(complete)) ||
           match(job->status, TO_STRING(create));
}

void printReadyQueue() {
    char* currPolicy;
    currPolicy = getCurrPolicy();
    
    printf(READY_QUEUE_TITLE_FORMAT, totalSubmittedJobs, getRQCount());
    if (isRQEmpty() && !isAJobRunning()) return;    // If RQ is empty or there's no job running, return
        
    printf(READY_QUEUE_HEADER_FORMAT, currPolicy);
    
    printf(READY_QUEUE_TABLEHEADER_FORMAT);
    printRunningJob();                              // First print the running Job

    char iString[LOOP_I_STRING_LEN];                // Then others
    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        if (isReadyJob(&readyQueue[i])) continue;
        
        snprintf(iString, LOOP_I_STRING_LEN, "%d", i + 1);
        printJobRow(iString, &readyQueue[i]);
    }

}

void printCompleteQueue() {
    CQNodePtr currCompleteJob = cqHead;
    if (currCompleteJob == NULL) return;                        // If no completed jobs
    
    printf(COMPLETED_QUEUE_TITLE_FORMAT, totalCompletedJobs);   // If no completed jobs
    if (totalCompletedJobs == 0) return;
    
    printf(COMPLETED_QUEUE_TABLEHEADER_FORMAT);
    int i = 0;
    while (currCompleteJob != NULL) {
        printf(COMPLETED_QUEUE_TABLEROW_FORMAT, 
               i + 1,
               currCompleteJob->job.name, 
               currCompleteJob->job.CPUBurstTime,
               currCompleteJob->job.executionTime,
               currCompleteJob->job.priority,
               currCompleteJob->job.arrivalTimeStamp.tm_hour,
               currCompleteJob->job.arrivalTimeStamp.tm_min,
               currCompleteJob->job.arrivalTimeStamp.tm_sec,
               currCompleteJob->job.status
            );
        currCompleteJob = currCompleteJob->nextJob;
        i++;
    }
}

void printList() {
    printReadyQueue();
    printf("\n");
    printCompleteQueue();
}