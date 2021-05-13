#ifndef LS_STACK_H
#define LS_STACK_H

#include "lsCRT.h"

struct stack
{
    void *top;
    void *data;
    u32 elementSize;
    
    u32 capacity;
    u32 used;
};

extern "C"
{
    stack  ls_stackAlloc(u32 elementSize); //NOTE: initialCapacity of 1 element.
    stack *ls_stackAllocPtr(u32 elementSize);
    void   ls_stackFree(stack *s);
    
    stack  ls_stackInit(u32 elementSize, u32 initialCapacity);
    
    void   ls_stackPush(stack *s, void *data);
    void  *ls_stackPop(stack *s);
    void  *ls_stackTop(stack *s);
    void   ls_stackClear(stack *s);
    
};


#endif //LS_STACK_H


#ifdef LS_STACK_IMPLEMENTATION

/*vvv INTERNAL vvv*/

static void ls_stackResize(stack *s)
{
    u64 oldCap = s->capacity;
    u64 newCap = s->capacity + 64;
    
    s->data = ls_realloc(s->data, oldCap, newCap);
    s->capacity = newCap;
    s->top = (void *)(((u8 *)s->data) + (s->used - 1));
}

/*^^^ INTERNAL ^^^*/


stack *ls_stackAllocPtr(u32 elementSize)
{
    stack *Result = (stack *)ls_alloc(sizeof(stack));
    Result->data = ls_alloc(elementSize * 1);
    Result->top = Result->data;
    Result->elementSize = elementSize;
    Result->capacity = 1;
    Result->used = 0;
    
    return Result;
}

stack ls_stackAlloc(u32 elementSize)
{
    stack Result = {};
    Result->data = ls_alloc(elementSize * 1);
    Result->top = Result->data;
    Result->elementSize = elementSize;
    Result->capacity = 1;
    Result->used = 0;
    
    return Result;
}

void ls_stackFree(stack *s)
{
    ls_free(s->data);
    ls_free(s);
}

stack ls_stackInit(u32 elementSize, u32 initialCapacity)
{
    stack Result = {};
    Result->data = ls_alloc(elementSize * initialCapacity);
    Result->top = Result->data;
    Result->elementSize = elementSize;
    Result->capacity = initialCapacity;
    Result->used = 0;
    
    return Result;
}

void ls_stackPush(stack *s, void *data)
{
    if(s->used == s->capacity)
    { ls_stackResize(s); }
    
    u8 *At = (u8 *)s->data;
    At += s->used*s->elementSize;
    
    ls_memcpy(data, At, s->elementSize);
    s->top = (void *)At;
    s->used += 1;
}

void *ls_stackPop(stack *s)
{
    if(s->used == 0) { return NULL; }
    
    void *Result = s->top;
    
    s->used -= 1;
    s->top = (u8 *)s->top - s->elementSize;
    
    return Result;
}

void *ls_stackTop(stack *s)
{ return s->top; }

void ls_stackClear(stack *s)
{ s->used = 0; }

#endif // IMPLEMENTATION
