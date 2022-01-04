#pragma once
#include "concepts.hpp"
namespace marko::MatrixT {

// FORCE_INLINE
void new_Translation(float x, float y, float z, float* elements);
template <TSatisfies(IntoC<float*>) MatT> MatT new_Translation(const ASatisfies(HasXyzGFuncsC) auto& posDelta) { auto res = constrWithZeroElems<MatT>(); MatrixT::new_Translation(x(posDelta), y(posDelta), z(posDelta), into(res)); return res; }



};
