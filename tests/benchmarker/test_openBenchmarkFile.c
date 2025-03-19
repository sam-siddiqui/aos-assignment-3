#include "base.h"

int checkFileOpenStatus(FILE* fp) {
    if(fp == NULL) {
        return BENCHMARK_FILE_CREATION_FAILED;
    }

    return SUCCESS;
}

int openBenchmarkSaveFile(char* cmdV[], FILE** ptrToFP) {
    char saveFileName[BENCHMARK_SAVE_FILENAME_SIZE];

    sprintf(saveFileName, BENCHMARK_SAVEFILENAME_FORMAT, cmdV[1], cmdV[2]);
    *ptrToFP = fopen(saveFileName, "w");

    return checkFileOpenStatus(*ptrToFP);
}

void test_openBenchmarkFile() {
    int status = openBenchmarkSaveFile(testCmdV, &testFp);

    CU_ASSERT_EQUAL(status, SUCCESS);
}