#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int32_t CLASS_DECL_mac __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);


/////////////////////////////////////////////////////////////////////////////
// initialize cast state such that it points to this module's core state

CLASS_DECL_mac bool __initialize(bool bDLL, DWORD dwVersion)
{
   __MODULE_STATE* pModuleState = __get_module_state();
   pModuleState->m_bDLL = (BYTE)bDLL;
   // xxx   ASSERT(dwVersion <= _MFC_VER);
   // xxx   UNUSED(dwVersion);  // not used in release build
   pModuleState->m_dwVersion = dwVersion;
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


//char gen_InitAppState = (char)(__initialize(FALSE, _MFC_VER));
char gen_InitAppState = (char)(__initialize(FALSE, 1));
