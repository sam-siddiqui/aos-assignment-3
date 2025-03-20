#include <stdlib.h>
#include <string.h>
#include "../../headers/job.h"
#include "./../../shared.h"
#include "../utility.h"

#ifndef SCH_POLICY_H_
#define SCH_POLICY_H_

// Gets the policy related attribute as defined by SCH_POLICY
int getJobAttribute(JobPtr job, char* policyName);
// Sorts the RQ and sets the queues head and tail to last and first
void sortQueue(u_int* currRQHead, char* policyName);
// Uses isValidPolicy internally
// Changes if success, returns failure if invalid policy
int changePolicy(char* givenPolicy);

#endif // SCH_POLICY_H_