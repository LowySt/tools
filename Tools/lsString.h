#ifndef LS_STRING_H
#define LS_STRING_H

#include "win32.h"
#include "lsCRT.h"

//NOTE: When creating a constant string (basically a view into a pointer on the stack)
//          Size is set to -7878, a sentinel value to recognize constant strings
struct string
{
    char *data;
    s32  len;
    s32  size;
};

struct utf8
{
    u8  *data;
    s32  len;
    s32  byteLen;
    s32  size;
};

struct utf32
{
    u32 *data;
    s32  len;
    s32  size;
};

//TODO I hate views
//     This single struct tries to act both as a view and as an iterator over the string
//     It shouldn't.
//     Either we just use constant strings (which we made possible through size = -7878)
//     Or we make the view really just a view.
//     And the iterator should happen separately!
struct view
{
    string s;
    
    char *next;
    u32  len;
};

struct uview
{
    utf32 s;
    
    u32 *next;
    u32 len;
};

//-----------------------------//
//        ASCII STRINGS        //
//-----------------------------//

//Create/Destroy
string  ls_strAlloc(s32 size);
string *ls_strAllocPtr(s32 size);
string *ls_strAllocArr(u32 numStrings, s32 initialSize);
void    ls_strFree(string *s);
void    ls_strFreePtr(string *s);
void    ls_strFreeArr(string *s, s32 arrSize);

//Manage
string  ls_strInit(char *s);
string  ls_strInit(const char *s);

//NOTE: In this case the char * string lives on the STACK!
string  ls_strConstant(char *p);
string  ls_strConstant(const char *p);
string  ls_strConstant(char *p, u32 len);
string  ls_strConstChar(char *c);

void    ls_strClear(string *s);
string  ls_strCopy(string s);
void	ls_strNCopy(string s, string *dst, size_t size);
string  ls_strCopySubstr(string s, u32 beginIdx, u32 _endIdx = (u32)-1);


//C Bullshit
void    ls_strNullTerminate(string *s);
char   *ls_strToCStr(string s);
void    ls_strToCStr_t(string s, char *buff, s32 buffSize);


//OperateOn
void    ls_strReverse(string *s);
void    ls_strRmSubstr(string *s, u32 beginIdx, u32 endIdx); //TODO: Make indices signed as well.
void    ls_strRmIdx(string *s, u32 idx);
void    ls_strRmAllNonTextChar(string *s);
void    ls_strTrimRight(string *s, u32 numChars);

void    ls_strInsertSubstr(string *s, string toInsert, u32 insertIdx);
void    ls_strInsertChar(string *s, char c, u32 idx);
void    ls_strInsertCStr(string *s, char *toInsert, u32 insertIdx);


//NOTE: Maybe reword these?
string  *ls_strBreakByDelimeter(string s, u32 *numOfStrings, char c);
string  *ls_strBreakByLine(string s, s32 *numOfLines);
string  *ls_strBreakByWhitespace(string s, u32 *numOfStrings);
string  *ls_strBreakBySpace(string s, u32 *numOfStrings);
string  *ls_strBreakBySpaceUntilDelimiter(string s, char delimiter, u32 *numOfStrings);
s32     ls_strLeftFind(string s, char c);
s32     ls_strRightFind(string s, char c);


//Merge
string  ls_strConcat(string s1, string s2);
void    ls_strConcatOn(string s1, string s2, string *out);
string  ls_strCatChar(string s1, char c);
string  ls_strCatCStr(string s1, char *c);
void    ls_strPrepend(string *s1, string s2);
void    ls_strPrependChar(string *s, char c);
void    ls_strPrependCStr(string *s, char *c);
void    ls_strAppend(string *s1, string s2);
void    ls_strAppend(string *s1, view v);
void    ls_strAppend(string *s1, char c);
void    ls_strAppend(string *s1, char *c);
void    ls_strAppend(string *s1, const char *c);
void    ls_strAppend(string *s1, char *c, u32 len);

//To/From Data
u8      ls_strCharFromUTF32(u32 codepoint);
b32     ls_strIsANumber(string s);
string  ls_itos(s64 x);
void    ls_itosOn(s64 x, string *out);
string  ls_itoh(u64 x);
s64     ls_stoi(string s);
f32	 ls_stof(string s);
string  ls_ftos(f32 x);

//CRTish?
string  ls_strReadFile(char *path, s32 readLenInBytes); //NOTE: Entire File -> readLenInBytes == 0

//Operator
b32     operator==(string s1, string s2);
b32     operator!=(string s1, string s2);

b32     ls_strIsEqualNCStr(string s1, char *s2, u32 len);

//-----------------------------//
//    UTF8  UNICODE STRINGS    //
//-----------------------------//

//Create/Destroy
utf8  ls_utf8Alloc(s32 size);
utf8 *ls_utf8AllocArr(u32 numStrings, s32 initialSize);
void  ls_utf8Free(utf8 *s);
void  ls_utf8FreeArr(utf8 *s, s32 arrSize);

b32   ls_utf8AreEqual(utf8 a, utf8 b);
void  ls_utf8Set(utf8 *toSet, utf8 source);

b32   ls_utf8IsValid(u8 *src, s32 byteLen);
s32   ls_utf8Len(u8 *src, s32 byteLen);

utf8  ls_utf8FromAscii(char *s);
utf8  ls_utf8FromAscii(char *s, s32 len);
void  ls_utf8FromAscii_t(utf8 *dst, char *src);
void  ls_utf8FromAscii_t(utf8 *dst, char *src, s32 len);
utf8  ls_utf8FromUTF32(utf32 s);
utf8  ls_utf8FromUTF32(const char32_t *s);
void  ls_utf8FromUTF32_t(utf8 *dst, const char32_t *s);
void  ls_utf8FromUTF32_t(utf8 *dst, utf32 s);
utf8  ls_utf8FromInt(s64 x);
void  ls_utf8FromInt_t(utf8 *s, s64 x);
utf8  ls_utf8FromF64(f64 x);
void  ls_utf8FromF64_t(utf8 *s, f64 x);
utf8  ls_utf8Constant(const char *p);
utf8  ls_utf8Constant(const u8 *p);
utf8  ls_utf8Constant(const u8 *p, s32 byteLen);

//Manage
void  ls_utf8Clear(utf8 *s);
utf8  ls_utf8Copy(utf8 s);

//OperateOn
void  ls_utf8Reverse(utf8 *s);
void  ls_utf8RmSubstr(utf8 *s, u32 beginIdx, u32 endIdx);  //TODO: Make indices signed as well.
void  ls_utf8RmIdx(utf8 *s, u32 idx);
void  ls_utf8RmAllNonTextChar(utf8 *s);
void  ls_utf8TrimRight(utf8 *s, u32 numChars);

void  ls_utf8InsertSubstr(utf8 *s, utf8 toInsert, u32 insertIdx);  //TODO: Make indices signed as well.
void  ls_utf8InsertChar(utf8 *s, u32 c, u32 idx);
void  ls_utf8InsertCStr(utf8 *s, char *toInsert, u32 insertIdx);
void  ls_utf8InsertBuffer(utf8 *s, u8 *toInsert, u32 buffLen, u32 insertIdx);

utf8 *ls_utf8Split(utf8 s, u32 *outNum, utf8 delim);
utf8 *ls_utf8Split(utf8 s, u32 *outNum, const u8 *delim);
utf8 *ls_utf8Split(utf8 s, u32 *outNum, u32 character);

s32   ls_utf8LeftFind(utf8 s, u8 c[4]);
s32   ls_utf8LeftFind(utf8 s, s32 offset, u8 c[4]);
s32   ls_utf8RightFind(utf8 s, u8 c[4]);
s32   ls_utf8RightFind(utf8 s, s32 offset, u8 c[4]);
s32   ls_utf8CountOccurrences(utf8 s, u8 c[4]);

b32   ls_utf8Contains(utf8 haystack, utf8 needle);

void  ls_utf8ToLower(utf8 *out, utf8 source);

//Merge
utf8  ls_utf8Concat(utf8 s1, utf8 s2);
void  ls_utf8ConcatOn(utf8 s1, utf8 s2, utf8 *out);
utf8  ls_utf8CatChar(utf8 s1, u32 c);
utf8  ls_utf8CatCStr(utf8 s1, char *c);
void  ls_utf8Prepend(utf8 *s1, utf8 s2);
void  ls_utf8PrependChar(utf8 *s, u32 c);
void  ls_utf8PrependCStr(utf8 *s, char *c);
void  ls_utf8Append(utf8 *s1, utf8 s2);
void  ls_utf8AppendChar(utf8 *s1, u32 c);
void  ls_utf8AppendCStr(utf8 *s1, char *c);
void  ls_utf8AppendNCStr(utf8 *s1, char *c, u32 len);
void  ls_utf8AppendBuffer(utf8 *s1, u32 *buff, u32 buffLen);

// Convert
s32   ls_utf8ToAscii_t(utf8 *s, char *buff, u32 buffMaxLen);
s64   ls_utf8ToInt(utf8 s);

b32   ls_utf8IsWhitespace(u32 c);
b32   ls_utf8IsNumber(u32 c);


//-----------------------------//
//    UTF32 UNICODE STRINGS    //
//-----------------------------//

//Create/Destroy
utf32  ls_utf32Alloc(s32 size);
utf32 *ls_utf32AllocArr(u32 numStrings, s32 initialSize);
void   ls_utf32Free(utf32 *s);
void   ls_utf32FreeArr(utf32 *s, s32 arrSize);

constexpr utf32 operator""_W(const char32_t *lit, size_t);

b32    ls_utf32AreEqual(utf32 a, utf32 b);
b32    ls_utf32AreEqualUpTo(utf32 a, utf32 b, s32 len);
b32    ls_utf32AsciiAreEqual(utf32 a, string b);
s32    ls_utf32FirstEqual(utf32 a, utf32 *set, s32 count);
void   ls_utf32Set(utf32 *toSet, utf32 source);

s32    ls_utf32Len(const char32_t *s);

utf32  ls_utf32FromAscii(char *s);
utf32  ls_utf32FromAscii(char *s, s32 len);
void   ls_utf32FromAscii_t(utf32 *dst, char *src);
void   ls_utf32FromAscii_t(utf32 *dst, char *src, s32 len);
void   ls_utf32FromUTF8_t(utf32 *dst, utf8 src, s32 len);
utf32  ls_utf32FromUTF8(utf8 src, s32 byteLen);
utf32  ls_utf32FromUTF32(const char32_t *s);
void   ls_utf32FromUTF32_t(utf32 *dst, const char32_t *s);
utf32  ls_utf32FromInt(s64 x);
void   ls_utf32FromInt_t(utf32 *s, s64 x);
utf32  ls_utf32FromF64(f64 x);
void   ls_utf32FromF64_t(utf32 *s, f64 x);
constexpr utf32 ls_utf32Constant(const char32_t *p);

u32    ls_utf32CharFromUtf8(utf8 src, s32 characterIndex);

//Manage
void   ls_utf32Clear(utf32 *s);
utf32  ls_utf32Copy(utf32 s);
void   ls_utf32Copy_t(utf32 s, utf32 *out);
void   ls_utf32NCopy(utf32 s, utf32 *dst, s32 size);
utf32  ls_utf32CopySubstr(utf32 s, u32 beginIdx, u32 _endIdx = (u32)-1);

//OperateOn
void   ls_utf32Reverse(utf32 *s);
void   ls_utf32RmSubstr(utf32 *s, u32 beginIdx, u32 endIdx);  //TODO: Call this RmRange. Make indices signed
b32    ls_utf32RmSubstr(utf32 *s, utf32 toRm);
void   ls_utf32RmIdx(utf32 *s, u32 idx);
void   ls_utf32TrimRight(utf32 *s, u32 numChars);

void   ls_utf32InsertSubstr(utf32 *s, utf32 toInsert, u32 insertIdx);
void   ls_utf32InsertSubstr(utf32 *s, const char32_t *toInsert, s32 insertIdx);
void   ls_utf32InsertChar(utf32 *s, u32 c, u32 idx);
void   ls_utf32InsertCStr(utf32 *s, const char *toInsert, u32 insertIdx);
void   ls_utf32InsertBuffer(utf32 *s, u32 *toInsert, s32 buffLen, u32 insertIdx);

utf32 *ls_utf32Split(utf32 s, u32 *outNum, utf32 delim);
utf32 *ls_utf32Split(utf32 s, u32 *outNum, const char32_t *a);
utf32 *ls_utf32Split(utf32 s, u32 *outNum, char32_t c);
utf32 *ls_utf32Split(utf32 s, u32 *outNum, u32 c);
utf32 *ls_utf32Split(utf32 s, u32 *outNum, char c);
utf32 *ls_utf32Split(utf32 s, u32 *outNum, const char *c);

utf32 *ls_utf32SeparateByNumber(utf32 s, u32 *outNum);

utf32 *ls_utf32BreakBySpaceUntilDelimiter(utf32 s, u32 delimiter, u32 *numOfStrings);

//TODO: Make offsets just default values and half the number of overloads??
s32    ls_utf32LeftFind(utf32 s, s32 offset, utf32 needle);
s32    ls_utf32LeftFind(utf32 s, utf32 needle);
s32    ls_utf32LeftFind(utf32 s, s32 offset, u32 c);
s32    ls_utf32LeftFind(utf32 s, u32 c);
s32    ls_utf32LeftFindAny(utf32 s, utf32 *needles, s32 count);

typedef b32(*UTF32FindProc)(u32 c);
s32    ls_utf32LeftFind(utf32 s, UTF32FindProc);
s32    ls_utf32LeftFindNumber(utf32 s, s32 offset);
s32    ls_utf32LeftFindNotNumber(utf32 s, s32 offset);
s32    ls_utf32RightFind(utf32 s, u32 c);
s32    ls_utf32RightFind(utf32 s, s32 offset, u32 c);
s32    ls_utf32RightFindNumber(utf32 s, s32 offset);
s32    ls_utf32CountOccurrences(utf32 s, u32 c);

b32    ls_utf32Contains(utf32 haystack, utf32 needle);

b32    ls_UTF32IsWhitespace(u32 c);

//Merge
utf32  ls_utf32Concat(utf32 s1, utf32 s2);
void   ls_utf32ConcatOn(utf32 s1, utf32 s2, utf32 *out);
utf32  ls_utf32CatChar(utf32 s1, u32 c);
utf32  ls_utf32CatCStr(utf32 s1, char *c);
void   ls_utf32Prepend(utf32 *s1, utf32 s2);
void   ls_utf32PrependChar(utf32 *s, u32 c);
void   ls_utf32PrependCStr(utf32 *s, char *c);
void   ls_utf32Append(utf32 *s1, utf32 s2);
void   ls_utf32Append(utf32 *s1, const char32_t *s);
void   ls_utf32AppendWithSeparator(utf32 *s1, const char32_t *sep, utf32 s2);
void   ls_utf32AppendChar(utf32 *s1, u32 c);
void   ls_utf32AppendCStr(utf32 *s1, char *c);
void   ls_utf32AppendNCStr(utf32 *s1, char *c, s32 len);
void   ls_utf32AppendBuffer(utf32 *s1, u32 *buff, s32 buffLen);
void   ls_utf32AppendInt(utf32 *s, s64 val);

b32    ls_utf32Replace(utf32 *s, const char32_t *pattern, const char32_t *replacement);
b32    ls_utf32Replace(utf32 *s, utf32 patStr, utf32 replStr);

