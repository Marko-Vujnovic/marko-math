#pragma once
#include "concepts.hpp"
#include "Float/add.hpp"

#include "vecOp2.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT add(const LT& l, float r) { return vecOp2<add>(l, r); } }

#include "vecOp.hpp"
namespace marko { template <TSatisfies(HasXyzGFuncsC) LT> LT add(const LT& l, const ASatisfies(HasXyzGFuncsC) auto& r) { return vecOp<add>(l, r); } };
