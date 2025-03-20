#ifndef CLI_COMMANDS_H
#define CLI_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../shared.h"
#include "../../headers/text.h"
#include "cliUtility.h"
#include "../queueDisplayer.h"
#include "../errorHandlers.h"
#include "../utility.h"
#include "../perfMeasure/benchmarker.h"
#include "../scheduler/scheduler.h"
#include "../scheduler/readyQueue.h"
#include "../scheduler/schedulePolicy.h"
// Lists out all the jobs: running, readyQueue, CompletedQueue
void listQueue(char* cmdV[], int cmdC);
// Validates the input and changes the current policy
void changeSchedulerPolicy(char* cmdV[], int cmdC);
// Validates input and sends it to Scheduler
void scheduleRun(char* cmdV[], int cmdC);
// Validates input and sends it to Scheduler
void initBenchmarkTest(char* cmdV[], int cmdC);
// Shows the help menu full or option wise
void showHelp(char* cmdV, int cmdCount);

#endif