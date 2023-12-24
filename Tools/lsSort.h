#ifndef LS_SORT_H
#define LS_SORT_H

//NOTE: SortFunc returns -1 if sortA is smaller than sortB, 
//                        0 if they are equal, 
//                        1 if sortA is bigger than sortB
typedef s32 (*sortFunc)(void *sortA, void *sortB);

void ls_bubblesort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_combsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_quicksort(void *data, u32 elementSize, u32 numElements, sortFunc customFunc);
void ls_mergesort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_insertionsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_heapsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_countingsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);
void ls_radixsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc);

#endif //LS_SORT_H


#ifdef LS_SORT_IMPLEMENTATION

void ls_bubblesort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc)
{
    u8 *swap = (u8 *)ls_alloc(itemSize);
    
    for(s32 i = 0; i < numItems; i++)
    {
        u8 *left = (u8 *)data;
        u8 *right = ((u8 *)data) + itemSize;
        
        for(s32 j = 0; j < numItems - 1 - i; j++)
        {
            s32 result = customFunc(left, right);
            
            //NOTE: Means left > right
            if(result == 1)
            {
                ls_memcpy(right, swap, itemSize);
                ls_memcpy(left, right, itemSize);
                ls_memcpy(swap, left, itemSize);
            }
            
            left += itemSize;
            right += itemSize;
        }
    }
    
    ls_free(swap);
}

void ls_combsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc)
{
    f32 shrinkFactor = 1.3f;
    s32 gap          = (s32)((f32)numItems / shrinkFactor);
    b32 sorted       = FALSE;
    u8 *swap         = (u8 *)ls_alloc(itemSize);
    
    while(sorted == FALSE)
    {
        if(gap <= 1) { gap = 1; sorted = TRUE; }
        
        u8 *left  = (u8 *)data;
        u8 *right = ((u8 *)data) + (gap*itemSize);
        
        s32 i = 0;
        for(s32 j = 0; j < numItems - gap - i; j++)
        {
            s32 result = customFunc(left, right);
            
            //NOTE: Means left > right
            if(result == 1)
            {
                ls_memcpy(right, swap, itemSize);
                ls_memcpy(left, right, itemSize);
                ls_memcpy(swap, left, itemSize);
                
                sorted = FALSE;
            }
            
            left  += itemSize;
            right += itemSize;
        }
        
        i  += 1;
        gap = (s32)((f32)gap / shrinkFactor);
    }
    
    ls_free(swap);
}

static u32 qs_partition(void *data, u32 elementSize, sortFunc customFunc, s32 lowIdx, s32 highIdx)
{
    const u32 maxBuffSize = 128;
    Assert(elementSize <= maxBuffSize);
    u8 tempBuff[maxBuffSize] = {};
    
    
    u8 *dataAt = (u8 *)data;
    dataAt += elementSize*highIdx;
    void *pivotElement = (void *)dataAt;
    
    // Index of smaller element
    s32 i = (lowIdx - 1);
    
    for (u32 j = lowIdx; j <= highIdx - 1; j++)
    {
        dataAt = (u8 *)data;
        dataAt += elementSize*j;
        void *currElement = (void *)dataAt;
        
        // If current element is smaller than or
        // equal to pivot
        s32 result = customFunc(currElement, pivotElement);
        
        if((result == -1) || (result == 0))
        {
            i++;    // increment index of smaller element
            
            
            dataAt = (u8 *)data;
            dataAt += elementSize*i;
            void *replaceElem = (void *)dataAt;
            
            //TODO: Is this ok?
            if(currElement != replaceElem)
            {
                ls_memcpy(replaceElem, tempBuff, elementSize);
                ls_memcpy(currElement, replaceElem, elementSize);
                ls_memcpy(tempBuff, currElement, elementSize);
            }
        }
    }
    
    dataAt = (u8 *)data;
    dataAt += elementSize*(i+1);
    void *finalElem = (void *)dataAt;
    
    //TODO: Is this ok?
    if(finalElem != pivotElement)
    {
        ls_memcpy(finalElem, tempBuff, elementSize);
        ls_memcpy(pivotElement, finalElem, elementSize);
        ls_memcpy(tempBuff, pivotElement, elementSize);
    }
    
    return (i + 1);
}

