#ifndef LS_BUFFER_H
#define LS_BUFFER_H

#include "lsCRT.h"
#include "lsString.h"

struct buffer
{
    void *data;
    u64 size;
    
    u64 cursor;
};

extern "C"
{
    buffer ls_bufferInit(u64 bufferSize);
    buffer ls_bufferViewIntoPtr(void *arr, u64 arrSize);
    buffer ls_bufferFromPtrArray(void *arr, u64 arrSize);
    buffer ls_bufferInitFromFile(string path);
    
    void   ls_bufferClear(buffer *buff);
    void   ls_bufferDestroy(buffer *buff);
    
    void   ls_bufferChangeByte(buffer *buff, u8 v);
    void   ls_bufferChangeWord(buffer *buff, u16 v);
    void   ls_bufferChangeDWord(buffer *buff, u32 v);
    void   ls_bufferChangeQWord(buffer *buff, u64 v);
    
    void   ls_bufferAddByte(buffer *buff, u8 v);
    void   ls_bufferAddWord(buffer *buff, u16 v);
    void   ls_bufferAddDWord(buffer *buff, u32 v);
    void   ls_bufferAddQWord(buffer *buff, u64 v);
    void   ls_bufferAddData(buffer *buff, void *data, u32 len); //TODO: Bad design. Allocated data must know size.
    void   ls_bufferAddDataClean(buffer *buff, void *data, u32 len);
    
    u8     ls_bufferPeekByte(buffer *buff);
    u16    ls_bufferPeekWord(buffer *buff);
    u32    ls_bufferPeekDWord(buffer *buff);
    u64    ls_bufferPeekQWord(buffer *buff);
    
    u8     ls_bufferReadByte(buffer *buff);
    u16    ls_bufferReadWord(buffer *buff);
    u32    ls_bufferReadDWord(buffer *buff);
    u64    ls_bufferReadQWord(buffer *buff);
    u32    ls_bufferReadData(buffer *buff, void *out);
    
    u8     ls_bufferPullByte(buffer *buff);
    u16    ls_bufferPullWord(buffer *buff);
    u32    ls_bufferPullDWord(buffer *buff);
    u64    ls_bufferPullQWord(buffer *buff);
    //TODONOTE: To be able to pull strings we need to change the implementation of AddString
    //      to add the string len both before and after the string data, so that the len can be known
    //      whether you're reading forward or backward. Remeber also to change ReadString to skip the
    //      2nd len bytes.
    
#ifdef LS_STRING_H
    void      ls_bufferAddString(buffer *buff, string v);
    void      ls_bufferAddUnistring(buffer *buff, unistring v);
    
    string    ls_bufferReadString(buffer *buff);
    unistring ls_bufferReadUnistring(buffer *buff);
    void      ls_bufferReadIntoUnistring(buffer *buff, unistring *s);
#endif
    
};

#endif //LS_BUFFER_H

#ifdef LS_BUFFER_IMPLEMENTATION


buffer ls_bufferInit(u64 bufferSize)
{
    buffer Result = {};
    Result.data = ls_alloc(bufferSize);
    Result.size = bufferSize;
    Result.cursor = 0;
    
    return Result;
}

buffer ls_bufferViewIntoPtr(void *arr, u64 arrSize)
{
    buffer Result = {};
    
    Result.data   = arr;
    Result.size   = arrSize;
    Result.cursor = 0;
    
    return Result;
}

buffer ls_bufferFromPtrArray(void *arr, u64 arrSize)
{
    buffer Result = {};
    
    u64 buffSize = arrSize + 4096; //NOTE: Over allocate so that more data fits easily
    Result.data = ls_alloc(buffSize);
    ls_memcpy(arr,Result. data, arrSize);
    Result.size = buffSize;
    Result.cursor = 0;
    
    return Result;
}

buffer ls_bufferInitFromFile(string path)
{
    buffer Result = {};
    
    //TODO: Error checking
    u64 readSize = ls_readFile(path.data, (char **)&Result.data, 0);
    Result.size = readSize;
    
    return Result;
}

void ls_bufferClear(buffer *buff)
{
    buff->data   = 0;
    buff->size   = 0;
    buff->cursor = 0;
}

void ls_bufferDestroy(buffer *buff)
{
    ls_free(buff->data);
    buff->size   = 0;
    buff->cursor = 0;
}

static void ls_bufferGrow(buffer *buff, u32 amount)
{
    void *newData = ls_alloc(buff->size + amount);
    ls_memcpy(buff->data, newData, buff->size);
    ls_free(buff->data);
    buff->data = newData;
    buff->size = buff->size + amount;
}

inline void ls_bufferSetCursorBegin(buffer *buff)
{ buff->cursor = 0; }

inline void ls_bufferSetCursorEnd(buffer *buff)
{ buff->cursor = buff->size; } //NOTE: Is this fine?

inline void ls_bufferSetCursorIdx(buffer *buff, u64 idx)
{ buff->cursor = idx; }

inline void ls_bufferAdvanceCursor(buffer *buff, u64 amount)
{ buff->cursor += amount; }

