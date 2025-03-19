#include "cliParser.h"

void runCLIParser() {
    char* cmdBuf;
    char* cmdsV[CMDV_NUM_ARGS] = {NULL};
    char* currCmd;
    int cmdC = -1;
    cmdBuf = (char*)malloc(INPUT_BUFFER_SIZE * sizeof(char));

    while (cmd != quit) {
        setConsoleColor(WHITE);

        if (cmd != quit) newLinePrint();
        fgets(cmdBuf, INPUT_BUFFER_SIZE, stdin);
        
        if(!isTestRunning()) flushOutputBuffer();
        
        cmdC = inputCleanup(cmdBuf, cmdsV);
        currCmd = cmdsV[0];

        if (isTestDone() && isTestReady() && currCmd == NULL)
            printStats();

        else if (currCmd == NULL) 
            printf(NO_CMD_TEXT);
        
        else if (match(currCmd, "help") || match(currCmd, "?"))
            showHelp(cmdsV[1], cmdC);

        else if (match(currCmd, "quit") || match(currCmd, "exit"))
            quitProgram();

        else if (match(currCmd, "test"))
            initBenchmarkTest(cmdsV, cmdC);
        
        else if (match(currCmd, "set_policy"))
            changeSchedulerPolicy(cmdsV, cmdC);

        else if (match(currCmd, "list") || match(currCmd, "ls"))
            listQueue(cmdsV, cmdC);

        else if (match(currCmd, "run"))
            scheduleRun(cmdsV, cmdC);

        else
            printf(UNKNOWN_CMD_TEXT);
    }

    free(cmdBuf);

    return;
}