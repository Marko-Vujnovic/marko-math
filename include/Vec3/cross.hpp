#pragma once
#include "concepts.hpp"

namespace marko { template <HasXyzGFuncsC LT, HasXyzGFuncsC RT> auto cross(const LT& self, const RT& other) { return LT{ y(self) * z(other) - z(self) * y(other), z(self) * x(other) - x(self) * z(other), x(self) * y(other) - y(self) * x(other)}; ; } }
