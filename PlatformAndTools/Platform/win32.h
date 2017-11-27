#pragma once

extern "C" {
	//////////////////////////////////////////////
	// WINDOWS DEFINES
	/////////////////////////////////////////////


#define CALLBACK				__stdcall
#define WINAPI					__stdcall
#define WINAPIV					__cdecl
#define LSCDECL					__cdecl
#define APIPRIVATE				__stdcall
#define PASCAL					__stdcall
#define DECLSPEC_ALLOCATOR		__declspec(allocator)
#define LSIMPORT				__declspec(dllimport)
#define CONST					const
#define APIENTRY				WINAPI
#define WSAAPI                  PASCAL
#define WINVER					0x0500 /* version 5.0 */
#define _WIN32_WINNT			0x0A00
#define _WIN32_WINDOWS			0x0410 // I don't even know if these versions defines are right...
#define _WIN32_IE				0x0501
#define NULL					0
#define _W64

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#define DUMMYSTRUCTNAME
#define DUMMYUNIONNAME


#pragma region ErrorMacros

#define ERROR_INVALID_HANDLE             6L
#define ERROR_NOT_ENOUGH_MEMORY          8L    

#define ERROR_INVALID_PARAMETER          87L

#define WAIT_TIMEOUT                     258L

#define ERROR_OPERATION_ABORTED          995L
#define ERROR_IO_INCOMPLETE              996L
#define ERROR_IO_PENDING                 997L
#define ERROR_NOACCESS                   998L

#define STATUS_WAIT_0                    ((DWORD   )0x00000000L) 
#define STATUS_USER_APC                  ((DWORD   )0x000000C0L)
#define INFINITE						 0xFFFFFFFF

#define MAXIMUM_WAIT_OBJECTS			 64
#define WAIT_FAILED						 ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0					 ((STATUS_WAIT_0 ) + 0 )
#define WAIT_IO_COMPLETION               STATUS_USER_APC
#pragma endregion

//
// Memory Management
//

#define RtlEqualMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))
#define RtlMoveMemory(Destination,Source,Length) memmove((Destination),(Source),(Length))
#define RtlCopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))

#define MoveMemory RtlMoveMemory
#define CopyMemory RtlCopyMemory
#define FillMemory RtlFillMemory
#define ZeroMemory RtlZeroMemory

#if (defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM)) && !defined(MIDL_PASS)
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT
#endif
#define WINUSERAPI				DECLSPEC_IMPORT
#define WINABLEAPI				DECLSPEC_IMPORT
#define WINBASEAPI				DECLSPEC_IMPORT
#define WINSOCK_API_LINKAGE		DECLSPEC_IMPORT

#if !defined(_GDI32_)
#define WINGDIAPI DECLSPEC_IMPORT
#else
#define WINGDIAPI
#endif

#define POINTER_64 __ptr64
	typedef unsigned __int64 POINTER_64_INT;
#if defined(_WIN64)
#define POINTER_32 __ptr32
#else
#define POINTER_32
#endif

//
// File I/O
//

#pragma region File I/O Defines

#define CREATE_NEW							1
#define CREATE_ALWAYS						2
#define OPEN_EXISTING						3
#define OPEN_ALWAYS							4
#define TRUNCATE_EXISTING					5

#define INVALID_FILE_SIZE					((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER			((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES				((DWORD)-1)

#define GENERIC_READ						(0x80000000L)
#define GENERIC_WRITE						(0x40000000L)
#define GENERIC_EXECUTE						(0x20000000L)
#define GENERIC_ALL							(0x10000000L)

#define FILE_READ_DATA						( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY					( 0x0001 )    // directory
#define FILE_WRITE_DATA						( 0x0002 )    // file & pipe
#define FILE_ADD_FILE						( 0x0002 )    // directory
#define FILE_APPEND_DATA					( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY				( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE			( 0x0004 )    // named pipe
#define FILE_READ_EA						( 0x0008 )    // file & directory
#define FILE_WRITE_EA						( 0x0010 )    // file & directory
#define FILE_EXECUTE						( 0x0020 )    // file
#define FILE_TRAVERSE						( 0x0020 )    // directory
#define FILE_DELETE_CHILD					( 0x0040 )    // directory
#define FILE_READ_ATTRIBUTES				( 0x0080 )    // all
#define FILE_WRITE_ATTRIBUTES				( 0x0100 )    // all

#define DELETE								(0x00010000L)
#define READ_CONTROL						(0x00020000L)
#define WRITE_DAC							(0x00040000L)
#define WRITE_OWNER							(0x00080000L)
#define SYNCHRONIZE							(0x00100000L)
#define STANDARD_RIGHTS_REQUIRED			(0x000F0000L)
#define STANDARD_RIGHTS_READ				(READ_CONTROL)
#define STANDARD_RIGHTS_WRITE				(READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE				(READ_CONTROL)
#define STANDARD_RIGHTS_ALL					(0x001F0000L)
#define SPECIFIC_RIGHTS_ALL					(0x0000FFFFL)


#define FILE_ALL_ACCESS						(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ					(STANDARD_RIGHTS_READ     |\
											 FILE_READ_DATA           |\
											 FILE_READ_ATTRIBUTES     |\
											 FILE_READ_EA             |\
											 SYNCHRONIZE)


#define FILE_GENERIC_WRITE					(STANDARD_RIGHTS_WRITE    |\
											 FILE_WRITE_DATA          |\
											 FILE_WRITE_ATTRIBUTES    |\
											 FILE_WRITE_EA            |\
											 FILE_APPEND_DATA         |\
											 SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE				(STANDARD_RIGHTS_EXECUTE  |\
											 FILE_READ_ATTRIBUTES     |\
											 FILE_EXECUTE             |\
											 SYNCHRONIZE)

// end_access
#define FILE_SHARE_READ						0x00000001  
#define FILE_SHARE_WRITE					0x00000002  
#define FILE_SHARE_DELETE					0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000  
#define FILE_ATTRIBUTE_EA                   0x00040000  
#define FILE_NOTIFY_CHANGE_FILE_NAME		0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME			0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES		0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE				0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE		0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS		0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION			0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY			0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE					((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER				((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001  
#define FILE_CASE_PRESERVED_NAMES           0x00000002  
#define FILE_UNICODE_ON_DISK                0x00000004  
#define FILE_PERSISTENT_ACLS                0x00000008  
#define FILE_FILE_COMPRESSION               0x00000010  
#define FILE_VOLUME_QUOTAS                  0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100  
#define FILE_VOLUME_IS_COMPRESSED           0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000  
#define FILE_SUPPORTS_ENCRYPTION            0x00020000  
#define FILE_NAMED_STREAMS                  0x00040000  
#define FILE_READ_ONLY_VOLUME               0x00080000  
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000  
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000  
#define FILE_SUPPORTS_HARD_LINKS            0x00400000  
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000  
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000  
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000  
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000  
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000  
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000  
#define FILE_INVALID_FILE_ID               ((LONGLONG)-1LL) 

#pragma endregion

#if 0
//
// SAL Shit I really don't understand... in the end everything is just turned off.
//

#define _SAL_nop_impl_ 
#define _Null_terminated_impl_
#define _NullNull_terminated_impl_
#define _Check_return_impl_
#define _Post_satisfies_impl_(expr)
#define _Ret1_impl_(p1)
#define _Post1_impl_(p1)
#define _Group_impl_(annos)
#define _GrouP_impl_(annos)
#define _Post_impl_
#define _Success_impl_(expr)
#define _Post_                         _Post_impl_
#define _Pre_maybenull_
#define _Post_ptr_invalid_

#define _Group_(annos)                 _Group_impl_(annos _SAL_nop_impl_)
#define _GrouP_(annos)                 _GrouP_impl_(annos _SAL_nop_impl_)

#define _SA_annotes0(n)
#define _SA_annotes1(n,pp1)
#define _SA_annotes2(n,pp1,pp2)
#define _SA_annotes3(n,pp1,pp2,pp3)

#if defined(BUILD_WINDOWS) && !_USE_ATTRIBUTES_FOR_SAL
#define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)

#ifndef _SAL_L_Source_
// Some annotations aren't officially SAL2 yet.
#define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)
#endif
#else
#define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _Group_(annotes _SAL_nop_impl_)
#define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _Group_(annotes _SAL_nop_impl_)
#define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _Group_(annotes _SAL_nop_impl_)
#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)
#define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)
#endif

