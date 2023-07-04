#ifndef LS_HASH_H
#define LS_HASH_H

#include "lsCRT.h"

typedef s64 (*hashFunc)(void *, s32);

template<typename T>
struct hashEntry
{
    hashEntry *next = 0;
    hashEntry *prev = 0;
    
    s64 hash;
    T data;
};

template<typename T>
struct HashTable
{
    hashEntry<T> *entries;
    
    s32 count;
    s32 capacity;
    s32 occupancy; // Out of 100 (%)
    
    hashFunc hash;
};

/*---------------------*/
/*  HASHING FUNCTIONS  */
/*---------------------*/
u64 ls_AES128(void *data, u32 _size);

#endif //LS_HASH_H

#ifdef LS_HASH_IMPLEMENTATION

// NOTE: Is it really AES128??
u64 ls_AES128(void *data, u32 _size)
{
    u64 Result = 0;
    
    if(_size < (16*sizeof(u64)))
    { ls_printf("Error in hashFunc, passed small data\n"); return 0;}
    
    u64 S0 = ((u64 *)data)[0];
    u64 S1 = ((u64 *)data)[1];
    u64 S2 = ((u64 *)data)[2];
    u64 S3 = ((u64 *)data)[3];
    
    u64 S4 = ((u64 *)data)[4];
    u64 S5 = ((u64 *)data)[5];
    u64 S6 = ((u64 *)data)[6];
    u64 S7 = ((u64 *)data)[7];
    
    u64 S8 = ((u64 *)data)[8];
    u64 S9 = ((u64 *)data)[9];
    u64 SA = ((u64 *)data)[10];
    u64 SB = ((u64 *)data)[11];
    
    u64 SC = ((u64 *)data)[12];
    u64 SD = ((u64 *)data)[13];
    u64 SE = ((u64 *)data)[14];
    u64 SF = ((u64 *)data)[15];
    
    u32 size  = _size / 8;
    
    u32 remainderBytes = _size % 8;
    
    u64 Prime0 = 0xF4DBB963AD367BD7;
    u64 Prime1 = 0xE5378DB8A08C3593;
    u64 Prime2 = 0xB3500D18E2C45635;
    u64 Prime3 = 0x27FE1A4AE65E3445;
    
    u64 tmp = 0;
    u64 tmp2 = 0;
    u64 tmp3 = 0;
    u64 tmp4 = 0;
    
    u64 R0, R1, R2, R3;
    
    for(u32 i = 16; i < size; i++)
    {
        /*Sub!*/
        tmp = S0; S0 = S8; S8 = tmp;
        tmp = SC; SC = S7; S7 = tmp;
        tmp = S6; S6 = SD; SD = tmp;
        tmp = SB; SB = S9; S9 = tmp;
        tmp = SD; SD = S0; S0 = tmp;
        tmp = S6; S6 = S8; S8 = tmp;
        tmp = S4; S4 = S2; S2 = tmp;
        tmp = S5; S5 = SB; SB = tmp;
        tmp = S3; S3 = S8; S8 = tmp;
        tmp = S6; S6 = SE; SE = tmp;
        tmp = S1; S1 = SE; SE = tmp;
        tmp = SA; SA = S2; S2 = tmp;
        tmp = S8; S8 = S5; S5 = tmp;
        tmp = S8; S8 = S2; S2 = tmp;
        
        /*Shift Data Rows*/
        tmp = S0; tmp2 = S1; tmp3 = S2; tmp4 = S3;
        S0 = tmp3; S1 = tmp4; S2 = tmp; S4 = tmp2;
        
        tmp = S4; tmp2 = S5; tmp3 = S6; tmp4 = S7;
        S4 = tmp3; S5 = tmp4; S6 = tmp; S7 = tmp2;
        
        /*Mix Columns*/
        
        R0 = (2*S0) ^ S3 ^ S2 ^ (2*S1) ^ S1;
        R1 = (2*S1) ^ S0 ^ S3 ^ (2*S2) ^ S2;
        R2 = (2*S2) ^ S1 ^ S0 ^ (2*S3) ^ S3;
        R3 = (2*S3) ^ S2 ^ S1 ^ (2*S0) ^ S0;
        
        S0 = R0; S1 = R1; S2 = R2; S3 = R3;
        
        R0 = (2*S4) ^ S7 ^ S6 ^ (2*S5) ^ S5;
        R1 = (2*S5) ^ S4 ^ S7 ^ (2*S6) ^ S6;
        R2 = (2*S6) ^ S5 ^ S4 ^ (2*S7) ^ S7;
        R3 = (2*S7) ^ S6 ^ S5 ^ (2*S4) ^ S4;
        
        S4 = R0; S5 = R1; S6 = R2; S7 = R3;
        
        
        R0 = (2*S8) ^ SB ^ SA ^ (2*S9) ^ S9;
        R1 = (2*S9) ^ S8 ^ SB ^ (2*SA) ^ SA;
        R2 = (2*SA) ^ S9 ^ S8 ^ (2*SB) ^ SB;
        R3 = (2*SB) ^ SA ^ S9 ^ (2*S8) ^ S8;
        
        S8 = R0; S9 = R1; SA = R2; SB = R3;
        
        R0 = (2*SC) ^ SF ^ SE ^ (2*SD) ^ SD;
        R1 = (2*SD) ^ SC ^ SF ^ (2*SE) ^ SE;
        R2 = (2*SE) ^ SD ^ SC ^ (2*SF) ^ SF;
        R3 = (2*SF) ^ SE ^ SD ^ (2*SC) ^ SC;
        
        SC = R0; SD = R1; SE = R2; SF = R3;
        
        /* XOR ON EACH COLUMN */
        
        R0 = (S0 ^ S4 ^ S8 ^ SC) ^ Prime0;
        R1 = (S1 ^ S5 ^ S9 ^ SD) ^ Prime1;
        R2 = (S2 ^ S6 ^ SA ^ SE) ^ Prime2;
        R3 = (S3 ^ S7 ^ SB ^ SF) ^ Prime3;
        
        Result = R0 ^ R1 ^ R2 ^ R3;
        
        /*Repeat for next Set of Data*/
        
        S0 = ((u64 *)data)[i];
        S1 = ((u64 *)data)[i+1];
        S2 = ((u64 *)data)[i+2];
        S3 = ((u64 *)data)[i+3];
        S4 = ((u64 *)data)[i+4];
        S5 = ((u64 *)data)[i+5];
        S6 = ((u64 *)data)[i+6];
        S7 = ((u64 *)data)[i+7];
        S8 = ((u64 *)data)[i+8];
        S9 = ((u64 *)data)[i+9];
        SA = ((u64 *)data)[i+10];
        SB = ((u64 *)data)[i+11];
        SC = ((u64 *)data)[i+12];
        SD = ((u64 *)data)[i+13];
        SE = ((u64 *)data)[i+14];
        SF = ((u64 *)data)[i+15];
    }
    
    return Result;
}

