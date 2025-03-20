#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "./../headers/job.h"
#include "./../shared.h" 

#ifndef UTILITY_H
#define UTILITY_H

// Theses macros are as is visible

#define signalScheduler() pthread_cond_signal(&inpBufUpdate);
#define signalDispatcher() pthread_cond_signal(&rqNotEmpty);
#define newLinePrint() printf("%s", CMD_HANDLE);
#define isCQEmpty() (cqHead == NULL)
#define incTotalCompletedJobs() totalCompletedJobs++;
#define inChildProcess(pid) (pid == 0)
#define isNum(ch) (ch >= '0' && ch <='9')
#define isRQEmpty() (getRQCount() <= 0)
#define isRQFull() (getRQCount() >= MAX_JOB_NUMBER)
#define initRandomSeed() srand(time(NULL));
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define isNextJobInRQWaiting() match(readyQueue[rqTail].status, TO_STRING(waiting))
#define safeIncRQHead() rqHead = (rqHead + 1) % MAX_JOB_NUMBER;
#define safeIncRQTail() rqTail = (rqTail + 1) % MAX_JOB_NUMBER;
#define isValidPolicy(policyStr) (in(validPolicies, sizeof(validPolicies), policyStr))
#define incAndGetQueueNumber() ++totalSubmittedJobs;
#define didSchedulePolicyChange() (prevSchedulePolicy != currSchedulePolicy)
#define isAJobRunning() (RunningJob != NULL)
#define isInputBufferEmpty() (inputBufferArr[0] == NULL)

#define errorForking(pid) pid == PROCESS_OR_PIPE_FAILED
#define checkProcessFailed(ch_pid) ch_pid == PROCESS_OR_PIPE_FAILED
#define pipeCreationFailed(pipeId) pipe(pipeId) == PROCESS_OR_PIPE_FAILED

// These functions are part of utility.c

// Wrapper around strcmp
int match(char* what, char* against);
// Changes terminal console color based on color enum
void setConsoleColor(ConsoleColor color);
// Appends a formatted text (just like printf) to a given buffer after size checking
void appendToBuffer(char* buffer, int bufferSize, const char* formattedNewText, ...);
// Same as appendToBuffer, but for convenience
void appendToOutputBuffer(const char* formattedNewText, ...);
// Clears a text buffer, putting '\0' values
void clearBuffer(char* buffer, int maxBufferSize);
// Prints whatever is in the output buffer
void flushOutputBuffer();
// Clears the input buffer for reuse
// This uses char**, so clearBuffer can't be used
void clearInputBuffer();
// Checks if target is in arr
int in(char** arr, int arrLen, char* target);
// Loops through char array to check if they're numbers
int isStrNumericOnly(const char* str);
// Wrapper around strcpy
int copyStr(char* to, char* what);
void updateJobStatus(JobPtr job, char* value);
void updateJobName(JobPtr job, char* value);
char* gen_uuid(int length);

#endif // UTILITY_H