#include <stdlib.h>
#include "../errorHandlers.h"
#include "../utility.h"
#include "../scheduler/jobCreationUtility.h"
#include "../scheduler/schedulePolicy.h"
#include "../scheduler/readyQueue.h"
#include "../../headers/benchMark.h"
#include "../../headers/job.h"
#include "../../shared.h"

#ifndef BENCHMARKER_H
#define BENCHMARKER_H

int isTestRunning();
int isTestReady();
void setTestReady();
void resetTest();
void setTestDone(); 
void setTestRunning();
int isTestDone();
// Stores the header of the benchmark table
void storeBenchmarkTestHeader(FILE* fp, benchMarkPtr benchMark);
// Stores the header of the benchmark row
void storeBenchmarkJobRow(FILE* fp, JobPtr testJob);
// Creates test jobs (the same struct was reused) based on the members in the benchmark struct
int createTestJobs(benchMarkPtr benchMark);
// Opens and checks if the file was opened properly
int openBenchmarkSaveFile(char* cmdV[], FILE** ptrToFP);
// Creates the actual benchmark struct to be used, from cmdV array (which is max 10 sized)
int createTestBenchmark(char* cmdV[], benchMarkPtr benchMark, FILE** ptrToFP);
// Wrapper around the above function
int createTest(char* cmdV[], FILE** ptrToFP);

#endif