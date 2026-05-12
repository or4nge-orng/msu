#include "students.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int loadStudentsFromFile(const std::string& filename, Student*** students) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return 0;
    }

    int count = 0;
    int capacity = 0;
    Student s;
    std::string line;

    if (*students == nullptr) {
        capacity = 1;
        *students = new Student*[capacity]();
    }

    while (std::getline(in, line)) {
        
        if (line.empty()) continue;

        std::istringstream iss(line);

        if (!(iss >> s.name)) {
            std::cerr << filename << " error: name error\n";
            return -1;
        }

        if (!(iss >> s.group) || (s.group < 100 || s.group > 999)) {
            std::cerr << filename << " error: group type error\n";
            return -2;
        }
        if (!(iss >> s.isElder) || (s.isElder != 0 && s.isElder != 1)) {
            std::cerr << filename << " error: isElder error\n";
            return -3;
        }

        if (count >= capacity) {
            capacity = count*2;
            Student** new_array = new Student*[capacity]();
            for (int i = 0; i < count; ++i) {
                new_array[i] = (*students)[i];
            }
            delete[] *students;
            *students = new_array;
        }

        (*students)[count++] = new Student(s);
    }

    in.close();
    return count;
}