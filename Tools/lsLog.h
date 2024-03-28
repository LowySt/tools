/* date = February 7th 2023 5:48 pm */

#ifndef LS_LOG_H
#define LS_LOG_H

#include "lsCRT.h"
#include "lsArray.h"
#include "lsString.h"

//TODO: How to deal with modifiers?
typedef s32(*LogFormatTypeProc)(char *, va_list *);
typedef s32(*LogFormatTypeModProc)(char *, char *mods, s32 numMods, s32 lenMod, va_list *);

struct LogRegisteredType
{
    string               typeName;
    LogFormatTypeProc    format;
    LogFormatTypeModProc modFormat;
};

void ls_logDefaultTypesRegister();
void ls_vlogRegister(const char *typeName, LogFormatTypeProc proc);
void ls_vlogRegister(const char *typeName, LogFormatTypeModProc proc);
s32  ls_log(const char *format, ...);
s32  ls_slog(char *dst, s32 dstMaxLen, const char *format, ...);

#endif //LS_LOG_H
#ifdef LS_LOG_IMPLEMENTATION

static const s32 LS_LOG_MAX_REGISTERED_TYPES = 64;
static LogRegisteredType __internal_logRegisteredTypes[LS_LOG_MAX_REGISTERED_TYPES] = {};
static s32 __ls_log__registered_types_count = 0;
static b32 __ls_log__initialize = FALSE;

s32 ls_vlogFormatPTR(char *dst, va_list *argList)
{
    u64 intValue = (u64)va_arg(*argList, void *);
    
    char intBuff[32] = {};
    s32 sLen = ls_utoax_t(intValue, intBuff, 32);
    ls_memcpy(intBuff, dst, sLen);
    return sLen;
}

s32 ls_vlogFormatB32(char *dst, va_list *argList)
{
    s32 intValue = va_arg(*argList, s32);
    
    if(intValue == FALSE) { ls_memcpy((void *)"false", dst, 5); return 5; }
    else                  { ls_memcpy((void *)"true", dst, 4);  return 4; }
    
    return 0;
}

s32 ls_vlogFormatS32(char *dst, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    s32 intValue = va_arg(*argList, s32);
    
    const s32 buffSize = 128;
    char intBuff[buffSize] = {};
    s32 sLen = 0;
    
    if(numMods == 0)
    {
        sLen = ls_itoa_t(intValue, intBuff, buffSize);
    }
    else
    {
        switch(mods[0])
        {
            case 'x': { sLen = ls_utoax_t((u32)intValue, intBuff, buffSize, 4, TRUE); } break;
            
            case 'b': { sLen = ls_utoab_t((u32)intValue, intBuff, buffSize, 4, TRUE); } break;
            
            default:
            {
                AssertMsgF(FALSE, "Mod %c not implemented\n", mods[0]);
            }
            
        }
    }
    
    if(lenMod > 0)
    {
        s32 lenDiff = lenMod - sLen;
        while(lenDiff > 0)
        {
            if(sLen+1 >= buffSize) { return sLen; }
            
            intBuff[sLen] = ' ';
            sLen += 1;
            lenDiff -= 1;
        }
    }
    
    ls_memcpy(intBuff, dst, sLen);
    
    return sLen;
}

s32 ls_vlogFormatS64(char *dst, va_list *argList)
{
    s64 intValue = va_arg(*argList, s64);
    
    char intBuff[32] = {};
    s32 sLen = ls_itoa_t(intValue, intBuff, 32);
    ls_memcpy(intBuff, dst, sLen);
    return sLen;
}

s32 ls_vlogFormatU32(char *dst, va_list *argList)
{
    u32 intValue = va_arg(*argList, u32);
    
    char intBuff[32] = {};
    s32 sLen = ls_utoa_t(intValue, intBuff, 32);
    ls_memcpy(intBuff, dst, sLen);
    return sLen;
}

s32 ls_vlogFormatU64(char *dst, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    //TODO:
    (void)(mods);
    (void)(numMods);
    
    u64 intValue = va_arg(*argList, u64);
    
    char intBuff[32] = {};
    s32 sLen = ls_utoa_t(intValue, intBuff, 32);
    ls_memcpy(intBuff, dst, sLen);
    
    if(lenMod > 0)
    {
        s32 lenDiff = lenMod - sLen;
        AssertMsg(lenDiff < 256, "Suspiciously large number. We don't check buffSize in the format, which is bad.\n");
        
        while(lenDiff > 0)
        {
            dst[sLen] = ' ';
            sLen += 1;
            lenDiff -= 1;
        }
    }
    
    
    return sLen;
}

