#ifndef LS_ARENA_H
#define LS_ARENA_H

#ifdef LS_PLAT_WINDOWS
#include "lsWindows.h"
#endif

#ifdef LS_PLAT_LINUX
#include "lsLinux.h"
#endif

struct Arena
{
    void *data;
    u32 id;
};

extern "C"
{
    Arena ls_arenaCreate(u64 arenaSize);
    void  ls_arenaDestroy(Arena a);
    
    void  ls_arenaUse(Arena a);
    void  ls_arenaStop();
    void  ls_arenaClear(Arena a);
};


#endif //LS_ARENA_H


#ifdef LS_ARENA_IMPLEMENTATION

Arena ls_arenaCreate(u64 arenaSize)
{
#ifdef LS_PLAT_WINDOWS
    u32 id = 0;
    void *p = windows_createArena(arenaSize, &id);
    Arena Res = {p, id};
    return Res;
#endif
    
#ifdef LS_PLAT_LINUX
    u32 id = 0;
    void *p = linux_createArena(arenaSize, &id);
    Arena Res = {p, id};
    return Res;
#endif
}


void ls_arenaDestroy(Arena a)
{
#ifdef LS_PLAT_WINDOWS
    return windows_destroyArena(a.id);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_destroyArena(a.id);
#endif
}


void ls_arenaUse(Arena a)
{
#ifdef LS_PLAT_WINDOWS
    return windows_useArena(a.id);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_useArena(a.id);
#endif
}

void ls_arenaStop()
{
#ifdef LS_PLAT_WINDOWS
    return windows_stopArena();
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_stopArena();
#endif
}

void ls_arenaClear(Arena a)
{
#ifdef LS_PLAT_WINDOWS
    return windows_clearArena(a.id);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_clearArena(a.id);
#endif
}

#endif //IMPLEMENTATION
