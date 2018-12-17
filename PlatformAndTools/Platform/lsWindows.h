#ifndef LS_WINDOWS_H
#define LS_WINDOWS_H

#include "..\..\win\win32.h"

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
 * and everything else in memory, giving us distances between these pointers, hence
 * the dimensions of the blocks.
 *
 * The allocated List is also stored in a flat memory block, allocated at startup
 * time (its dimension is constant for now, 1024 entries
 *
* [NOTE: Used to be 1024 entries, but that ended up being WAYYY TOO LOW, 
* so it has been bumped up multiple times reaching now: 131072 entries (2^17) 
 * which takes about 3MB of RAM]). 
* 
* So to be able to remove and insert entries in the list, without working with
 * allocation/freeing, we always add an entry at the tail of the list, and when
 * removing we move the tail in place of the removed entry, to avoid the 
* fragmentation of the alloc list. 
*
* The order (while it may be relevant, considering that alloc/free usually come 
* in pairs) should not be critical, that's why the tail is moved.
 */

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
    
	u64 size;
};

struct MemoryArena
{
	void *heap;
    
	MemoryBlockHeader *freeHead;
	MemoryBlockList *allocList;
	MemoryBlockList *allocTail;
	u64 allocListSize;
    
	u64 minBlockSize;
	u64 maxBlockSize;
    
	u64 totalSize;
	u64 firstAllocSize = 0;
};

static MemoryArena Memory = {};

extern "C"
{
	void windows_assert(const char *msg, const char *file, s32 line);
	void windows_setAllocatorParams(u64 firstAllocSize, u64 minBlockSize, u64 maxBlockSize);
	void *windows_memAlloc(size_t size);
	void windows_memFree(void *ptr);
    
	u64 windows_ReadConsole(char *Dest, u32 bytesToRead);
	u64 windows_WriteConsole(char *buffer, u32 bytesToWrite);
	u64 windows_ReadFile(char *Path, char **Dest, u32 bytesToRead);
    u64 windows_ReadFileByOffset(char *Path, char **Dest, u32 offset, u32 bytesToRead);
	u64 windows_WriteFile(char *Path, char *source, u32 bytesToWrite, b32 append);
    u32 windows_countFilesInDir(char *Dir, u32 dirLen);
    u32 windows_countFilesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen);
    void windows_getFileNamesInDir(char *Dir, u32 dirLen, char ***names, u32 *howManyNames, u32 **namesLen);
    void windows_getFileNamesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen, char ***names, u32 *howManyNames, u32 **namesLen);
    
    u32 windows_getFullPathName(char *fileName, u32 outBufferSize, char *outBuffer);
    
    u64 windows_GetWindowsTimeInMicrosec();
	u64 windows_GetWindowsTimeIn100Nanosec();
    u32 windows_GetUnix32Time();
    u64 windows_GetUnix64Time();
	windowsDate windows_GetDate(b32 localTime); /*If param is false UTC time is retrieved*/
	void windows_setupWindow(WindowInfo *Input);
    
    void windows_sleep(u64 milliseconds);
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

static void windows_breakMemoryBlock(MemoryBlockHeader *blockHeader, u64 desiredSize)
{
	u64 offsetSize = blockHeader->size - desiredSize;
	void *nextBlockPtr = (u8 *)blockHeader + offsetSize;
    
	Assert((u8*)nextBlockPtr < ((u8 *)Memory.heap + Memory.totalSize));
	int ASSERTFIRED = 0;
    
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
	/* 13/03/2018 - 
  *
  * @DONE
  * Got a crash here, because blockHeader->next was a nullptr.
  * I think this is because the block I was trying to remove from the
  * free list was actually the tail.
  * I have to add the special cases for head / tail removal.
  *
  * ALSO @NOTE: Remember to do the same when freeing these special entries
  * and readding them to the free list (even though this might not be a problem)
  */
	Assert(!(((MemoryBlockHeader *)blockHeader->prev == NULL) && ((MemoryBlockHeader *)blockHeader->next == NULL)));
    int assertBreak = 0;
    
	if ((MemoryBlockHeader *)blockHeader->prev == NULL)
	{ 
		((MemoryBlockHeader *)blockHeader->next)->prev = NULL;
		
		/* The head has been allocated, so I move it onto the next entry in the free list.*/
		Memory.freeHead = (MemoryBlockHeader *)Memory.freeHead->next;
	}
    
	else if ((MemoryBlockHeader *)blockHeader->next == NULL)
	{ 
		/* The last entry in the free list has been allocated, so I need to also
  * zero the next pointer of the previous entry, and that *should* be it...*/
		((MemoryBlockHeader *)blockHeader->prev)->next = NULL; 
	}
    
	else
	{
		((MemoryBlockHeader *)blockHeader->prev)->next = blockHeader->next;
		((MemoryBlockHeader *)blockHeader->next)->prev = blockHeader->prev;
	}
    
	return;
}

