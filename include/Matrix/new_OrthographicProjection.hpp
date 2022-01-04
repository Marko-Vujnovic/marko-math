#pragma once
#include "concepts.hpp"
namespace marko::MatrixT {

// FORCE_INLINE
void new_OrthographicProjection(float left, float right, float bottom, float top, float near, float far, float* elements);
template <TSatisfies(IntoC<float*>) MatT> MatT new_OrthographicProjection(float left, float right, float bottom, float top, float near, float far) { auto res = constrWithZeroElems<MatT>(); new_OrthographicProjection(left, right, bottom, top, near, far, into(res)); return res; }

};
