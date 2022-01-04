#include "Matrix/new_Identity.hpp"

namespace marko::MatrixT {

// A conceptually single argument is passed as multiple separate arguments made up of its constituents because this approach yields code with less overhead when such a function is inlined in the template function calling it. Link-time optimisations need to be enabled for inlining to take place since the definition of this function resides in a .cpp file.
void new_Translation(float x, float y, float z, float* elements) {
    new_Identity(elements);
		elements[3 + 0 * 4] = x;
		elements[3 + 1 * 4] = y;
		elements[3 + 2 * 4] = z;
}

};
