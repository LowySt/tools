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
 *  For every file you want watched, call ls_fwStartWatchingFile(FW_FileWatcher *fw, char *absolutePath, char **dest)
 *     This will both start watching the file and give you the file contents on first read
 *          Again dest is a buffer spacious enough you provided.
 *
 *       If the function succeeds with no problem, it will return bytesRead from file
 *       If the maximum amount of watchable files is reached, this function will return 0, and set *dest to 0
 *       If the backing buffer is full, this function will return 0, and set *dest to -1
 *       If the file could not be read for any reason, it will return 0 and set *dest to -2
 *       If the file could be read but attributes could not, it will return 0 and set *dest to -3
 *       If the function ignored the watchable file because of a blacklist, it will return 0, and set *dest to -4
 *          NOTE: Blacklists are explained below
 *
 *  If you want to watch all files inside a directory, 
 *    call ls_fwStartWatchingAllFilesInDir(FW_FileWatcher *fw, char *dirParentPath, char *dirName, bool recursive = true)
 *      It's essentially a wrapper to automatically call 'ls_fwStartWatchingFile(...) for every file in a directory
 *      But using it currently voids some error results, since it only returns the amount of files it started watching.
 *      - So, 0 for any failure state (or for an empty directory)
 *      - And N for any success state that started watching N files
 *
 *  NOTE: Calling a *StartWatching* function on the same input multiple times will just waste space and re-check the same
 *  files multiple times. Uniqueness is not guaranteed.
 *
 *  Whenever you want to check if there were modifications, use the iterator:
 *     FW_ChangedFile *ls_fwIterNext(FW_FileWatcher *fw)
 *       It returns 0 if no more files have been changed, otherwise it returns a valid pointer to a FW_ChangedFile
 *
 *  When asking for an entire directory, you probably want to filter some files/patterns from being watched,
 *  for that reason, a stack-like blacklist solution is provided.
 *  You can blacklist 'endings'. We are not blacklisting *extensions* or *filenames* but *endings*.
 *  Essentially, we are going to compare the path's end with the blacklist *ending*, by the length
 *  of the ending. So, if your *ending* is only an extension or an exact filename, or even
 *  a portion of filename+ending, that will be caught too.
 *
 *  Once a blacklist has been pushed, all next *StartWatching* functions will ignore what matches the pattern.
 *  You can pop the last blacklist, and then all next *StartWatching* functions will include those files again.
 *  You cannot start watching a blacklisted file after having popped the blacklist without a new call to *StartWatching*.
 *
 *  CUSTOMIZATION:
 *  After this block-comment explanation, you'll find constant defines that you can override in your own code
 *  to change the amount of stack-allocated memory by the context structure FW_FileWatcher, to allow fore more/less
 *  files/blacklists entries
 *
 * */

#include "lsWindows.h"
#include "lsCRT.h"
#include "lsLog.h"

#ifndef FW_MAX_FILES_WATCHED
#define FW_MAX_FILES_WATCHED 64
#endif

#ifndef FW_MAX_BLACKLIST_ENTRIES
#define FW_MAX_BLACKLIST_ENTRIES 64
#endif

#ifndef FW_MAX_BLACKLIST_ENTRY_LEN 
#define FW_MAX_BLACKLIST_ENTRY_LEN 32
#endif

#ifndef FW_PATH_SEPARATOR
#define FW_PATH_SEPARATOR '\\'
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

    //TODO: Would it be better for this to have its own backing memory, and better handle pushing/popping?
    // That would also allow me to embedd the metadata (count) inside the backing memory itself and make this
    // structure lighter...
    char ending_blacklist[FW_MAX_BLACKLIST_ENTRIES][FW_MAX_BLACKLIST_ENTRY_LEN];
    u32 ending_count;

    char *backingMemory;
    u32 used;
    u32 size;
};

FW_FileWatcher  ls_fwCreateFileWatcher(void *backingMemory, u32 size);

s32             ls_fwPushEndingToBlacklist(FW_FileWatcher *fw, char *ending);
s32             ls_fwPopEndingFromBlacklist(FW_FileWatcher *fw);