#define _Post_satisfies_(cond)			  _SAL2_Source_(_Post_satisfies_, (cond), _Post_satisfies_impl_(cond))
#define _Null_terminated_                 _SAL2_Source_(_Null_terminated_, (), _Null_terminated_impl_)
#define _NullNull_terminated_             _SAL2_Source_(_NullNull_terminated_, (), _NullNull_terminated_impl_)
#define _Check_return_					  _SAL2_Source_(_Check_return_, (), _Check_return_impl_)
#define _Post_equals_last_error_		  _SAL2_Source_(_Post_equals_last_error_, (),  _Post_satisfies_(_Curr_ != 0))
#define _Ret_maybenull_                   _SAL2_Source_(_Ret_maybenull_, (), _Ret1_impl_(__maybenull_impl))
#define _Post_writable_byte_size_(size)   _SAL2_Source_(_Post_writable_byte_size_, (size), _Post1_impl_(__bytecap_impl(size)))
#define __drv_freesMem(kind)			  _SAL_L_Source_(__drv_freesMem, (kind), _Post_ _SA_annotes1(SAL_NeedsRelease,__no))
#define _Frees_ptr_opt_					 _SAL_L_Source_(_Frees_ptr_opt_, (),  _Pre_maybenull_ _Post_ptr_invalid_ __drv_freesMem(Mem))
#define _Success_(expr)                  _SAL2_Source_(_Success_, (expr), _Success_impl_(expr))

#endif

//
// Aligment
//

#if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC) || defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM)
#define ALIGNMENT_MACHINE
#define UNALIGNED __unaligned
#if defined(_WIN64)
#define UNALIGNED64 __unaligned
#else
#define UNALIGNED64
#endif
#else
#undef ALIGNMENT_MACHINE
#define UNALIGNED
#define UNALIGNED64
#endif

//////////////////////////////////////////////
// FIXED-WIDTH INTEGRALS TYPES (copy-pasta of stdint.h)
//////////////////////////////////////////////

#pragma region FixedWidthTypes

	typedef signed char        int8_t;
	typedef short              int16_t;
	typedef int                int32_t;
	typedef long long          int64_t;
	typedef unsigned char      uint8_t;
	typedef unsigned short     uint16_t;
	typedef unsigned int       uint32_t;
	typedef unsigned long long uint64_t;

	typedef signed char        int_least8_t;
	typedef short              int_least16_t;
	typedef int                int_least32_t;
	typedef long long          int_least64_t;
	typedef unsigned char      uint_least8_t;
	typedef unsigned short     uint_least16_t;
	typedef unsigned int       uint_least32_t;
	typedef unsigned long long uint_least64_t;

	typedef signed char        int_fast8_t;
	typedef int                int_fast16_t;
	typedef int                int_fast32_t;
	typedef long long          int_fast64_t;
	typedef unsigned char      uint_fast8_t;
	typedef unsigned int       uint_fast16_t;
	typedef unsigned int       uint_fast32_t;
	typedef unsigned long long uint_fast64_t;

	typedef long long          intmax_t;
	typedef unsigned long long uintmax_t;

#pragma endregion

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
#ifdef _WIN64
	typedef unsigned __int64  uintptr_t;
#else
	typedef unsigned int uintptr_t;
#endif
#endif

//
// My own most used fixed-width types
//

	typedef int8_t			   s8;
	typedef int16_t			   s16;
	typedef int32_t			   s32;
	typedef int64_t			   s64;
	typedef uint8_t			   u8;
	typedef uint16_t		   u16;
	typedef uint32_t		   u32;
	typedef uint64_t		   u64;
	typedef uintptr_t		   ptr;

	typedef float			   f32;
	typedef double			   f64;

	typedef s32				   b32;

#pragma region FixedWithIntegralDefines
// These macros must exactly match those in the Windows SDK's intsafe.h.
#define INT8_MIN         (-127i8 - 1)
#define INT16_MIN        (-32767i16 - 1)
#define INT32_MIN        (-2147483647i32 - 1)
#define INT64_MIN        (-9223372036854775807i64 - 1)
#define INT8_MAX         127i8
#define INT16_MAX        32767i16
#define INT32_MAX        2147483647i32
#define INT64_MAX        9223372036854775807i64
#define UINT8_MAX        0xffui8
#define UINT16_MAX       0xffffui16
#define UINT32_MAX       0xffffffffui32
#define UINT64_MAX       0xffffffffffffffffui64

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN
#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX
#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INT_FAST8_MIN    INT8_MIN
#define INT_FAST16_MIN   INT32_MIN
#define INT_FAST32_MIN   INT32_MIN
#define INT_FAST64_MIN   INT64_MIN
#define INT_FAST8_MAX    INT8_MAX
#define INT_FAST16_MAX   INT32_MAX
#define INT_FAST32_MAX   INT32_MAX
#define INT_FAST64_MAX   INT64_MAX
#define UINT_FAST8_MAX   UINT8_MAX
#define UINT_FAST16_MAX  UINT32_MAX
#define UINT_FAST32_MAX  UINT32_MAX
#define UINT_FAST64_MAX  UINT64_MAX

#ifdef _WIN64
#define INTPTR_MIN   INT64_MIN
#define INTPTR_MAX   INT64_MAX
#define UINTPTR_MAX  UINT64_MAX
#else
#define INTPTR_MIN   INT32_MIN
#define INTPTR_MAX   INT32_MAX
#define UINTPTR_MAX  UINT32_MAX
#endif

#define INTMAX_MIN       INT64_MIN
#define INTMAX_MAX       INT64_MAX
#define UINTMAX_MAX      UINT64_MAX

#define PTRDIFF_MIN      INTPTR_MIN
#define PTRDIFF_MAX      INTPTR_MAX

#ifndef SIZE_MAX
#define SIZE_MAX     UINTPTR_MAX
#endif

#define SIG_ATOMIC_MIN   INT32_MIN
#define SIG_ATOMIC_MAX   INT32_MAX

#define WCHAR_MIN        0x0000
#define WCHAR_MAX        0xffff

#define WINT_MIN         0x0000
#define WINT_MAX         0xffff

#define INT8_C(x)    (x)
#define INT16_C(x)   (x)
#define INT32_C(x)   (x)
#define INT64_C(x)   (x ## LL)

#define UINT8_C(x)   (x)
#define UINT16_C(x)  (x)
#define UINT32_C(x)  (x ## U)
#define UINT64_C(x)  (x ## ULL)

#define INTMAX_C(x)  INT64_C(x)
#define UINTMAX_C(x) UINT64_C(x)

#pragma endregion

//////////////////////////////////////////////
// WINDOWS TYPES
//////////////////////////////////////////////

//
// Basics
//

#ifndef VOID
#define VOID			void
typedef char			CHAR;
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef USHORT			*PUSHORT;
typedef long			LONG;
typedef unsigned long	ULONG;
typedef ULONG			*PULONG;
#if !defined(MIDL_PASS)
typedef int				INT;
#endif
#endif

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed __int64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned __int64    UINT64, *PUINT64;

//
// The following types are guaranteed to be signed and 32 bits wide.
//

typedef signed int LONG32, *PLONG32;

//
// The following types are guaranteed to be unsigned and 32 bits wide.
//

typedef unsigned int ULONG32, *PULONG32;
typedef unsigned int DWORD32, *PDWORD32;

#if defined(_WIN64)
typedef __int64 INT_PTR, *PINT_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

#define __int3264   __int64

#else
typedef _W64 int INT_PTR, *PINT_PTR;
typedef _W64 unsigned int UINT_PTR, *PUINT_PTR;

typedef _W64 long LONG_PTR, *PLONG_PTR;
typedef _W64 unsigned long ULONG_PTR, *PULONG_PTR;

#define __int3264   __int32

#endif

//
// The following types are defined in the minwindef.h
//

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef WORD				ATOM;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL				*PBOOL;
typedef BOOL				*LPBOOL;
typedef BYTE				*PBYTE;
typedef BYTE				*LPBYTE;
typedef int					*PINT;
typedef int					*LPINT;
typedef WORD				*PWORD;
typedef WORD				*LPWORD;
typedef long				*LPLONG;
typedef DWORD				*PDWORD;
typedef DWORD				*LPDWORD;
typedef void				*LPVOID;
typedef CONST void			*LPCVOID;

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;
typedef ULONG_PTR			DWORD_PTR, *PDWORD_PTR;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character

typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;

typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef PWSTR *PZPWSTR;
typedef CONST PWSTR *PCZPWSTR;
typedef WCHAR UNALIGNED *LPUWSTR, *PUWSTR;
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef PCWSTR *PZPCWSTR;
typedef CONST PCWSTR *PCZPCWSTR;
typedef CONST WCHAR UNALIGNED *LPCUWSTR, *PCUWSTR;

typedef WCHAR *PZZWSTR;
typedef CONST WCHAR *PCZZWSTR;
typedef WCHAR UNALIGNED *PUZZWSTR;
typedef CONST WCHAR UNALIGNED *PCUZZWSTR;

typedef  WCHAR *PNZWCH;
typedef  CONST WCHAR *PCNZWCH;
typedef  WCHAR UNALIGNED *PUNZWCH;
typedef  CONST WCHAR UNALIGNED *PCUNZWCH;

typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;

typedef /*_Null_terminated_*/ CHAR *NPSTR, *LPSTR, *PSTR;
typedef /*_Null_terminated_*/ PSTR *PZPSTR;
typedef /*_Null_terminated_*/ CONST PSTR *PCZPSTR;
typedef /*_Null_terminated_*/ CONST CHAR *LPCSTR, *PCSTR;
typedef /*_Null_terminated_*/ PCSTR *PZPCSTR;
typedef /*_Null_terminated_*/ CONST PCSTR *PCZPCSTR;

