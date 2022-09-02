#ifndef LS_STRING_H
#define LS_STRING_H

#include "win32.h"
#include "lsCRT.h"

//TODO: Make size = -1 meaning undefined, and size = 0, meaning a constant string,
//      to allow the string functions to know if they're dealing with constant strings or not.

//NOTE: The minus 1 is to ignore the NULL terminator at the end of string literals.
#define ls_strConst(s) {s, sizeof(s)/sizeof(s[0])-1, sizeof(s)/sizeof(s[0])-1}

struct string
{
    char *data;
    u32  len;
    u32  size;
};

struct unistring
{
    u32 *data;
    u32  len;
    u32  size;
};

struct view
{
    string s;
    
    char *next;
    u32  len;
};

struct uview
{
    unistring s;
    
    u32 *next;
    u32 len;
};

//-----------------------------//
//        ASCII STRINGS        //
//-----------------------------//

//Create/Destroy
string  ls_strAlloc(u32 size);
string *ls_strAllocPtr(u32 size);
string *ls_strAllocArr(u32 numStrings, s32 initialSize);
void    ls_strFree(string *s);
void    ls_strFreePtr(string *s);
void    ls_strFreeArr(string *s, u32 arrSize);


//Manage
string  ls_strInit(char *s);

//NOTE: In this case the char * string lives on the STACK!
string  ls_strConstant(char *p);
string  ls_strConstant(char *p, u32 len);
string  ls_strConstChar(char *c);

void    ls_strClear(string *s);
string  ls_strCopy(string s);
void	ls_strNCopy(string s, string *dst, size_t size);
string  ls_strCopySubstr(string s, u32 beginIdx, u32 _endIdx = (u32)-1);


//C Bullshit
void    ls_strNullTerminate(string *s);
char   *ls_strToCStr(string s);
b32     ls_strToCStr_t(string s, char *buff, s32 buffSize);


//OperateOn
void    ls_strReverse(string *s);
void    ls_strRmSubstr(string *s, u32 beginIdx, u32 endIdx);
void    ls_strRmIdx(string *s, u32 idx);
void    ls_strRmAllNonTextChar(string *s);
void    ls_strTrimRight(string *s, u32 numChars);

void    ls_strInsertSubstr(string *s, string toInsert, u32 insertIdx);
void    ls_strInsertChar(string *s, char c, u32 idx);
void    ls_strInsertCStr(string *s, char *toInsert, u32 insertIdx);


//NOTE: Maybe reword these?
string  *ls_strBreakByDelimeter(string s, u32 *numOfStrings, char c);
string  *ls_strBreakByLine(string s, u32 *numOfLines);
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
void    ls_strAppendView(string *s1, view v);
void    ls_strAppendChar(string *s1, char c);
void    ls_strAppendCStr(string *s1, char *c);
void    ls_strAppendNCStr(string *s1, char *c, u32 len);


//To/From Data
b32     ls_strIsANumber(string s);
string  ls_itos(s64 x);
void    ls_itosOn(s64 x, string *out);
string  ls_itoh(u64 x);
s64     ls_stoi(string s);
f32	 ls_stof(string s);
string  ls_ftos(f32 x);


//Operator
b32     operator==(string s1, string s2);
b32     operator!=(string s1, string s2);

b32     ls_strIsEqualNCStr(string s1, char *s2, u32 len);


//-----------------------------//
//    UTF32 UNICODE STRINGS    //
//-----------------------------//

//Create/Destroy
unistring  ls_unistrAlloc(u32 size);
unistring *ls_unistrAllocPtr(u32 size);
unistring *ls_unistrAllocArr(u32 numStrings, s32 initialSize);
void       ls_unistrFree(unistring *s);
void       ls_unistrFreePtr(unistring *s);
void       ls_unistrFreeArr(unistring *s, u32 arrSize);

b32        ls_unistrAreEqual(unistring a, unistring b);
b32        ls_unistrAsciiAreEqual(unistring a, string b);
void       ls_unistrSet(unistring *toSet, unistring source);

unistring  ls_unistrFromAscii(char *s);
unistring  ls_unistrFromAscii(char *s, u32 len);
void       ls_unistrFromAscii_t(unistring *dst, char *src);
void       ls_unistrFromAscii_t(unistring *dst, char *src, u32 len);
unistring  ls_unistrFromUTF32(const char32_t *s);
void       ls_unistrFromUTF32_t(unistring *dst, const char32_t *s);
unistring  ls_unistrFromInt(s64 x);
void       ls_unistrFromInt_t(unistring *s, s64 x);
void       ls_unistrFromF64_t(unistring *s, f64 x);
unistring  ls_unistrConstant(const char32_t *p);

//Manage
void       ls_unistrClear(unistring *s);
unistring  ls_unistrCopy(unistring s);
void	   ls_unistrNCopy(unistring s, unistring *dst, size_t size);
unistring  ls_unistrCopySubstr(unistring s, u32 beginIdx, u32 _endIdx = (u32)-1);

//OperateOn
void    ls_unistrReverse(unistring *s);
void    ls_unistrRmSubstr(unistring *s, u32 beginIdx, u32 endIdx);
void    ls_unistrRmIdx(unistring *s, u32 idx);
void    ls_unistrRmAllNonTextChar(unistring *s);
void    ls_unistrTrimRight(unistring *s, u32 numChars);

void    ls_unistrInsertSubstr(unistring *s, unistring toInsert, u32 insertIdx);
void    ls_unistrInsertChar(unistring *s, u32 c, u32 idx);
void    ls_unistrInsertCStr(unistring *s, char *toInsert, u32 insertIdx);
void    ls_unistrInsertBuffer(unistring *s, u32 *toInsert, u32 buffLen, u32 insertIdx);

