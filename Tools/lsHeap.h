#ifndef LS_HEAP_H
#define LS_HEAP_H

struct heap_value
{
    s32 key;
    u8  item[16];
};

//NOTE: This is a "max heap", meaning the root contains the highest key
struct heap
{
    heap_value *data;
    s32         itemSize;
    s32         count;
    s32         capacity;
};

heap ls_heapAlloc(s32 itemSize, s32 capacity);
heap ls_heapFromArray(void *data, s64 *keys, s32 itemSize, s32 count);
heap ls_heapMerge(heap *first, heap second);

void ls_heapPush(heap *h, s32 key, void *item);
void ls_heapPop(heap *h, heap_value *valueBuff);
void ls_heapPeek(heap *h, heap_value *valueBuff);
void ls_heapRemoveRoot(heap *h);
void ls_heapReplaceRoot(heap *h, s32 key, void *item);

void ls_heapFree(heap *h);

#endif //LS_HEAP_H

#ifdef LS_HEAP_IMPLEMENTATION

//--------- Internal --------------

void __ls_heapSiftUp(heap *h, s32 idx)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    
    if(idx == 0) { return; }
    
    //NOTE: If the current node has a larger key than it's parent, we swap them
    //      and then recursively call the function on the parent (which is now at the bottom)
    //      to find it's proper position
    
    //      We may be able to save something by sifting down the parent if the swap happens,
    //      rather than sifting it up from the bottom? Not sure.
    
    s32 parentIdx      = ((idx - 1) / 2);
    heap_value *curr   = h->data + idx;
    heap_value *parent = h->data + parentIdx;
    if(curr->key > parent->key)
    {
        heap_value tmp = { curr->key };
        ls_memcpy(curr->item, tmp.item, h->itemSize);
        
        curr->key = parent->key;
        ls_memcpy(parent->item, curr->item, h->itemSize);
        
        parent->key = tmp.key;
        ls_memcpy(tmp.item, parent->item, h->itemSize);
        
        __ls_heapSiftUp(h, parentIdx);
    }
}

void __ls_heapSiftDown(heap *h, s32 idx)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    
    if(idx == (h->count-1)) { return; }
    
    //NOTE: If the current node has a smaller key than it's child, we swap them
    //      and then recursively call the function on the child (which is now at the top)
    //      to find it's proper position
    
    heap_value *curr   = h->data + idx;
    s32 swapIdx        = idx;
    s32 leftIdx        = ((idx*2) + 1);
    s32 rightIdx       = ((idx*2) + 2);
    heap_value *left   = h->data + leftIdx;
    heap_value *right  = h->data + rightIdx;
    
    if(leftIdx  < h->count && curr->key < left->key)                 { swapIdx = leftIdx;  }
    if(rightIdx < h->count && (h->data + swapIdx)->key < right->key) { swapIdx = rightIdx; }
    
    if(swapIdx != idx)
    {
        heap_value *toSwap = h->data + swapIdx;
        
        heap_value tmp = { curr->key };
        ls_memcpy(curr->item, tmp.item, h->itemSize);
        
        curr->key = toSwap->key;
        ls_memcpy(toSwap->item, curr->item, h->itemSize);
        
        toSwap->key = tmp.key;
        ls_memcpy(tmp.item, toSwap->item, h->itemSize);
        
        __ls_heapSiftDown(h, swapIdx);
    }
}

//---------------------------------


heap ls_heapAlloc(s32 itemSize, s32 capacity)
{
    heap result     = {};
    result.data     = (heap_value *)ls_alloc(sizeof(heap_value) * capacity);
    result.itemSize = itemSize;
    result.capacity = capacity;
    
    return result;
}

heap ls_heapFromArray(void *data, s64 *keys, s32 itemSize, s32 count)
{
    heap result     = {};
    result.data     = (heap_value *)ls_alloc(sizeof(heap_value)*count);
    result.itemSize = itemSize;
    result.capacity = count;
    result.count    = count;
    
    for(s32 i = 0; i < count; i++)
    {
        u8 *At = ((u8 *)data) + (i*itemSize);
        heap_value *curr = result.data + i;
        curr->key = (s32)(keys[i]);
        ls_memcpy(At, curr->item, itemSize);
    }
    
    for(s32 i = 0; i < count; i++) { __ls_heapSiftDown(&result, i); }
    __ls_heapSiftDown(&result, 0);
    
    return result;
}

heap ls_heapMerge(heap first, heap second)
{
    AssertMsg(first.itemSize == second.itemSize, "Item size not matching\n");
    
    heap result = ls_heapAlloc(first.itemSize, first.count + second.count);
    
    ls_memcpy(first.data, result.data, sizeof(heap_value)*first.count);
    result.count += first.count;
    
    for(s32 i = 0; i < second.count; i++)
    {
        heap_value *v = second.data + i;
        ls_heapPush(&result, v->key, v->item);
    }
    
    return result;
}

void ls_heapPush(heap *h, s32 key, void *item)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    AssertMsg(h->count != h->capacity, "Heap is full\n");
    
    heap_value *curr = h->data + h->count;
    curr->key        = key;
    ls_memcpy(item, curr->item, h->itemSize);
    h->count        += 1;
    
    __ls_heapSiftUp(h, h->count-1);
}

void ls_heapPop(heap *h, heap_value *valueBuff)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    AssertMsg(valueBuff != NULL, "Value return pointer is null\n");
    
    heap_value *root = h->data;
    valueBuff->key   = root->key;
    ls_memcpy(root->item, valueBuff->item, h->itemSize);
    
    heap_value *last = h->data + (h->count-1);
    h->count        -= 1;
    
    root->key = last->key;
    ls_memcpy(last->item, root->item, h->itemSize);
    
    __ls_heapSiftDown(h, 0);
}

heap_value *ls_heapPeek(heap *h)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    
    return h->data;
}

void ls_heapRemoveRoot(heap *h)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    
    heap_value *root = h->data;
    if(h->count > 1)
    {
        heap_value *last = h->data + (h->count-1);
        root->key = last->key;
        ls_memcpy(last->item, root->item, h->itemSize);
        
    }
    
    h->count -= 1;
    
    __ls_heapSiftDown(h, 0);
}

void ls_heapReplaceRoot(heap *h, s32 key, void *item)
{
    AssertMsg(h != NULL, "Heap pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    heap_value *root = h->data;
    root->key        = key;
    ls_memcpy(item, root->item, h->itemSize);
    
    __ls_heapSiftDown(h, 0);
}

void ls_heapFree(heap *h)
{
    ls_free(h->data);
    h->itemSize = 0;
    h->count    = 0;
    h->capacity = 0;
}

#endif //LS_HEAP_IMPLEMENTATION
