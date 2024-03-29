#ifndef LS_ARRAY_H
#define LS_ARRAY_H

//NOTE: If cap is -696969 it means the array doesn't own the memory, and thus can't free it

template<typename T>
struct Array
{
    T *data;
    
    s32 count;
    s32 cap;
    
    T& operator[](s32 index)
    {
        AssertMsgF(index < count, "Index (%d) out of bounds in Array<>\n", index); //NOTE: Should this be a crash or an error?
        AssertMsgF(index >= 0, "Index (%d) is negative Array<>\n", index); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    T* operator+(s32 index)
    {
        AssertMsgF(index < count, "Index (%d) out of bounds in Array<>\n", index); //NOTE: Should this be a crash or an error?
        AssertMsgF(index >= 0, "Index (%d) is negative Array<>\n", index); //NOTE: Should this be a crash or an error?
        return data + index;
    }
};

template<typename T>
Array<T> ls_arrayAlloc(s32 n)
{ 
    ProfileFunc;
    //auto bpArrayAlloc = BlockProfiler(__FUNCTION__, __COUNTER__ + 1);
    
    AssertMsgF(n > 0, "Number of Elements is Non-Positive: %d", n);
    
    Array<T> result = {};
    result.data     = (T *)ls_alloc(n*sizeof(T));
    //result.data = (T *)VirtualAlloc(NULL, n*sizeof(T), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    result.count    = 0;
    result.cap      = n;
    return result;
}

template<typename T> 
void ls_arrayFromPointer(Array<T> *arr, void *src, s32 count)
{
    AssertMsg(arr, "Null Array<> pointer\n");
    AssertMsgF(count > 0, "Number of Elements is Non-Positive: %d\n", count);
    
    arr->count = count;
    arr->cap   = -696969;
    arr->data  = (T*)src;
}

template<typename T>
void ls_arrayFree(Array<T> *a)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(a->data, " Array<> is not initialized\n");
    AssertMsg(a->cap > 0, "Can't free a FixedArray<> with negative cap. It doesn't own the memory\n");
    
    ls_free(a->data);
    a->count = 0;
    a->cap   = 0;
}

template<typename T>
void ls_arrayClear(Array<T> *a) 
{ 
    AssertMsg(a, "Null Array<> pointer\n");
    a->count = 0;
}

template<typename T>
void ls_arrayGrow(Array<T> *a, s32 amount)
{
    ProfileFunc;
    //auto bpArrayGrow = BlockProfiler(__FUNCTION__, __COUNTER__ + 1);
    
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsgF(amount > 0, "Grow Amount is Non-Positive: %d\n", amount);
    AssertMsg(a->cap >= 0, "Can't reallocate a negative cap Array<>. The memory isn't owned.\n");
    
    a->data = (T *)ls_realloc(a->data, a->cap*sizeof(T), (a->cap + amount)*sizeof(T));
    a->cap += amount;
}

template<typename T>
b32 ls_arrayIsFull(Array<T> a)
{ return (a.count == a.cap); }

template<typename T>
T *ls_arrayAppend(Array<T> *a, T val)
{
    ProfileFunc;
    //auto bpArrayAppend = BlockProfiler(__FUNCTION__, __COUNTER__ + 1);
    
    AssertMsg(a, "Null Array<>  pointer\n");
    
    if(a->count == a->cap) { ls_arrayGrow(a, 32); }
    
    a->data[a->count] = val;
    T *toReturn       = a->data + a->count;
    a->count         += 1;
    
    return toReturn;
}

template<typename T>
s32 ls_arrayAppendIndex(Array<T> *a, T val)
{
    AssertMsg(a, "Null Array<> pointer\n");
    
    if(a->count == a->cap) { ls_arrayGrow(a, 32); }
    
    a->data[a->count] = val;
    a->count         += 1;
    
    return (a->count - 1);
}

template<typename T>
T *ls_arrayPop(Array<T> *a)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(a->count > 0, "Can't pop empty Array<>\n");
    
    T *value  = &a->data[a->count - 1];
    a->count -= 1;
    return value;
}

template<typename T>
void ls_arrayInsert(Array<T> *a, T val, s32 index)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(index >= 0, "Index is negative in Array<>\n");
    
    if(a->count == a->cap) { ls_arrayGrow(a, 32); }
    size_t dataSize = sizeof(T);
    
    s32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in Array<> insertion is negative. Maybe bad Array<>?\n");
    AssertMsg(numElements <= a->cap, "Somehow the number of elements to move in Array<> insertion is > array->cap?\n");
    
    ls_memcpy(a->data + index, a->data + index + 1, numElements*dataSize);
    a->count += 1;
    a->data[index] = val;
}

