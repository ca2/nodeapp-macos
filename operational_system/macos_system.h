#pragma once



#ifdef __MM


#import <Cocoa/Cocoa.h>


#endif



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

#include "oswindow.h"




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
