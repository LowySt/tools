#ifndef LS_WINDOWS_H
#define LS_WINDOWS_H

#define LS_PLAT_WINDOWS
#include "win32.h"

#ifndef LS_CRT_H
#include "lsCRT.h"
#endif

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

s32    ls_printf(const char *fmt, ...);
s32    ls_sprintf(char *dest, u32 buffSize, const char *fmt, ...);
void   ls_memcpy(void *src, void *dest, size_t size);
void   ls_zeroMem(void *mem, size_t size);

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

enum RegionTimerPrecision
{
    RT_MILLISECOND,
    RT_HUNDMICRO,
    RT_TENSMICRO,
    RT_MICRO,
    RT_HUNDNANO,
    RT_TENSNANO,
    RT_NANO
};

LARGE_INTEGER __global_QueryPerfFreq;
u64           __global_TimerPrecMulti;
struct RegionTimer
{
    LARGE_INTEGER BeginRegion;
    LARGE_INTEGER EndRegion;
};

#define RegionTimerBegin(T) QueryPerformanceCounter(&T.BeginRegion)
#define RegionTimerEnd(T)   QueryPerformanceCounter(&T.EndRegion)
#define RegionTimerGet(T)   \
(((T.EndRegion.QuadPart - T.BeginRegion.QuadPart)*__global_TimerPrecMulti) / __global_QueryPerfFreq.QuadPart)

#ifdef _DEBUG
#define DebugTimerBegin(T) QueryPerformanceCounter(&T.BeginRegion)
#define DebugTimerEnd(T)   QueryPerformanceCounter(&T.EndRegion)
#define DebugTimerGet(T)   \
(((T.EndRegion.QuadPart - T.BeginRegion.QuadPart)*__global_TimerPrecMulti) / __global_QueryPerfFreq.QuadPart)
#else
#define DebugTimerBegin(T)
#define DebugTimerEnd(T)
#define DebugTimerGet(T) 0
#endif


struct CycleCounter
{
    u64 beginCycle;
    u64 endCycle;
};

#define CycleCounterBegin(C) (C.beginCycle = __rdtsc())
#define CycleCounterEnd(C)   (C.endCycle   = __rdtsc())
#define CycleCounterGet(C)   (C.endCycle - C.beginCycle)

#ifdef _DEBUG
#define DebugCounterBegin(C) (C.beginCycle = __rdtsc())
#define DebugCounterEnd(C)   (C.endCycle   = __rdtsc())
#define DebugCounterGet(C)   (C.endCycle - C.beginCycle)
#else
#define DebugCounterBegin(C)
#define DebugCounterEnd(C)
#define DebugCounterGet(C) 0
#endif


//NOTE: Memory System
#define MAX_ARENA_NUM 256

struct MemoryList
{
    MemoryList *next;
    MemoryList *prev;
    
    u32 relativePtr; 
    u32 sliceSize;
};

struct MemoryBlock
{
    MemoryBlock *next;
    MemoryBlock *prev;
    
    MemoryList  *busy;
    MemoryList  *bTail;
    MemoryList  *free;
    MemoryList  *fTail;
    
    u32 blockSize;
    
    u16 curSlices;
    u16 maxSlices;
};

struct InternalArena
{
    void *data;
    u64 capacity;
    u64 used;
    
    u32 id;
};

struct MemoryArena
{
    MemoryBlock *head;
    MemoryBlock *last;
    u32 numOfBlocks;
    
    b32 isUsingArena;
    u32 currArenaId;
    
    u32 totalBytesBusy;
    u32 totalBytesVirtualAlloc; //NOTETODO: This is ignoring the Arena System!!!
    
    /*Arenas System*/
    InternalArena arenas[MAX_ARENA_NUM];
    b32           used[MAX_ARENA_NUM];
};

extern "C"
{
	void windows_assert(const char *msg, const char *file, s32 line);
	void windows_setAllocatorParams(u64 firstAllocSize, u64 minBlockSize, u64 maxBlockSize);
	void *windows_memAlloc(size_t size);
	void windows_memFree(void *ptr);
    
    void *windows_createArena(u64 arenaSize, u32 *id);
    void windows_useArena(u32 id);
    void windows_stopArena();
    void windows_clearArena(u32 id);
    void windows_destroyArena(u32 id);
    
	u64 windows_ReadConsole(char *Dest, u32 bytesToRead);
	u64 windows_WriteConsole(char *buff, u32 bytesToWrite);
	u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead);
    u64 windows_ReadFileByOffset(char *Path, char **Dest, u32 offset, u32 bytesToRead);
	u64 windows_WriteFile(char *Path, char *source, u32 bytesToWrite, b32 append);
    b32 windows_fileExists(char *AbsPath);
    u32 windows_countFilesInDir(char *Dir, u32 dirLen);
    u32 windows_countFilesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen);
    u32 windows_countFilesInDirRecursive(char *Dir, u32 dirLen);
    
    void windows_getFileNamesInDir(char *Dir, u32 dirLen, char ***names, u32 *howManyNames, u32 **namesLen);
    void windows_getFileNamesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen,
                                        char ***names, u32 *howManyNames, u32 **namesLen);
    void windows_getFileNamesInDirRecursive(char *Dir, u32 dirLen, char ***names,
                                            u32 *howManyNames, u32 **namesLen);
    void windows_getFilePathsInDirRecursive(char *Dir, u32 dirLen, char ***names,
                                            u32 *howManyNames, u32 **namesLen);
    
    u32 windows_getFullPathName(char *fileName, u32 outBufferSize, char *outBuffer);
    
    u64 windows_GetWindowsTimeInMicrosec();
	u64 windows_GetWindowsTimeIn100Nanosec();
    u32 windows_GetUnix32Time();
    u64 windows_GetUnix64Time();
	windowsDate windows_GetDate(b32 localTime); /*If param is false UTC time is retrieved*/
    
    u32 windows_GetClipboard(void *buff, u32 maxUTF32Len);
    u32 windows_SetClipboard(void *data, u32 len);
    
	void windows_setupWindow(WindowInfo *Input);
    
    void windows_initRegionTimer(RegionTimerPrecision p = RT_MILLISECOND);
    void windows_sleep(u64 milliseconds);
};

