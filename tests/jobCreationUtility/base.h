#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../shared.h"
#include "../../modules/utility.h"

#ifndef JC_BASE_H
#define JC_BASE_H

#define incAndGetQueueNumber() ++totalSubmittedJobs;

extern char* testCmdV[CMDV_NUM_ARGS];
extern JobPtr testJob; 

void test_extractArgs();
void test_createJob();

void clearJob(JobPtr job, int delete); 
void extractArgs(JobPtr job, char* cmdV[]);

#endif // JC_BASE_H 