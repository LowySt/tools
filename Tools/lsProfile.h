#ifndef LS_PROFILE_H
#define LS_PROFILE_H

#include "lsLog.h"

#define CAT_STR(a, b)      a##b
#define CAT_STR2(a, b)     CAT_STR(a, b)
#define ProfileFunc        auto CAT_STR2(bp, __LINE__) = BlockProfiler(__FUNCTION__, __COUNTER__)
#define ProfileBlock(name) auto CAT_STR2(bp, __LINE__) = BlockProfiler(name, __COUNTER__)

struct BlockProfilerFrame
{
    u64 diff;
    u64 childrenDiff;
    s32 hitCount;
    char *name; //NOTE: This may be a little big, but at least it's not mem alloced
    
    BlockProfilerFrame *parent;
};

constexpr s32 MAX_BPF_COUNT = 128;

struct Profiler
{
    u64 beginTimestamp;
    
    BlockProfilerFrame *currParent;
    
    BlockProfilerFrame frames[MAX_BPF_COUNT];
    s32 count;
};

static Profiler GlobalProfiler;

void ProfilerStart() { GlobalProfiler.beginTimestamp = __rdtsc(); };

void ProfilerFlush()
{
    u64 max = __rdtsc() - GlobalProfiler.beginTimestamp;
    
    ls_log("Clock Time assuming the timer is running at 4.2Ghz\n");
    for(s32 i = GlobalProfiler.count-1; i >= 0; i--)
    {
        u64 diff        = GlobalProfiler.frames[i].diff;
        u64 exDiff      = GlobalProfiler.frames[i].diff - GlobalProfiler.frames[i].childrenDiff;
        u64 timeInMs    = diff / 4200000;
        char *blockName = GlobalProfiler.frames[i].name;
        
        f64 percentage   = ((f64)diff / (f64)max)*100.0;
        f64 exPercentage = ((f64)exDiff / (f64)max)*100.0;
        ls_log("In {36char*} {12u64} ({5u64} ms) [~{6.2f64}%] [~{6.2f64}% Exclusive]",
               blockName, diff, timeInMs, percentage, exPercentage);
    }
}

struct BlockProfiler
{
    char *name;
    u64 begin;
    s32 index;
    
    BlockProfiler(char *f, s32 idx)
    {
        name  = f;
        index = idx;
        begin = __rdtsc();
        
        GlobalProfiler.frames[index].parent = GlobalProfiler.currParent;
        GlobalProfiler.currParent = GlobalProfiler.frames + index;
    };
    
    ~BlockProfiler()
    {
        BlockProfilerFrame *frame  = GlobalProfiler.frames + index;
        BlockProfilerFrame *parent = frame->parent;
        
        //NOTE: Multiple Hits.
        if(frame->name != NULL)
        {
            frame->diff         += __rdtsc() - begin;
            frame->hitCount     += 1;
            
            if(parent) { parent->childrenDiff = frame->diff; }
        }
        else
        {
            frame->diff           = __rdtsc() - begin;
            frame->name           = name;
            GlobalProfiler.count += 1;
            
            if(parent) { parent->childrenDiff = frame->diff; }
        }
        
        GlobalProfiler.currParent = parent;
    };
};



#endif //LS_PROFILE_H
