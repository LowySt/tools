#ifndef LS_BUFFER_H
#define LS_BUFFER_H

#include "lsCRT.h"
#include "lsString.h"

//TODO: Add a debug-only member called 'isView' that is checked and asserts if a destructive operation is
//      applied to the view (like a free or re-alloc).
//      Or maybe decide that buffer always owns the data, and create a separate type called maybe "buffer_view"
//      which never owns the data.
struct buffer
{
    void *data;
    u64 size;
    
    u64 cursor;
};

//TODO: My names are stupid. Byte is okay, but Word, DWord and QWord are stupid.
//      Should be all renamed to (name)8, (name)16, (name)32, etc...
buffer ls_bufferInit(u64 bufferSize);
buffer ls_bufferViewIntoPtr(void *arr, u64 arrSize);
buffer ls_bufferFromPtrArray(void *arr, u64 arrSize);
buffer ls_bufferInitFromFile(string path);

void   ls_bufferClear(buffer *buff);
void   ls_bufferDestroy(buffer *buff);
void   ls_bufferSeekBegin(buffer *buff);

void   ls_bufferZeroPad(buffer *buff, u32 numBytes);
void   ls_bufferReadSkip(buffer *buff, u32 numBytes);

void   ls_bufferChangeByte(buffer *buff, u8 v);
void   ls_bufferChangeWord(buffer *buff, u16 v);
void   ls_bufferChangeDWord(buffer *buff, u32 v);
void   ls_bufferChangeQWord(buffer *buff, u64 v);

void   ls_bufferAddByte(buffer *buff, u8 v);
void   ls_bufferAddWord(buffer *buff, u16 v);
void   ls_bufferAddDWord(buffer *buff, u32 v);
void   ls_bufferAddQWord(buffer *buff, u64 v);
void   ls_bufferAddFloat(buffer *buff, f32 v);
void   ls_bufferAddDouble(buffer *buff, f64 v);

//NOTE: AddData includes serializes the length, AddDataClean does NOT.
void   ls_bufferAddData8(buffer *buff, void *data, u8 len);
void   ls_bufferAddData32(buffer *buff, void *data, u32 len);
void   ls_bufferAddDataClean(buffer *buff, void *data, u32 len);

u8     ls_bufferPeekByte(buffer *buff);
u16    ls_bufferPeekWord(buffer *buff);
u32    ls_bufferPeekDWord(buffer *buff);
u64    ls_bufferPeekQWord(buffer *buff);
f32    ls_bufferPeekFloat(buffer *buff);
f64    ls_bufferPeekDouble(buffer *buff);

u32    ls_bufferPeekData8(buffer *buff, void **dataOut);
u32    ls_bufferPeekData16(buffer *buff, void **dataOut);
u32    ls_bufferPeekData32(buffer *buff, void **dataOut);
void   ls_bufferPeekDataClean(buffer *buff, void **dataOut, u32 numBytes);

u8     ls_bufferReadByte(buffer *buff);
u16    ls_bufferReadWord(buffer *buff);
u32    ls_bufferReadDWord(buffer *buff);
u64    ls_bufferReadQWord(buffer *buff);
f32    ls_bufferReadFloat(buffer *buff);
f64    ls_bufferReadDouble(buffer *buff);

u32    ls_bufferReadData8(buffer *buff, void *out);
u32    ls_bufferReadData32(buffer *buff, void *out);
void   ls_bufferReadDataClean(buffer *buff, void *out, u32 numBytes);

u8     ls_bufferPullByte(buffer *buff);
u16    ls_bufferPullWord(buffer *buff);
u32    ls_bufferPullDWord(buffer *buff);
u64    ls_bufferPullQWord(buffer *buff);
f32    ls_bufferPullFloat(buffer *buff);
f64    ls_bufferPullDouble(buffer *buff);

//TODONOTE: To be able to pull strings we need to change the implementation of AddString
//      to add the string len both before and after the string data, so that the len can be known
//      whether you're reading forward or backward. Remeber also to change ReadString to skip the
//      2nd len bytes.

