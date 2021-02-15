#ifndef LS_BIGINT_HEADER
#define LS_BIGINT_HEADER

#include "lsCRT.h"
#include "lsString.h"

struct u128
{
    u64 l;
    u64 h;
};

struct u256
{
    union {
        struct {
            u64 l;
            u64 m;
            u64 t;
            u64 h;
        };
        
        u64 arr[4];
    };
};

struct u512
{
    union
    {
        struct
        {
            u256 low;
            u256 high;
        };
        struct
        {
            u64 ll;
            u64 ml;
            u64 tl;
            u64 hl;
            
            u64 lh;
            u64 mh;
            u64 th;
            u64 hh;
        };
        
        u64 arr[8];
    };
};

struct u1024
{
    union
    {
        struct
        {
            u512 low;
            u512 high;
        };
        struct
        {
            u256 lowlow;
            u256 lowhigh;
            u256 highlow;
            u256 highhigh;
        };
        struct
        {
            u64 ll;
            u64 ml;
            u64 tl;
            u64 hl;
            
            u64 lm;
            u64 mm;
            u64 tm;
            u64 hm;
            
            u64 lt;
            u64 mt;
            u64 tt;
            u64 ht;
            
            u64 lh;
            u64 mh;
            u64 th;
            u64 hh;
        };
        
        u64 arr[16];
    };
};

struct u2048
{
	union
	{
		struct
		{
			u1024 low;
			u1024 high;
		};
		struct
		{
			u64 b8;
			u64 b16;
			u64 b24;
			u64 b32;
            
			u64 b40;
			u64 b48;
			u64 b56;
			u64 b64;
            
			u64 b72;
			u64 b80;
			u64 b88;
			u64 b96;
            
			u64 b104;
			u64 b112;
			u64 b120;
			u64 b128;
            
			u64 b136;
			u64 b144;
			u64 b152;
			u64 b160;
            
			u64 b168;
			u64 b176;
			u64 b184;
			u64 b192;
            
			u64 b200;
			u64 b208;
			u64 b216;
			u64 b224;
            
			u64 b232;
			u64 b240;
			u64 b248;
			u64 b256;
		};
        
        u64 arr[32];
	};
};

struct u4096
{
	union
	{
		struct
		{
			u2048 low256;
			u2048 high256;
		};
        
		struct
		{
			u1024 low;
			u1024 med;
			u1024 tall;
			u1024 high;
		}part;
        
		struct
		{
			u64 b8;  u64 b16;
			u64 b24; u64 b32;
			u64 b40; u64 b48;
			u64 b56; u64 b64;
            
			u64 b72;  u64 b80;
			u64 b88;  u64 b96;
			u64 b104; u64 b112;
			u64 b120; u64 b128;
            
			u64 b136; u64 b144;
			u64 b152; u64 b160;
			u64 b168; u64 b176;
			u64 b184; u64 b192;
            
			u64 b200; u64 b208;
			u64 b216; u64 b224;
			u64 b232; u64 b240;
			u64 b248; u64 b256;
            
			u64 b264; u64 b280;
			u64 b288; u64 b296;
			u64 b304; u64 b312;
			u64 b320; u64 b328;
            
			u64 b336; u64 b344;
			u64 b352; u64 b360;
			u64 b368; u64 b376;
			u64 b384; u64 b392;
            
			u64 b400; u64 b408;
			u64 b416; u64 b424;
			u64 b432; u64 b440;
			u64 b448; u64 b456;
            
			u64 b464; u64 b472;
			u64 b480; u64 b488;
			u64 b496; u64 b504;
			u64 b512; u64 b520;
		};
    };
};

struct u8192
{
	union
	{
		struct
		{
            u4096 low512;
			u4096 high512;
		};
        
		struct
		{
			u2048 low;
			u2048 med;
			u2048 tall;
			u2048 high;
		}part;
        
		struct
		{
			u64 b8;  u64 b16;   u64 b24;  u64 b32;
			u64 b40; u64 b48;   u64 b56;  u64 b64;
            
			u64 b72;  u64 b80;  u64 b88;  u64 b96;
			u64 b104; u64 b112; u64 b120; u64 b128;
            
			u64 b136; u64 b144; u64 b152; u64 b160;
			u64 b168; u64 b176; u64 b184; u64 b192;
            
			u64 b200; u64 b208; u64 b216; u64 b224;
			u64 b232; u64 b240; u64 b248; u64 b256;
            
			u64 b264; u64 b280; u64 b288; u64 b296;
			u64 b304; u64 b312; u64 b320; u64 b328;
            
            u64 b336; u64 b344; u64 b352; u64 b360;
			u64 b368; u64 b376; u64 b384; u64 b392;
            
			u64 b400; u64 b408; u64 b416; u64 b424;
			u64 b432; u64 b440; u64 b448; u64 b456;
            
            u64 b464; u64 b472; u64 b480; u64 b488;
			u64 b496; u64 b504; u64 b512; u64 b520;
            
            u64 b528; u64 b536; u64 b544; u64 b552;
			u64 b560; u64 b568; u64 b576; u64 b584;
            
			u64 b592; u64 b600; u64 b608; u64 b616;
			u64 b624; u64 b632; u64 b640; u64 b648;
            
			u64 b656; u64 b664; u64 b672; u64 b680;
			u64 b688; u64 b696; u64 b704; u64 b712;
            
			u64 b720; u64 b728; u64 b736; u64 b744;
			u64 b752; u64 b760; u64 b768; u64 b776;
            
			u64 b784; u64 b792; u64 b800; u64 b808;
			u64 b816; u64 b824; u64 b832; u64 b840;
            
            u64 b848; u64 b856; u64 b864; u64 b872;
			u64 b880; u64 b888; u64 b896; u64 b904;
            
			u64 b912; u64 b920; u64 b928; u64 b936;
			u64 b944; u64 b952; u64 b960; u64 b968;
            
            u64 b976; u64 b984; u64 b992; u64 b1000;
			u64 b1008; u64 b1016; u64 b1024; u64 b1032;
		};
    };
};

struct u16384
{
	union
	{
		struct
		{
            u8192 low1024;
			u8192 high1024;
		};
        
		struct
		{
			u4096 low;
			u4096 med;
			u4096 tall;
			u4096 high;
		};
        
		struct
		{
			u64 b8;  u64 b16;   u64 b24;  u64 b32;
			u64 b40; u64 b48;   u64 b56;  u64 b64;
            
			u64 b72;  u64 b80;  u64 b88;  u64 b96;
			u64 b104; u64 b112; u64 b120; u64 b128;
            
			u64 b136; u64 b144; u64 b152; u64 b160;
			u64 b168; u64 b176; u64 b184; u64 b192;
            
			u64 b200; u64 b208; u64 b216; u64 b224;
			u64 b232; u64 b240; u64 b248; u64 b256;
            
			u64 b264; u64 b280; u64 b288; u64 b296;
			u64 b304; u64 b312; u64 b320; u64 b328;
            
            u64 b336; u64 b344; u64 b352; u64 b360;
			u64 b368; u64 b376; u64 b384; u64 b392;
            
			u64 b400; u64 b408; u64 b416; u64 b424;
			u64 b432; u64 b440; u64 b448; u64 b456;
            
            u64 b464; u64 b472; u64 b480; u64 b488;
			u64 b496; u64 b504; u64 b512; u64 b520;
            
            u64 b528; u64 b536; u64 b544; u64 b552;
			u64 b560; u64 b568; u64 b576; u64 b584;
            
			u64 b592; u64 b600; u64 b608; u64 b616;
			u64 b624; u64 b632; u64 b640; u64 b648;
            
			u64 b656; u64 b664; u64 b672; u64 b680;
			u64 b688; u64 b696; u64 b704; u64 b712;
            
			u64 b720; u64 b728; u64 b736; u64 b744;
			u64 b752; u64 b760; u64 b768; u64 b776;
            
			u64 b784; u64 b792; u64 b800; u64 b808;
			u64 b816; u64 b824; u64 b832; u64 b840;
            
            u64 b848; u64 b856; u64 b864; u64 b872;
			u64 b880; u64 b888; u64 b896; u64 b904;
            
			u64 b912; u64 b920; u64 b928; u64 b936;
			u64 b944; u64 b952; u64 b960; u64 b968;
            
            u64 b976; u64 b984; u64 b992; u64 b1000;
			u64 b1008; u64 b1016; u64 b1024; u64 b1032;
            
            u64 b1040; u64 b1048; u64 b1056; u64 b1064;
            u64 b1072; u64 b1080; u64 b1088; u64 b1096;
            
            u64 b1104; u64 b1112; u64 b1120; u64 b1128;
            u64 b1136; u64 b1144; u64 b1152; u64 b1160;
            
            u64 b1168; u64 b1176; u64 b1184; u64 b1192;
            u64 b1200; u64 b1208; u64 b1216; u64 b1224;
            
            u64 b1232; u64 b1240; u64 b1248; u64 b1256;
            u64 b1264; u64 b1272; u64 b1280; u64 b1288;
            
            u64 b1296; u64 b1304; u64 b1312; u64 b1320;
            u64 b1328; u64 b1336; u64 b1344; u64 b1352;
            
            u64 b1360; u64 b1368; u64 b1376; u64 b1384;
            u64 b1392; u64 b1400; u64 b1408; u64 b1416;
            
            u64 b1424; u64 b1432; u64 b1440; u64 b1448;
            u64 b1456; u64 b1464; u64 b1472; u64 b1480;
            
            u64 b1488; u64 b1496; u64 b1504; u64 b1512;
            u64 b1520; u64 b1528; u64 b1536; u64 b1544;
            
            u64 b1552; u64 b1560; u64 b1568; u64 b1576;
            u64 b1584; u64 b1592; u64 b1600; u64 b1608;
            
            u64 b1616; u64 b1624; u64 b1632; u64 b1640;
            u64 b1648; u64 b1656; u64 b1664; u64 b1672;
            
            u64 b1680; u64 b1688; u64 b1696; u64 b1704;
            u64 b1712; u64 b1720; u64 b1728; u64 b1736;
            
            u64 b1744; u64 b1752; u64 b1760; u64 b1768;
            u64 b1776; u64 b1784; u64 b1792; u64 b1800;
            
            u64 b1808; u64 b1816; u64 b1824; u64 b1832;
            u64 b1840; u64 b1848; u64 b1856; u64 b1864;
            
            u64 b1872; u64 b1880; u64 b1888; u64 b1896;
            u64 b1904; u64 b1912; u64 b1920; u64 b1928;
            
            u64 b1936; u64 b1944; u64 b1952; u64 b1960;
            u64 b1968; u64 b1976; u64 b1984; u64 b1992;
            
            u64 b2000; u64 b2008; u64 b2016; u64 b2024;
            u64 b2032; u64 b2040; u64 b2048; u64 b2056;
		};
    };
};


//
//@NOTE@TODO@IMPORTANT
//
//Release mode is kinda fucky with the manual assembly
//It seems that using temporary copies of parameters as parameters for
//the asm functions fucks everything up
//
//Probably because I don't do the startup/cleanup of parameters correctly?
//A lot of assumptions... Copying the parameter to a local variable seems to help.
//
//Still there are same strange results happening if
//operations are done in certain ways

//
//@NOTE@TODO@IMPORTANT
//
//Check that my ASM is preserving registers as determined by the x64
//calling convention
//https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions?view=vs-2019
//R12:R15, RDI, RSI, RBX, RBP ->  MUST BE PRESERVED BY CALLEE (It's a me! Callee)
//XMM6:XMM15, YMM6:YMM15      ->  MUST BE PRESERVED BY CALLEE (It's a me! Callee)

