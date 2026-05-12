a: load_students.o main.o task.o students_io.o
	g++ main.o load_students.o task.o students_io.o && rm *.o
load_students.o:load_students.cpp students.h
	g++ -c load_students.cpp  
main.o: main.cpp students.h
	g++ -c main.cpp
task.o: task.cpp students.h
	g++ -c task.cpp
students_io.o: students_io.cpp students.h
	g++ -c students_io.cpp