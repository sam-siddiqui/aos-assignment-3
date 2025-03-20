#include <time.h>

#ifndef JOB_H
#define JOB_H

#define JOB_ID_SIZE 10
#define JOB_PATH_NAME_SIZE 50
#define JOB_STATUS_SIZE 10

struct Job {
    char jobId[JOB_ID_SIZE];                    // UID Job ID
    char name[JOB_PATH_NAME_SIZE];              // Path of the file being executed
    char** jobArgs;                             // Array of char* to be sent to the file
    int nArgs;                                  // Num of Args
    
    struct tm arrivalTimeStamp;                 // The exact timestamp it came into the system
    time_t arrivalTime;                         // Same as above but in UNIX time
    time_t startTime;                           // Time when it was picked up by the Dispatcher
    time_t endTime;                             // Time when execution was finished and process ended
    int priority;                               // Priority Level of the Job
    int CPUBurstTime;                           // Expected Execution Time
    
    int executionTime;                          // Actual Exection Time
    int turnaroundTime;                     
    int waitTime;
    int responseTime;

    int queueNumber;
    char status[JOB_STATUS_SIZE];
};

// Absurd and default values of the three metrics being compared
#define DEFAULT_BURST_TIME 999999999
#define DEFAULT_PRIORITY 999999999
#define DEFAULT_QUEUE_NUMBER 999999999

typedef struct Job* JobPtr;

extern void updateJobStatus(JobPtr job, char* value);
extern void updateJobName(JobPtr job, char* value);
// Updates the name and status of a job
// Uses copyStr and strcmp internally

#endif  // JOB_H_