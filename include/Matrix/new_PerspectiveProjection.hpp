#pragma once
#include "concepts.hpp"
namespace marko::MatrixT {

// FORCE_INLINE
void new_PerspectiveProjection(float fovInRadians, float aspectRatio, float near, float far, float* elements);
template <TSatisfies(IntoC<float*>) MatT> MatT new_PerspectiveProjection(const ASatisfies(HasAsRadC) auto fovAngle, float aspectRatio, float near, float far) { auto res = constrWithZeroElems<MatT>(); new_PerspectiveProjection(asRad(fovAngle), aspectRatio, near, far, into(res)); return res; }



};
