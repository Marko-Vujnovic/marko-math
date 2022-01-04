#include <gtest/gtest.h>

#include <memory> // unique_ptr

#define WITH_CONCEPTS 1

TEST(Basic, TestsWork) { ASSERT_TRUE(true); }

struct Mat4 { float elements[16]; };
float* into(const Mat4& from) { return (float*)&from; }

struct HeapMat { std::unique_ptr<std::array<float,16>> elements = std::make_unique<std::array<float,16>>(); };
template <typename... Args> HeapMat HeapMat_ctor1(Args... args) { return HeapMat{std::make_unique<std::array<float,16>>(std::array<float,16>{static_cast<float>(args)...})}; }
/* struct HeapMat { std::unique_ptr<std::array<float,16>> elements; HeapMat(): elements{std::make_unique<std::array<float,16>>()} {} }; */
float* into(const HeapMat& from) { return (float*)from.elements->data(); }

struct AltHeapMat { float* elements = new float[16]; ~AltHeapMat() { delete[] elements; } };
float* into(const AltHeapMat& from) { return (float*)from.elements; }

struct Angle { float inRad; };
float asRad(const Angle angle) { return angle.inRad; }
struct AltAngle { float inDeg; };
float asRad(const AltAngle angle) { return (angle.inDeg / 180.f) * 3.14f; }

#include "macros.hpp"

struct Vec3 { float x,y,z; };
/* #define e0(letter) (vec.letter) */
/* XYZ(Vec3, e0); */

struct AltVec3 { float comps[3]; };
#define e1(letter) (vec.comps[xyzTo012(letter)])
XYZ(AltVec3, e1); // Abusing macros for the sake of convenience. Expands to:
/* float x(const AltVec3& vec) { return vec.comps[0]; } */
/* float y(const AltVec3& vec) { return vec.comps[1]; } */
/* float z(const AltVec3& vec) { return vec.comps[2]; } */

struct AbcVec3 { float c,a,b; };
#define e2(letter) (vec.xyzToAbc(letter))
XYZ(AbcVec3, e2);

#include "Float/eq.hpp"
#include "Vec3/eq.hpp"
#include "Vec3/add.hpp"
#include "Vec3/sub.hpp"
#include "Vec3/multiply.hpp"
#include "Vec3/divide.hpp"
#include "Vec3/magnitude.hpp"
#include "Vec3/normalized.hpp"
#include "Vec3/distance.hpp"
#include "Vec3/dot.hpp"
#include "Vec3/cross.hpp"
#include "Vec3/insertInto.hpp"
#include "Matrix/new_Identity.hpp"
#include "Matrix/new_Scale.hpp"
#include "Matrix/new_Rotation.hpp"
#include "Matrix/new_Translation.hpp"
#include "Matrix/new_OrthographicProjection.hpp"
#include "Matrix/new_PerspectiveProjection.hpp"
#include "Matrix/multiply.hpp"
#include "Matrix/transpose.hpp"
#include "Matrix/invert.hpp"
#include "Matrix/insertInto.hpp"
#include "Matrix/eq.hpp"
#include "Matrix_Vec3/multiply.hpp"
#include "HasOperatorsC.hpp"
using namespace marko;

// Whether to memset to 0:
template <> struct marko::AboutType<Mat4> { static const bool allElemsAreZeroInit = true; };
template <> struct marko::AboutType<HeapMat> { static const bool allElemsAreZeroInit = true; };
template <> struct marko::AboutType<AltHeapMat> { static const bool allElemsAreZeroInit = false; };

namespace Matrix {

				// You can use this syntax if you have only one of each type:
				/* constexpr auto* new_Scale = MatrixT::new_Scale<Mat4, Vec3>; */
				// constexpr auto* new_Translation = MatrixT::new_Translation<Mat4, Vec3>;
				// constexpr auto* new_Rotation = makeARotationMatrix<Mat4, Angle, Vec3>;
				constexpr auto* new_PerspectiveProjection = MatrixT::new_PerspectiveProjection<Mat4, Angle>;
				constexpr auto* new_OrthographicProjection = MatrixT::new_OrthographicProjection<Mat4>;