extern "C"
{
    
    //
    // u128 Operations
    //
    
    u128 u128_add(u128 *v, u64 w);
    u128 u128_addBig(u128 *v, u128 *w);
    u128 u128_sub(u128 *v, u64 w);
    u128 u128_subBig(u128 *v, u128 *w);
    u128 u128_mul(u128 *v, u64 w);
    u128 u128_mulBig(u128 *v, u128 *w);
    u128 u128_divBig(u128 *v, u128 *w, u128 *remainder);
    u128 u128_pow(u128 v, u32 exp);
    
    void u128_inc(u128 *v);
    void u128_dec(u128 *v);
    
    u128 u128_shl(u128 *v, u32 shift);
    u128 u128_shr(u128 *v, u32 shift);
    u128 u128_and(u128 *v, u128 *mask);
    u128 u128_or(u128 *v, u128 *mask);
    u128 u128_xor(u128 *v, u128 *mask);
    u128 u128_not(u128 *v);
    
    string u128_str(u128 v);
    
    //
    // u256 Operations
    //
    
    
    //               a  b  c  d *
    //               e  f  g  h =
    //               ------------
    //               ha hb hc hd
    //            ga gb gc gd 0  
    //         fa fb fc fd 0  0
    //      ea eb ec ed 0  0  0
    //    ----------------------
    //                          
    
    u256 u256_add(u256 *v, u64 w);
    u256 u256_addBig(u256 *v, u256 *w);
    u256 u256_sub(u256 *v, u64 w);
    u256 u256_subBig(u256 *v, u256 *w);
    u256 u256_mul(u256 *v, u64 w);
    u256 u256_mulBig(u256 *v, u256 *w); //@TODO: probably got an error with carries
    u256 u256_divBig(u256 *v, u256 *w, u256 *remainder);
    u256 u256_pow(u256 v, u32 exp);
    
    void u256_inc(u256 *v);
    void u256_dec(u256 *v);
    
    u256 u256_shl(u256 *v, u32 shift);
    u256 u256_shr(u256 *v, u32 shift);
    u256 u256_and(u256 *v, u256 *mask);
    u256 u256_or(u256 *v, u256 *mask);
    u256 u256_xor(u256 *v, u256 *mask);
    u256 u256_not(u256 *v);
    
    string u256_str(u256 v);
    
    //
    // u512 Operations
    //
    
    u512 u512_add(u512 *v, u64 w);
    u512 u512_addBig(u512 *v, u512 *w);
    u512 u512_sub(u512 *v, u64 w);
    u512 u512_subBig(u512 *v, u512 *w);
    u512 u512_mul(u512 *v, u64 w);
    u512 u512_mulBig(u512 *v, u512 *w); //@TODO: probably got an error with carries
    u512 u512_divBig(u512 *v, u512 *w, u512 *remainder);
    u512 u512_pow(u512 v, u32 exp);
    
    void u512_inc(u512 *v);
    void u512_dec(u512 *v);
    
    u512 u512_shl(u512 *v, u32 shift);
    u512 u512_shr(u512 *v, u32 shift);
    u512 u512_and(u512 *v, u512 *mask);
    u512 u512_or(u512 *v, u512 *mask);
    u512 u512_xor(u512 *v, u512 *mask);
    u512 u512_not(u512 *v);
    
    string u512_str(u512 v);
    
    //
    // u1024 Operations
    //
    
    u1024 u1024_add(u1024 *v, u64 w);
    u1024 u1024_addBig(u1024 *v, u1024 *w);
    u1024 u1024_sub(u1024 *v, u64 w);
    u1024 u1024_subBig(u1024 *v, u1024 *w);
    u1024 u1024_mul(u1024 *v, u64 w);
    u1024 u1024_mulBig(u1024 *v, u1024 *w); //@TODO: probably got an error with carries
    u1024 u1024_divBig(u1024 *v, u1024 *w, u1024 *remainder);
    u1024 u1024_pow(u1024 v, u32 exp);
    
    void u1024_inc(u1024 *v);
    void u1024_dec(u1024 *v);
    
    u1024 u1024_shl(u1024 *v, u32 shift);
    u1024 u1024_shr(u1024 *v, u32 shift);
    u1024 u1024_and(u1024 *v, u1024 *mask);
    u1024 u1024_or(u1024 *v, u1024 *mask);
    u1024 u1024_xor(u1024 *v, u1024 *mask);
    u1024 u1024_not(u1024 *v);
    
    string u1024_str(u1024 v);
    u1024  u1024_from64(u64 v);
    
    //
    // u2048 Operations
    //
    
    u2048 u2048_add(u2048 *v, u64 w);
    u2048 u2048_addBig(u2048 *v, u2048 *w);
    u2048 u2048_sub(u2048 *v, u64 w);
    u2048 u2048_subBig(u2048 *v, u2048 *w);
    u2048 u2048_mul(u2048 *v, u64 w);
    u2048 u2048_mulBig(u2048 *v, u2048 *w); //@TODO: probably got an error with carries
    u2048 u2048_divBig(u2048 *v, u2048 *w, u2048 *remainder);
    u2048 u2048_pow(u2048 v, u32 exp);
    
    void u2048_inc(u2048 *v);
    void u2048_dec(u2048 *v);
    
    u2048 u2048_shl(u2048 *v, u32 shift);
    u2048 u2048_shr(u2048 *v, u32 shift);
    u2048 u2048_and(u2048 *v, u2048 *mask);
    u2048 u2048_or(u2048 *v, u2048 *mask);
    u2048 u2048_xor(u2048 *v, u2048 *mask);
    u2048 u2048_not(u2048 *v);
    
    string u2048_str(u2048 v);
    
    //
    // u4096 Operations
    //
    
    u4096 u4096_add(u4096 *v, u64 w);
    u4096 u4096_addBig(u4096 *v, u4096 *w);
    u4096 u4096_sub(u4096 *v, u64 w);
    u4096 u4096_subBig(u4096 *v, u4096 *w);
    u4096 u4096_mul(u4096 *v, u64 w);
    u4096 u4096_mulBig(u4096 *v, u4096 *w); //@TODO: probably got an error with carries
    u4096 u4096_divBig(u4096 *v, u4096 *w, u4096 *remainder);
    u4096 u4096_pow(u4096 v, u32 exp);
    
    void u4096_inc(u4096 *v);
    void u4096_dec(u4096 *v);
    
    u4096 u4096_shl(u4096 *v, u32 shift);
    u4096 u4096_shr(u4096 *v, u32 shift);
    u4096 u4096_and(u4096 *v, u4096 *mask);
    u4096 u4096_or(u4096 *v, u4096 *mask);
    u4096 u4096_xor(u4096 *v, u4096 *mask);
    u4096 u4096_not(u4096 *v);
    
    string u4096_str(u4096 v);
    
    //
    // u8192 Operations
    //
    
    u8192 u8192_add(u8192 *v, u64 w);
    u8192 u8192_addBig(u8192 *v, u8192 *w);
    u8192 u8192_sub(u8192 *v, u64 w);
    u8192 u8192_subBig(u8192 *v, u8192 *w);
    u8192 u8192_mul(u8192 *v, u64 w);
    u8192 u8192_mulBig(u8192 *v, u8192 *w); //@TODO: probably got an error with carries
    u8192 u8192_divBig(u8192 *v, u8192 *w, u8192 *remainder);
    u8192 u8192_pow(u8192 v, u32 exp);
    
    void u8192_inc(u8192 *v);
    void u8192_dec(u8192 *v);
    
    u8192 u8192_shl(u8192 *v, u32 shift);
    u8192 u8192_shr(u8192 *v, u32 shift);
    u8192 u8192_and(u8192 *v, u8192 *mask);
    u8192 u8192_or(u8192 *v, u8192 *mask);
    u8192 u8192_xor(u8192 *v, u8192 *mask);
    u8192 u8192_not(u8192 *v);
    
    string u8192_str(u8192 v);
    
    //
    // u16384 Operations
    //
    
    u16384 u16384_add(u16384 *v, u64 w);
    u16384 u16384_addBig(u16384 *v, u16384 *w);
    u16384 u16384_sub(u16384 *v, u64 w);
    u16384 u16384_subBig(u16384 *v, u16384 *w);
    u16384 u16384_mul(u16384 *v, u64 w);
    u16384 u16384_mulBig(u16384 *v, u16384 *w); //@TODO: probably got an error with carries
    u16384 u16384_divBig(u16384 *v, u16384 *w, u16384 *remainder);
    u16384 u16384_pow(u16384 v, u32 exp);
    
    void u16384_inc(u16384 *v);
    void u16384_dec(u16384 *v);
    
    u16384 u16384_shl(u16384 *v, u32 shift);
    u16384 u16384_shr(u16384 *v, u32 shift);
    u16384 u16384_and(u16384 *v, u16384 *mask);
    u16384 u16384_or(u16384 *v, u16384 *mask);
    u16384 u16384_xor(u16384 *v, u16384 *mask);
    u16384 u16384_not(u16384 *v);
    
    string u16384_str(u16384 v);
    u16384 u16384_from64(u64 v);
}

#endif

#ifdef LS_BIGINT_IMPLEMENTATION





//
// u128 Operations
//

/*Logical Operations*/

b32 operator==(u128 v1, u64 v)
{ return ((v1.h == 0) && (v1.l == v)); }

b32 operator==(u128 v1, u128 v)
{ return ((v1.h == v.h) && (v1.l == v.l)); }

b32 operator!=(u128 v1, u64 v)
{ return !((v1.h == 0) && (v1.l == v)); }

b32 operator!=(u128 v1, u128 v)
{ return !((v1.h == v.h) && (v1.l == v.l)); }

b32 operator&&(u128 v1, u128 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u128 v1, u128 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u128 v)
{ return (v == u64(0)) ? 1 : 0; }

b32 operator>(u128 v1, u64 v)
{ return ((v1.h > 0) || (v1.l > v)); }

b32 operator>(u128 v1, u128 v) // @TODO: I'm having doubts on this function
{ return ((v1.h >= v.h) && (v1.l > v.l)); }

b32 operator>=(u128 v1, u64 v)
{ return ((v1.h > 0) || (v1.l >= v)); }

b32 operator>=(u128 v1, u128 v)
{ return ((v1.h >= v.h) && (v1.l >= v.l)); }

b32 operator<(u128 v1, u64 v)
{ return ((v1.h == 0) && (v1.l < v)); }

b32 operator<(u128 v1, u128 v)
{ return ((v1.h <= v.h) && (v1.l < v.l)); }

b32 operator<=(u128 v1, u64 v)
{ return ((v1.h == 0) && (v1.l <= v)); }

b32 operator<=(u128 v1, u128 v)
{ return ((v1.h <= v.h) && (v1.l <= v.l)); }

/*Arithmetic Operations*/
u128 operator+(u128 v1, u64 v)
{ return u128_add(&v1, v); }

u128 operator+(u128 v1, u128 v)
{ return u128_addBig(&v1, &v); }

void operator+=(u128 &v1, u64 v)
{ v1 = u128_add(&v1, v); }

void operator+=(u128 &v1, u128 v)
{ v1 = u128_addBig(&v1, &v); }

u128 operator-(u128 v1, u64 v)
{ return u128_sub(&v1, v); }

u128 operator-(u128 v1, u128 v)
{ return u128_subBig(&v1, &v); }

void operator-=(u128 &v1, u64 v)
{ v1 = u128_sub(&v1, v); }

void operator-=(u128 &v1, u128 v)
{ v1 = u128_subBig(&v1, &v); }

u128 operator*(u128 v1, u64 v)
{ return u128_mul(&v1, v); }