// Convert
s32    ls_utf32ToAscii_t(utf32 s, char *buff, s32 buffMaxLen);
s64    ls_utf32ToInt(utf32 s);

b32    ls_utf32IsNumber(u32 c);



//-----------------------------//
//            VIEWS            //
//-----------------------------//

//Create/Destroy
view  ls_viewCreate(string s);
uview ls_uviewCreate(utf32 s);

//OperateOn
view  ls_viewExpect(view v, char c);
view  ls_viewExpectAndConsume(view v, char c);
char  ls_viewPeekNextChar(view v);
view  ls_viewEatWhitespace(view v);
view  ls_viewNextNumeric(view v);
view  ls_viewNextDigit(view v);
view  ls_viewNextNChars(view v, u32 n);
view  ls_viewNextDelimiter(view v, char c);
view  ls_viewNextWord(view v);
view  ls_viewNextLine(view v);
view  ls_viewNextLineSkipWS(view v);
b32   ls_viewIsLineEmpty(view v);

uview  ls_uviewEatWhitespace(uview v);
uview  ls_uviewNextNChars(uview v, u32 n);
uview  ls_uviewNextDelimiter(uview v, u32 c);
uview  ls_uviewNextWord(uview v);
uview  ls_uviewNextLine(uview v);
uview  ls_uviewNextLineSkipWS(uview v);

b32   ls_uviewIsLineEmpty(uview v);



#endif //LS_STRING_H


#ifdef LS_STRING_IMPLEMENTATION

/*vv INTERNAL vv*/
static void ls_strGrow(string *s, u32 amount)
{
    AssertMsg(s, "String ptr was null\n");
    AssertMsg(amount < UINT32_MAX-1, "Amount was UINT32_MAX. Probably not a good sign. Off by 1 error?\n");
    u32 newSize = s->size + amount;
    
    char *newData = (char *)ls_alloc(sizeof(char)*newSize);
    if(s->data)
    {
        ls_memcpy(s->data, newData, s->len);
        ls_free(s->data);
    }
    
    s->data = newData;
    s->size = newSize;
}

static void ls_utf32Grow(utf32 *s, u32 amount)
{
    AssertMsg(s, "String ptr was null\n");
    AssertMsg(amount < UINT32_MAX-1, "Amount was UINT32_MAX. Probably not a good sign. Off by 1 error?\n");
    u32 newSize = s->size + amount;
    
    u32 *newData = (u32 *)ls_alloc(sizeof(u32)*newSize);
    if(s->data)
    {
        ls_memcpy(s->data, newData, s->len*sizeof(u32));
        ls_free(s->data);
    }
    
    s->data = newData;
    s->size = newSize;
}
/*^^ INTERNAL ^^*/



//------------------//
//  Create/Destroy  //

string ls_strAlloc(s32 size)
{
    AssertMsg(size > 0, "Non-Positive size when allocating string\n");
    
    char *data = (char *)ls_alloc(sizeof(char)*size);
    string Result = {data, 0, size};
    
    return Result;
}

string *ls_strAllocPtr(s32 size)
{
    AssertMsg(size > 0, "Non-Positive size when allocating string\n");
    
    string *Result = (string *)ls_alloc(sizeof(string));
    *Result = ls_strAlloc(size);
    
    return Result;
};

string *ls_strAllocArr(u32 numStrings, s32 initialSize = 0)
{
    AssertMsg(initialSize >= 0, "Non-Positive initialSize when allocating string array\n");
    
    string *s = (string *)ls_alloc(sizeof(string)*numStrings);
    if(initialSize > 0)
    {
        for(u32 i = 0; i < numStrings; i++) { s[i] = ls_strAlloc(initialSize); }
    }
    
    return s;
}

void ls_strFree(string *a)
{
    AssertMsg(a, "Trying to free a null pointer string\n");
    AssertMsgF(a->size >= 0, "Trying to free a Non-Positive sized string: %d\n", a->size);
    
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
}

void ls_strFreePtr(string *a)
{
    AssertMsg(a, "Trying to free a null pointer string\n");
    AssertMsgF(a->size > 0, "Trying to free a Non-Positive sized string: %d\n", a->size);
    
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
    
    ls_free(a);
}

void ls_strFreeArr(string *s, s32 arrSize)
{
    AssertMsg(s, "Trying to free a null pointer string\n");
    AssertMsg(arrSize > 0, "Non-Positive number of elements in array\n");
    
    for(u32 i = 0; i < arrSize; i++)
    { ls_strFree(&s[i]);}
    
    ls_free(s);
}

string ls_strConstant(const char *p)
{
    s32 len = ls_len((char *)p);
    string s = { (char *)p, len, -7878 };
    return s;
}

string ls_strConstant(char *p)
{
    s32 len = ls_len(p);
    string s = { p, len, -7878 };
    return s;
}

string ls_strConstant(char *p, s32 len)
{
    AssertMsg(len > 0, "Non-Positive len in constant string\n");
    
    string s = {p, len, -7878 };
    return s;
}

string ls_strConstChar(char *c)
{
    AssertMsg(c, "Null character address\n");
    
    string s = {c, 1, -7878};
    return s;
}


//  Create/Destroy  //
//------------------//


//------------------//
//     Manage       //

string ls_strInit(char *s)
{
    AssertMsg(s, "Null pointer to string constant\n");
    
    u32 len = ls_len(s);
    
    string Result = ls_strAlloc(len);
    ls_memcpy(s, Result.data, len);
    Result.len = len;
    
    return Result;
}

string ls_strInit(const char *s)
{
    AssertMsg(s, "Null pointer to string constant\n");
    
    u32 len = ls_len((char *)s);
    
    string Result = ls_strAlloc(len);
    ls_memcpy((void *)s, (void *)Result.data, len);
    Result.len = len;
    
    return Result;
}

void ls_strClear(string *s)
{ 
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to clear a Non-Positive sized string: %d\n", s->size);
    
    s->len = 0;
}

string ls_strCopy(string s)
{
    string Result = ls_strAlloc(s.len);
    ls_memcpy(s.data, Result.data, s.len);
    Result.len = s.len;
    
    return Result;
}

void ls_strNCopy(string src, string *dst, size_t size)
{
    AssertMsg(dst, "Null pointer to dest\n");
    
    u32 copySize = size;
    if(size > src.len) { copySize = src.len; }
    
    //TODO: Should the alloc and then maybe grow change???
    if(dst->data == NULL) { *dst = ls_strAlloc(copySize); }
    
    if(dst->size < src.len)
    {
        u32 growAmount = (dst->size - src.len + 32);
        ls_strGrow(dst, growAmount);
    }
    
    ls_memcpy(src.data, dst->data, copySize);
    dst->len = copySize;
}

string ls_strCopySubstr(string s, u32 beginIdx, u32 _endIdx)
{
    u32 endIdx = 0;
    if(_endIdx == (u32)-1) { endIdx = s.len-1; }
    else { endIdx = _endIdx; }
    
    if((beginIdx < 0 || beginIdx >= s.size) ||
       (endIdx < 0 || endIdx >= s.size) ||
       (endIdx - beginIdx >= s.size))
    { string error = {}; return error; }
    
    //TODO: Remove THIS
    // Need NULL terminator cause I haven't changed
    // All my functions to work with strings yet...
    string result = ls_strAlloc(((endIdx - beginIdx) + 1) + 1);
    
    ls_memcpy(s.data + beginIdx, result.data, result.size);
    result.len = (endIdx - beginIdx + 1);
    result.data[result.len] = 0;
    
    return result;
}

//      Manage      //
//------------------//


//------------------//
//    C Bullshit    //

void ls_strNullTerminate(string *s)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to null terminate a Non-Positive sized string: %d\n", s->size);
    
    if(s->len == s->size)
    { ls_strGrow(s, 1); }
    
    s->data[s->len] = 0;
}

char *ls_strToCStr(string s)
{
    char *result = (char *)ls_alloc(s.len + 1);
    ls_memcpy(s.data, result, s.len);
    result[s.len] = 0;
    
    return result;
}

void ls_strToCStr_t(string s, char *buff, s32 buffSize)
{
    AssertMsg(buff, "Null pointer to dest buff\n");
    AssertMsg(buffSize >= s.len+1, "C String Buff not large enough\n");
    
    ls_memcpy(s.data, buff, s.len);
    buff[s.len] = 0;
}


//    C Bullshit    //
//------------------//


//------------------//
//     OperateOn    //

void ls_strReverse(string *s)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to reverse a Non-Positive sized string: %d\n", s->size);
    
    char *Begin = s->data;
    char *End = s->data + s->len;
    if(*End == 0) { End--; } //Ignore null-terminator
    while (Begin < End)
    {
        char temp = *Begin;
        *Begin = *End;
        *End = temp;
        Begin++;
        End--;
    }
}

void ls_strRmSubstr(string *s, u32 beginIdx, u32 endIdx)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to remove from a Non-Positive sized string: %d\n", s->size);
    
    AssertMsg(beginIdx < s->len, "Begin Index Out of Bounds. Larger than string length\n");
    AssertMsg(endIdx < s->len, "End Index Out of Bounds. Larger than string length\n");
    AssertMsg(beginIdx < endIdx, "Begin Index is larger than End Index\n");
    AssertMsg((endIdx - beginIdx) < s->len, "Index Range is larger than length of string. How did this happen?\n");
    
    u32 remove = ((endIdx - beginIdx) + 1);
    remove = remove > s->len ? s->len : remove;
    
    u32 copyLen = s->len - (endIdx + 1);
    copyLen = copyLen == 0 ? 1 : copyLen;
    
    //NOTE: This is to avoid memcpying overlapping memory locations
    u32 *tempMem = (u32 *)ls_alloc(copyLen+1);
    
    ls_memcpy((void *)(s->data + endIdx + 1), tempMem, copyLen);
    ls_memcpy(tempMem, (void *)(s->data + beginIdx), copyLen);
    
    ls_free(tempMem);
    
    s->len -= remove;
    s->data[s->len] = 0; //TODO: Fuck C strings. Remove this abomination.
    
    return;
}

void ls_strRmIdx(string *s, u32 idx)
{ ls_strRmSubstr(s, idx, idx); }

void ls_strRmAllNonTextChar(string *s)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to remove from a Non-Positive sized string: %d\n", s->size);
    
    string *Result = ls_strAllocPtr(s->size);
    
    for(u32 i = 0; i < s->len; i++)
    {
        char c = s->data[i];
        if(!ls_isANumber(c))
        {
            if(c != '\r' && c != '\n' && c != '\t')
            {
                if(c < 32 || c > 126)
                { continue; }
            }
        }
        
        ls_strAppend(Result, c);
    }
    
    ls_free(s->data);
    *s = *Result;
    
    return;
}

void ls_strTrimRight(string *s, u32 numChars)
{ 
    AssertMsg(s, "Null string pointer passed\n");
    AssertMsg(s->len > 0, "Trying to trim an empty string\n");
    AssertMsgF(s->size > 0, "Trying to trim a Non-Positive sized string: %d\n", s->size);
    
    s->len -= numChars; 
}

void ls_strInsertSubstr(string *s, string toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null string pointer passed\n");
    AssertMsgF(s->size > 0, "Trying to insert into a Non-Positive sized string: %d\n", s->size);
    AssertMsg(insertIdx < s->len, "Insertion index past string length\n");
    
    if(s->size < s->len + toInsert.len)
    { ls_strGrow(s, toInsert.len); }
    
    //TODO:Make a better reverse memcpy for non byte-boundary blocks.
    s32 moveBytes = s->len - insertIdx;
    
    u8 *tempBuff = (u8 *)ls_alloc(moveBytes);
    ls_memcpy(s->data + insertIdx, tempBuff, moveBytes);
    ls_memcpy(tempBuff, s->data + insertIdx + toInsert.len, moveBytes);
    
    ls_free(tempBuff);
    
    ls_memcpy(toInsert.data, s->data + insertIdx, toInsert.len);
    
    s->len += toInsert.len;
}

void ls_strInsertChar(string *s, char c, u32 idx)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsgF(s->size > 0, "Trying to insert into a Non-Positive sized string: %d\n", s->size);
    
    //NOTE: This looks horrible. Even though it shouldn't create any problem since everything is copied.
    string insertString = ls_strConstChar(&c);
    ls_strInsertSubstr(s, insertString, idx);
}

void ls_strInsertCStr(string *s, char *toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null pointer to string\n");
    AssertMsg(toInsert, "Null pointer toInsert C string\n");
    AssertMsgF(s->size > 0, "Trying to insert into a Non-Positive sized string: %d\n", s->size);
    
    string insertString = ls_strConstant(toInsert);
    ls_strInsertSubstr(s, insertString, insertIdx);
}



string *ls_strBreakByDelimeter(string s, u32 *numOfStrings, char c)
{
    AssertMsg(numOfStrings, "Null pointer to out param numOfStrings\n");
    
    if(s.data == NULL) { return NULL; }
    if(s.len == 0)     { return NULL; }
    
    string *Result = 0;
    //TODO: The thing could crash if this buff overflows
    //      It's trivial to first count the occurence of the delimiter and allocate the necessary strings.
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        AssertMsg(buffIdx < 16384, "Buffer overflow\n");
        
        if (*At == c)
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            break;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    
    if(numOfStrings) {*numOfStrings = buffIdx;}
    
    return Result;
}

string *ls_strBreakByLine(string s, s32 *numOfLines)
{
    AssertMsg(numOfLines, "Null pointer to out param numOfLines\n");
    
    if(s.data == NULL) { return NULL; }
    if(s.len  == 0)    { return NULL; }
    
    u32 numLines = 1; // NOTE: Last line doesn't have newline in string? Can it?
    char *bAt = s.data;
    u32 l = s.len;
    //NOTE: This is currently overcounting when there's two newlines one after the other
    //But it doesn't matter because I only need the base pointer to free this, so no
    //memory is leaked, only slightly overused for most cases.
    while(l--)
    {
        if(*bAt == '\r') { numLines++; bAt += 2; l -= 1; continue; }
        if(*bAt == '\n') { numLines++; bAt += 1; continue; }
        bAt += 1;
    }
    
    string *Result = (string *)ls_alloc(sizeof(string)*numLines);
    
    char *At = s.data;
    u32 count = 0;
    u32 done = 0;
    u32 idx = 0;
    numLines = 0;
    
    u32 currLen = s.len;
    while(currLen--)
    {
        if(*At == '\r' && count == 0) { At += 2; currLen--; done += 2; continue; }
        if(*At == '\n' && count == 0) { At += 1; done += 1; continue; }
        
        
        if(*At == '\n' || currLen == 0)
        {
            u32 extra = 0;
            if(*(At-1) == '\r') { count--; extra = 1; }
            if(currLen == 0) {count += 1;}
            
            Result[idx] = ls_strAlloc(count + 1); numLines += 1;
            ls_memcpy(s.data + done, Result[idx].data, count);
            Result[idx].data[count] = 0;
            Result[idx].len  = count;
            
            done += count + 1 + extra;
            idx++;
            count = 0;
            
            At++;
            continue;
        }
        
        At++;
        count++;
    }
    
    if(numOfLines) { *numOfLines = numLines; }
    return Result;
}

