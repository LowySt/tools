#ifndef LS_RAND_H
#define LS_RAND_H

extern "C"
{
    /*return 0 if rdrand failed */
    u16 ls_rand16();
    u32 ls_rand32();
    u64 ls_rand64();
    
    void ls_fillBufferRand(u8 *data, u32 sizeOfBuffer);
}

#endif

#ifdef LS_RAND_IMPLEMENTATION

u16 ls_rand16()
{ 
    u16 result = 0;
    s32 success = _rdrand16_step(&result);
    if(success == 1) return result;
    else if (success == 0) return 0;
    return 0;
}

u32 ls_rand32()
{ 
    u32 result = 0;
    s32 success = _rdrand32_step(&result);
    if(success == 1) return result;
    else if (success == 0) return 0;
    return 0;
}

u64 ls_rand64()
{ 
    u64 result = 0;
    s32 success = _rdrand64_step(&result);
    if(success == 1) return result;
    else if (success == 0) return 0;
    return 0;
}

void ls_fillBufferRand(u8 *data, u32 sizeOfBuffer)
{
    for(u32 i = 0; i < sizeOfBuffer; i++)
    {
        u16 rand = ls_rand16();
        data[i] = (u8)rand;
    }
}


#endif



