#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "../../headers/job.h"
#include "./../../shared.h" 
#include "../utility.h"

#ifndef METRICS_MEASURE_H
#define METRICS_MEASURE_H
// Calculate and store the job metrics of the job
void calculateCompleteJobMetrics(JobPtr completedJobPtr);
// Calculate the total Statistics
void calculateCompletedJobStats();

void clearStats();

void printStats();

void storeStatsToFile(FILE* fp);

#endif