string *ls_strBreakByWhitespace(string s, u32 *numOfStrings)
{
    AssertMsg(numOfStrings, "Null pointer to out param numOfStrings\n");
    
    if(s.data == NULL) { return NULL; }
    if(s.len  == 0)    { return NULL; }
    
    string *Result = 0;
    //TODO: The thing could crash if this buff overflows
    //      It's trivial to first count the occurence of the delimiter and allocate the necessary strings.
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        AssertMsg(buffIdx < 16384, "Buffer Overflow\n");
        
        if ((*At == ' ') || (*At == '\n') || (*At == '\t') || (*At == '\r') )
        {
            if((*At == '\r') && (*(At + 1) == '\n'))
            {
                done++;
                At++;
            }
            
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count + 1;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count + 1;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            break;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    
    if(numOfStrings) {*numOfStrings = buffIdx;}
    
    return Result;
}

string *ls_strBreakBySpace(string s, u32 *numOfStrings)
{
    return ls_strBreakByDelimeter(s, numOfStrings, ' ');
}

string *ls_strBreakBySpaceUntilDelimiter(string s, char delimiter, u32 *numOfStrings)
{
    AssertMsg(numOfStrings, "Null pointer to out param numOfStrings\n");
    
    if(s.data == NULL) { return NULL; }
    if(s.len  == 0)    { return NULL; }
    
    string *Result = 0;
    
    //TODO: The thing could crash if this buff overflows
    //      It's trivial to first count the occurence of the delimiter and allocate the necessary strings.
    string buff[256] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        AssertMsg(buffIdx < 256, "Buffer overflow\n");
        
        if (*At == delimiter)
        {
            if(*(At + 1) == ' ') {done++;}
            done++;
            break;
        }
        
        if (*At == ' ')
        {
            
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    if(numOfStrings) { *numOfStrings = buffIdx; }
    
    return Result;
}

s32 ls_strLeftFind(string s, char c)
{
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    
    char *At = s.data;
    s32 offset = 0;
    while (At != (s.data + s.len))
    { 
        if(*At == c) { return offset; }
        At++; offset++;
    }
    
    return -1;
}

s32 ls_strRightFind(string s, char c)
{
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    
    char *At = s.data + s.len;
    s32 offset = s.len;
    
    while(At != s.data)
    {
        if(*At == c) { return offset; }
        At--;
        offset--;
    }
    
    return -1;
}

//    OperateOn     //
//------------------//


//------------------//
//      Merge       //

string ls_strConcat(string s1, string s2)
{
    string Result = ls_strAlloc(s1.len + s2.len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2.len) { ls_memcpy(s2.data, Result.data + s1.len, s2.len); }
    Result.len = s1.len + s2.len;
    
    return Result;
}

void ls_strConcatOn(string s1, string s2, string *out)
{
    AssertMsg(out, "Null out param out\n");
    AssertMsg(out->data, "Out param is not allocated\n");
    AssertMsgF(out->size > 0, "Out param is a Non-Positive sized string: %d\n", out->size);
    
    if(out == 0x0) return;
    if(out->data == 0x0) return;
    if(out->size < (s1.len + s2.len)) { return; }
    
    if(s1.len) { ls_memcpy(s1.data, out->data, s1.len); }
    if(s2.len) { ls_memcpy(s2.data, out->data + s1.len, s2.len); }
    out->len = s1.len + s2.len;
}

string ls_strCatChar(string s, char c)
{
    string Result = ls_strAlloc(s.len + 1);
    if(s.len) { ls_memcpy(s.data, Result.data, s.len); }
    Result.data[s.len] = c;
    Result.len = s.len + 1;
    
    return Result;
}

string ls_strCatCStr(string s1, char *s2)
{
    AssertMsg(s2, "Null input c string s2\n");
    s32 s2Len = ls_len(s2);
    
    string Result = ls_strAlloc(s1.len + s2Len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2Len) { ls_memcpy(s2, Result.data + s1.len, s2Len); }
    Result.len = s1.len + s2Len;
    
    return Result;
}

void ls_strPrepend(string *s1, string s2)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(s2.data, "Input string data is null\n");
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    char *At = s1->data + s1->len - 1;
    char *To = s1->data + s1->len + s2.len - 1;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s2.data, s1->data, s2.len);
    s1->len = s1->len + s2.len;
}

void ls_strPrependChar(string *s1, char c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_strGrow(s1, 32); }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    char *At = s1->data + s1->len - 1;
    char *To = s1->data + s1->len;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s1->data, s1->data + 1, s1->len);
    
    s1->data[0] = c;
    s1->len += 1;
}

void ls_strPrependCStr(string *s1, char *s2)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(s2, "C string ptr is null\n");
    
    u32 s2Len = ls_len(s2);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(s1->data, s1->data + s2Len, s1->len);
    ls_memcpy(s2, s1->data, s2Len);
    s1->len = s1->len + s2Len;
}

//@NOTE:TODO: Something strange appening in strings appending and getting longer
//Looks like memory stomping. Not quite sure how it would happen, since the grow
//seems to be good. - 29/04/2019
void ls_strAppend(string *s1, string s2)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(s2.data, "Input string data is null\n");
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(s2.data, s1->data + s1->len, s2.len);
    s1->len += s2.len;
}

void ls_strAppend(string *s, view v)
{
    AssertMsg(s, "Base string ptr is null\n");
    AssertMsgF(s->size > 0, "Trying to write to Non-Positive sized string: %d\n", s->size);
    AssertMsg(s->data, "Base string data is null\n");
    
    if(s->len + v.s.len > s->size)
    {
        u32 growSize = ((s->len + v.s.len) - s->size) + 32;
        ls_strGrow(s, growSize);
    }
    
    ls_memcpy(v.s.data, s->data + s->len, v.s.len);
    s->len += v.s.len;
}

void ls_strAppend(string *s1, char c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_strGrow(s1, 32); }
    
    s1->data[s1->len] = c;
    s1->len += 1;
}

void ls_strAppend(string *s1, char *c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    u32 len = ls_len(c);
    ls_strAppend(s1, c, len);
}

void ls_strAppend(string *s1, const char *c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    u32 len = ls_len((char *)c);
    ls_strAppend(s1, (char *)c, len);
}

void ls_strAppend(string *s1, char *c, u32 s2Len)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(c, s1->data + s1->len, s2Len);
    s1->len += s2Len;
}

//      Merge       //
//------------------//


//------------------//
//   To/From Data   //

//NOTE: Is returning a space for an invalid ascii codepoint ok?
u8 ls_strCharFromUTF32(u32 codepoint)
{
    if(codepoint < 128) { return (u8)codepoint; }
    else                { return ' '; }
}

b32 ls_strIsANumber(string s)
{
    for(u32 i = 0; i < s.len; i++)
    {
        if(ls_isANumber(s.data[i]) == FALSE)
        { return FALSE; }
    }
    
    return TRUE;
}

string ls_itos(s64 x)
{
    string result = ls_strAlloc(32);
    ls_itosOn(x, &result);
    return result;
}

void ls_itosOn(s64 x, string *out)
{
    AssertMsg(out, "Null out param out\n");
    AssertMsg(out->data, "Out param is not allocated\n");
    
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if (value == 0)
    {
        out->data[0] = '0';
        out->data[1] = '\0';
        out->len = 1;
        
        return;
    }
    
    s32 i = 0;
    while (value != 0)
    {
        out->data[i++] = value % 10 + '0';
        value = value / 10;
        
        AssertMsg(out->len > i, "Out string is not large enough to contain the number");
    }
    
    if (isNegative) { out->data[i++] = '-'; }
    out->data[i] = '\0';
    
    //@TODO@Speed Never build the string flipped!
    //(Still would need an approx of size.)
    
    //Flip string, it's in reverse.
    for (int t = 0; t < i / 2; t++)
    {
        out->data[t] ^= out->data[i - t - 1];
        out->data[i - t - 1] ^= out->data[t];
        out->data[t] ^= out->data[i - t - 1];
    }
    out->len = (u32)i;
}

string ls_itoh(u64 x)
{
    string buf = ls_strAlloc(32);
    string Result = ls_strAlloc(64);
    
    u8 *At = (u8 *)&x;
    for(u32 i = 0; i < 8; i++)
    {
        u8 lowNybble = (*At & 0x0F);
        u8 highNybble = (*At & 0xF0) >> 4;;
        
        switch(lowNybble)
        {
            case 0:  ls_strAppend(&buf, '0'); break;
            case 1:  ls_strAppend(&buf, '1'); break;
            case 2:  ls_strAppend(&buf, '2'); break;
            case 3:  ls_strAppend(&buf, '3'); break;
            case 4:  ls_strAppend(&buf, '4'); break;
            case 5:  ls_strAppend(&buf, '5'); break;
            case 6:  ls_strAppend(&buf, '6'); break;
            case 7:  ls_strAppend(&buf, '7'); break;
            case 8:  ls_strAppend(&buf, '8'); break;
            case 9:  ls_strAppend(&buf, '9'); break;
            case 10: ls_strAppend(&buf, 'A'); break;
            case 11: ls_strAppend(&buf, 'B'); break;
            case 12: ls_strAppend(&buf, 'C'); break;
            case 13: ls_strAppend(&buf, 'D'); break;
            case 14: ls_strAppend(&buf, 'E'); break;
            case 15: ls_strAppend(&buf, 'F'); break;
        }
        
        switch(highNybble)
        {
            case 0:  ls_strAppend(&buf, '0'); break;
            case 1:  ls_strAppend(&buf, '1'); break;
            case 2:  ls_strAppend(&buf, '2'); break;
            case 3:  ls_strAppend(&buf, '3'); break;
            case 4:  ls_strAppend(&buf, '4'); break;
            case 5:  ls_strAppend(&buf, '5'); break;
            case 6:  ls_strAppend(&buf, '6'); break;
            case 7:  ls_strAppend(&buf, '7'); break;
            case 8:  ls_strAppend(&buf, '8'); break;
            case 9:  ls_strAppend(&buf, '9'); break;
            case 10: ls_strAppend(&buf, 'A'); break;
            case 11: ls_strAppend(&buf, 'B'); break;
            case 12: ls_strAppend(&buf, 'C'); break;
            case 13: ls_strAppend(&buf, 'D'); break;
            case 14: ls_strAppend(&buf, 'E'); break;
            case 15: ls_strAppend(&buf, 'F'); break;
        }
        At++;
    }
    
    buf.data[buf.len] = 0;
    ls_strReverse(&buf);
    
    ls_strAppend(&Result, (char*)"0x");
    
    while(true)
    {
        if(buf.len == 2) { break; }
        if((buf.data[0] != '0') || (buf.data[1] != '0'))
        { break; }
        else
        { ls_strRmSubstr(&buf, 0, 1); }
    }
    
    string P = ls_strConcat(Result, buf);
    ls_strNullTerminate(&P);
    
    ls_strFree(&buf);
    ls_strFree(&Result);
    
    return P;
}

s64 ls_stoi(string s)
{
    s64 Result = ls_atoi(s.data, s.len);
    return Result;
}

f32 ls_stof(string s)
{
    f64 Result = ls_atof(s.data, s.len);
    return Result;
}

string ls_ftos(f32 x)
{
    string Result = {};
    
    char *data = ls_ftoa(x);
    u32 len = ls_len(data);
    
    Result.data = data;
    Result.len = len;
    Result.size = len;
    
    return Result;
}

//   To/From Data   //
//------------------//

//------------------//
//      CRT-ish     //

//NOTE: if we want the entire file -> readLenInBytes == 0 
//      else set to the amount of bytes to be read.
string ls_strReadFile(char *path, s32 readLenInBytes)
{
    string result = {};
    result.len    = ls_readFile(path, &result.data, readLenInBytes);
    
    if(result.data == NULL) { return {}; }
    
    result.size   = result.len;
    return result;
}

//      CRT-ish     //
//------------------//

//------------------//
//     Operator     //

b32 operator==(string s1, string s2)
{
    if(s1.len != s2.len) { return FALSE; }
    return ls_memcmp(s1.data, s2.data, s1.len);
}

b32 operator==(string s1, char *v)
{
    u32 len = ls_len(v);
    if(s1.len != len) { return FALSE; }
    return ls_memcmp(s1.data, v, s1.len);
}

b32 operator==(string s1, const char *v)
{
    //NOTE: Maybe shouldn't do this, but it's fine
    char *unConsted = (char *)v;
    
    u32 len = ls_len(unConsted);
    if(s1.len != len) { return FALSE; }
    return ls_memcmp(s1.data, unConsted, s1.len);
}

b32 operator==(string s, char v)
{
    if(s.len != 1) { return FALSE; }
    return (s.data[0] == v ? TRUE : FALSE);
}

b32 operator!=(string s1, string s2)
{ return (!(s1 == s2)); }

b32 operator!=(string s1, char *v)
{ return (!(s1 == v)); }

b32 ls_strIsEqualNCStr(string s1, char *s2, u32 len)
{
    if(s1.len < len) { return FALSE; }
    return ls_memcmp(s1.data, s2, len);
}

//     Operator     //
//------------------//


//-----------------------------//
//    UTF8  STRINGS

//Create/Destroy
utf8 ls_utf8Alloc(s32 size)
{
    AssertMsg(size > 0, "Non-Positive size when allocating string\n");
    
    u8 *data = (u8 *)ls_alloc(sizeof(u8) * size);
    utf8 result = { data, 0, 0, size };
    return result;
}

utf8 *ls_utf8AllocArr(u32 numStrings, s32 initialSize)
{
    AssertMsg(initialSize >= 0, "Non-Positive initialSize when allocating string array\n");
    
    if(numStrings == 0) { return 0x0; }
    
    utf8 *result = (utf8 *)ls_alloc(sizeof(utf8)*numStrings);
    if(initialSize > 0)
    {
        for(u32 i = 0; i < numStrings; i++) { result[i] = ls_utf8Alloc(initialSize); }
    }
    
    return result;
}

void ls_utf8Free(utf8 *s)
{
    AssertMsg(s, "Null string pointer\n");
    AssertMsgF(s->size >= 0, "Trying to free a Non-Positive sized string: %d\n", s->size);
    
    ls_free(s->data);
    s->data     = 0;
    s->len      = 0;
    s->byteLen  = 0;
    s->size     = 0;
}

void ls_utf8FreeArr(utf8 *s, s32 arrSize)
{
    AssertMsg(s, "Null string pointer\n");
    AssertMsgF(arrSize > 0, "Non-Positive number of elements in array: %d\n", arrSize);
    
    for(u32 i = 0; i < arrSize; i++)
    { ls_utf8Free(&s[i]);}
    
    ls_free(s);
}

b32 ls_utf8AreEqual(utf8 a, utf8 b)
{
    AssertMsg(a.data, "First string's data pointer is null");
    AssertMsg(b.data, "Second string's data pointer is null");
    
    if(a.data == b.data)       { return TRUE; }
    if(a.len != b.len)         { return FALSE; }
    if(a.byteLen != b.byteLen) { return FALSE; }
    
    return ls_memcmp(a.data, b.data, a.byteLen*sizeof(u8));
}

b32 ls_utf8IsValid(u8 *src, s32 byteLen)
{
    AssertMsg(src, "Null source pointer\n");
    AssertMsgF(byteLen > 0, "Non-Positive byteLen: %d\n", byteLen);
    
    u8 *At = (u8 *)src;
    while(byteLen > 0)
    {
        if(*At <= 0x7F)      { byteLen -= 1; At  += 1; }
        else if(*At <= 0xDF) { byteLen -= 2; At  += 2; }
        else if(*At <= 0xEF) { byteLen -= 3; At  += 3; }
        else if(*At <= 0xF7) { byteLen -= 4; At  += 4; }
        else { return FALSE; }
        
        if(byteLen < 0) { return FALSE; }
    }
    
    return TRUE;
}

