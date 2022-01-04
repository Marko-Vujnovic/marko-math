#define FORCE_INLINE __attribute__((always_inline))

#include <math.h> // cos(), sin()

namespace marko::MatrixT {

/* FORCE_INLINE */
				// GCC complains even with -flto: warning: ‘always_inline’ function might not be inlinable [-Wattributes]
void new_Rotation(float angleInRad, float x, float y, float z, float* elements) {
		float cos_ = cos(angleInRad);
		float sin_ = sin(angleInRad);
		float oneMinusCos = 1.0f - cos_;		
		elements[0 + 0 * 4] = x * x * oneMinusCos + cos_;
		elements[0 + 1 * 4] = y * x * oneMinusCos + z * sin_;
		elements[0 + 2 * 4] = x * z * oneMinusCos - y * sin_;
		elements[1 + 0 * 4] = x * y * oneMinusCos - z * sin_;
		elements[1 + 1 * 4] = y * y * oneMinusCos + cos_;
		elements[1 + 2 * 4] = y * z * oneMinusCos + x * sin_;
		elements[2 + 0 * 4] = x * z * oneMinusCos + y * sin_;
		elements[2 + 1 * 4] = y * z * oneMinusCos - x * sin_;
		elements[2 + 2 * 4] = z * z * oneMinusCos + cos_;
}

};
