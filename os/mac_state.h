#pragma once

#define slot___MODULE_THREAD_STATE 1
#define slot___THREAD_STATE 2

namespace mac
{
   class thread;
} // namespace mac

//#include "types.h"
//#include "template.h"

#ifndef __AFXTLS_H__
#include "mac_thread_slots.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ___DEBUG_STATE

#ifdef DEBUG

class ___DEBUG_STATE : public no_track_object
{
public:
   ___DEBUG_STATE();
   virtual ~___DEBUG_STATE();
};

EXTERN_PROCESS_LOCAL(___DEBUG_STATE, afxDebugState)

#endif //DEBUG

/////////////////////////////////////////////////////////////////////////////
// ___MAC_STATE


class ___MAC_STATE : public no_track_object
{
public:
   // printing abort
   bool m_bUserAbort;
};

EXTERN_PROCESS_LOCAL(___MAC_STATE, gen_WinState)


/////////////////////////////////////////////////////////////////////////////
// __MODULE_STATE : portion of state that is pushed/popped
// forward references required for __MODULE_THREAD_STATE definition
//class CHandleMap;
class hwnd_map;
class hmenu_map;
//class hdc_map;
//class hgdiobj_map;
class himagelist_map;
//class frame_window;
class CToolTipCtrl;
// xxx class ::userbase::control_bar;
// xxx class ::user::interaction;
namespace ca2
{
   
   class thread;
   class window;
}

