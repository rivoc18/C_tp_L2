all : test_csvl

test_csvl : test_csvl.o csvl.o csvl.h
	gcc -g -Wall -o test_csvl test_csvl.o csvl.o

test_csvl.o : test_csvl.c
	gcc -g -Wall -c test_csvl.c

csvl.o : csvl.c
	gcc -g -Wall -c csvl.c

clean :
	rm -f test_csvl test_csvl.o csvl.o
