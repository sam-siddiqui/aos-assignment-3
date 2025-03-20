#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../headers/job.h"
#include "./../../shared.h"
#include "../utility.h"
#include "schedulePolicy.h"

#ifndef JOB_INIT_UTILITY_H_
#define JOB_INIT_UTILITY_H_

void extractArgs(JobPtr job, char* cmdV[]);

JobPtr createJob(char* cmdV[]);

void populateJobFromBuffer(JobPtr job, char* cmdV[]);

void timeStampNewJob(JobPtr job);

#endif // JOB_INIT_UTILITY_H_