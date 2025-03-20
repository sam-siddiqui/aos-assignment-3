CC = gcc
CFLAGS = -Wall -g -ggdb -std=gnu17 -lpthread 
LDFLAGS = -lm
SCHEDULER_DIR = modules/scheduler
DISPATCHER_DIR = modules/dispatcher
CLI_DIR = modules/cliParser
PERF_DIR = modules/perfMeasure

SRC = aubatch.c \
		modules/utility.c modules/queueDisplayer.c modules/errorHandlers.c \
		$(PERF_DIR)/metricsMeasure.c $(PERF_DIR)/benchmarker.c \
		$(CLI_DIR)/cliParser.c $(CLI_DIR)/cliCommands.c $(CLI_DIR)/cliUtility.c \
		$(SCHEDULER_DIR)/scheduler.c $(SCHEDULER_DIR)/schedulePolicy.c $(SCHEDULER_DIR)/readyQueue.c $(SCHEDULER_DIR)/jobCreationUtility.c \
		$(DISPATCHER_DIR)/dispatcher.c $(DISPATCHER_DIR)/externalExecutor.c $(DISPATCHER_DIR)/completedQueue.c   

OBJ = $(SRC:.c=.o)
EXEC = aubatch.exe
DEPS = init.h

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)
	rm -f $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)