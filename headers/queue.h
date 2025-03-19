#include "job.h"

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_JOB_NUMBER 200
#define LOOP_I_STRING_LEN 3

extern struct Job readyQueue[MAX_JOB_NUMBER];

typedef struct completedQueue* CQNodePtr;
struct completedQueue {
    struct Job job;
    CQNodePtr nextJob; 
};
extern CQNodePtr cqHead;

extern JobPtr RunningJob;

extern void clearReadyQueue(int delete);
extern void clearCompletedQueue(int delete);
extern void clearJob(JobPtr job, int delete);
extern void enqueueJobFromBuffer(char* cmdV[]);
extern void enqueueJob(JobPtr job);
extern JobPtr createJob(char* cmdV[]);
extern void insertToCompletedQueue(JobPtr job);

#endif