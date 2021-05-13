#ifndef LS_STACK_H
#define LS_STACK_H

#include "lsCRT.h"

struct stack
{
    void *top;
    void *bot;
    void *data;
    u32 elementSize;
    
    u32 capacity;
    u32 used;
};

extern "C"
{
    stack  ls_stackAlloc(u32 elementSize); //NOTE: initialCapacity of 1 element.
    stack *ls_stackAllocPtr(u32 elementSize);
    void   ls_stackFreePtr(stack *s);
    void   ls_stackFree(stack s);
    
    stack  ls_stackInit(u32 elementSize, u32 initialCapacity);
    
    void   ls_stackPush(stack *s, void *data);
    void  *ls_stackPop(stack *s);
    void  *ls_stackTop(stack *s);
    
    void  *ls_stackPull(stack *s);
    void  *ls_stackBot(stack *s);
    
    
    void   ls_stackClear(stack *s);
    
};


#endif //LS_STACK_H


#ifdef LS_STACK_IMPLEMENTATION

/*vvv INTERNAL vvv*/

static void ls_stackResize(stack *s)
{
    u64 oldSize = (s->capacity) * s->elementSize;
    u64 newSize = (s->capacity + 64) *s->elementSize;
    
    //NOTE: As of right now if bot moves upward the space between data and bot becomes dead.
    u32 distFromData = (u8 *)s->bot - (u8 *)s->data;
    
    s->data = ls_realloc(s->data, oldSize, newSize);
    s->capacity = s->capacity + 64;
    s->top = (void *)(((u8 *)s->data) + (s->used - 1));
    s->bot = (u8 *)s->bot + distFromData;
}

/*^^^ INTERNAL ^^^*/


stack *ls_stackAllocPtr(u32 elementSize)
{
    stack *Result = (stack *)ls_alloc(sizeof(stack));
    Result->data = ls_alloc(elementSize * 1);
    Result->bot = Result->data;
    Result->top = Result->data;
    Result->elementSize = elementSize;
    Result->capacity = 1;
    Result->used = 0;
    
    return Result;
}

stack ls_stackAlloc(u32 elementSize)
{
    stack Result = {};
    Result.data = ls_alloc(elementSize * 1);
    Result.bot = Result.data;
    Result.top = Result.data;
    Result.elementSize = elementSize;
    Result.capacity = 1;
    Result.used = 0;
    
    return Result;
}

void ls_stackFreePtr(stack *s)
{
    ls_free(s->data);
    ls_free(s);
}

void ls_stackFree(stack s)
{ ls_free(s.data); }

stack ls_stackInit(u32 elementSize, u32 initialCapacity)
{
    stack Result = {};
    Result.data = ls_alloc(elementSize * initialCapacity);
    Result.bot = Result.data;
    Result.top = Result.data;
    Result.elementSize = elementSize;
    Result.capacity = initialCapacity;
    Result.used = 0;
    
    return Result;
}

void ls_stackPush(stack *s, void *data)
{
    if(s->used == s->capacity)
    { ls_stackResize(s); }
    
    u8 *At = (u8 *)s->bot;
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

void *ls_stackPull(stack *s)
{
    if(s->used == 0) { return NULL; }
    
    void *Result = s->bot;
    
    //NOTE: I cannot decrease used because there's no empty space at the top.
    // If I were to move the entire stack downwards once bot moved too far away from data
    // then I could move used as well? Or maybe track the moving bottom differently...
    //s->used -= 1;
    s->bot = (u8 *)s->bot + s->elementSize;
    
    return Result;
}

void *ls_stackBottom(stack *s)
{ return s->bot; }

void ls_stackClear(stack *s)
{ s->used = 0; }

#endif // IMPLEMENTATION
