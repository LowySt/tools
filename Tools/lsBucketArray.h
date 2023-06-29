#ifndef LS_BUCKET_ARRAY_H
#define LS_BUCKET_ARRAY_H

//NOTE: The bucket array is an unordered data structure.
//      For speed reasons, when an item is removed the vacancy will be filled
//      by the last item in that bucket. Conversly, finding a void at the end of a bucket
//      doesn't ensure that there's no other buckets after.

struct bucket
{
    bucket *next;
    s32 count;
    u8  data[0];
};

struct bucket_array
{
    bucket *first;
    
    s32     bucketCount;
    s32     bucketCapacity;
    s32     itemSize;
    
    void *operator+(s32 index)
    {
        s32 bucketIndex = index / bucketCapacity;
        
        //NOTE: Find the correct bucket
        bucket *curr = first;
        while(bucketIndex)
        {
            curr = curr->next;
            bucketIndex -= 1;
        }
        
        AssertMsg(curr->count > 0, "Index points to an empty bucket\n");
        
        s32 relativeIndex = index % bucketCapacity;
        u8 *dataPointer   = curr->data + (itemSize*relativeIndex);
        return (void *)dataPointer;
    }
};

bucket_array ls_bArrayAlloc(s32 itemSize, s32 bucketCapacity);

s32  ls_bArrayAppend(bucket_array *b, void *item);
void ls_bArrayRemove(bucket_array *b, s32 index);

#endif //LS_BUCKET_ARRAY_H

#ifdef LS_BUCKET_ARRAY_IMPLEMENTATION

bucket * __ls_bArrayAllocateBucket(s32 bucketCapacity)
{
    s32 allocSize  = sizeof(bucket*) + sizeof(s32) + bucketCapacity;
    bucket *result = (bucket *)ls_alloc(allocSize);
    return result;
}

bucket_array ls_bArrayAlloc(s32 itemSize, s32 bucketCapacity)
{
    bucket_array result = {};
    
    result.bucketCapacity = bucketCapacity;
    result.itemSize       = itemSize;
    result.first          = __ls_bArrayAllocateBucket(bucketCapacity);
    
    return result;
}

s32 ls_bArrayAppend(bucket_array *b, void *item)
{
    AssertMsg(b != NULL, "Null bucket array pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    bucket *curr = b->first;
    
    //NOTE: Find the first available bucket
    while(curr->next != NULL)
    {
        if(curr->count < b->bucketCapacity) { break; }
        curr = curr->next;
    }
    
    //NOTE: If necessary, allocate a new bucket
    if(curr->count == b->bucketCapacity)
    {
        curr->next = __ls_bArrayAllocateBucket(b->bucketCapacity);
        curr = curr->next;
    }
    
    //NOTE: Append the item
    u8 *At = curr->data + (b->itemSize*curr->count);
    ls_memcpy(item, At, b->itemSize);
    s32 result   = curr->count + ((b->bucketCount-1)*b->bucketCapacity);
    curr->count += 1;
    return result;
    
}

void ls_bArrayRemove(bucket_array *b, s32 index)
{
    AssertMsg(b != NULL, "Null bucket array pointer\n");
    AssertMsg(index >= 0, "Negative index\n");
    
    s32 bucketIndex = index / b->bucketCapacity;
    
    //NOTE: Find the correct bucket
    bucket *curr = b->first;
    while(bucketIndex)
    {
        curr = curr->next;
        bucketIndex -= 1;
    }
    
    AssertMsg(curr->count > 0, "Index points to an empty bucket\n");
    
    //NOTE: Replace the item with the last element in the bucket to fill the void
    s32 relativeIndex = index % b->bucketCapacity;
    
    if(curr->count-1 > relativeIndex)
    {
        u8 *Src = curr->data + (b->itemSize*(curr->count-1));
        u8 *Dst = curr->data + (b->itemSize*relativeIndex);
        ls_memcpy(Src, Dst, b->itemSize);
        curr->count -= 1;
    }
    else //NOTE: If the index is the last item in the bucket, we just decrease the count.
    {
        curr->count -= 1;
    }
}

#endif //LS_BUCKET_ARRAY_IMPLEMENTATION
