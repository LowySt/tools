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

	f32 operator[](u32 i);

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
	
	f32 operator[](u32 i);

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

	f32 operator[](u32 i);

	f32	operator*(v4 v);
};

struct v2i
{
	s32 x;
	s32 y;

	v2i operator+(v2i v);
	v2i operator-(v2i v);

	s32 operator[](u32 i);

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

	s32 operator[](u32 i);

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

	s32 operator[](u32 i);

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

f32 v2::operator[](u32 i)
{
	switch (i)
	{
	case 0:
		return this->x;
	case 1:
		return this->y;
	default:
		Assert(false);
	}
	Assert(false);
	return 0.0f;
}

f32 v3::operator[](u32 i)
{
	switch (i)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			Assert(false);
	}
	Assert(false);
	return 0.0f;
}

f32 v4::operator[](u32 i)
{
	switch (i)
	{
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	case 3:
		return this->w;
	default:
		Assert(false);
	}
	Assert(false);
	return 0.0f;
}

s32 v2i::operator[](u32 i)
{
	switch (i)
	{
	case 0:
		return this->x;
	case 1:
		return this->y;
	default:
		Assert(false);
	}
	Assert(false);
	return 0;
}

s32 v3i::operator[](u32 i)
{
	switch (i)
	{
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	default:
		Assert(false);
	}
	Assert(false);
	return 0;
}

