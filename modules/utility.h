#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "./../headers/job.h"
#include "./../shared.h" 

#ifndef UTILITY_H
#define UTILITY_H

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

int match(char* what, char* against);
void setConsoleColor(ConsoleColor color);
void appendToBuffer(char* buffer, int bufferSize, const char* formattedNewText, ...);
void appendToOutputBuffer(const char* formattedNewText, ...);
void clearBuffer(char* buffer, int maxBufferSize);
void flushOutputBuffer();
void clearInputBuffer();
int in(char** arr, int arrLen, char* target);
int isStrNumericOnly(const char* str);
int copyStr(char* to, char* what);
void updateJobStatus(JobPtr job, char* value);
void updateJobName(JobPtr job, char* value);
char* gen_uuid(int length);

#endif // UTILITY_H