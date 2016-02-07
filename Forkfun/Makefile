TARGET = test_fork fork1 fork2
OBJECT = fork_fun.o
CC = cc -g
FLAG = -std=c99

test_fork: fork1 fork2 fork_fun.o
	$(CC) -o test_fork fork_fun.o

fork_fun.o: fork_fun.c
	$(CC) -c fork_fun.c

fork1: fork1.c
	$(CC) fork1.c -o fork1

fork2: fork2.c
	$(CC) fork2.c -o fork2

clean:
	rm -f $(TARGET) $(OBJECT)
