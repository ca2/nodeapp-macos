#pragma once




#if defined(_M_X64)

    typedef long int INT_PTR, *PINT_PTR;
    typedef unsigned long int UINT_PTR, *PUINT_PTR;

    typedef long long LONG_PTR, *PLONG_PTR;
    typedef unsigned long long ULONG_PTR, *PULONG_PTR;

#else
    typedef int INT_PTR, *PINT_PTR;
    typedef unsigned int UINT_PTR, *PUINT_PTR;

    typedef long LONG_PTR, *PLONG_PTR;
    typedef unsigned int ULONG_PTR, *PULONG_PTR;
#endif


//typedef void * HANDLE;
//typedef void * HDC;
typedef unsigned char BYTE;
typedef unsigned int UINT;
//typedef INT_PTR WPARAM;
//typedef INT_PTR LPARAM;



#define __cdecl
#define _stdcall

// dbg alloc MS VC CRT
#define _NORMAL_BLOCK  1




#if ! defined(lint)
#define UNREFERENCED_PARAMETER(P)          (P)
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

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