#endif // LS_WINDOWS_H

#ifdef LS_WINDOWS_IMPLEMENTATION

u64 windows_ReadConsole(char *Dest, u32 bytesToRead)
{
	DWORD Error = 0;
    HANDLE FileHandle = GetStdHandle(STD_INPUT_HANDLE);
    if(FileHandle == INVALID_HANDLE_VALUE)
    {
        Error = GetLastError();
		OutputDebugStringA("When creating a console handle got error\n");
    }
    
#if 0
	HANDLE FileHandle = 0;
	if ((FileHandle = CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		ls_printf("When creating a file handle got error: %ld\n", Error);
	}
#endif
    
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
    //NOTE: Haven't created the handle myself, so can't destroy it!
#if 0
	if (CloseHandle(FileHandle) == FALSE)
	{ OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n"); }
#endif
	return BytesRead;
}

u64 windows_WriteConsole(char *buff, u32 bytesToWrite)
{
	DWORD Error = 0;
	HANDLE FileHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(FileHandle == INVALID_HANDLE_VALUE)
    {
        Error = GetLastError();
		OutputDebugStringA("When creating a console handle got error\n");
    }
    
#if 0
	//SECURITY_ATTRIBUTES attribs = {sizeof(SECURITY_ATTRIBUTES), NULL, FALSE};
    
	if ((FileHandle = CreateFileA("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		OutputDebugStringA("When creating a file handle got error\n");
	}
#endif
    
	DWORD BytesWritten = 0;
	if (!WriteFile(FileHandle, buff, bytesToWrite, &BytesWritten, NULL))
	{
		Error = GetLastError();
		OutputDebugStringA("When writing to Console Output got error\n");
	}
    
    //NOTE: Haven't created the handle myself, so can't destroy it!
#if 0
	if (!CloseHandle(FileHandle))
	{
		Error = GetLastError();
		OutputDebugStringA("When closing Console Output Handle got error\n");
	}
#endif
	return BytesWritten;
}

void windows_assert(const char *msg, const char *file, s32 line)
{
	char buff[512] = { 0 };
	s32 written = ls_sprintf(buff, 512, "In file %s, line %d, Assert %s fired\n", file, line, msg);
	windows_WriteConsole(buff, (u32)written);
}

// --------------------- //
// --- MEMORY SYSTEM --- //
// --------------------- //

#if !defined (__GNUG__) && !defined (__clang__)
thread_local MemoryArena Memory = {};
#else
__thread MemoryArena Memory = {};
#endif

void windows_InitMemory(size_t size)
{
    SYSTEM_INFO sysInfo = {};
    GetSystemInfo(&sysInfo);
    
    DWORD pageSize = sysInfo.dwPageSize;
    
    //NOTE: Either make a block pageSize (to subdivide) or if more is requested
    // just give a block exactly as big as requested, and it's all yours.
    u64 allocationSize = pageSize;
    
    //NOTE: Max Slices is hardcoded to be a pretty small number for large allocations @MaxSlicesComment
    //      Because I've found that often these allocations are things we want to keep around
    //      Like Asset Files being loaded from disk. These will never be sliced, and will never be freed.
    u32 maxSlices = ((allocationSize - sizeof(MemoryBlock)) / 128);
    if(size > (pageSize - sizeof(MemoryBlock)))
    { 
        allocationSize = size + sizeof(MemoryBlock);
        maxSlices = 1;
    }
    
    void *mem = VirtualAlloc(NULL, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    //NOTETODO: Useful for debugging, could be wrapped in a _DEBUG #ifdef @DebugOnlyData
    Memory.totalBytesVirtualAlloc += allocationSize;
    
    AssertMsg(mem, "VirtualAlloc of block failed\n");
    
    MemoryBlock header = {};
    header.next = NULL;
    header.prev = NULL;
    
    //NOTE: Block size of a page will be reported as 4040 instead of 4096 because of this.
    header.blockSize = (allocationSize - sizeof(MemoryBlock));
    header.curSlices = 1;
    
    header.maxSlices = maxSlices;
    
    header.busy = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.bTail = header.busy;
    
    header.free = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.fTail = header.free;
    
    //NOTETODO: @DebugOnlyData
    Memory.totalBytesVirtualAlloc += maxSlices*sizeof(MemoryList)*2;
    
    AssertMsg(header.busy, "VirtualAlloc of busy list failed\n");
    AssertMsg(header.free, "VirtualAlloc of free list failed\n");
    
    //NOTE: Is u64 -> u32 allocation size a problem? Shouldn't be. Why is allocation Size u64?
    header.free[0] = { 0, 0, sizeof(MemoryBlock), (u32)(allocationSize - sizeof(MemoryBlock))};
    
    ls_memcpy(&header, mem, sizeof(MemoryBlock));
    Memory.head = (MemoryBlock *)mem;
    Memory.last = (MemoryBlock *)mem;
    Memory.numOfBlocks = 1;
    return;
}

//NOTE: Copy Pasta from InitMemory because I'm too lazy to merge them.
MemoryBlock *windows_memAddBlock(size_t size)
{
    SYSTEM_INFO sysInfo = {};
    GetSystemInfo(&sysInfo);
    
    DWORD pageSize = sysInfo.dwPageSize;
    
    u64 allocationSize = pageSize;
    
    //NOTE: @MaxSlicesComment
    u32 maxSlices = ((allocationSize - sizeof(MemoryBlock)) / 128);
    if(size > (pageSize - sizeof(MemoryBlock)))
    { 
        allocationSize = size + sizeof(MemoryBlock);
        maxSlices = 1;
    }
    
    if(size > (pageSize - sizeof(MemoryBlock)))
    { allocationSize = size + sizeof(MemoryBlock); }
    
    void *mem = VirtualAlloc(NULL, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    //NOTETODO: @DebugOnlyData
    Memory.totalBytesVirtualAlloc += allocationSize;
    
    AssertMsg(mem, "VirtualAlloc of block failed\n");
    
    MemoryBlock *last = Memory.last;
    
    MemoryBlock header = {};
    header.next = NULL;
    header.prev = last;
    last->next = (MemoryBlock *)mem;
    
    Memory.last = (MemoryBlock *)mem;
    
    header.blockSize = (allocationSize - sizeof(MemoryBlock));
    header.curSlices = 1;
    
    header.maxSlices = maxSlices;
    
    header.busy = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.bTail = header.busy;
    
    header.free = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.fTail = header.free;
    
    //NOTETODO: @DebugOnlyData
    Memory.totalBytesVirtualAlloc += maxSlices*sizeof(MemoryList)*2;
    
    AssertMsg(header.busy, "VirtualAlloc of busy list failed\n");
    AssertMsg(header.free, "VirtualAlloc of free list failed\n");
    
    //NOTE: Is u64 -> u32 allocation size a problem? Shouldn't be. Why is allocation Size u64?
    header.free[0] = { 0, 0, sizeof(MemoryBlock), (u32)(allocationSize - sizeof(MemoryBlock))};
    
    ls_memcpy(&header, mem, sizeof(MemoryBlock));
    Memory.numOfBlocks += 1;
    
    return (MemoryBlock *)mem;
}

void windows_addToBusy(MemoryBlock *b, MemoryList *slice)
{
    MemoryList *newPos = (MemoryList *)((u8 *)b->bTail + sizeof(MemoryList));
    if(b->busy->relativePtr == 0)
    {
        newPos = b->busy; slice->prev = 0;
        ls_memcpy(slice, newPos, sizeof(MemoryList));
        return;
    }
    
    ls_memcpy(slice, newPos, sizeof(MemoryList));
    b->bTail->next = newPos;
    b->bTail       = newPos;
    return;
}

void *windows_sliceBlockIfNeeded(MemoryBlock *b, MemoryList *slice, size_t size)
{
    AssertMsg(slice->sliceSize >= size, "The passed slice can't contain the requested memory.\n");
    
    void *Result = (void *)((u8 *)b + slice->relativePtr);
    
    MemoryList newBusy = {0, b->bTail, slice->relativePtr, (u32)size};
    windows_addToBusy(b, &newBusy);
    
    if(slice->sliceSize == size)
    {
        if(b->fTail == b->free) { *b->free = { 0, 0, 0, 0}; return Result; }
        
        MemoryList *freeTail = b->fTail;
        slice->relativePtr = freeTail->relativePtr;
        slice->sliceSize   = freeTail->sliceSize;
        freeTail->prev->next = 0;
        b->fTail             = freeTail->prev;
        
        return Result;
    }
    
    slice->relativePtr = slice->relativePtr + size;
    slice->sliceSize   = slice->sliceSize - size;
    
    b->curSlices += 1;
    
    return Result;
}

void *windows_memAlloc(size_t size)
{
    if(size == 0) { return 0x0; }
    
    /*Arenas*/
    if(Memory.isUsingArena == TRUE)
    {
        InternalArena *Ar = &Memory.arenas[Memory.currArenaId];
        
        AssertMsg(Ar->id == Memory.currArenaId, "The arena ID doesn't match the Memory currentArenaID.\n");
        AssertMsg(Ar->used + size <= Ar->capacity, "Arena is out of space.\n");
        
        u8 *ResultPtr = (u8 *)Ar->data + Ar->used;
        Ar->used += size;
        
        return (void *)ResultPtr;
    }
    
    
    /*Blocks*/
    if(Memory.head == NULL) { windows_InitMemory(size); }
    
    MemoryBlock *curr = Memory.head;
    MemoryList   bestTmp = { 0, 0, 0, UINT32_MAX };
    MemoryList  *best = &bestTmp;
    for(u32 i = 0; i < Memory.numOfBlocks; i++)
    {
        //TODO: Add Merging
        //if(curr->curSlices == curr->maxSlices) {};
        //TODO: Add Merging
        
        //NOTETODO: 24/08/2020 Gotten into a bug, I think that maxSlices
        // Shouldn't be ignored, as it is right now???
        // So gonna skip any block that has reached curSlices == maxSlices
        //
        //NOTETODO: 26/12/2021 If a block has reached maxSlices, but there are free slices
        // it won't use them. Kinda stupid design. It should look to see if there are free
        // slices, rather than just if the block has been sliced max number of times!!
        if(curr->curSlices == curr->maxSlices) { curr = curr->next; continue; }
        
        
        MemoryList *free = curr->free;
        Assert(free != 0x0); //NOTE: What? Why can't free be == 0 here????
        
        do
        {
            u32 sliceSize = free->sliceSize;
            if((sliceSize >= size) && (sliceSize < best->sliceSize))
            {
                best = free;
            }
            free = free->next;
        } while(free != 0);
        
        if(best->relativePtr != 0) { break; }
        curr = curr->next;
    }
    
    MemoryBlock *newBlock = 0;
    if(best->relativePtr == 0)
    {
        newBlock = windows_memAddBlock(size);
        void *beginOfSliceData = windows_sliceBlockIfNeeded(newBlock, newBlock->free, size);
        return beginOfSliceData;
    }
    
    void *beginOfSliceData = windows_sliceBlockIfNeeded(curr, best, size);
    
    //NOTE: Logging the memory usage.
    Memory.totalBytesBusy += size;
    
    //TODONOTE: ZeroMem the slice??
    // 14 May 2021. I found a single case in which I got returned a pointer with old data inside.
    // That happened because a string had to grow before.
    // reallocations will cause Memory blocks to have previous data written in them.
    // First Allocations will be zero by default, but what about others?
    // I Should probably clean on free, not on alloc. But I dont know...
    // What should I do?
    ls_zeroMem(beginOfSliceData, size);
    return beginOfSliceData;
}

void windows_freeSlice(MemoryBlock *b, MemoryList *slice)
{
    //NOTETODO: Check for strange head/tail removing/adding cases
    
    //NOTE: Add slice to Free List
    MemoryList newSlice = { 0, b->fTail, slice->relativePtr, slice->sliceSize };
    void *slicePos = (void *)((u8 *)b->fTail + sizeof(MemoryList));
    
    //NOTE: If the Free List is empty:
    if((b->free == b->fTail) && b->free->relativePtr == 0)
    {
        newSlice.prev = 0; slicePos = b->free;
        ls_memcpy(&newSlice, slicePos, sizeof(MemoryList));
    }
    else
    {
        ls_memcpy(&newSlice, slicePos, sizeof(MemoryList));
        
        b->fTail->next = (MemoryList *)slicePos;
        b->fTail = (MemoryList *)slicePos;
    }
    
    //NOTE: Remove slice from Busy List
    if(b->bTail == b->busy) { *b->busy = {0, 0, 0, 0}; return; }
    
    MemoryList *busyTail = b->bTail;
    slice->relativePtr = busyTail->relativePtr;
    slice->sliceSize   = busyTail->sliceSize;
    busyTail->prev->next = 0;
    b->bTail             = busyTail->prev;
}

void windows_memFree(void *ptr)
{
    //NOTE:TODO: Apparently C free() is a no-op when ptr is NULL.
    //AssertMsg(ptr, "Pointer was NULL\n");
    if(!ptr) { return; }
    
    /*Arenas*/
    if(Memory.isUsingArena == TRUE) { return; }
    
    
    /*Blocks*/
    
    b32 found = FALSE;
    
    MemoryBlock *curr = Memory.head;
    for(u32 i = 0; i < Memory.numOfBlocks; i++)
    {
        u64 blockStart = (u64)((u8 *)curr + sizeof(MemoryBlock));
        u64 blockEnd   = blockStart + curr->blockSize;
        
        if(((u64)ptr >= blockStart) && ((u64)ptr < blockEnd))
        { found = TRUE; break; }
        
        curr = curr->next;
    }
    
    //NOTE: Trying to free something that wasn't an allocated pointer.
    //      Should this even crash, or should I just silently exit?
    AssertMsg(found == TRUE, "Trying to free something that wasn't an allocated pointer.\n");
    
    found = FALSE;
    u32 relativePtr = (u64)ptr - (u64)curr;
    MemoryList *slice = curr->busy;
    do
    {
        if(slice->relativePtr == relativePtr)
        { found = TRUE; break; }
        
        slice = slice->next;
    } while(slice != NULL);
    
    //NOTE: Trying to free a non busy pointer. Either a DOUBLE FREE,
    //      Or for some reason a busy pointer wasn't put in the busy list?
    AssertMsg(found == TRUE, "Trying to free a non-busy pointer.\n\tEither a double free or for some reason a busy"
              "pointer wasn't punt in the busy list?\n");
    
    //TODO: ZeroMem the slice??
    windows_freeSlice(curr, slice);
    
    //NOTE: Logging the memory usage.
    Memory.totalBytesBusy -= slice->sliceSize;
    
    return;
}



/*ARENAS*/
void *windows_createArena(u64 arenaSize, u32 *id)
{
    b32 found = FALSE;
    u32 arId = 0;
    
    for(u32 i = 0; i < MAX_ARENA_NUM; i++) { if(Memory.used[i] == FALSE) { found = TRUE; arId = i; break; } }
    if(!found) { Assert(!"No More Arenas available"); }
    
    InternalArena *Ar = &Memory.arenas[arId];
    
    Ar->data = VirtualAlloc(NULL, arenaSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    AssertMsg(Ar->data, "VirtualAlloc failed.\n");
    
    Ar->capacity = arenaSize;
    Ar->used     = 0;
    Ar->id       = arId;
    Memory.used[arId] = TRUE;
    
    *id = arId;
    return Ar->data;
}

void windows_useArena(u32 id)
{
    AssertMsg(Memory.arenas[id].data != 0x0, "Arena at chosen ID is not inizialied. Data is NULL.\n");
    
    Memory.isUsingArena = TRUE;
    Memory.currArenaId  = id;
    
    return;
}

void windows_stopArena()
{
    AssertMsg(Memory.isUsingArena == TRUE, "Arenas were already not being used. Double stopArena() call?\n");
    Memory.isUsingArena = FALSE;
    return;
}

void windows_clearArena(u32 id)
{
    AssertMsg(Memory.used[id] == TRUE, "The given ID refers to an Arena which was not being used.\n");
    Memory.arenas[id].used = 0;
    return;
}

void windows_destroyArena(u32 id)
{
    AssertMsg(Memory.used[id] == TRUE, "The given ID refers to an Arena which was not being used.\n");
    Assert(!(Memory.isUsingArena == TRUE && Memory.currArenaId == id)); //NOTE: Thinks this assertion is correct?
    AssertMsg(Memory.arenas[id].data != 0x0, "Trying to destroy arena with initialized data.\n");
    
    BOOL Error = VirtualFree(Memory.arenas[id].data, 0, MEM_RELEASE);
    AssertMsg(Error != 0, "Virtual Free failed.\n");
    
    Memory.arenas[id].data = 0x0;
    Memory.arenas[id].capacity = 0;
    Memory.arenas[id].used = 0;
    Memory.arenas[id].id = 0;
    
    Memory.used[id] = FALSE;
    
    return;
}





/*IO*/

VOID CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
    lpOverlapped->Offset = dwErrorCode;
    lpOverlapped->Offset = dwNumberOfBytesTransfered;
    return;
}

u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead)
{
    char errorBuff[256] = {};
    DWORD Error = 0;
    HANDLE FileHandle = 0;
    LARGE_INTEGER FileSize = {};
    
    if ((FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        Error = GetLastError();
        ls_sprintf(errorBuff, 256, "When creating a file handle in path '%cs' got error: %d\n", Path, Error);
        LogMsg(FALSE, errorBuff);
        return 0;
    }
    
    u32 ToRead;
    if (bytesToRead == 0)
    {
        if (GetFileSizeEx(FileHandle, &FileSize) == 0)
        {
            Error = GetLastError();
            ls_sprintf(errorBuff, 256, "When retrieving file size in path %cs got error: %d\n", Path, Error);
            LogMsg(FALSE, errorBuff);
            return 0;
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
        ls_sprintf(errorBuff, 256, "When reading file %cs got error: %d\n", Path, Error);
        LogMsg(FALSE, errorBuff);
        return 0;
    }
    else
    {
        if (BytesRead != ToRead)
        { 
            ls_sprintf(errorBuff, 256, "Bytes read (%d) in file %cs don't equal file size (%d)\n", 
                       BytesRead, Path, ToRead);
            LogMsg(FALSE, errorBuff);
            return 0;
        }
    }
    
    if (CloseHandle(FileHandle) == FALSE)
    { OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n"); }
    
    return BytesRead;
}

//NOTE: THIS ls_free is super annoying. ReadFileByOffset unfortunately
//allocates the buffer, because it has to deal with variable file dim...
//And checking for nullptr is not secure because C doesn't initialize
//null by default. But Really annoying
u64 windows_ReadFileByOffset(char *Path, char **Dest, u64 offset, u32 bytesToRead)
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
    if (GetFileSizeEx(FileHandle, &FileSize) == 0)
    {
        Error = GetLastError();
        ls_printf("When getting file size got error: %ld\n", Error);
    }
    
    if((bytesToRead == 0) || (bytesToRead > FileSize.LowPart))
    { ToRead = FileSize.LowPart; }
    else if(bytesToRead < FileSize.LowPart)
    { ToRead = bytesToRead; }
    
    *Dest = (char *)windows_memAlloc(ToRead + 1);
    
    OVERLAPPED overlData= {};
    overlData.Offset     = (u32)offset;
    overlData.OffsetHigh = (u32)(offset >> 32);
    
    DWORD BytesRead = 0;
    DWORD ErrorCode = 0;
    if (ReadFileEx(FileHandle, *Dest, ToRead, &overlData, FileIOCompletionRoutine) == FALSE)
    {
        /*Is this right?*/
        ErrorCode = overlData.Internal;
        
        Error = GetLastError();
        ls_printf("When Reading contents of a file got error: %ld\n", Error);
    }
    else
    {
        BytesRead = overlData.InternalHigh;
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
    
    /* How do we open a file always, but append if we don't want to re-write it completely? */
    
    u32 fileAccessRights = append ? FILE_APPEND_DATA : GENERIC_WRITE;
    
    u32 creationDisposition = append ? OPEN_ALWAYS : TRUNCATE_EXISTING;
    
    if ((FileHandle = CreateFileA(Path, fileAccessRights, FILE_SHARE_WRITE, NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        DWORD Error = GetLastError();
        
        if (Error == ERROR_FILE_NOT_FOUND)
        {
            if ((FileHandle = CreateFileA(Path, fileAccessRights, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
            {
                DWORD Error = GetLastError();
                ls_printf("Gotten Error %ld when creating file handle to file: %cs\n", Error, Path);
            }
        }
        else
        {
            ls_printf("Gotten Error %ld when creating file handle to file: %cs\n", Error, Path);
        }
    }
    
    DWORD BytesWritten = 0;
    if (WriteFile(FileHandle, source, (DWORD)bytesToWrite, &BytesWritten, NULL) == FALSE)
    {
        DWORD Error = GetLastError();
        ls_printf("Gotten Error %ld when writing to file %cs\n", Error, Path);
    }
    
    CloseHandle(FileHandle);
    
    return 0;
}

b32 windows_fileExists(char *AbsPath)
{
    WIN32_FIND_DATAA FindFileData;
    HANDLE handle = FindFirstFileA(AbsPath, &FindFileData);
    
    b32 found = FALSE;
    if(handle != INVALID_HANDLE_VALUE) { found = TRUE; }
    
    if(found) { FindClose(handle); }
    return found;
}

u32 windows_countFilesInDir(char *Dir, u32 dirLen)
{
    u32 Result = 0;
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + 3;
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - 3] = '\\';
    allFiles[totalLen - 2] = '*';
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return 0;}
    
    BOOL more = TRUE;
    while(more)
    {
        b32 isDir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if(!isDir) { Result++; }
        
        more = FindNextFileA(hFile, &findData);
    }
    
    FindClose(hFile);
    
    return Result;
}

u32 windows_countFilesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen)
{
    u32 Result = 0;
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + extLen + 5;
    
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - extLen - 5] = '\\';
    allFiles[totalLen - extLen - 4] = '*';
    allFiles[totalLen - extLen - 3] = '.';
    ls_memcpy(ext, allFiles + (totalLen - extLen - 2), extLen);
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return 0;}
    
    BOOL more = TRUE;
    while(more)
    {
        Result++;
        more = FindNextFileA(hFile, &findData);
    }
    
    FindClose(hFile);
    
    // NOTE: Removing current and previous directory!
    return (Result - 2);
}

u32 windows_countFilesInDirRecursive(char *Dir, u32 dirLen)
{
    u32 Result = 0;
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + 3;
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - 3] = '\\';
    allFiles[totalLen - 2] = '*';
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return 0;}
    
    BOOL more = TRUE;
    while(more)
    {
        if(findData.cFileName[0] == '.' ||
           (findData.cFileName[0] == '.' && findData.cFileName[1] == '.'))
        { more = FindNextFileA(hFile, &findData); continue; }
        
        b32 isDir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if(isDir) {
            
            u32 newDirLen = ls_len(findData.cFileName);
            char newDir[256] = {};
            ls_memcpy(Dir, newDir, dirLen);
            newDir[dirLen] = '\\';
            ls_memcpy(findData.cFileName, newDir+dirLen+1, newDirLen);
            newDir[dirLen+newDirLen+1] = 0;
            
            Result += windows_countFilesInDirRecursive(newDir, dirLen+newDirLen+1);
        }
        else
        {
            Result++;
        }
        
        more = FindNextFileA(hFile, &findData);
    }
    
    FindClose(hFile);
    
    return Result;
}

void windows_getFileNamesInDir(char *Dir, u32 dirLen, char ***names,
                               u32 *howManyNames, u32 **namesLen)
{
    *howManyNames = windows_countFilesInDir(Dir, dirLen);
    if(*howManyNames == 0) { return; }
    
    (*names)    = (char **)windows_memAlloc(sizeof(char *)*(*howManyNames));
    (*namesLen) = (u32 *)windows_memAlloc(sizeof(u32)*(*howManyNames));
    
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + 3;
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - 3] = '\\';
    allFiles[totalLen - 2] = '*';
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return;}
    
    u32 nameLen = 0;
    u32 it = 0;
    BOOL more = TRUE;
    do
    {
        if(findData.cFileName[0] == '.' ||
           (findData.cFileName[0] == '.' && findData.cFileName[1] == '.'))
        { more = FindNextFileA(hFile, &findData); continue; }
        
        u32 hasDirFlag = findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        u32 hasSysFlag = findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
        if(hasDirFlag != 0 || hasSysFlag != 0)
        { more = FindNextFileA(hFile, &findData); continue; }
        
        (*namesLen)[it] = ls_len(findData.cFileName);
        (*names)[it] = (char *)ls_alloc(sizeof(char)*((*namesLen)[it]));
        
        ls_memcpy(findData.cFileName, (*names)[it], (*namesLen)[it]);
        
        it++;
        
        more = FindNextFileA(hFile, &findData);
    }
    while(more);
    
    FindClose(hFile);
}

void windows_getFileNamesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen,
                                    char ***names, u32 *howManyNames, u32 **namesLen)
{
    *howManyNames = windows_countFilesInDirByExt(Dir, dirLen, ext, extLen);
    
    (*names) = (char **)windows_memAlloc(sizeof(char *)*(*howManyNames));
    (*namesLen) = (u32 *)windows_memAlloc(sizeof(u32)*(*howManyNames));
    
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + extLen + 5;
    
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - extLen - 5] = '\\';
    allFiles[totalLen - extLen - 4] = '*';
    allFiles[totalLen - extLen - 3] = '.';
    ls_memcpy(ext, allFiles + (totalLen - extLen - 2), extLen);
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return;}
    
    u32 nameLen = 0;
    u32 it = 0;
    BOOL more = TRUE;
    do
    {
        (*namesLen)[it] = ls_len(findData.cFileName);
        (*names)[it] = (char *)ls_alloc(sizeof(char)*((*namesLen)[it]));
        
        ls_memcpy(findData.cFileName, &(*names)[it], (*namesLen)[it]);
        
        it++;
        
        more = FindNextFileA(hFile, &findData);
    }
    while(more);
    
    FindClose(hFile);
}

void windows_getFileNamesInDirRecursive(char *Dir, u32 dirLen, char ***names,
                                        u32 *howManyNames, u32 **namesLen)
{
    *howManyNames = windows_countFilesInDirRecursive(Dir, dirLen);
    if(*howManyNames == 0) { return; }
    
    (*names)    = (char **)windows_memAlloc(sizeof(char *)*(*howManyNames));
    (*namesLen) = (u32 *)windows_memAlloc(sizeof(u32)*(*howManyNames));
    
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + 3;
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - 3] = '\\';
    allFiles[totalLen - 2] = '*';
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return;}
    
    u32 nameLen = 0;
    u32 it = 0;
    BOOL more = TRUE;
    do
    {
        if(findData.cFileName[0] == '.' ||
           (findData.cFileName[0] == '.' && findData.cFileName[1] == '.'))
        { more = FindNextFileA(hFile, &findData); continue; }
        
        u32 isDir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if(isDir)
        {
            u32 newDirLen = ls_len(findData.cFileName);
            char newDir[256] = {};
            ls_memcpy(Dir, newDir, dirLen);
            newDir[dirLen] = '\\';
            ls_memcpy(findData.cFileName, newDir+dirLen+1, newDirLen);
            newDir[dirLen+newDirLen+1] = 0;
            
            char **subNames = 0;
            u32 subNameCount = 0;
            u32 *subNamesLen = 0;
            windows_getFileNamesInDirRecursive(newDir, dirLen+newDirLen+1, &subNames, &subNameCount, &subNamesLen);
            
            for(u32 i = 0; i < subNameCount; i++)
            {
                (*namesLen)[it] = subNamesLen[i];
                (*names)[it] = (char *)ls_alloc(sizeof(char)*subNamesLen[i]);
                
                ls_memcpy(subNames[i], (*names)[it], subNamesLen[i]);
                
                it++;
            }
            
            more = FindNextFileA(hFile, &findData);
            continue;
        }
        
        (*namesLen)[it] = ls_len(findData.cFileName);
        (*names)[it] = (char *)ls_alloc(sizeof(char)*((*namesLen)[it]));
        
        ls_memcpy(findData.cFileName, (*names)[it], (*namesLen)[it]);
        
        it++;
        
        more = FindNextFileA(hFile, &findData);
    }
    while(more);
    
    FindClose(hFile);
}

void windows_getFilePathsInDirRecursive(char *Dir, u32 dirLen, char ***names,
                                        u32 *howManyNames, u32 **namesLen)
{
    *howManyNames = windows_countFilesInDirRecursive(Dir, dirLen);
    if(*howManyNames == 0) { return; }
    
    (*names)    = (char **)windows_memAlloc(sizeof(char *)*(*howManyNames));
    (*namesLen) = (u32 *)windows_memAlloc(sizeof(u32)*(*howManyNames));
    
    WIN32_FIND_DATAA findData = {};
    
    u32 totalLen = dirLen + 3;
    char *allFiles = (char *)windows_memAlloc(sizeof(char)*totalLen);
    ls_memcpy(Dir, allFiles, dirLen);
    allFiles[totalLen - 3] = '\\';
    allFiles[totalLen - 2] = '*';
    allFiles[totalLen - 1] = 0;
    
    HANDLE hFile = FindFirstFileA(allFiles, &findData);
    if(hFile == INVALID_HANDLE_VALUE) {return;}
    
    u32 nameLen = 0;
    u32 it = 0;
    BOOL more = TRUE;
    do
    {
        if(findData.cFileName[0] == '.' ||
           (findData.cFileName[0] == '.' && findData.cFileName[1] == '.'))
        { more = FindNextFileA(hFile, &findData); continue; }
        
        u32 isDir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if(isDir)
        {
            u32 newDirLen = ls_len(findData.cFileName);
            char newDir[256] = {};
            ls_memcpy(Dir, newDir, dirLen);
            newDir[dirLen] = '\\';
            ls_memcpy(findData.cFileName, newDir+dirLen+1, newDirLen);
            newDir[dirLen+newDirLen+1] = 0;
            
            char **subNames = 0;
            u32 subNameCount = 0;
            u32 *subNamesLen = 0;
            windows_getFilePathsInDirRecursive(newDir, dirLen+newDirLen+1, &subNames, &subNameCount, &subNamesLen);
            
            for(u32 i = 0; i < subNameCount; i++)
            {
                (*namesLen)[it] = subNamesLen[i];
                (*names)[it] = (char *)ls_alloc(sizeof(char)*subNamesLen[i]);
                
                ls_memcpy(subNames[i], (*names)[it], subNamesLen[i]);
                
                it++;
            }
            
            more = FindNextFileA(hFile, &findData);
            continue;
        }
        
        u32 fullNameLen = ls_len(findData.cFileName);
        char fullName[256] = {};
        ls_memcpy(Dir, fullName, dirLen);
        fullName[dirLen] = '\\';
        ls_memcpy(findData.cFileName, fullName+dirLen+1, fullNameLen);
        fullName[dirLen+fullNameLen+1] = 0;
        
        (*namesLen)[it] = fullNameLen+dirLen+1;
        (*names)[it] = (char *)ls_alloc(sizeof(char)*(fullNameLen+dirLen+1));
        
        ls_memcpy(fullName, (*names)[it], fullNameLen+dirLen+1);
        
        it++;
        
        more = FindNextFileA(hFile, &findData);
    }
    while(more);
    
    FindClose(hFile);
}

