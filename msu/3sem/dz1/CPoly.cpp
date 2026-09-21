#include "CPoly.h"

int CPoly::mod(int a) const {
    int res = a % p;
    if (res < 0) res += p;
    return res;
}

int CPoly::mod_inverse(int a) const {
    a = mod(a);
    if (a == 0) {
        throw std::domain_error("Деление на ноль в поле Z_p");
    }
    int m = p;
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

void CPoly::trim() {
    while (degree > 0 && coeffs[degree] == 0) {
        --degree;
    }
}

void CPoly::derivative() {
    if (degree == 0) {
        coeffs[0] = 0;
        return;
    }
    for (int i = 1; i <= degree; ++i) {
        coeffs[i - 1] = mod(coeffs[i] * i);
    }
    coeffs[degree] = 0;
    --degree;
    trim();
}

void CPoly::integral() {
    int max_i = (degree == N) ? N - 1 : degree;
    for (int i = max_i; i >= 0; --i) {
        if (coeffs[i] == 0) continue;
        int inv = mod_inverse(i + 1);
        coeffs[i + 1] = mod(coeffs[i] * inv);
    }
    coeffs[0] = 0; // Константа интегрирования
    if (degree < N) ++degree;
    trim();
}

CPoly::CPoly(int modulus) : p(modulus), degree(0) {
    if (p <= 1) throw std::invalid_argument("Модуль p должен быть > 1");
    for (int i = 0; i <= N; ++i) coeffs[i] = 0;
}

CPoly::CPoly(int modulus, const int* init_coeffs, int size) : p(modulus), degree(0) {
    if (p <= 1) throw std::invalid_argument("Модуль p должен быть > 1");
    for (int i = 0; i <= N; ++i) coeffs[i] = 0;
    for (int i = 0; i < size && i <= N; ++i) {
        coeffs[i] = mod(init_coeffs[i]);
        if (coeffs[i] != 0) degree = i;
    }
}

int CPoly::operator[](int d) const {
    if (d < 0 || d > N) throw std::out_of_range("Индекс вне диапазона [0, N]");
    return coeffs[d];
}

CPoly::CoeffRef CPoly::operator[](int index) {
    if (index < 0 || index > N) throw std::out_of_range("Индекс вне [0, N]");
    return CoeffRef(*this, index);
}

CPoly CPoly::operator+(int x) const {
    CPoly result = *this;
    if (x > 0) {
        for (int i = 0; i < x; ++i) result.integral();
    } else if (x < 0) {
        for (int i = 0; i < -x; ++i) result.derivative();
    }
    return result;
}

CPoly operator+(int x, const CPoly& poly) {
    return poly + x;
}

std::ostream& operator<<(std::ostream& os, const CPoly& poly) {
    bool first = true;
    for (int i = poly.degree; i >= 0; --i) {
        int c = poly.mod(poly.coeffs[i]);
        if (c == 0) continue;
        if (!first) os << " + ";
        if (i == 0) os << c;
        else if (i == 1) os << c << "x";
        else os << c << "x^" << i;
        first = false;
    }
    if (first) os << "0";
    return os;
}