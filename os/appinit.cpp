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
#include "sal.h"



/////////////////////////////////////////////////////////////////////////////

/*BOOL CLASS_DECL_VMSWIN AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   __in LPTSTR lpCmdLine, int nCmdShow)
{
}*/


/////////////////////////////////////////////////////////////////////////////
// ex1::filesp implementation helpers

#ifdef AfxGetFileName
#undef AfxGetFileName
#endif


UINT CLASS_DECL_VMSWIN AfxGetFileName(const char * lpszPathName, __out_ecount_opt(nMax) LPTSTR lpszTitle, UINT nMax)
{
   ASSERT(lpszTitle == NULL ||
      fx_is_valid_address(lpszTitle, nMax));
   ASSERT(AfxIsValidString(lpszPathName));

   ENSURE_ARG(lpszPathName != NULL);

   // always capture the complete file name including extension (if present)
   LPTSTR lpszTemp = ::PathFindFileName(lpszPathName);

   // lpszTitle can be NULL which just returns the number of bytes
   if (lpszTitle == NULL)
      return lstrlen(lpszTemp)+1;

   // otherwise copy it into the buffer provided
   _template::checked::tcsncpy_s(lpszTitle, nMax, lpszTemp, _TRUNCATE);
   return 0;
}


