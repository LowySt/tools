#ifndef LS_MATHS_H
#define LS_MATHS_H

#include "lsCRT.h"

#define PI_32 3.1415926f
#define PI_64 3.141592653589793

#define LS_EPSILON 0.00001f

#define ls_min(a, b) (a < b ? a : b)
#define ls_max(a, b) (a > b ? a : b)

/////////////
// GENERAL //
/////////////

extern "C"
{
    s32 ls_floor(f64 v);
    s32 ls_ceil(f64 v);
    s32 ls_abs(s32 x);
    f64 ls_fabs(f64 x);
    s64 ls_e10(s32 x);
    u64 ls_powui(u64 v, u32 exp);
    s64 ls_powi(s64 v, u32 exp);
    f64 ls_powf(f64 v, s32 exp);
    f64 ls_fmod(f64 v, f64 w);
    s64 ls_truncate(f64 x);
    f64 ls_truncEpsilon(f64 x);
    f32 ls_rad(f32 x);
    f64 ls_sqrt(f64 x);
    f64 ls_cbrt(f64 x);
    u32 ls_gcd(u32 a, u32 b);
    b32 ls_isPrime(u32 a);
    
    b32 ls_isF64Normal(f64 v);
    
    //NOTE: This only has 12 digits of precision!
    f32 ls_reciprocal(f32 x);
    
    f64 ls_sin(f64 rad);
    f64 ls_asin(f64 x);
    f64 ls_cos(f64 rad);
    f64 ls_acos(f64 x);
    f64 ls_tan(f64 rad);
    f64 ls_atan(f64 x);
    f64 ls_atan2(f64 a, f64 b);
};


/////////////
// VECTORS //
/////////////

struct v2 { f32 x, y; };
struct v3 { f32 x, y, z; };
struct v4 { f32 x, y, z, w; };

struct v2i { s64 x, y; };
struct v3i { s64 x, y, z; };
struct v4i { s64 x, y, z, w; };

extern "C"
{
	b32 isZero(f32 v);
	b32 isVal(f32 x, f32 val);
    
	v2  vec2(f32 x, f32 y);
	v3  vec3(f32 x, f32 y, f32 z);
	v4  vec4(f32 x, f32 y, f32 z, f32 w);
	v2i vec2i(s32 x, s32 y);
	v3i vec3i(s32 x, s32 y, s32 z);
	v4i vec4i(s32 x, s32 y, s32 z, s32 w);
    
	v2 V2(v3 v); v3 V3(v4 v); v4 V4(v3 v);
    
	f32 LengthV2(v2 v); f32 LengthV3(v3 v); f32 LengthV4(v4 v);
    f32 LengthV2i(v2i v); f32 LengthV3i(v3i v); f32 LengthV4i(v4i v);
    
	v2 NormalizeV2(v2 v); v3 NormalizeV3(v3 v); v4 NormalizeV4(v4 v);
    v2 NormalizeV2i(v2i v); v3 NormalizeV3i(v3i v); v4 NormalizeV4i(v4i v);
    
    v4i ls_v4iSubs64(v4i v, s64 s);
    
    v2i operator*(v2i a, f32 v);
    
    b32 ls_areV2iEqual(v2i v, v2i w);
    
#if 0
    b32 operator==(v2 v, v2 w); b32 operator==(v3 v, v3 w); b32 operator==(v4 v, v4 w);
    b32 operator!=(v2 v, v2 w); b32 operator!=(v3 v, v3 w); b32 operator!=(v4 v, v4 w);
    
    v2 operator+(v2 v, v2 w); v3 operator+(v3 v, v3 w); v4 operator+(v4 v, v4 w);
    v2i operator+(v2i v, v2i w); v3i operator+(v3i v, v3i w); v4i operator+(v4i v, v4i w);
    
    v2 operator-(v2 v, v2 w); v3 operator-(v3 v, v3 w); v4 operator-(v4 v, v4 w);
    v2 operator-(v2 v); v3 operator-(v3 v); v4 operator-(v4 v);
    v2i operator-(v2i v, v2i w); v3i operator-(v3i v, v3i w); v4i operator-(v4i v, v4i w);
    v2i operator-(v2i v); v3i operator-(v3i v); v4i operator-(v4i v);
    
    v2 operator*(v2 w, f32 value); v3 operator*(v3 w, f32 value); v4 operator*(v4 w, f32 value);
    f32 operator*(v2 v, v2 w); f32 operator*(v3 v, v3 w); f32 operator*(v4 v, v4 w);
    
    v3 operator^(v3 v, v3 w);
#endif
};

////////////
// MATRIX //
////////////

union Mat2
{
	struct { v2 row1, row2; };
	f32 values[2][2];
};

union Mat3
{
	struct { v3 row1, row2, row3; };
    f32 values[3][3];
};

union Mat4
{
	struct { v4 row1, row2, row3, row4; };
	f32 values[4][4];
};

extern "C"
{
	Mat2 Identity2();
	Mat3 Identity3();
	Mat4 Identity4();
    
	f32 Determinant2(Mat2 m);
	f32 Determinant3(Mat3 m);
	f32 Determinant4(Mat4 m);
    
	Mat2 MatOfMinors2(Mat2 m);
	Mat3 MatOfMinors3(Mat3 m);
	Mat4 MatOfMinors4(Mat4 m);
    
	Mat2 Inverse2(Mat2 m);
	Mat3 Inverse3(Mat3 m);
	Mat4 Inverse4(Mat4 m);
    
	Mat2 Transpose2(Mat2 m);
	Mat3 Transpose3(Mat3 m);
	Mat4 Transpose4(Mat4 m);
    
	Mat3 NormalMatrix(Mat4 m);
    
	Mat2 UniformScale2(f32 factor);
	Mat3 UniformScale3(f32 factor);
	Mat4 UniformScale4(f32 factor);
    
	Mat2 Scale2(v2 v);
	Mat3 Scale3(v3 v);
	Mat4 Scale4(v4 v);
    
	Mat4 Translate(v4 v);
    
	Mat4 RotateX(f32 Angle);
	Mat4 RotateY(f32 Angle);
	Mat4 RotateZ(f32 Angle);
    
	Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top);
	Mat4 PerspectiveProjEx(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom);
	Mat4 PerspectiveProjFOV(f32 FOV, f32 aspectRatio, f32 near, f32 far);
    
	Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top);
	Mat4 OrthoProjEx(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom);
    
    Mat2 ls_mat2Mulf32(Mat2 m, f32 value);
    
    Mat3 ls_mat3Mulf32(Mat3 m, f32 value);
    
    Mat4 ls_mat4Mulf32(Mat4 m, f32 value);
