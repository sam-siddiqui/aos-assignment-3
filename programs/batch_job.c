#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define LOG_FILE "batch_job_log.txt"
#define DEFAULT_SLEEP 5

int main(int argc, char* argv[]) {
    FILE* fp = fopen(LOG_FILE, "a");

    int seconds = DEFAULT_SLEEP;
    if(argc == 2) seconds = atoi(argv[1]);

    if(seconds == 0) fprintf(fp, "ArgV conversion failed at %ld", time(NULL));

    printf("Sleeping for %d seconds at %ld \n", seconds, time(NULL));
    fprintf(fp, "Sleeping for %d seconds at %ld \n", seconds, time(NULL));
    sleep(seconds);

    fclose(fp);
    return 0;
}