#include <stdio.h>

#ifndef BENCHMARK_H
#define BENCHMARK_H

// Various flags for the test state
#define TEST_DONE_STATE 1
#define TEST_RUNNING_STATE 0
#define TEST_NOT_CREATED_STATE -1

// Max char len of the save filename
#define BENCHMARK_SAVE_FILENAME_SIZE 30

#define BENCHMARK_TEST_FILE_PATH "batch_job"

// These are position indexes and member count of the benchmark struct
#define BENCHMARK_TEST_PARAMS_COUNT 8 
#define BENCHMARK_JOBNAME_INDEX 1
#define BENCHMARK_POLICY_INDEX 2
#define BENCHMARK_NUMJOBS_INDEX 3
#define BENCHMARK_PRILEVEL_INDEX 4
#define BENCHMARK_MINCPU_INDEX 5
#define BENCHMARK_MAXCPU_INDEX 6
#define BENCHMARK_ARRIVALRATE_INDEX 7
// This is the length of the jobArgs array a test job uses
#define BENCHMARK_JOBARGS_COUNT 5

struct benchMark {
    char name[BENCHMARK_SAVE_FILENAME_SIZE];            // Benchmark Name and saveFileName
    char sType[5];                                      // The scheduling policy used
    int numJobs;                                        
    int priorityLevel;
    int minCPUTime;
    int maxCPUTime;
    int arrivalDelay;
    FILE* saveFileFP;                                   // Pointer to the saveFile
};

typedef struct benchMark* benchMarkPtr;

// Various metrics being recorded
extern float avgTurnaroundTime;
extern float avgWaitTime;
extern float avgCPUTime;
extern float avgResponseTime;
extern float avgThroughput;
extern double responseTimeStd;
extern int maxResponseTime;
extern int minResponseTime;    
extern FILE* fp;                                        // The file pointer globally used by benchmarker and dispatcher

// Clears the stats recorded so far, for new tests
extern void clearStats();

// Prints the stats onto stdout. Uses storeStatsToFile internally
extern void printStats();

// Prints the stats to a file pointer
extern void storeStatsToFile(FILE* fp);

#endif