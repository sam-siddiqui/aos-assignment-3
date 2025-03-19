#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../modules/utility.h"

#ifndef JC_BASE_H
#define JC_BASE_H

extern char* validPolicies[3];

#define isValidPolicy(policyStr) (in(validPolicies, sizeof(validPolicies), policyStr))

extern FILE* testFp;
extern benchMarkPtr testBenchmark;
extern char* testCmdV[CMDV_NUM_ARGS];

void test_openBenchmarkFile();
void test_createBenchmark();

#endif // JC_BASE_H 