/* @NOTE: For now I'm arbitrarily setting the allocList size to 1024 possible 
 * entries I think it should be enough. At least for now...
 * 
 * Spoiler Alert:
 * It wasn't enough. Look further down. */

static void windows_initMemory()
{
	u64 allocationSize = 0;
    
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
        
		u64 totalRamInBytes = (u64)info.ullTotalVirtual;
        
		if (totalRamInBytes < GBytes(8ULL)) { allocationSize = totalRamInBytes / 4; }
		else { allocationSize = GBytes(2ULL); }
	}
    
	Memory.heap = VirtualAlloc(0, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	Memory.allocList = (MemoryBlockList *)VirtualAlloc(0, sizeof(MemoryBlockList)*131072, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
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
  *
  * We are at 64k entries now.
  * New count whooo: 131072 entries...
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

void windows_setAllocatorParams(u64 firstAllocSize, u64 minBlockSize, u64 maxBlockSize)
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
    if(request == 0) return NULL;
    
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
	MemoryBlockHeader *bestBlock = 0; u64 bestBlockSize = Memory.totalSize;
    
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
		/* @DONE
   * The crash happens because bestBlock has the wrong size.
   *
   * 12/03/2018 -
   * To be precise The bug happens when the extra size of the best block
   * Is smaller then sizeof(MemoryBlockHeader). It will cause to overwrite the
   * bestBlock header thus corrupting the memory.
   * 
   * To fix this I'm going to directly return the entire block, without breaking it.
   * Hopefully this doesn't break other things... I've forgotten the caveats of this
   * Memory system since I haven't worked with it in a while. Sneaky bug didn't appear for weeks!
   */
        
		if (bestBlock == NULL)
		{
			OutputDebugStringA("\n\n You RAN OUT OF USABLE MEMORY!!\n\n");
			Assert(false);
			int ASSERTFIRED = 0;
		}
        
		if ((bestBlock->size - givenMemory) < sizeof(MemoryBlockHeader))
		{
			actualBlock = bestBlock;
		}
		else
		{
			windows_breakMemoryBlock(bestBlock, (u64)givenMemory);
			actualBlock = (MemoryBlockHeader *)bestBlock->next;
		}
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

/* @NOTE: To be able to determine the size of the block that I'm freeing,
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
	u64 newBlockSize = 0;
    
	if ((uptr)p < (uptr)currHeader)
	{
		/* @NOTE: It means we've allocated the freeHead, 
   * which has been moved to the next entry in the free list.
   * Now what I need to do is check among the currently allocated
   * blocks to infer the block size */
        
        MemoryBlockList *currAllocated = Memory.allocList;
        void *closest = currHeader;
        do
        {
            if((currAllocated->blockAddr < currHeader) && (currAllocated->blockAddr > p))
            {
                if(currAllocated->blockAddr < closest)
                { closest = currAllocated->blockAddr; }
            }
            
            currAllocated = currAllocated->next;
        }
        while(currAllocated);
        
        newBlockSize = (u32)((u8 *)p - (u8 *)closest);
        next = Memory.freeHead;
        prev = NULL;
        
        //Push the freeHead back into highest position?
        Memory.freeHead = (MemoryBlockHeader *)p;
	}
    
	u32 runIdx = 0;
	while ((uptr)currHeader < (uptr)p)
	{
		Assert(currHeader->next != p);
        
		if (currHeader->next == NULL)
		{
			prev = currHeader;
			next = NULL;
            
			void *closestAllocBlock = (void *)UINTPTR_MAX;
			MemoryBlockList *curr = Memory.allocList;
			do
			{
				if (((uptr)curr->blockAddr > (uptr)p) && ((uptr)curr->blockAddr < (uptr)closestAllocBlock))
				{
					closestAllocBlock = curr->blockAddr;
				}
                
				curr = curr->next;
			} while (curr);
            
			if (closestAllocBlock == (void *)UINTPTR_MAX || ((uptr)closestAllocBlock < (uptr)p))
			{ newBlockSize = (u64)(((u8 *)Memory.heap + Memory.totalSize) - (u8 *)p); }
			else if ((uptr)closestAllocBlock > (uptr)p)
			{ newBlockSize = (u64)((u8 *)closestAllocBlock - (u8 *)p); }
			
			Assert(newBlockSize != 0);
			Assert(newBlockSize <= (Memory.totalSize / 2));
			Assert(closestAllocBlock != p);
            
			break;
		}
		
		if ((uptr)currHeader->next >(uptr)p)
		{
			prev = (void *)currHeader;
			next = currHeader->next;
            
			void *closestAllocBlock = (void *)UINTPTR_MAX;
			MemoryBlockList *curr = Memory.allocList;
			do
			{
				/* @NOTE: Remember the list is NOT ordered 
     * because I add new entries by appending them to the tail */
				if (((uptr)curr->blockAddr > (uptr)p) && ((uptr)curr->blockAddr < (uptr)closestAllocBlock))
				{ closestAllocBlock = curr->blockAddr; }
                
				curr = curr->next;
			} while (curr);
            
			if ((uptr)closestAllocBlock < (uptr)next)
			{ newBlockSize = (u64)((u8 *)closestAllocBlock - (u8 *)p); }
			else
			{ newBlockSize = (u64)((u8 *)next - (u8 *)p); }
			
			break;
		}
        
		currHeader = (MemoryBlockHeader *)currHeader->next;
		runIdx++;
	}
    
	MemoryBlockHeader newHeader = { next, prev, newBlockSize };
	ls_memcpy((void *)&newHeader, p, sizeof(MemoryBlockHeader));
    
	windows_removeFromAllocList(p);
    
	/* Next And Prev could be NULL if I'm freeing the extremities of my block, 
  * but NOT at the same time*/
	Assert(!((prev == NULL) && (next  == NULL)));
	if (prev == NULL)
	{
		((MemoryBlockHeader *)next)->prev = p;
	}
	else if (next == NULL)
	{
		((MemoryBlockHeader *)prev)->next = p;
	}
	else
	{
		((MemoryBlockHeader *)prev)->next = p;
		((MemoryBlockHeader *)next)->prev = p;
	}
    
	return;
}

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
        Result++;
        more = FindNextFileA(hFile, &findData);
    }
    
    FindClose(hFile);
    
    // NOTE: Removing current and previous directory!
    return (Result - 2);
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

