#pragma once
#include <cstdint> // uint16_t
#define WITH_CONCEPTS 1

namespace std { template<class From, class To> struct is_convertible; }
namespace marko {

/* #ifdef WITH_CONCEPTS */
    #define ASatisfies(c) c
    #define TSatisfies(c) c 
    
    /* #include <concepts> */
    /* #include <type_traits> */
    template <typename From, typename To> concept convertible_to = std::is_convertible<From, To>::value;
    /* template <typename From, typename To> concept SameAsC = std::is_same_v<From, To>; */
				
/* #else */
/* 				#define TSatisfies(c) typename */
/* 				#define ASatisfies(c) */
/* #endif */

// Angle trait:
				inline float asRad(float a) { return a; }
				template<typename T> concept HasAsRadC = requires(T a) { { asRad(a) } -> convertible_to<float>; };
				template<typename T> concept AngleC = HasAsRadC<T>;
// Vec trait:
    template<typename T> concept HasXyzFieldsC = requires(T a) { 
        { a.x } -> convertible_to<float>; 
        { a.y } -> convertible_to<float>; 
        { a.z } -> convertible_to<float>; 
    };
	 			float x(const ASatisfies(HasXyzFieldsC) auto& vec) { return vec.x; }   
				float y(const ASatisfies(HasXyzFieldsC) auto& vec) { return vec.y; }
				float z(const ASatisfies(HasXyzFieldsC) auto& vec) { return vec.z; }
    template<typename T> concept HasXyzGFuncsC = requires(T a) { 
        { x(a) } -> convertible_to<float>; 
        { y(a) } -> convertible_to<float>; 
        { z(a) } -> convertible_to<float>; 
    };


/* #ifdef WITH_CONCEPTS */
				template<typename T, typename ToT> concept IntoC = requires(T a) { { into(a) }->convertible_to<ToT>; };
				template<typename T> concept MatrixC = IntoC<T, float*>;
				float at(const ASatisfies(MatrixC) auto& obj, uint16_t x, uint16_t y) { auto *fl = into(obj); return fl[x + 4*y]; }
				void at(const ASatisfies(MatrixC) auto& obj, uint16_t x, uint16_t y, float newVal) { auto *fl = into(obj); fl[x + 4*y] = newVal; }
/* #endif */
	
// Sane defaults, overload if neccessary
    /* float* into(const auto& matrix) { return (float*)&matrix; } */
    /* float asRad(const auto angle) { return (float&)angle; } */
		/* static auto into = [](const auto& matrix) { return (float*)&matrix; }; */
// Example - how to overload:
    // float* into(const Mat4& from) { return (float*)&from; }
    // float asRad(const Angle angle) { return (angle.inDeg / 180.f) * 3.14f; }


#define FORCE_INLINE __attribute__((always_inline))

template <typename CollectionT> struct AboutType { static const bool allElemsAreZeroInit = false; };
};

