#include <stdlib.h>
#include <string.h>
#include "../../headers/job.h"
#include "./../../init.h"
#include "../utility.h"

#ifndef SCH_POLICY_H_
#define SCH_POLICY_H_

int getJobAttribute(JobPtr job, char* policyName);

void sortQueue(u_int* currRQHead, char* policyName);

int changePolicy(char* givenPolicy);

#endif // SCH_POLICY_H_