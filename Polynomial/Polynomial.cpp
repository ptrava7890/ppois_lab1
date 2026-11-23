#include "Polynomial.h"
#include <istream>
#include <ostream>
#include <stdexcept>
#include <utility>

Polynomial::Polynomial() : coefficients_{0.0} {}

Polynomial::Polynomial(std::initializer_list<double> coefficients)
    : coefficients_(coefficients) {
    normalize();
}

Polynomial::Polynomial(std::size_t degree, std::vector<double> coefficients)
    : coefficients_(std::move(coefficients)) {
    if (coefficients_.empty() || degree != coefficients_.size() - 1)
        throw std::invalid_argument("Expected degree + 1 coefficients");
    normalize();
}

void Polynomial::normalize() {
    if (coefficients_.empty()) coefficients_.push_back(0.0);
    while (coefficients_.size() > 1 && coefficients_.back() == 0.0)
        coefficients_.pop_back();
}

std::size_t Polynomial::degree() const { return coefficients_.size() - 1; }

double Polynomial::operator[](std::size_t power) const {
    return power < coefficients_.size() ? coefficients_[power] : 0.0;
}

double Polynomial::operator()(double x) const {
    double value = coefficients_.back();
    for (std::size_t i = degree(); i > 0; --i)
        value = value * x + coefficients_[i - 1];
    return value;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    if (degree() < rhs.degree()) coefficients_.resize(rhs.coefficients_.size());
    for (std::size_t i = 0; i < rhs.coefficients_.size(); ++i)
        coefficients_[i] += rhs.coefficients_[i];
    normalize();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
    if (degree() < rhs.degree()) coefficients_.resize(rhs.coefficients_.size());
    for (std::size_t i = 0; i < rhs.coefficients_.size(); ++i)
        coefficients_[i] -= rhs.coefficients_[i];
    normalize();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
    std::vector<double> product(degree() + rhs.degree() + 1, 0.0);
    for (std::size_t i = 0; i < coefficients_.size(); ++i)
        for (std::size_t j = 0; j < rhs.coefficients_.size(); ++j)
            product[i + j] += coefficients_[i] * rhs.coefficients_[j];
    coefficients_ = std::move(product);
    normalize();
    return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial& rhs) {
    if (rhs.degree() == 0 && rhs[0] == 0.0)
        throw std::domain_error("Division by zero polynomial");
    if (degree() < rhs.degree()) {
        coefficients_.assign(1, 0.0);
        return *this;
    }
    auto remainder = coefficients_;
    std::vector<double> quotient(degree() - rhs.degree() + 1);
    for (std::size_t count = quotient.size(); count > 0; --count) {
        const std::size_t shift = count - 1;
        const double factor = remainder[shift + rhs.degree()] / rhs.coefficients_.back();
        quotient[shift] = factor;
        for (std::size_t j = 0; j < rhs.degree(); ++j)
            remainder[shift + j] -= factor * rhs[j];
    }
    coefficients_ = std::move(quotient);
    normalize();
    return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) const {
    return coefficients_ == rhs.coefficients_;
}
bool Polynomial::operator!=(const Polynomial& rhs) const { return !(*this == rhs); }

Polynomial operator+(Polynomial lhs, const Polynomial& rhs) { lhs += rhs; return lhs; }
Polynomial operator-(Polynomial lhs, const Polynomial& rhs) { lhs -= rhs; return lhs; }
Polynomial operator*(Polynomial lhs, const Polynomial& rhs) { lhs *= rhs; return lhs; }
Polynomial operator/(Polynomial lhs, const Polynomial& rhs) { lhs /= rhs; return lhs; }

std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
    out << p.degree();
    for (std::size_t i = 0; i <= p.degree(); ++i) out << ' ' << p[i];
    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& p) {
    long long degree;
    if (!(in >> degree)) return in;
    std::vector<double> coefficients;
    if (degree < 0 || static_cast<unsigned long long>(degree) >= coefficients.max_size()) {
        in.setstate(std::ios::failbit);
        return in;
    }
    for (long long i = 0; i <= degree; ++i) {
        double value;
        if (!(in >> value)) return in;
        coefficients.push_back(value);
    }
    p = Polynomial(static_cast<std::size_t>(degree), std::move(coefficients));
    return in;
}
