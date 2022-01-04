#include "concepts.hpp"
#include <cstdint>
#include <type_traits>
namespace marko {
auto transpose(const MatrixC auto& self) { using T = std::remove_const_t<std::remove_reference_t<decltype(self)>>;
				T res{}; for(uint16_t i = 0; i < 16; i++) { at(res, i/4, i%4, at(self, i%4, i/4)); } return res; }

};
