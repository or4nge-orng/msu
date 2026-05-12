#include "students.h"
#include <iostream>

int findNewElders(Student** year1, int n1,
                     Student** year2, int n2,
                     Student** newElders) {
    int k = 0;
    for (int i = 0; i < n2; ++i) {
        if (year2[i]->isElder != 1) continue; // не староста во 2-м году

        bool wasElderInYear1 = false;
        for (int j = 0; j < n1; ++j) {
            if (year1[j]->name == year2[i]->name &&
                year1[j]->group + 100 == year2[i]->group) {
                if (year1[j]->isElder == 1) {
                    wasElderInYear1 = true;
                    break;
                }
            }
        }

        // Если в первом году не было старосты с такими параметрами, то добавляем
        if (!wasElderInYear1) {
            newElders[k] = new Student();
            newElders[k]->name = year2[i]->name;
            newElders[k]->group = year2[i]->group;
            newElders[k]->isElder = year2[i]->isElder;
            ++k;
        }
    }



    return k;
}

void sort(Student **students, int n){
   for(int i=0;i<n;i++) {
        for(int j=0;j<n-1;j++) {
            if(students[j]->group>students[j+1]->group){
                std::swap(students[j],students[j+1]);
            }
        }
    }
}

void free(Student** a, int n){
    for(int i = 0; i < n; i++) {
        delete a[i];
    }
}

void print(Student** a, int n){
    for(int i = 0; i < n; i++) {
        std::cout<<*a[i]<<"\n";
    }
    puts("_______________");
}