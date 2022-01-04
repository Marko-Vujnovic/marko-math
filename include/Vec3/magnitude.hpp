#pragma once
#include "concepts.hpp"
#include <math.h>

namespace marko { template <HasXyzGFuncsC LT> float magnitude(const LT& self) { return sqrt(self.x * self.x + self.y * self.y + self.z * self.z); } }


