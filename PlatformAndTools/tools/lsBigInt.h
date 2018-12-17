#ifndef LS_BIGINT_HEADER
#define LS_BIGINT_HEADER

#if 1
#ifndef LS_WINDOWS
#include "Platform\lsWindows.h"
#endif
#endif

struct u128;
struct u256;
struct u512;
struct u1024;
struct u2048;
struct u4096;

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
    
    //
    // u256 Operations
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
#if 0
    string u1024_hex(u1024 v);
#endif
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
    
}

struct u128
{
	u64 l;
	u64 h;
    
	u128(u64 low, u64 high)
	{ l = low; h = high; }
    
	u128(u64 low)
	{ l = low; h = 0; }
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{ return ((this->h == 0) && (this->l == v)); }
    
	bool operator==(u128 v)
	{ return ((this->h == v.h) && (this->l == v.l)); }
    
	bool operator!=(u64 v)
	{ return !((this->h == 0) && (this->l == v)); }
    
	bool operator!=(u128 v)
	{ return !((this->h == v.h) && (this->l == v.l)); }
    
	bool operator&&(u128 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u128 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{ return ((this->h > 0) || (this->l > v)); }
    
	bool operator>(u128 v) // @TODO: I'm having doubts on this function
	{ return ((this->h >= v.h) && (this->l > v.l)); }
    
	bool operator>=(u64 v)
	{ return ((this->h > 0) || (this->l >= v)); }
    
	bool operator>=(u128 v)
	{ return ((this->h >= v.h) && (this->l >= v.l)); }
    
	bool operator<(u64 v)
	{ return ((this->h == 0) && (this->l < v)); }
    
	bool operator<(u128 v)
	{ return ((this->h <= v.h) && (this->l < v.l)); }
    
	bool operator<=(u64 v)
	{ return ((this->h == 0) && (this->l <= v)); }
    
	bool operator<=(u128 v)
	{ return ((this->h <= v.h) && (this->l <= v.l)); }
    
	/*ARITHMETIC OP*/
    
	u128 operator+(u64 v)
	{ return u128_add(this, v); }
	
	u128 operator+(u128 v)
	{ return u128_addBig(this, &v); }
    
	void operator+=(u64 v)
	{ *this = u128_add(this, v); }
    
	void operator+=(u128 v)
	{ *this = u128_addBig(this, &v); }
    
	u128 operator-(u64 v)
	{ return u128_sub(this, v); }
    
	u128 operator-(u128 v)
	{ return u128_subBig(this, &v); }
    
	void operator-=(u64 v)
	{ *this = u128_sub(this, v); }
    
	void operator-=(u128 v)
	{ *this = u128_subBig(this, &v); }
    
	u128 operator*(u64 v)
	{ return u128_mul(this, v); }
    
	u128 operator*(u128 v)
	{ return u128_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u128_mul(this, v); }
    
	void operator*=(u128 v)
	{ *this = u128_mulBig(this, &v); }
    
	u128 operator/(u64 v)
	{ u128 temp = v; u128 r = 0; return v != 0 ? u128_divBig(this, &temp, &r) : 0; }
    
	u128 operator/(u128 v)
	{ u128 r = 0; return v != u64(0) ? u128_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u128 temp = v; u128 r = 0; *this = v != 0 ? u128_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u128 v)
	{ u128 r = 0; *this = v != u64(0) ? u128_divBig(this, &v, &r) : 0; }
    
	u128 operator%(u64 v)
	{ u128 temp = v; u128 r = 0; u128_divBig(this, &temp, &r); return r; }
    
	u128 operator%(u128 v)
	{ u128 r = 0; u128_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u128 temp = v; u128 r = 0; u128_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u128 v)
	{ u128 r = 0; u128_divBig(this, &v, &r); *this = r; }
    
	u128 operator++(int)
	{ u128 temp = *this; u128_inc(this); return temp; }
    
	u128 operator--(int)
	{ u128 temp = *this; u128_dec(this); return temp; }
    
	u128 operator++()
	{ u128_inc(this); return *this; }
    
	u128 operator--()
	{ u128_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u128 operator<<(u32 shift)
	{ return u128_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u128_shl(this, shift); }
    
	u128 operator>>(u32 shift)
	{ return u128_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u128_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u128 operator&(u128 mask)
	{ return u128_and(this, &mask); }
    
	u128 operator&(u64 mask)
	{ u128 temp = mask;	return u128_and(this, &temp); }
    
	void operator&=(u128 mask)
	{ *this = u128_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u128 temp = mask; *this = u128_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u128 operator|(u128 mask)
	{ return u128_or(this, &mask); }
    
	u128 operator|(u64 mask)
	{ u128 temp = mask;	return u128_or(this, &temp); }
    
	void operator|=(u128 mask)
	{ *this = u128_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u128 temp = mask; *this = u128_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u128 operator^(u128 mask)
	{ return u128_xor(this, &mask); }
    
	u128 operator^(u64 mask)
	{ u128 temp = mask;	return u128_xor(this, &temp); }
    
	void operator^=(u128 mask)
	{ *this = u128_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u128 temp = mask; *this = u128_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u128 operator~()
	{ return u128_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u64() { return this->l; }
	operator u32() { return (u32)this->l; }
	operator u16() { return (u16)this->l; }
	operator u8()  { return (u8)this->l; }
    
	operator s64() { return (s64)this->l; }
	operator s32() { return (s32)this->l; }
	operator s16() { return (s16)this->l; }
	operator s8()  { return (s8)this->l; }
};

struct u256
{
	u64 l;
	u64 m;
	u64 t;
	u64 h;
    
	u256(u64 low, u64 medium, u64 tall, u64 high)
	{ l = low; m = medium; t = tall; h = high; }
    
	u256(u64 low)
	{ l = low; m = 0; t = 0; h = 0;	}
    
	u256(u128 low)
	{ l = low.l; m = low.h; t = 0; h = 0; }
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{ 
		return ((this->h == 0) && (this->t == 0) && 
                (this->m == 0) && (this->l == v));
	}
    
	bool operator==(u128 v)
	{
		return ((this->h == 0) && (this->t == 0) && 
                (this->m == v.h) && (this->l == v.l));
	}
    
	bool operator==(u256 v)
	{
		return ((this->h == v.h) && (this->t == v.t) && 
                (this->m == v.m) && (this->l == v.l));
	}
    
	bool operator!=(u64 v)
	{
		return !((this->h == 0) && (this->t == 0) &&
                 (this->m == 0) && (this->l == v));
	}
    
	bool operator!=(u128 v)
	{
		return !((this->h == 0) && (this->t == 0) &&
                 (this->m == v.h) && (this->l == v.l));
	}
    
	bool operator!=(u256 v)
	{
		return !((this->h == v.h) && (this->t == v.t) &&
                 (this->m == v.m) && (this->l == v.l));
	}
    
	bool operator&&(u256 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u256 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{ return ((this->h > 0) || (this->t > 0) || (this->m > 0) || (this->l > v)); }
    
	bool operator>(u256 v) // @TODO: I'm having doubts on this function
	{ return ((this->h >= v.h) && (this->t >= v.t) && (this->m >= v.m) && (this->l > v.l)); }
    
	bool operator>=(u64 v)
	{ return ((this->h > 0) || (this->t > 0) || (this->m > 0) || (this->l >= v)); }
    
	bool operator>=(u256 v)
	{ return ((this->h >= v.h) && (this->t >= v.t) && (this->m >= v.m) && (this->l >= v.l)); }
    
	bool operator<(u64 v)
	{ return ((this->h == 0) && (this->t == 0) && (this->m == 0) && (this->l < v)); }
    
	bool operator<(u256 v)
	{ return ((this->h <= v.h) && (this->t <= v.t) && (this->m <= v.m) && (this->l < v.l)); }
    
	bool operator<=(u64 v)
	{ return ((this->h == 0) && (this->t == 0) && (this->m == 0) && (this->l <= v)); }
    
	bool operator<=(u256 v)
	{ return ((this->h <= v.h) && (this->t <= v.t) && (this->m <= v.m) && (this->l <= v.l)); }
    
	/*ARITHMETIC OP*/
    
	u256 operator+(u64 v)
	{ return u256_add(this, v); }
    
	u256 operator+(u256 v)
	{ return u256_addBig(this, &v); }
    
	void operator+=(u64 v)
	{ *this = u256_add(this, v); }
    
	void operator+=(u256 v)
	{ *this = u256_addBig(this, &v); }
    
	u256 operator-(u64 v)
	{ return u256_sub(this, v); }
    
	u256 operator-(u256 v)
	{ return u256_subBig(this, &v); }
    
	void operator-=(u64 v)
	{ *this = u256_sub(this, v); }
    
	void operator-=(u256 v)
	{ *this = u256_subBig(this, &v); }
    
	u256 operator*(u64 v)
	{ return u256_mul(this, v); }
    
	u256 operator*(u256 v)
	{  return u256_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u256_mul(this, v); }
    
	void operator*=(u256 v)
	{ *this = u256_mulBig(this, &v); }
    
	u256 operator/(u64 v)
	{ u256 temp = v; u256 r = 0; return v != 0 ? u256_divBig(this, &temp, &r) : 0; }
    
	u256 operator/(u256 v)
	{ u256 r = 0; return v != u64(0) ? u256_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u256 temp = v; u256 r = 0; *this = v != 0 ? u256_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u256 v)
	{ u256 r = 0; *this = v != u64(0) ? u256_divBig(this, &v, &r) : 0; }
    
	u256 operator%(u64 v)
	{ u256 temp = v; u256 r = 0; u256_divBig(this, &temp, &r); return r; }
    
	u256 operator%(u256 v)
	{ u256 r = 0; u256_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u256 temp = v; u256 r = 0; u256_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u256 v)
	{ u256 r = 0; u256_divBig(this, &v, &r); *this = r; }
    
	u256 operator++(int)
	{ u256 temp = *this; u256_inc(this); return temp; }
    
	u256 operator--(int)
	{ u256 temp = *this; u256_dec(this); return temp; }
    
	u256 operator++()
	{ u256_inc(this); return *this; }
    
	u256 operator--()
	{ u256_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u256 operator<<(u32 shift)
	{ return u256_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u256_shl(this, shift); }
    
	u256 operator>>(u32 shift)
	{ return u256_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u256_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u256 operator&(u256 mask)
	{ return u256_and(this, &mask); }
    
	u256 operator&(u64 mask)
	{ u256 temp = mask;	return u256_and(this, &temp); }
    
	void operator&=(u256 mask)
	{ *this = u256_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u256 temp = mask; *this = u256_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u256 operator|(u256 mask)
	{ return u256_or(this, &mask); }
    
	u256 operator|(u64 mask)
	{ u256 temp = mask;	return u256_or(this, &temp); }
    
	void operator|=(u256 mask)
	{ *this = u256_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u256 temp = mask; *this = u256_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u256 operator^(u256 mask)
	{ return u256_xor(this, &mask); }
    
	u256 operator^(u64 mask)
	{ u256 temp = mask;	return u256_xor(this, &temp); }
    
	void operator^=(u256 mask)
	{ *this = u256_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u256 temp = mask; *this = u256_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u256 operator~()
	{ return u256_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u128() { u128 tmp = this->l; tmp.h = this->m; return tmp; }
	operator u64() { return this->l; }
	operator u32() { return (u32)this->l; }
	operator u16() { return (u16)this->l; }
	operator u8() { return (u8)this->l; }
    
	operator s64() { return (s64)this->l; }
	operator s32() { return (s32)this->l; }
	operator s16() { return (s16)this->l; }
	operator s8() { return (s8)this->l; }
};

struct u512
{
	u64 ll;
	u64 ml;
	u64 tl;
	u64 hl;
    
	u64 lh;
	u64 mh;
	u64 th;
	u64 hh;
    
	u512(u64 lowlow, u64 medlow, u64 tallow, u64 highlow,
         u64 lowhigh, u64 medhigh, u64 tallhigh, u64 highhigh)
	{
		ll = lowlow; ml = medlow; tl = tallow; hl = highlow;
		lh = lowhigh; mh = medhigh; th = tallhigh; hh = highhigh;
	}
    
	u512(u64 low)
	{ ll = low; ml = 0; tl = 0; hl = 0; lh = 0; mh = 0; th = 0; hh = 0;	}
    
	u512(u128 low)
	{
		ll = low.l; ml = low.h; tl = 0; hl = 0;
		lh = 0; mh = 0; th = 0; hh = 0;
	}
    
	u512(u256 low)
	{
		ll = low.l; ml = low.m; tl = low.t; hl = low.h;
		lh = 0; mh = 0; th = 0; hh = 0;
	}
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{
		return ((this->hh == 0) && (this->th == 0) && 
                (this->mh == 0) && (this->lh == 0) && 
                (this->hl == 0) && (this->tl == 0) && 
                (this->ml == 0) && (this->ll == v));
	}
    
	bool operator==(u128 v)
	{
		return ((this->hh == 0) && (this->th == 0) &&
                (this->mh == 0) && (this->lh == 0) &&
                (this->hl == 0) && (this->tl == 0) &&
                (this->ml == v.h) && (this->ll == v.l));
	}
    
	bool operator==(u256 v)
	{
		return ((this->hh == 0) && (this->th == 0) &&
                (this->mh == 0) && (this->lh == 0) &&
                (this->hl == v.h) && (this->tl == v.t) &&
                (this->ml == v.m) && (this->ll == v.l));
	}
    
	bool operator==(u512 v)
	{
		return ((this->hh == v.hh) && (this->th == v.th) &&
                (this->mh == v.mh) && (this->lh == v.lh) &&
                (this->hl == v.hl) && (this->tl == v.tl) &&
                (this->ml == v.ml) && (this->ll == v.ll));
	}
    
	bool operator!=(u64 v)
	{
		return !((this->hh == 0) && (this->th == 0) &&
                 (this->mh == 0) && (this->lh == 0) &&
                 (this->hl == 0) && (this->tl == 0) &&
                 (this->ml == 0) && (this->ll == v));
	}
    
	bool operator!=(u128 v)
	{
		return !((this->hh == 0) && (this->th == 0) &&
                 (this->mh == 0) && (this->lh == 0) &&
                 (this->hl == 0) && (this->tl == 0) &&
                 (this->ml == v.h) && (this->ll == v.l));
	}
    
	bool operator!=(u256 v)
	{
		return !((this->hh == 0) && (this->th == 0) &&
                 (this->mh == 0) && (this->lh == 0) &&
                 (this->hl == v.h) && (this->tl == v.t) &&
                 (this->ml == v.m) && (this->ll == v.l));
	}
    
	bool operator!=(u512 v)
	{
		return !((this->hh == v.hh) && (this->th == v.th) &&
                 (this->mh == v.mh) && (this->lh == v.lh) &&
                 (this->hl == v.hl) && (this->tl == v.tl) &&
                 (this->ml == v.ml) && (this->ll == v.ll));
	}
    
	bool operator&&(u512 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u512 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{
		return ((this->hh > 0) || (this->th > 0) || (this->mh > 0) || (this->lh > 0) ||
                (this->hl > 0) || (this->tl > 0) || (this->ml > 0) || (this->ll > v));
	}
    
	bool operator>(u512 v) // @TODO: I'm having doubts on this function
	{
		return ((this->hh >= v.hh) && (this->th >= v.th) &&
                (this->mh >= v.mh) && (this->lh >= v.lh) &&
                (this->hl >= v.hl) && (this->tl >= v.tl) &&
                (this->ml >= v.ml) && (this->ll > v.ll));
	}
    
	bool operator>=(u64 v)
	{
		return ((this->hh > 0) || (this->th > 0) ||
                (this->mh > 0) || (this->lh > 0) ||
                (this->hl > 0) || (this->tl > 0) ||
                (this->ml > 0) || (this->ll >= v));
	}
    
	bool operator>=(u512 v)
	{
		return ((this->hh >= v.hh) && (this->th >= v.th) &&
                (this->mh >= v.mh) && (this->lh >= v.lh) &&
                (this->hl >= v.hl) && (this->tl >= v.tl) &&
                (this->ml >= v.ml) && (this->ll >= v.ll));
	}
    
	bool operator<(u64 v)
	{
		return ((this->hh == 0) && (this->th == 0) && (this->mh == 0) && (this->lh == 0) &&
                (this->hl == 0) && (this->tl == 0) && (this->ml == 0) && (this->ll < v));
	}
    
	bool operator<(u512 v)
	{
		return ((this->hh <= v.hh) && (this->th <= v.th) &&
                (this->mh <= v.mh) && (this->lh <= v.lh) &&
                (this->hl <= v.hl) && (this->tl <= v.tl) &&
                (this->ml <= v.ml) && (this->ll < v.ll));
	}
    
	bool operator<=(u64 v)
	{
		return ((this->hh == 0) && (this->th == 0) && (this->mh == 0) && (this->lh == 0) &&
                (this->hl == 0) && (this->tl == 0) && (this->ml == 0) && (this->ll <= v));
	}
    
	bool operator<=(u512 v)
	{
		return ((this->hh <= v.hh) && (this->th <= v.th) &&
                (this->mh <= v.mh) && (this->lh <= v.lh) &&
                (this->hl <= v.hl) && (this->tl <= v.tl) &&
                (this->ml <= v.ml) && (this->ll <= v.ll));
	}
    
	/*ARITHMETIC OP*/
    
	u512 operator+(u64 v)
	{ return u512_add(this, v);	}
    
	u512 operator+(u512 v)
	{ return u512_addBig(this, &v);	}
    
	void operator+=(u64 v)
	{ *this = u512_add(this, v); }
    
	void operator+=(u512 v)
	{ *this = u512_addBig(this, &v); }
    
	u512 operator-(u64 v)
	{ return u512_sub(this, v); }
    
	u512 operator-(u512 v)
	{ return u512_subBig(this, &v);	}
    
	void operator-=(u64 v)
	{ *this = u512_sub(this, v); }
    
	void operator-=(u512 v)
	{ *this = u512_subBig(this, &v); }
    
	u512 operator*(u64 v)
	{ return u512_mul(this, v); }
    
	u512 operator*(u512 v)
	{ return u512_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u512_mul(this, v); }
    
	void operator*=(u512 v)
	{ *this = u512_mulBig(this, &v); }
    
	u512 operator/(u64 v)
	{ u512 temp = v; u512 r = 0; return v != 0 ? u512_divBig(this, &temp, &r) : 0; }
    
	u512 operator/(u512 v)
	{ u512 r = 0; return v != u64(0) ? u512_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u512 temp = v; u512 r = 0; *this = v != 0 ? u512_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u512 v)
	{ u512 r = 0; *this = v != u64(0) ? u512_divBig(this, &v, &r) : 0; }
    
	u512 operator%(u64 v)
	{ u512 temp = v; u512 r = 0; u512_divBig(this, &temp, &r); return r; }
    
	u512 operator%(u512 v)
	{ u512 r = 0; u512_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u512 temp = v; u512 r = 0; u512_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u512 v)
	{ u512 r = 0; u512_divBig(this, &v, &r); *this = r; }
    
	u512 operator++(int)
	{ u512 temp = *this; u512_inc(this); return temp; }
    
	u512 operator--(int)
	{ u512 temp = *this; u512_dec(this); return temp; }
    
	u512 operator++()
	{ u512_inc(this); return *this; }
    
	u512 operator--()
	{ u512_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u512 operator<<(u32 shift)
	{ return u512_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u512_shl(this, shift); }
    
	u512 operator>>(u32 shift)
	{ return u512_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u512_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u512 operator&(u512 mask)
	{ return u512_and(this, &mask); }
    
	u512 operator&(u64 mask)
	{ u512 temp = mask;	return u512_and(this, &temp); }
    
	void operator&=(u512 mask)
	{ *this = u512_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u512 temp = mask; *this = u512_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u512 operator|(u512 mask)
	{ return u512_or(this, &mask); }
    
	u512 operator|(u64 mask)
	{ u512 temp = mask;	return u512_or(this, &temp); }
    
	void operator|=(u512 mask)
	{ *this = u512_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u512 temp = mask; *this = u512_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u512 operator^(u512 mask)
	{ return u512_xor(this, &mask); }
    
	u512 operator^(u64 mask)
	{ u512 temp = mask;	return u512_xor(this, &temp); }
    
	void operator^=(u512 mask)
	{ *this = u512_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u512 temp = mask; *this = u512_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u512 operator~()
	{ return u512_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u256() { u256 tmp = this->ll; tmp.m = this->ml; tmp.t = this->tl; tmp.h = this->hl; return tmp; }
	operator u128() { u128 tmp = this->ll; tmp.h = this->ml; return tmp; }
	operator u64() { return this->ll; }
	operator u32() { return (u32)this->ll; }
	operator u16() { return (u16)this->ll; }
	operator u8() { return (u8)this->ll; }
    
	operator s64() { return (s64)this->ll; }
	operator s32() { return (s32)this->ll; }
	operator s16() { return (s16)this->ll; }
	operator s8() { return (s8)this->ll; }
};

struct u1024
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
    
	u1024(u64 lowlow, u64 medlow, u64 tallow, u64 highlow,
          u64 lowmed, u64 medmed, u64 tallmed, u64 highmed,
          u64 lowtall, u64 medtall, u64 talltall, u64 hightall,
          u64 lowhigh, u64 medhigh, u64 tallhigh, u64 highhigh)
	{
		ll = lowlow; ml = medlow; tl = tallow; hl = highlow;
		lm = lowmed; mm = medmed; tm = tallmed; hm = highmed;
		lt = lowtall; mt = medtall; tt = talltall; ht = hightall;
		lh = lowhigh; mh = medhigh; th = tallhigh; hh = highhigh;
	}
    
	u1024(u64 low)
	{
		ll = low; ml = 0; tl = 0; hl = 0; 
		lm = 0;	  mm = 0; tm = 0; hm = 0;
		lt = 0;   mt = 0; tt = 0; ht = 0;
		lh = 0;   mh = 0; th = 0; hh = 0;
	}
    
	u1024(u128 low)
	{
		ll = low.l; ml = low.h; tl = 0; hl = 0;
		lm = 0;	mm = 0; tm = 0; hm = 0;
		lt = 0; mt = 0; tt = 0; ht = 0;
		lh = 0; mh = 0; th = 0; hh = 0;
	}
    
	u1024(u256 low)
	{
		ll = low.l; ml = low.m; tl = low.t; hl = low.h;
		lm = 0;	mm = 0; tm = 0; hm = 0;
		lt = 0; mt = 0; tt = 0; ht = 0;
		lh = 0; mh = 0; th = 0; hh = 0;
	}
    
	u1024(u512 low)
	{
		ll = low.ll; ml = low.ml; tl = low.tl; hl = low.hl;
		lm = low.lh; mm = low.mh; tm = low.th; hm = low.hh;
		lt = 0; mt = 0; tt = 0; ht = 0;
		lh = 0; mh = 0; th = 0; hh = 0;
	}
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{
		u512 *tmp = (u512 *)this;
		return ((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator==(u128 v)
	{
		u512 *tmp = (u512 *)this;
		return ((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator==(u256 v)
	{
		u512 *tmp = (u512 *)this;
		return ((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator==(u512 v)
	{
		u512 *tmp = (u512 *)this;
		return ((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator==(u1024 v)
	{
		return ((ll == v.ll) && (ml == v.ml) && (tl == v.tl) && (hl == v.hl) &&
                (lm == v.lm) && (mm == v.mm) && (tm == v.tm) && (hm == v.hm) &&
                (lt == v.lt) && (mt == v.mt) && (tt == v.tt) && (ht == v.ht) &&
                (lh == v.lh) && (mh == v.mh) && (th == v.th) && (hh == v.hh));
	}
    
	bool operator!=(u64 v)
	{
		u512 *tmp = (u512 *)this;
		return !((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator!=(u128 v)
	{
		u512 *tmp = (u512 *)this;
		return !((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator!=(u256 v)
	{
		u512 *tmp = (u512 *)this;
		return !((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator!=(u512 v)
	{
		u512 *tmp = (u512 *)this;
		return !((*tmp == v) && (*(tmp + 1) == (u64)0));
	}
    
	bool operator!=(u1024 v)
	{
		return !((ll == v.ll) && (ml == v.ml) && (tl == v.tl) && (hl == v.hl) &&
                 (lm == v.lh) && (mm == v.mh) && (tm == v.th) && (hm == v.hh) &&
                 (lt == v.lt) && (mt == v.mt) && (tt == v.tt) && (ht == v.ht) &&
                 (lh == v.lh) && (mh == v.mh) && (th == v.th) && (hh == v.hh));
	}
    
	bool operator&&(u1024 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u1024 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{
		u512 *tmp = (u512 *)this;
		return ((*tmp > v) || (*(tmp + 1) > (u64)0));
	}
    
	bool operator>(u1024 v) // @TODO: I'm having doubts on this function
	{
		return ((this->hh >= v.hh) && (this->th >= v.th) &&
                (this->mh >= v.mh) && (this->lh >= v.lh) &&
                (this->ht >= v.ht) && (this->tt >= v.tt) &&
                (this->mt >= v.mt) && (this->lt >= v.lt) &&
                (this->hm >= v.hm) && (this->tm >= v.tm) &&
                (this->mm >= v.mm) && (this->lm >= v.lm) &&
                (this->hl >= v.hl) && (this->tl >= v.tl) &&
                (this->ml >= v.ml) && (this->ll > v.ll));
	}
    
	bool operator>=(u64 v)
	{
		return ((this->hh > 0) || (this->th > 0) ||
                (this->mh > 0) || (this->lh > 0) ||
                (this->ht > 0) || (this->tt > 0) ||
                (this->mt > 0) || (this->lt > 0) ||
                (this->hm > 0) || (this->tm > 0) ||
                (this->mm > 0) || (this->lm > 0) ||
                (this->hl > 0) || (this->tl > 0) ||
                (this->ml > 0) || (this->ll >= v));
	}
    
	bool operator>=(u1024 v)
	{
		return ((this->hh >= v.hh) && (this->th >= v.th) &&
                (this->mh >= v.mh) && (this->lh >= v.lh) &&
                (this->ht >= v.ht) && (this->tt >= v.tt) &&
                (this->mt >= v.mt) && (this->lt >= v.lt) &&
                (this->hm >= v.hm) && (this->tm >= v.tm) &&
                (this->mm >= v.mm) && (this->lm >= v.lm) &&
                (this->hl >= v.hl) && (this->tl >= v.tl) &&
                (this->ml >= v.ml) && (this->ll >= v.ll));
	}
    
	bool operator<(u64 v)
	{
		return ((this->hh == 0) && (this->th == 0) && 
                (this->mh == 0) && (this->lh == 0) &&
                (this->ht == 0) && (this->tt == 0) && 
                (this->mt == 0) && (this->lt == 0) &&
                (this->hm == 0) && (this->tm == 0) &&
                (this->mm == 0) && (this->lm == 0) &&
                (this->hl == 0) && (this->tl == 0) &&
                (this->ml == 0) && (this->ll < v));
	}
    
	bool operator<(u1024 v)
	{
		return ((this->hh <= v.hh) && (this->th <= v.th) &&
                (this->mh <= v.mh) && (this->lh <= v.lh) &&
                (this->ht <= v.ht) && (this->tt <= v.tt) &&
                (this->mt <= v.mt) && (this->lt <= v.lt) &&
                (this->hm <= v.hm) && (this->tm <= v.tm) &&
                (this->mm <= v.mm) && (this->lm <= v.lm) &&
                (this->hl <= v.hl) && (this->tl <= v.tl) &&
                (this->ml <= v.ml) && (this->ll < v.ll));
	}
    
	bool operator<=(u64 v)
	{
		return ((this->hh == 0) && (this->th == 0) &&
                (this->mh == 0) && (this->lh == 0) &&
                (this->ht == 0) && (this->tt == 0) &&
                (this->mt == 0) && (this->lt == 0) &&
                (this->hm == 0) && (this->tm == 0) &&
                (this->mm == 0) && (this->lm == 0) &&
                (this->hl == 0) && (this->tl == 0) &&
                (this->ml == 0) && (this->ll <= v));
	}
    
	bool operator<=(u1024 v)
	{
		return ((this->hh <= v.hh) && (this->th <= v.th) &&
                (this->mh <= v.mh) && (this->lh <= v.lh) &&
                (this->ht <= v.ht) && (this->tt <= v.tt) &&
                (this->mt <= v.mt) && (this->lt <= v.lt) &&
                (this->hm <= v.hm) && (this->tm <= v.tm) &&
                (this->mm <= v.mm) && (this->lm <= v.lm) &&
                (this->hl <= v.hl) && (this->tl <= v.tl) &&
                (this->ml <= v.ml) && (this->ll <= v.ll));
	}
    
	/*ARITHMETIC OP*/
    
	u1024 operator+(u64 v)
	{ return u1024_add(this, v); }
    
	u1024 operator+(u1024 v)
	{ return u1024_addBig(this, &v); }
    
	void operator+=(u64 v)
	{ *this = u1024_add(this, v); }
    
	void operator+=(u1024 v)
	{ *this = u1024_addBig(this, &v); }
    
	u1024 operator-(u64 v)
	{ return u1024_sub(this, v); }
    
	u1024 operator-(u1024 v)
	{ return u1024_subBig(this, &v); }
    
	void operator-=(u64 v)
	{ *this = u1024_sub(this, v); }
    
	void operator-=(u1024 v)
	{ *this = u1024_subBig(this, &v); }
    
	u1024 operator*(u64 v)
	{ return u1024_mul(this, v); }
    
	u1024 operator*(u1024 v)
	{ return u1024_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u1024_mul(this, v); }
    
	void operator*=(u1024 v)
	{ *this = u1024_mulBig(this, &v); }
    
	u1024 operator/(u64 v)
	{ u1024 temp = v; u1024 r = 0; return v != 0 ? u1024_divBig(this, &temp, &r) : 0; }
    
	u1024 operator/(u1024 v)
	{ u1024 r = 0; return v != u64(0) ? u1024_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u1024 temp = v; u1024 r = 0; *this = v != 0 ? u1024_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u1024 v)
	{ u1024 r = 0; *this = v != u64(0) ? u1024_divBig(this, &v, &r) : 0; }
    
	u1024 operator%(u64 v)
	{ u1024 temp = v; u1024 r = 0; u1024_divBig(this, &temp, &r); return r; }
    
	u1024 operator%(u1024 v)
	{ u1024 r = 0; u1024_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u1024 temp = v; u1024 r = 0; u1024_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u1024 v)
	{ u1024 r = 0; u1024_divBig(this, &v, &r); *this = r; }
    
	u1024 operator++(int)
	{ u1024 temp = *this; u1024_inc(this); return temp; }
    
	u1024 operator--(int)
	{ u1024 temp = *this; u1024_dec(this); return temp; }
    
	u1024 operator++()
	{ u1024_inc(this); return *this; }
    
	u1024 operator--()
	{ u1024_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u1024 operator<<(u32 shift)
	{ return u1024_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u1024_shl(this, shift); }
    
	u1024 operator>>(u32 shift)
	{ return u1024_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u1024_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u1024 operator&(u1024 mask)
	{ return u1024_and(this, &mask); }
	u1024 operator&(u64 mask)
	{ u1024 temp = mask;	return u1024_and(this, &temp); }
    
	void operator&=(u1024 mask)
	{ *this = u1024_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u1024 temp = mask; *this = u1024_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u1024 operator|(u1024 mask)
	{ return u1024_or(this, &mask); }
    
	u1024 operator|(u64 mask)
	{ u1024 temp = mask;	return u1024_or(this, &temp); }
    
	void operator|=(u1024 mask)
	{ *this = u1024_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u1024 temp = mask; *this = u1024_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u1024 operator^(u1024 mask)
	{ return u1024_xor(this, &mask); }
    
	u1024 operator^(u64 mask)
	{ u1024 temp = mask;	return u1024_xor(this, &temp); }
    
	void operator^=(u1024 mask)
	{ *this = u1024_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u1024 temp = mask; *this = u1024_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u1024 operator~()
	{ return u1024_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u512() 
	{ 
		u512 tmp = this->ll; tmp.ml = this->ml; tmp.tl = this->tl; tmp.hl = this->hl;
		tmp.lh = this->lm; tmp.mh = this->mm; tmp.th = this->tm; tmp.hh = this->hm;
		return tmp; 
	}
	operator u256() { u256 tmp = this->ll; tmp.m = this->ml; tmp.t = this->tl; tmp.h = this->hl; return tmp; }
	operator u128() { u128 tmp = this->ll; tmp.h = this->ml; return tmp; }
	operator u64() { return this->ll; }
	operator u32() { return (u32)this->ll; }
	operator u16() { return (u16)this->ll; }
	operator u8() { return (u8)this->ll; }
    
	operator s64() { return (s64)this->ll; }
	operator s32() { return (s32)this->ll; }
	operator s16() { return (s16)this->ll; }
	operator s8() { return (s8)this->ll; }
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
		}byte;
        
	};
    
    
	u2048(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h,
          u64 i, u64 j, u64 k, u64 l, u64 m, u64 n, u64 o, u64 p,
          u64 q, u64 r, u64 s, u64 t, u64 u, u64 v, u64 w, u64 x,
          u64 y, u64 z, u64 aa, u64 bb, u64 cc, u64 dd, u64 ee, u64 ff)
	{
		byte.b8 = a; byte.b16 = b; byte.b24 = c; byte.b32 = d; byte.b40 = e; byte.b48 = f;
		byte.b56 = g; byte.b64 = h; byte.b72 = i; byte.b80 = j; byte.b88 = k; byte.b96 = l;
		byte.b104 = m; byte.b112 = n; byte.b120 = o; byte.b128 = p; byte.b136 = q; byte.b144 = r;
		byte.b152 = s; byte.b160 = t; byte.b168 = u; byte.b176 = v; byte.b184 = w; byte.b192 = x;
		byte.b200 = y; byte.b208 = z; byte.b216 = aa; byte.b224 = bb; byte.b232 = cc; byte.b240 = dd;
		byte.b248 = ee; byte.b256 = ff;
	}
    
	u2048(u64 l)
	{
		low = 0; high = 0;
		byte.b8 = l;
	}
    
	u2048(u128 l)
	{
		low = 0; high = 0;
		byte.b8 = l.l; byte.b16 = l.h;
	}
    
	u2048(u256 l)
	{
		low = 0; high = 0;
		byte.b8 = l.l; byte.b16 = l.m;
		byte.b24 = l.t; byte.b32 = l.h;
	}
    
	u2048(u512 l)
	{
		low = 0; high = 0;
		byte.b8 = l.ll; byte.b16 = l.ml; byte.b24 = l.tl; byte.b32 = l.hl;
		byte.b40 = l.lh; byte.b48 = l.mh; byte.b56 = l.th; byte.b64 = l.hh;
	}
    
	u2048(u1024 l)
	{
		low = l; high = 0;
	}
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{ return ((this->low == v) && (this->high == (u64)0)); }
    
	bool operator==(u128 v)
	{ return ((this->low == v) && (this->high == (u64)0)); }
    
	bool operator==(u256 v)
	{ return ((this->low == v) && (this->high == (u64)0)); }
    
	bool operator==(u512 v)
	{ return ((this->low == v) && (this->high == (u64)0)); }
    
	bool operator==(u1024 v)
	{ return ((this->low == v) && (this->high == (u64)0)); }
    
	bool operator==(u2048 v)
	{ return ((this->low == v.low) && (this->high == v.high)); }
    
	bool operator!=(u64 v)
	{ return !(*this == v); }
    
	bool operator!=(u128 v)
	{ return !(*this == v); }
    
	bool operator!=(u256 v)
	{ return !(*this == v); }
    
	bool operator!=(u512 v)
	{ return !(*this == v); }
    
	bool operator!=(u1024 v)
	{ return !(*this == v); }
    
	bool operator!=(u2048 v)
	{ return !(*this == v); }
    
	bool operator&&(u2048 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u2048 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{ return ((low > v) || (high > (u64)0)); }
    
	bool operator>(u2048 v) // @TODO: I'm having doubts on this function
	{ return ((high >= v.high) && (low > v.low)); }
    
	bool operator>=(u64 v)
	{ return ((high > (u64)0) || (low >= v)); }
    
	bool operator>=(u2048 v)
	{ return ((high >= v.high) && (low >= v.low)); }
    
	bool operator<(u64 v)
	{ return ((high == (u64)0) && (low < v)); }
    
	bool operator<(u2048 v)
	{ return ((high <= v.high) && (low < v.low)); }
    
	bool operator<=(u64 v)
	{ return ((high == (u64)0) && (low <= v)); }
    
	bool operator<=(u2048 v)
	{ return ((high <= v.high) && (low <= v.low)); }
    
	/*ARITHMETIC OP*/
    
	u2048 operator+(u64 v)
	{ return u2048_add(this, v); }
    
	u2048 operator+(u2048 v)
	{ return u2048_addBig(this, &v); }
    
	void operator+=(u64 v)
	{ *this = u2048_add(this, v); }
    
	void operator+=(u2048 v)
	{ *this = u2048_addBig(this, &v); }
    
	u2048 operator-(u64 v)
	{ return u2048_sub(this, v); }
    
	u2048 operator-(u2048 v)
	{ return u2048_subBig(this, &v); }
    
	void operator-=(u64 v)
	{ *this = u2048_sub(this, v); }
    
	void operator-=(u2048 v)
	{ *this = u2048_subBig(this, &v); }
    
	u2048 operator*(u64 v)
	{ return u2048_mul(this, v); }
    
	u2048 operator*(u2048 v)
	{ return u2048_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u2048_mul(this, v); }
    
	void operator*=(u2048 v)
	{ *this = u2048_mulBig(this, &v); }
    
	u2048 operator/(u64 v)
	{ u2048 temp = v; u2048 r = 0; return v != 0 ? u2048_divBig(this, &temp, &r) : 0; }
    
	u2048 operator/(u2048 v)
	{ u2048 r = 0; return v != u64(0) ? u2048_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u2048 temp = v; u2048 r = 0; *this = v != 0 ? u2048_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u2048 v)
	{ u2048 r = 0; *this = v != u64(0) ? u2048_divBig(this, &v, &r) : 0; }
    
	u2048 operator%(u64 v)
	{ u2048 temp = v; u2048 r = 0; u2048_divBig(this, &temp, &r); return r;	}
    
	u2048 operator%(u2048 v)
	{ u2048 r = 0; u2048_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u2048 temp = v; u2048 r = 0; u2048_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u2048 v)
	{ u2048 r = 0; u2048_divBig(this, &v, &r); *this = r; }
    
	u2048 operator++(int)
	{ u2048 temp = *this; u2048_inc(this); return temp; }
    
	u2048 operator--(int)
	{ u2048 temp = *this; u2048_dec(this); return temp; }
    
	u2048 operator++()
	{ u2048_inc(this); return *this; }
    
	u2048 operator--()
	{ u2048_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u2048 operator<<(u32 shift)
	{ return u2048_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u2048_shl(this, shift); }
    
	u2048 operator>>(u32 shift)
	{ return u2048_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u2048_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u2048 operator&(u2048 mask)
	{ return u2048_and(this, &mask); }
    
	u2048 operator&(u64 mask)
	{ u2048 temp = mask;	return u2048_and(this, &temp); }
    
	void operator&=(u2048 mask)
	{ *this = u2048_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u2048 temp = mask; *this = u2048_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u2048 operator|(u2048 mask)
	{ return u2048_or(this, &mask); }
    
	u2048 operator|(u64 mask)
	{ u2048 temp = mask;	return u2048_or(this, &temp); }
    
	void operator|=(u2048 mask)
	{ *this = u2048_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u2048 temp = mask; *this = u2048_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u2048 operator^(u2048 mask)
	{ return u2048_xor(this, &mask); }
    
	u2048 operator^(u64 mask)
	{ u2048 temp = mask;	return u2048_xor(this, &temp); }
    
	void operator^=(u2048 mask)
	{ *this = u2048_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u2048 temp = mask; *this = u2048_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u2048 operator~()
	{ return u2048_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u1024()
	{ return low; }
	operator u512()
	{
		u512 tmp = byte.b8; tmp.ml = byte.b16; tmp.tl = byte.b24; tmp.hl = byte.b32;
		tmp.lh = byte.b40; tmp.mh = byte.b48; tmp.th = byte.b56; tmp.hh = byte.b64;
		return tmp;
	}
	operator u256() { u256 tmp = byte.b8; tmp.m = byte.b16; tmp.t = byte.b24; tmp.h = byte.b32; return tmp; }
	operator u128() { u128 tmp = byte.b8; tmp.h = byte.b16; return tmp; }
	operator u64() { return byte.b8; }
	operator u32() { return (u32)byte.b8; }
	operator u16() { return (u16)byte.b8; }
	operator u8() { return (u8)byte.b8; }
    
	operator s64() { return (s64)byte.b8; }
	operator s32() { return (s32)byte.b8; }
	operator s16() { return (s16)byte.b8; }
	operator s8() { return (s8)byte.b8; }
    
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
			u64 b8;	u64 b16;
			u64 b24; u64 b32;
			u64 b40; u64 b48;
			u64 b56; u64 b64;
            
			u64 b72; u64 b80;
			u64 b88; u64 b96;
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
		}byte;
        
	};
    
    
	u4096(u64 a, u64 b, u64 c, u64 d, u64 e, u64 f, u64 g, u64 h,
          u64 i, u64 j, u64 k, u64 l, u64 m, u64 n, u64 o, u64 p,
          u64 q, u64 r, u64 s, u64 t, u64 u, u64 v, u64 w, u64 x,
          u64 y, u64 z, u64 aa, u64 bb, u64 cc, u64 dd, u64 ee, u64 ff,
          u64 gg, u64 hh, u64 ii, u64 jj, u64 kk, u64 ll, u64 mm, u64 nn,
          u64 oo, u64 pp, u64 qq, u64 rr, u64 ss, u64 tt, u64 uu, u64 vv,
          u64 ww, u64 xx, u64 yy, u64 zz, u64 aaa, u64 bbb, u64 ccc, u64 ddd,
          u64 eee, u64 fff, u64 ggg, u64 hhh, u64 iii, u64 jjj, u64 kkk, u64 lll)
	{
		byte.b8 = a; byte.b16 = b; byte.b24 = c; byte.b32 = d; byte.b40 = e; byte.b48 = f;
		byte.b56 = g; byte.b64 = h; byte.b72 = i; byte.b80 = j; byte.b88 = k; byte.b96 = l;
		byte.b104 = m; byte.b112 = n; byte.b120 = o; byte.b128 = p; byte.b136 = q; byte.b144 = r;
		byte.b152 = s; byte.b160 = t; byte.b168 = u; byte.b176 = v; byte.b184 = w; byte.b192 = x;
		byte.b200 = y; byte.b208 = z; byte.b216 = aa; byte.b224 = bb; byte.b232 = cc; byte.b240 = dd;
		byte.b248 = ee; byte.b256 = ff; byte.b264 = gg; byte.b280 = hh;	byte.b288 = ii; byte.b296 = jj; byte.b304 = kk; 
		byte.b312 = ll;	byte.b320 = mm; byte.b328 = nn; byte.b336 = oo; byte.b344 = pp; byte.b352 = qq; byte.b360 = rr;	
		byte.b368 = ss; byte.b376 = tt;	byte.b384 = uu; byte.b392 = vv;	byte.b400 = ww; byte.b408 = xx; byte.b416 = yy; 
		byte.b424 = zz;	byte.b432 = aaa; byte.b440 = bbb; byte.b448 = ccc; byte.b456 = ddd; byte.b464 = eee; byte.b472 = fff; 
		byte.b480 = ggg; byte.b488 = hhh; byte.b496 = iii; byte.b504 = jjj; byte.b512 = kkk; byte.b520 = lll;
	}
    
	u4096(u64 l)
	{
		low256 = 0; high256 = 0;
		byte.b8 = l;
	}
    
	u4096(u128 l)
	{
		low256 = 0; high256 = 0;
		byte.b8 = l.l; byte.b16 = l.h;
	}
    
	u4096(u256 l)
	{
		low256 = 0; high256 = 0;
		byte.b8 = l.l; byte.b16 = l.m;
		byte.b24 = l.t; byte.b32 = l.h;
	}
    
	u4096(u512 l)
	{
		low256 = 0; high256 = 0;
		byte.b8 = l.ll; byte.b16 = l.ml; byte.b24 = l.tl; byte.b32 = l.hl;
		byte.b40 = l.lh; byte.b48 = l.mh; byte.b56 = l.th; byte.b64 = l.hh;
	}
    
	u4096(u1024 l)
	{ low256 = 0; high256 = 0; part.low = l; }
    
	/*LOGICAL OP*/
    
	bool operator==(u64 v)
	{ return ((low256 == v) && (high256 == (u64)0)); }
    
	bool operator==(u128 v)
	{ return ((low256 == v) && (high256 == (u64)0)); }
    
	bool operator==(u256 v)
	{ return ((low256 == v) && (high256 == (u64)0)); }
    
	bool operator==(u512 v)
	{ return ((low256 == v) && (high256 == (u64)0)); }
    
	bool operator==(u1024 v)
	{ return ((low256 == v) && (high256 == (u64)0)); }
    
	bool operator==(u2048 v)
	{ return ((low256 == v.low) && (high256 == v.high)); }
    
	bool operator==(u4096 v)
	{ return ((low256 == v.low256) && (high256 == v.high256)); }
    
	bool operator!=(u64 v)
	{ return !(*this == v); }
    
	bool operator!=(u128 v)
	{ return !(*this == v); }
    
	bool operator!=(u256 v)
	{ return !(*this == v); }
    
	bool operator!=(u512 v)
	{ return !(*this == v); }
    
	bool operator!=(u1024 v)
	{ return !(*this == v); }
    
	bool operator!=(u2048 v)
	{ return !(*this == v); }
    
	bool operator!=(u4096 v)
	{ return !(*this == v); }
    
	bool operator&&(u4096 v)
	{ return (*this != u64(0) && (v != u64(0))); }
    
	bool operator||(u4096 v)
	{ return (*this != u64(0) || (v != u64(0))); }
    
	bool operator!()
	{ return *this == u64(0) ? 1 : 0; }
    
	bool operator>(u64 v)
	{ return ((low256 > v) || (high256 > (u64)0)); }
    
	bool operator>(u4096 v) // @TODO: I'm having doubts on this function
	{ return ((high256 >= v.high256) && (low256 > v.low256)); }
    
	bool operator>=(u64 v)
	{ return ((high256 > (u64)0) || (low256 >= v)); }
    
	bool operator>=(u4096 v)
	{ return ((high256 >= v.high256) && (low256 >= v.low256)); }
    
	bool operator<(u64 v)
	{ return ((high256 == (u64)0) && (low256 < v)); }
    
	bool operator<(u4096 v)
	{ return ((high256 <= v.high256) && (low256 < v.low256)); }
    
	bool operator<=(u64 v)
	{ return ((high256 == (u64)0) && (low256 <= v)); }
    
	bool operator<=(u4096 v)
	{ return ((high256 <= v.high256) && (low256 <= v.low256)); }
    
	/*ARITHMETIC OP*/
    
	u4096 operator+(u64 v)
	{ return u4096_add(this, v); }
    
	u4096 operator+(u4096 v)
	{ return u4096_addBig(this, &v); }
    
	void operator+=(u64 v)
	{ *this = u4096_add(this, v); }
    
	void operator+=(u4096 v)
	{ *this = u4096_addBig(this, &v); }
    
	u4096 operator-(u64 v)
	{ return u4096_sub(this, v); }
    
	u4096 operator-(u4096 v)
	{ return u4096_subBig(this, &v); }
    
	void operator-=(u64 v)
	{ *this = u4096_sub(this, v); }
    
	void operator-=(u4096 v)
	{ *this = u4096_subBig(this, &v); }
    
	u4096 operator*(u64 v)
	{ return u4096_mul(this, v); }
    
	u4096 operator*(u4096 v)
	{ return u4096_mulBig(this, &v); }
    
	void operator*=(u64 v)
	{ *this = u4096_mul(this, v); }
    
	void operator*=(u4096 v)
	{ *this = u4096_mulBig(this, &v); }
    
	u4096 operator/(u64 v)
	{ u4096 temp = v; u4096 r = 0; return v != 0 ? u4096_divBig(this, &temp, &r) : 0; }
    
	u4096 operator/(u4096 v)
	{ u4096 r = 0; return v != u64(0) ? u4096_divBig(this, &v, &r) : 0; }
    
	void operator/=(u64 v)
	{ u4096 temp = v; u4096 r = 0; *this = v != 0 ? u4096_divBig(this, &temp, &r) : 0; }
    
	void operator/=(u4096 v)
	{ u4096 r = 0; *this = v != u64(0) ? u4096_divBig(this, &v, &r) : 0; }
    
	u4096 operator%(u64 v)
	{ u4096 temp = v; u4096 r = 0; u4096_divBig(this, &temp, &r); return r; }
    
	u4096 operator%(u4096 v)
	{ u4096 r = 0; u4096_divBig(this, &v, &r); return r; }
    
	void operator%=(u64 v)
	{ u4096 temp = v; u4096 r = 0; u4096_divBig(this, &temp, &r); *this = r; }
    
	void operator%=(u4096 v)
	{ u4096 r = 0; u4096_divBig(this, &v, &r); *this = r; }
    
	u4096 operator++(int)
	{ u4096 temp = *this; u4096_inc(this); return temp; }
    
	u4096 operator--(int)
	{ u4096 temp = *this; u4096_dec(this); return temp; }
    
	u4096 operator++()
	{ u4096_inc(this); return *this; }
    
	u4096 operator--()
	{ u4096_dec(this); return *this; }
    
	/*BITWISE SHIFT OP*/
	//@TODO: WRONG! CAN ONLY SHIFT MY A MAX OF 63 BITS RIGHT NOW
	u4096 operator<<(u32 shift)
	{ return u4096_shl(this, shift); }
    
	void operator<<=(u32 shift)
	{ *this = u4096_shl(this, shift); }
    
	u4096 operator>>(u32 shift)
	{ return u4096_shr(this, shift); }
    
	void operator>>=(u32 shift)
	{ *this = u4096_shr(this, shift); }
    
	/*BITWISE AND OP*/
    
	u4096 operator&(u4096 mask)
	{ return u4096_and(this, &mask); }
    
	u4096 operator&(u64 mask)
	{ u4096 temp = mask;	return u4096_and(this, &temp); }
    
	void operator&=(u4096 mask)
	{ *this = u4096_and(this, &mask); }
    
	void operator&=(u64 mask)
	{ u4096 temp = mask; *this = u4096_and(this, &temp); }
    
	/*BITWISE OR OP*/
    
	u4096 operator|(u4096 mask)
	{ return u4096_or(this, &mask); }
    
	u4096 operator|(u64 mask)
	{ u4096 temp = mask;	return u4096_or(this, &temp); }
    
	void operator|=(u4096 mask)
	{ *this = u4096_or(this, &mask); }
    
	void operator|=(u64 mask)
	{ u4096 temp = mask; *this = u4096_or(this, &temp); }
    
	/*BITWISE XOR OP*/
    
	u4096 operator^(u4096 mask)
	{ return u4096_xor(this, &mask); }
    
	u4096 operator^(u64 mask)
	{ u4096 temp = mask;	return u4096_xor(this, &temp); }
    
	void operator^=(u4096 mask)
	{ *this = u4096_xor(this, &mask); }
    
	void operator^=(u64 mask)
	{ u4096 temp = mask; *this = u4096_xor(this, &temp); }
    
	/*BITWISE NOT OP*/
    
	u4096 operator~()
	{ return u4096_not(this); }
    
	/*STATIC CASTING OP*/
    
	operator u2048()
	{ return low256; }
	operator u1024()
	{ return part.low; }
	operator u512()
	{
		u512 tmp = byte.b8; tmp.ml = byte.b16; tmp.tl = byte.b24; tmp.hl = byte.b32;
		tmp.lh = byte.b40; tmp.mh = byte.b48; tmp.th = byte.b56; tmp.hh = byte.b64;
		return tmp;
	}
	operator u256() { u256 tmp = byte.b8; tmp.m = byte.b16; tmp.t = byte.b24; tmp.h = byte.b32; return tmp; }
	operator u128() { u128 tmp = byte.b8; tmp.h = byte.b16; return tmp; }
	operator u64() { return byte.b8; }
	operator u32() { return (u32)byte.b8; }
	operator u16() { return (u16)byte.b8; }
	operator u8() { return (u8)byte.b8; }
    
	operator s64() { return (s64)byte.b8; }
	operator s32() { return (s32)byte.b8; }
	operator s16() { return (s16)byte.b8; }
	operator s8() { return (s8)byte.b8; }
    
};


#endif

#ifdef LS_BIGINT_IMPLEMENTATION

//@Cleanup @Speedup @Todo : Make this completely ASM
u128 u128_pow(u128 v, u32 exp)
{
	u128 Result = 1;
	while (exp)
	{
		if (exp & 1)
		{ Result *= v; }
        
		exp >>= 1;
		v *= v;
	}
    
	return Result;
}

//@Cleanup @Speedup @Todo : Make this completely ASM
u256 u256_pow(u256 v, u32 exp)
{
	u256 Result = 1;
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

//@Cleanup @Speedup @Todo : Make this completely ASM
u512 u512_pow(u512 v, u32 exp)
{
	u512 Result = 1;
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

//@Cleanup @Speedup @Todo : Make this completely ASM
u1024 u1024_pow(u1024 v, u32 exp)
{
	u1024 Result = 1;
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
#if 0
string u1024_hex(u1024 v)
{
	char hexMap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	string Result = 256;
    
	u8 lowMask = 0x0F;
	u8 highMask = 0xF0;
    
	u8 value = 0;
	u8 *At = (u8 *)&v;
	for (s32 i = 127; i >= 0; i--)
	{
		value = (*(At + i) & highMask) >> 4;
		Result += hexMap[value];
        
		value = *(At + i) & lowMask;
		Result += hexMap[value];
	}
    
	return Result;
}
#endif
//@Cleanup @Speedup @Todo : Make this completely ASM
u2048 u2048_pow(u2048 v, u32 exp)
{
	u2048 Result = 1;
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

//@Cleanup @Speedup @Todo : Make this completely ASM
u4096 u4096_pow(u4096 v, u32 exp)
{
	u4096 Result = 1;
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

#endif