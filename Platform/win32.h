#pragma once

#ifdef __GNUG__
#define __int64 long long
#define __ptr64 
#endif

extern "C" {
	//////////////////////////////////////////////
	// WINDOWS DEFINES
	/////////////////////////////////////////////
    
    
#define CALLBACK			  __stdcall
#define WINAPI				__stdcall
#define WINAPIV			   __cdecl
#define LSCDECL			   __cdecl
#define APIPRIVATE			__stdcall
#define PASCAL				__stdcall
#define DECLSPEC_ALLOCATOR	__declspec(allocator)
#define LSIMPORT			  __declspec(dllimport)
#define CONST				 const
#define APIENTRY			  WINAPI
#define WSAAPI                PASCAL
#define WINVER				0x0500 /* version 5.0 */
#define _WIN32_WINNT		  0x0A00
#define _WIN32_WINDOWS		0x0410 // I don't even know if these versions defines are right...
#define _WIN32_IE			 0x0501
#define NULL				  0
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
    
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
    
#define DUMMYSTRUCTNAME
#define DUMMYUNIONNAME
    
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#ifdef UNICODE
#define MAKEINTRESOURCE  MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE  MAKEINTRESOURCEA
#endif // !UNICODE
    
#pragma region ErrorMacros
    
#define ERROR_INVALID_HANDLE             6L
#define ERROR_NOT_ENOUGH_MEMORY          8L
    
#define ERROR_INVALID_PARAMETER          87L
    
#define WAIT_TIMEOUT                     258L
    
#define ERROR_OPERATION_ABORTED          995L
#define ERROR_IO_INCOMPLETE              996L
#define ERROR_IO_PENDING                 997L
#define ERROR_NOACCESS                   998L
    
#define STATUS_WAIT_0                    ((DWORD)0x00000000L)
#define STATUS_USER_APC                  ((DWORD)0x000000C0L)
#define INFINITE						 0xFFFFFFFF
    
#define MAXIMUM_WAIT_OBJECTS			 64
#define WAIT_FAILED					  ((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0					((STATUS_WAIT_0 ) + 0 )
#define WAIT_IO_COMPLETION               STATUS_USER_APC
#pragma endregion
    
#define _ACRTIMP __declspec(dllimport)
    
#define MAX_PATH 0x00000104
    
    //
    // Memory Management
    //
    
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
    
#ifdef _WIN64
	typedef unsigned __int64 size_t;
	typedef __int64          ptrdiff_t;
	typedef __int64          intptr_t;
#else
	typedef unsigned int    size_t;
	typedef int             ptrdiff_t;
	typedef int             intptr_t;
#endif
    
    //
    // My own most used fixed-width types
    //
    
	typedef int8_t     s8;
	typedef int16_t	s16;
	typedef int32_t	s32;
	typedef int64_t	s64;
	typedef intptr_t   ptr;
	typedef uint8_t	u8;
	typedef uint16_t   u16;
	typedef uint32_t   u32;
	typedef uint64_t   u64;
	typedef uintptr_t  uptr;
    
	typedef float	  f32;
	typedef double	 f64;
    
	typedef s32		b32;
    
#pragma region FixedWithIntegralDefines
    // These macros must exactly match those in the Windows SDK's intsafe.h.
#ifdef __GNUG__
#define INT8_MIN         (-127 - 1)
#define INT16_MIN        (-32767 - 1)
#define INT32_MIN        (-2147483647 - 1)
#define INT64_MIN        (-9223372036854775807LL - 1)
#define INT8_MAX         127
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807LL
#define UINT8_MAX        0xff
#define UINT16_MAX       0xffffU
#define UINT32_MAX       0xffffffffU
#define UINT64_MAX       0xffffffffffffffffULL
    
#else
    
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
    
#endif
    
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
    typedef int				 *PINT;
    typedef int				 *LPINT;
    typedef WORD				*PWORD;
    typedef WORD				*LPWORD;
    typedef long				*LPLONG;
    typedef DWORD			   *PDWORD;
    typedef DWORD			   *LPDWORD;
    typedef void				*LPVOID;
    typedef CONST void		  *LPCVOID;
    
    typedef UINT_PTR            WPARAM;
    typedef LONG_PTR            LPARAM;
    typedef LONG_PTR            LRESULT;
    typedef ULONG_PTR		   DWORD_PTR, *PDWORD_PTR;
    
    typedef int                 INT;
    typedef unsigned int        UINT;
    typedef unsigned int        *PUINT;
    
    typedef long                __time32_t;
    typedef __int64             __time64_t;
    
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
    
    typedef DWORD ACCESS_MASK;
    typedef ACCESS_MASK* PACCESS_MASK;
    
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
        
        typedef ULONGLONG  DWORDLONG;
        typedef DWORDLONG *PDWORDLONG;
        
        //
        // Void
        //
        
        typedef void *PVOID;
        typedef void *POINTER_64 PVOID64;
        
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
        typedef UINT MMRESULT;   /* error return code, 0 means no error */
        typedef LONG HRESULT;
        
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
        DECLARE_HANDLE(HKL);
        DECLARE_HANDLE(HFONT);
        DECLARE_HANDLE(HGLOBAL);
        
        //
        // Function Pointers
        //
        
        typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
        
        typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE) (LPVOID lpThreadParameter);
        
        //////////////////////////////////////////////
        // WINDOWS STRUCTS
        /////////////////////////////////////////////
        
        typedef struct tagKBDLLHOOKSTRUCT {
            DWORD     vkCode;
            DWORD     scanCode;
            DWORD     flags;
            DWORD     time;
            ULONG_PTR dwExtraInfo;
        } KBDLLHOOKSTRUCT, *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;
        
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
        
        typedef struct timecaps_tag {
            UINT wPeriodMin;
            UINT wPeriodMax;
        } TIMECAPS, *PTIMECAPS, *NPTIMECAPS, *LPTIMECAPS;
        
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
        
        typedef struct tagSIZE {
            LONG cx;
            LONG cy;
        } SIZE, *PSIZE, *LPSIZE;
        
        
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
        
        
        /* constants for CreateDIBitmap */
#define CBM_INIT        0x04L   /* initialize bitmap */
        
#pragma endregion
        
        typedef long *LPFXPT16DOT16;
        typedef long *LPFXPT2DOT30;
        typedef long FXPT16DOT16;
        typedef long FXPT2DOT30;
        
        
        typedef struct tagCIEXYZ
        {
            FXPT2DOT30 ciexyzX;
            FXPT2DOT30 ciexyzY;
            FXPT2DOT30 ciexyzZ;
        } CIEXYZ;
        
        typedef struct tagICEXYZTRIPLE
        {
            CIEXYZ  ciexyzRed;
            CIEXYZ  ciexyzGreen;
            CIEXYZ  ciexyzBlue;
        } CIEXYZTRIPLE;
        
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
        
        typedef struct {
            DWORD        bV5Size;
            LONG         bV5Width;
            LONG         bV5Height;
            WORD         bV5Planes;
            WORD         bV5BitCount;
            DWORD        bV5Compression;
            DWORD        bV5SizeImage;
            LONG         bV5XPelsPerMeter;
            LONG         bV5YPelsPerMeter;
            DWORD        bV5ClrUsed;
            DWORD        bV5ClrImportant;
            DWORD        bV5RedMask;
            DWORD        bV5GreenMask;
            DWORD        bV5BlueMask;
            DWORD        bV5AlphaMask;
            DWORD        bV5CSType;
            CIEXYZTRIPLE bV5Endpoints;
            DWORD        bV5GammaRed;
            DWORD        bV5GammaGreen;
            DWORD        bV5GammaBlue;
            DWORD        bV5Intent;
            DWORD        bV5ProfileData;
            DWORD        bV5ProfileSize;
            DWORD        bV5Reserved;
        } BITMAPV5HEADER, *LPBITMAPV5HEADER, *PBITMAPV5HEADER;
        
        typedef struct tagBITMAPINFO {
            BITMAPINFOHEADER    bmiHeader;
            RGBQUAD             *bmiColors;
        } BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;
        
        
#pragma region BitmapInfoDefines
        
#define DIB_RGB_COLORS 0
#define DIB_PAL_COLORS 1
        
#define BI_RGB         0L
#define BI_RLE8        1L
#define BI_RLE4        2L
#define BI_BITFIELDS   3L
#define BI_JPEG        4L
#define BI_PNG         5L
        
#define SRCCOPY     (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT    (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND      (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT   (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE    (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY  (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY   (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT  (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY     (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT    (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT   (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT   (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS   (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS   (DWORD)0x00FF0062 /* dest = WHITE                    */
        
#define NOMIRRORBITMAP (DWORD)0x80000000 /* Do not Mirror the bitmap in this call */
#define CAPTUREBLT     (DWORD)0x40000000 /* Include layered windows */
        
#define GDI_ERROR (0xFFFFFFFFL)
#define HGDI_ERROR ((HANDLE)-1)
        
#pragma endregion
        
        //
        // Message structure
        //
        typedef struct tagPOINT
        {
            LONG  x;
            LONG  y;
        } POINT, *PPOINT, *NPPOINT, *LPPOINT;
        
        typedef struct tagPOINTS {
            SHORT x;
            SHORT y;
        } POINTS, *PPOINTS;
        
        typedef struct tagMSG {
            HWND        hwnd;
            UINT        message;
            WPARAM      wParam;
            LPARAM      lParam;
            DWORD       time;
            POINT       pt;
        } MSG, *PMSG, *NPMSG, *LPMSG;
        
        /*
 * GetSystemMetrics() codes
 */
#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXVSCROLL            2
#define SM_CYHSCROLL            3
#define SM_CYCAPTION            4
#define SM_CXBORDER             5
#define SM_CYBORDER             6
#define SM_CXDLGFRAME           7
#define SM_CYDLGFRAME           8
#define SM_CYVTHUMB             9
#define SM_CXHTHUMB             10
#define SM_CXICON               11
#define SM_CYICON               12
#define SM_CXCURSOR             13
#define SM_CYCURSOR             14
#define SM_CYMENU               15
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CYKANJIWINDOW        18
#define SM_MOUSEPRESENT         19
#define SM_CYVSCROLL            20
#define SM_CXHSCROLL            21
#define SM_DEBUG                22
#define SM_SWAPBUTTON           23
#define SM_RESERVED1            24
#define SM_RESERVED2            25
#define SM_RESERVED3            26
#define SM_RESERVED4            27
#define SM_CXMIN                28
#define SM_CYMIN                29
#define SM_CXSIZE               30
#define SM_CYSIZE               31
#define SM_CXFRAME              32
#define SM_CYFRAME              33
#define SM_CXMINTRACK           34
#define SM_CYMINTRACK           35
#define SM_CXDOUBLECLK          36
#define SM_CYDOUBLECLK          37
#define SM_CXICONSPACING        38
#define SM_CYICONSPACING        39
#define SM_MENUDROPALIGNMENT    40
#define SM_PENWINDOWS           41
#define SM_DBCSENABLED          42
#define SM_CMOUSEBUTTONS        43
#define SM_CXFIXEDFRAME           SM_CXDLGFRAME  /* ;win40 name change */
#define SM_CYFIXEDFRAME           SM_CYDLGFRAME  /* ;win40 name change */
#define SM_CXSIZEFRAME            SM_CXFRAME     /* ;win40 name change */
#define SM_CYSIZEFRAME            SM_CYFRAME     /* ;win40 name change */
#define SM_SECURE               44
#define SM_CXEDGE               45
#define SM_CYEDGE               46
#define SM_CXMINSPACING         47
#define SM_CYMINSPACING         48
#define SM_CXSMICON             49
#define SM_CYSMICON             50
#define SM_CYSMCAPTION          51
#define SM_CXSMSIZE             52
#define SM_CYSMSIZE             53
#define SM_CXMENUSIZE           54
#define SM_CYMENUSIZE           55
#define SM_ARRANGE              56
#define SM_CXMINIMIZED          57
#define SM_CYMINIMIZED          58
#define SM_CXMAXTRACK           59
#define SM_CYMAXTRACK           60
#define SM_CXMAXIMIZED          61
#define SM_CYMAXIMIZED          62
#define SM_NETWORK              63
#define SM_CLEANBOOT            67
#define SM_CXDRAG               68
#define SM_CYDRAG               69
#define SM_SHOWSOUNDS           70
#define SM_CXMENUCHECK          71   /* Use instead of GetMenuCheckMarkDimensions()! */
#define SM_CYMENUCHECK          72
#define SM_SLOWMACHINE          73
#define SM_MIDEASTENABLED       74
#define SM_MOUSEWHEELPRESENT    75
#define SM_XVIRTUALSCREEN       76
#define SM_YVIRTUALSCREEN       77
#define SM_CXVIRTUALSCREEN      78
#define SM_CYVIRTUALSCREEN      79
#define SM_CMONITORS            80
#define SM_SAMEDISPLAYFORMAT    81
#define SM_IMMENABLED           82
#define SM_CXFOCUSBORDER        83
#define SM_CYFOCUSBORDER        84
#define SM_TABLETPC             86
#define SM_MEDIACENTER          87
#define SM_STARTER              88
#define SM_SERVERR2             89
#define SM_MOUSEHORIZONTALWHEELPRESENT    91
#define SM_CXPADDEDBORDER       92
#define SM_DIGITIZER            94
#define SM_MAXIMUMTOUCHES       95
#define SM_CMETRICS             97
#define SM_REMOTESESSION        0x1000
#define SM_SHUTTINGDOWN           0x2000
#define SM_REMOTECONTROL          0x2001
#define SM_CARETBLINKINGENABLED   0x2002
#define SM_CONVERTIBLESLATEMODE   0x2003
#define SM_SYSTEMDOCKED           0x2004
        
        
        typedef struct tagWINDOWINFO {
            DWORD cbSize;
            RECT  rcWindow;
            RECT  rcClient;
            DWORD dwStyle;
            DWORD dwExStyle;
            DWORD dwWindowStatus;
            UINT  cxWindowBorders;
            UINT  cyWindowBorders;
            ATOM  atomWindowType;
            WORD  wCreatorVersion;
        } WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;
        
        
#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14
#define CF_HDROP            15
#define CF_LOCALE           16
#define CF_DIBV5            17
#define CF_MAX              18
        
#define CF_OWNERDISPLAY     0x0080
#define CF_DSPTEXT          0x0081
#define CF_DSPBITMAP        0x0082
#define CF_DSPMETAFILEPICT  0x0083
#define CF_DSPENHMETAFILE   0x008E
        
        /*
         * "Private" formats don't get GlobalFree()'d
         */
#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF
        
        /*
         * "GDIOBJ" formats do get DeleteObject()'d
         */
#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF
        
        
#define GHND          0x0042
#define GMEM_FIXED    0x0000
#define GMEM_MOVEABLE 0x0002
#define GMEM_ZEROINIT 0x0040
#define GPTR          0x0040
        
        
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
        
        typedef struct tagWNDCLASSEXA {
            UINT      cbSize;
            UINT      style;
            WNDPROC   lpfnWndProc;
            int       cbClsExtra;
            int       cbWndExtra;
            HINSTANCE hInstance;
            HICON     hIcon;
            HCURSOR   hCursor;
            HBRUSH    hbrBackground;
            LPCSTR    lpszMenuName;
            LPCSTR    lpszClassName;
            HICON     hIconSm;
        } WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;
        
        typedef struct tagWNDCLASSEXW {
            UINT        cbSize;
            UINT        style;
            WNDPROC     lpfnWndProc;
            int         cbClsExtra;
            int         cbWndExtra;
            HINSTANCE   hInstance;
            HICON       hIcon;
            HCURSOR     hCursor;
            HBRUSH      hbrBackground;
            LPCWSTR     lpszMenuName;
            LPCWSTR     lpszClassName;
            HICON       hIconSm;
        } WNDCLASSEXW, *PWNDCLASSEXW, *NPWNDCLASSEXW, *LPWNDCLASSEXW;
        
        typedef struct tagDRAWITEMSTRUCT {
            UINT      CtlType;
            UINT      CtlID;
            UINT      itemID;
            UINT      itemAction;
            UINT      itemState;
            HWND      hwndItem;
            HDC       hDC;
            RECT      rcItem;
            ULONG_PTR itemData;
        } DRAWITEMSTRUCT, *PDRAWITEMSTRUCT, *LPDRAWITEMSTRUCT;
        
        typedef struct tagMEASUREITEMSTRUCT {
            UINT      CtlType;
            UINT      CtlID;
            UINT      itemID;
            UINT      itemWidth;
            UINT      itemHeight;
            ULONG_PTR itemData;
        } MEASUREITEMSTRUCT, *PMEASUREITEMSTRUCT, *LPMEASUREITEMSTRUCT;
        
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
        // Window Menu Structures
        //
        
        typedef HANDLE HBITMAP;
        typedef HANDLE HRGN;
        typedef HANDLE HGDIOBJ;
        typedef DWORD COLORREF;
        typedef DWORD* LPCOLORREF;
        
#define win32RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
        
        typedef struct tagMENUINFO
        {
            DWORD   cbSize;
            DWORD   fMask;
            DWORD   dwStyle;
            UINT    cyMax;
            HBRUSH  hbrBack;
            DWORD   dwContextHelpID;
            ULONG_PTR dwMenuData;
        } MENUINFO, *LPMENUINFO;
        typedef MENUINFO CONST *LPCMENUINFO;
        
        
        typedef struct tagMENUITEMINFOA
        {
            UINT     cbSize;
            UINT     fMask;
            UINT     fType;         // used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
            UINT     fState;        // used if MIIM_STATE
            UINT     wID;           // used if MIIM_ID
            HMENU    hSubMenu;      // used if MIIM_SUBMENU
            HBITMAP  hbmpChecked;   // used if MIIM_CHECKMARKS
            HBITMAP  hbmpUnchecked; // used if MIIM_CHECKMARKS
            ULONG_PTR dwItemData;   // used if MIIM_DATA
            LPSTR    dwTypeData;    // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
            UINT     cch;           // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
            HBITMAP  hbmpItem;      // used if MIIM_BITMAP
        }   MENUITEMINFOA, *LPMENUITEMINFOA;
        
        typedef struct tagMENUITEMINFOW
        {
            UINT     cbSize;
            UINT     fMask;
            UINT     fType;         // used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
            UINT     fState;        // used if MIIM_STATE
            UINT     wID;           // used if MIIM_ID
            HMENU    hSubMenu;      // used if MIIM_SUBMENU
            HBITMAP  hbmpChecked;   // used if MIIM_CHECKMARKS
            HBITMAP  hbmpUnchecked; // used if MIIM_CHECKMARKS
            ULONG_PTR dwItemData;   // used if MIIM_DATA
            LPWSTR   dwTypeData;    // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
            UINT     cch;           // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
            HBITMAP  hbmpItem;      // used if MIIM_BITMAP
        }   MENUITEMINFOW, *LPMENUITEMINFOW;
        
        typedef MENUITEMINFOA CONST *LPCMENUITEMINFOA;
        typedef MENUITEMINFOW CONST *LPCMENUITEMINFOW;
        
        typedef struct tagTCITEMA
        {
            UINT mask;
            DWORD dwState;
            DWORD dwStateMask;
            LPSTR pszText;
            int cchTextMax;
            int iImage;
            
            LPARAM lParam;
        } TCITEMA, *LPTCITEMA;
        
        
        typedef struct tagPAINTSTRUCT {
            HDC  hdc;
            BOOL fErase;
            RECT rcPaint;
            BOOL fRestore;
            BOOL fIncUpdate;
            BYTE rgbReserved[32];
        } PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;
        
        typedef struct tagDRAWTEXTPARAMS {
            UINT cbSize;
            int  iTabLength;
            int  iLeftMargin;
            int  iRightMargin;
            UINT uiLengthDrawn;
        } DRAWTEXTPARAMS, *LPDRAWTEXTPARAMS;
        
        /* size of a device name string */
#define CCHDEVICENAME 32
        
        /* size of a form name string */
#define CCHFORMNAME 32
        
        typedef struct _POINTL {
            LONG x;
            LONG y;
        } POINTL, *PPOINTL;
        
        typedef struct _devicemodeA {
            BYTE  dmDeviceName[CCHDEVICENAME];
            WORD  dmSpecVersion;
            WORD  dmDriverVersion;
            WORD  dmSize;
            WORD  dmDriverExtra;
            DWORD dmFields;
            union {
                struct {
                    short dmOrientation;
                    short dmPaperSize;
                    short dmPaperLength;
                    short dmPaperWidth;
                    short dmScale;
                    short dmCopies;
                    short dmDefaultSource;
                    short dmPrintQuality;
                } DUMMYSTRUCTNAME;
                POINTL dmPosition;
                struct {
                    POINTL dmPosition;
                    DWORD  dmDisplayOrientation;
                    DWORD  dmDisplayFixedOutput;
                } DUMMYSTRUCTNAME2;
            } DUMMYUNIONNAME;
            short dmColor;
            short dmDuplex;
            short dmYResolution;
            short dmTTOption;
            short dmCollate;
            BYTE  dmFormName[CCHFORMNAME];
            WORD  dmLogPixels;
            DWORD dmBitsPerPel;
            DWORD dmPelsWidth;
            DWORD dmPelsHeight;
            union {
                DWORD dmDisplayFlags;
                DWORD dmNup;
            } DUMMYUNIONNAME2;
            DWORD dmDisplayFrequency;
            DWORD dmICMMethod;
            DWORD dmICMIntent;
            DWORD dmMediaType;
            DWORD dmDitherType;
            DWORD dmReserved1;
            DWORD dmReserved2;
            DWORD dmPanningWidth;
            DWORD dmPanningHeight;
        } DEVMODEA, *PDEVMODEA, *NPDEVMODEA, *LPDEVMODEA;
        
        
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
        
        typedef struct _WIN32_FIND_DATAA {
            DWORD    dwFileAttributes;
            FILETIME ftCreationTime;
            FILETIME ftLastAccessTime;
            FILETIME ftLastWriteTime;
            DWORD    nFileSizeHigh;
            DWORD    nFileSizeLow;
            DWORD    dwReserved0;
            DWORD    dwReserved1;
            CHAR     cFileName[MAX_PATH];
            CHAR     cAlternateFileName[14];
            DWORD    dwFileType;
            DWORD    dwCreatorType;
            WORD     wFinderFlags;
        } WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
        
        typedef enum _FINDEX_INFO_LEVELS {
            FindExInfoStandard,
            FindExInfoBasic,
            FindExInfoMaxInfoLevel
        } FINDEX_INFO_LEVELS;
        
        typedef enum _FINDEX_SEARCH_OPS {
            FindExSearchNameMatch,
            FindExSearchLimitToDirectories,
            FindExSearchLimitToDevices
        } FINDEX_SEARCH_OPS;
        
        
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
        
#pragma region AIFlags
        
#define AI_PASSIVE                0x01
#define AI_CANONNAME              0x02
#define AI_NUMERICHOST            0x04
#define AI_ALL                    0x0100
#define AI_ADDRCONFIG             0x0400
#define AI_V4MAPPED               0x0800
#define AI_NON_AUTHORITATIVE      0x04000
#define AI_SECURE                 0x08000
#define AI_RETURN_PREFERRED_NAMES 0x010000
#define AI_FQDN                   0x00020000
#define AI_FILESERVER             0x00040000
        
#pragma endregion
        
#pragma region SocketDefines
        
        typedef u32 socklen_t;
        
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
#define MSG_PEEK			   0x2             /* peek at incoming message */
#define MSG_DONTROUTE		  0x4             /* send without using routing tables */
#define MSG_WAITALL			0x8             /* do not complete until packet is completely filled */
#define MSG_PUSH_IMMEDIATE	 0x20         /* Do not delay receive request completion if data is available */
#define MSG_PARTIAL			0x8000          /* partial send or recv for message xport */
        
        //WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and WSARecvFrom()
#define MSG_INTERRUPT		  0x10            /* send/recv in the interrupt context */
#define MSG_MAXIOVLEN		  16
        
#pragma endregion
        
#define INADDR_ANY              (ULONG)0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        (ULONG)0xffffffff
#define INADDR_NONE             0xffffffff
        
#define INET_ADDRSTRLEN		 22
#define INET6_ADDRSTRLEN		65
        
#define ADDR_ANY                INADDR_ANY
        
#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128
        
        //Level number for (get/set)sockopt() to apply to socket itself
#define SOL_SOCKET			   0xffff          //Options for socket level
#define SOMAXCONN				0x7fffffff		//Maximum queue length specifiable by listen
#define SOMAXCONN_HINT(b)		(-(b))
#define INVALID_SOCKET		   (SOCKET)(~0)
#define SOCKET_ERROR             (-1)
        
        //N.B. required for backwards compatability to support 0 = IP for the level argument to get/setsockopt.
#define IPPROTO_IP               0
        
#define NSPROTO_IPX      1000
#define NSPROTO_SPX      1256
#define NSPROTO_SPXII    1257
        
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
        
        /*
         * Structures returned by network data base library, taken from the
         * BSD file netdb.h.  All addresses are supplied in host order, and
         * returned in network order (suitable for use in system calls).
         */
        
        struct  hostent
        {
            char    * h_name;          /* official name of host */
            char    **h_aliases;       /* alias list */
            short   h_addrtype;        /* host address type */
            short   h_length;          /* length of address */
            char    **h_addr_list;     /* list of addresses */
#define h_addr  h_addr_list[0] /* address, for backward compat */
        };
        
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
        
        /* timer error return values */
#define TIMERR_BASE           96
#define TIMERR_NOERROR        (0)                  /* no error */
#define TIMERR_NOCANDO        (TIMERR_BASE+1)      /* request not completed */
#define TIMERR_STRUCT         (TIMERR_BASE+33)     /* time struct size */
        
        int        WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
        LRESULT    WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);
        BOOL       CloseHandle(HANDLE hObject);
        FARPROC    GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
        HMODULE    GetModuleHandleA(LPCTSTR lpModuleName);
        HMODULE    LoadLibraryA(LPCSTR lpLibFileName);
        HANDLE     CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                SIZE_T dwStackSize,LPTHREAD_START_ROUTINE lpStartAddress,
                                LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
        HRESULT    SetThreadDescription(HANDLE hThread, PCWSTR lpThreadDescription);
        
        VOID       GetSystemTime(LPSYSTEMTIME lpSystemTime);
        int        GetSystemMetrics(int nIndex);
        VOID       GetLocalTime(LPSYSTEMTIME lpSystemTime);
        
        __time32_t _time32(__time32_t* _Time);
        __time64_t _time64(__time64_t* _Time);
        
        BOOL       GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer);
        VOID       GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
        VOID       GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);
        BOOL       FileTimeToSystemTime(CONST FILETIME * lpFileTime, LPSYSTEMTIME lpSystemTime);
        MMRESULT   timeBeginPeriod(UINT uPeriod);
        MMRESULT   timeEndPeriod(UINT uPeriod);
        BOOL       QueryPerformanceCounter(LARGE_INTEGER * lpPerformanceCount);
        BOOL       QueryPerformanceFrequency(LARGE_INTEGER * lpFrequency);
        
        MMRESULT   timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc);
        VOID       Sleep(DWORD dwMilliseconds);
        DWORD      SleepEx(DWORD dwMilliseconds, BOOL bAlertable);
        
        VOID       OutputDebugStringA(LPCSTR lpOutputString);
        VOID       DebugBreak(VOID);
        DWORD      GetLastError(VOID);
        
        HGLOBAL    GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
        LPVOID     GlobalLock(HGLOBAL hMem);
        BOOL       GlobalUnlock(HGLOBAL hMem);
        
        BOOL       OpenClipboard(HWND hWndNewOwner);
        BOOL       CloseClipboard(VOID);
        HANDLE     GetClipboardData(UINT uFormat);
        HANDLE     SetClipboardData(UINT uFormat, HANDLE hMem);
        BOOL EmptyClipboard();
        
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
        
        LSIMPORT	  int		 LSCDECL		_open_osfhandle(intptr_t OSFileHandle, int Flags);
        LSIMPORT	  FILE*	   LSCDECL		_fdopen(int FileHandle, char const* Mode);
        LSIMPORT	  int		 LSCDECL		setvbuf(FILE* Stream, char* Buffer, int Mode, size_t Size);
        LSIMPORT	  FILE*	   LSCDECL		__acrt_iob_func(unsigned);
        
        //TODO: Probably Remove
        size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
        FILE *fopen(const char *filename, const char *mode);
        int putchar(int c);
        
        WINBASEAPI	BOOL		WINAPI		AllocConsole(VOID);
        WINBASEAPI	BOOL		WINAPI		FreeConsole(VOID);
        WINBASEAPI	HANDLE	  WINAPI		GetStdHandle(DWORD nStdHandle);
        
        //
        // File I/O
        //
        typedef		VOID		(WINAPI *LPOVERLAPPED_COMPLETION_ROUTINE)(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);
        
        WINBASEAPI	HANDLE	   WINAPI		CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
        WINBASEAPI	BOOL		 WINAPI		ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
        WINBASEAPI	BOOL		 WINAPI		ReadFileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
        WINBASEAPI	BOOL		 WINAPI		WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
        WINBASEAPI	BOOL		 WINAPI		WriteFileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
        WINBASEAPI	BOOL		 WINAPI		GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize);
        WINBASEAPI	DWORD		WINAPI		GetFileType(HANDLE hFile);
        WINBASEAPI    DWORD        WINAPI        GetFullPathNameA(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer, LPSTR *lpFilePart);
        
        WINBASEAPI    HANDLE       WINAPI        FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
        WINBASEAPI    HANDLE       WINAPI        FindFirstFileExA(LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags);
        WINBASEAPI    BOOL         WINAPI        FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
        WINBASEAPI    BOOL         WINAPI        FindClose(HANDLE hFindFile);
        
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
        
#ifdef __GNUG__ //NOTE: Because of warning: 'allocator' attribute directive ignored [-Wattributes]
        WINBASEAPI	LPVOID	WINAPI	HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
#else
        WINBASEAPI	DECLSPEC_ALLOCATOR	LPVOID	WINAPI	HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
#endif
        WINBASEAPI	BOOL	WINAPI	HeapFree(HANDLE hHeap, DWORD dwFlags, /*__drv_freesMem(Mem) _Frees_ptr_opt_*/ LPVOID lpMem);
        WINBASEAPI 	LPVOID	WINAPI	VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
        WINBASEAPI 	BOOL      WINAPI	VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
        
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
        
        /*
         * ShowWindow() Commands
         */
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11
        
#define RDW_INVALIDATE          0x0001
#define RDW_INTERNALPAINT       0x0002
#define RDW_ERASE               0x0004
        
#define RDW_VALIDATE            0x0008
#define RDW_NOINTERNALPAINT     0x0010
#define RDW_NOERASE             0x0020
        
#define RDW_NOCHILDREN          0x0040
#define RDW_ALLCHILDREN         0x0080
        
#define RDW_UPDATENOW           0x0100
#define RDW_ERASENOW            0x0200
        
#define RDW_FRAME               0x0400
#define RDW_NOFRAME             0x0800
        
        /*
         * Standard Cursor IDs
         */
#define IDC_ARROW           MAKEINTRESOURCE(32512)
#define IDC_IBEAM           MAKEINTRESOURCE(32513)
#define IDC_WAIT            MAKEINTRESOURCE(32514)
#define IDC_CROSS           MAKEINTRESOURCE(32515)
#define IDC_UPARROW         MAKEINTRESOURCE(32516)
#define IDC_SIZE            MAKEINTRESOURCE(32640)  /* OBSOLETE: use IDC_SIZEALL */
#define IDC_ICON            MAKEINTRESOURCE(32641)  /* OBSOLETE: use IDC_ARROW */
#define IDC_SIZENWSE        MAKEINTRESOURCE(32642)
#define IDC_SIZENESW        MAKEINTRESOURCE(32643)
#define IDC_SIZEWE          MAKEINTRESOURCE(32644)
#define IDC_SIZENS          MAKEINTRESOURCE(32645)
#define IDC_SIZEALL         MAKEINTRESOURCE(32646)
#define IDC_NO              MAKEINTRESOURCE(32648) /*not in win3.1 */
#define IDC_HAND            MAKEINTRESOURCE(32649)
#define IDC_APPSTARTING     MAKEINTRESOURCE(32650) /*not in win3.1 */
#define IDC_HELP            MAKEINTRESOURCE(32651)
        
#pragma endregion
        
        /*
 * Window field offsets for GetWindowLong()
 */
#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)
        
#ifdef _WIN64
        
#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_USERDATA
        
#endif /* _WIN64 */
        
#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)
        
        
        /*
 * Windowstation-specific access flags
 */
#define WINSTA_ENUMDESKTOPS         0x0001L
#define WINSTA_READATTRIBUTES       0x0002L
#define WINSTA_ACCESSCLIPBOARD      0x0004L
#define WINSTA_CREATEDESKTOP        0x0008L
#define WINSTA_WRITEATTRIBUTES      0x0010L
#define WINSTA_ACCESSGLOBALATOMS    0x0020L
#define WINSTA_EXITWINDOWS          0x0040L
#define WINSTA_ENUMERATE            0x0100L
#define WINSTA_READSCREEN           0x0200L
        
#define WINSTA_ALL_ACCESS           (WINSTA_ENUMDESKTOPS  | WINSTA_READATTRIBUTES  | WINSTA_ACCESSCLIPBOARD | \
WINSTA_CREATEDESKTOP | WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | \
WINSTA_EXITWINDOWS   | WINSTA_ENUMERATE       | WINSTA_READSCREEN)
        
        
        /*
 * SetWindowsHook() codes
 */
#define WH_MIN              (-1)
#define WH_MSGFILTER        (-1)
#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
#define WH_KEYBOARD         2
#define WH_GETMESSAGE       3
#define WH_CALLWNDPROC      4
#define WH_CBT              5
#define WH_SYSMSGFILTER     6
#define WH_MOUSE            7
#define WH_HARDWARE         8
#define WH_DEBUG            9
#define WH_SHELL           10
#define WH_FOREGROUNDIDLE  11
#define WH_CALLWNDPROCRET  12
#define WH_KEYBOARD_LL     13
#define WH_MOUSE_LL        14
#define WH_MAX             14
        
        /*
         * Hook Codes
         */
#define HC_ACTION           0
#define HC_GETNEXT          1
#define HC_SKIP             2
#define HC_NOREMOVE         3
#define HC_NOREM            HC_NOREMOVE
#define HC_SYSMODALON       4
#define HC_SYSMODALOFF      5
        
        /*
         * CBT Hook Codes
         */
#define HCBT_MOVESIZE       0
#define HCBT_MINMAX         1
#define HCBT_QS             2
#define HCBT_CREATEWND      3
#define HCBT_DESTROYWND     4
#define HCBT_ACTIVATE       5
#define HCBT_CLICKSKIPPED   6
#define HCBT_KEYSKIPPED     7
#define HCBT_SYSCOMMAND     8
#define HCBT_SETFOCUS       9
        
        
        /* ---------------------- */
        /* Operating System Hooks */
        /* ---------------------- */
        
        typedef LRESULT (*HOOKPROC)(int, WPARAM, LPARAM);
        typedef HANDLE HHOOK;
        
        HHOOK    SetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId);
        LRESULT  CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);
        /* ---------------------------- */
        /* High Level Window Management */
        /* ---------------------------- */
        
        typedef HANDLE HWINSTA;
        typedef HANDLE HDESK;
        typedef BOOL (*DESKTOPENUMPROCA)(LPSTR, LPARAM);
        typedef BOOL (*WINSTAENUMPROCA)(LPSTR, LPARAM);
        typedef BOOL (*WNDENUMPROC)(HWND, LPARAM);
        
        HWINSTA  GetProcessWindowStation();
        HWINSTA  OpenWindowStationA(LPCSTR lpszWinSta, BOOL fInherit, ACCESS_MASK dwDesiredAccess);
        
        BOOL     EnumWindowStationsA(WINSTAENUMPROCA lpEnumFunc, LPARAM lParam);
        
        BOOL     EnumDesktopsA(HWINSTA hwinsta, DESKTOPENUMPROCA lpEnumFunc, LPARAM lParam);
        HDESK    OpenDesktopA(LPCSTR lpszDesktop, DWORD dwFlags, BOOL fInherit, ACCESS_MASK dwDesiredAccess);
        
        BOOL     EnumDesktopWindows(HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam);
        BOOL     EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);
        
        HDESK    CreateDesktopExA(LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA *pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid);
        BOOL     SwitchDesktop(HDESK hDesktop);
        
        
        /* --------------------------- */
        /* Low Level Window Management */
        /* --------------------------- */
        
        BOOL     PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
        BOOL     PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
        BOOL     GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
        BOOL     GetMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
        LRESULT  SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        LRESULT  SendMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        BOOL     TranslateMessage(CONST MSG *lpMsg);
        LRESULT  DispatchMessageA(CONST MSG *lpMsg);
        LRESULT  DispatchMessageW(CONST MSG *lpMsg);
        LRESULT  DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        LRESULT  CallWindowProcA(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        LRESULT  CallWindowProcW(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        LONG     GetWindowLongA(HWND hWnd, int  nIndex);
        LONG_PTR SetWindowLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong);
        LONG_PTR SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong);
        
        BOOL     PostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        VOID     PostQuitMessage(int nExitCode);
        BOOL     DestroyWindow(HWND hWnd);
        HWND     GetActiveWindow(void);
        HWND     GetForegroundWindow(void);
        HWND     GetDesktopWindow();
        BOOL     GetWindowInfo(HWND hwnd, PWINDOWINFO pwi);
        BOOL     GetWindowRect(HWND hWnd, LPRECT lpRect);
        BOOL     GetClientRect(HWND hWnd, LPRECT lpRect);
        int      GetWindowRgn(HWND hWnd, HRGN rgn);
        int      GetWindowRgnBox(HWND hWnd, LPRECT lprc);
        BOOL     UpdateWindow(HWND hWnd);
        BOOL     RedrawWindow(HWND hWnd, const RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags);
        BOOL     InvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase);
        VOID     ExitProcess(UINT uExitCode);
        
        HCURSOR  SetCursor(HCURSOR hCursor);
        HCURSOR  LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);
        HCURSOR  LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName);
        HWND     SetCapture(HWND hWnd);
        BOOL     ReleaseCapture(void);
        BOOL     GetCursorPos(LPPOINT lpPoint);
        BOOL     SetCursorPos(int X, int Y);
        int      ShowCursor(BOOL bShow);
        SHORT    GetAsyncKeyState(int vKey);
        
        BOOL     ScreenToClient(HWND hWnd, LPPOINT lpPoint);
        BOOL     ClientToScreen(HWND hWnd, LPPOINT lpPoint);
        BOOL     DragDetect(HWND hwnd, POINT pt);
        
        int      ToAscii(UINT VirtKey, UINT uScanCode, const BYTE *lpKeyState, LPWORD lpChar, UINT uFlags);
        int      ToAsciiEx(UINT VirtKey, UINT ScanCode, const BYTE *KeyState, LPWORD Char, UINT Flags, HKL dwhkl);
        
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
        
        /*
 * Owner draw control types
 */