s32 ls_vlogFormatF64(char *dst, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    f64 floatValue = va_arg(*argList, f64);
    
    char floatBuff[32] = {};
    u32 sLen = ls_ftoa_t(floatValue, floatBuff, 32);
    
    s32 copyLen = sLen;
    if(numMods > 0 && mods[0] == '.')
    {
        s32 i = 0; char *At = floatBuff;
        while(*At != '.' && i < sLen) { At += 1; i += 1; }
        
        if(i < sLen) { copyLen = i + mods[1] + 1; }
    }
    
    ls_memcpy(floatBuff, dst, copyLen);
    
    if(lenMod > 0)
    {
        s32 lenDiff = lenMod - copyLen;
        AssertMsg(lenDiff < 256, "Suspiciously large number. We don't check buffSize in the format, which is bad.\n");
        
        while(lenDiff > 0)
        {
            dst[copyLen] = ' ';
            copyLen += 1;
            lenDiff -= 1;
        }
    }
    
    return copyLen;
}

s32 ls_vlogFormatChar(char *dst, va_list *argList)
{
    //NOTE: Auto promotion in c...
    s32 c = va_arg(*argList, s32);
    
    ls_memcpy(&c, dst, 1);
    return 1;
}

s32 ls_vlogFormatString(char *dst, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    //NOTETODO: For now mods and numMods params are ignored!
    (void)(mods);
    (void)(numMods);
    
    string str = va_arg(*argList, string);
    ls_memcpy(str.data, dst, str.len);
    
    s32 sLen = str.len;
    if(lenMod > 0)
    {
        s32 lenDiff = lenMod - sLen;
        AssertMsg(lenDiff < 256, "Suspiciously large number. We don't check buffSize in the format, which is bad.\n");
        
        while(lenDiff > 0)
        {
            dst[sLen] = ' ';
            sLen += 1;
            lenDiff -= 1;
        }
    }
    
    return sLen;
}

s32 ls_vlogFormatCString(char *dst, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    //NOTETODO: For now mods and numMods params are ignored!
    (void)(mods);
    (void)(numMods);
    
    char *cStr = va_arg(*argList, char*);
    s32 len = ls_len(cStr);
    ls_memcpy(cStr, dst, len);
    
    if(lenMod > 0)
    {
        s32 lenDiff = lenMod - len;
        AssertMsg(lenDiff < 256, "Suspiciously large number. We don't check buffSize in the format, which is bad.\n");
        
        while(lenDiff > 0)
        {
            dst[len] = ' ';
            len += 1;
            lenDiff -= 1;
        }
    }
    
    return len;
}

s32 ls_vlogFormatUTF8(char *dst, va_list *argList)
{
    utf8 str = va_arg(*argList, utf8);
    
    ls_memcpy(str.data, dst, str.byteLen);
    return str.byteLen;
}

s32 ls_vlogFormatUTF32(char *dst, va_list *argList)
{
    utf32 str = va_arg(*argList, utf32);
    
    for(s32 i = 0; i < str.len; i++)
    { dst[i] = ls_strCharFromUTF32(str.data[i]); }
    
    return str.len;
    
    //s32 bytesWritten = str.len*sizeof(u32);
    //ls_memcpy(str.data, dst, bytesWritten);
    //return bytesWritten;
}

