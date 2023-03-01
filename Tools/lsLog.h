/* date = February 7th 2023 5:48 pm */

#ifndef LS_LOG_H
#define LS_LOG_H

#include "lsCRT.h"
#include "lsArray.h"
#include "lsString.h"

typedef s32(*LogFormatTypeProc)(char *, va_list *);

struct LogRegisteredType
{
    string typeName;
    LogFormatTypeProc format;
};

s32 ls_vlogRegisterType(const char *typeName, LogFormatTypeProc proc);
s32 ls_log(const char *format, ...);
s32 ls_slog(char *dst, s32 dstMaxLen, const char *format, ...);

#endif //LS_LOG_H
#ifdef LS_LOG_IMPLEMENTATION

static Array<LogRegisteredType> __internal_logRegisteredTypes = {};
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
    s64 intValue = va_arg(*argList, s64);
    
    if(intValue == FALSE) { ls_memcpy("false", dst, 5); return 5; }
    else                  { ls_memcpy("true", dst, 4);  return 4; }
    
    return 0;
}

s32 ls_vlogFormatS32(char *dst, va_list *argList)
{
    s32 intValue = va_arg(*argList, s32);
    
    char intBuff[32] = {};
    s32 sLen = ls_itoa_t(intValue, intBuff, 32);
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

s32 ls_vlogFormatU64(char *dst, va_list *argList)
{
    u64 intValue = va_arg(*argList, u64);
    
    char intBuff[32] = {};
    s32 sLen = ls_utoa_t(intValue, intBuff, 32);
    ls_memcpy(intBuff, dst, sLen);
    return sLen;
}

s32 ls_vlogFormatF64(char *dst, va_list *argList)
{
    f64 floatValue = va_arg(*argList, f64);
    
    char floatBuff[32] = {};
    u32 sLen = ls_ftoa_t(floatValue, floatBuff, 32);
    ls_memcpy(floatBuff, dst, sLen);
    return sLen;
}

s32 ls_vlogFormatString(char *dst, va_list *argList)
{
    string str = va_arg(*argList, string);
    
    ls_memcpy(str.data, dst, str.len);
    return str.len;
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
    
    s32 bytesWritten = str.len*sizeof(u32);
    ls_memcpy(str.data, dst, bytesWritten);
    return bytesWritten;
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

void ls_vlogRegister(const char *typeName, LogFormatTypeProc proc)
{
    LogRegisteredType t = { ls_strInit(typeName), proc };
    ls_arrayAppendIndex(&__internal_logRegisteredTypes, t);
}

s32 ls_vlogFormat(char *dst, view marker, va_list *argList)
{
    for(u32 i = 0; i < __internal_logRegisteredTypes.count; i++)
    {
        if(marker.s == __internal_logRegisteredTypes[i].typeName)
        {
            return __internal_logRegisteredTypes[i].format(dst, argList);
        }
    }
    
    return 0;
}

s32 ls_vlog(const char *format, char *dest, s32 buffSize, va_list *argList)
{
    char *buff = dest;
    const char *p = format;
    
    s32 i = 0;
    for(p = format; *p != 0; p++)
    {
        AssertMsg(i < buffSize, "Log Destination Buffer too small\n");
        
        if(*p == '{')
        {
            view marker = ls_viewNextDelimiter(ls_viewCreate(ls_strConstant(p+1)), '}');
            s32 length = ls_vlogFormat(buff + i, marker, argList);
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
    
    buff[i]   = '\n';
    buff[i+1] = 0;
    i += 2;
    
    return i;
}

s32 ls_slog(char *dst, s32 dstMaxLen, const char *format, ...)
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
        ls_vlogRegister("string", ls_vlogFormatString);
        ls_vlogRegister("utf8",   ls_vlogFormatUTF8);
        ls_vlogRegister("utf32",  ls_vlogFormatUTF32);
        
        ls_vlogRegister("__m128i", ls_vlogFormatM128I);
        
        __ls_log__initialize = TRUE;
    }
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, dst, dstMaxLen, &argList);
    
    va_end(argList);
    
    return ret;
}

s32 ls_log(const char *format, ...)
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
        ls_vlogRegister("string", ls_vlogFormatString);
        ls_vlogRegister("utf8",   ls_vlogFormatUTF8);
        ls_vlogRegister("utf32",  ls_vlogFormatUTF32);
        
        ls_vlogRegister("__m128i", ls_vlogFormatM128I);
        
        __ls_log__initialize = TRUE;
    }
    
    const s32 buffSize = KB(4);
    char buff[buffSize] = {};
    
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vlog(format, buff, buffSize, &argList);
    
    va_end(argList);
    
    ls_writeConsole(LS_STDOUT, buff, ret);
    
    return ret;
}


#endif LS_LOG_IMPLEMENTATION
