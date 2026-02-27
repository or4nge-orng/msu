a: funcs.o main.o arrayread.o
	gcc main.o funcs.o arrayread.o
funcs.o:funcs.c funcs.h
	gcc -c funcs.c  
main.o: main.c funcs.h
	gcc -c main.c  
arrayread.o: arrayread.c funcs.h
	gcc -c arrayread.c