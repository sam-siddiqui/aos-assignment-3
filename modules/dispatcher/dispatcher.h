#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../../headers/job.h"
#include "./../../init.h"
#include "./../utility.h"
#include "../perfMeasure/metricsMeasure.h"
#include "../perfMeasure/benchmarker.h"
#include "../scheduler/readyQueue.h"
#include "externalExecutor.h"

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

void getNextScheduledJob(JobPtr currentJobPtr, JobPtr jobPtr);

void runJob(JobPtr currentJobPtr, JobPtr completedJobPtr);

void cycleNextJobInRQ(JobPtr jobPtr, JobPtr currentJobPtr, JobPtr completedJobPtr);

void* dispatcher(void* message);

#endif