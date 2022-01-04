#include <math.h> // tan()
namespace marko::MatrixT {
void new_PerspectiveProjection(float fovInRadians, float aspectRatio, float near, float far, float* elements) {
  float q = 1.0f / tan(0.5f * fovInRadians);
  float a = q / aspectRatio;
  float b = (near + far) / (near - far);
  float c = (2.0f * near * far) / (near - far);
  elements[0 + 0 * 4] = a;
  elements[1 + 1 * 4] = q;
  elements[2 + 2 * 4] = b;
  elements[2 + 3 * 4] = -1.0f;
  elements[3 + 2 * 4] = c;
}
};
