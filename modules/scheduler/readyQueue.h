#include "../../headers/job.h"
#include "./../../init.h"
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

void sortJobsBasedOnPolicy(u_int oldRQHead, u_int oldRQTail, enum Scheduling_Policy currSchedulePolicy);

void addJobToRQHead(JobPtr job);

void clearJob(JobPtr job, int delete);

void clearReadyQueue(int delete);

#endif // READY_QUEUE_H