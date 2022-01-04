#pragma once
#include "concepts.hpp"
#include "Float/divide.hpp"

#include "vecOp2.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT divide(const LT& l, float r) { return vecOp2<divide>(l, r); } }

#include "vecOp.hpp"
namespace marko { template <HasXyzGFuncsC LT> LT divide(const LT& l, const HasXyzGFuncsC auto& r) { return vecOp<divide>(l, r); } };
