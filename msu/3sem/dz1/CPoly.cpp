#include "CPoly.h"

// MARK: methods

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
    if (degree < 0) return;
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
    if (degree < 0 || cap == 0) return;

    if (degree + 1 >= cap) {
        int new_cap = cap * 2;
        if (new_cap <= degree + 1) new_cap = degree + 2;

        int* new_coeffs = new int[new_cap];
        for(int i = 0; i < new_cap; ++i) new_coeffs[i] = 0;

        for(int i = 0; i <= degree; ++i) new_coeffs[i] = coeffs[i];

        delete[] coeffs;
        coeffs = new_coeffs;
        cap = new_cap;
    }

    for (int i = degree; i >= 0; --i) {
        if (coeffs[i] == 0) coeffs[i + 1] = 0;                    // затираем «старьё» в этом слоте
        else {
            int inv = mod_inverse(i + 1);          // может выбросить исключение
            coeffs[i + 1] = mod(coeffs[i] * inv);
        }
    }
    coeffs[0] = 0;                                // константа интегрирования
    ++degree;                                     // степень выросла
    trim(); 
}

// MARK: constuctors and destructor

CPoly::CPoly(): cap(10), p(P_MOD), degree(0) {
    coeffs = new int[cap];
    for (int i = 0; i < cap; ++i) coeffs[i] = 0;
}

CPoly::CPoly(const int* init_coeffs, int size, int module) : p(module) {
    if (p <= 1) throw std::invalid_argument("Модуль p должен быть > 1");
    if (size <= 0) throw std::invalid_argument("Размер массива коэффициентов должен быть > 0");
    if (init_coeffs == nullptr) throw std::invalid_argument("Указатель на массив коэффициентов не должен быть nullptr");

    cap = size;
    degree = size - 1;

    coeffs = new int[cap];

    for (int i = 0; i < cap; ++i) {
        coeffs[i] = mod(init_coeffs[i]);
    }
}

CPoly::CPoly(const CPoly& other) : cap(other.cap), degree(other.degree), p(other.p) {
    coeffs = new int[cap];
    for (int i = 0; i < cap; ++i) {
        coeffs[i] = other.coeffs[i];
    }
}

CPoly::CPoly(CPoly&& other) noexcept : coeffs(other.coeffs), cap(other.cap), degree(other.degree), p(other.p) {
    other.coeffs = nullptr;
    other.cap = 0;
    other.degree = -1;
}

CPoly::~CPoly() {
    delete[] coeffs;
}

// MARK: operators =

CPoly& CPoly::operator=(const CPoly& other) {
    if (this != &other) {
        if (cap >= other.cap) {
            degree = other.degree;
            p = other.p;
            for (int i = 0; i <= other.degree; ++i) coeffs[i]= other.coeffs[i];
            for (int i = other.degree + 1; i < cap; ++i) coeffs[i] = 0;
        } else {
            delete[] coeffs;
            cap = other.cap;
            degree = other.degree;
            p = other.p;
            coeffs = new int[cap];
            for (int i = 0; i < cap; ++i) coeffs[i] = other.coeffs[i];
        }
    }
    return *this;
}

CPoly& CPoly::operator=(CPoly&& other) noexcept {
    if (this != &other) {
        if (cap >= other.cap) {
            degree = other.degree;
            p = other.p;
            for (int i = 0; i <= other.degree; ++i) coeffs[i] = other.coeffs[i];
            for (int i = other.degree; i < cap; ++i) coeffs[i] = 0;
            delete[] other.coeffs;
            other.cap = 0;
            other.degree = -1;
            other.coeffs = nullptr;
        } else {
            delete[] coeffs;
            coeffs = other.coeffs;
            cap = other.cap;
            degree = other.degree;
            p = other.p;

            other.coeffs = nullptr;
            other.cap = 0;
            other.degree = -1;
        }
        
    }
    return *this;
}

// MARK: operators []

int CPoly::operator[](int d) const {
    if (d < 0 || d >= cap) throw std::out_of_range("Индекс вне диапазона [0, N]");
    return coeffs[d];
}

int& CPoly::operator[](int index) {
    if (index < 0 || index >= cap) throw std::out_of_range("Индекс вне диапазона [0, cap)");
    return coeffs[index];
}

// MARK: operators +-

CPoly CPoly::operator+() const & {
    CPoly res = *this;
    res.integral();
    return res;
}

CPoly CPoly::operator+() && {
    integral();
    return std::move(*this);
}

CPoly CPoly::operator-() const & {
    CPoly res = *this;
    res.derivative();
    return res;
}

CPoly CPoly::operator-() && {
    derivative();
    return std::move(*this);
}

CPoly& CPoly::operator++() {
    integral();
    return *this;
}

CPoly CPoly::operator++(int) {
    CPoly tmp = *this;
    integral();
    return tmp;
}

CPoly CPoly::operator-() && {
    derivative();
    return std::move(*this);
}

CPoly& CPoly::operator--() {
    derivative();
    return *this;
}

CPoly CPoly::operator--(int) {
    CPoly temp = (*this);
    derivative();
    return temp;
}

CPoly CPoly::operator+(const CPoly& other) const {
    int max_cap = std::max(cap, other.cap);
    int max_deg = std::max(degree, other.degree);

    CPoly res;
    res.p = p;
    if (res.cap < max_cap) {
        delete[] res.coeffs;
        res.cap = max_cap;
        res.coeffs = new int[max_cap];
    }

    for (int i = 0; i < res.cap; ++i) res.coeffs[i] = 0;
    for (int i = 0; i <= max_deg; ++i) {
        int a = (i < cap) ? coeffs[i] : 0;
        int b = (i < other.cap) ? other.coeffs[i] : 0;
        res.coeffs[i] = mod(a + b);
    }
    res.trim();
    return res;
}

CPoly CPoly::operator-(const CPoly& other) const {
    int max_cap = std::max(cap, other.cap);
    int max_deg = std::max(degree, other.degree);

    CPoly res;
    res.p = p;
    if (res.cap < max_cap) {
        delete[] res.coeffs;
        res.cap = max_cap;
        res.coeffs = new int[max_cap];
    }

    for (int i = 0; i < res.cap; ++i) res.coeffs[i] = 0;
    for (int i = 0; i <= max_deg; ++i) {
        int a = (i < cap) ? coeffs[i] : 0;
        int b = (i < other.cap) ? other.coeffs[i] : 0;
        res.coeffs[i] = mod(a - b);
    }
    res.trim();
    return res;
}

//MARK: operators <<

std::ostream& operator<<(std::ostream& os, const CPoly& poly) {

    bool first = true;
    if (poly.degree < 0) {
        os << "0 (mod " << poly.p << ")";
        return os;
    }
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