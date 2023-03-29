#pragma once

using Complex = std::complex<long double>;

inline constexpr long double kEpsilon = 1e-12L;

inline bool IsZero(const Complex& complex)
{
  return std::abs(complex) < kEpsilon;
}

inline bool IsReal(const Complex& complex)
{
  return std::abs(complex.imag()) < kEpsilon;
}