#include "errorHandlers.h"
#include "../shared.h"
#include "./utility.h"

void externalProcessFailure(char* processName) {
    // If external process creation failed
    // Print that (which will be redirected to outputBuffer)
    printf(ERROR_PROC_CREATION_FAILED_FORMAT, processName);
    
    exit(EXIT_FAILURE);
}

void checkTestStatus(int status) {
    if (status == INVALID_POLICY) {
        setConsoleColor(RED);
        appendToOutputBuffer(ERROR_INVALID_POLICY_TEXT);
    }
    if (status == BENCHMARK_FILE_CREATION_FAILED) {
        setConsoleColor(RED);
        appendToOutputBuffer(ERROR_BENCH_FILE_CREATION_FAILED_TEXT);
    }
}

void checkOutputBufferAllocation() {
    if (outputBuffer == NULL) {                         // Output buffer allocation failed
        fprintf(stderr, OUTPUT_BUFFER_FAILED_TEXT);
        exit(EXIT_FAILURE);                             // The outputBuffer is needed across the program
    }
}

int checkFileOpenStatus(FILE* fp) {
    if(fp == NULL) {
        return BENCHMARK_FILE_CREATION_FAILED;
    }

    return SUCCESS;
}

int validateRunInputs(char* cmdV[], int cmdC) {
    // Check if atleast 4 arguments were passed
    // run burstTime:int priority:int jobName:str otherArgs...
    if (cmdC < RUN_MIN_ARGS_COUNT) return 0;
    
    // First Character of Job Name is a number
    char firstCharOfJobName = cmdV[RUN_JOBNAME_INDEX][0];
    if (isNum(firstCharOfJobName)) return 0;      // It is a number and shouldn't be

    // The other two inputs are numbers
    return isStrNumericOnly(cmdV[RUN_BURSTTIME_INDEX]) && isStrNumericOnly(cmdV[RUN_PRI_INDEX]);
}

int validateTestInputs(char* cmdV[], int cmdC) {
    // If num of inputs are not exactly as  BENCHMARK_TEST_PARAMS_COUNT
    if (cmdC < BENCHMARK_TEST_PARAMS_COUNT || cmdC > BENCHMARK_TEST_PARAMS_COUNT) return 0;

    // Check First Character of save fileName is a number
    char firstCharOfsaveFileName = cmdV[BENCHMARK_JOBNAME_INDEX][1];
    if (isNum(firstCharOfsaveFileName)) return 0;      // It is a number and shouldn't be

    return isValidPolicy(cmdV[BENCHMARK_POLICY_INDEX]) &&
           isStrNumericOnly(cmdV[BENCHMARK_NUMJOBS_INDEX]) && 
           isStrNumericOnly(cmdV[BENCHMARK_PRILEVEL_INDEX]) &&
           isStrNumericOnly(cmdV[BENCHMARK_MINCPU_INDEX]) &&  
           isStrNumericOnly(cmdV[BENCHMARK_MAXCPU_INDEX]) &&
           isStrNumericOnly(cmdV[BENCHMARK_ARRIVALRATE_INDEX]);
}