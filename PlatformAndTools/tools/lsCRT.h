#ifndef LS_CRT_H
#define LS_CRT_H

#ifdef _DEBUG
#define Assert(condition) if(!(condition)){DebugBreak();}
#else
#define Assert(condition) ((void)0);
#endif

#ifdef _WIN32
#define LS_PLAT_WINDOWS
#elif __GNUC__
#define LS_PLAT_LINUX
#endif

#ifdef LS_PLAT_WINDOWS

#ifndef LS_WINDOWS_H
#include "Platform/lsWindows.h"
#endif

#define LS_STDOUT 0
#define LS_STDIN  0
#define LS_STDERR 0

#endif

#ifdef LS_PLAT_LINUX

#ifndef LS_LINUX_H
#include "Platform/lsLinux.h"
#endif

#define LS_STDOUT STDOUT_FILENO
#define LS_STDIN  STDIN_FILENO
#define LS_STDERR STDERR_FILENO

#endif

#ifndef LS_MATHS_H
#include "Maths/Maths.h"
#endif

#if 0
#ifndef LS_GRAPHICS_H
#include "lsGraphics.h"
#endif
#endif

#include <stdarg.h>

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

////////////////////////////////////////////////////
//	STRUCTURES
////////////////////////////////////////////////////

struct string;
struct v2;
union v3;
union v4;
struct v3i;

typedef struct
{
    char *ascii;
    char *value;
    char *bytecode;
    
    s32	  len; //Zero Terminated
    s32   byteLen;
} hex;

struct file
{
    char *data;
    char *curr;
    u64 size;
};

struct Date
{
    u32 milliseconds;
    u32 seconds;
    u32 minutes;
    u32 hour;
    
    u32 day;
    char *dayName;
    
    u32 month;
    char *monthName;
    
    u32 year;
};

struct Bitmap
{
    void *data;
    
    u32 width;
    u32 height;
    
    u32 headerSize;
    u32 compression;
    u32 pixelBufferSize;
    
    u64 size;
};

struct PNG
{
    char *compressedData;
    
    u32 width;				//In pixels
    u32 height;				//In pixels
    
    /*n° of bits per sample (or per palette index, not per pixel) i.e. 1, 2, 4, 8, 16 (only some are possible per colorType)*/
    u8 bitDepth;
    
    /*Valid values (with associated bitDepth possible values) are 
 0 - Greyscale			(bitDepth = 1, 2, 4, 8, 16)
 2 - Truecolor			(bitDepth = 8, 16)
 3 - IndexedColor		(bitDepth = 1, 2, 4, 8)
 4 - Greyscale & Alpha	(bitDepth = 8, 16)
 6 - Truecolor & alpha	(bitDepth = 8, 16)*/
    u8 colorType;
    
    /*Will always be 0 (Deflate / Inflate compression method is the International Standard*/
    u8 compressionMethod;
    
    /*Indicates the preprocessing method applied before compression. 
 Will always be 0 (adaptive filtering with 5 basic filter types is the International Standard)*/
    u8 filterMethod;
    
    /*0 - No interlace, 1 - Adam7 interlace*/
    u8 interlaceMethod;
    
    /*Contains from 1 to 256 pallete entries*/
    v3 *palette;
    
    /*Information used in optional blocks*/
    
    /*bKGD*/
    u8 defaultBackgroundIndex;
    u16 defaultBackgroundGreyscale;
    v3i defaultBackgroundColor;
    
    /*cHRM*/
    v2 whitePoint;
    v2 redChrom;
    v2 greenChrom;
    v2 blueChrom;
    
    /*gAMA*/
    f32 gamma;
    
    /*pHYs*/
    u32 pixelsPerUnit_X;
    u32 pixelsPerUnit_Y;
    u8 unitSpecifier; // 0 is Unkown, 1 is one metre;
    
    u64 size;
    
    operator Bitmap() 
    {
        Bitmap bitmap = { 0 };
        bitmap.data = compressedData;
        
        bitmap.width = width;
        bitmap.height = height;
        
        bitmap.headerSize = 0;
        bitmap.compression = 0;
        bitmap.pixelBufferSize = bitDepth;
        
        bitmap.size = size;
        
        return bitmap;
    }
};

struct MD5_128
{
    u32    v32[4]; 
    u64    v64[2];
    char   v128[16];
};

/*forward declare lsWindows functions? */
#ifdef LS_PLAT_WINDOWS
u64 windows_ReadCosole(char *, u32);
u64 windows_ReadFile(char *, char **, u32);
u64 windows_ReadFileByOffset(char *, char **, u64, u32);
u64 windows_WriteConsole(char *, u32);
u64 windows_WriteFile(char *, void *, u32, b32);
u32 windows_countFilesInDir(char *);
u32 windows_countFilesInDirByExt(char *, char *);
void windows_getFileNamesInDir(char *, u32, char **, u32 *, u32 *);
void windows_getFileNamesInDirByExt(char *, u32, char *, u32, char **, u32 *, u32 *);
u32 windows_getFullPathName(char *fileName, u32 outBufferSize, char *outBuffer);
u64 windows_GetWindowsTimeInMicrosec();
u64 windows_GetWindowsTimeIn100Nanosec();
u32 windows_GetUnix32Time();
u64 windows_GetUnix64Time();
windowsDate windows_GetDate(b32);
void windows_setupWindow(WindowInfo *);
void windows_setupOpenGLContext(WindowInfo *);
void windows_sleep(u64 milliseconds);
#endif

#ifdef LS_PLAT_LINUX
u64 linux_ReadConsole(s32, char *, u32);
u64 linux_ReadFile(char *, char **, u32);
u64 linux_WriteConsole(s32, char *, u32);
u64 linux_WriteFile(char *, void *, u32);
u64 linux_GetTime();
linuxDate linux_GetDate(b32);
#endif

extern "C"
{
    ////////////////////////////////////////////////////
    //	MATH FUNCTIONS
    ////////////////////////////////////////////////////
    
    s32 ls_abs(s32 x);
    f32 ls_fabs(f32 x);
    u64 ls_fact(u32 x);
    s64 ls_e10(s32 x);
    s64 ls_powi(s64 v, u32 exp);
    f64 ls_powf(f64 v, s32 exp);
    s64 ls_truncate(f64 x);
    f64 ls_truncEpsilon(f64 x);
    f32 rad(f32 x);
    f32 ls_sqrt(f32 x);
    
    string *ls_findNthPermutation(char *elementArr, u32 sizeOfElementArr, u32 termPosition); // Find the nth permutation of the lexicographic permutations of elementArr
    
#ifdef GENERATE_TABLES
    void ls_powersOfTwo(u32 lastPower); // lastPower indicates how many powers of two have to be computed.
    //void ls_fibonacciSequence(u32 lastNumberSize); // lastNumberSize indicates log10 of the last number in the computed sequence.
    
    void ls_primes(u64 upperLimit); // upperLimit indicates the largest possible prime to compute
#endif
    
    ////////////////////////////////////////////////////
    //	TRASCENDENTAL FUNCTIONS
    ////////////////////////////////////////////////////
    
    f64 ls_sine(f64 x);
    f64 ls_asin(f64 x);
    f64 ls_cos(f64 x);
    f64 ls_acos(f64 x);
    f64 ls_tan(f64 x);
    f64 ls_atan(f64 x);
    
    ////////////////////////////////////////////////////
    //	STRING FUNCTIONS
    ////////////////////////////////////////////////////
    
    char    ls_lowerCase(char c);
    b32	 ls_isANumber(char c);
    char	ls_itoc(s64 x);
    u32	 ls_ctoi(char c);
    
    string  ls_itoa(s64 x);
    string  ls_itoh(u64 x);
    s64     ls_stoi(string s);
    f32	 ls_atof(string s, int size);
    string  ls_ftoa(f32 x);
    
    string  ls_strstr(string s1, string s2);
    void    ls_concat(string s1, string s2);
    s32     operator==(string s1, string s2);
    void    ls_strcpy(string src, string dst);
    void	ls_strncpy(string src, string dst, size_t size);
    
    string  ls_breakUntilLine(string *data, u32 *bytesRead);
    string  ls_breakUntilSpace(string *data, u32 *bytesRead);
    
    string  *ls_breakByLine(string *data, u32 *numOfLines);
    string  *ls_breakBySpace(string *data, u32 *numOfStrings);
    string  *ls_breakBySpaceDelimiter(string *data, char delimiter, u32 *numOfStrings);
    u32	 ls_offsetToFirstChar(string *data, char c);
    
    
    void	ls_alphaOrder(char **names, u32 numOfNames);
    
    s32 	ls_sprintf(char *dest, const char *format, ...);
    s32 	ls_printf(const char *format, ...);
    char    ls_getc();
    
    ////////////////////////////////////////////////////
    //	FILE MANIPULATION FUNCTIONS
    ////////////////////////////////////////////////////
    
    void ls_getFileNameFromPath(char *Path, char *out);
    void ls_getFileExtension(char *Path, char *out);
    
    //If bytesToRead is set to 0 the entire file will be read.
    u64  ls_readFile(char *Path, char **Dest, u32 bytesToRead);
    u64  ls_ReadFileByOffset(string *Path, char **Dest, u64 offset, u32 bytesToRead);
    void ls_readFileString(char *Path, string *dest, u32 bytesToRead);
    u64  ls_writeFile(string *Path, void *Source, u32 bytesToWrite, b32 append);
    u32  ls_countFilesInDir(string *Directory);
    u32  ls_countFilesInDirByExt(string *Directory, string *extension);
    u32  ls_getFileNamesInDir(string Dir, string **names);
    u32  ls_getFileNamesInDirByExt(string *Dir, string *ext, string **names);
    
    string *ls_getFullPathName(char *name);
    
    void ls_loadBitmap(char *Path, Bitmap *bitmap);
    void ls_loadCompressedPNG(char *Path, PNG *png);
    void ls_Deflate(char *data, u64 inputSize, char *out);
    
    ////////////////////////////////////////////////////
    //	GENERAL PURPOSE SYSTEM FUNCTIONS
    ////////////////////////////////////////////////////
    
    /* The resolution depends on the OS:
  In Windows the epoch is January 1st, 1601 (UTC) and the value is 
  returned in microseconds (even tough resoultion is 100-nanoseconds intervals)
  In Linux the epoch is ***  and the value is returned in *** */
    u64 ls_getTimeSinceEpochInMicrosec();
    u64 ls_getTimeSinceEpochIn100Nanosec();
    
    u32 ls_getUnix32Time(); //NOTE: In seconds
    u64 ls_getUnix64Time(); //NOTE: In seconds
    
    /* If false UTC time is returned instead */
    Date ls_getDateTime(b32 local);
    
    void ls_sleep(u64 milliseconds);
    
    /* Function for creating and opening a window*/
    void ls_setupWindow(WindowInfo info);
    void ls_setupOpenGLContext(WindowInfo *Info);
    
    ////////////////////////////////////////////////////
    //	CRYPTOGRAPHY FUNCTIONS
    ////////////////////////////////////////////////////
    
    u16 btol16(u8 *At);
    u32 btol32(u8 *At);
    u64 btol64(u8 *At);
    
    MD5_128 ls_MD5(string &v);
    
    void ls_setupHex(hex *h, char *ascii);
    
    void ls_hexASCIIToValue(hex *h);
    void ls_hexValueToASCII(hex *h);
    void ls_hexToBytecode(hex *h);
    
    char *ls_hexTo64Value(hex *h);
    char *ls_hexTo64ASCII(hex *h);
    
    char *ls_stringFixedXOR(hex *h1, hex *h2);
    char *ls_stringVariableXOR(hex *h1, hex *h2);
    void ls_charVariableXOR(hex *h, char c, char *dest);
    
    s32  ls_scoreSentence(char *s);
    
    ////////////////////////////////////////////////////
    //	MEMORY FUNCTIONS
    ////////////////////////////////////////////////////
    
    void ls_memcpy(void *src, void *dest, size_t size);
    u32  ls_memcmp(void *a, void *b, size_t size);
    void ls_zeroMem(void *mem, size_t size);
    void ls_zeroMemASM(void *mem, size_t size);
    void ls_zeroString(void *mem, size_t size);
    void *ls_alloc(u64 size);
    void *ls_realloc(void *originalMem, u64 oldSize, u64 newSize);
    void ls_free(void *p);
    
    ////////////////////////////////////////////////////
    //	INTRINSICS
    ////////////////////////////////////////////////////
    
    u32 Log10(u64 value);
    u32 LeadingZeros32(u32 value);
    u32 LeadingZeros64(u64 value);
    u16 ByteSwap16(u16 value);
    u32 ByteSwap32(u32 value);
    u64 ByteSwap64(u64 value);
    f32 Ceil(f32 v);
}