template<typename T>
void ls_arraySet(Array<T> *a, T val, s32 index)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(index >= 0, "Index is negative Array<>\n");
    
    if(index > a->cap) { grow(index - a->cap + 1); }
    a->data[index] = val;
}

template<typename T>
void ls_arrayRemove(Array<T> *a, s32 index)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(index >= 0, "Index is negative Array<>\n");
    AssertMsg(a->count > 0, "Can't remove from an empty array<>!\n");
    
    if(a->count <= 0) { return; }
    if(index == (a->count-1)) { a->count -= 1; return; }
    
    size_t dataSize = sizeof(T);
    s32 numElements = (a->count-1) - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in Array<> remove is negative. Maybe bad Array<>?\n");
    AssertMsg(numElements <= a->cap, "Somehow the number of elements to move in Array<> remove is > array->cap?\n");
    
    //NOTETODO: Because this operation is by default on an overlapping memory region, we perform it
    //          one at a time. When we implement a proper memmove or reverse memcpy, we'll change it.
    for(s32 i = index + 1; i < a->count; i++)
    { ls_memcpy(a->data + i, a->data + (i-1), dataSize); }
    
    a->count -= 1;
}

template<typename T>
void ls_arrayRemoveUnordered(Array<T> *a, s32 index)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(index >= 0, "Index is negative Array<>\n");
    
    //NOTETODO: Should I zero the last element? Or fill it with sentinel values?
    a->data[index] = a->data[a->count-1];
    a->count -= 1;
}

template<typename T>
b32 ls_arrayContains(Array<T> *a, T val)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(a->data, "Array<> is not initialized\n");
    
    for(u32 i = 0; i < a->count; i++)
    {
        if (a->data[i] == val) { return TRUE; }
    }
    
    return FALSE;
}

template<typename T>
T *ls_arrayTop(Array<T> *a)
{
    AssertMsg(a, "Null Array<>  pointer\n");
    
    if(a->count == 0) { return NULL; }
    
    return a->data + (a->count - 1);
}


//---------------------------------------//
//----         STATIC ARRAYS         ----//
//---------------------------------------//

template<typename T, int N>
struct StaticArray
{
    T data[N];
    s32 count;
    
    //NOTE: It's okay to index into a value >= count, as long as it's smaller than N, because the array is static.
    T& operator[](s32 index)
    {
        AssertMsg(index < N, "Index out of bounds in StaticArray<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative StaticArray<>\n"); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    T* operator+(s32 index)
    {
        AssertMsg(index < N, "Index out of bounds in StaticArray<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative StaticArray<>\n"); //NOTE: Should this be a crash or an error?
        
        return data + index;
    }
};

template<typename T, int N>
void ls_staticArrayClear(StaticArray<T, N> *a)  { AssertMsg(a, "Null StaticArray<> pointer\n"); a->count = 0; }

template<typename T, int N>
b32 ls_staticArrayIsFull(StaticArray<T, N> a)
{ return (a.count == N); }

template<typename T, int N>
T *ls_staticArrayAppend(StaticArray<T, N> *a, T val)
{
    ProfileFunc;
    
    AssertMsg(a, "Null StaticArray<> pointer\n");
    
    if(a->count == N) { AssertMsg(FALSE, "Trying to append to full StaticArray<>\n"); return NULL; }
    
    a->data[a->count] = val;
    T *toReturn       = a->data + a->count;
    a->count         += 1;
    
    return toReturn;
}

template<typename T, int N>
void ls_staticArrayAppendUnique(StaticArray<T, N> *a, T val)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    
    if(ls_staticArrayContains(a, val)) { return; }
    if(a->count == N) { AssertMsg(FALSE, "Trying to append to full StaticArray<>\n"); return; }
    
    a->data[a->count] = val;
    a->count         += 1;
    return;
}

template<typename T, int N>
s32 ls_staticArrayAppendIndex(StaticArray<T, N> *a, T val)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    
    if(a->count == N) { AssertMsg(FALSE, "Trying to append to full StaticArray<>"); return -1; }
    
    a->data[a->count] = val;
    a->count         += 1;
    
    return (a->count - 1);
}

template<typename T, int N>
T *ls_staticArrayPop(StaticArray<T, N> *a)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    AssertMsg(a->count > 0, "Can't pop empty StaticArray<>\n");
    
    T *value  = &a->data[a->count - 1];
    a->count -= 1;
    return value;
}

