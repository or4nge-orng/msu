#ifndef CPOLY_H
#define CPOLY_H

#include <iostream>
#include <vector>

#define N 5 // Максимальная степень полинома согласно условию задачи

class CPoly {
private:
    int coeffs[N+1];
    int p;
    int degree;

    int mod(int val) const;
    int mod_inverse(int a) const;
    void trim();
    void derivative();
    void integral();

public:

    class CoeffRef {
        CPoly& poly;
        int idx;
    public:
        CoeffRef(CPoly& pl, int i) : poly(pl), idx(i) {}

        CoeffRef& operator=(int val) {
            poly.coeffs[idx] = poly.mod(val);
            if (poly.coeffs[idx] != 0 && idx > poly.degree) {
                poly.degree = idx;
            } else if (poly.coeffs[idx] == 0 && idx == poly.degree) {
                poly.trim();
            }
            return *this;
        }

        operator int() const { return poly.coeffs[idx]; }
    };
    CPoly(int prime);
    CPoly(int prime, const int* initial_coeffs, int size);

    int operator[](int index) const;
    CoeffRef operator[] (int index);

    CPoly operator+(int x) const;
    friend CPoly operator+(int x, const CPoly& poly);

    friend std::ostream& operator<<(std::ostream& os, const CPoly& poly);
};

#endif
