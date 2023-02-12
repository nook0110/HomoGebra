#include "Equation.h"

using var = Equation::var;

const std::array<var, 3> ConicEquation::prev =
{ var::kZ, var::kX, var::kY };

const std::array<var, 3> ConicEquation::next =
{ var::kY, var::kZ,var::kX };