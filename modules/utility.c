#include "utility.h"

int match(char* what, char* against) { return strcmp(what, against) == 0; }

void setConsoleColor(ConsoleColor color) {
    switch(color) {
        #define X(name, escapeCode) \
           case name: printf(escapeCode); break;
           CONSOLE_COLORS(X);
        #undef X
        default: printf("\033[0m");
    }; 
}

void appendToBuffer(char* buffer, int bufferSize, const char* formattedNewText, ...) {
    va_list args;
    va_start(args, formattedNewText);
    
    char* endOfBuffer = strchr(buffer, '\0');
    size_t remainingSpace = bufferSize - (endOfBuffer - buffer) - 1;

    vsnprintf(endOfBuffer, remainingSpace + 1, formattedNewText, args);

    va_end(args);
}

void appendToOutputBuffer(const char* formattedNewText, ...) {

    // Repeating this due a weird bug in passing around args to above function

    va_list args;
    va_start(args, formattedNewText);

    char* endOfBuffer = strchr(outputBuffer, '\0');
    size_t remainingSpace = OUTPUT_BUFFER_SIZE - (endOfBuffer - outputBuffer) - 1;

    vsnprintf(endOfBuffer, remainingSpace + 1, formattedNewText, args);
    
    va_end(args);
}

// int appendToBuffer_(char* buffer, int bufferSize, const char* formattedNewText, ...) {
//     va_list args;
//     va_start(args, formattedNewText);

//     // Find the current null-terminator in the buffer (end of the current data)
//     char* endOfBuffer = strchr(buffer, '\0');

//     // First pass to calculate the required space for the formatted string
//     int requiredLength = vsnprintf(NULL, 0, formattedNewText, args);

//     // If the null terminator is not found or buffer is full, return
//     if (endOfBuffer == NULL || (endOfBuffer - buffer) >= bufferSize - 1) {
//         // if (buffer != outputBuffer) flushOutputBuffer();
//         return BUFFER_FULL;
//     }

//     // Calculate how much space is left in the buffer (considering the end of the current string)
//     int currentLength = endOfBuffer - buffer; // Position of null-terminator gives current length
//     int remainingSpace = bufferSize - currentLength - 1; // -1 for the null terminator

//     // If there is not enough space to append, exit
//     if (requiredLength > remainingSpace) {
//         // if (buffer != outputBuffer) flushOutputBuffer();
//         return BUFFER_FULL;
//     }

//     // Now append the formatted text to the buffer, considering the remaining space
//     vsnprintf(endOfBuffer, remainingSpace + 1, formattedNewText, args); // +1 for the null-terminator

//     va_end(args);

//     return SUCCESS;
// }

void clearBuffer(char* buffer, int maxBufferSize) {
    for (int currPos = 0;
         currPos < maxBufferSize; currPos++) {
        buffer[currPos] = '\0';
    }
}

void flushOutputBuffer() {
    setConsoleColor(YELLOW);
    if(outputBuffer != NULL && strlen(outputBuffer) > 0) 
        printf("%s \n", outputBuffer);
    clearBuffer(outputBuffer, OUTPUT_BUFFER_SIZE);
    setConsoleColor(WHITE);
}

void clearInputBuffer() { 
    
    for (int i = 0; i < CMDV_NUM_ARGS; ++i) {
        free(inputBufferArr[i]); 
        inputBufferArr[i] = NULL;
    } 
    pthread_mutex_unlock(&inpBufLock);
}

int in(char** arr, int arrLen, char* target) {
    int i;
    for (i = 0; i < arrLen; i++) {
        if (strncmp(arr[i], target, strlen(target)) == 0) {
            return 1;
        }
    }
    return 0;
}

int isStrNumericOnly(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (isdigit(str[i++]) == 0) {
            return 0;
        }
    }
    return 1;
}

int copyStr(char* to, char* what) {
    strncpy(to, what, sizeof(to) - 1);
    to[sizeof(to) - 1] = '\0';  // Ensure null termination

    return sizeof(to) - 1 <= strlen(what);
}

void updateJobStatus(JobPtr job, char* value) {
    strncpy(job->status, value, sizeof(job->status) - 1);
    job->status[sizeof(job->status) - 1] = '\0';
}

void updateJobName(JobPtr job, char* value) {
    strncpy(job->name, value, sizeof(job->name) - 1);
    job->name[sizeof(job->name) - 1] = '\0';
}

/**
 * Borrowed from
 * https://stackoverflow.com/questions/51053568/generating-a-random-uuid-in-c
 */
char* gen_uuid(int length) {
    char v[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // 3fb17ebc-bc38-4939-bc8b-74f2443281d4
    // 8 dash 4 dash 4 dash 4 dash 12

    char* buf;
    buf = (char*)malloc(length * sizeof(char));
    buf[0] = 0;

    // gen random for all spaces because lazy
    for (int i = 0; i < length; ++i) {
        buf[i] = v[rand() % 16];
    }

    // put dashes in place
    for (int dashCount = 0; dashCount < (int)(length / 4); dashCount++) {
        buf[rand() % length] = '-';
    }

    // needs end byte
    buf[length - 1] = '\0';

    return buf;
}