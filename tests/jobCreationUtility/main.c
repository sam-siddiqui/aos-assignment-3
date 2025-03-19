#include "base.h"

char* testCmdV[CMDV_NUM_ARGS];
JobPtr testJob; 
u_int totalSubmittedJobs;

// Setup function
int setup_suite() {
    testCmdV[0] = "run";
    testCmdV[1] = "5";
    testCmdV[2] = "2";
    testCmdV[3] = "TestJob";
    testCmdV[4] = "5";
    totalSubmittedJobs  = 0;
    
    return 0; // Return 0 for success
}

// Teardown function - This is run after each test
int cleanup_suite() {
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
    fcfsSuite = CU_add_suite("jobCreationUtility Suite", setup_suite, cleanup_suite);
    if (NULL == fcfsSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(fcfsSuite, "test of extractArgs()", test_extractArgs)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(fcfsSuite, "test of createJob()", test_createJob)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_run_tests();

    // Clean up the CUnit registry
    CU_cleanup_registry();
    return 0;
}
