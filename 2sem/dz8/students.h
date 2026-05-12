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
    friend std::ifstream &operator>>(std::ifstream &, Student &);
    friend size_t findNewElders(Student**, size_t, Student**, size_t, Student**);
    friend void sort(Student**, size_t);
};

size_t loadStudentsFromFile(const std::string& filename, Student*** students);
size_t findNewElders(Student** year1, size_t n1, Student** year2, size_t n2, Student** newElders);
void sort(Student** students, size_t n);
void free(Student** a, size_t n);
void print(Student** a, size_t n);
void writeStudentsToFile(const char* filename, Student** students, size_t n);

#endif // STUDENT_H