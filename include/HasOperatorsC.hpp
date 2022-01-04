#include <utility> // declval
#include "concepts.hpp" 

namespace marko {

template<typename T> concept OperandC = requires(T a) { 
				{ add(a, a) } -> convertible_to<T>; 
				{ sub(a, a) } -> convertible_to<T>; 
};
template<typename T, typename O> concept MultipliableWith = requires(T a) { { multiply(std::declval<T>(), std::declval<O>()) }; };
template<typename T, typename O> concept DivisibleBy = requires(T a) { { divide(std::declval<T>(), std::declval<O>()) }; };
template<typename T, typename O> concept ComparableWith = requires(T a) { { eq(a, std::declval<O>()) } -> convertible_to<bool>; };

auto operator+(const OperandC auto& l, const OperandC auto& r) { return add(l, r); }
auto operator-(const ASatisfies(OperandC) auto& l, const ASatisfies(OperandC) auto& r) { return sub(l, r); }
template <typename O, MultipliableWith<O> LT> auto operator*(const LT& l, const O& r) { return multiply(l, r); }
template <typename O, DivisibleBy<O> LT> auto operator/(const LT& l, const O& r) { return divide(l, r); }
template <typename O> bool operator==(const ComparableWith<O> auto& l, const O& r) { return eq(l, r); }

};
