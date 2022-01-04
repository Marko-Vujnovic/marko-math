#include <cstdint>

namespace marko {
void multiply(float* mat1, float* mat2, float* res) {
  for (uint32_t row = 0; row < 4; row++) {
   for (uint32_t col = 0; col < 4; col++) {
    float sum = 0.0f; for (uint32_t e = 0; e < 4; e++) { sum += mat1[e + row * 4] * mat2[col + e * 4]; }
		res[col + row * 4] = sum;
   }
  }
}
};
