#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/job.h"

#ifndef QUEUE_DISPLAY_H_
#define QUEUE_DISPLAY_H_

// Gets the currSchedulePolicy, in char* form
char* getCurrPolicy();
// Print a job entry, takes in idx as string, and the job struct itself
void printJobRow(char* idxString, JobPtr job);

void printRunningJob();
// Check if a job is ready and *waiting*
int isReadyJob(JobPtr job);

void printReadyQueue();

void printCompleteQueue();
// Wrapper around printReadyQueue and printCompleteQueue
void printList();

#endif