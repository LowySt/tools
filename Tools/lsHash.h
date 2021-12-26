#ifndef LS_HASH_H
#define LS_HASH_H

#include "lsCRT.h"

struct MD5_128
{
    u32    v32[4]; 
    u64    v64[2];
    char   v128[16];
};

typedef u64 (*hashFunc)(void *, u32);

struct hashEntry
{
    void *data;
    
    hashEntry *next = 0;
    hashEntry *prev = 0;
};

struct HashTable
{
    hashEntry *entries;
    
    u32 size;
    u32 numElements;
    
    hashFunc Func = 0;
};

extern "C"
{
    HashTable  ls_hashTAlloc(u32 size);
    void       ls_hashTFreeTable(HashTable *h);
    void       ls_hashTSetHashFunc(HashTable *h, hashFunc f);
    
    void       ls_hashTAdd(HashTable *h, void *key, void *data);
    b32        ls_hashTAddUnique(HashTable *h, void *key, void *data);
    
    void       ls_hashTKeyModify(HashTable *h, void *key, void *newVal);
    void       ls_hashTKeyModifyAndFree(HashTable *h, void *key, void *newVal);
    
    void       ls_hashTRemove(HashTable *h, void *key);
    
    hashEntry *ls_hashTVal(HashTable *h, void *key);
    
    /*---------------------*/
    /*  HASHING FUNCTIONS  */
    /*---------------------*/
    u64     ls_AES128(void *data, u32 _size);
    MD5_128 ls_MD5(string &v);
};

#endif

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

u32 MD5_F(u32 S0, u32 S1, u32 S2)
{ return ((S0 & S1) | (~S0 & S2)); }

u32 MD5_G(u32 S0, u32 S1, u32 S2)
{ return ((S0 & S2) | (S1 & ~S2)); }

u32 MD5_H(u32 S0, u32 S1, u32 S2)
{ return (S0 ^ S1 ^ S2); }

u32 MD5_I(u32 S0, u32 S1, u32 S2)
{ return (S1 ^ (S0 | ~S2)); }