//@TODO: I really don't like the C++-ness of this string code... Could I clean it up in any way?
struct string
{
    char *data = 0;
    u32  len = 0;
    u32  size = 0;
    
    string(const char *src)
    {
        // If string was already in use,
        // free old data
        if(data) { ls_free(data); }
        
        len = ls_len((char *)src);
        
        if(len != 0)
        {
            size = len + 1;
            data = (char *)ls_alloc(sizeof(char) * (len + 1));
            ls_memcpy((void *)src, (void *)data, len);
            data[len] = 0;
        }
        else
        {
            size = 8;
            len = 0;
            data = (char *)ls_alloc(sizeof(char) * 8);
        }
    }
    
    string(char *src)
    {
        // If string was already in use,
        // free old data
        if(data) { ls_free(data); }
        
        len = ls_len(src);
        if(len != 0)
        {
            size = len + 1;
            data = (char *)ls_alloc(sizeof(char)*(len + 1));
            ls_memcpy(src, data, len);
            data[len] = 0;
        }
        else
        {
            size = 8;
            len = 0;
            data = (char *)ls_alloc(sizeof(char) * 8);
        }
    }
    
    string(int v)
    {
        // If string was already in use,
        // free old data
        if(data) { ls_free(data); }
        
        len = 0;
        size = v;
        data = (char *)ls_alloc(v);
    }
    
    /*Copy-Constructor Obj::Obj(Obj &T // const Obj &T // volatile Obj &T) 
*  Happens when:
*  1)
*     struct Obj a = someFunc();
*
*  2) 
*     struct Obj b = ...;
 *     struct Obj a = b;
*/
    string(string &s)
    {
        size = s.size;
        len  = s.len;
        
        data = (char *)ls_alloc(sizeof(char) * size);
        ls_memcpy(s.data, data, size);
    }
    
    
    /*Copy Assignment Operator Obj::Obj operator=(Obj T // Obj &T // const Obj &T // volatile Obj &T // const volatile Obj &T)
*  Happens when:
*  1)
    *     struct Obj a = ...;
*     struct Obj b = ...;
*     a = b
*
*  2)
*     struct Obj *a = ...;
*     struct Obj b = ...;
  *     a = alloc();
  *     *a = b;
  *
  *  3)
  *     struct Obj *a = ...;
  *     a = alloc();
  *     *a = someFunc(); Because it becomes an l-value reference.
  */
    /*
    string operator=(string a)
    {
        if(data) { ls_free(data); }
        
        size = a.size;
        len = a.len;
        data = (char *)ls_alloc(size);
        ls_memcpy((void *)a.data, (void *)data, size);
        return *this;
    }
    */
    
    string(string *s)
    {
        // If string was already in use,
        // free old data
        if(data) { ls_free(data); }
        
        size = s->size;
        len = s->len;
        data = (char *)ls_alloc(size);
        ls_memcpy((void *)s->data, (void *)data, size);
    }
    
    string()
    { 
        // If string was already in use,
        // free old data
        if(data) { ls_free(data); }
        
        data = 0; size = 0; len = 0;
    }
    
    //Not sure how to make this work
#if 0
    ~string()
    { free(); }
#endif
    
    //
    // Need to test operator overloading for memory leaks. I think I'm good but, who knows?
    //
    
    string operator+(string w)
    {
        string result; 
        
        u32 resultSize = len + w.len;
        char *resultData = (char *)ls_alloc(resultSize + 1);
        
        ls_memcpy((void*)data, (void *)resultData, len);
        ls_memcpy((void*)w.data, (void *)(resultData + len), w.len);
        
        result.data = resultData; result.size = resultSize + 1;
        result.len = resultSize;
        
        return result;
    }
    
    void operator+=(string w)
    {
        if(w.len + len > size)
        {
            char *tmpData = data;
            *this = *this + w;
            ls_free(tmpData);
        }
        else
        { ls_memcpy((void *)w.data, (void *)(data + len), w.len); len += w.len; }
        
        return;
    }
    
    string operator+(char c)
    {
        // Size has to be 1 bigger than len
        // And we need 1 more space for the new char
        string result = len + 1;
        
        ls_memcpy((void *)data, (void *)result.data, len);
        data[len] = c;
        
        return result;
    }
    
    void operator+=(char c)
    {
        if(len + 1 > size)
        {
            char *tmpData = data;
            *this = *this + c;
            ls_free(tmpData);
        }
        else
        { data[len] = c; len++; }
        
    }
    
    bool operator==(string w)
    {
        if (ls_strcmp(this->data, w.data) == 0)
        { return true; }
        else { return false; }
    }
    
    bool operator==(char c)
    {
        if ((this->size == 1) && (*this->data == c))
        { return TRUE; }
        
        return FALSE;
    }
    
    bool operator==(char *c)
    {
        int result = ls_strcmp(data, c);
        
        return (result == 0) ? TRUE : FALSE;
    }
    
    bool operator!=(string w)
    {
        if (ls_strcmp(this->data, w.data) == 0)
        { return false; }
        else { return true; }
    }
    
    void nullTerminate()
    { 
        if(len == 0) { return; }
        
        b32 check = FALSE;
        
        if(len < size)
        { check = data[len] != 0; }
        else if (len == size)
        { check = data[size - 1] != 0; }
        
        if(check)
        {
            char *newData = (char *)ls_alloc(sizeof(char)*(len+1));
            size = len+1;
            
            ls_memcpy(data, newData, len);
            newData[size-1] = 0;
            
            ls_free(data);
            
            data = newData;
        }
        return;
        
    }
    
    void reverse()
    {
        char *Begin = data;
        char *End = data + len;
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
    
    void remove(u32 idx)
    { this->removeSubstr(idx, idx); }
    
    string substr(u32 beginIdx, u32 _endIdx = (u32)-1)
    {
        u32 endIdx = 0;
        if(_endIdx == (u32)-1) { endIdx = len-1; }
        else { endIdx = _endIdx; }
        
        if((beginIdx < 0 || beginIdx >= size) || 
           (endIdx < 0 || endIdx >= size) || 
           (endIdx - beginIdx >= size))
        { string error = ""; return error; }
        
        // Need NULL terminator cause I haven't changed
        // All my functions to work with strings yet...
        string result = ((endIdx - beginIdx) + 1) + 1;
        
        ls_memcpy(this->data + beginIdx, result.data, result.size);
        
        result.len = (endIdx - beginIdx + 1);
        result.data[result.len] = 0;
        
        return result;
    }
    
    void removeSubstr(u32 beginIdx, u32 endIdx)
    {
        if((beginIdx < 0 || beginIdx >= size) || 
           (endIdx < 0 || endIdx >= size) || 
           (endIdx - beginIdx >= size))
        { return; }
        
        u32 remove = ((endIdx - beginIdx) + 1);
        remove = remove > len ? len : remove;
        ls_memcpy((void *)(data + endIdx + 1), (void *)(data + beginIdx), len - remove); 
        len -= remove;
        data[len] = 0;
        
        return;
    }
    
    u32 leftFind(char *s, u32 _startingPos = (u32)-1)
    {
        u32 startingPos = 0;
        if(_startingPos == (u32)-1) { startingPos = 0; }
        else { startingPos = _startingPos; }
        
        u32 indexResult = 0;
        
        u32 subStrLen = ls_len(s);
        char *i = (data + subStrLen + startingPos);
        char *subStr = (char *)ls_alloc(sizeof(char) * subStrLen);
        
        while(i < (data + len))
        {
            ls_memcpy((void *)(i - subStrLen), (void *)subStr, subStrLen);
            if(ls_strcmp(s, subStr) == 0)
            { ls_free(subStr); return indexResult; }
            
            indexResult++;
            i++;
        }
        
        ls_free(subStr);
        return (u32)-1;
    }
    
    u32 rightFind(char *s, u32 startingPos = (u32)-1)
    {
        u32 indexResult = (len - 1);
        
        u32 subStrLen = ls_len(s);
        char *i = 0; 
        
        if(startingPos == (u32)-1) { i = (data + len - subStrLen); }
        else { i = (data + startingPos - subStrLen); }
        
        char *subStr = (char *)ls_alloc(sizeof(char) * subStrLen);
        
        while(i > data)
        {
            ls_memcpy((void *)(i + subStrLen), (void *)subStr, subStrLen);
            if(ls_strcmp(s, subStr) == 0)
            { ls_free(subStr); return indexResult; }
            
            indexResult--;
            i--;
        }
        
        ls_free(subStr);
        return (u32)-1;
    }
    
    string *extractLine()
    {
        u32 toRemove = 0;
        while(this->data[toRemove] != '\n')
        { toRemove++; }
        
        u32 i = toRemove - 1;
        
        if(this->data[i] == '\r') { i -= 1; }
        
        string *result = (string *)ls_alloc(sizeof(string));
        *result = i+1;
        
        ls_memcpy(this->data, result->data, i+1);
        result->len += (i+1);
        
        this->removeSubstr(0, toRemove);
        
        result->nullTerminate();
        
        return result;
    }
    
    string *extractDelimiter(char c)
    {
        u32 toRemove = 0;
        while((this->data[toRemove] != '\n') && 
              (this->data[toRemove] != c) && (this->data[toRemove] != 0))
        { toRemove++; }
        
        u32 i = toRemove - 1;
        
        if(this->data[i] == '\r') { i -= 1; }
        
        string *result = (string *)ls_alloc(sizeof(string));
        *result = i+1;
        
        ls_memcpy(this->data, result->data, i+1);
        result->len += (i+1);
        
        this->removeSubstr(0, toRemove);
        
        result->nullTerminate();
        
        return result;
    }
    
    u32 lastIdx()
    { return len - 1; }
    
    void free()
    {
        if(this->data) { ls_free(this->data); }
        this->data = 0;
        size = 0;
        len = 0;
    }
};

struct dataBuffer
{
    void *data;
    u32 used;
    u32 size;
    
    dataBuffer()
    {
        data = ls_alloc(sizeof(char)*64);
        used = 0;
        size = 64;
    }
    
    dataBuffer(u32 s)
    {
        data = ls_alloc(sizeof(char)*s);
        used = 0;
        size = s;
    }
    
    dataBuffer(u8 *a, u32 arrSize)
    {
        data = ls_alloc(sizeof(char)*(arrSize + 64));
        ls_memcpy(a, data, arrSize);
        used = arrSize;
        size = arrSize + 64;
    }
    
    void init(u32 s = 0)
    {
        if(s == 0) { data = ls_alloc(sizeof(char)*64); size = 64; }
        else { data = ls_alloc(sizeof(char)*s); size = s; }
        
        used = 0;
    }
    
    dataBuffer operator+(u8 v)
    {
        u32 newSize = used < size ? size : size + 64;
        dataBuffer Result = newSize;
        
        ls_memcpy(data, Result.data, used);
        Result.used = used + 1;
        *((u8 *)Result.data + used) = v;
        return Result;
    }
    
    void operator+=(u8 v)
    {
        this->add(&v, sizeof(u8));
    }
    
    
    dataBuffer operator+(u16 v)
    {
        u32 newSize = used < (size - 1) ? size : size + 64;
        dataBuffer Result = newSize;
        
        ls_memcpy(data, Result.data, used);
        Result.used = used + 2;
        *(u16 *)((u8 *)Result.data + used) = v;
        return Result;
    }
    
    void operator+=(u16 v)
    {
        this->add(&v, sizeof(u16));
    }
    
    dataBuffer operator+(u32 v)
    {
        u32 newSize = used < (size - 3) ? size : size + 64;
        dataBuffer Result = newSize;
        
        ls_memcpy(data, Result.data, used);
        Result.used = used + 4;
        *(u32 *)((u8 *)Result.data + used) = v;
        return Result;
    }
    
    void operator+=(u32 v)
    {
        this->add(&v, sizeof(u32));
    }
    
    dataBuffer operator+(u64 v)
    {
        u32 newSize = used < (size - 7) ? size : size + 64;
        dataBuffer Result = newSize;
        
        ls_memcpy(data, Result.data, used);
        Result.used = used + 8;
        *(u64 *)((u8 *)Result.data + used) = v;
        return Result;
    }
    
    void operator+=(u64 v)
    {
#if 0
        if(used < size - 7)
        {
            *(u64 *)((u8 *)data + used) = v;
            used += 8;
            return;
        }
        
        data = ls_realloc(data, size, size + 64);
        size = size + 64;
        
        *(u64 *)((u8 *)data + used) = v;
        used += 8;
        return;
#endif
        this->add(&v, sizeof(u64));
    }
    