typedef /*_NullNull_terminated_*/ CHAR *PZZSTR;
typedef /*_NullNull_terminated_*/ CONST CHAR *PCZZSTR;

typedef  CHAR *PNZCH;
typedef  CONST CHAR *PCNZCH;

typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;


#if _WIN32_WINNT >= 0x0600 || (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

typedef CONST WCHAR *LPCWCHAR, *PCWCHAR;
typedef CONST WCHAR UNALIGNED *LPCUWCHAR, *PCUWCHAR;

#endif

#define _ULONGLONG_
#if (!defined (_MAC) && (!defined(MIDL_PASS) || defined(__midl)) && (!defined(_M_IX86) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64)))
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                         (0x7fffffffffffffff)

#else

#if defined(_MAC) && defined(_MAC_INT_64)
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)


#else
typedef double LONGLONG;
typedef double ULONGLONG;
#endif //_MAC and int64

#endif

typedef LONGLONG *PLONGLONG;
typedef ULONGLONG *PULONGLONG;

#ifdef UNICODE
typedef LPCWSTR LPCTSTR;
#else
typedef LPCSTR LPCTSTR;
#endif

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
#endif //MIDL_PASS
	LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
	struct {
		DWORD LowPart;
		DWORD HighPart;
	};
	struct {
		DWORD LowPart;
		DWORD HighPart;
	} u;
	ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

#ifdef _WIN64
typedef unsigned __int64 size_t;
typedef __int64          ptrdiff_t;
typedef __int64          intptr_t;
#else
typedef unsigned int    size_t;
typedef int             ptrdiff_t;
typedef int             intptr_t;
#endif

typedef ULONGLONG  DWORDLONG;
typedef DWORDLONG *PDWORDLONG;

//
// Void
//

typedef void *PVOID;
typedef void * POINTER_64 PVOID64;

#ifdef _WIN64
typedef INT_PTR(WINAPI *FARPROC)();
typedef INT_PTR(WINAPI *NEARPROC)();
typedef INT_PTR(WINAPI *PROC)();
#else
typedef int (WINAPI *FARPROC)();
typedef int (WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();
#endif  // _WIN64

//
//	Network Typedefs
//

typedef UINT_PTR        SOCKET;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
typedef u_long			SERVICETYPE;

#pragma region ServiceTypeDefines

#define SERVICETYPE_NOTRAFFIC               0x00000000  /* No data in this direction */
#define SERVICETYPE_BESTEFFORT              0x00000001  /* Best Effort */
#define SERVICETYPE_CONTROLLEDLOAD          0x00000002  /* Controlled Load */
#define SERVICETYPE_GUARANTEED              0x00000003  /* Guaranteed */
#define SERVICETYPE_NETWORK_UNAVAILABLE     0x00000004  /* Used to notify change to user */
#define SERVICETYPE_GENERAL_INFORMATION     0x00000005  /* corresponds to "General Parameters" defined by IntServ */
#define SERVICETYPE_NOCHANGE                0x00000006  /* used to indicate that the flow spec contains no change from any previous one */
#define SERVICETYPE_NONCONFORMING           0x00000009  /* Non-Conforming Traffic */
#define SERVICETYPE_NETWORK_CONTROL         0x0000000A  /* Network Control traffic */
#define SERVICETYPE_QUALITATIVE             0x0000000D  /* Qualitative applications */ 

#pragma endregion

//
// Handle to an Object
//

#ifdef STRICT
	typedef void *HANDLE;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

DECLARE_HANDLE(HINSTANCE);
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HCURSOR);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HGLRC);
DECLARE_HANDLE(HMODULE);

//
// Function Pointers
//

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

//////////////////////////////////////////////
// WINDOWS STRUCTS
/////////////////////////////////////////////

//
// System Structures
//

