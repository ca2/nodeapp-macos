#pragma once

#ifndef _TIME64_T_DEFINED
#if __WORDSIZE != 64
#error "error: for ca2, long should 8-byte on MACOS i.e. 64-bit Mac OS X compilation, currently"
#endif
typedef long __time64_t;     /* 64-bit time value */
//#define __time64_t __time_t
#define _TIME64_T_DEFINED
#endif


/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif
