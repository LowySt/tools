#pragma once

#include "Platform\win32.h"
#include "tools\lsCRT.h"

///////////////////////////////////////////
// VECTOR DEFINITIONS
///////////////////////////////////////////

_declspec(align(16))
struct v2
{
	f32 x;
	f32 y;
};

_declspec(align(16))
union v3
{
	struct
	{
		f32 x;
		f32 y;
		f32 z;
	};
	struct
	{
		f32 r;
		f32 g;
		f32 b;
	};
};

_declspec(align(16))
union v4
{
	struct
	{
		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
	struct
	{
		f32 r;
		f32 g;
		f32 b;
		f32 a;
	};
};

struct v2i
{
	s32 x;
	s32 y;
};

struct v3i
{
	s32 x;
	s32 y;
	s32 z;
};

struct v4i
{
	s32 x;
	s32 y;
	s32 z;
	s32 w;
};

///////////////////////////////////////////
// VECTOR FUNCTIONS
///////////////////////////////////////////

v2	vec2(f32 x, f32 y);
v3	vec3(f32 x, f32 y, f32 z);
v4	vec4(f32 x, f32 y, f32 z, f32 w);
v2i vec2(s32 x, s32 y);
v3i vec3(s32 x, s32 y, s32 z);
v4i vec4(s32 x, s32 y, s32 z, s32 w);

v2 V2(v3 v);
v3 V3(v4 v);
v4 V4(v3 v);

v2	operator+(v2 v, v2 u);
v3	operator+(v3 v, v3 u);
v4	operator+(v4 v, v4 u);

v2i operator+(v2i v, v2i u);
v3i	operator+(v3i v, v3i u);
v4i	operator+(v4i v, v4i u);

v2	operator-(v2 v, v2 u);
v3	operator-(v3 v, v3 u);
v4	operator-(v4 v, v4 u);

v2i operator-(v2i v, v2i u);
v3i	operator-(v3i v, v3i u);
v4i	operator-(v4i v, v4i u);

f32	Length(v2 v);
f32	Length(v3 v);
f32	Length(v4 v);

f32 Length(v2i v);
f32 Length(v3i v);
f32 Length(v4i v);

v2	Normalize(v2 v);
v3	Normalize(v3 v);
v4	Normalize(v4 v);

v2 Normalize(v2i v);
v3 Normalize(v3i v);
v4 Normalize(v4i v);

v2	operator*(v2 v, f32 value);
v3	operator*(v3 v, f32 value);
v4	operator*(v4 v, f32 value);

f32	operator*(v2 v, v2 u);
f32	operator*(v3 v, v3 u);
f32	operator*(v4 v, v4 u);

f32 operator*(v2i v, v2i u);
f32	operator*(v3i v, v3i u);
f32	operator*(v4i v, v4i u);

v3	operator^(v3 v, v3 u);
v3i	operator^(v3i v, v3i u);

///////////////////////////////////////////
// Coordinate System
///////////////////////////////////////////

struct CoordSys
{
	v3 x;
	v3 y;
	v3 z;
};

///////////////////////////////////////////
// MATRIX DEFINITIONS
///////////////////////////////////////////

union Mat2
{
	struct
	{
		v2 row1;
		v2 row2;
	};
	
	f32 values[2][2];
};

union Mat3
{
	struct
	{
		v3 row1;
		v3 row2;
		v3 row3;
	};

	f32 values[3][3];
};

union Mat4
{
	struct
	{
		v4 row1;
		v4 row2;
		v4 row3;
		v4 row4;
	};
	
	f32 values[4][4];
};

///////////////////////////////////////////
// MATRIX FUNCTIONS
///////////////////////////////////////////

Mat2 operator+(f32 value, Mat2 M);
Mat2 operator+(Mat2 m1, Mat2 m2);

Mat3 operator+(f32 value, Mat3 M);
Mat3 operator+(Mat3 m1, Mat3 m2);

Mat4 operator+(f32 value, Mat4 M);
Mat4 operator+(Mat4 m1, Mat4 m2);

Mat2 operator-(f32 value, Mat2 M);
Mat2 operator-(Mat2 m1, Mat2 m2);

Mat3 operator-(f32 value, Mat3 M);
Mat3 operator-(Mat3 m1, Mat3 m2);

Mat4 operator-(f32 value, Mat4 M);
Mat4 operator-(Mat4 m1, Mat4 m2);

Mat2 operator*(f32 value, Mat2 M);
Mat2 operator*(Mat2 m1, Mat2 m2);

Mat3 operator*(f32 value, Mat3 M);
Mat3 operator*(Mat3 m1, Mat3 m2);

Mat4 operator*(f32 value, Mat4 M);
Mat4 operator*(Mat4 m1, Mat4 m2);

v2 operator*(Mat2 m, v2 v);
v3 operator*(Mat3 m, v3 v);
v4 operator*(Mat4 m, v4 v);

Mat2 Identity2();
Mat3 Identity3();
Mat4 Identity4();

Mat2 UniformScale2(f32 factor);
Mat3 UniformScale3(f32 factor);
Mat4 UniformScale4(f32 factor);

Mat2 Scale(v2 v);
Mat3 Scale(v3 v);
Mat4 Scale(v4 v);

Mat4 Translate(v4 v);

Mat4 RotateX(f32 Angle);
Mat4 RotateY(f32 Angle);
Mat4 RotateZ(f32 Angle);

Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top);
Mat4 PerspectiveProj(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom);
Mat4 PerspectiveProjFOV(f32 FOV, f32 aspectRatio, f32 near, f32 far);

Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top);
Mat4 OrthoProj(f32 near, f32 far, f32 right, f32 top, f32 left, f32 bottom);
