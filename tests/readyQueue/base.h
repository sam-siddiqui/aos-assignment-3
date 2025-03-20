#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include "../../shared.h"
#include "../../modules/utility.h"

#ifndef RQ_BASE_H
#define RQ_BASE_H

#define safeIncRQHead() rqHead = (rqHead + 1) % MAX_JOB_NUMBER;

#define MAX_TEST_JOB_NUMBER 5
extern struct Job testReadyQueue[MAX_JOB_NUMBER]; // Global queue to be tested
extern u_int rqHead;
extern u_int rqTail;
extern atomic_uint currCount;

extern int getJobAttribute(JobPtr job, char* policyName);
extern void test_addJobToRQHead();
extern void test_clearJobSimple();
extern void test_clearJob();

extern JobPtr testJob;

#endif // RQ_BASE_H