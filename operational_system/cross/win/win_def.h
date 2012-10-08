#pragma once

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

// Win32 defines _WIN32 automatically,
// but Macintosh doesn't, so if we are using
// Win32 Functions, we must do it here

#ifdef __cplusplus
extern "C" {
#endif


/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal

#define far
#define near
#if (!defined(_MAC)) && ((_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED))
#define pascal __stdcall
#else
#define pascal
#endif

#if defined(DOSWIN32) || defined(_MAC)
#define cdecl _cdecl
#ifndef CDECL
#define CDECL _cdecl
#endif
#else
#define cdecl
#ifndef CDECL
#define CDECL
#endif
#endif

#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif

#ifdef _M_CEE_PURE
#define WINAPI_INLINE  __clrcall
#else
#define WINAPI_INLINE  WINAPI
#endif

#undef FAR
#undef  NEAR
#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif

typedef unsigned int       DWORD;
typedef int                 WINBOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef WINBOOL near           *PBOOL;
typedef WINBOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef int far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

#ifndef NT_INCLUDED
#include "win_nt.h"
#endif /* NT_INCLUDED */

// xxx #include <specstrings.h>

/* Types use for passing & returning polymorphic values */
typedef uint_ptr            WPARAM;
typedef long_ptr            LPARAM;
typedef long_ptr            LRESULT;


#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((dword_ptr)(a)) & 0xff)) | ((WORD)((BYTE)(((dword_ptr)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((dword_ptr)(a)) & 0xffff)) | ((DWORD)((WORD)(((dword_ptr)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((dword_ptr)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((dword_ptr)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((dword_ptr)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((dword_ptr)(w)) >> 8) & 0xff))


#ifndef WIN_INTERNAL
//DECLARE_HANDLE            (HWND);
//DECLARE_HANDLE            (HHOOK);
#ifdef WINABLE
//DECLARE_HANDLE            (HEVENT);
#endif
#endif

typedef WORD                ATOM;

/*typedef HANDLE NEAR         *SPHANDLE;
typedef HANDLE FAR          *LPHANDLE;
typedef HANDLE              HGLOBAL;
typedef HANDLE              HLOCAL;
typedef HANDLE              GLOBALHANDLE;
typedef HANDLE              LOCALHANDLE;*/
#ifndef _MANAGED
#ifndef _MAC
#ifdef _WIN64
typedef int_ptr (FAR WINAPI *FARPROC)();
typedef int_ptr (NEAR WINAPI *NEARPROC)();
typedef int_ptr (WINAPI *PROC)();
#else
typedef int (FAR WINAPI *FARPROC)();
typedef int (NEAR WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();
#endif  // _WIN64
#else
typedef int (CALLBACK *FARPROC)();
typedef int (CALLBACK *NEARPROC)();
typedef int (CALLBACK *PROC)();
#endif
#else
typedef int_ptr (WINAPI *FARPROC)(void);
typedef int_ptr (WINAPI *NEARPROC)(void);
typedef int_ptr (WINAPI *PROC)(void);
#endif

/*#if !defined(_MAC) || !defined(GDI_INTERNAL)
#ifdef STRICT
typedef void NEAR* HGDIOBJ;
#else
DECLARE_HANDLE(HGDIOBJ);
#endif
#endif*/

/*DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;

#if !defined(_MAC) || !defined(WIN_INTERNAL)
DECLARE_HANDLE(HACCEL);
#endif
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HBRUSH);
#endif
#if(WINVER >= 0x0400)
DECLARE_HANDLE(HCOLORSPACE);
#endif /* WINVER >= 0x0400 */
/*#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HDC);
#endif
DECLARE_HANDLE(HGLRC);          // OpenGL
DECLARE_HANDLE(HDESK);
DECLARE_HANDLE(HENHMETAFILE);
#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HFONT);
#endif
DECLARE_HANDLE(HICON);
#if !defined(_MAC) || !defined(WIN_INTERNAL)
DECLARE_HANDLE(HMENU);
#endif
DECLARE_HANDLE(HMETAFILE);*/
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */
/*#if !defined(_MAC) || !defined(GDI_INTERNAL)
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HPEN);
#endif
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSPRITE);
DECLARE_HANDLE(HLSURF);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);

#if(WINVER >= 0x0400)
DECLARE_HANDLE(HWINEVENTHOOK);
#endif /* WINVER >= 0x0400 */

/*#if(WINVER >= 0x0500)
#ifndef _MAC
DECLARE_HANDLE(HMONITOR);
#endif
DECLARE_HANDLE(HUMPD);
#endif /* WINVER >= 0x0500 */

/*#ifndef _MAC
typedef int HFILE;
typedef HICON HCURSOR;      /* HICONs & HCURSORs are polymorphic */
//#else
//typedef short HFILE;
//DECLARE_HANDLE(HCURSOR);    /* HICONs & HCURSORs are not polymorphic */
//#endif

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

#define HFILE_ERROR ((HFILE)-1)

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;

typedef const RECT FAR* LPCRECT;

typedef struct _RECTL       /* rcl */
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECTL, *PRECTL, *LPRECTL;

typedef const RECTL FAR* LPCRECTL;

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct _POINTL      /* ptl  */
{
    LONG  x;
    LONG  y;
} POINTL, *PPOINTL;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

typedef SIZE               SIZEL;
typedef SIZE               *PSIZEL, *LPSIZEL;

typedef struct tagPOINTS
{
#ifndef _MAC
    SHORT   x;
    SHORT   y;
#else
    SHORT   y;
    SHORT   x;
#endif
} POINTS, *PPOINTS, *LPPOINTS;

//
//  File System time stamps are represented with the following structure:
//

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#define _FILETIME_


/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_SIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#ifdef __cplusplus
}
#endif

//typedef void * HGLOBAL;
