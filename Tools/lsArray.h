#ifndef LS_ARRAY_H
#define LS_ARRAY_H

template<typename T>
struct Array
{
    T *data;
    u32 count;
    u32 cap;
    
    T& operator[](u32 index)
    {
        AssertMsg(index < count, "Index out of bounds in Array<>\n"); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    T* operator+(u32 index)
    {
        AssertMsg(index < count, "Index out of bounds in Array<>\n"); //NOTE: Should this be a crash or an error?
        return data + index;
    }
};

template<typename T> Array<T> ls_arrayAlloc(u32 n);
template<typename T> void     ls_arrayFromPointer(Array<T> *arr, void *src, u32 count);
template<typename T> void     ls_arrayFree(Array<T> *a);
template<typename T> void     ls_arrayClear(Array<T> *a);
template<typename T> void     ls_arrayGrow(Array<T> *a, u32 amount);

template<typename T> u32      ls_arrayAppend(Array<T> *a, T val);
template<typename T> void     ls_arrayInsert(Array<T> *a, T val, u32 index);
template<typename T> void     ls_arraySet(Array<T> *a, T val, u32 index);
template<typename T> void     ls_arrayRemove(Array<T> *a, u32 index);

template<typename T> b32      ls_arrayContains(Array<T> *a, T val);

#endif //LS_ARRAY_H

#ifdef LS_ARRAY_IMPLEMENTATION

template<typename T>
Array<T> ls_arrayAlloc(u32 n)
{ 
    Array<T> result = {};
    result.data = (T *)ls_alloc(n*sizeof(T));
    result.count = 0;
    result.cap = n;
    return result;
}

template<typename T> 
void ls_arrayFromPointer(Array<T> *arr, void *src, u32 count)
{
    arr->count = count;
    arr->cap = count;
    arr->data = (T*)src;
}

template<typename T>
void ls_arrayFree(Array<T> *a)
{
    ls_free(a->data);
    a->count = 0;
    a->cap = 0;
}

template<typename T>
void ls_arrayClear(Array<T> *a) 
{ 
    a->count = 0;
}

template<typename T>
void ls_arrayGrow(Array<T> *a, u32 amount)
{
    a->data = (T *)ls_realloc(a->data, a->cap*sizeof(T), (a->cap + amount)*sizeof(T));
    a->cap += amount;
}

template<typename T>
u32 ls_arrayAppend(Array<T> *a, T val)
{
    if(a->count == a->cap) { ls_arrayGrow(a, 32); }
    a->data[a->count++] = val;
    
    return (a->count - 1);
}

template<typename T>
void ls_arrayInsert(Array<T> *a, T val, u32 index)
{
    if(a->count == a->cap) { grow(32); }
    size_t dataSize = sizeof(T);
    
    u32 numElements = a->count - index;
    Assert(numElements <= a->cap);
    
    ls_memcpy(a->data + index, a->data + index + 1, numElements*dataSize);
    a->count += 1;
    a->data[index] = val;
}

template<typename T>
void ls_arraySet(Array<T> *a, T val, u32 index)
{
    if(index > a->cap) { grow(index - a->cap + 1); }
    a->data[index] = val;
}

template<typename T>
void ls_arrayRemove(Array<T> *a, u32 index)
{
    size_t dataSize = sizeof(T);
    u32 numElements = a->count - index;
    ls_memcpy(a->data + index + 1, a->data + index, numElements*dataSize);
    a->count -= 1;
}

template<typename T>
b32 ls_arrayContains(Array<T> *a, T val)
{
    for(u32 i = 0; i < a->count; i++)
    {
        if (a->data[i] == val) { return TRUE; }
    }
    
    return FALSE;
}

#endif