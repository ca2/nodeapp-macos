#pragma once


#define MACOS


#define _POSIX_SOURCE


#define DECL_C
//#define PASCAL


#define _PRE_WIDEN(x) L ## x
#define _WIDEN(x) _PRE_WIDEN(x)

#define NOTHROW throw()
#define THROWS // gnucc null throw statement means that the function can throw any exception


#define _DEBUG // ca2 is in debug - bugs come and go, always



#include <inttypes.h>

#define DWORD     uint32_t
#define BYTE      uint8_t

//#define NULL 0
#define _strcmpi strcasecmp

#include <stdlib.h>


typedef uint8_t byte;
typedef uint32_t DWORD_PTR;

 #define __int3264   int32_t

typedef void * PVOID;

#define _strcmpi strcasecmp

#ifndef _DEBUG
#define _DEBUG
#endif

#define PURE = 0


#define _X86_


#include "macos_system.h"
#define _ApplicationFrameworkDLL
#define _AFX_NO_OLE_SUPPORT



#ifndef _DEBUG
#define _DEBUG // ca2 is in debug - bugs come and go, always
#endif


#define __stdcall



#define if_then(p, q)  ((!(p))||(!(q)))


#include "bare_operational_system.h"        // Target version control


#include "cross/win/win.h"



