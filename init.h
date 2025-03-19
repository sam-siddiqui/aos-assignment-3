#include "./headers/queue.h"
#include "./headers/benchMark.h"
#include "./headers/text.h"
#include "./headers/errorCodes.h"
#include <pthread.h>
#include <stdatomic.h>

#ifndef COMMON_H_
#define COMMON_H_

typedef unsigned int u_int;

#define TO_STRING(X) #X

#define CONSOLE_COLORS(X) \
    X(RED, "\033[0;31m")   \
    X(YELLOW, "\033[0;33m") \
    X(BLUE, "\033[0;34m")   \
    X(WHITE, "\033[0m")

enum ConsoleColor { 
    #define X(name, _) name,
    CONSOLE_COLORS(X)
    #undef X
 };
typedef enum ConsoleColor ConsoleColor;  

#define Command(X) \
    X(run,  "-run", "-r", RUN_HELP_TEXT) \
    X(set_policy, "-set_policy", "-s", POLICY_HELP_TEXT) \
    X(list, "-list", "-l", LIST_HELP_TEXT) \
    X(test, "-test", "", TEST_HELP_TEXT) \
    X(quit, "-quit", "-q", QUIT_HELP_TEXT) \


enum Command { 
    init,
    help,
    #define X(cmd, _, __, ___) cmd,
    Command(X)
    #undef X
};
#define RUNNING_JOB_CURSOR_STRING "===>"
#define REPEAT_STRING "-r"
#define REPEAT_DELAY 2

#define SCH_POLICY(X) \
    X(FCFS, "fcfs", queueNumber)   \
    X(SJF, "sjf", CPUBurstTime) \
    X(PRIORITY, "pri", priority)   \
    
enum Scheduling_Policy { 
    #define X(name, _, __) name,
    SCH_POLICY(X)
    #undef X
};

extern char* validPolicies[3];

enum Job_Status { create, waiting, complete }; 

#define INPUT_BUFFER_SIZE 64
#define OUTPUT_BUFFER_SIZE 2048
#define TEMP_EXTERN_BUFFER_SIZE 128
#define COMP_EXTERN_BUFFER_SIZE 1024
#define CMDV_NUM_ARGS 10
#define ARRIVAL_RATE 0

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define WRITE_PIPE 1
#define READ_PIPE 0
#define DELETE_JOB 1
#define CLEAR_JOB 0

extern enum Command cmd;                                // Changed by CLI Parser only

extern enum Scheduling_Policy currSchedulePolicy;       // Changed by scheduler only
extern enum Scheduling_Policy prevSchedulePolicy;       // Changed by scheduler only

extern u_int totalSubmittedJobs;                        // Changed by scheduler only
extern u_int totalCompletedJobs;                        // Changed by dispatcher only
extern atomic_bool testRunning;                         // Changed by scheduler only
extern atomic_bool testReady;                           // Changed by scheduler only
extern atomic_uint currCount;                           // Changed by both scheduler and dispatcher!
extern atomic_uint totalExpectedTime;                   // Changed by both scheduler and dispatcher!

extern u_int rqHead;                                    // Changed by scheduler only
extern u_int rqTail;                                    // Changed by dispatcher only
extern atomic_bool schedulerBusy;                       // Changed only by scheduler but read by CLI Parser
extern pthread_mutex_t rqLock;                          // Used by scheduler and dispatcher
extern pthread_mutex_t initLock;                        // Used by main thread
extern pthread_cond_t threadReady;                      // Used by scheduler and dispatcher
extern pthread_cond_t rqNotFull;                        // Used by scheduler and dispatcher
extern pthread_cond_t rqNotEmpty;                       // Used by scheduler and dispatcher
extern pthread_cond_t inpBufUpdate;                     // Used by scheduler and CLI Parser
extern pthread_mutex_t inpBufLock;
extern char* inputBufferArr[];                          // Changed by both CLI Parser and Scheduler
 
extern char* outputBuffer;                              // Used by scheduler and dispatcher

#endif  // COMMON_H_ 

#ifndef AUBATCH_MAIN_H
#define AUBATCH_MAIN_H

void quitProgram();

#endif // AUBATCH_MAIN_H