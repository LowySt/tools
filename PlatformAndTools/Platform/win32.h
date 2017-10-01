#pragma once
#include "lsWindows.h"

#define internal	static
#define global		static

#define Byte(n)			(n)
#define Kilobyte(n)		1024*Byte(n)
#define Megabyte(n)		1024*Kilobyte(n)
#define Gigabyte(n)		1024*Megabyte(n)
#define Kb				Kilobyte
#define Mb				Megabyte
#define Gb				Gigabyte

//Really don't have time to fukin fight with includes...
#pragma region GL TYPES
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
#pragma endregion

enum FILE_TYPE
{
	BINARY_DATA,
	BITMAP,

	FILE_TYPE_MAX
};

struct FileInfo
{
	FILE_TYPE	FileType;

	u64			size;
	void		*data;

};

struct ScreenInfo
{
	WNDCLASSA	WindowClass;
	HWND		WindowHandle;
	HDC			DeviceContext;
	HGLRC		RenderingContext;

	s32			Width;
	s32			Height;

	s32			UpdateFrequency;
};

struct KeyboardManager
{
	b32	isQuitting	= FALSE;

	b32	DownArrow	= FALSE;
	b32 UpArrow		= FALSE;
	b32	LeftArrow	= FALSE;
	b32 RightArrow	= FALSE;

	b32 Key_W		= FALSE;
	b32 Key_A		= FALSE;
	b32 Key_S		= FALSE;
	b32 Key_D		= FALSE;

	b32 Key_P		= FALSE;

	b32 Key_Shift	= FALSE;
	b32 Key_Ctrl	= FALSE;
};

struct MouseManager
{
	f32 mouseX;
	f32 mouseY;

	f32 xOffset;
	f32 yOffset;

	f32 MouseCenterX;
	f32 MouseCenterY;
	
	b32 LeftDown	= FALSE;
	b32 RigthDown	= FALSE;
	b32 MiddleDown = FALSE;
};

enum VAO_Type
{
	VAO_TRIANGLE,
	VAO_RECTANGLE,
	VAO_LIGHT_CONTAINER,
	VAO_LIGHT,

	VAO_MAX
};

struct Shader;
struct Texture;
struct Camera;
struct TransformManager;

struct VAO_Container
{
	GLuint		VAO;
	Shader		*ShaderProgram;
	Texture		*Texture;

	VAO_Type	Type;
	u32			IndexInContainer;
};

struct OpenGLInfo
{
	VAO_Container		VAOs[32];
	u32					NextAvailableIndex;

	Camera				*Camera;
	TransformManager	*Transform;
};

struct InputManager
{
	MouseManager		*Mouse;
	KeyboardManager		*Keyboard;
};

struct Memory
{
	void		*BeginPointer;
	
	s32			Size;
	s32			UsedMemory;
	s32			RemainingMemory;

	s32			MinimumAllocationSize;
};

typedef DWORD		(*WIN32_GIVEMEMORYPROC)(Memory *Memory, VOID **BasePointer, s32 Size);
typedef VOID		(*WIN32_READTEXTFILE)(Memory *Memory, char *Path, char **Dest);
typedef VOID		(*WIN32_READENTIREFILE)(const char *Path, FileInfo *FileInfo, Memory *Memory);
typedef ULONGLONG	(*WIN32_TIME)();

struct MemoryArena
{
	WIN32_GIVEMEMORYPROC	Alloc;
	WIN32_TIME				Time;
	WIN32_READTEXTFILE		ReadTextFile;
	WIN32_READENTIREFILE	ReadEntireFile;

	ULONGLONG				StartingTime;
	f32						MsPerFrame;

	Memory					PermanentMemory;

	s32						PageSize;
	s32						AllocationGranularity;	
};