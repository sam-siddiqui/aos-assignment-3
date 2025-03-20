#include "metricsMeasure.h"

void calculateCompleteJobMetrics(JobPtr completedJobPtr) {
    if (completedJobPtr == NULL) return;

    int actualCPUTime = MAX(0, completedJobPtr->endTime - completedJobPtr->startTime);
    completedJobPtr->executionTime = actualCPUTime;
    completedJobPtr->turnaroundTime = MAX(0, completedJobPtr->endTime - completedJobPtr->arrivalTime);
    completedJobPtr->waitTime = MAX(0, completedJobPtr->turnaroundTime - actualCPUTime);
    completedJobPtr->responseTime = MAX(0, completedJobPtr->startTime - completedJobPtr->arrivalTime);
}

void calculateCompletedJobStats() {
    if (totalSubmittedJobs == 0) return;
    if (totalCompletedJobs == 0) return;

    if (cqHead == NULL) return;
    
    CQNodePtr tempCQHead = cqHead;
    int turnaroundTotal = 0;
    int waitingTotal = 0;
    int actualCPUTotal = 0;
    int responseTotal = 0;

    minResponseTime = __INT_MAX__;
    maxResponseTime = -__INT_MAX__;

    while (tempCQHead != NULL) {
        turnaroundTotal += tempCQHead->job.turnaroundTime;
        waitingTotal += tempCQHead->job.waitTime;
        actualCPUTotal += tempCQHead->job.executionTime;

        responseTotal += tempCQHead->job.responseTime;
        if (tempCQHead->job.responseTime < minResponseTime) minResponseTime = tempCQHead->job.responseTime;
        if (tempCQHead->job.responseTime > maxResponseTime) maxResponseTime = tempCQHead->job.responseTime;

        tempCQHead = tempCQHead->nextJob;
    }
    
    avgResponseTime = responseTotal / totalCompletedJobs;
    avgCPUTime = actualCPUTotal / totalCompletedJobs;
    avgTurnaroundTime = turnaroundTotal / totalCompletedJobs;
    avgWaitTime = waitingTotal / totalCompletedJobs;
    avgThroughput = turnaroundTotal == 0? 0 : (float) 1 / turnaroundTotal;
}

void clearStats() {
    avgCPUTime = 0;
    avgResponseTime = 0;
    minResponseTime = 0;
    maxResponseTime = 0;
    avgThroughput = 0;
    avgTurnaroundTime = 0;
    avgWaitTime = 0;
    totalCompletedJobs = 0;
    totalSubmittedJobs = 0;
}

void storeStatsToFile(FILE* fp) {
    fprintf(fp, STATS_LIST_FORMAT, 
        totalSubmittedJobs, 
        avgTurnaroundTime, 
        avgCPUTime, 
        avgWaitTime, 
        minResponseTime, 
        avgResponseTime, 
        maxResponseTime, 
        avgThroughput
    );
}

void printStats() {
    storeStatsToFile(stdout);
}

