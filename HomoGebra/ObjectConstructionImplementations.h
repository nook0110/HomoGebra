#pragma once
#include "FactoryWrapper.h"
#include "ObjectConstructor.h"
#include "Widget.h"

using LineByTwoPoints =
    ObjectConstructor<PointSelectorWrapper, PointSelectorWrapper,
                      LineByTwoPointsWrapper>;
