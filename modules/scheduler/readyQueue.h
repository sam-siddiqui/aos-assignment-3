#include "../../headers/job.h"
#include "./../../shared.h"
#include "../utility.h"
#include "schedulePolicy.h"

#ifndef READY_QUEUE_H
#define READY_QUEUE_H

int getRQCount();
void decreaseRQCount(int val);
void increaseRQCount(int val);
int getExpectedWaitingTime();
void decExpectedWaitingTime(int val);
void incExpectedWaitingTime(int val);
// Sort the jobs and set the oldRQTail
void sortJobsBasedOnPolicy(u_int oldRQHead, u_int oldRQTail, enum Scheduling_Policy currSchedulePolicy);
// Actually adds the job to the queue
void addJobToRQHead(JobPtr job);
// Resets a job space for reuse
void clearJob(JobPtr job, int delete);
// Clears the readyQueue
void clearReadyQueue(int delete);

#endif // READY_QUEUE_H