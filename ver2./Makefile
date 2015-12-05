main: main.c libfuncs.a
	gcc main.c -L. -I. -lfuncs -o main
libfuncs.a : basic.o test3.o
	ar rv libfuncs.a basic.o test3.o
basic.o: basic.c test3.h
	gcc -c basic.c
test3.o: test.c test3.h
	gcc -c -I. test3.c
clean:
	rm *.o *.a
