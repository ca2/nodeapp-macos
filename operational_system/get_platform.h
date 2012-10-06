#pragma once


#define MACOS


#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0


#define _POSIX_SOURCE 200809L
#define _POSIX_C_SOURCE 200809L
#define _DARWIN_C_SOURCE



#define DECL_C
//#define PASCAL


#define _PRE_WIDEN(x) L ## x
#define _WIDEN(x) _PRE_WIDEN(x)

#define NOTHROW throw()
#define THROWS // gnucc null throw statement means that the function can throw any exception


#ifdef _DEBUG
#define DEBUG
#endif // _DEBUG


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


typedef uint8_t byte;

#ifdef _LP64

typedef uint64_t dword_ptr;
#define int3264   int64_t

#else

typedef uint32_t dword_ptr;
#define int3264   int32_t

#endif


typedef void * PVOID;

#define _strcmpi strcasecmp

#define PURE = 0




#include "macos_system.h"


#define __stdcall




#include "bare_operational_system.h"        // Target version control


#include "cross/win/win.h"



