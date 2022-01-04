#pragma once
#include "concepts.hpp"
namespace marko {

template <typename OT> using OpFunc = OT(*)(OT, OT);
template <OpFunc<float> op, TSatisfies(HasXyzGFuncsC) LT>
LT vecOp(const LT& l, const ASatisfies(HasXyzGFuncsC) auto& r) { return LT{op(x(l),x(r)), op(y(l),y(r)), op(z(l),z(r))}; }

};
