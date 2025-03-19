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

    while (tempCQHead != NULL) {
        turnaroundTotal += tempCQHead->job.turnaroundTime;
        waitingTotal += tempCQHead->job.waitTime;
        responseTotal += tempCQHead->job.responseTime;
        actualCPUTotal += tempCQHead->job.executionTime;
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
    avgResponseTime = 0;
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
        avgThroughput
    );
}

void printStats() {
    // printf("Total number of job submitted: %d \n", totalSubmittedJobs);
    // printf( "Average turnaround time: %2f seconds \n", avgTurnaroundTime);
    // printf("Average CPU time: %2f seconds \n", avgCPUTime);
    // printf("Average waiting time: %2f seconds \n", avgWaitTime);
    // printf("Throughput: %2f No./second \n", avgThroughput);
    storeStatsToFile(stdout);
}