u32 windows_getFullPathName(char *fileName, u32 outBufferSize, char *outBuffer)
{ return GetFullPathNameA(fileName, outBufferSize, outBuffer, 0); }

u64 windows_GetWindowsTimeInMicrosec()
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

u64 windows_GetWindowsTimeIn100Nanosec()
{
    /*Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).*/
    FILETIME FileTime = {};
    GetSystemTimeAsFileTime(&FileTime);
    
    ULARGE_INTEGER Time = {};
    Time.LowPart = FileTime.dwLowDateTime;
    Time.HighPart = FileTime.dwHighDateTime;
    
    /*Returning microseconds since January 1, 1601 (UTC)*/
    ULONGLONG Result = Time.QuadPart;
    
    return (u64)Result;
}


u32 windows_GetUnix32Time()
{
    
    /*Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).*/
    u64 winTime = windows_GetWindowsTimeIn100Nanosec();
    
    // There's a difference of 369 years between Windows Time and Unix Time:
    // January 1, 1601 vs January 1, 1970
    // I have to calculate the difference in 100-nanoseconds intervals and
    // remove them from the retrieved Windows Time
    
    // 369 years correspond (properly counting the days and such, using
    // www.timeanddate.com) to 11.644.473.600 seconds
    // which is 11.644.473.600.000.000.000 nanoseconds
    // which is 116.444.736.000.000.000 100-nanosecond intervals
    
    u64 timeSinceUnix = winTime - 116444736000000000;
    timeSinceUnix /= 10000000;
    
    return (u32)timeSinceUnix;
}

