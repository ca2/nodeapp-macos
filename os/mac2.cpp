#include "StdAfx.h"

// Global helper functions
 CLASS_DECL_VMSMAC ::radix::application * AfxGetApp()
{ return dynamic_cast < ::radix::application * > (afxCurrentWinApp); }

 CLASS_DECL_VMSMAC HINSTANCE AfxGetInstanceHandle()
   { ASSERT(afxCurrentInstanceHandle != NULL);
      return afxCurrentInstanceHandle; }
 CLASS_DECL_VMSMAC HINSTANCE AfxGetResourceHandle()
   { ASSERT(afxCurrentResourceHandle != NULL);
      return afxCurrentResourceHandle; }
 CLASS_DECL_VMSMAC void AfxSetResourceHandle(HINSTANCE hInstResource)
   { ASSERT(hInstResource != NULL); afxCurrentResourceHandle = hInstResource; }
 CLASS_DECL_VMSMAC const char * AfxGetAppName()
   { ASSERT(afxCurrentAppName != NULL); return afxCurrentAppName; }
 CLASS_DECL_VMSMAC ::user::interaction * AfxGetMainWnd()
{
      ::radix::thread* pThread = dynamic_cast < ::radix::thread * > (::mac::get_thread());
      return pThread != NULL ? pThread->GetMainWnd() : NULL; 
 }

 CLASS_DECL_VMSMAC WINBOOL AfxGetAmbientActCtx()
   {    return afxAmbientActCtx; }
 CLASS_DECL_VMSMAC void AfxSetAmbientActCtx(WINBOOL bSet)
   {  afxAmbientActCtx = bSet; }



#ifdef _ApplicationFrameworkDLL
// AFX_MAINTAIN_STATE functions
 AFX_MAINTAIN_STATE::AFX_MAINTAIN_STATE(AFX_MODULE_STATE* pNewState)
   {  m_pPrevModuleState = AfxSetModuleState(pNewState); }
#endif

// AFX_MAINTAIN_STATE2 functions
 AFX_MAINTAIN_STATE2::~AFX_MAINTAIN_STATE2()
{
#ifdef _ApplicationFrameworkDLL
   // Not a good place to report errors here, so just be safe
   if(m_pThreadState)
   {
      m_pThreadState->m_pModuleState = m_pPrevModuleState;
   }
#endif

/*   if (m_bValidActCtxCookie)
   {
      WINBOOL bRet;
      bRet = AfxDeactivateActCtx(0, m_ulActCtxCookie);
      ASSERT(bRet == TRUE);
   }*/
}

