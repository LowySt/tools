#ifndef LS_MATHS_HEADER
#define LS_MATHS_HEADER

#include "Platform\win32.h"
#include "tools\lsCRT.h"

///////////////////////////////////////////
// VECTOR DEFINITIONS
///////////////////////////////////////////

union Mat2;
union Mat3;
union Mat4;

_declspec(align(16))
struct v2
{
	f32 x;
	f32 y;

	v2 operator+(v2 v);
	v2 operator-(v2 v);
	v2 operator*(f32 value);
	v2 operator*(Mat2 m);

	f32	operator*(v2 v);
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

	v3 operator+(v3 v);
	v3 operator-(v3 v);
	v3 operator*(f32 value);
	v3 operator*(Mat3 m);
	v3 operator^(v3 v);
	

	f32	operator*(v3 v);
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

	v4 operator+(v4 v);
	v4 operator-(v4 v);
	v4 operator*(f32 value);
	v4 operator*(Mat4 m);

	f32	operator*(v4 v);
};

struct v2i
{
	s32 x;
	s32 y;

	v2i operator+(v2i v);
	v2i operator-(v2i v);

	f32 operator*(v2i v);
};

struct v3i
{
	s32 x;
	s32 y;
	s32 z;

	v3i	operator+(v3i v);
	v3i	operator-(v3i v);

	v3i	operator^(v3i v);

	f32	operator*(v3i v);
};

struct v4i
{
	s32 x;
	s32 y;
	s32 z;
	s32 w;

	v4i	operator+(v4i v);
	v4i	operator-(v4i v);

	f32	operator*(v4i v);
};

///////////////////////////////////////////
// VECTOR FUNCTIONS
///////////////////////////////////////////

extern "C"
{
	v2	vec2(f32 x, f32 y);
	v3	vec3(f32 x, f32 y, f32 z);
	v4	vec4(f32 x, f32 y, f32 z, f32 w);
	v2i vec2i(s32 x, s32 y);
	v3i vec3i(s32 x, s32 y, s32 z);
	v4i vec4i(s32 x, s32 y, s32 z, s32 w);

	v2 V2(v3 v);
	v3 V3(v4 v);
	v4 V4(v3 v);

	f32	LengthV2(v2 v);
	f32	LengthV3(v3 v);
	f32	LengthV4(v4 v);

	f32 LengthV2i(v2i v);
	f32 LengthV3i(v3i v);
	f32 LengthV4i(v4i v);

	v2	NormalizeV2(v2 v);
	v3	NormalizeV3(v3 v);
	v4	NormalizeV4(v4 v);

	v2 NormalizeV2i(v2i v);
	v3 NormalizeV3i(v3i v);
	v4 NormalizeV4i(v4i v);
};

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

	Mat2 operator+(f32 value);
	Mat2 operator+(Mat2 m);

	Mat2 operator-(f32 value);
	Mat2 operator-(Mat2 m);

	Mat2 operator*(f32 value);
	Mat2 operator*(Mat2 m);
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

	Mat3 operator+(f32 value);
	Mat3 operator+(Mat3 m);

	Mat3 operator-(f32 value);
	Mat3 operator-(Mat3 m);

	Mat3 operator*(f32 value);
	Mat3 operator*(Mat3 m);
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

	Mat4 operator-(f32 value);
	Mat4 operator-(Mat4 m);

	Mat4 operator+(f32 value);
	Mat4 operator+(Mat4 m);

	Mat4 operator*(f32 value);
	Mat4 operator*(Mat4 m);
};

///////////////////////////////////////////
// MATRIX FUNCTIONS
///////////////////////////////////////////

extern "C"
{
	Mat2 Identity2();
	Mat3 Identity3();
	Mat4 Identity4();

	Mat4 NormalMatrix();

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
};

#endif

#ifdef LS_MATH_IMPLEMENTATION

#include <immintrin.h>
///////////////////////////////////////////
// VECTOR DEFINITIONS
///////////////////////////////////////////

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

v3	NormalizeV3(v3 v)
{
	f32 L = LengthV3(v);
	v3 Result = { v.x / L, v.y / L, v.z / L };

	return Result;
}

v4	NormalizeV4(v4 v)
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

v2 v2::operator+(v2 v)
{
	v2 Result = { this->x + v.x, this->y + v.y };
	return Result;
}

v3 v3::operator+(v3 v)
{
	v3 Result = { this->x + v.x, this->y + v.y, this->z + v.z };
	return Result;
}

v4 v4::operator+(v4 v)
{
	v4 Result = { this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w };
	return Result;
}

