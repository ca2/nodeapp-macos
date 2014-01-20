#pragma once





#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// from C++ Sockets Library
// ----------------------------------------
// common unix includes / defines
//#include <unistd.h>
//#include <sys/time.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>



#define _strdup strdup
#define _stricmp stricmp


#ifndef _XSERVER64
#ifndef _XTYPEDEF_XID
#define _XTYPEDEF_XID
typedef unsigned long XID;
#endif
#endif


struct device_context;
struct gdi_object;

typedef XID Window;


typedef struct device_context * HDC;
typedef struct gdi_object * HGDIOBJ;

union _XEvent;

typedef union _XEvent XEvent;



//typedef Font HFONT;



#define DECL_SPEC_ANY


/////////////////////////////////////////////////////////////////////////////
// Master version numbers

#define _AFX     1      // Microsoft Application Framework Classes
#ifndef _MFC_VER
#define _MFC_VER 0x0800 // Microsoft Foundation Classes version 8.00
#endif



/////////////////////////////////////////////////////////////////////////////
// Special configurations

// _AFXEXT implies _ApplicationFrameworkDLL
#if defined(_AFXEXT) && !defined(_ApplicationFrameworkDLL)
	#define _ApplicationFrameworkDLL
#endif

#if defined(_ApplicationFrameworkDLL) && !defined(_DLL) && defined(WIN32)
//	#error Please use the /MD switch for _ApplicationFrameworkDLL builds
#endif

#if defined(_ApplicationFrameworkDLL) && !defined(_MT) && defined(WIN32)
	#error Please use the /MD switch (multithreaded DLL C-runtime)
#endif


#include "version_macos.h"

// Include any non-Intel platform specific items
#ifndef _X86_
	#include "version_cpu.h"
#endif

#ifdef _ApplicationFrameworkDLL
	#include "version_dylib.h"
#endif

inline void __debug_break() { __asm("int $3"); }



/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined
/////////////////////////////////////////////////////////////////////////////

// SIZE_T_MAX is used by the collection classes
#ifndef SIZE_T_MAX
	#define SIZE_T_MAX  UINT_MAX
#endif

// PASCAL is used for static member functions
/*#ifndef PASCAL
	#define PASCAL
#endif*/

// FASTCALL is used for static member functions with little or no params
#ifndef FASTCALL
	#define FASTCALL
#endif

// CDECL and EXPORT are defined in case WINDOWS.H doesn't
#ifndef CDECL
	#define CDECL
#endif

#ifndef EXPORT
	#define EXPORT
#endif

// UNALIGNED is used for unaligned data access (in CArchive mostly)
#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

// AFX_DEPRECATED is used for functions that should no longer be used
#ifndef AFX_DEPRECATED
#ifdef _AFX_DISABLE_DEPRECATED
	#define AFX_DEPRECATED(_Message)
#else
	#define AFX_DEPRECATED(_Message) __declspec(deprecated(_Message))
#endif
#endif

// _AFX_INSECURE_DEPRECATE is used for deprecated, insecure functions.
#ifndef _AFX_INSECURE_DEPRECATE
#ifdef _AFX_SECURE_NO_DEPRECATE
#define _AFX_INSECURE_DEPRECATE(_Message)
#else
#define _AFX_INSECURE_DEPRECATE(_Message) __declspec(deprecated(_Message))
#endif // _AFX_SECURE_NO_DEPRECATE
#endif // _AFX_INSECURE_DEPRECATE

// AFXAPI is used on global public functions
#ifndef AFXAPI
	#define AFXAPI //__stdcall
#endif

// AFXOLEAPI is used for some special OLE functions
#ifndef AFXOLEAPI
	#define AFXOLEAPI __stdcall
#endif

// c_cdecl is used for rare functions taking variable arguments
#ifndef c_cdecl
	#define c_cdecl __cdecl
#endif

// AFX_EXPORT is used for functions which need to be exported
#ifndef AFX_EXPORT
	#define AFX_EXPORT EXPORT
#endif

#ifndef __STATIC
	#define __STATIC extern
	#define __STATIC_DATA extern __declspec(selectany)
#endif

// The following macros are used to enable export/import

// for data
#ifndef __DATA_EXPORT
	#define __DATA_EXPORT __declspec(dllexport)
#endif
#ifndef __DATA_IMPORT
	#define __DATA_IMPORT __declspec(dllimport)
#endif

// for classes
#ifndef AFX_CLASS_EXPORT
	#define AFX_CLASS_EXPORT __declspec(dllexport)
#endif
#ifndef AFX_CLASS_IMPORT
	#define AFX_CLASS_IMPORT __declspec(dllimport)
#endif

// for global APIs
#ifndef AFX_API_EXPORT
	#define AFX_API_EXPORT __declspec(dllexport)
#endif
#ifndef AFX_API_IMPORT
	#define AFX_API_IMPORT __declspec(dllimport)
