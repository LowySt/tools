#ifndef LS_CRT_H
#define LS_CRT_H

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
#include "../Platform/lsLinux.h"
#endif

#define LS_STDOUT STDOUT_FILENO
#define LS_STDIN  STDIN_FILENO
#define LS_STDERR STDERR_FILENO

#endif

#ifndef LS_MATHS_H
#include "Maths/Maths.h"
#endif

#ifndef LS_GRAPHICS_H
#include "lsGraphics.h"
#endif

#include <stdarg.h>

#define PI_32 3.1415926f

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

extern "C"
{
	////////////////////////////////////////////////////
	//	MATH FUNCTIONS
	////////////////////////////////////////////////////

	s32 ls_abs(s32 x);
	f32 ls_fabs(f32 x);
	u64 ls_fact(u32 x);
	s64	ls_e10(s32 x);
	s64 ls_powi(s64 v, u32 exp);
	f64 ls_powf(f64 v, s32 exp);
	s64	ls_truncate(f64 x);
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

	s32 ls_len(char * string);
	char ls_lowerCase(char c);
	char *ls_itoa(s64 x);
	char ls_itoc(s64 x);
	u32 ls_ctoi(char c);
	s64 ls_atoi(char *s, int base);
	char * ls_ftoa(f32 x);

	char * ls_concat(char *string1, char *string2, b32 hasToFree);
	s32 ls_strcmp(char *string1, char *string2);
	s32 ls_strcpy(char *dest, char *src, bool nullTerminate);
	void ls_strncpy(void *src, void *dest, size_t size);

	void ls_alphaOrder(char **names, u32 numOfNames);

	s32 ls_sprintf(char *dest, const char *format, ...);
	s32 ls_printf(const char *format, ...);
	char ls_getc();

	////////////////////////////////////////////////////
	//	FILE MANIPULATION FUNCTIONS
	////////////////////////////////////////////////////

	void ls_getFileNameFromPath(char *Path, char *out);
	void ls_getFileExtension(char *Path, char *out);

	//If bytesToRead is set to 0 the entire file will be read.
    u64 ls_readFile(char *Path, char **Dest, u32 bytesToRead);
	u64 ls_writeFile(char *Path, void *Source, u32 bytesToWrite, b32 append);

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
	u64 ls_getTimeSinceEpoch();
	
	/* If false UTC time is returned instead */
	Date ls_getDateTime(b32 local);


	/* Function for creating and opening a window*/
	void ls_createWindow(WindowInfo info);
	void ls_setupOpenGLContext(WindowInfo *Info);

	////////////////////////////////////////////////////
	//	CRYPTOGRAPHY FUNCTIONS
	////////////////////////////////////////////////////

	u16 btol16(char *At);
	u32 btol32(char *At);
	u64 btol64(char *At);

	void ls_setupHex(hex *h, char *ascii);

	void ls_hexASCIIToValue(hex *h);
	void ls_hexValueToASCII(hex *h);
	void ls_hexToBytecode(hex *h);

	char *ls_hexTo64Value(hex *h);
	char *ls_hexTo64ASCII(hex *h);

	char *ls_stringFixedXOR(hex *h1, hex *h2);
	char *ls_stringVariableXOR(hex *h1, hex *h2);
	void ls_charVariableXOR(hex *h, char c, char *dest);

	s32 ls_scoreSentence(char *s);

	////////////////////////////////////////////////////
	//	MEMORY FUNCTIONS
	////////////////////////////////////////////////////

	void ls_memcpy(void *src, void *dest, size_t size);
	u32 ls_memcmp(void *a, void *b, size_t size);
	void ls_zeroMem(void *mem, size_t size);
	void ls_zeroMemASM(void *mem, size_t size);
	void ls_zeroString(void *mem, size_t size);
	void *ls_alloc(u64 size);
	void ls_free(void *p);

	////////////////////////////////////////////////////
	//	INTRINSICS
	////////////////////////////////////////////////////
	
	u32	Log10(u64 value);
	u32 LeadingZeros32(u32 value);
	u32 LeadingZeros64(u64 value);
	u16 ByteSwap16(u16 value);
	u32 ByteSwap32(u32 value);
	u64 ByteSwap64(u64 value);
}

