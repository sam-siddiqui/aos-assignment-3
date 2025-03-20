#ifndef CLI_UTILITY_H
#define CLI_UTILITY_H

#include <string.h>

#include "../../headers/text.h"
#include "../../shared.h"
// Copies args from CLI Parser to inputBufferArr
void copyCmdV(char* cmdV[]);
// Loops and extracts the inputs from the buffer into cmdsV
int inputCleanup(char* buffer, char* cmdsV[]);

#endif