s32 ls_utf8Len(u8 *src, s32 byteLen)
{
    AssertMsg(src, "Null source pointer\n");
    AssertMsgF(byteLen > 0, "Non-Positive byteLen: %d\n", byteLen);
    
    s32 len = 0;
    u8 *At = (u8 *)src;
    while(byteLen > 0)
    {
        if(*At <= 0x7F)      { byteLen -= 1; At  += 1; }
        else if(*At <= 0xDF) { byteLen -= 2; At  += 2; }
        else if(*At <= 0xEF) { byteLen -= 3; At  += 3; }
        else if(*At <= 0xF7) { byteLen -= 4; At  += 4; }
        else { AssertMsgF(FALSE, "Unsupported utf8 character (c0: %d)... This should never be reached?\n", *At); }
        
        AssertMsg(byteLen >= 0, "Malformed utf8_source or Byte Length.\n");
        
        len += 1;
    }
    
    return len;
}

void ls_utf8Set(utf8 *toSet, utf8 source)
{
    AssertMsg(toSet, "String to be set pointer is null\n");
    AssertMsgF(toSet->size >= 0, "Trying to write to a Non-Positive sized string: %d\n", toSet->size);
    
    if(toSet->size < source.byteLen) { ls_utf8Free(toSet); }
    
    if(!toSet->data)
    { 
        u32 allocSize = (16 + source.byteLen);
        
        toSet->data = (u8 *)ls_alloc(allocSize*sizeof(u8));
        toSet->size = allocSize;
    }
    
    //NOTE: We assume source.byteLen == 0 if source.len == 0
    if(source.len == 0) { toSet->len = 0; toSet->byteLen = 0; return; }
    
    ls_memcpy(source.data, toSet->data, source.byteLen*sizeof(u8));
    toSet->len     = source.len;
    toSet->byteLen = source.byteLen;
}

utf8 ls_utf8FromAscii(char *s, s32 len)
{
    AssertMsg(s, "Null source c string\n");
    
    if(s == NULL) { return {}; }
    if(len == 0)  { return {}; }
    
    utf8 result = ls_utf8Alloc(len);
    
    for(u32 i = 0; i < len; i++) { result.data[i] = (u8)s[i]; }
    
    result.len     = len;
    result.byteLen = len;
    
    return result;
}

utf8 ls_utf8FromAscii(char *s)
{
    s32 len = ls_len(s);
    return ls_utf8FromAscii(s, len);
}

void ls_utf8FromAscii_t(utf8 *dst, char *src, s32 len)
{
    AssertMsg(dst, "Destination pointer is null\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(src, "Null source c string\n");
    AssertMsg(dst->size >= len, "TODO: Dst growth in this function\n");
    
    if(src == NULL) { return; }
    if(len == 0)    { return; }
    
    for(u32 i = 0; i < len; i++) { dst->data[i] = (u8)src[i]; }
    dst->len     = len;
    dst->byteLen = len;
}

void ls_utf8FromAscii_t(utf8 *dst, char *src)
{
    AssertMsg(dst, "Destination pointer is null\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(src, "Null source c string\n");
    
    if(src == NULL) { return; }
    
    u32 len = ls_len(src);
    ls_utf8FromAscii_t(dst, src, len);
}

utf8 ls_utf8FromUTF32(utf32 s)
{
    AssertMsg(s.data, "Null source string data\n");
    
    if(s.data == NULL) { return {}; }
    
    u32 byteLen = 0;
    u32 len = s.len;
    u32 *At = (u32 *)s.data;
    while(len--)
    {
        if(*At <= 0x7F)        byteLen += 1;
        else if(*At <= 0x7FF)  byteLen += 2;
        else if(*At <= 0xFFFF) byteLen += 3;
        else                   byteLen += 4;
        
        At  += 1;
    }
    
    utf8 result = ls_utf8Alloc(byteLen);
    result.byteLen = byteLen;
    result.len = s.len;
    
    for(u32 utf32_index = 0, utf8_index = 0; utf32_index < s.len; utf32_index++)
    {
        u32 utf32_code = s.data[utf32_index];
        
        AssertMsg(utf32_code <= 0x10FFFF, "UTF32 codepoint outside valid range [0x0 - 0x10FFFF]");
        
        if(utf32_code <= 0x7F)
        {
            result.data[utf8_index] = (u8)utf32_code;
            utf8_index += 1;
        }
        else if(utf32_code <= 0x7FF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0x07C0 & base_bytes) >> 6) | 0xC0);
            u8 low  = (u8)((0x003F  & base_bytes)       | 0x80);
            
            result.data[utf8_index]     = high;
            result.data[utf8_index + 1] = low;
            
            utf8_index += 2;
        }
        else if(utf32_code <= 0xFFFF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0xF000 & base_bytes) >> 12) | 0xE0);
            u8 mid  = (u8)(((0x0FC0 & base_bytes) >> 6)  | 0x80);
            u8 low  = (u8)((0x003F  & base_bytes)        | 0x80);
            
            result.data[utf8_index]     = high;
            result.data[utf8_index + 1] = mid;
            result.data[utf8_index + 2] = low;
            
            utf8_index += 3;
        }
        else if(utf32_code <= 0x10FFFF)
        {
            u8 high = (u8)(((0x001C0000 & utf32_code) >> 18) | 0xF0);
            u8 midh = (u8)(((0x0003F000 & utf32_code) >> 12) | 0x80);
            u8 midl = (u8)(((0x00000FC0 & utf32_code) >> 6)  | 0x80);
            u8 low  = (u8)((0x0000003F  & utf32_code)        | 0x80);
            
            result.data[utf8_index]     = high;
            result.data[utf8_index + 1] = midh;
            result.data[utf8_index + 2] = midl;
            result.data[utf8_index + 3] = low;
            
            utf8_index += 4;
        }
    }
    
    return result;
}

void ls_utf8FromUTF32_t(utf8 *dst, const char32_t *s)
{
    AssertMsg(dst, "Destination pointer is null\n");
    AssertMsgF(dst->size >= 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(s, "Null c string pointer\n");
    
    if(s == NULL) { return; }
    
    u32 byteLen = 0;
    u32 len = 0;
    u32 *At = (u32 *)s;
    while(*At)
    {
        if(*At <= 0x7F)        byteLen += 1;
        else if(*At <= 0x7FF)  byteLen += 2;
        else if(*At <= 0xFFFF) byteLen += 3;
        else                   byteLen += 4;
        
        At  += 1;
        len += 1;
    }
    
    if(dst->size < byteLen) { ls_utf8Free(dst); }
    
    if(dst->data == 0)
    {
        u32 allocSize = (16 + byteLen);
        
        dst->data     = (u8 *)ls_alloc(allocSize*sizeof(u8));
        dst->size     = allocSize;
    }
    
    u32 *utf32_buffer = (u32 *)s;
    
    for(u32 utf32_index = 0, utf8_index = 0; utf32_index < len; utf32_index++)
    {
        u32 utf32_code = utf32_buffer[utf32_index];
        
        AssertMsg(utf32_code <= 0x10FFFF, "UTF32 codepoint outside valid range [0x0 - 0x10FFFF]");
        
        if(utf32_code <= 0x7F)
        {
            dst->data[utf8_index] = (u8)utf32_code;
            utf8_index += 1;
        }
        else if(utf32_code <= 0x7FF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0x07C0 & base_bytes) >> 6) | 0xC0);
            u8 low  = (u8)((0x003F  & base_bytes)       | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = low;
            
            utf8_index += 2;
        }
        else if(utf32_code <= 0xFFFF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0xF000 & base_bytes) >> 12) | 0xE0);
            u8 mid  = (u8)(((0x0FC0 & base_bytes) >> 6)  | 0x80);
            u8 low  = (u8)((0x003F  & base_bytes)        | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = mid;
            dst->data[utf8_index + 2] = low;
            
            utf8_index += 3;
        }
        else if(utf32_code <= 0x10FFFF)
        {
            u8 high = (u8)(((0x001C0000 & utf32_code) >> 18) | 0xF0);
            u8 midh = (u8)(((0x0003F000 & utf32_code) >> 12) | 0x80);
            u8 midl = (u8)(((0x00000FC0 & utf32_code) >> 6)  | 0x80);
            u8 low  = (u8)((0x0000003F  & utf32_code)        | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = midh;
            dst->data[utf8_index + 2] = midl;
            dst->data[utf8_index + 3] = low;
            
            utf8_index += 4;
        }
    }
    
    dst->byteLen  = byteLen;
    dst->len      = len;
    
    return;
}

void ls_utf8FromUTF32_t(utf8 *dst, utf32 s)
{
    AssertMsg(dst, "Null destination pointer\n");
    AssertMsg(dst->data, "Destination string is not allocated\n");
    if(s.len == 0) { return; }
    
    u32 len = s.len;
    u32 byteLen = 0;
    for(s32 i = 0; i < len; i++)
    {
        if(s.data[i] <= 0x7F)        byteLen += 1;
        else if(s.data[i] <= 0x7FF)  byteLen += 2;
        else if(s.data[i] <= 0xFFFF) byteLen += 3;
        else                         byteLen += 4;
    }
    
    AssertMsg(dst->size >= byteLen, "Destination is not large enough for source string\n");
    if(dst->size < byteLen) { return; }
    
    u32 *utf32_buffer = s.data;
    
    for(u32 utf32_index = 0, utf8_index = 0; utf32_index < len; utf32_index++)
    {
        u32 utf32_code = utf32_buffer[utf32_index];
        
        AssertMsg(utf32_code <= 0x10FFFF, "UTF32 codepoint outside valid range [0x0 - 0x10FFFF]");
        
        if(utf32_code <= 0x7F)
        {
            dst->data[utf8_index] = (u8)utf32_code;
            utf8_index += 1;
        }
        else if(utf32_code <= 0x7FF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0x07C0 & base_bytes) >> 6) | 0xC0);
            u8 low  = (u8)((0x003F  & base_bytes)       | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = low;
            
            utf8_index += 2;
        }
        else if(utf32_code <= 0xFFFF)
        {
            u16 base_bytes = (u16)utf32_code;
            
            u8 high = (u8)(((0xF000 & base_bytes) >> 12) | 0xE0);
            u8 mid  = (u8)(((0x0FC0 & base_bytes) >> 6)  | 0x80);
            u8 low  = (u8)((0x003F  & base_bytes)        | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = mid;
            dst->data[utf8_index + 2] = low;
            
            utf8_index += 3;
        }
        else if(utf32_code <= 0x10FFFF)
        {
            u8 high = (u8)(((0x001C0000 & utf32_code) >> 18) | 0xF0);
            u8 midh = (u8)(((0x0003F000 & utf32_code) >> 12) | 0x80);
            u8 midl = (u8)(((0x00000FC0 & utf32_code) >> 6)  | 0x80);
            u8 low  = (u8)((0x0000003F  & utf32_code)        | 0x80);
            
            dst->data[utf8_index]     = high;
            dst->data[utf8_index + 1] = midh;
            dst->data[utf8_index + 2] = midl;
            dst->data[utf8_index + 3] = low;
            
            utf8_index += 4;
        }
    }
    
    dst->byteLen  = byteLen;
    dst->len      = len;
    
    return;
}

utf8 ls_utf8FromUTF32(const char32_t *s)
{
    AssertMsg(s, "Null literal pointer\n");
    
    if(s == NULL) { return {}; }
    
    utf8 result = {};
    ls_utf8FromUTF32_t(&result, s);
    return result;
}


//TODO: Should I try optimizing it for utf-8 directly, rather than converting?
utf8 ls_utf8FromInt(s64 x)
{
    char buff[32] = {};
    ls_itoa_t(x, buff, 32);
    
    return ls_utf8FromAscii(buff);
}

void ls_utf8FromInt_t(utf8 *s, s64 x)
{
    AssertMsg(s, "Source pointer is null");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    
    char buff[32] = {};
    s32 len = ls_itoa_t(x, buff, 32);
    
    //NOTE: Fine because ascii string lengths are equivalent to utf8 byte lengths
    if(s->size < len) { ls_utf8Free(s); }
    
    if(s->data == NULL)
    {
        *s = ls_utf8FromAscii(buff, len);
    }
    else
    {
        for(u32 i = 0; i < len; i++)
        { s->data[i] = buff[i]; }
        
        s->len     = len;
        s->byteLen = len;
    }
}

utf8 ls_utf8FromF64(f64 x)
{
    char buff[32] = {};
    u32 len = ls_ftoa_t(x, buff, 32);
    
    return ls_utf8FromAscii(buff, len);
}

void ls_utf8FromF64_t(utf8 *s, f64 x)
{
    AssertMsg(s, "Source ptr is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    
    char buff[32] = {};
    u32 len = ls_ftoa_t(x, buff, 32);
    
    //NOTE: Fine because ascii string lengths are equivalent to utf8 byte lengths
    if(s->size < len) { ls_utf8Free(s); }
    
    if(s->data == NULL)
    {
        *s = ls_utf8FromAscii(buff, len);
    }
    else
    {
        for(u32 i = 0; i < len; i++)
        { s->data[i] = buff[i]; }
        
        s->len     = len;
        s->byteLen = len;
    }
}

utf8 ls_utf8Constant(const char8_t *p)
{
    return ls_utf8Constant((const u8 *)p);
}


utf8 ls_utf8Constant(const char *p)
{
    return ls_utf8Constant((const u8 *)p);
}

utf8 ls_utf8Constant(const u8 *p)
{
    AssertMsg(p, "Null literal source string\n");
    
    s32 byteLen = 0;
    s32 len = 0;
    u8 *At = (u8 *)p;
    while(*At)
    {
        if(*At <= 0x7F)      { byteLen += 1; At += 1; }
        else if(*At <= 0xDF) { byteLen += 2; At += 2; }
        else if(*At <= 0xEF) { byteLen += 3; At += 3; }
        else if(*At <= 0xF7) { byteLen += 4; At += 4; }
        else { AssertMsg(FALSE, "Unsupported utf8 character... This should never be reached?\n"); }
        
        len += 1;
    }
    
    utf8 result = { (u8 *)p, len, byteLen, -7878 };
    return result;
}

utf8 ls_utf8Constant(const u8 *p, s32 byteLen)
{
    AssertMsg(p, "Null literal source string\n");
    
    s32 len     = ls_utf8Len((u8 *)p, byteLen);
    utf8 result = { (u8 *)p, len, byteLen, -7878 };
    return result;
}

//Manage
void ls_utf8Clear(utf8 *s)
{
    AssertMsg(s, "Null source string\n");
    AssertMsgF(s->size > 0, "Trying to clear a Non-Positive sized string: %d\n", s->size);
    
    s->len     = 0;
    s->byteLen = 0;
}

utf8 ls_utf8Copy(utf8 s)
{
    utf8 result = ls_utf8Alloc(s.byteLen);
    ls_memcpy(s.data, result.data, s.byteLen);
    result.len     = s.len;
    result.byteLen = s.byteLen;
    
    return result;
}

//OperateOn
void ls_utf8Reverse(utf8 *s)
{
    AssertMsg(FALSE, "Not Implemented yet");
}

void  ls_utf8RmSubstr(utf8 *s, u32 beginIdx, u32 endIdx)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8RmIdx(utf8 *s, u32 idx)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8RmAllNonTextChar(utf8 *s)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8TrimRight(utf8 *s, u32 numChars)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void  ls_utf8InsertSubstr(utf8 *s, utf8 toInsert, u32 insertIdx)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8InsertChar(utf8 *s, u32 c, u32 idx)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8InsertCStr(utf8 *s, char *toInsert, u32 insertIdx)
{
    AssertMsg(FALSE, "Not implemented yet");
}
void  ls_utf8InsertBuffer(utf8 *s, u8 *toInsert, u32 buffLen, u32 insertIdx)
{
    AssertMsg(FALSE, "Not implemented yet");
}

utf8 *ls_utf8Split(utf8 s, u32 *outNum, utf8 delim)
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}
utf8 *ls_utf8Split(utf8 s, u32 *outNum, const u8 *delim)
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}
utf8 *ls_utf8Split(utf8 s, u32 *outNum, u32 character)
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}

