#pragma once
#include "concepts.hpp"
namespace marko {

template <typename OT> using OpFunc = OT(*)(OT, OT);
template <OpFunc<float> op, TSatisfies(HasXyzGFuncsC) LT> LT vecOp2(const LT& l, float r) { return LT{op(x(l),r), op(y(l),r), op(z(l),r)}; }

};