//@TODO: I really don't like the C++-ness of this string code... Could I clean it up in any way?
struct string
{
	char	*data;
	u32		size;

	string(const char *src)
	{
		u32 len = ls_len((char *)src);
		size = len;
		data = (char *)ls_alloc(len);
		ls_memcpy((void *)src, (void *)data, len);
	}
	
	string(int v)
	{
		size = v;
		data = (char *)ls_alloc(v);
	}

	string(string *v)
	{
		size = v->size;
		data = (char *)ls_alloc(size);
		ls_memcpy((void *)v->data, (void *)data, size);
	}

	string()
	{ data = 0; size = 0; }

	//
	// Need to test operator overloading for memory leaks. I think I'm good but, who knows?
	//

	string operator+(string w)
	{
		u32 newSize = size + w.size;
		char *newData = (char *)ls_alloc(newSize);

		ls_memcpy((void*)data, (void *)newData, size);
		ls_memcpy((void*)w.data, (void *)(newData + size), w.size);

		ls_free(data);
		ls_free(w.data);

		string result; result.data = newData; result.size = newSize;
		return result;
	}

	void operator+=(string w)
	{
		*this = *this + w;
	}

	string operator+(char c)
	{
		u32 usedSize = ls_len(data);
		if (size == usedSize)
		{
			string result = *this;
			return result;
		}

		string result = *this;
		result.data[usedSize] = c;

		return result;
	}

	void operator+=(char c)
	{
		*this = *this + c;
	}

	bool operator==(string w)
	{
		if (ls_strcmp(this->data, w.data) == 0)
		{ return true; }
		else { return false; }
	}
	
	bool operator!=(string w)
	{
		if (ls_strcmp(this->data, w.data) == 0)
		{ return false; }
		else { return true; }
	}

	void reverse()
	{
		char *Begin = data;
		char *End = data + size;
		while (Begin < End)
		{
			char temp = *Begin;
			*Begin = *End;
			*End = temp;
			Begin++;
			End--;
		}
	}

	void remove(char c)
	{
		for (u32 i = 0; i < size; i++)
		{
			if (data[i] == c)
			{
				data[i] = 0;
				ls_memcpy(data + i + 1, data + i, size - i - 1);
				data[size - 1] = 0;
				i--;
			}
		}
	}
};