u64 windows_GetUnix64Time()
{
    u64 winTime = windows_GetWindowsTimeIn100Nanosec();
    u64 timeSinceUnix = winTime - 116444736000000000;
    timeSinceUnix /= 10000000; // Convert to seconds
    
    return timeSinceUnix;
}

windowsDate windows_GetDate(b32 localTime)
{
    SYSTEMTIME time = {};
    
    if (localTime) { GetLocalTime(&time); }
    else { GetSystemTime(&time); }
    
    windowsDate result = {};
    
    result.Year         = (u32)time.wYear;;
    result.Month        = (u32)time.wMonth;;
    result.DayOfWeek    = (u32)time.wDayOfWeek;;
    result.Day          = (u32)time.wDay;;
    result.Hour         = (u32)time.wHour;;
    result.Minute       = (u32)time.wMinute;;
    result.Second       = (u32)time.wSecond;;
    result.Milliseconds = (u32)time.wMilliseconds;;
    
    return result;
}


u32 __windows_convertUTF16To32(u32 *utf32Buff, u32 maxBuff, wchar_t* data, u32 u16Len)
{
    //NOTE: isSurrogate is checking if the code is in range [0xD800 - 0xDFFF], with smartypants unsined math.
    auto isSurrogate     = [](wchar_t code) -> b32 { return ((u16)code - (u16)0xD800) < (u16)2048; };
    auto isHighSurrogate = [](wchar_t code) -> b32 { return (code & 0xFFFFFC00) == 0xD800; };
    auto isLowSurrogate  = [](wchar_t code) -> b32 { return (code & 0xFFFFFC00) == 0xDC00; };
    auto surrogateTo32   = [](wchar_t h, wchar_t l) -> u32 { return ((h << 10) + l - 0x35FDC00); };
    
    u32 idx = 0;
    
    wchar_t *In = data;
    while(In < (data + u16Len))
    {
        wchar_t curr16 = *In; 
        In += 1;
        
        b32 isSurr = (curr16 >= 0xD800) && (curr16 <= 0xDFFF);
        if(!isSurr) { utf32Buff[idx] = (u32)curr16; idx += 1; }
        else
        {
            AssertMsg(In < (data + u16Len), "Input cut off low surrogate??\n");
            
            wchar_t next16 = *In;
            In += 1;
            
            b32 hS = isHighSurrogate(curr16);
            b32 lS = isLowSurrogate(next16);
            
            AssertMsg((hS && lS) == TRUE, "Surrogate missing either High or Low\n");
            
            utf32Buff[idx] = surrogateTo32(curr16, next16);
        }
        
        AssertMsg(idx < maxBuff, "UTF32 buffer provided is too small\n");
    }
    
    return idx;
}

