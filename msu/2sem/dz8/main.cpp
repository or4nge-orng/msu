#include<iostream>
#include"students.h"

int main(){
    Student** year1 = nullptr;
    Student** year2 = nullptr;
    Student** newElders = nullptr;

    int n1 = loadStudentsFromFile("1year.txt", &year1);
    
    
    if (n1 < 0) {
        std::cerr << "Error while writing year1" << std::endl;
        return 1;
    }
    int n2 = loadStudentsFromFile("2year.txt", &year2);
    if (n2 < 0) {
        std::cerr << "Error while writing year2" << std::endl;
        free(year1, n1);
        delete[] year1;
        return 1;
    }
    int n = std::max(n1, n2);
        
    newElders = new Student*[n];
    n = findNewElders(year1, n1, year2, n2, newElders);

    writeStudentsToFile("newElders.txt", newElders, n);
    free(year1, n1);
    free(year2, n2);
    free(newElders, n);
    delete[] year1;
    delete[] year2;
    delete[] newElders;
    return 0;
}
