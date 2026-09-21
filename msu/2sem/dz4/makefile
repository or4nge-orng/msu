a: read.o main.o tasks.o
	gcc main.o read.o tasks.o && rm *.o
read.o:read.c funcs.h
	gcc -c read.c  
main.o: main.c funcs.h
	gcc -c main.c  
tasks.o: tasks.c funcs.h
	gcc -c tasks.c  