    void add(void *v, u32 len)
    {
        if(used <= (size - len))
        {
            ls_memcpy(v, (u8 *)data + used, len);
            used += len;
            return;
        }
        
        data = ls_realloc(data, size, size + len + 64);
        size = size + len + 64;
        
        ls_memcpy(v, (u8 *)data + used, len);
        used += len;
        return;
    }
    
    void free()
    {
        if(data) {ls_free(data);}
        data = 0;
        size = 0;
        used = 0;
    }
};

struct hashtable
{
    struct hashEntry
    {
        string id;
        s32 val;
        hashEntry *next = 0;
    };
    
    hashEntry *entries;
    u32 size;
    u32 elementsInTable;
    u32 longestLink;
    
    u32 (*hashFunction)(void *, u32) = 0;
    
    u32 baseHash(void *d, u32 s)
    {
        /* For some reason I was doing this
        * u32 it = -1;
        * Why was I starting at -1??
        */
        char *At = (char *)d;
        u32 it = (At[0] - 'A');
        for (u32 i = 1; i < s; i++)
        {
            it += (At[i] * i);
        }
        return it % size;
    }
    
    void growTable()
    {
        hashEntry *newEntries = (hashEntry *)ls_alloc(sizeof(hashEntry)*size * 2);
        size = size * 2;
        longestLink = 0; elementsInTable = 0;
        
        hashEntry *temp = entries;
        entries = newEntries;
        
        for (u32 i = 0; i < size / 2; i++)
        {
            if (temp[i].id.data != 0)
            {
                add(temp[i].id, temp[i].val);
                hashEntry *At = &temp[i];
                while (At->next != 0)
                {
                    At = At->next;
                    add(At->id, At->val);
                }				
            }
        }
        
        ls_free((void *)temp);
    }
#if 0
    //hashtable shouldn't have a construct, especially without a desctructor
    //see automatic initialization of object from inside a struct.
    // struct x { hashtable table; }
    // How do I force the table to construct differently than this constructor?
    // I CANT!
    hashtable(u32 tableSize = 64, u32 (*func)(string) = 0)
    {
        size = tableSize;
        entries = (hashEntry *)ls_alloc(sizeof(hashEntry) * size);
        elementsInTable = 0; longestLink = 0;
        
        if (func) { hashFunction = func; }
    }
#endif
    
    void Init(u32 tableSize, u32 (*func)(void *, u32) = 0)
    {
        size = tableSize;
        entries = (hashEntry *)ls_alloc(sizeof(hashEntry) * size);
        elementsInTable = 0; longestLink = 0;
        
        if (func) { hashFunction = func; }
    }
    
    void add(string id, u32 value)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        
        if (longestLink > 3)
        {
            growTable();
        }
        
        if (entries[index].id.data == 0)
        {
            entries[index].id = id;
            entries[index].val = value;
            elementsInTable++;
        }
        else
        {
            hashEntry *At = &entries[index]; u32 linkLength = 0;
            while (At->next != 0) { At = At->next; linkLength++; }
            At->next = (hashEntry *)ls_alloc(sizeof(hashEntry));
            At = At->next; linkLength++;
            At->id = id; At->val = value;
            elementsInTable++;
            
            if (linkLength > longestLink) { longestLink = linkLength; }
        }
    }
    
    u32 addUnique(string id, u32 value)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        
        if (longestLink > 3)
        {
            growTable();
        }
        
        if (entries[index].id.data == 0)
        {
            entries[index].id = &id;
            entries[index].val = value;
            elementsInTable++;
            return index;
        }
        else
        { return -1; }
    }
    
    u32 find(string id)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        if (entries[index].id != id)
        {
            hashEntry *At = &entries[index];
            while (At->id != id)
            {
                if (At->next == 0) { Assert(false); }
                At = At->next;
            }
            return At->val;
        }
        return entries[index].val;
    }
    
    s32 findLargest()
    {
        // NOTE: TOOD: This doesn't look through the linked list for
        // Colliding entries...
        s32 largest = -2147483647;
        for (u32 i = 0; i < size; i++)
        {
            largest = entries[i].val > largest ? entries[i].val : largest;
        }
        
        return largest;
    }
    
    void modify(string id, u32 val)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        if (entries[index].id != id)
        {
            hashEntry *At = &entries[index];
            while (At->id != id)
            {
                if (At->next == 0) { Assert(false); }
                At = At->next;
            }
            At->val = val;
        }
        entries[index].val = val;
    }
    
    void addTo(string id, s32 addend)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        if (entries[index].id != id)
        {
            hashEntry *At = &entries[index];
            while (At->id != id)
            {
                if (At->next == 0) { Assert(false); }
                At = At->next;
            }
            At->val += addend;
        }
        entries[index].val += addend;
    }
    
    void subTo(string id, s32 subdend)
    {
        u32 index = hashFunction ? hashFunction(id.data, id.size) : baseHash(id.data, id.size);
        if (entries[index].id != id)
        {
            hashEntry *At = &entries[index];
            while (At->id != id)
            {
                if (At->next == 0) { Assert(false); }
                At = At->next;
            }
            At->val -= subdend;
        }
        entries[index].val -= subdend;
    }
};

struct Array
{
    void *data;
    u32 type;
    
    u32 size;
    u32 usedSize;
    
    Array()
    { data = 0; type = 0; size = 0; usedSize = 0; }
    
    void *operator[](u32 idx)
    {
        return (void *)((char *)data + (idx*type));
    }
    
    void createArray(u32 dim, size_t sizeOfType)
    {
        data = ls_alloc((u32)sizeOfType * dim);
        type = (u32)sizeOfType;
        size = dim;
        usedSize = 0;
    }
    
    void populate(void *src, size_t sizeOfType, u32 elements)
    {
        ls_memcpy(src, data, sizeOfType*elements);
        usedSize = elements;
    }
    
    void resize(s32 amount)
    {
        void *newData = ls_alloc((size + amount)*type);
        ls_memcpy(data, newData, (size*type));
        ls_free(data);
        
        size = (size + amount);
        data = newData;
    }
    
    void remove(u32 index)
    {
        if (usedSize <= 0) { return; }
        
        char *From = ((char *)data) + ((index + 1)*type);
        char *To = ((char *)data) + (index*type);
        u32 amount = (usedSize*type) - ((index + 1)*type);
        
        ls_memcpy((void *)From, (void *)To, amount);
        ls_zeroMem((void*)(((char *)data) + ((usedSize - 1)*type)), type);
        usedSize--;
        
        if (usedSize <= (size / 2))
        {
            s32 amountToResize = -(s32)(size / 4);
            resize(amountToResize);
        }
    }
    
    void remove(void *element)
    {
        for (u32 i = 0; i < usedSize; i++)
        {
            void *currElement = (u8*)data + (i*type);
            if (ls_memcmp(currElement, element, type) == 0)
            { remove(i); }
        }
    }
    
    void insert(void *value)
    {
        if (usedSize == size)
        {
            resize(16);
        }
        
        char *From = (char *)value;
        char *To = ((char *)data) + (usedSize*type);
        ls_memcpy((void *)From, (void *)To, type);
        
        usedSize++;
    }
    
    b32 hasElement(void *element)
    {
        char *b1 = (char *)ls_alloc(type);
        char *b2 = (char *)ls_alloc(type);
        ls_memcpy(element, b2, type);
        
        char *At;
        for (u32 i = 0; i < usedSize; i++)
        {
            At = ((char *)data) + (i*type);
            ls_memcpy(At, b1, type);
            
            if (ls_memcmp(b1, b2, type) == 0)
            { return TRUE; }
            
            ls_zeroMem(b1, sizeof(b1));
        }
        
        return FALSE;
    }
    
    b32 hasElement(void *element, u32 *index)
    {
        char *b1 = (char *)ls_alloc(type);
        char *b2 = (char *)ls_alloc(type);
        ls_memcpy(element, b2, type);
        
        char *At;
        for (u32 i = 0; i < usedSize; i++)
        {
            At = ((char *)data) + (i*type);
            ls_memcpy(At, b1, type);
            
            if (ls_memcmp(b1, b2, type) == 0)
            {
                *index = i;
                return TRUE;
            }
            
            ls_zeroMem(b1, sizeof(b1));
        }
        
        return FALSE;
    }
};

struct Tree
{
    struct Node
    {
        u64 Data;
        
        Array Children;
        Node *Parent;
        
        Node()
        { Data = 0;  Children.createArray(2, sizeof(Node *)); Parent = 0; }
        
        void newChild(Node *child)
        { 
            Children.insert((void*)child);
            child->Parent = this;
        }
    };
    
    Node *Root;
    u32 numOfNodes;
    
    Tree()
    {
        Root = (Node *)ls_alloc(sizeof(Node)); 
        numOfNodes = 1;
    }
    
    void newChild(Node *parent, Node *child)
    { parent->newChild(child); }
    
};

/*When does JAI come out? I hate this, but I don't want to deal...*/
template<class T>
struct stack
{
    struct stack_element
    {
        stack_element *prev;
        T value;
    };
    
    stack_element *head;
    u32 numElements;
    
    void push(T val)
    {
        
        stack_element *e = (stack_element *)ls_alloc(sizeof(stack_element));
        e->prev = head;
        e->value = val;
        head = e;
        numElements++;
    }
    
    T pop()
    {
        T result = head->value;
        stack_element *p = head;
        head = head->prev;
        numElements--;
        ls_free(p);
        
        return result;
    }
    
    T top()
    { return head->value; }
    
    b32 isEmpty()
    { return (numElements == 0); }
    
    //Pops every element from src, pushing them into dest(this).
    //The order gets inverted.
    void pushInv(stack<T> *src)
    {
        u32 n = src->numElements;
        for(u32 i = 0; i < n; i++)
        { this->push(src->pop()); }
    }
    
    //Pops every element from src, pushing them into dest(this).
    //Order is mantained.
    void push(stack<T> *src)
    {
        u32 n = src->numElements;
        T *el = (T *)ls_alloc(sizeof(T)*n);
        if(!el) { return; }
        
        for(u32 i = 0; i < n; i++)
        { el[i] = src->pop(); }
        
        for(u32 i = n; i != 0; i--)
        { this->push(el[i-1]); }
        
        ls_free(el);
    }
};

#endif

#ifdef LS_CRT_IMPLEMENTATION

#include "FunctionTables/FunctionTables.h"
#include <immintrin.h>

#ifdef LS_PLAT_WINDOWS
#include <intrin.h>
#endif

#ifdef LS_PLAT_LINUX
#include <x86intrin.h>
#endif

////////////////////////////////////////////////////
//	MATH FUNCTIONS
////////////////////////////////////////////////////

s32 ls_abs(s32 x)
{
    return (x < 0) ? x*(-1) : x;
}

f32 ls_fabs(f32 x)
{
    return (x < 0.0f) ? x*(-1.0f) : x;
}

u64 ls_fact(u32 x)
{
    if (x <= 2) return x;
    return x*ls_fact(x - 1);
}

s64	ls_e10(s32 x)
{
    s64 Result = 1;
    for (int i = 0; i < x; i++) { Result *= 10; }
    return Result;
}

s64 ls_powi(s64 v, u32 exp)
{
    s64 Result = 1;
    while (exp)
    {
        if (exp & 1)
        { Result *= v; }
        
        exp >>= 1;
        v *= v;
    }
    return Result;
}

f64 ls_powf(f64 v, s32 exp)
{
    f64 Result = 1.0f;
    while (exp)
    {
        Result *= v;
        exp--;
    }
    
    return Result;
}

s64	ls_truncate(f64 x)
{
    return s64(x + 0.5f);
}

f64 ls_truncEpsilon(f64 x)
{
    u64 value = (u64)x;
    
    if(((f64)(value + 1) - x) < 0.005f)
    { return f64(value + 1); }
    
    return x;
}

f32 rad(f32 x)
{
    return ((x*PI_32) / 180.0f);
}

f32 ls_sqrt(f32 x)
{
#ifdef LS_PLAT_WINDOWS
    __m128 Result = _mm_set_ps1(x);
    Result = _mm_rsqrt_ps(Result);
    
    return (1 / Result.m128_f32[0]);
#endif
    
#ifdef LS_PLAT_LINUX
    f32 Result = __builtin_sqrtf(x);
    return Result;
#endif
}

