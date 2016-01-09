#pragma once


#include <inttypes.h>




#if OSBIT == 64

    typedef int64_t int_ptr, *pint_ptr;
    typedef uint64_t uint_ptr, *puint_ptr;

    typedef int64_t long_ptr, *plong_ptr;
    //typedef uint64_t ulong_ptr, *pulong_ptr;

//    typedef uint64_t dword_ptr;


#else

    typedef int32_t int_ptr, *pint_ptr;
    typedef uint32_t uint_ptr, *puint_ptr;

    typedef int32_t long_ptr, *plong_ptr;
//    typedef uint32_t ulong_ptr, *pulong_ptr;

//	typedef uint32_t dword_ptr;


#define __int3264   int32_t


#endif


typedef unsigned char BYTE;
typedef uint32_t UINT;