#if 0
    Mat2 operator+(Mat2 m, f32 value); Mat3 operator+(Mat3 m, f32 value); Mat4 operator+(Mat4 m, f32 value);
    Mat2 operator+(Mat2 n, Mat2 m); Mat3 operator+(Mat3 n, Mat3 m); Mat4 operator+(Mat4 n, Mat4 m);
    
    Mat2 operator-(Mat2 m, f32 value); Mat3 operator-(Mat3 m, f32 value); Mat4 operator-(Mat4 m, f32 value);
    Mat2 operator-(Mat2 n, Mat2 m); Mat3 operator-(Mat3 n, Mat3 m); Mat4 operator-(Mat4 n, Mat4 m);
    
    Mat2 operator*(Mat2 m, f32 value); Mat3 operator*(Mat3 m, f32 value); Mat4 operator*(Mat4 m, f32 value);
    Mat2 operator*(Mat2 n, Mat2 m); Mat3 operator*(Mat3 n, Mat3 m); Mat4 operator*(Mat4 n, Mat4 m);
    
    v2 operator*(Mat2 m, v2 v); v3 operator*(Mat3 m, v3 v); v4 operator*(Mat4 m, v4 v);
#endif
};

#endif //LS_MATH_IMPLEMENTATION

#ifdef LS_MATH_IMPLEMENTATION

/////////////
// GENERAL //
/////////////

s32 ls_floor(f64 v)
{ return (s32)v; }

s32 ls_ceil(f64 v)
{ return (s32)(v+1); };

s32 ls_abs(s32 x)
{
    return (x < 0) ? x*(-1) : x;
}

f64 ls_fabs(f64 x)
{
    return (x < 0.0f) ? x*(-1.0f) : x;
}

s64 ls_e10(s32 x)
{
    s64 Result = 1;
    for (int i = 0; i < x; i++) { Result *= 10; }
    return Result;
}

u64 ls_powui(u64 v, u32 exp)
{
    u64 Result = 1;
    while (exp)
    {
        if (exp & 1)
        { Result *= v; }
        
        exp >>= 1;
        v *= v;
    }
    return Result;
}

s64 ls_powi(s64 v, u32 exp)
{
    s64 Result = 1;
    while (exp)
    {
        if (exp & 1)
        { Result *= v; }
        
        exp >>= 1;
        v *= v;
    }
    return Result;
}

f64 ls_powf(f64 v, s32 exp)
{
    f64 Result = 1.0f;
    while (exp)
    {
        Result *= v;
        exp--;
    }
    
    return Result;
}

f64 ls_fmod(f64 v, f64 w)
{
    if(w == 0) { return 0; }
    
    return v - ls_floor(v/w)*w;
}

s64 ls_truncate(f64 x)
{
    return s64(x + 0.5f);
}

f64 ls_truncEpsilon(f64 x)
{
    u64 value = (u64)x;
    
    if(((f64)(value + 1) - x) < 0.005f)
    { return f64(value + 1); }
    
    return x;
}

f32 ls_rad(f32 x)
{
    return ((x*PI_32) / 180.0f);
}

#ifdef __GNUG__
f64 ls_sqrt(f64 x)
{
    return 0.0f;
}
#else
f64 ls_sqrt(f64 x)
{
#ifdef LS_PLAT_WINDOWS
    __m128d Result = _mm_set_pd1(x);
    Result = _mm_invsqrt_pd(Result);
    
    //NOTE: Not using reciprocal builtin because
    // I don't know how 12 bits of precision are here...
    return ((f64)1.0f / Result.m128d_f64[0]);
#endif
    
#ifdef LS_PLAT_LINUX
    f32 Result = __builtin_sqrtf(x);
    return Result;
#endif
}
#endif

f64 ls_cbrt(f64 x)
{
#ifdef LS_PLAT_WINDOWS
    __m128d Result = _mm_set_pd1(x);
    Result = _mm_cbrt_pd(Result);
    
    return Result.m128d_f64[0];
#endif
    
#ifdef LS_PLAT_LINUX
    return 0.0f;
#endif
}

#ifdef __GNUG__
f32 ls_reciprocal(f32 x)
{
    return 0.0f;
}
#else
//NOTE: This only has 12 digits of precision!
f32 ls_reciprocal(f32 x)
{
#ifdef LS_PLAT_WINDOWS
    __m128 Result = _mm_set_ps1(x);
    Result = _mm_rcp_ps(Result);
    
    return Result.m128_f32[0];
#endif
    
#ifdef LS_PLAT_LINUX
    f32 Result = UNKNOWN_BUILTIN(x);
    return Result;
#endif
}
#endif

u32 ls_gcd(u32 a, u32 b) //NOTE: Stein's Algorithm
{
    s32 shift;
    
    /* GCD(0,b) == b; GCD(a,0) == a, GCD(0,0) == 0 */
    if(a == 0) { return b; }
    if(b == 0) { return a; }
    
    /* Let shift := lg K, where K is the greatest power of 2
    dividing both a and b. */
    for (shift = 0; ((a | b) & 1) == 0; ++shift)
    {
        a >>= 1;
        b >>= 1;
    }
    
    while ((a & 1) == 0)
    { a >>= 1; }
    
    /* From here on, a is always odd. */
    do {
        /* remove all factors of 2 in b -- they are not common */
        /*   note: b is not zero, so while will terminate */
        while ((b & 1) == 0)  /* Loop X */
        { b >>= 1; }
        
        /* Now a and b are both odd. Swap if necessary so a <= b,
        then set b = b - a (which is even). For bignums, the
        swapping is just pointer movement, and the subtraction
        can be done in-place. */
        if (a > b) {
            u32 t = b; b = a; a = t; // Swap a and b.
        }
        
        b = b - a; // Here b >= a.
    } while (b != 0);
    
    /* restore common factors of 2 */
    return (a << shift);
}

b32 ls_isPrime(u32 a)
{
    //TODO: Pretty slow. For limited range should precompute a table.
    //NOTE: Table Lookup seems instant in Release (For a trivial example
    //the compiler has probably found everything constant and just put the values
    //instead of having it be computed)
    //BUT Table lookup is extremely slow in Debug compared to this Primality test.
    //A perfect lookup table would be one with
    //    b8 isPrime[] = {FALSE, TRUE, TRUE, ... };
    //But that would be much bigger and problematic.
    //1MB just to lookup 75k primes... For Now I prefer This Algo.
    
    //NOTE: Simple (6k - 1) (6k + 1) prime test
    //
    // All primes (except 2 and 3) are of the form 6k - 1 or 6k + 1
    // So we look for those divisors.
    
    if(a == 1) { return FALSE; }
    if(a == 2 || a == 3) { return TRUE; }
    if((a % 2 == 0) || (a % 3 == 0)) { return FALSE; }
    
    u32 i = 5, w = 2;
    
    while((i*i) <= a)
    {
        if(a % i == 0) { return FALSE; }
        
        i += w;
        w = 6 - w;
    }
    
    return TRUE;
}