static void qs_helper(void *data, u32 elementSize, sortFunc customFunc, s32 lowIdx, s32 highIdx)
{
    if (lowIdx < highIdx)
    {
        /* pi is partitioning index, a[pi] is now
        at right place */
        u32 pi = qs_partition(data, elementSize, customFunc, lowIdx, highIdx);
        
        qs_helper(data, elementSize, customFunc, lowIdx, pi - 1);  // Before pi
        qs_helper(data, elementSize, customFunc, pi + 1, highIdx); // After pi
    }
}

void ls_quicksort(void *data, u32 elementSize, u32 numElements, sortFunc customFunc) 
{
    qs_helper(data, elementSize, customFunc, 0, ((s32)numElements)-1); 
}

void ms_merge(void *B, s32 begin, s32 middle, s32 numItems, void *A, s32 itemSize, sortFunc customFunc)
{
    s32 i = begin;
    s32 j = middle;
    
    for(s32 k = begin; k < numItems; k++)
    {
        u8 *Ai      = ((u8 *)A) + (itemSize * i);
        u8 *Aj      = ((u8 *)A) + (itemSize * j);
        s32 compare = customFunc(Ai, Aj);
        
        //NOTE: If left side is valid and behind the right side
        //      And a swap is necessary
        if (i < middle && (j >= numItems || compare <= 0))
        {
            u8 *Bk = ((u8 *)B) + (itemSize * k);
            ls_memcpy(Ai, Bk, itemSize);
            i += 1;
        }
        else
        {
            u8 *Bk = ((u8 *)B) + (itemSize * k);
            ls_memcpy(Aj, Bk, itemSize);
            j += 1;
        }
    }
}

void ms_splitMerge(void *B, s32 begin, s32 numItems, void *A, s32 itemSize, sortFunc customFunc)
{
    //NOTE: If there's only 1 item, it's sorted.
    if(numItems - begin <= 1) { return; } // if run size == 1
    
    //NOTE: Halve every sub-list
    s32 middle = (numItems + begin) / 2;
    
    //NOTE: Recursively sort both halves from A into B
    ms_splitMerge(A, begin,  middle, B, itemSize, customFunc);
    ms_splitMerge(A, middle, numItems, B, itemSize, customFunc);
    
    //NOTE: Merge the resulting halves from array B into A
    ms_merge(B, begin, middle, numItems, A, itemSize, customFunc);
}

void ls_mergesort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc)
{
    //NOTE: Mergesort needs a work array, copied from the source
    void *workArr = ls_alloc(itemSize*numItems);
    ls_memcpy(data, workArr, itemSize*numItems);
    
    ms_splitMerge(data, 0, numItems, workArr, itemSize, customFunc);
    
    ls_free(workArr);
}

void ls_insertionsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc)
{
    void *swap = ls_alloc(itemSize);
    
    //NOTE: i represents the number of fixed (sorted) elements.
    s32 i = 1;
    while(i < numItems)
    {
        u8 *Ai = ((u8 *)data) + (itemSize * i);
        ls_memcpy(Ai, swap, itemSize);
        
        s32 j       = i - 1;
        u8 *Aj      = ((u8 *)data) + (itemSize * j);
        u8 *Aj1     = ((u8 *)data) + (itemSize * (j+1));
        
        //NOTE: This does the actual sorting of the item down the fixed (sorted) elements
        //      If the algorithm has to be made online, this would be the part that is called to sort
        //      one item. The item would be placed at the end of the array, and everything left of it
        //      is assumed already sorted
        while(j >= 0 && (customFunc(Aj, swap) == 1))
        {
            ls_memcpy(Aj, Aj1, itemSize);
            j   -= 1;
            Aj   = ((u8 *)data) + (itemSize * j);
            Aj1  = ((u8 *)data) + (itemSize * (j+1));
        }
        
        Aj1 = ((u8 *)data) + (itemSize * (j+1));
        ls_memcpy(swap, Aj1, itemSize);
        i += 1;
    }
    
    ls_free(swap);
}

