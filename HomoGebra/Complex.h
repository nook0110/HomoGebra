#pragma once
#include <complex>

/**
 * \brief Wrapper of std::complex
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date July 2023
 */
class Complex : public std::complex<long double>
{
 public:
  using std::complex<long double>::complex;

  /**
   * \brief Constructor from std::complex.
   *
   * \param value Value.
   */
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

  /**
   * \brief Converts complex number to long double.
   *
   * \warning If imaginary part is not zero, then undefined behavior.
   */
  explicit operator long double() const;

  /**
   * \brief Converts complex number to float.
   *
   * \warning If imaginary part is not zero, then undefined behavior.
   */
  explicit operator float() const;

  /**
   * \brief operator*= overload.
   *
   * \param other Other complex number.
   *
   * \return Reference to this.
   */
  Complex& operator*=(const Complex& other);

  /**
   * \brief operator* overload.
   *
   * \param other Other complex number.
   *
   * \return Result of multiplication.
   */
  Complex operator*(const Complex& other) const;

  /**
   * \brief operator/= overload.
   *
   * \param other Other complex number.
   *
   * \return Reference to this.
   */
  Complex& operator/=(const Complex& other);

  /**
   * \brief operator/ overload.
   *
   * \param other Other complex number.
   *
   * \return Result of division.
   */
  Complex operator/(const Complex& other) const;

  /**
   * \brief operator+= overload.
   *
   * \param other Other complex number.
   *
   * \return Reference to this.
   */
  Complex& operator+=(const Complex& other);

  /**
   * \brief operator+ overload.
   *
   * \param other Other complex number.
   *
   * \return Result of addition.
   */
  Complex operator+(const Complex& other) const;

  /**
   * \brief operator-= overload.
   *
   * \param other Other complex number.
   *
   * \return Reference to this.
   */
  Complex& operator-=(const Complex& other);

  /**
   * \brief operator- overload.
   *
   * \param other Other complex number.
   *
   * \return Result of subtraction.
   */
  Complex operator-(const Complex& other) const;

  /**
   * \brief operator- overload.
   *
   * \return Result of negation.
   */
  Complex operator-() const;

 private:
  static constexpr long double kEpsilon = 1e-10L;  //!< Epsilon for comparison.
};

/**
 * \brief sqrt overload.
 *
 * \param value Complex number.
 *
 * \return Square root of complex number.
 */
inline Complex sqrt(const Complex& value)
{
  const std::complex<long double> copy = value;

  return Complex{sqrt(copy)};
}
