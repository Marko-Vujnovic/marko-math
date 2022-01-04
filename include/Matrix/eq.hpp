#pragma once
#include "concepts.hpp"
namespace marko {

bool eq(const ASatisfies(MatrixC) auto& l, const ASatisfies(MatrixC) auto& r) { bool same = true; int i = 0; while(same && i < 16) { same &= (at(l, i%4, i/4) == at(r, i%4, i/4)); i++; } return same; }

};
