#ifndef LS_SORT_H
#define LS_SORT_H

extern "C"
{
    void quicksort(u32 *a, u32 size);
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

void quicksort(u32 *a, u32 size)
{ qs_helper(a, 0, ((s32)size)-1); }


#endif //IMPLEMENTATION