v2i v2i::operator+(v2i v)
{
	v2i Result = { this->x + v.x, this->y + v.y };
	return Result;
}

v3i	v3i::operator+(v3i v)
{
	v3i Result = { this->x + v.x, this->y + v.y, this->z + v.z };
	return Result;
}

v4i	v4i::operator+(v4i v)
{
	v4i Result = { this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w };
	return Result;
}

v2 v2::operator-(v2 v)
{
	v2 Result = { this->x - v.x, this->y - v.y };
	return Result;
}

v3 v3::operator-(v3 v)
{
	v3 Result = { this->x - v.x, this->y - v.y, this->z - v.z };
	return Result;
}

v4 v4::operator-(v4 v)
{
	v4 Result = { this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w };
	return Result;
}

v2i v2i::operator-(v2i v)
{
	v2i Result = { this->x - v.x, this->y - v.y };
	return Result;
}

v3i	v3i::operator-(v3i v)
{
	v3i Result = { this->x - v.x, this->y - v.y, this->z - v.z };
	return Result;
}

v4i	v4i::operator-(v4i v)
{
	v4i Result = { this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w };
	return Result;
}

v2 v2::operator*(f32 value)
{
	v2 Result = { this->x * value, this->y * value };
	return Result;
}

v3 v3::operator*(f32 value)
{
	v3 Result = { this->x * value, this->y * value, this->z * value };
	return Result;
}

v4 v4::operator*(f32 value)
{
	v4 Result = { this->x * value, this->y * value, this->z * value, this->w * value };
	return Result;
}

f32	v2::operator*(v2 v)
{
	return (this->x * v.x) + (this->y * v.y);
}

f32	v3::operator*(v3 v)
{
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

f32	v4::operator*(v4 v)
{
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z) + (this->w * v.w);
}

f32 v2i::operator*(v2i v)
{
	return (f32)(this->x * v.x) + (this->y * v.y);
}

