#include "framework.h"


// interesting function
/*WINBOOL CLASS_DECL_lnx AfxCustomLogFont(UINT nIDS, LOGFONT* pLogFont)
 {
 ENSURE_ARG(pLogFont != NULL);
 ASSERT(nIDS != 0);
 
 char szFontInfo[256];
 if (!AfxLoadString(nIDS, szFontInfo,_countof(szFontInfo)))
 return FALSE;
 
 LPTSTR lpszSize = _tcschr(szFontInfo, '\n');
 if (lpszSize != NULL)
 {
 // get point size and convert to pixels
 pLogFont->lfHeight = _ttoi(lpszSize+1);
 pLogFont->lfHeight =
 MulDiv(pLogFont->lfHeight, afxData.cyPixelsPerInch, 72);
 *lpszSize = '\0';
 }
 _template::checked::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
 return TRUE;
 }*/

/*
 WINBOOL CLASS_DECL_lnx _AfxIsComboBoxControl(oswindow hWnd, UINT nStyle)
 {
 if (hWnd == NULL)
 return FALSE;
 // do cheap style compare first
 if ((UINT)(::GetWindowLong(hWnd, GWL_STYLE) & 0x0F) != nStyle)
 return FALSE;
 
 // do expensive classname compare next
 char szCompare[_countof("combobox")+1];
 ::GetClassName(hWnd, szCompare, _countof(szCompare));
 return ::AfxInvariantStrICmp(szCompare, "combobox") == 0;
 }
 
 WINBOOL CLASS_DECL_lnx _AfxCompareClassName(oswindow hWnd, const char * lpszClassName)
 {
 ASSERT(::IsWindow(hWnd));
 char szTemp[32];
 ::GetClassName(hWnd, szTemp, _countof(szTemp));
 return ::AfxInvariantStrICmp(szTemp, lpszClassName) == 0;
 }
 
 oswindow CLASS_DECL_lnx _AfxChildWindowFromPoint(oswindow hWnd, POINT pt)
 {
 ASSERT(hWnd != NULL);
 
 // check child windows
 ::ClientToScreen(hWnd, &pt);
 oswindow hWndChild = ::GetWindow(hWnd, GW_CHILD);
 for (; hWndChild != NULL; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
 {
 if (_AfxGetDlgCtrlID(hWndChild) != (WORD)0 &&
 (::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
 {
 // see if point hits the child ::window
 rect rect;
 ::GetWindowRect(hWndChild, rect);
 if (rect.contains(pt))
 return hWndChild;
 }
 }
 
 return NULL;    // not found
 }
 
 void CLASS_DECL_lnx AfxSetWindowText(::user::interaction * hWndCtrl, const char * lpszNew)
 {
 hWndCtrl->SetWindowText(lpszNew);
ENSURE(hWndCtrl);
 ENSURE(lpszNew);
 
 int32_t nNewLen = lstrlen(lpszNew);
 char szOld[256]="";
 // fast check to see if text really changes (reduces flash in controls)
 if (nNewLen > _countof(szOld) ||
 ::GetWindowText(hWndCtrl, szOld, _countof(szOld)) != nNewLen ||
 lstrcmp(szOld, lpszNew) != 0)
 {
 // change it
 ::SetWindowText(hWndCtrl, lpszNew);
 }*/
//}

/*
 void CLASS_DECL_lnx AfxDeleteObject(HGDIOBJ* pObject)
 {
 ENSURE_ARG(pObject != NULL);
 if (*pObject != NULL)
 {
 ::DeleteObject(*pObject);
 *pObject = NULL;
 }
 }*/

/*
 void CLASS_DECL_lnx AfxCancelModes(oswindow hWndRcvr)
 {
 // if we receive a message destined for a ::window, cancel any combobox
 //  popups that could be in toolbars or dialog bars
 oswindow hWndCancel = ::GetFocus();
 if (hWndCancel == NULL)
 return;     // nothing to cancel
 
 if (hWndCancel == hWndRcvr)
 return;     // let input go to ::window with focus
 
 // focus is in part of a combo-box
 if (!_AfxIsComboBoxControl(hWndCancel, (UINT)CBS_DROPDOWNLIST))
 {
 // check as a dropdown
 hWndCancel = ::GetParent(hWndCancel);   // parent of edit is combo
 if (hWndCancel == hWndRcvr)
 return;     // let input go to part of combo
 
 if (!_AfxIsComboBoxControl(hWndCancel, (UINT)CBS_DROPDOWN))
 return;     // not a combo-box that is active
 }
 
 // combo-box is active, but if receiver is a popup, do nothing
 if (hWndRcvr != NULL &&
 (::GetWindowLong(hWndRcvr, GWL_STYLE) & WS_CHILD) != 0 &&
 ::GetParent(hWndRcvr) == ::GetDesktopWindow())
 return;
 
 // finally, we should cancel the mode!
 ::SendMessage(hWndCancel, CB_SHOWDROPDOWN, FALSE, 0L);
 }*/

/*
 void CLASS_DECL_lnx AfxGlobalFree(HGLOBAL hGlobal)
 {
 if (hGlobal == NULL)
 return;
 
 // avoid bogus warning error messages from various debugging tools
 ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
 UINT nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
 while (nCount--)
 GlobalUnlock(hGlobal);
 
 // finally, really free the handle
 GlobalFree(hGlobal);
 }
 */
/////////////////////////////////////////////////////////////////////////////
// Special new handler for safety pool on temp maps

#ifndef _AFX_PORTABLE

#define MIN_MALLOC_OVERHEAD 4   // LocalAlloc or other overhead

int32_t AfxCriticalNewHandler(size_t nSize)
// nSize is already rounded
{
   return 0;
   // called during critical primitive::memory allocation
   //  free up part of the cast's safety cache
   //   TRACE(::ca2::trace::category_Memory, 0, "Warning: Critical primitive::memory allocation failed!\n");
   /*   ___THREAD_STATE* pThreadState = __get_thread_state();
    if (pThreadState != NULL && pThreadState->m_pSafetyPoolBuffer != NULL)
    {
    size_t nOldBufferSize = _msize(pThreadState->m_pSafetyPoolBuffer);
    if (nOldBufferSize <= nSize + MIN_MALLOC_OVERHEAD)
    {
    // give it all up
    ///       TRACE(::ca2::trace::category_Memory, 0, "Warning: Freeing application's primitive::memory safety pool!\n");
    free(pThreadState->m_pSafetyPoolBuffer);
    pThreadState->m_pSafetyPoolBuffer = NULL;
    }
    else
    {
    WINBOOL bEnable = AfxEnableMemoryTracking(FALSE);
    _expand(pThreadState->m_pSafetyPoolBuffer,
    nOldBufferSize - (nSize + MIN_MALLOC_OVERHEAD));
    AfxEnableMemoryTracking(bEnable);
    //         TRACE(::ca2::trace::category_Memory, 0, "Warning: Shrinking safety pool from %d to %d to satisfy request of %d bytes.\n",
    //           nOldBufferSize, _msize(pThreadState->m_pSafetyPoolBuffer), nSize);
    }
    return 1;       // retry it
    }
    */
   //   TRACE(::ca2::trace::category_Memory, 0, "ERROR: Critical primitive::memory allocation from safety pool failed!\n");
   //   AfxThrowMemoryException();      // oops
}
#endif // !_AFX_PORTABLE

/////////////////////////////////////////////////////////////////////////////
