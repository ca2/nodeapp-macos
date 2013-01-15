#pragma once


#define SECURITY_MAC32


#include "app/appseed/ca/ca.h"


#define CLASS_DECL_mac


string get_error_message(DWORD dwError);

::ca::application *     win_instantiate_application(::ca::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

CLASS_DECL_mac WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_mac void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_mac WINBOOL AfxCheckMemory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_mac WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
   LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_mac void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_mac void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_mac void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_mac WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_mac void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "mac1.h"
#include "implementation.h"
#include "state.h"
#include "handle.h"
#include "dir.h"
#include "factory_exchange.h"
//#include "UACTools.h"
#include "window_draw.h"
#include "graphics_object.h"
#include "mac_graphics_path.h"
#include "bitmap.h"
#include "dib.h"
#include "palette.h"
#include "pen.h"
#include "font.h"
#include "brush.h"
#include "rgn.h"
#include "graphics.h"
//#include "draw_dib.h"
#include "thread.h"
#include "window.h"
#include "osi.h"
#include "port_forward.h"

#define NULL_REF(class) (*((class *) NULL))
//CLASS_DECL_mac WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::ca::thread * >(pthread)))
#define MAC_WINDOW(pwnd) (dynamic_cast < ::mac::window * > (dynamic_cast < ::ca::window * >(pwnd)))
#define MAC_DC(pgraphics) (dynamic_cast < ::mac::graphics * > (dynamic_cast < ::ca::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::mac::graphics * > (( ::ca::graphics * )(pgraphics)))
#define MAC_HDC(pgraphics) ((HDC)*(dynamic_cast < ::mac::graphics * > (dynamic_cast < ::ca::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::mac::graphics * > ((::ca::graphics *)(pgraphics))))
#define MAC_DIB(pdib) (dynamic_cast < ::mac::dib * > (dynamic_cast < ::ca::dib * >(pdib)))


#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 
#pragma comment(lib, "Wtsapi32.lib") 
#pragma comment(lib, "Secur32.lib") 
#pragma comment(lib, "Msimg32.lib") 
#pragma comment(lib, "Psapi.lib") 

CLASS_DECL_mac void _AfxTraceMsg(const char * lpszPrefix, gen::signal_object * pobj);
CLASS_DECL_mac void _AfxTraceMsg(const char * lpszPrefix, MESSAGE * lpmsg);

CLASS_DECL_mac WINBOOL __cdecl AfxIsIdleMessage(gen::signal_object * pobj);
CLASS_DECL_mac WINBOOL __cdecl AfxIsIdleMessage(MESSAGE * pMsg);


CLASS_DECL_mac void AfxProcessWndProcException(base_exception*, gen::signal_object * pobj);
CLASS_DECL_mac void __cdecl AfxPreTranslateMessage(gen::signal_object * pobj);


#include "application.h"