unistring  *ls_unistrSplit(unistring s, u32 *outNum, unistring delim);
unistring  *ls_unistrSplit(unistring s, u32 *outNum, const char32_t *a);
unistring  *ls_unistrSplit(unistring s, u32 *outNum, char32_t c);
unistring  *ls_unistrSplit(unistring s, u32 *outNum, u32 c);
unistring  *ls_unistrSplit(unistring s, u32 *outNum, char c);
unistring  *ls_unistrSplit(unistring s, u32 *outNum, const char *c);

unistring  *ls_unistrSeparateByNumber(unistring s, u32 *outNum);

unistring  *ls_unistrBreakBySpaceUntilDelimiter(unistring s, u32 delimiter, u32 *numOfStrings);
s32         ls_unistrLeftFind(unistring s, u32 c);
s32         ls_unistrLeftFind(unistring s, s32 offset, u32 c);
s32         ls_unistrRightFind(unistring s, u32 c);
s32         ls_unistrRightFind(unistring s, s32 offset, u32 c);
s32         ls_unistrCountOccurrences(unistring s, u32 c);

b32         ls_UTF32IsWhitespace(u32 c);

//Merge
unistring  ls_unistrConcat(unistring s1, unistring s2);
void       ls_unistrConcatOn(unistring s1, unistring s2, unistring *out);
unistring  ls_unistrCatChar(unistring s1, u32 c);
unistring  ls_unistrCatCStr(unistring s1, char *c);
void       ls_unistrPrepend(unistring *s1, unistring s2);
void       ls_unistrPrependChar(unistring *s, u32 c);
void       ls_unistrPrependCStr(unistring *s, char *c);
void       ls_unistrAppend(unistring *s1, unistring s2);
void       ls_unistrAppendChar(unistring *s1, u32 c);
void       ls_unistrAppendCStr(unistring *s1, char *c);
void       ls_unistrAppendNCStr(unistring *s1, char *c, u32 len);
void       ls_unistrAppendBuffer(unistring *s1, u32 *buff, u32 buffLen);

// Convert
s32        ls_unistrToAscii_t(unistring *s, char *buff, u32 buffMaxLen);
s64        ls_unistrToInt(unistring s);

b32        ls_utf32IsNumber(u32 c);

//Create/Destroy
view  ls_viewCreate(string s);
uview ls_uviewCreate(unistring s);

//OperateOn
view  ls_viewEatWhitespace(view v);
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

static void ls_unistrGrow(unistring *s, u32 amount)
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

string ls_strAlloc(u32 size)
{
    char *data = (char *)ls_alloc(sizeof(char)*size);
    string Result = {data, 0, size};
    
    return Result;
}

string *ls_strAllocPtr(u32 size)
{
    string *Result = (string *)ls_alloc(sizeof(string));
    *Result = ls_strAlloc(size);
    
    return Result;
};

string *ls_strAllocArr(u32 numStrings, s32 initialSize = 0)
{
    string *s = (string *)ls_alloc(sizeof(string)*numStrings);
    if(initialSize > 0)
    {
        for(u32 i = 0; i < numStrings; i++) { s[i] = ls_strAlloc(initialSize); }
    }
    
    return s;
}

void ls_strFree(string *a)
{
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
}

void ls_strFreePtr(string *a)
{
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
    
    ls_free(a);
}

void ls_strFreeArr(string *s, u32 arrSize)
{
    for(u32 i = 0; i < arrSize; i++)
    { ls_strFree(&s[i]);}
    
    ls_free(s);
}

//TODO: This stack living string is always strange... 
//      for example in printf it seemed to work not that good...
string ls_strConstant(char *p)
{
    u32 len = ls_len(p);
    string s = {p, len, len};
    return s;
}

string  ls_strConstant(char *p, u32 len)
{
    string s = {p, len, len};
    return s;
}

string ls_strConstChar(char *c)
{
    string s = {c, 1, 1};
    return s;
}


//  Create/Destroy  //
//------------------//


//------------------//
//     Manage       //

string ls_strInit(char *s)
{
    u32 len = ls_len(s);
    
    string Result = ls_strAlloc(len);
    ls_memcpy(s, Result.data, len);
    Result.len = len;
    
    return Result;
}

void ls_strClear(string *s)
{ s->len = 0; }

string ls_strCopy(string s)
{
    string Result = ls_strAlloc(s.len);
    ls_memcpy(s.data, Result.data, s.len);
    Result.len = s.len;
    
    return Result;
}

void ls_strNCopy(string src, string *dst, size_t size)
{
    u32 copySize = size;
    if(size > src.len) { copySize = src.len; }
    
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

b32 ls_strToCStr_t(string s, char *buff, s32 buffSize)
{
    AssertMsg(buffSize >= s.len+1, "C String Buff not large enough\n");
    
    ls_memcpy(s.data, buff, s.len);
    buff[s.len] = 0;
    
    return TRUE;
}


//    C Bullshit    //
//------------------//


//------------------//
//     OperateOn    //

void ls_strReverse(string *s)
{
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
    AssertMsg(s, "String pointer is null\n");
    AssertMsg(beginIdx < s->len, "Begin Index Out of Bounds. Larger than string length\n");
    AssertMsg(endIdx < s->len, "End Index Out of Bounds. Larger than string length\n");
    AssertMsg(beginIdx < endIdx, "Begin Index is larger than End Index\n");
    AssertMsg((endIdx - beginIdx) < s->len, "Index Range is larger than length of string. How did this happen?\n");
    
    u32 remove = ((endIdx - beginIdx) + 1);
    remove = remove > s->len ? s->len : remove;
    
    u32 copyLen = s->len - (endIdx + 1);
    copyLen = copyLen == 0 ? 1 : copyLen;
    
    ls_memcpy((void *)(s->data + endIdx + 1), (void *)(s->data + beginIdx), copyLen);
    s->len -= remove;
    s->data[s->len] = 0; //TODO: Fuck C strings. Remove this abomination.
    
    return;
}

void ls_strRmIdx(string *s, u32 idx)
{ ls_strRmSubstr(s, idx, idx); }

void ls_strRmAllNonTextChar(string *s)
{
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
        
        ls_strAppendChar(Result, c);
    }
    
    ls_free(s->data);
    *s = *Result;
    
    return;
}

