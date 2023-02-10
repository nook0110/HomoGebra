#include "GeometricObjectImplementation.h"

void GeometricObjectImplementation::Attach(const IObserver* observer)
{
  observers_.push_back(observer);
}

void GeometricObjectImplementation::Detach(const IObserver* observer)
{
  observers_.remove(observer);
}

void GeometricObjectImplementation::Notify() const
{
  for (auto observer : observers_)
  {
    observer->Update();
  }
}