void ls_bufferChangeByte(buffer *buff, u8 v)
{
    Assert(buff->data);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    *At = v;
}

void ls_bufferChangeWord(buffer *buff, u16 v)
{
    Assert(buff->data);
    
    u16 *At = (u16 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferChangeDWord(buffer *buff, u32 v)
{
    Assert(buff->data);
    
    u32 *At = (u32 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferChangeQWord(buffer *buff, u64 v)
{
    Assert(buff->data);
    
    u64 *At = (u64 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferAddByte(buffer *buff, u8 v)
{
    Assert(buff->data);
    
    if(buff->cursor + 1 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    *At = v;
    buff->cursor += 1;
}

void ls_bufferAddWord(buffer *buff, u16 v)
{
    Assert(buff->data);
    
    if(buff->cursor + 2 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u16 *At = (u16 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 2;
}

void ls_bufferAddDWord(buffer *buff, u32 v)
{
    Assert(buff->data);
    
    if(buff->cursor + 4 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u32 *At = (u32 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 4;
}

void ls_bufferAddQWord(buffer *buff, u64 v)
{
    Assert(buff->data);
    
    if(buff->cursor + 8 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u64 *At = (u64 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 8;
}

void ls_bufferAddData(buffer *buff, void *data, u32 len)
{
    Assert(buff->data);
    
    ls_bufferAddDWord(buff, len);
    
    if(buff->cursor + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(data, At, len);
    buff->cursor += len;
}

void ls_bufferAddDataClean(buffer *buff, void *data, u32 len)
{
    Assert(buff->data);
    
    if(buff->cursor + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(data, At, len);
    buff->cursor += len;
}

u8 ls_bufferPeekByte(buffer *buff)
{
    Assert(buff->data);
    
    u8 v = *((u8 *)buff->data + buff->cursor);
    return v;
}

u16 ls_bufferPeekWord(buffer *buff)
{
    Assert(buff->data);
    
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u32 ls_bufferPeekDWord(buffer *buff)
{
    Assert(buff->data);
    
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u64 ls_bufferPeekQWord(buffer *buff)
{
    Assert(buff->data);
    
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    return v;
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

u32 ls_bufferReadData(buffer *buff, void *out)
{
    Assert(buff->data);
    Assert(out);
    
    u32 numBytes = ls_bufferReadDWord(buff);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, out, numBytes);
    buff->cursor += numBytes;
    
    return numBytes;
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
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 4;
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u64 ls_bufferPullQWord(buffer *buff)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 8;
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    return v;
}

#ifdef LS_STRING_H
void ls_bufferAddString(buffer *buff, string v)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    //NOTE: We add count the string data(v.len) and the string len itself (sizeof(u32))
    if(buff->cursor + v.len + sizeof(u32) > buff->size)
    { ls_bufferGrow(buff, v.len + sizeof(u32) + 4096); }
    
    ls_bufferAddDWord(buff, v.len);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(v.data, At, v.len);
    buff->cursor += v.len;
}

void ls_bufferAddUnistring(buffer *buff, unistring v)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    if(v.len == 0) { ls_bufferAddDWord(buff, 0); return; }
    
    u32 lenInBytes = v.len*sizeof(u32);
    u32 totalLen   = lenInBytes + sizeof(u32); //Adding the lenght of len itself.
    
    if(buff->cursor + totalLen > buff->size)
    { ls_bufferGrow(buff, totalLen + 4096); }
    
    ls_bufferAddDWord(buff, v.len);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(v.data, At, lenInBytes);
    buff->cursor += lenInBytes;
}



string ls_bufferReadString(buffer *buff)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    u32 strLen = ls_bufferReadDWord(buff);
    string s = ls_strAlloc(strLen);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s.data, strLen);
    s.len = strLen;
    
    buff->cursor += strLen;
    return s;
}

unistring ls_bufferReadUnistring(buffer *buff)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    u32 strLen     = ls_bufferReadDWord(buff);
    if(strLen == 0) { return unistring({NULL, 0, 0}); }
    
    u32 lenInBytes = strLen * sizeof(u32);
    unistring s    = ls_unistrAlloc(strLen);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s.data, lenInBytes);
    s.len = strLen;
    
    buff->cursor += lenInBytes;
    return s;
}

void ls_bufferReadIntoUnistring(buffer *buff, unistring *s)
{
    AssertMsg(buff, "Buffer pointer is NULL\n");
    AssertMsg(s, "Unistring pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated");
    
    if(!s->data) { *s = ls_bufferReadUnistring(buff); return; }
    
    u32 strLen     = ls_bufferReadDWord(buff);
    u32 lenInBytes = strLen * sizeof(u32);
    
    if(s->size < strLen)
    {
        s32 growSize = (strLen - s->size) + 32;
        ls_unistrGrow(s, growSize);
    }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s->data, lenInBytes);
    s->len = strLen;
    
    buff->cursor += lenInBytes;
}
#endif //STRING_H

#endif //IMPLEMENTATION