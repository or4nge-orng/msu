#ifndef CPOLY_H
#define CPOLY_H

#include <iostream>
#include <vector>

#define P_MOD 5 // Максимальная степень полинома согласно условию задачи

class CPoly {
private:
    int* coeffs;
    int cap;
    int p;
    int degree;

    int mod(int val) const;
    int mod_inverse(int a) const;
    void trim();
    void derivative();
    void integral();

public:
    
	CPoly();
    CPoly(const int* init_coeffs, int size, int module = P_MOD);
    CPoly(const CPoly& other);
    CPoly(CPoly&& other) noexcept;
    ~CPoly();

    CPoly& operator=(const CPoly& other);
    CPoly& operator=(CPoly&& other) noexcept;

    int operator[](int index) const;
    int& operator[](int index);

    CPoly operator+() &&;
    CPoly operator+() const &;

    CPoly operator-() &&;
    CPoly operator-() const &;

    CPoly& operator++();
    CPoly operator++(int);

    CPoly& operator--();
    CPoly operator--(int);

    CPoly operator+(const CPoly& other) const;
    CPoly operator-(const CPoly& other) const;


    friend std::ostream& operator<<(std::ostream& os, const CPoly& poly);
};

#endif
