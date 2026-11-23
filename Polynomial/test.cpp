#include "Polynomial.h"
#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include <stdexcept>
#include <string>

TEST(DefaultZero) {
    CHECK_EQUAL(0.0, Polynomial()[0]);
}

TEST(ConstantDegree) {
    CHECK_EQUAL(0u, Polynomial{4}.degree());
}

TEST(DeclaredDegree) {
    Polynomial p(2, {1, 2, 3});
    CHECK_EQUAL(2u, p.degree());
}

TEST(WrongSize) {
    CHECK_THROW(Polynomial(3, {1}), std::invalid_argument);
}

TEST(EmptyArray) {
    CHECK_THROW(Polynomial(0, {}), std::invalid_argument);
}

TEST(NormalizeLeadingZeros) {
    Polynomial p{1, 2, 0, 0};
    CHECK_EQUAL(1u, p.degree());
}

TEST(NormalizeAllZeros) {
    CHECK((Polynomial{0, 0, 0} == Polynomial{}));
}

TEST(ReadCoefficient) {
    Polynomial p{1, -4, 3};
    CHECK_EQUAL(-4.0, p[1]);
}

TEST(AboveDegree) {
    CHECK_EQUAL(0.0, Polynomial{1}[10]);
}

TEST(EvaluateAtZero) {
    Polynomial p{7, 1, 2};
    CHECK_EQUAL(7.0, p(0));
}

TEST(EvaluateNegative) {
    Polynomial p{2, -3, 1};
    CHECK_EQUAL(12.0, p(-2));
}

TEST(EvaluateFraction) {
    Polynomial p{1, 2, 4};
    CHECK_CLOSE(3.0, p(0.5), 1e-12);
}

TEST(CopyIndependent) {
    Polynomial p{2};
    Polynomial q = p;
    q += Polynomial{1};
    CHECK_EQUAL(2.0, p[0]);
}

TEST(Assignment) {
    Polynomial p{1}, q{2, 3};
    p = q;
    CHECK(p == q);
}

TEST(Unequal) {
    CHECK((Polynomial{1, 2} != Polynomial{2, 1}));
}

TEST(AddDifferentDegrees) {
    CHECK((Polynomial{1} + Polynomial{2, 3} == Polynomial{3, 3}));
}

TEST(AddCancelLeading) {
    CHECK((Polynomial{1, 3} + Polynomial{2, -3} == Polynomial{3}));
}

TEST(SelfAddition) {
    Polynomial p{1, 2};
    p += p;
    CHECK((p == Polynomial{2, 4}));
}

TEST(AddReference) {
    Polynomial p{3};
    CHECK(&(p += Polynomial{1}) == &p);
}

TEST(SubtractLonger) {
    CHECK((Polynomial{3} - Polynomial{1, 2} == Polynomial{2, -2}));
}

TEST(SelfSubtraction) {
    Polynomial p{1, 2};
    p -= p;
    CHECK(p == Polynomial{});
}

TEST(SubtractNegative) {
    CHECK((Polynomial{1} - Polynomial{-3} == Polynomial{4}));
}

TEST(MultiplyLinear) {
    CHECK((Polynomial{1, 1} * Polynomial{-1, 1} == Polynomial{-1, 0, 1}));
}

TEST(MultiplyZero) {
    CHECK((Polynomial{2, 3} * Polynomial{} == Polynomial{}));
}

TEST(SquareInPlace) {
    Polynomial p{1, 2};
    p *= p;
    CHECK((p == Polynomial{1, 4, 4}));
}

TEST(MultiplyFraction) {
    CHECK((Polynomial{2, 4} * Polynomial{0.5} == Polynomial{1, 2}));
}

TEST(DivideExact) {
    CHECK((Polynomial{-1, 0, 1} / Polynomial{-1, 1} == Polynomial{1, 1}));
}

TEST(DivideWithRemainder) {
    CHECK((Polynomial{2, 0, 1} / Polynomial{1, 1} == Polynomial{-1, 1}));
}

TEST(DivideHigherDegree) {
    CHECK((Polynomial{3} / Polynomial{0, 1} == Polynomial{}));
}

TEST(DivideConstant) {
    CHECK((Polynomial{1, 3} / Polynomial{2} == Polynomial{0.5, 1.5}));
}

TEST(DivideSelf) {
    Polynomial p{1, -2, 3};
    p /= p;
    CHECK(p == Polynomial{1});
}

TEST(DivideZeroNumerator) {
    CHECK((Polynomial{} / Polynomial{1, 1} == Polynomial{}));
}

TEST(DivideZeroThrows) {
    Polynomial p{4};
    CHECK_THROW(p /= Polynomial{}, std::domain_error);
    CHECK(p == Polynomial{4});
}

TEST(SmallDivisor) {
    CHECK((Polynomial{1e-12} / Polynomial{1e-12} == Polynomial{1}));
}

TEST(OutputFormat) {
    std::ostringstream out;
    out << Polynomial{1, -2, 3};
    CHECK_EQUAL(std::string("2 1 -2 3"), out.str());
}

TEST(InputValid) {
    std::istringstream in("2 4 0 3");
    Polynomial p;
    in >> p;
    CHECK((p == Polynomial{4, 0, 3}));
}

TEST(InputNegativeDegree) {
    std::istringstream in("-1");
    Polynomial p{2};
    in >> p;
    CHECK(in.fail());
    CHECK(p == Polynomial{2});
}

TEST(InputIncomplete) {
    std::istringstream in("2 4 1");
    Polynomial p{3};
    in >> p;
    CHECK(in.fail());
    CHECK(p == Polynomial{3});
}

TEST(InputNonNumeric) {
    std::istringstream in("1 5 abc");
    Polynomial p{9};
    in >> p;
    CHECK(in.fail());
    CHECK(p == Polynomial{9});
}

TEST(InputTwoPolynomials) {
    std::istringstream in("1 1 2 0 9");
    Polynomial p, q;
    in >> p >> q;
    CHECK((p == Polynomial{1, 2}));
    CHECK(q == Polynomial{9});
}

int main() {
    return UnitTest::RunAllTests();
}