s32 ls_utf8LeftFind(utf8 s, u8 c[4])
{
    AssertMsg(s.data, "UTF8 string data is null.\n");
    AssertMsg(c[0] <= 0xF7, "UTF8 first byte is out of range [0x0 - 0xF7]\n");
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    
    s8 codepointLen = 0;
    if     (c[0] <= 0x7F) codepointLen = 1;
    else if(c[0] <= 0xDF) codepointLen = 2;
    else if(c[0] <= 0xEF) codepointLen = 3;
    else                  codepointLen = 4;
    
    u8 *At = s.data;
    s32 i  = 0;
    while(i < s.len)
    {
        if(*At == c[0])
        {
            if(ls_memcmp(At, c, codepointLen) == TRUE) { return i; }
        }
        
        if     (*At <= 0x7F) { i += 1; At += 1; }
        else if(*At <= 0xDF) { i += 2; At += 2; }
        else if(*At <= 0xEF) { i += 3; At += 3; }
        else                 { i += 4; At += 4; }
    }
    
    return -1;
}

s32 ls_utf8LeftFind(utf8 s, s32 offset, u8 c[4])
{
    AssertMsg(s.data, "UTF8 string data is null.\n");
    AssertMsg(c[0] <= 0xF7, "UTF8 first byte is out of range [0x0 - 0xF7]\n");
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    
    s8 codepointLen = 0;
    if     (c[0] <= 0x7F) codepointLen = 1;
    else if(c[0] <= 0xDF) codepointLen = 2;
    else if(c[0] <= 0xEF) codepointLen = 3;
    else                  codepointLen = 4;
    
    u8 *At = s.data + offset;
    s32 i  = 0;
    while(i < s.len)
    {
        if(*At == c[0])
        {
            if(ls_memcmp(At, c, codepointLen) == TRUE) { return i; }
        }
        
        if     (*At <= 0x7F) { i += 1; At += 1; }
        else if(*At <= 0xDF) { i += 2; At += 2; }
        else if(*At <= 0xEF) { i += 3; At += 3; }
        else                 { i += 4; At += 4; }
    }
    
    return -1;
}

s32 ls_utf8RightFind(utf8 s, u8 c[4])
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}

s32 ls_utf8RightFind(utf8 s, s32 offset, u8 c[4])
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}

s32 ls_utf8CountOccurrences(utf8 s, u8 c[4])
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}

b32 ls_utf8Contains(utf8 haystack, utf8 needle)
{
    AssertMsg(haystack.data, "Haystack data is null\n");
    AssertMsg(needle.data, "Needle data is null\n");
    
    if(haystack.data == NULL) { return FALSE; }
    if(needle.data   == NULL) { return FALSE; }
    if(haystack.len  == 0)    { return FALSE; }
    if(needle.len    == 0)    { return FALSE; }
    
    u8 *At    = haystack.data;
    u8 *Check = needle.data;
    for(u32 i = 0; i < haystack.byteLen; i++)
    {
        if((haystack.byteLen - i) < needle.byteLen) { return FALSE; }
        
        if(At[i] == Check[0])
        {
            if(ls_memcmp(At + i, Check, needle.byteLen) == TRUE) { return TRUE; }
        }
    }
    
    return FALSE;
}

void ls_utf8ToLower(utf8 *out, utf8 source)
{
    AssertMsg(out, "Null out pointer\n");
    AssertMsg(out->data, "Out data is null\n");
    AssertMsg(out->size >= source.byteLen, "Out is not long enough\n");
    
    if(out->data   == NULL) { return; }
    if(source.data == NULL) { return; }
    if(source.len  == 0)    { return; }
    
    for(u32 i = 0; i < source.len;)
    {
        u8 c0 = source.data[i];
        
        if(c0 <= 0x7F)
        {
            if(c0 >= 'A' && c0 <= 'Z') { out->data[i] = c0 + 0x20; }
            else                       { out->data[i] = c0;}
            
            i += 1;
        }
        else if(c0 <= 0xDF)
        { 
            out->data[i] = c0;
            out->data[i+1] = source.data[i+1];
            i += 2;
        }
        else if(c0 <= 0xEF)
        { 
            out->data[i] = c0;
            out->data[i+1] = source.data[i+1];
            out->data[i+2] = source.data[i+2];
            i += 3;
        }
        else if(c0 <= 0xF7)
        {
            out->data[i] = c0;
            out->data[i+1] = source.data[i+1];
            out->data[i+2] = source.data[i+2];
            out->data[i+3] = source.data[i+3];
            i += 4;
        }
    }
    
    out->byteLen = source.byteLen;
    out->len     = source.len;
    
    return;
}

//Merge
utf8 ls_utf8Concat(utf8 s1, utf8 s2)
{
    AssertMsg(FALSE, "Not implemented yet");
    return {};
}

void ls_utf8ConcatOn(utf8 s1, utf8 s2, utf8 *out)
{
    AssertMsg(FALSE, "Not implemented yet");
}

utf8 ls_utf8CatChar(utf8 s1, u32 c)
{
    AssertMsg(FALSE, "Not implemented yet");
    return {};
}

utf8 ls_utf8CatCStr(utf8 s1, char *c)
{
    AssertMsg(FALSE, "Not implemented yet");
    return {};
}

void ls_utf8Prepend(utf8 *s1, utf8 s2)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void ls_utf8PrependChar(utf8 *s, u32 c)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void ls_utf8PrependCStr(utf8 *s, char *c)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void ls_utf8Append(utf8 *s1, utf8 s2)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void ls_utf8AppendChar(utf8 *s1, u32 c)
{
    AssertMsg(s1, "utf8 pointer is null");
    
    if(c < 128)
    {
        if(s1->byteLen + 1 > s1->size)
        {
            AssertMsg(FALSE, "Grow utf8 string not implemented yet\n");
        }
        
        s1->data[s1->byteLen] = (u8)c;
        s1->byteLen += 1;
        s1->len += 1;
    }
    else
    {
        AssertMsg(FALSE, "Not implemented yet for Non-Ascii characters\n");
    }
}

void ls_utf8AppendCStr(utf8 *s1, char *c)
{
    AssertMsg(s1, "utf8 pointer is null\n");
    AssertMsg(c,  "c string pointer is null\n");
    
    s32 cLen = ls_len(c);
    
    if(s1->byteLen + cLen > s1->size)
    {
        AssertMsg(FALSE, "Grow utf8 string not implemented yet\n");
    }
    
    ls_memcpy(c, s1->data + s1->byteLen, cLen);
    s1->byteLen += cLen;
    s1->len     += cLen;
}

void ls_utf8AppendNCStr(utf8 *s1, char *c, u32 len)
{
    AssertMsg(FALSE, "Not implemented yet");
}

void ls_utf8AppendBuffer(utf8 *s1, u32 *buff, u32 buffLen)
{
    AssertMsg(FALSE, "Not implemented yet");
}

// Convert
s32 ls_utf8ToAscii_t(utf8 *s, char *buff, u32 buffMaxLen)
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}
s64 ls_utf8ToInt(utf8 s)
{
    AssertMsg(FALSE, "Not implemented yet");
    return 0;
}

b32 ls_utf8IsWhitespace(u32 c)
{
    if((c == (u32)' ') || (c == (u32)'\n') || (c == (u32)'\r') || (c == (u32)'\t') || (c == (u32)'\v'))
    { return TRUE; }
    
    return FALSE;
}

b32 ls_utf8IsNumber(u32 c)
{
    if(c >= (u32)'0' && c <= (u32)'9') { return TRUE; }
    return FALSE;
}



//-----------------------------//
//    UTF32 UNICODE STRINGS    //
//-----------------------------//

//------------------//
//  Create/Destroy  //

utf32 ls_utf32Alloc(s32 size)
{
    AssertMsgF(size > 0, "Non-Positive size when allocating: %d\n", size);
    
    u32 *data = (u32 *)ls_alloc(sizeof(u32)*size);
    utf32 Result = {data, 0, size};
    
    return Result;
}

utf32 *ls_utf32AllocArr(u32 numStrings, s32 initialSize)
{
    AssertMsgF(initialSize >= 0, "Non-Positive initial size: %d\n", initialSize);
    
    if(numStrings == 0) { return 0x0; }
    
    utf32 *s = (utf32 *)ls_alloc(sizeof(utf32)*numStrings);
    if(initialSize > 0)
    {
        for(u32 i = 0; i < numStrings; i++) { s[i] = ls_utf32Alloc(initialSize); }
    }
    
    return s;
}

void ls_utf32Free(utf32 *s)
{
    AssertMsg(s, "Null string pointer\n");
    AssertMsgF(s->size >= 0, "Trying to free Non-Positive sized string: %d\n", s->size);
    
    ls_free(s->data);
    s->data = 0;
    s->len  = 0;
    s->size = 0;
}

void ls_utf32FreeArr(utf32 *s, s32 arrSize)
{
    AssertMsg(s, "Null string array pointer\n");
    AssertMsgF(arrSize > 0, "Non-Positive number of elements in array: %d\n", arrSize);
    
    for(s32 i = 0; i < arrSize; i++)
    { ls_utf32Free(&s[i]);}
    
    ls_free(s);
}

constexpr utf32 operator""_W(const char32_t *lit, size_t s) { return ls_utf32Constant(lit); }

b32 ls_utf32AreEqual(utf32 a, utf32 b)
{
    AssertMsg(a.data, "First string's data pointer is null\n");
    AssertMsg(b.data, "Second string's data pointer is null\n");
    
    if(a.len != b.len)   { return FALSE; }
    if(a.data == b.data) { return TRUE; }
    
    return ls_memcmp(a.data, b.data, a.len*sizeof(u32));
}

b32 ls_utf32AreEqualUpTo(utf32 a, utf32 b, s32 len)
{
    AssertMsg(a.data, "First string's data pointer is null\n");
    AssertMsg(b.data, "Second string's data pointer is null\n");
    
    if(a.len < len)      { return FALSE; }
    if(b.len < len)      { return FALSE; }
    if(a.data == b.data) { return TRUE; }
    
    return ls_memcmp(a.data, b.data, len*sizeof(u32));
}

b32 ls_utf32AsciiAreEqual(utf32 a, string b)
{
    AssertMsg(a.data, "First string's data pointer is null\n");
    AssertMsg(b.data, "Second string's data pointer is null\n");
    
    if(a.len != b.len)   { return FALSE; }
    
    for(u32 i = 0; i < a.len; i++) {
        if(a.data[i] != (u32)(b.data[i])) { return FALSE; }
    }
    
    return TRUE;
}

s32 ls_utf32FirstEqual(utf32 a, utf32 *set, s32 count)
{
    AssertMsg(set, "Array pointer to be checked is null\n");
    AssertMsg(count > 0, "Invalid number of utf32 strings in array\n");
    
    for(s32 i = 0; i < count; i++)
    { if(ls_utf32AreEqual(a, set[i])) { return i; } }
    
    return -1;
}

void ls_utf32Set(utf32 *toSet, utf32 source)
{
    AssertMsg(toSet, "String to be set pointer is null\n");
    AssertMsgF(toSet->size >= 0, "Trying to write to a Non-Positive sized string: %d\n", toSet->size);
    
    if(toSet->size < source.len) { ls_utf32Free(toSet); }
    
    if(!toSet->data)
    { 
        u32 allocSize = (16 + source.len);
        
        toSet->data = (u32 *)ls_alloc(allocSize*sizeof(u32));
        toSet->size = allocSize;
    }
    
    if(source.len == 0) { toSet->len = 0; return; }
    
    ls_memcpy(source.data, toSet->data, source.len*sizeof(u32));
    toSet->len = source.len;
}

s32 ls_utf32Len(const char32_t *s)
{
    AssertMsg(s, "Null source literal string\n");
    
    s32 len = 0;
    u32 *At = (u32 *)s;
    while(*At) { len += 1; At += 1; }
    return len;
}


utf32 ls_utf32FromAscii(char *s, s32 len)
{
    AssertMsg(s, "Null source literal string\n");
    AssertMsg(len > 0, "Non-Positive len\n");
    
    utf32 Result = ls_utf32Alloc(len);
    for(u32 i = 0; i < len; i++) { Result.data[i] = (u32)s[i]; }
    Result.len = len;
    
    return Result;
}

utf32 ls_utf32FromAscii(char *s)
{
    AssertMsg(s, "Null source literal string\n");
    
    s32 len = ls_len(s);
    return ls_utf32FromAscii(s, len);
}

