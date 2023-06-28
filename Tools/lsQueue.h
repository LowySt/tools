#ifndef LS_QUEUE_H
#define LS_QUEUE_H

#include "lsList.h"

//-----------------------
//NOTE: List Queue

struct lqueue
{
    dlist items;
    s32   count;
};

lqueue ls_lqueueInit(s32 itemSize);

void ls_lqueueEnqueue(lqueue *q, void *item);
void ls_lqueueEnqueueMem(lqueue *q, void *item);
void ls_lqueueDequeue(lqueue *q, void *itemBuff);

//NOTE: List Queue
//-----------------------


//-----------------------
//NOTE: Circular Queue

struct cqueue
{
    void *items;
    s32   itemSize;
    s32   capacity;
    s32   count;
    
    s32   insertIdx;
    s32   removeIdx;
};

cqueue ls_cqueueInit(s32 itemSize, s32 capacity);

void ls_cqueueEnqueue(cqueue *q, void *item);
void ls_cqueueDequeue(cqueue *q, void *itemBuff);

//NOTE: Circular Queue
//-----------------------

#endif //LS_QUEUE_H


#ifdef LS_QUEUE_IMPLEMENTATION

//-----------------------
//NOTE: List Queue

lqueue ls_lqueueInit(s32 itemSize)
{
    lqueue result = {};
    result.items = ls_dlistInit(itemSize);
    return result;
}

void ls_lqueueEnqueue(lqueue *q, void *item)
{
    AssertMsg(q != NULL, "Null lqueue pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    ls_dlistPrepend(&q->items, item);
    q->count += 1;
}

void ls_lqueueEnqueueMem(lqueue *q, void *item)
{
    AssertMsg(q != NULL, "Null lqueue pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    ls_dlistPrependMem(&q->items, item);
    q->count += 1;
}

void ls_lqueueDequeue(lqueue *q, void *itemBuff)
{
    AssertMsg(q != NULL, "Null lqueue pointer\n");
    AssertMsg(itemBuff != NULL, "Null return item buffer\n");
    AssertMsg(q->count > 0, "Dequeuing from an empty lqueue\n");
    
    //NOTETODO: if the item memory is owned by the user rather than the list,
    //          there's no point in copying it. I should just set the pointer?
    ls_memcpy(q->items.tail->item, itemBuff, q->items.itemSize);
    ls_dlistRem(&q->items, q->items.tail);
    q->count -= 1;
}
//NOTE: List Queue
//-----------------------


//-----------------------
//NOTE: Circular Queue

cqueue ls_cqueueInit(s32 itemSize, s32 capacity)
{
    cqueue result = {};
    
    result.items    = ls_alloc(itemSize * capacity);
    result.itemSize = itemSize;
    result.capacity = capacity;
    
    return result;
}


void ls_cqueueEnqueue(cqueue *q, void *item)
{
    AssertMsg(q != NULL, "Null cqueue pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    AssertMsg(q->count <= q->capacity, "Circular queue overflow\n");
    
    s32 onePastRemove = (q->removeIdx + 1) == q->capacity ? 0 : q->removeIdx + 1;
    s32 onePastInsert = (q->insertIdx + 1) == q->capacity ? 0 : q->insertIdx + 1;
    AssertMsg(onePastInsert  == onePastRemove, "Circular queue overflow\n");
    
    u8 *At = (u8 *)q->items;
    At    += q->insertIdx * q->itemSize;
    ls_memcpy(item, At, q->itemSize);
    q->count += 1;
    
    q->insertIdx += onePastInsert;
}

void ls_cqueueDequeue(cqueue *q, void *itemBuff)
{
    AssertMsg(q != NULL, "Null cqueue pointer\n");
    AssertMsg(itemBuff != NULL, "Null return item buffer\n");
    AssertMsg(q->count > 0, "Circular queue is empty\n");
    AssertMsg(q->removeIdx == q->insertIdx, "Circular queue underflow. Count is wrong...\n");
    
    u8 *At = (u8 *)q->items;
    At    += q->removeIdx * q->itemSize;
    ls_memcpy(At, itemBuff, q->itemSize);
    q->count -= 1;
    
    q->removeIdx += 1;
    if(q->removeIdx == q->capacity) { q->removeIdx = 0; }
}


//NOTE: Circular Queue
//-----------------------

#endif //LS_QUEUE_IMPLEMENTATION
