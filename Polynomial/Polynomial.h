/** @file Polynomial.h
 * @brief Интерфейс класса многочлена одной переменной.
 */
#pragma once
#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <vector>

/** @brief Многочлен с вещественными коэффициентами.
 * @details Коэффициент с индексом i стоит при x в степени i. Например,
 * Polynomial{2, -3, 1} задаёт x² − 3x + 2. Старшие нули удаляются.
 * Для нулевого многочлена по соглашению степень равна 0.
 * @see operator>>(std::istream&, Polynomial&)
 */
class Polynomial {
public:
    /** @brief Создаёт нулевой многочлен. */
    Polynomial();
    /** @brief Создаёт многочлен по списку от свободного члена к старшему. */
    Polynomial(std::initializer_list<double> coefficients);
    /** @brief Создаёт многочлен по заданной степени и массиву коэффициентов.
     * @param degree Заявленная степень до удаления старших нулей.
     * @param coefficients Массив из degree + 1 элементов.
     * @throws std::invalid_argument При несоответствии размера.
     */
    Polynomial(std::size_t degree, std::vector<double> coefficients);
    /** @return Степень после удаления старших нулей. */
    std::size_t degree() const;
    /** @return Коэффициент при x в степени power, включая ноль выше степени. */
    double operator[](std::size_t power) const;
    /** @brief Вычисляет значение в точке x по схеме Горнера. */
    double operator()(double x) const;
    /** @brief Прибавляет rhs к текущему многочлену. */
    Polynomial& operator+=(const Polynomial& rhs);
    /** @brief Вычитает rhs из текущего многочлена. */
    Polynomial& operator-=(const Polynomial& rhs);
    /** @brief Умножает текущий многочлен на rhs. */
    Polynomial& operator*=(const Polynomial& rhs);
    /** @brief Записывает частное от деления уголком, отбрасывая остаток.
     * @throws std::domain_error При делении на нулевой многочлен.
     */
    Polynomial& operator/=(const Polynomial& rhs);
    /** @brief Сравнивает соответствующие коэффициенты на точное равенство. */
    bool operator==(const Polynomial& rhs) const;
    /** @brief Проверяет различие многочленов. */
    bool operator!=(const Polynomial& rhs) const;
private:
    void normalize();
    std::vector<double> coefficients_;
};

/** @brief Возвращает сумму. */
Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
/** @brief Возвращает разность. */
Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
/** @brief Возвращает произведение. */
Polynomial operator*(Polynomial lhs, const Polynomial& rhs);
/** @brief Возвращает частное от деления уголком. @see Polynomial::operator/= */
Polynomial operator/(Polynomial lhs, const Polynomial& rhs);
/** @brief Выводит степень и коэффициенты от свободного к старшему через пробел. */
std::ostream& operator<<(std::ostream& out, const Polynomial& p);
/** @brief Читает степень и коэффициенты в формате оператора вывода.
 * @details При ошибке ввода сохраняет прежнее значение p и устанавливает failbit.
 */
std::istream& operator>>(std::istream& in, Polynomial& p);
