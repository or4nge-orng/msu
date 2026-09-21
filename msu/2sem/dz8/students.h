// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    public:
    std::string name;
    int group;
    int isElder;

    Student();
    Student(const std::string &name, int group, int isElder);

    friend std::ostream &operator<<(std::ostream &, const Student &);
    friend int findNewElders(Student**, int, Student**, int, Student**);
    friend void sort(Student**, int);
};

int loadStudentsFromFile(const std::string& filename, Student*** students);
int findNewElders(Student** year1, int n1, Student** year2, int n2, Student** newElders);
void sort(Student** students, int n);
void free(Student** a, int n);
void print(Student** a, int n);
void writeStudentsToFile(const char* filename, Student** students, int n);

#endif // STUDENT_H