#ifdef LS_STRING_H
void   ls_bufferAddString(buffer *buff, string v);
void   ls_bufferAddStringClean(buffer *buff, string v);
void   ls_bufferAddUTF32(buffer *buff, utf32 v);

string ls_bufferReadString(buffer *buff);
utf32  ls_bufferReadUTF32(buffer *buff);
void   ls_bufferReadIntoUTF32(buffer *buff, utf32 *s);
#endif


#ifdef LS_ARRAY_H

template<typename T, int N>
void ls_bufferAddStaticArray(buffer *buff, StaticArray<T, N> a)
{
    AssertNonNull(buff);
    
    //NOTE: First we serialize the template parameters to be able to assert, 
    //      when deserializing, that the correct data type is being used.
    ls_bufferAddDWord(buff, sizeof(T));
    ls_bufferAddDWord(buff, N);
    
    ls_bufferAddDWord(buff, a.count);
    ls_bufferAddDataClean(buff, a.data, sizeof(T)*a.count);
}

template<typename T, int N>
void ls_bufferReadStaticArray(buffer *buff, StaticArray<T, N> *a)
{
    AssertNonNull(buff);
    AssertNonNull(a);
    
    s32 sizeOfT = ls_bufferReadDWord(buff);
    AssertMsg(sizeOfT == sizeof(T), "Incorrect StaticArray<> passed to function. sizeof(T) doesn't match\n");
    
    s32 staticN = ls_bufferReadDWord(buff);
    AssertMsg(staticN == N, "Incorrect StaticArray<> passed to function. N template param doesn't match\n");
    
    a->count = ls_bufferReadDWord(buff);
    ls_bufferReadDataClean(buff, a->data, sizeof(T)*a->count);
}

#endif

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
    
    u64 buffSize = arrSize;
    Result.data = ls_alloc(buffSize);
    ls_memcpy(arr, Result.data, arrSize);
    Result.size = buffSize;
    Result.cursor = 0;
    
    return Result;
}

buffer ls_bufferInitFromFile(string path)
{
    buffer Result = {};
    
    u64 readSize = ls_readFile(path.data, (char **)&Result.data, 0);
    Result.size = readSize;
    
    return Result;
}

//NOTE: bufferClear and bufferSeekBegin are the same, but the intention is different!
//      When we use clear, we don't care about the data currently inside the buffer
//      When we use SeekBegin we do care, and may re-use it!
void ls_bufferClear(buffer *buff)
{ buff->cursor = 0; }

void ls_bufferSeekBegin(buffer *buff)
{ buff->cursor = 0; }

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

inline void ls_bufferSetCursorEnd(buffer *buff)
{ buff->cursor = buff->size; } //NOTE: Is this fine?

inline void ls_bufferSetCursorIdx(buffer *buff, u64 idx)
{ buff->cursor = idx; }

inline void ls_bufferAdvanceCursor(buffer *buff, u64 amount)
{ buff->cursor += amount; }


void ls_bufferZeroPad(buffer *buff, u32 numBytes)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + numBytes > buff->size)
    { ls_bufferGrow(buff, numBytes + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memset(At, 0, numBytes);
    buff->cursor += numBytes;
}

void ls_bufferReadSkip(buffer *buff, u32 numBytes)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    buff->cursor += numBytes;
}

void ls_bufferChangeByte(buffer *buff, u8 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    *At = v;
}

