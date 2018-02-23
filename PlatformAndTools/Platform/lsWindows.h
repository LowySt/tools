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

struct WindowInfo;

extern "C" s32 ls_printf(const char *fmt, ...);
extern "C" s32 ls_sprintf(char *dest, const char *fmt, ...);
extern "C" void ls_memcpy(void *src, void *dest, size_t size);
extern "C" void ls_zeroMem(void *mem, size_t size);

struct windowsDate
{
	u32 Year;
	u32 Month;
	u32 DayOfWeek;
	u32 Day;
	u32 Hour;
	u32 Minute;
	u32 Second;
	u32 Milliseconds;
};

struct MemoryBlockList
{
	MemoryBlockList *next;
	MemoryBlockList *prev;

	void *blockAddr;
};

struct MemoryBlockHeader
{
	void *next;
	void *prev;

	u32 size;
};

/* This allocation system is similar to the buddy system. It consists 
 * of a flat block of memory allocated at the process startup (Right now
 * the amount allocated is either asked for by the caller, or determined
 * by looking at the system physical memory and availability).
 *
 * The flat memory is then fragmented depending on demand, and the pointers
 * to the fragments are what is returned when asking for memory.
 * To know which blocks are still available, the memory itself is formatted to
 * give this information. Headers at the beginning of each free block act as a
 * double linked list, pointing to previous and next free block, as well as
 * keeping track of the fragment's size.
 * 
 * When allocating a free block, its contents are zeroed (wiping also the header
 * we just mentioned), the previous and next block's links are adjusted (just like
 * when removing an entry form a linked list) and the pointer to that location in
 * memory is then returned to the user.
 * 
 * As of right now the implementation doesn't allow free block merging (in case of
 * excessive fragmentation). That would probably require the addition of a footer.
 *
 * When freeing a pointer, to be able to properly determine the size of the block
 * this pointer originated from, we also keep a double linked list of the allocated
 * blocks, to be able to perform pointer arithmetic between the "pointer to be freed"
 * and everything else in memory, giving me distances between these pointers, hence
 * the dimensions of the blocks.
 *
 * The allocated List is also stored in a flat memory block, allocated at startup
 * time (its dimension is constast for now, 1024 entries). So to be able to remove 
 * and insert entries in the list, without working with allocation/freeing, we always
 * add an entry at the tail of the list, and when removing we move the tail in place
 * of the removed entry, to avoid the fragmentation of the alloc list. The order (while
 * it may be relevant, considering that alloc/free usually come in pairs) should not
 * be critical, that's why the tail is moved.
 */

struct MemoryArena
{
	void *heap;

	MemoryBlockHeader *freeHead;
	MemoryBlockList *allocList;
	MemoryBlockList *allocTail;
	u32 allocListSize;

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

	u64 windows_GetTime();
	windowsDate windows_GetDate(b32 localTime); /*If param is false UTC time is retrieved*/
	void windows_setupWindow(WindowInfo *Input);
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

	//SECURITY_ATTRIBUTES attribs = {sizeof(SECURITY_ATTRIBUTES), NULL, FALSE};

