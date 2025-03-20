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
        // If no test is running, print the outputBuffer
        if(!isTestRunning()) flushOutputBuffer();
        // Convert the buffer string into char*
        cmdC = inputCleanup(cmdBuf, cmdsV);
        currCmd = cmdsV[0];

        if (isTestDone() && isTestReady() && currCmd == NULL)
            printStats();
        // Here, NULL meaning simply pressing enter with no input
        else if (currCmd == NULL) 
            printf(NO_CMD_TEXT);
        
        else if (match(currCmd, TO_STRING(help)) || match(currCmd, "?"))
            showHelp(cmdsV[1], cmdC);

        else if (match(currCmd, TO_STRING(quit)) || match(currCmd, "exit"))
            quitProgram();

        else if (match(currCmd, TO_STRING(test)))
            initBenchmarkTest(cmdsV, cmdC);
        
        else if (match(currCmd, TO_STRING(set_policy)))
            changeSchedulerPolicy(cmdsV, cmdC);

        else if (match(currCmd, TO_STRING(list)) || match(currCmd, "ls"))
            listQueue(cmdsV, cmdC);

        else if (match(currCmd, TO_STRING(run)))
            scheduleRun(cmdsV, cmdC);

        else
            printf(UNKNOWN_CMD_TEXT);
    }

    free(cmdBuf);

    return;
}