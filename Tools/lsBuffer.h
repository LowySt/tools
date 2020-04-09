#ifndef LS_BUFFER_H
#define LS_BUFFER_H

#include "lsCRT.h"
#include "lsString.h"

struct buffer
{
    void *data;
    u64 used;
    u64 size;
    
    u64 cursor;
};

extern "C"
{
    buffer ls_bufferInit(u64 bufferSize);
    buffer ls_bufferFromPtrArray(void *arr, u64 arrSize);
    void   ls_destroyBuffer(buffer *buff);
    
    void   ls_bufferSetCursorBegin(buffer *buff);
    void   ls_bufferSetCursorEnd(buffer *buff);
    void   ls_bufferSetCursorIdx(buffer *buff, u64 idx);
    
    void   ls_bufferAddByte(buffer *buff, u8 v);
    void   ls_bufferAddWord(buffer *buff, u16 v);
    void   ls_bufferAddDWord(buffer *buff, u32 v);
    void   ls_bufferAddQWord(buffer *buff, u64 v);
    void   ls_bufferAddString(buffer *buff, string v);
    void   ls_bufferAddData(buffer *buff, void *data, u32 len);
    
    u8     ls_bufferReadByte(buffer *buff);
    u16    ls_bufferReadWord(buffer *buff);
    u32    ls_bufferReadDWord(buffer *buff);
    u64    ls_bufferReadQWord(buffer *buff);
    string ls_bufferReadString(buffer *buff);
    
    u8     ls_bufferPullByte(buffer *buff);
    u16    ls_bufferPullWord(buffer *buff);
    u32    ls_bufferPullDWord(buffer *buff);
    u64    ls_bufferPullQWord(buffer *buff);
    //NOTE: To be able to pull strings we need to change the implementation of AddString
    //      to add the string len both before and after the string data, so that the len can be known
    //      whether you're reading forward or backward. Remeber also to change ReadString to skip the
    //      2nd len bytes.
};

#endif //LS_BUFFER_H

#ifdef LS_BUFFER_IMPLEMENTATION


buffer ls_bufferInit(u64 bufferSize)
{
    buffer Result = {};
    Result.data = ls_alloc(bufferSize);
    Result.used = 0;
    Result.size = bufferSize;
    Result.cursor = 0;
    
    return Result;
}

buffer ls_bufferFromPtrArray(void *arr, u64 arrSize)
{
    buffer Result = {};
    
    u64 buffSize = arrSize + 4096; //NOTE: Over allocate so that more data fits easily
    Result.data = ls_alloc(buffSize);
    ls_memcpy(arr,Result. data, arrSize);
    Result.used = arrSize;
    Result.size = buffSize;
    Result.cursor = 0;
    
    return Result;
}

void ls_destroyBuffer(buffer *buff)
{
    ls_free(buff->data);
    buff->used   = 0;
    buff->size   = 0;
    buff->cursor = 0;
}

static void ls_bufferGrow(buffer *buff, u32 amount)
{
    void *newData = ls_alloc(buff->size + amount);
    ls_memcpy(buff->data, newData, buff->used);
    ls_free(buff->data);
    buff->data = newData;
}

inline void ls_bufferSetCursorBegin(buffer *buff)
{ buff->cursor = 0; }

inline void ls_bufferSetCursorEnd(buffer *buff)
{ buff->cursor = buff->used; } //NOTE: Is this fine?

inline void ls_bufferSetCursorIdx(buffer *buff, u64 idx)
{ buff->cursor = idx; }

void ls_bufferAddByte(buffer *buff, u8 v)
{
    Assert(buff->data);
    
    if(buff->used + 1 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u8 *At = (u8 *)buff->data + buff->used;
    *At = v;
    buff->used += 1;
}

void ls_bufferAddWord(buffer *buff, u16 v)
{
    Assert(buff->data);
    
    if(buff->used + 2 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u16 *At = (u16 *)((u8 *)buff->data + buff->used);
    *At = v;
    buff->used += 2;
}

void ls_bufferAddDWord(buffer *buff, u32 v)
{
    Assert(buff->data);
    
    if(buff->used + 4 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u32 *At = (u32 *)((u8 *)buff->data + buff->used);
    *At = v;
    buff->used += 4;
}

void ls_bufferAddQWord(buffer *buff, u64 v)
{
    Assert(buff->data);
    
    if(buff->used + 8 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u64 *At = (u64 *)((u8 *)buff->data + buff->used);
    *At = v;
    buff->used += 8;
}


void ls_bufferAddString(buffer *buff, string v)
{
    Assert(buff->data);
    
    if(buff->used + v.len + 4 > buff->size)
    { ls_bufferGrow(buff, v.len + 4 + 4096); }
    
    ls_bufferAddDWord(buff, v.len);
    
    u8 *At = (u8 *)buff->data + buff->used;
    ls_memcpy(v.data, At, v.len);
    buff->used += v.len;
}

void ls_bufferAddData(buffer *buff, void *data, u32 len)
{
    Assert(buff->data);
    
    if(buff->used + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->used;
    ls_memcpy(data, At, len);
    buff->used += len;
}

u8 ls_bufferReadByte(buffer *buff)
{
    Assert(buff->data);
    
    u8 v = *((u8 *)buff->data + buff->cursor);
    buff->cursor += 1;
    return v;
}

u16 ls_bufferReadWord(buffer *buff)
{
    Assert(buff->data);
    
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 2;
    return v;
}

u32 ls_bufferReadDWord(buffer *buff)
{
    Assert(buff->data);
    
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 4;
    return v;
}

u64 ls_bufferReadQWord(buffer *buff)
{
    Assert(buff->data);
    
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 8;
    return v;
}

string ls_bufferReadString(buffer *buff)
{
    Assert(buff->data);
    
    u32 strLen = ls_bufferReadDWord(buff);
    string s = ls_strAlloc(strLen);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s.data, strLen);
    s.len = strLen;
    
    buff->cursor += strLen;
    return s;
}

u8 ls_bufferPullByte(buffer *buff)
{
    Assert(buff->data);
    
    buff->cursor -= 1;
    u8 v = *((u8 *)buff->data + buff->cursor);
    return v;
}

u16 ls_bufferPullWord(buffer *buff)
{
    Assert(buff->data);
    
    buff->cursor -= 2;
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u32 ls_bufferPullDWord(buffer *buff)
{
    Assert(buff->data);
    
    buff->cursor -= 4;
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u64 ls_bufferPullQWord(buffer *buff)
{
    Assert(buff->data);
    
    buff->cursor -= 8;
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    return v;
}

#endif //IMPLEMENTATION