	if ((FileHandle = CreateFileA("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
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

static void windows_removeFromFreeList(MemoryBlockHeader *blockHeader)
{
	((MemoryBlockHeader *)blockHeader->prev)->next = blockHeader->next;
	((MemoryBlockHeader *)blockHeader->next)->prev = blockHeader->prev;

	return;
}

/* TODO: For now I'm arbitrarily setting the allocList size to 1024 possible 
 * entries I think it should be enough. At least for now... */

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
	Memory.allocList = (MemoryBlockList *)VirtualAlloc(0, sizeof(MemoryBlockList)* 65536, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	Memory.allocTail = Memory.allocList;
	Memory.allocListSize = 0;

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

static void windows_addToAllocList(void *p)
{
	/*Useless, I now keep track of the tail.
	MemoryBlockList *curr = Memory.allocList;
	MemoryBlockList *newNode = 0;
	while (curr->next)
	{ curr = curr->next; }
	*/
	MemoryBlockList *tail = Memory.allocTail;
	MemoryBlockList *newNode = 0;

	/* @TODO: @FIXME: REFACTOR NEEDED!
	 * As of right now if I allocate too many things
	 * And I hadn't created enough space in the alloc list
	 * I get fucked. How should I solve that?
	 * Just allocate a lot of memory because who gives a shit?
	 * 
	 * Consider this: 1024 List entries are not enough for stupid small problems.
	 * Also 1024 Entries only occupy 24 KB. Which is super negligible...
	 * Let's bite the bullet for now and give it:
	 * 8192 Entries which occupy 192 KB. Still negligible but should be enough for
	 * Most applications.
	 *
	 * Ok... tried again, and 8192 entries are again not enough... this makes me
	 * Think I should instead make it dynamic, and use a percentage of the main Memory...
	 * Maybe make it parametrized so the user can choose the behaviour?
	 * For now I've again increased it to 16384 (2^14)
	 *
	 * Again not enough (I'm keeping track of this info to understand if this is
	 * a one-time "special" problem, or something that will happen often).
	 * Bump it up to 2^15, 32768
	 *
	 * 32768 worked. I'll keep it like this for now. More testing required!
	 * 32768 Entries -> 24 Bytes * 32768 = 786432 Bytes = 768 KB (Still not that bad)
	 *
	 * Problem presented itself again. I apparently filled 32k entries. Now, the program 
	 * didn't seem to really need that many entries, which means that might be a bug in the
	 * ls_free function not correctly removing entries sometimes??
	 * !!! RECTIFY !!!
	 *
	 * Pretty sure it's not an ls_free bug, but rather, I was using an hashTable which
	 * constantly had to grow. So if there's a bug, it's probably in the hashTable
	 * (Which I wrote quickly and without too many checks... it kinda sucks.)
	 */

	newNode = tail + 1;
	newNode->next = 0;
	newNode->prev = tail;
	tail->next = newNode;

	newNode->blockAddr = p;
	Memory.allocTail = newNode;
	Memory.allocListSize++;
}

static void windows_removeFromAllocList(void *p)
{
	MemoryBlockList *curr = Memory.allocList;

	do
	{
		if (curr->blockAddr == p)
		{
			curr->blockAddr = Memory.allocTail->blockAddr;
			(Memory.allocTail->prev)->next = 0;
			Memory.allocTail = Memory.allocTail - 1;
			Memory.allocListSize--;
			return;
		}
		curr = curr->next;
	} while (curr);

}

void windows_setAllocatorParams(u32 firstAllocSize, u32 minBlockSize, u32 maxBlockSize)
{
	if (firstAllocSize != 0)
	{
		Memory.firstAllocSize = firstAllocSize;
	}

	if (minBlockSize != 0)
	{
		Memory.minBlockSize = minBlockSize;
	}

	if (maxBlockSize != 0)
	{
		Memory.maxBlockSize = maxBlockSize;
	}
}

void *windows_memAlloc(size_t request)
{
	u64 givenMemory = request >= sizeof(MemoryBlockHeader) ? request : sizeof(MemoryBlockHeader);

	if (Memory.heap == 0)
	{
		windows_initMemory();
	}

	if (Memory.freeHead->next == 0)
	{
		windows_halveMemoryBlock(Memory.freeHead);
	}

	MemoryBlockHeader *currHeader = Memory.freeHead;
	MemoryBlockHeader *bestBlock = 0; u32 bestBlockSize = Memory.totalSize;

	b32 found = FALSE;
	do
	{
		if ((currHeader->size < bestBlockSize) && (currHeader->size > givenMemory))
		{
			bestBlock = currHeader; bestBlockSize = currHeader->size;
		}

		if (currHeader->size == givenMemory)
		{
			found = TRUE; break;
		}

		currHeader = (MemoryBlockHeader *)currHeader->next;
	} while (currHeader);

	MemoryBlockHeader *actualBlock;
	if (!found)
	{
		// @TODO: @FIXCRASH
		// The crash happens because bestBlock has the wrong size.
		
		windows_breakMemoryBlock(bestBlock, (u32)givenMemory);
		actualBlock = (MemoryBlockHeader *)bestBlock->next;
	}
	else
	{
		actualBlock = (MemoryBlockHeader *)currHeader;
	}

	windows_removeFromFreeList(actualBlock);
	ls_zeroMem(actualBlock, actualBlock->size);

	windows_addToAllocList((void *)actualBlock);

	return actualBlock;
}

/* NOTE: To be able to determine the size of the block that I'm freeing,
 * I need to know the distance between my pointer, and the pointer of the
 * next block (wether the next block is free or allocated). This means I either
 * need to keep track of the block sizes relative to their base pointer
 * (for example with an hash table) or keep a list of the allocated blocks
 * and walk it after I found the range in which the memory to be freed lives in.
 * By walking the allocated list I can find if there are blocks between my pointer
 * and the next free block, thus giving me the accurate size of the new free block.
 *
 * For now I'm choosing to go the allocated list route. Maybe the hash table is
 * better performance wise. Need to research this more.
 */

void windows_memFree(void *p)
{
	MemoryBlockHeader *currHeader = Memory.freeHead;

	void *prev = 0, *next = 0;
	u32 newBlockSize = 0;

	if (p < currHeader)
	{
		Assert(false);
		int breakHere = 0;
	}

	while ((void *)currHeader < p)
	{
		Assert(currHeader->next != NULL);
		Assert(currHeader->next != p);
		
		if (currHeader->next > p)
		{
			prev = (void *)currHeader;
			next = currHeader->next;

			void *closestAllocBlock = (void *)UINTPTR_MAX;
			MemoryBlockList *curr = Memory.allocList;
			do
			{
				/* The list is not ordered because
				 * When I free pointers I move the tail
				 * I gave up ordering for quick/easy list
				 * entry removal... Are there other quick exits?
				 *
				 * if (curr->blockAddr > next)
				 * { break; }
				 */

				if ((curr->blockAddr > p) && (curr->blockAddr < closestAllocBlock))
				{ closestAllocBlock = curr->blockAddr; }

				curr = curr->next;
			} while (curr);

			if (closestAllocBlock < next)
			{ newBlockSize = (u32)((u8 *)closestAllocBlock - (u8 *)p); }
			else
			{ newBlockSize = (u32)((u8 *)next - (u8 *)p); }
			
			break;
		}

		currHeader = (MemoryBlockHeader *)currHeader->next;
	}

	Assert(prev);
	Assert(next);

	MemoryBlockHeader newHeader = { next, prev, newBlockSize };
	ls_memcpy((void *)&newHeader, p, sizeof(MemoryBlockHeader));

	windows_removeFromAllocList(p);

	//TODO: FIXME: Check for head / last block exceptions
	//TODO: FIXME: Check for head / last block exceptions
	//TODO: FIXME: Check for head / last block exceptions
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
	
	*Dest = (char *)windows_memAlloc(ToRead + 1);

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

u64 windows_GetTime()
{
	/*Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).*/
	FILETIME FileTime = {};
	GetSystemTimeAsFileTime(&FileTime);

	ULARGE_INTEGER Time = {};
	Time.LowPart = FileTime.dwLowDateTime;
	Time.HighPart = FileTime.dwHighDateTime;

	/*Returning microseconds since January 1, 1601 (UTC)*/
	ULONGLONG Result = (Time.QuadPart / 1000);

	return (u64)Result;
}

windowsDate windows_GetDate(b32 localTime)
{
	SYSTEMTIME time = {};

	if (localTime) { GetLocalTime(&time); }
	else { GetSystemTime(&time); }
	
	windowsDate result = {};

	result.Year			= (u32)time.wYear;;
	result.Month		= (u32)time.wMonth;;
	result.DayOfWeek	= (u32)time.wDayOfWeek;;
	result.Day			= (u32)time.wDay;;
	result.Hour			= (u32)time.wHour;;
	result.Minute		= (u32)time.wMinute;;
	result.Second		= (u32)time.wSecond;;
	result.Milliseconds = (u32)time.wMilliseconds;;

	return result;
}

#ifdef I_WANT_GRAPHICS

void windows_setupWindow(WindowInfo *In)
{
	HMODULE hInstance = GetModuleHandleA(0);
	HWND WindowHandle = 0;

	WNDCLASSA WindowClass = { 0 };
	WindowClass.style = In->properties; //CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	WindowClass.lpfnWndProc = In->WindowProc;
	WindowClass.hInstance = hInstance;
	WindowClass.hCursor = 0;
	WindowClass.lpszMenuName = In->menuName; //"Window Menu";
	WindowClass.lpszClassName = In->className; //"Window Class";

	if (!RegisterClassA(&WindowClass))
	{
		DWORD Error = GetLastError();
		ls_printf("When Registering WindowClass in Win32_SetupScreen got error: %d", Error);
	}

	//@NOTE: WindowProc function needs to be fully operational before calling CreateWindow(Ex)(A/W) Because it calls it and uses it's return to create the window.
	//It can be set to return DefWindowProc(A/W) to return all default values and not have to handle them
	if ((WindowHandle = CreateWindowExA(0L, WindowClass.lpszClassName, In->windowName /*"Win 32 Platform"*/, 
									In->style /*WS_OVERLAPPED | WS_VISIBLE*/, CW_USEDEFAULT, CW_USEDEFAULT, In->Width, In->Height, 0, 0, hInstance, 0)) == nullptr)
	{
		DWORD Error = GetLastError();
		ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
	}

	//@TODO Make this error path more @ROBUST. SetCapture actually returns an Handle to the previous Window owning mouse capture
	//If that window wasn't me, it will just post errors without meaning, even if stuff worked.
	if (SetCapture(WindowHandle) == NULL)
	{
		DWORD Error = GetLastError();
		ls_printf("When Setting Mouse Capture in Win32_SetupScreen got error: %d", Error);
	}

	In->WindowHandle = WindowHandle;

	/* @TODO: @NOTE: Should I even do this here ? */
	if (SetCursorPos(In->Width / 2, In->Height / 2) == NULL)
	{
		DWORD Error = GetLastError();
		ls_printf("When Setting Cursor Position in Win32_SetupScreen got error: %d", Error);
	}
}

void windows_setupOpenGLContext(WindowInfo *In)
{
	PIXELFORMATDESCRIPTOR PixelFormat = {};

	PixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	PixelFormat.nVersion = 1;
	PixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PixelFormat.iPixelType = PFD_TYPE_RGBA;
	PixelFormat.cColorBits = 32;	//Colordepth of the framebuffer
	PixelFormat.cDepthBits = 24;	//Number of bits for the depthbuffer
	PixelFormat.cStencilBits = 8;	//Number of bits for the stencilbuffer

	HDC DeviceContext = 0;
	HGLRC RenderingContext = 0;

	DeviceContext = GetDC(In->WindowHandle);
	s32 PixelFormatValue = ChoosePixelFormat(DeviceContext, &PixelFormat);
	SetPixelFormat(DeviceContext, PixelFormatValue, &PixelFormat);

	RenderingContext = wglCreateContext(DeviceContext);
	wglMakeCurrent(DeviceContext, RenderingContext);
	LoadGLFunc(DeviceContext);

	/*Create better context (that allows me to use RenderDoc) with extension function.
	Don't know If I should pass the 3rd param which is a list of tuples <name, value>
	option to pass for the rendering context creation*/
	HGLRC OldContext = RenderingContext;
	RenderingContext = wglCreateContextAttribsARB(DeviceContext, NULL, NULL);
	wglDeleteContext(OldContext);
	wglMakeCurrent(DeviceContext, RenderingContext);

	In->DeviceContext = DeviceContext;
	In->RenderingContext = RenderingContext;

	glEnable(GL_DEPTH_TEST);
}
#endif

#endif