a: funcs.o main.o
	gcc main.o funcs.o && rm *.o
funcs.o:funcs.c funcs.h
	gcc -c funcs.c  
main.o: main.c funcs.h
	gcc -c main.c  