s32 ls_vlogFormatM128I(char *dst, va_list *argList)
{
    __m128i val = va_arg(*argList, __m128i);
    
    u8 c0 = (u8)_mm_extract_epi8(val, 0);
    u8 c1 = (u8)_mm_extract_epi8(val, 1);
    u8 c2 = (u8)_mm_extract_epi8(val, 2);
    u8 c3 = (u8)_mm_extract_epi8(val, 3);
    u8 c4 = (u8)_mm_extract_epi8(val, 4);
    u8 c5 = (u8)_mm_extract_epi8(val, 5);
    u8 c6 = (u8)_mm_extract_epi8(val, 6);
    u8 c7 = (u8)_mm_extract_epi8(val, 7);
    
    u8 c8  = (u8)_mm_extract_epi8(val, 8);
    u8 c9  = (u8)_mm_extract_epi8(val, 9);
    u8 c10 = (u8)_mm_extract_epi8(val, 10);
    u8 c11 = (u8)_mm_extract_epi8(val, 11);
    u8 c12 = (u8)_mm_extract_epi8(val, 12);
    u8 c13 = (u8)_mm_extract_epi8(val, 13);
    u8 c14 = (u8)_mm_extract_epi8(val, 14);
    u8 c15 = (u8)_mm_extract_epi8(val, 15);
    
    const s32 buffSize = 128;
    char buff[buffSize] = {};
    
    s32 bytesWritten = ls_slog(buff, buffSize, "[ [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}],"
                               " [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}], [{u8}] ]", 
                               c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15);
    
    ls_memcpy(buff, dst, bytesWritten);
    return bytesWritten;
}

s32 ls_vlogFormatArena(char *dst, va_list *argList)
{
    Arena tmp = va_arg(*argList, Arena);
    InternalArena ar = Memory.arenas[tmp.id];
    
    const s32 buffSize = 256;
    char buff[buffSize] = {};
    
    s32 bytesWritten = ls_slog(buff, buffSize, "{{\n   Capacity: {u64}\n   Used: {u64}"
                               "\n   ID: {u32}\n}", ar.capacity, ar.used, ar.id);
    
    ls_memcpy(buff, dst, bytesWritten);
    return bytesWritten;
}


void ls_vlogRegister(const char *typeName, LogFormatTypeProc proc)
{
    LogRegisteredType t = { ls_strConstant(typeName), proc, 0 };
    __internal_logRegisteredTypes[__ls_log__registered_types_count] = t;
    __ls_log__registered_types_count += 1;
}

void ls_vlogRegister(const char *typeName, LogFormatTypeModProc proc)
{
    LogRegisteredType t = { ls_strConstant(typeName), 0, proc };
    __internal_logRegisteredTypes[__ls_log__registered_types_count] = t;
    __ls_log__registered_types_count += 1;
}

s32 ls_vlogFormat(char *dst, view marker, char *mods, s32 numMods, s32 lenMod, va_list *argList)
{
    for(u32 i = 0; i < __ls_log__registered_types_count; i++)
    {
        if(marker.s == __internal_logRegisteredTypes[i].typeName)
        {
            if(__internal_logRegisteredTypes[i].format)
            { return __internal_logRegisteredTypes[i].format(dst, argList); }
            else if(__internal_logRegisteredTypes[i].modFormat)
            { return __internal_logRegisteredTypes[i].modFormat(dst, mods, numMods, lenMod, argList); }
        }
    }
    
    AssertMsgF(FALSE, "Unhandled Log Format %s\n", marker.s);
    
    return 0;
}

void ls_logDefaultTypesRegister()
{
    if (!__ls_log__initialize)
    {
        ls_vlogRegister("ptr",    ls_vlogFormatPTR);
        ls_vlogRegister("b32",    ls_vlogFormatB32);
        ls_vlogRegister("s8",     ls_vlogFormatS32);
        ls_vlogRegister("s16",    ls_vlogFormatS32);
        ls_vlogRegister("s32",    ls_vlogFormatS32);
        ls_vlogRegister("s64",    ls_vlogFormatS64);
        ls_vlogRegister("u8",     ls_vlogFormatU32);
        ls_vlogRegister("u16",    ls_vlogFormatU32);
        ls_vlogRegister("u32",    ls_vlogFormatU32);
        ls_vlogRegister("u64",    ls_vlogFormatU64);
        ls_vlogRegister("f32",    ls_vlogFormatF64);
        ls_vlogRegister("f64",    ls_vlogFormatF64);
        ls_vlogRegister("char",   ls_vlogFormatChar);
        ls_vlogRegister("string", ls_vlogFormatString);
        ls_vlogRegister("char*",  ls_vlogFormatCString);
        ls_vlogRegister("utf8",   ls_vlogFormatUTF8);
        ls_vlogRegister("utf32",  ls_vlogFormatUTF32);
        
        ls_vlogRegister("__m128i", ls_vlogFormatM128I);
        ls_vlogRegister("Arena", ls_vlogFormatArena);
        
        __ls_log__initialize = TRUE;
    }
}

