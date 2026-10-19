#include "CPoly.h"

CPoly::Coeff::Coeff(std::shared_ptr<State> s, int idx)
    : state(std::move(s)), index(idx) {}

CPoly::Coeff& CPoly::Coeff::operator=(int val) {
    if (index < 0 || index >= state->cap) {
        throw std::out_of_range("Индекс вне диапазона [0, cap)");
    }

    int p = state->p;
    int normalized = val % p;
    if (normalized < 0) normalized += p;
    state->coeffs[index] = normalized;

    if (index > state->degree && normalized != 0) {
        state->degree = index;
    } else if (index == state->degree && normalized == 0) {
        while (state->degree > 0 && state->coeffs[state->degree] == 0) {
            state->degree--;
        }
    }
    return *this;
}

CPoly::Coeff& CPoly::Coeff::operator=(const Coeff& other) {
    if (this != &other) {
        if (state != other.state) {
            throw std::invalid_argument("Cannot assign Coeff from a different polynomial");
        }
        *this = static_cast<int>(other);
    }
    return *this;
}

CPoly::Coeff::operator int() const {
    if (index < 0 || index >= state->cap) {
        throw std::out_of_range("Индекс вне диапазона [0, cap)");
    }
    return state->coeffs[index];
}
// MARK: methods

bool CPoly::is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void CPoly::check_same_module(const CPoly& other) const {
    if (state->p != other.state->p) {
        throw std::invalid_argument("Операции возможны только для полиномов с одинаковым модулем");
    }
}

int CPoly::mod(int a) const {
    int res = a % state->p;
    if (res < 0) res += state->p;
    return static_cast<int>(res);
}

int CPoly::mod_inverse(int a) const {
    a = mod(a);
    if (a == 0) {
        throw std::domain_error("Деление на ноль в поле Z_p");
    }
    int m = state->p;
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
    while (state->degree > 0 && state->coeffs[state->degree] == 0) {
        state->degree--;
    }
}

void CPoly::derivative() {
    if (state->degree < 0) return;
    if (state->degree == 0) {
        state->coeffs[0] = 0;
        return;
    }
    for (int i = 1; i <= state->degree; ++i) {
        state->coeffs[i - 1] = mod(static_cast<int>(state->coeffs[i]) * i);
    }
    state->coeffs[state->degree] = 0;
    --state->degree;
    trim();
}

void CPoly::integral() {
    for (int i = 0; i <= state->degree; ++i) {
        if (state->coeffs[i] != 0 && (i + 1) % state->p == 0) {
            throw std::domain_error("Обратного элемента не существует, интеграл не может быть вычислен");
        }
    }

    if (state->degree + 1 >= state->cap) {
        int new_cap = std::max(state->cap * 2, state->degree + 2);

        std::unique_ptr<int[]> new_coeffs(new int[new_cap]());

        for(int i = 0; i <= state->degree; ++i) new_coeffs[i] = state->coeffs[i];

        state->coeffs = std::move(new_coeffs);
        state->cap = new_cap;
    }

    for (int i = state->degree; i >= 0; --i) {                // затираем «старьё» в этом слоте
        state->coeffs[i + 1] = (state->coeffs[i] == 0) ? 0 : mod(static_cast<int>(state->coeffs[i]) * mod_inverse(i + 1));
    }
    state->coeffs[0] = 0;                                // константа интегрирования
    ++state->degree;                                     // степень выросла
    trim(); 
}

// MARK: constuctors and destructor

CPoly::CPoly(): state(std::make_shared<State>(10, 0, P_MOD)) {}

CPoly::CPoly(const int* init_coeffs, int size, int module) {
    if (!is_prime(module)) {
        throw std::invalid_argument("Модуль должен быть простым числом");
    }
    if (size <= 0) throw std::length_error("Размер массива меньше или равен нулю");
    if (init_coeffs == nullptr) throw std::invalid_argument("Указатель на массив равен nullptr");

    state = std::make_shared<State>(size, 0, module);
    for (int i = 0; i < size; ++i) {
        int normalized = mod(init_coeffs[i]);
        state->coeffs[i] = normalized;
        if (normalized != 0) {
            state->degree = i;
        }
    }
}

CPoly::CPoly(int cap, int deg, int module) {
    if (!is_prime(module)) {
        throw std::invalid_argument("Модуль должен быть простым числом");
    }
    if (cap <= 0) throw std::length_error("Размер массива меньше или равен нулю");

    if (deg < 0 || deg >= cap) {
        throw std::out_of_range("Степень должна быть в диапазоне [0, cap)");
    }
    state = std::make_shared<State>(cap, deg, module);
}

CPoly CPoly::copy() const {
    CPoly result(state->cap, state->degree, state->p);
    for (int i = 0; i <= state->degree; ++i) {
        result.state->coeffs[i] = state->coeffs[i];
    }
    return result;
}

// MARK: operators []

CPoly::Coeff CPoly::operator[](int d) const {
    if (d < 0 || d >= state->cap) throw std::out_of_range("Индекс вне диапазона [0, N]");
    return Coeff(state, d);
}

int CPoly::operator[](int index) {
    if (index < 0 || index >= state->cap) throw std::out_of_range("Индекс вне диапазона [0, cap)");
    return state->coeffs[index];
}

// MARK: operators +-

CPoly&& CPoly::operator-() && {
    derivative();
    return std::move(*this);
}

CPoly CPoly::operator-() const & {
    CPoly res = copy();
    res.derivative();
    return res;
}

CPoly& CPoly::operator++() {
    integral();
    return *this;
}

CPoly CPoly::operator++(int) {
    CPoly tmp = copy();
    ++(*this);
    return tmp;
}

CPoly& CPoly::operator--() {
    derivative();
    return *this;
}

CPoly CPoly::operator--(int) {
    CPoly temp = copy();
    --(*this);
    return temp;
}

CPoly CPoly::operator+(const CPoly& other) const {
    check_same_module(other);
    int max_cap = std::max(state->cap, other.state->cap);
    int max_deg = std::max(state->degree, other.state->degree);

    CPoly res(max_cap, max_deg, state->p);

    for (int i = 0; i <= max_deg; ++i) {
        int a = (i <= state->degree) ? state->coeffs[i] : 0;
        int b = (i <= other.state->degree) ? other.state->coeffs[i] : 0;
        res.state->coeffs[i] = res.mod(static_cast<int>(a) + b);
    }
    res.trim();
    return res;
}

CPoly CPoly::operator-(const CPoly& other) const {
    check_same_module(other);
    int max_cap = std::max(state->cap, other.state->cap);
    int max_deg = std::max(state->degree, other.state->degree);

    CPoly res(max_cap, max_deg, state->p);
    res.state->degree = max_deg;

    for (int i = 0; i <= max_deg; ++i) {
        int a = (i <= state->degree) ? state->coeffs[i] : 0;
        int b = (i <= other.state->degree) ? other.state->coeffs[i] : 0;
        res.state->coeffs[i] = res.mod(static_cast<int>(a) - b);
    }
    res.trim();
    return res;
}

//MARK: operators <<

std::ostream& operator<<(std::ostream& os, const CPoly& poly) {

    bool first = true;
    if (poly.state->degree < 0) {
        os << "0 (mod " << poly.state->p << ")";
        return os;
    }
    for (int i = poly.state->degree; i >= 0; --i) {
        int c = poly.mod(poly.state->coeffs[i]);
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