struct hashTable
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

	u32 (*hashFunction)(string id) = 0;

	u32 baseHash(string id)
	{
		u32 it = -1;
		for (u32 i = 0; i < id.size; i++)
		{
			it += id.data[i] * i;
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

	hashTable(u32 tableSize = 64, u32 (*func)(string) = 0)
	{
		size = tableSize;
		entries = (hashEntry *)ls_alloc(sizeof(hashEntry) * size);
		elementsInTable = 0; longestLink = 0;

		if (func) { hashFunction = func; }
	}

	void add(string id, u32 value)
	{
		u32 index = hashFunction ? hashFunction(id) : baseHash(id);

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

	u32 find(string id)
	{
		u32 index = hashFunction ? hashFunction(id) : baseHash(id);
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
};

struct Array
{
	void *data;
	u32 type;

	u32 size;
	u32 usedSize;

	Array()
	{ data = 0; type = 0; size = 0; usedSize = 0; }

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

char * ls_itoa(s64 x)
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

char * ls_concat(char *string1, char *string2, b32 hasToFree)
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
s32 ls_strcpy(char *dest, char *src, bool nullTerminate)
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

	size_t it = size - 1;
	while (it--)
	{
		*To = *At;
		At++;
		To++;
	}

	*To = 0;
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

	return i;
}

s32 ls_printf(const char *format, ...)
{
	char *buff = (char *)ls_alloc(1048576);
	const char *p = format;
	char *s = 0;
	char *s_label = 0;
	b32 isLong = FALSE;
	b32 isUnsigned = FALSE;


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
	while (Path[i] != '/')
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

u64 ls_writeConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite)
{
#ifdef LS_PLAT_WINDOWS
    return windows_WriteConsole(Source, bytesToWrite);
#endif

#ifdef LS_PLAT_LINUX
    return linux_WriteConsole(ConsoleHandle, Source, bytesToWrite);
#endif                                                           
}

u64 ls_writeFile(char *Path, void *Source, u32 bytesToWrite, b32 append)
{
#ifdef LS_PLAT_WINDOWS
    return windows_WriteFile(Path, (char *)Source, bytesToWrite, append);
#endif

#ifdef LS_PLAT_LINUX
    return linux_WriteFile(Path, Source, bytesToWrite);
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

	char *At = pngFile;
	
	//Checks the png file is "valid" with the first 4 bytes, 1 check byte and a "PNG" signature.
	Assert((*At == 0x89) && (*(At+1) == 0x50) && (*(At + 2) == 0x4E) && (*(At + 1) == 0x47));
	At += 8;

	char chunkType[5];

	u32 chunkSize = btol32(At); At += 4;
	ls_memcpy(At, chunkType, 4); At += 4;
	chunkType[4] = 0;

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
		ls_memcpy(At, chunkType, 4); At += 4;
		chunkType[4] = 0;
	}

	return;
}

/*------DEFLATE HELPERS------*/
#define MAXBITS 15              /* maximum bits in a code */
#define MAXLCODES 286           /* maximum number of literal/length codes */
#define MAXDCODES 30            /* maximum number of distance codes */
#define MAXCODES (MAXLCODES+MAXDCODES)  /* maximum codes lengths to read */
#define FIXLCODES 288           /* number of fixed literal/length codes */

struct deflateState
{
	char *in;
	u32 bytesRead;
	u64 inSize;

	char *out;
	u64 outSize;

	u32 bitBuffer;
	u32 bitCount;

};

struct huffman
{
	u16 *count;
	u16 *symbol;
};

static u32 getBits(struct deflateState *s, u32 howMany)
{
	u32 Result;
	u8 tmp;
	while (s->bitCount < howMany)
	{
		tmp = s->in[s->bytesRead++];
		s->bitBuffer = (s->bitBuffer << 8) | tmp;
		s->bitCount += 8;
	}

	Result = (s->bitBuffer & ((1 << howMany) - 1));
	s->bitBuffer = s->bitBuffer >> howMany;
	s->bitCount -= howMany;

	return Result;
}

static void buildHuffTable(huffman *h, u16 *length, u32 n)
{
	u32 symbol;					/* current symbol when stepping through length[] */
	u32 len;					/* current length when stepping through h->count[] */
	u16 offs[MAXBITS + 1] = {}; /* offsets in symbol table for each length */

	/* It's like this because codes are sequential? Maybe? */
	for (symbol = 0; symbol < n; symbol++)
	{ (h->count[length[symbol]])++; }

	if (h->count[0] == n)
	{ 
		/*Complete but undecodable*/ 
		return; 
	}

	/* Need to check for over-subscribed or incomplete set of lengths? */

	/* Generate offsets into symbol table for each length for sorting */
	for (len = 1; len < MAXBITS; len++)
	{ offs[len + 1] = offs[len] + h->count[len]; }

	/* Put symbols in table sorted by length and
		by symbol order within each length */
	for (symbol = 0; symbol < n; symbol++)
	{
		if (length[symbol] != 0)
		{ h->symbol[offs[length[symbol]]++] = symbol; }
	}

	return;
}

static u32 huffmanDecode(deflateState *s, huffman *h)
{
	s32 len;			/* len bits being decoded */
	s32 code;			/* current number of bits in code */
	s32 first;			/* first code of length len */
	s32 codeCount;		/* number of codes of length len */
	s32 index;			/* index of first code of length len in symbol table */
	s32 bitBuffer;		/* bits from stream */
	s32 bitsLeft;		/* bits left in next or left to process */
	u16 *nextCodeCount; /* next number of codes */

	code = first = index = 0;
	len = 1;
	
	nextCodeCount = h->count + 1;
	bitBuffer = s->bitBuffer;
	bitsLeft = s->bitCount;

	while (TRUE)
	{
		while (bitsLeft--)
		{
			code |= bitBuffer & 1;
			bitBuffer >>= 1;
			codeCount = *(nextCodeCount++);

			/*if length len, return symbol*/
			if (code - codeCount < first)
			{
				s->bitBuffer = bitBuffer;
				s->bitCount = (s->bitCount - len) & 7;
				return h->symbol[index + (code - first)];
			}
			/* Else, update for next code length*/

			index += codeCount;
			first += codeCount;
			first <<= 1;
			code <<= 1;
			len++;
		}

		bitsLeft = (MAXBITS + 1) - len;
		if (bitsLeft == 0)
		{ break; }

		bitBuffer = s->in[s->bytesRead++];
		if (bitsLeft > 8)
		{ bitsLeft = 8; }
	}
	return 0;
}

/*------DEFLATE HELPERS------*/

void ls_Deflate(char *data, u64 inputSize, char *out)
{
	/*Setup the deflate state structure*/
	deflateState state = {};
	state.in = data;
	state.inSize = inputSize;
	state.out = out;

	/* CODES FOR DECOMPRESSING HUFFMAN CODES? */
	/* Size base for length codes 257..285 */
	u16 lenTable[29] = { 
		3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 
		35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258 };

	/* Extra bits for length codes 257..285 */
	u16 lenExtTable[29] = { 
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
		3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };

	/* Offset base for distance codes 0..29 */
	u16 distTable[30] = { 
		1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
		257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
		8193, 12289, 16385, 24577 };

	/* Extra bits for distance codes 0..29 */
	u16 distExtTable[30] = { 
		0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
		7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };

	/*---Parse zlib header---*/
	u8 cmf = state.in[state.bytesRead++]; u8 flag = state.in[state.bytesRead++];
	if ((cmf & 0x0F) != 8 || (cmf >> 4) != 7 || (cmf*256 + flag) % 31 != 0)
	{ Assert(false); } 	//Not a png or corrupted?

	u32 dict = 0;
	if ((flag & 0b00100000) != 0)
	{ dict = btol32(&state.in[state.bytesRead]); state.bytesRead += 4; }

	//Parse deflate block header

	u8 byte = state.in[state.bytesRead++];
	u8 type = (byte & 0x06) >> 1;
	while ((byte & 0x01) != 1)
	{
		byte >>= 3;

		/*No compression*/
		if (type == 0)
		{
			/* Moving 2 extra because of !Len bytes right after */
			u16 len = btol16(&state.in[state.bytesRead]); state.bytesRead += 4;
			ls_memcpy(&state.in[state.bytesRead], &state.out[state.outSize], len);
			state.outSize += len;
			state.bytesRead += len;
		}
		/*Compressed with fixed Huffman codes*/
		else if (type == 1)
		{

		}
		/*Compressed with dynamic Huffman codes*/
		else if (type == 2)
		{
			u32 numOfLengths;
			u32 numOfDists;
			u32 numOfCodesLength;

			/* descriptor code lengths (<len,dist>) */
			u16 lengths[MAXCODES] = {};
			
			/* lencode memory */
			u16 lenSymbol[MAXLCODES] = {};
			u16 lenCount[MAXBITS + 1] = {};

			/* distcode memory */
			u16 distSymbol[MAXDCODES] = {};
			u16 distCount[MAXBITS + 1] = {};

			huffman lencode, distcode;

			lencode.count = lenCount;
			lencode.symbol = lenSymbol;
			distcode.count = distCount;
			distcode.symbol = distSymbol;

			/* permutation of code length codes */
			u16 order[19] = {
				16, 17, 18, 0, 8, 7, 9, 6, 10, 5,
				11, 4, 12, 3, 13, 2, 14, 1, 15 };

			u32 i;

			numOfLengths	 = getBits(&state, 5) + 257;
			numOfDists		 = getBits(&state, 5) + 1;
			numOfCodesLength = getBits(&state, 4) + 4;

			if (numOfLengths > MAXLCODES || numOfDists > MAXDCODES)
			{ return; /*BAD PNG*/}

			/* Read the lengths of the "Code Length" Codes 
				(stupid double huffman compression) */
			for (i = 0; i < numOfCodesLength; i++)
			{ lengths[order[i]] = (u16)getBits(&state, 3); }
			for (; i < 19; i++)
			{ lengths[order[i]] = 0; }

			/* Build huffman table (use lencode as tmp) */
			buildHuffTable(&lencode, lengths, 19);

			/* Read the ACTUAL "Length/Literal" and "Distance" code lengths */
			i = 0;
			while (i < numOfLengths + numOfDists)
			{
				u32 symbol;	/*decoded value*/
				u32 len;	/*last length to repeat*/

				/* Working out Alphabet for Code Lengths */
				symbol = huffmanDecode(&state, &lencode);
				if (symbol < 0) 
				{ 
					/* Invalid Symbol */ 
					return; 
				}

				/* Length is in range 0..15 */
				if (symbol < 16)
				{ lengths[i++] = symbol; }
				else
				{
					len = 0;
					/* Repeat last length 3..6 times */
					if (symbol == 16)
					{
						if (i == 0)
						{ 
							/* Error: no last length */	
							return; 
						}

						len = lengths[i - 1];
						symbol = 3 + getBits(&state, 2);
					}
					/* Repeat zero 3..10 times */
					else if (symbol == 17)
					{ symbol = 3 + getBits(&state, 3); }
					/* Repeat zero 11..138 times */
					else
					{ symbol = 11 + getBits(&state, 7); }

					if ((i + symbol) > (numOfLengths + numOfDists))
					{ 
						/* Error: too many lengths */ 
						return; 
					}

					while (symbol--)
					{ lengths[i++] = len; }
				}

			}

			/* Check for end-of-block code -- there better be one! */
			if (lengths[256] == 0)
			{ /* Error no EOB */ return; }

			int breakHere2 = 0;

			/* Build huffman table for literal/length codes */
			buildHuffTable(&lencode, lengths, numOfLengths);

			/* Build huffman table for distance codes */
			buildHuffTable(&distcode, lengths + numOfLengths, numOfDists);

			/* Finally return the data*/
			{
				u32 symbol;
				u32 len;
				u32 dist;

				do
				{
					symbol = huffmanDecode(&state, &lencode);
					if (symbol < 0) { /* Error: invalid symbol */ return;  }

					/* Literal, write to out */
					if (symbol < 256)
					{ state.out[state.outSize++] = (u8)symbol; }
					else if (symbol > 256)
					{
						/* Compute Length */
						symbol -= 257;
						if (symbol >= 29) { /* Error: Invalid*/ return; }

						len = lenTable[symbol] + getBits(&state, lenExtTable[symbol]);

						/* Get Distance*/
						symbol = huffmanDecode(&state, &distcode);
						if (symbol < 0) { /* Error: Invalid*/ return; }

						dist = distTable[symbol] + getBits(&state, distExtTable[symbol]);

						/* Write to Output (LZ77 style <len,dist>)*/
						/* I'm not using memcpy because it may have problems
						 * with overlaps */
						while (len--)
						{
							state.out[state.outSize] = state.out[state.outSize - dist];
							state.outSize++;
						}
					}
				} while (symbol != 256); /* End Of Block symbol*/
			}
			/* DONE! */

			int breakHere = 0;
		}
		/*Reserved*/
		else
		{
		}

		byte = state.in[state.bytesRead++];
		type = (byte & 0x06) >> 1;
	}
	return;

#undef MAXBITS
#undef MAXLCODES
#undef MAXDCODES
#undef MAXCODES
#undef FIXLCODES
}

////////////////////////////////////////////////////
//	GENERAL PURPOSE SYSTEM FUNCTIONS
////////////////////////////////////////////////////

u64 ls_getTimeSinceEpoch()
{
#ifdef LS_PLAT_WINDOWS
	return windows_GetTime();
#endif

#ifdef LS_PLAT_LINUX
	return linux_GetTime();
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

void ls_createWindow(WindowInfo *info)
{
#ifdef LS_PLAT_WINDOWS
	windows_setupWindow(info);
#endif
}

void ls_setupOpenGLContext(WindowInfo *info)
{
#ifdef LS_PLAT_WINDOWS
	windows_setupOpenGLContext(info);
#endif
}

////////////////////////////////////////////////////
//	CRYPTOGRAPHY FUNCTIONS
////////////////////////////////////////////////////

u16 btol16(char *At)
{
	u16 result = 0;
	u8 buffer[2] = { 0 };

	ls_memcpy(At, buffer, 2);

	result |= (u16)buffer[1];
	result |= ((u16)buffer[0] << 8);

	return result;
}

u32 btol32(char *At)
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

u64 btol64(char *At)
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


void *ls_alloc(u64 size)
{
#ifdef LS_PLAT_WINDOWS
    return windows_memAlloc(size);
#endif

#ifdef LS_PLAT_LINUX
    return linux_memAlloc(size);
#endif
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

#endif
