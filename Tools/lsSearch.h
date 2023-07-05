#ifndef LS_SEARCH_H
#define LS_SEARCH_H

//NOTE: compareFunc returns -1 if A is smaller than B, 
//                           0 if they are equal,
//                           1 if A is bigger than B
typedef s32(*compareFunc)(void *A, void *B);

b32 ls_searchBinary(void *data, void *item, s32 itemSize, s32 count, compareFunc compare);

#endif //LS_SEARCH_H

#ifdef LS_SEARCH_IMPLEMENTATION

b32 ls_searchLinear(void *data, void *item, s32 itemSize, s32 count, compareFunc compare)
{
    u8 *At = (u8 *)data;
    for(s32 i = 0; i < count; i++)
    {
        u8 *Ai = At + (i*itemSize);
        if(compare(Ai, item) == 0) { return TRUE; }
    }
    
    return FALSE;
}

b32 ls_searchBinary(void *data, void *item, s32 itemSize, s32 count, compareFunc compare)
{
    s32 begin = 0;
    s32 end   = count-1;
    
    u8 *At = (u8 *)data;
    while(begin <= end)
    {
        s32 middle = (begin + end) / 2;
        u8 *Am = At + (itemSize * middle);
        s32 comparison = compare(Am, item);
        
        if(comparison == 0)  { return TRUE; }
        if(comparison == -1) { begin = middle + 1; continue; }
        if(comparison == 1)  { end   = middle - 1; continue; }
        
        AssertMsg(FALSE, "Bad compareFunc. Results must be 0 for equality, -1 for left smaller, 1 for left bigger");
    }
    
    return FALSE;
}

b32 ls_searchInterpolation(s64 *keys, s64 itemKey, s32 count)
{
    s32 begin = 0;
    s32 end   = count - 1;
    
    while((keys[end] != keys[begin]) && (itemKey >= keys[begin]) && (itemKey <= keys[end]))
    {
        s32 mid = begin + ((itemKey - keys[begin]) * (end - begin) / (keys[end] - keys[begin]));
        
        if(keys[mid] < itemKey)       { begin = mid + 1; }
        else if (itemKey < keys[mid]) { end = mid - 1; }
        else                          { return TRUE; }
    }
    
    if (itemKey == keys[begin]) { return TRUE; }
    
    return FALSE;
}

s32 ls_searchDijkstra(s64 **graph, s32 count, s32 startIdx, s32 endIdx)
{
    AssertMsg(graph != NULL, "Invaid graph pointer\n");
    AssertMsg(startIdx >= 0 && startIdx < count, "StartIdx out of range");
    AssertMsg(endIdx >= 0 && endIdx < count, "EndIdx is out of range");
    
    //NOTE: The output array.  dist[i] will hold the shortest distance
    s32 *dist = (s32 *)ls_alloc(sizeof(s32)*count);
    
    //NOTE: shortestSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    b32 *shortestSet = (s32 *)ls_alloc(sizeof(s32)*count);
    
    s32 s32Max = 0x7FFFFFFF;
    for (s32 i = 0; i < count; i++)
    {
        dist[i]        = s32Max;
        shortestSet[i] = false;
    }
    
    //NOTE: Find the index of the vertex with minimum distance value
    //      not included in the solution set
    auto minDistance = [](s32 *dist, s32 *set, s32 count) -> s32 {
        s32 min    = 0x7FFFFFFF;
        s32 minIdx = -1;
        
        for(s32 i = 0; i < count; i++)
        {
            if((set[i] == FALSE) && (dist[i] <= min))
            { min = dist[i]; minIdx = i; }
        }
        
        return minIdx;
    };
    
    //NOTE: Distance of source vertex from itself is always 0
    dist[startIdx] = 0;
    
    // Find shortest path for all vertices
    for(s32 vertexIdx = 0; vertexIdx < count - 1; vertexIdx++)
    {
        //NOTE: Pick the minimum distance vertex from the set of
        // vertices not yet processed. This is always equal to startIdx in the first iteration.
        s32 minVertex = minDistance(dist, shortestSet, count);
        
        // Mark the picked vertex as processed
        shortestSet[minVertex] = TRUE;
        
        //NOTE: Update dist value of the adjacent vertices of the picked vertex.
        for(s32 i = 0; i < count; i++)
        {
            //NOTE:Update the current vertex's distance from startIdx only if:
            //       -It is not already in the solution set
            //       -There is a valid edge between minVertex and the current vertex
            //       -The distance from startIdx to the current vertex passing from the
            //           minVertex is actually smaller.
            if(shortestSet[i] == TRUE)    { continue; }
            if(graph[minVertex][i] == 0)  { continue; }
            if(dist[minVertex] == s32Max) { continue; }
            
            if((dist[minVertex] + graph[minVertex][i]) < dist[i])
            { dist[i] = dist[minVertex] + graph[minVertex][i]; }
        }
    }
    
    return dist[endIdx];
}

#endif //LS_SEARCH_IMPLEMENTATION