void ls_utf32FromAscii_t(utf32 *dst, char *src, s32 len)
{
    AssertMsg(src, "Null source literal c string\n");
    AssertMsg(dst, "Null destination string\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(len > 0, "Non-Positive len\n");
    
    for(u32 i = 0; i < len; i++) { dst->data[i] = (u32)src[i]; }
    dst->len = len;
}

void ls_utf32FromAscii_t(utf32 *dst, char *src)
{
    AssertMsg(src, "Null source literal c string\n");
    AssertMsg(dst, "Null destination string\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    
    u32 len = ls_len(src);
    ls_utf32FromAscii_t(dst, src, len);
}

void ls_utf32FromUTF8_t(utf32 *dst, u8 *src, s32 len)
{
    AssertMsg(dst, "Destination pointer is null\n");
    AssertMsg(src, "Source pointer is null\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(len > 0, "Non-Positive len\n");
    AssertMsg(dst->size >= len, "Destination string is not big enough\n");
    
    dst->len = len;
    
    u8 *At = src;
    for(u32 utf32_index = 0, utf8_index = 0; utf32_index < len; utf32_index++)
    {
        u8 c0 = At[utf8_index];
        
        AssertMsg(c0 <= 0xF7, "UTF8 first byte is out of range [0x0 - 0xF7]\n");
        
        if(c0 <= 0x7F)
        {
            dst->data[utf32_index] = (u32)c0;
            utf8_index += 1;
        }
        else if(c0 <= 0xDF)
        {
            u8 c1 = At[utf8_index + 1];
            
            u16 byte1 = u16(c0 & 0x1F);
            u16 byte2 = u16(c1 & 0x3F);
            
            u32 codepoint = u32((byte1 << 6) | byte2);
            
            dst->data[utf32_index] = codepoint;
            utf8_index += 2;
        }
        else if(c0 <= 0xEF)
        {
            u8 c1 = At[utf8_index + 1];
            u8 c2 = At[utf8_index + 2];
            
            u16 byte1 = u16(c0 & 0x0F);
            u16 byte2 = u16(c1 & 0x3F);
            u16 byte3 = u16(c2 & 0x3F);
            
            u32 codepoint = u32((byte1 << 12) | (byte2 << 6) | byte3);
            
            dst->data[utf32_index] = codepoint;
            utf8_index += 3;
        }
        else if(c0 <= 0xF7)
        {
            u8 c1 = At[utf8_index + 1];
            u8 c2 = At[utf8_index + 2];
            u8 c3 = At[utf8_index + 3];
            
            u16 byte1 = u16(c0 & 0x07);
            u16 byte2 = u16(c1 & 0x3F);
            u16 byte3 = u16(c2 & 0x3F);
            u16 byte4 = u16(c3 & 0x3F);
            
            u32 codepoint = u32((byte1 << 18) | (byte2 << 12) | (byte3 << 6) | byte4);
            
            dst->data[utf32_index] = codepoint;
            utf8_index += 4;
        }
    }
}

utf32 ls_utf32FromUTF8(u8 *src, s32 byteLen)
{
    AssertMsg(src, "Null source pointer\n");
    AssertMsg(byteLen > 0, "Non-Positive bytelen\n");
    
    s32 len = ls_utf8Len(src, byteLen);
    utf32 result = ls_utf32Alloc(len);
    
    ls_utf32FromUTF8_t(&result, src, len);
    
    return result;
    
}

utf32 ls_utf32FromUTF32(const char32_t *s)
{
    AssertMsg(s, "Null source literal string\n");
    
    if(s == NULL) { return {}; }
    
    s32 len = 0;
    u32 *At = (u32 *)s;
    while(*At) { len += 1; At += 1; }
    
    utf32 Result = ls_utf32Alloc(len);
    ls_memcpy((void *)s, Result.data, len*sizeof(u32));
    Result.len = len;
    
    return Result;
}

void ls_utf32FromUTF32_t(utf32 *dst, const char32_t *s)
{
    AssertMsg(dst, "Destination utf32 pointer is null\n");
    AssertMsgF(dst->size > 0, "Trying to write to a Non-Positive sized string: %d\n", dst->size);
    AssertMsg(s, "Null source literal string\n");
    
    if(s == NULL) { return; }
    
    u32 len = 0;
    u32 *At = (u32 *)s;
    while(*At) { len += 1; At += 1; }
    
    if(dst->data == 0)
    {
        u32 allocSize = (16 + len);
        
        dst->data = (u32 *)ls_alloc(allocSize*sizeof(u32));
        dst->size = allocSize;
    }
    
    if(dst->size < len)
    {
        u32 growAmount = (dst->size - len + 32);
        ls_utf32Grow(dst, growAmount);
    }
    
    ls_memcpy((void *)s, dst->data, len*sizeof(u32));
    dst->len = len;
    
    return;
}

constexpr utf32 ls_utf32Constant(const char32_t *p)
{
    AssertMsg(p, "Null source literal string\n");
    
    s32 len = 0;
    u32 *At = (u32 *)p;
    while(*At != 0) { len += 1; At += 1; }
    
    utf32 Result = { (u32 *)p, len, -7878 };
    return Result;
}

//TODO: This function is fucking stupid. Why am I looking for the character, rathen than just fucking passing it?
u32 ls_utf32CharFromUtf8(utf8 src, s32 characterIndex)
{
    AssertMsg(characterIndex >= 0, "Negative character index\n");
    
    u8 *At = src.data;
    
    u32 utf8_index    = 0;
    u32 utf8_char_idx = 0;
    while(utf8_index < src.byteLen)
    {
        //TODO: We are assuming a well formed utf8 string... Need error detection.
        u8 c0 = At[utf8_index];
        
        if(utf8_char_idx == characterIndex)
        {
            if(c0 <= 0x7F)
            {
                return (u32)c0;
            }
            else if(c0 <= 0xDF)
            {
                u8 c1 = At[utf8_index + 1];
                
                u16 byte1 = u16(c0 & 0x1F);
                u16 byte2 = u16(c1 & 0x3F);
                
                u32 codepoint = u32((byte1 << 6) | byte2);
                return codepoint;
            }
            else if(c0 <= 0xEF)
            {
                u8 c1 = At[utf8_index + 1];
                u8 c2 = At[utf8_index + 2];
                
                u16 byte1 = u16(c0 & 0x0F);
                u16 byte2 = u16(c1 & 0x3F);
                u16 byte3 = u16(c2 & 0x3F);
                
                u32 codepoint = u32((byte1 << 12) | (byte2 << 6) | byte3);
                return codepoint;
            }
            else if(c0 <= 0xF7)
            {
                u8 c1 = At[utf8_index + 1];
                u8 c2 = At[utf8_index + 2];
                u8 c3 = At[utf8_index + 3];
                
                u16 byte1 = u16(c0 & 0x07);
                u16 byte2 = u16(c1 & 0x3F);
                u16 byte3 = u16(c2 & 0x3F);
                u16 byte4 = u16(c3 & 0x3F);
                
                u32 codepoint = u32((byte1 << 18) | (byte2 << 12) | (byte3 << 6) | byte4);
                return codepoint;
            }
        }
        
        if(c0 <= 0x7F)      { utf8_index += 1; }
        else if(c0 <= 0xDF) { utf8_index += 2; }
        else if(c0 <= 0xEF) { utf8_index += 3; }
        else if(c0 <= 0xF7) { utf8_index += 4; }
        
        utf8_char_idx += 1;
    }
    
    AssertMsg(FALSE, "The utf8 codepoint could not be converted"
              "(The index was never found?). Need better error detection.\n");
    return 0;
}

//  Create/Destroy  //
//------------------//

//------------------//
//     Manage       //


void ls_utf32Clear(utf32 *s)
{ 
    AssertMsg(s, "Null source string pointer\n");
    AssertMsgF(s->size > 0, "Trying to clear a Non-Positive sized string: %d\n", s->size);
    s->len = 0;
}

utf32 ls_utf32Copy(utf32 s)
{
    utf32 Result = ls_utf32Alloc(s.len);
    ls_memcpy(s.data, Result.data, s.len*4);
    Result.len = s.len;
    
    return Result;
}

void ls_utf32Copy_t(utf32 s, utf32 *out)
{
    AssertMsg(out, "Output string pointer is null\n");
    AssertMsg(out->data, "Output string data is un-allocated\n");
    AssertMsg(out->size > s.len, "Output string is too small to fit original\n");
    
    ls_memcpy(s.data, out->data, s.len*4);
    out->len = s.len;
}

void ls_utf32NCopy(utf32 src, utf32 *dst, s32 size)
{
    AssertMsg(dst, "Null destination string pointer\n");
    AssertMsg(dst->size > 0, "Trying to write to a Non-Positive sized string.\n");
    AssertMsg(size >= 0, "Negative copy size passed\n");
    
    u32 copySize = size;
    if(size > src.len) { copySize = src.len; }
    
    if(dst->data == NULL) { *dst = ls_utf32Alloc(copySize); }
    
    if(dst->size < src.len)
    {
        u32 growAmount = (dst->size - src.len + 32);
        ls_utf32Grow(dst, growAmount);
    }
    
    ls_memcpy(src.data, dst->data, copySize*4);
    dst->len = copySize;
}

utf32 ls_utf32CopySubstr(utf32 s, u32 beginIdx, u32 _endIdx)
{
    u32 endIdx = 0;
    if(_endIdx == (u32)-1) { endIdx = s.len-1; }
    else { endIdx = _endIdx; }
    
    if((beginIdx < 0 || beginIdx >= s.size) ||
       (endIdx < 0 || endIdx >= s.size) ||
       (endIdx - beginIdx >= s.size))
    { utf32 error = {}; return error; }
    
    utf32 result = ls_utf32Alloc((endIdx - beginIdx) + 1);
    
    ls_memcpy(s.data + beginIdx, result.data, result.size*4);
    result.len = ((endIdx - beginIdx) + 1);
    
    return result;
}

//      Manage      //
//------------------//

//------------------//
//     OperateOn    //

void ls_utf32Reverse(utf32 *s)
{
    AssertMsg(s, "Null source string\n");
    AssertMsgF(s->size > 0, "Trying to reverse a Non-Positive sized string: %d\n", s->size);
    
    u32 *Begin = s->data;
    u32 *End   = s->data + s->len;
    u32 temp = 0;
    //NOTE: utf32 doesn't have null-terminators if(*End == 0) { End--; } Ignore null-terminator
    while (Begin < End)
    {
        temp   = *Begin;
        *Begin = *End;
        *End   = temp;
        
        Begin += 1;
        End   -= 1;
    }
}

//TODO: Call this RmRange
void ls_utf32RmSubstr(utf32 *s, u32 beginIdx, u32 endIdx)
{
    AssertMsg(s, "Source pointer is null\n");
    AssertMsgF(s->size > 0, "Trying to remove substring of a Non-Positive sized string: %d\n", s->size);
    AssertMsg(beginIdx < s->len, "Begin Index is out of bounds. Larger than string length\n");
    AssertMsg(endIdx   < s->len, "End Index is out of bounds. Larger than string length\n");
    AssertMsg((endIdx - beginIdx) < s->len, "Index Range is larger than string length. How??\n");
    
    if(s->data == NULL) { return; }
    if(s->len  == 0)    { return; }
    
    u32 remove  = ((endIdx - beginIdx) + 1);
    u32 copyLen = s->len - (endIdx + 1);
    
    //NOTE: This is to avoid memcpying overlapping memory regions
    u32 *tempMem = (u32 *)ls_alloc((copyLen+1)*4);
    
    ls_memcpy((void *)(s->data + endIdx + 1), tempMem, copyLen*4);
    ls_memcpy(tempMem, (void *)(s->data + beginIdx), copyLen*4);
    
    ls_free(tempMem);
    
    s->len -= remove;
    
    return;
}

b32 ls_utf32RmSubstr(utf32 *s, utf32 toRm)
{
    AssertMsg(s, "Source pointer is null\n");
    AssertMsgF(s->size > 0, "Trying to remove substring of a Non-Positive sized string: %d\n", s->size);
    
    if(toRm.len > s->len) { return FALSE; }
    if(toRm.len == 0) { return FALSE; }
    
    s32 foundIdx = ls_utf32LeftFind(*s, toRm);
    if(foundIdx == -1) { return FALSE; }
    
    ls_utf32RmSubstr(s, foundIdx, foundIdx + (toRm.len-1));
    return TRUE;
}

b32 ls_utf32RmSubstrInList(utf32 *s, utf32 *toRm, s32 count)
{
    AssertMsg(s, "Source pointer is null\n");
    AssertMsgF(s->size > 0, "Trying to remove substring of a Non-Positive sized string: %d\n", s->size);
    AssertMsg(toRm, "To Remove Array pointer is null\n");
    AssertMsgF(count > 0 && count < 10000000, "Count has an invalid or strangely large value: %d\n", count);
    
    b32 hasRemoved = FALSE;
    
    for(s32 i = 0; i < count; i++)
    { hasRemoved |= ls_utf32RmSubstr(s, toRm[i]); }
    
    return hasRemoved;
}


void ls_utf32RmIdx(utf32 *s, u32 idx)
{ ls_utf32RmSubstr(s, idx, idx); }


void ls_utf32TrimRight(utf32 *s, u32 numChars)
{ 
    AssertMsg(s, "Null utf32 pointer passed\n");
    AssertMsg(s->data, "Null source string data\n");
    AssertMsgF(s->size > 0, "Trying to trim a Non-Positive sized string: %d\n", s->size);
    AssertMsg(s->len > 0, "Trying to trim an empty utf32\n");
    AssertMsg(numChars <= s->len, "Trying to trim more than the string length.\n");
    
    if(s->data == NULL)       { return; }
    if(s->len - numChars < 0) { return; }
    
    s->len -= numChars; 
}

void ls_utf32InsertSubstr(utf32 *s, utf32 toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null utf32 pointer passed\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    AssertMsg(toInsert.data, "Null toInsert data ptr\n");
    AssertMsg(insertIdx <= s->len, "Insertion index past utf32 length\n");
    
    if(s->len + toInsert.len > s->size)
    {
        u32 growSize = ((s->len + toInsert.len) - s->size) + 32;
        ls_utf32Grow(s, growSize);
    }
    
    //TODO:Make a better reverse memcpy for non byte-boundary blocks.
    s32 moveBytes = (s->len - insertIdx)*sizeof(u32);
    u32 *tempMem = (u32 *)ls_alloc(moveBytes + 1);
    
    ls_memcpy(s->data + insertIdx, tempMem, moveBytes);
    ls_memcpy(tempMem, s->data + insertIdx + toInsert.len, moveBytes);
    
    ls_free(tempMem);
    
    ls_memcpy(toInsert.data, s->data + insertIdx, toInsert.len*sizeof(u32));
    
    s->len += toInsert.len;
}

void ls_utf32InsertSubstr(utf32 *s, const char32_t *toInsert, s32 insertIdx)
{
    AssertMsg(s, "Null utf32 pointer passed\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n");
    AssertMsg(toInsert, "String pointer passed is null\n");
    AssertMsg(insertIdx >= 0, "Insertion index is negative\n");
    AssertMsg(insertIdx <= s->len, "Insertion index past utf32 length\n");
    
    s32 len = ls_utf32Len(toInsert);
    
    if(s->len + len > s->size)
    {
        u32 growSize = ((s->len + len) - s->size) + 32;
        ls_utf32Grow(s, growSize);
    }
    
    //NOTE: Must be done passing through a temporary buffer because memory will overlap otherwise.
    u32 tmpBuffer[1024] = {};
    ls_memcpy(s->data + insertIdx, tmpBuffer, (s->len - insertIdx)*sizeof(u32));
    ls_memcpy(tmpBuffer, s->data + insertIdx + len, (s->len - insertIdx)*sizeof(u32));
    ls_memcpy((void *)toInsert, s->data + insertIdx, len*sizeof(u32));
    s->len += len;
}

void ls_utf32InsertChar(utf32 *s, u32 c, u32 idx)
{
    utf32 insertString = {&c, 1, 1};
    ls_utf32InsertSubstr(s, insertString, idx);
}

void ls_utf32InsertCStr(utf32 *s, const char *toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null utf32 pointer passed\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n");
    AssertMsg(toInsert, "C String pointer passed is null\n");
    AssertMsg(insertIdx <= s->len, "Insertion index past utf32 length\n");
    
    u32 len = ls_len((char *)toInsert);
    
    if(s->len + len > s->size)
    {
        u32 growSize = ((s->len + len) - s->size) + 32;
        ls_utf32Grow(s, growSize);
    }
    
    //NOTE: Must be done passing through a temporary buffer because memory will overlap otherwise.
    u32 tmpBuffer[1024] = {};
    ls_memcpy(s->data + insertIdx, tmpBuffer, (s->len - insertIdx)*sizeof(u32));
    ls_memcpy(tmpBuffer, s->data + insertIdx + len, (s->len - insertIdx)*sizeof(u32));
    
    u32 *At = s->data + insertIdx;
    for(u32 i = 0; i < len; i++) { At[i] = (u32)toInsert[i]; }
    s->len += len;
}

void ls_utf32InsertBuffer(utf32 *s, u32 *toInsert, s32 buffLen, u32 insertIdx)
{
    AssertMsg(s, "Dest string pointer is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    AssertMsg(toInsert, "To Insert string pointer is null\n");
    
    if(buffLen <= 0) { return; }
    
    utf32 insertString = {toInsert, buffLen, buffLen};
    ls_utf32InsertSubstr(s, insertString, insertIdx);
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, utf32 delim)
{
    AssertMsg(s.data, "Source data pointer is null\n");
    AssertMsg(outNum, "Output parameter outNum is null\n");
    
    u32 delimCount = 0;
    
    u32 *At = s.data;
    while(At < (s.data + s.len))
    {
        utf32 test = { At, delim.len, delim.len };
        if(ls_utf32AreEqual(test, delim) == TRUE)
        { 
            delimCount += 1;
            
            while(ls_utf32AreEqual(test, delim) == TRUE) {
                At += 1; 
                test.data = At;
            }
        }
        
        At += 1;
    }
    
    utf32 *Result = ls_utf32AllocArr(delimCount+1, 16);
    u32 idx = 0;
    
    
    u32 *BeginString = s.data;
    At = s.data;
    while(At < (s.data + s.len))
    {
        utf32 test = { At, delim.len, delim.len };
        if(ls_utf32AreEqual(test, delim) == TRUE)
        {
            utf32 toCopy = { BeginString, (s32)(At - BeginString), (s32)(At - BeginString)};
            ls_utf32Set(Result + idx, toCopy);
            idx += 1;
            
            while(ls_utf32AreEqual(test, delim) == TRUE) {
                At += 1; 
                test.data = At; 
            }
            
            BeginString = At;
        }
        
        At += 1;
    }
    
    if(BeginString != At)
    {
        utf32 toCopy = { BeginString, (s32)(At - BeginString), (s32)(At - BeginString)};
        ls_utf32Set(Result + idx, toCopy);
        idx += 1;
    }
    
    *outNum = idx;
    
    return Result;
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, const char32_t *a)
{
    utf32 delim = ls_utf32Constant(a);
    return ls_utf32Split(s, outNum, delim);
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, u32 c)
{
    utf32 delim = {&c, 1, 1};
    return ls_utf32Split(s, outNum, delim);
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, char32_t c)
{
    utf32 delim = {(u32 *)(&c), 1, 1};
    return ls_utf32Split(s, outNum, delim);
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, char c)
{
    u32 ch = (u32)c;
    return ls_utf32Split(s, outNum, ch);
}

utf32 *ls_utf32Split(utf32 s, u32 *outNum, const char *c)
{
    //TODO: Maybe use FromAscii_t
    utf32 delim = ls_utf32FromAscii((char *)c);
    utf32 *result = ls_utf32Split(s, outNum, delim);
    
    ls_utf32Free(&delim);
    return result;
}

utf32 *ls_utf32SeparateByNumber(utf32 s, u32 *outNum)
{
    AssertMsg(s.data, "Source data pointer is null\n");
    AssertMsg(outNum, "Output parameter outNum is null\n");
    
    u32 count = 0;
    s32 len = 0;
    u32 *At = s.data;
    while(At < (s.data + s.len))
    {
        if(ls_utf32IsNumber(*At) == TRUE)
        { 
            if(len > 0) { count += 1; len = 0; }
            
            while(ls_utf32IsNumber(*At) == TRUE)
            {
                if(At+1 >= (s.data + s.len)) { break; }
                At += 1;
            }
            
            count += 1;
        }
        
        if(At+1 >= (s.data + s.len)) { break; }
        At  += 1;
        len += 1;
    }
    
    if(len > 0) { count += 1; }
    
    utf32 *Result = ls_utf32AllocArr(count, 16);
    u32 idx = 0;
    
    u32 *BeginString = s.data;
    len = 0;
    At = s.data;
    while(At < (s.data + s.len))
    {
        if(ls_utf32IsNumber(*At) == TRUE)
        {
            if(len > 0)
            {
                utf32 nonNumber = { BeginString, len, len};
                ls_utf32Set(Result + idx, nonNumber);
                idx += 1;
                len = 0; 
            }
            
            BeginString = At;
            while(ls_utf32IsNumber(*At) == TRUE)
            {
                if(At+1 > (s.data + s.len)) { break; }
                At += 1;
            }
            
            utf32 number = { BeginString, (s32)(At - BeginString), (s32)(At - BeginString)};
            ls_utf32Set(Result + idx, number);
            idx += 1;
            
            BeginString = At;
        }
        
        if(At+1 >= (s.data + s.len)) { break; }
        At  += 1;
        len += 1;
    }
    
    if(len > 0)
    {
        utf32 nonNumber = { BeginString, len+1, len+1};
        ls_utf32Set(Result + idx, nonNumber);
        idx += 1;
    }
    
    *outNum = idx;
    
    return Result;
}


utf32 *ls_utf32BreakBySpaceUntilDelimiter(utf32 s, u32 delimiter, u32 *numOfStrings)
{
    AssertMsg(FALSE, "Not implmented\n");
    utf32 *Result = 0;
    return Result;
    
#if 0
    utf32 *Result = 0;
    utf32 buff[256] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 256);
        
        if (*At == delimiter)
        {
            if(*(At + 1) == ' ') {done++;}
            done++;
            break;
        }
        
        if (*At == ' ')
        {
            
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        
    } while (*At);
    
    Result = (utf32 *)ls_alloc(sizeof(utf32)*buffIdx);
    ls_memcpy(buff, Result, sizeof(utf32)*buffIdx);
    if(numOfStrings) { *numOfStrings = buffIdx; }
    
    return Result;
#endif
}


s32 ls_utf32LeftFind(utf32 s, s32 off, utf32 needle)
{
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Negative offset.\n"); 
    AssertMsg(needle.data, "Needle data is null.\n");
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At    = s.data + off;
    s32 offset = off;
    u32 c      = needle.data[0];
    while (At != (s.data + s.len))
    { 
        //TODO: Maybe integrate this better in the while condition?
        if(At + needle.len > (s.data + s.len)) { return -1; }
        
        if(*At == c) {
            if(needle.len == 1) { return offset; }
            if(ls_memcmp(At, needle.data, needle.len*sizeof(u32))) { return offset; }
        }
        At++; offset++;
    }
    
    return -1;
}

s32 ls_utf32LeftFind(utf32 s, utf32 needle)
{ return ls_utf32LeftFind(s, 0, needle); }

s32 ls_utf32LeftFind(utf32 s, s32 off, u32 c)
{ return ls_utf32LeftFind(s, off, utf32({&c, 1, 1})); }

s32 ls_utf32LeftFind(utf32 s, u32 c)
{ return ls_utf32LeftFind(s, 0, c); }

s32 ls_utf32LeftFindAny(utf32 s, utf32 *needles, s32 count)
{
    s32 result = -1;
    for(s32 i = 0; i < count; i++)
    {
        if((result = ls_utf32LeftFind(s, 0, needles[i])) != -1) { return result; }
    }
    
    return -1;
}

//TODO: This doesn't seem worth it
s32 ls_utf32LeftFind(utf32 s, s32 off, UTF32FindProc proc)
{
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Negative offset.\n"); 
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At    = s.data + off;
    s32 offset = off;
    while (At != (s.data + s.len))
    { 
        //TODO: Maybe integrate this better in the while condition?
        if(At + 1 > (s.data + s.len)) { return -1; }
        
        if(proc(*At)) { return offset; }
        At++; offset++;
    }
    
    return -1;
}

s32 ls_utf32LeftFindNumber(utf32 s, s32 off)
{
    return ls_utf32LeftFind(s, off, ls_utf32IsNumber);
#if 0
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Negative offset.\n"); 
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At    = s.data + off;
    s32 offset = off;
    while (At != (s.data + s.len))
    { 
        //TODO: Maybe integrate this better in the while condition?
        if(At + 1 > (s.data + s.len)) { return -1; }
        
        if(ls_utf32IsNumber(*At)) { return offset; }
        At++; offset++;
    }
    
    return -1;
#endif
}

s32 ls_utf32LeftFindNotNumber(utf32 s, s32 off)
{
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Negative offset.\n"); 
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At    = s.data + off;
    s32 offset = off;
    while (At != (s.data + s.len))
    { 
        //TODO: Maybe integrate this better in the while condition?
        if(At + 1 > (s.data + s.len)) { return -1; }
        
        if(!ls_utf32IsNumber(*At)) { return offset; }
        At++; offset++;
    }
    
    return -1;
}

s32 ls_utf32LeftFindNumber(utf32 s)
{ return ls_utf32LeftFindNumber(s, 0); }

//NOTE: ??? Offset is suuuper strange here?? Shouldn't it go from the end towards the beginning??
s32 ls_utf32RightFind(utf32 s, s32 off, u32 c)
{
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Offset is negative.\n");
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At = s.data + off;
    s32 offset = off;
    
    while(offset >= 0)
    {
        if(*At == c) { return offset; }
        At--; offset--;
    }
    
    return -1;
}

s32 ls_utf32RightFind(utf32 s, u32 c)
{ return ls_utf32RightFind(s, 0, c); }

s32 ls_utf32RightFindNumber(utf32 s, s32 off)
{
    AssertMsg(s.data, "Source data is null.\n");
    AssertMsg(off >= 0, "Negative offset.\n"); 
    
    if(s.data == NULL) { return -1; }
    if(s.len  == 0)    { return -1; }
    if(off >= s.len)   { return -1; }
    if(off < 0)        { return -1; }
    
    u32 *At    = s.data + off;
    s32 offset = off;
    while(offset >= 0)
    { 
        if(ls_utf32IsNumber(*At)) { return offset; }
        At--; offset--;
    }
    
    return -1;
}

s32 ls_utf32CountOccurrences(utf32 s, u32 c)
{
    AssertMsg(s.data, "Source data is null.\n");
    
    u32 *At = s.data;
    u32 *End = s.data + s.len;
    
    s32 result = 0;
    while(At != End)
    {
        result += (s32)(*At == c);
        At += 1;
    }
    
    return result;
}

b32 ls_utf32Contains(utf32 haystack, utf32 needle)
{
    AssertMsg(haystack.data, "Haystack data is null\n");
    AssertMsg(needle.data, "Needle data is null\n");
    
    if(haystack.data == NULL) { return FALSE; }
    if(needle.data   == NULL) { return FALSE; }
    if(haystack.len  == 0)    { return FALSE; }
    if(needle.len    == 0)    { return FALSE; }
    
    u32 *At    = haystack.data;
    u32 *Check = needle.data;
    for(u32 i = 0; i < haystack.len; i++)
    {
        if((haystack.len - i) < needle.len) { return FALSE; }
        
        if(At[i] == Check[0])
        {
            if(ls_memcmp(At + i, Check, needle.len*sizeof(u32)) == TRUE) { return TRUE; }
        }
    }
    
    return FALSE;
}

b32 ls_UTF32IsWhitespace(u32 c)
{
    if((c == (u32)' ') || (c == (u32)'\n') || (c == (u32)'\r') || (c == (u32)'\t') || (c == (u32)'\v'))
    { return TRUE; }
    
    return FALSE;
}

//    OperateOn     //
//------------------//



//------------------//
//      Merge       //

utf32 ls_utf32Concat(utf32 s1, utf32 s2)
{
    utf32 Result = ls_utf32Alloc(s1.len + s2.len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len*4); }
    if(s2.len) { ls_memcpy(s2.data, Result.data + s1.len, s2.len*4); }
    Result.len = s1.len + s2.len;
    
    return Result;
}

void ls_utf32ConcatOn(utf32 s1, utf32 s2, utf32 *out)
{
    AssertMsg(out, "Output utf32 ptr is null\n");
    AssertMsg(out->data, "Output utf32 data is null\n");
    AssertMsgF(out->size > 0, "Trying to write to a Non-Positive sized string: %d\n", out->size);
    AssertMsg((out->size > (s1.len + s2.len)), "Output utf32 is too small to fit inputs\n");
    
    if(s1.len) { ls_memcpy(s1.data, out->data, s1.len*4); }
    if(s2.len) { ls_memcpy(s2.data, out->data + s1.len, s2.len*4); }
    out->len = s1.len + s2.len;
}

utf32 ls_utf32CatChar(utf32 s, u32 c)
{
    AssertMsg(s.data, "Input utf32 data is null\n");
    
    utf32 Result = ls_utf32Alloc(s.len + 1);
    if(s.len) { ls_memcpy(s.data, Result.data, s.len*4); }
    Result.data[s.len] = c;
    Result.len = s.len + 1;
    
    return Result;
}

utf32 ls_utf32CatCStr(utf32 s1, char *s2)
{
    AssertMsg(NULL, "Not implemented\n");
    utf32 Result = {};
    return Result;
#if 0
    u32 s2Len = ls_len(s2);
    
    utf32 Result = ls_utf32Alloc(s1.len + s2Len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2Len) { ls_memcpy(s2, Result.data + s1.len, s2Len); }
    Result.len = s1.len + s2Len;
    
    return Result;
#endif
}

void ls_utf32Prepend(utf32 *s1, utf32 s2)
{
    AssertMsg(s1,       "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s2.data,  "Input utf32 data is null\n");
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    u32 *At = s1->data + s1->len - 1;
    u32 *To = s1->data + s1->len + s2.len - 1;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s2.data, s1->data, s2.len*4);
    s1->len = s1->len + s2.len;
}

void ls_utf32PrependChar(utf32 *s1, u32 c)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s1->data, "Base utf32 data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_utf32Grow(s1, 32); }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    u32 *At = s1->data + s1->len - 1;
    u32 *To = s1->data + s1->len;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s1->data, s1->data + 1, s1->len*4);
    
    s1->data[0] = c;
    s1->len += 1;
}

