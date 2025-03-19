#include "base.h"

int getJobAttribute(JobPtr job, char* policyName) {
    
    if (strcmp(policyName, "fcfs") == 0) return job->queueNumber;
    if (strcmp(policyName, "sjf") == 0) return job->CPUBurstTime;
    if (strcmp(policyName, "pri") == 0) return job->priority;

    // default
    return job->queueNumber;
}

// Test for "fcfs" policy
void test_getJobAttribute_fcfs() {
    JobPtr job = &testReadyQueue[0];

    // Get the queue number based on "fcfs" policy
    int result = getJobAttribute(job, "fcfs");

    // Assert that the correct attribute (queueNumber) is returned
    CU_ASSERT_EQUAL(result, job->queueNumber);
}

// Test for "sjf" policy
void test_getJobAttribute_sjf() {
    JobPtr job = &testReadyQueue[0];

    // Get the CPUBurstTime based on "sjf" policy
    int result = getJobAttribute(job, "sjf");

    // Assert that the correct attribute (CPUBurstTime) is returned
    CU_ASSERT_EQUAL(result, job->CPUBurstTime);
}

// Test for "pri" policy
void test_getJobAttribute_pri() {
    JobPtr job = &testReadyQueue[0];

    int result = getJobAttribute(job, "pri");

    CU_ASSERT_EQUAL(result, job->priority);
}
