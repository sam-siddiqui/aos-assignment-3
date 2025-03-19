#include "cliUtility.h"

void copyCmdV(char* cmdV[]) {
    pthread_mutex_lock(&inpBufLock); 
    for (int i = 0; i < CMDV_NUM_ARGS; ++i) 
    if(cmdV[i] != NULL) inputBufferArr[i] = strdup(cmdV[i]);  
    pthread_mutex_unlock(&inpBufLock); 
}

int inputCleanup(char* buffer, char* cmdsV[]) {
    char* argToken;
    int token_idx = 0;
    buffer[strcspn(buffer, "\r\n")] = 0;
    argToken = strtok(buffer, " ");
    cmdsV[token_idx] = argToken;

    while (argToken != NULL && token_idx < CMDV_NUM_ARGS) {
        token_idx++;
        argToken = strtok(NULL, " ");
        cmdsV[token_idx] = argToken;
    };

    for (int i = token_idx; i < CMDV_NUM_ARGS; i++) {
        cmdsV[i] = NULL;
    }

    return token_idx;   //cmdCount
}