b32 ls_isF64Normal(f64 v)
{
    u64 vBit = *((u64 *)(&v));
    
    u32 exp = (u32)((vBit >> 52) & 0x07FF);
    if(exp == 0x0 || exp == 0x7FF) { return FALSE; }
    
    return TRUE;
}


f64 ls_sin(f64 radians)
{
    __m128d rad128 = _mm_set_pd1(radians);
    __m128d sinVal = _mm_sin_pd(rad128);
    
    return sinVal.m128d_f64[0];
}

f64 ls_asin(f64 x)
{
    __m128d xVal = _mm_set_pd1(x);
    __m128d asinVal = _mm_asin_pd(xVal);
    
    return asinVal.m128d_f64[0];
}

f64 ls_cos(f64 rad)
{
    __m128d rad128 = _mm_set_pd1(rad);
    __m128d cosVal = _mm_cos_pd(rad128);
    
    return cosVal.m128d_f64[0];
}

f64 ls_acos(f64 x)
{
    __m128d xVal = _mm_set_pd1(x);
    __m128d acosVal = _mm_acos_pd(xVal);
    
    return acosVal.m128d_f64[0];
}

f64 ls_tan(f64 rad)
{
    __m128d rad128 = _mm_set_pd1(rad);
    __m128d tanVal = _mm_tan_pd(rad128);
    
    return tanVal.m128d_f64[0];
}

f64 ls_atan(f64 x)
{
    __m128d xVal = _mm_set_pd1(x);
    __m128d atanVal = _mm_atan_pd(xVal);
    
    return atanVal.m128d_f64[0];
}

f64 ls_atan2(f64 a, f64 b)
{
    __m128d aVal = _mm_set_pd1(a);
    __m128d bVal = _mm_set_pd1(b);
    __m128d atanVal = _mm_atan2_pd(aVal, bVal);
    
    return atanVal.m128d_f64[0];
}

/////////////
// VECTORS //
/////////////

b32 isZero(f32 v)
{
	if (ls_fabs(v) < LS_EPSILON) { return TRUE; }
	return FALSE;
}

b32 isVal(f32 x, f32 val)
{
	if (ls_fabs(x - val) < LS_EPSILON) { return TRUE; }
	return FALSE;
}

v2 vec2(f32 x, f32 y)
{
	v2 Result = { x, y };
	return Result;
}

v3 vec3(f32 x, f32 y, f32 z)
{
	v3 Result = { x, y, z };
	return Result;
}

v4 vec4(f32 x, f32 y, f32 z, f32 w)
{
	v4 Result = { x, y, z, w };
	return Result;
}

v2i vec2(s32 x, s32 y)
{
	v2i Result = { x, y };
	return Result;
}

v3i vec3(s32 x, s32 y, s32 z)
{
	v3i Result = { x, y, z };
	return Result;
}

v4i vec4(s32 x, s32 y, s32 z, s32 w)
{
	v4i Result = { x, y, z, w };
	return Result;
}

v2 V2(v3 v)
{
	v2 Result = { v.x, v.y };
	return Result;
}

v3 V3(v4 v)
{
	v3 Result = { v.x, v.y, v.z };
	return Result;
}

v4 V4(v3 v)
{
	v4 Result = { v.x, v.y, v.z, 1.0f };
	return Result;
}

///////////////////////////////////////////
// VECTOR OPERATORS
///////////////////////////////////////////

f32 LengthV2(v2 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y));
	return Result;
}

f32 LengthV3(v3 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
	return Result;
}

f32 LengthV4(v4 v)
{
	f32 Result = ls_sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
	return Result;
}

f32 LengthV2i(v2i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y));
	return Result;
}

f32 LengthV3i(v3i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y) + (f32)(v.z*v.z));
	return Result;
}

f32 LengthV4i(v4i v)
{
	f32 Result = ls_sqrt((f32)(v.x*v.x) + (f32)(v.y*v.y) + (f32)(v.z*v.z) + (f32)(v.w*v.w));
	return Result;
}

v2 NormalizeV2(v2 v)
{
	f32 L = LengthV2(v);
	v2 Result = { v.x / L, v.y / L };
    
	return Result;
}

v3 NormalizeV3(v3 v)
{
	f32 L = LengthV3(v);
	v3 Result = { v.x / L, v.y / L, v.z / L };
    
	return Result;
}

v4 NormalizeV4(v4 v)
{
	f32 L = LengthV4(v);
	v4 Result = { v.x / L, v.y / L, v.z / L, v.w / L };
    
	return Result;
}

v2 NormalizeV2i(v2i v)
{
	f32 L = LengthV2i(v);
	v2 Result = { v.x / L, v.y / L };
    
	return Result;
}

v3 NormalizeV3i(v3i v)
{
	f32 L = LengthV3i(v);
	v3 Result = { v.x / L, v.y / L, v.z / L };
    
	return Result;
}

v4 NormalizeV4i(v4i v)
{
	f32 L = LengthV4i(v);
	v4 Result = { v.x / L, v.y / L, v.z / L, v.w / L };
    
	return Result;
}

v4i ls_v4iSubs64(v4i v, s64 s)
{
    v4i Result = { v.x - s, v.y - s, v.z - s, v.w - s };
    return Result;
}

v2i operator*(v2i a, f32 v)
{
    v2i result = { (s32)((f32)a.x * v), (s32)((f32)a.y*v) };
    return result;
}

b32 ls_areV2iEqual(v2i v, v2i w)
{
    if((w.x == v.x) && (w.y == v.y)) { return TRUE; }
    return FALSE;
}

#if 0
b32 operator==(v2 v, v2 w)
{
    if((w.x == v.x) && (w.y == v.y)) { return TRUE; }
    return FALSE;
}

b32 operator!=(v2 v, v2 w) { return !(w == v); }

b32 operator==(v3 v, v3 w)
{
    if((w.x == v.x) && (w.y == v.y) && (w.z == w.z))
    { return TRUE; }
    return FALSE;
}

b32 operator!=(v3 v, v3 w) { return !(w == v); }

b32 operator==(v4 v, v4 w)
{
    if((w.x == v.x) && (w.y == v.y) && (w.z == v.z) && (w.w == v.w))
    { return TRUE; }
    return FALSE;
}

b32 operator!=(v4 v, v4 w) { return !(w == v); }


v2 operator+(v2 v, v2 w)
{
	v2 Result = { w.x + v.x, w.y + v.y };
	return Result;
}

v3 operator+(v3 v, v3 w)
{
	v3 Result = { w.x + v.x, w.y + v.y, w.z + v.z };
	return Result;
}

v4 operator+(v4 v, v4 w)
{
	v4 Result = { w.x + v.x, w.y + v.y, w.z + v.z, w.w + v.w };
	return Result;
}

v2i operator+(v2i v, v2i w)
{
	v2i Result = { w.x + v.x, w.y + v.y };
	return Result;
}

