#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../../headers/job.h"
#include "./../../shared.h"
#include "./../utility.h"
#include "../perfMeasure/metricsMeasure.h"
#include "../perfMeasure/benchmarker.h"
#include "../scheduler/readyQueue.h"
#include "externalExecutor.h"

#ifndef DISPATCHER_H_
#define DISPATCHER_H_
// Extract the next scheduled job from the readyQueue
void getNextScheduledJob(JobPtr currentJobPtr, JobPtr jobPtr);
// Time and execute the job
void runJob(JobPtr currentJobPtr, JobPtr completedJobPtr);
// Cycle to the next job in Queue and see if it needs executing
void cycleNextJobInRQ(JobPtr jobPtr, JobPtr currentJobPtr, JobPtr completedJobPtr);
// The main driver function of the second thread
void* dispatcher(void* message);

#endif