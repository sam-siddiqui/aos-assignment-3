#include "cliUtility.h"

void copyCmdV(char* cmdV[]) {
    pthread_mutex_lock(&inpBufLock); 
    for (int i = 0; i < CMDV_NUM_ARGS; ++i) 
    if(cmdV[i] != NULL) inputBufferArr[i] = strdup(cmdV[i]);            // Make a copy of the char*
    pthread_mutex_unlock(&inpBufLock); 
}

int inputCleanup(char* buffer, char* cmdsV[]) {
    char* argToken;
    int token_idx = 0;
    buffer[strcspn(buffer, "\r\n")] = 0;                                // First split the string
    argToken = strtok(buffer, " ");
    cmdsV[token_idx] = argToken;                                        // First arg is first token

    while (argToken != NULL && token_idx < CMDV_NUM_ARGS) {             // While not null
        token_idx++;                                                    // Loop through the various space seperated input
        argToken = strtok(NULL, " ");
        cmdsV[token_idx] = argToken;                                    // And assign it to cmdsV
    };

    for (int i = token_idx; i < CMDV_NUM_ARGS; i++) {
        cmdsV[i] = NULL;                                                // NULL out the remaining
    }

    return token_idx;   //cmdCount
}