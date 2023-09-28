#ifndef LS_PROFILE_H
#define LS_PROFILE_H

#include <intrin.h>

#ifndef DO_PROFILE
#define DO_PROFILE 0
#endif

typedef unsigned long long u64;
typedef int s32;

struct BlockProfilerFrame
{
    u64 elapsedInclusive;  //NOTE: Own Time + Children Time
    u64 elapsedExclusive;  //NOTE: Own Time Without Children Time
    u64 bytesProcessed;
    s32 hitCount;
    char *name; //NOTE: This may be a little big, but at least it's not mem alloced
};

constexpr s32 MAX_BPF_COUNT = 128;

struct Profiler
{
    u64 beginTimestamp;
    BlockProfilerFrame frames[MAX_BPF_COUNT];
};

static Profiler GlobalProfiler;
static s32      GlobalParentIndex;

#if DO_PROFILE

#define PROF_CAT_STR(a, b)      a##b
#define PROF_CAT_STR2(a, b)     PROF_CAT_STR(a, b)
#define ProfileBlockBandwidth(name, bytes)    auto PROF_CAT_STR2(bp, __LINE__) = BlockProfiler(name, __COUNTER__ + 1, bytes)
#define ProfileBlock(name) ProfileBlockBandwidth(name, 0)
#define ProfileFunc             ProfileBlock(__FUNCTION__)
#define ProfileEndCounterCheck  static_assert(__COUNTER__ < MAX_BPF_COUNT, "Too many Profile Points\n")

struct BlockProfiler
{
    u64 begin;
    u64 old;
    s32 index;
    s32 parentIdx;
    
    BlockProfiler(char *f, s32 idx, u64 bytesProcessed)
    {
        parentIdx = GlobalParentIndex;
        index     = idx;
        begin     = __rdtsc();
        old       = GlobalProfiler.frames[index].elapsedInclusive;
        
        GlobalParentIndex = index;
        GlobalProfiler.frames[index].name   = f;
        GlobalProfiler.frames[index].bytesProcessed += bytesProcessed;
    };
    
    ~BlockProfiler()
    {
        u64 elapsed = __rdtsc() - begin;
        GlobalParentIndex = parentIdx;
        
        BlockProfilerFrame *frame  = GlobalProfiler.frames + index;
        BlockProfilerFrame *parent = GlobalProfiler.frames + parentIdx;
        
        parent->elapsedExclusive -= elapsed;
        frame->elapsedExclusive  += elapsed;
        frame->elapsedInclusive   = old + elapsed;
        frame->hitCount += 1;
    };
};

#else

#define PROF_CAT_STR(...)
#define PROF_CAT_STR2(...)
#define ProfileBlockBandwidth(...)
#define ProfileBlock(...)
#define ProfileFunc  ProfileBlock(__FUNCTION__)
#define ProfileEndCounterCheck

#endif //DO_PROFILE

#endif //LS_PROFILE_H

#ifdef LS_PROFILE_IMPLEMENTATION

void ProfilerStart() { GlobalProfiler.beginTimestamp = __rdtsc(); };
u64 ProfilerEnd()
{
    u64 max = __rdtsc() - GlobalProfiler.beginTimestamp;
    
    ls_log("Clock Time assuming the timer is running at 4.2Ghz");
    ls_log("Total: {12u64} ({5u64} ms)\n", max, max / 4200000);
    
    return max;
}

#if DO_PROFILE

void ProfilerFlush()
{
    u64 max = ProfilerEnd();
    
    BlockProfilerFrame *frame = &GlobalProfiler.frames[0];
    BlockProfilerFrame *end   = &GlobalProfiler.frames[MAX_BPF_COUNT];
    while(frame != end)
    {
        if(frame->elapsedInclusive != 0)
        {
            u64 diff        = frame->elapsedInclusive;
            u64 exDiff      = frame->elapsedExclusive;
            
            u64 timeInMs    = diff / 4200000;
            char *blockName = frame->name;
            
            f64 percentage   = ((f64)diff / (f64)max)*100.0;
            f64 exPercentage = ((f64)exDiff / (f64)max)*100.0;
            
            if(frame->bytesProcessed == 0)
            {
                ls_log("In [{8s32}] {36char*} {12u64} ({5u64} ms) [~{6.2f64}%] [~{6.2f64}% Exclusive]",
                       frame->hitCount, blockName, diff, timeInMs, percentage, exPercentage);
            }
            else
            {
                f64 totalMbytes = (f64)frame->bytesProcessed / (1024.0*1024.0); //(f64)MBytes(1);
                f64 BytesPerSecond = frame->bytesProcessed / ((f64)timeInMs / 1000.0);
                f64 GbPerSecond = BytesPerSecond / (1024.0*1024.0*1024.0);
                
                ls_log("In [{8s32}] {36char*} {12u64} ({5u64} ms) [~{6.2f64}%] [~{6.2f64}% Exclusive]"
                       " {8.2f64} Mbytes; {6.2f64} Gb/s",
                       frame->hitCount, blockName, diff, timeInMs, percentage, 
                       exPercentage, totalMbytes, GbPerSecond);
            }
        }
        
        frame += 1;
    }
    
    ls_log("Finished");
}

#else

void ProfilerFlush() { ProfilerEnd(); }

#endif //DO_PROFILE

#endif //LS_PROFILE_IMPLEMENTATION