void ls_bufferChangeWord(buffer *buff, u16 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u16 *At = (u16 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferChangeDWord(buffer *buff, u32 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u32 *At = (u32 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferChangeQWord(buffer *buff, u64 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u64 *At = (u64 *)((u8 *)buff->data + buff->cursor);
    *At = v;
}

void ls_bufferAddByte(buffer *buff, u8 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 1 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    *At = v;
    buff->cursor += 1;
}

void ls_bufferAddWord(buffer *buff, u16 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 2 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u16 *At = (u16 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 2;
}

void ls_bufferAddDWord(buffer *buff, u32 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 4 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u32 *At = (u32 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 4;
}

void ls_bufferAddQWord(buffer *buff, u64 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 8 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    u64 *At = (u64 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 8;
}


void ls_bufferAddFloat(buffer *buff, f32 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 4 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    f32 *At = (f32 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 4;
}

void ls_bufferAddDouble(buffer *buff, f64 v)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + 8 > buff->size)
    { ls_bufferGrow(buff, 4096); }
    
    f64 *At = (f64 *)((u8 *)buff->data + buff->cursor);
    *At = v;
    buff->cursor += 8;
}

void ls_bufferAddData8(buffer *buff, void *data, u8 len)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    ls_bufferAddByte(buff, len);
    
    if(buff->cursor + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(data, At, len);
    buff->cursor += len;
}

void ls_bufferAddData32(buffer *buff, void *data, u32 len)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    ls_bufferAddDWord(buff, len);
    
    if(buff->cursor + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(data, At, len);
    buff->cursor += len;
}

void ls_bufferAddDataClean(buffer *buff, void *data, u32 len)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    if(buff->cursor + len > buff->size)
    { ls_bufferGrow(buff, len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(data, At, len);
    buff->cursor += len;
}

u8 ls_bufferPeekByte(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u8 v = *((u8 *)buff->data + buff->cursor);
    return v;
}

u16 ls_bufferPeekWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u32 ls_bufferPeekDWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

f32 ls_bufferPeekFloat(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    f32 v = *(f32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

f64 ls_bufferPeekDouble(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    f64 v = *(f64 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u64 ls_bufferPeekQWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u32 ls_bufferPeekData8(buffer *buff, void **dataOut)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(dataOut,    "Output buffer is null\n");
    
    u32 numBytes = ls_bufferPeekByte(buff);
    
    u8 *At = (u8 *)buff->data + (buff->cursor + 1);
    
    //NOTE Peek should never copy, only return the pointer into the data and the length.
    *dataOut = (void *)At;
    
    return numBytes;
}

u32 ls_bufferPeekData16(buffer *buff, void **dataOut)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(dataOut,    "Output buffer is null\n");
    
    u32 numBytes = ls_bufferPeekWord(buff);
    
    u8 *At = (u8 *)buff->data + (buff->cursor + 2);
    
    //NOTE Peek should never copy, only return the pointer into the data and the length.
    *dataOut = (void *)At;
    
    return numBytes;
}

u32 ls_bufferPeekData32(buffer *buff, void **dataOut)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(dataOut,    "Output buffer is null\n");
    
    u32 numBytes = ls_bufferPeekDWord(buff);
    
    u8 *At = (u8 *)buff->data + (buff->cursor + 4);
    
    //NOTE Peek should never copy, only return the pointer into the data and the length.
    *dataOut = (void *)At;
    
    return numBytes;
}

void ls_bufferPeekDataClean(buffer *buff, void **dataOut, u32 numBytes)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(dataOut,    "Output buffer is null\n");
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    
    //NOTE Peek should never copy, only return the pointer into the data and the length.
    //ls_memcpy(At, dataOut, numBytes);
    *dataOut = (void *)At;
}

u8 ls_bufferReadByte(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u8 v = *((u8 *)buff->data + buff->cursor);
    buff->cursor += 1;
    return v;
}

u16 ls_bufferReadWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 2;
    return v;
}

u32 ls_bufferReadDWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 4;
    return v;
}

f32 ls_bufferReadFloat(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    f32 v = *(f32 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 4;
    return v;
}

f64 ls_bufferReadDouble(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    f64 v = *(f64 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 8;
    return v;
}

u64 ls_bufferReadQWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    buff->cursor += 8;
    return v;
}

u32 ls_bufferReadData8(buffer *buff, void *out)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(out,        "Output buffer is null\n");
    
    u32 numBytes = ls_bufferReadByte(buff);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, out, numBytes);
    buff->cursor += numBytes;
    
    return numBytes;
}

u32 ls_bufferReadData32(buffer *buff, void *out)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(out,        "Output buffer is null\n");
    
    u32 numBytes = ls_bufferReadDWord(buff);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, out, numBytes);
    buff->cursor += numBytes;
    
    return numBytes;
}

void ls_bufferReadDataClean(buffer *buff, void *out, u32 numBytes)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    AssertMsg(out,        "Output buffer is null\n");
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, out, numBytes);
    buff->cursor += numBytes;
}

