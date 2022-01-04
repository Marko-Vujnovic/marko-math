#include <cstdint>
#include "concepts.hpp"

namespace marko {

void invert(float* elements, float* result);

auto invert(const MatrixC auto& self) { using T = std::remove_const_t<std::remove_reference_t<decltype(self)>>;
				T res{}; invert(into(self), into(res)); return res; }

};
