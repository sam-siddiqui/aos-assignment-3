#ifndef CLI_UTILITY_H
#define CLI_UTILITY_H

#include <string.h>

#include "../../headers/text.h"
#include "../../shared.h"

void copyCmdV(char* cmdV[]);
int inputCleanup(char* buffer, char* cmdsV[]);

#endif