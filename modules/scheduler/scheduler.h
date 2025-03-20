#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../../shared.h"
#include "../errorHandlers.h"
#include "../utility.h"
#include "../../headers/job.h"
#include "readyQueue.h"
#include "schedulePolicy.h"
#include "jobCreationUtility.h"
#include "../cliParser/cliUtility.h"
#include "../perfMeasure/benchmarker.h" 

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

int isSchedulerBusy();
void setSchedulerNotReady();
void setSchedulerReady();

// Schedules a job into the ReadyQueue
void scheduleJob(JobPtr job);
// Creates a job from a char* buffer, uses enqueueJob and createJob internally
void enqueueJobFromBuffer(char* cmdV[]);
// Enqueues a job into the readyQueue
void enqueueJob(JobPtr job);
// Creates a test from the given inputBufferArr or copy of cmdV
void scheduleTest();
// The driver program of the second thread
void* scheduler(void* message);

#endif // SCHEDULER_H_