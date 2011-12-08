#pragma once

namespace win
{
   class thread;

   class win
   {
      int function();
   };

   CLASS_DECL_VMSWIN HINSTANCE   LoadLibrary(const char * lpsz);
   CLASS_DECL_VMSWIN BOOL        SHGetSpecialFolderPath(HWND hwnd, string &str, int csidl, BOOL fCreate);
   CLASS_DECL_VMSWIN DWORD       GetFileAttributes(const char * lpFileName);
   CLASS_DECL_VMSWIN BOOL        CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
   CLASS_DECL_VMSWIN DWORD       GetCurrentDirectory(string & str);
   CLASS_DECL_VMSWIN DWORD       GetTempPath(string & str);
   CLASS_DECL_VMSWIN LONG        RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str);
   CLASS_DECL_VMSWIN HICON       ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex);
   CLASS_DECL_VMSWIN BOOL        DeleteFile(const char * lpFileName);
   CLASS_DECL_VMSWIN int         GetMenuStringW(HMENU hMenu, UINT uIDItem, string & str, UINT flags);
   CLASS_DECL_VMSWIN void        TimeToFileTime(::ca::application * papp, const class time& time, LPFILETIME pFileTime);

} // namespace win



// Placed on frame for EXCEPTION linkage, or base_exception cleanup
struct CLASS_DECL_VMSWIN AFX_EXCEPTION_LINK
{
   AFX_EXCEPTION_LINK* m_pLinkPrev;    // previous top, next in handler chain
   base_exception* m_pException;   // current exception (NULL in try block)

   AFX_EXCEPTION_LINK();       // for initialization and linking
   ~AFX_EXCEPTION_LINK()       // for cleanup and unlinking
      { AfxTryCleanup(); };
};

// Exception global state - never access directly
struct CLASS_DECL_VMSWIN AFX_EXCEPTION_CONTEXT
{
   AFX_EXCEPTION_LINK* m_pLinkTop;

   // Note: most of the exception context is now in the AFX_EXCEPTION_LINK
};

#ifndef _PNH_DEFINED
typedef int (__cdecl * _PNH)( size_t );
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_VMSWIN AfxGetNewHandler();
_PNH CLASS_DECL_VMSWIN AfxSetNewHandler(_PNH pfnNewHandler);
CLASS_DECL_ca int AFX_CDECL AfxNewHandler(size_t nSize);

void CLASS_DECL_VMSWIN AfxAbort();


// helpers for registering your own WNDCLASSes
CLASS_DECL_VMSWIN const char * AfxRegisterWndClass(UINT nClassStyle,
   HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

CLASS_DECL_VMSWIN BOOL AfxRegisterClass(WNDCLASS* lpWndClass);

// helper to initialize rich edit 1.0 control
CLASS_DECL_VMSWIN BOOL AfxInitRichEdit();
// helper to initialize rich edit 2.0 control
CLASS_DECL_VMSWIN BOOL AfxInitRichEdit2();

CLASS_DECL_VMSWIN LRESULT CALLBACK AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
CLASS_DECL_VMSWIN WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

typedef void (AFX_MSG_CALL ::ca::window::*AFX_PMSGW)(void);
   // like 'AFX_PMSG' but for ::ca::window derived classes only

typedef void (AFX_MSG_CALL ::radix::thread::*AFX_PMSGT)(void);
   // like 'AFX_PMSG' but for thread-derived classes only




CLASS_DECL_VMSWIN LONG AfxDelRegTreeHelper(HKEY hParentKey, const string & strKeyName);


// Advanced initialization: for overriding default diagnostics
CLASS_DECL_VMSWIN BOOL AfxDiagnosticInit(void);


CLASS_DECL_VMSWIN ::win::thread * AfxGetThread();
CLASS_DECL_VMSWIN void AfxSetThread(::radix::thread * pthread);
CLASS_DECL_VMSWIN MSG* AfxGetCurrentMessage();

CLASS_DECL_VMSWIN void AfxEndThread(::radix::application * papp, UINT nExitCode, BOOL bDelete = TRUE);

CLASS_DECL_VMSWIN void AfxInitThread();
CLASS_DECL_VMSWIN void AfxTermThread(::radix::application * papp, HINSTANCE hInstTerm = NULL);

/////////////////////////////////////////////////////////////////////////////
// Global functions for access to the one and only application

#define afxCurrentWinApp    AfxGetModuleState()->m_pCurrentWinApp
#define afxCurrentInstanceHandle    AfxGetModuleState()->m_hCurrentInstanceHandle
#define afxCurrentResourceHandle    AfxGetModuleState()->m_hCurrentResourceHandle
#define afxCurrentAppName   AfxGetModuleState()->m_lpszCurrentAppName
#define afxContextIsDLL     AfxGetModuleState()->m_bDLL
#define afxRegisteredClasses    AfxGetModuleState()->m_fRegisteredClasses
#define afxAmbientActCtx    AfxGetModuleState()->m_bSetAmbientActCtx

#ifndef _AFX_NO_OCC_SUPPORT
#define afxOccManager   AfxGetModuleState()->m_pOccManager
#endif

//Fusion: Access macros for WinSxS dynamic wrappers.
#ifndef _AFX_NO_AFXCMN_SUPPORT
#define _AFX_COMCTL32_ISOLATION_WRAPPER_INDEX 0
#define afxComCtlWrapper static_cast<CComCtlWrapper*>(AfxGetModuleState()->m_pDllIsolationWrappers[_AFX_COMCTL32_ISOLATION_WRAPPER_INDEX])
#endif

#define _AFX_COMMDLG_ISOLATION_WRAPPER_INDEX 1
#define afxCommDlgWrapper static_cast<CCommDlgWrapper*>(AfxGetModuleState()->m_pDllIsolationWrappers[_AFX_COMMDLG_ISOLATION_WRAPPER_INDEX])

// Advanced initialization: for overriding default WinMain
//CLASS_DECL_VMSWIN BOOL AfxWinInit(__in HINSTANCE hInstance, __in HINSTANCE hPrevInstance,
  // __in_z LPTSTR lpCmdLine, __in int nCmdShow);
CLASS_DECL_VMSWIN void AfxWinTerm();

CLASS_DECL_VMSWIN ::radix::application* AfxGetApp();
CLASS_DECL_VMSWIN ::user::interaction* AfxGetMainWnd();
//CLASS_DECL_VMSWIN HINSTANCE CLASS_DECL_VMSWIN System.m_hInstance;
CLASS_DECL_VMSWIN HINSTANCE AfxGetResourceHandle();
CLASS_DECL_VMSWIN void AfxSetResourceHandle(HINSTANCE hInstResource);
CLASS_DECL_VMSWIN const char * AfxGetAppName();

CLASS_DECL_VMSWIN HINSTANCE AfxGetResourceHandle();
CLASS_DECL_VMSWIN HINSTANCE AfxFindStringResourceHandle(UINT nID);

CLASS_DECL_VMSWIN void AfxDeleteObject(HGDIOBJ* pObject);

void CLASS_DECL_VMSWIN AfxGlobalFree(HGLOBAL hGlobal);
