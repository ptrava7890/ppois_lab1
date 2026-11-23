//
// Created by iunits on 23.11.2026.
//
#include <UnitTest++/UnitTest++.h>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include "Vector3.h"

namespace {
// Вектор от начала координат до точки (x, y, z)
Vector3 V(double x, double y, double z) { return Vector3(0, 0, 0, x, y, z); }
const double TOL = 1e-9;
}

// ---------- Конструкторы и доступ к данным ----------
TEST(DefaultConstructorIsZero) {
    Vector3 v;
    CHECK_CLOSE(0, v.getBeginX(), TOL);
    CHECK_CLOSE(0, v.getEndZ(), TOL);
    CHECK_CLOSE(0, v.length(), TOL);
}

TEST(ParametricConstructorStoresPoints) {
    Vector3 v(1, 2, 3, 4, 5, 6);
    CHECK_CLOSE(1, v.getBeginX(), TOL);
    CHECK_CLOSE(2, v.getBeginY(), TOL);
    CHECK_CLOSE(3, v.getBeginZ(), TOL);
    CHECK_CLOSE(4, v.getEndX(), TOL);
    CHECK_CLOSE(5, v.getEndY(), TOL);
    CHECK_CLOSE(6, v.getEndZ(), TOL);
}

TEST(DeltaCoordinates) {
    Vector3 v(3, 4, 2, 5, 2, 7);
    CHECK_CLOSE(2, v.dx(), TOL);
    CHECK_CLOSE(-2, v.dy(), TOL);
    CHECK_CLOSE(5, v.dz(), TOL);
}

TEST(CopyConstructor) {
    Vector3 a(1, 2, 3, 4, 5, 6);
    Vector3 b = a;
    CHECK(a == b);
}

TEST(AssignmentOperator) {
    Vector3 a(1, 2, 3, 4, 5, 6);
    Vector3 b;
    b = a;
    CHECK(a == b);
}

TEST(ConstObjectCanBeRead) {
    const Vector3 c(0, 0, 0, 3, 4, 0);
    CHECK_CLOSE(5, c.length(), TOL);
    CHECK_CLOSE(3, c.dx(), TOL);
}

// ---------- Длина и скалярное произведение ----------
TEST(LengthPythagorean) { CHECK_CLOSE(5, V(3, 4, 0).length(), TOL); }
TEST(LengthIgnoresShift) { CHECK_CLOSE(5, Vector3(1, 1, 1, 4, 5, 1).length(), TOL); }
TEST(LengthNegativeCoordinates) { CHECK_CLOSE(5, V(-3, -4, 0).length(), TOL); }
TEST(LengthSpace) { CHECK_CLOSE(std::sqrt(14.0), V(1, 2, 3).length(), TOL); }

TEST(DotProduct) { CHECK_CLOSE(32, V(1, 2, 3).dot(V(4, 5, 6)), TOL); }
TEST(DotOrthogonal) { CHECK_CLOSE(0, V(1, 0, 0).dot(V(0, 1, 0)), TOL); }
TEST(DotCommutative) {
    Vector3 a = V(1, -2, 3), b = V(4, 5, -6);
    CHECK_CLOSE(a.dot(b), b.dot(a), TOL);
}

// ---------- Сложение и вычитание ----------
TEST(Addition) { CHECK(V(1, 2, 3) + V(4, 5, 6) == V(5, 7, 9)); }

TEST(AdditionKeepsBeginOfLeftOperand) {
    Vector3 r = Vector3(1, 1, 1, 2, 2, 2) + V(1, 1, 1);
    CHECK_CLOSE(1, r.getBeginX(), TOL);
    CHECK_CLOSE(3, r.getEndX(), TOL);
    CHECK_CLOSE(3, r.getEndZ(), TOL);
}

TEST(AdditionAssignmentChain) {
    Vector3 a = V(1, 2, 3);
    (a += V(1, 1, 1)) += V(1, 1, 1);
    CHECK(a == V(3, 4, 5));
}

TEST(AdditionWithItself) {
    Vector3 a = V(1, 2, 3);
    a += a;
    CHECK(a == V(2, 4, 6));
}

TEST(Subtraction) { CHECK(V(4, 5, 6) - V(1, 2, 3) == V(3, 3, 3)); }

TEST(SubtractionAssignment) {
    Vector3 a = V(4, 5, 6);
    a -= V(1, 2, 3);
    CHECK(a == V(3, 3, 3));
}

TEST(SubtractionOfSelfIsZeroLength) {
    Vector3 a = V(1, 2, 3);
    CHECK_CLOSE(0, (a - a).length(), TOL);
}

TEST(AdditionThenSubtraction) {
    Vector3 a = V(1, 2, 3), b = V(7, 8, 9);
    CHECK(a + b - b == a);
}

// ---------- Произведение ----------
TEST(CrossProductBasis) { CHECK(V(1, 0, 0) * V(0, 1, 0) == V(0, 0, 1)); }
TEST(CrossProductExample) { CHECK(V(1, 2, 3) * V(4, 5, 6) == V(-3, 6, -3)); }