				// If you have more than one of certain types, DON'T use this - deduction doesn't work:
				// template <typename AngleT, typename VecT> constexpr Mat4(*new_Rotation)(const AngleT, const VecT&) = &MatrixT::new_Rotation<Mat4, AngleT, VecT>;
				// template <typename AngleT, typename VecT> constexpr auto* new_Rotation = &MatrixT::new_Rotation<Mat4, AngleT, VecT>;
				
				// Use this if you have more than one of certain types - deduction works
				auto new_Rotation(const auto& a1, const auto& a2) { return MatrixT::new_Rotation<Mat4>(a1, a2); }
				template <typename MatT = Mat4> auto new_Translation(const auto& a1) { return MatrixT::new_Translation<MatT>(a1); }
				template <typename MatT = Mat4> auto new_Scale(const auto& a1) { return MatrixT::new_Scale<MatT>(a1); }
				template <typename MatT = Mat4> auto new_Identity() { return MatrixT::new_Identity<MatT>(); }};

void test(const auto& input, const auto& trans, const auto& expectedOutput, std::remove_const_t<std::remove_reference_t<decltype(input)>>(*op)(decltype(trans), decltype(input))) {
				ASSERT_TRUE(eq(op(trans, input), expectedOutput)); 
}
void testT(const auto& input, const auto& trans, const auto& expectedOutput) { test(input, trans, expectedOutput, marko::multiply<decltype(trans), decltype(input)>); }

#define PI 3.1415926535897932384626433832795f

TEST(Vec, ops) {
				{ Vec3 v1{10, 10, 10}; Vec3 v2{10, 10, 10}; ASSERT_TRUE(eq(v1, v2)); }
				{ Vec3 v1{10, 10, 10}; Vec3 v2{10, 10, 10}; ASSERT_TRUE(v1 == v2); }
				ASSERT_TRUE((AltVec3{10, 10, 10} + Vec3{4, 2, 5} == AbcVec3{15, 14, 12}));
				{ ASSERT_TRUE((AltVec3{10, 10, 10} - Vec3{4, 2, 5} == AbcVec3{5, 6, 8})); }
 				ASSERT_TRUE((Vec3{10, 10, 10} * Vec3{4, 2, 5} == Vec3{40, 20, 50})); 
 				ASSERT_TRUE((Vec3{10, 10, 10} / Vec3{2, 5, 1} == Vec3{5, 2, 10})); 
 				ASSERT_TRUE((Vec3{10, 10, 10} * 2.f == Vec3{20, 20, 20})); 
 				ASSERT_TRUE((Vec3{10, 10, 10} / 2.f == Vec3{5, 5, 5})); 
 				ASSERT_TRUE((Vec3{10, 10, 10} + 2.f == Vec3{12, 12, 12})); 
 				ASSERT_TRUE((Vec3{10, 10, 10} - 2.f == Vec3{8, 8, 8})); 
}

TEST(Matrix, identity) {
 				ASSERT_TRUE((Matrix::new_Identity() * Matrix::new_Identity() == Matrix::new_Identity())); 
 				ASSERT_TRUE((Mat4{5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8} * Matrix::new_Identity() == Mat4{5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8})); 
}

TEST(Matrix, invert) {
				std::cout << invert(Mat4{5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8}) << '\n';
				{ auto m = MatrixT::new_Translation<HeapMat>(Vec3{0, 33, 0}); ASSERT_TRUE((m * invert(m) == Matrix::new_Identity())); }
				{ auto m = MatrixT::new_Translation<HeapMat>(Vec3{0, 33, 0}); ASSERT_TRUE(((m * Vec3{10, 10, 10}) * invert(m) == AltVec3{10, 10, 10})); }
}

TEST(Matrix, transpose) {
				std::cout << transpose(Mat4{5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8}) << '\n';
 				ASSERT_TRUE((transpose(Mat4{
								5, 7, 9, 10, 
								2, 3, 3, 8, 
								8, 10, 2, 3, 
								3, 3, 4, 8}) == HeapMat_ctor1(
				5, 2, 8, 3,
				7, 3, 10, 3,
				9, 3, 2, 4,
				10, 8, 3, 8
				))); 
}

