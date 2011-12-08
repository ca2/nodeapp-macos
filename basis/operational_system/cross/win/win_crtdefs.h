#pragma once

#ifndef _TIME64_T_DEFINED
//typedef int64_t __time64_t;     /* 64-bit time value */
#define __time64_t __time_t
#define _TIME64_T_DEFINED
#endif


/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif
