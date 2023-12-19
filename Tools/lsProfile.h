#ifndef LS_PROFILE_H
#define LS_PROFILE_H

#include <intrin.h>

#ifndef DO_PROFILE
#define DO_PROFILE 0
#endif

typedef unsigned long long u64;
typedef int s32;
typedef int b32;

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

enum RepetitionTesterState
{
    REPTESTER_UNDEFINED,
    REPTESTER_TESTING,
    REPTESTER_COMPLETED,
    REPTESTER_ERROR,
};

enum RepetitionTesterValues
{
    REPTESTER_TOT,
    REPTESTER_MIN,
    REPTESTER_MAX,
    REPTESTER_COUNT,
    REPTESTER_BYTES,
    REPTESTER_PAGE_FAULTS,
    
    REPTESTER_VALUES_COUNT
};

struct RepetitionTester
{
    RepetitionTesterState state;
    
    u64 values[REPTESTER_VALUES_COUNT];
    
    u64 timerFreq;
    u64 beginTime;
    
    u64 blockOpen;
    u64 blockClose;
    
    u64 timeout;
    u64 currTime;
};

RepetitionTester repTester_Init(u64 timerFrequency, u64 timeoutInSeconds);
void repTester_Begin(RepetitionTester *t);
void repTester_End(RepetitionTester *t);
void repTester_Error(RepetitionTester *t, const char *s);
b32  repTester_isTesting(RepetitionTester *t);

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
                ls_log("In [{9s32}] {36char*} {12u64} ({5u64} ms) [~{6.2f64}%] [~{6.2f64}% Exclusive]",
                       frame->hitCount, blockName, diff, timeInMs, percentage, exPercentage);
            }
            else
            {
                f64 totalMbytes = (f64)frame->bytesProcessed / (1024.0*1024.0); //(f64)MBytes(1);
                f64 BytesPerSecond = frame->bytesProcessed / ((f64)timeInMs / 1000.0);
                f64 GbPerSecond = BytesPerSecond / (1024.0*1024.0*1024.0);
                
                ls_log("In [{9s32}] {36char*} {12u64} ({5u64} ms) [~{6.2f64}%] [~{6.2f64}% Exclusive]"
                       " {8.2f64} Mbytes; {6.2f64} Gb/s",
                       frame->hitCount, blockName, diff, timeInMs, percentage, 
                       exPercentage, totalMbytes, GbPerSecond);
            }
        }
        
        frame += 1;
    }
    
    ls_log("Finished\n");
}


/*--------------------------------------*/
/*              REP TESTER              */
/*--------------------------------------*/

RepetitionTester repTester_Init(u64 timerFrequency, u64 timeoutInSeconds)
{
    RepetitionTester res      = {};
    res.state                 = REPTESTER_TESTING;
    res.timerFreq             = timerFrequency;
    res.values[REPTESTER_MIN] = UINT64_MAX;
    res.timeout               = timeoutInSeconds*timerFrequency;
    
    return res;
}

u64 repTester_GetPageFaults()
{
#ifdef LS_PLAT_WINDOWS
    PROCESS_MEMORY_COUNTERS processMemoryCounters = {};
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    BOOL res = GetProcessMemoryInfo(proc, &processMemoryCounters, sizeof(PROCESS_MEMORY_COUNTERS));
    if(res == 0) { AssertMsg(FALSE, "GetProcessMemoryInfo Failed\n"); }
    return (u64)processMemoryCounters.PageFaultCount;
#else
    return -1;
#endif
}

void repTester_Begin(RepetitionTester *t)
{
    t->beginTime = __rdtsc();
    t->blockOpen += 1;
}

void repTester_End(RepetitionTester *t, u64 bytesProcessed = 0)
{
    u64 interval                      = __rdtsc() - t->beginTime;
    t->currTime                      += interval;
    t->values[REPTESTER_TOT]         += interval;
    t->values[REPTESTER_COUNT]       += 1;
    t->values[REPTESTER_BYTES]       += bytesProcessed;
    t->values[REPTESTER_PAGE_FAULTS] += repTester_GetPageFaults();
    
    if(interval > t->values[REPTESTER_MAX])      { t->values[REPTESTER_MAX] = interval; }
    else if(interval < t->values[REPTESTER_MIN]) { t->values[REPTESTER_MIN] = interval; t->currTime = 0; }
    
    t->blockClose += 1;
}

void repTester_Error(RepetitionTester *t, const char *s)
{
    t->state = REPTESTER_ERROR;
    ls_log("[REPTESTER ERROR]: {char *}", s);
}

b32 repTester_isTesting(RepetitionTester *t)
{
    if(t->state != REPTESTER_TESTING) { return FALSE; }
    
    if(t->currTime >= t->timeout)
    {
        t->state = REPTESTER_COMPLETED;
        
        f64 minInSec = (f64)t->values[REPTESTER_MIN] / (f64)t->timerFreq;
        f64 maxInSec = (f64)t->values[REPTESTER_MAX] / (f64)t->timerFreq;
        u64 avg     = t->values[REPTESTER_TOT] / t->values[REPTESTER_COUNT];
        f64 avgInSec = (f64)avg / (f64)t->timerFreq;
        
        f64 bytesPerCount = (f64)t->values[REPTESTER_BYTES] / (f64)t->values[REPTESTER_COUNT];
        
        f64 BytesPerSecondMin = bytesPerCount / minInSec;
        f64 GbPerSecondMin    = BytesPerSecondMin / (1024.0*1024.0*1024.0);
        f64 BytesPerSecondMax = bytesPerCount / maxInSec;
        f64 GbPerSecondMax    = BytesPerSecondMax / (1024.0*1024.0*1024.0);
        f64 BytesPerSecondAvg = bytesPerCount / avgInSec;
        f64 GbPerSecondAvg    = BytesPerSecondAvg / (1024.0*1024.0*1024.0);
        
        ls_log("Min: {9u64} ({4.2f64} ms) {4.2f64} Gb/s", t->values[REPTESTER_MIN], minInSec*1000.0, GbPerSecondMin);
        ls_log("Max: {9u64} ({4.2f64} ms) {4.2f64} Gb/s", t->values[REPTESTER_MAX], maxInSec*1000.0, GbPerSecondMax);
        ls_log("Avg: {9u64} ({4.2f64} ms) {4.2f64} Gb/s", avg, avgInSec*1000.0, GbPerSecondAvg);
        ls_log("Page Faults: {8u64}\n", t->values[REPTESTER_PAGE_FAULTS] / t->values[REPTESTER_COUNT]);
        return FALSE;
    }
    
    if(t->blockOpen != 0)
    {
        if(t->blockClose != t->blockOpen) { repTester_Error(t, "Mismatched Blocks!"); }
    }
    
    return t->state == REPTESTER_TESTING;
}


#else

void ProfilerFlush() { ProfilerEnd(); }

RepetitionTester repTester_Init(u64 timerFrequency, u64 timeoutInSeconds) { return {}; }
u64 repTester_GetPageFaults() { return 0; }
void repTester_Begin(RepetitionTester *t) { return; }
void repTester_End(RepetitionTester *t, u64 bytesProcessed = 0) { return; }
void repTester_Error(RepetitionTester *t, const char *s) { return; }
b32 repTester_isTesting(RepetitionTester *t) { return FALSE; }

#endif //DO_PROFILE



#endif //LS_PROFILE_IMPLEMENTATION