#include <cstdint>

namespace marko::MatrixT { void new_Identity(float* elements) { for(uint16_t i = 0; i < 4; i++) { elements[i +i*4] = 1; } } };
