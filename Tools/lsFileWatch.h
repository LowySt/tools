#ifndef LS_FILEWATCH_H
#define LS_FILEWATCH_H

/*
 * HOW TO USE:
 * The library does not want to allocate/deallocate memory, or force you into some patterns
 * so by default here's the expected usage:
 *
 *  At init call ls_fwCreateFileWatcher(void*, u32)
 *     The parameters are a memory buffer and it's size. That is the buffer the FileWatcher will use for all its
 *     memory needs.
 *
 *  For every file you want watched, call ls_fwStartWatchingFile(FW_FileWatcher fw, char *filePath, char **dest)
 *     This will both start watching the file and give you the file contents on first read.
 *       If the function succeeds with no problem, it will return bytesRead from file
 *       If the backing buffer is full, this function will return 0, and set *dest to 0
 *       If the file could not be read for any reason, it will return 0 and set *dest to -1
 *       If the file could be read but attributes could not, it will return 0 and set *dest to -2
 *
 *  Whenever you want to check if there were modifications, use the iterator:
 *     FW_ChangedFile *ls_fwIterNext()
 *       It returns 0 if no more files have been changed, otherwise it returns a valid pointer to a FW_ChangedFile
 *
 * */

#include "lsWindows.h"
#include "lsCRT.h"
#include "lsLog.h"

#ifndef FW_MAX_FILES_WATCHED
#define FW_MAX_FILES_WATCHED 256
#endif

struct FW_WatchedFile
{
    char *absolutePath;
    char *fileName;
    char *extension;

    u64 lastTimestamp;
    u64 size;
};

struct FW_FileWatcher
{
    FW_WatchedFile watchedFiles[FW_MAX_FILES_WATCHED];
    u32 count;
    u32 idx;

    char *backingMemory;
    u32 used;
    u32 size;
};

FW_FileWatcher  ls_fwCreateFileWatcher(void *backingMemory, u32 size);
s32             ls_fwStartWatchingFile(FW_FileWatcher *fw, char *filePath, char **dest);
FW_WatchedFile *ls_fwIterNext(FW_FileWatcher *fw);

#endif //LS_FILEWATCH_H



#ifdef LS_FILEWATCH_IMPLEMENTATION

FW_FileWatcher ls_fwCreateFileWatcher(char *backingMemory, u32 size)
{
    FW_FileWatcher fw = {};
    fw.backingMemory  = backingMemory;
    fw.size           = size;

    return fw;
}

s32 ls_fwStartWatchingFile(FW_FileWatcher *fw, char *filePath, char **dest)
{
    u32 fpLen = ls_len(filePath);

    if ((fw->used + fpLen) > fw->size)
    {
        *dest = (char*)0;
        return 0;
    }

    u64 read = ls_readFile(filePath, dest, 0);
    if (read == 0)
    {
        *dest = (char*)-1;
        return 0;
    }

    FW_WatchedFile *curr = fw->watchedFiles + fw->count;
    fw->count += 1;

    curr->absolutePath = (fw->backingMemory + fw->used);
    fw->used += fpLen;
    ls_memcpy(filePath, curr->absolutePath, fpLen);

    //TODO: Setup filename and extension


    WIN32_FILE_ATTRIBUTE_DATA attrData = {};
    if (!GetFileAttributesExA(filePath, GetFileExInfoStandard, &attrData))
    {
        *dest = (char*)-2;
        return 0;
    }

    u64 fSize = ((u64)attrData.nFileSizeHigh << 32) | attrData.nFileSizeLow;
    u64 ts    = ((u64)attrData.ftLastWriteTime.dwHighDateTime << 32) | attrData.ftLastWriteTime.dwLowDateTime;
    if (fSize != read)
    {
        ls_log("What {u64} != {u64}", fSize, read);
        return -3;
    }

    curr->size          = fSize;
    curr->lastTimestamp = ts;
    return fSize;
}

FW_WatchedFile *ls_fwIterNext(FW_FileWatcher *fw)
{
    if (fw->idx >= fw->count)
    {
        fw->idx = 0;
        return 0;
    }

    FW_WatchedFile *watchedFile = fw->watchedFiles + fw->idx;
    fw->idx += 1;

    WIN32_FILE_ATTRIBUTE_DATA attrData = {};
    if (!GetFileAttributesExA(watchedFile->absolutePath, GetFileExInfoStandard, &attrData))
    {
        fw->idx = 0;
        return 0;
    }

    u64 fSize = ((u64)attrData.nFileSizeHigh << 32) | attrData.nFileSizeLow;
    u64 ts    = ((u64)attrData.ftLastWriteTime.dwHighDateTime << 32) | attrData.ftLastWriteTime.dwLowDateTime;
    
    if ((fSize == watchedFile->size) || (ts == watchedFile->lastTimestamp))
    {
        fw->idx = 0;
        return 0;
    }

    watchedFile->size          = fSize;
    watchedFile->lastTimestamp = ts;

    return watchedFile;
}

#endif //LS_FILEWATCH_IMPLEMENTATION