string *ls_findNthPermutation(char *elementArr, u32 sizeOfElementArr, u32 termPosition)
{
    string *result = (string *)ls_alloc(sizeof(string) * 1);
    u64 numOfTerms = ls_fact(sizeOfElementArr);
    
    if (termPosition > numOfTerms)
    {
        *result = elementArr;
        return result;
    }
    
    if (termPosition == numOfTerms)
    {
        *result = elementArr; result->reverse();
        return result;
    }
    
    *result = sizeOfElementArr;
    
    string elementBuffer = elementArr;
    u32 elementBufferSize = elementBuffer.size;
    
    u32 consideredElements = sizeOfElementArr - 1;
    u32 currentPermutation = 1;
    u32 idx = 0;
    char currElement = elementBuffer.data[idx];
    
    while (currentPermutation != termPosition)
    {
        u32 addend = (u32)ls_fact(consideredElements);
        if ((currentPermutation + addend) < termPosition)
        {
            currentPermutation += addend;
            idx = (idx == elementBufferSize - 1) ? 0 : idx + 1;
            currElement = elementBuffer.data[idx];
        }
        else if ((currentPermutation + addend) > termPosition)
        {
            *result += currElement;
            elementBuffer.remove(currElement);
            elementBufferSize--;
            consideredElements--;
            idx = 0;
        }
        else if ((currentPermutation + addend) == termPosition)
        {
            currentPermutation += addend;
            idx = (idx == elementBufferSize - 1) ? 0 : idx + 1;
            currElement = elementBuffer.data[idx];
            while (elementBufferSize)
            {
                *result += currElement;
                elementBuffer.remove(currElement);
                elementBufferSize--;
                consideredElements--;
                idx = 0;
                currElement = elementBuffer.data[idx];
            }
        }
    }
    
    return result;
}

#ifdef GENERATE_TABLES
void ls_powersOfTwo(u32 lastPower)
{
    u32 sizeOfBiggestPower = u32(0.3010299957f * lastPower); // This is the log10 of the last Power which tells me approximately the number of digits of it.
    u32 *a = (u32 *)ls_alloc(sizeof(u32)*(sizeOfBiggestPower+2));
    
    u32 m = 1;
    u32 carry = 0;
    a[0] = 1;
    
    char bufferBegin[] = "char powersOfTwo[][] = \r\n{\r\n\t";
    char bufferBeginLine[] = "{\"";
    char bufferEndLine[] = "\"},\r\n\t";
    ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferBegin, sizeof(bufferBegin)-1, TRUE);
    
    char *bufferPowers = (char *)ls_alloc(lastPower);
    u32 idx = 0;
    
    for (u32 i = 1; i <= lastPower; i++)
    {
        for (u32 j = 0; j < m; j++)
        {
            int x = a[j] * 2 + carry;
            a[j] = x % 10;
            carry = x / 10;
        }
        while (carry != 0)
        {
            a[m++] = carry % 10;
            carry /= 10;
        }
        
        for (int k = (m - 1); k > -1; k--)
        {
            bufferPowers[idx++] = ls_itoc(a[k]);
        }
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferBeginLine, sizeof(bufferBeginLine)-1, TRUE);
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferPowers, idx, TRUE);
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferEndLine, sizeof(bufferEndLine)-1, TRUE);
        idx = 0;
        
    }
    
    char bufferEnd[] = "};";
}

void ls_primes(u64 upperLimit)
{
    char bufferBegin[] = "u64 primes[] = \r\n{\r\n\t";
    ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)bufferBegin, sizeof(bufferBegin) - 1, TRUE);
    
    u32 newline = 0;
    for (u64 i = 1; i < upperLimit; i++)
    {
        for (u64 j = 2; j < i; j++)
        {
            if (i % j == 0)
            { break; }
            if (j == i - 1)
            {
                char *v = ls_itoa(i);
                string print = v; print += ", "; 
                if (++newline == 30)
                {
                    newline = 0;
                    print += "\r\n\t";
                }
                ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)print.data, print.size, TRUE);
            }
        }
    }
    
    char end[] = "};";
    ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)end, sizeof(end), TRUE);
}

#endif

////////////////////////////////////////////////////
//	TRASCENDENTAL FUNCTIONS
////////////////////////////////////////////////////

f64 ls_sine(f64 x)
{
    b32 isNegative = (x > 0) ? FALSE : TRUE;
    f64 mappedX = x;
    
    if (isNegative)
    {
        while (mappedX < -(2.0f*PI_32))
        {
            mappedX += (2.0f*PI_32);
        }
        
        mappedX += 2.0f*PI_32;
    }
    else
    {
        while (mappedX > 2.0f*PI_32)
        {
            mappedX -= (2.0f*PI_32);
        }
    }
    
    f64 z = (mappedX - 3.1416f) / 1.8413f;
    
    f64 cube = z*z*z;
    f64 fifth = cube*z*z;
    f64 seventh = fifth*z*z;
    f64 ninth = seventh*z*z;
    
    f64 square = z*z;
    f64 fourth = square*square;
    f64 sixth = fourth*square;
    f64 eigth = fourth*fourth;
    f64 tenth = eigth*square;
    
    return (1.9252e-16*tenth) - (0.00052653*ninth) - (1.3721e-15*eigth) + (0.013847*seventh) + (3.344e-15*sixth)
        - (0.17589*fifth) - (3.0365e-15*fourth) + (1.0402*cube) + (1.6822e-16*square) - (1.8412*z) + (5.4606e-16);
}

f64 ls_asin(f64 x)
{
    if ((x < -1.0f) || (x > 1.0f))
        return 0;
    
    f64 z = (x + 7.2164e-17f) / 0.5817f;
    
    f64 cube = z*z*z;
    f64 fifth = cube*z*z;
    f64 seventh = fifth*z*z;
    f64 ninth = seventh*z*z;
    
    f64 square = z*z;
    f64 fourth = square*square;
    f64 sixth = fourth*square;
    f64 eigth = fourth*fourth;
    f64 tenth = eigth*square;
    
    return (1.6544e-15*tenth) + (0.024044*ninth) - (1.1741e-14*eigth) - (0.12358*seventh) + (2.9093e-14*sixth)
        + (0.22158*fifth) - (2.938e-14*fourth) - (0.10393*cube) + (1.0267e-14*square) + (0.60425*z) - 6.3772e-16;
}

f64 ls_cos(f64 x)
{
    b32 isNegative = (x > 0) ? FALSE : TRUE;
    f64 mappedX = x;
    
    if (isNegative)
    {
        while (mappedX < -(2.0f*PI_32))
        {
            mappedX += (2.0f*PI_32);
        }
        mappedX += 2.0f*PI_32;
    }
    else
    {
        while (mappedX > 2.0f*PI_32)
        {
            mappedX -= (2.0f*PI_32);
        }
    }
    
    f64 z = (mappedX - 3.1416f) / 1.8413f;
    
    f64 cube = z*z*z;
    f64 fifth = cube*z*z;
    f64 seventh = fifth*z*z;
    f64 ninth = seventh*z*z;
    
    f64 square = z*z;
    f64 fourth = square*square;
    f64 sixth = fourth*square;
    f64 eigth = fourth*fourth;
    f64 tenth = eigth*square;
    
    return (9.9058e-05*tenth) - (2.4826e-16*ninth) - (0.0032018*eigth) + (1.475e-15*seventh) + (0.054013*sixth)
        - (3.0717e-15*fifth) - (0.47883*fourth) + (2.9256e-15*cube) + (1.6951*square) - (1.5395e-15*z) - 1;
}

f64 ls_acos(f64 x)
{
    if ((x < -1.0f) || (x > 1.0f))
        return 0;
    
    f64 z = (x + 7.2164e-17f) / 0.5817f;
    
    f64 cube = z*z*z;
    f64 fifth = cube*z*z;
    f64 seventh = fifth*z*z;
    f64 ninth = seventh*z*z;
    
    f64 square = z*z;
    f64 fourth = square*square;
    f64 sixth = fourth*square;
    f64 eigth = fourth*fourth;
    f64 tenth = eigth*square;
    
    return -(2.3277e-15*tenth) - (0.024044*ninth) + (1.7628e-14*eigth) + (0.12358*seventh) - (4.6935e-14*sixth)
        - (0.22158*fifth) + (5.1126e-14*fourth) + (0.10393*cube) - (1.9655e-14*square) - (0.60425*z) + 1.5708;
}

f64 ls_tan(f64 x)
{
    return (ls_sine(x) / ls_cos(x));
}

f64 ls_atan(f64 x)
{
    b32 isNegative = x < 0.0f ? TRUE : FALSE;
    if ((x > 10.00f) || (x < -10.00f))
    {
        if (isNegative) { return -arctan[1000]; }
        else { return arctan[1000]; }
    }
    
    f32 xValue = ls_fabs((f32)x)*100.0f;
    if (isNegative) { return -arctan[(int)xValue]; }
    else { return arctan[(int)xValue]; }
}

////////////////////////////////////////////////////
//	STRING FUNCTIONS
////////////////////////////////////////////////////

s32 ls_len(char * string)
{
    int Result = 0;
    char *At = string;
    while (*At != 0)
    {
        Result++;
        At++;
    }
    
    return Result;
}

char ls_lowerCase(char c)
{
    if ((c > 64) && (c < 91)) { return c + 32; }
    else { return c; }
}

b32	ls_isANumber(char c)
{
    if((c >= 48 && c <= 57))
    { return TRUE; }
    
    return FALSE;
}

char *ls_itoa(s64 x)
{
    char *Result = 0;
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if (value == 0)
    {
        Result = (char *)ls_alloc(2);
        Result[0] = '0'; Result[1] = '\0';
        return Result;
    }
    
    //My Log10 Function is not super precise at the boundaries between values i.e. 999999 - 1000000. So just to be sure, I give it an extra byte, which is super fine.
    
    //Update months Later: BTW I think this is a fuckin waste of time and processor power, considering no number to be printed is ever going to be bigger than 128 char long 
    //I should just waste this 0.000000016% of the average computer FUCKING Memory to just allocate a little bit more than necessary.
    
    //I'm not going to change it now just because it's good training for me to approximate trascendental functions and stuff like that
    
    //Update few days later: Fuck it I'm changing this shitty Log10 functions that sucks freakin balls.
    
    //@TODO @CLEANUP @FIXME: Make a Log2 / Log10 / LOGN Function Tables so that I quit having this stupid shitty problem. (Or maybe see if theres cool ASM for them)
    Result = (char *)ls_alloc(128);
    s32 i = 0;
    
    while (value != 0)
    {
        Result[i++] = value % 10 + '0';
        value = value / 10;
    }
    
    if (isNegative) { Result[i++] = '-'; }
    Result[i] = '\0';
    
    //Flip string, it's in reverse.
    for (int t = 0; t < i / 2; t++)
    {
        Result[t] ^= Result[i - t - 1];
        Result[i - t - 1] ^= Result[t];
        Result[t] ^= Result[i - t - 1];
    }
    
    return Result;
}

string *ls_itohs(u64 x)
{
    string buffer = 32;
    string *a = (string *)ls_alloc(sizeof(string));
    
    u8 *At = (u8 *)&x;
    for(u32 i = 0; i < 8; i++)
    {
        u8 lowNybble = (*At & 0x0F);
        u8 highNybble = (*At & 0xF0) >> 4;;
        
        switch(lowNybble)
        {
            case 0: buffer += '0'; break; case 1: buffer += '1'; break;
            case 2: buffer += '2'; break; case 3: buffer += '3'; break;
            case 4: buffer += '4'; break; case 5: buffer += '5'; break;
            case 6: buffer += '6'; break; case 7: buffer += '7'; break;
            case 8: buffer += '8'; break; case 9: buffer += '9'; break;
            case 10: buffer += 'A'; break; case 11: buffer += 'B'; break;
            case 12: buffer += 'C'; break; case 13: buffer += 'D'; break;
            case 14: buffer += 'E'; break; case 15: buffer += 'F'; break;
        }
        switch(highNybble)
        {
            case 0: buffer += '0'; break; case 1: buffer += '1'; break;
            case 2: buffer += '2'; break; case 3: buffer += '3'; break;
            case 4: buffer += '4'; break; case 5: buffer += '5'; break;
            case 6: buffer += '6'; break; case 7: buffer += '7'; break;
            case 8: buffer += '8'; break; case 9: buffer += '9'; break;
            case 10: buffer += 'A'; break; case 11: buffer += 'B'; break;
            case 12: buffer += 'C'; break; case 13: buffer += 'D'; break;
            case 14: buffer += 'E'; break; case 15: buffer += 'F'; break;
        }
        At++;
    }
    
    buffer.data[buffer.len] = 0;
    buffer.reverse();
    
    *a = 19;
    *a = "0x";
    
    while(true)
    {
        if(buffer.len == 2) { break; }
        if((buffer.data[0] != '0') || (buffer.data[1] != '0'))
        { break; }
        else
        { buffer.removeSubstr(0, 1); }
    }
    
    *a += buffer;
    a->data[a->len] = 0;
    
    buffer.free();
    
    return a;
}

