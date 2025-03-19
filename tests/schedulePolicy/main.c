#include "base.h"

struct Job testReadyQueue[MAX_JOB_NUMBER];
int totalCount = 0;
u_int rqHead = 0;
u_int rqTail = 0;

// Setup function
int setup_suite() {
    totalCount = 0;

    for (int i = 0; i < MAX_JOB_NUMBER; i++) {
        clearJob(&testReadyQueue[i], CLEAR_JOB);
    }
    

    JobPtr newJob = (JobPtr)malloc(sizeof(struct Job));

    for (int i = 0; i < MAX_TEST_JOB_NUMBER; i++) {
        newJob->queueNumber = rand() % MAX_TEST_JOB_NUMBER;  // Randomize for testing
        newJob->CPUBurstTime = rand() % 10;
        newJob->priority = rand() % 5;
        testReadyQueue[i] = *newJob;
        totalCount++;
    }
    rqTail = totalCount;
    free(newJob);

    return 0; // Return 0 for success
}

// Teardown function - This is run after each test
int cleanup_suite() {
    
    
    return 0; // Return 0 for success
}

// Example of setting up the test suite
CU_pSuite fcfsSuite;
CU_pSuite sjfSuite;
CU_pSuite priSuite;

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) 
        return CU_get_error();

    // Add suite to the registry with setup and teardown functions
    fcfsSuite = CU_add_suite("FCFS Suite", setup_suite, cleanup_suite);
    if (NULL == fcfsSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add suite to the registry with setup and teardown functions
    sjfSuite = CU_add_suite("SJF Suite", setup_suite, cleanup_suite);
    if (NULL == sjfSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add suite to the registry with setup and teardown functions
    priSuite = CU_add_suite("Priority Suite", setup_suite, cleanup_suite);
    if (NULL == priSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(fcfsSuite, "test of sortQueue() - fcfs", test_sortQueue_fcfs)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(fcfsSuite, "test of getJobAttribute() - fcfs", test_getJobAttribute_fcfs)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(sjfSuite, "test of sortQueue() - sjf", test_sortQueue_sjf)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(sjfSuite, "test of getJobAttribute() - sjf", test_getJobAttribute_sjf)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add individual tests to the suite
    if (NULL == CU_add_test(priSuite, "test of sortQueue() - pri", test_sortQueue_pri)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(priSuite, "test of getJobAttribute() - pri", test_getJobAttribute_pri)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    // Run all tests
    CU_basic_run_tests();

    // Clean up the CUnit registry
    CU_cleanup_registry();
    return 0;
}
