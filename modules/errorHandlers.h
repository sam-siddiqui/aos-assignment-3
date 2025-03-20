#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef ERROR_HANDLERS_H_
#define ERROR_HANDLERS_H_

// Checks if a process creation failed
void externalProcessFailure(char* processName);
// Checks if test creation failed
void checkTestStatus(int status);
// Checks if outputBuffer was allocated and not null
void checkOutputBufferAllocation();
// Checks if file was opened and not null
int checkFileOpenStatus(FILE* fp);
// Validate run cmd's inputs
int validateRunInputs(char* cmdV[], int cmdC);

// Validate test cmd's inputs
int validateTestInputs(char* cmdV[], int cmdC);

#endif