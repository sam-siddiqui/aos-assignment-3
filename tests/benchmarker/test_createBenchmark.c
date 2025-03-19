#include "base.h"

int match(char* what, char* against) { return strcmp(what, against) == 0; }

int in(char** arr, int arrLen, char* target) {
    int i;
    for (i = 0; i < arrLen; i++) {
        if (strncmp(arr[i], target, strlen(target)) == 0) {
            return 1;
        }
    }
    return 0;
}

int copyStr(char* to, char* what) {
    strncpy(to, what, sizeof(to) - 1);
    to[sizeof(to) - 1] = '\0';  // Ensure null termination

    return sizeof(to) - 1 <= strlen(what);
}

int changePolicy(char* givenPolicy) {
    if (!isValidPolicy(givenPolicy)) return INVALID_POLICY;
    
    #define X(name, strrep, _) if(match(givenPolicy, strrep)) currSchedulePolicy = name;
    SCH_POLICY(X)
    #undef X

    return SUCCESS;
}

int createTestBenchmark(char* cmdV[], benchMarkPtr benchMark, FILE** ptrToFP) {    

    copyStr(benchMark->name, cmdV[1]);
    copyStr(benchMark->sType, cmdV[2]);
    benchMark->numJobs = atoi(cmdV[3]);
    benchMark->priorityLevel = atoi(cmdV[4]);
    benchMark->minCPUTime = atoi(cmdV[5]);
    benchMark->maxCPUTime = atoi(cmdV[6]);
    benchMark->saveFileFP = *ptrToFP;

    if (changePolicy(benchMark->sType) == INVALID_POLICY) return INVALID_POLICY;

    return SUCCESS;
}

void test_createBenchmark() {
    int status = createTestBenchmark(testCmdV, testBenchmark, &testFp);
    CU_ASSERT_EQUAL(status, SUCCESS);
    CU_ASSERT_STRING_EQUAL(testBenchmark->name, "testFil");
    CU_ASSERT_STRING_EQUAL(testBenchmark->sType, "sjf");
    CU_ASSERT_EQUAL(testBenchmark->numJobs, 5);
    CU_ASSERT_EQUAL(testBenchmark->priorityLevel, 10);
    CU_ASSERT_EQUAL(testBenchmark->minCPUTime, 10);
    CU_ASSERT_EQUAL(testBenchmark->maxCPUTime, 20);
}