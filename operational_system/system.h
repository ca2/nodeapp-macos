//
//  _c.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/18/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once

#define index os_index


#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0


//#define _DARWIN_C_SOURCE
//#define _POSIX_SOURCE 200809L
//#define _POSIX_C_SOURCE 200809L

//#include <inttypes.h>
//#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <errno.h>
#include <sys/time.h>

#include "_stdint.h"


/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef __cplusplus


#include <new>


#endif





#define _strdup strdup
#define _stricmp stricmp


struct device_context;
struct gdi_object;


typedef struct device_context * HDC;
typedef struct gdi_object * HGDIOBJ;


#define DECL_SPEC_ANY


// STRICT is the only supported option (NOSTRICT is no longer supported)
#ifndef STRICT
#define STRICT 1
#endif

#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#if defined(__MM) || defined(__M)

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>

#endif

#include <Carbon/Carbon.h>

#if DEBUG
#undef DEBUG
#define DEBUG
#else
#undef DEBUG
#endif



#ifndef EXPORT
#define EXPORT
#endif


#ifndef _X86_
#include "version_cpu.h"
#endif

#ifdef _ApplicationFrameworkDLL
#include "version_dylib.h"
#endif

inline void debug_break() { __asm("int $3"); }



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








#define MAX_DWORD_PTR ((uint_ptr)(-1))

#define TRUE 1
#define FALSE 0



#define MOVE_SEMANTICS


#define PURE = 0





//#pragma once






/*
#if defined(__LP64__)

typedef long int_ptr, *pint_ptr;
typedef unsigned long int uint_ptr, *puint_ptr;

typedef long long int_ptr, *plong_ptr;
typedef unsigned long long uint_ptr, *pulong_ptr;

#else
typedef int int_ptr, *pint_ptr;
typedef unsigned int uint_ptr, *puint_ptr;

typedef long int_ptr, *plong_ptr;
typedef unsigned int uint_ptr, *pulong_ptr;
#endif
*/

/* Types use for passing & returning polymorphic values */
//typedef uint_ptr            WPARAM;
//typedef int_ptr            LPARAM;
//typedef int_ptr            LRESULT;


//typedef void * HANDLE;
//typedef void * HDC;
//typedef unsigned char BYTE;
//typedef unsigned int UINT;
//typedef int_ptr WPARAM;
//typedef int_ptr LPARAM;



#define __cdecl
#define _stdcall

// dbg alloc MS VC CRT
#define _NORMAL_BLOCK  1

//#include "oswindow.h"




#if ! defined(lint)
//#define UNREFERENCED_PARAMETER(P)
//#define DBG_UNREFERENCED_PARAMETER(P)
//#define DBG_UNREFERENCED_LOCAL_VARIABLE(V)

#else // lint

// Note: lint -e530 says don't complain about uninitialized variables for
// this varible.  Error 527 has to do with unreachable code.
// -restore restores checking to the -save state

#define UNREFERENCED_PARAMETER(P)          \
/*lint -save -e527 -e530 */ \
{ \
(P) = (P); \
} \
/*lint -restore */
#define DBG_UNREFERENCED_PARAMETER(P)      \
/*lint -save -e527 -e530 */ \
{ \
(P) = (P); \
} \
/*lint -restore */
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) \
/*lint -save -e527 -e530 */ \
{ \
(V) = (V); \
} \
/*lint -restore */

#endif // lint

#define __stdcall




















#define DECL_C



#define _PRE_WIDEN(x) L ## x
#ifdef WINDOWS
#define _WIDEN(x) _PRE_WIDEN(x)
#else
#define _WIDEN(x) unitext(x)
#endif

#define NOTHROW throw()
#define THROWS // gnucc null _throw( statement means that the function can _throw( any exception

#define _WCHAR_T_DEFINED

#ifdef DEBUG

#define RELEASENOTHROW

#else

#define RELEASENOTHROW throw()

#endif


#define DWORD     uint32_t
#define BYTE      uint8_t


#define _strcmpi strcasecmp


#ifdef _LP64

//typedef int64_t int_ptr;
//typedef uint64_t uint_ptr;
#define int3264   int64_t

#else

//typedef int32_t int_ptr;
//typedef uint32_t uint_ptr;
#define int3264   int32_t

#endif


typedef void * PVOID;


#define _strcmpi strcasecmp


#ifdef _LP64
#define OS64BIT
#endif


#include <pthread.h>


/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


typedef unsigned short     unichar;
typedef wchar_t            unichar32;



#undef index


#define WINBOOL int