v3i operator+(v3i v, v3i w)
{
	v3i Result = { w.x + v.x, w.y + v.y, w.z + v.z };
	return Result;
}

v4i operator+(v4i v, v4i w)
{
	v4i Result = { w.x + v.x, w.y + v.y, w.z + v.z, w.w + v.w };
	return Result;
}

v2 operator-(v2 v, v2 w)
{
	v2 Result = { w.x - v.x, w.y - v.y };
	return Result;
}

v2 operator-(v2 v)
{
    v2 Result = { -v.x, -v.y };
    return Result;
}

v3 operator-(v3 v, v3 w)
{
	v3 Result = { w.x - v.x, w.y - v.y, w.z - v.z };
	return Result;
}

v3 operator-(v3 v)
{
    v2 Result = { -v.x, -v.y, -v.z };
    return Result;
}

v4 operator-(v4 v, v4 w)
{
	v4 Result = { w.x - v.x, w.y - v.y, w.z - v.z, w.w - v.w };
	return Result;
}

v4 operator-(v4 v)
{
	v4 Result = { -v.x, -v.y, -v.z, -v.w };
	return Result;
}

v2i operator-(v2i v, v2i w)
{
	v2i Result = { w.x - v.x, w.y - v.y };
	return Result;
}

v2i operator-(v2i v)
{
	v2i Result = { -v.x, -v.y };
	return Result;
}

v3i operator-(v3i v, v3i w)
{
	v3i Result = { w.x - v.x, w.y - v.y, w.z - v.z };
	return Result;
}

v3i operator-(v3i v)
{
	v3i Result = { -v.x, -v.y, -v.z };
	return Result;
}

v4i operator-(v4i v, v4i w)
{
	v4i Result = { w.x - v.x, w.y - v.y, w.z - v.z, w.w - v.w };
	return Result;
}

v4i operator-(v4i v)
{
	v4i Result = { -v.x, -v.y, -v.z, -v.w };
	return Result;
}

v2 operator*(v2 w, f32 value)
{
	v2 Result = { w.x * value, w.y * value };
	return Result;
}

v3 operator*(f32 value)
{
	v3 Result = { w.x * value, w.y * value, w.z * value };
	return Result;
}

v4 operator*(f32 value)
{
	v4 Result = { w.x * value, w.y * value, w.z * value, w.w * value };
	return Result;
}

f32 operator*(v2 v, v2 w)
{
	return (w.x * v.x) + (w.y * v.y);
}

f32 operator*(v3 v, v3 w)
{
	return (w.x * v.x) + (w.y * v.y) + (w.z * v.z);
}

f32 operator*(v4 v)
{
	return (w.x * v.x) + (w.y * v.y) + (w.z * v.z) + (w.w * v.w);
}

v3 operator^(v3 v, v3 w)
{
	v3 Result = {};
	Result.x = (w.y * v.z) - (w.z * v.y);
	Result.y = (w.z * v.x) - (w.x * v.z);
	Result.z = (w.x * v.y) - (w.y * v.x);
    
	return Result;
}
#endif
///////////////////////////////////////////
// MATRIX OPERATIONS
///////////////////////////////////////////

Mat2 ls_mat2Mulf32(Mat2 m, f32 value)
{
	Mat2 Result =
	{
		m.values[0][0] * value, m.values[0][1] * value,
		m.values[1][0] * value, m.values[1][1] * value
	};
    
	return Result;
}

Mat3 ls_mat3Mulf32(Mat3 m, f32 value)
{
	Mat3 Result =
	{
		m.values[0][0] * value, m.values[0][1] * value, m.values[0][2] * value,
		m.values[1][0] * value, m.values[1][1] * value, m.values[1][2] * value,
		m.values[2][0] * value, m.values[2][1] * value, m.values[2][2] * value
	};
    
	return Result;
}

Mat4 ls_mat4Mulf32(Mat4 m, f32 value)
{
	Mat4 Result =
	{
		m.values[0][0] * value, m.values[0][1] * value, m.values[0][2] * value, m.values[0][3] * value,
		m.values[1][0] * value, m.values[1][1] * value, m.values[1][2] * value, m.values[1][3] * value,
		m.values[2][0] * value, m.values[2][1] * value, m.values[2][2] * value, m.values[2][3] * value,
		m.values[3][0] * value, m.values[3][1] * value, m.values[3][2] * value, m.values[3][3] * value
	};
    
	return Result;
}

#if 0

Mat2 operator+(Mat2 m, f32 value)
{
	Mat2 Result =
	{
		m.values[0][0] + value,
		m.values[0][1] + value,
		m.values[1][0] + value,
		m.values[1][1] + value
	};
    
	return Result;
}

Mat2 operator+(Mat2 n, Mat2 m)
{
	Mat2 Result =
	{
		n.values[0][0] + m.values[0][0],
		n.values[0][1] + m.values[0][1],
		n.values[1][0] + m.values[1][0],
		n.values[1][1] + m.values[1][1]
	};
    
	return Result;
}

Mat3 operator+(Mat3 m, f32 value)
{
	Mat3 Result =
	{
		m.values[0][0] + value,
		m.values[0][1] + value,
		m.values[0][2] + value,
		m.values[1][0] + value,
		m.values[1][1] + value,
		m.values[1][2] + value,
		m.values[2][0] + value,
		m.values[2][1] + value,
		m.values[2][2] + value
	};
    
	return Result;
}

Mat3 operator+(Mat3 m, Mat3 n)
{
	Mat3 Result =
	{
		m.values[0][0] + n.values[0][0],
		m.values[0][1] + n.values[0][1],
		m.values[0][2] + n.values[0][2],
		m.values[1][0] + n.values[1][0],
		m.values[1][1] + n.values[1][1],
		m.values[1][2] + n.values[1][2],
		m.values[2][0] + n.values[2][0],
		m.values[2][1] + n.values[2][1],
		m.values[2][2] + n.values[2][2]
	};
    
	return Result;
}

Mat4 operator+(Mat4 m, f32 value)
{
	Mat4 Result =
	{
		m.values[0][0] + value,
		m.values[0][1] + value,
		m.values[0][2] + value,
		m.values[0][3] + value,
		m.values[1][0] + value,
		m.values[1][1] + value,
		m.values[1][2] + value,
		m.values[1][3] + value,
		m.values[2][0] + value,
		m.values[2][1] + value,
		m.values[2][2] + value,
		m.values[2][3] + value,
		m.values[3][0] + value,
		m.values[3][1] + value,
		m.values[3][2] + value,
		m.values[3][3] + value
	};
    
	return Result;
}

