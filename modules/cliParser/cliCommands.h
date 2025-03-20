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

void listQueue(char* cmdV[], int cmdC);

void changeSchedulerPolicy(char* cmdV[], int cmdC);

void scheduleRun(char* cmdV[], int cmdC);

void initBenchmarkTest(char* cmdV[], int cmdC);

void showHelp(char* cmdV, int cmdCount);

#endif