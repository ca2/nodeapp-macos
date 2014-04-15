#pragma once


namespace mac
{
   
   
   class thread;
   
   class MAC
   {
      int32_t function();
   };
   
   
   
} // namespace mac



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_mac __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base * m_pException;   // current exception (NULL in try block)
   
   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
   {
      //__try_cleanup();
   };
};

// Exception global state - never access directly
struct CLASS_DECL_mac __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;
   
   // Note: most of the exception context is now in the __exception_link
};

#ifndef _PNH_DEFINED
typedef int32_t (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_mac __get_new_handler();
_PNH CLASS_DECL_mac __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_mac int32_t c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_mac __abort();

//typedef void * HICON;


// helpers for registering your own WNDCLASSes
CLASS_DECL_mac const char * __register_window_class(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

// xxx CLASS_DECL_mac bool __register_class(WNDCLASS* lpWndClass);


CLASS_DECL_mac LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
// xxx CLASS_DECL_mac WNDPROC __get_window_procedure();
// xxx #define __window_procedure (*__get_window_procedure())

typedef void (__MSG_CALL ::window::*__PMSGW)();
// like '__PMSG' but for ::window derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
// like '__PMSG' but for thread-derived classes only




// xxx CLASS_DECL_mac LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);


// Advanced initialization: for overriding default diagnostics
//CLASS_DECL_mac bool __diagnostic_init();

namespace mac
{
   CLASS_DECL_mac ::thread * __get_thread();
   CLASS_DECL_mac void __set_thread(::thread * pthread);
}
CLASS_DECL_mac MESSAGE * __get_current_message();

CLASS_DECL_mac void __end_thread(base_application * papp, UINT nExitCode, bool bDelete = TRUE);

CLASS_DECL_mac void __init_thread();
CLASS_DECL_mac void __term_thread(base_application * papp, HINSTANCE hInstTerm = NULL);

/////////////////////////////////////////////////////////////////////////////
// Global functions for access to the one and only application

#define afxCurrentWinApp    __get_module_state()->m_pCurrentWinApp
#define afxCurrentInstanceHandle    __get_module_state()->m_hCurrentInstanceHandle
#define afxCurrentResourceHandle    __get_module_state()->m_hCurrentResourceHandle
#define afxCurrentAppName   __get_module_state()->m_lpszCurrentAppName
#define afxContextIsDLL     __get_module_state()->m_bDLL
#define afxRegisteredClasses    __get_module_state()->m_fRegisteredClasses
#define afxAmbientActCtx    __get_module_state()->m_bSetAmbientActCtx


// Advanced initialization: for overriding default WinMain
//CLASS_DECL_mac bool ::ca2::WinInit(__in HINSTANCE hInstance, __in HINSTANCE hPrevInstance,
// __in_z LPTSTR lpCmdLine, __in int32_t nCmdShow);
CLASS_DECL_mac void __mac_term();

CLASS_DECL_mac base_application * __get_app();
CLASS_DECL_mac sp(::user::interaction) __get_main_window();
//CLASS_DECL_mac HINSTANCE CLASS_DECL_mac System.m_hInstance;
CLASS_DECL_mac HINSTANCE __get_resource_handle();
CLASS_DECL_mac void __set_resource_handle(HINSTANCE hInstResource);
CLASS_DECL_mac const char * __get_app_name();

CLASS_DECL_mac HINSTANCE __get_resource_handle();
CLASS_DECL_mac HINSTANCE __find_string_resource_handle(UINT nID);

CLASS_DECL_mac void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_mac __global_free(HGLOBAL hGlobal);
