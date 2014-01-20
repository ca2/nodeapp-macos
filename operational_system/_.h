#pragma once


#define MACOS


#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0


#define _POSIX_SOURCE 200809L
#define _POSIX_C_SOURCE 200809L
#define _DARWIN_C_SOURCE

#define CLASS_DECL_IMPORT
#define CLASS_DECL_EXPORT
#define CLASS_DECL_THREAD __thread

#define DECL_C
//#define PASCAL


#define _PRE_WIDEN(x) L ## x
#define _WIDEN(x) _PRE_WIDEN(x)

#define NOTHROW throw()
#define THROWS // gnucc null throw statement means that the function can throw any exception



#ifdef DEBUG

#define RELEASENOTHROW

#else

#define RELEASENOTHROW throw()

#endif




#include <inttypes.h>

#define DWORD     uint32_t
#define BYTE      uint8_t

//#define NULL 0
#define _strcmpi strcasecmp

#include <stdlib.h>


#ifdef _LP64

typedef int64_t int_ptr;
typedef uint64_t uint_ptr;
#define int3264   int64_t

#else

typedef int32_t int_ptr;
typedef uint32_t uint_ptr;
#define int3264   int32_t

#endif


typedef void * PVOID;

#define _strcmpi strcasecmp


#ifdef _LP64
#define OS64BIT
#endif







