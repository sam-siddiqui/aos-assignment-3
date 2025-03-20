#include "job.h"

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_JOB_NUMBER 200                          // Max len of the queue
#define LOOP_I_STRING_LEN 3                         // Length of string to store queueNum, max 200

// A struct ptr array based readyQueue being used in the program
extern struct Job readyQueue[MAX_JOB_NUMBER];

typedef struct completedQueue* CQNodePtr;
// A linked-list based completedQueue
struct completedQueue {
    struct Job job;                                 // The current job
    CQNodePtr nextJob;                              // The next Queue node, which holds the next job
};
extern CQNodePtr cqHead;                            // Pointer to hold the first job in the CQ 

extern JobPtr RunningJob;                           // Pointer to the currently RunningJob, if any

// Clears or frees the readyQueue, depending on the flag delete passed
extern void clearReadyQueue(int delete);
// Clears or frees the completedQueue, depending on the flag delete passed
extern void clearCompletedQueue(int delete);
// Clears for reuse or frees a job struct, depending on the flag delete passed
extern void clearJob(JobPtr job, int delete);
// Creates a job from the given char* array and enqueues it to readyQueue. 
// Uses enqueueJob and createJob internally
extern void enqueueJobFromBuffer(char* cmdV[]);
// Enqueues a job to the readyQueue
extern void enqueueJob(JobPtr job);
// Creates a job based on the given char* array, 
// returns a pointer to the newly created job
extern JobPtr createJob(char* cmdV[]);
// Inserts a job to the completedQueue linked list
extern void insertToCompletedQueue(JobPtr job);

#endif