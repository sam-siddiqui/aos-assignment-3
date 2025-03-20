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

void storeBenchmarkTestHeader(FILE* fp, benchMarkPtr benchMark);

void storeBenchmarkJobRow(FILE* fp, JobPtr testJob);

int createTestJobs(benchMarkPtr benchMark);

int openBenchmarkSaveFile(char* cmdV[], FILE** ptrToFP);

int createTestBenchmark(char* cmdV[], benchMarkPtr benchMark, FILE** ptrToFP);

int createTest(char* cmdV[], FILE** ptrToFP);

#endif