char ls_itoc(s64 x)
{
    return ((char)x + '0');
}

char * ls_ftoa(f32 x)
{
    char *Result = 0;
    
    char *IntegerPart = ls_itoa((int)x);
    char *FractPart = 0;
    if (x < 1.0f)
    {
        s32 fractValue = s32((x + 1.0f) * 1000000);
        FractPart = ls_itoa(fractValue);
    }
    else if (x >= 10.0f)
    {
        f32 fixedX = (x - (int)x) + 1.0f;
        s32 fractValue = s32(fixedX * 1000000);
        FractPart = ls_itoa(fractValue);
    }
    else
    {
        s32 fractValue = s32(x * 1000000);
        FractPart = ls_itoa(fractValue);
    }
    
    if (x < 0)
    {
        char *Negative = ls_concat((char *)"-", IntegerPart, 0);
        char *Part1 = ls_concat(Negative, (char *)".", 0);
        Result = ls_concat(Part1, FractPart + 1, 0);
        
        ls_free(Negative);
        ls_free(Part1);
    }
    else
    {
        char *Part1 = ls_concat(IntegerPart, (char *)".", 0);
        Result = ls_concat(Part1, FractPart + 1, 0);
        
        ls_free(Part1);
    }
    
    ls_free(IntegerPart);
    ls_free(FractPart);
    
    return Result;
}

u32 ls_ctoi(char c)
{
    return c - '0';
}

s64 ls_atoi(char *s)
{
    s64 Result = 0;
    s32 len = ls_len(s);
    b32 isNegative = s[0] == '-' ? TRUE : FALSE;
    
    if (!isNegative)
    {
        for (int i = (len - 1), k = 0; i >= 0; i--, k++)
        {
            Result += ( (s[i] - 48) * ls_e10(k) );
        }
    }
    else
    {
        for (int i = (len - 1), k = 0; i > 0; i--, k++)
        {
            Result -= ( (s[i] - 48) * ls_e10(k) );
        }
    }
    return Result;
}

s64 ls_stoi(string *s)
{
    s->nullTerminate();
    return ls_atoi(s->data);
}

s64 ls_atoi16(char *s)
{
    s64 Result = 0;
    s32 len = ls_len(s);
    b32 isNegative = s[0] == '-' ? TRUE : FALSE;
    
    if (!isNegative)
    {
        for (int i = (len - 1), k = 1; i >= 0; i--, k++)
        {
            s32 c = s[i];
            if (c > 47 && c < 58) { Result += ((c - 48) * ls_e10(k)); }
            if (c > 64 && c < 71) { Result += ((c - 55) * ls_e10(k)); }
            if (c > 96 && c < 103) { Result += ((c - 87) * ls_e10(k)); }
        }
    }
    else
    {
        for (int i = (len - 1), k = 1; i > 0; i--, k++)
        {
            s32 c = s[i];
            if (c > 47 && c < 58) { Result -= ((c - 48) * ls_e10(k)); }
            if (c > 64 && c < 71) { Result -= ((c - 55) * ls_e10(k)); }
            if (c > 96 && c < 103) { Result -= ((c - 87) * ls_e10(k)); }
        }
    }
    return Result;
}

s64 ls_atoi(char *s, int base)
{
    switch (base)
    {
        case 10:
        return ls_atoi(s);
        case 16:
        return ls_atoi16(s);
        default:
        return -1;
    }
}

f32 ls_atof(char *s, int size)
{
    s32 len = size;
    f32 base = 0;
    f32 decimal = 0;
    
    if (len == 0)
    { len = ls_len(s); }
    
    char buffer[32] = {};
    char *At = s;
    u32 count = 0;
    u32 done = 0;
    while (len-- > 0)
    {
        if (*At == '.') { break; }
        At++; count++;
    }
    
    ls_memcpy(s, buffer, count);
    done += count + 1;
    
    base = (f32)ls_atoi(buffer);
    ls_zeroMem(buffer, 32);
    
    count = 0;
    while (len-- > 0)
    {
        At++; count++;
    }
    
    ls_memcpy(s + done, buffer, count);
    
    decimal = (f32)ls_atoi(buffer);
    
    f32 Result = 0.0f;
    
    Result += base;
    Result += (decimal / (f32)ls_powi(10, count));
    
    return Result;
}

char *ls_strstr(char *string1, char *string2)
{
    char *result = 0;
    
    u32 len1 = ls_len(string1);
    u32 len2 = ls_len(string2);
    
    char *i = (string1 + len2);
    char buffer[256] = { 0 };
    
    while(i < (string1 + len1))
    {
        ls_memcpy((void *)(i - len2), (void *)buffer, len2);
        if(ls_strcmp(string2, buffer) == 0)
        { result = (i - len2); return result; }
        
        i++;
    }
    
    return result;
    
}

char *ls_concat(char *string1, char *string2, b32 hasToFree = FALSE)
{
    char *Result = 0;
    int string1Len = ls_len(string1);
    int string2Len = ls_len(string2);
    
    int size = string1Len + string2Len;
    Result = (char *)ls_alloc(size + 1);
    
    char *At = string1;
    int i = 0;
    while (i < string1Len)
    {
        Result[i] = *At;
        At++;
        i++;
    }
    int y = 0;
    At = string2;
    while (y <= string2Len)
    {
        Result[i] = *At;
        At++;
        y++;
        i++;
    }
    
    if (hasToFree)
    {
        ls_free(string1);
        ls_free(string2);
    }
    
    return Result;
}
s32 ls_strcmp(char *string1, char *string2)
{
    s32 string1Len = ls_len(string1);
    s32 string2Len = ls_len(string2);
    
    char *At1 = string1;
    char *At2 = string2;
    
    b32 areSame = TRUE;
    while ((string1Len || string2Len) && areSame)
    {
        if (*At1 != *At2)
        {
            areSame = FALSE;
            break;
        }
        
        At1++;
        At2++;
        string1Len--;
        string2Len--;
    }
    
    if (areSame == TRUE)
    {
        return 0;
    }
    else
    {
        return *At1 < *At2 ? -1 : 1;
    }
    
    return 2;
}
s32 ls_strcpy(char *dest, char *src, bool nullTerminate = TRUE)
{
    char *At = src;
    char *To = dest;
    
    s32 srcLen = ls_len(src);
    s32 c = 0;
    
    s32 it = srcLen;
    if (nullTerminate) { it += 1; }
    while (it--)
    {
        *To = *At;
        At++;
        To++;
        c++;
    }
    
    return c;
}

void ls_strncpy(void *src, void *dest, size_t size)
{
    char *At = (char *)src;
    char *To = (char *)dest;
    
    size_t it = size;
    while (it--)
    {
        *To = *At;
        At++;
        To++;
    }
    
    *To = 0;
}

/*This function returns the entire line, null terminated, 
* WITHOUT carriage return or newline. The bytesRead report
* the every single byte, so they will count \r\n as well.
*
* This function does NOT advance the data pointer.*/
char *ls_breakUntilLine(char *data, u32 *bytesRead, u32 *stringSize)
{
    char *At = (char *)data;
    
    u32 count = 0;
    while (*At)
    {
        if (*At == '\r') { break; }
        if (*At == '\n') { break; }
        At++;
        count++;
    }
    
    char *line = (char *)ls_alloc(sizeof(char)*(count + 1));
    ls_memcpy(data, line, count);
    if (stringSize) { *stringSize = count; }
    
    At++;
    count++;
    if (*At == '\r') { At++; count++; }
    if (*At == '\n') { At++; count++; }
    if (bytesRead) { *bytesRead = count; }
    
    return line;
}

char *ls_breakUntilSpace(char *data, u32 *bytesRead)
{
    char *At = data;
    
    u32 count = 0;
    while (*At)
    {
        if (*At == ' ') { break; }
        At++;
        count++;
    }
    
    char *line = (char *)ls_alloc(sizeof(char)*(count + 1));
    ls_memcpy(data, line, count);
    
    while (*At == ' ') { At++; count++; }
    if (bytesRead) { *bytesRead = count; }
    
    return line;
}

/*@TODO: Test this thoroughly*/
string *ls_breakByLine(char *data, u32 *numOfLines)
{
    string *Result = 0;
    string buff[256] = {};
    u32 buffIdx = 0;
    char *At = (char *)data;
    
    u32 count = 0;
    u32 done = 0;
    while (*At)
    {
        if (((*At == '\r') || (*At == '\n')) && count == 0)
        { At++; continue; }
        if ((*At == '\r') || (*At == '\n'))
        {
            /* @TODO: @NOTE: Make a better ls_strcpy / ls_strncpy which uses strings */
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count+1)); //NullTerm
            ls_memcpy(data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count + 1;
            buff[buffIdx].len  = count;
            done += count + 1;
            buffIdx++;
            count = 0;
            
            if (*(At + 1) == '\n') { At++; done++; }
            
            At++;
            continue;
        }
        At++;
        count++;
    }
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    *numOfLines = buffIdx;
    
    return Result;
}

