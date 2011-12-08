#include "StdAfx.h"
#include "sal.h"

#ifdef _ApplicationFrameworkDLL
//#include <mfcassem.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int CLASS_DECL_VMSWIN AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   __in LPTSTR lpCmdLine, int nCmdShow);

extern "C" int WINAPI
_tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   __in LPTSTR lpCmdLine, int nCmdShow)
{
   // call shared/exported WinMain
   return AfxWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

/////////////////////////////////////////////////////////////////////////////
// initialize cast state such that it points to this module's core state

CLASS_DECL_VMSWIN BOOL AfxInitialize(BOOL bDLL, DWORD dwVersion)
{
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   pModuleState->m_bDLL = (BYTE)bDLL;
   ASSERT(dwVersion <= _MFC_VER);
   UNUSED(dwVersion);  // not used in release build
#ifdef _ApplicationFrameworkDLL
   pModuleState->m_dwVersion = dwVersion;
#endif
#ifdef _MBCS
   // set correct multi-byte code-page for Win32 apps
   if (!bDLL)
      _setmbcp(_MB_CP_ANSI);
#endif //_MBCS
   return TRUE;
}

// force initialization early
//#pragma warning(disable: 4074)
//#pragma init_seg(lib)

#ifndef _ApplicationFrameworkDLL
void AFX_CDECL _AfxTermAppState()
{
   // terminate local data and critical sections
   AfxTermLocalData(NULL, TRUE);
   AfxCriticalTerm();

   // release the reference to thread local storage data
   AfxTlsRelease();
}
#endif

#ifndef _ApplicationFrameworkDLL
char _afxInitAppState = (char)(AfxInitialize(FALSE, _MFC_VER), atexit(&_AfxTermAppState));
#else
char _afxInitAppState = (char)(AfxInitialize(FALSE, _MFC_VER));
#endif

/////////////////////////////////////////////////////////////////////////////
