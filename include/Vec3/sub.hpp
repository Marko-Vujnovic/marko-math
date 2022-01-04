#pragma once
#include "concepts.hpp"
#include "Float/sub.hpp"

#include "vecOp2.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT sub(const LT& l, float r) { return vecOp2<sub>(l, r); } }

#include "vecOp.hpp"
namespace marko { template <TSatisfies(HasXyzGFuncsC) LT> LT sub(const LT& l, const ASatisfies(HasXyzGFuncsC) auto& r) { return vecOp<sub>(l, r); } };