#ifndef _PNH_DEFINED
typedef int32_t (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

template<class TYPE>
class CEmbeddedButActsLikePtr
{
public:
   inline TYPE* operator->() { return &m_data; }
   inline operator TYPE*() { return &m_data; }
   TYPE m_data;
};

// __MODULE_THREAD_STATE (local to thread *and* module)
class CLASS_DECL_mac __MODULE_THREAD_STATE :
public no_track_object
{
public:
   __MODULE_THREAD_STATE();
   virtual ~__MODULE_THREAD_STATE();
   
   // current thread pointer
   class ::mac::thread* m_pCurrentWinThread;
   
   
   
   // thread-local ca2 API new handler (separate from C-runtime)
   _PNH m_pfnNewHandler;
   
   
   // common controls thread state
   CToolTipCtrl* m_pToolTip;
   ::window * m_pLastHit;       // last ::window to own tooltip
   int_ptr m_nLastHit;         // last hittest code
   // xxx   TOOLINFO* m_pLastInfo;    // last TOOLINFO structure
   int_ptr m_nLastStatus;      // last flyby status message
   ::user::control_bar* m_pLastStatus; // last flyby status control bar
};

// forward references required for __MODULE_STATE definition
class application;


// xxx class ::window;



class CDllIsolationWrapperBase;
#ifndef ___NO_AFXCMN_SUPPORT
class CComCtlWrapper;
#endif
class CCommDlgWrapper;

// __MODULE_STATE (global data for a module)
class CLASS_DECL_mac __MODULE_STATE : public no_track_object
{
public:
   // xxx  __MODULE_STATE(bool bDLL, WNDPROC pfn_window_procedure, DWORD dwVersion,
   // xxx   bool bSystem = FALSE);
   __MODULE_STATE(bool bDLL, DWORD dwVersion, bool bSystem = FALSE);
   ~__MODULE_STATE();
   
   base_application * m_pCurrentWinApp;
   HINSTANCE m_hCurrentInstanceHandle;
   HINSTANCE m_hCurrentResourceHandle;
   const char * m_lpszCurrentAppName;
   bool m_bDLL;    // TRUE if module is a DLL, FALSE if it is an EXE
   bool m_bSystem; // TRUE if module is a "system" module, FALSE if not
   bool m_bReserved[2]; // padding
   
   DWORD m_fRegisteredClasses; // flags for registered ::window classes
   
   mutex       m_mutexRegClassList;
   
   hwnd_map       * m_pmapHWND;
   mutex             * m_pmutexHwnd;
   //   hdc_map        * m_pmapHDC;
   //   hgdiobj_map    * m_pmapHGDIOBJ;
   hmenu_map      * m_pmapHMENU;
   
   
   
   
   // number of locked OLE objects
   long m_nObjectCount;
   bool m_bUserCtrl;
   
   // __register_class and System.RegisterWndClass data
   
   string * m_pstrUnregisterList;
   
   // xxx WNDPROC m_pfn_window_procedure;
   DWORD m_dwVersion;  // version that module linked against
   
   // variables related to a given process in a module
   //  (used to be __MODULE_PROCESS_STATE)
   void (PASCAL *m_pfnFilterToolTipMessage)(MESSAGE*, ::window *);
   
   
   // define thread local portions of module state
   ::thread_slot < __MODULE_THREAD_STATE, slot___MODULE_THREAD_STATE > m_thread;
   
   //Fusion: declare pointer to array of pointers to isolation aware dll wrappers (ex: comctl32).
   CDllIsolationWrapperBase** m_pDllIsolationWrappers;
   //Defaults to TRUE. When FALSE - ca2 API will not activate context in __MAINTAIN_STATE2 (used by __MANAGE_STATE).
   bool   m_bSetAmbientActCtx;
   //Handle of the module context.
   HANDLE   m_hActCtx;
   void CreateActivationContext();
};

CLASS_DECL_mac __MODULE_STATE* __set_module_state(__MODULE_STATE* pNewState);
CLASS_DECL_mac __MODULE_STATE* __get_module_state();
CLASS_DECL_mac bool __is_module_dll();
CLASS_DECL_mac bool __init_current_state_app();
CLASS_DECL_mac __MODULE_STATE* __get_static_module_state();
CLASS_DECL_mac HINSTANCE __get_instance_handle_helper();

CLASS_DECL_mac __MODULE_THREAD_STATE* __get_module_thread_state();

#define ___CMDTARGET_GETSTATE() (m_pModuleState)

/////////////////////////////////////////////////////////////////////////////
// macros & classes to manage pushing/popping the module state

struct CLASS_DECL_mac __MAINTAIN_STATE
{
   explicit __MAINTAIN_STATE(__MODULE_STATE* pModuleState) throw();
   ~__MAINTAIN_STATE();
   
protected:
   __MODULE_STATE* m_pPrevModuleState;
};

class ___THREAD_STATE;
struct CLASS_DECL_mac __MAINTAIN_STATE2
{
   explicit __MAINTAIN_STATE2(__MODULE_STATE* pModuleState);
   ~__MAINTAIN_STATE2();
   
protected:
   __MODULE_STATE* m_pPrevModuleState;
   ___THREAD_STATE* m_pThreadState;
   
   uint_ptr m_ulActCtxCookie;
   bool m_bValidActCtxCookie;
};
#define __MANAGE_STATE(p) _gen::InitManaged(); __MAINTAIN_STATE2 _ctlState(p);

/////////////////////////////////////////////////////////////////////////////
// Thread global state

// forward references required for ___THREAD_STATE definition
class view;
class CToolTipCtrl;
// xxx class ::userbase::control_bar;
class push_routing_frame;
class CPushRoutingView;

#define ___TEMP_CLASS_NAME_SIZE 96
class CLASS_DECL_mac ___THREAD_STATE :
public no_track_object,
public ::thread_state
{
public:
   ___THREAD_STATE();
   virtual ~___THREAD_STATE();
   
   // override for m_pModuleState in ___APP_STATE
   __MODULE_STATE* m_pModuleState;
   __MODULE_STATE* m_pPrevModuleState;
   
   
   ::mac::thread * m_pCurrentWinThread;
   
   
   // primitive::memory safety pool for temp maps
   void * m_pSafetyPoolBuffer;    // current buffer
   
   // thread local exception context
   __EXCEPTION_CONTEXT m_exceptionContext;
   
   // ::window create, gray dialog hook, and other hook data
   ::user::interaction * m_pWndInit;
   ::window * m_pAlternateWndInit;      // special case commdlg hooking
   DWORD m_dwPropStyle;
   DWORD m_dwPropExStyle;
   oswindow m_hWndInit;
   // xxx   HHOOK m_hHookOldCbtFilter;
   // xxx   HHOOK m_hHookOldMsgFilter;
   
   // message pump for run
   MESSAGE m_msgCur;                   // current message
   point m_ptCursorLast;          // last mouse position
   UINT m_nMsgLast;                // last mouse message
   
#ifdef DEBUG
   int32_t m_nDisablePumpCount; // Diagnostic trap to detect illegal re-entrancy
#endif
   
   // other ::window modal data
   MESSAGE m_lastSentMsg;              // see ::window::message_handler
   oswindow m_hTrackingWindow;         // see ::window::TrackPopupMenu
   HMENU m_hTrackingMenu;
   char m_szTempClassName[___TEMP_CLASS_NAME_SIZE];    // see System.RegisterWndClass
   oswindow m_hLockoutNotifyWindow;    // see ::window::OnCommand
   bool m_bInMsgFilter;
   
   // other framework modal data
   CPushRoutingView* m_pPushRoutingView;
   
   // ca2 API/DB thread-local data
   bool m_bWaitForDataSource;
   
   // OLE control thread-local data
   ::window * m_pWndPark;       // "parking space" ::window
   long m_nCtrlRef;        // reference count on parking ::window
   bool m_bNeedTerm;       // TRUE if OleUninitialize needs to be called
};

EXTERN_THREAD_LOCAL(___THREAD_STATE, gen_ThreadState, slot___THREAD_STATE)

CLASS_DECL_mac ___THREAD_STATE * __get_thread_state();


namespace mac
{
   
   CLASS_DECL_mac ::thread_state * __get_thread_state();
   
} // namespace mac