/*@TODO: Test this thoroughly*/
string *ls_breakBySpace(char *data, u32 *numOfStrings, u32 *charsRead)
{
    string *Result = 0;
    string buff[256] = {};
    u32 buffIdx = 0;
    char *At = data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        if (*At == ' ') 
        { 
            /* @TODO: @NOTE: Make a better ls_strcpy / ls_strncpy which uses strings */
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            ls_memcpy(data + done, buff[buffIdx].data, count);
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
            ls_memcpy(data + done, buff[buffIdx].data, count);
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
    if(charsRead) {*charsRead = done; }
    
    return Result;
}

string *ls_breakBySpaceDelimiter(char *data, char delimiter, u32 *numOfStrings, u32 *charsRead)
{
    string *Result = 0;
    string buff[256] = {};
    u32 buffIdx = 0;
    char *At = data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        if (*At == delimiter)
        { 
            if(*(At + 1) == ' ') {done++;}
            done++; 
            break; 
        }
        
        if (*At == ' ') 
        { 
            /* @TODO: @NOTE: Make a better ls_strcpy / ls_strncpy which uses strings */
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            ls_memcpy(data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
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
            ls_memcpy(data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
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
    if(charsRead) { *charsRead = done; }
    
    
    return Result;
}

char *ls_breakByChar(char *data, u32 *bytesRead, char c)
{
    char *At = data;
    
    u32 count = 0;
    while (*At)
    {
        if (*At == c) { break; }
        At++;
        count++;
    }
    
    char *line = (char *)ls_alloc(sizeof(char)*(count + 1));
    ls_memcpy(data, line, count);
    
    //Remove the unwanted char
    count++;
    if (bytesRead) { *bytesRead = count; }
    
    return line;
}

u32 ls_offsetToFirstChar(char *data, char c)
{
    char *At = data;
    u32 offset = 0;
    
    while ((*At != c) && (*At != 0))
    { At++; offset++; }
    
    return offset;
}

void ls_alphaOrder(char **names, u32 numOfNames)
{
    char temp[256] = { 0 };
    
    for (u32 i = 0; i < numOfNames - 1; i++)
    {
        for (u32 j = i + 1; j < numOfNames; j++)
        {
            if (ls_strcmp(names[i], names[j]) > 0)
            {
                ls_strcpy(temp, names[i], TRUE);
                ls_strcpy(names[i], names[j], TRUE);
                ls_strcpy(names[j], temp, TRUE);
            }
        }
    }
}

u64 ls_writeConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite);
u64 ls_readConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite);

/* Write a formatted string to dest.
* Returns the numbers of chars written without counting 
* the null terminator (which is appended anyway)
*/
s32 ls_sprintf(char *dest, const char *format, ...)
{
    char *buff = (char *)ls_alloc(1048576);
    const char *p = format;
    char *s = 0;
    char *s_label = 0;
    b32 isLong = FALSE;
    
    s64 nInt = 0;
    char c = 0;
    f32 nFloat = 0.0f;
    
    va_list argList;
    va_start(argList, format);
    
    s32 i = 0;
    for (p = format; *p != 0; p++)
    {
        if (*p != '%')
        {
            buff[i] = *p;
            i++;
            continue;
        }
        
        switch (*++p)
        {
            case 'l':
            isLong = TRUE;
            p++;
            
            case 'd':
            if (isLong) { nInt = va_arg(argList, s64); }
            else { nInt = (u64)va_arg(argList, s32); }
            s = ls_itoa(nInt);
            i += ls_strcpy(buff + i, s, 0);
            ls_free(s);
            break;
            
            case 'c':
            c = va_arg(argList, int);
            buff[i] = c;
            i++;
            break;
            
            case 'f':
            nFloat = (f32)va_arg(argList, f64);
            s = ls_ftoa(nFloat);
            i += ls_strcpy(buff + i, s, 0);
            ls_free(s);
            break;
            
            case 's':
            s_label = va_arg(argList, char *);
            i += ls_strcpy(buff + i, s_label, 0);
            break;
            
            case '%':
            buff[i] = '%';
            i++;
            break;
        }
    }
    va_end(argList);
    
    buff[i] = 0;
    i++;
    ls_memcpy(buff, dest, i);
    
    ls_free((void *)buff);
    
    return (i - 1);
}

s32 ls_printf(const char *format, ...)
{
    char *buff = (char *)ls_alloc(1048576);
    const char *p = format;
    char *s = 0;
    char *s_label = 0;
    b32 isLong = FALSE;
    b32 isUnsigned = FALSE;
    
    u64 uLongInt = 0;
    s64 nInt = 0;
    char c = 0;
    f32 nFloat = 0.0f;
    
    va_list argList;
    va_start(argList, format);
    
    s32 i = 0;
    for (p = format; *p != 0; p++)
    {
        if (*p != '%')
        {
            buff[i] = *p;
            i++;
            continue;
        }
        
        switch (*++p)
        {
            //@TODO THIS IS WRONG ON SO MANY LEVELS
            case 'u':
            isUnsigned = TRUE;
            p++;
            
            case 'l':
            isLong = TRUE;
            p++;
            
            case 'd':
            if(isLong) 
            { nInt = isUnsigned ? va_arg(argList, u64) : va_arg(argList, s64); }
            else { nInt = (u64)va_arg(argList, s32); }
            s = ls_itoa(nInt);
            i += ls_strcpy(buff + i, s, 0);
            ls_free((void *)s);
            break;
            
            case 'c':
            c = va_arg(argList, int);
            *(buff + i) = c;
            i++;
            break;
            
            case 'f':
            nFloat = (f32)va_arg(argList, f64);
            s = ls_ftoa(nFloat);
            i += ls_strcpy(buff + i, s, 0);
            ls_free((void *)s);
            break;
            
            case 's':
            s_label = va_arg(argList, char *);
            i += ls_strcpy(buff + i, s_label, 0);
            break;
            
            case 'p':
            uLongInt = (u64)va_arg(argList, void *);
            s = ls_itoa(nInt);
            i += ls_strcpy(buff + i, s, 0);
            ls_free((void *)s);
            break;
            
            case '%':
            buff[i] = '%';
            i++;
            break;
        }
    }
    va_end(argList);
    
    buff[i] = 0;
    i++;
    
    //Write buffer to stdout file.
    ls_writeConsole(LS_STDOUT, buff, i);
    
    ls_free((void *)buff);
    
    return i;
}

char ls_getc()
{
    char Result = 0;
    ls_readConsole(LS_STDIN, &Result, 1);
    
    return Result;
}

////////////////////////////////////////////////////
//	FILE MANIPULATION FUNCTIONS
////////////////////////////////////////////////////

void ls_getFileNameFromPath(char *Path, char *out)
{
    u32 len = ls_len(Path);
    
    u32 i = len - 1;
    while (Path[i] != '\\')
    { i--; }
    
    ls_strcpy(out, Path + i + 1, true);
    
    return;
}

void ls_getFileExtension(char *Path, char *out)
{
    u32 len = ls_len(Path);
    
    u32 i = len - 1;
    while (Path[i] != '.')
    {
        i--;
    }
    
    ls_strcpy(out, Path + i + 1, true);
    
    return;
}

u64 ls_readConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite)
{
#ifdef LS_PLAT_WINDOWS
    return windows_ReadConsole(Source, bytesToWrite);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadConsole(ConsoleHandle, Source, bytesToWrite);
#endif                                                           
}

u64 ls_readFile(char *Path, char **Dest, u32 bytesToRead)
{
#ifdef LS_PLAT_WINDOWS
    return windows_ReadFile(Path, Dest, bytesToRead);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadFile(Path, Dest, bytesToRead);
#endif
}

u64 ls_ReadFileByOffset(string *Path, char **Dest, u64 offset, u32 bytesToRead)
{
    Path->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    return windows_ReadFileByOffset(Path->data, Dest, offset, bytesToRead);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadFileByOffset(Path->data, Dest, offset, bytesToRead);
#endif
}

void ls_readFileString(char *Path, string *dest, u32 bytesToRead)
{
#ifdef LS_PLAT_WINDOWS
    dest->size = (u32)windows_ReadFile(Path, &dest->data, bytesToRead);
    dest->len = dest->size;
    dest->nullTerminate();
#endif
    
#ifdef LS_PLAT_LINUX
    dest->size = (u32)linux_ReadFile(Path, &dest->data, bytesToRead);
#endif
}

u64 ls_writeConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite)
{
#ifdef LS_PLAT_WINDOWS
    return windows_WriteConsole(Source, bytesToWrite);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_WriteConsole(ConsoleHandle, Source, bytesToWrite);
#endif                                                           
}

u64 ls_writeFile(string *Path, void *Source, u32 bytesToWrite, b32 append)
{
    Path->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    return windows_WriteFile(Path->data, (char *)Source, bytesToWrite, append);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_WriteFile(Path, Source, bytesToWrite);
#endif
}

u32  ls_countFilesInDir(string *Dir)
{
    Dir->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    return windows_countFilesInDir(Dir->data, Dir->len);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDir(Dir->data, Dir->len);
#endif
}

u32  ls_countFilesInDirByExt(string *Dir, string *ext)
{
    Dir->nullTerminate(); ext->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    return windows_countFilesInDirByExt(Dir->data, Dir->len, 
                                        ext->data, ext->len);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDirByExt(Dir->data, Dir->len, 
                                      ext->data, ext->len);
#endif
}

u32  ls_getFileNamesInDir(string *Dir, string **names)
{
    Dir->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    char **cNames = 0;
    u32 howManyNames = 0;
    u32 *namesLen = 0;
    
    windows_getFileNamesInDir(Dir->data, Dir->len, &cNames, &howManyNames, &namesLen);
    
    (*names) = (string *)ls_alloc(sizeof(string)*howManyNames);
    for(u32 i = 0; i < howManyNames; i++)
    {
        (*names)[i].data = cNames[i];
        (*names)[i].size = namesLen[i];
        (*names)[i].len  = namesLen[i];
    }
    
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_getFileNamesInDir(Dir->data, Dir->len);
#endif
}

u32  ls_getFileNamesInDirByExt(string *Dir, string *ext, string **names)
{
    Dir->nullTerminate(); ext->nullTerminate();
#ifdef LS_PLAT_WINDOWS
    char **cNames = 0;
    u32 howManyNames = 0;
    u32 *namesLen = 0;
    
    windows_getFileNamesInDirByExt(Dir->data, Dir->len, ext->data, ext->len, &cNames, &howManyNames, &namesLen);
    
    (*names) = (string *)ls_alloc(sizeof(string)*howManyNames);
    for(u32 i = 0; i < howManyNames; i++)
    {
        (*names)[i].data = cNames[i];
        (*names)[i].size = namesLen[i];
        (*names)[i].len  = namesLen[i];
    }
    
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDirByExt(Directory.data, Directory.len, 
                                      extension.data, extension.len);
#endif
}

string *ls_getFullPathName(char *name)
{
#ifdef LS_PLAT_WINDOWS
    string *s = 0;
    char buffer[256] = {};
    u32 len = windows_getFullPathName(name, 256, buffer);
    
    s = (string *)ls_alloc(sizeof(string));
    *s = buffer;
    return s;
#endif
    
#ifdef LS_PLAT_LINUX
    char buffer[256] = {};
    return linux_getFullPathName(name, 256, buffer);
#endif
}

void ls_loadBitmap(char *Path, Bitmap *bitmap)
{
    char *bitmapFile;
    u64 bitmapFileSize = ls_readFile(Path, &bitmapFile, 0);
    
    u32 PixelOffset = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    Height = ls_abs(Height);
    
    u32 Compression = *((u32 *)((char *)bitmapFile + 30));
    
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    
    bitmap->data = ((char *)bitmapFile + PixelOffset);
    bitmap->width = Width;
    bitmap->height = Height;
    bitmap->headerSize = HeaderSize;
    bitmap->compression = Compression;
    bitmap->pixelBufferSize = PixelBufferSize;
    bitmap->size = bitmapFileSize;
    
    return;
}

void ls_loadCompressedPNG(char *Path, PNG *png)
{
    char *pngFile;
    u64 pngFileSize = ls_readFile(Path, &pngFile, 0);
    
    png->compressedData = (char *)ls_alloc(sizeof(char)*pngFileSize);
    
    u8 *At = (u8 *)pngFile;
    
    //Checks the png file is "valid" with the first 4 bytes, 1 check byte and a "PNG" signature.
    Assert((*At == 0x89) && (*(At + 1) == 0x50) && (*(At + 2) == 0x4E) && (*(At + 3) == 0x47));
    At += 8;
    
    char chunkType[5];
    
    u32 chunkSize = btol32(At); At += 4;
    //ls_memcpy(At, chunkType, 4); At += 4;
    //chunkType[4] = 0;
    ls_strncpy(At, chunkType, 4); At += 4;
    
    while (ls_strcmp(chunkType, (char *)"IEND") != 0)
    {
        if (ls_strcmp(chunkType, (char *)"IHDR") == 0)
        {
            png->width				= btol32(At); At += 4;
            png->height				= btol32(At); At += 4;
            png->bitDepth			= *At; At++;
            png->colorType			= *At; At++;
            png->compressionMethod	= *At; At++;
            png->filterMethod		= *At; At++;
            png->interlaceMethod	= *At; At++;
        }
        else if (ls_strcmp(chunkType, (char *)"PLTE") == 0)
        {
            Assert((chunkSize % 3) == 0);
            u32 numOfEntries = chunkSize / 3;
            
            png->palette = (v3 *)ls_alloc(sizeof(v3)*numOfEntries);
            
            for (u32 i = 0; i < numOfEntries; i++)
            {
                png->palette[i].r = *At; At++;
                png->palette[i].g = *At; At++;
                png->palette[i].b = *At; At++;
            }
        }
        else if (ls_strcmp(chunkType, (char *)"IDAT") == 0)
        {
            ls_memcpy(At, png->compressedData + png->size, chunkSize); At += chunkSize;
            png->size += chunkSize;
        }
        else if (ls_strcmp(chunkType, "bKGD") == 0)
        {
            if (png->colorType == 3) { png->defaultBackgroundIndex = *At; At++; }
            
            else if ((png->colorType == 0) || (png->colorType == 4))
            { png->defaultBackgroundGreyscale = btol16(At); At += 2; }
            
            else 
            { 
                png->defaultBackgroundColor.x = btol16(At); At += 2; 
                png->defaultBackgroundColor.y = btol16(At); At += 2;
                png->defaultBackgroundColor.z = btol16(At); At += 2;
            }
        }
        else if (ls_strcmp(chunkType, "cHRM") == 0)
        {
            png->whitePoint.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->whitePoint.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->redChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->redChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->greenChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->greenChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->blueChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->blueChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
        }
        else if (ls_strcmp(chunkType, "gAMA") == 0)
        {
            png->gamma = (f32)btol32(At) / 100000.0f; At += 4;
        }
        else if (ls_strcmp(chunkType, "pHYs") == 0)
        {
            png->pixelsPerUnit_X = btol32(At); At += 4;
            png->pixelsPerUnit_Y = btol32(At); At += 4;
            png->unitSpecifier = *At; At++;
        }
        /*else if (ls_strcmp(chunkType, "tRNS") == 0)
        {
        
        }*/
        else
        {
            At += chunkSize;
        }
        
        //Jump CRC
        At += 4;
        
        chunkSize = btol32(At); At += 4;
        ls_strncpy(At, chunkType, 4); At += 4;
    }
    
    return;
}

#if 1

/*------DEFLATE HELPERS------*/
#define MAXBITS 15              /* maximum bits in a code */
#define MAXLCODES 286           /* maximum number of literal/length codes */
#define MAXDCODES 30            /* maximum number of distance codes */
#define MAXCODES (MAXLCODES+MAXDCODES)  /* maximum codes lengths to read */
#define FIXLCODES 288           /* number of fixed literal/length codes */

struct deflate_state
{
    char *in;
    u32 bytesRead;
    u64 inSize;
    
    char *out;
    u64 outSize;
    