#define ODT_MENU        1
#define ODT_LISTBOX     2
#define ODT_COMBOBOX    3
#define ODT_BUTTON      4
#define ODT_STATIC      5
        
        /*
                 * Owner draw actions
                 */
#define ODA_DRAWENTIRE  0x0001
#define ODA_SELECT      0x0002
#define ODA_FOCUS       0x0004
        
        /*
         * Owner draw state
         */
#define ODS_SELECTED     0x0001
#define ODS_GRAYED       0x0002
#define ODS_DISABLED     0x0004
#define ODS_CHECKED      0x0008
#define ODS_FOCUS        0x0010
#define ODS_DEFAULT      0x0020
#define ODS_COMBOBOXEDIT 0x1000
#define ODS_HOTLIGHT     0x0040
#define ODS_INACTIVE     0x0080
#define ODS_NOACCEL      0x0100
#define ODS_NOFOCUSRECT  0x0200
        
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
        
        /*
         * SetWindowPos Flags
         */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */
        
#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER
        
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000
        
#define HWND_TOP        ((HWND)0)
#define HWND_BOTTOM     ((HWND)1)
#define HWND_TOPMOST    ((HWND)-1)
#define HWND_NOTOPMOST  ((HWND)-2)
        
        /*
        * Color Types
        */
#define CTLCOLOR_MSGBOX         0
#define CTLCOLOR_EDIT           1
#define CTLCOLOR_LISTBOX        2
#define CTLCOLOR_BTN            3
#define CTLCOLOR_DLG            4
#define CTLCOLOR_SCROLLBAR      5
#define CTLCOLOR_STATIC         6
#define CTLCOLOR_MAX            7
        
#define COLOR_SCROLLBAR         0
#define COLOR_BACKGROUND        1
#define COLOR_ACTIVECAPTION     2
#define COLOR_INACTIVECAPTION   3
#define COLOR_MENU              4
#define COLOR_WINDOW            5
#define COLOR_WINDOWFRAME       6
#define COLOR_MENUTEXT          7
#define COLOR_WINDOWTEXT        8
#define COLOR_CAPTIONTEXT       9
#define COLOR_ACTIVEBORDER      10
#define COLOR_INACTIVEBORDER    11
#define COLOR_APPWORKSPACE      12
#define COLOR_HIGHLIGHT         13
#define COLOR_HIGHLIGHTTEXT     14
#define COLOR_BTNFACE           15
#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT           18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT      20
        
#define COLOR_3DDKSHADOW        21
#define COLOR_3DLIGHT           22
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
        
#define COLOR_HOTLIGHT          26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#define COLOR_MENUHILIGHT       29
#define COLOR_MENUBAR           30
        
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
        
        
        WINUSERAPI	HWND  WINAPI  CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
        WINUSERAPI	HWND  WINAPI  CreateWindowExW(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
        WINUSERAPI	ATOM  WINAPI  RegisterClassA(CONST WNDCLASSA *lpWndClass);
        WINUSERAPI	ATOM  WINAPI  RegisterClassW(const WNDCLASSW *lpWndClass);
        WINUSERAPI    int   WINAPI  GetClassNameA(HWND hWnd, LPSTR lpClassName, int nMaxCount);
        WINUSERAPI    BOOL  WINAPI  GetClassInfoExA(HINSTANCE hInstance, LPCSTR lpszClass, LPWNDCLASSEXA lpwcx);
        WINUSERAPI    BOOL  WINAPI  GetClassInfoExW(HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx);
        WINUSERAPI	BOOL  WINAPI  ShowWindow(HWND hWnd, int nCmdShow);
        WINUSERAPI    HWND  WINAPI  SetFocus(HWND hWnd);
        
        WINUSERAPI    BOOL  WINAPI  CloseWindow(HWND hWnd);
        WINUSERAPI    BOOL  WINAPI  MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint);
        WINUSERAPI    BOOL  WINAPI  SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
        
        //
        // Windows GUI Control Types
        //
        
#define WC_EDIT          "Edit"
#define WC_BUTTON        "Button"
#define WC_COMBOBOX      "ComboBox"
#define WC_COMBOBOXEX    "ComboBoxEx32"
#define WC_HEADER        "SysHeader32"
#define WC_LISTBOX       "ListBox"
#define WC_LISTVIEW      "SysListView32"
#define WC_PAGESCROLLER  "SysPager"
#define WC_SCROLLBAR     "ScrollBar"
#define WC_STATIC        "Static"
#define WC_TABCONTROL    "SysTabControl32"
        
        
        /*
         * Tab Control Defines
         */
        
#define TCS_SCROLLOPPOSITE      0x0001   // assumes multiline tab
#define TCS_BOTTOM              0x0002
#define TCS_RIGHT               0x0002
#define TCS_MULTISELECT         0x0004  // allow multi-select in button mode
#define TCS_FLATBUTTONS         0x0008
#define TCS_FORCEICONLEFT       0x0010
#define TCS_FORCELABELLEFT      0x0020
#define TCS_HOTTRACK            0x0040
#define TCS_VERTICAL            0x0080
#define TCS_TABS                0x0000
#define TCS_BUTTONS             0x0100
#define TCS_SINGLELINE          0x0000
#define TCS_MULTILINE           0x0200
#define TCS_RIGHTJUSTIFY        0x0000
#define TCS_FIXEDWIDTH          0x0400
#define TCS_RAGGEDRIGHT         0x0800
#define TCS_FOCUSONBUTTONDOWN   0x1000
#define TCS_OWNERDRAWFIXED      0x2000
#define TCS_TOOLTIPS            0x4000
#define TCS_FOCUSNEVER          0x8000
        
        // EX styles for use with TCM_SETEXTENDEDSTYLE
#define TCS_EX_FLATSEPARATORS   0x00000001
#define TCS_EX_REGISTERDROP     0x00000002
        
#define TCM_FIRST               0x1300      // Tab control messages
#define TCM_GETIMAGELIST        (TCM_FIRST + 2)
#define Tab_GetImageList(hwnd) (HIMAGELIST)SNDMSG((hwnd), TCM_GETIMAGELIST, 0, 0L)
        
#define TCM_SETIMAGELIST        (TCM_FIRST + 3)
#define Tab_SetImageList(hwnd, himl) (HIMAGELIST)SNDMSG((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)(himl))
        
#define TCM_GETITEMCOUNT        (TCM_FIRST + 4)
#define Tab_GetItemCount(hwnd) (int)SNDMSG((hwnd), TCM_GETITEMCOUNT, 0, 0L)
        
#define TCM_INSERTITEMA         (TCM_FIRST + 7)
#define Tab_InsertItem(hwndCtl, idx, data) ((int)(DWORD)SNDMSG((hwndCtl), TCM_INSERTITEMA, (WPARAM)idx, (LPARAM)data))
        
#define TCM_DELETEITEM          (TCM_FIRST + 8)
#define TabCtrl_DeleteItem(hwnd, i) (BOOL)SNDMSG((hwnd), TCM_DELETEITEM, (WPARAM)(int)(i), 0L)
        
#define TCM_DELETEALLITEMS      (TCM_FIRST + 9)
#define TabCtrl_DeleteAllItems(hwnd) (BOOL)SNDMSG((hwnd), TCM_DELETEALLITEMS, 0, 0L)
        
#define TCM_GETITEMRECT         (TCM_FIRST + 10)
#define TabCtrl_GetItemRect(hwnd, i, prc) (BOOL)SNDMSG((hwnd), TCM_GETITEMRECT, (WPARAM)(int)(i), (LPARAM)(RECT *)(prc))
        
#define TCM_GETCURSEL           (TCM_FIRST + 11)
#define TabCtrl_GetCurSel(hwnd) (int)SNDMSG((hwnd), TCM_GETCURSEL, 0, 0)
        
        
#define TCM_SETCURSEL           (TCM_FIRST + 12)
#define TabCtrl_SetCurSel(hwnd, i) \
(int)SNDMSG((hwnd), TCM_SETCURSEL, (WPARAM)(i), 0)
        
        
#define TCIF_TEXT               0x0001
#define TCIF_IMAGE              0x0002
#define TCIF_RTLREADING         0x0004
#define TCIF_PARAM              0x0008
#define TCIF_STATE              0x0010
        
#define TCIS_BUTTONPRESSED      0x0001
#define TCIS_HIGHLIGHTED        0x0002
        
        //
        // Windows Menu Interface
        //
        
        
        
#define MNGOF_TOPGAP         0x00000001
#define MNGOF_BOTTOMGAP      0x00000002
#define MNGO_NOINTERFACE     0x00000000
#define MNGO_NOERROR         0x00000001
#define MIIM_STATE       0x00000001
#define MIIM_ID          0x00000002
#define MIIM_SUBMENU     0x00000004
#define MIIM_CHECKMARKS  0x00000008
#define MIIM_TYPE        0x00000010
#define MIIM_DATA        0x00000020
#define MIIM_STRING      0x00000040
#define MIIM_BITMAP      0x00000080
#define MIIM_FTYPE       0x00000100
        
#define HBMMENU_CALLBACK            ((HBITMAP) -1)
#define HBMMENU_SYSTEM              ((HBITMAP)  1)
#define HBMMENU_MBAR_RESTORE        ((HBITMAP)  2)
#define HBMMENU_MBAR_MINIMIZE       ((HBITMAP)  3)
#define HBMMENU_MBAR_CLOSE          ((HBITMAP)  5)
#define HBMMENU_MBAR_CLOSE_D        ((HBITMAP)  6)
#define HBMMENU_MBAR_MINIMIZE_D     ((HBITMAP)  7)
#define HBMMENU_POPUP_CLOSE         ((HBITMAP)  8)
#define HBMMENU_POPUP_RESTORE       ((HBITMAP)  9)
#define HBMMENU_POPUP_MAXIMIZE      ((HBITMAP) 10)
#define HBMMENU_POPUP_MINIMIZE      ((HBITMAP) 11)
        
        /*
         * Menu flags for Add/Check/EnableMenuItem()
         */
#define MF_INSERT           0x00000000L
#define MF_CHANGE           0x00000080L
#define MF_APPEND           0x00000100L
#define MF_DELETE           0x00000200L
#define MF_REMOVE           0x00001000L
        
#define MF_BYCOMMAND        0x00000000L
#define MF_BYPOSITION       0x00000400L
        
#define MF_SEPARATOR        0x00000800L
        
#define MF_ENABLED          0x00000000L
#define MF_GRAYED           0x00000001L
#define MF_DISABLED         0x00000002L
        
#define MF_UNCHECKED        0x00000000L
#define MF_CHECKED          0x00000008L
#define MF_USECHECKBITMAPS  0x00000200L
        
#define MF_STRING           0x00000000L
#define MF_BITMAP           0x00000004L
#define MF_OWNERDRAW        0x00000100L
        
#define MF_POPUP            0x00000010L
#define MF_MENUBARBREAK     0x00000020L
#define MF_MENUBREAK        0x00000040L
        
#define MF_UNHILITE         0x00000000L
#define MF_HILITE           0x00000080L
        
#define MF_DEFAULT          0x00001000L
#define MF_SYSMENU          0x00002000L
#define MF_HELP             0x00004000L
#define MF_RIGHTJUSTIFY     0x00004000L
        
#define MF_MOUSESELECT      0x00008000L
#define MF_END              0x00000080L  /* Obsolete -- only used by old RES files */
        
#define MFT_STRING          MF_STRING
#define MFT_BITMAP          MF_BITMAP
#define MFT_MENUBARBREAK    MF_MENUBARBREAK
#define MFT_MENUBREAK       MF_MENUBREAK
#define MFT_OWNERDRAW       MF_OWNERDRAW
#define MFT_RADIOCHECK      0x00000200L
#define MFT_SEPARATOR       MF_SEPARATOR
#define MFT_RIGHTORDER      0x00002000L
#define MFT_RIGHTJUSTIFY    MF_RIGHTJUSTIFY
#define MFS_GRAYED          0x00000003L
#define MFS_DISABLED        MFS_GRAYED
#define MFS_CHECKED         MF_CHECKED
#define MFS_HILITE          MF_HILITE
#define MFS_ENABLED         MF_ENABLED
#define MFS_UNCHECKED       MF_UNCHECKED
#define MFS_UNHILITE        MF_UNHILITE
#define MFS_DEFAULT         MF_DEFAULT
        
        /*
        * Edit Control Styles
        */
#define ES_LEFT             0x0000L
#define ES_CENTER           0x0001L
#define ES_RIGHT            0x0002L
#define ES_MULTILINE        0x0004L
#define ES_UPPERCASE        0x0008L
#define ES_LOWERCASE        0x0010L
#define ES_PASSWORD         0x0020L
#define ES_AUTOVSCROLL      0x0040L
#define ES_AUTOHSCROLL      0x0080L
#define ES_NOHIDESEL        0x0100L
#define ES_OEMCONVERT       0x0400L
#define ES_READONLY         0x0800L
#define ES_WANTRETURN       0x1000L
#define ES_NUMBER           0x2000L
        
        
        /*
        * Edit Control Notification Codes
        */
#define EN_SETFOCUS         0x0100
#define EN_KILLFOCUS        0x0200
#define EN_CHANGE           0x0300
#define EN_UPDATE           0x0400
#define EN_ERRSPACE         0x0500
#define EN_MAXTEXT          0x0501
#define EN_HSCROLL          0x0601
#define EN_VSCROLL          0x0602
#define EN_ALIGN_LTR_EC     0x0700
#define EN_ALIGN_RTL_EC     0x0701
#define EN_BEFORE_PASTE     0x0800
#define EN_AFTER_PASTE      0x0801
        
        /*
 * Edit Control Messages
 */
#define EM_GETSEL               0x00B0
#define EM_SETSEL               0x00B1
#define EM_GETRECT              0x00B2
#define EM_SETRECT              0x00B3
#define EM_SETRECTNP            0x00B4
#define EM_SCROLL               0x00B5
#define EM_LINESCROLL           0x00B6
#define EM_SCROLLCARET          0x00B7
#define EM_GETMODIFY            0x00B8
#define EM_SETMODIFY            0x00B9
#define EM_GETLINECOUNT         0x00BA
#define EM_LINEINDEX            0x00BB
#define EM_SETHANDLE            0x00BC
#define EM_GETHANDLE            0x00BD
#define EM_GETTHUMB             0x00BE
#define EM_LINELENGTH           0x00C1
#define EM_REPLACESEL           0x00C2
#define EM_GETLINE              0x00C4
#define EM_LIMITTEXT            0x00C5
#define EM_CANUNDO              0x00C6
#define EM_UNDO                 0x00C7
#define EM_FMTLINES             0x00C8
#define EM_LINEFROMCHAR         0x00C9
#define EM_SETTABSTOPS          0x00CB
#define EM_SETPASSWORDCHAR      0x00CC
#define EM_EMPTYUNDOBUFFER      0x00CD
#define EM_GETFIRSTVISIBLELINE  0x00CE
#define EM_SETREADONLY          0x00CF
#define EM_SETWORDBREAKPROC     0x00D0
#define EM_GETWORDBREAKPROC     0x00D1
#define EM_GETPASSWORDCHAR      0x00D2
#define EM_SETMARGINS           0x00D3
#define EM_GETMARGINS           0x00D4
#define EM_SETLIMITTEXT         EM_LIMITTEXT   /* ;win40 Name change */
#define EM_GETLIMITTEXT         0x00D5
#define EM_POSFROMCHAR          0x00D6
#define EM_CHARFROMPOS          0x00D7
#define EM_SETIMESTATUS         0x00D8
#define EM_GETIMESTATUS         0x00D9
#define EM_ENABLEFEATURE        0x00DA
        
        /*
         * Button Control Styles
         */
#define BS_PUSHBUTTON       0x00000000L
#define BS_DEFPUSHBUTTON    0x00000001L
#define BS_CHECKBOX         0x00000002L
#define BS_AUTOCHECKBOX     0x00000003L
#define BS_RADIOBUTTON      0x00000004L
#define BS_3STATE           0x00000005L
#define BS_AUTO3STATE       0x00000006L
#define BS_GROUPBOX         0x00000007L
#define BS_USERBUTTON       0x00000008L
#define BS_AUTORADIOBUTTON  0x00000009L
#define BS_PUSHBOX          0x0000000AL
#define BS_OWNERDRAW        0x0000000BL
#define BS_TYPEMASK         0x0000000FL
#define BS_LEFTTEXT         0x00000020L
#define BS_TEXT             0x00000000L
#define BS_ICON             0x00000040L
#define BS_BITMAP           0x00000080L
#define BS_LEFT             0x00000100L
#define BS_RIGHT            0x00000200L
#define BS_CENTER           0x00000300L
#define BS_TOP              0x00000400L
#define BS_BOTTOM           0x00000800L
#define BS_VCENTER          0x00000C00L
#define BS_PUSHLIKE         0x00001000L
#define BS_MULTILINE        0x00002000L
#define BS_NOTIFY           0x00004000L
#define BS_FLAT             0x00008000L
#define BS_RIGHTBUTTON      BS_LEFTTEXT
        
        /*
        * Listbox Styles
        */
#define LBS_NOTIFY            0x0001L
#define LBS_SORT              0x0002L
#define LBS_NOREDRAW          0x0004L
#define LBS_MULTIPLESEL       0x0008L
#define LBS_OWNERDRAWFIXED    0x0010L
#define LBS_OWNERDRAWVARIABLE 0x0020L
#define LBS_HASSTRINGS        0x0040L
#define LBS_USETABSTOPS       0x0080L
#define LBS_NOINTEGRALHEIGHT  0x0100L
#define LBS_MULTICOLUMN       0x0200L
#define LBS_WANTKEYBOARDINPUT 0x0400L
#define LBS_EXTENDEDSEL       0x0800L
#define LBS_DISABLENOSCROLL   0x1000L
#define LBS_NODATA            0x2000L
#define LBS_NOSEL             0x4000L
#define LBS_COMBOBOX          0x8000L
#define LBS_STANDARD          (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)
        
        /*
         * User Button Notification Codes
         */
#define BN_CLICKED          0
#define BN_PAINT            1
#define BN_HILITE           2
#define BN_UNHILITE         3
#define BN_DISABLE          4
#define BN_DOUBLECLICKED    5
#define BN_PUSHED           BN_HILITE
#define BN_UNPUSHED         BN_UNHILITE
#define BN_DBLCLK           BN_DOUBLECLICKED
#define BN_SETFOCUS         6
#define BN_KILLFOCUS        7
        
        /*
         * Button Control Messages
         */
#define BM_GETCHECK        0x00F0
#define BM_SETCHECK        0x00F1
#define BM_GETSTATE        0x00F2
#define BM_SETSTATE        0x00F3
#define BM_SETSTYLE        0x00F4
#define BM_CLICK           0x00F5
#define BM_GETIMAGE        0x00F6
#define BM_SETIMAGE        0x00F7
#define BM_SETDONTCLICK    0x00F8
        
#define BST_UNCHECKED      0x0000
#define BST_CHECKED        0x0001
#define BST_INDETERMINATE  0x0002
#define BST_PUSHED         0x0004
#define BST_FOCUS          0x0008
        
        /*
         * Static Control Constants
         */
#define SS_LEFT             0x00000000L
#define SS_CENTER           0x00000001L
#define SS_RIGHT            0x00000002L
#define SS_ICON             0x00000003L
#define SS_BLACKRECT        0x00000004L
#define SS_GRAYRECT         0x00000005L
#define SS_WHITERECT        0x00000006L
#define SS_BLACKFRAME       0x00000007L
#define SS_GRAYFRAME        0x00000008L
#define SS_WHITEFRAME       0x00000009L
#define SS_USERITEM         0x0000000AL
#define SS_SIMPLE           0x0000000BL
#define SS_LEFTNOWORDWRAP   0x0000000CL
#define SS_OWNERDRAW        0x0000000DL
#define SS_BITMAP           0x0000000EL
#define SS_ENHMETAFILE      0x0000000FL
#define SS_ETCHEDHORZ       0x00000010L
#define SS_ETCHEDVERT       0x00000011L
#define SS_ETCHEDFRAME      0x00000012L
#define SS_TYPEMASK         0x0000001FL
#define SS_REALSIZECONTROL  0x00000040L
#define SS_NOPREFIX         0x00000080L /* Don't do "&" character translation */
#define SS_NOTIFY           0x00000100L
#define SS_CENTERIMAGE      0x00000200L
#define SS_RIGHTJUST        0x00000400L
#define SS_REALSIZEIMAGE    0x00000800L
#define SS_SUNKEN           0x00001000L
#define SS_EDITCONTROL      0x00002000L
#define SS_ENDELLIPSIS      0x00004000L
#define SS_PATHELLIPSIS     0x00008000L
#define SS_WORDELLIPSIS     0x0000C000L
#define SS_ELLIPSISMASK     0x0000C000L
        
        /*
         * Combo Box return Values
         */
#define CB_OKAY             0
#define CB_ERR              (-1)
#define CB_ERRSPACE         (-2)
        
        /*
         * Combo Box Notification Codes
         */
#define CBN_ERRSPACE        (-1)
#define CBN_SELCHANGE       1
#define CBN_DBLCLK          2
#define CBN_SETFOCUS        3
#define CBN_KILLFOCUS       4
#define CBN_EDITCHANGE      5
#define CBN_EDITUPDATE      6
#define CBN_DROPDOWN        7
#define CBN_CLOSEUP         8
#define CBN_SELENDOK        9
#define CBN_SELENDCANCEL    10
        
        /*
         * Combo Box styles
         */
#define CBS_SIMPLE            0x0001L
#define CBS_DROPDOWN          0x0002L
#define CBS_DROPDOWNLIST      0x0003L
#define CBS_OWNERDRAWFIXED    0x0010L
#define CBS_OWNERDRAWVARIABLE 0x0020L
#define CBS_AUTOHSCROLL       0x0040L
#define CBS_OEMCONVERT        0x0080L
#define CBS_SORT              0x0100L
#define CBS_HASSTRINGS        0x0200L
#define CBS_NOINTEGRALHEIGHT  0x0400L
#define CBS_DISABLENOSCROLL   0x0800L
#define CBS_UPPERCASE         0x2000L
#define CBS_LOWERCASE         0x4000L
        
        /*
         * Combo Box messages
         */
#define CB_GETEDITSEL               0x0140
#define CB_LIMITTEXT                0x0141
#define CB_SETEDITSEL               0x0142
#define CB_ADDSTRING                0x0143
#define CB_DELETESTRING             0x0144
#define CB_DIR                      0x0145
#define CB_GETCOUNT                 0x0146
#define CB_GETCURSEL                0x0147
#define CB_GETLBTEXT                0x0148
#define CB_GETLBTEXTLEN             0x0149
#define CB_INSERTSTRING             0x014A
#define CB_RESETCONTENT             0x014B
#define CB_FINDSTRING               0x014C
#define CB_SELECTSTRING             0x014D
#define CB_SETCURSEL                0x014E
#define CB_SHOWDROPDOWN             0x014F
#define CB_GETITEMDATA              0x0150
#define CB_SETITEMDATA              0x0151
#define CB_GETDROPPEDCONTROLRECT    0x0152
#define CB_SETITEMHEIGHT            0x0153
#define CB_GETITEMHEIGHT            0x0154
#define CB_SETEXTENDEDUI            0x0155
#define CB_GETEXTENDEDUI            0x0156
#define CB_GETDROPPEDSTATE          0x0157
#define CB_FINDSTRINGEXACT          0x0158
#define CB_SETLOCALE                0x0159
#define CB_GETLOCALE                0x015A
#define CB_GETTOPINDEX              0x015b
#define CB_SETTOPINDEX              0x015c
#define CB_GETHORIZONTALEXTENT      0x015d
#define CB_SETHORIZONTALEXTENT      0x015e
#define CB_GETDROPPEDWIDTH          0x015f
#define CB_SETDROPPEDWIDTH          0x0160
#define CB_INITSTORAGE              0x0161
#define CB_MULTIPLEADDSTRING        0x0163
#define CB_GETCOMBOBOXINFO          0x0164
        
#define CB_MSGMAX                   0x0165
        
        /*
         * Listbox Notification Codes
         */
#define LBN_ERRSPACE        (-2)
#define LBN_SELCHANGE       1
#define LBN_DBLCLK          2
#define LBN_SELCANCEL       3
#define LBN_SETFOCUS        4
#define LBN_KILLFOCUS       5
        
        
        // tab control
#define TCN_FIRST               (0U-550U)
#define TCN_LAST                (0U-580U)
#define TCN_SELCHANGE           (TCN_FIRST - 1)
#define TCN_SELCHANGING         (TCN_FIRST - 2)
#define TCN_GETOBJECT           (TCN_FIRST - 3)
#define TCN_FOCUSCHANGE         (TCN_FIRST - 4)
        
        /*
         * Listbox messages
         */
#define LB_ADDSTRING            0x0180
#define LB_INSERTSTRING         0x0181
#define LB_DELETESTRING         0x0182
#define LB_SELITEMRANGEEX       0x0183
#define LB_RESETCONTENT         0x0184
#define LB_SETSEL               0x0185
#define LB_SETCURSEL            0x0186
#define LB_GETSEL               0x0187
#define LB_GETCURSEL            0x0188
#define LB_GETTEXT              0x0189
#define LB_GETTEXTLEN           0x018A
#define LB_GETCOUNT             0x018B
#define LB_SELECTSTRING         0x018C
#define LB_DIR                  0x018D
#define LB_GETTOPINDEX          0x018E
#define LB_FINDSTRING           0x018F
#define LB_GETSELCOUNT          0x0190
#define LB_GETSELITEMS          0x0191
#define LB_SETTABSTOPS          0x0192
#define LB_GETHORIZONTALEXTENT  0x0193
#define LB_SETHORIZONTALEXTENT  0x0194
#define LB_SETCOLUMNWIDTH       0x0195
#define LB_ADDFILE              0x0196
#define LB_SETTOPINDEX          0x0197
#define LB_GETITEMRECT          0x0198
#define LB_GETITEMDATA          0x0199
#define LB_SETITEMDATA          0x019A
#define LB_SELITEMRANGE         0x019B
#define LB_SETANCHORINDEX       0x019C
#define LB_GETANCHORINDEX       0x019D
#define LB_SETCARETINDEX        0x019E
#define LB_GETCARETINDEX        0x019F
#define LB_SETITEMHEIGHT        0x01A0
#define LB_GETITEMHEIGHT        0x01A1
#define LB_FINDSTRINGEXACT      0x01A2
#define LB_SETLOCALE            0x01A5
#define LB_GETLOCALE            0x01A6
#define LB_SETCOUNT             0x01A7
#define LB_INITSTORAGE          0x01A8
#define LB_ITEMFROMPOINT        0x01A9
#define LB_MULTIPLEADDSTRING    0x01B1
#define LB_GETLISTBOXINFO       0x01B2
        
#define LB_MSGMAX               0x01B3
        
        
        /*
         * GetDCEx() flags
         */
#define DCX_WINDOW           0x00000001L
#define DCX_CACHE            0x00000002L
#define DCX_NORESETATTRS     0x00000004L
#define DCX_CLIPCHILDREN     0x00000008L
#define DCX_CLIPSIBLINGS     0x00000010L
#define DCX_PARENTCLIP       0x00000020L
#define DCX_EXCLUDERGN       0x00000040L
#define DCX_INTERSECTRGN     0x00000080L
#define DCX_EXCLUDEUPDATE    0x00000100L
#define DCX_INTERSECTUPDATE  0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L
        
#define DCX_VALIDATE         0x00200000L
        
        /*
         * Listbox Return Values
         */
#define LB_OKAY             0
#define LB_ERR              (-1)
#define LB_ERRSPACE         (-2)
        
        
        typedef struct _FIXED {
            short   value;
            WORD    fract;
        } FIXED;
        
        typedef struct _MAT2 {
            FIXED  eM11;
            FIXED  eM12;
            FIXED  eM21;
            FIXED  eM22;
        } MAT2, *LPMAT2;
        
        
        
        typedef struct _GLYPHMETRICS {
            UINT    gmBlackBoxX;
            UINT    gmBlackBoxY;
            POINT   gmptGlyphOrigin;
            short   gmCellIncX;
            short   gmCellIncY;
        } GLYPHMETRICS, *LPGLYPHMETRICS;
        
#define GGI_MARK_NONEXISTING_GLYPHS  0X0001
        
        /*
         * Font Families
*/
#define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
#define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. Times Roman, Century Schoolbook, etc. */
#define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. Helvetica, Swiss, etc. */
#define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. Pica, Elite, Courier, etc. */
#define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE       (5<<4)  /* Old English, etc. */
        
        /* 
* Font Weights 
*/
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900
        
#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY
        
#define OUT_DEFAULT_PRECIS          0
#define OUT_STRING_PRECIS           1
#define OUT_CHARACTER_PRECIS        2
#define OUT_STROKE_PRECIS           3
#define OUT_TT_PRECIS               4
#define OUT_DEVICE_PRECIS           5
#define OUT_RASTER_PRECIS           6
#define OUT_TT_ONLY_PRECIS          7
#define OUT_OUTLINE_PRECIS          8
#define OUT_SCREEN_OUTLINE_PRECIS   9
#define OUT_PS_ONLY_PRECIS          10
        
#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2
#define CLIP_MASK               0xf
#define CLIP_LH_ANGLES          (1<<4)
#define CLIP_TT_ALWAYS          (2<<4)
#define CLIP_DFA_DISABLE        (4<<4)
#define CLIP_EMBEDDED           (8<<4)
        
#define DEFAULT_QUALITY           0
#define DRAFT_QUALITY             1
#define PROOF_QUALITY             2
#define NONANTIALIASED_QUALITY    3
#define ANTIALIASED_QUALITY       4
#define CLEARTYPE_QUALITY         5
#define CLEARTYPE_NATURAL_QUALITY 6
        
#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2
#define MONO_FONT               8
        
#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255
#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204
        
#define MAC_CHARSET             77
#define BALTIC_CHARSET          186
        
        /*
* GetGlyphOutline constants
*/
        
#define GGO_METRICS        0
#define GGO_BITMAP         1
#define GGO_NATIVE         2
#define GGO_BEZIER         3
#define  GGO_GRAY2_BITMAP   4
#define  GGO_GRAY4_BITMAP   5
#define  GGO_GRAY8_BITMAP   6
#define  GGO_GLYPH_INDEX    0x0080
#define  GGO_UNHINTED       0x0100
        
#define TT_POLYGON_TYPE   24
#define TT_PRIM_LINE       1
#define TT_PRIM_QSPLINE    2
#define TT_PRIM_CSPLINE    3
        
        
        /*
         DrawTextEX Formatter
         */
#define DT_TOP                      0x00000000
#define DT_LEFT                     0x00000000
#define DT_CENTER                   0x00000001
#define DT_RIGHT                    0x00000002
#define DT_VCENTER                  0x00000004
#define DT_BOTTOM                   0x00000008
#define DT_WORDBREAK                0x00000010
#define DT_SINGLELINE               0x00000020
#define DT_EXPANDTABS               0x00000040
#define DT_TABSTOP                  0x00000080
#define DT_NOCLIP                   0x00000100
#define DT_EXTERNALLEADING          0x00000200
#define DT_CALCRECT                 0x00000400
#define DT_NOPREFIX                 0x00000800
#define DT_INTERNAL                 0x00001000
#define DT_EDITCONTROL              0x00002000
#define DT_PATH_ELLIPSIS            0x00004000
#define DT_END_ELLIPSIS             0x00008000
#define DT_MODIFYSTRING             0x00010000
#define DT_RTLREADING               0x00020000
#define DT_WORD_ELLIPSIS            0x00040000
#define DT_NOFULLWIDTHCHARBREAK     0x00080000
#define DT_HIDEPREFIX               0x00100000
#define DT_PREFIXONLY               0x00200000
        
        
#define MNS_NOCHECK         0x80000000
#define MNS_MODELESS        0x40000000
#define MNS_DRAGDROP        0x20000000
#define MNS_AUTODISMISS     0x10000000
#define MNS_NOTIFYBYPOS     0x08000000
#define MNS_CHECKORBMP      0x04000000
        
#define MIM_MAXHEIGHT               0x00000001
#define MIM_BACKGROUND              0x00000002
#define MIM_HELPID                  0x00000004
#define MIM_MENUDATA                0x00000008
#define MIM_STYLE                   0x00000010
#define MIM_APPLYTOSUBMENUS         0x80000000
        
        /* flags for DrawCaption */
#define DC_ACTIVE           0x0001
#define DC_SMALLCAP         0x0002
#define DC_ICON             0x0004
#define DC_TEXT             0x0008
#define DC_INBUTTON         0x0010
#define DC_GRADIENT         0x0020
#define DC_BUTTONS          0x1000
        
        
        /* flags for DrawFrameControl */
        
#define DFC_CAPTION             1
#define DFC_MENU                2
#define DFC_SCROLL              3
#define DFC_BUTTON              4
#define DFC_POPUPMENU           5
        
#define DFCS_CAPTIONCLOSE       0x0000
#define DFCS_CAPTIONMIN         0x0001
#define DFCS_CAPTIONMAX         0x0002
#define DFCS_CAPTIONRESTORE     0x0003
#define DFCS_CAPTIONHELP        0x0004
        
#define DFCS_MENUARROW          0x0000
#define DFCS_MENUCHECK          0x0001
#define DFCS_MENUBULLET         0x0002
#define DFCS_MENUARROWRIGHT     0x0004
#define DFCS_SCROLLUP           0x0000
#define DFCS_SCROLLDOWN         0x0001
#define DFCS_SCROLLLEFT         0x0002
#define DFCS_SCROLLRIGHT        0x0003
#define DFCS_SCROLLCOMBOBOX     0x0005
#define DFCS_SCROLLSIZEGRIP     0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010
        
#define DFCS_BUTTONCHECK        0x0000
#define DFCS_BUTTONRADIOIMAGE   0x0001
#define DFCS_BUTTONRADIOMASK    0x0002
#define DFCS_BUTTONRADIO        0x0004
#define DFCS_BUTTON3STATE       0x0008
#define DFCS_BUTTONPUSH         0x0010
        
#define DFCS_INACTIVE           0x0100
#define DFCS_PUSHED             0x0200
#define DFCS_CHECKED            0x0400
        
#define DFCS_TRANSPARENT        0x0800
#define DFCS_HOT                0x1000
        
#define DFCS_ADJUSTRECT         0x2000
#define DFCS_FLAT               0x4000
#define DFCS_MONO               0x8000
        
        /*
         * WM_MENUDRAG return values.
         */