#ifndef LS_HEAP_IMPLEMENTATION
#define LS_HEAP_IMPLEMENTATION
#include "lsHeap.h"
#undef LS_HEAP_IMPLEMENTATION
#endif

void ls_heapsort(void *data, s32 itemSize, s32 numItems, sortFunc customFunc)
{
    heap h = ls_heapFromArray(data, (s64 *)data, itemSize, numItems);
    
    for(s32 i = numItems-1; i >= 0; i--)
    {
        heap_value el = {};
        ls_heapPop(&h, &el);
        
        u8 *At = ((u8 *)data) + (itemSize * i);
        ls_memcpy(el.item, At, itemSize);
    }
    
    ls_heapFree(&h);
}

//NOTE: This is for base 10 numbers
void ls_countingsort(s64 *data, s64 *output, s32 numItems, s32 digitIdx)
{
    auto key = [=](s64 value) -> s64 {
        s32 divisor = 1;
        for(s32 i = 0; i < digitIdx; i++) { divisor *= 10; }
        s64 result = ((value / divisor) % 10);
        return ls_abs(result);
    };
    
    s64 *count  = (s64 *)ls_alloc(sizeof(s64)*10); //10 possible digits to count
    
    for(s32 i = 0; i < numItems; i++)
    {
        s32 j = key(data[i]);
        count[j] += 1;
    }
    
    //NOTE: Prefix sum to determine the position range
    //      items of key 'i' should be place starting at count[i]
    for(s32 i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i-1];
    }
    
    for(s32 i = numItems - 1; i >= 0; i--)
    {
        s32 j = key(data[i]);
        count[j] -= 1;
        output[count[j]] = data[i];
    }
    
    ls_free(count);
}

void ls_radixsort(s64 *data, s32 numItems)
{
    auto digitCount = [](s64 value) -> s64 {
        if(value < 10ULL) { return 1; }
        else if((value > 10ULL) && (value < 100ULL)) { return 2; }
        else if((value > 100ULL) && (value < 1000ULL)) { return 3; }
        else if((value > 1000ULL) && (value < 10000ULL)) { return 4; }
        else if((value > 10000ULL) && (value < 100000ULL)) { return 5; }
        else if((value > 100000ULL) && (value < 1000000ULL)) { return 6; }
        else if((value > 1000000ULL) && (value < 10000000ULL)) { return 7; }
        else if((value > 10000000ULL) && (value < 100000000ULL)) { return 8; }
        else if((value > 100000000ULL) && (value < 1000000000ULL)) { return 9; }
        else if((value > 1000000000ULL) && (value < 10000000000ULL)) { return 10; }
        else if((value > 10000000000ULL) && (value < 100000000000ULL)) { return 11; }
        else if((value > 100000000000ULL) && (value < 1000000000000ULL)) { return 12; }
        
        return -1;
    };
    
    //NOTE: Find the max
    s64 max = 0x8000000000000000;
    for(s32 i = 0; i < numItems; i++) { if(data[i] > max) { max = data[i]; } }
    
    s64 maxDigits = digitCount(max);
    
    //NOTE: For every digit, counting sort the items
    s64 *A = data;
    s64 *B = (s64 *)ls_alloc(sizeof(s64)*numItems);
    s64 *swap = 0;
    
    for(s32 i = 0; i < maxDigits; i++)
    {
        ls_countingsort(A, B, numItems, i);
        
        swap = A;
        A    = B;
        B    = swap;
    }
    
    //NOTE: If we swapped an odd number of times, we copy the result in data,
    //      and return that.
    //TODO: Passing a double pointer, to allow me to re-assing the data pointer
    //      (since we need an allocation anyway), would save this copy.
    if((maxDigits % 2) != 0)
    {
        swap = A;
        A    = B;
        B    = swap;
        ls_memcpy(B, A, sizeof(s64)*numItems);
    };
    
    ls_free(B);
}

#endif //IMPLEMENTATION
