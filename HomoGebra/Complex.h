#pragma once
#include <complex>

class Complex : public std::complex<long double>
{
 public:
  using std::complex<long double>::complex;

  explicit Complex(std::complex<long double> value);

  /**
   * \brief Checks if complex number is zero.
   *
   * \return True if complex number is zero, otherwise false.
   */
  [[nodiscard]] bool IsZero() const;

  /**
   * \brief Checks if complex number is real.
   *
   *
   * \return True if complex number is real, otherwise false.
   */

  [[nodiscard]] bool IsReal() const;

  explicit operator long double() const;

  Complex& operator*=(const Complex& other);

  Complex operator*(const Complex& other) const;

  Complex& operator/=(const Complex& other);

  Complex operator/(const Complex& other) const;

  Complex& operator+=(const Complex& other);

  Complex operator+(const Complex& other) const;

  Complex& operator-=(const Complex& other);

  Complex operator-(const Complex& other) const;

  Complex operator-() const;

 private:
  static constexpr long double kEpsilon = 1e-10L;
};

inline Complex sqrt(const Complex& value)
{
  const std::complex<long double> copy = value;

  return Complex{sqrt(copy)};
}
