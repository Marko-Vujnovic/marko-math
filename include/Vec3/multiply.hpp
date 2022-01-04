#pragma once
#include "concepts.hpp"
#include "Float/multiply.hpp"

#include "vecOp2.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT multiply(const LT& l, float r) { return vecOp2<multiply>(l, r); } }

#include "vecOp.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT multiply(const LT& l, const HasXyzGFuncsC auto& r) { return vecOp<multiply>(l, r); } };