void ls_strTrimRight(string *s, u32 numChars)
{ 
    AssertMsg(s, "Null string pointer passed\n");
    AssertMsg(s->len > 0, "Trying to trim an empty string\n");
    s->len -= numChars; 
}

void ls_strInsertSubstr(string *s, string toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null string pointer passed\n");
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
    string insertString = ls_strConstChar(&c);
    ls_strInsertSubstr(s, insertString, idx);
}

void ls_strInsertCStr(string *s, char *toInsert, u32 insertIdx)
{
    string insertString = ls_strConstant(toInsert);
    ls_strInsertSubstr(s, insertString, insertIdx);
}



string *ls_strBreakByDelimeter(string s, u32 *numOfStrings, char c)
{
    if(s.data == NULL) { return NULL; } //TODO: This should probably be an AssertMsg()
    
    string *Result = 0;
    //The thing could crash if this buff overflows
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 16384);
        
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

string *ls_strBreakByLine(string s, u32 *numOfLines)
{
    if(s.data == NULL) { return NULL; }
    
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
    if(s.data == NULL) { return NULL; }
    
    string *Result = 0;
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 16384);
        
        if ((*At == ' ') || (*At == '\n') || (*At == '\t') || (*At == '\r') )
        {
            //TODO: Test this
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
    Assert(s.len != 0);
    return ls_strBreakByDelimeter(s, numOfStrings, ' ');
}

string *ls_strBreakBySpaceUntilDelimiter(string s, char delimiter, u32 *numOfStrings)
{
    string *Result = 0;
    string buff[256] = {};
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
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    if(numOfStrings) { *numOfStrings = buffIdx; }
    
    return Result;
}

s32 ls_strLeftFind(string s, char c)
{
    AssertMsg(s.data, "Unistring data is null.\n");
    
    char *At = s.data;
    s32 offset = 0;
    
    b32 found = FALSE;
    while (At != (s.data + s.len))
    { 
        if(*At == c) { found = TRUE; break; }
        At++; offset++;
    }
    
    if(found) return offset;
    
    return -1;
}

s32 ls_strRightFind(string s, char c)
{
    AssertMsg(s.data, "Unistring data is null.\n");
    
    char *At = s.data + s.len;
    s32 offset = s.len;
    
    b32 found = FALSE;
    while(At != s.data)
    {
        if(*At == c) { found = TRUE; break; }
        At--;
        offset--;
    }
    
    if(found) return offset;
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
    u32 s2Len = ls_len(s2);
    
    string Result = ls_strAlloc(s1.len + s2Len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2Len) { ls_memcpy(s2, Result.data + s1.len, s2Len); }
    Result.len = s1.len + s2Len;
    
    return Result;
}

