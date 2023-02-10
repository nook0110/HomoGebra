#pragma once
#include <list>

struct Coordinate
{

};

struct PointCoordinate : public Coordinate
{

};

struct LineCoordinate : public Coordinate
{

};

class IObserver
{
public:
  virtual ~IObserver() = default;

  virtual void Update() const = 0;
};

class ISubject
{
public:
  virtual ~ISubject() = default;

  virtual void Attach(const IObserver* observer) = 0;
  virtual void Detach(const IObserver* observer) = 0;
  virtual void Notify() const = 0;
};

class GeometricObjectImplementation : public ISubject
{
public:
  ~GeometricObjectImplementation() override = default;

  // ISubject overrides

  void Attach(const IObserver* observer) override;
  void Detach(const IObserver* observer) override;
  void Notify() const override;
private:

  std::list<const IObserver*> observers_;

};

class PointImplementation : public GeometricObjectImplementation
{
private:
  PointImplementation();
};

class LineImplementation : public GeometricObjectImplementation
{};

class ConicImplementation : public GeometricObjectImplementation
{};


class Construction : public IObserver
{};

class ConstructionPoint : public Construction
{

};

class ConstructionOnPlane : public ConstructionPoint
{

};

class ConstructionLine : public Construction
{

};

class ConstructionConic : public Construction
{

};