    u8 bitBuffer;
    u8 bitCount;
};

struct deflate_CodeTree
{
    u16 table[16];
    u16 symbols[288];
};

u8 deflate_getBits(deflate_state *s, u8 n)
{
    u8 Result = 0;
    Assert(s->bitCount <= 8);
    
    if (s->bitCount)
    {
        if (s->bitCount >= n)
        {
            Result = s->bitBuffer;
            Result <<= (8 - n);
            Result >>= (8 - n);
            s->bitCount -= n;
            s->bitBuffer >>= n;
            
            return Result;
        }
        else
        {
            u8 left = n - s->bitCount;
            Result = s->bitBuffer;
            Result <<= left;
            s->bitBuffer = s->in[s->bytesRead++];
            
            u8 partial = s->bitBuffer;
            partial <<= (8 - left);
            partial >>= (8 - left);
            Result |= partial;
            
            s->bitCount = 8 - left;
            s->bitBuffer >>= left;
            
            return Result;
        }
    }
    else
    {
        s->bitBuffer = s->in[s->bytesRead++];
        
        Result = s->bitBuffer;
        Result <<= (8 - n);
        Result >>= (8 - n);
        
        s->bitCount = 8 - n;
        s->bitBuffer >>= n;
        
        return Result;
    }
    
    return Result;
}

void decompressUncompressedBlock()
{
    
}

void decompressHuffmanBlock(u32, u32)
{
    
}

void decodeHuffmanCodes()
{
    
}

void deflate_buildTree(deflate_CodeTree *t, u8 *lengths, u32 amount)
{
    u16 offsets[16];
    
    /* scan symbol lengths, and sum code length counts */
    for (u32 i = 0; i < amount; i++) { t->table[lengths[i]]++; }
    t->table[0] = 0;
    
    /* compute offset table for distribution sort */
    //The two methods are the same
    offsets[1] = 0;
    //for (u32 sum = 0, i = 0; i < 16; i++)
    for(u32 len = 1; len < 15; len++)
    {
        //offsets[i] = sum;
        //sum += t->table[i];
        offsets[len + 1] = offsets[len] + t->table[len];
    }
    
    /* create code->symbol translation table (symbols sorted by code) */
    for (u32 i = 0; i < amount; i++)
    {
        if (lengths[i]) { t->symbols[offsets[lengths[i]]++] = i; }
    }
}

s32 deflate_decodeSym(deflate_state *s, deflate_CodeTree *t)
{
    s32 sum = 0, cur = 0, len = 0;
    
    do
    {
        cur = 2 * cur + deflate_getBits(s, 1);
        len++;
        
        sum += t->table[len];
        cur -= t->table[len];
    } while (cur >= 0);
    
    return t->symbols[sum + cur];
}

void ls_Deflate(char *data, u64 inputSize, char *out)
{
    /*Setup the deflate state structure*/
    deflate_state state = {};
    state.in = data;
    state.inSize = inputSize;
    state.out = out;
    
    /*---Parse zlib header---*/
    u8 cmf = state.in[state.bytesRead++]; u8 flag = state.in[state.bytesRead++];
    if ((cmf & 0x0F) != 8 || (cmf >> 4) != 7 || (u32)(cmf*256 + flag) % 31 != 0)
    { Assert(false); } 	//Not a png or corrupted?
    
    u32 dict = 0;
    if ((flag & 0b00100000) != 0)
    { dict = btol32((u8 *)(&state.in[state.bytesRead])); state.bytesRead += 4; }
    
    // Process the stream of blocks
    do {
        // Read the block header
        //u8 byte = state.in[state.bytesRead++];
        //u8 type = (byte & 0x06) >> 1;
        u8 BFINAL = deflate_getBits(&state, 1);
        u8 BTYPE = deflate_getBits(&state, 2);
        
        // Decompress rest of block based on the type
        if (BTYPE == 0)		{ decompressUncompressedBlock(); }
        else if (BTYPE == 1) { decompressHuffmanBlock(FIXLCODES, MAXDCODES); }
        else if (BTYPE == 2)
        {
            u16 HLIT = (u16)deflate_getBits(&state, 5) + 257;
            u8 HDIST = deflate_getBits(&state, 5) + 1;
            u8 HCLEN = deflate_getBits(&state, 4) + 4;
            
            /* Enough to fit HLIT + HDIST amount of codes */
            u8 codeLengths[288+32] = {};
            
            /* Get Code Lengths used in the "Code Length Alphabet" in the order:
            * 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 */
            u8 order[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
            for (u32 i = 0; i < HCLEN; i++)
            { codeLengths[order[i]] = deflate_getBits(&state, 3); }
            
            /* Build the code tree.       ????? 19 because it's the max value for HCLEN ????? */
            deflate_CodeTree codeTree = {};
            deflate_buildTree(&codeTree, codeLengths, 19);
            
            /* Decode code lengths for dynamic trees 
            * (HLIT amount for literal/length alphabet, HDIST amount for distance alphabet) */
            {
                u32 repeat = 0;
                u8 prev = 0;
                for (u32 num = 0; num < (u16)(HLIT + HDIST); )
                {
                    s32 sym = deflate_decodeSym(&state, &codeTree);
                    
                    switch (sym)
                    {
                        case 16:
                        {
                            /* copy previous code length 3-6 times (read 2 bits) */
                            prev = codeLengths[num - 1];
                            for (repeat = deflate_getBits(&state, 2) + 3; repeat; repeat--)
                            { codeLengths[num++] = prev; }
                        }
                        break;
                        
                        case 17:
                        {
                            /* repeat code length 0 for 3-10 times (read 3 bits) */
                            for (repeat = deflate_getBits(&state, 3) + 3; repeat; repeat--)
                            { codeLengths[num++] = 0; }
                        }
                        break;
                        
                        case 18:
                        {
                            /* repeat code length 0 for 11-138 times (read 7 bits) */
                            for (repeat = deflate_getBits(&state, 7) + 11; repeat; repeat--)
                            { codeLengths[num++] = 0; }
                        }
                        break;
                        default:
                        {
                            /* values 0-15 represent the actual code lengths */
                            codeLengths[num++] = sym;
                        }
                        break;
                    }
                }
            }
            
            /* Build Dynamic Trees*/
            deflate_CodeTree lenTree, distTree;
            deflate_buildTree(&lenTree, codeLengths, HLIT);
            deflate_buildTree(&distTree, codeLengths + HLIT, HDIST);
            
            int a = 0;
        }
        else if (BTYPE == 3) { Assert(FALSE); }
        else { Assert(FALSE); }
    } while (state.bytesRead < inputSize);
    
    return;
    
#undef MAXBITS
#undef MAXLCODES
#undef MAXDCODES
#undef MAXCODES
#undef FIXLCODES
}

#endif

////////////////////////////////////////////////////
//	GENERAL PURPOSE SYSTEM FUNCTIONS
////////////////////////////////////////////////////

u64 ls_getTimeSinceEpochInMicrosec()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetWindowsTimeInMicrosec();
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_GetWindowsTime();
#endif
}

u64 ls_getTimeSinceEpochIn100Nanosec()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetWindowsTimeIn100Nanosec();
#endif
}

u32 ls_getUnix32Time()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetUnix32Time();
#endif
}

u64 ls_getUnix64Time()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetUnix64Time();
#endif
}

string ls_getDayName(u32 num)
{
    string Result;
    switch (num)
    {
        case 0:
        Result = "Monday";
        return Result;
        case 1:
        Result = "Tuesday";
        return Result;
        case 2:
        Result = "Wednesday";
        return Result;
        case 3:
        Result = "Thursday";
        return Result;
        case 4:
        Result = "Friday";
        return Result;
        case 5:
        Result = "Saturday";
        return Result;
        case 6:
        Result = "Sunday";
        return Result;
        default:
        Result = "Error?";
        return Result;
    }
}

string ls_getMonthName(u32 m)
{
    string Result;
    switch (m)
    {
        case 1:
        Result = "January";
        return Result;
        case 2:
        Result = "February";
        return Result;
        case 3:
        Result = "March";
        return Result;
        case 4:
        Result = "April";
        return Result;
        case 5:
        Result = "May";
        return Result;
        case 6:
        Result = "June";
        return Result;
        case 7:
        Result = "July";
        return Result;
        case 8:
        Result = "August";
        return Result;
        case 9:
        Result = "September";
        return Result;
        case 10:
        Result = "October";
        return Result;
        case 11:
        Result = "November";
        return Result;
        case 12:
        Result = "December";
        return Result;
        default:
        Result = "Error?";
        return Result;
    }
}

Date ls_getDateTime(b32 local)
{
    Date Result = {};
    
#ifdef LS_PLAT_WINDOWS
    windowsDate wDate = windows_GetDate(local);
    
    Result.milliseconds = wDate.Milliseconds;
    Result.seconds = wDate.Second;
    Result.minutes = wDate.Minute;
    Result.hour = wDate.Hour;
    Result.day = wDate.Day;
    string dayName = ls_getDayName(wDate.DayOfWeek);
    ls_memcpy(dayName.data, Result.dayName, dayName.size);
    Result.month = wDate.Month;
    string monthName = ls_getMonthName(wDate.Month);
    ls_memcpy(monthName.data, Result.monthName, monthName.size);
    Result.year = wDate.Year;
#endif
    
#ifdef LS_PLAT_LINUX
    linuxDate lDate = linux_GetDate(local);
    
    Result.milliseconds = lDate.Milliseconds;
    Result.seconds = lDate.Second;
    Result.minutes = lDate.Minute;
    Result.hour = lDate.Hour;
    Result.day = lDate.Day;
    Result.dayName = ls_getDayName(lDate.DayOfWeek);
    Result.month = lDate.Month;
    Result.monthName = ls_getMonthName(lDate.Month);
    Result.year = lDate.Year;
#endif
    
    return Result;
}

void ls_setupWindow(WindowInfo *info)
{
#ifdef LS_PLAT_WINDOWS
#ifdef I_WANT_GRAPHICS
    windows_setupWindow(info);
#endif
#endif
}

void ls_setupOpenGLContext(WindowInfo *info)
{
#ifdef LS_PLAT_WINDOWS
#ifdef I_WANT_GRAPHICS
    windows_setupOpenGLContext(info);
#endif
#endif
}

void ls_sleep(u64 milliseconds)
{
#ifdef LS_PLAT_WINDOWS
    windows_sleep(milliseconds);
#endif
}

////////////////////////////////////////////////////
//	CRYPTOGRAPHY FUNCTIONS
////////////////////////////////////////////////////

u16 btol16(u8 *At)
{
    u16 result = 0;
    u8 buffer[2] = { 0 };
    
    ls_memcpy(At, buffer, 2);
    
    result |= (u16)buffer[1];
    result |= ((u16)buffer[0] << 8);
    
    return result;
}

u32 btol32(u8 *At)
{
    u32 result = 0;
    u8 buffer[4] = { 0 };
    
    ls_memcpy(At, buffer, 4);
    
    result |= (u32)buffer[3];
    result |= ((u32)buffer[2] << 8);
    result |= ((u32)buffer[1] << 16);
    result |= ((u32)buffer[0] << 24);
    
    return result;
}

u64 btol64(u8 *At)
{
    u64 result = 0;
    u8 buffer[8] = { 0 };
    
    ls_memcpy(At, buffer, 8);
    
    result |= (u64)buffer[7];
    result |= ((u64)buffer[6] << 8);
    result |= ((u64)buffer[5] << 16);
    result |= ((u64)buffer[4] << 24);
    result |= ((u64)buffer[3] << 32);
    result |= ((u64)buffer[2] << 40);
    result |= ((u64)buffer[1] << 48);
    result |= ((u64)buffer[0] << 56);
    
    return result;
}

u32 MD5_F(u32 S0, u32 S1, u32 S2)
{ return ((S0 & S1) | (~S0 & S2)); }

u32 MD5_G(u32 S0, u32 S1, u32 S2)
{ return ((S0 & S2) | (S1 & ~S2)); }

u32 MD5_H(u32 S0, u32 S1, u32 S2)
{ return (S0 ^ S1 ^ S2); }

u32 MD5_I(u32 S0, u32 S1, u32 S2)
{ return (S1 ^ (S0 | ~S2)); }

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

void ls_setupHex(hex *h, char *ascii)
{
    s32 len = ls_len(ascii);
    h->ascii = (char *)ls_alloc(len+1);
    ls_memcpy(ascii, h->ascii, len + 1);
    
    h->len = len+1;
    
    ls_hexASCIIToValue(h);
    ls_hexToBytecode(h);
}

