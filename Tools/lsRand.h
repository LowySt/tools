#ifndef LS_RAND_H
#define LS_RAND_H


/*NOTE:
RDRAND is an instruction seeded by an on-chip entropy generator
Thus it doesn't need to be seeded to be used.

RDSEED gives access to that entropy generator, to obtain those random seeds.
*/

/*return 0 if rdrand failed */
u16 ls_rand16();
u32 ls_rand32();
u64 ls_rand64();

f64 ls_randFloatZeroOne();
f64 ls_randFloatNegativeOneToOne();

u64 ls_randRange(u64 min, u64 max);

void ls_fillBufferRand(u8 *data, u32 sizeOfBuffer);

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

f64 ls_randFloatZeroOne()
{
    u64 base = ls_rand64();
    u64 max  = u64(-1);
    f64 result = (f64)base / (f64)max;
    return result;
}

f64 ls_randFloatNegativeOneToOne()
{
    u64 max = 100000;
    u64 val  = ls_randRange(0, max);
    f64 convVal = (f64)val;
    f64 convMax = (f64)max;
    f64 fval = convVal / max;
    fval = fval * 2.0;
    fval = fval - 1.0;
    
    return fval;
}

u64 ls_randRange(u64 min, u64 max)
{
    u64 range = (max - min) + 1;
    u64 val = (ls_rand64() % range) + min;
    return val;
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



