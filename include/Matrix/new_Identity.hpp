#pragma once
#include "concepts.hpp"
#include "zeroOutElems.hpp"
namespace marko::MatrixT {
				void new_Identity(float* elements);  
				template <TSatisfies(IntoC<float*>) MatT> MatT new_Identity() { auto res = constrWithZeroElems<MatT>(); MatrixT::new_Identity(into(res)); return res; }
};
