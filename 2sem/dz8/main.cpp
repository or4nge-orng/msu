#include<iostream>
#include"students.h"

int main(){
    Student** year1 = nullptr;
    Student** year2 = nullptr;
    

    size_t n1 = loadStudentsFromFile("1year.txt", &year1);
    size_t n2 = loadStudentsFromFile("2year.txt", &year2);
    size_t n = std::max(n1, n2);

    Student *newElders[n];

    n = findNewElders(year1, n1, year2, n2, newElders);

    for(size_t i=0;i<n1;i++)
        std::cout<<*year1[i]<<"\n";//печать данных всех записанных в файл студентов
    puts("_______________");
    for(size_t i=0;i<n2;i++)
        std::cout<<*year2[i]<<"\n";//печать данных всех записанных в файл студентов
    puts("_______________");
    for(size_t i=0;i<n;i++)
        std::cout<<*newElders[i]<<"\n";

    writeStudentsToFile("newElders.txt", newElders, n);
    free(year1, n1);
    free(year2, n2);
    delete[] year1;
    delete[] year2;
    return 0;    
}