void ls_utf32PrependCStr(utf32 *s1, char *s2)
{
    AssertMsg(NULL, "Not implemented\n");
    
#if 0
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsg(s2, "C utf32 ptr is null\n");
    
    u32 s2Len = ls_len(s2);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    ls_memcpy(s1->data, s1->data + s2Len, s1->len);
    ls_memcpy(s2, s1->data, s2Len);
    s1->len = s1->len + s2Len;
#endif
}

void ls_utf32Append(utf32 *s1, utf32 s2)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s2.data, "Input utf32 data is null\n");
    AssertMsgF(s2.len >= 0, "Trying to append negative len string: %d\n", s2.len);
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    ls_memcpy(s2.data, s1->data + s1->len, s2.len*4);
    s1->len += s2.len;
}

void ls_utf32Append(utf32 *s1, const char32_t *s)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s, "Input utf32 data is null\n");
    
    s32 s2Len = ls_utf32Len(s);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    ls_memcpy((void *)s, s1->data + s1->len, s2Len*4);
    s1->len += s2Len;
}

void ls_utf32AppendInt(utf32 *s, s64 val)
{
    AssertMsg(s, "Base utf32 ptr is null\n");
    AssertMsg(s->data, "Base utf32 data is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    
    u32 tmpBuff[32] = {};
    utf32 temp = { tmpBuff, 0, 32 };
    
    ls_utf32FromInt_t(&temp, val);
    ls_utf32Append(s, temp);
}

void ls_utf32AppendWithSeparator(utf32 *s1, const char32_t *sep, utf32 s2)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(s2.data, "Input utf32 data is null\n");
    AssertMsg(sep, "No separator was provided. Do we want to allow this?\n");
    
    u32 sepLen = 0;
    u32 *At = (u32 *)sep;
    while(*At != 0) { sepLen += 1; At += 1; }
    
    if(s1->len + s2.len + sepLen > s1->size)
    {
        u32 growSize = ((s1->len + s2.len + sepLen) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    ls_memcpy((void *)sep, s1->data + s1->len, sepLen*4);
    ls_memcpy(s2.data, s1->data + s1->len + sepLen, s2.len*4);
    s1->len += s2.len + sepLen;
}

void ls_utf32AppendChar(utf32 *s1, u32 c)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    
    if(s1->len + 1 > s1->size)
    { ls_utf32Grow(s1, 32); }
    
    s1->data[s1->len] = c;
    s1->len += 1;
}

void ls_utf32AppendCStr(utf32 *s1, char *c)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(c, "C String ptr is null\n");
    
    u32 len = ls_len(c);
    ls_utf32AppendNCStr(s1, c, len);
}