void ls_strPrepend(string *s1, string s2)
{
    AssertMsg(s1, "Base string ptr is null\n");
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

void ls_strAppendView(string *s, view v)
{
    AssertMsg(s, "Base string ptr is null\n");
    AssertMsg(s->data, "Base string data is null\n");
    
    if(s->len + v.s.len > s->size)
    {
        u32 growSize = ((s->len + v.s.len) - s->size) + 32;
        ls_strGrow(s, growSize);
    }
    
    ls_memcpy(v.s.data, s->data + s->len, v.s.len);
    s->len += v.s.len;
}

void ls_strAppendChar(string *s1, char c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsg(s1->data, "Base string data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_strGrow(s1, 32); }
    
    s1->data[s1->len] = c;
    s1->len += 1;
}

void ls_strAppendCStr(string *s1, char *c)
{
    AssertMsg(s1, "Base string ptr is null\n");
    AssertMsg(s1->data, "Base string data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    u32 len = ls_len(c);
    ls_strAppendNCStr(s1, c, len);
}

void ls_strAppendNCStr(string *s1, char *c, u32 s2Len)
{
    //NOTE: Do I want these asserts?
    AssertMsg(s1, "Base string ptr is null\n");
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
    Assert(out != 0x0);
    Assert(out->data != 0x0);
    Assert(out->size > 20);
    
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if (value == 0)
    {
        out->data[0] = '0';
        out->data[1] = '\0';
        out->len = 1;
        
        return;
    }
    
    //My Log10 Function is not super precise at the boundaries between values i.e. 999999 - 1000000. So just to be sure, I give it an extra byte, which is super fine.
    
    //Update months Later: BTW I think this is a fuckin waste of time and processor power, considering no number to be printed is ever going to be bigger than 128 char long
    //I should just waste this 0.000000016% of the average computer FUCKING Memory to just allocate a little bit more than necessary.
    
    //I'm not going to change it now just because it's good training for me to approximate trascendental functions and stuff like that
    
    //Update few days later: Fuck it I'm changing this shitty Log10 functions that sucks freakin balls.
    
    //@TODO @CLEANUP @FIXME: Make a Log2 / Log10 / LOGN Function Tables so that I quit having this stupid shitty problem. (Or maybe see if theres cool ASM for them)
    
    s32 i = 0;
    
    while (value != 0)
    {
        out->data[i++] = value % 10 + '0';
        value = value / 10;
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
    string buffer = ls_strAlloc(32);
    string Result = ls_strAlloc(64);
    
    u8 *At = (u8 *)&x;
    for(u32 i = 0; i < 8; i++)
    {
        u8 lowNybble = (*At & 0x0F);
        u8 highNybble = (*At & 0xF0) >> 4;;
        
        switch(lowNybble)
        {
            case 0:  ls_strAppendChar(&buffer, '0'); break;
            case 1:  ls_strAppendChar(&buffer, '1'); break;
            case 2:  ls_strAppendChar(&buffer, '2'); break;
            case 3:  ls_strAppendChar(&buffer, '3'); break;
            case 4:  ls_strAppendChar(&buffer, '4'); break;
            case 5:  ls_strAppendChar(&buffer, '5'); break;
            case 6:  ls_strAppendChar(&buffer, '6'); break;
            case 7:  ls_strAppendChar(&buffer, '7'); break;
            case 8:  ls_strAppendChar(&buffer, '8'); break;
            case 9:  ls_strAppendChar(&buffer, '9'); break;
            case 10: ls_strAppendChar(&buffer, 'A'); break;
            case 11: ls_strAppendChar(&buffer, 'B'); break;
            case 12: ls_strAppendChar(&buffer, 'C'); break;
            case 13: ls_strAppendChar(&buffer, 'D'); break;
            case 14: ls_strAppendChar(&buffer, 'E'); break;
            case 15: ls_strAppendChar(&buffer, 'F'); break;
        }
        
        switch(highNybble)
        {
            case 0:  ls_strAppendChar(&buffer, '0'); break;
            case 1:  ls_strAppendChar(&buffer, '1'); break;
            case 2:  ls_strAppendChar(&buffer, '2'); break;
            case 3:  ls_strAppendChar(&buffer, '3'); break;
            case 4:  ls_strAppendChar(&buffer, '4'); break;
            case 5:  ls_strAppendChar(&buffer, '5'); break;
            case 6:  ls_strAppendChar(&buffer, '6'); break;
            case 7:  ls_strAppendChar(&buffer, '7'); break;
            case 8:  ls_strAppendChar(&buffer, '8'); break;
            case 9:  ls_strAppendChar(&buffer, '9'); break;
            case 10: ls_strAppendChar(&buffer, 'A'); break;
            case 11: ls_strAppendChar(&buffer, 'B'); break;
            case 12: ls_strAppendChar(&buffer, 'C'); break;
            case 13: ls_strAppendChar(&buffer, 'D'); break;
            case 14: ls_strAppendChar(&buffer, 'E'); break;
            case 15: ls_strAppendChar(&buffer, 'F'); break;
        }
        At++;
    }
    
    buffer.data[buffer.len] = 0;
    ls_strReverse(&buffer);
    
    ls_strAppendCStr(&Result, (char*)"0x");
    
    while(true)
    {
        if(buffer.len == 2) { break; }
        if((buffer.data[0] != '0') || (buffer.data[1] != '0'))
        { break; }
        else
        { ls_strRmSubstr(&buffer, 0, 1); }
    }
    
    string P = ls_strConcat(Result, buffer);
    ls_strNullTerminate(&P);
    
    ls_strFree(&buffer);
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






//UTF32 UNICODE STRINGS

//------------------//
//  Create/Destroy  //

unistring ls_unistrAlloc(u32 size)
{
    u32 *data = (u32 *)ls_alloc(sizeof(u32)*size);
    unistring Result = {data, 0, size};
    
    return Result;
}

unistring *ls_unistrAllocPtr(u32 size)
{
    unistring *Result = (unistring *)ls_alloc(sizeof(string));
    *Result = ls_unistrAlloc(size);
    
    return Result;
}

unistring *ls_unistrAllocArr(u32 numStrings, s32 initialSize)
{
    if(numStrings == 0) { return 0x0; }
    
    
    unistring *s = (unistring *)ls_alloc(sizeof(unistring)*numStrings);
    if(initialSize > 0)
    {
        for(u32 i = 0; i < numStrings; i++) { s[i] = ls_unistrAlloc(initialSize); }
    }
    
    return s;
}

void ls_unistrFree(unistring *s)
{
    ls_free(s->data);
    s->data = 0;
    s->len = 0;
    s->size = 0;
}

void ls_unistrFreePtr(unistring *s)
{
    ls_free(s->data);
    s->data = 0;
    s->len = 0;
    s->size = 0;
    
    ls_free(s);
}

void ls_unistrFreeArr(unistring *s, u32 arrSize)
{
    for(u32 i = 0; i < arrSize; i++)
    { ls_unistrFree(&s[i]);}
    
    ls_free(s);
}

b32 ls_unistrAreEqual(unistring a, unistring b)
{
    AssertMsg(a.data, "First string's data pointer is null");
    AssertMsg(b.data, "Second string's data pointer is null");
    
    if(a.len != b.len)   { return FALSE; }
    if(a.data == b.data) { return TRUE; }
    
    b32 isDataEqual = ls_memcmp(a.data, b.data, a.len);
    if(isDataEqual == TRUE) { return TRUE; }
    
    return FALSE;
}

b32 ls_unistrAsciiAreEqual(unistring a, string b)
{
    AssertMsg(a.data, "First string's data pointer is null");
    AssertMsg(b.data, "Second string's data pointer is null");
    
    if(a.len != b.len)   { return FALSE; }
    
    for(u32 i = 0; i < a.len; i++) {
        if(a.data[i] != (u32)(b.data[i])) { return FALSE; }
    }
    
    return TRUE;
}

void ls_unistrSet(unistring *toSet, unistring source)
{
    AssertMsg(toSet, "String to be set pointer is null\n");
    
    if(!toSet->data)
    { 
        u32 allocSize = (16 + source.len);
        
        toSet->data = (u32 *)ls_alloc(allocSize*sizeof(u32));
        toSet->size = allocSize;
    }
    
    if(source.len == 0) { toSet->len = 0; return; }
    
    if(toSet->size < source.len)
    {
        u32 growAmount = (toSet->size - source.len + 32);
        ls_unistrGrow(toSet, growAmount);
    }
    
    ls_memcpy(source.data, toSet->data, source.len*sizeof(u32));
    toSet->len = source.len;
}


unistring ls_unistrFromAscii(char *s, u32 len)
{
    unistring Result = ls_unistrAlloc(len);
    
    for(u32 i = 0; i < len; i++) { Result.data[i] = (u32)s[i]; }
    Result.len = len;
    
    return Result;
}

unistring ls_unistrFromAscii(char *s)
{
    u32 len = ls_len(s);
    return ls_unistrFromAscii(s, len);
}

void ls_unistrFromAscii_t(unistring *dst, char *src, u32 len)
{
    for(u32 i = 0; i < len; i++) { dst->data[i] = (u32)src[i]; }
    dst->len = len;
}

void ls_unistrFromAscii_t(unistring *dst, char *src)
{
    u32 len = ls_len(src);
    ls_unistrFromAscii_t(dst, src, len);
}

unistring ls_unistrFromUTF32(const char32_t *s)
{
    if(s == NULL) { return {}; }
    
    u32 len = 0;
    u32 *At = (u32 *)s;
    while(*At) { len += 1; At += 1; }
    
    unistring Result = ls_unistrAlloc(len);
    ls_memcpy((void *)s, Result.data, len*sizeof(u32));
    Result.len = len;
    
    return Result;
}

void ls_unistrFromUTF32_t(unistring *dst, const char32_t *s)
{
    AssertMsg(dst, "Destination unistring pointer is null\n");
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
        ls_unistrGrow(dst, growAmount);
    }
    
    ls_memcpy((void *)s, dst->data, len*sizeof(u32));
    dst->len = len;
    
    return;
}

unistring ls_unistrConstant(const char32_t *p)
{
    u32 len = 0;
    u32 *At = (u32 *)p;
    while(*At != 0) { len += 1; At += 1; }
    
    unistring Result = { (u32 *)p, len, len };
    return Result;
}

//  Create/Destroy  //
//------------------//

//------------------//
//     Manage       //


void ls_unistrClear(unistring *s)
{ s->len = 0; }

unistring ls_unistrCopy(unistring s)
{
    unistring Result = ls_unistrAlloc(s.len);
    ls_memcpy(s.data, Result.data, s.len*4);
    Result.len = s.len;
    
    return Result;
}

void ls_unistrNCopy(unistring src, unistring *dst, size_t size)
{
    u32 copySize = size;
    if(size > src.len) { copySize = src.len; }
    
    if(dst->data == NULL) { *dst = ls_unistrAlloc(copySize); }
    
    if(dst->size < src.len)
    {
        u32 growAmount = (dst->size - src.len + 32);
        ls_unistrGrow(dst, growAmount);
    }
    
    ls_memcpy(src.data, dst->data, copySize*4);
    dst->len = copySize;
}

unistring ls_unistrCopySubstr(unistring s, u32 beginIdx, u32 _endIdx)
{
    u32 endIdx = 0;
    if(_endIdx == (u32)-1) { endIdx = s.len-1; }
    else { endIdx = _endIdx; }
    
    if((beginIdx < 0 || beginIdx >= s.size) ||
       (endIdx < 0 || endIdx >= s.size) ||
       (endIdx - beginIdx >= s.size))
    { unistring error = {}; return error; }
    
    unistring result = ls_unistrAlloc((endIdx - beginIdx) + 1);
    
    ls_memcpy(s.data + beginIdx, result.data, result.size*4);
    result.len = ((endIdx - beginIdx) + 1);
    
    return result;
}

//      Manage      //
//------------------//

//------------------//
//     OperateOn    //

void ls_unistrReverse(unistring *s)
{
    u32 *Begin = s->data;
    u32 *End   = s->data + s->len;
    u32 temp = 0;
    //NOTE: unistring doesn't have null-terminators if(*End == 0) { End--; } Ignore null-terminator
    while (Begin < End)
    {
        temp   = *Begin;
        *Begin = *End;
        *End   = temp;
        
        Begin += 1;
        End   -= 1;
    }
}

void ls_unistrRmSubstr(unistring *s, u32 beginIdx, u32 endIdx)
{
    AssertMsg(s, "Unistring pointer is null\n");
    AssertMsg(beginIdx < s->len, "Begin Index is out of bounds. Larger than string length\n");
    AssertMsg(endIdx   < s->len, "End Index is out of bounds. Larger than string length\n");
    AssertMsg((endIdx - beginIdx) < s->len, "Index Range is larger than string length. How??\n");
    
    u32 remove  = ((endIdx - beginIdx) + 1);
    u32 copyLen = s->len - (endIdx + 1);
    
    ls_memcpy((void *)(s->data + endIdx + 1), (void *)(s->data + beginIdx), copyLen*4);
    s->len -= remove;
    
    return;
}

void ls_unistrRmIdx(unistring *s, u32 idx)
{ ls_unistrRmSubstr(s, idx, idx); }


void ls_unistrRmAllNonTextChar(unistring *s)
{
    AssertMsg(FALSE, "Function needs to be implemented\n");
    
#if 0
    unistring *Result = ls_unistrAllocPtr(s->size);
    
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
        
        ls_unistrAppendChar(Result, c);
    }
    
    ls_free(s->data);
    *s = *Result;
    
    return;
#endif
}

void ls_unistrTrimRight(unistring *s, u32 numChars)
{ 
    AssertMsg(s, "Null unistring pointer passed\n");
    AssertMsg(s->len > 0, "Trying to trim an empty unistring\n");
    AssertMsg(numChars <= s->len, "Trying to trim more than the string length.\n");
    s->len -= numChars; 
}

void ls_unistrInsertSubstr(unistring *s, unistring toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null unistring pointer passed\n");
    AssertMsg(insertIdx < s->len, "Insertion index past unistring length\n");
    
    if(s->len + toInsert.len > s->size)
    {
        u32 growSize = ((s->len + toInsert.len) - s->size) + 32;
        ls_unistrGrow(s, growSize);
    }
    
    //TODO:Make a better reverse memcpy for non byte-boundary blocks.
    s32 moveBytes = (s->len - insertIdx)*sizeof(u32);
    
    u32 *tempBuff = (u32 *)ls_alloc(moveBytes);
    ls_memcpy(s->data + insertIdx, tempBuff, moveBytes);
    ls_memcpy(tempBuff, s->data + insertIdx + toInsert.len, moveBytes);
    
    ls_free(tempBuff);
    
    ls_memcpy(toInsert.data, s->data + insertIdx, toInsert.len*sizeof(u32));
    
    s->len += toInsert.len;
}

void ls_unistrInsertChar(unistring *s, u32 c, u32 idx)
{
    unistring insertString = {&c, 1, 1};
    ls_unistrInsertSubstr(s, insertString, idx);
}

void ls_unistrInsertCStr(unistring *s, char *toInsert, u32 insertIdx)
{
    AssertMsg(s, "Null unistring pointer passed\n");
    AssertMsg(toInsert, "C String pointer passed is null\n");
    AssertMsg(insertIdx < s->len, "Insertion index past unistring length\n");
    
    u32 len = ls_len(toInsert);
    
    if(s->len + len > s->size)
    {
        u32 growSize = ((s->len + len) - s->size) + 32;
        ls_unistrGrow(s, growSize);
    }
    
    ls_memcpy(s->data + insertIdx, s->data + insertIdx + len, (s->len - insertIdx)*sizeof(u32));
    
    u32 *At = s->data + insertIdx;
    for(u32 i = 0; i < len; i++) { At[i] = (u32)toInsert[i]; }
    s->len += len;
}

void ls_unistrInsertBuffer(unistring *s, u32 *toInsert, u32 buffLen, u32 insertIdx)
{
    AssertMsg(s, "Dest string pointer is null\n");
    AssertMsg(toInsert, "To Insert string pointer is null\n");
    
    if(buffLen == 0) { return; }
    
    unistring insertString = {toInsert, buffLen, buffLen};
    ls_unistrInsertSubstr(s, insertString, insertIdx);
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, unistring delim)
{
    AssertMsg(s.data, "Unistring data pointer is null\n");
    AssertMsg(outNum, "Output parameter outNum is null\n");
    
    u32 delimCount = 0;
    
    u32 *At = s.data;
    while(At < (s.data + s.len))
    {
        unistring test = { At, delim.len, delim.len };
        if(ls_unistrAreEqual(test, delim) == TRUE)
        { 
            delimCount += 1;
            
            while(ls_unistrAreEqual(test, delim) == TRUE) {
                At += 1; 
                test.data = At;
            }
        }
        
        At += 1;
    }
    
    unistring *Result = ls_unistrAllocArr(delimCount+1, 16);
    u32 idx = 0;
    
    
    u32 *BeginString = s.data;
    At = s.data;
    while(At < (s.data + s.len))
    {
        unistring test = { At, delim.len, delim.len };
        if(ls_unistrAreEqual(test, delim) == TRUE)
        {
            unistring toCopy = { BeginString, (u32)(At - BeginString), (u32)(At - BeginString)};
            ls_unistrSet(Result + idx, toCopy);
            idx += 1;
            
            while(ls_unistrAreEqual(test, delim) == TRUE) {
                At += 1; 
                test.data = At; 
            }
            
            BeginString = At;
        }
        
        At += 1;
    }
    
    if(BeginString != At)
    {
        unistring toCopy = { BeginString, (u32)(At - BeginString), (u32)(At - BeginString)};
        ls_unistrSet(Result + idx, toCopy);
        idx += 1;
    }
    
    *outNum = idx;
    
    return Result;
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, const char32_t *a)
{
    unistring delim = ls_unistrConstant(a);
    return ls_unistrSplit(s, outNum, delim);
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, u32 c)
{
    unistring delim = {&c, 1, 1};
    return ls_unistrSplit(s, outNum, delim);
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, char32_t c)
{
    unistring delim = {(u32 *)(&c), 1, 1};
    return ls_unistrSplit(s, outNum, delim);
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, char c)
{
    u32 ch = (u32)c;
    return ls_unistrSplit(s, outNum, ch);
}

unistring *ls_unistrSplit(unistring s, u32 *outNum, const char *c)
{
    unistring delim = ls_unistrFromAscii((char *)c);
    unistring *result = ls_unistrSplit(s, outNum, delim);
    
    ls_unistrFree(&delim);
    return result;
}

unistring *ls_unistrSeparateByNumber(unistring s, u32 *outNum)
{
    AssertMsg(s.data, "Unistring data pointer is null\n");
    AssertMsg(outNum, "Output parameter outNum is null\n");
    
    u32 count = 0;
    u32 len = 0;
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
    
    unistring *Result = ls_unistrAllocArr(count, 16);
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
                unistring nonNumber = { BeginString, len, len};
                ls_unistrSet(Result + idx, nonNumber);
                idx += 1;
                len = 0; 
            }
            
            BeginString = At;
            while(ls_utf32IsNumber(*At) == TRUE)
            {
                if(At+1 > (s.data + s.len)) { break; }
                At += 1;
            }
            
            unistring number = { BeginString, (u32)(At - BeginString), (u32)(At - BeginString)};
            ls_unistrSet(Result + idx, number);
            idx += 1;
            
            BeginString = At;
        }
        
        if(At+1 >= (s.data + s.len)) { break; }
        At  += 1;
        len += 1;
    }
    
    if(len > 0)
    {
        unistring nonNumber = { BeginString, len+1, len+1};
        ls_unistrSet(Result + idx, nonNumber);
        idx += 1;
    }
    
    *outNum = idx;
    
    return Result;
}


