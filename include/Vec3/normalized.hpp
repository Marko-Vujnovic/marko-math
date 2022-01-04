#pragma once
#include "concepts.hpp"
#include "magnitude.hpp"

namespace marko { template <HasXyzGFuncsC LT> LT normalized(const LT& self) { auto m = magnitude(self); return LT{x(self) / m, y(self) / m, z(self) / m}; } }