void windows_getFileNamesInDir(char *Dir, u32 dirLen, char ***names, u32 *howManyNames, u32 **namesLen)
{
    *howManyNames = windows_countFilesInDir(Dir, dirLen);
    
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
        
        (*namesLen)[it] = ls_len(findData.cFileName);
        (*names)[it] = (char *)ls_alloc(sizeof(char)*((*namesLen)[it]));
        
        ls_memcpy(findData.cFileName, (*names)[it], (*namesLen)[it]);
        
        it++;
        
        more = FindNextFileA(hFile, &findData);
    }
    while(more);
    
    FindClose(hFile);
}

void windows_getFileNamesInDirByExt(char *Dir, u32 dirLen, char *ext, u32 extLen, char ***names, u32 *howManyNames, u32 **namesLen)
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
    if ((WindowHandle = CreateWindowExA(0L, WindowClass.lpszClassName, In->windowName /*"Win 32 Platform"*/, 
                                        In->style /*WS_OVERLAPPED | WS_VISIBLE*/, CW_USEDEFAULT, CW_USEDEFAULT, In->Width, In->Height, 0, 0, hInstance, 0)) == nullptr)
    {
        DWORD Error = GetLastError();
        ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
    }
    
    /*SetCapture returns the handle to the previous owner of the mouse.
    * No need for a error path */
    SetCapture(WindowHandle);
    
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
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
}

#endif

#endif