u8 ls_bufferPullByte(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    buff->cursor -= 1;
    u8 v = *((u8 *)buff->data + buff->cursor);
    return v;
}

u16 ls_bufferPullWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is null\n");
    AssertMsg(buff->data, "Buffer data is null\n");
    
    buff->cursor -= 2;
    u16 v = *(u16 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u32 ls_bufferPullDWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 4;
    u32 v = *(u32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

u64 ls_bufferPullQWord(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 8;
    u64 v = *(u64 *)((u8 *)buff->data + buff->cursor);
    return v;
}

f32 ls_bufferPullFloat(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 4;
    f32 v = *(f32 *)((u8 *)buff->data + buff->cursor);
    return v;
}

f64 ls_bufferPullDouble(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    buff->cursor -= 8;
    f64 v = *(f64 *)((u8 *)buff->data + buff->cursor);
    return v;
}


#ifdef LS_STRING_H
void ls_bufferAddString(buffer *buff, string v)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    AssertMsg(v.data,     "String data is NULL\n");
    
    //NOTE: We add count the string data(v.len) and the string len itself (sizeof(u32))
    if(buff->cursor + v.len + sizeof(u32) > buff->size)
    { ls_bufferGrow(buff, v.len + sizeof(u32) + 4096); }
    
    ls_bufferAddDWord(buff, v.len);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(v.data, At, v.len);
    buff->cursor += v.len;
}

void ls_bufferAddStringClean(buffer *buff, string v)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    AssertMsg(v.data,     "String data is NULL\n");
    
    if(buff->cursor + v.len > buff->size)
    { ls_bufferGrow(buff, v.len + 4096); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(v.data, At, v.len);
    buff->cursor += v.len;
}

void ls_bufferAddUTF32(buffer *buff, utf32 v)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    if(v.data == 0) { ls_bufferAddDWord(buff, 0); return; }
    if(v.len == 0)  { ls_bufferAddDWord(buff, 0); return; }
    
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
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    u32 strLen = ls_bufferReadDWord(buff);
    string s = ls_strAlloc(strLen);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s.data, strLen);
    s.len = strLen;
    
    buff->cursor += strLen;
    return s;
}

utf32 ls_bufferReadUTF32(buffer *buff)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated\n");
    
    u32 strLen     = ls_bufferReadDWord(buff);
    if(strLen == 0) { return utf32({NULL, 0, 0}); }
    
    u32 lenInBytes = strLen * sizeof(u32);
    utf32 s        = ls_utf32Alloc(strLen);
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s.data, lenInBytes);
    s.len = strLen;
    
    buff->cursor += lenInBytes;
    return s;
}

void ls_bufferReadIntoUTF32(buffer *buff, utf32 *s)
{
    AssertMsg(buff,       "Buffer pointer is NULL\n");
    AssertMsg(s,          "Unistring pointer is NULL\n");
    AssertMsg(buff->data, "Buffer data is not allocated");
    
    u32 strLen     = ls_bufferReadDWord(buff);
    u32 lenInBytes = strLen * sizeof(u32);
    
    if(s->size < strLen) { ls_utf32Free(s); }
    
    if(!s->data) { *s = ls_utf32Alloc(strLen + 8); }
    
    u8 *At = (u8 *)buff->data + buff->cursor;
    ls_memcpy(At, s->data, lenInBytes);
    s->len = strLen;
    
    buff->cursor += lenInBytes;
}
#endif //STRING_H

#endif //IMPLEMENTATION