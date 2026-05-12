#include "students.h"
#include <iostream>
#include <fstream>

size_t loadStudentsFromFile(const std::string& filename, Student*** students) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return 0;
    }

    size_t count = 0;
    size_t capacity = 0;
    Student s;

    if (*students == nullptr) {
        capacity = 1;
        *students = new Student*[capacity]();
    }

    while (in >> s) {
        // Если массив заполнен — расширяем
        if (count >= capacity) {
            capacity = count*2;
            Student** new_array = new Student*[capacity]();
            for (size_t i = 0; i < count; ++i) {
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