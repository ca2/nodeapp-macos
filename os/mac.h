#pragma once


#define SECURITY_WIN32


#include "app/appseed/ca2/ca2.h"


#define CLASS_DECL_DRAW2D_COCOA


string get_error_message(DWORD dwError);

::ca2::application *     mac_instantiate_application(::ca2::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_DRAW2D_COCOA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_DRAW2D_COCOA WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_DRAW2D_COCOA void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_DRAW2D_COCOA bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_DRAW2D_COCOA WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_DRAW2D_COCOA void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_DRAW2D_COCOA void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_DRAW2D_COCOA void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_DRAW2D_COCOA WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_DRAW2D_COCOA void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "mac1.h"
#include "mac_implementation.h"
#include "mac_state.h"
//#include "mac_handle.h"
// xxx #include "mac_file_find.h"
#include "mac_dir.h"
// xxx #include "mac_folder_watch.h"
#include "mac_factory_exchange.h"
#include "mac_window_draw.h"
#include "mac_thread.h"
#include "mac_window.h"
#include "mac_os.h"
#include "mac_port_forward.h"
#include "mac_copydesk.h"
#include "mac_crypt.h"
#include "mac_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_DRAW2D_COCOA WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::ca2::thread * >(pthread)))
#define MAC_WINDOW(pwnd) (dynamic_cast < ::mac::window * > (dynamic_cast < ::ca2::window * >(pwnd)))

#include "mac_shell.h"

CLASS_DECL_DRAW2D_COCOA void __trace_message(const char * lpszPrefix, ::ca2::signal_object * pobj);
CLASS_DECL_DRAW2D_COCOA void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_DRAW2D_COCOA WINBOOL __cdecl __is_idle_message(::ca2::signal_object * pobj);
CLASS_DECL_DRAW2D_COCOA WINBOOL __cdecl __is_idle_message(MESSAGE* pMsg);


CLASS_DECL_DRAW2D_COCOA void AfxProcessWndProcException(base_exception*, ::ca2::signal_object * pobj);
CLASS_DECL_DRAW2D_COCOA void __cdecl __pre_translate_message(::ca2::signal_object * pobj);
#include "mac_printer.h"

#include "mac_application.h"



WINBOOL PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);

WINBOOL GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);



int32_t CLASS_DECL_DRAW2D_COCOA __mac_main(int32_t argc, char * argv[]);


CLASS_DECL_DRAW2D_COCOA void vfxThrowFileException(::ca2::application * papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);
