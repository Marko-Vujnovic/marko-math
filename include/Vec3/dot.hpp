#pragma once
#include "concepts.hpp"

namespace marko { template <HasXyzGFuncsC LT, HasXyzGFuncsC RT> auto dot(const LT& self, const RT& o) { return x(self) * x(o) + y(self) * y(o) + z(self) * z(o) ; } }