Mat4 operator+(Mat4 n, Mat4 m)
{
	Mat4 Result =
	{
		n.values[0][0] + m.values[0][0],
		n.values[0][1] + m.values[0][1],
		n.values[0][2] + m.values[0][2],
		n.values[0][3] + m.values[0][3],
		n.values[1][0] + m.values[1][0],
		n.values[1][1] + m.values[1][1],
		n.values[1][2] + m.values[1][2],
		n.values[1][3] + m.values[1][3],
		n.values[2][0] + m.values[2][0],
		n.values[2][1] + m.values[2][1],
		n.values[2][2] + m.values[2][2],
		n.values[2][3] + m.values[2][3],
		n.values[3][0] + m.values[3][0],
		n.values[3][1] + m.values[3][1],
		n.values[3][2] + m.values[3][2],
		n.values[3][3] + m.values[3][3]
	};
    
	return Result;
}

Mat2 operator-(Mat2 m, f32 value)
{
	Mat2 Result =
	{
		m.values[0][0] - value,
		m.values[0][1] - value,
		m.values[1][0] - value,
		m.values[1][1] - value
	};
    
	return Result;
}

Mat2 operator-(Mat2 n, Mat2 m)
{
	Mat2 Result =
	{
		n.values[0][0] - m.values[0][0],
		n.values[0][1] - m.values[0][1],
		n.values[1][0] - m.values[1][0],
		n.values[1][1] - m.values[1][1]
	};
    
	return Result;
}

Mat3 operator-(Mat3 m, f32 value)
{
	Mat3 Result =
	{
		m.values[0][0] - value,
		m.values[0][1] - value,
		m.values[0][2] - value,
		m.values[1][0] - value,
		m.values[1][1] - value,
		m.values[1][2] - value,
		m.values[2][0] - value,
		m.values[2][1] - value,
		m.values[2][2] - value
	};
    
	return Result;
}

Mat3 operator-(Mat3 n, Mat3 m)
{
	Mat3 Result =
	{
		n.values[0][0] - m.values[0][0],
		n.values[0][1] - m.values[0][1],
		n.values[0][2] - m.values[0][2],
		n.values[1][0] - m.values[1][0],
		n.values[1][1] - m.values[1][1],
		n.values[1][2] - m.values[1][2],
		n.values[2][0] - m.values[2][0],
		n.values[2][1] - m.values[2][1],
		n.values[2][2] - m.values[2][2]
	};
    
	return Result;
}

Mat4 operator-(Mat4 m, f32 value)
{
	Mat4 Result =
	{
		m.values[0][0] - value,
		m.values[0][1] - value,
		m.values[0][2] - value,
		m.values[0][3] - value,
		m.values[1][0] - value,
		m.values[1][1] - value,
		m.values[1][2] - value,
		m.values[1][3] - value,
		m.values[2][0] - value,
		m.values[2][1] - value,
		m.values[2][2] - value,
		m.values[2][3] - value,
		m.values[3][0] - value,
		m.values[3][1] - value,
		m.values[3][2] - value,
		m.values[3][3] - value
	};
    
	return Result;
}

Mat4 operator-(Mat4 n, Mat4 m)
{
	Mat4 Result =
	{
		n.values[0][0] - m.values[0][0],
		n.values[0][1] - m.values[0][1],
		n.values[0][2] - m.values[0][2],
		n.values[0][3] - m.values[0][3],
		n.values[1][0] - m.values[1][0],
		n.values[1][1] - m.values[1][1],
		n.values[1][2] - m.values[1][2],
		n.values[1][3] - m.values[1][3],
		n.values[2][0] - m.values[2][0],
		n.values[2][1] - m.values[2][1],
		n.values[2][2] - m.values[2][2],
		n.values[2][3] - m.values[2][3],
		n.values[3][0] - m.values[3][0],
		n.values[3][1] - m.values[3][1],
		n.values[3][2] - m.values[3][2],
		n.values[3][3] - m.values[3][3]
	};
    
	return Result;
}

Mat2 operator*(Mat2 n, Mat2 m)
{
	Mat2 Result =
	{
		(n.values[0][0] * m.values[0][0]) + (n.values[0][1] * m.values[1][0]),
		(n.values[0][0] * m.values[0][1]) + (n.values[0][1] * m.values[1][1]),
        
		(n.values[1][0] * m.values[0][0]) + (n.values[1][1] * m.values[1][0]),
		(n.values[1][0] * m.values[0][1]) + (n.values[1][1] * m.values[1][1])
	};
    
	return Result;
}

Mat3 operator*(Mat3 n, Mat3 m)
{
	Mat3 Result =
	{
		(n.values[0][0] * m.values[0][0]) + (n.values[0][1] * m.values[1][0]) + (n.values[0][2] * m.values[2][0]),
		(n.values[0][0] * m.values[0][1]) + (n.values[0][1] * m.values[1][1]) + (n.values[0][2] * m.values[2][1]),
		(n.values[0][0] * m.values[0][2]) + (n.values[0][1] * m.values[1][2]) + (n.values[0][2] * m.values[2][2]),
        
		(n.values[1][0] * m.values[0][0]) + (n.values[1][1] * m.values[1][0]) + (n.values[1][2] * m.values[2][0]),
		(n.values[1][0] * m.values[0][1]) + (n.values[1][1] * m.values[1][1]) + (n.values[1][2] * m.values[2][1]),
		(n.values[1][0] * m.values[0][2]) + (n.values[1][1] * m.values[1][2]) + (n.values[1][2] * m.values[2][2]),
        
		(n.values[2][0] * m.values[0][0]) + (n.values[2][1] * m.values[1][0]) + (n.values[2][2] * m.values[2][0]),
		(n.values[2][0] * m.values[0][1]) + (n.values[2][1] * m.values[1][1]) + (n.values[2][2] * m.values[2][1]),
		(n.values[2][0] * m.values[0][2]) + (n.values[2][1] * m.values[1][2]) + (n.values[2][2] * m.values[2][2])
	};
    
	return Result;
}

