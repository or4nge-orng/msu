#include<iostream>
#include"students.h"

int main(){
    Student** year1 = nullptr;
    Student** year2 = nullptr;
    

    int n1 = loadStudentsFromFile("1year.txt", &year1);
    int n2 = loadStudentsFromFile("2year.txt", &year2);
    
    if (n1 > 0 && n2 > 0) {
        int n = std::max(n1, n2);
        
        Student *newElders[n];
        n = findNewElders(year1, n1, year2, n2, newElders);

        writeStudentsToFile("newElders.txt", newElders, n);
        free(year1, n1);
        free(year2, n2);
        delete[] year1;
        delete[] year2;
        return 0;
    }       
}