#define MND_CONTINUE       0
#define MND_ENDMENU        1
        
        HMENU    CreateMenu(VOID);
        BOOL     DestroyMenu(HMENU hMenu);
        UINT     GetMenuState(HMENU hMenu, UINT uId, UINT uFlags);
        BOOL     GetMenuItemRect(HWND hWnd, HMENU hMenu, UINT uId, LPRECT);
        BOOL     DrawMenuBar(HWND hWnd);
        HMENU    GetMenu(HWND hWnd);
        BOOL     SetMenu(HWND hWnd, HMENU hMenu);
        BOOL     AppendMenuA(HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem);
        BOOL     AppendMenuW(HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem);
        BOOL     InsertMenuItemA(HMENU hmenu, UINT item, BOOL fByPosition, LPCMENUITEMINFOA lpmi);
        BOOL     InsertMenuItemW(HMENU hmenu, UINT item, BOOL fByPosition, LPCMENUITEMINFOW lpmi);
        BOOL     SetWindowTextA(HWND hWnd, LPCSTR lpString);
        BOOL     SetWindowTextW(HWND hWnd, LPCWSTR lpString);
        int      GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount);
        int      GetWindowTextW(HWND hWnd, LPWSTR lpString, int nMaxCount);
        int      GetWindowTextLengthA(HWND hWnd);
        int      GetWindowTextLengthW(HWND hWnd);
        BOOL     GetMenuInfo(HMENU, LPMENUINFO);
        BOOL     SetMenuInfo(HMENU, LPCMENUINFO);
        BOOL     EndMenu(VOID);
        
        BOOL     IsWindowVisible(HWND hWnd);
        
        HFONT    CreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic,
                             DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision,
                             DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName);
        
        DWORD    GetFontData (HDC hdc, DWORD dwTable, DWORD dwOffset, PVOID pvBuffer, DWORD cjBuffer);
        
        DWORD    GetGlyphOutlineA(HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cjBuffer,
                                  LPVOID pvBuffer, CONST MAT2 *lpmat2);
        DWORD GetGlyphOutlineW(HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cjBuffer,
                               LPVOID pvBuffer, const MAT2 *lpmat2);
        
        DWORD    GetGlyphIndicesA(HDC hdc, LPCSTR lpstr, int c, LPWORD pgi, DWORD fl);
        DWORD    GetGlyphIndicesW(HDC hdc, LPCWSTR lpstr, int c, LPWORD pgi, DWORD fl);
        
        BOOL     DrawCaption(HWND hwnd, HDC hdc, CONST RECT * lprect, UINT flags);
        BOOL     DrawFrameControl(HDC hdc, LPRECT lprect, UINT frameType, UINT frameState);
        
        HDC      BeginPaint(HWND hwnd, PAINTSTRUCT *ps);
        BOOL     GdiFlush();
        VOID     EndPaint(HWND hwnd, PAINTSTRUCT *ps);
        int      FillRect(HDC hDC, const RECT *lprc, HBRUSH hbr);
        int      DrawTextExA(HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp);
        BOOL     TextOutA(HDC hdc, int x, int y, LPCSTR lpString, int c);
        COLORREF SetTextColor(HDC hdc, COLORREF color);
        COLORREF SetBkColor(HDC hdc, COLORREF color);
        HBRUSH   CreateSolidBrush(COLORREF color);
        BOOL     DeleteObject(HGDIOBJ ho);
        
        BOOL     GetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl);
        
        
        // -------------------//
        //       OPENGL       //
        // -------------------//
        
        typedef unsigned int   GLenum;
        typedef unsigned char  GLboolean;
        typedef unsigned int   GLbitfield;
        typedef signed char    GLbyte;
        typedef short          GLshort;
        typedef int            GLint;
        typedef int            GLsizei;
        typedef unsigned char  GLubyte;
        typedef unsigned short GLushort;
        typedef unsigned int   GLuint;
        typedef float          GLfloat;
        typedef float          GLclampf;
        typedef double         GLdouble;
        typedef double         GLclampd;
        typedef void           GLvoid;
        
        WINGDIAPI BOOL  WINAPI wglCopyContext(HGLRC, HGLRC, UINT);
        WINGDIAPI HGLRC WINAPI wglCreateContext(HDC);
        WINGDIAPI HGLRC WINAPI wglCreateLayerContext(HDC, int);
        WINGDIAPI BOOL  WINAPI wglDeleteContext(HGLRC);
        WINGDIAPI HGLRC WINAPI wglGetCurrentContext(VOID);
        WINGDIAPI HDC   WINAPI wglGetCurrentDC(VOID);
        WINGDIAPI PROC  WINAPI wglGetProcAddress(LPCSTR);
        WINGDIAPI BOOL  WINAPI wglMakeCurrent(HDC, HGLRC);
        WINGDIAPI BOOL  WINAPI wglShareLists(HGLRC, HGLRC);
        WINGDIAPI BOOL  WINAPI wglUseFontBitmapsA(HDC, DWORD, DWORD, DWORD);
        
        
        
        // Now... why the fuck would the ComboBox interface be done with messages
        // If everything else uses functions? Why the actual fuck...
#define SNDMSG SendMessageA
#define ComboBox_AddString(hwndCtl, lpsz) ((int)(DWORD)SNDMSG((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(LPCTSTR)(lpsz)))
#define ComboBox_InsertString(hwndCtl, index, lpsz) ((int)(DWORD)SNDMSG((hwndCtl), CB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpsz)))
#define ComboBox_Enable(hwndCtl, fEnable)       EnableWindow((hwndCtl), (fEnable))
        
#define ComboBox_GetText(hwndCtl, lpch, cchMax) GetWindowTextA((hwndCtl), (lpch), (cchMax))
#define ComboBox_GetTextLength(hwndCtl)         GetWindowTextLengthA(hwndCtl)
#define ComboBox_SetText(hwndCtl, lpsz)         SetWindowTextA((hwndCtl), (lpsz))
        
#define ComboBox_LimitText(hwndCtl, cchLimit)   ((int)(DWORD)SNDMSG((hwndCtl), CB_LIMITTEXT, (WPARAM)(int)(cchLimit), 0L))
        
#define ComboBox_GetEditSel(hwndCtl)            ((DWORD)SNDMSG((hwndCtl), CB_GETEDITSEL, 0L, 0L))
#define ComboBox_SetEditSel(hwndCtl, ichStart, ichEnd) ((int)(DWORD)SNDMSG((hwndCtl), CB_SETEDITSEL, 0L, MAKELPARAM((ichStart), (ichEnd))))
        
#define ComboBox_GetCount(hwndCtl)              ((int)(DWORD)SNDMSG((hwndCtl), CB_GETCOUNT, 0L, 0L))
#define ComboBox_ResetContent(hwndCtl)          ((int)(DWORD)SNDMSG((hwndCtl), CB_RESETCONTENT, 0L, 0L))
        
#define ComboBox_AddItemData(hwndCtl, data)     ((int)(DWORD)SNDMSG((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(data)))
#define ComboBox_InsertItemData(hwndCtl, index, data) ((int)(DWORD)SNDMSG((hwndCtl), CB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(data)))
        
#define ComboBox_DeleteString(hwndCtl, index)   ((int)(DWORD)SNDMSG((hwndCtl), CB_DELETESTRING, (WPARAM)(int)(index), 0L))
        
#define ComboBox_GetLBTextLen(hwndCtl, index)           ((int)(DWORD)SNDMSG((hwndCtl), CB_GETLBTEXTLEN, (WPARAM)(int)(index), 0L))
#define ComboBox_GetLBText(hwndCtl, index, lpszBuffer)  ((int)(DWORD)SNDMSG((hwndCtl), CB_GETLBTEXT, (WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpszBuffer)))
        
#define ComboBox_GetItemData(hwndCtl, index)        ((LRESULT)(ULONG_PTR)SNDMSG((hwndCtl), CB_GETITEMDATA, (WPARAM)(int)(index), 0L))
#define ComboBox_SetItemData(hwndCtl, index, data)  ((int)(DWORD)SNDMSG((hwndCtl), CB_SETITEMDATA, (WPARAM)(int)(index), (LPARAM)(data)))
        
#define ComboBox_FindString(hwndCtl, indexStart, lpszFind)  ((int)(DWORD)SNDMSG((hwndCtl), CB_FINDSTRING, (WPARAM)(int)(indexStart), (LPARAM)(LPCTSTR)(lpszFind)))
#define ComboBox_FindItemData(hwndCtl, indexStart, data)    ((int)(DWORD)SNDMSG((hwndCtl), CB_FINDSTRING, (WPARAM)(int)(indexStart), (LPARAM)(data)))
        
#define ComboBox_GetCurSel(hwndCtl)                 ((int)(DWORD)SNDMSG((hwndCtl), CB_GETCURSEL, 0L, 0L))
#define ComboBox_SetCurSel(hwndCtl, index)          ((int)(DWORD)SNDMSG((hwndCtl), CB_SETCURSEL, (WPARAM)(int)(index), 0L))
        
#define ComboBox_SelectString(hwndCtl, indexStart, lpszSelect)  ((int)(DWORD)SNDMSG((hwndCtl), CB_SELECTSTRING, (WPARAM)(int)(indexStart), (LPARAM)(LPCTSTR)(lpszSelect)))
#define ComboBox_SelectItemData(hwndCtl, indexStart, data)      ((int)(DWORD)SNDMSG((hwndCtl), CB_SELECTSTRING, (WPARAM)(int)(indexStart), (LPARAM)(data)))
        
#define ComboBox_Dir(hwndCtl, attrs, lpszFileSpec)  ((int)(DWORD)SNDMSG((hwndCtl), CB_DIR, (WPARAM)(UINT)(attrs), (LPARAM)(LPCTSTR)(lpszFileSpec)))
        
#define ComboBox_ShowDropdown(hwndCtl, fShow)       ((BOOL)(DWORD)SNDMSG((hwndCtl), CB_SHOWDROPDOWN, (WPARAM)(BOOL)(fShow), 0L))
        
        
        
        /****** ListBox control message APIs *****************************************/
#define ListBox_Enable(hwndCtl, fEnable)            EnableWindow((hwndCtl), (fEnable))
        
#define ListBox_GetCount(hwndCtl)                   ((int)(DWORD)SNDMSG((hwndCtl), LB_GETCOUNT, 0L, 0L))
#define ListBox_ResetContent(hwndCtl)               ((BOOL)(DWORD)SNDMSG((hwndCtl), LB_RESETCONTENT, 0L, 0L))
        
#define ListBox_AddString(hwndCtl, lpsz)            ((int)(DWORD)SNDMSG((hwndCtl), LB_ADDSTRING, 0L, (LPARAM)(LPCTSTR)(lpsz)))
#define ListBox_InsertString(hwndCtl, index, lpsz)  ((int)(DWORD)SNDMSG((hwndCtl), LB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpsz)))
        
#define ListBox_AddItemData(hwndCtl, data)          ((int)(DWORD)SNDMSG((hwndCtl), LB_ADDSTRING, 0L, (LPARAM)(data)))
#define ListBox_InsertItemData(hwndCtl, index, data) ((int)(DWORD)SNDMSG((hwndCtl), LB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(data)))
        
#define ListBox_DeleteString(hwndCtl, index)        ((int)(DWORD)SNDMSG((hwndCtl), LB_DELETESTRING, (WPARAM)(int)(index), 0L))
        
#define ListBox_GetTextLen(hwndCtl, index)          ((int)(DWORD)SNDMSG((hwndCtl), LB_GETTEXTLEN, (WPARAM)(int)(index), 0L))
#define ListBox_GetText(hwndCtl, index, lpszBuffer)  ((int)(DWORD)SNDMSG((hwndCtl), LB_GETTEXT, (WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpszBuffer)))
        
#define ListBox_GetItemData(hwndCtl, index)         ((LRESULT)(ULONG_PTR)SNDMSG((hwndCtl), LB_GETITEMDATA, (WPARAM)(int)(index), 0L))
#define ListBox_SetItemData(hwndCtl, index, data)   ((int)(DWORD)SNDMSG((hwndCtl), LB_SETITEMDATA, (WPARAM)(int)(index), (LPARAM)(data)))
        
#define ListBox_FindString(hwndCtl, indexStart, lpszFind) ((int)(DWORD)SNDMSG((hwndCtl), LB_FINDSTRING, (WPARAM)(int)(indexStart), (LPARAM)(LPCTSTR)(lpszFind)))
#define ListBox_FindItemData(hwndCtl, indexStart, data) ((int)(DWORD)SNDMSG((hwndCtl), LB_FINDSTRING, (WPARAM)(int)(indexStart), (LPARAM)(data)))
        
#define ListBox_SetSel(hwndCtl, fSelect, index)     ((int)(DWORD)SNDMSG((hwndCtl), LB_SETSEL, (WPARAM)(BOOL)(fSelect), (LPARAM)(index)))
#define ListBox_SelItemRange(hwndCtl, fSelect, first, last)    ((int)(DWORD)SNDMSG((hwndCtl), LB_SELITEMRANGE, (WPARAM)(BOOL)(fSelect), MAKELPARAM((first), (last))))
        
#define ListBox_GetCurSel(hwndCtl)                  ((int)(DWORD)SNDMSG((hwndCtl), LB_GETCURSEL, 0L, 0L))
#define ListBox_SetCurSel(hwndCtl, index)           ((int)(DWORD)SNDMSG((hwndCtl), LB_SETCURSEL, (WPARAM)(int)(index), 0L))
        
#define ListBox_SelectString(hwndCtl, indexStart, lpszFind) ((int)(DWORD)SNDMSG((hwndCtl), LB_SELECTSTRING, (WPARAM)(int)(indexStart), (LPARAM)(LPCTSTR)(lpszFind)))
#define ListBox_SelectItemData(hwndCtl, indexStart, data)   ((int)(DWORD)SNDMSG((hwndCtl), LB_SELECTSTRING, (WPARAM)(int)(indexStart), (LPARAM)(data)))
        
#define ListBox_GetSel(hwndCtl, index)              ((int)(DWORD)SNDMSG((hwndCtl), LB_GETSEL, (WPARAM)(int)(index), 0L))
#define ListBox_GetSelCount(hwndCtl)                ((int)(DWORD)SNDMSG((hwndCtl), LB_GETSELCOUNT, 0L, 0L))
#define ListBox_GetTopIndex(hwndCtl)                ((int)(DWORD)SNDMSG((hwndCtl), LB_GETTOPINDEX, 0L, 0L))
#define ListBox_GetSelItems(hwndCtl, cItems, lpItems) ((int)(DWORD)SNDMSG((hwndCtl), LB_GETSELITEMS, (WPARAM)(int)(cItems), (LPARAM)(int *)(lpItems)))
        
#define ListBox_SetTopIndex(hwndCtl, indexTop)      ((int)(DWORD)SNDMSG((hwndCtl), LB_SETTOPINDEX, (WPARAM)(int)(indexTop), 0L))
        
#define ListBox_SetColumnWidth(hwndCtl, cxColumn)   ((void)SNDMSG((hwndCtl), LB_SETCOLUMNWIDTH, (WPARAM)(int)(cxColumn), 0L))
#define ListBox_GetHorizontalExtent(hwndCtl)        ((int)(DWORD)SNDMSG((hwndCtl), LB_GETHORIZONTALEXTENT, 0L, 0L))
#define ListBox_SetHorizontalExtent(hwndCtl, cxExtent)     ((void)SNDMSG((hwndCtl), LB_SETHORIZONTALEXTENT, (WPARAM)(int)(cxExtent), 0L))
        
#define ListBox_SetTabStops(hwndCtl, cTabs, lpTabs) ((BOOL)(DWORD)SNDMSG((hwndCtl), LB_SETTABSTOPS, (WPARAM)(int)(cTabs), (LPARAM)(int *)(lpTabs)))
        
#define ListBox_GetItemRect(hwndCtl, index, lprc)   ((int)(DWORD)SNDMSG((hwndCtl), LB_GETITEMRECT, (WPARAM)(int)(index), (LPARAM)(RECT *)(lprc)))
        
#define ListBox_SetCaretIndex(hwndCtl, index)       ((int)(DWORD)SNDMSG((hwndCtl), LB_SETCARETINDEX, (WPARAM)(int)(index), 0L))
#define ListBox_GetCaretIndex(hwndCtl)              ((int)(DWORD)SNDMSG((hwndCtl), LB_GETCARETINDEX, 0L, 0L))
        
#define ListBox_FindStringExact(hwndCtl, indexStart, lpszFind) ((int)(DWORD)SNDMSG((hwndCtl), LB_FINDSTRINGEXACT, (WPARAM)(int)(indexStart), (LPARAM)(LPCTSTR)(lpszFind)))
        
#define ListBox_SetItemHeight(hwndCtl, index, cy)   ((int)(DWORD)SNDMSG((hwndCtl), LB_SETITEMHEIGHT, (WPARAM)(int)(index), MAKELPARAM((cy), 0)))
#define ListBox_GetItemHeight(hwndCtl, index)       ((int)(DWORD)SNDMSG((hwndCtl), LB_GETITEMHEIGHT, (WPARAM)(int)(index), 0L))
        
#define ListBox_Dir(hwndCtl, attrs, lpszFileSpec)   ((int)(DWORD)SNDMSG((hwndCtl), LB_DIR, (WPARAM)(UINT)(attrs), (LPARAM)(LPCTSTR)(lpszFileSpec)))
        
        /****** Edit control message APIs ********************************************/
        
#define Edit_Enable(hwndCtl, fEnable)           EnableWindow((hwndCtl), (fEnable))
        
#define Edit_GetText(hwndCtl, lpch, cchMax)     GetWindowTextA((hwndCtl), (lpch), (cchMax))
#define Edit_GetTextLength(hwndCtl)             GetWindowTextLengthA(hwndCtl)
#define Edit_SetText(hwndCtl, lpsz)             SetWindowTextA((hwndCtl), (lpsz))
#define Edit_SetReadOnly(hwndCtl, fReadOnly)    ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_SETREADONLY, (WPARAM)(BOOL)(fReadOnly), 0L))
        
#define Edit_LimitText(hwndCtl, cchMax)         ((void)SNDMSG((hwndCtl), EM_LIMITTEXT, (WPARAM)(cchMax), 0L))
        
#define Edit_GetLineCount(hwndCtl)              ((int)(DWORD)SNDMSG((hwndCtl), EM_GETLINECOUNT, 0L, 0L))
#ifndef _MAC
#define Edit_GetLine(hwndCtl, line, lpch, cchMax) ((*((int *)(lpch)) = (cchMax)), ((int)(DWORD)SNDMSG((hwndCtl), EM_GETLINE, (WPARAM)(int)(line), (LPARAM)(LPTSTR)(lpch))))
#else
#define Edit_GetLine(hwndCtl, line, lpch, cchMax) ((*((WORD *)(lpch)) = (cchMax)), ((int)(DWORD)SNDMSG((hwndCtl), EM_GETLINE, (WPARAM)(int)(line), (LPARAM)(LPTSTR)(lpch))))
#endif
        
#define Edit_GetRect(hwndCtl, lprc)             ((void)SNDMSG((hwndCtl), EM_GETRECT, 0L, (LPARAM)(RECT *)(lprc)))
#define Edit_SetRect(hwndCtl, lprc)             ((void)SNDMSG((hwndCtl), EM_SETRECT, 0L, (LPARAM)(const RECT *)(lprc)))
#define Edit_SetRectNoPaint(hwndCtl, lprc)      ((void)SNDMSG((hwndCtl), EM_SETRECTNP, 0L, (LPARAM)(const RECT *)(lprc)))
        
#define Edit_GetSel(hwndCtl)                    ((DWORD)SNDMSG((hwndCtl), EM_GETSEL, 0L, 0L))
#define Edit_SetSel(hwndCtl, ichStart, ichEnd)  ((void)SNDMSG((hwndCtl), EM_SETSEL, (ichStart), (ichEnd)))
#define Edit_ReplaceSel(hwndCtl, lpszReplace)   ((void)SNDMSG((hwndCtl), EM_REPLACESEL, 0L, (LPARAM)(LPCTSTR)(lpszReplace)))
        
#define Edit_GetModify(hwndCtl)                 ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_GETMODIFY, 0L, 0L))
#define Edit_SetModify(hwndCtl, fModified)      ((void)SNDMSG((hwndCtl), EM_SETMODIFY, (WPARAM)(UINT)(fModified), 0L))
        
#define Edit_ScrollCaret(hwndCtl)               ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_SCROLLCARET, 0, 0L))
        
#define Edit_LineFromChar(hwndCtl, ich)         ((int)(DWORD)SNDMSG((hwndCtl), EM_LINEFROMCHAR, (WPARAM)(int)(ich), 0L))
#define Edit_LineIndex(hwndCtl, line)           ((int)(DWORD)SNDMSG((hwndCtl), EM_LINEINDEX, (WPARAM)(int)(line), 0L))
#define Edit_LineLength(hwndCtl, line)          ((int)(DWORD)SNDMSG((hwndCtl), EM_LINELENGTH, (WPARAM)(int)(line), 0L))
        
#define Edit_Scroll(hwndCtl, dv, dh)            ((void)SNDMSG((hwndCtl), EM_LINESCROLL, (WPARAM)(dh), (LPARAM)(dv)))
        
#define Edit_CanUndo(hwndCtl)                   ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_CANUNDO, 0L, 0L))
#define Edit_Undo(hwndCtl)                      ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_UNDO, 0L, 0L))
#define Edit_EmptyUndoBuffer(hwndCtl)           ((void)SNDMSG((hwndCtl), EM_EMPTYUNDOBUFFER, 0L, 0L))
        
#define Edit_SetPasswordChar(hwndCtl, ch)       ((void)SNDMSG((hwndCtl), EM_SETPASSWORDCHAR, (WPARAM)(UINT)(ch), 0L))
        
#define Edit_SetTabStops(hwndCtl, cTabs, lpTabs) ((void)SNDMSG((hwndCtl), EM_SETTABSTOPS, (WPARAM)(int)(cTabs), (LPARAM)(const int *)(lpTabs)))
        
#define Edit_FmtLines(hwndCtl, fAddEOL)         ((BOOL)(DWORD)SNDMSG((hwndCtl), EM_FMTLINES, (WPARAM)(BOOL)(fAddEOL), 0L))
        
#define Edit_GetHandle(hwndCtl)                 ((HLOCAL)(UINT_PTR)SNDMSG((hwndCtl), EM_GETHANDLE, 0L, 0L))
#define Edit_SetHandle(hwndCtl, h)              ((void)SNDMSG((hwndCtl), EM_SETHANDLE, (WPARAM)(UINT_PTR)(HLOCAL)(h), 0L))
        
        
        
        //
        // Windows Graphical Interface Functions
        //
        
        WINUSERAPI   HDC		  WINAPI		GetDC(HWND hWnd);
        WINUSERAPI   HDC          WINAPI        GetDCEx(HWND  hWnd, HRGN hrgnClip, DWORD flags);
        WINUSERAPI   HDC          WINAPI        GetWindowDC(HWND hWnd);
        WINUSERAPI   int          WINAPI        ReleaseDC(HWND hWnd, HDC hDC);
        WINUSERAPI   HWND         WINAPI        GetDlgItem(HWND hDlg, int nIDDlgItem);
        WINUSERAPI   int          WINAPI        GetDlgCtrlID(HWND hDlg);
        WINUSERAPI   HBITMAP      WINAPI        CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, const VOID *lpBits);
        WINGDIAPI    HDC          WINAPI        CreateCompatibleDC(HDC hdc);
        WINGDIAPI    HBITMAP      WINAPI        CreateCompatibleBitmap(HDC hdc, int cx, int cy);
        WINGDIAPI    HBITMAP      WINAPI        CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset);
        WINGDIAPI    HBITMAP      WINAPI        CreateDIBitmap(HDC hdc, CONST BITMAPINFOHEADER *pbmih, DWORD flInit, CONST VOID *pjBits, CONST BITMAPINFO *pbmi, UINT iUsage);
        WINGDIAPI    HGDIOBJ      WINAPI        SelectObject(HDC hdc, HGDIOBJ h);
        WINGDIAPI    int          WINAPI        GetRgnBox(HRGN hrgn, LPRECT lprc);
        WINGDIAPI    BOOL         WINAPI        BeginPath(HDC hdc);
        WINGDIAPI    BOOL         WINAPI        EndPath(HDC hdc);
        WINGDIAPI	int		  WINAPI		ChoosePixelFormat(HDC hdc, CONST PIXELFORMATDESCRIPTOR *ppfd);
        WINGDIAPI	BOOL		 WINAPI		SetPixelFormat(HDC hdc, int format, CONST PIXELFORMATDESCRIPTOR * ppfd);
        WINGDIAPI	int		  WINAPI		StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, CONST VOID *lpBits, CONST BITMAPINFO *lpbmi, UINT iUsage, DWORD rop);
        WINGDIAPI    HRGN         WINAPI        CreateRectRgn(int x1, int y1, int x2, int y2);
        WINGDIAPI    BOOL         WINAPI        FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbr);
        WINGDIAPI    BOOL         WINAPI        BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
        WINGDIAPI	BOOL 		WINAPI		SwapBuffers(HDC);
        
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
        
        WINSOCK_API_LINKAGE		SOCKET	 WSAAPI		socket(int af, int type, int protocol);
        WINSOCK_API_LINKAGE		int        WSAAPI		select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);
        WINSOCK_API_LINKAGE		SOCKET	 WSAAPI		accept(SOCKET s, struct sockaddr *addr, int *addrlen);
        WINSOCK_API_LINKAGE		int	    WSAAPI		bind(SOCKET s, const struct sockaddr *name, int namelen);
        WINSOCK_API_LINKAGE		int	    WSAAPI		closesocket(SOCKET s);
        WINSOCK_API_LINKAGE		int	    WSAAPI		connect(SOCKET s, const struct sockaddr *name, int namelen);
        WINSOCK_API_LINKAGE		int	    WSAAPI		send(SOCKET s, const char *buf, int len, int flags);
        WINSOCK_API_LINKAGE		int	    WSAAPI		recv(SOCKET s, char *buf, int len, int flags);
        WINSOCK_API_LINKAGE		int	    WSAAPI		shutdown(SOCKET s, int how);
        
        WINSOCK_API_LINKAGE		u_long	 WSAAPI		htonl(u_long hostlong);
        WINSOCK_API_LINKAGE		u_short	WSAAPI		htons(u_short hostshort);
        WINSOCK_API_LINKAGE		u_long	 WSAAPI		ntohl(u_long netlong);
        WINSOCK_API_LINKAGE		u_short	WSAAPI		ntohs(u_short netshort);
        
        WINSOCK_API_LINKAGE        int        WSAAPI        setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen);
        WINSOCK_API_LINKAGE		int		WSAAPI		getaddrinfo(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult);
        WINSOCK_API_LINKAGE        int        WSAAPI        getnameinfo(const sockaddr *sa, socklen_t salen, char *host, DWORD hostlen, char *serv, DWORD servlen, int flags);
        WINSOCK_API_LINKAGE 	   VOID       WSAAPI        freeaddrinfo(PADDRINFOA pAddrInfo);
        
        /* DEPRECATED */
        WINSOCK_API_LINKAGE        hostent *  WSAAPI        gethostbyname(const char *name);
        WINSOCK_API_LINKAGE        hostent *  WSAAPI        gethostbyaddr(const char *addr,int len, int type);
        /* DEPRECATED */
        
        WINSOCK_API_LINKAGE		int		WSAAPI		inet_pton(int Family, PCSTR pszAddrString, PVOID pAddrBuf);
        PCSTR	  WSAAPI		inet_ntop(int Family, const VOID *pAddr, PSTR pStringBuf, size_t StringBufSize);
        WINSOCK_API_LINKAGE		u_long	 WSAAPI		inet_addr(const char *cp);
        
        WINSOCK_API_LINKAGE		int		WSAAPI		listen(SOCKET s, int backlog);
        
#pragma region ErrorCodes
        
