#pragma once

using Complex = std::complex<long double>;

inline constexpr long double kEpsilon = 1e-10L;

/**
 * \brief Checks if complex number is zero.
 *
 * \param complex Complex number to check.
 *
 * \return True if complex number is zero, otherwise false.
 */
inline bool IsZero(const Complex& complex)
{
  return std::abs(complex) < kEpsilon;
}

/**
 * \brief Checks if complex number is real.
 *
 * \param complex Complex number to check.
 *
 * \return True if complex number is real, otherwise false.
 */
inline bool IsReal(const Complex& complex)
{
  return std::abs(complex.imag()) < kEpsilon;
}