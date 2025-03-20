#include "cliCommands.h"


void listQueue(char* cmdV[], int cmdC) {
    cmd = list;
    
    if (cmdC == 1) {
        printList();
    } else if (cmdC == 2 && match(cmdV[CMD_INDEX + 1], REPEAT_STRING)) {        // list -r (or) ls -r
        while (getRQCount() > 0 || isAJobRunning()) {
            printList();
            sleep(REPEAT_DELAY);                                                // Repeat with delay
        }
        // For the final print statement when all jobs are done
        printList();
    } else {
        printf(LIST_ERROR_TEXT);
    }
}

void changeSchedulerPolicy(char* cmdV[], int cmdC) {
    if(isTestRunning()) {                           // No change during test
        printf(ERROR_TEST_RUNNING_FORMAT, TO_STRING(set_policy));
        return;
    }
    
    if (cmdC < 2 || cmdC > 2) {                     // Too many or too litte args passed
        printf(ERROR_WRONG_NUM_ARGS_POLICY_TEXT); return;
    }

    char* givenPolicy = cmdV[CMD_INDEX + 1];
    if(!(isValidPolicy(givenPolicy))) {             // Not a valid policy
        printf(ERROR_WRONG_POLICY_TEXT); 
        return;
    }

    cmd = set_policy;
    changePolicy(givenPolicy);                      // Changes if success, else returns an errorcode
    pthread_cond_signal(&inpBufUpdate);             // Signal Scheduler

    printf(POLICY_CHANGE_SUCCESS_FORMAT, givenPolicy);
}

void scheduleRun(char* cmdV[], int cmdC) {

    if(isTestRunning()) {                                   // No run during test
        printf(ERROR_TEST_RUNNING_FORMAT, TO_STRING(run));
        return;
    }

    if (isSchedulerBusy()) {                                // Wait for scheduler to be free
        printf(ERROR_RUN_SCHEDULER_BUSY);
        return;
    }

    if(!validateRunInputs(cmdV, cmdC)) {
        printf(ERROR_RUN_TEXT_FORMAT, cmdC);
        return;
    }

    cmd = run;
    copyCmdV(cmdV);
    
    printf(
        RUN_SUCCESS_TEXT_FORMAT, 
        cmdV[RUN_JOBNAME_INDEX],
        getRQCount() + 1,
        getExpectedWaitingTime() + atoi(cmdV[RUN_BURSTTIME_INDEX]),
        getCurrPolicy()
    );

    // To avoid mismatch of RQCount and ExpectedWaitingTime, signal scheduler AFTER printing
    signalScheduler();
}

void initBenchmarkTest(char* cmdV[], int cmdC) {
    
    if (!validateTestInputs(cmdV, cmdC)) {
        printf(ERROR_TEST_TEXT);
        return;
    }

    if (isAJobRunning() || !isRQEmpty()) {                  // No test during a running test or running jobs
        printf(ERROR2_TEST_TEXT);
        return;
    }

    cmd = test;

    copyCmdV(cmdV);
    resetTest();
    signalScheduler();

    printf(TEST_SUBMIT_SUCCESS_TEXT);

    while (!isTestReady()) sleep(REPEAT_DELAY);             // Wait till Scheduler has printed all the jobs, 
                                                            // bad decision, goes against the three threads
}

void showHelp(char* cmdV, int cmdCount) {
    cmd = help;

    if (cmdCount == 1) {printf(HELP_TEXT); return;}
    //X macro to use preprocessor with generating the if-else repeats
    #define X(cmd, alias1, alias2, helpText) \
    else if (match(cmdV, TO_STRING(cmd)) || match(cmdV, alias1) || match(cmdV, alias2)) printf( helpText );
    Command(X)
    #undef X
    
    else printf("%s", ERROR_HELP_TEXT);   
}