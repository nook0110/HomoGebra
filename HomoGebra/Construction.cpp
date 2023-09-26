#include "Construction.h"

namespace HomoGebra
{
const Transformation& WeekConstruction::GetTransformation() const
{
  // Return transformation
  return transformation_;
}

void Construction::Update(const ObjectEvent::Moved& moved_event)
{
  // Recalculate equation
  RecalculateEquation();
}
}  // namespace HomoGebra