#pragma once
#include "concepts.hpp"
#include "magnitude.hpp"
#include "sub.hpp"

namespace marko { template <HasXyzGFuncsC LT, HasXyzGFuncsC RT> auto distance(const LT& self, const RT& o) { return magnitude(sub(self, o)); } }