s32 ls_vlog(const char *format, char *dest, s32 buffSize, va_list *argList, b32 newline = TRUE)
{
    if(!__ls_log__initialize) { ls_logDefaultTypesRegister(); }
    
    char *buff = dest;
    const char *p = format;
    
    s32 numMods = 0;
    char mods[8] = {};
    
    s32 lenMod = 0;
    s32 lenModCount = 0;
    
    s32 i = 0;
    for(p = format; *p != 0; p++)
    {
        AssertMsg(i < buffSize, "Log Destination Buffer too small\n");
        
        numMods = 0;
        lenMod = 0;
        lenModCount = 0;
        
        if(*p == '{')
        {
            if(*(p+1) == '{')
            { 
                buff[i] = *p;
                p += 1;
                i += 1;
                continue;
            }
            
            //NOTE: First we check a len mod for right padding
            while(ls_isANumber(*(p+1+lenModCount))) { lenModCount += 1; }
            if(lenModCount > 0) { lenMod = ls_atoi((char *)(p+1), lenModCount); p += lenModCount; }
            
            //NOTE: Then we check modifiers
            if(*(p+1) == 'x')
            {
                mods[numMods] = 'x';
                p += 1;
                numMods += 1;
            }
            
            if(*(p+1) == 'b')
            {
                mods[numMods] = 'b';
                p += 1;
                numMods += 1;
            }
            
            if(*(p+1) == '.')
            {
                mods[numMods]   = '.';
                p += 1;
                numMods += 1;
                
                s32 precLenCount = 0;
                s32 precLen      = 0;
                while(ls_isANumber(*(p+1+precLenCount))) { precLenCount += 1; }
                if(precLenCount > 0) { precLen = ls_atoi((char *)(p+1), precLenCount); p += precLenCount; }
                
                mods[numMods] = precLen;
                numMods += 1;
            }
            
            view marker = ls_viewNextDelimiter(ls_viewCreate(ls_strConstant(p+1)), '}');
            s32 length = ls_vlogFormat(buff + i, marker, mods, numMods, lenMod, argList);
            i += length;
            p += marker.s.len + 1; //We skip the open braces
            continue;
        }
        else
        {
            buff[i] = *p;
            i += 1;
            continue;
        }
    }
    
    if(newline == TRUE)
    {
        buff[i]   = '\n';
        i        += 1;
    }
    //buff[i+1] = 0;
    //i += 2;
    
    return i;
}

s32 ls_slog(char *dst, s32 dstMaxLen, const char *format, ...)
{
    if(dstMaxLen <= 0) { return 0; }
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, dst, dstMaxLen, &argList);
    
    va_end(argList);
    
    return ret;
}

s32 ls_slog(string *out, const char *format, ...)
{
    if(out->size <= 0) { return 0; }
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, out->data, out->size, &argList);
    out->len = ret;
    
    va_end(argList);
    
    return ret;
}

s32 ls_log(const char *format, ...)
{
    const s32 buffSize = KB(4);
    char buff[buffSize] = {};
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, buff, buffSize, &argList);
    
    va_end(argList);
    
    ls_writeConsole(LS_STDOUT, buff, ret);
    
    return ret;
}

//TODO: Shitty names
s32 ls_slogs(char *dst, s32 dstMaxLen, const char *format, ...)
{
    if(dstMaxLen <= 0) { return 0; }
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, dst, dstMaxLen, &argList, FALSE);
    
    va_end(argList);
    
    return ret;
}

s32 ls_slogs(string *out, const char *format, ...)
{
    if(out->size <= 0) { return 0; }
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, out->data, out->size, &argList, FALSE);
    out->len = ret;
    
    va_end(argList);
    
    return ret;
}

s32 ls_logs(const char *format, ...)
{
    const s32 buffSize = KB(4);
    char buff[buffSize] = {};
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, buff, buffSize, &argList, FALSE);
    
    va_end(argList);
    
    ls_writeConsole(LS_STDOUT, buff, ret);
    
    return ret;
}


#endif //LS_LOG_IMPLEMENTATION