#endif

// This macro is used to reduce size requirements of some classes
#ifndef AFX_ALWAYS_VTABLE
#ifndef AFX_NOVTABLE
#if _MSC_VER >= 1100 && !defined(_DEBUG)
#define AFX_NOVTABLE __declspec(novtable)
#else
#define AFX_NOVTABLE
#endif
#endif
#endif

// for global data that should be in COMDATs (packaged data)
#ifndef AFX_COMDAT
#define AFX_COMDAT __declspec(selectany)
#endif

// The following macros are used on data declarations/definitions
//  (they are redefined for extension DLLs and the shared MFC DLL)
#define __DATADEF
#define AFX_API CLASS_DECL_BOOT

// used when building the "core" MFC80.DLL
#ifndef __CORE_DATA
	#define __CORE_DATA CLASS_DECL_BOOT
	#define __CORE_DATADEF
#endif


// used when building extension DLLs
#ifndef AFX_EXT_DATA
	#define AFX_EXT_DATA
	#define AFX_EXT_DATADEF
	#define AFX_EXT_CLASS
	#define AFX_EXT_API
#endif

// BASED_XXXX macros are provided for backward compatibility
#ifndef BASED_CODE
	#define BASED_CODE
#endif

#ifndef BASED_DEBUG
	#define BASED_DEBUG
#endif

#ifndef BASED_STACK
	#define BASED_STACK
#endif





#include "version_cpu.h"







#ifdef _AFX_DEVBUILD
	#define AFX_IMPL_DATA __DATA_EXPORT
#else
	#define AFX_IMPL_DATA CLASS_DECL_BOOT
#endif


// #define _AFX_NOFORCE_LIBS
#define _AFX_FULLTYPEINFO
#define VC_EXTRALEAN
#define NO_ANSIUNI_ONLY
#define _MFC_OVERRIDES_NEW

#define MAX_DWORD_PTR ((uint_ptr)(-1))

#define TRUE 1
#define FALSE 0

#define max(x,y) (((x) > (y)) ? (x) : (y))
#define min(x,y) (((x) < (y)) ? (x) : (y))


#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

//#define LOWORD(x)  (x & 0xffff)
//#define HIWORD(x)  ((x >> 16) & 0xffff)





// str
//void strncpy(char * dest, const char * cat, int iLen);
/*
const char * stristr(const char * src, const char * find);
char to_lower(int ch);
char to_upper(int ch);
int stricmp(const char * sz1, const char * sz2);
int strcmp(const char * sz1, const char * sz2);
const char * strbegins(const char * sz1, const char * prefix);
char * strrch(char * sz, char ch);
void itoa(int i, char * sz, int radix);
void ltoa(long l, char * sz, int radix);
void ultoa(unsigned long ul, char * sz, int radix);
void i64toa(int64_t i, char * sz, int radix);
void ui64toa(uint64_t i, char * sz, int radix);
void str_reverse(char * sz);
void zero_pad(char * sz, int_ptr iPad);

char * strlwr(char * psz);
char * strupr(char * psz);

//void wcscat(wchar_t * dest, const wchar_t * cat);
//void wcscpy(wchar_t * dest, const wchar_t * cat);
//void wcsncpy(wchar_t * dest, const wchar_t * cat, int iLen);
//int  wcslen(const wchar_t * cat);
//const wchar_t * wcsdup(const wchar_t * src);
const wchar_t * wcsdup(const wchar_t * src, int iLen);
//const wchar_t * wcsstr(const wchar_t * src, const wchar_t * find);
const wchar_t * wcsistr(const wchar_t * src, const wchar_t * find);
wchar_t to_lower(wchar_t wch);
int wcsicmp(const wchar_t * sz1, const wchar_t * sz2);
//int wcscmp(const wchar_t * sz1, const wchar_t * sz2);
const wchar_t * wcsbegins(const wchar_t * sz1, const wchar_t * prefix);
wchar_t * wcsrch(wchar_t * sz, wchar_t ch);
void itoa(int i, wchar_t * sz, int radix);
void ltoa(long l, wchar_t * sz, int radix);
void ultow(unsigned long ul, wchar_t * sz, int radix);
void i64tow(int64_t i, wchar_t * sz, int radix);
void ui64tow(uint64_t i, wchar_t * sz, int radix);
void wcs_reverse(wchar_t * sz);
void zero_pad(wchar_t * sz, int iPad);

void wcslwr(wchar_t * psz);
void wcsupr(wchar_t * psz);

*/
/*
 #ifndef HWND_DEF
#define HWND_DEF
typedef class tag_WINDOW
{
public:
   
   WindowRef      m_windowref;
   void *         m_pnswindow;
   
   
   
} WINDOW, * LPWINDOW;

typedef LPWINDOW oswindow;
#endif
*/

#include "cross/win/win.h"