Mat4 operator*(Mat4 n, Mat4 m)
{
	Mat4 Result =
	{
		(n.values[0][0] * m.values[0][0]) + (n.values[0][1] * m.values[1][0]) + (n.values[0][2] * m.values[2][0]) + (n.values[0][3] * m.values[3][0]),
		(n.values[0][0] * m.values[0][1]) + (n.values[0][1] * m.values[1][1]) + (n.values[0][2] * m.values[2][1]) + (n.values[0][3] * m.values[3][1]),
		(n.values[0][0] * m.values[0][2]) + (n.values[0][1] * m.values[1][2]) + (n.values[0][2] * m.values[2][2]) + (n.values[0][3] * m.values[3][2]),
		(n.values[0][0] * m.values[0][3]) + (n.values[0][1] * m.values[1][3]) + (n.values[0][2] * m.values[2][3]) + (n.values[0][3] * m.values[3][3]),
        
		(n.values[1][0] * m.values[0][0]) + (n.values[1][1] * m.values[1][0]) + (n.values[1][2] * m.values[2][0]) + (n.values[1][3] * m.values[3][0]),
		(n.values[1][0] * m.values[0][1]) + (n.values[1][1] * m.values[1][1]) + (n.values[1][2] * m.values[2][1]) + (n.values[1][3] * m.values[3][1]),
		(n.values[1][0] * m.values[0][2]) + (n.values[1][1] * m.values[1][2]) + (n.values[1][2] * m.values[2][2]) + (n.values[1][3] * m.values[3][2]),
		(n.values[1][0] * m.values[0][3]) + (n.values[1][1] * m.values[1][3]) + (n.values[1][2] * m.values[2][3]) + (n.values[1][3] * m.values[3][3]),
        
		(n.values[2][0] * m.values[0][0]) + (n.values[2][1] * m.values[1][0]) + (n.values[2][2] * m.values[2][0]) + (n.values[2][3] * m.values[3][0]),
		(n.values[2][0] * m.values[0][1]) + (n.values[2][1] * m.values[1][1]) + (n.values[2][2] * m.values[2][1]) + (n.values[2][3] * m.values[3][1]),
		(n.values[2][0] * m.values[0][2]) + (n.values[2][1] * m.values[1][2]) + (n.values[2][2] * m.values[2][2]) + (n.values[2][3] * m.values[3][2]),
		(n.values[2][0] * m.values[0][3]) + (n.values[2][1] * m.values[1][3]) + (n.values[2][2] * m.values[2][3]) + (n.values[2][3] * m.values[3][3]),
        
		(n.values[3][0] * m.values[0][0]) + (n.values[3][1] * m.values[1][0]) + (n.values[3][2] * m.values[2][0]) + (n.values[3][3] * m.values[3][0]),
		(n.values[3][0] * m.values[0][1]) + (n.values[3][1] * m.values[1][1]) + (n.values[3][2] * m.values[2][1]) + (n.values[3][3] * m.values[3][1]),
		(n.values[3][0] * m.values[0][2]) + (n.values[3][1] * m.values[1][2]) + (n.values[3][2] * m.values[2][2]) + (n.values[3][3] * m.values[3][2]),
		(n.values[3][0] * m.values[0][3]) + (n.values[3][1] * m.values[1][3]) + (n.values[3][2] * m.values[2][3]) + (n.values[3][3] * m.values[3][3])
	};
    
	return Result;
}

v2 operator*(Mat2 m, v2 v)
{
	v2 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y),
        (m.values[1][0] * v.x) + (m.values[1][1] * v.y)
	};
    
	return Result;
}

v3 operator*(Mat3 m, v3 v)
{
	v3 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y) + (m.values[0][2] * v.z),
        (m.values[1][0] * v.x) + (m.values[1][1] * v.y) + (m.values[1][2] * v.z),
        (m.values[2][0] * v.x) + (m.values[2][1] * v.y) + (m.values[2][2] * v.z)
	};
    
	return Result;
}

v4 operator*(Mat4 m, v4 v)
{
	v4 Result =
	{
		(m.values[0][0] * v.x) + (m.values[0][1] * v.y) + (m.values[0][2] * v.z) + (m.values[0][3] * v.w),
        (m.values[1][0] * v.x) + (m.values[1][1] * v.y) + (m.values[1][2] * v.z) + (m.values[1][3] * v.w),
        (m.values[2][0] * v.x) + (m.values[2][1] * v.y) + (m.values[2][2] * v.z) + (m.values[2][3] * v.w),
        (m.values[3][0] * v.x) + (m.values[3][1] * v.y) + (m.values[3][2] * v.z) + (m.values[3][3] * v.w)
	};
    
	return Result;
}
#endif

f32 Determinant2(Mat2 m)
{
	f32 Result = (m.values[0][0] * m.values[1][1]) - (m.values[0][1] * m.values[0][0]);
    
	return Result;
}

f32 Determinant3(Mat3 m)
{
	f32 Result = 0.0f;
    
	Result += (m.row1.x * m.row2.y * m.row3.z);
	Result += (m.row1.y * m.row2.z * m.row3.x);
	Result += (m.row1.z * m.row2.x * m.row3.y);
    
	Result -= (m.row1.z * m.row2.y * m.row3.x);
	Result -= (m.row1.x * m.row2.z * m.row3.y);
	Result -= (m.row1.y * m.row2.x * m.row3.z);
    
	return Result;
}

f32 Determinant4(Mat4 m)
{
	f32 Result = 0.0f;
    
	Mat3 Minor1;
	Mat3 Minor2;
	Mat3 Minor3;
	Mat3 Minor4;
    
	v3 row1 = vec3(m.row1.y, m.row1.z, m.row1.w);
	v3 row2 = vec3(m.row2.y, m.row2.z, m.row2.w);
	v3 row3 = vec3(m.row3.y, m.row3.z, m.row3.w);
	v3 row4 = vec3(m.row4.y, m.row4.z, m.row4.w);
    
	Minor1.row1 = row2; Minor1.row2 = row3; Minor1.row3 = row4;
	Minor2.row1 = row1; Minor2.row2 = row3; Minor2.row3 = row4;
	Minor3.row1 = row1; Minor3.row2 = row2; Minor3.row3 = row4;
	Minor4.row1 = row1; Minor4.row2 = row2; Minor4.row3 = row3;
    
	Result = m.row1.x * Determinant3(Minor1) - m.row2.x * Determinant3(Minor2) +
        m.row3.x * Determinant3(Minor3) - m.row4.x * Determinant3(Minor4);
    
	return Result;
}

Mat2 Identity2()
{
	Mat2 Result = { 1, 0, 0, 1 };
	return Result;
}

Mat3 Identity3()
{
	Mat3 Result = {};
	Result.values[0][0] = 1;
	Result.values[1][1] = 1;
	Result.values[2][2] = 1;
    
	return Result;
}

Mat4 Identity4()
{
	Mat4 Result = {};
	Result.values[0][0] = 1;
	Result.values[1][1] = 1;
	Result.values[2][2] = 1;
	Result.values[3][3] = 1;
    
	return Result;
}

Mat2 MatOfMinors2(Mat2 m)
{
	Mat2 Result = {};
	Result.values[0][0] = m.row2.y;
	Result.values[0][0] = m.row2.x;
	Result.values[0][0] = m.row1.y;
	Result.values[0][0] = m.row1.x;
    
	return Result;
}

