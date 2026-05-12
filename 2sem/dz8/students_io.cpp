#include "students.h"
#include <iostream>
#include<fstream>

// Конструктор по умолчанию
Student::Student() : name(""), group(0), isElder(0) {}

// Конструктор с параметрами
Student::Student(const std::string &name, int group, int isElder)
    : name(name), group(group), isElder(isElder) {}

// operator<<
std::ostream &operator<<(std::ostream &out, const Student &s) {
    out << s.name << " " << s.group << " " << s.isElder;
    return out;
}

void writeStudentsToFile(const char* filename, Student** students, int n){
    std::ofstream out("new_elders.txt");
    if (out) {
        for (int i = 0; i < n; ++i) {
            out << *students[i] << "\n";
        }
        out.close();
        std::cout << "Результат записан в new_elders.txt\n";
    } else {
        std::cerr << "Ошибка: не удалось открыть файл для записи\n";
    }
}