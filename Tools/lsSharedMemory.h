#ifndef LS_SHARED_MEMORY_H
#define LS_SHARED_MEMORY_H

/* --------------------------------------------------------------
*  This is meant to be used as a Single Producer Single Consumer
*  queue between processes (rather than threads) for message
*  communications. It uses a single Write Memory Barrier on push
*  and a sentinel value on the SharedMemoryMessageHeader to make 
*  sure everything is working correctly.
*  The payloadSize is decided at Initialization and constant.
*
*  NOTE Because of how File Mapping works on windows, the
*  address of the data is obtained by offsetting from the
*  beginOfData returned by MapViewOfFile when Connecting to a
*  SharedMemory.
*
*  Look up: @JustViewsProblems
*  -------------------------------------------------------------- */

struct SharedMemoryMessage
{
    u8    sentinel;
    u8    payload[];
};

struct SharedMemory
{
    u64    maxPayloads;
    u64    payloadSize;
    u64    writeCursor;
    u64    readCursor;
};

SharedMemory *ls_sharedMemInit(char *name, u64 payloadSize, u64 maxPayloads);
SharedMemory *ls_sharedMemConnect(char *name);

b32           ls_sharedMemPush   (SharedMemory *mem, void *payload);
b32           ls_sharedMemPop    (SharedMemory *mem, void *payload);

#endif //LS_SHARED_MEMORY_H

#ifdef LS_SHARED_MEMORY_IMPLEMENTATION

SharedMemory *ls_sharedMemInit(char *name, u64 payloadSize, u64 maxPayloads)
{
    AssertMsg((payloadSize != 0) && (maxPayloads != 0), "Invalid payloadSize or maxPayloads\n");
    
    SharedMemory *Result = NULL;
    
    //NOTE: We add enough space for the Shared Memory structure itself, duplicated at the beginning of the memory.
    u64 maxSize = maxPayloads*sizeof(SharedMemoryMessage) + sizeof(SharedMemory);
    
    u32 highOrd = (u32)((maxSize & 0xFFFFFFFF00000000LL) >> 32);
    u32 lowOrd  = (u32)maxSize;
    
    //NOTE:Committed pages cannot be decommitted or freed.
    HANDLE mappedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 
                                           highOrd, lowOrd, name);
    
    void *beginOfData    = MapViewOfFile(mappedFile, FILE_MAP_ALL_ACCESS, 0, 0, maxSize);
    Result               = (SharedMemory *)beginOfData;
    Result->maxPayloads  = maxPayloads;
    Result->payloadSize  = payloadSize;
    Result->writeCursor  = 0;
    Result->readCursor   = 0;
    
    return Result;
}

SharedMemory *ls_sharedMemConnect(char *name)
{
    SharedMemory *Result = NULL;
    
    /*NOTE: CreateFileMapping and MapViewOfFile give access to a Virtual Address Space. Because of that
*       Different processes may be given (I think they will CERTAINLY be given) different addresses
*       that point to the same file. Because of that I can't store the data pointer in the
*       SharedMemory structure, because that pointer is only valid for the process that originally
*       obtained it.
*
*       Since it's just a view into the memory region, and the SharedMemory structure is stored in
*       the region itself, simply offsetting from the beginOfData address (the one provided by
*       MapViewOfFile) will always give the correct data address on any process.
*       @JustViewsProblems
*/
    
    //NOTE:Committed pages cannot be decommitted or freed.
    HANDLE mappedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 1, name);
    void *beginOfData = MapViewOfFile(mappedFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    Result            = (SharedMemory *)beginOfData;
    
    return Result;
}

u32 ls_sharedMemAdvanceCursor(SharedMemory *mem, u32 cursor)
{
    u8 *byteData       = (u8 *)mem + sizeof(SharedMemory);
    const u32 sentinelSize = sizeof(u8);
    u32 lastSlotOffset = mem->payloadSize*(mem->maxPayloads-1 + sentinelSize);
    
    u32 newCursor = cursor + mem->payloadSize + sentinelSize;
    if(newCursor >= lastSlotOffset) { newCursor = 0; }
    
    return newCursor;
}

b32 ls_sharedMemPush(SharedMemory *mem, void *payload)
{
    u8 *byteData             = (u8 *)mem + sizeof(SharedMemory);
    SharedMemoryMessage *msg = (SharedMemoryMessage *)(byteData + mem->writeCursor);
    
    if(msg->sentinel == 0)
    {
        _mm_sfence();
        
        ls_memcpy(payload, &msg->payload, mem->payloadSize);
        msg->sentinel = 1;
        mem->writeCursor = ls_sharedMemAdvanceCursor(mem, mem->writeCursor);
        
        return TRUE;
    }
    
    return FALSE;
}

b32 ls_sharedMemPop(SharedMemory *mem, void *payload)
{
    u8 *byteData             = (u8 *)mem + sizeof(SharedMemory);
    SharedMemoryMessage *msg = (SharedMemoryMessage *)(byteData + mem->readCursor);
    
    if(msg->sentinel == 0) { return FALSE; }
    
    ls_memcpy(&msg->payload, payload, mem->payloadSize);
    u32 readSize = mem->payloadSize;
    
    ls_zeroMem(&msg->payload, readSize);
    msg->sentinel = 0;
    mem->readCursor = ls_sharedMemAdvanceCursor(mem, mem->readCursor);
    
    return TRUE;
}

#endif //LS_SHARED_MEMORY_IMPLEMENTATION