f32	v3i::operator*(v3i v)
{
	return (f32)(this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

f32	v4i::operator*(v4i v)
{
	return (f32)(this->x * v.x) + (this->y * v.y) + (this->z * v.z) + (this->w * v.w);
}

v3 v3::operator^(v3 v)
{
	v3 Result = {};
	Result.x = (this->y * v.z) - (this->z * v.y);
	Result.y = (this->z * v.x) - (this->x * v.z);
	Result.z = (this->x * v.y) - (this->y * v.x);

	return Result;
}

v3i	v3i::operator^(v3i v)
{
	v3i Result = {};
	Result.x = (this->y * v.z) - (this->z * v.y);
	Result.y = (this->z * v.x) - (this->x * v.z);
	Result.z = (this->x * v.y) - (this->y * v.x);

	return Result;
}

///////////////////////////////////////////
// MATRIX OPERATIONS
///////////////////////////////////////////

Mat2 Mat2::operator+(f32 value)
{
	Mat2 Result =
	{
		this->values[0][0] + value,
		this->values[0][1] + value,
		this->values[1][0] + value,
		this->values[1][1] + value
	};

	return Result;
}

Mat2 Mat2::operator+(Mat2 m)
{
	Mat2 Result =
	{
		this->values[0][0] + m.values[0][0],
		this->values[0][1] + m.values[0][1],
		this->values[1][0] + m.values[1][0],
		this->values[1][1] + m.values[1][1]
	};

	return Result;
}

Mat3 Mat3::operator+(f32 value)
{
	Mat3 Result =
	{
		this->values[0][0] + value,
		this->values[0][1] + value,
		this->values[0][2] + value,
		this->values[1][0] + value,
		this->values[1][1] + value,
		this->values[1][2] + value,
		this->values[2][0] + value,
		this->values[2][1] + value,
		this->values[2][2] + value
	};

	return Result;
}

Mat3 Mat3::operator+(Mat3 m)
{
	Mat3 Result =
	{
		this->values[0][0] + m.values[0][0],
		this->values[0][1] + m.values[0][1],
		this->values[0][2] + m.values[0][2],
		this->values[1][0] + m.values[1][0],
		this->values[1][1] + m.values[1][1],
		this->values[1][2] + m.values[1][2],
		this->values[2][0] + m.values[2][0],
		this->values[2][1] + m.values[2][1],
		this->values[2][2] + m.values[2][2]
	};

	return Result;
}

Mat4 Mat4::operator+(f32 value)
{
	Mat4 Result =
	{
		this->values[0][0] + value,
		this->values[0][1] + value,
		this->values[0][2] + value,
		this->values[0][3] + value,
		this->values[1][0] + value,
		this->values[1][1] + value,
		this->values[1][2] + value,
		this->values[1][3] + value,
		this->values[2][0] + value,
		this->values[2][1] + value,
		this->values[2][2] + value,
		this->values[2][3] + value,
		this->values[3][0] + value,
		this->values[3][1] + value,
		this->values[3][2] + value,
		this->values[3][3] + value
	};

	return Result;
}

Mat4 Mat4::operator+(Mat4 m)
{
	Mat4 Result =
	{
		this->values[0][0] + m.values[0][0],
		this->values[0][1] + m.values[0][1],
		this->values[0][2] + m.values[0][2],
		this->values[0][3] + m.values[0][3],
		this->values[1][0] + m.values[1][0],
		this->values[1][1] + m.values[1][1],
		this->values[1][2] + m.values[1][2],
		this->values[1][3] + m.values[1][3],
		this->values[2][0] + m.values[2][0],
		this->values[2][1] + m.values[2][1],
		this->values[2][2] + m.values[2][2],
		this->values[2][3] + m.values[2][3],
		this->values[3][0] + m.values[3][0],
		this->values[3][1] + m.values[3][1],
		this->values[3][2] + m.values[3][2],
		this->values[3][3] + m.values[3][3]
	};

	return Result;
}

Mat2 Mat2::operator-(f32 value)
{
	Mat2 Result =
	{
		this->values[0][0] - value,
		this->values[0][1] - value,
		this->values[1][0] - value,
		this->values[1][1] - value
	};

	return Result;
}

Mat2 Mat2::operator-(Mat2 m)
{
	Mat2 Result =
	{
		this->values[0][0] - m.values[0][0],
		this->values[0][1] - m.values[0][1],
		this->values[1][0] - m.values[1][0],
		this->values[1][1] - m.values[1][1]
	};

	return Result;
}

Mat3 Mat3::operator-(f32 value)
{
	Mat3 Result =
	{
		this->values[0][0] - value,
		this->values[0][1] - value,
		this->values[0][2] - value,
		this->values[1][0] - value,
		this->values[1][1] - value,
		this->values[1][2] - value,
		this->values[2][0] - value,
		this->values[2][1] - value,
		this->values[2][2] - value
	};

	return Result;
}

Mat3 Mat3::operator-(Mat3 m)
{
	Mat3 Result =
	{
		this->values[0][0] - m.values[0][0],
		this->values[0][1] - m.values[0][1],
		this->values[0][2] - m.values[0][2],
		this->values[1][0] - m.values[1][0],
		this->values[1][1] - m.values[1][1],
		this->values[1][2] - m.values[1][2],
		this->values[2][0] - m.values[2][0],
		this->values[2][1] - m.values[2][1],
		this->values[2][2] - m.values[2][2]
	};

	return Result;
}

Mat4 Mat4::operator-(f32 value)
{
	Mat4 Result =
	{
		this->values[0][0] - value,
		this->values[0][1] - value,
		this->values[0][2] - value,
		this->values[0][3] - value,
		this->values[1][0] - value,
		this->values[1][1] - value,
		this->values[1][2] - value,
		this->values[1][3] - value,
		this->values[2][0] - value,
		this->values[2][1] - value,
		this->values[2][2] - value,
		this->values[2][3] - value,
		this->values[3][0] - value,
		this->values[3][1] - value,
		this->values[3][2] - value,
		this->values[3][3] - value
	};

	return Result;
}

Mat4 Mat4::operator-(Mat4 m)
{
	Mat4 Result =
	{
		this->values[0][0] - m.values[0][0],
		this->values[0][1] - m.values[0][1],
		this->values[0][2] - m.values[0][2],
		this->values[0][3] - m.values[0][3],
		this->values[1][0] - m.values[1][0],
		this->values[1][1] - m.values[1][1],
		this->values[1][2] - m.values[1][2],
		this->values[1][3] - m.values[1][3],
		this->values[2][0] - m.values[2][0],
		this->values[2][1] - m.values[2][1],
		this->values[2][2] - m.values[2][2],
		this->values[2][3] - m.values[2][3],
		this->values[3][0] - m.values[3][0],
		this->values[3][1] - m.values[3][1],
		this->values[3][2] - m.values[3][2],
		this->values[3][3] - m.values[3][3]
	};

	return Result;
}

Mat2 Mat2::operator*(f32 value)
{
	Mat2 Result =
	{
		this->values[0][0] * value,
		this->values[0][1] * value,
		this->values[1][0] * value,
		this->values[1][1] * value
	};

	return Result;
}

Mat2 Mat2::operator*(Mat2 m)
{
	Mat2 Result =
	{
		(this->values[0][0] * m.values[0][0]) + (this->values[0][1] * m.values[1][0]),
		(this->values[0][0] * m.values[0][1]) + (this->values[0][1] * m.values[1][1]),

		(this->values[1][0] * m.values[0][0]) + (this->values[1][1] * m.values[1][0]),
		(this->values[1][0] * m.values[0][1]) + (this->values[1][1] * m.values[1][1])
	};

	return Result;
}

Mat3 Mat3::operator*(f32 value)
{
	Mat3 Result =
	{
		this->values[0][0] * value,
		this->values[0][1] * value,
		this->values[0][2] * value,
		this->values[1][0] * value,
		this->values[1][1] * value,
		this->values[1][2] * value,
		this->values[2][0] * value,
		this->values[2][1] * value,
		this->values[2][2] * value
	};

	return Result;
}

Mat3 Mat3::operator*(Mat3 m)
{
	Mat3 Result =
	{
		(this->values[0][0] * m.values[0][0]) + (this->values[0][1] * m.values[1][0]) + (this->values[0][2] * m.values[2][0]),
		(this->values[0][0] * m.values[0][1]) + (this->values[0][1] * m.values[1][1]) + (this->values[0][2] * m.values[2][1]),
		(this->values[0][0] * m.values[0][2]) + (this->values[0][1] * m.values[1][2]) + (this->values[0][2] * m.values[2][2]),

		(this->values[1][0] * m.values[0][0]) + (this->values[1][1] * m.values[1][0]) + (this->values[1][2] * m.values[2][0]),
		(this->values[1][0] * m.values[0][1]) + (this->values[1][1] * m.values[1][1]) + (this->values[1][2] * m.values[2][1]),
		(this->values[1][0] * m.values[0][2]) + (this->values[1][1] * m.values[1][2]) + (this->values[1][2] * m.values[2][2]),

		(this->values[2][0] * m.values[0][0]) + (this->values[2][1] * m.values[1][0]) + (this->values[2][2] * m.values[2][0]),
		(this->values[2][0] * m.values[0][1]) + (this->values[2][1] * m.values[1][1]) + (this->values[2][2] * m.values[2][1]),
		(this->values[2][0] * m.values[0][2]) + (this->values[2][1] * m.values[1][2]) + (this->values[2][2] * m.values[2][2])
	};

	return Result;
}

Mat4 Mat4::operator*(f32 value)
{
	Mat4 Result =
	{
		this->values[0][0] * value,
		this->values[0][1] * value,
		this->values[0][2] * value,
		this->values[0][3] * value,
		this->values[1][0] * value,
		this->values[1][1] * value,
		this->values[1][2] * value,
		this->values[1][3] * value,
		this->values[2][0] * value,
		this->values[2][1] * value,
		this->values[2][2] * value,
		this->values[2][3] * value,
		this->values[3][0] * value,
		this->values[3][1] * value,
		this->values[3][2] * value,
		this->values[3][3] * value
	};

	return Result;
}

Mat4 Mat4::operator*(Mat4 m)
{
	Mat4 Result =
	{
		(this->values[0][0] * m.values[0][0]) + (this->values[0][1] * m.values[1][0]) + (this->values[0][2] * m.values[2][0]) + (this->values[0][3] * m.values[3][0]),
		(this->values[0][0] * m.values[0][1]) + (this->values[0][1] * m.values[1][1]) + (this->values[0][2] * m.values[2][1]) + (this->values[0][3] * m.values[3][1]),
		(this->values[0][0] * m.values[0][2]) + (this->values[0][1] * m.values[1][2]) + (this->values[0][2] * m.values[2][2]) + (this->values[0][3] * m.values[3][2]),
		(this->values[0][0] * m.values[0][3]) + (this->values[0][1] * m.values[1][3]) + (this->values[0][2] * m.values[2][3]) + (this->values[0][3] * m.values[3][3]),

		(this->values[1][0] * m.values[0][0]) + (this->values[1][1] * m.values[1][0]) + (this->values[1][2] * m.values[2][0]) + (this->values[1][3] * m.values[3][0]),
		(this->values[1][0] * m.values[0][1]) + (this->values[1][1] * m.values[1][1]) + (this->values[1][2] * m.values[2][1]) + (this->values[1][3] * m.values[3][1]),
		(this->values[1][0] * m.values[0][2]) + (this->values[1][1] * m.values[1][2]) + (this->values[1][2] * m.values[2][2]) + (this->values[1][3] * m.values[3][2]),
		(this->values[1][0] * m.values[0][3]) + (this->values[1][1] * m.values[1][3]) + (this->values[1][2] * m.values[2][3]) + (this->values[1][3] * m.values[3][3]),

		(this->values[2][0] * m.values[0][0]) + (this->values[2][1] * m.values[1][0]) + (this->values[2][2] * m.values[2][0]) + (this->values[2][3] * m.values[3][0]),
		(this->values[2][0] * m.values[0][1]) + (this->values[2][1] * m.values[1][1]) + (this->values[2][2] * m.values[2][1]) + (this->values[2][3] * m.values[3][1]),
		(this->values[2][0] * m.values[0][2]) + (this->values[2][1] * m.values[1][2]) + (this->values[2][2] * m.values[2][2]) + (this->values[2][3] * m.values[3][2]),
		(this->values[2][0] * m.values[0][3]) + (this->values[2][1] * m.values[1][3]) + (this->values[2][2] * m.values[2][3]) + (this->values[2][3] * m.values[3][3]),

		(this->values[3][0] * m.values[0][0]) + (this->values[3][1] * m.values[1][0]) + (this->values[3][2] * m.values[2][0]) + (this->values[3][3] * m.values[3][0]),
		(this->values[3][0] * m.values[0][1]) + (this->values[3][1] * m.values[1][1]) + (this->values[3][2] * m.values[2][1]) + (this->values[3][3] * m.values[3][1]),
		(this->values[3][0] * m.values[0][2]) + (this->values[3][1] * m.values[1][2]) + (this->values[3][2] * m.values[2][2]) + (this->values[3][3] * m.values[3][2]),
		(this->values[3][0] * m.values[0][3]) + (this->values[3][1] * m.values[1][3]) + (this->values[3][2] * m.values[2][3]) + (this->values[3][3] * m.values[3][3])
	};

	return Result;
}

v2 v2::operator*(Mat2 m)
{
	v2 Result =
	{
		(m.values[0][0] * this->x) + (m.values[0][1] * this->y),

		(m.values[1][0] * this->x) + (m.values[1][1] * this->y)
	};

	return Result;
}

v3 v3::operator*(Mat3 m)
{
	v3 Result =
	{
		(m.values[0][0] * this->x) + (m.values[0][1] * this->y) + (m.values[0][2] * this->z),

		(m.values[1][0] * this->x) + (m.values[1][1] * this->y) + (m.values[1][2] * this->z),

		(m.values[2][0] * this->x) + (m.values[2][1] * this->y) + (m.values[2][2] * this->z)
	};

	return Result;
}

v4 v4::operator*(Mat4 m)
{
	v4 Result =
	{
		(m.values[0][0] * this->x) + (m.values[0][1] * this->y) + (m.values[0][2] * this->z) + (m.values[0][3] * this->w),

		(m.values[1][0] * this->x) + (m.values[1][1] * this->y) + (m.values[1][2] * this->z) + (m.values[1][3] * this->w),

		(m.values[2][0] * this->x) + (m.values[2][1] * this->y) + (m.values[2][2] * this->z) + (m.values[2][3] * this->w),

		(m.values[3][0] * this->x) + (m.values[3][1] * this->y) + (m.values[3][2] * this->z) + (m.values[3][3] * this->w)
	};

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

Mat2 UniformScale2(f32 factor)
{
	Mat2 Result = Identity2();
	Result = Result * factor;

	return Result;
}

Mat3 UniformScale3(f32 factor)
{
	Mat3 Result = Identity3();
	Result = Result * factor;

	return Result;
}

Mat4 UniformScale4(f32 factor)
{
	Mat4 Result = Identity4();
	Result = Result * factor;

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
	Result.values[1][2] = (f32)-ls_sine(Angle);
	Result.values[2][1] = (f32)ls_sine(Angle);

	return Result;
}

Mat4 RotateY(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[0][2] = (f32)ls_sine(Angle);
	Result.values[2][0] = (f32)-ls_sine(Angle);
	Result.values[2][2] = (f32)ls_cos(Angle);

	return Result;
}

Mat4 RotateZ(f32 Angle)
{
	Mat4 Result = Identity4();
	Result.values[0][0] = (f32)ls_cos(Angle);
	Result.values[1][1] = (f32)ls_cos(Angle);
	Result.values[1][0] = (f32)ls_sine(Angle);
	Result.values[0][1] = (f32)-ls_sine(Angle);

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