unistring *ls_unistrBreakBySpaceUntilDelimiter(unistring s, u32 delimiter, u32 *numOfStrings)
{
    AssertMsg(FALSE, "Not implmented\n");
    unistring *Result = 0;
    return Result;
    
#if 0
    unistring *Result = 0;
    unistring buff[256] = {};
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
    
    Result = (unistring *)ls_alloc(sizeof(unistring)*buffIdx);
    ls_memcpy(buff, Result, sizeof(unistring)*buffIdx);
    if(numOfStrings) { *numOfStrings = buffIdx; }
    
    return Result;
#endif
}

s32 ls_unistrLeftFind(unistring s, s32 off, u32 c)
{
    AssertMsg(s.data, "Unistring data is null.\n");
    AssertMsg(off >= 0, "Offset is negative.\n");
    
    u32 *At = s.data + off;
    s32 offset = 0;
    
    b32 found = FALSE;
    while (At != (s.data + s.len))
    { 
        if(*At == c) { found = TRUE; break; }
        At++; offset++;
    }
    
    if(found) return offset;
    return -1;
}


s32 ls_unistrLeftFind(unistring s, u32 c)
{ return ls_unistrLeftFind(s, 0, c); }

s32 ls_unistrRightFind(unistring s, s32 off, u32 c)
{
    AssertMsg(s.data, "Unistring data is null.\n");
    AssertMsg(off >= 0, "Offset is negative.\n");
    
    u32 *At = s.data + off;
    s32 offset = off;
    
    b32 found = FALSE;
    while(At != s.data)
    {
        if(*At == c) { found = TRUE; break; }
        At--; offset--;
    }
    
    if(found) return offset;
    return -1;
}