#define ERROR_SUCCESS                    0L
#define ERROR_INVALID_FUNCTION           1L
#define ERROR_FILE_NOT_FOUND             2L
#define ERROR_PATH_NOT_FOUND             3L
#define ERROR_TOO_MANY_OPEN_FILES        4L
#define ERROR_ACCESS_DENIED              5L
#define ERROR_INVALID_HANDLE             6L
#define ERROR_ARENA_TRASHED              7L
#define ERROR_NOT_ENOUGH_MEMORY          8L    // dderror
#define ERROR_INVALID_BLOCK              9L
#define ERROR_BAD_ENVIRONMENT            10L
#define ERROR_BAD_FORMAT                 11L
#define ERROR_INVALID_ACCESS             12L
#define ERROR_INVALID_DATA               13L
#define ERROR_OUTOFMEMORY                14L
#define ERROR_INVALID_DRIVE              15L
#define ERROR_CURRENT_DIRECTORY          16L
#define ERROR_NOT_SAME_DEVICE            17L
#define ERROR_NO_MORE_FILES              18L
#define ERROR_WRITE_PROTECT              19L
#define ERROR_BAD_UNIT                   20L
#define ERROR_NOT_READY                  21L
#define ERROR_BAD_COMMAND                22L
#define ERROR_CRC                        23L
#define ERROR_BAD_LENGTH                 24L
#define ERROR_SEEK                       25L
#define ERROR_NOT_DOS_DISK               26L
#define ERROR_SECTOR_NOT_FOUND           27L
#define ERROR_OUT_OF_PAPER               28L
#define ERROR_WRITE_FAULT                29L
#define ERROR_READ_FAULT                 30L
#define ERROR_GEN_FAILURE                31L
#define ERROR_SHARING_VIOLATION          32L
#define ERROR_LOCK_VIOLATION             33L
#define ERROR_WRONG_DISK                 34L
#define ERROR_SHARING_BUFFER_EXCEEDED    36L
#define ERROR_HANDLE_EOF                 38L
#define ERROR_HANDLE_DISK_FULL           39L
#define ERROR_NOT_SUPPORTED              50L
#define ERROR_REM_NOT_LIST               51L
#define ERROR_DUP_NAME                   52L
#define ERROR_BAD_NETPATH                53L
#define ERROR_NETWORK_BUSY               54L
#define ERROR_DEV_NOT_EXIST              55L    // dderror
#define ERROR_TOO_MANY_CMDS              56L
#define ERROR_ADAP_HDW_ERR               57L
#define ERROR_BAD_NET_RESP               58L
#define ERROR_UNEXP_NET_ERR              59L
#define ERROR_BAD_REM_ADAP               60L
#define ERROR_PRINTQ_FULL                61L
#define ERROR_NO_SPOOL_SPACE             62L
#define ERROR_PRINT_CANCELLED            63L
#define ERROR_NETNAME_DELETED            64L
#define ERROR_NETWORK_ACCESS_DENIED      65L
#define ERROR_BAD_DEV_TYPE               66L
#define ERROR_BAD_NET_NAME               67L
#define ERROR_TOO_MANY_NAMES             68L
#define ERROR_TOO_MANY_SESS              69L
#define ERROR_SHARING_PAUSED             70L
#define ERROR_REQ_NOT_ACCEP              71L
#define ERROR_REDIR_PAUSED               72L
#define ERROR_FILE_EXISTS                80L
#define ERROR_CANNOT_MAKE                82L
#define ERROR_FAIL_I24                   83L
#define ERROR_OUT_OF_STRUCTURES          84L
#define ERROR_ALREADY_ASSIGNED           85L
#define ERROR_INVALID_PASSWORD           86L
#define ERROR_INVALID_PARAMETER          87L    // dderror
#define ERROR_NET_WRITE_FAULT            88L
#define ERROR_NO_PROC_SLOTS              89L
#define ERROR_TOO_MANY_SEMAPHORES        100L
#define ERROR_EXCL_SEM_ALREADY_OWNED     101L
#define ERROR_SEM_IS_SET                 102L
#define ERROR_TOO_MANY_SEM_REQUESTS      103L
#define ERROR_INVALID_AT_INTERRUPT_TIME  104L
#define ERROR_SEM_OWNER_DIED             105L
#define ERROR_SEM_USER_LIMIT             106L
#define ERROR_DISK_CHANGE                107L
#define ERROR_DRIVE_LOCKED               108L
#define ERROR_BROKEN_PIPE                109L
#define ERROR_OPEN_FAILED                110L
#define ERROR_BUFFER_OVERFLOW            111L
#define ERROR_DISK_FULL                  112L
#define ERROR_NO_MORE_SEARCH_HANDLES     113L
#define ERROR_INVALID_TARGET_HANDLE      114L
#define ERROR_INVALID_CATEGORY           117L
#define ERROR_INVALID_VERIFY_SWITCH      118L
#define ERROR_BAD_DRIVER_LEVEL           119L
#define ERROR_CALL_NOT_IMPLEMENTED       120L
#define ERROR_SEM_TIMEOUT                121L
#define ERROR_INSUFFICIENT_BUFFER        122L    // dderror
#define ERROR_INVALID_NAME               123L    // dderror
#define ERROR_INVALID_LEVEL              124L
#define ERROR_NO_VOLUME_LABEL            125L
#define ERROR_MOD_NOT_FOUND              126L
#define ERROR_PROC_NOT_FOUND             127L
#define ERROR_WAIT_NO_CHILDREN           128L
#define ERROR_CHILD_NOT_COMPLETE         129L
#define ERROR_DIRECT_ACCESS_HANDLE       130L
#define ERROR_NEGATIVE_SEEK              131L
#define ERROR_SEEK_ON_DEVICE             132L
#define ERROR_IS_JOIN_TARGET             133L
#define ERROR_IS_JOINED                  134L
#define ERROR_IS_SUBSTED                 135L
#define ERROR_NOT_JOINED                 136L
#define ERROR_NOT_SUBSTED                137L
#define ERROR_JOIN_TO_JOIN               138L
#define ERROR_SUBST_TO_SUBST             139L
#define ERROR_JOIN_TO_SUBST              140L
#define ERROR_SUBST_TO_JOIN              141L
#define ERROR_BUSY_DRIVE                 142L
#define ERROR_SAME_DRIVE                 143L
#define ERROR_DIR_NOT_ROOT               144L
#define ERROR_DIR_NOT_EMPTY              145L
#define ERROR_IS_SUBST_PATH              146L
#define ERROR_IS_JOIN_PATH               147L
#define ERROR_PATH_BUSY                  148L
#define ERROR_IS_SUBST_TARGET            149L
#define ERROR_SYSTEM_TRACE               150L
#define ERROR_INVALID_EVENT_COUNT        151L
#define ERROR_TOO_MANY_MUXWAITERS        152L
#define ERROR_INVALID_LIST_FORMAT        153L
#define ERROR_LABEL_TOO_LONG             154L
#define ERROR_TOO_MANY_TCBS              155L
#define ERROR_SIGNAL_REFUSED             156L
#define ERROR_DISCARDED                  157L
#define ERROR_NOT_LOCKED                 158L
#define ERROR_BAD_THREADID_ADDR          159L
#define ERROR_BAD_ARGUMENTS              160L
#define ERROR_BAD_PATHNAME               161L
#define ERROR_SIGNAL_PENDING             162L
#define ERROR_MAX_THRDS_REACHED          164L
#define ERROR_LOCK_FAILED                167L
#define ERROR_BUSY                       170L    // dderror
#define ERROR_DEVICE_SUPPORT_IN_PROGRESS 171L
#define ERROR_CANCEL_VIOLATION           173L
#define ERROR_ATOMIC_LOCKS_NOT_SUPPORTED 174L
#define ERROR_INVALID_SEGMENT_NUMBER     180L
#define ERROR_INVALID_ORDINAL            182L
#define ERROR_ALREADY_EXISTS             183L
#define ERROR_INVALID_FLAG_NUMBER        186L
#define ERROR_SEM_NOT_FOUND              187L
#define ERROR_INVALID_STARTING_CODESEG   188L
#define ERROR_INVALID_STACKSEG           189L
#define ERROR_INVALID_MODULETYPE         190L
#define ERROR_INVALID_EXE_SIGNATURE      191L
#define ERROR_EXE_MARKED_INVALID         192L
#define ERROR_BAD_EXE_FORMAT             193L
#define ERROR_ITERATED_DATA_EXCEEDS_64k  194L
#define ERROR_INVALID_MINALLOCSIZE       195L
#define ERROR_DYNLINK_FROM_INVALID_RING  196L
#define ERROR_IOPL_NOT_ENABLED           197L
#define ERROR_INVALID_SEGDPL             198L
#define ERROR_AUTODATASEG_EXCEEDS_64k    199L
#define ERROR_RING2SEG_MUST_BE_MOVABLE   200L
#define ERROR_RELOC_CHAIN_XEEDS_SEGLIM   201L
#define ERROR_INFLOOP_IN_RELOC_CHAIN     202L
#define ERROR_ENVVAR_NOT_FOUND           203L
#define ERROR_NO_SIGNAL_SENT             205L
#define ERROR_FILENAME_EXCED_RANGE       206L
#define ERROR_RING2_STACK_IN_USE         207L
#define ERROR_META_EXPANSION_TOO_LONG    208L
#define ERROR_INVALID_SIGNAL_NUMBER      209L
#define ERROR_THREAD_1_INACTIVE          210L
#define ERROR_LOCKED                     212L
#define ERROR_TOO_MANY_MODULES           214L
#define ERROR_NESTING_NOT_ALLOWED        215L
#define ERROR_EXE_MACHINE_TYPE_MISMATCH  216L
#define ERROR_EXE_CANNOT_MODIFY_SIGNED_BINARY 217L
#define ERROR_EXE_CANNOT_MODIFY_STRONG_SIGNED_BINARY 218L
#define ERROR_FILE_CHECKED_OUT           220L
#define ERROR_CHECKOUT_REQUIRED          221L
#define ERROR_BAD_FILE_TYPE              222L
#define ERROR_FILE_TOO_LARGE             223L
#define ERROR_FORMS_AUTH_REQUIRED        224L
#define ERROR_VIRUS_INFECTED             225L
#define ERROR_VIRUS_DELETED              226L
#define ERROR_PIPE_LOCAL                 229L
#define ERROR_BAD_PIPE                   230L
#define ERROR_PIPE_BUSY                  231L
#define ERROR_NO_DATA                    232L
#define ERROR_PIPE_NOT_CONNECTED         233L
#define ERROR_MORE_DATA                  234L    // dderror
#define ERROR_NO_WORK_DONE               235L
#define ERROR_VC_DISCONNECTED            240L
#define ERROR_INVALID_EA_NAME            254L
#define ERROR_EA_LIST_INCONSISTENT       255L
#define WAIT_TIMEOUT                     258L    // dderror
#define ERROR_NO_MORE_ITEMS              259L
#define ERROR_CANNOT_COPY                266L
#define ERROR_DIRECTORY                  267L
#define ERROR_EAS_DIDNT_FIT              275L
#define ERROR_EA_FILE_CORRUPT            276L
#define ERROR_EA_TABLE_FULL              277L
#define ERROR_INVALID_EA_HANDLE          278L
#define ERROR_EAS_NOT_SUPPORTED          282L
#define ERROR_NOT_OWNER                  288L
#define ERROR_TOO_MANY_POSTS             298L
#define ERROR_PARTIAL_COPY               299L
#define ERROR_OPLOCK_NOT_GRANTED         300L
#define ERROR_INVALID_OPLOCK_PROTOCOL    301L
#define ERROR_DISK_TOO_FRAGMENTED        302L
#define ERROR_DELETE_PENDING             303L
#define ERROR_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING 304L
#define ERROR_SHORT_NAMES_NOT_ENABLED_ON_VOLUME 305L
#define ERROR_SECURITY_STREAM_IS_INCONSISTENT 306L
#define ERROR_INVALID_LOCK_RANGE         307L
#define ERROR_IMAGE_SUBSYSTEM_NOT_PRESENT 308L
#define ERROR_NOTIFICATION_GUID_ALREADY_DEFINED 309L
#define ERROR_INVALID_EXCEPTION_HANDLER  310L
#define ERROR_DUPLICATE_PRIVILEGES       311L
#define ERROR_NO_RANGES_PROCESSED        312L
#define ERROR_NOT_ALLOWED_ON_SYSTEM_FILE 313L
#define ERROR_DISK_RESOURCES_EXHAUSTED   314L
#define ERROR_INVALID_TOKEN              315L
#define ERROR_DEVICE_FEATURE_NOT_SUPPORTED 316L
#define ERROR_MR_MID_NOT_FOUND           317L
#define ERROR_SCOPE_NOT_FOUND            318L
#define ERROR_UNDEFINED_SCOPE            319L
#define ERROR_INVALID_CAP                320L
#define ERROR_DEVICE_UNREACHABLE         321L
#define ERROR_DEVICE_NO_RESOURCES        322L
#define ERROR_DATA_CHECKSUM_ERROR        323L
#define ERROR_INTERMIXED_KERNEL_EA_OPERATION 324L
#define ERROR_FILE_LEVEL_TRIM_NOT_SUPPORTED 326L
#define ERROR_OFFSET_ALIGNMENT_VIOLATION 327L
#define ERROR_INVALID_FIELD_IN_PARAMETER_LIST 328L
#define ERROR_OPERATION_IN_PROGRESS      329L
#define ERROR_BAD_DEVICE_PATH            330L
#define ERROR_TOO_MANY_DESCRIPTORS       331L
#define ERROR_SCRUB_DATA_DISABLED        332L
#define ERROR_NOT_REDUNDANT_STORAGE      333L
#define ERROR_RESIDENT_FILE_NOT_SUPPORTED 334L
#define ERROR_COMPRESSED_FILE_NOT_SUPPORTED 335L
#define ERROR_DIRECTORY_NOT_SUPPORTED    336L
#define ERROR_NOT_READ_FROM_COPY         337L
#define ERROR_FT_WRITE_FAILURE           338L
#define ERROR_FT_DI_SCAN_REQUIRED        339L
#define ERROR_INVALID_KERNEL_INFO_VERSION 340L
#define ERROR_INVALID_PEP_INFO_VERSION   341L
#define ERROR_OBJECT_NOT_EXTERNALLY_BACKED 342L
#define ERROR_EXTERNAL_BACKING_PROVIDER_UNKNOWN 343L
#define ERROR_COMPRESSION_NOT_BENEFICIAL 344L
#define ERROR_STORAGE_TOPOLOGY_ID_MISMATCH 345L
#define ERROR_BLOCKED_BY_PARENTAL_CONTROLS 346L
#define ERROR_BLOCK_TOO_MANY_REFERENCES  347L
#define ERROR_MARKED_TO_DISALLOW_WRITES  348L
#define ERROR_ENCLAVE_FAILURE            349L
#define ERROR_FAIL_NOACTION_REBOOT       350L
#define ERROR_FAIL_SHUTDOWN              351L
#define ERROR_FAIL_RESTART               352L
#define ERROR_MAX_SESSIONS_REACHED       353L
#define ERROR_NETWORK_ACCESS_DENIED_EDP  354L
#define ERROR_DEVICE_HINT_NAME_BUFFER_TOO_SMALL 355L
#define ERROR_EDP_POLICY_DENIES_OPERATION 356L
#define ERROR_EDP_DPL_POLICY_CANT_BE_SATISFIED 357L
#define ERROR_CLOUD_FILE_PROVIDER_UNKNOWN 358L
#define ERROR_DEVICE_IN_MAINTENANCE      359L
#define ERROR_NOT_SUPPORTED_ON_DAX       360L
#define ERROR_DAX_MAPPING_EXISTS         361L
#define ERROR_CLOUD_FILE_PROVIDER_NOT_RUNNING 362L
#define ERROR_CLOUD_FILE_METADATA_CORRUPT 363L
#define ERROR_CLOUD_FILE_METADATA_TOO_LARGE 364L
#define ERROR_CLOUD_FILE_PROPERTY_BLOB_TOO_LARGE 365L
#define ERROR_CLOUD_FILE_PROPERTY_BLOB_CHECKSUM_MISMATCH 366L
#define ERROR_CHILD_PROCESS_BLOCKED      367L
#define ERROR_STORAGE_LOST_DATA_PERSISTENCE 368L
#define ERROR_THREAD_MODE_ALREADY_BACKGROUND 400L
#define ERROR_THREAD_MODE_NOT_BACKGROUND 401L
#define ERROR_PROCESS_MODE_ALREADY_BACKGROUND 402L
#define ERROR_PROCESS_MODE_NOT_BACKGROUND 403L
#define ERROR_CAPAUTHZ_NOT_DEVUNLOCKED   450L
#define ERROR_CAPAUTHZ_CHANGE_TYPE       451L
#define ERROR_CAPAUTHZ_NOT_PROVISIONED   452L
#define ERROR_CAPAUTHZ_NOT_AUTHORIZED    453L
#define ERROR_CAPAUTHZ_NO_POLICY         454L
#define ERROR_CAPAUTHZ_DB_CORRUPTED      455L
#define ERROR_DEVICE_HARDWARE_ERROR      483L
#define ERROR_INVALID_ADDRESS            487L
#define ERROR_USER_PROFILE_LOAD          500L
#define ERROR_ARITHMETIC_OVERFLOW        534L
#define ERROR_PIPE_CONNECTED             535L
#define ERROR_PIPE_LISTENING             536L
#define ERROR_VERIFIER_STOP              537L
#define ERROR_ABIOS_ERROR                538L
#define ERROR_WX86_WARNING               539L
#define ERROR_WX86_ERROR                 540L
#define ERROR_TIMER_NOT_CANCELED         541L
#define ERROR_UNWIND                     542L
#define ERROR_BAD_STACK                  543L
#define ERROR_INVALID_UNWIND_TARGET      544L
#define ERROR_INVALID_PORT_ATTRIBUTES    545L
#define ERROR_PORT_MESSAGE_TOO_LONG      546L
#define ERROR_INVALID_QUOTA_LOWER        547L
#define ERROR_DEVICE_ALREADY_ATTACHED    548L
#define ERROR_INSTRUCTION_MISALIGNMENT   549L
#define ERROR_PROFILING_NOT_STARTED      550L
#define ERROR_PROFILING_NOT_STOPPED      551L
#define ERROR_COULD_NOT_INTERPRET        552L
#define ERROR_PROFILING_AT_LIMIT         553L
#define ERROR_CANT_WAIT                  554L
#define ERROR_CANT_TERMINATE_SELF        555L
#define ERROR_UNEXPECTED_MM_CREATE_ERR   556L
#define ERROR_UNEXPECTED_MM_MAP_ERROR    557L
#define ERROR_UNEXPECTED_MM_EXTEND_ERR   558L
#define ERROR_BAD_FUNCTION_TABLE         559L
#define ERROR_NO_GUID_TRANSLATION        560L
#define ERROR_INVALID_LDT_SIZE           561L
#define ERROR_INVALID_LDT_OFFSET         563L
#define ERROR_INVALID_LDT_DESCRIPTOR     564L
#define ERROR_TOO_MANY_THREADS           565L
#define ERROR_THREAD_NOT_IN_PROCESS      566L
#define ERROR_PAGEFILE_QUOTA_EXCEEDED    567L
#define ERROR_LOGON_SERVER_CONFLICT      568L
#define ERROR_SYNCHRONIZATION_REQUIRED   569L
#define ERROR_NET_OPEN_FAILED            570L
#define ERROR_IO_PRIVILEGE_FAILED        571L
#define ERROR_CONTROL_C_EXIT             572L    // winnt
#define ERROR_MISSING_SYSTEMFILE         573L
#define ERROR_UNHANDLED_EXCEPTION        574L
#define ERROR_APP_INIT_FAILURE           575L
#define ERROR_PAGEFILE_CREATE_FAILED     576L
#define ERROR_INVALID_IMAGE_HASH         577L
#define ERROR_NO_PAGEFILE                578L
#define ERROR_ILLEGAL_FLOAT_CONTEXT      579L
#define ERROR_NO_EVENT_PAIR              580L
#define ERROR_DOMAIN_CTRLR_CONFIG_ERROR  581L
#define ERROR_ILLEGAL_CHARACTER          582L
#define ERROR_UNDEFINED_CHARACTER        583L
#define ERROR_FLOPPY_VOLUME              584L
#define ERROR_BIOS_FAILED_TO_CONNECT_INTERRUPT 585L
#define ERROR_BACKUP_CONTROLLER          586L
#define ERROR_MUTANT_LIMIT_EXCEEDED      587L
#define ERROR_FS_DRIVER_REQUIRED         588L
#define ERROR_CANNOT_LOAD_REGISTRY_FILE  589L
#define ERROR_DEBUG_ATTACH_FAILED        590L
#define ERROR_SYSTEM_PROCESS_TERMINATED  591L
#define ERROR_DATA_NOT_ACCEPTED          592L
#define ERROR_VDM_HARD_ERROR             593L
#define ERROR_DRIVER_CANCEL_TIMEOUT      594L
#define ERROR_REPLY_MESSAGE_MISMATCH     595L
#define ERROR_LOST_WRITEBEHIND_DATA      596L
#define ERROR_CLIENT_SERVER_PARAMETERS_INVALID 597L
#define ERROR_NOT_TINY_STREAM            598L
#define ERROR_STACK_OVERFLOW_READ        599L
#define ERROR_CONVERT_TO_LARGE           600L
#define ERROR_FOUND_OUT_OF_SCOPE         601L
#define ERROR_ALLOCATE_BUCKET            602L
#define ERROR_MARSHALL_OVERFLOW          603L
#define ERROR_INVALID_VARIANT            604L
#define ERROR_BAD_COMPRESSION_BUFFER     605L
#define ERROR_AUDIT_FAILED               606L
#define ERROR_TIMER_RESOLUTION_NOT_SET   607L
#define ERROR_INSUFFICIENT_LOGON_INFO    608L
#define ERROR_BAD_DLL_ENTRYPOINT         609L
#define ERROR_BAD_SERVICE_ENTRYPOINT     610L
#define ERROR_IP_ADDRESS_CONFLICT1       611L
#define ERROR_IP_ADDRESS_CONFLICT2       612L
#define ERROR_REGISTRY_QUOTA_LIMIT       613L
#define ERROR_NO_CALLBACK_ACTIVE         614L
#define ERROR_PWD_TOO_SHORT              615L
#define ERROR_PWD_TOO_RECENT             616L
#define ERROR_PWD_HISTORY_CONFLICT       617L
#define ERROR_UNSUPPORTED_COMPRESSION    618L
#define ERROR_INVALID_HW_PROFILE         619L
#define ERROR_INVALID_PLUGPLAY_DEVICE_PATH 620L
#define ERROR_QUOTA_LIST_INCONSISTENT    621L
#define ERROR_EVALUATION_EXPIRATION      622L
#define ERROR_ILLEGAL_DLL_RELOCATION     623L
#define ERROR_DLL_INIT_FAILED_LOGOFF     624L
#define ERROR_VALIDATE_CONTINUE          625L
#define ERROR_NO_MORE_MATCHES            626L
#define ERROR_RANGE_LIST_CONFLICT        627L
#define ERROR_SERVER_SID_MISMATCH        628L
#define ERROR_CANT_ENABLE_DENY_ONLY      629L
#define ERROR_FLOAT_MULTIPLE_FAULTS      630L    // winnt
#define ERROR_FLOAT_MULTIPLE_TRAPS       631L    // winnt
#define ERROR_NOINTERFACE                632L
#define ERROR_DRIVER_FAILED_SLEEP        633L
#define ERROR_CORRUPT_SYSTEM_FILE        634L
#define ERROR_COMMITMENT_MINIMUM         635L
#define ERROR_PNP_RESTART_ENUMERATION    636L
#define ERROR_SYSTEM_IMAGE_BAD_SIGNATURE 637L
#define ERROR_PNP_REBOOT_REQUIRED        638L
#define ERROR_INSUFFICIENT_POWER         639L
#define ERROR_MULTIPLE_FAULT_VIOLATION   640L
#define ERROR_SYSTEM_SHUTDOWN            641L
#define ERROR_PORT_NOT_SET               642L
#define ERROR_DS_VERSION_CHECK_FAILURE   643L
#define ERROR_RANGE_NOT_FOUND            644L
#define ERROR_NOT_SAFE_MODE_DRIVER       646L
#define ERROR_FAILED_DRIVER_ENTRY        647L
#define ERROR_DEVICE_ENUMERATION_ERROR   648L
#define ERROR_MOUNT_POINT_NOT_RESOLVED   649L
#define ERROR_INVALID_DEVICE_OBJECT_PARAMETER 650L
#define ERROR_MCA_OCCURED                651L
#define ERROR_DRIVER_DATABASE_ERROR      652L
#define ERROR_SYSTEM_HIVE_TOO_LARGE      653L
#define ERROR_DRIVER_FAILED_PRIOR_UNLOAD 654L
#define ERROR_VOLSNAP_PREPARE_HIBERNATE  655L
#define ERROR_HIBERNATION_FAILURE        656L
#define ERROR_PWD_TOO_LONG               657L
#define ERROR_FILE_SYSTEM_LIMITATION     665L
#define ERROR_ASSERTION_FAILURE          668L
#define ERROR_ACPI_ERROR                 669L
#define ERROR_WOW_ASSERTION              670L
#define ERROR_PNP_BAD_MPS_TABLE          671L
#define ERROR_PNP_TRANSLATION_FAILED     672L
#define ERROR_PNP_IRQ_TRANSLATION_FAILED 673L
#define ERROR_PNP_INVALID_ID             674L
#define ERROR_WAKE_SYSTEM_DEBUGGER       675L
#define ERROR_HANDLES_CLOSED             676L
#define ERROR_EXTRANEOUS_INFORMATION     677L
#define ERROR_RXACT_COMMIT_NECESSARY     678L
#define ERROR_MEDIA_CHECK                679L
#define ERROR_GUID_SUBSTITUTION_MADE     680L
#define ERROR_STOPPED_ON_SYMLINK         681L
#define ERROR_LONGJUMP                   682L
#define ERROR_PLUGPLAY_QUERY_VETOED      683L
#define ERROR_UNWIND_CONSOLIDATE         684L
#define ERROR_REGISTRY_HIVE_RECOVERED    685L
#define ERROR_DLL_MIGHT_BE_INSECURE      686L
#define ERROR_DLL_MIGHT_BE_INCOMPATIBLE  687L
#define ERROR_DBG_EXCEPTION_NOT_HANDLED  688L    // winnt
#define ERROR_DBG_REPLY_LATER            689L
#define ERROR_DBG_UNABLE_TO_PROVIDE_HANDLE 690L
#define ERROR_DBG_TERMINATE_THREAD       691L    // winnt
#define ERROR_DBG_TERMINATE_PROCESS      692L    // winnt
#define ERROR_DBG_CONTROL_C              693L    // winnt
#define ERROR_DBG_PRINTEXCEPTION_C       694L
#define ERROR_DBG_RIPEXCEPTION           695L
#define ERROR_DBG_CONTROL_BREAK          696L    // winnt
#define ERROR_DBG_COMMAND_EXCEPTION      697L    // winnt
#define ERROR_OBJECT_NAME_EXISTS         698L
#define ERROR_THREAD_WAS_SUSPENDED       699L
#define ERROR_IMAGE_NOT_AT_BASE          700L
#define ERROR_RXACT_STATE_CREATED        701L
#define ERROR_SEGMENT_NOTIFICATION       702L    // winnt
#define ERROR_BAD_CURRENT_DIRECTORY      703L
#define ERROR_FT_READ_RECOVERY_FROM_BACKUP 704L
#define ERROR_FT_WRITE_RECOVERY          705L
#define ERROR_IMAGE_MACHINE_TYPE_MISMATCH 706L
#define ERROR_RECEIVE_PARTIAL            707L
#define ERROR_RECEIVE_EXPEDITED          708L
#define ERROR_RECEIVE_PARTIAL_EXPEDITED  709L
#define ERROR_EVENT_DONE                 710L
#define ERROR_EVENT_PENDING              711L
#define ERROR_CHECKING_FILE_SYSTEM       712L
#define ERROR_FATAL_APP_EXIT             713L
#define ERROR_PREDEFINED_HANDLE          714L
#define ERROR_WAS_UNLOCKED               715L
#define ERROR_SERVICE_NOTIFICATION       716L
#define ERROR_WAS_LOCKED                 717L
#define ERROR_LOG_HARD_ERROR             718L
#define ERROR_ALREADY_WIN32              719L
#define ERROR_IMAGE_MACHINE_TYPE_MISMATCH_EXE 720L
#define ERROR_NO_YIELD_PERFORMED         721L
#define ERROR_TIMER_RESUME_IGNORED       722L
#define ERROR_ARBITRATION_UNHANDLED      723L
#define ERROR_CARDBUS_NOT_SUPPORTED      724L
#define ERROR_MP_PROCESSOR_MISMATCH      725L
#define ERROR_HIBERNATED                 726L
#define ERROR_RESUME_HIBERNATION         727L
#define ERROR_FIRMWARE_UPDATED           728L
#define ERROR_DRIVERS_LEAKING_LOCKED_PAGES 729L
#define ERROR_WAKE_SYSTEM                730L
#define ERROR_WAIT_1                     731L
#define ERROR_WAIT_2                     732L
#define ERROR_WAIT_3                     733L
#define ERROR_WAIT_63                    734L
#define ERROR_ABANDONED_WAIT_0           735L    // winnt
#define ERROR_ABANDONED_WAIT_63          736L
#define ERROR_USER_APC                   737L    // winnt
#define ERROR_KERNEL_APC                 738L
#define ERROR_ALERTED                    739L
#define ERROR_ELEVATION_REQUIRED         740L
#define ERROR_REPARSE                    741L
#define ERROR_OPLOCK_BREAK_IN_PROGRESS   742L
#define ERROR_VOLUME_MOUNTED             743L
#define ERROR_RXACT_COMMITTED            744L
#define ERROR_NOTIFY_CLEANUP             745L
#define ERROR_PRIMARY_TRANSPORT_CONNECT_FAILED 746L
#define ERROR_PAGE_FAULT_TRANSITION      747L
#define ERROR_PAGE_FAULT_DEMAND_ZERO     748L
#define ERROR_PAGE_FAULT_COPY_ON_WRITE   749L
#define ERROR_PAGE_FAULT_GUARD_PAGE      750L
#define ERROR_PAGE_FAULT_PAGING_FILE     751L
#define ERROR_CACHE_PAGE_LOCKED          752L
#define ERROR_CRASH_DUMP                 753L
#define ERROR_BUFFER_ALL_ZEROS           754L
#define ERROR_REPARSE_OBJECT             755L
#define ERROR_RESOURCE_REQUIREMENTS_CHANGED 756L
#define ERROR_TRANSLATION_COMPLETE       757L
#define ERROR_NOTHING_TO_TERMINATE       758L
#define ERROR_PROCESS_NOT_IN_JOB         759L
#define ERROR_PROCESS_IN_JOB             760L
#define ERROR_VOLSNAP_HIBERNATE_READY    761L
#define ERROR_FSFILTER_OP_COMPLETED_SUCCESSFULLY 762L
#define ERROR_INTERRUPT_VECTOR_ALREADY_CONNECTED 763L
#define ERROR_INTERRUPT_STILL_CONNECTED  764L
#define ERROR_WAIT_FOR_OPLOCK            765L
#define ERROR_DBG_EXCEPTION_HANDLED      766L    // winnt
#define ERROR_DBG_CONTINUE               767L    // winnt
#define ERROR_CALLBACK_POP_STACK         768L
#define ERROR_COMPRESSION_DISABLED       769L
#define ERROR_CANTFETCHBACKWARDS         770L
#define ERROR_CANTSCROLLBACKWARDS        771L
#define ERROR_ROWSNOTRELEASED            772L
#define ERROR_BAD_ACCESSOR_FLAGS         773L
#define ERROR_ERRORS_ENCOUNTERED         774L
#define ERROR_NOT_CAPABLE                775L
#define ERROR_REQUEST_OUT_OF_SEQUENCE    776L
#define ERROR_VERSION_PARSE_ERROR        777L
#define ERROR_BADSTARTPOSITION           778L
#define ERROR_MEMORY_HARDWARE            779L
#define ERROR_DISK_REPAIR_DISABLED       780L
#define ERROR_INSUFFICIENT_RESOURCE_FOR_SPECIFIED_SHARED_SECTION_SIZE 781L
#define ERROR_SYSTEM_POWERSTATE_TRANSITION 782L
#define ERROR_SYSTEM_POWERSTATE_COMPLEX_TRANSITION 783L
#define ERROR_MCA_EXCEPTION              784L
#define ERROR_ACCESS_AUDIT_BY_POLICY     785L
#define ERROR_ACCESS_DISABLED_NO_SAFER_UI_BY_POLICY 786L
#define ERROR_ABANDON_HIBERFILE          787L
#define ERROR_LOST_WRITEBEHIND_DATA_NETWORK_DISCONNECTED 788L
#define ERROR_LOST_WRITEBEHIND_DATA_NETWORK_SERVER_ERROR 789L
#define ERROR_LOST_WRITEBEHIND_DATA_LOCAL_DISK_ERROR 790L
#define ERROR_BAD_MCFG_TABLE             791L
#define ERROR_DISK_REPAIR_REDIRECTED     792L
#define ERROR_DISK_REPAIR_UNSUCCESSFUL   793L
#define ERROR_CORRUPT_LOG_OVERFULL       794L
#define ERROR_CORRUPT_LOG_CORRUPTED      795L
#define ERROR_CORRUPT_LOG_UNAVAILABLE    796L
#define ERROR_CORRUPT_LOG_DELETED_FULL   797L
#define ERROR_CORRUPT_LOG_CLEARED        798L
#define ERROR_ORPHAN_NAME_EXHAUSTED      799L
#define ERROR_OPLOCK_SWITCHED_TO_NEW_HANDLE 800L
#define ERROR_CANNOT_GRANT_REQUESTED_OPLOCK 801L
#define ERROR_CANNOT_BREAK_OPLOCK        802L
#define ERROR_OPLOCK_HANDLE_CLOSED       803L
#define ERROR_NO_ACE_CONDITION           804L
#define ERROR_INVALID_ACE_CONDITION      805L
#define ERROR_FILE_HANDLE_REVOKED        806L
#define ERROR_IMAGE_AT_DIFFERENT_BASE    807L
#define ERROR_ENCRYPTED_IO_NOT_POSSIBLE  808L
#define ERROR_FILE_METADATA_OPTIMIZATION_IN_PROGRESS 809L
#define ERROR_QUOTA_ACTIVITY             810L
#define ERROR_HANDLE_REVOKED             811L
#define ERROR_CALLBACK_INVOKE_INLINE     812L
#define ERROR_CPU_SET_INVALID            813L
#define ERROR_EA_ACCESS_DENIED           994L
#define ERROR_OPERATION_ABORTED          995L
#define ERROR_IO_INCOMPLETE              996L
#define ERROR_IO_PENDING                 997L    // dderror
#define ERROR_NOACCESS                   998L
#define ERROR_SWAPERROR                  999L
#define ERROR_STACK_OVERFLOW             1001L
#define ERROR_INVALID_MESSAGE            1002L
#define ERROR_CAN_NOT_COMPLETE           1003L
#define ERROR_INVALID_FLAGS              1004L
#define ERROR_UNRECOGNIZED_VOLUME        1005L
#define ERROR_FILE_INVALID               1006L
#define ERROR_FULLSCREEN_MODE            1007L
#define ERROR_NO_TOKEN                   1008L
#define ERROR_BADDB                      1009L
#define ERROR_BADKEY                     1010L
#define ERROR_CANTOPEN                   1011L
#define ERROR_CANTREAD                   1012L
#define ERROR_CANTWRITE                  1013L
#define ERROR_REGISTRY_RECOVERED         1014L
#define ERROR_REGISTRY_CORRUPT           1015L
#define ERROR_REGISTRY_IO_FAILED         1016L
#define ERROR_NOT_REGISTRY_FILE          1017L
#define ERROR_KEY_DELETED                1018L
#define ERROR_NO_LOG_SPACE               1019L
#define ERROR_KEY_HAS_CHILDREN           1020L
#define ERROR_CHILD_MUST_BE_VOLATILE     1021L
#define ERROR_NOTIFY_ENUM_DIR            1022L
#define ERROR_DEPENDENT_SERVICES_RUNNING 1051L
#define ERROR_INVALID_SERVICE_CONTROL    1052L
#define ERROR_SERVICE_REQUEST_TIMEOUT    1053L
#define ERROR_SERVICE_NO_THREAD          1054L
#define ERROR_SERVICE_DATABASE_LOCKED    1055L
#define ERROR_SERVICE_ALREADY_RUNNING    1056L
#define ERROR_INVALID_SERVICE_ACCOUNT    1057L
#define ERROR_SERVICE_DISABLED           1058L
#define ERROR_CIRCULAR_DEPENDENCY        1059L
#define ERROR_SERVICE_DOES_NOT_EXIST     1060L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL 1061L
#define ERROR_SERVICE_NOT_ACTIVE         1062L
#define ERROR_FAILED_SERVICE_CONTROLLER_CONNECT 1063L
#define ERROR_EXCEPTION_IN_SERVICE       1064L
#define ERROR_DATABASE_DOES_NOT_EXIST    1065L
#define ERROR_SERVICE_SPECIFIC_ERROR     1066L
#define ERROR_PROCESS_ABORTED            1067L
#define ERROR_SERVICE_DEPENDENCY_FAIL    1068L
#define ERROR_SERVICE_LOGON_FAILED       1069L
#define ERROR_SERVICE_START_HANG         1070L
#define ERROR_INVALID_SERVICE_LOCK       1071L
#define ERROR_SERVICE_MARKED_FOR_DELETE  1072L
#define ERROR_SERVICE_EXISTS             1073L
#define ERROR_ALREADY_RUNNING_LKG        1074L
#define ERROR_SERVICE_DEPENDENCY_DELETED 1075L
#define ERROR_BOOT_ALREADY_ACCEPTED      1076L
#define ERROR_SERVICE_NEVER_STARTED      1077L
#define ERROR_DUPLICATE_SERVICE_NAME     1078L
#define ERROR_DIFFERENT_SERVICE_ACCOUNT  1079L
#define ERROR_CANNOT_DETECT_DRIVER_FAILURE 1080L
#define ERROR_CANNOT_DETECT_PROCESS_ABORT 1081L
#define ERROR_NO_RECOVERY_PROGRAM        1082L
#define ERROR_SERVICE_NOT_IN_EXE         1083L
#define ERROR_NOT_SAFEBOOT_SERVICE       1084L
#define ERROR_END_OF_MEDIA               1100L
#define ERROR_FILEMARK_DETECTED          1101L
#define ERROR_BEGINNING_OF_MEDIA         1102L
#define ERROR_SETMARK_DETECTED           1103L
#define ERROR_NO_DATA_DETECTED           1104L
#define ERROR_PARTITION_FAILURE          1105L
#define ERROR_INVALID_BLOCK_LENGTH       1106L
#define ERROR_DEVICE_NOT_PARTITIONED     1107L
#define ERROR_UNABLE_TO_LOCK_MEDIA       1108L
#define ERROR_UNABLE_TO_UNLOAD_MEDIA     1109L
#define ERROR_MEDIA_CHANGED              1110L
#define ERROR_BUS_RESET                  1111L
#define ERROR_NO_MEDIA_IN_DRIVE          1112L
#define ERROR_NO_UNICODE_TRANSLATION     1113L
#define ERROR_DLL_INIT_FAILED            1114L
#define ERROR_SHUTDOWN_IN_PROGRESS       1115L
#define ERROR_NO_SHUTDOWN_IN_PROGRESS    1116L
#define ERROR_IO_DEVICE                  1117L
#define ERROR_SERIAL_NO_DEVICE           1118L
#define ERROR_IRQ_BUSY                   1119L
#define ERROR_MORE_WRITES                1120L
#define ERROR_COUNTER_TIMEOUT            1121L
#define ERROR_FLOPPY_ID_MARK_NOT_FOUND   1122L
#define ERROR_FLOPPY_WRONG_CYLINDER      1123L
#define ERROR_FLOPPY_UNKNOWN_ERROR       1124L
#define ERROR_FLOPPY_BAD_REGISTERS       1125L
#define ERROR_DISK_RECALIBRATE_FAILED    1126L
#define ERROR_DISK_OPERATION_FAILED      1127L
#define ERROR_DISK_RESET_FAILED          1128L
#define ERROR_EOM_OVERFLOW               1129L
#define ERROR_NOT_ENOUGH_SERVER_MEMORY   1130L
#define ERROR_POSSIBLE_DEADLOCK          1131L
#define ERROR_MAPPED_ALIGNMENT           1132L
#define ERROR_SET_POWER_STATE_VETOED     1140L
#define ERROR_SET_POWER_STATE_FAILED     1141L
#define ERROR_TOO_MANY_LINKS             1142L
#define ERROR_OLD_WIN_VERSION            1150L
#define ERROR_APP_WRONG_OS               1151L
#define ERROR_SINGLE_INSTANCE_APP        1152L
#define ERROR_RMODE_APP                  1153L
#define ERROR_INVALID_DLL                1154L
#define ERROR_NO_ASSOCIATION             1155L
#define ERROR_DDE_FAIL                   1156L
#define ERROR_DLL_NOT_FOUND              1157L
#define ERROR_NO_MORE_USER_HANDLES       1158L
#define ERROR_MESSAGE_SYNC_ONLY          1159L
#define ERROR_SOURCE_ELEMENT_EMPTY       1160L
#define ERROR_DESTINATION_ELEMENT_FULL   1161L
#define ERROR_ILLEGAL_ELEMENT_ADDRESS    1162L
#define ERROR_MAGAZINE_NOT_PRESENT       1163L
#define ERROR_DEVICE_REINITIALIZATION_NEEDED 1164L    // dderror
#define ERROR_DEVICE_REQUIRES_CLEANING   1165L
#define ERROR_DEVICE_DOOR_OPEN           1166L
#define ERROR_DEVICE_NOT_CONNECTED       1167L
#define ERROR_NOT_FOUND                  1168L
#define ERROR_NO_MATCH                   1169L
#define ERROR_SET_NOT_FOUND              1170L
#define ERROR_POINT_NOT_FOUND            1171L
#define ERROR_NO_TRACKING_SERVICE        1172L
#define ERROR_NO_VOLUME_ID               1173L
#define ERROR_UNABLE_TO_REMOVE_REPLACED  1175L
#define ERROR_UNABLE_TO_MOVE_REPLACEMENT 1176L
#define ERROR_UNABLE_TO_MOVE_REPLACEMENT_2 1177L
#define ERROR_JOURNAL_DELETE_IN_PROGRESS 1178L
#define ERROR_JOURNAL_NOT_ACTIVE         1179L
#define ERROR_POTENTIAL_FILE_FOUND       1180L
#define ERROR_JOURNAL_ENTRY_DELETED      1181L
#define ERROR_SHUTDOWN_IS_SCHEDULED      1190L
#define ERROR_SHUTDOWN_USERS_LOGGED_ON   1191L
#define ERROR_BAD_DEVICE                 1200L
#define ERROR_CONNECTION_UNAVAIL         1201L
#define ERROR_DEVICE_ALREADY_REMEMBERED  1202L
#define ERROR_NO_NET_OR_BAD_PATH         1203L
#define ERROR_BAD_PROVIDER               1204L
#define ERROR_CANNOT_OPEN_PROFILE        1205L
#define ERROR_BAD_PROFILE                1206L
#define ERROR_NOT_CONTAINER              1207L
#define ERROR_EXTENDED_ERROR             1208L
#define ERROR_INVALID_GROUPNAME          1209L
#define ERROR_INVALID_COMPUTERNAME       1210L
#define ERROR_INVALID_EVENTNAME          1211L
#define ERROR_INVALID_DOMAINNAME         1212L
#define ERROR_INVALID_SERVICENAME        1213L
#define ERROR_INVALID_NETNAME            1214L
#define ERROR_INVALID_SHARENAME          1215L
#define ERROR_INVALID_PASSWORDNAME       1216L
#define ERROR_INVALID_MESSAGENAME        1217L
#define ERROR_INVALID_MESSAGEDEST        1218L
#define ERROR_SESSION_CREDENTIAL_CONFLICT 1219L
#define ERROR_REMOTE_SESSION_LIMIT_EXCEEDED 1220L
#define ERROR_DUP_DOMAINNAME             1221L
#define ERROR_NO_NETWORK                 1222L
#define ERROR_CANCELLED                  1223L
#define ERROR_USER_MAPPED_FILE           1224L
#define ERROR_CONNECTION_REFUSED         1225L
#define ERROR_GRACEFUL_DISCONNECT        1226L
#define ERROR_ADDRESS_ALREADY_ASSOCIATED 1227L
#define ERROR_ADDRESS_NOT_ASSOCIATED     1228L
#define ERROR_CONNECTION_INVALID         1229L
#define ERROR_CONNECTION_ACTIVE          1230L
#define ERROR_NETWORK_UNREACHABLE        1231L
#define ERROR_HOST_UNREACHABLE           1232L
#define ERROR_PROTOCOL_UNREACHABLE       1233L
#define ERROR_PORT_UNREACHABLE           1234L
#define ERROR_REQUEST_ABORTED            1235L
#define ERROR_CONNECTION_ABORTED         1236L
#define ERROR_RETRY                      1237L
#define ERROR_CONNECTION_COUNT_LIMIT     1238L
#define ERROR_LOGIN_TIME_RESTRICTION     1239L
#define ERROR_LOGIN_WKSTA_RESTRICTION    1240L
#define ERROR_INCORRECT_ADDRESS          1241L
#define ERROR_ALREADY_REGISTERED         1242L
#define ERROR_SERVICE_NOT_FOUND          1243L
#define ERROR_NOT_AUTHENTICATED          1244L
#define ERROR_NOT_LOGGED_ON              1245L
#define ERROR_CONTINUE                   1246L    // dderror
#define ERROR_ALREADY_INITIALIZED        1247L
#define ERROR_NO_MORE_DEVICES            1248L    // dderror
#define ERROR_NO_SUCH_SITE               1249L
#define ERROR_DOMAIN_CONTROLLER_EXISTS   1250L
#define ERROR_ONLY_IF_CONNECTED          1251L
#define ERROR_OVERRIDE_NOCHANGES         1252L
#define ERROR_BAD_USER_PROFILE           1253L
#define ERROR_NOT_SUPPORTED_ON_SBS       1254L
#define ERROR_SERVER_SHUTDOWN_IN_PROGRESS 1255L
#define ERROR_HOST_DOWN                  1256L
#define ERROR_NON_ACCOUNT_SID            1257L
#define ERROR_NON_DOMAIN_SID             1258L
#define ERROR_APPHELP_BLOCK              1259L
#define ERROR_ACCESS_DISABLED_BY_POLICY  1260L
#define ERROR_REG_NAT_CONSUMPTION        1261L
#define ERROR_CSCSHARE_OFFLINE           1262L
#define ERROR_PKINIT_FAILURE             1263L
#define ERROR_SMARTCARD_SUBSYSTEM_FAILURE 1264L
#define ERROR_DOWNGRADE_DETECTED         1265L
#define ERROR_MACHINE_LOCKED             1271L
#define ERROR_SMB_GUEST_LOGON_BLOCKED    1272L
#define ERROR_CALLBACK_SUPPLIED_INVALID_DATA 1273L
#define ERROR_SYNC_FOREGROUND_REFRESH_REQUIRED 1274L
#define ERROR_DRIVER_BLOCKED             1275L
#define ERROR_INVALID_IMPORT_OF_NON_DLL  1276L
#define ERROR_ACCESS_DISABLED_WEBBLADE   1277L
#define ERROR_ACCESS_DISABLED_WEBBLADE_TAMPER 1278L
#define ERROR_RECOVERY_FAILURE           1279L
#define ERROR_ALREADY_FIBER              1280L
#define ERROR_ALREADY_THREAD             1281L
#define ERROR_STACK_BUFFER_OVERRUN       1282L
#define ERROR_PARAMETER_QUOTA_EXCEEDED   1283L
#define ERROR_DEBUGGER_INACTIVE          1284L
#define ERROR_DELAY_LOAD_FAILED          1285L
#define ERROR_VDM_DISALLOWED             1286L
#define ERROR_UNIDENTIFIED_ERROR         1287L
#define ERROR_INVALID_CRUNTIME_PARAMETER 1288L
#define ERROR_BEYOND_VDL                 1289L
#define ERROR_INCOMPATIBLE_SERVICE_SID_TYPE 1290L
#define ERROR_DRIVER_PROCESS_TERMINATED  1291L
#define ERROR_IMPLEMENTATION_LIMIT       1292L
#define ERROR_PROCESS_IS_PROTECTED       1293L
#define ERROR_SERVICE_NOTIFY_CLIENT_LAGGING 1294L
#define ERROR_DISK_QUOTA_EXCEEDED        1295L
#define ERROR_CONTENT_BLOCKED            1296L
#define ERROR_INCOMPATIBLE_SERVICE_PRIVILEGE 1297L
#define ERROR_APP_HANG                   1298L
#define ERROR_INVALID_LABEL              1299L
#define ERROR_NOT_ALL_ASSIGNED           1300L
#define ERROR_SOME_NOT_MAPPED            1301L
#define ERROR_NO_QUOTAS_FOR_ACCOUNT      1302L
#define ERROR_LOCAL_USER_SESSION_KEY     1303L
#define ERROR_NULL_LM_PASSWORD           1304L
#define ERROR_UNKNOWN_REVISION           1305L
#define ERROR_REVISION_MISMATCH          1306L
#define ERROR_INVALID_OWNER              1307L
#define ERROR_INVALID_PRIMARY_GROUP      1308L
#define ERROR_NO_IMPERSONATION_TOKEN     1309L
#define ERROR_CANT_DISABLE_MANDATORY     1310L
#define ERROR_NO_LOGON_SERVERS           1311L
#define ERROR_NO_SUCH_LOGON_SESSION      1312L
#define ERROR_NO_SUCH_PRIVILEGE          1313L
#define ERROR_PRIVILEGE_NOT_HELD         1314L
#define ERROR_INVALID_ACCOUNT_NAME       1315L
#define ERROR_USER_EXISTS                1316L
#define ERROR_NO_SUCH_USER               1317L
#define ERROR_GROUP_EXISTS               1318L
#define ERROR_NO_SUCH_GROUP              1319L
#define ERROR_MEMBER_IN_GROUP            1320L
#define ERROR_MEMBER_NOT_IN_GROUP        1321L
#define ERROR_LAST_ADMIN                 1322L
#define ERROR_WRONG_PASSWORD             1323L
#define ERROR_ILL_FORMED_PASSWORD        1324L
#define ERROR_PASSWORD_RESTRICTION       1325L
#define ERROR_LOGON_FAILURE              1326L
#define ERROR_ACCOUNT_RESTRICTION        1327L
#define ERROR_INVALID_LOGON_HOURS        1328L
#define ERROR_INVALID_WORKSTATION        1329L
#define ERROR_PASSWORD_EXPIRED           1330L
#define ERROR_ACCOUNT_DISABLED           1331L
#define ERROR_NONE_MAPPED                1332L
#define ERROR_TOO_MANY_LUIDS_REQUESTED   1333L
#define ERROR_LUIDS_EXHAUSTED            1334L
#define ERROR_INVALID_SUB_AUTHORITY      1335L
#define ERROR_INVALID_ACL                1336L
#define ERROR_INVALID_SID                1337L
#define ERROR_INVALID_SECURITY_DESCR     1338L
#define ERROR_BAD_INHERITANCE_ACL        1340L
#define ERROR_SERVER_DISABLED            1341L
#define ERROR_SERVER_NOT_DISABLED        1342L
#define ERROR_INVALID_ID_AUTHORITY       1343L
#define ERROR_ALLOTTED_SPACE_EXCEEDED    1344L
#define ERROR_INVALID_GROUP_ATTRIBUTES   1345L
#define ERROR_BAD_IMPERSONATION_LEVEL    1346L
#define ERROR_CANT_OPEN_ANONYMOUS        1347L
#define ERROR_BAD_VALIDATION_CLASS       1348L
#define ERROR_BAD_TOKEN_TYPE             1349L
#define ERROR_NO_SECURITY_ON_OBJECT      1350L
#define ERROR_CANT_ACCESS_DOMAIN_INFO    1351L
#define ERROR_INVALID_SERVER_STATE       1352L
#define ERROR_INVALID_DOMAIN_STATE       1353L
#define ERROR_INVALID_DOMAIN_ROLE        1354L
#define ERROR_NO_SUCH_DOMAIN             1355L
#define ERROR_DOMAIN_EXISTS              1356L
#define ERROR_DOMAIN_LIMIT_EXCEEDED      1357L
#define ERROR_INTERNAL_DB_CORRUPTION     1358L
#define ERROR_INTERNAL_ERROR             1359L
#define ERROR_GENERIC_NOT_MAPPED         1360L
#define ERROR_BAD_DESCRIPTOR_FORMAT      1361L
#define ERROR_NOT_LOGON_PROCESS          1362L
#define ERROR_LOGON_SESSION_EXISTS       1363L
#define ERROR_NO_SUCH_PACKAGE            1364L
#define ERROR_BAD_LOGON_SESSION_STATE    1365L
#define ERROR_LOGON_SESSION_COLLISION    1366L
#define ERROR_INVALID_LOGON_TYPE         1367L
#define ERROR_CANNOT_IMPERSONATE         1368L
#define ERROR_RXACT_INVALID_STATE        1369L
#define ERROR_RXACT_COMMIT_FAILURE       1370L
#define ERROR_SPECIAL_ACCOUNT            1371L
#define ERROR_SPECIAL_GROUP              1372L
#define ERROR_SPECIAL_USER               1373L
#define ERROR_MEMBERS_PRIMARY_GROUP      1374L
#define ERROR_TOKEN_ALREADY_IN_USE       1375L
#define ERROR_NO_SUCH_ALIAS              1376L
#define ERROR_MEMBER_NOT_IN_ALIAS        1377L
#define ERROR_MEMBER_IN_ALIAS            1378L
#define ERROR_ALIAS_EXISTS               1379L
#define ERROR_LOGON_NOT_GRANTED          1380L
#define ERROR_TOO_MANY_SECRETS           1381L
#define ERROR_SECRET_TOO_LONG            1382L
#define ERROR_INTERNAL_DB_ERROR          1383L
#define ERROR_TOO_MANY_CONTEXT_IDS       1384L
#define ERROR_LOGON_TYPE_NOT_GRANTED     1385L
#define ERROR_NT_CROSS_ENCRYPTION_REQUIRED 1386L
#define ERROR_NO_SUCH_MEMBER             1387L
#define ERROR_INVALID_MEMBER             1388L
#define ERROR_TOO_MANY_SIDS              1389L
#define ERROR_LM_CROSS_ENCRYPTION_REQUIRED 1390L
#define ERROR_NO_INHERITANCE             1391L
#define ERROR_FILE_CORRUPT               1392L
#define ERROR_DISK_CORRUPT               1393L
#define ERROR_NO_USER_SESSION_KEY        1394L
#define ERROR_LICENSE_QUOTA_EXCEEDED     1395L
#define ERROR_WRONG_TARGET_NAME          1396L
#define ERROR_MUTUAL_AUTH_FAILED         1397L
#define ERROR_TIME_SKEW                  1398L
#define ERROR_CURRENT_DOMAIN_NOT_ALLOWED 1399L
#define ERROR_INVALID_WINDOW_HANDLE      1400L
#define ERROR_INVALID_MENU_HANDLE        1401L
#define ERROR_INVALID_CURSOR_HANDLE      1402L
#define ERROR_INVALID_ACCEL_HANDLE       1403L
#define ERROR_INVALID_HOOK_HANDLE        1404L
#define ERROR_INVALID_DWP_HANDLE         1405L
#define ERROR_TLW_WITH_WSCHILD           1406L
#define ERROR_CANNOT_FIND_WND_CLASS      1407L
#define ERROR_WINDOW_OF_OTHER_THREAD     1408L
#define ERROR_HOTKEY_ALREADY_REGISTERED  1409L
#define ERROR_CLASS_ALREADY_EXISTS       1410L
#define ERROR_CLASS_DOES_NOT_EXIST       1411L
#define ERROR_CLASS_HAS_WINDOWS          1412L
#define ERROR_INVALID_INDEX              1413L
#define ERROR_INVALID_ICON_HANDLE        1414L
#define ERROR_PRIVATE_DIALOG_INDEX       1415L
#define ERROR_LISTBOX_ID_NOT_FOUND       1416L
#define ERROR_NO_WILDCARD_CHARACTERS     1417L
#define ERROR_CLIPBOARD_NOT_OPEN         1418L
#define ERROR_HOTKEY_NOT_REGISTERED      1419L
#define ERROR_WINDOW_NOT_DIALOG          1420L
#define ERROR_CONTROL_ID_NOT_FOUND       1421L
#define ERROR_INVALID_COMBOBOX_MESSAGE   1422L
#define ERROR_WINDOW_NOT_COMBOBOX        1423L
#define ERROR_INVALID_EDIT_HEIGHT        1424L
#define ERROR_DC_NOT_FOUND               1425L
#define ERROR_INVALID_HOOK_FILTER        1426L
#define ERROR_INVALID_FILTER_PROC        1427L
#define ERROR_HOOK_NEEDS_HMOD            1428L
#define ERROR_GLOBAL_ONLY_HOOK           1429L
#define ERROR_JOURNAL_HOOK_SET           1430L
#define ERROR_HOOK_NOT_INSTALLED         1431L
#define ERROR_INVALID_LB_MESSAGE         1432L
#define ERROR_SETCOUNT_ON_BAD_LB         1433L
#define ERROR_LB_WITHOUT_TABSTOPS        1434L
#define ERROR_DESTROY_OBJECT_OF_OTHER_THREAD 1435L
#define ERROR_CHILD_WINDOW_MENU          1436L
#define ERROR_NO_SYSTEM_MENU             1437L
#define ERROR_INVALID_MSGBOX_STYLE       1438L
#define ERROR_INVALID_SPI_VALUE          1439L
#define ERROR_SCREEN_ALREADY_LOCKED      1440L
#define ERROR_HWNDS_HAVE_DIFF_PARENT     1441L
#define ERROR_NOT_CHILD_WINDOW           1442L
#define ERROR_INVALID_GW_COMMAND         1443L
#define ERROR_INVALID_THREAD_ID          1444L
#define ERROR_NON_MDICHILD_WINDOW        1445L
#define ERROR_POPUP_ALREADY_ACTIVE       1446L
#define ERROR_NO_SCROLLBARS              1447L
#define ERROR_INVALID_SCROLLBAR_RANGE    1448L
#define ERROR_INVALID_SHOWWIN_COMMAND    1449L
#define ERROR_NO_SYSTEM_RESOURCES        1450L
#define ERROR_NONPAGED_SYSTEM_RESOURCES  1451L
#define ERROR_PAGED_SYSTEM_RESOURCES     1452L
#define ERROR_WORKING_SET_QUOTA          1453L
#define ERROR_PAGEFILE_QUOTA             1454L
#define ERROR_COMMITMENT_LIMIT           1455L
#define ERROR_MENU_ITEM_NOT_FOUND        1456L
#define ERROR_INVALID_KEYBOARD_HANDLE    1457L
#define ERROR_HOOK_TYPE_NOT_ALLOWED      1458L
#define ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION 1459L
#define ERROR_TIMEOUT                    1460L
#define ERROR_INVALID_MONITOR_HANDLE     1461L
#define ERROR_INCORRECT_SIZE             1462L
#define ERROR_SYMLINK_CLASS_DISABLED     1463L
#define ERROR_SYMLINK_NOT_SUPPORTED      1464L
#define ERROR_XML_PARSE_ERROR            1465L
#define ERROR_XMLDSIG_ERROR              1466L
#define ERROR_RESTART_APPLICATION        1467L
#define ERROR_WRONG_COMPARTMENT          1468L
#define ERROR_AUTHIP_FAILURE             1469L
#define ERROR_NO_NVRAM_RESOURCES         1470L
#define ERROR_NOT_GUI_PROCESS            1471L
#define ERROR_EVENTLOG_FILE_CORRUPT      1500L
#define ERROR_EVENTLOG_CANT_START        1501L
#define ERROR_LOG_FILE_FULL              1502L
#define ERROR_EVENTLOG_FILE_CHANGED      1503L
#define ERROR_CONTAINER_ASSIGNED         1504L
#define ERROR_JOB_NO_CONTAINER           1505L
#define ERROR_INVALID_TASK_NAME          1550L
#define ERROR_INVALID_TASK_INDEX         1551L
#define ERROR_THREAD_ALREADY_IN_TASK     1552L
#define ERROR_INSTALL_SERVICE_FAILURE    1601L
#define ERROR_INSTALL_USEREXIT           1602L
#define ERROR_INSTALL_FAILURE            1603L
#define ERROR_INSTALL_SUSPEND            1604L
#define ERROR_UNKNOWN_PRODUCT            1605L
#define ERROR_UNKNOWN_FEATURE            1606L
#define ERROR_UNKNOWN_COMPONENT          1607L
#define ERROR_UNKNOWN_PROPERTY           1608L
#define ERROR_INVALID_HANDLE_STATE       1609L
#define ERROR_BAD_CONFIGURATION          1610L
#define ERROR_INDEX_ABSENT               1611L
#define ERROR_INSTALL_SOURCE_ABSENT      1612L
#define ERROR_INSTALL_PACKAGE_VERSION    1613L
#define ERROR_PRODUCT_UNINSTALLED        1614L
#define ERROR_BAD_QUERY_SYNTAX           1615L
#define ERROR_INVALID_FIELD              1616L
#define ERROR_DEVICE_REMOVED             1617L
#define ERROR_INSTALL_ALREADY_RUNNING    1618L
#define ERROR_INSTALL_PACKAGE_OPEN_FAILED 1619L
#define ERROR_INSTALL_PACKAGE_INVALID    1620L
#define ERROR_INSTALL_UI_FAILURE         1621L
#define ERROR_INSTALL_LOG_FAILURE        1622L
#define ERROR_INSTALL_LANGUAGE_UNSUPPORTED 1623L
#define ERROR_INSTALL_TRANSFORM_FAILURE  1624L
#define ERROR_INSTALL_PACKAGE_REJECTED   1625L
#define ERROR_FUNCTION_NOT_CALLED        1626L
#define ERROR_FUNCTION_FAILED            1627L
#define ERROR_INVALID_TABLE              1628L
#define ERROR_DATATYPE_MISMATCH          1629L
#define ERROR_UNSUPPORTED_TYPE           1630L
#define ERROR_CREATE_FAILED              1631L
#define ERROR_INSTALL_TEMP_UNWRITABLE    1632L
#define ERROR_INSTALL_PLATFORM_UNSUPPORTED 1633L
#define ERROR_INSTALL_NOTUSED            1634L
#define ERROR_PATCH_PACKAGE_OPEN_FAILED  1635L
#define ERROR_PATCH_PACKAGE_INVALID      1636L
#define ERROR_PATCH_PACKAGE_UNSUPPORTED  1637L
#define ERROR_PRODUCT_VERSION            1638L
#define ERROR_INVALID_COMMAND_LINE       1639L
#define ERROR_INSTALL_REMOTE_DISALLOWED  1640L
#define ERROR_SUCCESS_REBOOT_INITIATED   1641L
#define ERROR_PATCH_TARGET_NOT_FOUND     1642L
#define ERROR_PATCH_PACKAGE_REJECTED     1643L
#define ERROR_INSTALL_TRANSFORM_REJECTED 1644L
#define ERROR_INSTALL_REMOTE_PROHIBITED  1645L
#define ERROR_PATCH_REMOVAL_UNSUPPORTED  1646L
#define ERROR_UNKNOWN_PATCH              1647L
#define ERROR_PATCH_NO_SEQUENCE          1648L
#define ERROR_PATCH_REMOVAL_DISALLOWED   1649L
#define ERROR_INVALID_PATCH_XML          1650L
#define ERROR_PATCH_MANAGED_ADVERTISED_PRODUCT 1651L
#define ERROR_INSTALL_SERVICE_SAFEBOOT   1652L
#define ERROR_FAIL_FAST_EXCEPTION        1653L
#define ERROR_INSTALL_REJECTED           1654L
#define ERROR_DYNAMIC_CODE_BLOCKED       1655L
#define ERROR_NOT_SAME_OBJECT            1656L
#define RPC_S_INVALID_STRING_BINDING     1700L
#define RPC_S_WRONG_KIND_OF_BINDING      1701L
#define RPC_S_INVALID_BINDING            1702L
#define RPC_S_PROTSEQ_NOT_SUPPORTED      1703L
#define RPC_S_INVALID_RPC_PROTSEQ        1704L
#define RPC_S_INVALID_STRING_UUID        1705L
#define RPC_S_INVALID_ENDPOINT_FORMAT    1706L
#define RPC_S_INVALID_NET_ADDR           1707L
#define RPC_S_NO_ENDPOINT_FOUND          1708L
#define RPC_S_INVALID_TIMEOUT            1709L
#define RPC_S_OBJECT_NOT_FOUND           1710L
#define RPC_S_ALREADY_REGISTERED         1711L
#define RPC_S_TYPE_ALREADY_REGISTERED    1712L
#define RPC_S_ALREADY_LISTENING          1713L
#define RPC_S_NO_PROTSEQS_REGISTERED     1714L
#define RPC_S_NOT_LISTENING              1715L
#define RPC_S_UNKNOWN_MGR_TYPE           1716L
#define RPC_S_UNKNOWN_IF                 1717L
#define RPC_S_NO_BINDINGS                1718L
#define RPC_S_NO_PROTSEQS                1719L
#define RPC_S_CANT_CREATE_ENDPOINT       1720L
#define RPC_S_OUT_OF_RESOURCES           1721L
#define RPC_S_SERVER_UNAVAILABLE         1722L
#define RPC_S_SERVER_TOO_BUSY            1723L
#define RPC_S_INVALID_NETWORK_OPTIONS    1724L
#define RPC_S_NO_CALL_ACTIVE             1725L
#define RPC_S_CALL_FAILED                1726L
#define RPC_S_CALL_FAILED_DNE            1727L
#define RPC_S_PROTOCOL_ERROR             1728L
#define RPC_S_PROXY_ACCESS_DENIED        1729L
#define RPC_S_UNSUPPORTED_TRANS_SYN      1730L
#define RPC_S_UNSUPPORTED_TYPE           1732L
#define RPC_S_INVALID_TAG                1733L
#define RPC_S_INVALID_BOUND              1734L
#define RPC_S_NO_ENTRY_NAME              1735L
#define RPC_S_INVALID_NAME_SYNTAX        1736L
#define RPC_S_UNSUPPORTED_NAME_SYNTAX    1737L
#define RPC_S_UUID_NO_ADDRESS            1739L
#define RPC_S_DUPLICATE_ENDPOINT         1740L
#define RPC_S_UNKNOWN_AUTHN_TYPE         1741L
#define RPC_S_MAX_CALLS_TOO_SMALL        1742L
#define RPC_S_STRING_TOO_LONG            1743L
#define RPC_S_PROTSEQ_NOT_FOUND          1744L
#define RPC_S_PROCNUM_OUT_OF_RANGE       1745L
#define RPC_S_BINDING_HAS_NO_AUTH        1746L
#define RPC_S_UNKNOWN_AUTHN_SERVICE      1747L
#define RPC_S_UNKNOWN_AUTHN_LEVEL        1748L
#define RPC_S_INVALID_AUTH_IDENTITY      1749L
#define RPC_S_UNKNOWN_AUTHZ_SERVICE      1750L
#define EPT_S_INVALID_ENTRY              1751L
#define EPT_S_CANT_PERFORM_OP            1752L
#define EPT_S_NOT_REGISTERED             1753L
#define RPC_S_NOTHING_TO_EXPORT          1754L
#define RPC_S_INCOMPLETE_NAME            1755L
#define RPC_S_INVALID_VERS_OPTION        1756L
#define RPC_S_NO_MORE_MEMBERS            1757L
#define RPC_S_NOT_ALL_OBJS_UNEXPORTED    1758L
#define RPC_S_INTERFACE_NOT_FOUND        1759L
#define RPC_S_ENTRY_ALREADY_EXISTS       1760L
#define RPC_S_ENTRY_NOT_FOUND            1761L
#define RPC_S_NAME_SERVICE_UNAVAILABLE   1762L
#define RPC_S_INVALID_NAF_ID             1763L
#define RPC_S_CANNOT_SUPPORT             1764L
#define RPC_S_NO_CONTEXT_AVAILABLE       1765L
#define RPC_S_INTERNAL_ERROR             1766L
#define RPC_S_ZERO_DIVIDE                1767L
#define RPC_S_ADDRESS_ERROR              1768L
#define RPC_S_FP_DIV_ZERO                1769L
#define RPC_S_FP_UNDERFLOW               1770L
#define RPC_S_FP_OVERFLOW                1771L
#define RPC_X_NO_MORE_ENTRIES            1772L
#define RPC_X_SS_CHAR_TRANS_OPEN_FAIL    1773L
#define RPC_X_SS_CHAR_TRANS_SHORT_FILE   1774L
#define RPC_X_SS_IN_NULL_CONTEXT         1775L
#define RPC_X_SS_CONTEXT_DAMAGED         1777L
#define RPC_X_SS_HANDLES_MISMATCH        1778L
#define RPC_X_SS_CANNOT_GET_CALL_HANDLE  1779L
#define RPC_X_NULL_REF_POINTER           1780L
#define RPC_X_ENUM_VALUE_OUT_OF_RANGE    1781L
#define RPC_X_BYTE_COUNT_TOO_SMALL       1782L
#define RPC_X_BAD_STUB_DATA              1783L
#define ERROR_INVALID_USER_BUFFER        1784L
#define ERROR_UNRECOGNIZED_MEDIA         1785L
#define ERROR_NO_TRUST_LSA_SECRET        1786L
#define ERROR_NO_TRUST_SAM_ACCOUNT       1787L
#define ERROR_TRUSTED_DOMAIN_FAILURE     1788L
#define ERROR_TRUSTED_RELATIONSHIP_FAILURE 1789L
#define ERROR_TRUST_FAILURE              1790L
#define RPC_S_CALL_IN_PROGRESS           1791L
#define ERROR_NETLOGON_NOT_STARTED       1792L
#define ERROR_ACCOUNT_EXPIRED            1793L
#define ERROR_REDIRECTOR_HAS_OPEN_HANDLES 1794L
#define ERROR_PRINTER_DRIVER_ALREADY_INSTALLED 1795L
#define ERROR_UNKNOWN_PORT               1796L
#define ERROR_UNKNOWN_PRINTER_DRIVER     1797L
#define ERROR_UNKNOWN_PRINTPROCESSOR     1798L
#define ERROR_INVALID_SEPARATOR_FILE     1799L
#define ERROR_INVALID_PRIORITY           1800L
#define ERROR_INVALID_PRINTER_NAME       1801L
#define ERROR_PRINTER_ALREADY_EXISTS     1802L
#define ERROR_INVALID_PRINTER_COMMAND    1803L
#define ERROR_INVALID_DATATYPE           1804L
#define ERROR_INVALID_ENVIRONMENT        1805L
#define RPC_S_NO_MORE_BINDINGS           1806L
#define ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT 1807L
#define ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT 1808L
#define ERROR_NOLOGON_SERVER_TRUST_ACCOUNT 1809L
#define ERROR_DOMAIN_TRUST_INCONSISTENT  1810L
#define ERROR_SERVER_HAS_OPEN_HANDLES    1811L
#define ERROR_RESOURCE_DATA_NOT_FOUND    1812L
#define ERROR_RESOURCE_TYPE_NOT_FOUND    1813L
#define ERROR_RESOURCE_NAME_NOT_FOUND    1814L
#define ERROR_RESOURCE_LANG_NOT_FOUND    1815L
#define ERROR_NOT_ENOUGH_QUOTA           1816L
#define RPC_S_NO_INTERFACES              1817L
#define RPC_S_CALL_CANCELLED             1818L
#define RPC_S_BINDING_INCOMPLETE         1819L
#define RPC_S_COMM_FAILURE               1820L
#define RPC_S_UNSUPPORTED_AUTHN_LEVEL    1821L
#define RPC_S_NO_PRINC_NAME              1822L
#define RPC_S_NOT_RPC_ERROR              1823L
#define RPC_S_UUID_LOCAL_ONLY            1824L
#define RPC_S_SEC_PKG_ERROR              1825L
#define RPC_S_NOT_CANCELLED              1826L
#define RPC_X_INVALID_ES_ACTION          1827L
#define RPC_X_WRONG_ES_VERSION           1828L
#define RPC_X_WRONG_STUB_VERSION         1829L
#define RPC_X_INVALID_PIPE_OBJECT        1830L
#define RPC_X_WRONG_PIPE_ORDER           1831L
#define RPC_X_WRONG_PIPE_VERSION         1832L
#define RPC_S_COOKIE_AUTH_FAILED         1833L
#define RPC_S_DO_NOT_DISTURB             1834L
#define RPC_S_SYSTEM_HANDLE_COUNT_EXCEEDED 1835L
#define RPC_S_SYSTEM_HANDLE_TYPE_MISMATCH 1836L
#define RPC_S_GROUP_MEMBER_NOT_FOUND     1898L
#define EPT_S_CANT_CREATE                1899L
#define RPC_S_INVALID_OBJECT             1900L
#define ERROR_INVALID_TIME               1901L
#define ERROR_INVALID_FORM_NAME          1902L
#define ERROR_INVALID_FORM_SIZE          1903L
#define ERROR_ALREADY_WAITING            1904L
#define ERROR_PRINTER_DELETED            1905L
#define ERROR_INVALID_PRINTER_STATE      1906L
#define ERROR_PASSWORD_MUST_CHANGE       1907L
#define ERROR_DOMAIN_CONTROLLER_NOT_FOUND 1908L
#define ERROR_ACCOUNT_LOCKED_OUT         1909L
#define OR_INVALID_OXID                  1910L
#define OR_INVALID_OID                   1911L
#define OR_INVALID_SET                   1912L
#define RPC_S_SEND_INCOMPLETE            1913L
#define RPC_S_INVALID_ASYNC_HANDLE       1914L
#define RPC_S_INVALID_ASYNC_CALL         1915L
#define RPC_X_PIPE_CLOSED                1916L
#define RPC_X_PIPE_DISCIPLINE_ERROR      1917L
#define RPC_X_PIPE_EMPTY                 1918L
#define ERROR_NO_SITENAME                1919L
#define ERROR_CANT_ACCESS_FILE           1920L
#define ERROR_CANT_RESOLVE_FILENAME      1921L
#define RPC_S_ENTRY_TYPE_MISMATCH        1922L
#define RPC_S_NOT_ALL_OBJS_EXPORTED      1923L
#define RPC_S_INTERFACE_NOT_EXPORTED     1924L
#define RPC_S_PROFILE_NOT_ADDED          1925L
#define RPC_S_PRF_ELT_NOT_ADDED          1926L
#define RPC_S_PRF_ELT_NOT_REMOVED        1927L
#define RPC_S_GRP_ELT_NOT_ADDED          1928L
#define RPC_S_GRP_ELT_NOT_REMOVED        1929L
#define ERROR_KM_DRIVER_BLOCKED          1930L
#define ERROR_CONTEXT_EXPIRED            1931L
#define ERROR_PER_USER_TRUST_QUOTA_EXCEEDED 1932L
#define ERROR_ALL_USER_TRUST_QUOTA_EXCEEDED 1933L
#define ERROR_USER_DELETE_TRUST_QUOTA_EXCEEDED 1934L
#define ERROR_AUTHENTICATION_FIREWALL_FAILED 1935L
#define ERROR_REMOTE_PRINT_CONNECTIONS_BLOCKED 1936L
#define ERROR_NTLM_BLOCKED               1937L
#define ERROR_PASSWORD_CHANGE_REQUIRED   1938L
#define ERROR_INVALID_PIXEL_FORMAT       2000L
#define ERROR_BAD_DRIVER                 2001L
#define ERROR_INVALID_WINDOW_STYLE       2002L
#define ERROR_METAFILE_NOT_SUPPORTED     2003L
#define ERROR_TRANSFORM_NOT_SUPPORTED    2004L
#define ERROR_CLIPPING_NOT_SUPPORTED     2005L
#define ERROR_INVALID_CMM                2010L
#define ERROR_INVALID_PROFILE            2011L
#define ERROR_TAG_NOT_FOUND              2012L
#define ERROR_TAG_NOT_PRESENT            2013L
#define ERROR_DUPLICATE_TAG              2014L
#define ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE 2015L
#define ERROR_PROFILE_NOT_FOUND          2016L
#define ERROR_INVALID_COLORSPACE         2017L
#define ERROR_ICM_NOT_ENABLED            2018L
#define ERROR_DELETING_ICM_XFORM         2019L
#define ERROR_INVALID_TRANSFORM          2020L
#define ERROR_COLORSPACE_MISMATCH        2021L
#define ERROR_INVALID_COLORINDEX         2022L
#define ERROR_PROFILE_DOES_NOT_MATCH_DEVICE 2023L
#define ERROR_CONNECTED_OTHER_PASSWORD   2108L
#define ERROR_CONNECTED_OTHER_PASSWORD_DEFAULT 2109L
#define ERROR_BAD_USERNAME               2202L
#define ERROR_NOT_CONNECTED              2250L
#define ERROR_OPEN_FILES                 2401L
#define ERROR_ACTIVE_CONNECTIONS         2402L
#define ERROR_DEVICE_IN_USE              2404L
#define ERROR_UNKNOWN_PRINT_MONITOR      3000L
#define ERROR_PRINTER_DRIVER_IN_USE      3001L
#define ERROR_SPOOL_FILE_NOT_FOUND       3002L
#define ERROR_SPL_NO_STARTDOC            3003L
#define ERROR_SPL_NO_ADDJOB              3004L
#define ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED 3005L
#define ERROR_PRINT_MONITOR_ALREADY_INSTALLED 3006L
#define ERROR_INVALID_PRINT_MONITOR      3007L
#define ERROR_PRINT_MONITOR_IN_USE       3008L
#define ERROR_PRINTER_HAS_JOBS_QUEUED    3009L
#define ERROR_SUCCESS_REBOOT_REQUIRED    3010L
#define ERROR_SUCCESS_RESTART_REQUIRED   3011L
#define ERROR_PRINTER_NOT_FOUND          3012L
#define ERROR_PRINTER_DRIVER_WARNED      3013L
#define ERROR_PRINTER_DRIVER_BLOCKED     3014L
#define ERROR_PRINTER_DRIVER_PACKAGE_IN_USE 3015L
#define ERROR_CORE_DRIVER_PACKAGE_NOT_FOUND 3016L
#define ERROR_FAIL_REBOOT_REQUIRED       3017L
#define ERROR_FAIL_REBOOT_INITIATED      3018L
#define ERROR_PRINTER_DRIVER_DOWNLOAD_NEEDED 3019L
#define ERROR_PRINT_JOB_RESTART_REQUIRED 3020L
#define ERROR_INVALID_PRINTER_DRIVER_MANIFEST 3021L
#define ERROR_PRINTER_NOT_SHAREABLE      3022L
#define ERROR_REQUEST_PAUSED             3050L
#define ERROR_IO_REISSUE_AS_CACHED       3950L
#define ERROR_WINS_INTERNAL              4000L
#define ERROR_CAN_NOT_DEL_LOCAL_WINS     4001L
#define ERROR_STATIC_INIT                4002L
#define ERROR_INC_BACKUP                 4003L
#define ERROR_FULL_BACKUP                4004L
#define ERROR_REC_NON_EXISTENT           4005L
#define ERROR_RPL_NOT_ALLOWED            4006L
#define PEERDIST_ERROR_CONTENTINFO_VERSION_UNSUPPORTED 4050L
#define PEERDIST_ERROR_CANNOT_PARSE_CONTENTINFO 4051L
#define PEERDIST_ERROR_MISSING_DATA      4052L
#define PEERDIST_ERROR_NO_MORE           4053L
#define PEERDIST_ERROR_NOT_INITIALIZED   4054L
#define PEERDIST_ERROR_ALREADY_INITIALIZED 4055L
#define PEERDIST_ERROR_SHUTDOWN_IN_PROGRESS 4056L
#define PEERDIST_ERROR_INVALIDATED       4057L
#define PEERDIST_ERROR_ALREADY_EXISTS    4058L
#define PEERDIST_ERROR_OPERATION_NOTFOUND 4059L
#define PEERDIST_ERROR_ALREADY_COMPLETED 4060L
#define PEERDIST_ERROR_OUT_OF_BOUNDS     4061L
#define PEERDIST_ERROR_VERSION_UNSUPPORTED 4062L
#define PEERDIST_ERROR_INVALID_CONFIGURATION 4063L
#define PEERDIST_ERROR_NOT_LICENSED      4064L
#define PEERDIST_ERROR_SERVICE_UNAVAILABLE 4065L
#define PEERDIST_ERROR_TRUST_FAILURE     4066L
#define ERROR_DHCP_ADDRESS_CONFLICT      4100L
#define ERROR_WMI_GUID_NOT_FOUND         4200L
#define ERROR_WMI_INSTANCE_NOT_FOUND     4201L
#define ERROR_WMI_ITEMID_NOT_FOUND       4202L
#define ERROR_WMI_TRY_AGAIN              4203L
#define ERROR_WMI_DP_NOT_FOUND           4204L
#define ERROR_WMI_UNRESOLVED_INSTANCE_REF 4205L
#define ERROR_WMI_ALREADY_ENABLED        4206L
#define ERROR_WMI_GUID_DISCONNECTED      4207L
#define ERROR_WMI_SERVER_UNAVAILABLE     4208L
#define ERROR_WMI_DP_FAILED              4209L
#define ERROR_WMI_INVALID_MOF            4210L
#define ERROR_WMI_INVALID_REGINFO        4211L
#define ERROR_WMI_ALREADY_DISABLED       4212L
#define ERROR_WMI_READ_ONLY              4213L
#define ERROR_WMI_SET_FAILURE            4214L
#define ERROR_NOT_APPCONTAINER           4250L
#define ERROR_APPCONTAINER_REQUIRED      4251L
#define ERROR_NOT_SUPPORTED_IN_APPCONTAINER 4252L
#define ERROR_INVALID_PACKAGE_SID_LENGTH 4253L
#define ERROR_INVALID_MEDIA              4300L
#define ERROR_INVALID_LIBRARY            4301L
#define ERROR_INVALID_MEDIA_POOL         4302L
#define ERROR_DRIVE_MEDIA_MISMATCH       4303L
#define ERROR_MEDIA_OFFLINE              4304L
#define ERROR_LIBRARY_OFFLINE            4305L
#define ERROR_EMPTY                      4306L
#define ERROR_NOT_EMPTY                  4307L
#define ERROR_MEDIA_UNAVAILABLE          4308L
#define ERROR_RESOURCE_DISABLED          4309L
#define ERROR_INVALID_CLEANER            4310L
#define ERROR_UNABLE_TO_CLEAN            4311L
#define ERROR_OBJECT_NOT_FOUND           4312L
#define ERROR_DATABASE_FAILURE           4313L
#define ERROR_DATABASE_FULL              4314L
#define ERROR_MEDIA_INCOMPATIBLE         4315L
#define ERROR_RESOURCE_NOT_PRESENT       4316L
#define ERROR_INVALID_OPERATION          4317L
#define ERROR_MEDIA_NOT_AVAILABLE        4318L
#define ERROR_DEVICE_NOT_AVAILABLE       4319L
#define ERROR_REQUEST_REFUSED            4320L
#define ERROR_INVALID_DRIVE_OBJECT       4321L
#define ERROR_LIBRARY_FULL               4322L
#define ERROR_MEDIUM_NOT_ACCESSIBLE      4323L
#define ERROR_UNABLE_TO_LOAD_MEDIUM      4324L
#define ERROR_UNABLE_TO_INVENTORY_DRIVE  4325L
#define ERROR_UNABLE_TO_INVENTORY_SLOT   4326L
#define ERROR_UNABLE_TO_INVENTORY_TRANSPORT 4327L
#define ERROR_TRANSPORT_FULL             4328L
#define ERROR_CONTROLLING_IEPORT         4329L
#define ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA 4330L
#define ERROR_CLEANER_SLOT_SET           4331L
#define ERROR_CLEANER_SLOT_NOT_SET       4332L
#define ERROR_CLEANER_CARTRIDGE_SPENT    4333L
#define ERROR_UNEXPECTED_OMID            4334L
#define ERROR_CANT_DELETE_LAST_ITEM      4335L
#define ERROR_MESSAGE_EXCEEDS_MAX_SIZE   4336L
#define ERROR_VOLUME_CONTAINS_SYS_FILES  4337L
#define ERROR_INDIGENOUS_TYPE            4338L
#define ERROR_NO_SUPPORTING_DRIVES       4339L
#define ERROR_CLEANER_CARTRIDGE_INSTALLED 4340L
#define ERROR_IEPORT_FULL                4341L
#define ERROR_FILE_OFFLINE               4350L
#define ERROR_REMOTE_STORAGE_NOT_ACTIVE  4351L
#define ERROR_REMOTE_STORAGE_MEDIA_ERROR 4352L
#define ERROR_NOT_A_REPARSE_POINT        4390L
#define ERROR_REPARSE_ATTRIBUTE_CONFLICT 4391L
#define ERROR_INVALID_REPARSE_DATA       4392L
#define ERROR_REPARSE_TAG_INVALID        4393L
#define ERROR_REPARSE_TAG_MISMATCH       4394L
#define ERROR_REPARSE_POINT_ENCOUNTERED  4395L
#define ERROR_APP_DATA_NOT_FOUND         4400L
#define ERROR_APP_DATA_EXPIRED           4401L
#define ERROR_APP_DATA_CORRUPT           4402L
#define ERROR_APP_DATA_LIMIT_EXCEEDED    4403L
#define ERROR_APP_DATA_REBOOT_REQUIRED   4404L
#define ERROR_SECUREBOOT_ROLLBACK_DETECTED 4420L
#define ERROR_SECUREBOOT_POLICY_VIOLATION 4421L
#define ERROR_SECUREBOOT_INVALID_POLICY  4422L
#define ERROR_SECUREBOOT_POLICY_PUBLISHER_NOT_FOUND 4423L
#define ERROR_SECUREBOOT_POLICY_NOT_SIGNED 4424L
#define ERROR_SECUREBOOT_NOT_ENABLED     4425L
#define ERROR_SECUREBOOT_FILE_REPLACED   4426L
#define ERROR_SECUREBOOT_POLICY_NOT_AUTHORIZED 4427L
#define ERROR_SECUREBOOT_POLICY_UNKNOWN  4428L
#define ERROR_SECUREBOOT_POLICY_MISSING_ANTIROLLBACKVERSION 4429L
#define ERROR_SECUREBOOT_PLATFORM_ID_MISMATCH 4430L
#define ERROR_SECUREBOOT_POLICY_ROLLBACK_DETECTED 4431L
#define ERROR_SECUREBOOT_POLICY_UPGRADE_MISMATCH 4432L
#define ERROR_SECUREBOOT_REQUIRED_POLICY_FILE_MISSING 4433L
#define ERROR_SECUREBOOT_NOT_BASE_POLICY 4434L
#define ERROR_SECUREBOOT_NOT_SUPPLEMENTAL_POLICY 4435L
#define ERROR_OFFLOAD_READ_FLT_NOT_SUPPORTED 4440L
#define ERROR_OFFLOAD_WRITE_FLT_NOT_SUPPORTED 4441L
#define ERROR_OFFLOAD_READ_FILE_NOT_SUPPORTED 4442L
#define ERROR_OFFLOAD_WRITE_FILE_NOT_SUPPORTED 4443L
#define ERROR_VOLUME_NOT_SIS_ENABLED     4500L
#define ERROR_SYSTEM_INTEGRITY_ROLLBACK_DETECTED 4550L
#define ERROR_SYSTEM_INTEGRITY_POLICY_VIOLATION 4551L
#define ERROR_SYSTEM_INTEGRITY_INVALID_POLICY 4552L
#define ERROR_SYSTEM_INTEGRITY_POLICY_NOT_SIGNED 4553L
#define ERROR_VSM_NOT_INITIALIZED        4560L
#define ERROR_VSM_DMA_PROTECTION_NOT_IN_USE 4561L
#define ERROR_PLATFORM_MANIFEST_NOT_AUTHORIZED 4570L
#define ERROR_PLATFORM_MANIFEST_INVALID  4571L
#define ERROR_PLATFORM_MANIFEST_FILE_NOT_AUTHORIZED 4572L
#define ERROR_PLATFORM_MANIFEST_CATALOG_NOT_AUTHORIZED 4573L
#define ERROR_PLATFORM_MANIFEST_BINARY_ID_NOT_FOUND 4574L
#define ERROR_PLATFORM_MANIFEST_NOT_ACTIVE 4575L
#define ERROR_PLATFORM_MANIFEST_NOT_SIGNED 4576L
#define ERROR_DEPENDENT_RESOURCE_EXISTS  5001L
#define ERROR_DEPENDENCY_NOT_FOUND       5002L
#define ERROR_DEPENDENCY_ALREADY_EXISTS  5003L
#define ERROR_RESOURCE_NOT_ONLINE        5004L
#define ERROR_HOST_NODE_NOT_AVAILABLE    5005L
#define ERROR_RESOURCE_NOT_AVAILABLE     5006L
#define ERROR_RESOURCE_NOT_FOUND         5007L
#define ERROR_SHUTDOWN_CLUSTER           5008L
#define ERROR_CANT_EVICT_ACTIVE_NODE     5009L
#define ERROR_OBJECT_ALREADY_EXISTS      5010L
#define ERROR_OBJECT_IN_LIST             5011L
#define ERROR_GROUP_NOT_AVAILABLE        5012L
#define ERROR_GROUP_NOT_FOUND            5013L
#define ERROR_GROUP_NOT_ONLINE           5014L
#define ERROR_HOST_NODE_NOT_RESOURCE_OWNER 5015L
#define ERROR_HOST_NODE_NOT_GROUP_OWNER  5016L
#define ERROR_RESMON_CREATE_FAILED       5017L
#define ERROR_RESMON_ONLINE_FAILED       5018L
#define ERROR_RESOURCE_ONLINE            5019L
#define ERROR_QUORUM_RESOURCE            5020L
#define ERROR_NOT_QUORUM_CAPABLE         5021L
#define ERROR_CLUSTER_SHUTTING_DOWN      5022L
#define ERROR_INVALID_STATE              5023L
#define ERROR_RESOURCE_PROPERTIES_STORED 5024L
#define ERROR_NOT_QUORUM_CLASS           5025L
#define ERROR_CORE_RESOURCE              5026L
#define ERROR_QUORUM_RESOURCE_ONLINE_FAILED 5027L
#define ERROR_QUORUMLOG_OPEN_FAILED      5028L
#define ERROR_CLUSTERLOG_CORRUPT         5029L
#define ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE 5030L
#define ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE 5031L
#define ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND 5032L
#define ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE 5033L
#define ERROR_QUORUM_OWNER_ALIVE         5034L
#define ERROR_NETWORK_NOT_AVAILABLE      5035L
#define ERROR_NODE_NOT_AVAILABLE         5036L
#define ERROR_ALL_NODES_NOT_AVAILABLE    5037L
#define ERROR_RESOURCE_FAILED            5038L
#define ERROR_CLUSTER_INVALID_NODE       5039L
#define ERROR_CLUSTER_NODE_EXISTS        5040L
#define ERROR_CLUSTER_JOIN_IN_PROGRESS   5041L
#define ERROR_CLUSTER_NODE_NOT_FOUND     5042L
#define ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND 5043L
#define ERROR_CLUSTER_NETWORK_EXISTS     5044L
#define ERROR_CLUSTER_NETWORK_NOT_FOUND  5045L
#define ERROR_CLUSTER_NETINTERFACE_EXISTS 5046L
#define ERROR_CLUSTER_NETINTERFACE_NOT_FOUND 5047L
#define ERROR_CLUSTER_INVALID_REQUEST    5048L
#define ERROR_CLUSTER_INVALID_NETWORK_PROVIDER 5049L
#define ERROR_CLUSTER_NODE_DOWN          5050L
#define ERROR_CLUSTER_NODE_UNREACHABLE   5051L
#define ERROR_CLUSTER_NODE_NOT_MEMBER    5052L
#define ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS 5053L
#define ERROR_CLUSTER_INVALID_NETWORK    5054L
#define ERROR_CLUSTER_NODE_UP            5056L
#define ERROR_CLUSTER_IPADDR_IN_USE      5057L
#define ERROR_CLUSTER_NODE_NOT_PAUSED    5058L
#define ERROR_CLUSTER_NO_SECURITY_CONTEXT 5059L
#define ERROR_CLUSTER_NETWORK_NOT_INTERNAL 5060L
#define ERROR_CLUSTER_NODE_ALREADY_UP    5061L
#define ERROR_CLUSTER_NODE_ALREADY_DOWN  5062L
#define ERROR_CLUSTER_NETWORK_ALREADY_ONLINE 5063L
#define ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE 5064L
#define ERROR_CLUSTER_NODE_ALREADY_MEMBER 5065L
#define ERROR_CLUSTER_LAST_INTERNAL_NETWORK 5066L
#define ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS 5067L
#define ERROR_INVALID_OPERATION_ON_QUORUM 5068L
#define ERROR_DEPENDENCY_NOT_ALLOWED     5069L
#define ERROR_CLUSTER_NODE_PAUSED        5070L
#define ERROR_NODE_CANT_HOST_RESOURCE    5071L
#define ERROR_CLUSTER_NODE_NOT_READY     5072L
#define ERROR_CLUSTER_NODE_SHUTTING_DOWN 5073L
#define ERROR_CLUSTER_JOIN_ABORTED       5074L
#define ERROR_CLUSTER_INCOMPATIBLE_VERSIONS 5075L
#define ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED 5076L
#define ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED 5077L
#define ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND 5078L
#define ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED 5079L
#define ERROR_CLUSTER_RESNAME_NOT_FOUND  5080L
#define ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED 5081L
#define ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST 5082L
#define ERROR_CLUSTER_DATABASE_SEQMISMATCH 5083L
#define ERROR_RESMON_INVALID_STATE       5084L
#define ERROR_CLUSTER_GUM_NOT_LOCKER     5085L
#define ERROR_QUORUM_DISK_NOT_FOUND      5086L
#define ERROR_DATABASE_BACKUP_CORRUPT    5087L
#define ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT 5088L
#define ERROR_RESOURCE_PROPERTY_UNCHANGEABLE 5089L
#define ERROR_NO_ADMIN_ACCESS_POINT      5090L
#define ERROR_CLUSTER_MEMBERSHIP_INVALID_STATE 5890L
#define ERROR_CLUSTER_QUORUMLOG_NOT_FOUND 5891L
#define ERROR_CLUSTER_MEMBERSHIP_HALT    5892L
#define ERROR_CLUSTER_INSTANCE_ID_MISMATCH 5893L
#define ERROR_CLUSTER_NETWORK_NOT_FOUND_FOR_IP 5894L
#define ERROR_CLUSTER_PROPERTY_DATA_TYPE_MISMATCH 5895L
#define ERROR_CLUSTER_EVICT_WITHOUT_CLEANUP 5896L
#define ERROR_CLUSTER_PARAMETER_MISMATCH 5897L
#define ERROR_NODE_CANNOT_BE_CLUSTERED   5898L
#define ERROR_CLUSTER_WRONG_OS_VERSION   5899L
#define ERROR_CLUSTER_CANT_CREATE_DUP_CLUSTER_NAME 5900L
#define ERROR_CLUSCFG_ALREADY_COMMITTED  5901L
#define ERROR_CLUSCFG_ROLLBACK_FAILED    5902L
#define ERROR_CLUSCFG_SYSTEM_DISK_DRIVE_LETTER_CONFLICT 5903L
#define ERROR_CLUSTER_OLD_VERSION        5904L
#define ERROR_CLUSTER_MISMATCHED_COMPUTER_ACCT_NAME 5905L
#define ERROR_CLUSTER_NO_NET_ADAPTERS    5906L
#define ERROR_CLUSTER_POISONED           5907L
#define ERROR_CLUSTER_GROUP_MOVING       5908L
#define ERROR_CLUSTER_RESOURCE_TYPE_BUSY 5909L
#define ERROR_RESOURCE_CALL_TIMED_OUT    5910L
#define ERROR_INVALID_CLUSTER_IPV6_ADDRESS 5911L
#define ERROR_CLUSTER_INTERNAL_INVALID_FUNCTION 5912L
#define ERROR_CLUSTER_PARAMETER_OUT_OF_BOUNDS 5913L
#define ERROR_CLUSTER_PARTIAL_SEND       5914L
#define ERROR_CLUSTER_REGISTRY_INVALID_FUNCTION 5915L
#define ERROR_CLUSTER_INVALID_STRING_TERMINATION 5916L
#define ERROR_CLUSTER_INVALID_STRING_FORMAT 5917L
#define ERROR_CLUSTER_DATABASE_TRANSACTION_IN_PROGRESS 5918L
#define ERROR_CLUSTER_DATABASE_TRANSACTION_NOT_IN_PROGRESS 5919L
#define ERROR_CLUSTER_NULL_DATA          5920L
#define ERROR_CLUSTER_PARTIAL_READ       5921L
#define ERROR_CLUSTER_PARTIAL_WRITE      5922L
#define ERROR_CLUSTER_CANT_DESERIALIZE_DATA 5923L
#define ERROR_DEPENDENT_RESOURCE_PROPERTY_CONFLICT 5924L
#define ERROR_CLUSTER_NO_QUORUM          5925L
#define ERROR_CLUSTER_INVALID_IPV6_NETWORK 5926L
#define ERROR_CLUSTER_INVALID_IPV6_TUNNEL_NETWORK 5927L
#define ERROR_QUORUM_NOT_ALLOWED_IN_THIS_GROUP 5928L
#define ERROR_DEPENDENCY_TREE_TOO_COMPLEX 5929L
#define ERROR_EXCEPTION_IN_RESOURCE_CALL 5930L
#define ERROR_CLUSTER_RHS_FAILED_INITIALIZATION 5931L
#define ERROR_CLUSTER_NOT_INSTALLED      5932L
#define ERROR_CLUSTER_RESOURCES_MUST_BE_ONLINE_ON_THE_SAME_NODE 5933L
#define ERROR_CLUSTER_MAX_NODES_IN_CLUSTER 5934L
#define ERROR_CLUSTER_TOO_MANY_NODES     5935L
#define ERROR_CLUSTER_OBJECT_ALREADY_USED 5936L
#define ERROR_NONCORE_GROUPS_FOUND       5937L
#define ERROR_FILE_SHARE_RESOURCE_CONFLICT 5938L
#define ERROR_CLUSTER_EVICT_INVALID_REQUEST 5939L
#define ERROR_CLUSTER_SINGLETON_RESOURCE 5940L
#define ERROR_CLUSTER_GROUP_SINGLETON_RESOURCE 5941L
#define ERROR_CLUSTER_RESOURCE_PROVIDER_FAILED 5942L
#define ERROR_CLUSTER_RESOURCE_CONFIGURATION_ERROR 5943L
#define ERROR_CLUSTER_GROUP_BUSY         5944L
#define ERROR_CLUSTER_NOT_SHARED_VOLUME  5945L
#define ERROR_CLUSTER_INVALID_SECURITY_DESCRIPTOR 5946L
#define ERROR_CLUSTER_SHARED_VOLUMES_IN_USE 5947L
#define ERROR_CLUSTER_USE_SHARED_VOLUMES_API 5948L
#define ERROR_CLUSTER_BACKUP_IN_PROGRESS 5949L
#define ERROR_NON_CSV_PATH               5950L
#define ERROR_CSV_VOLUME_NOT_LOCAL       5951L
#define ERROR_CLUSTER_WATCHDOG_TERMINATING 5952L
#define ERROR_CLUSTER_RESOURCE_VETOED_MOVE_INCOMPATIBLE_NODES 5953L
#define ERROR_CLUSTER_INVALID_NODE_WEIGHT 5954L
#define ERROR_CLUSTER_RESOURCE_VETOED_CALL 5955L
#define ERROR_RESMON_SYSTEM_RESOURCES_LACKING 5956L
#define ERROR_CLUSTER_RESOURCE_VETOED_MOVE_NOT_ENOUGH_RESOURCES_ON_DESTINATION 5957L
#define ERROR_CLUSTER_RESOURCE_VETOED_MOVE_NOT_ENOUGH_RESOURCES_ON_SOURCE 5958L
#define ERROR_CLUSTER_GROUP_QUEUED       5959L
#define ERROR_CLUSTER_RESOURCE_LOCKED_STATUS 5960L
#define ERROR_CLUSTER_SHARED_VOLUME_FAILOVER_NOT_ALLOWED 5961L
#define ERROR_CLUSTER_NODE_DRAIN_IN_PROGRESS 5962L
#define ERROR_CLUSTER_DISK_NOT_CONNECTED 5963L
#define ERROR_DISK_NOT_CSV_CAPABLE       5964L
#define ERROR_RESOURCE_NOT_IN_AVAILABLE_STORAGE 5965L
#define ERROR_CLUSTER_SHARED_VOLUME_REDIRECTED 5966L
#define ERROR_CLUSTER_SHARED_VOLUME_NOT_REDIRECTED 5967L
#define ERROR_CLUSTER_CANNOT_RETURN_PROPERTIES 5968L
#define ERROR_CLUSTER_RESOURCE_CONTAINS_UNSUPPORTED_DIFF_AREA_FOR_SHARED_VOLUMES 5969L
#define ERROR_CLUSTER_RESOURCE_IS_IN_MAINTENANCE_MODE 5970L
#define ERROR_CLUSTER_AFFINITY_CONFLICT  5971L
#define ERROR_CLUSTER_RESOURCE_IS_REPLICA_VIRTUAL_MACHINE 5972L
#define ERROR_CLUSTER_UPGRADE_INCOMPATIBLE_VERSIONS 5973L
#define ERROR_CLUSTER_UPGRADE_FIX_QUORUM_NOT_SUPPORTED 5974L
#define ERROR_CLUSTER_UPGRADE_RESTART_REQUIRED 5975L
#define ERROR_CLUSTER_UPGRADE_IN_PROGRESS 5976L
#define ERROR_CLUSTER_UPGRADE_INCOMPLETE 5977L
#define ERROR_CLUSTER_NODE_IN_GRACE_PERIOD 5978L
#define ERROR_CLUSTER_CSV_IO_PAUSE_TIMEOUT 5979L
#define ERROR_NODE_NOT_ACTIVE_CLUSTER_MEMBER 5980L
#define ERROR_CLUSTER_RESOURCE_NOT_MONITORED 5981L
#define ERROR_CLUSTER_RESOURCE_DOES_NOT_SUPPORT_UNMONITORED 5982L
#define ERROR_CLUSTER_RESOURCE_IS_REPLICATED 5983L
#define ERROR_CLUSTER_NODE_ISOLATED      5984L
#define ERROR_CLUSTER_NODE_QUARANTINED   5985L
#define ERROR_CLUSTER_DATABASE_UPDATE_CONDITION_FAILED 5986L
#define ERROR_CLUSTER_SPACE_DEGRADED     5987L
#define ERROR_CLUSTER_TOKEN_DELEGATION_NOT_SUPPORTED 5988L
#define ERROR_CLUSTER_CSV_INVALID_HANDLE 5989L
#define ERROR_CLUSTER_CSV_SUPPORTED_ONLY_ON_COORDINATOR 5990L
#define ERROR_GROUPSET_NOT_AVAILABLE     5991L
#define ERROR_GROUPSET_NOT_FOUND         5992L
#define ERROR_GROUPSET_CANT_PROVIDE      5993L
#define ERROR_CLUSTER_FAULT_DOMAIN_PARENT_NOT_FOUND 5994L
#define ERROR_CLUSTER_FAULT_DOMAIN_INVALID_HIERARCHY 5995L
#define ERROR_CLUSTER_FAULT_DOMAIN_FAILED_S2D_VALIDATION 5996L
#define ERROR_CLUSTER_FAULT_DOMAIN_S2D_CONNECTIVITY_LOSS 5997L
#define ERROR_ENCRYPTION_FAILED          6000L
#define ERROR_DECRYPTION_FAILED          6001L
#define ERROR_FILE_ENCRYPTED             6002L
#define ERROR_NO_RECOVERY_POLICY         6003L
#define ERROR_NO_EFS                     6004L
#define ERROR_WRONG_EFS                  6005L
#define ERROR_NO_USER_KEYS               6006L
#define ERROR_FILE_NOT_ENCRYPTED         6007L
#define ERROR_NOT_EXPORT_FORMAT          6008L
#define ERROR_FILE_READ_ONLY             6009L
#define ERROR_DIR_EFS_DISALLOWED         6010L
#define ERROR_EFS_SERVER_NOT_TRUSTED     6011L
#define ERROR_BAD_RECOVERY_POLICY        6012L
#define ERROR_EFS_ALG_BLOB_TOO_BIG       6013L
#define ERROR_VOLUME_NOT_SUPPORT_EFS     6014L
#define ERROR_EFS_DISABLED               6015L
#define ERROR_EFS_VERSION_NOT_SUPPORT    6016L
#define ERROR_CS_ENCRYPTION_INVALID_SERVER_RESPONSE 6017L
#define ERROR_CS_ENCRYPTION_UNSUPPORTED_SERVER 6018L
#define ERROR_CS_ENCRYPTION_EXISTING_ENCRYPTED_FILE 6019L
#define ERROR_CS_ENCRYPTION_NEW_ENCRYPTED_FILE 6020L
#define ERROR_CS_ENCRYPTION_FILE_NOT_CSE 6021L
#define ERROR_ENCRYPTION_POLICY_DENIES_OPERATION 6022L
#define ERROR_NO_BROWSER_SERVERS_FOUND   6118L
#define SCHED_E_SERVICE_NOT_LOCALSYSTEM  6200L
#define ERROR_LOG_SECTOR_INVALID         6600L
#define ERROR_LOG_SECTOR_PARITY_INVALID  6601L
#define ERROR_LOG_SECTOR_REMAPPED        6602L
#define ERROR_LOG_BLOCK_INCOMPLETE       6603L
#define ERROR_LOG_INVALID_RANGE          6604L
#define ERROR_LOG_BLOCKS_EXHAUSTED       6605L
#define ERROR_LOG_READ_CONTEXT_INVALID   6606L
#define ERROR_LOG_RESTART_INVALID        6607L
#define ERROR_LOG_BLOCK_VERSION          6608L
#define ERROR_LOG_BLOCK_INVALID          6609L
#define ERROR_LOG_READ_MODE_INVALID      6610L
#define ERROR_LOG_NO_RESTART             6611L
#define ERROR_LOG_METADATA_CORRUPT       6612L
#define ERROR_LOG_METADATA_INVALID       6613L
#define ERROR_LOG_METADATA_INCONSISTENT  6614L
#define ERROR_LOG_RESERVATION_INVALID    6615L
#define ERROR_LOG_CANT_DELETE            6616L
#define ERROR_LOG_CONTAINER_LIMIT_EXCEEDED 6617L
#define ERROR_LOG_START_OF_LOG           6618L
#define ERROR_LOG_POLICY_ALREADY_INSTALLED 6619L
#define ERROR_LOG_POLICY_NOT_INSTALLED   6620L
#define ERROR_LOG_POLICY_INVALID         6621L
#define ERROR_LOG_POLICY_CONFLICT        6622L
#define ERROR_LOG_PINNED_ARCHIVE_TAIL    6623L
#define ERROR_LOG_RECORD_NONEXISTENT     6624L
#define ERROR_LOG_RECORDS_RESERVED_INVALID 6625L
#define ERROR_LOG_SPACE_RESERVED_INVALID 6626L
#define ERROR_LOG_TAIL_INVALID           6627L
#define ERROR_LOG_FULL                   6628L
#define ERROR_COULD_NOT_RESIZE_LOG       6629L
#define ERROR_LOG_MULTIPLEXED            6630L
#define ERROR_LOG_DEDICATED              6631L
#define ERROR_LOG_ARCHIVE_NOT_IN_PROGRESS 6632L
#define ERROR_LOG_ARCHIVE_IN_PROGRESS    6633L
#define ERROR_LOG_EPHEMERAL              6634L
#define ERROR_LOG_NOT_ENOUGH_CONTAINERS  6635L
#define ERROR_LOG_CLIENT_ALREADY_REGISTERED 6636L
#define ERROR_LOG_CLIENT_NOT_REGISTERED  6637L
#define ERROR_LOG_FULL_HANDLER_IN_PROGRESS 6638L
#define ERROR_LOG_CONTAINER_READ_FAILED  6639L
#define ERROR_LOG_CONTAINER_WRITE_FAILED 6640L
#define ERROR_LOG_CONTAINER_OPEN_FAILED  6641L
#define ERROR_LOG_CONTAINER_STATE_INVALID 6642L
#define ERROR_LOG_STATE_INVALID          6643L
#define ERROR_LOG_PINNED                 6644L
#define ERROR_LOG_METADATA_FLUSH_FAILED  6645L
#define ERROR_LOG_INCONSISTENT_SECURITY  6646L
#define ERROR_LOG_APPENDED_FLUSH_FAILED  6647L
#define ERROR_LOG_PINNED_RESERVATION     6648L
#define ERROR_INVALID_TRANSACTION        6700L
#define ERROR_TRANSACTION_NOT_ACTIVE     6701L
#define ERROR_TRANSACTION_REQUEST_NOT_VALID 6702L
#define ERROR_TRANSACTION_NOT_REQUESTED  6703L
#define ERROR_TRANSACTION_ALREADY_ABORTED 6704L
#define ERROR_TRANSACTION_ALREADY_COMMITTED 6705L
#define ERROR_TM_INITIALIZATION_FAILED   6706L
#define ERROR_RESOURCEMANAGER_READ_ONLY  6707L
#define ERROR_TRANSACTION_NOT_JOINED     6708L
#define ERROR_TRANSACTION_SUPERIOR_EXISTS 6709L
#define ERROR_CRM_PROTOCOL_ALREADY_EXISTS 6710L
#define ERROR_TRANSACTION_PROPAGATION_FAILED 6711L
#define ERROR_CRM_PROTOCOL_NOT_FOUND     6712L
#define ERROR_TRANSACTION_INVALID_MARSHALL_BUFFER 6713L
#define ERROR_CURRENT_TRANSACTION_NOT_VALID 6714L
#define ERROR_TRANSACTION_NOT_FOUND      6715L
#define ERROR_RESOURCEMANAGER_NOT_FOUND  6716L
#define ERROR_ENLISTMENT_NOT_FOUND       6717L
#define ERROR_TRANSACTIONMANAGER_NOT_FOUND 6718L
#define ERROR_TRANSACTIONMANAGER_NOT_ONLINE 6719L
#define ERROR_TRANSACTIONMANAGER_RECOVERY_NAME_COLLISION 6720L
#define ERROR_TRANSACTION_NOT_ROOT       6721L
#define ERROR_TRANSACTION_OBJECT_EXPIRED 6722L
#define ERROR_TRANSACTION_RESPONSE_NOT_ENLISTED 6723L
#define ERROR_TRANSACTION_RECORD_TOO_LONG 6724L
#define ERROR_IMPLICIT_TRANSACTION_NOT_SUPPORTED 6725L
#define ERROR_TRANSACTION_INTEGRITY_VIOLATED 6726L
#define ERROR_TRANSACTIONMANAGER_IDENTITY_MISMATCH 6727L
#define ERROR_RM_CANNOT_BE_FROZEN_FOR_SNAPSHOT 6728L
#define ERROR_TRANSACTION_MUST_WRITETHROUGH 6729L
#define ERROR_TRANSACTION_NO_SUPERIOR    6730L
#define ERROR_HEURISTIC_DAMAGE_POSSIBLE  6731L
#define ERROR_TRANSACTIONAL_CONFLICT     6800L
#define ERROR_RM_NOT_ACTIVE              6801L
#define ERROR_RM_METADATA_CORRUPT        6802L
#define ERROR_DIRECTORY_NOT_RM           6803L
#define ERROR_TRANSACTIONS_UNSUPPORTED_REMOTE 6805L
#define ERROR_LOG_RESIZE_INVALID_SIZE    6806L
#define ERROR_OBJECT_NO_LONGER_EXISTS    6807L
#define ERROR_STREAM_MINIVERSION_NOT_FOUND 6808L
#define ERROR_STREAM_MINIVERSION_NOT_VALID 6809L
#define ERROR_MINIVERSION_INACCESSIBLE_FROM_SPECIFIED_TRANSACTION 6810L
#define ERROR_CANT_OPEN_MINIVERSION_WITH_MODIFY_INTENT 6811L
#define ERROR_CANT_CREATE_MORE_STREAM_MINIVERSIONS 6812L
#define ERROR_REMOTE_FILE_VERSION_MISMATCH 6814L
#define ERROR_HANDLE_NO_LONGER_VALID     6815L
#define ERROR_NO_TXF_METADATA            6816L
#define ERROR_LOG_CORRUPTION_DETECTED    6817L
#define ERROR_CANT_RECOVER_WITH_HANDLE_OPEN 6818L
#define ERROR_RM_DISCONNECTED            6819L
#define ERROR_ENLISTMENT_NOT_SUPERIOR    6820L
#define ERROR_RECOVERY_NOT_NEEDED        6821L
#define ERROR_RM_ALREADY_STARTED         6822L
#define ERROR_FILE_IDENTITY_NOT_PERSISTENT 6823L
#define ERROR_CANT_BREAK_TRANSACTIONAL_DEPENDENCY 6824L
#define ERROR_CANT_CROSS_RM_BOUNDARY     6825L
#define ERROR_TXF_DIR_NOT_EMPTY          6826L
#define ERROR_INDOUBT_TRANSACTIONS_EXIST 6827L
#define ERROR_TM_VOLATILE                6828L
#define ERROR_ROLLBACK_TIMER_EXPIRED     6829L
#define ERROR_TXF_ATTRIBUTE_CORRUPT      6830L
#define ERROR_EFS_NOT_ALLOWED_IN_TRANSACTION 6831L
#define ERROR_TRANSACTIONAL_OPEN_NOT_ALLOWED 6832L
#define ERROR_LOG_GROWTH_FAILED          6833L
#define ERROR_TRANSACTED_MAPPING_UNSUPPORTED_REMOTE 6834L
#define ERROR_TXF_METADATA_ALREADY_PRESENT 6835L
#define ERROR_TRANSACTION_SCOPE_CALLBACKS_NOT_SET 6836L
#define ERROR_TRANSACTION_REQUIRED_PROMOTION 6837L
#define ERROR_CANNOT_EXECUTE_FILE_IN_TRANSACTION 6838L
#define ERROR_TRANSACTIONS_NOT_FROZEN    6839L
#define ERROR_TRANSACTION_FREEZE_IN_PROGRESS 6840L
#define ERROR_NOT_SNAPSHOT_VOLUME        6841L
#define ERROR_NO_SAVEPOINT_WITH_OPEN_FILES 6842L
#define ERROR_DATA_LOST_REPAIR           6843L
#define ERROR_SPARSE_NOT_ALLOWED_IN_TRANSACTION 6844L
#define ERROR_TM_IDENTITY_MISMATCH       6845L
#define ERROR_FLOATED_SECTION            6846L
#define ERROR_CANNOT_ACCEPT_TRANSACTED_WORK 6847L
#define ERROR_CANNOT_ABORT_TRANSACTIONS  6848L
#define ERROR_BAD_CLUSTERS               6849L
#define ERROR_COMPRESSION_NOT_ALLOWED_IN_TRANSACTION 6850L
#define ERROR_VOLUME_DIRTY               6851L
#define ERROR_NO_LINK_TRACKING_IN_TRANSACTION 6852L
#define ERROR_OPERATION_NOT_SUPPORTED_IN_TRANSACTION 6853L
#define ERROR_EXPIRED_HANDLE             6854L
#define ERROR_TRANSACTION_NOT_ENLISTED   6855L
#define ERROR_CTX_WINSTATION_NAME_INVALID 7001L
#define ERROR_CTX_INVALID_PD             7002L
#define ERROR_CTX_PD_NOT_FOUND           7003L
#define ERROR_CTX_WD_NOT_FOUND           7004L
#define ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY 7005L
#define ERROR_CTX_SERVICE_NAME_COLLISION 7006L
#define ERROR_CTX_CLOSE_PENDING          7007L
#define ERROR_CTX_NO_OUTBUF              7008L
#define ERROR_CTX_MODEM_INF_NOT_FOUND    7009L
#define ERROR_CTX_INVALID_MODEMNAME      7010L
#define ERROR_CTX_MODEM_RESPONSE_ERROR   7011L
#define ERROR_CTX_MODEM_RESPONSE_TIMEOUT 7012L
#define ERROR_CTX_MODEM_RESPONSE_NO_CARRIER 7013L
#define ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE 7014L
#define ERROR_CTX_MODEM_RESPONSE_BUSY    7015L
#define ERROR_CTX_MODEM_RESPONSE_VOICE   7016L
#define ERROR_CTX_TD_ERROR               7017L
#define ERROR_CTX_WINSTATION_NOT_FOUND   7022L
#define ERROR_CTX_WINSTATION_ALREADY_EXISTS 7023L
#define ERROR_CTX_WINSTATION_BUSY        7024L
#define ERROR_CTX_BAD_VIDEO_MODE         7025L
#define ERROR_CTX_GRAPHICS_INVALID       7035L
#define ERROR_CTX_LOGON_DISABLED         7037L
#define ERROR_CTX_NOT_CONSOLE            7038L
#define ERROR_CTX_CLIENT_QUERY_TIMEOUT   7040L
#define ERROR_CTX_CONSOLE_DISCONNECT     7041L
#define ERROR_CTX_CONSOLE_CONNECT        7042L
#define ERROR_CTX_SHADOW_DENIED          7044L
#define ERROR_CTX_WINSTATION_ACCESS_DENIED 7045L
#define ERROR_CTX_INVALID_WD             7049L
#define ERROR_CTX_SHADOW_INVALID         7050L
#define ERROR_CTX_SHADOW_DISABLED        7051L
#define ERROR_CTX_CLIENT_LICENSE_IN_USE  7052L
#define ERROR_CTX_CLIENT_LICENSE_NOT_SET 7053L
#define ERROR_CTX_LICENSE_NOT_AVAILABLE  7054L
#define ERROR_CTX_LICENSE_CLIENT_INVALID 7055L
#define ERROR_CTX_LICENSE_EXPIRED        7056L
#define ERROR_CTX_SHADOW_NOT_RUNNING     7057L
#define ERROR_CTX_SHADOW_ENDED_BY_MODE_CHANGE 7058L
#define ERROR_ACTIVATION_COUNT_EXCEEDED  7059L
#define ERROR_CTX_WINSTATIONS_DISABLED   7060L
#define ERROR_CTX_ENCRYPTION_LEVEL_REQUIRED 7061L
#define ERROR_CTX_SESSION_IN_USE         7062L
#define ERROR_CTX_NO_FORCE_LOGOFF        7063L
#define ERROR_CTX_ACCOUNT_RESTRICTION    7064L
#define ERROR_RDP_PROTOCOL_ERROR         7065L
#define ERROR_CTX_CDM_CONNECT            7066L
#define ERROR_CTX_CDM_DISCONNECT         7067L
#define ERROR_CTX_SECURITY_LAYER_ERROR   7068L
#define ERROR_TS_INCOMPATIBLE_SESSIONS   7069L
#define ERROR_TS_VIDEO_SUBSYSTEM_ERROR   7070L
#define FRS_ERR_INVALID_API_SEQUENCE     8001L
#define FRS_ERR_STARTING_SERVICE         8002L
#define FRS_ERR_STOPPING_SERVICE         8003L
#define FRS_ERR_INTERNAL_API             8004L
#define FRS_ERR_INTERNAL                 8005L
#define FRS_ERR_SERVICE_COMM             8006L
#define FRS_ERR_INSUFFICIENT_PRIV        8007L
#define FRS_ERR_AUTHENTICATION           8008L
#define FRS_ERR_PARENT_INSUFFICIENT_PRIV 8009L
#define FRS_ERR_PARENT_AUTHENTICATION    8010L
#define FRS_ERR_CHILD_TO_PARENT_COMM     8011L
#define FRS_ERR_PARENT_TO_CHILD_COMM     8012L
#define FRS_ERR_SYSVOL_POPULATE          8013L
#define FRS_ERR_SYSVOL_POPULATE_TIMEOUT  8014L
#define FRS_ERR_SYSVOL_IS_BUSY           8015L
#define FRS_ERR_SYSVOL_DEMOTE            8016L
#define FRS_ERR_INVALID_SERVICE_PARAMETER 8017L
#define ERROR_DS_NOT_INSTALLED           8200L
#define ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY 8201L
#define ERROR_DS_NO_ATTRIBUTE_OR_VALUE   8202L
#define ERROR_DS_INVALID_ATTRIBUTE_SYNTAX 8203L
#define ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED 8204L
#define ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS 8205L
#define ERROR_DS_BUSY                    8206L
#define ERROR_DS_UNAVAILABLE             8207L
#define ERROR_DS_NO_RIDS_ALLOCATED       8208L
#define ERROR_DS_NO_MORE_RIDS            8209L
#define ERROR_DS_INCORRECT_ROLE_OWNER    8210L
#define ERROR_DS_RIDMGR_INIT_ERROR       8211L
#define ERROR_DS_OBJ_CLASS_VIOLATION     8212L
#define ERROR_DS_CANT_ON_NON_LEAF        8213L
#define ERROR_DS_CANT_ON_RDN             8214L
#define ERROR_DS_CANT_MOD_OBJ_CLASS      8215L
#define ERROR_DS_CROSS_DOM_MOVE_ERROR    8216L
#define ERROR_DS_GC_NOT_AVAILABLE        8217L
#define ERROR_SHARED_POLICY              8218L
#define ERROR_POLICY_OBJECT_NOT_FOUND    8219L
#define ERROR_POLICY_ONLY_IN_DS          8220L
#define ERROR_PROMOTION_ACTIVE           8221L
#define ERROR_NO_PROMOTION_ACTIVE        8222L
#define ERROR_DS_OPERATIONS_ERROR        8224L
#define ERROR_DS_PROTOCOL_ERROR          8225L
#define ERROR_DS_TIMELIMIT_EXCEEDED      8226L
#define ERROR_DS_SIZELIMIT_EXCEEDED      8227L
#define ERROR_DS_ADMIN_LIMIT_EXCEEDED    8228L
#define ERROR_DS_COMPARE_FALSE           8229L
#define ERROR_DS_COMPARE_TRUE            8230L
#define ERROR_DS_AUTH_METHOD_NOT_SUPPORTED 8231L
#define ERROR_DS_STRONG_AUTH_REQUIRED    8232L
#define ERROR_DS_INAPPROPRIATE_AUTH      8233L
#define ERROR_DS_AUTH_UNKNOWN            8234L
#define ERROR_DS_REFERRAL                8235L
#define ERROR_DS_UNAVAILABLE_CRIT_EXTENSION 8236L
#define ERROR_DS_CONFIDENTIALITY_REQUIRED 8237L
#define ERROR_DS_INAPPROPRIATE_MATCHING  8238L
#define ERROR_DS_CONSTRAINT_VIOLATION    8239L
#define ERROR_DS_NO_SUCH_OBJECT          8240L
#define ERROR_DS_ALIAS_PROBLEM           8241L
#define ERROR_DS_INVALID_DN_SYNTAX       8242L
#define ERROR_DS_IS_LEAF                 8243L
#define ERROR_DS_ALIAS_DEREF_PROBLEM     8244L
#define ERROR_DS_UNWILLING_TO_PERFORM    8245L
#define ERROR_DS_LOOP_DETECT             8246L
#define ERROR_DS_NAMING_VIOLATION        8247L
#define ERROR_DS_OBJECT_RESULTS_TOO_LARGE 8248L
#define ERROR_DS_AFFECTS_MULTIPLE_DSAS   8249L
#define ERROR_DS_SERVER_DOWN             8250L
#define ERROR_DS_LOCAL_ERROR             8251L
#define ERROR_DS_ENCODING_ERROR          8252L
#define ERROR_DS_DECODING_ERROR          8253L
#define ERROR_DS_FILTER_UNKNOWN          8254L
#define ERROR_DS_PARAM_ERROR             8255L
#define ERROR_DS_NOT_SUPPORTED           8256L
#define ERROR_DS_NO_RESULTS_RETURNED     8257L
#define ERROR_DS_CONTROL_NOT_FOUND       8258L
#define ERROR_DS_CLIENT_LOOP             8259L
#define ERROR_DS_REFERRAL_LIMIT_EXCEEDED 8260L
#define ERROR_DS_SORT_CONTROL_MISSING    8261L
#define ERROR_DS_OFFSET_RANGE_ERROR      8262L
#define ERROR_DS_RIDMGR_DISABLED         8263L
#define ERROR_DS_ROOT_MUST_BE_NC         8301L
#define ERROR_DS_ADD_REPLICA_INHIBITED   8302L
#define ERROR_DS_ATT_NOT_DEF_IN_SCHEMA   8303L
#define ERROR_DS_MAX_OBJ_SIZE_EXCEEDED   8304L
#define ERROR_DS_OBJ_STRING_NAME_EXISTS  8305L
#define ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA 8306L
#define ERROR_DS_RDN_DOESNT_MATCH_SCHEMA 8307L
#define ERROR_DS_NO_REQUESTED_ATTS_FOUND 8308L
#define ERROR_DS_USER_BUFFER_TO_SMALL    8309L
#define ERROR_DS_ATT_IS_NOT_ON_OBJ       8310L
#define ERROR_DS_ILLEGAL_MOD_OPERATION   8311L
#define ERROR_DS_OBJ_TOO_LARGE           8312L
#define ERROR_DS_BAD_INSTANCE_TYPE       8313L
#define ERROR_DS_MASTERDSA_REQUIRED      8314L
#define ERROR_DS_OBJECT_CLASS_REQUIRED   8315L
#define ERROR_DS_MISSING_REQUIRED_ATT    8316L
#define ERROR_DS_ATT_NOT_DEF_FOR_CLASS   8317L
#define ERROR_DS_ATT_ALREADY_EXISTS      8318L
#define ERROR_DS_CANT_ADD_ATT_VALUES     8320L
#define ERROR_DS_SINGLE_VALUE_CONSTRAINT 8321L
#define ERROR_DS_RANGE_CONSTRAINT        8322L
#define ERROR_DS_ATT_VAL_ALREADY_EXISTS  8323L
#define ERROR_DS_CANT_REM_MISSING_ATT    8324L
#define ERROR_DS_CANT_REM_MISSING_ATT_VAL 8325L
#define ERROR_DS_ROOT_CANT_BE_SUBREF     8326L
#define ERROR_DS_NO_CHAINING             8327L
#define ERROR_DS_NO_CHAINED_EVAL         8328L
#define ERROR_DS_NO_PARENT_OBJECT        8329L
#define ERROR_DS_PARENT_IS_AN_ALIAS      8330L
#define ERROR_DS_CANT_MIX_MASTER_AND_REPS 8331L
#define ERROR_DS_CHILDREN_EXIST          8332L
#define ERROR_DS_OBJ_NOT_FOUND           8333L
#define ERROR_DS_ALIASED_OBJ_MISSING     8334L
#define ERROR_DS_BAD_NAME_SYNTAX         8335L
#define ERROR_DS_ALIAS_POINTS_TO_ALIAS   8336L
#define ERROR_DS_CANT_DEREF_ALIAS        8337L
#define ERROR_DS_OUT_OF_SCOPE            8338L
#define ERROR_DS_OBJECT_BEING_REMOVED    8339L
#define ERROR_DS_CANT_DELETE_DSA_OBJ     8340L
#define ERROR_DS_GENERIC_ERROR           8341L
#define ERROR_DS_DSA_MUST_BE_INT_MASTER  8342L
#define ERROR_DS_CLASS_NOT_DSA           8343L
#define ERROR_DS_INSUFF_ACCESS_RIGHTS    8344L
#define ERROR_DS_ILLEGAL_SUPERIOR        8345L
#define ERROR_DS_ATTRIBUTE_OWNED_BY_SAM  8346L
#define ERROR_DS_NAME_TOO_MANY_PARTS     8347L
#define ERROR_DS_NAME_TOO_LONG           8348L
#define ERROR_DS_NAME_VALUE_TOO_LONG     8349L
#define ERROR_DS_NAME_UNPARSEABLE        8350L
#define ERROR_DS_NAME_TYPE_UNKNOWN       8351L
#define ERROR_DS_NOT_AN_OBJECT           8352L
#define ERROR_DS_SEC_DESC_TOO_SHORT      8353L
#define ERROR_DS_SEC_DESC_INVALID        8354L
#define ERROR_DS_NO_DELETED_NAME         8355L
#define ERROR_DS_SUBREF_MUST_HAVE_PARENT 8356L
#define ERROR_DS_NCNAME_MUST_BE_NC       8357L
#define ERROR_DS_CANT_ADD_SYSTEM_ONLY    8358L
#define ERROR_DS_CLASS_MUST_BE_CONCRETE  8359L
#define ERROR_DS_INVALID_DMD             8360L
#define ERROR_DS_OBJ_GUID_EXISTS         8361L
#define ERROR_DS_NOT_ON_BACKLINK         8362L
#define ERROR_DS_NO_CROSSREF_FOR_NC      8363L
#define ERROR_DS_SHUTTING_DOWN           8364L
#define ERROR_DS_UNKNOWN_OPERATION       8365L
#define ERROR_DS_INVALID_ROLE_OWNER      8366L
#define ERROR_DS_COULDNT_CONTACT_FSMO    8367L
#define ERROR_DS_CROSS_NC_DN_RENAME      8368L
#define ERROR_DS_CANT_MOD_SYSTEM_ONLY    8369L
#define ERROR_DS_REPLICATOR_ONLY         8370L
#define ERROR_DS_OBJ_CLASS_NOT_DEFINED   8371L
#define ERROR_DS_OBJ_CLASS_NOT_SUBCLASS  8372L
#define ERROR_DS_NAME_REFERENCE_INVALID  8373L
#define ERROR_DS_CROSS_REF_EXISTS        8374L
#define ERROR_DS_CANT_DEL_MASTER_CROSSREF 8375L
#define ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD 8376L
#define ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX 8377L
#define ERROR_DS_DUP_RDN                 8378L
#define ERROR_DS_DUP_OID                 8379L
#define ERROR_DS_DUP_MAPI_ID             8380L
#define ERROR_DS_DUP_SCHEMA_ID_GUID      8381L
#define ERROR_DS_DUP_LDAP_DISPLAY_NAME   8382L
#define ERROR_DS_SEMANTIC_ATT_TEST       8383L
#define ERROR_DS_SYNTAX_MISMATCH         8384L
#define ERROR_DS_EXISTS_IN_MUST_HAVE     8385L
#define ERROR_DS_EXISTS_IN_MAY_HAVE      8386L
#define ERROR_DS_NONEXISTENT_MAY_HAVE    8387L
#define ERROR_DS_NONEXISTENT_MUST_HAVE   8388L
#define ERROR_DS_AUX_CLS_TEST_FAIL       8389L
#define ERROR_DS_NONEXISTENT_POSS_SUP    8390L
#define ERROR_DS_SUB_CLS_TEST_FAIL       8391L
#define ERROR_DS_BAD_RDN_ATT_ID_SYNTAX   8392L
#define ERROR_DS_EXISTS_IN_AUX_CLS       8393L
#define ERROR_DS_EXISTS_IN_SUB_CLS       8394L
#define ERROR_DS_EXISTS_IN_POSS_SUP      8395L
#define ERROR_DS_RECALCSCHEMA_FAILED     8396L
#define ERROR_DS_TREE_DELETE_NOT_FINISHED 8397L
#define ERROR_DS_CANT_DELETE             8398L
#define ERROR_DS_ATT_SCHEMA_REQ_ID       8399L
#define ERROR_DS_BAD_ATT_SCHEMA_SYNTAX   8400L
#define ERROR_DS_CANT_CACHE_ATT          8401L
#define ERROR_DS_CANT_CACHE_CLASS        8402L
#define ERROR_DS_CANT_REMOVE_ATT_CACHE   8403L
#define ERROR_DS_CANT_REMOVE_CLASS_CACHE 8404L
#define ERROR_DS_CANT_RETRIEVE_DN        8405L
#define ERROR_DS_MISSING_SUPREF          8406L
#define ERROR_DS_CANT_RETRIEVE_INSTANCE  8407L
#define ERROR_DS_CODE_INCONSISTENCY      8408L
#define ERROR_DS_DATABASE_ERROR          8409L
#define ERROR_DS_GOVERNSID_MISSING       8410L
#define ERROR_DS_MISSING_EXPECTED_ATT    8411L
#define ERROR_DS_NCNAME_MISSING_CR_REF   8412L
#define ERROR_DS_SECURITY_CHECKING_ERROR 8413L
#define ERROR_DS_SCHEMA_NOT_LOADED       8414L
#define ERROR_DS_SCHEMA_ALLOC_FAILED     8415L
#define ERROR_DS_ATT_SCHEMA_REQ_SYNTAX   8416L
#define ERROR_DS_GCVERIFY_ERROR          8417L
#define ERROR_DS_DRA_SCHEMA_MISMATCH     8418L
#define ERROR_DS_CANT_FIND_DSA_OBJ       8419L
#define ERROR_DS_CANT_FIND_EXPECTED_NC   8420L
#define ERROR_DS_CANT_FIND_NC_IN_CACHE   8421L
#define ERROR_DS_CANT_RETRIEVE_CHILD     8422L
#define ERROR_DS_SECURITY_ILLEGAL_MODIFY 8423L
#define ERROR_DS_CANT_REPLACE_HIDDEN_REC 8424L
#define ERROR_DS_BAD_HIERARCHY_FILE      8425L
#define ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED 8426L
#define ERROR_DS_CONFIG_PARAM_MISSING    8427L
#define ERROR_DS_COUNTING_AB_INDICES_FAILED 8428L
#define ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED 8429L
#define ERROR_DS_INTERNAL_FAILURE        8430L
#define ERROR_DS_UNKNOWN_ERROR           8431L
#define ERROR_DS_ROOT_REQUIRES_CLASS_TOP 8432L
#define ERROR_DS_REFUSING_FSMO_ROLES     8433L
#define ERROR_DS_MISSING_FSMO_SETTINGS   8434L
#define ERROR_DS_UNABLE_TO_SURRENDER_ROLES 8435L
#define ERROR_DS_DRA_GENERIC             8436L
#define ERROR_DS_DRA_INVALID_PARAMETER   8437L
#define ERROR_DS_DRA_BUSY                8438L
#define ERROR_DS_DRA_BAD_DN              8439L
#define ERROR_DS_DRA_BAD_NC              8440L
#define ERROR_DS_DRA_DN_EXISTS           8441L
#define ERROR_DS_DRA_INTERNAL_ERROR      8442L
#define ERROR_DS_DRA_INCONSISTENT_DIT    8443L
#define ERROR_DS_DRA_CONNECTION_FAILED   8444L
#define ERROR_DS_DRA_BAD_INSTANCE_TYPE   8445L
#define ERROR_DS_DRA_OUT_OF_MEM          8446L
#define ERROR_DS_DRA_MAIL_PROBLEM        8447L
#define ERROR_DS_DRA_REF_ALREADY_EXISTS  8448L
#define ERROR_DS_DRA_REF_NOT_FOUND       8449L
#define ERROR_DS_DRA_OBJ_IS_REP_SOURCE   8450L
#define ERROR_DS_DRA_DB_ERROR            8451L
#define ERROR_DS_DRA_NO_REPLICA          8452L
#define ERROR_DS_DRA_ACCESS_DENIED       8453L
#define ERROR_DS_DRA_NOT_SUPPORTED       8454L
#define ERROR_DS_DRA_RPC_CANCELLED       8455L
#define ERROR_DS_DRA_SOURCE_DISABLED     8456L
#define ERROR_DS_DRA_SINK_DISABLED       8457L
#define ERROR_DS_DRA_NAME_COLLISION      8458L
#define ERROR_DS_DRA_SOURCE_REINSTALLED  8459L
#define ERROR_DS_DRA_MISSING_PARENT      8460L
#define ERROR_DS_DRA_PREEMPTED           8461L
#define ERROR_DS_DRA_ABANDON_SYNC        8462L
#define ERROR_DS_DRA_SHUTDOWN            8463L
#define ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET 8464L
#define ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA 8465L
#define ERROR_DS_DRA_EXTN_CONNECTION_FAILED 8466L
#define ERROR_DS_INSTALL_SCHEMA_MISMATCH 8467L
#define ERROR_DS_DUP_LINK_ID             8468L
#define ERROR_DS_NAME_ERROR_RESOLVING    8469L
#define ERROR_DS_NAME_ERROR_NOT_FOUND    8470L
#define ERROR_DS_NAME_ERROR_NOT_UNIQUE   8471L
#define ERROR_DS_NAME_ERROR_NO_MAPPING   8472L
#define ERROR_DS_NAME_ERROR_DOMAIN_ONLY  8473L
#define ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING 8474L
#define ERROR_DS_CONSTRUCTED_ATT_MOD     8475L
#define ERROR_DS_WRONG_OM_OBJ_CLASS      8476L
#define ERROR_DS_DRA_REPL_PENDING        8477L
#define ERROR_DS_DS_REQUIRED             8478L
#define ERROR_DS_INVALID_LDAP_DISPLAY_NAME 8479L
#define ERROR_DS_NON_BASE_SEARCH         8480L
#define ERROR_DS_CANT_RETRIEVE_ATTS      8481L
#define ERROR_DS_BACKLINK_WITHOUT_LINK   8482L
#define ERROR_DS_EPOCH_MISMATCH          8483L
#define ERROR_DS_SRC_NAME_MISMATCH       8484L
#define ERROR_DS_SRC_AND_DST_NC_IDENTICAL 8485L
#define ERROR_DS_DST_NC_MISMATCH         8486L
#define ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC 8487L
#define ERROR_DS_SRC_GUID_MISMATCH       8488L
#define ERROR_DS_CANT_MOVE_DELETED_OBJECT 8489L
#define ERROR_DS_PDC_OPERATION_IN_PROGRESS 8490L
#define ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD 8491L
#define ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION 8492L
#define ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS 8493L
#define ERROR_DS_NC_MUST_HAVE_NC_PARENT  8494L
#define ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE 8495L
#define ERROR_DS_DST_DOMAIN_NOT_NATIVE   8496L
#define ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER 8497L
#define ERROR_DS_CANT_MOVE_ACCOUNT_GROUP 8498L
#define ERROR_DS_CANT_MOVE_RESOURCE_GROUP 8499L
#define ERROR_DS_INVALID_SEARCH_FLAG     8500L
#define ERROR_DS_NO_TREE_DELETE_ABOVE_NC 8501L
#define ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE 8502L
#define ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE 8503L
#define ERROR_DS_SAM_INIT_FAILURE        8504L
#define ERROR_DS_SENSITIVE_GROUP_VIOLATION 8505L
#define ERROR_DS_CANT_MOD_PRIMARYGROUPID 8506L
#define ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD 8507L
#define ERROR_DS_NONSAFE_SCHEMA_CHANGE   8508L
#define ERROR_DS_SCHEMA_UPDATE_DISALLOWED 8509L
#define ERROR_DS_CANT_CREATE_UNDER_SCHEMA 8510L
#define ERROR_DS_INSTALL_NO_SRC_SCH_VERSION 8511L
#define ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE 8512L
#define ERROR_DS_INVALID_GROUP_TYPE      8513L
#define ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN 8514L
#define ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN 8515L
#define ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER 8516L
#define ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER 8517L
#define ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER 8518L
#define ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER 8519L
#define ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER 8520L
#define ERROR_DS_HAVE_PRIMARY_MEMBERS    8521L
#define ERROR_DS_STRING_SD_CONVERSION_FAILED 8522L
#define ERROR_DS_NAMING_MASTER_GC        8523L
#define ERROR_DS_DNS_LOOKUP_FAILURE      8524L
#define ERROR_DS_COULDNT_UPDATE_SPNS     8525L
#define ERROR_DS_CANT_RETRIEVE_SD        8526L
#define ERROR_DS_KEY_NOT_UNIQUE          8527L
#define ERROR_DS_WRONG_LINKED_ATT_SYNTAX 8528L
#define ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD 8529L
#define ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY 8530L
#define ERROR_DS_CANT_START              8531L
#define ERROR_DS_INIT_FAILURE            8532L
#define ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION 8533L
#define ERROR_DS_SOURCE_DOMAIN_IN_FOREST 8534L
#define ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST 8535L
#define ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED 8536L
#define ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN 8537L
#define ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER 8538L
#define ERROR_DS_SRC_SID_EXISTS_IN_FOREST 8539L
#define ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH 8540L
#define ERROR_SAM_INIT_FAILURE           8541L
#define ERROR_DS_DRA_SCHEMA_INFO_SHIP    8542L
#define ERROR_DS_DRA_SCHEMA_CONFLICT     8543L
#define ERROR_DS_DRA_EARLIER_SCHEMA_CONFLICT 8544L
#define ERROR_DS_DRA_OBJ_NC_MISMATCH     8545L
#define ERROR_DS_NC_STILL_HAS_DSAS       8546L
#define ERROR_DS_GC_REQUIRED             8547L
#define ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY 8548L
#define ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS 8549L
#define ERROR_DS_CANT_ADD_TO_GC          8550L
#define ERROR_DS_NO_CHECKPOINT_WITH_PDC  8551L
#define ERROR_DS_SOURCE_AUDITING_NOT_ENABLED 8552L
#define ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC 8553L
#define ERROR_DS_INVALID_NAME_FOR_SPN    8554L
#define ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS 8555L
#define ERROR_DS_UNICODEPWD_NOT_IN_QUOTES 8556L
#define ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED 8557L
#define ERROR_DS_MUST_BE_RUN_ON_DST_DC   8558L
#define ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER 8559L
#define ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ 8560L
#define ERROR_DS_INIT_FAILURE_CONSOLE    8561L
#define ERROR_DS_SAM_INIT_FAILURE_CONSOLE 8562L
#define ERROR_DS_FOREST_VERSION_TOO_HIGH 8563L
#define ERROR_DS_DOMAIN_VERSION_TOO_HIGH 8564L
#define ERROR_DS_FOREST_VERSION_TOO_LOW  8565L
#define ERROR_DS_DOMAIN_VERSION_TOO_LOW  8566L
#define ERROR_DS_INCOMPATIBLE_VERSION    8567L
#define ERROR_DS_LOW_DSA_VERSION         8568L
#define ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN 8569L
#define ERROR_DS_NOT_SUPPORTED_SORT_ORDER 8570L
#define ERROR_DS_NAME_NOT_UNIQUE         8571L
#define ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4 8572L
#define ERROR_DS_OUT_OF_VERSION_STORE    8573L
#define ERROR_DS_INCOMPATIBLE_CONTROLS_USED 8574L
#define ERROR_DS_NO_REF_DOMAIN           8575L
#define ERROR_DS_RESERVED_LINK_ID        8576L
#define ERROR_DS_LINK_ID_NOT_AVAILABLE   8577L
#define ERROR_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER 8578L
#define ERROR_DS_MODIFYDN_DISALLOWED_BY_INSTANCE_TYPE 8579L
#define ERROR_DS_NO_OBJECT_MOVE_IN_SCHEMA_NC 8580L
#define ERROR_DS_MODIFYDN_DISALLOWED_BY_FLAG 8581L
#define ERROR_DS_MODIFYDN_WRONG_GRANDPARENT 8582L
#define ERROR_DS_NAME_ERROR_TRUST_REFERRAL 8583L
#define ERROR_NOT_SUPPORTED_ON_STANDARD_SERVER 8584L
#define ERROR_DS_CANT_ACCESS_REMOTE_PART_OF_AD 8585L
#define ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE_V2 8586L
#define ERROR_DS_THREAD_LIMIT_EXCEEDED   8587L
#define ERROR_DS_NOT_CLOSEST             8588L
#define ERROR_DS_CANT_DERIVE_SPN_WITHOUT_SERVER_REF 8589L
#define ERROR_DS_SINGLE_USER_MODE_FAILED 8590L
#define ERROR_DS_NTDSCRIPT_SYNTAX_ERROR  8591L
#define ERROR_DS_NTDSCRIPT_PROCESS_ERROR 8592L
#define ERROR_DS_DIFFERENT_REPL_EPOCHS   8593L
#define ERROR_DS_DRS_EXTENSIONS_CHANGED  8594L
#define ERROR_DS_REPLICA_SET_CHANGE_NOT_ALLOWED_ON_DISABLED_CR 8595L
#define ERROR_DS_NO_MSDS_INTID           8596L
#define ERROR_DS_DUP_MSDS_INTID          8597L
#define ERROR_DS_EXISTS_IN_RDNATTID      8598L
#define ERROR_DS_AUTHORIZATION_FAILED    8599L
#define ERROR_DS_INVALID_SCRIPT          8600L
#define ERROR_DS_REMOTE_CROSSREF_OP_FAILED 8601L
#define ERROR_DS_CROSS_REF_BUSY          8602L
#define ERROR_DS_CANT_DERIVE_SPN_FOR_DELETED_DOMAIN 8603L
#define ERROR_DS_CANT_DEMOTE_WITH_WRITEABLE_NC 8604L
#define ERROR_DS_DUPLICATE_ID_FOUND      8605L
#define ERROR_DS_INSUFFICIENT_ATTR_TO_CREATE_OBJECT 8606L
#define ERROR_DS_GROUP_CONVERSION_ERROR  8607L
#define ERROR_DS_CANT_MOVE_APP_BASIC_GROUP 8608L
#define ERROR_DS_CANT_MOVE_APP_QUERY_GROUP 8609L
#define ERROR_DS_ROLE_NOT_VERIFIED       8610L
#define ERROR_DS_WKO_CONTAINER_CANNOT_BE_SPECIAL 8611L
#define ERROR_DS_DOMAIN_RENAME_IN_PROGRESS 8612L
#define ERROR_DS_EXISTING_AD_CHILD_NC    8613L
#define ERROR_DS_REPL_LIFETIME_EXCEEDED  8614L
#define ERROR_DS_DISALLOWED_IN_SYSTEM_CONTAINER 8615L
#define ERROR_DS_LDAP_SEND_QUEUE_FULL    8616L
#define ERROR_DS_DRA_OUT_SCHEDULE_WINDOW 8617L
#define ERROR_DS_POLICY_NOT_KNOWN        8618L
#define ERROR_NO_SITE_SETTINGS_OBJECT    8619L
#define ERROR_NO_SECRETS                 8620L
#define ERROR_NO_WRITABLE_DC_FOUND       8621L
#define ERROR_DS_NO_SERVER_OBJECT        8622L
#define ERROR_DS_NO_NTDSA_OBJECT         8623L
#define ERROR_DS_NON_ASQ_SEARCH          8624L
#define ERROR_DS_AUDIT_FAILURE           8625L
#define ERROR_DS_INVALID_SEARCH_FLAG_SUBTREE 8626L
#define ERROR_DS_INVALID_SEARCH_FLAG_TUPLE 8627L
#define ERROR_DS_HIERARCHY_TABLE_TOO_DEEP 8628L
#define ERROR_DS_DRA_CORRUPT_UTD_VECTOR  8629L
#define ERROR_DS_DRA_SECRETS_DENIED      8630L
#define ERROR_DS_RESERVED_MAPI_ID        8631L
#define ERROR_DS_MAPI_ID_NOT_AVAILABLE   8632L
#define ERROR_DS_DRA_MISSING_KRBTGT_SECRET 8633L
#define ERROR_DS_DOMAIN_NAME_EXISTS_IN_FOREST 8634L
#define ERROR_DS_FLAT_NAME_EXISTS_IN_FOREST 8635L
#define ERROR_INVALID_USER_PRINCIPAL_NAME 8636L
#define ERROR_DS_OID_MAPPED_GROUP_CANT_HAVE_MEMBERS 8637L
#define ERROR_DS_OID_NOT_FOUND           8638L
#define ERROR_DS_DRA_RECYCLED_TARGET     8639L
#define ERROR_DS_DISALLOWED_NC_REDIRECT  8640L
#define ERROR_DS_HIGH_ADLDS_FFL          8641L
#define ERROR_DS_HIGH_DSA_VERSION        8642L
#define ERROR_DS_LOW_ADLDS_FFL           8643L
#define ERROR_DOMAIN_SID_SAME_AS_LOCAL_WORKSTATION 8644L
#define ERROR_DS_UNDELETE_SAM_VALIDATION_FAILED 8645L
#define ERROR_INCORRECT_ACCOUNT_TYPE     8646L
#define ERROR_DS_SPN_VALUE_NOT_UNIQUE_IN_FOREST 8647L
#define ERROR_DS_UPN_VALUE_NOT_UNIQUE_IN_FOREST 8648L
#define ERROR_DS_MISSING_FOREST_TRUST    8649L
#define ERROR_DS_VALUE_KEY_NOT_UNIQUE    8650L
#define DNS_ERROR_RESPONSE_CODES_BASE 9000
#define DNS_ERROR_MASK 0x00002328 // 9000 or DNS_ERROR_RESPONSE_CODES_BASE
#define DNS_ERROR_RCODE_FORMAT_ERROR     9001L
#define DNS_ERROR_RCODE_SERVER_FAILURE   9002L
#define DNS_ERROR_RCODE_NAME_ERROR       9003L
#define DNS_ERROR_RCODE_NOT_IMPLEMENTED  9004L
#define DNS_ERROR_RCODE_REFUSED          9005L
#define DNS_ERROR_RCODE_YXDOMAIN         9006L
#define DNS_ERROR_RCODE_YXRRSET          9007L
#define DNS_ERROR_RCODE_NXRRSET          9008L
#define DNS_ERROR_RCODE_NOTAUTH          9009L
#define DNS_ERROR_RCODE_NOTZONE          9010L
#define DNS_ERROR_RCODE_BADSIG           9016L
#define DNS_ERROR_RCODE_BADKEY           9017L
#define DNS_ERROR_RCODE_BADTIME          9018L
#define DNS_ERROR_RCODE_LAST			 DNS_ERROR_RCODE_BADTIME
#define DNS_ERROR_DNSSEC_BASE 9100
#define DNS_ERROR_KEYMASTER_REQUIRED     9101L
#define DNS_ERROR_NOT_ALLOWED_ON_SIGNED_ZONE 9102L
#define DNS_ERROR_NSEC3_INCOMPATIBLE_WITH_RSA_SHA1 9103L
#define DNS_ERROR_NOT_ENOUGH_SIGNING_KEY_DESCRIPTORS 9104L
#define DNS_ERROR_UNSUPPORTED_ALGORITHM  9105L
#define DNS_ERROR_INVALID_KEY_SIZE       9106L
#define DNS_ERROR_SIGNING_KEY_NOT_ACCESSIBLE 9107L
#define DNS_ERROR_KSP_DOES_NOT_SUPPORT_PROTECTION 9108L
#define DNS_ERROR_UNEXPECTED_DATA_PROTECTION_ERROR 9109L
#define DNS_ERROR_UNEXPECTED_CNG_ERROR   9110L
#define DNS_ERROR_UNKNOWN_SIGNING_PARAMETER_VERSION 9111L
#define DNS_ERROR_KSP_NOT_ACCESSIBLE     9112L
#define DNS_ERROR_TOO_MANY_SKDS          9113L
#define DNS_ERROR_INVALID_ROLLOVER_PERIOD 9114L
#define DNS_ERROR_INVALID_INITIAL_ROLLOVER_OFFSET 9115L
#define DNS_ERROR_ROLLOVER_IN_PROGRESS   9116L
#define DNS_ERROR_STANDBY_KEY_NOT_PRESENT 9117L
#define DNS_ERROR_NOT_ALLOWED_ON_ZSK     9118L
#define DNS_ERROR_NOT_ALLOWED_ON_ACTIVE_SKD 9119L
#define DNS_ERROR_ROLLOVER_ALREADY_QUEUED 9120L
#define DNS_ERROR_NOT_ALLOWED_ON_UNSIGNED_ZONE 9121L
#define DNS_ERROR_BAD_KEYMASTER          9122L
#define DNS_ERROR_INVALID_SIGNATURE_VALIDITY_PERIOD 9123L
#define DNS_ERROR_INVALID_NSEC3_ITERATION_COUNT 9124L
#define DNS_ERROR_DNSSEC_IS_DISABLED     9125L
#define DNS_ERROR_INVALID_XML            9126L
#define DNS_ERROR_NO_VALID_TRUST_ANCHORS 9127L
#define DNS_ERROR_ROLLOVER_NOT_POKEABLE  9128L
#define DNS_ERROR_NSEC3_NAME_COLLISION   9129L
#define DNS_ERROR_NSEC_INCOMPATIBLE_WITH_NSEC3_RSA_SHA1 9130L
#define DNS_ERROR_PACKET_FMT_BASE		 9500
#define DNS_INFO_NO_RECORDS              9501L
#define DNS_ERROR_BAD_PACKET             9502L
#define DNS_ERROR_NO_PACKET              9503L
#define DNS_ERROR_RCODE                  9504L
#define DNS_ERROR_UNSECURE_PACKET        9505L
#define DNS_STATUS_PACKET_UNSECURE		 DNS_ERROR_UNSECURE_PACKET
#define DNS_REQUEST_PENDING              9506L
#define DNS_ERROR_NO_MEMORY              ERROR_OUTOFMEMORY
#define DNS_ERROR_INVALID_NAME           ERROR_INVALID_NAME
#define DNS_ERROR_INVALID_DATA           ERROR_INVALID_DATA
#define DNS_ERROR_GENERAL_API_BASE		 9550
#define DNS_ERROR_INVALID_TYPE           9551L
#define DNS_ERROR_INVALID_IP_ADDRESS     9552L
#define DNS_ERROR_INVALID_PROPERTY       9553L
#define DNS_ERROR_TRY_AGAIN_LATER        9554L
#define DNS_ERROR_NOT_UNIQUE             9555L
#define DNS_ERROR_NON_RFC_NAME           9556L
#define DNS_STATUS_FQDN                  9557L
#define DNS_STATUS_DOTTED_NAME           9558L
#define DNS_STATUS_SINGLE_PART_NAME      9559L
#define DNS_ERROR_INVALID_NAME_CHAR      9560L
#define DNS_ERROR_NUMERIC_NAME           9561L
#define DNS_ERROR_NOT_ALLOWED_ON_ROOT_SERVER 9562L
#define DNS_ERROR_NOT_ALLOWED_UNDER_DELEGATION 9563L
#define DNS_ERROR_CANNOT_FIND_ROOT_HINTS 9564L
#define DNS_ERROR_INCONSISTENT_ROOT_HINTS 9565L
#define DNS_ERROR_DWORD_VALUE_TOO_SMALL  9566L
#define DNS_ERROR_DWORD_VALUE_TOO_LARGE  9567L
#define DNS_ERROR_BACKGROUND_LOADING     9568L
#define DNS_ERROR_NOT_ALLOWED_ON_RODC    9569L
#define DNS_ERROR_NOT_ALLOWED_UNDER_DNAME 9570L
#define DNS_ERROR_DELEGATION_REQUIRED    9571L
#define DNS_ERROR_INVALID_POLICY_TABLE   9572L
#define DNS_ERROR_ADDRESS_REQUIRED       9573L
#define DNS_ERROR_ZONE_BASE 9600
#define DNS_ERROR_ZONE_DOES_NOT_EXIST    9601L
#define DNS_ERROR_NO_ZONE_INFO           9602L
#define DNS_ERROR_INVALID_ZONE_OPERATION 9603L
#define DNS_ERROR_ZONE_CONFIGURATION_ERROR 9604L
#define DNS_ERROR_ZONE_HAS_NO_SOA_RECORD 9605L
#define DNS_ERROR_ZONE_HAS_NO_NS_RECORDS 9606L
#define DNS_ERROR_ZONE_LOCKED            9607L
#define DNS_ERROR_ZONE_CREATION_FAILED   9608L
#define DNS_ERROR_ZONE_ALREADY_EXISTS    9609L
#define DNS_ERROR_AUTOZONE_ALREADY_EXISTS 9610L
#define DNS_ERROR_INVALID_ZONE_TYPE      9611L
#define DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP 9612L
#define DNS_ERROR_ZONE_NOT_SECONDARY     9613L
#define DNS_ERROR_NEED_SECONDARY_ADDRESSES 9614L
#define DNS_ERROR_WINS_INIT_FAILED       9615L
#define DNS_ERROR_NEED_WINS_SERVERS      9616L
#define DNS_ERROR_NBSTAT_INIT_FAILED     9617L
#define DNS_ERROR_SOA_DELETE_INVALID     9618L
#define DNS_ERROR_FORWARDER_ALREADY_EXISTS 9619L
#define DNS_ERROR_ZONE_REQUIRES_MASTER_IP 9620L
#define DNS_ERROR_ZONE_IS_SHUTDOWN       9621L
#define DNS_ERROR_ZONE_LOCKED_FOR_SIGNING 9622L
#define DNS_ERROR_DATAFILE_BASE 9650
#define DNS_ERROR_PRIMARY_REQUIRES_DATAFILE 9651L
#define DNS_ERROR_INVALID_DATAFILE_NAME  9652L
#define DNS_ERROR_DATAFILE_OPEN_FAILURE  9653L
#define DNS_ERROR_FILE_WRITEBACK_FAILED  9654L
#define DNS_ERROR_DATAFILE_PARSING       9655L
#define DNS_ERROR_DATABASE_BASE 9700
#define DNS_ERROR_RECORD_DOES_NOT_EXIST  9701L
#define DNS_ERROR_RECORD_FORMAT          9702L
#define DNS_ERROR_NODE_CREATION_FAILED   9703L
#define DNS_ERROR_UNKNOWN_RECORD_TYPE    9704L
#define DNS_ERROR_RECORD_TIMED_OUT       9705L
#define DNS_ERROR_NAME_NOT_IN_ZONE       9706L
#define DNS_ERROR_CNAME_LOOP             9707L
#define DNS_ERROR_NODE_IS_CNAME          9708L
#define DNS_ERROR_CNAME_COLLISION        9709L
#define DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT 9710L
#define DNS_ERROR_RECORD_ALREADY_EXISTS  9711L
#define DNS_ERROR_SECONDARY_DATA         9712L
#define DNS_ERROR_NO_CREATE_CACHE_DATA   9713L
#define DNS_ERROR_NAME_DOES_NOT_EXIST    9714L
#define DNS_WARNING_PTR_CREATE_FAILED    9715L
#define DNS_WARNING_DOMAIN_UNDELETED     9716L
#define DNS_ERROR_DS_UNAVAILABLE         9717L
#define DNS_ERROR_DS_ZONE_ALREADY_EXISTS 9718L
#define DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE 9719L
#define DNS_ERROR_NODE_IS_DNAME          9720L
#define DNS_ERROR_DNAME_COLLISION        9721L
#define DNS_ERROR_ALIAS_LOOP             9722L
#define DNS_ERROR_OPERATION_BASE 9750
#define DNS_INFO_AXFR_COMPLETE           9751L
#define DNS_ERROR_AXFR                   9752L
#define DNS_INFO_ADDED_LOCAL_WINS        9753L
#define DNS_ERROR_SECURE_BASE 9800
#define DNS_STATUS_CONTINUE_NEEDED       9801L
#define DNS_ERROR_SETUP_BASE 9850
#define DNS_ERROR_NO_TCPIP               9851L
#define DNS_ERROR_NO_DNS_SERVERS         9852L
#define DNS_ERROR_DP_BASE 9900
#define DNS_ERROR_DP_DOES_NOT_EXIST      9901L
#define DNS_ERROR_DP_ALREADY_EXISTS      9902L
#define DNS_ERROR_DP_NOT_ENLISTED        9903L
#define DNS_ERROR_DP_ALREADY_ENLISTED    9904L
#define DNS_ERROR_DP_NOT_AVAILABLE       9905L
#define DNS_ERROR_DP_FSMO_ERROR          9906L
#define DNS_ERROR_RRL_NOT_ENABLED        9911L
#define DNS_ERROR_RRL_INVALID_WINDOW_SIZE 9912L
#define DNS_ERROR_RRL_INVALID_IPV4_PREFIX 9913L
#define DNS_ERROR_RRL_INVALID_IPV6_PREFIX 9914L
#define DNS_ERROR_RRL_INVALID_TC_RATE    9915L
#define DNS_ERROR_RRL_INVALID_LEAK_RATE  9916L
#define DNS_ERROR_RRL_LEAK_RATE_LESSTHAN_TC_RATE 9917L
#define DNS_ERROR_VIRTUALIZATION_INSTANCE_ALREADY_EXISTS 9921L
#define DNS_ERROR_VIRTUALIZATION_INSTANCE_DOES_NOT_EXIST 9922L
#define DNS_ERROR_VIRTUALIZATION_TREE_LOCKED 9923L
#define DNS_ERROR_INVAILD_VIRTUALIZATION_INSTANCE_NAME 9924L
#define DNS_ERROR_DEFAULT_VIRTUALIZATION_INSTANCE 9925L
#define DNS_ERROR_ZONESCOPE_ALREADY_EXISTS 9951L
#define DNS_ERROR_ZONESCOPE_DOES_NOT_EXIST 9952L
#define DNS_ERROR_DEFAULT_ZONESCOPE      9953L
#define DNS_ERROR_INVALID_ZONESCOPE_NAME 9954L
#define DNS_ERROR_NOT_ALLOWED_WITH_ZONESCOPES 9955L
#define DNS_ERROR_LOAD_ZONESCOPE_FAILED  9956L
#define DNS_ERROR_ZONESCOPE_FILE_WRITEBACK_FAILED 9957L
#define DNS_ERROR_INVALID_SCOPE_NAME     9958L
#define DNS_ERROR_SCOPE_DOES_NOT_EXIST   9959L
#define DNS_ERROR_DEFAULT_SCOPE          9960L
#define DNS_ERROR_INVALID_SCOPE_OPERATION 9961L
#define DNS_ERROR_SCOPE_LOCKED           9962L
#define DNS_ERROR_SCOPE_ALREADY_EXISTS   9963L
#define DNS_ERROR_POLICY_ALREADY_EXISTS  9971L
#define DNS_ERROR_POLICY_DOES_NOT_EXIST  9972L
#define DNS_ERROR_POLICY_INVALID_CRITERIA 9973L
#define DNS_ERROR_POLICY_INVALID_SETTINGS 9974L
#define DNS_ERROR_CLIENT_SUBNET_IS_ACCESSED 9975L
#define DNS_ERROR_CLIENT_SUBNET_DOES_NOT_EXIST 9976L
#define DNS_ERROR_CLIENT_SUBNET_ALREADY_EXISTS 9977L
#define DNS_ERROR_SUBNET_DOES_NOT_EXIST  9978L
#define DNS_ERROR_SUBNET_ALREADY_EXISTS  9979L
#define DNS_ERROR_POLICY_LOCKED          9980L
#define DNS_ERROR_POLICY_INVALID_WEIGHT  9981L
#define DNS_ERROR_POLICY_INVALID_NAME    9982L
#define DNS_ERROR_POLICY_MISSING_CRITERIA 9983L
#define DNS_ERROR_INVALID_CLIENT_SUBNET_NAME 9984L
#define DNS_ERROR_POLICY_PROCESSING_ORDER_INVALID 9985L
#define DNS_ERROR_POLICY_SCOPE_MISSING   9986L
#define DNS_ERROR_POLICY_SCOPE_NOT_ALLOWED 9987L
#define DNS_ERROR_SERVERSCOPE_IS_REFERENCED 9988L
#define DNS_ERROR_ZONESCOPE_IS_REFERENCED 9989L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_CLIENT_SUBNET 9990L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_TRANSPORT_PROTOCOL 9991L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_NETWORK_PROTOCOL 9992L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_INTERFACE 9993L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_FQDN 9994L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_QUERY_TYPE 9995L
#define DNS_ERROR_POLICY_INVALID_CRITERIA_TIME_OF_DAY 9996L
#define ERROR_IPSEC_QM_POLICY_EXISTS     13000L
#define ERROR_IPSEC_QM_POLICY_NOT_FOUND  13001L
#define ERROR_IPSEC_QM_POLICY_IN_USE     13002L
#define ERROR_IPSEC_MM_POLICY_EXISTS     13003L
#define ERROR_IPSEC_MM_POLICY_NOT_FOUND  13004L
#define ERROR_IPSEC_MM_POLICY_IN_USE     13005L
#define ERROR_IPSEC_MM_FILTER_EXISTS     13006L
#define ERROR_IPSEC_MM_FILTER_NOT_FOUND  13007L
#define ERROR_IPSEC_TRANSPORT_FILTER_EXISTS 13008L
#define ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND 13009L
#define ERROR_IPSEC_MM_AUTH_EXISTS       13010L
#define ERROR_IPSEC_MM_AUTH_NOT_FOUND    13011L
#define ERROR_IPSEC_MM_AUTH_IN_USE       13012L
#define ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND 13013L
#define ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND 13014L
#define ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND 13015L
#define ERROR_IPSEC_TUNNEL_FILTER_EXISTS 13016L
#define ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND 13017L
#define ERROR_IPSEC_MM_FILTER_PENDING_DELETION 13018L
#define ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION 13019L
#define ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION 13020L
#define ERROR_IPSEC_MM_POLICY_PENDING_DELETION 13021L
#define ERROR_IPSEC_MM_AUTH_PENDING_DELETION 13022L
#define ERROR_IPSEC_QM_POLICY_PENDING_DELETION 13023L
#define WARNING_IPSEC_MM_POLICY_PRUNED   13024L
#define WARNING_IPSEC_QM_POLICY_PRUNED   13025L
#define ERROR_IPSEC_IKE_NEG_STATUS_BEGIN 13800L
#define ERROR_IPSEC_IKE_AUTH_FAIL        13801L
#define ERROR_IPSEC_IKE_ATTRIB_FAIL      13802L
#define ERROR_IPSEC_IKE_NEGOTIATION_PENDING 13803L
#define ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR 13804L
#define ERROR_IPSEC_IKE_TIMED_OUT        13805L
#define ERROR_IPSEC_IKE_NO_CERT          13806L
#define ERROR_IPSEC_IKE_SA_DELETED       13807L
#define ERROR_IPSEC_IKE_SA_REAPED        13808L
#define ERROR_IPSEC_IKE_MM_ACQUIRE_DROP  13809L
#define ERROR_IPSEC_IKE_QM_ACQUIRE_DROP  13810L
#define ERROR_IPSEC_IKE_QUEUE_DROP_MM    13811L
#define ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM 13812L
#define ERROR_IPSEC_IKE_DROP_NO_RESPONSE 13813L
#define ERROR_IPSEC_IKE_MM_DELAY_DROP    13814L
#define ERROR_IPSEC_IKE_QM_DELAY_DROP    13815L
#define ERROR_IPSEC_IKE_ERROR            13816L
#define ERROR_IPSEC_IKE_CRL_FAILED       13817L
#define ERROR_IPSEC_IKE_INVALID_KEY_USAGE 13818L
#define ERROR_IPSEC_IKE_INVALID_CERT_TYPE 13819L
#define ERROR_IPSEC_IKE_NO_PRIVATE_KEY   13820L
#define ERROR_IPSEC_IKE_SIMULTANEOUS_REKEY 13821L
#define ERROR_IPSEC_IKE_DH_FAIL          13822L
#define ERROR_IPSEC_IKE_CRITICAL_PAYLOAD_NOT_RECOGNIZED 13823L
#define ERROR_IPSEC_IKE_INVALID_HEADER   13824L
#define ERROR_IPSEC_IKE_NO_POLICY        13825L
#define ERROR_IPSEC_IKE_INVALID_SIGNATURE 13826L
#define ERROR_IPSEC_IKE_KERBEROS_ERROR   13827L
#define ERROR_IPSEC_IKE_NO_PUBLIC_KEY    13828L
#define ERROR_IPSEC_IKE_PROCESS_ERR      13829L
#define ERROR_IPSEC_IKE_PROCESS_ERR_SA   13830L
#define ERROR_IPSEC_IKE_PROCESS_ERR_PROP 13831L
#define ERROR_IPSEC_IKE_PROCESS_ERR_TRANS 13832L
#define ERROR_IPSEC_IKE_PROCESS_ERR_KE   13833L
#define ERROR_IPSEC_IKE_PROCESS_ERR_ID   13834L
#define ERROR_IPSEC_IKE_PROCESS_ERR_CERT 13835L
#define ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ 13836L
#define ERROR_IPSEC_IKE_PROCESS_ERR_HASH 13837L
#define ERROR_IPSEC_IKE_PROCESS_ERR_SIG  13838L
#define ERROR_IPSEC_IKE_PROCESS_ERR_NONCE 13839L
#define ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY 13840L
#define ERROR_IPSEC_IKE_PROCESS_ERR_DELETE 13841L
#define ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR 13842L
#define ERROR_IPSEC_IKE_INVALID_PAYLOAD  13843L
#define ERROR_IPSEC_IKE_LOAD_SOFT_SA     13844L
#define ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN 13845L
#define ERROR_IPSEC_IKE_INVALID_COOKIE   13846L
#define ERROR_IPSEC_IKE_NO_PEER_CERT     13847L
#define ERROR_IPSEC_IKE_PEER_CRL_FAILED  13848L
#define ERROR_IPSEC_IKE_POLICY_CHANGE    13849L
#define ERROR_IPSEC_IKE_NO_MM_POLICY     13850L
#define ERROR_IPSEC_IKE_NOTCBPRIV        13851L
#define ERROR_IPSEC_IKE_SECLOADFAIL      13852L
#define ERROR_IPSEC_IKE_FAILSSPINIT      13853L
#define ERROR_IPSEC_IKE_FAILQUERYSSP     13854L
#define ERROR_IPSEC_IKE_SRVACQFAIL       13855L
#define ERROR_IPSEC_IKE_SRVQUERYCRED     13856L
#define ERROR_IPSEC_IKE_GETSPIFAIL       13857L
#define ERROR_IPSEC_IKE_INVALID_FILTER   13858L
#define ERROR_IPSEC_IKE_OUT_OF_MEMORY    13859L
#define ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED 13860L
#define ERROR_IPSEC_IKE_INVALID_POLICY   13861L
#define ERROR_IPSEC_IKE_UNKNOWN_DOI      13862L
#define ERROR_IPSEC_IKE_INVALID_SITUATION 13863L
#define ERROR_IPSEC_IKE_DH_FAILURE       13864L
#define ERROR_IPSEC_IKE_INVALID_GROUP    13865L
#define ERROR_IPSEC_IKE_ENCRYPT          13866L
#define ERROR_IPSEC_IKE_DECRYPT          13867L
#define ERROR_IPSEC_IKE_POLICY_MATCH     13868L
#define ERROR_IPSEC_IKE_UNSUPPORTED_ID   13869L
#define ERROR_IPSEC_IKE_INVALID_HASH     13870L
#define ERROR_IPSEC_IKE_INVALID_HASH_ALG 13871L
#define ERROR_IPSEC_IKE_INVALID_HASH_SIZE 13872L
#define ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG 13873L
#define ERROR_IPSEC_IKE_INVALID_AUTH_ALG 13874L
#define ERROR_IPSEC_IKE_INVALID_SIG      13875L
#define ERROR_IPSEC_IKE_LOAD_FAILED      13876L
#define ERROR_IPSEC_IKE_RPC_DELETE       13877L
#define ERROR_IPSEC_IKE_BENIGN_REINIT    13878L
#define ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY 13879L
#define ERROR_IPSEC_IKE_INVALID_MAJOR_VERSION 13880L
#define ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN 13881L
#define ERROR_IPSEC_IKE_MM_LIMIT         13882L
#define ERROR_IPSEC_IKE_NEGOTIATION_DISABLED 13883L
#define ERROR_IPSEC_IKE_QM_LIMIT         13884L
#define ERROR_IPSEC_IKE_MM_EXPIRED       13885L
#define ERROR_IPSEC_IKE_PEER_MM_ASSUMED_INVALID 13886L
#define ERROR_IPSEC_IKE_CERT_CHAIN_POLICY_MISMATCH 13887L
#define ERROR_IPSEC_IKE_UNEXPECTED_MESSAGE_ID 13888L
#define ERROR_IPSEC_IKE_INVALID_AUTH_PAYLOAD 13889L
#define ERROR_IPSEC_IKE_DOS_COOKIE_SENT  13890L
#define ERROR_IPSEC_IKE_SHUTTING_DOWN    13891L
#define ERROR_IPSEC_IKE_CGA_AUTH_FAILED  13892L
#define ERROR_IPSEC_IKE_PROCESS_ERR_NATOA 13893L
#define ERROR_IPSEC_IKE_INVALID_MM_FOR_QM 13894L
#define ERROR_IPSEC_IKE_QM_EXPIRED       13895L
#define ERROR_IPSEC_IKE_TOO_MANY_FILTERS 13896L
#define ERROR_IPSEC_IKE_NEG_STATUS_END   13897L
#define ERROR_IPSEC_IKE_KILL_DUMMY_NAP_TUNNEL 13898L
#define ERROR_IPSEC_IKE_INNER_IP_ASSIGNMENT_FAILURE 13899L
#define ERROR_IPSEC_IKE_REQUIRE_CP_PAYLOAD_MISSING 13900L
#define ERROR_IPSEC_KEY_MODULE_IMPERSONATION_NEGOTIATION_PENDING 13901L
#define ERROR_IPSEC_IKE_COEXISTENCE_SUPPRESS 13902L
#define ERROR_IPSEC_IKE_RATELIMIT_DROP   13903L
#define ERROR_IPSEC_IKE_PEER_DOESNT_SUPPORT_MOBIKE 13904L
#define ERROR_IPSEC_IKE_AUTHORIZATION_FAILURE 13905L
#define ERROR_IPSEC_IKE_STRONG_CRED_AUTHORIZATION_FAILURE 13906L
#define ERROR_IPSEC_IKE_AUTHORIZATION_FAILURE_WITH_OPTIONAL_RETRY 13907L
#define ERROR_IPSEC_IKE_STRONG_CRED_AUTHORIZATION_AND_CERTMAP_FAILURE 13908L
#define ERROR_IPSEC_IKE_NEG_STATUS_EXTENDED_END 13909L
#define ERROR_IPSEC_BAD_SPI              13910L
#define ERROR_IPSEC_SA_LIFETIME_EXPIRED  13911L
#define ERROR_IPSEC_WRONG_SA             13912L
#define ERROR_IPSEC_REPLAY_CHECK_FAILED  13913L
#define ERROR_IPSEC_INVALID_PACKET       13914L
#define ERROR_IPSEC_INTEGRITY_CHECK_FAILED 13915L
#define ERROR_IPSEC_CLEAR_TEXT_DROP      13916L
#define ERROR_IPSEC_AUTH_FIREWALL_DROP   13917L
#define ERROR_IPSEC_THROTTLE_DROP        13918L
#define ERROR_IPSEC_DOSP_BLOCK           13925L
#define ERROR_IPSEC_DOSP_RECEIVED_MULTICAST 13926L
#define ERROR_IPSEC_DOSP_INVALID_PACKET  13927L
#define ERROR_IPSEC_DOSP_STATE_LOOKUP_FAILED 13928L
#define ERROR_IPSEC_DOSP_MAX_ENTRIES     13929L
#define ERROR_IPSEC_DOSP_KEYMOD_NOT_ALLOWED 13930L
#define ERROR_IPSEC_DOSP_NOT_INSTALLED   13931L
#define ERROR_IPSEC_DOSP_MAX_PER_IP_RATELIMIT_QUEUES 13932L
#define ERROR_SXS_SECTION_NOT_FOUND      14000L
#define ERROR_SXS_CANT_GEN_ACTCTX        14001L
#define ERROR_SXS_INVALID_ACTCTXDATA_FORMAT 14002L
#define ERROR_SXS_ASSEMBLY_NOT_FOUND     14003L
#define ERROR_SXS_MANIFEST_FORMAT_ERROR  14004L
#define ERROR_SXS_MANIFEST_PARSE_ERROR   14005L
#define ERROR_SXS_ACTIVATION_CONTEXT_DISABLED 14006L
#define ERROR_SXS_KEY_NOT_FOUND          14007L
#define ERROR_SXS_VERSION_CONFLICT       14008L
#define ERROR_SXS_WRONG_SECTION_TYPE     14009L
#define ERROR_SXS_THREAD_QUERIES_DISABLED 14010L
#define ERROR_SXS_PROCESS_DEFAULT_ALREADY_SET 14011L
#define ERROR_SXS_UNKNOWN_ENCODING_GROUP 14012L
#define ERROR_SXS_UNKNOWN_ENCODING       14013L
#define ERROR_SXS_INVALID_XML_NAMESPACE_URI 14014L
#define ERROR_SXS_ROOT_MANIFEST_DEPENDENCY_NOT_INSTALLED 14015L
#define ERROR_SXS_LEAF_MANIFEST_DEPENDENCY_NOT_INSTALLED 14016L
#define ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE 14017L
#define ERROR_SXS_MANIFEST_MISSING_REQUIRED_DEFAULT_NAMESPACE 14018L
#define ERROR_SXS_MANIFEST_INVALID_REQUIRED_DEFAULT_NAMESPACE 14019L
#define ERROR_SXS_PRIVATE_MANIFEST_CROSS_PATH_WITH_REPARSE_POINT 14020L
#define ERROR_SXS_DUPLICATE_DLL_NAME     14021L
#define ERROR_SXS_DUPLICATE_WINDOWCLASS_NAME 14022L
#define ERROR_SXS_DUPLICATE_CLSID        14023L
#define ERROR_SXS_DUPLICATE_IID          14024L
#define ERROR_SXS_DUPLICATE_TLBID        14025L
#define ERROR_SXS_DUPLICATE_PROGID       14026L
#define ERROR_SXS_DUPLICATE_ASSEMBLY_NAME 14027L
#define ERROR_SXS_FILE_HASH_MISMATCH     14028L
#define ERROR_SXS_POLICY_PARSE_ERROR     14029L
#define ERROR_SXS_XML_E_MISSINGQUOTE     14030L
#define ERROR_SXS_XML_E_COMMENTSYNTAX    14031L
#define ERROR_SXS_XML_E_BADSTARTNAMECHAR 14032L
#define ERROR_SXS_XML_E_BADNAMECHAR      14033L
#define ERROR_SXS_XML_E_BADCHARINSTRING  14034L
#define ERROR_SXS_XML_E_XMLDECLSYNTAX    14035L
#define ERROR_SXS_XML_E_BADCHARDATA      14036L
#define ERROR_SXS_XML_E_MISSINGWHITESPACE 14037L
#define ERROR_SXS_XML_E_EXPECTINGTAGEND  14038L
#define ERROR_SXS_XML_E_MISSINGSEMICOLON 14039L
#define ERROR_SXS_XML_E_UNBALANCEDPAREN  14040L
#define ERROR_SXS_XML_E_INTERNALERROR    14041L
#define ERROR_SXS_XML_E_UNEXPECTED_WHITESPACE 14042L
#define ERROR_SXS_XML_E_INCOMPLETE_ENCODING 14043L
#define ERROR_SXS_XML_E_MISSING_PAREN    14044L
#define ERROR_SXS_XML_E_EXPECTINGCLOSEQUOTE 14045L
#define ERROR_SXS_XML_E_MULTIPLE_COLONS  14046L
#define ERROR_SXS_XML_E_INVALID_DECIMAL  14047L
#define ERROR_SXS_XML_E_INVALID_HEXIDECIMAL 14048L
#define ERROR_SXS_XML_E_INVALID_UNICODE  14049L
#define ERROR_SXS_XML_E_WHITESPACEORQUESTIONMARK 14050L
#define ERROR_SXS_XML_E_UNEXPECTEDENDTAG 14051L
#define ERROR_SXS_XML_E_UNCLOSEDTAG      14052L
#define ERROR_SXS_XML_E_DUPLICATEATTRIBUTE 14053L
#define ERROR_SXS_XML_E_MULTIPLEROOTS    14054L
#define ERROR_SXS_XML_E_INVALIDATROOTLEVEL 14055L
#define ERROR_SXS_XML_E_BADXMLDECL       14056L
#define ERROR_SXS_XML_E_MISSINGROOT      14057L
#define ERROR_SXS_XML_E_UNEXPECTEDEOF    14058L
#define ERROR_SXS_XML_E_BADPEREFINSUBSET 14059L
#define ERROR_SXS_XML_E_UNCLOSEDSTARTTAG 14060L
#define ERROR_SXS_XML_E_UNCLOSEDENDTAG   14061L
#define ERROR_SXS_XML_E_UNCLOSEDSTRING   14062L
#define ERROR_SXS_XML_E_UNCLOSEDCOMMENT  14063L
#define ERROR_SXS_XML_E_UNCLOSEDDECL     14064L
#define ERROR_SXS_XML_E_UNCLOSEDCDATA    14065L
#define ERROR_SXS_XML_E_RESERVEDNAMESPACE 14066L
#define ERROR_SXS_XML_E_INVALIDENCODING  14067L
#define ERROR_SXS_XML_E_INVALIDSWITCH    14068L
#define ERROR_SXS_XML_E_BADXMLCASE       14069L
#define ERROR_SXS_XML_E_INVALID_STANDALONE 14070L
#define ERROR_SXS_XML_E_UNEXPECTED_STANDALONE 14071L
#define ERROR_SXS_XML_E_INVALID_VERSION  14072L
#define ERROR_SXS_XML_E_MISSINGEQUALS    14073L
#define ERROR_SXS_PROTECTION_RECOVERY_FAILED 14074L
#define ERROR_SXS_PROTECTION_PUBLIC_KEY_TOO_SHORT 14075L
#define ERROR_SXS_PROTECTION_CATALOG_NOT_VALID 14076L
#define ERROR_SXS_UNTRANSLATABLE_HRESULT 14077L
#define ERROR_SXS_PROTECTION_CATALOG_FILE_MISSING 14078L
#define ERROR_SXS_MISSING_ASSEMBLY_IDENTITY_ATTRIBUTE 14079L
#define ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME 14080L
#define ERROR_SXS_ASSEMBLY_MISSING       14081L
#define ERROR_SXS_CORRUPT_ACTIVATION_STACK 14082L
#define ERROR_SXS_CORRUPTION             14083L
#define ERROR_SXS_EARLY_DEACTIVATION     14084L
#define ERROR_SXS_INVALID_DEACTIVATION   14085L
#define ERROR_SXS_MULTIPLE_DEACTIVATION  14086L
#define ERROR_SXS_PROCESS_TERMINATION_REQUESTED 14087L
#define ERROR_SXS_RELEASE_ACTIVATION_CONTEXT 14088L
#define ERROR_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY 14089L
#define ERROR_SXS_INVALID_IDENTITY_ATTRIBUTE_VALUE 14090L
#define ERROR_SXS_INVALID_IDENTITY_ATTRIBUTE_NAME 14091L
#define ERROR_SXS_IDENTITY_DUPLICATE_ATTRIBUTE 14092L
#define ERROR_SXS_IDENTITY_PARSE_ERROR   14093L
#define ERROR_MALFORMED_SUBSTITUTION_STRING 14094L
#define ERROR_SXS_INCORRECT_PUBLIC_KEY_TOKEN 14095L
#define ERROR_UNMAPPED_SUBSTITUTION_STRING 14096L
#define ERROR_SXS_ASSEMBLY_NOT_LOCKED    14097L
#define ERROR_SXS_COMPONENT_STORE_CORRUPT 14098L
#define ERROR_ADVANCED_INSTALLER_FAILED  14099L
#define ERROR_XML_ENCODING_MISMATCH      14100L
#define ERROR_SXS_MANIFEST_IDENTITY_SAME_BUT_CONTENTS_DIFFERENT 14101L
#define ERROR_SXS_IDENTITIES_DIFFERENT   14102L
#define ERROR_SXS_ASSEMBLY_IS_NOT_A_DEPLOYMENT 14103L
#define ERROR_SXS_FILE_NOT_PART_OF_ASSEMBLY 14104L
#define ERROR_SXS_MANIFEST_TOO_BIG       14105L
#define ERROR_SXS_SETTING_NOT_REGISTERED 14106L
#define ERROR_SXS_TRANSACTION_CLOSURE_INCOMPLETE 14107L
#define ERROR_SMI_PRIMITIVE_INSTALLER_FAILED 14108L
#define ERROR_GENERIC_COMMAND_FAILED     14109L
#define ERROR_SXS_FILE_HASH_MISSING      14110L
#define ERROR_EVT_INVALID_CHANNEL_PATH   15000L
#define ERROR_EVT_INVALID_QUERY          15001L
#define ERROR_EVT_PUBLISHER_METADATA_NOT_FOUND 15002L
#define ERROR_EVT_EVENT_TEMPLATE_NOT_FOUND 15003L
#define ERROR_EVT_INVALID_PUBLISHER_NAME 15004L
#define ERROR_EVT_INVALID_EVENT_DATA     15005L
#define ERROR_EVT_CHANNEL_NOT_FOUND      15007L
#define ERROR_EVT_MALFORMED_XML_TEXT     15008L
#define ERROR_EVT_SUBSCRIPTION_TO_DIRECT_CHANNEL 15009L
#define ERROR_EVT_CONFIGURATION_ERROR    15010L
#define ERROR_EVT_QUERY_RESULT_STALE     15011L
#define ERROR_EVT_QUERY_RESULT_INVALID_POSITION 15012L
#define ERROR_EVT_NON_VALIDATING_MSXML   15013L
#define ERROR_EVT_FILTER_ALREADYSCOPED   15014L
#define ERROR_EVT_FILTER_NOTELTSET       15015L
#define ERROR_EVT_FILTER_INVARG          15016L
#define ERROR_EVT_FILTER_INVTEST         15017L
#define ERROR_EVT_FILTER_INVTYPE         15018L
#define ERROR_EVT_FILTER_PARSEERR        15019L
#define ERROR_EVT_FILTER_UNSUPPORTEDOP   15020L
#define ERROR_EVT_FILTER_UNEXPECTEDTOKEN 15021L
#define ERROR_EVT_INVALID_OPERATION_OVER_ENABLED_DIRECT_CHANNEL 15022L
#define ERROR_EVT_INVALID_CHANNEL_PROPERTY_VALUE 15023L
#define ERROR_EVT_INVALID_PUBLISHER_PROPERTY_VALUE 15024L
#define ERROR_EVT_CHANNEL_CANNOT_ACTIVATE 15025L
#define ERROR_EVT_FILTER_TOO_COMPLEX     15026L
#define ERROR_EVT_MESSAGE_NOT_FOUND      15027L
#define ERROR_EVT_MESSAGE_ID_NOT_FOUND   15028L
#define ERROR_EVT_UNRESOLVED_VALUE_INSERT 15029L
#define ERROR_EVT_UNRESOLVED_PARAMETER_INSERT 15030L
#define ERROR_EVT_MAX_INSERTS_REACHED    15031L
#define ERROR_EVT_EVENT_DEFINITION_NOT_FOUND 15032L
#define ERROR_EVT_MESSAGE_LOCALE_NOT_FOUND 15033L
#define ERROR_EVT_VERSION_TOO_OLD        15034L
#define ERROR_EVT_VERSION_TOO_NEW        15035L
#define ERROR_EVT_CANNOT_OPEN_CHANNEL_OF_QUERY 15036L
#define ERROR_EVT_PUBLISHER_DISABLED     15037L
#define ERROR_EVT_FILTER_OUT_OF_RANGE    15038L
#define ERROR_EC_SUBSCRIPTION_CANNOT_ACTIVATE 15080L
#define ERROR_EC_LOG_DISABLED            15081L
#define ERROR_EC_CIRCULAR_FORWARDING     15082L
#define ERROR_EC_CREDSTORE_FULL          15083L
#define ERROR_EC_CRED_NOT_FOUND          15084L
#define ERROR_EC_NO_ACTIVE_CHANNEL       15085L
#define ERROR_MUI_FILE_NOT_FOUND         15100L
#define ERROR_MUI_INVALID_FILE           15101L
#define ERROR_MUI_INVALID_RC_CONFIG      15102L
#define ERROR_MUI_INVALID_LOCALE_NAME    15103L
#define ERROR_MUI_INVALID_ULTIMATEFALLBACK_NAME 15104L
#define ERROR_MUI_FILE_NOT_LOADED        15105L
#define ERROR_RESOURCE_ENUM_USER_STOP    15106L
#define ERROR_MUI_INTLSETTINGS_UILANG_NOT_INSTALLED 15107L
#define ERROR_MUI_INTLSETTINGS_INVALID_LOCALE_NAME 15108L
#define ERROR_MRM_RUNTIME_NO_DEFAULT_OR_NEUTRAL_RESOURCE 15110L
#define ERROR_MRM_INVALID_PRICONFIG      15111L
#define ERROR_MRM_INVALID_FILE_TYPE      15112L
#define ERROR_MRM_UNKNOWN_QUALIFIER      15113L
#define ERROR_MRM_INVALID_QUALIFIER_VALUE 15114L
#define ERROR_MRM_NO_CANDIDATE           15115L
#define ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE 15116L
#define ERROR_MRM_RESOURCE_TYPE_MISMATCH 15117L
#define ERROR_MRM_DUPLICATE_MAP_NAME     15118L
#define ERROR_MRM_DUPLICATE_ENTRY        15119L
#define ERROR_MRM_INVALID_RESOURCE_IDENTIFIER 15120L
#define ERROR_MRM_FILEPATH_TOO_LONG      15121L
#define ERROR_MRM_UNSUPPORTED_DIRECTORY_TYPE 15122L
#define ERROR_MRM_INVALID_PRI_FILE       15126L
#define ERROR_MRM_NAMED_RESOURCE_NOT_FOUND 15127L
#define ERROR_MRM_MAP_NOT_FOUND          15135L
#define ERROR_MRM_UNSUPPORTED_PROFILE_TYPE 15136L
#define ERROR_MRM_INVALID_QUALIFIER_OPERATOR 15137L
#define ERROR_MRM_INDETERMINATE_QUALIFIER_VALUE 15138L
#define ERROR_MRM_AUTOMERGE_ENABLED      15139L
#define ERROR_MRM_TOO_MANY_RESOURCES     15140L
#define ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_MERGE 15141L
#define ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE 15142L
#define ERROR_MRM_NO_CURRENT_VIEW_ON_THREAD 15143L
#define ERROR_DIFFERENT_PROFILE_RESOURCE_MANAGER_EXIST 15144L
#define ERROR_OPERATION_NOT_ALLOWED_FROM_SYSTEM_COMPONENT 15145L
#define ERROR_MRM_DIRECT_REF_TO_NON_DEFAULT_RESOURCE 15146L
#define ERROR_MRM_GENERATION_COUNT_MISMATCH 15147L
#define ERROR_PRI_MERGE_VERSION_MISMATCH 15148L
#define ERROR_PRI_MERGE_MISSING_SCHEMA   15149L
#define ERROR_PRI_MERGE_LOAD_FILE_FAILED 15150L
#define ERROR_PRI_MERGE_ADD_FILE_FAILED  15151L
#define ERROR_PRI_MERGE_WRITE_FILE_FAILED 15152L
#define ERROR_MCA_INVALID_CAPABILITIES_STRING 15200L
#define ERROR_MCA_INVALID_VCP_VERSION    15201L
#define ERROR_MCA_MONITOR_VIOLATES_MCCS_SPECIFICATION 15202L
#define ERROR_MCA_MCCS_VERSION_MISMATCH  15203L
#define ERROR_MCA_UNSUPPORTED_MCCS_VERSION 15204L
#define ERROR_MCA_INTERNAL_ERROR         15205L
#define ERROR_MCA_INVALID_TECHNOLOGY_TYPE_RETURNED 15206L
#define ERROR_MCA_UNSUPPORTED_COLOR_TEMPERATURE 15207L
#define ERROR_AMBIGUOUS_SYSTEM_DEVICE    15250L
#define ERROR_SYSTEM_DEVICE_NOT_FOUND    15299L
#define ERROR_HASH_NOT_SUPPORTED         15300L
#define ERROR_HASH_NOT_PRESENT           15301L
#define ERROR_SECONDARY_IC_PROVIDER_NOT_REGISTERED 15321L
#define ERROR_GPIO_CLIENT_INFORMATION_INVALID 15322L
#define ERROR_GPIO_VERSION_NOT_SUPPORTED 15323L
#define ERROR_GPIO_INVALID_REGISTRATION_PACKET 15324L
#define ERROR_GPIO_OPERATION_DENIED      15325L
#define ERROR_GPIO_INCOMPATIBLE_CONNECT_MODE 15326L
#define ERROR_GPIO_INTERRUPT_ALREADY_UNMASKED 15327L
#define ERROR_CANNOT_SWITCH_RUNLEVEL     15400L
#define ERROR_INVALID_RUNLEVEL_SETTING   15401L
#define ERROR_RUNLEVEL_SWITCH_TIMEOUT    15402L
#define ERROR_RUNLEVEL_SWITCH_AGENT_TIMEOUT 15403L
#define ERROR_RUNLEVEL_SWITCH_IN_PROGRESS 15404L
#define ERROR_SERVICES_FAILED_AUTOSTART  15405L
#define ERROR_COM_TASK_STOP_PENDING      15501L
#define ERROR_INSTALL_OPEN_PACKAGE_FAILED 15600L
#define ERROR_INSTALL_PACKAGE_NOT_FOUND  15601L
#define ERROR_INSTALL_INVALID_PACKAGE    15602L
#define ERROR_INSTALL_RESOLVE_DEPENDENCY_FAILED 15603L
#define ERROR_INSTALL_OUT_OF_DISK_SPACE  15604L
#define ERROR_INSTALL_NETWORK_FAILURE    15605L
#define ERROR_INSTALL_REGISTRATION_FAILURE 15606L
#define ERROR_INSTALL_DEREGISTRATION_FAILURE 15607L
#define ERROR_INSTALL_CANCEL             15608L
#define ERROR_INSTALL_FAILED             15609L
#define ERROR_REMOVE_FAILED              15610L
#define ERROR_PACKAGE_ALREADY_EXISTS     15611L
#define ERROR_NEEDS_REMEDIATION          15612L
#define ERROR_INSTALL_PREREQUISITE_FAILED 15613L
#define ERROR_PACKAGE_REPOSITORY_CORRUPTED 15614L
#define ERROR_INSTALL_POLICY_FAILURE     15615L
#define ERROR_PACKAGE_UPDATING           15616L
#define ERROR_DEPLOYMENT_BLOCKED_BY_POLICY 15617L
#define ERROR_PACKAGES_IN_USE            15618L
#define ERROR_RECOVERY_FILE_CORRUPT      15619L
#define ERROR_INVALID_STAGED_SIGNATURE   15620L
#define ERROR_DELETING_EXISTING_APPLICATIONDATA_STORE_FAILED 15621L
#define ERROR_INSTALL_PACKAGE_DOWNGRADE  15622L
#define ERROR_SYSTEM_NEEDS_REMEDIATION   15623L
#define ERROR_APPX_INTEGRITY_FAILURE_CLR_NGEN 15624L
#define ERROR_RESILIENCY_FILE_CORRUPT    15625L
#define ERROR_INSTALL_FIREWALL_SERVICE_NOT_RUNNING 15626L
#define ERROR_PACKAGE_MOVE_FAILED        15627L
#define ERROR_INSTALL_VOLUME_NOT_EMPTY   15628L
#define ERROR_INSTALL_VOLUME_OFFLINE     15629L
#define ERROR_INSTALL_VOLUME_CORRUPT     15630L
#define ERROR_NEEDS_REGISTRATION         15631L
#define ERROR_INSTALL_WRONG_PROCESSOR_ARCHITECTURE 15632L
#define ERROR_DEV_SIDELOAD_LIMIT_EXCEEDED 15633L
#define ERROR_INSTALL_OPTIONAL_PACKAGE_REQUIRES_MAIN_PACKAGE 15634L
#define ERROR_PACKAGE_NOT_SUPPORTED_ON_FILESYSTEM 15635L
#define APPMODEL_ERROR_NO_PACKAGE        15700L
#define APPMODEL_ERROR_PACKAGE_RUNTIME_CORRUPT 15701L
#define APPMODEL_ERROR_PACKAGE_IDENTITY_CORRUPT 15702L
#define APPMODEL_ERROR_NO_APPLICATION    15703L
#define APPMODEL_ERROR_DYNAMIC_PROPERTY_READ_FAILED 15704L
#define APPMODEL_ERROR_DYNAMIC_PROPERTY_INVALID 15705L
#define APPMODEL_ERROR_PACKAGE_NOT_AVAILABLE 15706L
#define ERROR_STATE_LOAD_STORE_FAILED    15800L
#define ERROR_STATE_GET_VERSION_FAILED   15801L
#define ERROR_STATE_SET_VERSION_FAILED   15802L
#define ERROR_STATE_STRUCTURED_RESET_FAILED 15803L
#define ERROR_STATE_OPEN_CONTAINER_FAILED 15804L
#define ERROR_STATE_CREATE_CONTAINER_FAILED 15805L
#define ERROR_STATE_DELETE_CONTAINER_FAILED 15806L
#define ERROR_STATE_READ_SETTING_FAILED  15807L
#define ERROR_STATE_WRITE_SETTING_FAILED 15808L
#define ERROR_STATE_DELETE_SETTING_FAILED 15809L
#define ERROR_STATE_QUERY_SETTING_FAILED 15810L
#define ERROR_STATE_READ_COMPOSITE_SETTING_FAILED 15811L
#define ERROR_STATE_WRITE_COMPOSITE_SETTING_FAILED 15812L
#define ERROR_STATE_ENUMERATE_CONTAINER_FAILED 15813L
#define ERROR_STATE_ENUMERATE_SETTINGS_FAILED 15814L
#define ERROR_STATE_COMPOSITE_SETTING_VALUE_SIZE_LIMIT_EXCEEDED 15815L
#define ERROR_STATE_SETTING_VALUE_SIZE_LIMIT_EXCEEDED 15816L
#define ERROR_STATE_SETTING_NAME_SIZE_LIMIT_EXCEEDED 15817L
#define ERROR_STATE_CONTAINER_NAME_SIZE_LIMIT_EXCEEDED 15818L
#define ERROR_API_UNAVAILABLE            15841L
#define STORE_ERROR_UNLICENSED           15861L
#define STORE_ERROR_UNLICENSED_USER      15862L
#define STORE_ERROR_PENDING_COM_TRANSACTION 15863L
#define STORE_ERROR_LICENSE_REVOKED      15864L
        
#pragma endregion
    }
    