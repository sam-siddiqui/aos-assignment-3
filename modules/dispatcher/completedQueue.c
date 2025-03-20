#include "completedQueue.h"

void insertToCompletedQueue(JobPtr job) {
    CQNodePtr newCQJobNode = (CQNodePtr)malloc(sizeof(struct completedQueue));
    CQNodePtr lastestCQJobHead = cqHead;
    newCQJobNode->job = *job;
    newCQJobNode->nextJob = NULL;
    RunningJob = NULL;
    
    if (isCQEmpty()) {
        lastestCQJobHead = newCQJobNode;
        cqHead = lastestCQJobHead;
    } else {
        while (lastestCQJobHead->nextJob != NULL) {             // Loop through the Queue
            lastestCQJobHead = lastestCQJobHead->nextJob;
        }

        lastestCQJobHead->nextJob = newCQJobNode;               // Add the job to the last of the Queue
    }
    
}

void clearCompletedQueue(int delete) {
    CQNodePtr nextJob;
    CQNodePtr currJob = cqHead;

    while (currJob != NULL) {
        nextJob = currJob->nextJob;
        if(&nextJob->job != NULL) clearJob(&nextJob->job, delete);      // If nextJob struct's job isn't null, clear that too.
        free(currJob);
        currJob = nextJob;
    }
    
    cqHead = NULL;
}