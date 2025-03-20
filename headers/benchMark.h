#include <stdio.h>

#ifndef BENCHMARK_H
#define BENCHMARK_H

#define TEST_DONE_STATE 1
#define TEST_RUNNING_STATE 0
#define TEST_NOT_CREATED_STATE -1

#define BENCHMARK_SAVE_FILENAME_SIZE 25

#define BENCHMARK_TEST_FILE_PATH "sleep"

// TODO is it better to have all text in one file or context-wise separated?
#define BENCHMARK_TEST_PARAMS_COUNT 8 
#define BENCHMARK_JOBNAME_INDEX 1
#define BENCHMARK_POLICY_INDEX 2
#define BENCHMARK_NUMJOBS_INDEX 3
#define BENCHMARK_PRILEVEL_INDEX 4
#define BENCHMARK_MINCPU_INDEX 5
#define BENCHMARK_MAXCPU_INDEX 6
#define BENCHMARK_ARRIVALRATE_INDEX 7
#define BENCHMARK_JOBARGS_COUNT 5

struct benchMark {
    char name[BENCHMARK_SAVE_FILENAME_SIZE];
    char sType[5];
    int numJobs;
    int priorityLevel;
    int minCPUTime;
    int maxCPUTime;
    int arrivalRate;
    FILE* saveFileFP;
};

typedef struct benchMark* benchMarkPtr;

extern float avgTurnaroundTime;                         // Changed by scheduler thread only (perf_measure)
extern float avgWaitTime;                               // Changed by scheduler thread only (perf_measure)
extern float avgCPUTime;                                // Changed by scheduler thread only (perf_measure)
extern float avgResponseTime;                           // Changed by scheduler thread only (perf_measure)
extern float avgThroughput;                             // Changed by scheduler thread only (perf_measure)
extern double responseTimeStd;                           // Changed by scheduler thread only (perf_measure)
extern int maxResponseTime;                           // Changed by scheduler thread only (perf_measure)
extern int minResponseTime;                           // Changed by scheduler thread only (perf_measure)
extern FILE* fp;                                        // Changed by scheduler thread only (perf_measure)

extern void clearStats();
extern void printStats();
extern void storeStatsToFile(FILE* fp);

#endif