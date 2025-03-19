#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef ERROR_HANDLERS_H_
#define ERROR_HANDLERS_H_

void externalProcessFailure(char* processName);

void checkTestStatus(int status);

void checkOutputBufferAllocation();

int checkFileOpenStatus(FILE* fp);

int validateRunInputs(char* cmdV[], int cmdC);

int validateTestInputs(char* cmdV[], int cmdC);

#endif