s32 ls_unistrRightFind(unistring s, u32 c)
{ return ls_unistrRightFind(s, 0, c); }


s32 ls_unistrCountOccurrences(unistring s, u32 c)
{
    AssertMsg(s.data, "Unistring data is null.\n");
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

unistring ls_unistrConcat(unistring s1, unistring s2)
{
    unistring Result = ls_unistrAlloc(s1.len + s2.len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len*4); }
    if(s2.len) { ls_memcpy(s2.data, Result.data + s1.len, s2.len*4); }
    Result.len = s1.len + s2.len;
    
    return Result;
}

void ls_unistrConcatOn(unistring s1, unistring s2, unistring *out)
{
    AssertMsg(out, "Output unistring ptr is null\n");
    AssertMsg(out->data, "Output unistring data is null\n");
    AssertMsg((out->size > (s1.len + s2.len)), "Output unistring is too small to fit inputs\n");
    
    if(s1.len) { ls_memcpy(s1.data, out->data, s1.len*4); }
    if(s2.len) { ls_memcpy(s2.data, out->data + s1.len, s2.len*4); }
    out->len = s1.len + s2.len;
}

unistring ls_unistrCatChar(unistring s, u32 c)
{
    AssertMsg(s.data, "Input unistring data is null\n");
    
    unistring Result = ls_unistrAlloc(s.len + 1);
    if(s.len) { ls_memcpy(s.data, Result.data, s.len*4); }
    Result.data[s.len] = c;
    Result.len = s.len + 1;
    
    return Result;
}

