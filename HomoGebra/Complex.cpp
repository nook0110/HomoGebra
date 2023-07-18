#include "Complex.h"

#include "Assert.h"

Complex::Complex(const std::complex<long double> value)
    : std::complex<long double>(value)
{}

bool Complex::IsZero() const
{
  // Check if real and imaginary parts are almost zero
  return std::abs(*this) < kEpsilon;
}

bool Complex::IsReal() const
{
  // Check if imaginary part is almost zero
  return std::abs(imag()) < kEpsilon;
}

Complex::operator long double() const
{
  // Check if number is real
  Expect(IsReal(), "Converting non-real number to double!");

  // Return real part
  return real();
}

Complex::operator float() const
{
  return static_cast<float>(static_cast<long double>(*this));
}

Complex& Complex::operator*=(const Complex& other)
{
  // Multiply
  _Mul(other);
  return *this;
}

Complex Complex::operator*(const Complex& other) const
{
  auto copy = *this;

  copy *= other;

  return copy;
}

Complex& Complex::operator/=(const Complex& other)
{
  // Divide
  _Div(other);
  return *this;
}

Complex Complex::operator/(const Complex& other) const
{
  auto copy = *this;

  copy /= other;

  return copy;
}

Complex& Complex::operator+=(const Complex& other)
{
  // Add
  _Add(other);
  return *this;
}

Complex Complex::operator+(const Complex& other) const
{
  auto copy = *this;

  copy += other;

  return copy;
}

Complex& Complex::operator-=(const Complex& other)
{
  // Subtract
  _Sub(other);
  return *this;
}

Complex Complex::operator-(const Complex& other) const
{
  auto copy = *this;

  copy -= other;

  return copy;
}

Complex Complex::operator-() const
{
  return Complex{-std::complex<long double>(*this)};
}