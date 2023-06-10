#include "Construction.h"

const Transformation& WeekConstruction::GetTransformation() const
{
  return transformation_;
}

void Construction::Update(const Event::Moved& moved_event)
{
  // Recalculate equation
  RecalculateEquation();
}