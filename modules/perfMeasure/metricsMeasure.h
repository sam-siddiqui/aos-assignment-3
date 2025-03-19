#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../headers/job.h"
#include "./../../init.h"
#include "../utility.h"

#ifndef METRICS_MEASURE_H
#define METRICS_MEASURE_H

void calculateCompleteJobMetrics(JobPtr completedJobPtr);

void calculateCompletedJobStats();

void clearStats();

void printStats();

void storeStatsToFile(FILE* fp);

#endif