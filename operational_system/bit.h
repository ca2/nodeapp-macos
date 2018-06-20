#pragma once


#if defined(__LP64__) || defined(_LP64)    // X64


//#error "test"
#define AMD64
#define OS64BIT
#define OSBIT 64
#if !defined(__LP64__)
#define __LP64__
#endif
#if !defined(_LP64)
#define _LP64
#endif



#else







#define X86
#define OS32BIT
#define OSBIT 32
#define _X86_






#endif




















