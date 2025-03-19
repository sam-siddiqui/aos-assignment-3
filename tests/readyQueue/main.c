#include "base.h"

struct Job testReadyQueue[MAX_JOB_NUMBER];
u_int rqHead;
u_int rqTail;
atomic_uint currCount;
JobPtr testJob;

// Setup function
int setup_suite() {
    rqHead = 0;
    rqTail = 0;
    atomic_store(&currCount, 0);
    testJob = (JobPtr)malloc(sizeof(struct Job));

    strcpy(testJob->name, "TestJob");
    strcpy(testJob->status, "waiting");
    testJob->queueNumber = 1;
    testJob->CPUBurstTime = 5;
    testJob->jobArgs = malloc(sizeof(char*) * 3);
    testJob->priority = 2;


    return 0; // Return 0 for success
}

// Teardown function - This is run after each test
int cleanup_suite() {
    free(testJob->jobArgs);
    clearJob(testJob, DELETE_JOB);
    free(testJob);
    
    return 0; // Return 0 for success
}

// Example of setting up the test suite
CU_pSuite fcfsSuite;

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) 
        return CU_get_error();

    // Add suite to the registry with setup and teardown functions
    fcfsSuite = CU_add_suite("readyQueue Suite", setup_suite, cleanup_suite);
    if (NULL == fcfsSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(fcfsSuite, "test of addJobToRQHead()", test_addJobToRQHead)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(fcfsSuite, "test of clearJob()", test_clearJobSimple)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(fcfsSuite, "test of clearJob() with args", test_clearJob)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_run_tests();

    // Clean up the CUnit registry
    CU_cleanup_registry();
    return 0;
}