TEST(Matrix, mul) {
 				ASSERT_TRUE((Mat4{5, 7, 9, 10, 2, 3, 3, 8, 8, 10, 2, 3, 3, 3, 4, 8} * Mat4{3, 10, 12, 18, 12, 1, 4, 9, 9, 10, 12, 2, 3, 12, 4, 10} == HeapMat_ctor1(210, 267, 236, 271, 93, 149, 104, 149, 171, 146, 172, 268, 105, 169, 128, 169))); 
}

TEST(Vec, magnitude) {
 				ASSERT_TRUE((eq(magnitude(Vec3{2, 2, 2}), sqrt(12)))); 
}

TEST(Vec, normalize) {
				std::cout << normalized(Vec3{4, 2, 1}) << '\n';
 				ASSERT_TRUE((eq(magnitude(normalized(Vec3{4, 2, 1})), 1.f))); 
}

TEST(Vec, distance) {
 				ASSERT_TRUE((eq(distance(Vec3{2, 2, 0}, Vec3{4, 4, 0}), 2.f*sqrt(2.f)))); 
}
TEST(Vec, dot) {
				ASSERT_TRUE((eq(dot(Vec3{2, 3, 4}, Vec3{4, 5, 3}), 2*4+3*5+4*3))); 
}
TEST(Vec, cross) {
     ASSERT_TRUE((eq(cross(Vec3{2, 3, 4}, Vec3{4, 5, 3}), Vec3{3*3-4*5, 4*4-2*3, 2*5-3*4}))); 
}

TEST(Matrix, translation) {
				// Bears a resemblance to a named ctor or a static factory method
				{ auto m = Matrix::new_Translation(Vec3{0, 33, 0}); auto lhs = m * Vec3{10, 10, 10}; std::cout << m << '\n' << lhs << '\n'; ASSERT_TRUE((m * Vec3{10, 10, 10} == Vec3{10, 43, 10})); }
				{ auto m = MatrixT::new_Translation<HeapMat>(Vec3{0, 33, 0}); ASSERT_TRUE((m * Vec3{10, 10, 10} == AltVec3{10, 43, 10})); }
				{ auto m = MatrixT::new_Translation<AltHeapMat>(Vec3{0, 33, 0}); ASSERT_TRUE((m * Vec3{10, 10, 10} == AltVec3{10, 43, 10})); }
}

TEST(Matrix, scale) { { auto m = Matrix::new_Scale(Vec3{2, 2, 2}); testT(AltVec3{10, 10, 10}, m, AbcVec3{20, 20, 20}); } }

TEST(Matrix, projections) {
    { auto m = Matrix::new_PerspectiveProjection(Angle{PI/3.f}, 16.0f / 9.0f, 0.1f, 1000.0f); }
    { auto m = Matrix::new_OrthographicProjection(-10, 10, -10, 10, -10, 20); }
}

TEST(Matrix, rotation) {
    // Can mix and match all types willy-nilly!
    // Types are interchangeable if they fulfill the same concept. This is similar to Rust’s traits
    { auto m = Matrix::new_Rotation(Angle{-PI/2.f}, AltVec3{0, 0, 1}); testT(Vec3{0, 1, 0}, m, Vec3{1, 0, 0}); }
    { auto m = Matrix::new_Rotation(-PI/2.f, Vec3{0, 0, 1}); testT(Vec3{0, 1, 0}, m, Vec3{1, 0, 0}); }
    { auto m = Matrix::new_Rotation(AltAngle{-90.f}, AbcVec3{1, 0, 0}); testT(Vec3{0, 1, 0}, m, Vec3{1, 0, 0}); }
}

