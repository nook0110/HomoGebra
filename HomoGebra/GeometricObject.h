#pragma once

#include "GeometricObjectImplementation.h"
#include "GeometricObjectBody.h"

class Point
{
private:
  PointBody body_;
  PointImplementation implementation_;
};

class Line
{
private:
  LineBody body_;
  LineImplementation implementation_;
};

class Conic
{
private:
  ConicBody body_;
  ConicImplementation implementation_;
};