void ls_utf32AppendNCStr(utf32 *s1, char *c, s32 s2Len)
{
    //NOTE: We are assuming a classical C String is ASCII
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(c, "C String ptr is null\n");
    
    if(s2Len <= 0) { return; }
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    u32 *At = s1->data + s1->len;
    for(u32 i = 0; i < s2Len; i++) { At[i] = (u32)c[i]; }
    s1->len += s2Len;
}

void ls_utf32AppendBuffer(utf32 *s1, u32 *buff, s32 buffLen)
{
    AssertMsg(s1, "Base utf32 ptr is null\n");
    AssertMsg(s1->data, "Base utf32 data is null\n");
    AssertMsgF(s1->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s1->size);
    AssertMsg(buff, "C String ptr is null\n");
    
    if(buffLen <= 0) { return; }
    
    if(s1->len + buffLen > s1->size)
    {
        u32 growSize = ((s1->len + buffLen) - s1->size) + 32;
        ls_utf32Grow(s1, growSize);
    }
    
    u32 *At = s1->data + s1->len;
    ls_memcpy(buff, At, buffLen*sizeof(u32));
    s1->len += buffLen;
}


b32 ls_utf32Replace(utf32 *s, const char32_t *pattern, const char32_t *replacement)
{
    AssertMsg(s, "Base utf32 ptr is null\n");
    AssertMsg(s->data, "Base utf32 data is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    AssertMsg(pattern, "Pattern ptr is null\n");
    AssertMsg(replacement, "Replacement ptr is null\n");
    
    utf32 patStr  = ls_utf32Constant(pattern);
    utf32 replStr = ls_utf32Constant(replacement);
    
    b32 hasReplaced = FALSE; 
    s32 findIdx = -1;
    while((findIdx = ls_utf32LeftFind(*s, patStr)) != -1)
    {
        ls_utf32RmSubstr(s, findIdx, findIdx+patStr.len-1);
        ls_utf32InsertSubstr(s, replStr, findIdx);
        hasReplaced = TRUE;
    }
    
    return hasReplaced;
}

b32 ls_utf32Replace(utf32 *s, utf32 patStr, utf32 replStr)
{
    AssertMsg(s, "Base utf32 ptr is null\n");
    AssertMsg(s->data, "Base utf32 data is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    AssertMsg(patStr.data, "Pattern ptr is null\n");
    AssertMsg(replStr.data, "Replacement ptr is null\n");
    
    b32 hasReplaced = FALSE; 
    s32 findIdx = -1;
    while((findIdx = ls_utf32LeftFind(*s, patStr)) != -1)
    {
        ls_utf32RmSubstr(s, findIdx, findIdx+patStr.len-1);
        ls_utf32InsertSubstr(s, replStr, findIdx);
        hasReplaced = TRUE;
    }
    
    return hasReplaced;
}

//      Merge       //
//------------------//


//------------------//
//      Stuff       //


//TODO: Should I try optimizing it for utf-32 directly, rather than converting?
utf32  ls_utf32FromInt(s64 x)
{
    char buff[32] = {};
    ls_itoa_t(x, buff, 32);
    
    return ls_utf32FromAscii(buff);
}

void ls_utf32FromInt_t(utf32 *s, s64 x)
{
    AssertMsg(s, "Source pointer is null");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    
    char buff[32] = {};
    s32 len = ls_itoa_t(x, buff, 32);
    
    if(s->size < len) { ls_utf32Free(s); }
    
    if(s->data == NULL)
    { 
        *s = ls_utf32FromAscii(buff, len);
    }
    else
    {
        for(u32 i = 0; i < len; i++)
        { s->data[i] = (u32)buff[i]; }
        
        s->len = len;
    }
}

utf32 ls_utf32FromF64(f64 x)
{
    char buff[32] = {};
    u32 len = ls_ftoa_t(x, buff, 32);
    
    return ls_utf32FromAscii(buff, len);
}

void ls_utf32FromF64_t(utf32 *s, f64 x)
{
    AssertMsg(s, "Source ptr is null\n");
    AssertMsgF(s->size > 0, "Trying to write to a Non-Positive sized string: %d\n", s->size);
    
    char buff[32] = {};
    u32 len = ls_ftoa_t(x, buff, 32);
    
    if(s->size < len) { ls_utf32Free(s); }
    
    if(s->data == NULL)
    {
        *s = ls_utf32FromAscii(buff, len);
    }
    else
    {
        for(u32 i = 0; i < len; i++)
        { s->data[i] = (u32)buff[i]; }
        
        s->len = len;
    }
}

s32 ls_utf32ToAscii_t(utf32 s, char *buff, s32 buffMaxLen)
{
    AssertMsg(buff, "Output buffer pointer is null\n");
    AssertMsg(buffMaxLen > 0, "Non-Positive buff max len\n");
    
    if(s.len == 0) { return 0; }
    
    u32 *At = s.data;
    u32 idx = 0;
    while(*At && idx < s.len && idx < buffMaxLen)
    {
        buff[idx] = (char)(*At);
        
        At  += 1;
        idx += 1;
    }
    
    return idx;
}

s64 ls_utf32ToInt(utf32 s)
{
    AssertMsg(s.data, "Source string data is null\n");
    //AssertMsg(s.len >= 0, "Negative len in source string\n");
    
    if(s.len == 0) { return 0; }
    
    char numBuff[64] = {};
    AssertMsgF(s.len < 64, "Source passed represents a number that contains too many digits (%d)\n", s.len);
    
    s32 i = 0;
    for(i = 0; i < s.len; i++)
    {
        numBuff[i] = (char)(s.data[i]);
    }
    
    return ls_atoi(numBuff, i);
}

s64 ls_utf32ToIntIgnoreWhitespace(utf32 s)
{
    AssertMsg(s.data, "Source string data is null\n");
    //AssertMsg(s.len >= 0, "Negative len in source string\n");
    
    if(s.len == 0) { return 0; }
    
    char numBuff[64] = {};
    s32  buffIdx = 0;
    AssertMsgF(s.len < 64, "Source passed represents a number that contains too many digits (%d)\n", s.len);
    
    s32 i = 0;
    for(i = 0; i < s.len; i++)
    {
        if(ls_UTF32IsWhitespace(s.data[i])) { continue; }
        numBuff[buffIdx] = (char)(s.data[i]);
        buffIdx += 1;
    }
    
    return ls_atoi(numBuff, buffIdx);
}


b32 ls_utf32IsNumber(u32 c)
{
    if(c >= U'0' && c <= U'9') { return TRUE; }
    return FALSE;
}


//--------------//
//    VIEWS     //
//--------------//

//------------------//
//      Create      //

view ls_viewCreate(string s)
{
    view Res = {};
    
    Res.next = s.data;
    Res.len  = s.len;
    
    return Res;
}

uview ls_uviewCreate(utf32 s)
{
    uview Res = {};
    
    Res.next = s.data;
    Res.len  = s.len;
    
    return Res;
}

//      Create      //
//------------------//


//------------------//
//     OperateOn    //

view ls_viewExpect(view v, char c)
{
    char *At = v.next;
    AssertMsgF(*At == c, "View Expect %c Failed\n", c);
    return v;
}

view ls_viewExpectAndConsume(view v, char c)
{
    char *At = v.next;
    AssertMsgF(*At == c, "View Expect %c Failed\n", c);
    
    view Result = { {}, v.next + 1, v.len - 1 };
    return Result;
}

char ls_viewPeekNextChar(view v)
{
    char *At = v.next;
    return *At;
}

view ls_viewEatWhitespace(view v)
{
    char *At = v.next;
    u32 advance = 0;
    while(ls_isWhitespace(*At))
    {
        advance += 1;
        At += 1;
    }
    
    view Result = { {}, v.next + advance, v.len - advance};
    
    return Result;
}

view ls_viewNextNumeric(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    s32 wordLen = 0;
    s32 beginIdx = 0;
    char *At = v.next;
    
    while(!ls_isANumber(*At) && At < v.next + v.len) { At += 1; beginIdx += 1; }
    if(At >= v.next + v.len) { return Result; }
    
    while(ls_isANumber(*At) && At < v.next + v.len && wordLen < v.len) { At += 1; wordLen += 1; }
    
    Result.s    = { v.next + beginIdx, wordLen, wordLen };
    Result.next = v.next + beginIdx + wordLen;
    Result.len  = v.len - (beginIdx + wordLen);
    
    return Result;
}

view ls_viewNextDigit(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    s32 beginIdx = 0;
    char *At = v.next;
    
    while(!ls_isANumber(*At) && At < v.next + v.len) { At += 1; beginIdx += 1; }
    if(At >= v.next + v.len) { return Result; }
    
    Result.s    = { v.next + beginIdx, 1, 1 };
    Result.next = v.next + beginIdx + 1;
    Result.len  = v.len - (beginIdx + 1);
    
    return Result;
}

view ls_viewNextNChars(view v, u32 n)
{
    view Result = {};
    
    Result.s = {v.next, (s32)n, (s32)n};
    Result.next = v.next + n;
    Result.len  = v.len - n;
    
    return Result;
}

view ls_viewNextDelimiter(view v, char c)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 wordLen = 0;
    char *At = v.next;
    
    //NOTETODO: add found, and return original if not found? Or return error?
    while(wordLen < v.len)
    {
        if(*At == c)
        { break; }
        
        wordLen++;
        At++;
    }
    
    //NOTE: The delimeter was not found
    if(wordLen >= v.len) return {};
    
    //NOTE: We don't keep the delimiter in the word
    //      But we skip it in the .next
    u32 nextLen = wordLen + 1;
    if(wordLen == v.len)
    { nextLen = wordLen; }
    
    Result.s = {v.next, (s32)wordLen, (s32)wordLen};
    Result.next = v.next + nextLen;
    Result.len  = v.len - nextLen;
    
    return Result;
}

view ls_viewNextWord(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 wordLen = 0;
    char *At = v.next;
    while(wordLen < v.len)
    {
        if(ls_isWhitespace(*At))
        { break; }
        
        wordLen++;
        At++;
    }
    
    Result.s = {v.next, (s32)wordLen, (s32)wordLen};
    Result.next = v.next + wordLen;
    Result.len  = v.len - wordLen;
    
    return Result;
}

view ls_viewNextLineSkipWS(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 lineLen = 0;
    u32 skipWhite = 0;
    
    char *At = v.next;
    while(lineLen < v.len)
    {
        if(*At == '\r')
        { 
            skipWhite += 1;
            
            if((At+1 < v.next+v.len) && (*(At+1) == '\n'))
            { skipWhite += 1; }
            
            break;
        }
        
        if(*At == '\n')
        { skipWhite += 1; break; }
        
        lineLen++;
        At++;
    }
    
    Result.s = {v.next, (s32)lineLen, (s32)lineLen};
    Result.next = v.next + lineLen + skipWhite;
    Result.len  = v.len - (lineLen + skipWhite);
    
    return Result;
}

view ls_viewNextLine(view v)
{
    view Result = {};
    
    u32 lineLen = 0;
    char *At = v.next;
    while(lineLen < v.len)
    {
        if((*At == '\r') && (*(At+1) == '\n'))
        { lineLen += 2; break; }
        if(*At == '\n') { lineLen += 1; break; }
        
        lineLen += 1;
        At++;
    }
    
    Result.s = {v.next, (s32)lineLen, (s32)lineLen};
    Result.next = v.next + lineLen;
    Result.len  = v.len - lineLen;
    
    return Result;
}

b32 ls_viewIsLineEmpty(view v)
{
    string s = v.s;
    if(s.len == 1)
    {
        if(s.data[0] == '\n') { return TRUE; }
    }
    else if(s.len == 2)
    {
        if((s.data[0] == '\r') && (s.data[1] == '\n')) { return TRUE; }
    }
    
    return FALSE;
}


uview ls_uviewEatWhitespace(uview v)
{
    u32 *At = v.next;
    u32 advance = 0;
    while(ls_UTF32IsWhitespace(*At))
    {
        advance += 1;
        At += 1;
    }
    
    uview Result = { {}, v.next + advance, v.len - advance};
    
    return Result;
}

uview ls_uviewNextNChars(uview v, u32 n)
{
    uview Result = {};
    
    Result.s = {v.next, (s32)n, (s32)n};
    Result.next = v.next + n;
    Result.len  = v.len - n;
    
    return Result;
}

uview ls_uviewNextDelimiter(uview v, u32 c)
{
    uview Result = {};
    
    v = ls_uviewEatWhitespace(v);
    
    s32 wordLen = 0;
    u32 *At = v.next;
    
    //NOTETODO: add found, and return original if not found? Or return error?
    while(wordLen < v.len)
    {
        if(*At == c)
        { break; }
        
        wordLen++;
        At++;
    }
    
    //TODO: This is bullshit.
    AssertMsg(wordLen <= v.len, "Delimeter not found\n");
    
    //NOTE: We don't keep the delimiter in the word
    //      But we skip it in the .next
    u32 nextLen = wordLen + 1;
    if(wordLen == v.len)
    { nextLen = wordLen; }
    
    Result.s = {v.next, wordLen, wordLen};
    Result.next = v.next + nextLen;
    Result.len  = v.len - nextLen;
    
    return Result;
}

uview ls_uviewNextWord(uview v)
{
    uview Result = {};
    
    v = ls_uviewEatWhitespace(v);
    
    s32 wordLen = 0;
    u32 *At = v.next;
    while(wordLen < v.len)
    {
        if(ls_UTF32IsWhitespace(*At))
        { break; }
        
        wordLen++;
        At++;
    }
    
    Result.s = {v.next, wordLen, wordLen};
    Result.next = v.next + wordLen;
    Result.len  = v.len - wordLen;
    
    return Result;
}

uview ls_uviewNextLine(uview v)
{
    uview Result = {};
    
    s32 lineLen = 0;
    u32 *At = v.next;
    while(lineLen < v.len)
    {
        if((*At == (u32)'\r') && (*(At+1) == (u32)'\n'))
        { lineLen += 2; break; }
        if(*At == (u32)'\n') { lineLen += 1; break; }
        
        lineLen += 1;
        At++;
    }
    
    Result.s = {v.next, lineLen, lineLen};
    Result.next = v.next + lineLen;
    Result.len  = v.len - lineLen;
    
    return Result;
}

uview ls_uviewNextLineSkipWS(uview v)
{
    uview Result = {};
    
    v = ls_uviewEatWhitespace(v);
    
    s32 lineLen   = 0;
    u32 skipWhite = 0;
    
    u32 *At = v.next;
    while(lineLen < v.len)
    {
        if(*At == (u32)'\r')
        { 
            skipWhite += 1;
            
            if((At+1 < v.next+v.len) && (*(At+1) == (u32)'\n'))
            { skipWhite += 1; }
            
            break;
        }
        if(*At == (u32)'\n')
        { 
            skipWhite += 1;
            break;
        }
        
        lineLen++;
        At++;
    }
    
    Result.s = {v.next, lineLen, lineLen};
    Result.next = v.next + lineLen + skipWhite;
    Result.len  = v.len - (lineLen + skipWhite);
    
    return Result;
}

b32 ls_uviewIsLineEmpty(uview v)
{
    utf32 s = v.s;
    if(s.len == 1)
    {
        if(s.data[0] == (u32)'\n') { return TRUE; }
    }
    else if(s.len == 2)
    {
        if((s.data[0] == (u32)'\r') && (s.data[1] == (u32)'\n')) { return TRUE; }
    }
    
    return FALSE;
}


//     OperateOn    //
//------------------//

#endif //IMPLEMENTATION