template<typename T, int N>
void ls_staticArrayInsert(StaticArray<T, N> *a, T val, s32 index)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    AssertMsgF(index < N, "Index %d is out of bounds (%d) in StaticArray<>\n", index, N);
    AssertMsg(index >= 0, "Index is negative in StaticArray<>\n");
    
    if(a->count == N) { AssertMsg(FALSE, "Trying to insert in full StaticArray<>"); return; }
    size_t dataSize = sizeof(T);
    
    s32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in StaticArray<> insertion is negative. Maybe bad StaticArray<>?\n");
    AssertMsg(numElements <= N, "Somehow the number of elements to move in StaticArray<> insertion is > cap?\n");
    
    ls_memcpy(a->data + index, a->data + index + 1, numElements*dataSize);
    a->count += 1;
    a->data[index] = val;
}

template<typename T, int N>
void ls_staticArraySet(StaticArray<T, N> *a, T val, s32 index)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    AssertMsgF(index < N, "Index %d is out of bounds (%d) in StaticArray<>\n", index, N);
    AssertMsg(index >= 0, "Index is negative StaticArray<>\n");
    
    a->data[index] = val;
}

template<typename T, int N>
void ls_staticArrayRemove(StaticArray<T, N> *a, s32 index)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    AssertMsgF(index < N, "Index %d is out of bounds (%d) in StaticArray<>\n", index, N);
    AssertMsg(index >= 0, "Index is negative StaticArray<>\n");
    
    size_t dataSize = sizeof(T);
    u32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in StaticArray<> remove is negative. Maybe bad StaticArray<>?\n");
    AssertMsg(numElements <= a->cap, "Somehow the number of elements to move in StaticArray<> remove is > cap?\n");
    
    ls_memcpy(a->data + index + 1, a->data + index, numElements*dataSize);
    a->count -= 1;
}

template<typename T, int N>
void ls_staticArrayRemoveUnordered(StaticArray<T, N> *a, s32 index)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    AssertMsgF(index < N, "Index %d is out of bounds (%d) in StaticArray<>\n", index, N);
    AssertMsg(index >= 0, "Index is negative StaticArray<>\n");
    
    //NOTETODO: Should I zero the last element? Or fill it with sentinel values?
    a->data[index] = a->data[a->count-1];
    a->count -= 1;
}

template<typename T, int N>
b32 ls_staticArrayContains(StaticArray<T, N> *a, T val)
{
    AssertMsg(a, "Null StaticArray<> pointer\n");
    
    for(s32 i = 0; i < a->count; i++)
    {
        if(ls_memcmp(a->data + i, &val, sizeof(T)) == TRUE) { return TRUE; }
    }
    
    return FALSE;
}

template<typename T, int N>
T *ls_staticArrayTop(StaticArray<T, N> *a)
{
    AssertMsg(a, "Null StaticArray<>  pointer\n");
    
    if(a->count == 0) { return NULL; }
    
    return a->data + (a->count - 1);
}


//---------------------------------------//
//----         FIXED ARRAYS          ----//
//---------------------------------------//

template<typename T>
struct FixedArray
{
    T *data;
    s32 count;
    s32 cap;
    
    T& operator[](s32 index)
    {
        AssertMsg(index < count, "Index an empty slot in FixedArray<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative FixedArray<>\n"); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    T* operator+(s32 index)
    {
        AssertMsg(index < count, "Index an empty slot in FixedArray<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative FixedArray<>\n"); //NOTE: Should this be a crash or an error?
        
        return data + index;
    }
};

template<typename T>
FixedArray<T> ls_fixedArrayAlloc(s32 n)
{ 
    AssertMsgF(n > 0, "Number of Elements is Non-Positive: %d", n);
    
    FixedArray<T> result = {};
    result.data          = (T *)ls_alloc(n*sizeof(T));
    //result.data = (T *)VirtualAlloc(NULL, n*sizeof(T), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    result.count    = 0;
    result.cap      = n;
    return result;
}

template<typename T> 
void ls_fixedArrayFromPointer(FixedArray<T> *arr, void *src, s32 count)
{
    AssertMsg(arr, "Null Array<> pointer\n");
    AssertMsgF(count > 0, "Number of Elements is Non-Positive: %d\n", count);
    
    //NOTE: Cap is set to -696969 to indicate the array doesn't own the memory
    //      And can't free it.
    arr->count = count;
    arr->cap   = -696969;
    arr->data  = (T*)src;
}

template<typename T>
void ls_fixedArrayFree(FixedArray<T> *a)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsg(a->data, "FixedArray<> is not initialized\n");
    AssertMsg(a->cap > 0, "Can't free a FixedArray<> with negative cap. It doesn't own the memory\n");
    
    ls_free(a->data);
    a->count = 0;
    a->cap   = 0;
}

