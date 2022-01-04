#pragma once
#include <cstring> /// memset()
void zeroOutElems(auto& o) { float* c = into(o); memset(c, 0, 16*sizeof(float)); }
template <typename CollT> constexpr void maybeZeroOutElems(CollT& o) { if constexpr (marko::AboutType<CollT>::allElemsAreZeroInit == false) { zeroOutElems(o); } }
template <typename CollT> constexpr CollT constrWithZeroElems() { CollT res{}; maybeZeroOutElems(res); return res; }
