#ifndef LS_SORT_H
#define LS_SORT_H

//NOTE: SortFunc returns -1 if sortA is smaller than sortB, 
//                        0 if they are equal, 
//                        1 if sortA is bigger than sortB
typedef s32 (*sortFunc)(void *sortA, void *sortB);

extern "C"
{
    void ls_quicksort(u32 *a, u32 size);
    void ls_quicksortCustom(void *data, u32 elementSize, u32 numElements, sortFunc customFunc);
};


#endif //LS_SORT_H


#ifdef LS_SORT_IMPLEMENTATION

static u32 qs_partition(u32 *a, s32 low, s32 high)
{
    // pivot (Element to be placed at right position)
    u32 pivot = a[high];
    
    // Index of smaller element
    s32 i = (low - 1);
    
    for (u32 j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (a[j] <= pivot)
        {
            i++;    // increment index of smaller element
            u32 oldI = a[i];
            a[i] = a[j];
            a[j] = oldI;
        }
    }
    
    u32 oldV = a[i+1];
    a[i+1] = a[high];
    a[high] = oldV;
    
    return (i + 1);
}

static void qs_helper(u32 *a, s32 low, s32 high)
{
    if (low < high)
    {
        /* pi is partitioning index, a[pi] is now
        at right place */
        u32 pi = qs_partition(a, low, high);
        
        qs_helper(a, low, pi - 1);  // Before pi
        qs_helper(a, pi + 1, high); // After pi
    }
}

void ls_quicksort(u32 *a, u32 size)
{ qs_helper(a, 0, ((s32)size)-1); }


static u32 qsCust_partition(void *data, u32 elementSize, sortFunc customFunc, s32 lowIdx, s32 highIdx)
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
            
            ls_memcpy(replaceElem, tempBuff, elementSize);
            ls_memcpy(currElement, replaceElem, elementSize);
            ls_memcpy(tempBuff, currElement, elementSize);
        }
    }
    
    dataAt = (u8 *)data;
    dataAt += elementSize*(i+1);
    void *finalElem = (void *)dataAt;
    
    ls_memcpy(finalElem, tempBuff, elementSize);
    ls_memcpy(pivotElement, finalElem, elementSize);
    ls_memcpy(tempBuff, pivotElement, elementSize);
    
    return (i + 1);
}

static void qsCust_helper(void *data, u32 elementSize, sortFunc customFunc, s32 lowIdx, s32 highIdx)
{
    if (lowIdx < highIdx)
    {
        /* pi is partitioning index, a[pi] is now
        at right place */
        u32 pi = qsCust_partition(data, elementSize, customFunc, lowIdx, highIdx);
        
        qsCust_helper(data, elementSize, customFunc, lowIdx, pi - 1);  // Before pi
        qsCust_helper(data, elementSize, customFunc, pi + 1, highIdx); // After pi
    }
}

void ls_quicksortCustom(void *data, u32 elementSize, u32 numElements, sortFunc customFunc) 
{
    qsCust_helper(data, elementSize, customFunc, 0, ((s32)numElements)-1); 
}

#endif //IMPLEMENTATION