s32             ls_fwStartWatchingFile(FW_FileWatcher *fw, char *absolutePath, char **dest);
s32             ls_fwStartWatchingAllFilesInDir(FW_FileWatcher *fw, char *dirParentPath, char *dirName, bool recursive);
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

s32 ls_fwPushEndingToBlacklist(FW_FileWatcher *fw, char *ending)
{
    if (fw->ending_count >= FW_MAX_BLACKLIST_ENTRIES) { return 1; }

    s32 len = ls_len(ending);
    if (len > FW_MAX_BLACKLIST_ENTRY_LEN) { return 1; }

    char *slot = (char *)(fw->ending_blacklist + fw->ending_count);
    ls_memcpy(ending, slot, len);
    ls_memcpy((char *)"\0", slot+len, 1);
    fw->ending_count += 1;
    return 0;
}

s32 ls_fwPopEndingFromBlacklist(FW_FileWatcher *fw)
{
    fw->ending_count -= 1;
    return 0;
}

bool __ls_fwIsBlacklisted(FW_FileWatcher *fw, char *path, s32 pLen)
{
    char *pathEnd = path+pLen;

    for (s32 endI = 0; endI < fw->ending_count; endI++)
    {
        char *endEntry = fw->ending_blacklist[endI];
        s32 entryLen = ls_len(endEntry);

        if (ls_memcmp(pathEnd-entryLen, endEntry, entryLen) == TRUE)
        {
            return true;
        }
    }

    return false;
}

void __ls_fwGetNameAndExtension(char *absolutePath, s32 *filenameIdx, s32 *filenameLen, s32 *extIdx, s32 *extLen)
{
    s32 len = ls_len(absolutePath);
    bool extFound = false;
    bool firstSepFound = false;
    for (s32 i = len-1; i >= 0; i--)
    {
        if (extFound && firstSepFound) { break; }

        if (!extFound && (absolutePath[i] == '.'))
        {
            *extIdx = i;
            *extLen = (len-1) - i;
            extFound = true;
        }

        if (!firstSepFound && (absolutePath[i] == FW_PATH_SEPARATOR))
        {
            *filenameIdx = i+1;
            *filenameLen = (len-1) - (i+1);
            firstSepFound = true;
        }
    }

    return;
}

s32 ls_fwStartWatchingFile(FW_FileWatcher *fw, char *absolutePath, char **dest)
{
    if (fw->idx >= FW_MAX_FILES_WATCHED)
    {
        if (dest != NULL) { *dest = (char*)0; }
        return 0;
    }

    u32 fpLen = ls_len(absolutePath);

    if ((fw->used + fpLen+1) > fw->size)
    {
        if (dest != NULL) { *dest = (char*)-1; }
        return 0;
    }

    if (dest != NULL)
    {
        u64 read = ls_readFile(absolutePath, dest, 0);
        if (read == 0)
        {
            *dest = (char*)-2;
            return 0;
        }
    }

    if(__ls_fwIsBlacklisted(fw, absolutePath, fpLen))
    {
        if (dest != NULL) { *dest = (char*)-4; }
        return 0;
    }

    FW_WatchedFile *curr = fw->watchedFiles + fw->count;
    fw->count += 1;

    curr->absolutePath = (fw->backingMemory + fw->used);
    ls_memcpy(absolutePath, curr->absolutePath, fpLen);
    fw->used += fpLen;
    fw->backingMemory[fw->used] = 0;
    fw->used += 1;

    //TODO: Allocate on backing buffer for... filename and extension?
    //      or keep two len?
    s32 filenameIdx, filenameLen, extIdx, extLen;
    __ls_fwGetNameAndExtension(absolutePath, &filenameIdx, &filenameLen, &extIdx, &extLen);
    curr->fileName  = curr->absolutePath + filenameIdx;
    curr->extension = curr->absolutePath + extIdx;

    WIN32_FILE_ATTRIBUTE_DATA attrData = {};
    if (!GetFileAttributesExA(absolutePath, GetFileExInfoStandard, &attrData))
    {
        if(dest != NULL) { *dest = (char*)-3; }
        return 0;
    }

    u64 fSize = ((u64)attrData.nFileSizeHigh << 32) | attrData.nFileSizeLow;
    u64 ts    = ((u64)attrData.ftLastWriteTime.dwHighDateTime << 32) | attrData.ftLastWriteTime.dwLowDateTime;
    curr->size          = fSize;
    curr->lastTimestamp = ts;
    return fSize;
}