u128 operator*(u128 v1, u128 v)
{ return u128_mulBig(&v1, &v); }

void operator*=(u128 &v1, u64 v)
{ v1 = u128_mul(&v1, v); }

void operator*=(u128 &v1, u128 v)
{ v1 = u128_mulBig(&v1, &v); }

u128 operator/(u128 v1, u64 v)
{ u128 temp = {v, 0}; u128 r = {};
    return v != 0 ? u128_divBig(&v1, &temp, &r) : u128({}); }

u128 operator/(u128 v1, u128 v)
{ u128 r = {}; return v != u64(0) ? u128_divBig(&v1, &v, &r) :  u128({}); }

void operator/=(u128 &v1, u64 v)
{ u128 temp = {v, 0}; u128 r = {};
    v1 = v != 0 ? u128_divBig(&v1, &temp, &r) :  u128({}); }

void operator/=(u128 &v1, u128 v)
{ u128 r = {}; v1 = v != u64(0) ? u128_divBig(&v1, &v, &r) :  u128({}); }

u128 operator%(u128 v1, u64 v)
{ u128 temp = {v, 0}; u128 r = {}; u128_divBig(&v1, &temp, &r); return r; }

u128 operator%(u128 v1, u128 v)
{ u128 r = {}; u128_divBig(&v1, &v, &r); return r; }

void operator%=(u128 &v1, u64 v)
{ u128 temp = {v, 0}; u128 r = {}; u128_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u128 &v1, u128 v)
{ u128 r = {}; u128_divBig(&v1, &v, &r); v1 = r; }

#if 0
u128 operator++(int)
{ u128 temp = *this; u128_inc(this); return temp; }

u128 operator--(int)
{ u128 temp = *this; u128_dec(this); return temp; }

u128 operator++()
{ u128_inc(this); return *this; }