TEST(Matrix, combiningTransf) {
				{
        auto t = Matrix::new_Translation<Mat4>(Vec3{0, 33, 0}); auto s = Matrix::new_Scale<Mat4>(Vec3{2, 2, 2}); auto r = Matrix::new_Rotation(Angle{-PI/2.f}, AltVec3{0, 0, 1});
        std::cout << "t, s, t*s, s*t" << '\n';
        std::cout << t << '\n';
        std::cout << s << '\n';
        // "Usually it is t*r*s", which means "first scale, then rotation and lastly translation"
        // "However, if you want to rotate an object around a certain point, then it is scale, point translation, rotation and lastly object translation."
        auto ts = (t * s);
        auto st = (s*t);
        std::cout << ts << '\n';
        std::cout << st << '\n';
        /* ASSERT_TRUE((t*s * Vec3{10, 10, 10} == AltVec3{20, 53, 20})); */
        ASSERT_TRUE((t*(s * Vec3{10, 10, 10}) == AltVec3{20, 53, 20}));
        ASSERT_TRUE((s*t * Vec3{10, 10, 10} == AltVec3{20, 86, 20}));
        /* ASSERT_TRUE(((t * s) * Vec3{10, 10, 10} == AltVec3{20, 86, 20})); */
        /* ASSERT_TRUE(((s*t) * Vec3{10, 10, 10} == AltVec3{20, 86, 20})); */
        /* ASSERT_TRUE((s * t * Vec3{10, 10, 10} == AltVec3{20, 86, 20})); */
        /* ASSERT_TRUE((t * r * s * Vec3{0, 10, 0} != AltVec3{86, 0, 0})); */
        /* ASSERT_TRUE(((s*r*t) * Vec3{0, 10, 0} == AltVec3{86, 0, 0})); */
        /* ASSERT_TRUE(((s*r*t) * Vec3{0, 10, 0} == AltVec3{53, 0, 0})); */
        /* ASSERT_TRUE(((s*(r*(t * Vec3{0, 10, 0}))) == AltVec3{86, 0, 0})); */
        ASSERT_TRUE((s * Vec3{0, 10, 0} == AltVec3{0, 20, 0}));
        std::cout << (r*(s * Vec3{0, 10, 0})) << '\n';
        ASSERT_TRUE(((r*(s * Vec3{0, 10, 0})) == AltVec3{20, 0, 0}));
        
        ASSERT_TRUE(((t*(r*(s * Vec3{0, 10, 0}))) == AltVec3{20, 33, 0}));
        ASSERT_TRUE(((Vec3{0, 10, 0} * s*r*t) == AltVec3{20, 33, 0}));

        ASSERT_TRUE((((t*r*s) * Vec3{0, 10, 0}) != AltVec3{20, 33, 0}));
        ASSERT_TRUE(((Vec3{0, 10, 0} * (t*r*s)) != AltVec3{20, 33, 0}));
        ASSERT_TRUE(((Vec3{0, 10, 0} * t*r*s) != AltVec3{20, 33, 0}));
        ASSERT_TRUE((((t*(r*s)) * Vec3{0, 10, 0}) != AltVec3{20, 33, 0}));
        ASSERT_TRUE((((s*r*t) * Vec3{0, 10, 0}) != AltVec3{20, 33, 0}));
        ASSERT_TRUE((((s*(r*t)) * Vec3{0, 10, 0}) != AltVec3{20, 33, 0}));
        /* ASSERT_TRUE((s*t*r * Vec3{0, 10, 0} != AltVec3{86, 0, 0})); */
        /* ASSERT_TRUE((r*s*t * Vec3{0, 10, 0} == AltVec3{86, 0, 0})); */
        /* ASSERT_TRUE((m2 * m1 * Vec3{10, 10, 10} == AltVec3{20, 86, 20})); */
        /* ASSERT_TRUE(((m2 * m1) * Vec3{10, 10, 10} == Vec3{20, 53, 20}));  */
    }
}

TEST(Matrix, cApi) {
				// C way. No templates neccessary. The claim that a certain small subset of generic programming can be done just fine without templates has merit to it. But it's less convenient and requires peaking through abstractions at all call sites, potentially numerous times in the codebase.
				{ Mat4 m{}; MatrixT::new_Rotation(-PI/2.f, 0, 0, 1, (float*)&m); testT(Vec3{0, 1, 0}, m, Vec3{1, 0, 0});}
				{ Mat4 m{}; MatrixT::new_Translation(0, 33, 0, (float*)&m); ASSERT_TRUE((m * Vec3{10, 10, 10} == AltVec3{10, 43, 10}));}
				// A combination of the two approaches is used internally in this project resulting in templates whose actual implementation code doesn't need to be distributed to the end-user of the library in source form, which is an attractive proposition for closed-source libraries.
}
