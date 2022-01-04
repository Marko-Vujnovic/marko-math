#pragma once
#include "concepts.hpp"

namespace marko::MatrixT {

// FORCE_INLINE
void new_Rotation(float angleInRad, float x, float y, float z, float* elements);

template <TSatisfies(IntoC<float*>) MatT> MatT new_Rotation(const ASatisfies(HasAsRadC) auto angle, const ASatisfies(HasXyzGFuncsC) auto& axis) { auto res = constrWithZeroElems<MatT>(); MatrixT::new_Rotation(asRad(angle), x(axis), y(axis), z(axis), into(res)); return res; }

};
