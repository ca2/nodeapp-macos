// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#include "StdAfx.h"
#include <ddeml.h> // for MSGF_DDEMGR



/////////////////////////////////////////////////////////////////////////////
// other globals (internal library use)

/////////////////////////////////////////////////////////////////////////////
// Standard cleanup called by WinMain and AfxAbort

void CLASS_DECL_VMSWIN AfxUnregisterWndClasses()
{
   // unregister Window classes
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   AfxLockGlobals(CRIT_REGCLASSLIST);
   if(pModuleState->m_pstrUnregisterList != NULL) 
   {
      int start = 0;
      string className = pModuleState->m_pstrUnregisterList->Tokenize("\n",start);
      while (!className.is_empty())
      {
//         UnregisterClass(static_cast<const char *>(className), System.m_hInstance);
         className = pModuleState->m_pstrUnregisterList->Tokenize("\n",start);
      }
      pModuleState->m_pstrUnregisterList->Empty();
      pModuleState->m_pstrUnregisterList = NULL;
   }
   AfxUnlockGlobals(CRIT_REGCLASSLIST);

}
void CLASS_DECL_VMSWIN AfxWinTerm(void)
{   
   AfxUnregisterWndClasses();
   // cleanup OLE if required
//   thread* pThread = &System;

   // cleanup thread local tooltip ::ca::window
//   AFX_MODULE_THREAD_STATE* pModuleThreadState = AfxGetModuleThreadState();
/*   if (pModuleThreadState->m_pToolTip != NULL)
   {
      if (pModuleThreadState->m_pToolTip->DestroyToolTipCtrl())
         pModuleThreadState->m_pToolTip = NULL;
   }*/

   _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
   if (!afxContextIsDLL)
   {
      // unhook windows hooks
      if (pThreadState->m_hHookOldMsgFilter != NULL)
      {
         ::UnhookWindowsHookEx(pThreadState->m_hHookOldMsgFilter);
         pThreadState->m_hHookOldMsgFilter = NULL;
      }
      if (pThreadState->m_hHookOldCbtFilter != NULL)
      {
         ::UnhookWindowsHookEx(pThreadState->m_hHookOldCbtFilter);
         pThreadState->m_hHookOldCbtFilter = NULL;
      }
   }
    // We used to suppress all exceptions here. But that's the wrong thing
    // to do. If this process crashes, we should allow Windows to crash
    // the process and invoke watson.
}

/////////////////////////////////////////////////////////////////////////////
