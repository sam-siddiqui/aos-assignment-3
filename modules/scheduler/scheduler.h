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

void scheduleJob(JobPtr job);

void enqueueJobFromBuffer(char* cmdV[]);
void enqueueJob(JobPtr job);

void scheduleTest();

void* scheduler(void* message);

#endif // SCHEDULER_H_