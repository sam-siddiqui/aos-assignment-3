#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../shared.h"

#ifndef SP_BASE_H
#define SP_BASE_H

#define MAX_TEST_JOB_NUMBER 5
extern struct Job testReadyQueue[MAX_JOB_NUMBER]; // Global queue to be tested
extern int totalCount;

extern void clearJob(JobPtr job, int delete);
extern void sortQueue(u_int* currRQHead, char* policyName);
extern int getJobAttribute(JobPtr job, char* policyName);
extern void test_sortQueue_fcfs();
extern void test_getJobAttribute_fcfs();
extern void test_sortQueue_sjf();
extern void test_getJobAttribute_sjf();
extern void test_sortQueue_pri();
extern void test_getJobAttribute_pri();

#endif // SP_BASE_H