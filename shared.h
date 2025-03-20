#include "./headers/queue.h"
#include "./headers/benchMark.h"
#include "./headers/text.h"
#include "./headers/errorCodes.h"
#include <pthread.h>
#include <stdatomic.h>

#ifndef COMMON_H_
#define COMMON_H_

// Commonly used type in the program
typedef unsigned int u_int;

// A Stringify trick to convert enums to string by the pre-processor
#define TO_STRING(X) #X

// List of the various terminal colors and related escape codes
#define CONSOLE_COLORS(X) \
    X(RED, "\033[0;31m")   \
    X(YELLOW, "\033[0;33m") \
    X(BLUE, "\033[0;34m")   \
    X(WHITE, "\033[0m")

// Color being used for different threads
enum ConsoleColor { 
    #define X(name, _) name,
    CONSOLE_COLORS(X)
    #undef X
 };
typedef enum ConsoleColor ConsoleColor;  

// List of commands used, their variants and helper texts
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

#define RUNNING_JOB_CURSOR_STRING "===>"                    // Running Job marker when readyQueue is printed

#define REPEAT_STRING "-r"
#define REPEAT_DELAY 2
// String compare and delay time for list -r

// List of schedule policies, their string versions, 
// and attributes to look for from Job struct
#define SCH_POLICY(X) \
    X(FCFS, "fcfs", queueNumber)   \
    X(SJF, "sjf", CPUBurstTime) \
    X(PRIORITY, "pri", priority)   \
    
enum Scheduling_Policy { 
    #define X(name, _, __) name,
    SCH_POLICY(X)
    #undef X
};

// List of validPolicies, Derived from SCH_POLICY(X)
extern char* validPolicies[3];

enum Job_Status { create, waiting, running, complete }; 


#define INPUT_BUFFER_SIZE 64                                        // Used by CLI --> Scheduler
#define OUTPUT_BUFFER_SIZE 2048                                     // Used by Sch & Dis --> CLI
#define TEMP_EXTERN_BUFFER_SIZE 128                                 // Temp buffer to store intermediate output
#define COMP_EXTERN_BUFFER_SIZE 1024                                // Complete buffer length. Change this if external program is verbose
// Various buffers being used
// Input: CLI -> Sch, Output: Sch & Dis -> CLI, 
// Extern buffer: between child execv process and dispatcher

#define CMDV_NUM_ARGS 10                                            // Max args CLI parser will take

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define WRITE_PIPE 1
#define READ_PIPE 0
#define DELETE_JOB 1
#define CLEAR_JOB 0

extern enum Command cmd;                                // Global enum used across the program

extern enum Scheduling_Policy currSchedulePolicy;       // Currently enforced policy
extern enum Scheduling_Policy prevSchedulePolicy;       // Used as temp for comparison

extern u_int totalSubmittedJobs;                        // Total Jobs submitted, including test jobs
extern u_int totalCompletedJobs;                        // Total jobs completed
extern atomic_bool testRunning;                         // Is Test Running?
extern atomic_bool testReady;                           // Is Test Ready or Reset?
extern atomic_uint currCount;                           // Current Count of Jobs in the ReadyQueue
extern atomic_uint totalExpectedTime;                   // Expected Waiting time based on CPUBurstTime of waiting jobs

extern u_int rqHead;                                    // The first job entered, last of the queue
extern u_int rqTail;                                    // The first job waiting, front of the queue
extern atomic_bool schedulerBusy;                       // Is scheduler Busy?
extern pthread_mutex_t rqLock;                          // Mutex for readyQueue
extern pthread_mutex_t initLock;                        // Mutex for thread creation
extern pthread_cond_t threadReady;                      // Used during thread creation
extern pthread_cond_t rqNotFull;                        // Used by dispatcher to inform scheduler
extern pthread_cond_t rqNotEmpty;                       // Used by scheduler to inform dispatcher
extern pthread_cond_t inpBufUpdate;                     // Used by CLI Parser to inform scheduler
extern pthread_mutex_t inpBufLock;                      // Used by CLI parser
extern char* inputBufferArr[];                          // The input *Buffer*, used to copy cmdV from CLI Parser
 
extern char* outputBuffer;                              // A outputBuffer used by scheduler, dispatcher and external program

#endif  // COMMON_H_ 

#ifndef AUBATCH_MAIN_H
#define AUBATCH_MAIN_H

// Quits the program by signalling the global quit cmd
void quitProgram();

#endif // AUBATCH_MAIN_H