typedef struct _SYSTEM_INFO {
	union {
		DWORD dwOemId;          // Obsolete field...do not use
		struct {
			WORD wProcessorArchitecture;
			WORD wReserved;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;
	DWORD dwPageSize;
	LPVOID lpMinimumApplicationAddress;
	LPVOID lpMaximumApplicationAddress;
	DWORD_PTR dwActiveProcessorMask;
	DWORD dwNumberOfProcessors;
	DWORD dwProcessorType;
	DWORD dwAllocationGranularity;
	WORD wProcessorLevel;
	WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

typedef struct _MEMORYSTATUSEX {
	DWORD dwLength;
	DWORD dwMemoryLoad;
	DWORDLONG ullTotalPhys;
	DWORDLONG ullAvailPhys;
	DWORDLONG ullTotalPageFile;
	DWORDLONG ullAvailPageFile;
	DWORDLONG ullTotalVirtual;
	DWORDLONG ullAvailVirtual;
	DWORDLONG ullAvailExtendedVirtual;
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

//
//	Graphical Related structures
//

typedef struct tagRECT
{
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

/* Pixel format descriptor */
typedef struct tagPIXELFORMATDESCRIPTOR
{
	WORD  nSize;
	WORD  nVersion;
	DWORD dwFlags;
	BYTE  iPixelType;
	BYTE  cColorBits;
	BYTE  cRedBits;
	BYTE  cRedShift;
	BYTE  cGreenBits;
	BYTE  cGreenShift;
	BYTE  cBlueBits;
	BYTE  cBlueShift;
	BYTE  cAlphaBits;
	BYTE  cAlphaShift;
	BYTE  cAccumBits;
	BYTE  cAccumRedBits;
	BYTE  cAccumGreenBits;
	BYTE  cAccumBlueBits;
	BYTE  cAccumAlphaBits;
	BYTE  cDepthBits;
	BYTE  cStencilBits;
	BYTE  cAuxBuffers;
	BYTE  iLayerType;
	BYTE  bReserved;
	DWORD dwLayerMask;
	DWORD dwVisibleMask;
	DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

#pragma region PixelDefines

//	pixel types
#define PFD_TYPE_RGBA        0
#define PFD_TYPE_COLORINDEX  1

// layer types
#define PFD_MAIN_PLANE       0
#define PFD_OVERLAY_PLANE    1
#define PFD_UNDERLAY_PLANE   (-1)

//	PIXELFORMATDESCRIPTOR flags
#define PFD_DOUBLEBUFFER            0x00000001
#define PFD_STEREO                  0x00000002
#define PFD_DRAW_TO_WINDOW          0x00000004
#define PFD_DRAW_TO_BITMAP          0x00000008
#define PFD_SUPPORT_GDI             0x00000010
#define PFD_SUPPORT_OPENGL          0x00000020
#define PFD_GENERIC_FORMAT          0x00000040
#define PFD_NEED_PALETTE            0x00000080
#define PFD_NEED_SYSTEM_PALETTE     0x00000100
#define PFD_SWAP_EXCHANGE           0x00000200
#define PFD_SWAP_COPY               0x00000400
#define PFD_SWAP_LAYER_BUFFERS      0x00000800
#define PFD_GENERIC_ACCELERATED     0x00001000
#define PFD_SUPPORT_DIRECTDRAW      0x00002000
#define PFD_DIRECT3D_ACCELERATED    0x00004000
#define PFD_SUPPORT_COMPOSITION     0x00008000

//	PIXELFORMATDESCRIPTOR flags for use in ChoosePixelFormat only
#define PFD_DEPTH_DONTCARE          0x20000000
#define PFD_DOUBLEBUFFER_DONTCARE   0x40000000
#define PFD_STEREO_DONTCARE         0x80000000

#pragma endregion

typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

//
// Message structure
//
typedef struct tagPOINT
{
	LONG  x;
	LONG  y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef struct tagMSG {
	HWND        hwnd;
	UINT        message;
	WPARAM      wParam;
	LPARAM      lParam;
	DWORD       time;
	POINT       pt;
} MSG, *PMSG, *NPMSG, *LPMSG;

//
// Window Structures
//
#define CW_USEDEFAULT       ((int)0x80000000)

#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

#define CS_IME              0x00010000
#if(_WIN32_WINNT >= 0x0501)
#define CS_DROPSHADOW       0x00020000
#endif /* _WIN32_WINNT >= 0x0501 */

typedef struct tagWNDCLASSA {
	UINT        style;
	WNDPROC     lpfnWndProc;
	int         cbClsExtra;
	int         cbWndExtra;
	HINSTANCE   hInstance;
	HICON       hIcon;
	HCURSOR     hCursor;
	HBRUSH      hbrBackground;
	LPCSTR      lpszMenuName;
	LPCSTR      lpszClassName;
} WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;

typedef struct tagWNDCLASSW {
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	HICON     hIcon;
	HCURSOR   hCursor;
	HBRUSH    hbrBackground;
	LPCTSTR   lpszMenuName;
	LPCTSTR   lpszClassName;
} WNDCLASSW, *PWNDCLASSW, *NPWNDCLASSW, *LPWNDCLASSW;

typedef struct tagCREATESTRUCTW {
	LPVOID      lpCreateParams;
	HINSTANCE   hInstance;
	HMENU       hMenu;
	HWND        hwndParent;
	int         cy;
	int         cx;
	int         y;
	int         x;
	LONG        style;
	LPCWSTR     lpszName;
	LPCWSTR     lpszClass;
	DWORD       dwExStyle;
} CREATESTRUCTW, *LPCREATESTRUCTW;

//
// File I/O
//

typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _OVERLAPPED {
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	union {
		struct {
			DWORD Offset;
			DWORD OffsetHigh;
		} DUMMYSTRUCTNAME;
		PVOID Pointer;
	} DUMMYUNIONNAME;

	HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _OVERLAPPED *    LPWSAOVERLAPPED;

typedef struct _iobuf
{
	void* _Placeholder;
} FILE;

//
//	Network Structures
//

#pragma region WSA_Errors

/*
* All Windows Sockets error constants are biased by WSABASEERR from
* the "normal"
*/
#define WSABASEERR              10000

//Windows Sockets definitions of regular Microsoft C error constants
#define WSAEINTR                (WSABASEERR+4)
#define WSAEBADF                (WSABASEERR+9)
#define WSAEACCES               (WSABASEERR+13)
#define WSAEFAULT               (WSABASEERR+14)
#define WSAEINVAL               (WSABASEERR+22)
#define WSAEMFILE               (WSABASEERR+24)

//Windows Sockets definitions of regular Berkeley error constants
#define WSAEWOULDBLOCK          (WSABASEERR+35)
#define WSAEINPROGRESS          (WSABASEERR+36)
#define WSAEALREADY             (WSABASEERR+37)
#define WSAENOTSOCK             (WSABASEERR+38)
#define WSAEDESTADDRREQ         (WSABASEERR+39)
#define WSAEMSGSIZE             (WSABASEERR+40)
#define WSAEPROTOTYPE           (WSABASEERR+41)
#define WSAENOPROTOOPT          (WSABASEERR+42)
#define WSAEPROTONOSUPPORT      (WSABASEERR+43)
#define WSAESOCKTNOSUPPORT      (WSABASEERR+44)
#define WSAEOPNOTSUPP           (WSABASEERR+45)
#define WSAEPFNOSUPPORT         (WSABASEERR+46)
#define WSAEAFNOSUPPORT         (WSABASEERR+47)
#define WSAEADDRINUSE           (WSABASEERR+48)
#define WSAEADDRNOTAVAIL        (WSABASEERR+49)
#define WSAENETDOWN             (WSABASEERR+50)
#define WSAENETUNREACH          (WSABASEERR+51)
#define WSAENETRESET            (WSABASEERR+52)
#define WSAECONNABORTED         (WSABASEERR+53)
#define WSAECONNRESET           (WSABASEERR+54)
#define WSAENOBUFS              (WSABASEERR+55)
#define WSAEISCONN              (WSABASEERR+56)
#define WSAENOTCONN             (WSABASEERR+57)
#define WSAESHUTDOWN            (WSABASEERR+58)
#define WSAETOOMANYREFS         (WSABASEERR+59)
#define WSAETIMEDOUT            (WSABASEERR+60)
#define WSAECONNREFUSED         (WSABASEERR+61)
#define WSAELOOP                (WSABASEERR+62)
#define WSAENAMETOOLONG         (WSABASEERR+63)
#define WSAEHOSTDOWN            (WSABASEERR+64)
#define WSAEHOSTUNREACH         (WSABASEERR+65)
#define WSAENOTEMPTY            (WSABASEERR+66)
#define WSAEPROCLIM             (WSABASEERR+67)
#define WSAEUSERS               (WSABASEERR+68)
#define WSAEDQUOT               (WSABASEERR+69)
#define WSAESTALE               (WSABASEERR+70)
#define WSAEREMOTE              (WSABASEERR+71)

//Extended Windows Sockets error constant definitions
#define WSASYSNOTREADY          (WSABASEERR+91)
#define WSAVERNOTSUPPORTED      (WSABASEERR+92)
#define WSANOTINITIALISED       (WSABASEERR+93)
#define WSAEDISCON              (WSABASEERR+101)
#define WSAENOMORE              (WSABASEERR+102)
#define WSAECANCELLED           (WSABASEERR+103)
#define WSAEINVALIDPROCTABLE    (WSABASEERR+104)
#define WSAEINVALIDPROVIDER     (WSABASEERR+105)
#define WSAEPROVIDERFAILEDINIT  (WSABASEERR+106)
#define WSASYSCALLFAILURE       (WSABASEERR+107)
#define WSASERVICE_NOT_FOUND    (WSABASEERR+108)
#define WSATYPE_NOT_FOUND       (WSABASEERR+109)
#define WSA_E_NO_MORE           (WSABASEERR+110)
#define WSA_E_CANCELLED         (WSABASEERR+111)
#define WSAEREFUSED             (WSABASEERR+112)

//Authoritative Answer: Host not found
#define WSAHOST_NOT_FOUND       (WSABASEERR+1001)

//Non-Authoritative: Host not found, or SERVERFAIL
#define WSATRY_AGAIN            (WSABASEERR+1002)

//Non-recoverable errors, FORMERR, REFUSED, NOTIMP
#define WSANO_RECOVERY          (WSABASEERR+1003)

//Valid name, no data record of requested type
#define WSANO_DATA              (WSABASEERR+1004)

//Compatibility macros.
#define h_errno         WSAGetLastError()
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND
#define TRY_AGAIN               WSATRY_AGAIN
#define NO_RECOVERY             WSANO_RECOVERY
#define NO_DATA                 WSANO_DATA
/* no address, look for MX record */
#define WSANO_ADDRESS           WSANO_DATA
#define NO_ADDRESS              WSANO_ADDRESS

#pragma endregion

#pragma region WinSock2Extensions
#define WSAAPI                  PASCAL
#define WSAEVENT                HANDLE
#define LPWSAEVENT              LPHANDLE
#define WSAOVERLAPPED           OVERLAPPED
typedef struct _OVERLAPPED *    LPWSAOVERLAPPED;

#define WSA_IO_PENDING          (ERROR_IO_PENDING)
#define WSA_IO_INCOMPLETE       (ERROR_IO_INCOMPLETE)
#define WSA_INVALID_HANDLE      (ERROR_INVALID_HANDLE)
#define WSA_INVALID_PARAMETER   (ERROR_INVALID_PARAMETER)
#define WSA_NOT_ENOUGH_MEMORY   (ERROR_NOT_ENOUGH_MEMORY)
#define WSA_OPERATION_ABORTED   (ERROR_OPERATION_ABORTED)

#define WSA_INVALID_EVENT       ((WSAEVENT)NULL)
#define WSA_MAXIMUM_WAIT_EVENTS (MAXIMUM_WAIT_OBJECTS)
#define WSA_WAIT_FAILED         (WAIT_FAILED)
#define WSA_WAIT_EVENT_0        (WAIT_OBJECT_0)
#define WSA_WAIT_IO_COMPLETION  (WAIT_IO_COMPLETION)
#define WSA_WAIT_TIMEOUT        (WAIT_TIMEOUT)
#define WSA_INFINITE            (INFINITE)
#pragma endregion

#pragma region AddressFamily

#define AF_UNSPEC       0               // unspecified
#define AF_UNIX         1               // local to host (pipes, portals)
#define AF_INET         2               // internetwork: UDP, TCP, etc.
#define AF_IMPLINK      3               // arpanet imp addresses
#define AF_PUP          4               // pup protocols: e.g. BSP
#define AF_CHAOS        5               // mit CHAOS protocols
#define AF_NS           6               // XEROX NS protocols
#define AF_IPX          AF_NS           // IPX protocols: IPX, SPX, etc.
#define AF_ISO          7               // ISO protocols
#define AF_OSI          AF_ISO          // OSI is ISO
#define AF_ECMA         8               // european computer manufacturers
#define AF_DATAKIT      9               // datakit protocols
#define AF_CCITT        10              // CCITT protocols, X.25 etc
#define AF_SNA          11              // IBM SNA
#define AF_DECnet       12              // DECnet
#define AF_DLI          13              // Direct data link interface
#define AF_LAT          14              // LAT
#define AF_HYLINK       15              // NSC Hyperchannel
#define AF_APPLETALK    16              // AppleTalk
#define AF_NETBIOS      17              // NetBios-style addresses
#define AF_VOICEVIEW    18              // VoiceView
#define AF_FIREFOX      19              // Protocols from Firefox
#define AF_UNKNOWN1     20              // Somebody is using this!
#define AF_BAN          21              // Banyan
#define AF_ATM          22              // Native ATM Services
#define AF_INET6        23              // Internetwork Version 6
#define AF_CLUSTER      24              // Microsoft Wolfpack
#define AF_12844        25              // IEEE 1284.4 WG AF
#define AF_IRDA         26              // IrDA
#define AF_NETDES       28              // Network Designers OSI & gateway
#define AF_TCNPROCESS   29
#define AF_TCNMESSAGE   30
#define AF_ICLFXBM      31
#define AF_BTH          32              // Bluetooth RFCOMM/L2CAP protocols
#define AF_LINK         33
#define AF_HYPERV       34
#define AF_MAX          35

#pragma endregion

#pragma region SocketDefines

//Socket Types
#define SOCK_STREAM				1
#define SOCK_DGRAM				2
#define SOCK_RAW				3
#define SOCK_RDM				4
#define SOCK_SEQPACKET			5

//Define a level for socket I/O controls in the same numbering space as IPPROTO_TCP, IPPROTO_IP, etc.
#define SOL_SOCKET				0xffff

//Define socket-level options.
#define SO_DEBUG				0x0001      // turn on debugging info recording
#define SO_ACCEPTCONN			0x0002      // socket has had listen()
#define SO_REUSEADDR			0x0004      // allow local address reuse
#define SO_KEEPALIVE			0x0008      // keep connections alive
#define SO_DONTROUTE			0x0010      // just use interface addresses
#define SO_BROADCAST			0x0020      // permit sending of broadcast msgs
#define SO_USELOOPBACK			0x0040      // bypass hardware when possible
#define SO_LINGER				0x0080      // linger on close if data present
#define SO_OOBINLINE			0x0100      // leave received OOB data in line

#define SO_DONTLINGER			(int)(~SO_LINGER)
#define SO_EXCLUSIVEADDRUSE		((int)(~SO_REUSEADDR))          // disallow local address reuse

#define SO_SNDBUF				0x1001      // send buffer size
#define SO_RCVBUF				0x1002      // receive buffer size
#define SO_SNDLOWAT				0x1003      // send low-water mark
#define SO_RCVLOWAT				0x1004      // receive low-water mark
#define SO_SNDTIMEO				0x1005      // send timeout
#define SO_RCVTIMEO				0x1006      // receive timeout
#define SO_ERROR				0x1007      // get error status and clear
#define SO_TYPE					0x1008      // get socket type
#define SO_BSP_STATE			0x1009      // get socket 5-tuple state
#define SO_GROUP_ID				0x2001      // ID of a socket group
#define SO_GROUP_PRIORITY		0x2002		// the relative priority within a group
#define SO_MAX_MSG_SIZE			0x2003      // maximum message size

#define SO_CONDITIONAL_ACCEPT	0x3002		// enable true conditional accept:

// connection is not ack-ed to the other side until conditional function returns CF_ACCEPT
#define SO_PAUSE_ACCEPT			0x3003      // pause accepting new connections
#define SO_COMPARTMENT_ID		0x3004		// get/set the compartment for a socket
#define SO_RANDOMIZE_PORT		0x3005		// randomize assignment of wildcard ports
#define SO_PORT_SCALABILITY		0x3006		// enable port scalability
#define SO_REUSE_UNICASTPORT	0x3007		// defer ephemeral port allocation for outbound connections
#define SO_REUSE_MULTICASTPORT	0x3008		// enable port reuse and disable unicast reception.

#pragma endregion

#pragma region IPPortsDefines

//Port/socket numbers: network standard functions
#define IPPORT_TCPMUX           1
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_QOTD             17
#define IPPORT_MSP              18
#define IPPORT_CHARGEN          19
#define IPPORT_FTP_DATA         20
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57

//Port/socket numbers: host specific functions
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95

//UNIX TCP sockets
#define IPPORT_POP3             110
#define IPPORT_NTP              123
#define IPPORT_EPMAP            135
#define IPPORT_NETBIOS_NS       137
#define IPPORT_NETBIOS_DGM      138
#define IPPORT_NETBIOS_SSN      139
#define IPPORT_IMAP             143
#define IPPORT_SNMP             161
#define IPPORT_SNMP_TRAP        162
#define IPPORT_IMAP3            220
#define IPPORT_LDAP             389
#define IPPORT_HTTPS            443
#define IPPORT_MICROSOFT_DS     445
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520

//UNIX UDP sockets
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
/* 520+1 also used */

//Ports < IPPORT_RESERVED are reserved for privileged processes (e.g. root).
#define IPPORT_RESERVED         1024
#define IPPORT_REGISTERED_MIN   IPPORT_RESERVED
#define IPPORT_REGISTERED_MAX   0xbfff
#define IPPORT_DYNAMIC_MIN      0xc000
#define IPPORT_DYNAMIC_MAX      0xffff

#pragma endregion

#pragma region NetworkMessageDefines

#define MSG_OOB				0x1             /* process out-of-band data */
#define MSG_PEEK			0x2             /* peek at incoming message */
#define MSG_DONTROUTE		0x4             /* send without using routing tables */
#define MSG_WAITALL			0x8             /* do not complete until packet is completely filled */
#define MSG_PUSH_IMMEDIATE	0x20         /* Do not delay receive request completion if data is available */
#define MSG_PARTIAL			0x8000          /* partial send or recv for message xport */

//WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and WSARecvFrom()
#define MSG_INTERRUPT		0x10            /* send/recv in the interrupt context */
#define MSG_MAXIOVLEN		16

#pragma endregion

#define INADDR_ANY              (ULONG)0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        (ULONG)0xffffffff
#define INADDR_NONE             0xffffffff

#define INET_ADDRSTRLEN			22
#define INET6_ADDRSTRLEN		65

#define ADDR_ANY                INADDR_ANY

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

//Level number for (get/set)sockopt() to apply to socket itself
#define SOL_SOCKET				0xffff          //Options for socket level
#define SOMAXCONN				0x7fffffff		//Maximum queue length specifiable by listen
#define SOMAXCONN_HINT(b)		(-(b))
#define INVALID_SOCKET			(SOCKET)(~0)
#define SOCKET_ERROR            (-1)

//N.B. required for backwards compatability to support 0 = IP for the level argument to get/setsockopt.
#define IPPROTO_IP              0

//Protocols.  The IPv6 defines are specified in RFC 2292.
typedef enum {
	IPPROTO_HOPOPTS = 0,	// IPv6 Hop-by-Hop options
	IPPROTO_ICMP = 1,
	IPPROTO_IGMP = 2,
	IPPROTO_GGP = 3,
	IPPROTO_IPV4 = 4,
	IPPROTO_ST = 5,
	IPPROTO_TCP = 6,
	IPPROTO_CBT = 7,
	IPPROTO_EGP = 8,
	IPPROTO_IGP = 9,
	IPPROTO_PUP = 12,
	IPPROTO_UDP = 17,
	IPPROTO_IDP = 22,
	IPPROTO_RDP = 27,
	IPPROTO_IPV6 = 41,		// IPv6 header
	IPPROTO_ROUTING = 43,	// IPv6 Routing header
	IPPROTO_FRAGMENT = 44,	// IPv6 fragmentation header
	IPPROTO_ESP = 50,		// encapsulating security payload
	IPPROTO_AH = 51,		// authentication header
	IPPROTO_ICMPV6 = 58,	// ICMPv6
	IPPROTO_NONE = 59,		// IPv6 no next header
	IPPROTO_DSTOPTS = 60,	// IPv6 Destination options
	IPPROTO_ND = 77,
	IPPROTO_ICLFXBM = 78,
	IPPROTO_PIM = 103,
	IPPROTO_PGM = 113,
	IPPROTO_L2TP = 115,
	IPPROTO_SCTP = 132,
	IPPROTO_RAW = 255,
	IPPROTO_MAX = 256,
	//
	//  These are reserved for internal use by Windows.
	//
	IPPROTO_RESERVED_RAW = 257,
	IPPROTO_RESERVED_IPSEC = 258,
	IPPROTO_RESERVED_IPSECOFFLOAD = 259,
	IPPROTO_RESERVED_WNV = 260,
	IPPROTO_RESERVED_MAX = 261
} IPPROTO, *PIPROTO;

typedef struct WSAData {
	WORD                    wVersion;
	WORD                    wHighVersion;
#ifdef _WIN64
	unsigned short          iMaxSockets;
	unsigned short          iMaxUdpDg;
	char					*lpVendorInfo;
	char                    szDescription[WSADESCRIPTION_LEN + 1];
	char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
#else
	char                    szDescription[WSADESCRIPTION_LEN + 1];
	char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
	unsigned short          iMaxSockets;
	unsigned short          iMaxUdpDg;
	char *					lpVendorInfo;
#endif
} WSADATA, *LPWSADATA;

#define FD_SETSIZE	64

typedef struct fd_set {
	u_int	fd_count;				/* how many are SET? */
	SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} fd_set;

struct timeval {
	long    tv_sec;					/* seconds */
	long    tv_usec;				/* and microseconds */
};

//Scope ID definition
typedef enum {
	ScopeLevelInterface = 1,
	ScopeLevelLink = 2,
	ScopeLevelSubnet = 3,
	ScopeLevelAdmin = 4,
	ScopeLevelSite = 5,
	ScopeLevelOrganization = 8,
	ScopeLevelGlobal = 14,
	ScopeLevelCount = 16
} SCOPE_LEVEL;

typedef struct {
	union {
		struct {
			u_long Zone : 28;
			u_long Level : 4;
		};
		u_long Value;
	};
} SCOPE_ID, *PSCOPE_ID;

//IPv4 Internet address. This is an 'on-wire' format structure. (TERRIBLE STRUCTURE! JUST USE s_addr)
typedef struct in_addr {
	union {
		struct { u_char s_b1, s_b2, s_b3, s_b4; } S_un_b;
		struct { u_short s_w1, s_w2; } S_un_w;
		u_long S_addr;
	} S_un;
#define s_addr  S_un.S_addr			/* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR, *LPIN_ADDR;

//IPv6 Internet address (RFC 2553). This is an 'on-wire' format structure.
typedef struct in6_addr {
	union {
		u_char       Byte[16];
		u_short      Word[8];
	} u;

#define s6_addr8                u.Byte
#define s6_addr16               u.Word

} IN6_ADDR, *PIN6_ADDR, *LPIN6_ADDR;

typedef struct sockaddr {
	u_short sa_family;				// Address family, AF_xxx
	char	sa_data[14];			// Up to 14 bytes of direct address(protocol address)
} SOCKADDR, *PSOCKADDR, *LPSOCKADDR;

typedef struct sockaddr_in {
	
	u_short sin_family;
	u_short	sin_port;
	IN_ADDR sin_addr;
	char	sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;

typedef struct sockaddr_in6 {
	u_short sin6_family;			// AF_INET6.
	u_short sin6_port;				// Transport level port number.
	u_long  sin6_flowinfo;			// IPv6 flow information.
	IN6_ADDR sin6_addr;				// IPv6 address.
	union {
		u_long		sin6_scope_id;	// Set of interfaces for a scope.
		SCOPE_ID	sin6_scope_struct;
	};
} SOCKADDR_IN6_LH, *PSOCKADDR_IN6_LH, *LPSOCKADDR_IN6_LH;

#define _SS_MAXSIZE 128                 // Maximum size
#define _SS_ALIGNSIZE (sizeof(__int64)) // Desired alignment
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(u_short))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(u_short) + _SS_PAD1SIZE + _SS_ALIGNSIZE))
typedef struct sockaddr_storage {
	u_short ss_family;					// address family

	char	__ss_pad1[_SS_PAD1SIZE];	// 6 byte pad, this is to make
										// implementation specific pad up to
										// alignment field that follows explicit
										// in the data structure
	__int64 __ss_align;					// Field to force desired structure
	char	__ss_pad2[_SS_PAD2SIZE];	// 112 byte pad to achieve desired size;
										// _SS_MAXSIZE value minus size of
										// ss_family, __ss_pad1, and
										// __ss_align fields is 112
} SOCKADDR_STORAGE_LH, *PSOCKADDR_STORAGE_LH, *LPSOCKADDR_STORAGE_LH;

typedef struct _WSABUF {
	u_long	len;					/* the length of the buffer */
	char	*buf;					/* the pointer to the buffer */
} WSABUF, *LPWSABUF;

typedef struct _flowspec
{
	u_long       TokenRate;              /* In Bytes/sec */
	u_long       TokenBucketSize;        /* In Bytes */
	u_long       PeakBandwidth;          /* In Bytes/sec */
	u_long       Latency;                /* In microseconds */
	u_long       DelayVariation;         /* In microseconds */
	SERVICETYPE  ServiceType;
	u_long       MaxSduSize;             /* In Bytes */
	u_long       MinimumPolicedSize;     /* In Bytes */

} FLOWSPEC, *PFLOWSPEC, *LPFLOWSPEC;

typedef struct _QualityOfService
{
	FLOWSPEC      SendingFlowspec;       /* the flow spec for data sending */
	FLOWSPEC      ReceivingFlowspec;     /* the flow spec for data receiving */
	WSABUF        ProviderSpecific;      /* additional provider specific stuff */
} QOS, *LPQOS;

typedef struct addrinfo
{
	int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
	int                 ai_family;      // PF_xxx
	int                 ai_socktype;    // SOCK_xxx
	int                 ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
	size_t              ai_addrlen;     // Length of ai_addr
	char *              ai_canonname;   // Canonical name for nodename
	struct sockaddr *   ai_addr;        // Binary address
	struct addrinfo *   ai_next;        // Next structure in linked list
} ADDRINFOA, *PADDRINFOA;

//
// Window Styles
//

#pragma region WindowStylesDefines

#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L


#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

#pragma endregion

//
// Common Window Styles
//
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX    | \
                             WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW      (WS_POPUP          | \
                             WS_BORDER         | \
                             WS_SYSMENU)

#define WS_CHILDWINDOW      (WS_CHILD)


//////////////////////////////////////////////
// WINDOWS FUNCTIONS
/////////////////////////////////////////////

int			CALLBACK				WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT		CALLBACK				WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);
WINBASEAPI	BOOL		WINAPI		CloseHandle(HANDLE hObject);
WINBASEAPI	FARPROC		WINAPI		GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
WINBASEAPI	HMODULE		WINAPI		GetModuleHandleA(LPCTSTR lpModuleName);
WINBASEAPI	HMODULE		WINAPI		LoadLibraryA(LPCSTR lpLibFileName);
WINBASEAPI	VOID		WINAPI		GetSystemTime(LPSYSTEMTIME lpSystemTime);
WINBASEAPI	VOID		WINAPI		GetLocalTime(LPSYSTEMTIME lpSystemTime);
WINBASEAPI	BOOL		WINAPI		GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer);
WINBASEAPI	VOID		WINAPI		GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
WINBASEAPI	VOID		WINAPI		GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);
WINBASEAPI	BOOL		WINAPI		FileTimeToSystemTime(CONST FILETIME * lpFileTime, LPSYSTEMTIME lpSystemTime);
WINBASEAPI	BOOL		WINAPI		QueryPerformanceCounter(LARGE_INTEGER * lpPerformanceCount);
WINBASEAPI	BOOL		WINAPI		QueryPerformanceFrequency(LARGE_INTEGER * lpFrequency);

WINBASEAPI	VOID		WINAPI		Sleep(DWORD dwMilliseconds);
WINBASEAPI	DWORD		WINAPI		SleepEx(DWORD dwMilliseconds, BOOL bAlertable);

WINBASEAPI	VOID		WINAPI		OutputDebugStringA(LPCSTR lpOutputString);
WINBASEAPI	VOID		WINAPI		DebugBreak(VOID);
WINBASEAPI	DWORD		WINAPI		GetLastError(VOID);

#pragma region ConsoleDefines

#define STD_INPUT_HANDLE    ((DWORD)-10)
#define STD_OUTPUT_HANDLE   ((DWORD)-11)
#define STD_ERROR_HANDLE    ((DWORD)-12)
#define _O_RDONLY      0x0000  // open for reading only
#define _O_WRONLY      0x0001  // open for writing only
#define _O_RDWR        0x0002  // open for reading and writing
#define _O_APPEND      0x0008  // writes done at eof
#define _O_CREAT       0x0100  // create and open file
#define _O_TRUNC       0x0200  // open and truncate
#define _O_EXCL        0x0400  // open only if file doesn't already exist

// O_TEXT files have <cr><lf> sequences translated to <lf> on read()'s and <lf> sequences translated to <cr><lf> on write()'s
#define _O_TEXT        0x4000  // file mode is text (translated)
#define _O_BINARY      0x8000  // file mode is binary (untranslated)
#define _O_WTEXT       0x10000 // file mode is UTF16 (translated)
#define _O_U16TEXT     0x20000 // file mode is UTF16 no BOM (translated)
#define _O_U8TEXT      0x40000 // file mode is UTF8  no BOM (translated)
#define _O_NOINHERIT   0x0080  // child process doesn't inherit file
#define _O_TEMPORARY   0x0040  // temporary file bit (file is deleted when last handle is closed)
#define _O_SHORT_LIVED 0x1000  // temporary storage file, try not to flush
#define _O_OBTAIN_DIR  0x2000  // get information about a directory
#define _O_SEQUENTIAL  0x0020  // file access is primarily sequential
#define _O_RANDOM      0x0010  // file access is primarily random

#define _O_RAW _O_BINARY // macro to translate the C 2.0 name used to force binary mode for files

#define EOF    (-1)
#define _IOFBF 0x0000
#define _IOLBF 0x0040
#define _IONBF 0x0004

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

#pragma endregion

WINBASEAPI	BOOL		WINAPI		AllocConsole(VOID);
WINBASEAPI	HANDLE		WINAPI		GetStdHandle(DWORD nStdHandle);
LSIMPORT	int			LSCDECL		_open_osfhandle(intptr_t OSFileHandle, int Flags);
LSIMPORT	FILE*		LSCDECL		_fdopen(int FileHandle, char const* Mode);
LSIMPORT	int			LSCDECL		setvbuf(FILE* Stream, char* Buffer, int Mode, size_t Size);
LSIMPORT	FILE*		LSCDECL		__acrt_iob_func(unsigned);

//
// File I/O
//
typedef		VOID		(WINAPI *LPOVERLAPPED_COMPLETION_ROUTINE)(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);

WINBASEAPI	HANDLE		WINAPI		CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI	BOOL		WINAPI		ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINBASEAPI	BOOL		WINAPI		ReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI	BOOL		WINAPI		WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINBASEAPI	BOOL		WINAPI		WriteFileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINBASEAPI	BOOL		WINAPI		GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize);
WINBASEAPI	DWORD		WINAPI		GetFileType(HANDLE hFile);

//
// Memory Management
//

#pragma region Defines
#define HEAP_ZERO_MEMORY			0x00000008
#define HEAP_NO_SERIALIZE			0x00000001
#define HEAP_GENERATE_EXCEPTIONS	0x00000004

#define PAGE_NOACCESS          0x01     
#define PAGE_READONLY          0x02     
#define PAGE_READWRITE         0x04     
#define PAGE_WRITECOPY         0x08     
#define PAGE_EXECUTE           0x10     
#define PAGE_EXECUTE_READ      0x20     
#define PAGE_EXECUTE_READWRITE 0x40     
#define PAGE_EXECUTE_WRITECOPY 0x80     
#define PAGE_GUARD            0x100     
#define PAGE_NOCACHE          0x200     
#define PAGE_WRITECOMBINE     0x400     
#define PAGE_REVERT_TO_FILE_MAP     0x80000000     
#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000     
#define PAGE_TARGETS_NO_UPDATE      0x40000000     
#define PAGE_TARGETS_INVALID        0x40000000     
#define PAGE_ENCLAVE_UNVALIDATED    0x20000000     
#define MEM_COMMIT                  0x1000      
#define MEM_RESERVE                 0x2000      
#define MEM_DECOMMIT                0x4000      
#define MEM_RELEASE                 0x8000      
#define MEM_FREE                    0x10000     
#define MEM_PRIVATE                 0x20000     
#define MEM_MAPPED                  0x40000     
#define MEM_RESET                   0x80000     
#define MEM_TOP_DOWN                0x100000    
#define MEM_WRITE_WATCH             0x200000    
#define MEM_PHYSICAL                0x400000    
#define MEM_ROTATE                  0x800000    
#define MEM_DIFFERENT_IMAGE_BASE_OK 0x800000    
#define MEM_RESET_UNDO              0x1000000   
#define MEM_LARGE_PAGES             0x20000000  
#define MEM_4MB_PAGES               0x80000000  
#define SEC_FILE           0x800000     
#define SEC_IMAGE         0x1000000     
#define SEC_PROTECTED_IMAGE  0x2000000  
#define SEC_RESERVE       0x4000000     
#define SEC_COMMIT        0x8000000     
#define SEC_NOCACHE      0x10000000     
#define SEC_WRITECOMBINE 0x40000000     
#define SEC_LARGE_PAGES  0x80000000     
#define SEC_IMAGE_NO_EXECUTE (SEC_IMAGE | SEC_NOCACHE)     
#define MEM_IMAGE         SEC_IMAGE     
#define WRITE_WATCH_FLAG_RESET  0x01     
#define MEM_UNMAP_WITH_TRANSIENT_BOOST  0x01     

#define ENCLAVE_TYPE_SGX            0x00000001

#pragma endregion

WINBASEAPI	DECLSPEC_ALLOCATOR	LPVOID	WINAPI	HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI	BOOL	WINAPI	HeapFree(HANDLE hHeap, DWORD dwFlags, /*__drv_freesMem(Mem) _Frees_ptr_opt_*/ LPVOID lpMem);
WINBASEAPI 	LPVOID	WINAPI	VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

WINBASEAPI	HANDLE	WINAPI	GetProcessHeap(VOID);

//
// Message Queue
//

#pragma region VK Codes

//
// Virtual Keys, Standard Set
//
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

//0x07 : reserved

#define VK_BACK           0x08
#define VK_TAB            0x09

//0x0A - 0x0B : reserved

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

//0x0E - 0x0F : unassigned

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15

//0x16 : unassigned

#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

//0x1A : unassigned

#define VK_ESCAPE         0x1B
#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F
#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

/*
* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x3A - 0x40 : unassigned
* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D

//0x5E : reserved

#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#if(_WIN32_WINNT >= 0x0604)

//0x88 - 0x8F : UI navigation

#define VK_NAVIGATION_VIEW     0x88 // reserved
#define VK_NAVIGATION_MENU     0x89 // reserved
#define VK_NAVIGATION_UP       0x8A // reserved
#define VK_NAVIGATION_DOWN     0x8B // reserved
#define VK_NAVIGATION_LEFT     0x8C // reserved
#define VK_NAVIGATION_RIGHT    0x8D // reserved
#define VK_NAVIGATION_ACCEPT   0x8E // reserved
#define VK_NAVIGATION_CANCEL   0x8F // reserved

#endif /* _WIN32_WINNT >= 0x0604 */

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

//NEC PC-9800 kbd definitions

#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad

//Fujitsu/OASYS kbd definitions

#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

//0x97 - 0x9F : unassigned

/*
* VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
* Used only as parameters to GetAsyncKeyState() and GetKeyState().
* No other API or message will distinguish left and right keys in this way.
*/
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC
#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

//0xB8 - 0xB9 : reserved

#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

//0xC1 - 0xC2 : reserved

#if(_WIN32_WINNT >= 0x0604)

//0xC3 - 0xDA : Gamepad input

#define VK_GAMEPAD_A                         0xC3 // reserved
#define VK_GAMEPAD_B                         0xC4 // reserved
#define VK_GAMEPAD_X                         0xC5 // reserved
#define VK_GAMEPAD_Y                         0xC6 // reserved
#define VK_GAMEPAD_RIGHT_SHOULDER            0xC7 // reserved
#define VK_GAMEPAD_LEFT_SHOULDER             0xC8 // reserved
#define VK_GAMEPAD_LEFT_TRIGGER              0xC9 // reserved
#define VK_GAMEPAD_RIGHT_TRIGGER             0xCA // reserved
#define VK_GAMEPAD_DPAD_UP                   0xCB // reserved
#define VK_GAMEPAD_DPAD_DOWN                 0xCC // reserved
#define VK_GAMEPAD_DPAD_LEFT                 0xCD // reserved
#define VK_GAMEPAD_DPAD_RIGHT                0xCE // reserved
#define VK_GAMEPAD_MENU                      0xCF // reserved
#define VK_GAMEPAD_VIEW                      0xD0 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON    0xD1 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON   0xD2 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_UP        0xD3 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_DOWN      0xD4 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT     0xD5 // reserved
#define VK_GAMEPAD_LEFT_THUMBSTICK_LEFT      0xD6 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_UP       0xD7 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN     0xD8 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT    0xD9 // reserved
#define VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT     0xDA // reserved

#endif /* _WIN32_WINNT >= 0x0604 */


#define VK_OEM_4          0xDB  //  '[{' for US
#define VK_OEM_5          0xDC  //  '\|' for US
#define VK_OEM_6          0xDD  //  ']}' for US
#define VK_OEM_7          0xDE  //  ''"' for US
#define VK_OEM_8          0xDF

//0xE0 : reserved

//Various extended or enhanced keyboards

#define VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP       0xE3  //  Help key on ICO
#define VK_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define VK_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define VK_ICO_CLEAR      0xE6

#if(_WIN32_WINNT >= 0x0500)
#define VK_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

//0xE8 : unassigned

//Nokia/Ericsson definitions
#define VK_OEM_RESET      0xE9
#define VK_OEM_JUMP       0xEA
#define VK_OEM_PA1        0xEB
#define VK_OEM_PA2        0xEC
#define VK_OEM_PA3        0xED
#define VK_OEM_WSCTRL     0xEE
#define VK_OEM_CUSEL      0xEF
#define VK_OEM_ATTN       0xF0
#define VK_OEM_FINISH     0xF1
#define VK_OEM_COPY       0xF2
#define VK_OEM_AUTO       0xF3
#define VK_OEM_ENLW       0xF4
#define VK_OEM_BACKTAB    0xF5
#define VK_ATTN           0xF6
#define VK_CRSEL          0xF7
#define VK_EXSEL          0xF8
#define VK_EREOF          0xF9
#define VK_PLAY           0xFA
#define VK_ZOOM           0xFB
#define VK_NONAME         0xFC
#define VK_PA1            0xFD
#define VK_OEM_CLEAR      0xFE

//0xFF : reserved


#pragma endregion

WINUSERAPI	BOOL		WINAPI		PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
WINUSERAPI	BOOL		WINAPI		PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
WINUSERAPI	BOOL		WINAPI		GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
WINUSERAPI	BOOL		WINAPI		GetMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
WINUSERAPI  BOOL		WINAPI		TranslateMessage(CONST MSG *lpMsg);
WINUSERAPI	LRESULT		WINAPI		DispatchMessageA(CONST MSG *lpMsg);
WINUSERAPI	LRESULT		WINAPI		DispatchMessageW(CONST MSG *lpMsg);
			LRESULT		WINAPI		DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WINUSERAPI	BOOL		WINAPI		PostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WINUSERAPI	VOID		WINAPI		PostQuitMessage(int nExitCode);
WINUSERAPI	BOOL		WINAPI		DestroyWindow(HWND hWnd);
WINUSERAPI	HWND		WINAPI		GetActiveWindow(void);

WINUSERAPI	HWND		WINAPI		SetCapture(HWND hWnd);
WINUSERAPI	BOOL		WINAPI		ReleaseCapture(void);
WINUSERAPI	BOOL		WINAPI		GetCursorPos(LPPOINT lpPoint);
WINUSERAPI	BOOL		WINAPI		SetCursorPos(int X, int Y);


//
//PeekMessage() Options
//
#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002
#if(WINVER >= 0x0500)
#define PM_QS_INPUT         (QS_INPUT << 16)
#define PM_QS_POSTMESSAGE   ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
#define PM_QS_PAINT         (QS_PAINT << 16)
#define PM_QS_SENDMESSAGE   (QS_SENDMESSAGE << 16)
#endif /* WINVER >= 0x0500 */

//
// (Actual)Windows Management Stuff
//
#pragma region WINDOS_MESSAGES_MACROS

#define     WA_INACTIVE     0
#define     WA_ACTIVE       1 //WM_ACTIVATE state values
#define     WA_CLICKACTIVE  2

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005
#define WM_ACTIVATE                     0x0006
#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016
#endif
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A

#if(WINVER >= 0x0400)
#define WM_SETTINGCHANGE				WM_WININICHANGE
#endif /* WINVER >= 0x0400 */

#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023
#define WM_GETMINMAXINFO                0x0024
#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039
#if(WINVER >= 0x0500)
	#ifndef _WIN32_WCE
	#define WM_GETOBJECT                0x003D
	#endif
#endif /* WINVER >= 0x0500 */

#define WM_COMPACTING                   0x0041
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047
#define WM_POWER                        0x0048

#define PWR_OK              1
#define PWR_FAIL            (-1)
#define PWR_SUSPENDREQUEST  1			//wParam for WM_POWER window message and DRV_POWER driver notification
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3

#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B

#if(WINVER >= 0x0400)
#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define NFR_ANSI                             1
#define NFR_UNICODE                          2
#define NF_QUERY                             3
#define NF_REQUERY                           4

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080
#endif /* WINVER >= 0x0400 */

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9

#if(_WIN32_WINNT >= 0x0500)
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT_DEVICE_CHANGE          0x00FE
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT                        0x00FF
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#if(_WIN32_WINNT >= 0x0501)
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109
#define UNICODE_NOCHAR                  0xFFFF
#else
#define WM_KEYLAST                      0x0108
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F
#endif /* WINVER >= 0x0400 */

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#if(WINVER >= 0x0601)
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A
#endif /* WINVER >= 0x0601 */
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121
#if(WINVER >= 0x0500)
	#ifndef _WIN32_WCE
		#define WM_MENURBUTTONUP                0x0122
		#define WM_MENUDRAG                     0x0123
		#define WM_MENUGETOBJECT                0x0124
		#define WM_UNINITMENUPOPUP              0x0125
		#define WM_MENUCOMMAND                  0x0126
		
		#ifndef _WIN32_WCE
			#if(_WIN32_WINNT >= 0x0500)
				#define WM_CHANGEUISTATE                0x0127
				#define WM_UPDATEUISTATE                0x0128
				#define WM_QUERYUISTATE                 0x0129
				
				#define UIS_SET                         1
				#define UIS_CLEAR                       2 //LOWORD(wParam) values in WM_*UISTATE*
				#define UIS_INITIALIZE                  3
				
				#define UISF_HIDEFOCUS                  0x1
				#define UISF_HIDEACCEL                  0x2 //HIWORD(wParam) values in WM_*UISTATE*
				#if(_WIN32_WINNT >= 0x0501)
					#define UISF_ACTIVE                     0x4
				#endif /* _WIN32_WINNT >= 0x0501 */
			#endif /* _WIN32_WINNT >= 0x0500 */
		#endif
	#endif
#endif /* WINVER >= 0x0500 */

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1
#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSEHWHEEL                  0x020E
#endif

#if (_WIN32_WINNT >= 0x0600)
#define WM_MOUSELAST                    0x020E
#elif (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSELAST                    0x020A
#else
#define WM_MOUSELAST                    0x0209
#endif /* (_WIN32_WINNT >= 0x0600) */

#if(_WIN32_WINNT >= 0x0400)
//Value for rolling one detent
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

//Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES
#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

//XButton values are WORD flags
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
//Were there to be an XBUTTON3, its value would be 0x0004
#endif /* _WIN32_WINNT >= 0x0500 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_DEVICECHANGE                 0x0219
#endif /* WINVER >= 0x0400 */

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229
#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#if(WINVER >= 0x0400)
#define WM_APP                          0x8000
#endif /* WINVER >= 0x0400 */

/*
* NOTE: All Message Numbers below 0x0400 are RESERVED.
*
* Private Window Messages Start Here:
*/
#define WM_USER                         0x0400

#pragma endregion

WINUSERAPI	HWND		WINAPI		CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
WINUSERAPI	HWND		WINAPI		CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
WINUSERAPI	ATOM		WINAPI		RegisterClassA(CONST WNDCLASSA *lpWndClass);
WINUSERAPI	ATOM		WINAPI		RegisterClassW(const WNDCLASSW *lpWndClass);

//
// Windows Graphical Interface Functions
//

WINUSERAPI	HDC			WINAPI		GetDC(HWND hWnd);
WINGDIAPI	int			WINAPI		ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR *ppfd);
WINGDIAPI	BOOL		WINAPI		SetPixelFormat(HDC hdc, int format, CONST PIXELFORMATDESCRIPTOR * ppfd);
WINGDIAPI	int			WINAPI		StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, 
													int SrcHeight, CONST VOID *lpBits, CONST BITMAPINFO *lpbmi, UINT iUsage, DWORD rop);
WINGDIAPI	BOOL		WINAPI		SwapBuffers(HDC);

//
// Windows Socket Functions (Network Programming)
//

typedef	void	(CALLBACK * LPWSAOVERLAPPED_COMPLETION_ROUTINE)(DWORD dwError,DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);

WINSOCK_API_LINKAGE		int		WSAAPI		WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
WINSOCK_API_LINKAGE		int		WSAAPI		WSACleanup(void);
WINSOCK_API_LINKAGE		int		WSAAPI		WSAGetLastError(void);
WINSOCK_API_LINKAGE		int		WSAAPI		WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINSOCK_API_LINKAGE		int		WSAAPI		WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
WINSOCK_API_LINKAGE		int		WSAAPI		WSAConnect(SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);

WINSOCK_API_LINKAGE		SOCKET	WSAAPI		socket(int af, int type, int protocol);
WINSOCK_API_LINKAGE		int		WSAAPI		select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);
WINSOCK_API_LINKAGE		SOCKET	WSAAPI		accept(SOCKET s, struct sockaddr *addr, int *addrlen);
WINSOCK_API_LINKAGE		int		WSAAPI		bind(SOCKET s, const struct sockaddr *name, int namelen);
WINSOCK_API_LINKAGE		int		WSAAPI		closesocket(SOCKET s);
WINSOCK_API_LINKAGE		int		WSAAPI		connect(SOCKET s, const struct sockaddr *name, int namelen);
WINSOCK_API_LINKAGE		int		WSAAPI		send(SOCKET s, const char *buf, int len, int flags);
WINSOCK_API_LINKAGE		int		WSAAPI		recv(SOCKET s, char *buf, int len, int flags);
WINSOCK_API_LINKAGE		int		WSAAPI		shutdown(SOCKET s, int how);

WINSOCK_API_LINKAGE		u_long	WSAAPI		htonl(u_long hostlong);
WINSOCK_API_LINKAGE		u_short	WSAAPI		htons(u_short hostshort);
WINSOCK_API_LINKAGE		u_long	WSAAPI		ntohl(u_long netlong);
WINSOCK_API_LINKAGE		u_short	WSAAPI		ntohs(u_short netshort);

WINSOCK_API_LINKAGE		int		WSAAPI		getaddrinfo(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, ADDRINFOA *ppResult);
WINSOCK_API_LINKAGE		int		WSAAPI		inet_pton(int Family, PCSTR pszAddrString, PVOID pAddrBuf);
						PCSTR	WSAAPI		inet_ntop(int Family, const VOID *pAddr, PSTR pStringBuf, size_t StringBufSize);
WINSOCK_API_LINKAGE		u_long	WSAAPI		inet_addr(const char *cp);

WINSOCK_API_LINKAGE		int		WSAAPI		listen(SOCKET s, int backlog);
}

#ifdef _DEBUG
#define Assert(condition) if(!condition){DebugBreak();}
#else
#define Assert(condition) ((void)0);
#endif