Mat3 MatOfMinors3(Mat3 m)
{
	Mat3 Result = {};
	Mat2 Minor11, Minor12, Minor13, Minor21, Minor22, Minor23, Minor31, Minor32, Minor33;
    
	Minor11.row1 = vec2(m.row2.y, m.row2.z);
	Minor11.row2 = vec2(m.row3.y, m.row3.z);
	Minor12.row1 = vec2(m.row2.x, m.row2.z);
	Minor12.row2 = vec2(m.row3.x, m.row3.z);
	Minor13.row1 = vec2(m.row2.x, m.row2.y);
	Minor13.row2 = vec2(m.row3.x, m.row3.y);
    
	Minor21.row1 = vec2(m.row1.y, m.row1.z);
	Minor21.row2 = vec2(m.row3.y, m.row3.z);
	Minor22.row1 = vec2(m.row1.x, m.row1.z);
	Minor22.row2 = vec2(m.row3.x, m.row3.z);
	Minor23.row1 = vec2(m.row1.x, m.row1.y);
	Minor23.row2 = vec2(m.row3.x, m.row3.y);
    
	Minor31.row1 = vec2(m.row1.y, m.row1.z);
	Minor31.row2 = vec2(m.row2.y, m.row2.z);
	Minor32.row1 = vec2(m.row1.x, m.row1.z);
	Minor32.row2 = vec2(m.row2.x, m.row2.z);
	Minor33.row1 = vec2(m.row1.x, m.row1.y);
	Minor33.row2 = vec2(m.row2.x, m.row2.y);
    
	Result.values[0][0] = Determinant2(Minor11);
	Result.values[0][1] = Determinant2(Minor12);
	Result.values[0][2] = Determinant2(Minor13);
    
	Result.values[1][0] = Determinant2(Minor21);
	Result.values[1][1] = Determinant2(Minor22);
	Result.values[1][2] = Determinant2(Minor23);
    
	Result.values[2][0] = Determinant2(Minor31);
	Result.values[2][1] = Determinant2(Minor32);
	Result.values[2][2] = Determinant2(Minor33);
    
	return Result;
}

Mat4 MatOfMinors4(Mat4 m)
{
	Mat4 Result = {};
    
	Mat3 Minor11, Minor12, Minor13, Minor14, Minor21, Minor22, Minor23, Minor24, Minor31, Minor32, Minor33, Minor34, Minor41, Minor42, Minor43, Minor44;
    
	Minor11.row1 = vec3(m.row2.y, m.row2.z, m.row2.w);
	Minor11.row2 = vec3(m.row3.y, m.row3.z, m.row3.w);
	Minor11.row3 = vec3(m.row4.y, m.row4.z, m.row4.w);
	Minor12.row1 = vec3(m.row2.x, m.row2.z, m.row2.w);
	Minor12.row2 = vec3(m.row3.x, m.row3.z, m.row3.w);
	Minor12.row3 = vec3(m.row4.x, m.row4.z, m.row4.w);
	Minor13.row1 = vec3(m.row2.x, m.row2.y, m.row2.w);
	Minor13.row2 = vec3(m.row3.x, m.row3.y, m.row3.w);
	Minor13.row3 = vec3(m.row4.x, m.row4.y, m.row4.w);
	Minor14.row1 = vec3(m.row2.x, m.row2.y, m.row2.z);
	Minor14.row2 = vec3(m.row3.x, m.row3.y, m.row3.z);
	Minor14.row3 = vec3(m.row4.x, m.row4.y, m.row4.z);
    
	Minor21.row1 = vec3(m.row1.y, m.row1.z, m.row1.w);
	Minor21.row2 = vec3(m.row3.y, m.row3.z, m.row3.w);
	Minor21.row3 = vec3(m.row4.y, m.row4.z, m.row4.w);
	Minor22.row1 = vec3(m.row1.x, m.row1.z, m.row1.w);
	Minor22.row2 = vec3(m.row3.x, m.row3.z, m.row3.w);
	Minor22.row3 = vec3(m.row4.x, m.row4.z, m.row4.w);
	Minor23.row1 = vec3(m.row1.x, m.row1.y, m.row1.w);
	Minor23.row2 = vec3(m.row3.x, m.row3.y, m.row3.w);
	Minor23.row3 = vec3(m.row4.x, m.row4.y, m.row4.w);
	Minor24.row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	Minor24.row2 = vec3(m.row3.x, m.row3.y, m.row3.z);
	Minor24.row3 = vec3(m.row4.x, m.row4.y, m.row4.z);
    
	Minor31.row1 = vec3(m.row1.y, m.row1.z, m.row1.w);
	Minor31.row2 = vec3(m.row2.y, m.row2.z, m.row2.w);
	Minor31.row3 = vec3(m.row4.y, m.row4.z, m.row4.w);
	Minor32.row1 = vec3(m.row1.x, m.row1.z, m.row1.w);
	Minor32.row2 = vec3(m.row2.x, m.row2.z, m.row2.w);
	Minor32.row3 = vec3(m.row4.x, m.row4.z, m.row4.w);
	Minor33.row1 = vec3(m.row1.x, m.row1.y, m.row1.w);
	Minor33.row2 = vec3(m.row2.x, m.row2.y, m.row2.w);
	Minor33.row3 = vec3(m.row4.x, m.row4.y, m.row4.w);
	Minor34.row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	Minor34.row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	Minor34.row3 = vec3(m.row4.x, m.row4.y, m.row4.z);
    
	Minor41.row1 = vec3(m.row1.y, m.row1.z, m.row1.w);
	Minor41.row2 = vec3(m.row2.y, m.row2.z, m.row2.w);
	Minor41.row3 = vec3(m.row3.y, m.row3.z, m.row3.w);
	Minor42.row1 = vec3(m.row1.x, m.row1.z, m.row1.w);
	Minor42.row2 = vec3(m.row2.x, m.row2.z, m.row2.w);
	Minor42.row3 = vec3(m.row3.x, m.row3.z, m.row3.w);
	Minor43.row1 = vec3(m.row1.x, m.row1.y, m.row1.w);
	Minor43.row2 = vec3(m.row2.x, m.row2.y, m.row2.w);
	Minor43.row3 = vec3(m.row3.x, m.row3.y, m.row3.w);
	Minor44.row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	Minor44.row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	Minor44.row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
    
	Result.values[0][0] = Determinant3(Minor11);
	Result.values[0][1] = Determinant3(Minor12);
	Result.values[0][2] = Determinant3(Minor13);
	Result.values[0][3] = Determinant3(Minor14);
    
	Result.values[1][0] = Determinant3(Minor21);
	Result.values[1][1] = Determinant3(Minor22);
	Result.values[1][2] = Determinant3(Minor23);
	Result.values[1][3] = Determinant3(Minor24);
    
	Result.values[2][0] = Determinant3(Minor31);
	Result.values[2][1] = Determinant3(Minor32);
	Result.values[2][2] = Determinant3(Minor33);
	Result.values[2][3] = Determinant3(Minor34);
    
	Result.values[3][0] = Determinant3(Minor41);
	Result.values[3][1] = Determinant3(Minor42);
	Result.values[3][2] = Determinant3(Minor43);
	Result.values[3][3] = Determinant3(Minor44);
    
	return Result;
}

Mat2 Transpose2(Mat2 m)
{
	Mat2 Result = {};
	
	v2 row1 = { m.row1.x, m.row2.x };
	v2 row2 = { m.row1.y, m.row2.y };
    
	Result.row1 = row1;
	Result.row2 = row2;
    
	return Result;
}

