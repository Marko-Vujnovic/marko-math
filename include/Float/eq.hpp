#pragma once
#include <cmath>
namespace marko { inline bool eq(float l, float r) { return std::abs(l - r) < 0.01; } };