u128 operator--()
{ u128_dec(this); return *this; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u128 operator<<(u128 v1, u32 shift)
{ return u128_shl(&v1, shift); }

void operator<<=(u128 &v1, u32 shift)
{ v1 = u128_shl(&v1, shift); }

u128 operator>>(u128 v1, u32 shift)
{ return u128_shr(&v1, shift); }

void operator>>=(u128 &v1, u32 shift)
{ v1 = u128_shr(&v1, shift); }

/*BITWISE AND OP*/

u128 operator&(u128 v1, u128 mask)
{ return u128_and(&v1, &mask); }

u128 operator&(u128 v1, u64 mask)
{ u128 temp = {mask, 0}; return u128_and(&v1, &temp); }

void operator&=(u128 &v1, u128 mask)
{ v1 = u128_and(&v1, &mask); }

void operator&=(u128 &v1, u64 mask)
{ u128 temp = {mask, 0}; v1 = u128_and(&v1, &temp); }

/*BITWISE OR OP*/

u128 operator|(u128 v1, u128 mask)
{ return u128_or(&v1, &mask); }

u128 operator|(u128 v1, u64 mask)
{ u128 temp = {mask, 0}; return u128_or(&v1, &temp); }

void operator|=(u128 &v1, u128 mask)
{ v1 = u128_or(&v1, &mask); }

void operator|=(u128 &v1, u64 mask)
{ u128 temp = {mask, 0}; v1 = u128_or(&v1, &temp); }

/*BITWISE XOR OP*/

u128 operator^(u128 v1, u128 mask)
{ return u128_xor(&v1, &mask); }

u128 operator^(u128 v1, u64 mask)
{ u128 temp = {mask, 0}; return u128_xor(&v1, &temp); }

void operator^=(u128 &v1, u128 mask)
{ v1 = u128_xor(&v1, &mask); }

void operator^=(u128 &v1, u64 mask)
{ u128 temp = {mask, 0}; v1 = u128_xor(&v1, &temp); }

/*BITWISE NOT OP*/
u128 operator~(u128 v)
{ return u128_not(&v); }











//
// u256 Operations
//


/*LOGICAL OP*/

bool operator==(u256 v1, u64 v)
{
    return ((v1.h == 0) && (v1.t == 0) &&
            (v1.m == 0) && (v1.l == v));
}

bool operator==(u256 v1, u128 v)
{
    return ((v1.h == 0) && (v1.t == 0) &&
            (v1.m == v.h) && (v1.l == v.l));
}

bool operator==(u256 v1, u256 v)
{
    return ((v1.h == v.h) && (v1.t == v.t) &&
            (v1.m == v.m) && (v1.l == v.l));
}

bool operator!=(u256 v1, u64 v)
{
    return !((v1.h == 0) && (v1.t == 0) &&
             (v1.m == 0) && (v1.l == v));
}

bool operator!=(u256 v1, u128 v)
{
    return !((v1.h == 0) && (v1.t == 0) &&
             (v1.m == v.h) && (v1.l == v.l));
}

bool operator!=(u256 v1, u256 v)
{
    return !((v1.h == v.h) && (v1.t == v.t) &&
             (v1.m == v.m) && (v1.l == v.l));
}

bool operator&&(u256 v1, u256 v)
{ return (v1 != u64(0) && (v != u64(0))); }

bool operator||(u256 v1, u256 v)
{ return (v1 != u64(0) || (v != u64(0))); }

bool operator!(u256 v1)
{ return (v1 == u64(0)) ? 1 : 0; }

bool operator>(u256 v1, u64 v)
{ return ((v1.h > 0) || (v1.t > 0) || (v1.m > 0) || (v1.l > v)); }

bool operator>(u256 v1, u256 v) // @TODO: I'm having doubts on this function
{ return ((v1.h >= v.h) && (v1.t >= v.t) && (v1.m >= v.m) && (v1.l > v.l)); }

bool operator>=(u256 v1, u64 v)
{ return ((v1.h > 0) || (v1.t > 0) || (v1.m > 0) || (v1.l >= v)); }

bool operator>=(u256 v1, u256 v)
{ return ((v1.h >= v.h) && (v1.t >= v.t) && (v1.m >= v.m) && (v1.l >= v.l)); }

bool operator<(u256 v1, u64 v)
{ return ((v1.h == 0) && (v1.t == 0) && (v1.m == 0) && (v1.l < v)); }

bool operator<(u256 v1, u256 v)
{ return ((v1.h <= v.h) && (v1.t <= v.t) && (v1.m <= v.m) && (v1.l < v.l)); }

bool operator<=(u256 v1, u64 v)
{ return ((v1.h == 0) && (v1.t == 0) && (v1.m == 0) && (v1.l <= v)); }

bool operator<=(u256 v1, u256 v)
{ return ((v1.h <= v.h) && (v1.t <= v.t) && (v1.m <= v.m) && (v1.l <= v.l)); }

/*ARITHMETIC OP*/

u256 operator+(u256 v1, u64 v)
{ return u256_add(&v1, v); }

u256 operator+(u256 v1, u256 v)
{ return u256_addBig(&v1, &v); }

void operator+=(u256 &v1, u64 v)
{ v1 = u256_add(&v1, v); }

void operator+=(u256 &v1, u256 v)
{ v1 = u256_addBig(&v1, &v); }

u256 operator-(u256 v1, u64 v)
{ return u256_sub(&v1, v); }

u256 operator-(u256 v1, u256 v)
{ return u256_subBig(&v1, &v); }

void operator-=(u256 &v1, u64 v)
{ v1 = u256_sub(&v1, v); }

void operator-=(u256 &v1, u256 v)
{ v1 = u256_subBig(&v1, &v); }


/*
u256 operator*(u256 v1, u256 v)
{  return u256_mulBig(&v1, &v); }

void operator*=(u256 &v1, u256 v)
{ v1 = u256_mulBig(&v1, &v); }
**/

// Example in 256 bits (every letter represents a 64bit value)
// v->           a  b  c  d *
// w->           e  f  g  h =
//               ------------
//            0  ha hb hc hd
//         0  ga gb gc gd 0  
//      0  fa fb fc fd 0  0
//      ea eb ec ed 0  0  0
//    ----------------------
//                          

u256 u256_multTest(u256 v, u256 w)
{
    u256 result = {};
    
    u64 tmp = 0;
    
    u64 highPartOne = 0;
    u64 highPartTwo = 0;
    
    // Column 1
    result.arr[0] = _umul128(v.arr[0], w.arr[0], &highPartOne);
    
    /* Column 2 - 4*/
    for(u64 i = 2; i < 4; i++)
    {
        result.arr[i] += _addcarry_u64(0, result.arr[i-1], highPartOne, &result.arr[i-1]);
        
        for(u64 j = 0; j < i; j++) {
            tmp = _umul128(v.arr[i-j-1], w.arr[j], &highPartOne);
            result.arr[i] += _addcarry_u64(0, highPartTwo, highPartOne, &highPartTwo);
            result.arr[i] += _addcarry_u64(0, result.arr[i-1], tmp, &result.arr[i-1]);
        }
        
        highPartOne = highPartTwo;
        highPartTwo = 0;
    }
    
    return result;
}

u256 operator*(u256 v1, u256 v)
{  return u256_multTest(v1, v); }

void operator*=(u256 &v1, u256 v)
{ v1 = u256_multTest(v1, v); }

u256 operator*(u256 v1, u64 v)
{ return u256_mul(&v1, v); }

void operator*=(u256 &v1, u64 v)
{ v1 = u256_mul(&v1, v); }

u256 operator/(u256 v1, u64 v)
{ u256 temp = {v,0,0,0}; u256 r = {};
    return v != 0 ? u256_divBig(&v1, &temp, &r) : u256({}); }

u256 operator/(u256 v1, u256 v)
{ u256 r = {}; return v != u64(0) ? u256_divBig(&v1, &v, &r) : u256({}); }

void operator/=(u256 &v1, u64 v)
{ u256 temp = {v,0,0,0}; u256 r = {};
    v1 = v != 0 ? u256_divBig(&v1, &temp, &r) : u256({}); }

void operator/=(u256 &v1, u256 v)
{ u256 r = {}; v1 = v != u64(0) ? u256_divBig(&v1, &v, &r) : u256({}); }

u256 operator%(u256 v1, u64 v)
{ u256 temp = {v,0,0,0}; u256 r = {}; u256_divBig(&v1, &temp, &r); return r; }

u256 operator%(u256 v1, u256 v)
{ u256 r = {}; u256_divBig(&v1, &v, &r); return r; }

void operator%=(u256 &v1, u64 v)
{ u256 temp = {v,0,0,0}; u256 r = {}; u256_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u256 &v1, u256 v)
{ u256 r = {}; u256_divBig(&v1, &v, &r); v1 = r; }

#if 0
u256 operator++(int)
{ u256 temp = *this; u256_inc(this); return temp; }

u256 operator--(int)
{ u256 temp = *this; u256_dec(this); return temp; }

u256 operator++()
{ u256_inc(this); return *this; }

u256 operator--()
{ u256_dec(this); return *this; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT BY A MAX OF 63 BITS RIGHT NOW
u256 operator<<(u256 v1, u32 shift)
{ return u256_shl(&v1, shift); }

void operator<<=(u256 &v1, u32 shift)
{ v1 = u256_shl(&v1, shift); }

u256 operator>>(u256 v1, u32 shift)
{ return u256_shr(&v1, shift); }

void operator>>=(u256 &v1, u32 shift)
{ v1 = u256_shr(&v1, shift); }

/*BITWISE AND OP*/

u256 operator&(u256 v1, u256 mask)
{ return u256_and(&v1, &mask); }

u256 operator&(u256 v1, u64 mask)
{ u256 temp = {mask,0,0,0}; return u256_and(&v1, &temp); }

void operator&=(u256 &v1, u256 mask)
{ v1 = u256_and(&v1, &mask); }

void operator&=(u256 &v1, u64 mask)
{ u256 temp = {mask,0,0,0}; v1 = u256_and(&v1, &temp); }

/*BITWISE OR OP*/

u256 operator|(u256 v1, u256 mask)
{ return u256_or(&v1, &mask); }

u256 operator|(u256 v1, u64 mask)
{ u256 temp = {mask,0,0,0}; return u256_or(&v1, &temp); }

void operator|=(u256 &v1, u256 mask)
{ v1 = u256_or(&v1, &mask); }

void operator|=(u256 &v1, u64 mask)
{ u256 temp = {mask,0,0,0}; v1 = u256_or(&v1, &temp); }

/*BITWISE XOR OP*/

u256 operator^(u256 v1, u256 mask)
{ return u256_xor(&v1, &mask); }

u256 operator^(u256 v1, u64 mask)
{ u256 temp = {mask,0,0,0}; return u256_xor(&v1, &temp); }

void operator^=(u256 &v1, u256 mask)
{ v1 = u256_xor(&v1, &mask); }

void operator^=(u256 &v1, u64 mask)
{ u256 temp = {mask,0,0,0}; v1 = u256_xor(&v1, &temp); }

/*BITWISE NOT OP*/

u256 operator~(u256 v1)
{ return u256_not(&v1); }





//
// u512 Operations
//
/*LOGICAL OP*/

b32 operator==(u512 v1, u64 v)
{
    return ((v1.hh == 0) && (v1.th == 0) &&
            (v1.mh == 0) && (v1.lh == 0) &&
            (v1.hl == 0) && (v1.tl == 0) &&
            (v1.ml == 0) && (v1.ll == v));
}

b32 operator==(u512 v1, u128 v)
{
    return ((v1.hh == 0) && (v1.th == 0) &&
            (v1.mh == 0) && (v1.lh == 0) &&
            (v1.hl == 0) && (v1.tl == 0) &&
            (v1.ml == v.h) && (v1.ll == v.l));
}

b32 operator==(u512 v1, u256 v)
{
    return ((v1.hh == 0) && (v1.th == 0) &&
            (v1.mh == 0) && (v1.lh == 0) &&
            (v1.hl == v.h) && (v1.tl == v.t) &&
            (v1.ml == v.m) && (v1.ll == v.l));
}

b32 operator==(u512 v1, u512 v)
{
    return ((v1.hh == v.hh) && (v1.th == v.th) &&
            (v1.mh == v.mh) && (v1.lh == v.lh) &&
            (v1.hl == v.hl) && (v1.tl == v.tl) &&
            (v1.ml == v.ml) && (v1.ll == v.ll));
}

b32 operator!=(u512 v1, u64 v)
{
    return !((v1.hh == 0) && (v1.th == 0) &&
             (v1.mh == 0) && (v1.lh == 0) &&
             (v1.hl == 0) && (v1.tl == 0) &&
             (v1.ml == 0) && (v1.ll == v));
}

b32 operator!=(u512 v1, u128 v)
{
    return !((v1.hh == 0) && (v1.th == 0) &&
             (v1.mh == 0) && (v1.lh == 0) &&
             (v1.hl == 0) && (v1.tl == 0) &&
             (v1.ml == v.h) && (v1.ll == v.l));
}

b32 operator!=(u512 v1, u256 v)
{
    return !((v1.hh == 0) && (v1.th == 0) &&
             (v1.mh == 0) && (v1.lh == 0) &&
             (v1.hl == v.h) && (v1.tl == v.t) &&
             (v1.ml == v.m) && (v1.ll == v.l));
}

b32 operator!=(u512 v1, u512 v)
{
    return !((v1.hh == v.hh) && (v1.th == v.th) &&
             (v1.mh == v.mh) && (v1.lh == v.lh) &&
             (v1.hl == v.hl) && (v1.tl == v.tl) &&
             (v1.ml == v.ml) && (v1.ll == v.ll));
}

b32 operator&&(u512 v1, u512 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u512 v1, u512 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u512 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u512 v1, u64 v)
{
    return ((v1.hh > 0) || (v1.th > 0) || (v1.mh > 0) || (v1.lh > 0) ||
            (v1.hl > 0) || (v1.tl > 0) || (v1.ml > 0) || (v1.ll > v));
}

b32 operator>(u512 v1, u512 v) // @TODO: I'm having doubts on this function
{
    return ((v1.hh >= v.hh) && (v1.th >= v.th) &&
            (v1.mh >= v.mh) && (v1.lh >= v.lh) &&
            (v1.hl >= v.hl) && (v1.tl >= v.tl) &&
            (v1.ml >= v.ml) && (v1.ll > v.ll));
}

b32 operator>=(u512 v1, u64 v)
{
    return ((v1.hh > 0) || (v1.th > 0) ||
            (v1.mh > 0) || (v1.lh > 0) ||
            (v1.hl > 0) || (v1.tl > 0) ||
            (v1.ml > 0) || (v1.ll >= v));
}

b32 operator>=(u512 v1, u512 v)
{
    return ((v1.hh >= v.hh) && (v1.th >= v.th) &&
            (v1.mh >= v.mh) && (v1.lh >= v.lh) &&
            (v1.hl >= v.hl) && (v1.tl >= v.tl) &&
            (v1.ml >= v.ml) && (v1.ll >= v.ll));
}

b32 operator<(u512 v1, u64 v)
{
    return ((v1.hh == 0) && (v1.th == 0) && (v1.mh == 0) && (v1.lh == 0) &&
            (v1.hl == 0) && (v1.tl == 0) && (v1.ml == 0) && (v1.ll < v));
}

b32 operator<(u512 v1, u512 v)
{
    return ((v1.hh <= v.hh) && (v1.th <= v.th) &&
            (v1.mh <= v.mh) && (v1.lh <= v.lh) &&
            (v1.hl <= v.hl) && (v1.tl <= v.tl) &&
            (v1.ml <= v.ml) && (v1.ll < v.ll));
}

b32 operator<=(u512 v1, u64 v)
{
    return ((v1.hh == 0) && (v1.th == 0) && (v1.mh == 0) && (v1.lh == 0) &&
            (v1.hl == 0) && (v1.tl == 0) && (v1.ml == 0) && (v1.ll <= v));
}

b32 operator<=(u512 v1, u512 v)
{
    return ((v1.hh <= v.hh) && (v1.th <= v.th) &&
            (v1.mh <= v.mh) && (v1.lh <= v.lh) &&
            (v1.hl <= v.hl) && (v1.tl <= v.tl) &&
            (v1.ml <= v.ml) && (v1.ll <= v.ll));
}

/*ARITHMETIC OP*/

u512 operator+(u512 v1, u64 v)
{ return u512_add(&v1, v); }

u512 operator+(u512 v1, u512 v)
{ return u512_addBig(&v1, &v); }

void operator+=(u512 &v1, u64 v)
{ v1 = u512_add(&v1, v); }

void operator+=(u512 &v1, u512 v)
{ v1 = u512_addBig(&v1, &v); }

u512 operator-(u512 v1, u64 v)
{ return u512_sub(&v1, v); }

u512 operator-(u512 v1, u512 v)
{ return u512_subBig(&v1, &v); }

void operator-=(u512 &v1, u64 v)
{ v1 = u512_sub(&v1, v); }

void operator-=(u512 &v1, u512 v)
{ v1 = u512_subBig(&v1, &v); }


/*
u512 operator*(u512 v1, u512 v)
{ return u512_mulBig(&v1, &v); }

void operator*=(u512 &v1, u512 v)
{ v1 = u512_mulBig(&v1, &v); }
*/

// Example in 256 bits (every letter represents a 64bit value)
// v->           a  b  c  d *
// w->           e  f  g  h =
//               ------------
//            0  ha hb hc hd
//         0  ga gb gc gd 0  
//      0  fa fb fc fd 0  0
//      ea eb ec ed 0  0  0
//    ----------------------
//                          

u512 u512_multTest(u512 v, u512 w)
{
    u512 result = {};
    
    u64 tmp = 0;
    
    u64 highPartOne = 0;
    u64 highPartTwo = 0;
    
    // Column 1
    result.arr[0] = _umul128(v.arr[0], w.arr[0], &highPartOne);
    
    /* Column 2 - 8*/
    for(u64 i = 2; i < 8; i++)
    {
        result.arr[i] += _addcarry_u64(0, result.arr[i-1], highPartOne, &result.arr[i-1]);
        
        for(u64 j = 0; j < i; j++) {
            tmp = _umul128(v.arr[i-j-1], w.arr[j], &highPartOne);
            result.arr[i] += _addcarry_u64(0, highPartTwo, highPartOne, &highPartTwo);
            result.arr[i] += _addcarry_u64(0, result.arr[i-1], tmp, &result.arr[i-1]);
        }
        
        highPartOne = highPartTwo;
        highPartTwo = 0;
    }
    
    return result;
}

u512 operator*(u512 v1, u512 v)
{ return u512_multTest(v1, v); }

void operator*=(u512 &v1, u512 v)
{ v1 = u512_multTest(v1, v); }


u512 operator*(u512 v1, u64 v)
{ return u512_mul(&v1, v); }

void operator*=(u512 &v1, u64 v)
{ v1 = u512_mul(&v1, v); }

u512 operator/(u512 v1, u64 v)
{ u512 temp = {v,0,0,0,0,0,0,0}; u512 r = {};
    return v != 0 ? u512_divBig(&v1, &temp, &r) : u512({}); }

u512 operator/(u512 v1, u512 v)
{ u512 r = {}; return v != u64(0) ? u512_divBig(&v1, &v, &r) : u512({}); }

void operator/=(u512 &v1, u64 v)
{ u512 temp = {v,0,0,0,0,0,0,0}; u512 r = {};
    v1 = v != 0 ? u512_divBig(&v1, &temp, &r) : u512({}); }

void operator/=(u512 &v1, u512 v)
{ u512 r = {}; v1 = v != u64(0) ? u512_divBig(&v1, &v, &r) : u512({}); }

u512 operator%(u512 v1, u64 v)
{ u512 temp = {v,0,0,0,0,0,0,0}; u512 r = {};
    u512_divBig(&v1, &temp, &r); return r; }

u512 operator%(u512 v1, u512 v)
{ u512 r = {}; u512_divBig(&v1, &v, &r); return r; }

void operator%=(u512 &v1, u64 v)
{ u512 temp = {v,0,0,0,0,0,0,0}; u512 r = {};
    u512_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u512 &v1, u512 v)
{ u512 r = {}; u512_divBig(&v1, &v, &r); v1 = r; }

#if 0
u512 operator++(int)
{ u512 temp = v1; u512_inc(&v1); return temp; }

u512 operator--(int)
{ u512 temp = v1; u512_dec(&v1); return temp; }

u512 operator++()
{ u512_inc(&v1); return v1; }

u512 operator--()
{ u512_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u512 operator<<(u512 v1, u32 shift)
{ return u512_shl(&v1, shift); }

void operator<<=(u512 &v1, u32 shift)
{ v1 = u512_shl(&v1, shift); }

u512 operator>>(u512 v1, u32 shift)
{ return u512_shr(&v1, shift); }

void operator>>=(u512 &v1, u32 shift)
{ v1 = u512_shr(&v1, shift); }

/*BITWISE AND OP*/

u512 operator&(u512 v1, u512 mask)
{ return u512_and(&v1, &mask); }

u512 operator&(u512 v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; return u512_and(&v1, &temp); }

void operator&=(u512 &v1, u512 mask)
{ v1 = u512_and(&v1, &mask); }

void operator&=(u512 &v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; v1 = u512_and(&v1, &temp); }

/*BITWISE OR OP*/

u512 operator|(u512 v1, u512 mask)
{ return u512_or(&v1, &mask); }

u512 operator|(u512 v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; return u512_or(&v1, &temp); }

void operator|=(u512 &v1, u512 mask)
{ v1 = u512_or(&v1, &mask); }

void operator|=(u512 &v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; v1 = u512_or(&v1, &temp); }

/*BITWISE XOR OP*/

u512 operator^(u512 v1, u512 mask)
{ return u512_xor(&v1, &mask); }

u512 operator^(u512 v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; return u512_xor(&v1, &temp); }

void operator^=(u512 &v1, u512 mask)
{ v1 = u512_xor(&v1, &mask); }

void operator^=(u512 &v1, u64 mask)
{ u512 temp = {mask,0,0,0,0,0,0,0}; v1 = u512_xor(&v1, &temp); }

/*BITWISE NOT OP*/

u512 operator~(u512 v1)
{ return u512_not(&v1); }


















//
// u1024 Operations
//

/*@TODO WROOOOOONG LOGICAL OP... IS IT WRONG THO?*/

b32 operator==(u1024 v1, u64 v)
{
    u512 *tmp = (u512 *)&v1;
    return ((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator==(u1024 v1, u128 v)
{
    u512 *tmp = (u512 *)&v1;
    return ((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator==(u1024 v1, u256 v)
{
    u512 *tmp = (u512 *)&v1;
    return ((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator==(u1024 v1, u512 v)
{
    u512 *tmp = (u512 *)&v1;
    return ((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator==(u1024 v1, u1024 v)
{
    return
        ((v1.ll == v.ll) && (v1.ml == v.ml) && (v1.tl == v.tl) && (v1.hl == v.hl) &&
         (v1.lm == v.lm) && (v1.mm == v.mm) && (v1.tm == v.tm) && (v1.hm == v.hm) &&
         (v1.lt == v.lt) && (v1.mt == v.mt) && (v1.tt == v.tt) && (v1.ht == v.ht) &&
         (v1.lh == v.lh) && (v1.mh == v.mh) && (v1.th == v.th) && (v1.hh == v.hh));
}

b32 operator!=(u1024 v1, u64 v)
{
    u512 *tmp = (u512 *)&v1;
    return !((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator!=(u1024 v1, u128 v)
{
    u512 *tmp = (u512 *)&v1;
    return !((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator!=(u1024 v1, u256 v)
{
    u512 *tmp = (u512 *)&v1;
    return !((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator!=(u1024 v1, u512 v)
{
    u512 *tmp = (u512 *)&v1;
    return !((*tmp == v) && (*(tmp + 1) == (u64)0));
}

b32 operator!=(u1024 v1, u1024 v)
{
    return
        !((v1.ll == v.ll) && (v1.ml == v.ml) && (v1.tl == v.tl) && (v1.hl == v.hl) &&
          (v1.lm == v.lh) && (v1.mm == v.mh) && (v1.tm == v.th) && (v1.hm == v.hh) &&
          (v1.lt == v.lt) && (v1.mt == v.mt) && (v1.tt == v.tt) && (v1.ht == v.ht) &&
          (v1.lh == v.lh) && (v1.mh == v.mh) && (v1.th == v.th) && (v1.hh == v.hh));
}

b32 operator&&(u1024 v1, u1024 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u1024 v1, u1024 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u1024 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u1024 v1, u64 v)
{
    u512 *tmp = (u512 *)&v1;
    return ((*tmp > v) || (*(tmp + 1) > (u64)0));
}

b32 operator>(u1024 v1, u1024 v) // @TODO: I'm having doubts on this function
{
    return ((v1.hh >= v.hh) || (v1.th >= v.th) ||
            (v1.mh >= v.mh) || (v1.lh >= v.lh) ||
            (v1.ht >= v.ht) || (v1.tt >= v.tt) ||
            (v1.mt >= v.mt) || (v1.lt >= v.lt) ||
            (v1.hm >= v.hm) || (v1.tm >= v.tm) ||
            (v1.mm >= v.mm) || (v1.lm >= v.lm) ||
            (v1.hl >= v.hl) || (v1.tl >= v.tl) ||
            (v1.ml >= v.ml) || (v1.ll > v.ll));
}

b32 operator>=(u1024 v1, u64 v)
{
    return ((v1.hh > 0) || (v1.th > 0) ||
            (v1.mh > 0) || (v1.lh > 0) ||
            (v1.ht > 0) || (v1.tt > 0) ||
            (v1.mt > 0) || (v1.lt > 0) ||
            (v1.hm > 0) || (v1.tm > 0) ||
            (v1.mm > 0) || (v1.lm > 0) ||
            (v1.hl > 0) || (v1.tl > 0) ||
            (v1.ml > 0) || (v1.ll >= v));
}

b32 operator>=(u1024 v1, u1024 v)
{
    return ((v1.hh >= v.hh) || (v1.th >= v.th) ||
            (v1.mh >= v.mh) || (v1.lh >= v.lh) ||
            (v1.ht >= v.ht) || (v1.tt >= v.tt) ||
            (v1.mt >= v.mt) || (v1.lt >= v.lt) ||
            (v1.hm >= v.hm) || (v1.tm >= v.tm) ||
            (v1.mm >= v.mm) || (v1.lm >= v.lm) ||
            (v1.hl >= v.hl) || (v1.tl >= v.tl) ||
            (v1.ml >= v.ml) || (v1.ll >= v.ll));
}

b32 operator<(u1024 v1, u64 v)
{
    return ((v1.hh == 0) || (v1.th == 0) ||
            (v1.mh == 0) || (v1.lh == 0) ||
            (v1.ht == 0) || (v1.tt == 0) ||
            (v1.mt == 0) || (v1.lt == 0) ||
            (v1.hm == 0) || (v1.tm == 0) ||
            (v1.mm == 0) || (v1.lm == 0) ||
            (v1.hl == 0) || (v1.tl == 0) ||
            (v1.ml == 0) || (v1.ll < v));
}

b32 operator<(u1024 v1, u1024 v)
{
    return ((v1.hh <= v.hh) || (v1.th <= v.th) ||
            (v1.mh <= v.mh) || (v1.lh <= v.lh) ||
            (v1.ht <= v.ht) || (v1.tt <= v.tt) ||
            (v1.mt <= v.mt) || (v1.lt <= v.lt) ||
            (v1.hm <= v.hm) || (v1.tm <= v.tm) ||
            (v1.mm <= v.mm) || (v1.lm <= v.lm) ||
            (v1.hl <= v.hl) || (v1.tl <= v.tl) ||
            (v1.ml <= v.ml) || (v1.ll < v.ll));
}

b32 operator<=(u1024 v1, u64 v)
{
    return ((v1.hh == 0) || (v1.th == 0) ||
            (v1.mh == 0) || (v1.lh == 0) ||
            (v1.ht == 0) || (v1.tt == 0) ||
            (v1.mt == 0) || (v1.lt == 0) ||
            (v1.hm == 0) || (v1.tm == 0) ||
            (v1.mm == 0) || (v1.lm == 0) ||
            (v1.hl == 0) || (v1.tl == 0) ||
            (v1.ml == 0) || (v1.ll <= v));
}

b32 operator<=(u1024 v1, u1024 v)
{
    return ((v1.hh <= v.hh) || (v1.th <= v.th) ||
            (v1.mh <= v.mh) || (v1.lh <= v.lh) ||
            (v1.ht <= v.ht) || (v1.tt <= v.tt) ||
            (v1.mt <= v.mt) || (v1.lt <= v.lt) ||
            (v1.hm <= v.hm) || (v1.tm <= v.tm) ||
            (v1.mm <= v.mm) || (v1.lm <= v.lm) ||
            (v1.hl <= v.hl) || (v1.tl <= v.tl) ||
            (v1.ml <= v.ml) || (v1.ll <= v.ll));
}

/*ARITHMETIC OP*/

u1024 operator+(u1024 v1, u64 v)
{ return u1024_add(&v1, v); }

u1024 operator+(u1024 v1, u1024 v)
{ return u1024_addBig(&v1, &v); }

void operator+=(u1024 &v1, u64 v)
{ v1 = u1024_add(&v1, v); }

void operator+=(u1024 &v1, u1024 v)
{ v1 = u1024_addBig(&v1, &v); }

u1024 operator-(u1024 v1, u64 v)
{ return u1024_sub(&v1, v); }

u1024 operator-(u1024 v1, u1024 v)
{ return u1024_subBig(&v1, &v); }

void operator-=(u1024 &v1, u64 v)
{ v1 = u1024_sub(&v1, v); }

void operator-=(u1024 &v1, u1024 v)
{ v1 = u1024_subBig(&v1, &v); }

u1024 operator*(u1024 v1, u64 v)
{ return u1024_mul(&v1, v); }

//NOTE: ASM Multiplication doesn't work, so I'm
//      substituting it with C && intrinsics.
/*
u1024 operator*(u1024 v1, u1024 v)
{ return u1024_mulBig(&v1, &v); }
*/

/*
void operator*=(u1024 &v1, u1024 v)
{ v1 = u1024_mulBig(&v1, &v); }
*/

// Example in 256 bits (every letter represents a 64bit value)
// v->           a  b  c  d *
// w->           e  f  g  h =
//               ------------
//            0  ha hb hc hd
//         0  ga gb gc gd 0  
//      0  fa fb fc fd 0  0
//      ea eb ec ed 0  0  0
//    ----------------------
//                          

u1024 u1024_multTest(u1024 v, u1024 w)
{
    u1024 result = {};
    
    u64 tmp = 0;
    
    u64 highPartOne = 0;
    u64 highPartTwo = 0;
    
    //u8  carry = 0;
    
    // Column 1
    result.arr[0] = _umul128(v.arr[0], w.arr[0], &highPartOne);
    
    /* Column 2 - 16*/
    for(u64 i = 2; i < 16; i++)
    {
        result.arr[i] += _addcarry_u64(0, result.arr[i-1], highPartOne, &result.arr[i-1]);
        
        for(u64 j = 0; j < i; j++) {
            tmp = _umul128(v.arr[i-j-1], w.arr[j], &highPartOne);
            result.arr[i] += _addcarry_u64(0, highPartTwo, highPartOne, &highPartTwo);
            result.arr[i] += _addcarry_u64(0, result.arr[i-1], tmp, &result.arr[i-1]);
        }
        
        highPartOne = highPartTwo;
        highPartTwo = 0;
    }
    
    return result;
}

u1024 operator*(u1024 v1, u1024 v)
{ return u1024_multTest(v1, v); }

void operator*=(u1024 &v1, u1024 v)
{ v1 = u1024_multTest(v1, v); }



void operator*=(u1024 &v1, u64 v)
{ v1 = u1024_mul(&v1, v); }

u1024 operator/(u1024 v1, u64 v)
{ u1024 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u1024 r = {}; return v != 0 ? u1024_divBig(&v1, &temp, &r) : u1024({}); }

u1024 operator/(u1024 v1, u1024 v)
{ u1024 r = {}; return v != u64(0) ? u1024_divBig(&v1, &v, &r) : u1024({}); }

void operator/=(u1024 &v1, u64 v)
{ u1024 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u1024 r = {}; v1 = v != 0 ? u1024_divBig(&v1, &temp, &r) : u1024({}); }

void operator/=(u1024 &v1, u1024 v)
{ u1024 r = {}; v1 = v != u64(0) ? u1024_divBig(&v1, &v, &r) : u1024({}); }

u1024 operator%(u1024 v1, u64 v)
{
    u1024 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u1024 r = {}; u1024_divBig(&v1, &temp, &r);
    return r;
}

u1024 operator%(u1024 v1, u1024 v)
{ u1024 r = {}; u1024_divBig(&v1, &v, &r); return r; }

void operator%=(u1024 &v1, u64 v)
{ u1024 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u1024 r = {}; u1024_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u1024 &v1, u1024 v)
{ u1024 r = {}; u1024_divBig(&v1, &v, &r); v1 = r; }

#if 0
u1024 operator++(int)
{ u1024 temp = v1; u1024_inc(&v1); return temp; }

u1024 operator--(int)
{ u1024 temp = v1; u1024_dec(&v1); return temp; }

u1024 operator++()
{ u1024_inc(&v1); return v1; }

u1024 operator--()
{ u1024_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u1024 operator<<(u1024 v1, u32 shift)
{ return u1024_shl(&v1, shift); }

void operator<<=(u1024 &v1, u32 shift)
{ v1 = u1024_shl(&v1, shift); }

u1024 operator>>(u1024 v1, u32 shift)
{ return u1024_shr(&v1, shift); }

void operator>>=(u1024 &v1, u32 shift)
{ v1 = u1024_shr(&v1, shift); }

/*BITWISE AND OP*/

u1024 operator&(u1024 v1, u1024 mask)
{ return u1024_and(&v1, &mask); }

u1024 operator&(u1024 v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u1024_and(&v1, &temp); }

void operator&=(u1024 &v1, u1024 mask)
{ v1 = u1024_and(&v1, &mask); }

void operator&=(u1024 &v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u1024_and(&v1, &temp); }

/*BITWISE OR OP*/

u1024 operator|(u1024 v1, u1024 mask)
{ return u1024_or(&v1, &mask); }

u1024 operator|(u1024 v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u1024_or(&v1, &temp); }

void operator|=(u1024 &v1, u1024 mask)
{ v1 = u1024_or(&v1, &mask); }

void operator|=(u1024 &v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u1024_or(&v1, &temp); }

/*BITWISE XOR OP*/

u1024 operator^(u1024 v1, u1024 mask)
{ return u1024_xor(&v1, &mask); }

u1024 operator^(u1024 v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u1024_xor(&v1, &temp); }

void operator^=(u1024 &v1, u1024 mask)
{ v1 = u1024_xor(&v1, &mask); }

void operator^=(u1024 &v1, u64 mask)
{ u1024 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u1024_xor(&v1, &temp); }

/*BITWISE NOT OP*/

u1024 operator~(u1024 v1)
{ return u1024_not(&v1); }












//
// u2048 Operations
//

/*LOGICAL OP*/

b32 operator==(u2048 v1, u64 v)
{ return ((v1.low == v) && (v1.high == (u64)0)); }

b32 operator==(u2048 v1, u128 v)
{ return ((v1.low == v) && (v1.high == (u64)0)); }

b32 operator==(u2048 v1, u256 v)
{ return ((v1.low == v) && (v1.high == (u64)0)); }

b32 operator==(u2048 v1, u512 v)
{ return ((v1.low == v) && (v1.high == (u64)0)); }

b32 operator==(u2048 v1, u1024 v)
{ return ((v1.low == v) && (v1.high == (u64)0)); }

b32 operator==(u2048 v1, u2048 v)
{ return ((v1.low == v.low) && (v1.high == v.high)); }

b32 operator!=(u2048 v1, u64 v)
{ return !(v1 == v); }

b32 operator!=(u2048 v1, u128 v)
{ return !(v1 == v); }

b32 operator!=(u2048 v1, u256 v)
{ return !(v1 == v); }

b32 operator!=(u2048 v1, u512 v)
{ return !(v1 == v); }

b32 operator!=(u2048 v1, u1024 v)
{ return !(v1 == v); }

b32 operator!=(u2048 v1, u2048 v)
{ return !(v1 == v); }

b32 operator&&(u2048 v1, u2048 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u2048 v1, u2048 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u2048 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u2048 v1, u64 v)
{ return ((v1.low > v) || (v1.high > (u64)0)); }

b32 operator>(u2048 v1, u2048 v) // @TODO: I'm having doubts on this function
{ return ((v1.high >= v.high) && (v1.low > v.low)); }

b32 operator>=(u2048 v1, u64 v)
{ return ((v1.high > (u64)0) || (v1.low >= v)); }

b32 operator>=(u2048 v1, u2048 v)
{ return ((v1.high >= v.high) && (v1.low >= v.low)); }

b32 operator<(u2048 v1, u64 v)
{ return ((v1.high == (u64)0) && (v1.low < v)); }

b32 operator<(u2048 v1, u2048 v)
{ return ((v1.high <= v.high) && (v1.low < v.low)); }

b32 operator<=(u2048 v1, u64 v)
{ return ((v1.high == (u64)0) && (v1.low <= v)); }

b32 operator<=(u2048 v1, u2048 v)
{ return ((v1.high <= v.high) && (v1.low <= v.low)); }

/*ARITHMETIC OP*/

u2048 operator+(u2048 v1, u64 v)
{ return u2048_add(&v1, v); }

u2048 operator+(u2048 v1, u2048 v)
{ return u2048_addBig(&v1, &v); }

void operator+=(u2048 &v1, u64 v)
{ v1 = u2048_add(&v1, v); }

void operator+=(u2048 &v1, u2048 v)
{ v1 = u2048_addBig(&v1, &v); }

u2048 operator-(u2048 v1, u64 v)
{ return u2048_sub(&v1, v); }

u2048 operator-(u2048 v1, u2048 v)
{ return u2048_subBig(&v1, &v); }

void operator-=(u2048 &v1, u64 v)
{ v1 = u2048_sub(&v1, v); }

void operator-=(u2048 &v1, u2048 v)
{ v1 = u2048_subBig(&v1, &v); }

/*
u2048 operator*(u2048 v1, u2048 v)
{ return u2048_mulBig(&v1, &v); }

void operator*=(u2048 &v1, u2048 v)
{ v1 = u2048_mulBig(&v1, &v); }
*/

// Example in 256 bits (every letter represents a 64bit value)
// v->           a  b  c  d *
// w->           e  f  g  h =
//               ------------
//            0  ha hb hc hd
//         0  ga gb gc gd 0  
//      0  fa fb fc fd 0  0
//      ea eb ec ed 0  0  0
//    ----------------------
//                          

u2048 u2048_multTest(u2048 v, u2048 w)
{
    u2048 result = {};
    
    u64 tmp = 0;
    
    u64 highPartOne = 0;
    u64 highPartTwo = 0;
    
    //u8  carry = 0;
    
    // Column 1
    result.arr[0] = _umul128(v.arr[0], w.arr[0], &highPartOne);
    
    /* Column 2 - 32*/
    for(u64 i = 2; i < 32; i++)
    {
        result.arr[i] += _addcarry_u64(0, result.arr[i-1], highPartOne, &result.arr[i-1]);
        
        for(u64 j = 0; j < i; j++) {
            tmp = _umul128(v.arr[i-j-1], w.arr[j], &highPartOne);
            result.arr[i] += _addcarry_u64(0, highPartTwo, highPartOne, &highPartTwo);
            result.arr[i] += _addcarry_u64(0, result.arr[i-1], tmp, &result.arr[i-1]);
        }
        
        highPartOne = highPartTwo;
        highPartTwo = 0;
    }
    
    return result;
}


u2048 operator*(u2048 v1, u2048 v)
{ return u2048_multTest(v1, v); }

void operator*=(u2048 &v1, u2048 v)
{ v1 = u2048_multTest(v1, v); }


u2048 operator*(u2048 v1, u64 v)
{ return u2048_mul(&v1, v); }

void operator*=(u2048 &v1, u64 v)
{ v1 = u2048_mul(&v1, v); }

u2048 operator/(u2048 v1, u64 v)
{ u2048 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u2048 r = {}; return v != 0 ? u2048_divBig(&v1, &temp, &r) : u2048({}); }

u2048 operator/(u2048 v1, u2048 v)
{ u2048 r = {}; return v != u64(0) ? u2048_divBig(&v1, &v, &r) : u2048({}); }

void operator/=(u2048 &v1, u64 v)
{ u2048 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u2048 r = {}; v1 = v != 0 ? u2048_divBig(&v1, &temp, &r) : u2048({}); }

void operator/=(u2048 &v1, u2048 v)
{ u2048 r = {}; v1 = v != u64(0) ? u2048_divBig(&v1, &v, &r) : u2048({}); }

u2048 operator%(u2048 v1, u64 v)
{ u2048 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u2048 r = {}; u2048_divBig(&v1, &temp, &r); return r; }

u2048 operator%(u2048 v1, u2048 v)
{ u2048 r = {}; u2048_divBig(&v1, &v, &r); return r; }

void operator%=(u2048 &v1, u64 v)
{ u2048 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u2048 r = {}; u2048_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u2048 &v1, u2048 v)
{ u2048 r = {}; u2048_divBig(&v1, &v, &r); v1 = r; }

#if 0
u2048 operator++(int)
{ u2048 temp = v1; u2048_inc(&v1); return temp; }

u2048 operator--(int)
{ u2048 temp = v1; u2048_dec(&v1); return temp; }

u2048 operator++()
{ u2048_inc(&v1); return v1; }

u2048 operator--()
{ u2048_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u2048 operator<<(u2048 v1, u32 shift)
{ return u2048_shl(&v1, shift); }

void operator<<=(u2048 &v1, u32 shift)
{ v1 = u2048_shl(&v1, shift); }

u2048 operator>>(u2048 v1, u32 shift)
{ return u2048_shr(&v1, shift); }

void operator>>=(u2048 &v1, u32 shift)
{ v1 = u2048_shr(&v1, shift); }

/*BITWISE AND OP*/

u2048 operator&(u2048 v1, u2048 mask)
{ return u2048_and(&v1, &mask); }

u2048 operator&(u2048 v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u2048_and(&v1, &temp); }

void operator&=(u2048 &v1, u2048 mask)
{ v1 = u2048_and(&v1, &mask); }

void operator&=(u2048 &v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u2048_and(&v1, &temp); }

/*BITWISE OR OP*/

u2048 operator|(u2048 v1, u2048 mask)
{ return u2048_or(&v1, &mask); }

u2048 operator|(u2048 v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u2048_or(&v1, &temp); }

void operator|=(u2048 &v1, u2048 mask)
{ v1 = u2048_or(&v1, &mask); }

void operator|=(u2048 &v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u2048_or(&v1, &temp); }

/*BITWISE XOR OP*/

u2048 operator^(u2048 v1, u2048 mask)
{ return u2048_xor(&v1, &mask); }

u2048 operator^(u2048 v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    return u2048_xor(&v1, &temp); }

void operator^=(u2048 &v1, u2048 mask)
{ v1 = u2048_xor(&v1, &mask); }

void operator^=(u2048 &v1, u64 mask)
{ u2048 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    v1 = u2048_xor(&v1, &temp); }

/*BITWISE NOT OP*/

u2048 operator~(u2048 v1)
{ return u2048_not(&v1); }


















//
// u4096 Operations
//

/*LOGICAL OP*/

b32 operator==(u4096 v1, u64 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u128 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u256 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u512 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u1024 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u2048 v)
{ return ((v1.low256 == v) && (v1.high256 == (u64)0)); }

b32 operator==(u4096 v1, u4096 v)
{ return ((v1.low256 == v.low256) && (v1.high256 == v.high256)); }

b32 operator!=(u4096 v1, u64 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u128 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u256 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u512 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u1024 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u2048 v)
{ return !(v1 == v); }

b32 operator!=(u4096 v1, u4096 v)
{ return !(v1 == v); }

b32 operator&&(u4096 v1, u4096 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u4096 v1, u4096 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u4096 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u4096 v1, u64 v)
{ return ((v1.low256 > v) || (v1.high256 > (u64)0)); }

b32 operator>(u4096 v1, u4096 v) // @TODO: I'm having doubts on this function
{ return ((v1.high256 >= v.high256) && (v1.low256 > v.low256)); }

b32 operator>=(u4096 v1, u64 v)
{ return ((v1.high256 > (u64)0) || (v1.low256 >= v)); }

b32 operator>=(u4096 v1, u4096 v)
{ return ((v1.high256 >= v.high256) && (v1.low256 >= v.low256)); }

b32 operator<(u4096 v1, u64 v)
{ return ((v1.high256 == (u64)0) && (v1.low256 < v)); }

b32 operator<(u4096 v1, u4096 v)
{ return ((v1.high256 <= v.high256) && (v1.low256 < v.low256)); }

b32 operator<=(u4096 v1, u64 v)
{ return ((v1.high256 == (u64)0) && (v1.low256 <= v)); }

b32 operator<=(u4096 v1, u4096 v)
{ return ((v1.high256 <= v.high256) && (v1.low256 <= v.low256)); }

/*ARITHMETIC OP*/

u4096 operator+(u4096 v1, u64 v)
{ return u4096_add(&v1, v); }

u4096 operator+(u4096 v1, u4096 v)
{ return u4096_addBig(&v1, &v); }

void operator+=(u4096 &v1, u64 v)
{ v1 = u4096_add(&v1, v); }

void operator+=(u4096 &v1, u4096 v)
{ v1 = u4096_addBig(&v1, &v); }

u4096 operator-(u4096 v1, u64 v)
{ return u4096_sub(&v1, v); }

u4096 operator-(u4096 v1, u4096 v)
{ return u4096_subBig(&v1, &v); }

void operator-=(u4096 &v1, u64 v)
{ v1 = u4096_sub(&v1, v); }

void operator-=(u4096 &v1, u4096 v)
{ v1 = u4096_subBig(&v1, &v); }

u4096 operator*(u4096 v1, u64 v)
{ return u4096_mul(&v1, v); }

u4096 operator*(u4096 v1, u4096 v)
{ return u4096_mulBig(&v1, &v); }

void operator*=(u4096 &v1, u64 v)
{ v1 = u4096_mul(&v1, v); }

void operator*=(u4096 &v1, u4096 v)
{ v1 = u4096_mulBig(&v1, &v); }

u4096 operator/(u4096 v1, u64 v)
{ u4096 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u4096 r = {}; return v != 0 ? u4096_divBig(&v1, &temp, &r) : u4096({}); }

u4096 operator/(u4096 v1, u4096 v)
{ u4096 r = {}; return v != u64(0) ? u4096_divBig(&v1, &v, &r) : u4096({}); }

void operator/=(u4096 &v1, u64 v)
{ u4096 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u4096 r = {}; v1 = v != 0 ? u4096_divBig(&v1, &temp, &r) : u4096({}); }

void operator/=(u4096 &v1, u4096 v)
{ u4096 r = {}; v1 = v != u64(0) ? u4096_divBig(&v1, &v, &r) : u4096({}); }

u4096 operator%(u4096 v1, u64 v)
{ u4096 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u4096 r = {}; u4096_divBig(&v1, &temp, &r); return r; }

u4096 operator%(u4096 v1, u4096 v)
{ u4096 r = {}; u4096_divBig(&v1, &v, &r); return r; }

void operator%=(u4096 &v1, u64 v)
{ u4096 temp = {v,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u4096 r = {}; u4096_divBig(&v1, &temp, &r); v1 = r; }

void operator%=(u4096 &v1, u4096 v)
{ u4096 r = {}; u4096_divBig(&v1, &v, &r); v1 = r; }

#if 0
u4096 operator++(int)
{ u4096 temp = v1; u4096_inc(&v1); return temp; }

u4096 operator--(int)
{ u4096 temp = v1; u4096_dec(&v1); return temp; }

u4096 operator++()
{ u4096_inc(&v1); return v1; }

u4096 operator--()
{ u4096_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u4096 operator<<(u4096 v1, u32 shift)
{ return u4096_shl(&v1, shift); }

void operator<<=(u4096 &v1, u32 shift)
{ v1 = u4096_shl(&v1, shift); }

u4096 operator>>(u4096 v1, u32 shift)
{ return u4096_shr(&v1, shift); }

void operator>>=(u4096 &v1, u32 shift)
{ v1 = u4096_shr(&v1, shift); }

/*BITWISE AND OP*/

u4096 operator&(u4096 v1, u4096 mask)
{ return u4096_and(&v1, &mask); }

u4096 operator&(u4096 v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; return u4096_and(&v1, &temp); }

void operator&=(u4096 &v1, u4096 mask)
{ v1 = u4096_and(&v1, &mask); }

void operator&=(u4096 &v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; v1 = u4096_and(&v1, &temp); }

/*BITWISE OR OP*/

u4096 operator|(u4096 v1, u4096 mask)
{ return u4096_or(&v1, &mask); }

u4096 operator|(u4096 v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; return u4096_or(&v1, &temp); }

void operator|=(u4096 &v1, u4096 mask)
{ v1 = u4096_or(&v1, &mask); }

void operator|=(u4096 &v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; v1 = u4096_or(&v1, &temp); }

/*BITWISE XOR OP*/

u4096 operator^(u4096 v1, u4096 mask)
{ return u4096_xor(&v1, &mask); }

u4096 operator^(u4096 v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; return u4096_xor(&v1, &temp); }

void operator^=(u4096 &v1, u4096 mask)
{ v1 = u4096_xor(&v1, &mask); }

void operator^=(u4096 &v1, u64 mask)
{ u4096 temp = {mask,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; v1 = u4096_xor(&v1, &temp); }

/*BITWISE NOT OP*/

u4096 operator~(u4096 v1)
{ return u4096_not(&v1); }

























//
// u8192 Operations
//

/*LOGICAL OP*/

b32 operator==(u8192 v1, u64 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u128 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u256 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u512 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u1024 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u2048 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u4096 v)
{ return ((v1.low512 == v) && (v1.high512 == (u64)0)); }

b32 operator==(u8192 v1, u8192 v)
{ return ((v1.low512 == v.low512) && (v1.high512 == v.high512)); }

b32 operator!=(u8192 v1, u64 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u128 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u256 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u512 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u1024 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u2048 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u4096 v)
{ return !(v1 == v); }

b32 operator!=(u8192 v1, u8192 v)
{ return !(v1 == v); }

b32 operator&&(u8192 v1, u8192 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u8192 v1, u8192 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u8192 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u8192 v1, u64 v)
{ return ((v1.low512 > v) || (v1.high512 > (u64)0)); }

b32 operator>(u8192 v1, u8192 v) // @TODO: I'm having doubts on this function
{ return ((v1.high512 >= v.high512) && (v1.low512 > v.low512)); }

b32 operator>=(u8192 v1, u64 v)
{ return ((v1.high512 > (u64)0) || (v1.low512 >= v)); }

b32 operator>=(u8192 v1, u8192 v)
{ return ((v1.high512 >= v.high512) && (v1.low512 >= v.low512)); }

b32 operator<(u8192 v1, u64 v)
{ return ((v1.high512 == (u64)0) && (v1.low512 < v)); }

b32 operator<(u8192 v1, u8192 v)
{ return ((v1.high512 <= v.high512) && (v1.low512 < v.low512)); }

b32 operator<=(u8192 v1, u64 v)
{ return ((v1.high512 == (u64)0) && (v1.low512 <= v)); }

b32 operator<=(u8192 v1, u8192 v)
{ return ((v1.high512 <= v.high512) && (v1.low512 <= v.low512)); }

/*ARITHMETIC OP*/

u8192 operator+(u8192 v1, u64 v)
{ return u8192_add(&v1, v); }

u8192 operator+(u8192 v1, u8192 v)
{ return u8192_addBig(&v1, &v); }

void operator+=(u8192 &v1, u64 v)
{ v1 = u8192_add(&v1, v); }

void operator+=(u8192 &v1, u8192 v)
{ v1 = u8192_addBig(&v1, &v); }

u8192 operator-(u8192 v1, u64 v)
{ return u8192_sub(&v1, v); }

u8192 operator-(u8192 v1, u8192 v)
{ return u8192_subBig(&v1, &v); }

void operator-=(u8192 &v1, u64 v)
{ v1 = u8192_sub(&v1, v); }

void operator-=(u8192 &v1, u8192 v)
{ v1 = u8192_subBig(&v1, &v); }

u8192 operator*(u8192 v1, u64 v)
{ return u8192_mul(&v1, v); }

u8192 operator*(u8192 v1, u8192 v)
{ return u8192_mulBig(&v1, &v); }

void operator*=(u8192 &v1, u64 v)
{ v1 = u8192_mul(&v1, v); }

void operator*=(u8192 &v1, u8192 v)
{ v1 = u8192_mulBig(&v1, &v); }

u8192 operator/(u8192 v1, u64 v)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = v;
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192 zero; zero.low512 = {}; zero.high512 = {};
    return v != 0 ? u8192_divBig(&v1, &temp, &r) : zero;
}

u8192 operator/(u8192 v1, u8192 v)
{
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192 zero; zero.low512 = {}; zero.high512 = {};
    return v != u64(0) ? u8192_divBig(&v1, &v, &r) : zero;
}

void operator/=(u8192 &v1, u64 v)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = v;
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192 zero; zero.low512 = {}; zero.high512 = {};
    v1 = v != 0 ? u8192_divBig(&v1, &temp, &r) : zero;
}

void operator/=(u8192 &v1, u8192 v)
{
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192 zero; zero.low512 = {}; zero.high512 = {};
    v1 = v != u64(0) ? u8192_divBig(&v1, &v, &r) : zero;
}

u8192 operator%(u8192 v1, u64 v)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = v;
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192_divBig(&v1, &temp, &r); return r; }

u8192 operator%(u8192 v1, u8192 v)
{
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192_divBig(&v1, &v, &r); return r;
}

void operator%=(u8192 &v1, u64 v)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = v;
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192_divBig(&v1, &temp, &r); v1 = r;
}

void operator%=(u8192 &v1, u8192 v)
{
    u8192 r; r.low512 = {}; r.high512 = {};
    u8192_divBig(&v1, &v, &r); v1 = r;
}

#if 0
u8192 operator++(int)
{ u8192 temp = v1; u8192_inc(&v1); return temp; }

u8192 operator--(int)
{ u8192 temp = v1; u8192_dec(&v1); return temp; }

u8192 operator++()
{ u8192_inc(&v1); return v1; }

u8192 operator--()
{ u8192_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u8192 operator<<(u8192 v1, u32 shift)
{ return u8192_shl(&v1, shift); }

void operator<<=(u8192 &v1, u32 shift)
{ v1 = u8192_shl(&v1, shift); }

u8192 operator>>(u8192 v1, u32 shift)
{ return u8192_shr(&v1, shift); }

void operator>>=(u8192 &v1, u32 shift)
{ v1 = u8192_shr(&v1, shift); }

/*BITWISE AND OP*/

u8192 operator&(u8192 v1, u8192 mask)
{ return u8192_and(&v1, &mask); }

u8192 operator&(u8192 v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    return u8192_and(&v1, &temp);
}

void operator&=(u8192 &v1, u8192 mask)
{ v1 = u8192_and(&v1, &mask); }

void operator&=(u8192 &v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    v1 = u8192_and(&v1, &temp);
}

/*BITWISE OR OP*/

u8192 operator|(u8192 v1, u8192 mask)
{ return u8192_or(&v1, &mask); }

u8192 operator|(u8192 v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    return u8192_or(&v1, &temp);
}

void operator|=(u8192 &v1, u8192 mask)
{ v1 = u8192_or(&v1, &mask); }

void operator|=(u8192 &v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    v1 = u8192_or(&v1, &temp);
}

/*BITWISE XOR OP*/

u8192 operator^(u8192 v1, u8192 mask)
{ return u8192_xor(&v1, &mask); }

u8192 operator^(u8192 v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    return u8192_xor(&v1, &temp);
}

void operator^=(u8192 &v1, u8192 mask)
{ v1 = u8192_xor(&v1, &mask); }

void operator^=(u8192 &v1, u64 mask)
{
    u8192 temp; temp.low512 = {}; temp.high512 = {}; temp.b8 = mask;
    v1 = u8192_xor(&v1, &temp);
}

/*BITWISE NOT OP*/

u8192 operator~(u8192 v1)
{ return u8192_not(&v1); }






























//
// u16384 Operations
//

/*LOGICAL OP*/

b32 operator==(u16384 v1, u64 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u128 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u256 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u512 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u1024 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u2048 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u4096 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u8192 v)
{ return ((v1.low1024 == v) && (v1.high1024 == (u64)0)); }

b32 operator==(u16384 v1, u16384 v)
{ return ((v1.low1024 == v.low1024) && (v1.high1024 == v.high1024)); }

b32 operator!=(u16384 v1, u64 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u128 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u256 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u512 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u1024 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u2048 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u4096 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u8192 v)
{ return !(v1 == v); }

b32 operator!=(u16384 v1, u16384 v)
{ return !(v1 == v); }

b32 operator&&(u16384 v1, u16384 v)
{ return (v1 != u64(0) && (v != u64(0))); }

b32 operator||(u16384 v1, u16384 v)
{ return (v1 != u64(0) || (v != u64(0))); }

b32 operator!(u16384 v1)
{ return v1 == u64(0) ? 1 : 0; }

b32 operator>(u16384 v1, u64 v)
{ return ((v1.low1024 > v) || (v1.high1024 > (u64)0)); }

b32 operator>(u16384 v1, u16384 v) // @TODO: I'm having doubts on this function
{ return ((v1.high1024 >= v.high1024) && (v1.low1024 > v.low1024)); }

b32 operator>=(u16384 v1, u64 v)
{ return ((v1.high1024 > (u64)0) || (v1.low1024 >= v)); }

b32 operator>=(u16384 v1, u16384 v)
{ return ((v1.high1024 >= v.high1024) && (v1.low1024 >= v.low1024)); }

b32 operator<(u16384 v1, u64 v)
{ return ((v1.high1024 == (u64)0) && (v1.low1024 < v)); }

b32 operator<(u16384 v1, u16384 v)
{ return ((v1.high1024 <= v.high1024) && (v1.low1024 < v.low1024)); }

b32 operator<=(u16384 v1, u64 v)
{ return ((v1.high1024 == (u64)0) && (v1.low1024 <= v)); }

b32 operator<=(u16384 v1, u16384 v)
{ return ((v1.high1024 <= v.high1024) && (v1.low1024 <= v.low1024)); }

/*ARITHMETIC OP*/

u16384 operator+(u16384 v1, u64 v)
{ return u16384_add(&v1, v); }

u16384 operator+(u16384 v1, u16384 v)
{ return u16384_addBig(&v1, &v); }

void operator+=(u16384 &v1, u64 v)
{ v1 = u16384_add(&v1, v); }

void operator+=(u16384 &v1, u16384 v)
{ v1 = u16384_addBig(&v1, &v); }

u16384 operator-(u16384 v1, u64 v)
{ return u16384_sub(&v1, v); }

u16384 operator-(u16384 v1, u16384 v)
{ return u16384_subBig(&v1, &v); }

void operator-=(u16384 &v1, u64 v)
{ v1 = u16384_sub(&v1, v); }

void operator-=(u16384 &v1, u16384 v)
{ v1 = u16384_subBig(&v1, &v); }

u16384 operator*(u16384 v1, u64 v)
{ return u16384_mul(&v1, v); }

u16384 operator*(u16384 v1, u16384 v)
{ return u16384_mulBig(&v1, &v); }

void operator*=(u16384 &v1, u64 v)
{ v1 = u16384_mul(&v1, v); }

void operator*=(u16384 &v1, u16384 v)
{ v1 = u16384_mulBig(&v1, &v); }

u16384 operator/(u16384 v1, u64 v)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {};temp.b8 = v;
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384 zero; zero.low = {}; zero.med = {}; zero.tall = {}; zero.high = {};
    return v != 0 ? u16384_divBig(&v1, &temp, &r) : zero;
}

u16384 operator/(u16384 v1, u16384 v)
{
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384 zero; zero.low = {}; zero.med = {}; zero.tall = {}; zero.high = {};
    return v != u64(0) ? u16384_divBig(&v1, &v, &r) : zero;
}

void operator/=(u16384 &v1, u64 v)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {};temp.b8 = v;
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384 zero; zero.low = {}; zero.med = {}; zero.tall = {}; zero.high = {};
    v1 = v != 0 ? u16384_divBig(&v1, &temp, &r) : zero;
}

void operator/=(u16384 &v1, u16384 v)
{
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384 zero; zero.low = {}; zero.med = {}; zero.tall = {}; zero.high = {};
    v1 = v != u64(0) ? u16384_divBig(&v1, &v, &r) : zero;
}

u16384 operator%(u16384 v1, u64 v)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {};temp.b8 = v;
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384_divBig(&v1, &temp, &r); return r; }

u16384 operator%(u16384 v1, u16384 v)
{
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384_divBig(&v1, &v, &r); return r;
}

void operator%=(u16384 &v1, u64 v)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {};temp.b8 = v;
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384_divBig(&v1, &temp, &r); v1 = r;
}

void operator%=(u16384 &v1, u16384 v)
{
    u16384 r; r.low = {}; r.med = {}; r.tall = {}; r.high = {};
    u16384_divBig(&v1, &v, &r); v1 = r;
}

#if 0
u16384 operator++(int)
{ u16384 temp = v1; u16384_inc(&v1); return temp; }

u16384 operator--(int)
{ u16384 temp = v1; u16384_dec(&v1); return temp; }

u16384 operator++()
{ u16384_inc(&v1); return v1; }

u16384 operator--()
{ u16384_dec(&v1); return v1; }
#endif

/*BITWISE SHIFT OP*/
//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
u16384 operator<<(u16384 v1, u32 shift)
{ return u16384_shl(&v1, shift); }

void operator<<=(u16384 &v1, u32 shift)
{ v1 = u16384_shl(&v1, shift); }

u16384 operator>>(u16384 v1, u32 shift)
{ return u16384_shr(&v1, shift); }

void operator>>=(u16384 &v1, u32 shift)
{ v1 = u16384_shr(&v1, shift); }

/*BITWISE AND OP*/

u16384 operator&(u16384 v1, u16384 mask)
{ return u16384_and(&v1, &mask); }

u16384 operator&(u16384 v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    return u16384_and(&v1, &temp);
}

void operator&=(u16384 &v1, u16384 mask)
{ v1 = u16384_and(&v1, &mask); }

void operator&=(u16384 &v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    v1 = u16384_and(&v1, &temp);
}

/*BITWISE OR OP*/

u16384 operator|(u16384 v1, u16384 mask)
{ return u16384_or(&v1, &mask); }

u16384 operator|(u16384 v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    return u16384_or(&v1, &temp);
}

void operator|=(u16384 &v1, u16384 mask)
{ v1 = u16384_or(&v1, &mask); }

void operator|=(u16384 &v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    v1 = u16384_or(&v1, &temp);
}

/*BITWISE XOR OP*/

u16384 operator^(u16384 v1, u16384 mask)
{ return u16384_xor(&v1, &mask); }

u16384 operator^(u16384 v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    return u16384_xor(&v1, &temp);
}

void operator^=(u16384 &v1, u16384 mask)
{ v1 = u16384_xor(&v1, &mask); }

void operator^=(u16384 &v1, u64 mask)
{
    u16384 temp; temp.low = {}; temp.med = {};
    temp.tall = {}; temp.high = {}; temp.b8 = mask;
    v1 = u16384_xor(&v1, &temp);
}

/*BITWISE NOT OP*/

u16384 operator~(u16384 v1)
{ return u16384_not(&v1); }













//@Cleanup @Speedup @Todo : Make this completely ASM
u128 u128_pow(u128 v, u32 exp)
{
	u128 Result = {1, 0};
	while (exp)
	{
		if (exp & 1)
		{ Result *= v; }
        
		exp >>= 1;
		v *= v;
	}
    
	return Result;
}

string u128_str(u128 v)
{
    string Result = ls_strAlloc(64);
    u128 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).l;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u256 u256_pow(u256 v, u32 exp)
{
    u256 Result = {1, 0, 0, 0};
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u256_str(u256 v)
{
    string Result = ls_strAlloc(128);
    u256 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).l;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u512 u512_pow(u512 v, u32 exp)
{
    u512 Result = {1, 0, 0, 0, 0, 0, 0, 0};
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u512_str(u512 v)
{
    string Result = ls_strAlloc(256);
    u512 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).ll;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u1024 u1024_pow(u1024 v, u32 exp)
{
    u1024 Result = {1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0};
    while (exp)
    {
        if (exp & 1)
        {
            Result = u1024_multTest(Result, v);
            //Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u1024_str(u1024 v)
{
    string Result = ls_strAlloc(448);
    u1024 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).ll;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

u1024 u1024_from64(u64 v)
{
    u1024 Result = {v, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0};
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u2048 u2048_pow(u2048 v, u32 exp)
{
    u2048 Result = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u2048_str(u2048 v)
{
    string Result = ls_strAlloc(1024);
    u2048 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).b8;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u4096 u4096_pow(u4096 v, u32 exp)
{
    u4096 Result = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u4096_str(u4096 v)
{
    string Result = ls_strAlloc(1728);
    u4096 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).b8;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}


//@Cleanup @Speedup @Todo : Make this completely ASM
u8192 u8192_pow(u8192 v, u32 exp)
{
    u8192 Result;
    Result.low512 = {};
    Result.high512 = {};
    Result.b8 = 1;
    
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u8192_str(u8192 v)
{
    string Result = ls_strAlloc(2564);
    u8192 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).b8;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u16384 u16384_pow(u16384 v, u32 exp)
{
    u16384 Result;
    Result.low = {};
    Result.med = {};
    Result.tall = {};
    Result.high = {};
    Result.b8 = 1;
    
    while (exp)
    {
        if (exp & 1)
        {
            Result *= v;
        }
        
        exp >>= 1;
        v *= v;
    }
    
    return Result;
}

string u16384_str(u16384 v)
{
    string Result = ls_strAlloc(5000);
    u16384 cpy = v;
    
    u32 i = 0;
    b32 first = TRUE;
    while(cpy > 0)
    {
        if((i%3 == 0) && (first != TRUE))
        {
            ls_strAppendChar(&Result, '.');
        }
        
        u64 r = (cpy % 10).b8;
        cpy = cpy / 10;
        
        string val = ls_itos(r);
        ls_strAppend(&Result, val);
        ls_strFree(&val);
        i++;
        
        if(first == TRUE) { first = FALSE; }
    }
    
    ls_strReverse(&Result);
    
    return Result;
}

u16384 u16384_from64(u64 v)
{
    u16384 Result;
    Result.low = {};
    Result.med = {};
    Result.tall = {};
    Result.high = {};
    Result.b8 = v;
    
    return Result;
}

#endif