Mat3 Transpose3(Mat3 m)
{
	Mat3 Result = {};
    
	v3 row1 = { m.row1.x, m.row2.x, m.row3.x };
	v3 row2 = { m.row1.y, m.row2.y, m.row3.y };
	v3 row3 = { m.row1.z, m.row2.z, m.row3.z };
    
	Result.row1 = row1;
	Result.row2 = row2;
	Result.row3 = row3;
    
	return Result;
}

Mat4 Transpose4(Mat4 m)
{
	Mat4 Result = {};
    
	v4 row1 = { m.row1.x, m.row2.x, m.row3.x, m.row4.x };
	v4 row2 = { m.row1.y, m.row2.y, m.row3.y, m.row4.y };
	v4 row3 = { m.row1.z, m.row2.z, m.row3.z, m.row4.z };
	v4 row4 = { m.row1.z, m.row2.z, m.row3.z, m.row4.z };
    
	Result.row1 = row1;
	Result.row2 = row2;
	Result.row3 = row3;
	Result.row4 = row4;
    
	return Result;
}


Mat2 Inverse2(Mat2 m)
{
	Mat2 Result = {};
    
	f32 InverseDet = 1.0f / Determinant2(m);
	Mat2 TransMinor = Transpose2(MatOfMinors2(m));
    
	Result = ls_mat2Mulf32(TransMinor, InverseDet);
    
	return Result;
}

Mat3 Inverse3(Mat3 m)
{
	Mat3 Result = {};
    
	f32 InverseDet = 1.0f / Determinant3(m);
	Mat3 TransMinor = Transpose3(MatOfMinors3(m));
    
	Result = ls_mat3Mulf32(TransMinor, InverseDet);
    
	return Result;
}

Mat4 Inverse4(Mat4 m)
{
	Mat4 Result = {};
    
	f32 InverseDet = 1.0f / Determinant4(m);
	Mat4 TransMinor = Transpose4(MatOfMinors4(m));
    
	Result = ls_mat4Mulf32(TransMinor, InverseDet);
    
	return Result;
}

Mat3 NormalMatrix(Mat4 m)
{
	Mat3 Result = {};
    
	Mat4 tmp = Transpose4(Inverse4(m));
    
	Result.row1 = vec3(tmp.row1.x, tmp.row1.y, tmp.row1.z);
	Result.row2 = vec3(tmp.row2.x, tmp.row2.y, tmp.row2.z);
	Result.row3 = vec3(tmp.row3.x, tmp.row3.y, tmp.row3.z);
    
	return Result;
}

Mat2 UniformScale2(f32 factor)
{
	Mat2 Result = Identity2();
	Result = ls_mat2Mulf32(Result, factor);
    
	return Result;
}

Mat3 UniformScale3(f32 factor)
{
	Mat3 Result = Identity3();
	Result = ls_mat3Mulf32(Result, factor);
    
	return Result;
}

Mat4 UniformScale4(f32 factor)
{
	Mat4 Result = Identity4();
	Result = ls_mat4Mulf32(Result, factor);
    
	return Result;
}

Mat2 Scale2(v2 v)
{
	Mat2 Result = Identity2();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;
    
	return Result;
}

Mat3 Scale3(v3 v)
{
	Mat3 Result = Identity3();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;
	Result.values[2][2] = v.z;
    
	return Result;
}

Mat4 Scale4(v4 v)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = v.x;
	Result.values[1][1] = v.y;
	Result.values[2][2] = v.z;
	Result.values[3][3] = v.w;
    
	return Result;
}

Mat4 Translate(v4 v)
{
	Mat4 Result = Identity4();
	Result.values[0][3] = v.x;
	Result.values[1][3] = v.y;
	Result.values[2][3] = v.z;
	Result.values[3][3] = v.w;
    
	return Result;
}

///////////////////////////////////////////
// MATRIX BAD ROTATION (WANT QUATERNIONS D=)
///////////////////////////////////////////

Mat4 RotateX(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[1][1] = (f32)ls_cos(Angle);
	Result.values[2][2] = (f32)ls_cos(Angle);
	Result.values[1][2] = (f32)-ls_sin(Angle);
	Result.values[2][1] = (f32)ls_sin(Angle);
    
	return Result;
}

Mat4 RotateY(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[0][2] = (f32)ls_sin(Angle);
	Result.values[2][0] = (f32)-ls_sin(Angle);
	Result.values[2][2] = (f32)ls_cos(Angle);
    
	return Result;
}

Mat4 RotateZ(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[1][1] = (f32)ls_cos(Angle);
	Result.values[1][0] = (f32)ls_sin(Angle);
	Result.values[0][1] = (f32)-ls_sin(Angle);
    
	return Result;
}

///////////////////////////////////////////
// PROJECTION MATRIXES
///////////////////////////////////////////

Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top)
{
	Mat4 Result = {};
	Result.values[0][0] = near / right;
	Result.values[1][1] = near / top;
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;
    
	return Result;
}

Mat4 PerspectiveProjEx(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom)
{
	Mat4 Result = {};
	Result.values[0][0] = ((2.0f*near) / (right - left));
	Result.values[0][2] = ((right + left) / (right - left));
	Result.values[1][1] = ((2.0f*near) / (top - bottom));
	Result.values[1][2] = ((top + bottom) / (top - bottom));
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;
    
	return Result;
}

Mat4 PerspectiveProjFOV(f32 FOV, f32 aspectRatio, f32 near, f32 far)
{
	Mat4 Result = {};
    
	f32 tanHalfFOV = (f32)ls_tan(FOV / 2.0f);
    
	Result.values[0][0] = (1.0f / (aspectRatio * tanHalfFOV));
	Result.values[1][1] = (1.0f / tanHalfFOV);
	Result.values[2][2] = -((far + near) / (far - near));
	Result.values[2][3] = ((-2.0f*far*near) / (far - near));
	Result.values[3][2] = -1.0f;
    
	return Result;
}

Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top)
{
	Mat4 Result = {};
	Result.values[0][0] = 1.0f / right;
	Result.values[1][1] = 1.0f / top;
	Result.values[2][2] = -(2.0f / (far - near));
	Result.values[2][3] = -((far + near) / (far - near));
	Result.values[3][3] = 1.0f;
    
	return Result;
}

Mat4 OrthoProjEx(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom)
{
	Mat4 Result = {};
	Result.values[0][0] = ((2.0f) / (right - left));
	Result.values[0][3] = -((right + left) / (right - left));
	Result.values[1][1] = ((2.0f) / (top - bottom));
	Result.values[1][3] = -((top + bottom) / (top - bottom));
	Result.values[2][2] = -((2.0f) / (far - near));
	Result.values[2][3] = -((far + near) / (far - near));
	Result.values[3][3] = 1.0f;
    
	return Result;
}

#endif
