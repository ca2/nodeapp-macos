#include "framework.h"


/*
 /////////////////////////////////////////////////////////////////////////////
 // Helper functions
 
 __STATIC long CLASS_DECL_DRAW2D_QUARTZ2D _AfxMultMultDivDiv(
 int32_t factor, int32_t num1, int32_t num2,
 int32_t den1, int32_t den2)
 {
 #ifdef _AFX_PORTABLE
 // make sure that (num1 * num2) does not overflow 31-bits.
 long temp = num1 < 0 ? -num1 : num1;
 for (int32_t nBitsResult = 0; temp != 0; nBitsResult++)
 temp >>= 1;
 temp = num2 < 0 ? -num2 : num2;
 for (; temp != 0; nBitsResult++)
 temp >>= 1;
 if (nBitsResult > 31)
 {
 num1 >>= nBitsResult - 31;
 num2 >>= nBitsResult - 31;
 }
 
 // make sure that (den1 * den2) does not overflow 31-bits
 temp = den1 < 0 ? -den1 : den1;
 for (nBitsResult = 0; temp != 0; nBitsResult++)
 temp >>= 1;
 temp = den2 < 0 ? -den2 : den2;
 for (; temp != 0; nBitsResult++)
 temp >>= 1;
 if (nBitsResult > 31)
 {
 den1 >>= nBitsResult - 31;
 den2 >>= nBitsResult - 31;
 }
 
 long numerator = (long)num1 * (long)num2;   // no overflow
 long denominator = (long)den1 * (long)den2; // no overflow
 #else
 int64_t numerator = (int64_t)num1 * (int64_t)num2;   // no overflow
 int64_t denominator = (int64_t)den1 * (int64_t)den2; // no overflow
 int64_t temp;
 #endif
 
 temp = numerator < 0 ? -numerator : numerator;
 int32_t nBitsInNum;
 for (nBitsInNum = 0; temp != 0; nBitsInNum++)
 temp >>= 1;
 
 temp = factor < 0 ? -factor : factor;
 int32_t nBitsInFactor;
 for (nBitsInFactor = 0; temp != 0; nBitsInFactor++)
 temp >>= 1;
 
 nBitsInNum += nBitsInFactor;
 
 //
 // normalizing the denominator to positive results in an easier
 // determination of whether there is overflow
 //
 if (denominator < 0)
 {
 denominator = -denominator;
 numerator = -numerator;
 }
 
 // get the product of factor * numerator representable in a long/int64_t
 // while distributing loss of presision across all three numerator terms
 // Adjust denominator as well
 //
 while (nBitsInNum-- > 31)
 {
 numerator >>= 1;
 denominator >>= 1;
 if (nBitsInNum-- <= 31)
 break;
 numerator >>= 1;
 denominator >>= 1;
 if (nBitsInNum-- <= 31)
 break;
 factor >>= 1;
 denominator >>= 1;
 }
 numerator *= factor;
 
 if (denominator == 0)
 return numerator < 0 ? LONG_MIN : LONG_MAX;
 
 return (long) ((numerator + denominator/2) / denominator);
 }
 
 /////////////////////////////////////////////////////////////////////////////
 // Print Preview DC (preview_dc)
 
 preview_dc::preview_dc()
 {
 // Initial scale factor and top-left offset
 m_nScaleNum = m_nScaleDen = 1;
 m_sizeTopLeft.cx = m_sizeTopLeft.cy = 8;
 m_hFont = m_hPrinterFont = NULL;
 }
 
 void preview_dc::SetOutputDC(HDC hDC)
 {
 ASSERT(hDC != NULL);
 m_nSaveDCIndex = ::SaveDC(hDC); // restore in ReleaseOutputDC()
 ::draw2d::graphics_sp::SetOutputDC(hDC);
 
 if (get_handle2() != NULL)
 {
 MirrorMappingMode(FALSE);
 
 if (m_hFont)
 ::SelectObject(get_os_data(), m_hFont);
 else
 MirrorFont();
 MirrorAttributes();
 }
 }
 
 void preview_dc::ReleaseOutputDC()
 {
 ASSERT(get_os_data() != NULL);
 ::RestoreDC(get_os_data(), m_nSaveDCIndex); // Saved in SetOutputDC()
 ::draw2d::graphics_sp::ReleaseOutputDC();
 }
 
 void preview_dc::SetAttribDC(HDC hDC)
 {
 ASSERT(hDC != NULL);
 ::draw2d::graphics_sp::SetAttribDC(hDC);
 
 MirrorMappingMode(TRUE);
 MirrorFont();
 MirrorAttributes();
 }
 
 preview_dc::~preview_dc()
 {
 ASSERT(get_os_data() == NULL);      // Should not have a screen DC at this time
 AfxDeleteObject((HGDIOBJ*)&m_hFont);
 }
 
 void preview_dc::SetScaleRatio(int32_t nNumerator, int32_t nDenominator)
 {
 m_nScaleNum = nNumerator;
 m_nScaleDen = nDenominator;
 if (get_handle2() != NULL)
 {
 MirrorMappingMode(TRUE);
 MirrorFont();
 }
 }
 
 // Implementation support
 #ifdef DEBUG
 void preview_dc::assert_valid() const
 {
 ::draw2d::graphics_sp::assert_valid();
 }
 
 
 void preview_dc::dump(dump_context & dumpcontext) const
 {
 ::draw2d::graphics_sp::dump(dumpcontext);
 
 dumpcontext << "Scale Factor: " << m_nScaleNum << "/" << m_nScaleDen;
 dumpcontext << "\n";
 }
 #endif
 
 int32_t preview_dc::SaveDC()
 {
 ASSERT(get_handle2() != NULL);
 int32_t nAttribIndex = ::SaveDC(get_handle2());
 if (get_os_data() != NULL)
 {
 // remove font from object
 ::SelectObject(get_os_data(), GetStockObject(SYSTEM_FONT));
 m_nSaveDCDelta = ::SaveDC(get_os_data()) - nAttribIndex;
 // Select font back in after save
 ::SelectObject(get_os_data(), m_hFont);
 }
 else
 {
 m_nSaveDCDelta = 0x7fff;        // impossibly high value
 }
 return nAttribIndex;
 }
 
 WINBOOL preview_dc::RestoreDC(int32_t nSavedDC)
 {
 ASSERT(get_handle2() != NULL);
 WINBOOL bSuccess = ::RestoreDC(get_handle2(), nSavedDC);
 if (bSuccess)
 {
 if (m_nSaveDCDelta != 0x7fff)
 {
 ASSERT(get_os_data() != NULL);      // removed Output DC after save
 
 if (nSavedDC != -1)
 nSavedDC += m_nSaveDCDelta;
 bSuccess = ::RestoreDC(get_os_data(), nSavedDC);
 MirrorFont();               // mirror the font
 }
 else
 {
 ASSERT(get_os_data() == NULL);      // Added the Output DC after save
 }
 }
 return bSuccess;
 }
 
 void preview_dc::MirrorAttributes()
 {
 ASSERT(get_handle2() != NULL);
 
 if (get_os_data() != NULL)
 {
 // extract and re-set Pen and Brush
 HGDIOBJ hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_PEN));
 ::SelectObject(get_handle2(), hTemp);
 ::SelectObject(get_os_data(), hTemp);
 hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_BRUSH));
 ::SelectObject(get_handle2(), hTemp);
 ::SelectObject(get_os_data(), hTemp);
 
 SetROP2(GetROP2());
 SetBkMode(GetBkMode());
 SetTextAlign(GetTextAlign());
 SetPolyFillMode(GetPolyFillMode());
 SetStretchBltMode(GetStretchBltMode());
 SetTextColor(GetNearestColor(GetTextColor()));
 SetBkColor(GetNearestColor(GetBkColor()));
 }
 }
 
 ::draw2d::object* preview_dc::SelectStockObject(int32_t nIndex)
 {
 ASSERT(get_handle2() != NULL);
 
 HGDIOBJ hObj = ::GetStockObject(nIndex);
 
 switch (nIndex)
 {
 case ANSI_FIXED_FONT:
 case ANSI_VAR_FONT:
 case DEVICE_DEFAULT_FONT:
 case OEM_FIXED_FONT:
 case SYSTEM_FONT:
 case SYSTEM_FIXED_FONT:
 case DEFAULT_GUI_FONT:
 // Handle the stock fonts correctly
 {
 ::draw2d::object* pObject = ::draw2d_quartz2d::object::from_handle(
 ::SelectObject(get_handle2(), hObj));
 
 // Don't re-mirror screen font if this is the same font.
 if (m_hPrinterFont == (HFONT) hObj)
 return pObject;
 
 m_hPrinterFont = (HFONT) hObj;
 
 ASSERT(m_hPrinterFont != NULL); // Do not allow infinite recursion
 
 MirrorFont();
 return pObject;
 }
 
 default:
 if (get_os_data() != NULL)
 ::SelectObject(get_os_data(), hObj);
 return ::draw2d_quartz2d::object::from_handle(::SelectObject(get_handle2(), hObj));
 }
 }
 
 void preview_dc::MirrorFont()
 {
 if (get_handle2() == NULL)
 return;         // Can't do anything without Attrib DC
 
 if (m_hPrinterFont == NULL)
 {
 SelectStockObject(DEVICE_DEFAULT_FONT); // will recurse
 return;
 }
 
 if (get_os_data() == NULL)
 return;         // can't mirror font without a screen DC
 
 LOGFONT logFont;
 // Fill the logFont structure with the original info
 ::GetObject(m_hPrinterFont, sizeof(LOGFONT), (LPVOID)&logFont);
 
 TEXTMETRICW tm;
 
 GetTextFace(LF_FACESIZE, (LPTSTR)&logFont.lfFaceName[0]);
 GetTextMetrics(&tm);
 
 // Set real values based on the Printer's text metrics.
 
 if (tm.tmHeight < 0)
 logFont.lfHeight = tm.tmHeight;
 else
 logFont.lfHeight = -(tm.tmHeight - tm.tmInternalLeading);
 
 logFont.lfWidth = tm.tmAveCharWidth;
 logFont.lfWeight = tm.tmWeight;
 logFont.lfItalic = tm.tmItalic;
 logFont.lfUnderline = tm.tmUnderlined;
 logFont.lfStrikeOut = tm.tmStruckOut;
 logFont.lfCharSet = tm.tmCharSet;
 logFont.lfPitchAndFamily = tm.tmPitchAndFamily;
 
 HFONT hNewFont = ::CreateFontIndirect(&logFont);
 ::SelectObject(get_os_data(), hNewFont);
 
 ::GetTextMetrics(get_os_data(), &tm);
 
 // Is the displayed font too large?
 
 int32_t cyDesired = -logFont.lfHeight;
 int32_t cyActual;
 if (tm.tmHeight < 0)
 cyActual = -tm.tmHeight;
 else
 cyActual = tm.tmHeight - tm.tmInternalLeading;
 
 size sizeWinExt;
 VERIFY(::GetWindowExtEx(get_os_data(), &sizeWinExt));
 size sizeVpExt;
 VERIFY(::GetViewportExtEx(get_os_data(), &sizeVpExt));
 
 // Only interested in Extent Magnitudes, not direction
 if (sizeWinExt.cy < 0)
 sizeWinExt.cy = -sizeWinExt.cy;
 if (sizeVpExt.cy < 0)
 sizeVpExt.cy = -sizeVpExt.cy;
 
 // Convert to screen device coordinates to eliminate rounding
 // errors as a source of SmallFont aliasing
 
 cyDesired = MulDiv(cyDesired, sizeVpExt.cy, sizeWinExt.cy);
 cyActual = MulDiv(cyActual, sizeVpExt.cy, sizeWinExt.cy);
 
 ASSERT(cyDesired >= 0 && cyActual >= 0);
 
 if (cyDesired < cyActual)
 {
 logFont.lfFaceName[0] = 0;      // let the mapper find a good fit
 
 if ((logFont.lfPitchAndFamily & 0xf0) == FF_DECORATIVE)
 logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DECORATIVE;
 else
 logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
 
 HFONT hTempFont = ::CreateFontIndirect(&logFont);
 ::SelectObject(get_os_data(), hTempFont);           // Select it in.
 ::DeleteObject(hNewFont);
 hNewFont = hTempFont;
 }
 
 AfxDeleteObject((HGDIOBJ*)&m_hFont);  // delete the old logical font
 m_hFont = hNewFont;         // save the new one
 }
 
 ::draw2d::font* preview_dc::SelectObject(::draw2d::font* pFont)
 {
 if (pFont == NULL)
 return NULL;
 
 ASSERT(get_handle2() != NULL);
 ASSERT_VALID(pFont);
 
 ::draw2d::font* pOldFont = (::draw2d::font*) ::draw2d_quartz2d::object::from_handle(
 ::SelectObject(get_handle2(), pFont->get_handle()));
 
 // If same as already selected, don't re-mirror screen font
 if (m_hPrinterFont != pFont->get_handle())
 {
 m_hPrinterFont = (HFONT)pFont->get_handle();
 MirrorFont();
 }
 
 return pOldFont;
 }
 
 /////////////////////////////////////////////////////////////////////////////
 // Drawing-Attribute Functions
 
 COLORREF preview_dc::SetBkColor(COLORREF crColor)
 {
 ASSERT(get_handle2() != NULL);
 if (get_os_data() != NULL)
 ::SetBkColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
 return ::SetBkColor(get_handle2(), crColor);
 }
 
 COLORREF preview_dc::SetTextColor(COLORREF crColor)
 {
 ASSERT(get_handle2() != NULL);
 if (get_os_data() != NULL)
 ::SetTextColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
 return ::SetTextColor(get_handle2(), crColor);
 }
 
 int32_t preview_dc::SetMapMode(int32_t nMapMode)
 {
 ASSERT(get_handle2() != NULL);
 int32_t nModeOld = ::SetMapMode(get_handle2(), nMapMode);
 MirrorMappingMode(TRUE);
 return nModeOld;
 }
 
 point preview_dc::SetViewportOrg(int32_t x, int32_t y)
 {
 ASSERT(get_handle2() != NULL);
 point ptOrgOld;
 VERIFY(::SetViewportOrgEx(get_handle2(), x, y, &ptOrgOld));
 MirrorViewportOrg();
 return ptOrgOld;
 }
 
 point preview_dc::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
 {
 ASSERT(get_handle2() != NULL);
 point ptOrgOld;
 VERIFY(::OffsetViewportOrgEx(get_handle2(), nWidth, nHeight, &ptOrgOld));
 MirrorViewportOrg();
 return ptOrgOld;
 }
 
 size preview_dc::SetViewportExt(int32_t x, int32_t y)
 {
 ASSERT(get_handle2() != NULL);
 size sizeExtOld;
 VERIFY(::SetViewportExtEx(get_handle2(), x, y, &sizeExtOld));
 MirrorMappingMode(TRUE);
 return sizeExtOld;
 }
 
 size preview_dc::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
 {
 ASSERT(get_handle2() != NULL);
 size sizeExtOld;
 VERIFY(::ScaleViewportExtEx(get_handle2(), xNum, xDenom,
 yNum, yDenom, &sizeExtOld));
 MirrorMappingMode(TRUE);
 return sizeExtOld;
 }
 
 size preview_dc::SetWindowExt(int32_t x, int32_t y)
 {
 ASSERT(get_handle2() != NULL);
 size sizeExtOld;
 VERIFY(::SetWindowExtEx(get_handle2(), x, y, &sizeExtOld));
 MirrorMappingMode(TRUE);
 return sizeExtOld;
 }
 
 size preview_dc::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
 {
 ASSERT(get_handle2() != NULL);
 size sizeExtOld;
 VERIFY(::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom,
 &sizeExtOld));
 MirrorMappingMode(TRUE);
 return sizeExtOld;
 }
 
 /////////////////////////////////////////////////////////////////////////////
 // Text Functions
 
 // private helpers for TextOut functions
 
 __STATIC int32_t CLASS_DECL_DRAW2D_QUARTZ2D _AfxComputeNextTab(int32_t x, UINT nTabStops, LPINT lpnTabStops, int32_t nTabOrigin, int32_t nTabWidth)
 {
 ENSURE(nTabWidth!=0);
 x -= nTabOrigin;        // normalize position to tab origin
 for (UINT i = 0; i < nTabStops; i++, lpnTabStops++)
 {
 if (*lpnTabStops > x)
 {
 return *lpnTabStops + nTabOrigin;
 }
 }
 return (x / nTabWidth + 1) * nTabWidth + nTabOrigin;
 }
 
 // Compute a character delta table for correctly positioning the screen
 // font characters where the printer characters will appear on the page
 size preview_dc::ComputeDeltas(int32_t& x, const char * lpszString, UINT &nCount,
 WINBOOL bTabbed, UINT nTabStops, LPINT lpnTabStops, int32_t nTabOrigin,
 __out_z LPTSTR lpszOutputString, int32_t* pnDxWidths, int32_t& nRightFixup)
 {
 ASSERT_VALID(this);
 
 TEXTMETRICW tmAttrib;
 TEXTMETRICW tmScreen;
 ::GetTextMetrics(get_handle2(), &tmAttrib);
 ::GetTextMetrics(get_os_data(), &tmScreen);
 
 size sizeExtent;
 ::GetTextExtentPoint32A(get_handle2(), "A", 1, &sizeExtent);
 
 point ptCurrent;
 UINT nAlignment = ::GetTextAlign(get_handle2());
 WINBOOL bUpdateCP = (nAlignment & TA_UPDATECP) != 0;
 if (bUpdateCP)
 {
 ::GetCurrentPositionEx(get_os_data(), &ptCurrent);
 x = ptCurrent.x;
 }
 
 const char * lpszCurChar = lpszString;
 const char * lpszStartRun = lpszString;
 int32_t* pnCurDelta = pnDxWidths;
 int32_t nStartRunPos = x;
 int32_t nCurrentPos = x;
 int32_t nStartOffset = 0;
 
 int32_t nTabWidth = 0;
 if (bTabbed)
 {
 if (nTabStops == 1)
 {
 nTabWidth = lpnTabStops[0];
 }
 else
 {
 // get default size of a tab
 nTabWidth = LOWORD(::GetTabbedTextExtentA(get_handle2(),
 "\t", 1, 0, NULL));
 }
 }
 
 for (UINT i = 0; i < nCount; i++)
 {
 WINBOOL bSpace = ((_TUCHAR)*lpszCurChar == (_TUCHAR)tmAttrib.tmBreakChar);
 if (bSpace || (bTabbed && *lpszCurChar == '\t'))
 {
 // bSpace will be either TRUE (==1) or FALSE (==0).  For spaces
 // we want the space included in the GetTextExtent, for tabs we
 // do not want the tab included
 int32_t nRunLength = (int32_t)(lpszCurChar - lpszStartRun) + bSpace;
 
 size sizeExtent;
 ::GetTextExtentPoint32(get_handle2(), lpszStartRun, nRunLength,
 &sizeExtent);
 int32_t nNewPos = nStartRunPos + sizeExtent.cx
 - tmAttrib.tmOverhang;
 
 // now, if this is a Tab (!bSpace), compute the next tab stop
 if (!bSpace)
 {
 nNewPos = _AfxComputeNextTab(nNewPos, nTabStops, lpnTabStops,
 nTabOrigin, nTabWidth);
 }
 
 // add this width to previous width
 if (pnCurDelta == pnDxWidths)
 nStartOffset += nNewPos - nCurrentPos;
 else
 *(pnCurDelta-1) += nNewPos - nCurrentPos;
 
 nCurrentPos = nNewPos;
 
 nStartRunPos = nCurrentPos;     // set start of run
 // *lpszCurChar must be SBC: tmBreakChar or '\t'
 lpszStartRun = lpszCurChar + 1;
 }
 else
 {
 // For the non-tabbed or non-tab-character case
 int32_t cxScreen;
 if (_istlead(*lpszCurChar))
 {
 cxScreen = tmScreen.tmAveCharWidth;
 *pnCurDelta = tmAttrib.tmAveCharWidth;
 }
 else
 {
 ::GetCharWidth(get_os_data(), (_TUCHAR)*lpszCurChar,
 (_TUCHAR)*lpszCurChar, &cxScreen);
 if (!::GetCharWidth(get_handle2(), (_TUCHAR)*lpszCurChar,
 (_TUCHAR)*lpszCurChar, pnCurDelta))
 {
 // If printer driver fails the above call, use the average width
 *pnCurDelta = tmAttrib.tmAveCharWidth;
 }
 }
 *pnCurDelta -= tmAttrib.tmOverhang;
 cxScreen -= tmScreen.tmOverhang;
 nCurrentPos += *pnCurDelta;     // update current position
 
 // Center character in allotted space
 if (pnCurDelta != pnDxWidths)
 {
 int32_t diff = (*pnCurDelta - cxScreen) / 2;
 *pnCurDelta -= diff;
 *(pnCurDelta - 1) += diff;
 }
 *lpszOutputString++ = *lpszCurChar;
 if (_istlead(*lpszCurChar))
 {
 *lpszOutputString++ = *(lpszCurChar+1); // copy trailing byte
 *(pnCurDelta + 1) = *pnCurDelta;        // double wide
 nCurrentPos += *pnCurDelta;
 pnCurDelta++;
 i++;
 }
 pnCurDelta++;
 }
 lpszCurChar = _tcsinc(lpszCurChar);
 }
 
 nAlignment &= TA_CENTER|TA_RIGHT;
 sizeExtent.cx = nCurrentPos - x;
 nRightFixup = 0;
 
 if (nAlignment == TA_LEFT)
 x += nStartOffset;      // Full left side adjustment
 else if (nAlignment == TA_CENTER)
 x += nStartOffset/2;    // Adjust Center by 1/2 left side adjustment
 else if (nAlignment == TA_RIGHT)
 nRightFixup = nStartOffset; // Right adjust needed later if TA_UPDATECP
 
 if (bUpdateCP)
 ::MoveToEx(get_os_data(), x, ptCurrent.y, NULL);
 
 nCount = (UINT)(pnCurDelta - pnDxWidths);   // number of characters output
 return sizeExtent;
 }
 
 WINBOOL preview_dc::TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount)
 {
 return ExtTextOut(x, y, 0, NULL, lpszString, nCount, NULL);
 }
 
 WINBOOL preview_dc::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect,
 const char * lpszString, UINT nCount, LPINT lpDxWidths)
 {
 ASSERT(get_os_data() != NULL);
 ASSERT(get_handle2() != NULL);
 ASSERT(lpszString != NULL);
 ASSERT(lpDxWidths == NULL ||
 fx_is_valid_address(lpDxWidths, sizeof(int32_t) * nCount, FALSE));
 ASSERT(fx_is_valid_address(lpszString, nCount, FALSE));
 
 int32_t* pDeltas = NULL;
 LPTSTR pOutputString = NULL;
 int32_t nRightFixup = 0;
 
 if (lpDxWidths == NULL)
 {
 if (nCount == 0)    // Do nothing
 return TRUE;
 
 try
 {
 pDeltas = new int32_t[nCount];
 pOutputString = new char[nCount];
 }
 catch(::exception::base * pe)
 {
 delete[] pDeltas;  // in case it was allocated
 // Note: DELETE_EXCEPTION(e) not required
 return FALSE;   // Could not allocate buffer, cannot display
 }
 
 
 ComputeDeltas(x, (LPTSTR)lpszString, nCount, FALSE, 0, NULL, 0,
 pOutputString, pDeltas, nRightFixup);
 
 lpDxWidths = pDeltas;
 lpszString = pOutputString;
 }
 
 WINBOOL bSuccess = ::ExtTextOut(get_os_data(), x, y, nOptions, lpRect, lpszString,
 nCount, lpDxWidths);
 if (nRightFixup != 0 && bSuccess && (GetTextAlign() & TA_UPDATECP))
 {
 point pt;
 ::GetCurrentPositionEx(get_os_data(), &pt);
 MoveTo(pt.x - nRightFixup, pt.y);
 }
 delete[] pDeltas;
 delete[] pOutputString;
 
 return bSuccess;
 }
 
 size preview_dc::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount,
 int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
 {
 ASSERT(get_handle2() != NULL);
 ASSERT(get_os_data() != NULL);
 ASSERT(lpszString != NULL);
 ASSERT(fx_is_valid_address(lpszString, nCount, FALSE));
 ASSERT(lpnTabStopPositions == NULL ||
 fx_is_valid_address(lpnTabStopPositions, sizeof(int32_t) * nTabPositions,
 FALSE));
 
 if (nCount <= 0)
 return (DWORD) 0;         // nCount is zero, there is nothing to print
 
 int32_t* pDeltas = NULL;
 LPTSTR pOutputString = NULL;
 int32_t nRightFixup;
 
 try
 {
 pDeltas = new int32_t[nCount];
 pOutputString = new char[nCount];
 }
 catch(::exception::base * pe)
 {
 delete[] pDeltas;
 // Note: DELETE_EXCEPTION(e) not required
 return (DWORD) 0;           // signify error
 }
 
 
 UINT uCount = nCount;
 size sizeFinalExtent = ComputeDeltas(x, lpszString, uCount, TRUE,
 nTabPositions, lpnTabStopPositions, nTabOrigin,
 pOutputString, pDeltas, nRightFixup);
 
 WINBOOL bSuccess = ExtTextOut(x, y, 0, NULL, pOutputString, uCount, pDeltas);
 
 delete[] pDeltas;
 delete[] pOutputString;
 
 if (bSuccess && (GetTextAlign() & TA_UPDATECP))
 {
 point pt;
 ::GetCurrentPositionEx(get_os_data(), &pt);
 MoveTo(pt.x - nRightFixup, pt.y);
 }
 
 return sizeFinalExtent;
 }
 
 // This one is too complicated to do character-by-character output positioning
 // All we really need to do here is mirror the current position
 int32_t preview_dc::DrawText(const char * lpszString, int32_t nCount, LPRECT lpRect,
 UINT nFormat)
 {
 ASSERT(get_handle2() != NULL);
 ASSERT(get_os_data() != NULL);
 ASSERT(lpszString != NULL);
 ASSERT(lpRect != NULL);
 ASSERT(fx_is_valid_address(lpRect, sizeof(RECT)));
 ASSERT(nCount == -1 ?
 AfxIsValidString(lpszString) :
 fx_is_valid_address(lpszString, nCount, FALSE));
 
 int32_t retVal = ::DrawText(get_os_data(), lpszString, nCount, lpRect, nFormat);
 
 point pos;
 ::GetCurrentPositionEx(get_os_data(), &pos);
 ::MoveToEx(get_handle2(), pos.x, pos.y, NULL);
 return retVal;
 }
 
 int32_t preview_dc::DrawTextEx(__in_ecount(nCount) LPTSTR lpszString, int32_t nCount, LPRECT lpRect,
 UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
 {
 ASSERT(get_handle2() != NULL);
 ASSERT(get_os_data() != NULL);
 ASSERT(lpszString != NULL);
 ASSERT(lpRect != NULL);
 ASSERT(fx_is_valid_address(lpRect, sizeof(RECT)));
 ASSERT(nCount == -1 ?
 AfxIsValidString(lpszString) :
 fx_is_valid_address(lpszString, nCount, FALSE));
 
 int32_t retVal = ::DrawTextEx(get_os_data(), lpszString, nCount, lpRect, nFormat, lpDTParams);
 
 point pos;
 ::GetCurrentPositionEx(get_os_data(), &pos);
 ::MoveToEx(get_handle2(), pos.x, pos.y, NULL);
 return retVal;
 }
 
 WINBOOL preview_dc::GrayString(::draw2d::brush*,
 WINBOOL (CALLBACK *)(HDC, LPARAM, int32_t),
 LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t, int32_t)
 {
 TRACE(::ca2::trace::category_AppMsg, 0, "TextOut() substituted for GrayString() in Print Preview.\n");
 return TextOut(x, y, (const char *)lpData, nCount);
 }
 
 int32_t preview_dc::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, void * lpOutData)
 {
 // The tact here is to NOT allow any of the document control escapes
 // to be passed through.  Elimination of StartDoc and EndDoc should
 // eliminate anything actually going to the printer.  Also anything
 // that actually draws something will be filtered.
 
 ASSERT(get_handle2() != NULL);
 
 switch (nEscape)
 {
 case NEXTBAND:
 case SETCOLORTABLE:
 case GETCOLORTABLE:
 case FLUSHOUTPUT:
 case DRAFTMODE:
 case QUERYESCSUPPORT:
 case GETPHYSPAGESIZE:
 case GETPRINTINGOFFSET:
 case GETSCALINGFACTOR:
 case GETPENWIDTH:
 case SETCOPYCOUNT:
 case SELECTPAPERSOURCE:
 case GETTECHNOLOGY:
 case SETLINECAP:
 case SETLINEJOIN:
 case SETMITERLIMIT:
 case BANDINFO:
 case GETVECTORPENSIZE:
 case GETVECTORBRUSHSIZE:
 case ENABLEDUPLEX:
 case GETSETPAPERBINS:
 case GETSETPRINTORIENT:
 case ENUMPAPERBINS:
 case SETDIBSCALING:
 case ENUMPAPERMETRICS:
 case GETSETPAPERMETRICS:
 case GETEXTENDEDTEXTMETRICS:
 case GETEXTENTTABLE:
 case GETPAIRKERNTABLE:
 case GETTRACKKERNTABLE:
 case ENABLERELATIVEWIDTHS:
 case ENABLEPAIRKERNING:
 case SETKERNTRACK:
 case SETALLJUSTVALUES:
 case SETCHARSET:
 case SET_BACKGROUND_COLOR:
 case SET_SCREEN_ANGLE:
 case SET_SPREAD:
 return ::Escape(get_handle2(), nEscape, nCount, lpszInData, lpOutData);
 
 default:
 return 0;
 }
 }
 
 void preview_dc::MirrorMappingMode(WINBOOL bCompute)
 {
 ASSERT(get_handle2() != NULL);
 if (bCompute)
 {
 //
 // The following formula is used to compute the screen's viewport extent
 // From the printer and screen information and the Printer's Viewport
 // Extents.  (Note:  This formula is used twice, once for horizontal
 // and once for vertical)
 //
 // It is assumed that the Window Extents are maintained as equal.
 //
 //                  m * LogPixPerInch(Screen) * VpExt(Printer)
 // VpExt(Screen) = -------------------------------------------------
 //                          n * LogPixPerInch(Printer)
 //
 // Where m/n is the scaling factor.  (m/n > 1 is expansion)
 //
 
 VERIFY(::GetViewportExtEx(get_handle2(), &m_sizeVpExt));
 VERIFY(::GetWindowExtEx(get_handle2(), &m_sizeWinExt));
 
 while (m_sizeWinExt.cx > -0x4000 && m_sizeWinExt.cx < 0x4000 &&
 m_sizeVpExt.cx  > -0x4000 && m_sizeVpExt.cx  < 0x4000)
 {
 m_sizeWinExt.cx <<= 1;
 m_sizeVpExt.cx  <<= 1;
 }
 
 while (m_sizeWinExt.cy > -0x4000 && m_sizeWinExt.cy < 0x4000 &&
 m_sizeVpExt.cy  > -0x4000 && m_sizeVpExt.cy  < 0x4000)
 {
 m_sizeWinExt.cy <<= 1;
 m_sizeVpExt.cy  <<= 1;
 }
 
 long lTempExt = _AfxMultMultDivDiv(m_sizeVpExt.cx,
 m_nScaleNum, afxData.cxPixelsPerInch,
 m_nScaleDen, ::GetDeviceCaps(get_handle2(), LOGPIXELSX));
 
 ASSERT(m_sizeWinExt.cx != 0);
 m_sizeVpExt.cx = (int32_t)lTempExt;
 
 lTempExt = _AfxMultMultDivDiv(m_sizeVpExt.cy,
 m_nScaleNum, afxData.cyPixelsPerInch,
 m_nScaleDen, ::GetDeviceCaps(get_handle2(), LOGPIXELSY));
 
 ASSERT(m_sizeWinExt.cy != 0);
 m_sizeVpExt.cy = (int32_t)lTempExt;
 }
 
 if (get_os_data() != NULL)
 {
 ::SetMapMode(get_os_data(), MM_ANISOTROPIC);
 ::SetWindowExtEx(get_os_data(), m_sizeWinExt.cx, m_sizeWinExt.cy, NULL);
 ::SetViewportExtEx(get_os_data(), m_sizeVpExt.cx, m_sizeVpExt.cy, NULL);
 
 // Now that the Logical Units are synchronized, we can set the Viewport Org
 MirrorViewportOrg();
 }
 }
 
 void preview_dc::MirrorViewportOrg()
 {
 if (get_handle2() == NULL || get_os_data() == NULL)
 return;
 
 point ptVpOrg;
 VERIFY(::GetViewportOrgEx(get_handle2(), &ptVpOrg));
 PrinterDPtoScreenDP(&ptVpOrg);
 ptVpOrg += m_sizeTopLeft;
 ::SetViewportOrgEx(get_os_data(), ptVpOrg.x, ptVpOrg.y, NULL);
 
 point ptWinOrg;
 VERIFY(::GetWindowOrgEx(get_handle2(), &ptWinOrg));
 ::SetWindowOrgEx(get_os_data(), ptWinOrg.x, ptWinOrg.y, NULL);
 }
 
 void preview_dc::SetTopLeftOffset(size sizeTopLeft)
 {
 ASSERT(get_handle2() != NULL);
 m_sizeTopLeft = sizeTopLeft;
 MirrorViewportOrg();
 }
 
 void preview_dc::ClipToPage()
 {
 ASSERT(get_handle2() != NULL);
 ASSERT(get_os_data() != NULL);
 // create a rect in Screen Device coordinates that is one pixel larger
 // on all sides than the actual page.  This is to hide the fact that
 // the printer to screen mapping mode is approximate and may result
 // in rounding error.
 
 point pt(::GetDeviceCaps(get_handle2(), HORZRES),
 ::GetDeviceCaps(get_handle2(), VERTRES));
 PrinterDPtoScreenDP(&pt);
 
 // Set the screen dumpcontext <<to MM_TEXT and no WindowOrg for the interesection
 
 ::SetMapMode(get_os_data(), MM_TEXT);
 ::SetWindowOrgEx(get_os_data(), 0, 0, NULL);
 ::SetViewportOrgEx(get_os_data(), m_sizeTopLeft.cx, m_sizeTopLeft.cy, NULL);
 ::IntersectClipRect(get_os_data(), -1, -1, pt.x + 2, pt.y + 2);
 
 // Resynchronize the mapping mode
 MirrorMappingMode(FALSE);
 }
 
 // these conversion functions can be used without an attached screen DC
 
 void preview_dc::PrinterDPtoScreenDP(LPPOINT lpPoint) const
 {
 ASSERT(get_handle2() != NULL);
 
 size sizePrinterVpExt;
 VERIFY(::GetViewportExtEx(get_handle2(), &sizePrinterVpExt));
 size sizePrinterWinExt;
 VERIFY(::GetWindowExtEx(get_handle2(), &sizePrinterWinExt));
 
 long xScreen = _AfxMultMultDivDiv(lpPoint->x,
 sizePrinterWinExt.cx, m_sizeVpExt.cx,
 sizePrinterVpExt.cx, m_sizeWinExt.cx);
 
 lpPoint->x = (int32_t)xScreen;
 
 long yScreen = _AfxMultMultDivDiv(lpPoint->y,
 sizePrinterWinExt.cy, m_sizeVpExt.cy,
 sizePrinterVpExt.cy, m_sizeWinExt.cy);
 
 lpPoint->y = (int32_t)yScreen;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // AfxCreateDC
 
 HDC CLASS_DECL_DRAW2D_QUARTZ2D AfxCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode)
 {
 if (hDevNames == NULL)
 return NULL;
 
 LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
 LPDEVMODE  lpDevMode = (hDevMode != NULL) ?
 (LPDEVMODE)::GlobalLock(hDevMode) : NULL;
 
 if (lpDevNames == NULL)
 return NULL;
 
 HDC hDC = ::CreateDC((const char *)lpDevNames + lpDevNames->wDriverOffset,
 (const char *)lpDevNames + lpDevNames->wDeviceOffset,
 (const char *)lpDevNames + lpDevNames->wOutputOffset,
 lpDevMode);
 
 ::GlobalUnlock(hDevNames);
 if (hDevMode != NULL)
 ::GlobalUnlock(hDevMode);
 return hDC;
 }
 
 
 // IMPLEMENT_DYNAMIC(preview_dc, ::draw2d::graphics_sp)
 
 /////////////////////////////////////////////////////////////////////////////
 */
