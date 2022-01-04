#pragma once
#include "concepts.hpp"

namespace marko {

float multiply_CalcVecComp(uint8_t vecCompIndex, float* matrix, float x, float y, float z);
auto multiply(const ASatisfies(MatrixC) auto& matrix_, const ASatisfies(HasXyzGFuncsC) auto& vec) { 
   float* matrix = into(matrix_); auto x_ = x(vec); auto y_ = y(vec); auto z_ = z(vec);
   return decltype(vec){multiply_CalcVecComp(0, matrix, x_, y_, z_), multiply_CalcVecComp(1, matrix, x_, y_, z_), multiply_CalcVecComp(2, matrix, x_, y_, z_)};
}
auto multiply(const ASatisfies(HasXyzGFuncsC) auto& vec, const ASatisfies(MatrixC) auto& matrix_) { return multiply(matrix_, vec); }

};
