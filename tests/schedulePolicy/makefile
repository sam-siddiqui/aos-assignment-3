CC = gcc
CFLAGS = -Wall -g -ggdb -std=gnu17 -lcunit
LDFLAGS = -lcunit

SRC = main.c test_getJobAttribute.c test_sortQueue.c  

OBJ = $(SRC:.c=.o)
EXEC = test_FCFS
DEPS = init.h

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)
	rm -f $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)