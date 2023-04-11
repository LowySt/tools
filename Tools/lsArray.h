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
    AssertMsgF(n > 0, "Number of Elements is Non-Positive: %d", n);
    
    Array<T> result = {};
    result.data     = (T *)ls_alloc(n*sizeof(T));
    result.count    = 0;
    result.cap      = n;
    return result;
}

template<typename T> 
void ls_arrayFromPointer(Array<T> *arr, void *src, s32 count)
{
    AssertMsg(arr, "Null Array<> pointer\n");
    AssertMsgF(count > 0, "Number of Elements is Non-Positive: %d\n", n);
    
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
    AssertMsg(a, "Null Array<> pointer\n");
    AssertMsgF(amount > 0, "Grow Amount is Non-Positive: %d\n", n);
    
    a->data = (T *)ls_realloc(a->data, a->cap*sizeof(T), (a->cap + amount)*sizeof(T));
    a->cap += amount;
}

template<typename T>
b32 ls_arrayIsFull(Array<T> a)
{ return (a.count == a.cap); }

template<typename T>
T *ls_arrayAppend(Array<T> *a, T val)
{
    AssertMsg(a, "Null Array<>  pointer\n");
    
    if(a->count == a->cap) { ls_arrayGrow(a, 32); }
    
    a->data[a->count] = val;
    T *toReturn       = a->data + a->count;
    a->count         += 1;
    
    return toReturn;
}

template<typename T>
u32 ls_arrayAppendIndex(Array<T> *a, T val)
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

#endif