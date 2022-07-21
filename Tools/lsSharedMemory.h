#ifndef LS_SHARED_MEMORY_H
#define LS_SHARED_MEMORY_H

/* --------------------------------------------------------------
*  This is meant to be used as a Single Producer Single Consumer
*  queue between processes (rather than threads) for message
*  communications. It uses a single Write Memory Barrier on push
*  and the payloadSize as a sentinel value on the 
*  SharedMemoryMessageHeader to make sure everything is working
 *  correctly.
*  -------------------------------------------------------------- */

struct SharedMemoryMessage
{
    u32   payloadSize;
    void *payload;
};

struct SharedMemory
{
    HANDLE mappedFile;
    void  *data;
    
    u64    maxSize;
    u64    writeCursor;
    u64    readCursor;
};

SharedMemory *ls_sharedMemInit(char *name, u64 maxSizeInBytes);
SharedMemory *ls_sharedMemConnect(char *name);

void          ls_sharedMemPush(SharedMemory *mem, void *payload, u64 sizeInBytes);

template <typename T>
void          ls_sharedMemPush(SharedMemory *mem, T *payload);

u32           ls_sharedMemPop(SharedMemory *mem, void *payload);

#endif //LS_SHARED_MEMORY_H

#ifdef LS_SHARED_MEMORY_IMPLEMENTATION

SharedMemory *ls_sharedMemInit(char *name, u64 maxSizeInBytes)
{
    SharedMemory *Result = NULL;
    
    //NOTE: We add enough space for the Shared Memory structure itself, duplicated at the beginning of the memory.
    u64 maxSize = maxSizeInBytes + sizeof(SharedMemory);
    
    u32 highOrd = (u32)((maxSize & 0xFFFFFFFF00000000LL) >> 32);
    u32 lowOrd  = (u32)maxSize;
    
    //NOTE:Committed pages cannot be decommitted or freed.
    HANDLE mappedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 
                                           highOrd, lowOrd, name);
    
    void *beginOfData    = MapViewOfFile(mappedFile, FILE_MAP_ALL_ACCESS, 0, 0, maxSize);
    Result               = (SharedMemory *)beginOfData;
    Result->mappedFile   = mappedFile;
    Result->data         = (u8 *)beginOfData + sizeof(SharedMemory);
    Result->maxSize      = maxSize;
    Result->writeCursor  = 0;
    Result->readCursor   = 0;
    
    return Result;
}

SharedMemory *ls_sharedMemConnect(char *name)
{
    SharedMemory *Result = NULL;
    
    //NOTE:Committed pages cannot be decommitted or freed.
    HANDLE mappedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1, name);
    
    void *beginOfData = MapViewOfFile(mappedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    Result            = (SharedMemory *)beginOfData;
    
    return Result;
}

void ls_sharedMemPush(SharedMemory *mem, void *payload, u64 sizeInBytes)
{
    if(sizeInBytes == 0) return;
    
    SharedMemoryMessage *msg = (SharedMemoryMessage *)(((u8 *)(mem->data)) + mem->writeCursor);
    
    if(msg->payloadSize == 0)
    {
        _mm_sfence();
        
        AssertMsg(FALSE, "Shit\n");
        
        msg->payloadSize = sizeInBytes;
        ls_memcpy(payload, msg->payload, sizeInBytes);
        mem->writeCursor = ls_sharedMemAdvanceCursor(mem->writeCursor, mem->maxSize);
    }
    
    return;
}

template <typename T>
void ls_sharedMemPush(SharedMemory *mem, T *payload)
{
    ls_sharedMemPush(mem, payload, sizeof(T));
}

u32 ls_sharedMemPop(SharedMemory *mem, void *payload)
{
    SharedMemoryMessage *msg = (SharedMemoryMessage *)(((u8 *)(mem->data)) + mem->readCursor);
    
    if(msg->payloadSize == 0) return 0;
    
    ls_memcpy(msg->payload, payload, msg->payloadSize);
    u32 readSize = msg->payloadSize;
    
    ls_zeroMem(msg->payload, msg->payloadSize);
    msg->payloadSize = 0;
    mem->readCursor = ls_sharedMemAdvanceCursor(mem->readCursor, mem->maxSize);
    
    return readSize;
}

#endif //LS_SHARED_MEMORY_IMPLEMENTATION
