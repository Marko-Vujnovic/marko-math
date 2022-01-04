#define SQ(A) (#A[0])

/* #define concat(l,r) (l ## r) */
#define concat(l,r) (l r)

#define xyzTo012(letter) (SQ(letter) - 'x')

/* #define xyzToAbc(letter) ("abc"[xyzTo012(letter)]) */
#define xyzToAbcCase_x a
#define xyzToAbcCase_y b
#define xyzToAbcCase_z c
#define xyzToAbc(letter) xyzToAbcCase_##letter

#define XYZ(Type_, expr) \
float x(const Type_& vec) { return expr(x); } \
float y(const Type_& vec) { return expr(y); } \
float z(const Type_& vec) { return expr(z); }
