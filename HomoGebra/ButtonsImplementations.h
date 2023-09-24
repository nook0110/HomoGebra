#pragma once
#include "Button.h"
#include "ButtonElement.h"
#include "GeometricObjectFactory.h"

using LineByTwoPointButton =
    Button<ObjectSelector<Point>, ObjectSelector<Point>,
           FactoryWrapper<LineByTwoPointsFactory>>;
