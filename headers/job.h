#include <time.h>

#ifndef JOB_H
#define JOB_H

#define JOB_ID_SIZE 10
#define JOB_PATH_NAME_SIZE 50
#define JOB_STATUS_SIZE 10

struct Job {
    char jobId[JOB_ID_SIZE];
    char name[JOB_PATH_NAME_SIZE];
    char** jobArgs;
    int nArgs;
    
    struct tm arrivalTimeStamp;
    time_t arrivalTime;
    time_t startTime;
    time_t endTime;
    int priority;
    int CPUBurstTime;
    
    int executionTime;
    int turnaroundTime;
    int waitTime;
    int responseTime;

    int queueNumber;
    char status[JOB_STATUS_SIZE];
};

#define DEFAULT_BURST_TIME 999999999
#define DEFAULT_PRIORITY 999999999
#define DEFAULT_QUEUE_NUMBER 999999999

typedef struct Job* JobPtr;

extern void updateJobStatus(JobPtr job, char* value);
extern void updateJobName(JobPtr job, char* value);

#endif  // JOB_H_