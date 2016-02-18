make4061: main.o util_dummy.a
	gcc -o make4061 main.o util_dummy.a

main.o: main.c
	gcc -c main.c

util_dummy.a: util.o dummy.o
	ar rcs util_dummy.a util.o dummy.o

util.o: util.c
	gcc -c util.c

dummy.o: dummy.c
	gcc -c dummy.c

clean:
	rm -rf *.o *.a
#This is just a comment.
