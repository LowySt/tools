#ifndef WIN32_H
#define WIN32_H

#include "win32.h"

#define internal	static
#define global		static

#define Byte(n)			(n)
#define Kilobyte(n)		1024ULL*Byte(n)
#define Megabyte(n)		1024ULL*Kilobyte(n)
#define Gigabyte(n)		1024ULL*Megabyte(n)
#define Kb				Kilobyte
#define Mb				Megabyte
#define Gb				Gigabyte
#define KBytes			Kb
#define MBytes			Mb
#define GBytes			Gb


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

extern "C" s32 ls_printf(const char *fmt, ...);
extern "C" s32 ls_sprintf(char *dest, const char *fmt, ...);
extern "C" void ls_memcpy(void *src, void *dest, size_t size);
extern "C" void ls_zeroMem(void *mem, size_t size);

struct MemoryBlockHeader
{
	void *next;
	void *prev;

	u32 size;
};

struct MemoryArena
{
	void *heap;

	MemoryBlockHeader *freeHead;

	u32 minBlockSize;
	u32 maxBlockSize;

	u32 totalSize;
	u32 firstAllocSize = 0;
};

static MemoryArena Memory = {};

extern "C"
{
	void windows_assert(const char *msg, const char *file, s32 line);
	void windows_setAllocatorParams(u32 firstAllocSize, u32 minBlockSize, u32 maxBlockSize);
	void *windows_memAlloc(size_t size);
	void windows_memFree(void *ptr);

	u64 windows_ReadConsole(char *Dest, u32 bytesToRead);
	u64 windows_WriteConsole(char *buffer, u32 bytesToWrite);
	u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead);
	u64 windows_WriteFile(char *Path, char *source, u32 bytesToWrite, b32 append);
};

#endif

#ifdef PLATFORM_IMPLEMENTATION

