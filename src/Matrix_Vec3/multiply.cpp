#include <cstdint>

namespace marko {

float multiply_CalcVecComp(uint8_t vecCompIndex, float* matrix, float x, float y, float z) { auto row = vecCompIndex;
				return matrix[0 + row*4] * x + matrix[1 + row*4] * y + matrix[2 + row*4] * z + matrix[3 + row*4];
}

};
