#include <stdlib.h>
#include "../utility.h"
#include "./../../init.h"
#include "../../headers/job.h"

#ifndef COMPLETE_QUEUE_H_
#define COMPLETE_QUEUE_H_

void insertToCompletedQueue(JobPtr job);

void clearCompletedQueue(int delete);

#endif