#if 0
MD5_128 ls_MD5(string &v)
{
    MD5_128 Result = {};
    
    dataBuffer msg((u8 *)v.data, v.len);
    
    u32 numBlocks = (v.len / 56) + 1;
    
    /*Pad the message*/
    msg += (u8)0x80;
    
    while((msg.used % 64) != 56)
    { msg += (u8)0x00; }
    
    u64 originalLengthInBits = (u64)((u64)v.len * 8ull);
    msg += originalLengthInBits;
    
    Assert((msg.used % 64) == 0);
    
    u32 shift[] = 
    {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    
    u32 sineTable[] = 
    {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };
    /*NOTE: Fucking ENDIANESS AAAAAH 0x01234567 == 0x67452301 !*/
    u32 A0 = 0x67452301;
    u32 B0 = 0xEFCDAB89;
    u32 C0 = 0x98BADCFE;
    u32 D0 = 0x10325476;
    
    /*TODO: Need to decide which version I want?*/
#if 0
    for(u32 i = 0; i < numBlocks; i++)
    {
        u32 chunks[16];
        
        for(u32 j = 0; j < 16; j++)
        { ls_memcpy((u32 *)msg.data + j + (i*16), chunks + j, sizeof(u32)); }
        
        u32 A = A0;
        u32 B = B0;
        u32 C = C0;
        u32 D = D0;
        
        for(u32 j = 0; j < 64; j++)
        {
            u32 F, g;
            
            if(j >= 0 && j <= 15)
            {
                F = MD5_F(B, C, D);
                g = j;
            }
            else if(j >= 16 && j <= 31)
            {
                F = MD5_G(B, C, D);
                g = (5*j + 1) % 16;
            }
            else if(j >= 32 && j <= 47)
            {
                F = MD5_H(B, C, D);
                g = (3*j + 5) % 16;
            }
            else if(j >= 48 && j <= 63)
            {
                F = MD5_I(B, C, D);
                g = (7*j) % 16;
            }
            
            F = F + A + sineTable[j] + chunks[g];
            A = D;
            D = C;
            C = B;
            u32 FRot = ((F << shift[j]) | (F >> (32-shift[j])));
            B = B + FRot;
        }
        
        A0 = A0 + A;
        B0 = B0 + B;
        C0 = C0 + C;
        D0 = D0 + D;
    }
#else
    
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
    
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
    
#define FF(a, b, c, d, x, s, ac) { \
(a) += F ((b), (c), (d)) + (x) + (u32)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
(a) += G ((b), (c), (d)) + (x) + (u32)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
(a) += H ((b), (c), (d)) + (x) + (u32)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
(a) += I ((b), (c), (d)) + (x) + (u32)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
    for(u32 i = 0; i < numBlocks; i++)
    {
        u32 chunk[16];
        
        for(u32 j = 0; j < 16; j++)
        { ls_memcpy((u32 *)msg.data + j + (i*16), chunk + j, sizeof(u32)); }
        
        u32 A = A0;
        u32 B = B0;
        u32 C = C0;
        u32 D = D0;
        
        /* Round 1 */
        FF (A, B, C, D, chunk[ 0], shift[0], 0xd76aa478); /* 1 */
        FF (D, A, B, C, chunk[ 1], shift[1], 0xe8c7b756); /* 2 */
        FF (C, D, A, B, chunk[ 2], shift[2], 0x242070db); /* 3 */
        FF (B, C, D, A, chunk[ 3], shift[3], 0xc1bdceee); /* 4 */
        FF (A, B, C, D, chunk[ 4], shift[0], 0xf57c0faf); /* 5 */
        FF (D, A, B, C, chunk[ 5], shift[1], 0x4787c62a); /* 6 */
        FF (C, D, A, B, chunk[ 6], shift[2], 0xa8304613); /* 7 */
        FF (B, C, D, A, chunk[ 7], shift[3], 0xfd469501); /* 8 */
        FF (A, B, C, D, chunk[ 8], shift[0], 0x698098d8); /* 9 */
        FF (D, A, B, C, chunk[ 9], shift[1], 0x8b44f7af); /* 10 */
        FF (C, D, A, B, chunk[10], shift[2], 0xffff5bb1); /* 11 */
        FF (B, C, D, A, chunk[11], shift[3], 0x895cd7be); /* 12 */
        FF (A, B, C, D, chunk[12], shift[0], 0x6b901122); /* 13 */
        FF (D, A, B, C, chunk[13], shift[1], 0xfd987193); /* 14 */
        FF (C, D, A, B, chunk[14], shift[2], 0xa679438e); /* 15 */
        FF (B, C, D, A, chunk[15], shift[3], 0x49b40821); /* 16 */
        
        /* Round 2 */
        GG (A, B, C, D, chunk[ 1], shift[16], 0xf61e2562); /* 17 */
        GG (D, A, B, C, chunk[ 6], shift[17], 0xc040b340); /* 18 */
        GG (C, D, A, B, chunk[11], shift[18], 0x265e5a51); /* 19 */
        GG (B, C, D, A, chunk[ 0], shift[19], 0xe9b6c7aa); /* 20 */
        GG (A, B, C, D, chunk[ 5], shift[16], 0xd62f105d); /* 21 */
        GG (D, A, B, C, chunk[10], shift[17], 0x02441453); /* 22 */
        GG (C, D, A, B, chunk[15], shift[18], 0xd8a1e681); /* 23 */
        GG (B, C, D, A, chunk[ 4], shift[19], 0xe7d3fbc8); /* 24 */
        GG (A, B, C, D, chunk[ 9], shift[16], 0x21e1cde6); /* 25 */
        GG (D, A, B, C, chunk[14], shift[17], 0xc33707d6); /* 26 */
        GG (C, D, A, B, chunk[ 3], shift[18], 0xf4d50d87); /* 27 */
        GG (B, C, D, A, chunk[ 8], shift[19], 0x455a14ed); /* 28 */
        GG (A, B, C, D, chunk[13], shift[16], 0xa9e3e905); /* 29 */
        GG (D, A, B, C, chunk[ 2], shift[17], 0xfcefa3f8); /* 30 */
        GG (C, D, A, B, chunk[ 7], shift[18], 0x676f02d9); /* 31 */
        GG (B, C, D, A, chunk[12], shift[19], 0x8d2a4c8a); /* 32 */
        
        /* Round 3 */
        HH (A, B, C, D, chunk[ 5], shift[32], 0xfffa3942); /* 33 */
        HH (D, A, B, C, chunk[ 8], shift[33], 0x8771f681); /* 34 */
        HH (C, D, A, B, chunk[11], shift[34], 0x6d9d6122); /* 35 */
        HH (B, C, D, A, chunk[14], shift[35], 0xfde5380c); /* 36 */
        HH (A, B, C, D, chunk[ 1], shift[32], 0xa4beea44); /* 37 */
        HH (D, A, B, C, chunk[ 4], shift[33], 0x4bdecfa9); /* 38 */
        HH (C, D, A, B, chunk[ 7], shift[34], 0xf6bb4b60); /* 39 */
        HH (B, C, D, A, chunk[10], shift[35], 0xbebfbc70); /* 40 */
        HH (A, B, C, D, chunk[13], shift[32], 0x289b7ec6); /* 41 */
        HH (D, A, B, C, chunk[ 0], shift[33], 0xeaa127fa); /* 42 */
        HH (C, D, A, B, chunk[ 3], shift[34], 0xd4ef3085); /* 43 */
        HH (B, C, D, A, chunk[ 6], shift[35], 0x04881d05); /* 44 */
        HH (A, B, C, D, chunk[ 9], shift[32], 0xd9d4d039); /* 45 */
        HH (D, A, B, C, chunk[12], shift[33], 0xe6db99e5); /* 46 */
        HH (C, D, A, B, chunk[15], shift[34], 0x1fa27cf8); /* 47 */
        HH (B, C, D, A, chunk[ 2], shift[35], 0xc4ac5665); /* 48 */
        
        /* Round 4 */
        II (A, B, C, D, chunk[ 0], shift[48], 0xf4292244); /* 49 */
        II (D, A, B, C, chunk[ 7], shift[49], 0x432aff97); /* 50 */
        II (C, D, A, B, chunk[14], shift[50], 0xab9423a7); /* 51 */
        II (B, C, D, A, chunk[ 5], shift[51], 0xfc93a039); /* 52 */
        II (A, B, C, D, chunk[12], shift[48], 0x655b59c3); /* 53 */
        II (D, A, B, C, chunk[ 3], shift[49], 0x8f0ccc92); /* 54 */
        II (C, D, A, B, chunk[10], shift[50], 0xffeff47d); /* 55 */
        II (B, C, D, A, chunk[ 1], shift[51], 0x85845dd1); /* 56 */
        II (A, B, C, D, chunk[ 8], shift[48], 0x6fa87e4f); /* 57 */
        II (D, A, B, C, chunk[15], shift[49], 0xfe2ce6e0); /* 58 */
        II (C, D, A, B, chunk[ 6], shift[50], 0xa3014314); /* 59 */
        II (B, C, D, A, chunk[13], shift[51], 0x4e0811a1); /* 60 */
        II (A, B, C, D, chunk[ 4], shift[48], 0xf7537e82); /* 61 */
        II (D, A, B, C, chunk[11], shift[49], 0xbd3af235); /* 62 */
        II (C, D, A, B, chunk[ 2], shift[50], 0x2ad7d2bb); /* 63 */
        II (B, C, D, A, chunk[ 9], shift[51], 0xeb86d391); /* 64 */
        
        A0 += A;
        B0 += B;
        C0 += C;
        D0 += D;
    }
    
#undef F
#undef G
#undef H
#undef I
#undef ROTATE_LEFT
#undef FF
#undef GG
#undef HH
#undef II
    
#endif
    
    msg.free();
    
    /* BUILD 64bit Sections of the 128bit Hash*/
    
    Result.v64[0] = (u64)(B0 & 0x000000FF) << 24 | 
        (u64)(B0 & 0x0000FF00) << 8  |
        (u64)(B0 & 0x00FF0000) >> 8  | 
        (u64)(B0 & 0xFF000000) >> 24 | 
        (u64)(A0 & 0x000000FF) << 56 | 
        (u64)(A0 & 0x0000FF00) << 40 | 
        (u64)(A0 & 0x00FF0000) << 24 | 
        (u64)(A0 & 0xFF000000) << 8;
    
    Result.v64[1] = (u64)(D0 & 0x000000FF) << 24 | 
        (u64)(D0 & 0x0000FF00) << 8  |
        (u64)(D0 & 0x00FF0000) >> 8  | 
        (u64)(D0 & 0xFF000000) >> 24 | 
        (u64)(C0 & 0x000000FF) << 56 | 
        (u64)(C0 & 0x0000FF00) << 40 | 
        (u64)(C0 & 0x00FF0000) << 24 | 
        (u64)(C0 & 0xFF000000) << 8;
    
    Result.v32[0] = (u32)(Result.v64[0] >> 32);
    Result.v32[1] = (u32)(Result.v64[0] & 0x00000000FFFFFFFF);
    Result.v32[2] = (u32)(Result.v64[1] >> 32);;
    Result.v32[3] = (u32)(Result.v64[1] & 0x00000000FFFFFFFF);
    
    Result.v128[0]  = (u8)((Result.v32[0] & 0xFF000000) >> 24);
    Result.v128[1]  = (u8)((Result.v32[0] & 0x00FF0000) >> 16);
    Result.v128[2]  = (u8)((Result.v32[0] & 0x0000FF00) >> 8);
    Result.v128[3]  = (u8)((Result.v32[0] & 0x000000FF));
    Result.v128[4]  = (u8)((Result.v32[1] & 0xFF000000) >> 24);
    Result.v128[5]  = (u8)((Result.v32[1] & 0x00FF0000) >> 16);
    Result.v128[6]  = (u8)((Result.v32[1] & 0x0000FF00) >> 8);
    Result.v128[7]  = (u8)((Result.v32[1] & 0x000000FF));
    Result.v128[8]  = (u8)((Result.v32[2] & 0xFF000000) >> 24);
    Result.v128[9]  = (u8)((Result.v32[2] & 0x00FF0000) >> 16);
    Result.v128[10] = (u8)((Result.v32[2] & 0x0000FF00) >> 8);
    Result.v128[11] = (u8)((Result.v32[2] & 0x000000FF));
    Result.v128[12] = (u8)((Result.v32[3] & 0xFF000000) >> 24);
    Result.v128[13] = (u8)((Result.v32[3] & 0x00FF0000) >> 16);
    Result.v128[14] = (u8)((Result.v32[3] & 0x0000FF00) >> 8);
    Result.v128[15] = (u8)((Result.v32[3] & 0x000000FF));
    
    return Result;
}

u64 baseHash(void *d, u32 s)
{
    string tmp = ls_strAlloc(s);
    tmp.len = s;
    ls_memcpy(d, tmp.data, s);
    
    MD5_128 result = ls_MD5(tmp);
    
    ls_strFree(&tmp);
    
    return result.v64[0];
}

HashTable ls_hashTAlloc(u32 size)
{
    HashTable Result = {};
    
    Result.entries = (hashEntry *)ls_alloc(sizeof(hashEntry)*size);
    Result.size = size;
    Result.numElements = 0;
    
    Result.Func = baseHash;
    
    return Result;
}

void hashTFreeEntry(hashEntry *v)
{
    hashEntry *curr = v;
    u32 depth = 0;
    while(TRUE)
    { 
        if(curr->next) { curr = curr->next; depth++; }
        else { break; }
    }
    
    while(depth--)
    {
        hashEntry *newCurr = curr->prev;
        ls_free(curr);
        curr = newCurr;
    }
    
    if(v->next) { ls_free(v->next); }
}

void ls_hashTFreeTable(HashTable *h)
{
    ls_free(h->entries);
    h->entries = 0;
    h->size = 0;
    h->numElements = 0;
}

void ls_hashTSetHashFunc(HashTable *h, hashFunc f)
{ h->Func = f; }

u32 hashTGetIdx(HashTable *h, void *key)
{
    u16 u16MaxVal = u16(-1);
    
    /* TODO: This is hardcoded to work with strings. It shouldn't be. */
    
    string *k = (string *)key;
    u64 hash = h->Func(k->data, k->len);
    
    u16 idxRange = (u16)hash;
    u32 Idx = u32((f32)idxRange*((f32)h->size / (f32) u16MaxVal));
    
    return Idx;
}

void hashTAddByIdx(HashTable *h, u32 Idx, void *data)
{
    hashEntry *curr = &h->entries[Idx];
    
    while(curr->next) {curr = curr->next; }
    
    if(curr->data == 0)
    { curr->data = data; }
    else 
    {
        curr->next = (hashEntry *)ls_alloc(sizeof(hashEntry));
        (curr->next)->prev = curr;
        curr = curr->next;
        
        curr->data = data;
    }
    
    h->numElements += 1;
}

void ls_hashTAdd(HashTable *h, void *key, void *data)
{
    u32 Idx = hashTGetIdx(h, key);
    
    hashTAddByIdx(h, Idx, data);
}

b32 ls_hashTAddUnique(HashTable *h, void *key, void *data)
{
    u32 Idx = hashTGetIdx(h, key);
    hashEntry *curr = &h->entries[Idx];
    
    do
    {
        if(curr->data == data)
        { return FALSE; }
        curr = curr->next;
    }
    while(curr);
    
    hashTAddByIdx(h, Idx, data);
    
    return TRUE;
}


void ls_hashTKeyModify(HashTable *h, void *key, void *newVal)
{
    u32 Idx = hashTGetIdx(h, key);
    hashEntry *curr = &h->entries[Idx];
    
    curr->data = newVal;
}

void ls_hashTKeyModifyAndFree(HashTable *h, void *key, void *newVal)
{
    u32 Idx = hashTGetIdx(h, key);
    hashEntry *curr = &h->entries[Idx];
    
    void *oldData = curr->data;
    curr->data = newVal;
    ls_free(oldData);
}

void ls_hashTRemove(HashTable *h, void *key)
{
    u32 Idx = hashTGetIdx(h, key);
    hashEntry *curr = &h->entries[Idx];
    
    hashTFreeEntry(curr);
    
    h->numElements -= 1;
    
    ls_free(curr);
}

hashEntry *ls_hashTVal(HashTable *h, void *key)
{ 
    hashEntry *Result = NULL;
    
    u32 Idx = hashTGetIdx(h, key);
    
    Result = &h->entries[Idx];
    
    return Result;
}
#endif

#endif