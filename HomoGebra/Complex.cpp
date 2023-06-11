#include "Complex.h"

#include <cassert>

Complex::Complex(const std::complex<long double> value)
    : std::complex<long double>(value)
{}

bool Complex::IsZero() const { return std::abs(*this) < kEpsilon; }

bool Complex::IsReal() const { return std::abs(imag()) < kEpsilon; }

Complex::operator long double() const
{
  assert(IsReal());
  return real();
}

Complex& Complex::operator*=(const Complex& other)
{
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