TEST(CrossProductAnticommutative) {
    Vector3 a = V(1, 2, 3), b = V(4, 5, 6);
    CHECK(a * b == -1 * (b * a));
}

TEST(CrossProductWithSelfIsZero) {
    Vector3 a = V(1, 2, 3);
    CHECK_CLOSE(0, (a * a).length(), TOL);
}

TEST(CrossProductAssignment) {
    Vector3 a = V(1, 0, 0);
    a *= V(0, 1, 0);
    CHECK(a == V(0, 0, 1));
}

TEST(MultiplyByNumber) { CHECK(V(1, 2, 3) * 2 == V(2, 4, 6)); }
TEST(MultiplyNumberByVector) { CHECK(3 * V(1, 2, 3) == V(3, 6, 9)); }

TEST(MultiplyAssignmentByNumber) {
    Vector3 a = V(2, 4, 6);
    a *= 0.5;
    CHECK(a == V(1, 2, 3));
}

TEST(MultiplyByZeroGivesZeroLength) { CHECK_CLOSE(0, (V(1, 2, 3) * 0).length(), TOL); }

// ---------- Деление ----------
TEST(Division) { CHECK(V(4, 5, 6) / V(1, 2, 3) == V(4, 2.5, 2)); }

TEST(DivisionAssignment) {
    Vector3 a = V(2, 4, 6);
    a /= V(2, 2, 2);
    CHECK(a == V(1, 2, 3));
}

TEST(DivisionByZeroProjectionThrows) {
    CHECK_THROW(V(1, 2, 3) / V(1, 0, 3), std::invalid_argument);
}

TEST(DivisionByZeroVectorThrows) {
    CHECK_THROW(V(1, 2, 3) / Vector3(), std::invalid_argument);
}

// ---------- Косинус (оператор ^) ----------
TEST(CosineParallel) { CHECK_CLOSE(1, (V(1, 2, 3) ^ V(2, 4, 6)), TOL); }
TEST(CosineOpposite) { CHECK_CLOSE(-1, (V(1, 2, 3) ^ V(-1, -2, -3)), TOL); }
TEST(CosinePerpendicular) { CHECK_CLOSE(0, (V(1, 0, 0) ^ V(0, 5, 0)), TOL); }
TEST(CosineExample) { CHECK_CLOSE(32.0 / std::sqrt(1078.0), (V(1, 2, 3) ^ V(4, 5, 6)), TOL); }
TEST(CosineWithZeroVectorThrows) { CHECK_THROW(V(1, 2, 3) ^ Vector3(), std::invalid_argument); }

// ---------- Сравнение ----------
TEST(EqualVectors) { CHECK(V(1, 2, 3) == V(1, 2, 3)); }
TEST(NotEqualVectors) { CHECK(V(1, 2, 3) != V(1, 2, 4)); }
TEST(SameDeltaDifferentBeginNotEqual) {
    CHECK(Vector3(0, 0, 0, 1, 1, 1) != Vector3(1, 1, 1, 2, 2, 2));
}

TEST(LessByLength) { CHECK(V(1, 0, 0) < V(2, 0, 0)); }
TEST(GreaterByLength) { CHECK(V(0, 0, 5) > V(3, 0, 0)); }
TEST(EqualLengthsLessEqualAndGreaterEqual) {
    CHECK(V(3, 4, 0) <= V(0, 0, 5));
    CHECK(V(3, 4, 0) >= V(0, 0, 5));
}
TEST(VectorIsNotLessThanItself) { CHECK(!(V(1, 2, 3) < V(1, 2, 3))); }

// ---------- Ввод и вывод ----------
TEST(OutputOperator) {
    std::ostringstream os;
    os << Vector3(1, 2, 3, 4, 5, 6);
    CHECK_EQUAL("(1, 2, 3) -> (4, 5, 6)", os.str());
}

TEST(InputOperator) {
    std::istringstream is("1 2 3 4 5 6");
    Vector3 v;
    is >> v;
    CHECK(v == Vector3(1, 2, 3, 4, 5, 6));
}

TEST(InputOperatorBadDataKeepsVector) {
    std::istringstream is("1 2 x");
    Vector3 v(1, 1, 1, 2, 2, 2);
    is >> v;
    CHECK(!is);
    CHECK(v == Vector3(1, 1, 1, 2, 2, 2));
}
TEST(CosineOfSmallParallelVectors) {
    Vector3 a = V(0.00001, 0, 0);
    Vector3 b = V(0.00002, 0, 0);
    CHECK_CLOSE(1.0, (a ^ b), TOL);
}

TEST(DivisionBySmallNonzeroProjection) {
    Vector3 a = V(1e-10, 4, 6);
    Vector3 b = V(1e-10, 2, 3);
    CHECK(a / b == V(1, 2, 2));
}
int main() {
    return UnitTest::RunAllTests();
}