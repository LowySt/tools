#ifndef LS_WINDOWS_H
#define LS_WINDOWS_H

#define LS_PLAT_WINDOWS
#include "win32.h"

#include "lsCRT.h"

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

extern "C" s32    ls_printf(const char *fmt, ...);
extern "C" s32    ls_sprintf(char *dest, const char *fmt, ...);
extern "C" void   ls_memcpy(void *src, void *dest, size_t size);
extern "C" void   ls_zeroMem(void *mem, size_t size);

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
    void windows_resetArena(u32 id);
    void windows_destroyArena(void *data, u32 id);
    
	u64 windows_ReadConsole(char *Dest, u32 bytesToRead);
	u64 windows_WriteConsole(char *buffer, u32 bytesToWrite);
	u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead);
    u64 windows_ReadFileByOffset(char *Path, char **Dest, u32 offset, u32 bytesToRead);
	u64 windows_WriteFile(char *Path, char *source, u32 bytesToWrite, b32 append);
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
	void windows_setupWindow(WindowInfo *Input);
    
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

u64 windows_WriteConsole(char *buffer, u32 bytesToWrite)
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
	if (!WriteFile(FileHandle, buffer, bytesToWrite, &BytesWritten, NULL))
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
	s32 written = ls_sprintf(buff, "In file %s, line %d, Assert %s fired\n", file, line, msg);
	windows_WriteConsole(buff, (u32)written);
}

// --------------------- //
// --- MEMORY SYSTEM --- //
// --------------------- //

MemoryArena Memory = {};

void windows_InitMemory(size_t size)
{
    SYSTEM_INFO sysInfo = {};
    GetSystemInfo(&sysInfo);
    
    DWORD pageSize = sysInfo.dwPageSize;
    
    //NOTE: Either make a block pageSize (to subdivide) or if more is requested
    // just give a block exactly as big as requested, and it's all yours.
    u64 allocationSize = pageSize;
    if(size > (pageSize - sizeof(MemoryBlock)))
    { allocationSize = size + sizeof(MemoryBlock); }
    
    void *mem = VirtualAlloc(NULL, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    Assert(mem); //NOTE: Block Allocation Failed.
    
    MemoryBlock header = {};
    header.next = NULL;
    header.prev = NULL;
    
    header.blockSize = (allocationSize - sizeof(MemoryBlock));
    header.curSlices = 1;
    
    u32 maxSlices = (header.blockSize / 128);
    header.maxSlices = maxSlices;
    
    header.busy = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.bTail = header.busy;
    
    header.free = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.fTail = header.free;
    
    Assert(header.busy); //NOTE: Array Allocation Failed.
    Assert(header.free); //NOTE: Array Allocation Failed.
    
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
    if(size > (pageSize - sizeof(MemoryBlock)))
    { allocationSize = size + sizeof(MemoryBlock); }
    
    void *mem = VirtualAlloc(NULL, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    Assert(mem); //NOTE: Block Allocation Failed.
    
    MemoryBlock *last = Memory.last;
    
    MemoryBlock header = {};
    header.next = NULL;
    header.prev = last;
    last->next = (MemoryBlock *)mem;
    
    Memory.last = (MemoryBlock *)mem;
    
    header.blockSize = (allocationSize - sizeof(MemoryBlock));
    header.curSlices = 1;
    
    u32 maxSlices = (header.blockSize / 128);
    header.maxSlices = maxSlices;
    
    header.busy = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.bTail = header.busy;
    
    header.free = (MemoryList *)VirtualAlloc(NULL, maxSlices*sizeof(MemoryList),
                                             MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    header.fTail = header.free;
    
    Assert(header.busy); //NOTE: Array Allocation Failed.
    Assert(header.free); //NOTE: Array Allocation Failed.
    
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
    Assert(slice->sliceSize >= size);
    
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
    /*Arenas*/
    if(Memory.isUsingArena == TRUE)
    {
        InternalArena *Ar = &Memory.arenas[Memory.currArenaId];
        
        Assert(Ar->id == Memory.currArenaId); //NOTE: Some mistake in Arena usage functions?
        Assert(Ar->used + size <= Ar->capacity); //NOTE: Buy More ArenaRAM
        
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
        
        MemoryList *free = curr->free;
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
    Assert(found == TRUE);
    
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
    Assert(found == TRUE);
    
    windows_freeSlice(curr, slice);
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
    
    Ar->data = VirtualAlloc(NULL, arenaSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    Assert(Ar->data); //NOTE: Buy More RAM
    
    Ar->capacity = arenaSize;
    Ar->used     = 0;
    Ar->id       = arId;
    Memory.used[arId] = TRUE;
    
    *id = arId;
    return Ar->data;
}

void windows_useArena(u32 id)
{
    Assert(Memory.isUsingArena == FALSE);
    Assert(Memory.arenas[id].data != 0x0);
    
    Memory.isUsingArena = TRUE;
    Memory.currArenaId  = id;
    
    return;
}

void windows_stopArena()
{
    Assert(Memory.isUsingArena == TRUE);
    Memory.isUsingArena = FALSE;
    return;
}

void windows_resetArena(u32 id)
{
    Assert(Memory.used[id] == TRUE);
    Memory.arenas[id].used = 0;
    return;
}

void windows_destroyArena(void *data, u32 id)
{
    Assert(Memory.used[id] == TRUE);
    Assert(!(Memory.isUsingArena == TRUE && Memory.currArenaId == id)); //NOTE: Thinks this assertion is correct?
    Assert(Memory.arenas[id].data != 0x0);
    
    BOOL Error = VirtualFree(Memory.arenas[id].data, 0, MEM_RELEASE);
    Assert(Error != 0); //NOTE: Couldn't free, something's fucky
    
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
    DWORD Error = 0;
    HANDLE FileHandle = 0;
    LARGE_INTEGER FileSize = {};
    
    if ((FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        Error = GetLastError();
        ls_printf("%cs\n\n", Path);
        ls_printf("When creating a file handle got error: %ld\n", Error);
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
                ls_printf("Gotten Error %ld when creating file handle to file: %s\n", Error, Path);
            }
        }
        else
        {
            ls_printf("Gotten Error %ld when creating file handle to file: %s\n", Error, Path);
        }
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

void windows_sleep(u64 milliseconds)
{
    Sleep(milliseconds);
    return;
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