s64 ls_DEKHash(void *data, s32 len)
{
    s64 hash = len;
    
    u8 *At = (u8 *)data;
    for(s32 i = 0; i < len; i++)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*At);
        At += 1;
    }
    
    return hash;
}

template<typename T>
HashTable<T> ls_hashTAlloc(s32 capacity, s32 occupancy, hashFunc hash = NULL)
{
    HashTable<T> Result = {};
    
    Result.entries     = (hashEntry<T> *)ls_alloc(sizeof(hashEntry<T>)*capacity);
    Result.capacity    = capacity;
    Result.occupancy   = occupancy;
    Result.count       = 0;
    
    if(hash == NULL) { Result.hash = ls_DEKHash; }
    else             { Result.hash = hash; }
    
    return Result;
}

template<typename T>
void ls_hashTFreeTable(HashTable<T> *h)
{
    //NOTE: Check all entries for hits
    for(s32 i = 0; i < count; i++)
    {
        hashEntry<T> *curr = entries;
        hashEntry<T> *next = curr->next;
        
        while(next)
        {
            hashEntry<T> *after = next->next;
            ls_free(next);
            next = after;
        }
    }
    
    ls_free(h->entries);
    h->entries   = NULL;
    h->count     = 0;
    h->capacity  = 0;
    h->occupancy = 0;
    h->hash      = 0;
}

template<typename T>
s64 ls_hashTGetIdx(HashTable<T> *h, T key, s64 *hashOut)
{
    AssertMsg(h != NULL, "Null hashtable pointer\n");
    
    u64 hash = h->hash(&key, sizeof(T));
    s64 index = hash % h->capacity;
    *hashOut = hash;
    
    return index;
}

template<typename T>
s64 ls_hashTAdd(HashTable<T> *h, T data)
{
    AssertMsg(h != NULL, "Null hashtable pointer\n");
    
    s32 occupancy = ((f32)h->count / (f32)h->capacity)*100;
    if(occupancy > h->occupancy) { AssertMsg(FALSE, "Hash table is full!\n"); return -1; }
    
    s64 hash = 0;
    s64 idx = ls_hashTGetIdx(h, data, &hash);
    
    hashEntry<T> *entry = h->entries + idx;
    
    //NOTE: Then the slot is empty, I can add
    T zero = {};
    if(ls_memcmp(&entry->data, &zero, sizeof(T)) == TRUE)
    {
        entry->data = data;
        entry->hash = hash;
        h->count += 1;
        return idx;
    }
    
    //NOTETODO: If it's already present, we skip it?
    if(hash == entry->hash) { return idx; }
    
    //NOTE: Otherwise, we have a hit, let's create a chain
    while(entry->next) {
        entry = entry->next;
        if(hash == entry->hash) { return idx; }
    }
    
    entry->next = (hashEntry<T> *)ls_alloc(sizeof(hashEntry<T>));
    entry->next->prev = entry;
    entry->next->data = data;
    entry->next->hash = hash;
    
    //NOTETODO: Should this be increased only for non-blocked entries?
    h->count += 1;
    
    return idx;
}

template<typename T>
T ls_hashTLookup(HashTable<T> *h, s64 index)
{
    T result = (h->entries + index)->data;
    return result;
}

#endif //LS_HASH_IMPLEMENTATION