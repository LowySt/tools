#ifndef LS_ARRAY_H
#define LS_ARRAY_H

template<typename T>
struct Array
{
    T *data;
    
    s32 count;
    s32 cap;
    
    T& operator[](s32 index)
    {
        AssertMsg(index < count, "Index out of bounds in Array<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative Array<>\n"); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    T* operator+(s32 index)
    {
        AssertMsg(index < count, "Index out of bounds in Array<>\n"); //NOTE: Should this be a crash or an error?
        AssertMsg(index >= 0, "Index is negative Array<>\n"); //NOTE: Should this be a crash or an error?
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
    arr->cap   = count;
    arr->data  = (T*)src;
}

template<typename T>
void ls_arrayFree(Array<T> *a)
{
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsg(a->data, " Array<> is not initialized\n");
    
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
    
    size_t dataSize = sizeof(T);
    u32 numElements = a->count - index;
    
    AssertMsg(numElements >= 0, "Number of elements to move in Array<> remove is negative. Maybe bad Array<>?\n");
    AssertMsg(numElements <= a->cap, "Somehow the number of elements to move in Array<> remove is > array->cap?\n");
    
    ls_memcpy(a->data + index + 1, a->data + index, numElements*dataSize);
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
    
    if(a->count == N) { AssertMsg(FALSE, "Trying to append to full StaticArray<>"); return NULL; }
    
    a->data[a->count] = val;
    T *toReturn       = a->data + a->count;
    a->count         += 1;
    
    return toReturn;
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
        if (a->data[i] == val) { return TRUE; }
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

#endif