s32 ls_fwStartWatchingAllFilesInDir(FW_FileWatcher *fw, char *dirParentPath, char *dirName, bool recursive = true)
{
    //TODO Better errors
    if (fw->idx >= FW_MAX_FILES_WATCHED)
    {
        return 0;
    }

    u32 dpLen = ls_len(dirName);
    u32 parentLen = ls_len(dirParentPath);

    char dirBuff[512] = {};
    char *adjustedDirPath = dirBuff;
    ls_memcpy((char *)"\\\\?\\", adjustedDirPath, 4);
    ls_memcpy(dirParentPath, adjustedDirPath+4, parentLen);
    ls_memcpy(dirName, adjustedDirPath+4+parentLen, dpLen);
    ls_memcpy((char *)"\\*\0", adjustedDirPath+4+parentLen+dpLen, 3);

    WIN32_FIND_DATAA dirFindData = {};
    HANDLE hFind = FindFirstFileA(adjustedDirPath, &dirFindData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return 0; 
    }

    s32 totalFilesWatched = 0;
    do
    {
        if (dirFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (recursive) {
                if (dirFindData.cFileName[0] != '.')
                {
                    char nextDirPath[512] = {};
                    ls_memcpy(dirParentPath, nextDirPath, parentLen);
                    ls_memcpy(dirName, nextDirPath+parentLen, dpLen);
                    ls_memcpy((char *)"\\\0", nextDirPath+parentLen+dpLen, 1);

                    s32 dRes = ls_fwStartWatchingAllFilesInDir(fw, nextDirPath, dirFindData.cFileName);
                    if (dRes == 0)
                    {
                        return 0;
                    }
                    totalFilesWatched += dRes;
                }
            }
        }
        else
        {
            s32 fLen = ls_len(dirFindData.cFileName);

            char nextFilePath[512] = {};
            ls_memcpy(dirParentPath, nextFilePath, parentLen);
            ls_memcpy(dirName, nextFilePath+parentLen, dpLen);
            ls_memcpy((char *)"\\", nextFilePath+parentLen+dpLen, 1);
            ls_memcpy(dirFindData.cFileName, nextFilePath+parentLen+dpLen+1, fLen);

            s32 fRes = ls_fwStartWatchingFile(fw, nextFilePath, NULL);
            if (fRes == 0)
            {
                continue;
            }
            totalFilesWatched += 1;
        }
    }
    while (FindNextFileA(hFind, &dirFindData) != 0);
 
    DWORD dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) 
    {
        return 0;
    }

    FindClose(hFind);
    return totalFilesWatched;
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
        return 0;
    }

    u64 fSize = ((u64)attrData.nFileSizeHigh << 32) | attrData.nFileSizeLow;
    u64 ts    = ((u64)attrData.ftLastWriteTime.dwHighDateTime << 32) | attrData.ftLastWriteTime.dwLowDateTime;
    
    //TODO: Probably want to always report changes if the timestamp changed...
    // Even though some text editors do funky tricks on the file contents when trying to keep
    // backups running (vim for examples writes to a backup first, and that invalidates the 
    // written to file, without properly setting it's new size?)
    //if ((fSize == watchedFile->size) || (ts == watchedFile->lastTimestamp))
    if(ts == watchedFile->lastTimestamp)
    {
        return 0;
    }

    watchedFile->size          = fSize;
    watchedFile->lastTimestamp = ts;

    return watchedFile;
}

#endif //LS_FILEWATCH_IMPLEMENTATION
