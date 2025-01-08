#ifndef LS_ARENA_H
#define LS_ARENA_H

#ifdef LS_PLAT_WINDOWS
#include "lsWindows.h"
#endif

#ifdef LS_PLAT_LINUX
#include "lsLinux.h"
#endif

#include "lsCRT.h"

struct Arena
{
    void *data;
    u32 id;
};

extern "C"
{
    Arena ls_arenaCreate(u64 arenaSize, char *name);
    void  ls_arenaDestroy(Arena a);
    
    Arena ls_arenaUse(Arena a);
    void  ls_arenaStop();
    void  ls_arenaClear(Arena a);
};


#endif //LS_ARENA_H


#ifdef LS_ARENA_IMPLEMENTATION

Arena ls_arenaCreate(u64 arenaSize, char *name=NULL)
{
#ifdef LS_PLAT_WINDOWS
    u32 id = 0;
    void *p = windows_createArena(arenaSize, &id, name);
    Arena Res = {p, id};
#endif
    
#ifdef LS_PLAT_LINUX
    u32 id = 0;
    void *p = linux_createArena(arenaSize, &id, name);
    Arena Res = {p, id};
#endif
    
    return Res;
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


Arena ls_arenaUse(Arena a)
{
    InternalArena prevArena = {};
#ifdef LS_PLAT_WINDOWS
    prevArena = windows_useArena(a.id);
    Arena previous = {prevArena.data, prevArena.id};
    return previous;
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