unistring ls_unistrCatCStr(unistring s1, char *s2)
{
    AssertMsg(NULL, "Not implemented\n");
    unistring Result = {};
    return Result;
#if 0
    u32 s2Len = ls_len(s2);
    
    unistring Result = ls_unistrAlloc(s1.len + s2Len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2Len) { ls_memcpy(s2, Result.data + s1.len, s2Len); }
    Result.len = s1.len + s2Len;
    
    return Result;
#endif
}

void ls_unistrPrepend(unistring *s1, unistring s2)
{
    AssertMsg(s1,       "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(s2.data,  "Input unistring data is null\n");
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_unistrGrow(s1, growSize);
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

void ls_unistrPrependChar(unistring *s1, u32 c)
{
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_unistrGrow(s1, 32); }
    
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

void ls_unistrPrependCStr(unistring *s1, char *s2)
{
    AssertMsg(NULL, "Not implemented\n");
    
#if 0
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(s2, "C unistring ptr is null\n");
    
    u32 s2Len = ls_len(s2);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_unistrGrow(s1, growSize);
    }
    
    ls_memcpy(s1->data, s1->data + s2Len, s1->len);
    ls_memcpy(s2, s1->data, s2Len);
    s1->len = s1->len + s2Len;
#endif
}

void ls_unistrAppend(unistring *s1, unistring s2)
{
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(s2.data, "Input unistring data is null\n");
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_unistrGrow(s1, growSize);
    }
    
    ls_memcpy(s2.data, s1->data + s1->len, s2.len*4);
    s1->len += s2.len;
}

