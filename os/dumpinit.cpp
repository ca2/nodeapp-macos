#include "StdAfx.h"


/////////////////////////////////////////////////////////////////////////////
// _AFX_DEBUG_STATE implementation

#ifndef _AFX_NO_DEBUG_CRT
static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = NULL;


void __cdecl _AfxCrtDumpClient(void * pvData, size_t nBytes)
{
   char sz[1024];
   try
   {
      
      if(_CrtReportBlockType(pvData) != _AFX_CLIENT_BLOCK)
         return;

      ::radix::object * pca = (::radix::object * ) pvData;

      ::radix::object * pobject = NULL;

      /*for(int i = 0; i < 256; i++)
      {
         try
         {
            pobject = dynamic_cast < ::radix::object * > ((::radix::object *)&((INT_PTR *)pca)[i]);
         }
         catch(std::__non_rtti_object & e)
         {
            pobject = NULL;
         }
         catch(...)
         {
            pobject = NULL;
         }
         if(pobject != NULL)
            break;
      }*/

      if(pobject == NULL)
      {
            ATL_CRT_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "unknown object at $%p, %u bytes long\n", pvData, nBytes));
      }
      else if(afxdump.GetDepth() > 0)
      {
         // long form
         pobject->dump(afxdump);
         afxdump << "\n";
      }
      if(false) // else
      {
         ::radix::object & obj = *pobject;
         // short form
         ATL_CRT_ERRORCHECK_SPRINTF(_snprintf_s(sz, _countof(sz), _countof(sz) - 1, "a %hs object at $%p, %u bytes long\n", typeid(obj).name(), pvData, nBytes));
         afxdump << sz;
      }
   }
   catch(std::__non_rtti_object & e)
   {
      afxdump << "_AfxCrtdumpClient __non_rtti_object ";
      afxdump << e.what();
   }
   catch(...)
   {
      // short form for trashed objects
      sprintf_s(sz, _countof(sz), "faulted while dumping object at $%p, %u bytes long\n", pvData, nBytes);
      afxdump << sz;
   }
   if (pfnOldCrtDumpClient != NULL)
      (*pfnOldCrtDumpClient)(pvData, nBytes);
}

int __cdecl _AfxCrtReportHook(int nRptType, __in char *szMsg, int* pResult)
{
   // no hook on asserts or when m_pFile is NULL
   if (nRptType == _CRT_ASSERT || afxdump.m_pFile == NULL)
      return FALSE;

   ASSERT( pResult != NULL );
   if( pResult == NULL )
      AfxThrowInvalidArgException();

   ASSERT( szMsg != NULL );
   if( szMsg == NULL )
      AfxThrowInvalidArgException();

   // non-NULL m_pFile, so go through afxdump for the message
   *pResult = FALSE;
   afxdump << szMsg;
   //Allow other report hooks to be called.
   return FALSE;
}
#endif // _AFX_NO_DEBUG_CRT




_AFX_DEBUG_STATE::_AFX_DEBUG_STATE()
{
#ifndef _AFX_NO_DEBUG_CRT
   ASSERT(pfnOldCrtDumpClient == NULL);
   pfnOldCrtDumpClient = _CrtSetDumpClient(_AfxCrtDumpClient);

   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL,_AfxCrtReportHook) != -1);
   _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
#endif // _AFX_NO_DEBUG_CRT
}

_AFX_DEBUG_STATE::~_AFX_DEBUG_STATE()
{
#ifndef _AFX_NO_DEBUG_CRT
   try
   {
      _CrtDumpMemoryLeaks();
   }
   catch(std::__non_rtti_object & e)
   {
      ::OutputDebugString("~_AFX_DEBUG_STATE _CrtdumpMemoryLeaks std::__non_rtti_object\n");
      ::OutputDebugString(e.what());
      ::OutputDebugString("\n");
   }
   catch(...)
   {
      ::OutputDebugString("~_AFX_DEBUG_STATE _CrtdumpMemoryLeaks exception\n");
   }
   int nOldState = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
   _CrtSetDbgFlag(nOldState & ~_CRTDBG_LEAK_CHECK_DF);

   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE,_AfxCrtReportHook) != -1);   
   _CrtSetDumpClient(pfnOldCrtDumpClient);
#endif // _AFX_NO_DEBUG_CRT
}

PROCESS_LOCAL(_AFX_DEBUG_STATE, afxDebugState)

BOOL CLASS_DECL_VMSWIN AfxDiagnosticInit(void)
{
   // just get the debug state to cause initialization
   _AFX_DEBUG_STATE* pState = afxDebugState.get_data();
   ASSERT(pState != NULL);

   return TRUE;
}



#include "StdAfx.h"
#include "sal.h"


//AFX_DATADEF BOOL afxTraceEnabled = TRUE;
//AFX_DATADEF UINT afxTraceFlags = 0;
static BOOL _afxDiagnosticInit = AfxDiagnosticInit();

