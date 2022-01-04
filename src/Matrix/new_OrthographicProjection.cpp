namespace marko::MatrixT {
void new_OrthographicProjection(float left, float right, float bottom, float top, float near, float far, float* elements) {
    elements[0 + 0 * 4] = 2.0f / (right - left);
		elements[1 + 1 * 4] = 2.0f / (top - bottom);
		elements[2 + 2 * 4] = 2.0f / (near - far);
		elements[3 + 0 * 4] = (left + right) / (left - right);
		elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
		elements[3 + 2 * 4] = (far + near) / (far - near);
}
};
