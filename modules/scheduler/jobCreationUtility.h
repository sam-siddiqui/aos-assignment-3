#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../headers/job.h"
#include "./../../shared.h"
#include "../utility.h"
#include "schedulePolicy.h"

#ifndef JOB_INIT_UTILITY_H_
#define JOB_INIT_UTILITY_H_

// Extracts args and copy thems into the jobArgs array of a Job
void extractArgs(JobPtr job, char* cmdV[]);
// Creates a job from given char* array, and returns a pointer
JobPtr createJob(char* cmdV[]);
// Updates the job's members based on given char*[]
void populateJobFromBuffer(JobPtr job, char* cmdV[]);
// Timestamp the current time, and added it to Job's startTime
void timeStampNewJob(JobPtr job);

#endif // JOB_INIT_UTILITY_H_