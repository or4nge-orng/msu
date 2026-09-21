a: sort.o main.o generatearray.o printarray.o copyarray.o
	gcc main.o sort.o generatearray.o printarray.o copyarray.o && rm *.o
sort.o:sort.c funcs.h
	gcc -c sort.c  
main.o: main.c funcs.h
	gcc -c main.c  
generatearray.o: generatearray.c funcs.h
	gcc -c generatearray.c
printarray.o: printarray.c funcs.h
	gcc -c printarray.c
copyarray.o: copyarray.c funcs.h
	gcc -c copyarray.c