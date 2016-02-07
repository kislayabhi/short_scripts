TARGET = test_hashing
OBJECT = hash_table.o hash_test.o
CC = cc -g
FLAG = -std=c99

test_hashing: hash_table.o hash_test.o
	$(CC) $(FLAG) -o test_hashing hash_table.o hash_test.o

hash_table.o: hash_table.c
	$(CC) $(FLAG) -c hash_table.c

hash_test.o: hash_test.c
	$(CC) $(FLAG) -c hash_test.c

clean: 
	rm -f $(TARGET) $(OBJECT)
