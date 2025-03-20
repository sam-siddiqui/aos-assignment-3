#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "init.h"
#include "./modules/errorHandlers.h"

extern void* scheduler(void* message);
extern void* dispatcher(void* message);
extern void setConsoleColor(ConsoleColor color);
extern void runCLIParser();
extern void clearBuffer(char* buffer, int maxBufferSize);

// Global Inits
char* validPolicies[3] = {
    #define X(name, strrep, _) strrep,
    SCH_POLICY(X)
    #undef X
};
enum Command cmd = init;
enum Scheduling_Policy currSchedulePolicy = FCFS;
enum Scheduling_Policy prevSchedulePolicy = FCFS;
u_int totalSubmittedJobs = 0;
atomic_bool testRunning;
atomic_bool testReady;
atomic_uint currCount;
atomic_uint totalExpectedTime;
float avgTurnaroundTime = 0;
float avgWaitTime = 0;
float avgCPUTime = 0;
float avgResponseTime = 0;
int minResponseTime = 0;
int maxResponseTime = 0;
u_int totalCompletedJobs = 0;
float avgThroughput = 0;
struct Job readyQueue[MAX_JOB_NUMBER];
char* outputBuffer;
CQNodePtr cqHead = NULL;
JobPtr RunningJob = NULL;
FILE* fp;
u_int rqHead = 0;
u_int rqTail = 0;
char* inputBufferArr[CMDV_NUM_ARGS];

atomic_bool schedulerBusy;
pthread_mutex_t inpBufLock;
pthread_mutex_t initLock;
pthread_cond_t threadReady;
pthread_mutex_t rqLock;
pthread_cond_t rqNotFull;
pthread_cond_t rqNotEmpty;
pthread_cond_t inpBufUpdate;

/** -------------------------------------------------------- */


int main(int argc, char *argv[]) {
    pthread_t schedulerThread, executorThread;
    pthread_attr_t threadAttr;

    printf(WELCOME_MAIN_TEXT);
    char* schedulerMessage = WELCOME_SCHEDULER_TEXT;
    char* dispatcherMessage = WELCOME_DISPATCHER_TEXT;
    outputBuffer = (char*)malloc(OUTPUT_BUFFER_SIZE * sizeof(char));
    void checkOutputBufferAllocation();
    clearBuffer(outputBuffer, OUTPUT_BUFFER_SIZE);
    
    // Init the thread variables, mutex, attributes
    // And the readyQueue for which we're doing all this!
    pthread_mutex_init(&inpBufLock, NULL);
    pthread_mutex_init(&initLock, NULL);
    pthread_mutex_init(&rqLock, NULL);
    pthread_cond_init(&threadReady, NULL);
    pthread_cond_init(&rqNotEmpty, NULL);
    pthread_cond_init(&rqNotFull, NULL);
    pthread_cond_init(&inpBufUpdate, NULL);
    pthread_attr_init(&threadAttr);
    atomic_init(&currCount, 0);
    atomic_init(&totalExpectedTime, 0);
    atomic_init(&schedulerBusy, 1);
    atomic_init(&testRunning, 0);
    atomic_init(&testReady, 0);
    
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_lock(&initLock);
    pthread_create(&executorThread, &threadAttr, dispatcher, (void*) dispatcherMessage);
    pthread_cond_wait(&threadReady, &initLock);
    pthread_create(&schedulerThread, &threadAttr, scheduler, (void*) schedulerMessage);
    pthread_cond_wait(&threadReady, &initLock);
    pthread_mutex_unlock(&initLock);

    runCLIParser();

    // Wait for the two threads to exit and return
    pthread_join(schedulerThread, NULL);
    pthread_join(executorThread, NULL);

    /** The following executes AFTER the quit command and quitProgram */
    pthread_attr_destroy(&threadAttr);
    pthread_mutex_destroy(&rqLock);
    pthread_mutex_destroy(&initLock);
    pthread_mutex_destroy(&inpBufLock);
    pthread_cond_destroy(&rqNotEmpty);
    pthread_cond_destroy(&rqNotFull);
    pthread_cond_destroy(&threadReady);
    pthread_cond_destroy(&inpBufUpdate);
    setConsoleColor(WHITE);
    printf(QUIT_MAIN_TEXT);
    free(outputBuffer);
    pthread_exit(NULL);
}

void quitProgram() {
    cmd = quit;

    setConsoleColor(WHITE);
    printf(QUIT_CLI_TEXT);

    // Signal the scheduler to wake up and update itself
    pthread_cond_signal(&inpBufUpdate);    
}