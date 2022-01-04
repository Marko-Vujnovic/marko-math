#pragma once
#include "concepts.hpp"
#include <cstdint>
#include <ostream>
namespace marko {

std::ostream& operator<<(std::ostream& os, const ASatisfies(MatrixC) auto& obj) { os << ""; for(uint16_t i=0; i<4*4; i++) { os << at(obj, i%4, i/4) << ((i%4 == 3) ? "\n" : " "); } os << ""; return os; }

};
