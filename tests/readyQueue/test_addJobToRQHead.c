#include "base.h"

void increaseRQCount(int val) { atomic_fetch_add(&currCount, val); }

void addJobToRQHead(JobPtr job) {
    increaseRQCount(1);
    testReadyQueue[rqHead] = *job;
    safeIncRQHead();
}

void test_addJobToRQHead() {
    addJobToRQHead(testJob);
    
    CU_ASSERT_EQUAL(1, rqHead);
    CU_ASSERT_STRING_EQUAL(testReadyQueue[rqHead-1].name, "TestJob"); 
    CU_ASSERT_EQUAL(1, atomic_load(&currCount));
}