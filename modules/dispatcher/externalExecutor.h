#include <sys/wait.h>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../headers/job.h"
#include "./../../shared.h"
#include "../errorHandlers.h"
#include "../utility.h"

#ifndef EXECUTOR_H_
#define EXECUTOR_H_
// The part which the child process runs
// This duplicates the externBuffers to the stdout and stderr of the child process
// to capture it's outputs
void externalProgramFlow(char* const* jobArgs, int externBufferPipe[2]);

// The part which the forked parent process runs
// This listens to the externBuffer for any output from the child process
void parentProgramFlow(
    int forkedProcStatus, 
    int externBufferPipe[2], 
    char* tempExternBuffer, int tempExternBufferSize, 
    char* completeExternBuffer, int completeExternBufferSize, 
    pid_t pid
);

// The main function of the external program executor, uses fork and execv
void execute(JobPtr job, int status);

#endif