void ls_hexASCIIToValue(hex *h)
{
    h->value = (char *)ls_alloc(h->len);
    
    char c = 0;
    for(int i = 0; i < h->len-1; i++)
    {
        c = h->ascii[i];
        if (c == 0) { h->value[i] = 0; }
        
        if (c > 47 && c < 58) { h->value[i] = (c - 48); }
        else if (c > 64 && c < 71) { h->value[i] = (c - 55); }
        else if (c > 96 && c < 103) { h->value[i] = (c - 87); }
    }
}

void ls_hexValueToASCII(hex *h)
{
    if (h->ascii == nullptr)
    {
        h->ascii = (char *)ls_alloc(h->len);
    }
    
    for (int i = 0; i < h->len-1; i++)
    {
        char c = h->value[i];
        if(c < 10){ h->ascii[i] = c + 48; }
        else if( c > 9 && c < 16) { h->ascii[i] = c + 55; }
    }
}

void ls_hexToBytecode(hex *h)
{
    h->byteLen = (h->len / 2) + 1;
    h->bytecode = (char *)ls_alloc(h->byteLen);
    
    for (int i = 0, j = 0; i < h->len; i += 2, j++)
    {
        h->bytecode[j] = (h->value[i] << 4) | (h->value[i + 1]);
    }
}

char *ls_64ValueToASCII(char *s)
{
    char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    s32 len = ls_len(s);
    char *Result = (char *)ls_alloc(len);
    
    for (int i = 0; i < len; i++)
    {
        Result[i] = base64[s[i]];
    }
    
    ls_free(s);
    
    return Result;
}

char *ls_hexTo64Value(hex *h)
{
    char *Result = 0;
    char buffer[8] = {0};
    s32 newLength = (((h->len-1) * 2) / 3) + 2;
    
    Result = (char *)ls_alloc(newLength);
    
    u8 holder = 0; s32 k = 0;
    for (int i = 0; i < (h->len-1); i += 6)
    {
        ls_memcpy(h->value + i, buffer, 6);
        holder = (buffer[0] << 4) | (buffer[1]);
        Result[k++] = (holder >> 2) & 0b00111111;
        holder = (buffer[1] << 4) | (buffer[2]);
        Result[k++] = holder & 0b00111111;
        holder = (buffer[3] << 4) | (buffer[4]);
        Result[k++] = (holder >> 2) & 0b00111111;
        holder = (buffer[4] << 4) | (buffer[5]);
        Result[k++] = holder & 0b00111111;
    }
    
    Result[k] = 0;
    return Result;
}

char *ls_hexTo64ASCII(hex *h)
{
    char *temp = ls_hexTo64Value(h);
    char *Result = ls_64ValueToASCII(temp);
    
    return Result;
}

char *ls_stringFixedXOR(hex *h1, hex *h2)
{
    hex Result = { 0 };
    Result.value = (char *)ls_alloc(h1->len);
    Result.len = h1->len;
    
    for (int i = 0; i < h1->len-1; i++)
    {
        Result.value[i] = h1->value[i] ^ h2->value[i];
    }
    Result.value[h1->len-1] = 0;
    ls_hexValueToASCII(&Result);
    
    ls_free(Result.value);
    
    return Result.ascii;
}

//Smaller has to be the secon one
char *ls_stringVariableXOR(hex *hLonger, hex *hShorter)
{
    hex Result = { 0 };
    s32 longer = hLonger->len;
    s32 smaller = hShorter->len;
    
    Result.len = longer;
    Result.value = (char *)ls_alloc(longer);
    
    for (int i = 0; i < longer - 1; i++)
    {
        for (int j = 0; j < smaller - 1; j++)
        {
            Result.value[i] = hLonger->value[i] ^ hShorter->value[j];
        }
    }
    
    Result.value[longer - 1] = 0;
    ls_hexValueToASCII(&Result);
    
    ls_free(Result.value);
    
    return Result.ascii;
}

void ls_charVariableXOR(hex *h, char c, char *dest)
{
    s32 len = h->byteLen;
    
    for (int i = 0; i < len - 1; i++)
    {
        dest[i] = h->bytecode[i] ^ c;
    }
    
    dest[len - 1] = 0;
    
}

s32 ls_scoreSentence(char *s)
{
    s32 Score = 0;
    s32 length = ls_len(s);
    
    for (int i = 0; i < length; i++)
    {
        if ((s[i] >= 0) && (s[i] < 32)) { return 0; }
        if (s[i] < 0) { return 0; }
        
        switch (ls_lowerCase(s[i]))
        {
            case 'a': Score += 2; break;
            case 'b': Score++; break;
            case 'c': Score++; break;
            case 'd': Score++; break;
            case 'e': Score += 2; break;
            case 'f': Score++; break;
            case 'g': Score++; break;
            case 'h': Score++; break;
            case 'i': Score += 2; break;
            case 'j': Score++; break;
            case 'k': Score++; break;
            case 'l': Score++; break;
            case 'm': Score++; break;
            case 'n': Score++; break;
            case 'o': Score += 2; break;
            case 'p': Score++; break;
            case 'q': Score++; break;
            case 'r': Score++; break;
            case 's': Score++; break;
            case 't': Score++; break;
            case 'u': Score += 2; break;
            case 'v': Score++; break;
            case 'w': Score++; break;
            case 'x': Score++; break;
            case 'y': Score++; break;
            case 'z': Score++; break;
            case ' ': Score += 2; break;
        }
    }
    
    return Score;
}

////////////////////////////////////////////////////
//	MEMORY FUNCTIONS
////////////////////////////////////////////////////

void ls_memcpy(void *src, void *dest, size_t size)
{
    if(size == 0) { return; }
    
    char *At = (char *)src;
    char *To = (char *)dest;
    size_t it = size;
    
    switch (size)
    {
        case 1:
        *To = *At;
        return;
        case 2:
        *(u16 *)To = *(u16 *)At;
        return;
        case 4:
        *(u32 *)To = *(u32 *)At;
        return;
        case 8:
        *(u64 *)To = *(u64 *)At;
        return;
        case 16:
        *(u64 *)To = *(u64 *)At;
        At += 8; To += 8;
        *(u64 *)To = *(u64 *)At;
        return;
        case 32:
        for (int i = 0; i < 4; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 64:
        for (int i = 0; i < 8; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 128:
        for (int i = 0; i < 16; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 256:
        for (int i = 0; i < 32; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 512:
        for (int i = 0; i < 64; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 1024:
        for (int i = 0; i < 128; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 2048:
        for (int i = 0; i < 256; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 4096:
        for (int i = 0; i < 512; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 8192:
        for (int i = 0; i < 1024; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 16384:
        for (int i = 0; i < 2048; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 32768:
        for (int i = 0; i < 4096; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 65536:
        for (int i = 0; i < 8192; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 131072:
        for (int i = 0; i < 16384; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 262144:
        for (int i = 0; i < 32768; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 524288:
        for (int i = 0; i < 65536; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        case 1048576:
        for (int i = 0; i < 131072; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        default:
        while (it--)
        {
            *To = *At;
            At++;
            To++;
        }
        return;
    }
}

u32 ls_memcmp(void *a, void *b, size_t size)
{
    char *At = (char *)a;
    char *Bt = (char *)b;
    
    for (u32 i = 0; i < size; i++)
    {
        if (*At != *Bt)
        { return 1; }
        At++;
        Bt++;
    }
    
    return 0;
}

void ls_zeroMem(void *mem, size_t size)
{
    
    char *To = (char *)mem;
    size_t it = size;
    
    switch (size)
    {
        case 1:
        *To = 0;
        return;
        case 2:
        *(u16 *)To = 0;
        return;
        case 4:
        *(u32 *)To = 0;
        return;
        case 8:
        *(u64 *)To = 0;
        return;
        case 16:
        *(u64 *)To = 0;
        To += 8;
        *(u64 *)To = 0;
        return;
        case 32:
        for (int i = 0; i < 4; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 64:
        for (int i = 0; i < 8; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 128:
        for (int i = 0; i < 16; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 256:
        for (int i = 0; i < 32; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 512:
        for (int i = 0; i < 64; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 1024:
        for (int i = 0; i < 128; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 2048:
        for (int i = 0; i < 256; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 4096:
        for (int i = 0; i < 512; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 8192:
        for (int i = 0; i < 1024; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 16384:
        for (int i = 0; i < 2048; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 32768:
        for (int i = 0; i < 4096; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 65536:
        for (int i = 0; i < 8192; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 131072:
        for (int i = 0; i < 16384; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 262144:
        for (int i = 0; i < 32768; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 524288:
        for (int i = 0; i < 65536; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 1048576:
        for (int i = 0; i < 131072; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        default:
        while (it--)
        {
            *To = 0;
            To++;
        }
        return;
    }
}

void ls_zeroString(void *mem, size_t size)
{
    char *To = (char *)mem;
    size_t it = size;
    
    switch (size)
    {
        case 1:
        *To = 0;
        return;
        case 2:
        *(u16 *)To = 0;
        return;
        case 4:
        *(u32 *)To = 0;
        return;
        case 8:
        *(u64 *)To = 0;
        return;
        case 16:
        *(u64 *)To = 0;
        To += 8;
        *(u64 *)To = 0;
        return;
        case 32:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 64:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 128:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 256:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 512:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 1024:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 2048:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 4096:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 8192:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 16384:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 32768:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 65536:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 131072:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 262144:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 524288:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        case 1048576:
        while (*((u64 *)To) != 0)
        { *((u64 *)To) = 0; To += 8; }
        return;
        default:
        while (it--)
        { *To = 0; To++; }
        return;
    }
}

//@TODO: Modify ls_alloc to automatically check if the returned pointer is null.
void *ls_alloc(u64 size)
{
#ifdef LS_PLAT_WINDOWS
    return windows_memAlloc(size);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_memAlloc(size);
#endif
}

void *ls_realloc(void *originalMem, u64 oldSize, u64 newSize)
{
    if(originalMem)
    {
        void *newMem = windows_memAlloc(newSize);
        ls_memcpy(originalMem, newMem, oldSize);
        windows_memFree(originalMem);
        
        return newMem;
    }
    
    return windows_memAlloc(newSize);
}

void ls_free(void *p)
{
#ifdef LS_PLAT_WINDOWS
    return windows_memFree(p);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_memFree(p);
#endif
}

////////////////////////////////////////////////////
//	INTRINSICS
////////////////////////////////////////////////////

#if _M_IX86
#define LeadingZeros(value) LeadingZeros32((u32)value)
#elif _M_X64
#define LeadingZeros(value) LeadingZeros64((u64)value)
#endif

u32 LeadingZeros32(u32 value)
{
    unsigned long index = 0;
#ifdef LS_PLAT_WINDOWS
    _BitScanReverse(&index, value);
    return 31 - index;
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_clz(value);
    return index;
#endif
}

u32 LeadingZeros64(u64 value)
{
    unsigned long index = 0;
#if _M_IX86
    return LeadingZeros(value);
#else
    
#ifdef LS_PLAT_WINDOWS
    _BitScanReverse64(&index, value);
    return 63 - index;
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_clz(value);
    return index;
#endif
    
#endif
}

f32 Log2(u64 value)
{
    unsigned long index = 0;
#ifdef LS_PLAT_WINDOWS
#if _M_IX86
    _BitScanReverse(&index, (u32)value);
#else
    _BitScanReverse64(&index, value);
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_ctz(value);
#endif
    
    f32 Result = (f32)index;
    
    if (((value >> (index-1)) & 1u))
    { 
        Result += 0.50f;
        if (((value >> (index - 2)) & 1u))
        { 
            Result += 0.315f;
            if (((value >> (index - 3)) & 1u))
            { Result += 0.10f; }
        }
    }
    return Result;
}

u32	Log10(u64 value)
{
    return (u32)ls_truncEpsilon(0.3010299957f * Log2(value));
}

u16 ByteSwap16(u16 value)
{
#ifdef LS_PLAT_WINDOWS
    return _byteswap_ushort(value);
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap16(value);
#endif
}

u32 ByteSwap32(u32 value)
{
#ifdef LS_PLAT_WINDOWS
    return _byteswap_ulong(value);
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap32(value);
#endif
}

u64 ByteSwap64(u64 value)
{
#ifdef LS_PLAT_WINDOWS
    return _byteswap_uint64(value);
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap64(value);
#endif
}

f32 Ceil(f32 v)
{
#ifdef LS_PLAT_WINDOWS
    __m128 Result = _mm_set_ps1(v);
    Result = _mm_ceil_ps(Result);
    
    return (Result.m128_f32[0]);
#endif
    
#ifdef LS_PLAT_LINUX
    return 0.0f;
#endif
}

#endif
