#include "concepts.hpp"
#include <type_traits>
namespace marko {
void multiply(float* mat1, float* mat2, float* res);
auto multiply(const MatrixC auto& l, const MatrixC auto& r) { using LT = std::remove_const_t<std::remove_reference_t<decltype(l)>>;
				auto res = constrWithZeroElems<LT>(); multiply(into(l), into(r), into(res)); return res; }
};

