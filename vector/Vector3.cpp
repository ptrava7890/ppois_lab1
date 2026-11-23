#include "Vector3.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
const double EPS = 1e-9;
bool same(double a, double b) { return std::fabs(a - b) < EPS; }
}

Vector3::Vector3() : x1_(0), y1_(0), z1_(0), x2_(0), y2_(0), z2_(0) {}

Vector3::Vector3(double x1, double y1, double z1,
                 double x2, double y2, double z2)
    : x1_(x1), y1_(y1), z1_(z1), x2_(x2), y2_(y2), z2_(z2) {}

double Vector3::getBeginX() const { return x1_; }
double Vector3::getBeginY() const { return y1_; }
double Vector3::getBeginZ() const { return z1_; }
double Vector3::getEndX() const { return x2_; }
double Vector3::getEndY() const { return y2_; }
double Vector3::getEndZ() const { return z2_; }

double Vector3::dx() const { return x2_ - x1_; }
double Vector3::dy() const { return y2_ - y1_; }
double Vector3::dz() const { return z2_ - z1_; }

double Vector3::length() const {
    return std::sqrt(dx() * dx() + dy() * dy() + dz() * dz());
}

double Vector3::dot(const Vector3& o) const {
    return dx() * o.dx() + dy() * o.dy() + dz() * o.dz();
}

void Vector3::setDelta(double ddx, double ddy, double ddz) {
    x2_ = x1_ + ddx;
    y2_ = y1_ + ddy;
    z2_ = z1_ + ddz;
}

Vector3& Vector3::operator+=(const Vector3& o) {
    setDelta(dx() + o.dx(), dy() + o.dy(), dz() + o.dz());
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& o) {
    setDelta(dx() - o.dx(), dy() - o.dy(), dz() - o.dz());
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& o) {
    setDelta(dy() * o.dz() - dz() * o.dy(),
             dz() * o.dx() - dx() * o.dz(),
             dx() * o.dy() - dy() * o.dx());
    return *this;
}

Vector3& Vector3::operator*=(double k) {
    setDelta(dx() * k, dy() * k, dz() * k);
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& o) {
    if (o.dx() == 0.0 || o.dy() == 0.0 || o.dz() == 0.0)
        throw std::invalid_argument("delenie na vector s nulevoi proekciei");
    setDelta(dx() / o.dx(), dy() / o.dy(), dz() / o.dz());
    return *this;
}

Vector3 Vector3::operator+(const Vector3& o) const { Vector3 r(*this); r += o; return r; }
Vector3 Vector3::operator-(const Vector3& o) const { Vector3 r(*this); r -= o; return r; }
Vector3 Vector3::operator*(const Vector3& o) const { Vector3 r(*this); r *= o; return r; }
Vector3 Vector3::operator*(double k) const { Vector3 r(*this); r *= k; return r; }
Vector3 Vector3::operator/(const Vector3& o) const { Vector3 r(*this); r /= o; return r; }

double Vector3::operator^(const Vector3& o) const {
    const double lenA = length();
    const double lenB = o.length();

    if (lenA == 0.0 || lenB == 0.0)
        throw std::invalid_argument("kosinus s nulevim vectorom ne opredelen");

    return dot(o) / (lenA * lenB);
}

bool Vector3::operator==(const Vector3& o) const {
    return same(x1_, o.x1_) && same(y1_, o.y1_) && same(z1_, o.z1_) &&
           same(x2_, o.x2_) && same(y2_, o.y2_) && same(z2_, o.z2_);
}
bool Vector3::operator!=(const Vector3& o) const { return !(*this == o); }
bool Vector3::operator<(const Vector3& o) const { return length() < o.length(); }
bool Vector3::operator>(const Vector3& o) const { return o < *this; }
bool Vector3::operator<=(const Vector3& o) const { return !(o < *this); }
bool Vector3::operator>=(const Vector3& o) const { return !(*this < o); }

Vector3 operator*(double k, const Vector3& v) { return v * k; }

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    return os << "(" << v.getBeginX() << ", " << v.getBeginY() << ", " << v.getBeginZ()
              << ") -> (" << v.getEndX() << ", " << v.getEndY() << ", " << v.getEndZ() << ")";
}

std::istream& operator>>(std::istream& is, Vector3& v) {
    double x1, y1, z1, x2, y2, z2;
    if (is >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)
        v = Vector3(x1, y1, z1, x2, y2, z2);
    return is;
}