template<typename T>
void ls_fixedArrayClear(FixedArray<T> *a)  { AssertMsg(a, "Null FixedArray<> pointer\n"); a->count = 0; }

template<typename T>
b32 ls_fixedArrayIsFull(FixedArray<T> a)
{ return (a.count == a.cap); }

template<typename T>
T *ls_fixedArrayAppend(FixedArray<T> *a, T val)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    
    if(a->count == a.cap) { AssertMsg(FALSE, "Trying to append to full FixedArray<>\n"); return NULL; }
    
    a->data[a->count] = val;
    T *toReturn       = a->data + a->count;
    a->count         += 1;
    
    return toReturn;
}

template<typename T>
void ls_fixedArrayAppendUnique(FixedArray<T> *a, T val)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    
    if(ls_fixedArrayContains(a, val)) { return; }
    if(a->count == a.cap) { AssertMsg(FALSE, "Trying to append to full FixedArray<>\n"); return; }
    
    a->data[a->count] = val;
    a->count         += 1;
    return;
}

template<typename T>
s32 ls_fixedArrayAppendIndex(FixedArray<T> *a, T val)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    
    if(a->count == a.cap) { AssertMsg(FALSE, "Trying to append to full FixedArray<>"); return -1; }
    
    a->data[a->count] = val;
    a->count         += 1;
    
    return (a->count - 1);
}

template<typename T>
T *ls_fixedArrayPop(FixedArray<T> *a)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsg(a->count > 0, "Can't pop empty FixedArray<>\n");
    
    T *value  = &a->data[a->count - 1];
    a->count -= 1;
    return value;
}

template<typename T>
void ls_fixedArrayInsert(FixedArray<T> *a, T val, s32 index)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsg(index < a.cap, "Index is out of allocated bounds in FixedArray<>\n");
    AssertMsgF(index <= a.count, "Index %d is out of bounds (%d) in FixedArray<>\n", index, a.count);
    AssertMsg(index >= 0, "Index is negative in FixedArray<>\n");
    
    if(a->count == a.cap) { AssertMsg(FALSE, "Trying to insert in full FixedArray<>"); return; }
    size_t dataSize = sizeof(T);
    
    s32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in FixedArray<> insertion is negative. Maybe bad FixedArray<>?\n");
    AssertMsg(numElements <= a.cap, "Somehow the number of elements to move in FixedArray<> insertion is > cap?\n");
    
    ls_memcpy(a->data + index, a->data + index + 1, numElements*dataSize);
    a->count += 1;
    a->data[index] = val;
}

template<typename T>
void ls_fixedArraySet(FixedArray<T> *a, T val, s32 index)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsgF(index < a.count, "Index %d is out of bounds (%d) in FixedArray<>\n", index, a.count);
    AssertMsg(index >= 0, "Index is negative FixedArray<>\n");
    
    a->data[index] = val;
}

template<typename T>
void ls_fixedArrayRemove(FixedArray<T> *a, s32 index)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsgF(index < a.count, "Index %d is out of bounds (%d) in FixedArray<>\n", index, a.count);
    AssertMsg(index >= 0, "Index is negative FixedArray<>\n");
    
    size_t dataSize = sizeof(T);
    u32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in FixedArray<> remove is negative. Maybe bad FixedArray<>?\n");
    AssertMsg(numElements <= a->cap, "Somehow the number of elements to move in FixedArray<> remove is > cap?\n");
    
    ls_memcpy(a->data + index + 1, a->data + index, numElements*dataSize);
    a->count -= 1;
}

template<typename T>
void ls_fixedArrayRemoveUnordered(FixedArray<T> *a, s32 index)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    AssertMsgF(index < a.count, "Index %d is out of bounds (%d) in FixedArray<>\n", index, a.count);
    AssertMsg(index >= 0, "Index is negative FixedArray<>\n");
    
    //NOTETODO: Should I zero the last element? Or fill it with sentinel values?
    a->data[index] = a->data[a->count-1];
    a->count -= 1;
}

template<typename T>
b32 ls_fixedArrayContains(FixedArray<T> *a, T val)
{
    AssertMsg(a, "Null FixedArray<> pointer\n");
    
    for(s32 i = 0; i < a->count; i++)
    {
        if(ls_memcmp(a->data + i, &val, sizeof(T)) == TRUE) { return TRUE; }
    }
    
    return FALSE;
}

template<typename T>
T *ls_fixedArrayTop(FixedArray<T> *a)
{
    AssertMsg(a, "Null FixedArray<>  pointer\n");
    
    if(a->count == 0) { return NULL; }
    
    return a->data + (a->count - 1);
}

#endif