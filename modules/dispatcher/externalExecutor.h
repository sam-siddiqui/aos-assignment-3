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

void externalProgramFlow(char* const* jobArgs, int externBufferPipe[2]);

void parentProgramFlow(
    int forkedProcStatus, 
    int externBufferPipe[2], 
    char* tempExternBuffer, int tempExternBufferSize, 
    char* completeExternBuffer, int completeExternBufferSize, 
    pid_t pid
);

void execute(JobPtr job, int status);

#endif