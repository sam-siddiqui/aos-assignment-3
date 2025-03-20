#include "benchmarker.h"
#include "../scheduler/scheduler.h"

int isTestRunning() {return atomic_load(&testRunning) == 1; }
int isTestReady() {return atomic_load(&testReady) == 1; }
void setTestReady() { atomic_store(&testReady, 1); }
void resetTest() { atomic_store(&testReady, 0); }
void setTestDone() {if(isTestRunning()) atomic_store(&testRunning, 0);}
void setTestRunning() { atomic_store(&testRunning, 1); }
int isTestDone() {return atomic_load(&testRunning) == 0;}

void storeBenchmarkTestHeader(FILE* fp, benchMarkPtr benchMark) {
    fprintf(fp, BENCHMARK_HEADER_FORMAT, 
        benchMark->sType, 
        benchMark->arrivalDelay,
        benchMark->numJobs, 
        benchMark->priorityLevel, 
        benchMark->minCPUTime, 
        benchMark->maxCPUTime
    );
}

void storeBenchmarkJobRow(FILE* fp, JobPtr testJob) {
    fprintf(fp, BENCHMARK_ROW_FORMAT, testJob->name, testJob->CPUBurstTime, testJob->priority, testJob->status);
}


int createTestJobs(benchMarkPtr benchMark) {
    JobPtr testJob = (JobPtr) malloc(sizeof(struct Job));
    int randBurstTime = 0;
    int randPriority = 0;
    int burstTimeDelta = benchMark->maxCPUTime - benchMark->minCPUTime;
    char* jobArgs[BENCHMARK_JOBARGS_COUNT + 1];
    int SIZE_INT_MAX_DIGITS = 12;

    jobArgs[0] = TO_STRING(test);
    jobArgs[RUN_BURSTTIME_INDEX] = malloc(SIZE_INT_MAX_DIGITS * sizeof(char));
    jobArgs[RUN_PRI_INDEX] = malloc(SIZE_INT_MAX_DIGITS * sizeof(char));
    jobArgs[RUN_JOBNAME_INDEX] = BENCHMARK_TEST_FILE_PATH;
    jobArgs[RUN_JOBNAME_INDEX + 1] = malloc(SIZE_INT_MAX_DIGITS * sizeof(char));
    jobArgs[BENCHMARK_JOBARGS_COUNT] = NULL;


    for (int i = 0; i < benchMark->numJobs; i++) {
        randBurstTime =  (rand() % (burstTimeDelta + 1)) + benchMark->minCPUTime;

        snprintf(jobArgs[RUN_BURSTTIME_INDEX], SIZE_INT_MAX_DIGITS, "%d", randBurstTime);
        
        randPriority = rand() % benchMark->priorityLevel + 1;
        
        snprintf(jobArgs[RUN_PRI_INDEX], SIZE_INT_MAX_DIGITS, "%d", randPriority);
        snprintf(jobArgs[RUN_JOBNAME_INDEX + 1], SIZE_INT_MAX_DIGITS, "%d", randBurstTime);

        populateJobFromBuffer(testJob, jobArgs);
        enqueueJob(testJob);

        storeBenchmarkJobRow(benchMark->saveFileFP, testJob);
        storeBenchmarkJobRow(stdout, testJob);

        if(benchMark->arrivalDelay > 0)
            sleep(benchMark->arrivalDelay);
    }

    free(jobArgs[RUN_BURSTTIME_INDEX]);
    free(jobArgs[RUN_PRI_INDEX]);
    free(jobArgs[RUN_JOBNAME_INDEX + 1]);
    clearJob(testJob, CLEAR_JOB);
    free(testJob);

    return SUCCESS;
}

int openBenchmarkSaveFile(char* cmdV[], FILE** ptrToFP) {
    char saveFileName[BENCHMARK_SAVE_FILENAME_SIZE];

    sprintf(saveFileName, BENCHMARK_SAVEFILENAME_FORMAT, cmdV[1], cmdV[2]);
    *ptrToFP = fopen(saveFileName, "a");

    return checkFileOpenStatus(*ptrToFP);
}

int createTestBenchmark(char* cmdV[], benchMarkPtr benchMark, FILE** ptrToFP) {    

    copyStr(benchMark->name, cmdV[BENCHMARK_JOBNAME_INDEX]);
    copyStr(benchMark->sType, cmdV[BENCHMARK_POLICY_INDEX]);
    benchMark->numJobs = atoi(cmdV[BENCHMARK_NUMJOBS_INDEX]);
    benchMark->priorityLevel = atoi(cmdV[BENCHMARK_PRILEVEL_INDEX]);
    benchMark->minCPUTime = atoi(cmdV[BENCHMARK_MINCPU_INDEX]);
    benchMark->maxCPUTime = atoi(cmdV[BENCHMARK_MAXCPU_INDEX]);
    benchMark->arrivalDelay = atoi(cmdV[BENCHMARK_ARRIVALRATE_INDEX]);
    benchMark->saveFileFP = *ptrToFP;

    if (changePolicy(benchMark->sType) == INVALID_POLICY) return INVALID_POLICY;

    return SUCCESS;
}


int createTest(char* cmdV[], FILE** ptrToFP) {
    if (openBenchmarkSaveFile(cmdV, ptrToFP) == BENCHMARK_FILE_CREATION_FAILED) return BENCHMARK_FILE_CREATION_FAILED;

    benchMarkPtr benchMark = (benchMarkPtr) malloc(INPUT_BUFFER_SIZE * sizeof(struct benchMark));
    
    if (createTestBenchmark(cmdV, benchMark, ptrToFP) == INVALID_POLICY){
        free(benchMark);
        fclose(*ptrToFP);
        return INVALID_POLICY;
    };

    initRandomSeed();

    storeBenchmarkTestHeader(benchMark->saveFileFP, benchMark);
    setConsoleColor(RED);
    storeBenchmarkTestHeader(stdout, benchMark);

    createTestJobs(benchMark);

    setTestReady();

    free(benchMark);

    return SUCCESS;
}