//NOTE:TODO: Stuff copy-pasted from the internet. Those left and right shifts are just masking bits...
u32 __windows_convertUTF32To16(wchar_t* utf16Buff, u32 maxBuff, u32 *data, u32 u32Len)
{
    u32 *In = data;
    
    u32 index = 0;
    while(In < (data + u32Len))
    {
        u32 codepoint = *In;
        In += 1;
        
        wchar_t high = 0;
        wchar_t low  = 0;
        
        if(codepoint < 0x10000) 
        { 
            utf16Buff[index] = (wchar_t)codepoint; 
            index += 1; 
            continue; 
        }
        
        u32 temp = codepoint -  0x10000;
        high = (((temp << 12) >> 22) + 0xD800);
        low  = (((temp << 22) >> 22) + 0xDC00);
        
        utf16Buff[index]   = high;
        utf16Buff[index+1] = low;
        
        index += 1;
    }
    
    return index;
}

u32 windows_GetClipboard(void *buff, u32 maxUTF32Len)
{
    if(OpenClipboard(NULL) == 0) { return 0; }
    
    HANDLE Clipboard = GetClipboardData(CF_UNICODETEXT);
    
    wchar_t* data = (wchar_t *)GlobalLock(Clipboard);
    
    wchar_t* At = data;
    u32 strLen = 0;
    while(*At != 0) { strLen += 1; At += 1; }
    
    u32 utf32Buff[4096] = {}; //TODO: I am unsure about this.
    
    u32 utf32Len = __windows_convertUTF16To32(utf32Buff, 4096, data, strLen);
    
    u32 copyLen = utf32Len < maxUTF32Len ? utf32Len : maxUTF32Len;
    
    ls_memcpy(utf32Buff, buff, copyLen*sizeof(u32));
    GlobalUnlock(Clipboard);
    
    CloseClipboard();
    
    return copyLen;
}

