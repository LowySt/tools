#ifndef LS_LINUX_H
#define LS_LINUX_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fcntl.h>

#define TRUE  1
#define FALSE 0

#ifndef NDEBUG
#define Assert(Ex) if(!Ex) {linux_assert(#Ex, __FILE__, __LINE__); abort();}
#else
#define Assert(Ex)
#endif

#define Bytes(n) (n)
#define KBytes(n) 1024ul*Bytes(n)
#define MBytes(n) 1024ul*KBytes(n)
#define GBytes(n) 1024ul*MBytes(n)

#define LS_STDOUT STDOUT_FILENO
#define LS_STDIN  STDIN_FILENO
#define LS_STDERR STDERR_FILENO

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef s32 b32;

typedef float   f32;
typedef double  f64;

extern "C" s32 ls_printf(const char *fmt, ...);
extern "C" s32 ls_sprintf(char *dest, const char *fmt, ...);

struct MemoryBlock
{
    MemoryBlock *next;
    MemoryBlock *prev;

    void *mem;
    u32 size;
};

struct MemoryArena
{
    void *heap;

    MemoryBlock freeBlocks;
    u32 minBlockSize;
    u32 maxBlockSize;

    u32 firstAllocSize = 0;
};

static MemoryArena Memory = {};

extern "C"
{
    
    void linux_assert(const char *msg, const char *file, s32 line);
    void *linux_memAlloc(u64 size);
    void linux_memFree(void *p);
        
    u64 linux_ReadFile(char *path, char **outputBuffer, u32 bytesToRead);
    u64 linux_WriteFile(char *path, void *buffer, u32 bytesToWrite);
    u64 linux_ReadConsole(s32 ConsoleHandle, char *outputBuffer, u32 bytesToRead);
    u64 linux_WriteConsole(s32 ConsoleHandle, void *buffer, u32 bytesToWrite);
}

#endif

#ifdef PLATFORM_IMPLEMENTATION

u64 linux_ReadConsole(s32 ConsoleHandle, char *outputBuffer, u32 bytesToRead)
{
    u64 bytesRead = 0;
    bytesRead = (u64)read(ConsoleHandle, outputBuffer, bytesToRead);

    return bytesRead;
}

u64 linux_WriteConsole(s32 ConsoleHandle, void *buffer, u32 bytesToWrite)
{
    u64 bytesWritten = 0;
    
    bytesWritten = (u64)write(ConsoleHandle, buffer, bytesToWrite);
    if(bytesWritten <= 0)
    { printf("Error %d in writeFile(), when writing to console\n", errno); }

    return bytesWritten;
}

void linux_assert(const char *msg, const char *file, s32 line)
{
    char buff[512] = {0};
    s32 written = ls_sprintf(buff, "In file %s, line %d, Assert %s fired\n", file, line, msg);
    linux_WriteConsole(LS_STDERR, (void *)buff, (u32)written);
}

static void linux_breakMemoryBlock(MemoryBlock *block, u32 desiredSize)
{
//    MemoryBlock *newBlock;
    return;

}

static void linux_halveMemoryBlock(MemoryBlock *block)
{
    linux_breakMemoryBlock(block, block->size/2);
}

static void linux_initMemory()
{
    u32 allocationSize = 0;

    if(Memory.firstAllocSize != 0) { allocationSize = Memory.firstAllocSize; }
    else
    {
        struct sysinfo info = {};
        s32 error = sysinfo(&info);
        if(error != 0)
        {
            ls_printf("Error %d, when calling sysinfo() in linux_initMemory()\n", errno);
        }

        if (info.totalram < GBytes(8)) { allocationSize = info.totalram / 4; }
        else { allocationSize = GBytes(2); }
    }

    Memory.heap = malloc(allocationSize);
    if(Memory.heap == NULL)
    {
        ls_printf("Error when malloc()ing memory in linux_initMemory()");
    }

    MemoryBlock firstBlock = {NULL, NULL, Memory.heap, allocationSize};
    Memory.freeBlocks = firstBlock;
}

void *linux_memAlloc(u64 size)
{
    void *p = malloc(size);
    if(p == NULL)
    {
        ls_printf("Error when allocating memory in linux_memAlloc()\n");
    }

    return p;
}

void linux_memFree(void *p)
{
    free(p);
    return;
}

u64 linux_ReadFile(char *path, char **outputBuffer, u32 bytesToRead)
{
    u64 bytesRead = 0;

    struct stat fileStat = {0};
    s32 error = stat(path, &fileStat);
    if (error != 0)
    { printf("Error %d in readFile(), when requesting file stats for path:\n%s\n", errno, path); }
    
    u32 readAmount = bytesToRead == 0 ? fileStat.st_size : bytesToRead;

    s32 fileDesc = open(path, O_RDONLY);
    if(fileDesc < 0)
    { printf("Error %d in readFile(), when opening file descriptor for path:\n%s\n", errno, path); }
    
    *outputBuffer = (char *)malloc(sizeof(char)*fileStat.st_size);   

    bytesRead = (u64)read(fileDesc, outputBuffer, readAmount);

    if(close(fileDesc) != 0)
    { printf("Error %d in readFile(), when closing file descriptor for path:\n%s\n", errno, path); }

    return bytesRead;
}

u64 linux_WriteFile(char *path, void *buffer, u32 bytesToWrite)
{
    u64 bytesWritten = 0;

    s32 fileDesc = open(path, O_WRONLY | O_CREAT, S_IRWXU);
    if(fileDesc < 0)
    { printf("Error %d in writeFile(), when opening file descriptor for path:\n%s\n", errno, path); }
    
    bytesWritten = (u64)write(fileDesc, buffer, bytesToWrite);
    if(bytesWritten <= 0)
    { printf("Error %d in writeFile(), when writing to file \n%s\n", errno, path); }


    if(close(fileDesc) != 0)
    { printf("Error %d in writeFile(), when closing file descriptor for path:\n %s\n", errno, path); }

    return bytesWritten;
}

#endif
