#ifndef CPOLY_H
#define CPOLY_H

#include <iostream>
#include <vector>
#include <memory>

#define P_MOD 5 // Максимальная степень полинома согласно условию задачи

class CPoly {
private:
    struct State{
        std::unique_ptr<int[]> coeffs;
        int cap;
        int degree;
        int p;

        State(int capacity, int deg, int module)
            : coeffs(new int[capacity]()), cap(capacity), degree(deg), p(module) {}
    };

    std::shared_ptr<State> state;

    CPoly(int cap, int deg, int module);

    static bool is_prime(int n);
    void check_same_module(const CPoly& other) const;
    int mod(int val) const;
    int mod_inverse(int a) const;
    void trim();
    void derivative();
    void integral();

public:
    class Coeff {
        private:
            std::shared_ptr<State> state;
            int index;
        public:
            Coeff(std::shared_ptr<State> state, int idx);
            Coeff& operator=(int value);
            Coeff& operator=(const Coeff& other);
            operator int() const;

            friend std::ostream& operator<<(std::ostream& os, const Coeff& coeff) {
                os << static_cast<int>(coeff);
                return os;
            }
    };

    CPoly();
    CPoly(const int* init_coeffs, int size, int module = P_MOD);
    CPoly(const CPoly&) = default;
    CPoly& operator=(const CPoly&) = default;
    ~CPoly() = default;

    CPoly copy() const;

    Coeff operator[](int index) const;
    int operator[](int index);

    CPoly&& operator-() &&;
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