u32 windows_SetClipboard(void *data, u32 len)
{
    if(OpenClipboard(NULL) == 0) { return 0; }
    
    HANDLE Clipboard = GetClipboardData(CF_UNICODETEXT);
    EmptyClipboard();
    
    wchar_t charBuff[4096] = {};
    u32 buffLen = __windows_convertUTF32To16(charBuff, 4096, (u32 *)data, len);
    
    HGLOBAL clipMem = GlobalAlloc(GMEM_MOVEABLE, (buffLen+1)*sizeof(u32));
    wchar_t *clipData = (wchar_t *)GlobalLock(clipMem);
    
    ls_memcpy(charBuff, clipData, buffLen*sizeof(wchar_t));
    clipData[buffLen] = 0;
    
    GlobalUnlock(clipMem);
    
    SetClipboardData(CF_UNICODETEXT, clipMem);
    
    CloseClipboard();
    
    return len;
}


// --------------------- //
// --- TIMER  SYSTEM --- //
// --------------------- //

//NOTE:TODO: Make Precision modifiable?
void windows_initRegionTimer(RegionTimerPrecision p)
{
    BOOL Result = QueryPerformanceFrequency(&__global_QueryPerfFreq);
    if(Result == 0) 
    {
        Assert(FALSE); 
    }
    
    //NOTE: We count with a precision of 0.1 milliseconds
    
    if(p == RT_MILLISECOND)    { __global_TimerPrecMulti = 1000; }
    else if(p == RT_HUNDMICRO) { __global_TimerPrecMulti = 10000; }
    else if(p == RT_TENSMICRO) { __global_TimerPrecMulti = 100000; }
    else if(p == RT_MICRO)     { __global_TimerPrecMulti = 1000000; }
    else if(p == RT_HUNDNANO)  { __global_TimerPrecMulti = 10000000; }
    else if(p == RT_TENSNANO)  { __global_TimerPrecMulti = 100000000; }
    else if(p == RT_NANO)      { __global_TimerPrecMulti = 1000000000; }
    //TODO: What if a wrong value is passed?
    
    //__global_QueryPerfFreq.QuadPart /= 1000*10;
}