void ls_unistrAppendChar(unistring *s1, u32 c)
{
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    
    if(s1->len + 1 > s1->size)
    { ls_unistrGrow(s1, 32); }
    
    s1->data[s1->len] = c;
    s1->len += 1;
}

void ls_unistrAppendCStr(unistring *s1, char *c)
{
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    u32 len = ls_len(c);
    ls_unistrAppendNCStr(s1, c, len);
}

void ls_unistrAppendNCStr(unistring *s1, char *c, u32 s2Len)
{
    //NOTE: We are assuming a classical C String is ASCII
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(c, "C String ptr is null\n");
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_unistrGrow(s1, growSize);
    }
    
    u32 *At = s1->data + s1->len;
    for(u32 i = 0; i < s2Len; i++) { At[i] = (u32)c[i]; }
    s1->len += s2Len;
}

void ls_unistrAppendBuffer(unistring *s1, u32 *buff, u32 buffLen)
{
    AssertMsg(s1, "Base unistring ptr is null\n");
    AssertMsg(s1->data, "Base unistring data is null\n");
    AssertMsg(buff, "C String ptr is null\n");
    
    if(buffLen == 0) { return; }
    
    if(s1->len + buffLen > s1->size)
    {
        u32 growSize = ((s1->len + buffLen) - s1->size) + 32;
        ls_unistrGrow(s1, growSize);
    }
    
    u32 *At = s1->data + s1->len;
    ls_memcpy(buff, At, buffLen*sizeof(u32));
    s1->len += buffLen;
}


//      Merge       //
//------------------//


//------------------//
//      Stuff       //


//TODO: Should I try optimizing it for utf-32 directly, rather than converting?
unistring  ls_unistrFromInt(s64 x)
{
    char buff[32] = {};
    ls_itoa_t(x, buff, 32);
    
    unistring s = ls_unistrFromAscii(buff);
    return s;
}

void ls_unistrFromInt_t(unistring *s, s64 x)
{
    AssertMsg(s, "Unistring pointer is null");
    
    if(s->data == NULL)
    {
        unistring str = ls_unistrFromInt(x);
        *s = str;
    }
    else
    {
        char buff[32] = {};
        s32 len = ls_itoa_t(x, buff, 32);
        
        if(s->size < len)
        {
            u32 growSize = len + 32;
            ls_unistrGrow(s, growSize);
        }
        
        for(u32 i = 0; i < len; i++)
        { s->data[i] = (u32)buff[i]; }
        
        s->len = len;
    }
}

void ls_unistrFromF64_t(unistring *s, f64 x)
{
    AssertMsg(s, "Unistring ptr is null\n");
    
    if(s->data == NULL)
    {
        //TODO: Add string allocation
        AssertMsg(s->data, "Unistring data allocation is not YET implemented.\n");
    }
    else
    {
        char buff[32] = {};
        u32 len = ls_ftoa_t(x, buff, 32);
        
        if(s->size < len)
        {
            u32 growSize = len + 32;
            ls_unistrGrow(s, growSize);
        }
        
        for(u32 i = 0; i < len; i++)
        { s->data[i] = (u32)buff[i]; }
        
        s->len = len;
    }
}

s32 ls_unistrToAscii_t(unistring *s, char *buff, u32 buffMaxLen)
{
    AssertMsg(s, "Unistring pointer is null\n");
    AssertMsg(buff, "Output buffer pointer is null\n");
    
    u32 *At = s->data;
    u32 idx = 0;
    while(*At && idx < buffMaxLen)
    {
        buff[idx] = (char)(*At);
        
        At  += 1;
        idx += 1;
    }
    
    return idx;
}

s64 ls_unistrToInt(unistring s)
{
    if(s.len == 0) { return 0; }
    
    char numBuff[64] = {};
    AssertMsg(s.len < 64, "Unistring passed represents a number that contains too many digits.");
    
    u32 i = 0;
    for(i = 0; i < s.len; i++)
    {
        numBuff[i] = (char)(s.data[i]);
    }
    
    return ls_atoi(numBuff, i);
}


b32 ls_utf32IsNumber(u32 c)
{
    if(c >= U'0' && c <= U'9') { return TRUE; }
    return FALSE;
}


//VIEWS

//------------------//
//      Create      //

view ls_viewCreate(string s)
{
    view Res = {};
    
    Res.next = s.data;
    Res.len  = s.len;
    
    return Res;
}

uview ls_uviewCreate(unistring s)
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

view ls_viewNextNChars(view v, u32 n)
{
    view Result = {};
    
    Result.s = {v.next, n, n};
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
    
    Result.s = {v.next, wordLen, wordLen};
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
    
    Result.s = {v.next, lineLen, lineLen};
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
    
    Result.s = {v.next, lineLen, lineLen};
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
    
    Result.s = {v.next, n, n};
    Result.next = v.next + n;
    Result.len  = v.len - n;
    
    return Result;
}

uview ls_uviewNextDelimiter(uview v, u32 c)
{
    uview Result = {};
    
    v = ls_uviewEatWhitespace(v);
    
    u32 wordLen = 0;
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
    
    u32 wordLen = 0;
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
    
    u32 lineLen = 0;
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
    
    u32 lineLen   = 0;
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
    unistring s = v.s;
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