u64 windows_ReadConsole(char *Dest, u32 bytesToRead)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;
	if ((FileHandle = CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		ls_printf("When creating a file handle got error: %ld\n", Error);
	}

	DWORD BytesRead = 0;
	if (ReadFile(FileHandle, Dest, bytesToRead, &BytesRead, NULL) == FALSE)
	{
		Error = GetLastError();
		ls_printf("When Reading contents of a file got error: %ld\n", Error);
	}
	else
	{
		if (BytesRead != bytesToRead)
		{ ls_printf("Bytes read when reading entire file don't equal the file size!!\n"); }
	}

	if (CloseHandle(FileHandle) == FALSE)
	{ OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n"); }

	return BytesRead;
}

u64 windows_WriteConsole(char *buffer, u32 bytesToWrite)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;
	if ((FileHandle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		OutputDebugStringA("When creating a file handle got error\n");
	}

	DWORD BytesWritten = 0;
	if (!WriteFile(FileHandle, buffer, bytesToWrite, &BytesWritten, NULL))
	{
		Error = GetLastError();
		OutputDebugStringA("When writing to Console Output got error\n");
	}

	if (!CloseHandle(FileHandle))
	{
		Error = GetLastError();
		OutputDebugStringA("When closing Console Output Handle got error\n");
	}

	return BytesWritten;
}

void windows_assert(const char *msg, const char *file, s32 line)
{
	char buff[512] = { 0 };
	s32 written = ls_sprintf(buff, "In file %s, line %d, Assert %s fired\n", file, line, msg);
	windows_WriteConsole(buff, (u32)written);
}

static void windows_breakMemoryBlock(MemoryBlockHeader *blockHeader, u32 desiredSize)
{
	u32 offsetSize = blockHeader->size - desiredSize;
	void *nextBlockPtr = (u8 *)blockHeader + offsetSize;

	MemoryBlockHeader newBlock = { blockHeader->next, blockHeader, desiredSize };
	ls_memcpy((void *)&newBlock, nextBlockPtr, sizeof(MemoryBlockHeader));

	if (blockHeader->next)
	{
		((MemoryBlockHeader *)blockHeader->next)->prev = nextBlockPtr;
	}
	blockHeader->next = nextBlockPtr;
	blockHeader->size = offsetSize;

	return;
}

static void windows_halveMemoryBlock(MemoryBlockHeader *blockHeader)
{
	windows_breakMemoryBlock(blockHeader, blockHeader->size / 2);
}

static void windows_removeMemoryBlockFromList(MemoryBlockHeader *blockHeader)
{
	((MemoryBlockHeader *)blockHeader->prev)->next = blockHeader->next;
	((MemoryBlockHeader *)blockHeader->next)->prev = blockHeader->prev;

	return;
}

static void windows_initMemory()
{
	u32 allocationSize = 0;

	if (Memory.firstAllocSize != 0) { allocationSize = Memory.firstAllocSize; }
	else
	{
		MEMORYSTATUSEX info = { 0 }; info.dwLength = sizeof(MEMORYSTATUSEX);
		b32 result = GlobalMemoryStatusEx(&info);
		if (!result)
		{ 
			DWORD Error = GetLastError();
			OutputDebugStringA("Error when calling GlobalMemoryStatusEx() in windows_initMemory()\n"); 
		}

		u32 totalRamInBytes = (u32)info.ullTotalVirtual;

		if (totalRamInBytes < GBytes(8ULL)) { allocationSize = totalRamInBytes / 4; }
		else { allocationSize = GBytes(2ULL); }
	}

	Memory.heap = VirtualAlloc(0, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (Memory.heap == NULL)
	{
		DWORD Error = GetLastError();
		OutputDebugStringA("Error when calling VirtualAlloc() in windows_initMemory()");
	}

	MemoryBlockHeader firstBlock = { NULL, NULL, allocationSize };
	Memory.totalSize = allocationSize;
	ls_memcpy((void *)&firstBlock, Memory.heap, sizeof(MemoryBlockHeader));

	Memory.freeHead = (MemoryBlockHeader *)Memory.heap;
}

void windows_setAllocatorParams(u32 firstAllocSize, u32 minBlockSize, u32 maxBlockSize)
{
	if (firstAllocSize != 0)
	{ Memory.firstAllocSize = firstAllocSize; }

	if (minBlockSize != 0)
	{ Memory.minBlockSize = minBlockSize; }

	if (maxBlockSize != 0)
	{ Memory.maxBlockSize = maxBlockSize; }
}

void *windows_memAlloc(size_t request)
{
	u64 givenMemory = request >= 12 ? request : 12;

	if (Memory.heap == 0)
	{ windows_initMemory(); }

	if (Memory.freeHead->next == 0)
	{ windows_halveMemoryBlock(Memory.freeHead); }

	MemoryBlockHeader *currHeader = Memory.freeHead;
	MemoryBlockHeader *bestBlock = 0; u32 bestBlockSize = Memory.totalSize;

	b32 found = FALSE;
	do
	{
		if ((currHeader->size < bestBlockSize) && (currHeader->size > givenMemory))
		{ bestBlock = currHeader; bestBlockSize = currHeader->size; }

		if (currHeader->size == givenMemory)
		{ found = TRUE; break; }

		currHeader = (MemoryBlockHeader *)currHeader->next;
	} 
	while (currHeader);

	if (!found)
	{ windows_breakMemoryBlock(bestBlock, (u32)givenMemory); }

	MemoryBlockHeader *actualBlock = (MemoryBlockHeader *)bestBlock->next;

	windows_removeMemoryBlockFromList(actualBlock);
	ls_zeroMem(actualBlock, actualBlock->size);

	return actualBlock;
}

void windows_memFree(void *p)
{
	MemoryBlockHeader *currHeader = Memory.freeHead;

	void *prev = 0, *next = 0;
	while ((void *)currHeader < p)
	{
		if (currHeader->next > p)
		{
			prev = (void *)currHeader;
			next = currHeader->next;
			break;
		}

		currHeader = (MemoryBlockHeader *)currHeader->next;
	}

	u32 newHeaderSize = (u32)((u8 *)next - (u8 *)p);
	MemoryBlockHeader newHeader = { next, prev, newHeaderSize };

	ls_memcpy((void *)&newHeader, p, sizeof(MemoryBlockHeader));

	((MemoryBlockHeader *)prev)->next = p;
	((MemoryBlockHeader *)next)->prev = p;

	return;
}

u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;
	LARGE_INTEGER FileSize = {};

	if ((FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		ls_printf("When creating a file handle got error: %ld", Error);
	}
	
	u32 ToRead;
	if (bytesToRead == 0)
	{
		if (GetFileSizeEx(FileHandle, &FileSize) == 0)
		{
			Error = GetLastError();
			ls_printf("When getting file size got error: %ld\n", Error);
		}
		ToRead = FileSize.LowPart;
	}
	else
	{
		ToRead = bytesToRead;
	}
	
	*Dest = (char *)windows_memAlloc(ToRead);

	DWORD BytesRead = 0;
	if (ReadFile(FileHandle, *Dest, ToRead, &BytesRead, NULL) == FALSE)
	{
		Error = GetLastError();
		ls_printf("When Reading contents of a file got error: %ld\n", Error);
	}
	else
	{
		if (BytesRead != ToRead)
		{ ls_printf("Bytes read when reading entire file don't equal the file size!!\n"); }
	}

	if (CloseHandle(FileHandle) == FALSE)
	{ OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n"); }

	return BytesRead;
}

u64 windows_WriteFile(char *Path, char *source, u32 bytesToWrite, b32 append)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;

	u32 fileAccessRights = append ? FILE_APPEND_DATA : FILE_GENERIC_WRITE;

	if ((FileHandle = CreateFileA(Path, fileAccessRights, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		DWORD Error = GetLastError();
		ls_printf("Gotten Error %ld when creating file handle to file: %s\n", Error, Path);
	}

	DWORD BytesWritten = 0;
	if (WriteFile(FileHandle, source, (DWORD)bytesToWrite, &BytesWritten, NULL) == FALSE)
	{
		DWORD Error = GetLastError();
		ls_printf("Gotten Error %ld when writing to file %s\n", Error, Path);
	}

	CloseHandle(FileHandle);

	return 0;
}

#endif