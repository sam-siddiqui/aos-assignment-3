#include "base.h"

FILE* testFp;
benchMarkPtr testBenchmark;
struct Job testReadyQueue[MAX_JOB_NUMBER];
char* testCmdV[CMDV_NUM_ARGS];
enum Scheduling_Policy currSchedulePolicy = FCFS;
char* validPolicies[] = {
    "fcfs",
    "sjf",
    "pri"
};

// Setup function
int setup_suite() {

    testBenchmark = (benchMarkPtr) malloc(INPUT_BUFFER_SIZE * sizeof(struct benchMark));

    testCmdV[0] = "test";
    testCmdV[1] = "testFile";
    testCmdV[2] = "sjf";
    testCmdV[3] = "5";
    testCmdV[4] = "10";
    testCmdV[5] = "10";
    testCmdV[6] = "20";

    return 0; // Return 0 for success
}

// Teardown function - This is run after each test
int cleanup_suite() {
    if (testFp) fclose (testFp);
    free(testBenchmark);
    
    return 0; // Return 0 for success
}

// Example of setting up the test suite
CU_pSuite fcfsSuite;

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) 
        return CU_get_error();

    // Add suite to the registry with setup and teardown functions
    fcfsSuite = CU_add_suite("benchmarker Suite", setup_suite, cleanup_suite);
    if (NULL == fcfsSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(fcfsSuite, "test of openBenchmarkFile()", test_openBenchmarkFile)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(fcfsSuite, "test of createBenchmark()", test_createBenchmark)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_run_tests();

    // Clean up the CUnit registry
    CU_cleanup_registry();
    return 0;
}
