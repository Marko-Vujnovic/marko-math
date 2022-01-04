#pragma once
#include "concepts.hpp"
#include "Matrix/zeroOutElems.hpp"
namespace marko::MatrixT {

// FORCE_INLINE
void new_Scale(float x, float y, float z, float* elements);
template <TSatisfies(IntoC<float*>) MatT> MatT new_Scale(const ASatisfies(HasXyzGFuncsC) auto& scaleBy) { auto res = constrWithZeroElems<MatT>(); MatrixT::new_Scale(scaleBy.x, scaleBy.y, scaleBy.z, into(res)); return res; }



};
