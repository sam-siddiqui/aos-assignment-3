#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/job.h"

#ifndef QUEUE_DISPLAY_H_
#define QUEUE_DISPLAY_H_

char* getCurrPolicy();

void printJobRow(char* idxString, JobPtr job);

void printRunningJob();

int isReadyJob(JobPtr job);

void printReadyQueue();

void printCompleteQueue();

void printList();

#endif