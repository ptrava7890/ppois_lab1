/**
 * @file Vector3.h
 * @author Трава Пётр
 * @brief Класс трёхмерного вектора, заданного координатами начала и конца.
 */
#ifndef LAB1_VECTOR3_H
#define LAB1_VECTOR3_H

#include <iosfwd>

/**
 * @brief Вектор в трёхмерном пространстве.
 * @details Хранит две точки: начало и конец. Операции над векторами
 * работают с приращениями (конец минус начало), а результат строится
 * от начала левого операнда.
 */
class Vector3 {
public:
    /** @brief Нулевой вектор: начало и конец в (0, 0, 0). */
    Vector3();

    /**
     * @brief Вектор по координатам начала и конца.
     * @param x1,y1,z1 координаты начала
     * @param x2,y2,z2 координаты конца
     */
    Vector3(double x1, double y1, double z1,
            double x2, double y2, double z2);

    /** @return X-координата начала вектора. */
    double getBeginX() const;
    /** @return  Y-координата начала вектора. */
    double getBeginY() const;
    /** @return Z-координата начала вектора. */
    double getBeginZ() const;
    /** @return X-координата конца вектора. */
    double getEndX() const;
    /** @return Y-координата конца вектора. */
    double getEndY() const;
    /** @return Z-координата конца вектора. */
    double getEndZ() const;

    /** @brief Проекции вектора на оси (конец минус начало). */
    double dx() const;
    double dy() const;
    double dz() const;

    /** @return длина вектора */
    double length() const;

    /** @return скалярное произведение с вектором other */
    double dot(const Vector3& other) const;

    /**
  * @brief Прибавляет другой вектор к текущему, сохраняя начало текущего вектора.
  * @param other Вектор, который прибавляется.
  * @return Ссылка на текущий вектор после сложения.
  */
    Vector3& operator+=(const Vector3& other);

    /**
     * @brief Вычитает другой вектор из текущего, сохраняя начало текущего вектора.
     * @param other Вектор, который вычитается.
     * @return Ссылка на текущий вектор после вычитания.
     */
    Vector3& operator-=(const Vector3& other);

    /**
  * @brief Записывает в текущий вектор результат векторного произведения.
  * @param other Правый множитель в произведении (*this) × other.
  * @return Ссылка на текущий вектор после умножения.
  */
    Vector3& operator*=(const Vector3& other);

    /**
     * @brief Умножает каждую проекцию текущего вектора на число.
     * @param k Число, на которое умножаются проекции.
     * @return Ссылка на текущий вектор после умножения.
     */
    Vector3& operator*=(double k);

    /**
     * @brief Делит каждую проекцию текущего вектора на соответствующую проекцию другого.
     * @param other Вектор, проекции которого используются как делители.
     * @return Ссылка на текущий вектор после деления.
    * @throws std::invalid_argument Если хотя бы одна проекция делителя равна нулю.
     */
    Vector3& operator/=(const Vector3& other);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator*(double k) const;
    Vector3 operator/(const Vector3& other) const;

    /**
     * @brief Косинус угла между векторами.
     * @throws std::invalid_argument если один из векторов нулевой
     * @note У оператора ^ низкий приоритет, пишите (a ^ b) в скобках.
     */
    double operator^(const Vector3& other) const;

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    /** @brief Операторы сравнения сравнивают длины векторов. */
    bool operator>(const Vector3& other) const;
    bool operator>=(const Vector3& other) const;
    bool operator<(const Vector3& other) const;
    bool operator<=(const Vector3& other) const;

private:
    /** @brief Задаёт конец так, чтобы приращения стали (ddx, ddy, ddz). */
    void setDelta(double ddx, double ddy, double ddz);

    double x1_, y1_, z1_;   // начало
    double x2_, y2_, z2_;   // конец
};

/** @brief Число на вектор (не-член, чтобы работало 3 * v). */
Vector3 operator*(double k, const Vector3& v);

/** @brief Вывод в виде (x1, y1, z1) -> (x2, y2, z2). */
std::ostream& operator<<(std::ostream& os, const Vector3& v);

/** @brief Ввод шести чисел: x1 y1 z1 x2 y2 z2. */
std::istream& operator>>(std::istream& is, Vector3& v);

#endif
