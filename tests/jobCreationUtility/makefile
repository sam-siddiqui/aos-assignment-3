CC = gcc
CFLAGS = -Wall -g -ggdb -std=gnu17 -lcunit
LDFLAGS = -lcunit

SRC = main.c test_createJob.c test_extractArgs.c  

OBJ = $(SRC:.c=.o)
EXEC = test_jobCreationUtility
DEPS = 

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)
	rm -f $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)