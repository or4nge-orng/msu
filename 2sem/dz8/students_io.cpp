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

std::ifstream &operator>>(std::ifstream &f,Student &l){ //перегрузка оператора извлечь из потока (>>) студента
    std::string s;int g, e;
    f>>s>>g>>e;
    if(f)l=Student(s,g,e);
    return f; 
}

void writeStudentsToFile(const char* filename, Student** students, size_t n){
    std::ofstream out("new_elders.txt");
    if (out) {
        for (size_t i = 0; i < n; ++i) {
            out << *students[i] << "\n";
        }
        out.close();
        std::cout << "Результат записан в new_elders.txt\n";
    } else {
        std::cerr << "Ошибка: не удалось открыть файл для записи\n";
    }
}