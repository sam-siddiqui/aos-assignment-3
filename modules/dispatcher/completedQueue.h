#include <stdlib.h>
#include "../utility.h"
#include "./../../shared.h"
#include "../../headers/job.h"

#ifndef COMPLETE_QUEUE_H_
#define COMPLETE_QUEUE_H_
// Inserts at the last of the linked list Queue
void insertToCompletedQueue(JobPtr job);
// Loops through the linked list Queue and either clears the jobs or deletes
// Either way, the Queue itself it cleared and freed.
void clearCompletedQueue(int delete);

#endif