s32 v4i::operator[](u32 i)
{
	switch (i)
	{
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	case 3:
		return this->w;
	default:
		Assert(false);
	}
	Assert(false);
	return 0;
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

f32 Determinant2(Mat2 m)
{
	f32 Result = (m.values[0][0] * m.values[1][1]) - (m.values[0][1] * m.values[0][0]);

	return Result;
}

f32 Determinant3(Mat3 m)
{
	f32 Result = 0.0f;

	Result += (m.row1[0] * m.row2[1] * m.row3[2]);
	Result += (m.row1[1] * m.row2[2] * m.row3[0]);
	Result += (m.row1[2] * m.row2[0] * m.row3[1]);

	Result -= (m.row1[2] * m.row2[1] * m.row3[0]);
	Result -= (m.row1[0] * m.row2[2] * m.row3[1]);
	Result -= (m.row1[1] * m.row2[0] * m.row3[2]);

	return Result;
}

f32 Determinant4(Mat4 m)
{
	f32 Result = 0.0f;

	Mat3 Minor1;
	Mat3 Minor2;
	Mat3 Minor3;
	Mat3 Minor4;

	v3 row1 = vec3(m.row1[1], m.row1[2], m.row1[3]);
	v3 row2 = vec3(m.row2[1], m.row2[2], m.row2[3]);
	v3 row3 = vec3(m.row3[1], m.row3[2], m.row3[3]);
	v3 row4 = vec3(m.row4[1], m.row4[2], m.row4[3]);

	Minor1.row1 = row2; Minor1.row2 = row3; Minor1.row3 = row4;
	Minor2.row1 = row1; Minor1.row2 = row3; Minor1.row3 = row4;
	Minor3.row1 = row1; Minor1.row2 = row2; Minor1.row3 = row4;
	Minor4.row1 = row1; Minor1.row2 = row2; Minor1.row3 = row3;

	Result = m.row1[0] * Determinant3(Minor1) - m.row2[0] * Determinant3(Minor2) + m.row3[0] * Determinant3(Minor3) - m.row4[0] * Determinant3(Minor4);

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
	Result.values[0][0] = m.row2[1];
	Result.values[0][0] = m.row2[0];
	Result.values[0][0] = m.row1[1];
	Result.values[0][0] = m.row1[0];

	return Result;
}

Mat3 MatOfMinors3(Mat3 m)
{
	Mat3 Result = {};
	Mat2 Minor11, Minor12, Minor13, Minor21, Minor22, Minor23, Minor31, Minor32, Minor33;

	Minor11.row1 = vec2(m.row2[1], m.row2[2]);
	Minor11.row2 = vec2(m.row3[1], m.row3[2]);
	Minor12.row1 = vec2(m.row2[0], m.row2[2]);
	Minor12.row2 = vec2(m.row3[0], m.row3[2]);
	Minor13.row1 = vec2(m.row2[0], m.row2[1]);
	Minor13.row2 = vec2(m.row3[0], m.row3[1]);

	Minor21.row1 = vec2(m.row1[1], m.row1[2]);
	Minor21.row2 = vec2(m.row3[1], m.row3[2]);
	Minor22.row1 = vec2(m.row1[0], m.row1[2]);
	Minor22.row2 = vec2(m.row3[0], m.row3[2]);
	Minor23.row1 = vec2(m.row1[0], m.row1[1]);
	Minor23.row2 = vec2(m.row3[0], m.row3[1]);

	Minor31.row1 = vec2(m.row1[1], m.row1[2]);
	Minor31.row2 = vec2(m.row2[1], m.row2[2]);
	Minor32.row1 = vec2(m.row1[0], m.row1[2]);
	Minor32.row2 = vec2(m.row2[0], m.row2[2]);
	Minor33.row1 = vec2(m.row1[0], m.row1[1]);
	Minor33.row2 = vec2(m.row2[0], m.row2[1]);

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

	Minor11.row1 = vec3(m.row2[1], m.row2[2], m.row2[3]);
	Minor11.row2 = vec3(m.row3[1], m.row3[2], m.row3[3]);
	Minor11.row3 = vec3(m.row4[1], m.row4[2], m.row4[3]);
	Minor12.row1 = vec3(m.row2[0], m.row2[2], m.row2[3]);
	Minor12.row2 = vec3(m.row3[0], m.row3[2], m.row3[3]);
	Minor12.row3 = vec3(m.row4[0], m.row4[2], m.row4[3]);
	Minor13.row1 = vec3(m.row2[0], m.row2[1], m.row2[3]);
	Minor13.row2 = vec3(m.row3[0], m.row3[1], m.row3[3]);
	Minor13.row3 = vec3(m.row4[0], m.row4[1], m.row4[3]);
	Minor14.row1 = vec3(m.row2[0], m.row2[1], m.row2[2]);
	Minor14.row2 = vec3(m.row3[0], m.row3[1], m.row3[2]);
	Minor14.row3 = vec3(m.row4[0], m.row4[1], m.row4[2]);

	Minor21.row1 = vec3(m.row1[1], m.row1[2], m.row1[3]);
	Minor21.row2 = vec3(m.row3[1], m.row3[2], m.row3[3]);
	Minor21.row3 = vec3(m.row4[1], m.row4[2], m.row4[3]);
	Minor22.row1 = vec3(m.row1[0], m.row1[2], m.row1[3]);
	Minor22.row2 = vec3(m.row3[0], m.row3[2], m.row3[3]);
	Minor22.row3 = vec3(m.row4[0], m.row4[2], m.row4[3]);
	Minor23.row1 = vec3(m.row1[0], m.row1[1], m.row1[3]);
	Minor23.row2 = vec3(m.row3[0], m.row3[1], m.row3[3]);
	Minor23.row3 = vec3(m.row4[0], m.row4[1], m.row4[3]);
	Minor24.row1 = vec3(m.row1[0], m.row1[1], m.row1[2]);
	Minor24.row2 = vec3(m.row3[0], m.row3[1], m.row3[2]);
	Minor24.row3 = vec3(m.row4[0], m.row4[1], m.row4[2]);

	Minor31.row1 = vec3(m.row1[1], m.row1[2], m.row1[3]);
	Minor31.row2 = vec3(m.row2[1], m.row2[2], m.row2[3]);
	Minor31.row3 = vec3(m.row4[1], m.row4[2], m.row4[3]);
	Minor32.row1 = vec3(m.row1[0], m.row1[2], m.row1[3]);
	Minor32.row2 = vec3(m.row2[0], m.row2[2], m.row2[3]);
	Minor32.row3 = vec3(m.row4[0], m.row4[2], m.row4[3]);
	Minor33.row1 = vec3(m.row1[0], m.row1[1], m.row1[3]);
	Minor33.row2 = vec3(m.row2[0], m.row2[1], m.row2[3]);
	Minor33.row3 = vec3(m.row4[0], m.row4[1], m.row4[3]);
	Minor34.row1 = vec3(m.row1[0], m.row1[1], m.row1[2]);
	Minor34.row2 = vec3(m.row2[0], m.row2[1], m.row2[2]);
	Minor34.row3 = vec3(m.row4[0], m.row4[1], m.row4[2]);

	Minor41.row1 = vec3(m.row1[1], m.row1[2], m.row1[3]);
	Minor41.row2 = vec3(m.row2[1], m.row2[2], m.row2[3]);
	Minor41.row3 = vec3(m.row3[1], m.row3[2], m.row3[3]);
	Minor42.row1 = vec3(m.row1[0], m.row1[2], m.row1[3]);
	Minor42.row2 = vec3(m.row2[0], m.row2[2], m.row2[3]);
	Minor42.row3 = vec3(m.row3[0], m.row3[2], m.row3[3]);
	Minor43.row1 = vec3(m.row1[0], m.row1[1], m.row1[3]);
	Minor43.row2 = vec3(m.row2[0], m.row2[1], m.row2[3]);
	Minor43.row3 = vec3(m.row3[0], m.row3[1], m.row3[3]);
	Minor44.row1 = vec3(m.row1[0], m.row1[1], m.row1[2]);
	Minor44.row2 = vec3(m.row2[0], m.row2[1], m.row2[2]);
	Minor44.row3 = vec3(m.row3[0], m.row3[1], m.row3[2]);

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
	
	v2 row1 = { m.row1[0], m.row2[0] };
	v2 row2 = { m.row1[1], m.row2[1] };

	Result.row1 = row1;
	Result.row2 = row2;

	return Result;
}

Mat3 Transpose3(Mat3 m)
{
	Mat3 Result = {};

	v3 row1 = { m.row1[0], m.row2[0], m.row3[0] };
	v3 row2 = { m.row1[1], m.row2[1], m.row3[1] };
	v3 row3 = { m.row1[2], m.row2[2], m.row3[2] };

	Result.row1 = row1;
	Result.row2 = row2;
	Result.row3 = row3;

	return Result;
}

Mat4 Transpose4(Mat4 m)
{
	Mat4 Result = {};

	v4 row1 = { m.row1[0], m.row2[0], m.row3[0], m.row4[0] };
	v4 row2 = { m.row1[1], m.row2[1], m.row3[1], m.row4[1] };
	v4 row3 = { m.row1[2], m.row2[2], m.row3[2], m.row4[2] };
	v4 row4 = { m.row1[3], m.row2[3], m.row3[3], m.row4[3] };

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

	Result = TransMinor * InverseDet;

	return Result;
}

Mat3 Inverse3(Mat3 m)
{
	Mat3 Result = {};

	f32 InverseDet = 1.0f / Determinant3(m);
	Mat3 TransMinor = Transpose3(MatOfMinors3(m));

	Result = TransMinor * InverseDet;

	return Result;
}

Mat4 Inverse4(Mat4 m)
{
	Mat4 Result = {};

	f32 InverseDet = 1.0f / Determinant4(m);
	Mat4 TransMinor = Transpose4(MatOfMinors4(m));

	Result = TransMinor * InverseDet;

	return Result;
}

Mat3 NormalMatrix(Mat4 modelMat)
{
	Mat3 Result = {};

	Mat4 tmp = Transpose4(Inverse4(modelMat));

	Result.row1 = vec3(tmp.row1[0], tmp.row1[1], tmp.row1[2]);
	Result.row2 = vec3(tmp.row2[0], tmp.row2[1], tmp.row2[2]);
	Result.row3 = vec3(tmp.row3[0], tmp.row3[1], tmp.row3[2]);

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