void windows_sleep(u64 milliseconds)
{
    Sleep(milliseconds);
    return;
}




//
// BULLSHIT
// 



#ifdef I_WANT_GRAPHICS

#include "lsGraphics.h"

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
    if ((WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName,
                                        In->windowName, In->style,
                                        CW_USEDEFAULT, CW_USEDEFAULT,
                                        In->Width, In->Height,
                                        0, 0, hInstance, 0)) == nullptr)
    {
        DWORD Error = GetLastError();
        ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
    }
    
    //NOTE: NOTE: IMPORTANT: SetCapture Is used to forcibly use mouse input
    //And should NOT be forcibly imposed (Unless it's released short after) because
    //It stops all other window activities (Like resizing the window, or using
    //the window menu buttons).
    //SetCapture(WindowHandle);
    
    In->WindowHandle = WindowHandle;
    
    /* @TODO: @NOTE: Should I even do this here ? */
    if (SetCursorPos(In->Width / 2, In->Height / 2) == NULL)
    {
        DWORD Error = GetLastError();
        ls_printf("When Setting Cursor Position in Win32_SetupScreen got error: %d", Error);
    }
}

#ifdef OPENGL_GRAPHICS

#include "OpenGL\glHelperFunctions.h"
#include "OpenGL\ls_OpenGL.h"

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
    glClearDepth(1.0f);     //NOTE: z-depth for drawing
    glDepthFunc(GL_LEQUAL); //NOTE: draw if depth is <= current val
}

#endif //OPENGL_GRAPHICS

#endif //I_WANT_GRAPHICS

#endif //PLATFORM_IMPLEMENTATION