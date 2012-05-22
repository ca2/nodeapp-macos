#pragma once

namespace win
{

   class CLASS_DECL_VMSWIN graphics : 
      virtual public ::ca::graphics,
      virtual public hdc_handle
   {
      // // DECLARE_DYNCREATE(::ca::graphics_sp)
   public:

      graphics();
      graphics(::ca::application * papp);
      virtual ~graphics();

   // Attributes
   //   HDC get_os_data();          // The output DC (must be first data member <= no more true (What are the consequences?))
   //   HDC get_handle2();    // The Attribute DC
      operator HDC() const;
      HDC get_handle1() const; // Always returns the Output DC
      virtual void * get_os_data();
      ::ca::window * GetWindow() const;

      static ::ca::graphics * PASCAL from_handle(HDC hDC);
      static void PASCAL DeleteTempMap();
      WINBOOL Attach(HDC hDC);   // Attach/Detach affects only the Output DC
      HDC Detach();

      virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
      virtual void SetOutputDC(HDC hDC);  // Set the Output DC
      virtual void ReleaseAttribDC();     // Release the Attribute DC
      virtual void ReleaseOutputDC();     // Release the Output DC

      WINBOOL IsPrinting() const;            // TRUE if being used for printing

      ::ca::pen* GetCurrentPen() const;
      ::ca::brush* GetCurrentBrush() const;
      ::ca::palette* GetCurrentPalette() const;
      ::ca::font* GetCurrentFont() const;
      ::ca::bitmap* GetCurrentBitmap() const;

      // for bidi and mirrored localization
      DWORD GetLayout() const;
      DWORD SetLayout(DWORD dwLayout);

   // Constructors
      WINBOOL CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      WINBOOL CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
         const char * lpszOutput, const void * lpInitData);
      WINBOOL CreateCompatibleDC(::ca::graphics * pgraphics);

      WINBOOL DeleteDC();

   // Device-Context Functions
      virtual int SaveDC();
      virtual WINBOOL RestoreDC(int nSavedDC);
      int GetDeviceCaps(int nIndex) const;
      UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags);
      UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags);
      WINBOOL ResetDC(const DEVMODE* lpDevMode);

   // Drawing-Tool Functions
      point GetBrushOrg() const;
      point SetBrushOrg(int x, int y);
      point SetBrushOrg(POINT point);
      int EnumObjects(int nObjectType,
            int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

   // Type-safe selection helpers
   public:
      virtual ::ca::graphics_object* SelectStockObject(int nIndex);
      ::ca::pen* SelectObject(::ca::pen* pPen);
      ::ca::brush* SelectObject(::ca::brush* pBrush);
      virtual ::ca::font* SelectObject(::ca::font* pFont);
      ::ca::bitmap* SelectObject(::ca::bitmap* pBitmap);
      int SelectObject(::ca::rgn* pRgn);       // special return for regions
      ::ca::graphics_object* SelectObject(::ca::graphics_object* pObject);
         // ::ca::graphics_object* provided so compiler doesn't use SelectObject(HGDIOBJ)

   // color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) const;
      ::ca::palette* SelectPalette(::ca::palette* pPalette, WINBOOL bForceBackground);
      UINT RealizePalette();
      void UpdateColors();

   // Drawing-Attribute Functions
      COLORREF GetBkColor() const;
      int GetBkMode() const;
      int GetPolyFillMode() const;
      int GetROP2() const;
      int GetStretchBltMode() const;
      COLORREF GetTextColor() const;

      virtual COLORREF SetBkColor(COLORREF crColor);
      int SetBkMode(int nBkMode);
      int SetPolyFillMode(int nPolyFillMode);
      int SetROP2(int nDrawMode);
      int SetStretchBltMode(int nStretchMode);
      virtual COLORREF SetTextColor(COLORREF crColor);

      WINBOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      WINBOOL SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

   #if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() const;
      COLORREF SetDCBrushColor(COLORREF crColor);

      COLORREF GetDCPenColor() const;
      COLORREF SetDCPenColor(COLORREF crColor);

   #endif

      // Graphics mode
      int SetGraphicsMode(int iMode);
      int GetGraphicsMode() const;

      // World transform
      WINBOOL SetWorldTransform(const XFORM* pXform);
      WINBOOL ModifyWorldTransform(const XFORM* pXform,DWORD iMode);
      WINBOOL GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual int GetMapMode() const;
      virtual point GetViewportOrg() const;
      virtual int SetMapMode(int nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(int x, int y);
      virtual point SetViewportOrg(POINT point);
      virtual point OffsetViewportOrg(int nWidth, int nHeight);

      // Viewport Extent
      virtual size GetViewportExt() const;
      virtual size SetViewportExt(int cx, int cy);
      virtual size SetViewportExt(SIZE size);
      virtual size ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);

      // Window Origin
      point GetWindowOrg() const;
      point SetWindowOrg(int x, int y);
      point SetWindowOrg(POINT point);
      point OffsetWindowOrg(int nWidth, int nHeight);

      // Window extent
      size GetWindowExt() const;
      virtual size SetWindowExt(int cx, int cy);
            size SetWindowExt(SIZE size);
      virtual size ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

   // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints, int nCount = 1) const;
      void DPtoLP(LPRECT lpRect) const;
      void DPtoLP(LPSIZE lpSize) const;
      void LPtoDP(LPPOINT lpPoints, int nCount = 1) const;
      void LPtoDP(LPRECT lpRect) const;
      void LPtoDP(LPSIZE lpSize) const;

   // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) const;
      void LPtoHIMETRIC(LPSIZE lpSize) const;
      void HIMETRICtoDP(LPSIZE lpSize) const;
      void HIMETRICtoLP(LPSIZE lpSize) const;

   // Region Functions
      WINBOOL FillRgn(::ca::rgn* pRgn, ::ca::brush* pBrush);
      WINBOOL FrameRgn(::ca::rgn* pRgn, ::ca::brush* pBrush, int nWidth, int nHeight);
      WINBOOL InvertRgn(::ca::rgn* pRgn);
      WINBOOL PaintRgn(::ca::rgn* pRgn);

   // Clipping Functions
      virtual int GetClipBox(LPRECT lpRect) const;
      virtual WINBOOL PtVisible(int x, int y) const;
            WINBOOL PtVisible(POINT point) const;
      virtual WINBOOL RectVisible(LPCRECT lpRect) const;
            int SelectClipRgn(::ca::rgn* pRgn);
            int ExcludeClipRect(int x1, int y1, int x2, int y2);
            int ExcludeClipRect(LPCRECT lpRect);
            int ExcludeUpdateRgn(::ca::window * pWnd);
            int IntersectClipRect(int x1, int y1, int x2, int y2);
            int IntersectClipRect(LPCRECT lpRect);
            int OffsetClipRgn(int x, int y);
            int OffsetClipRgn(SIZE size);
      int SelectClipRgn(::ca::rgn* pRgn, int nMode);

   // Line-Output Functions
      point GetCurrentPosition() const;
      point MoveTo(int x, int y);
      point MoveTo(POINT point);
      WINBOOL LineTo(int x, int y);
      WINBOOL LineTo(POINT point);
      WINBOOL Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      WINBOOL Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      WINBOOL Polyline(const POINT* lpPoints, int nCount);

      WINBOOL AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle);
      WINBOOL ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      WINBOOL ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      int GetArcDirection() const;
      int SetArcDirection(int nArcDirection);

      WINBOOL PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount);
      WINBOOL PolylineTo(const POINT* lpPoints, int nCount);
      WINBOOL PolyPolyline(const POINT* lpPoints,
         const DWORD* lpPolyPoints, int nCount);

      WINBOOL PolyBezier(const POINT* lpPoints, int nCount);
      WINBOOL PolyBezierTo(const POINT* lpPoints, int nCount);

   // Simple Drawing Functions
      void FillRect(LPCRECT lpRect, ::ca::brush* pBrush);
      void FrameRect(LPCRECT lpRect, ::ca::brush* pBrush);
      void InvertRect(LPCRECT lpRect);
      WINBOOL DrawIcon(int x, int y, ::visual::icon * picon);
      WINBOOL DrawIcon(POINT point, ::visual::icon * picon);
      WINBOOL DrawIcon(int x, int y, ::visual::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      WINBOOL DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
         HBRUSH hBrush = NULL);
      WINBOOL DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags,
         ::ca::brush* pBrush = NULL);
      WINBOOL DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         HBRUSH hBrush = NULL);
      WINBOOL DrawState(point pt, size size, HICON hIcon, UINT nFlags,
         ::ca::brush* pBrush = NULL);
      WINBOOL DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         WINBOOL bPrefixText = TRUE, int nTextLen = 0, HBRUSH hBrush = NULL);
      WINBOOL DrawState(point pt, size size, const char * lpszText, UINT nFlags,
         WINBOOL bPrefixText = TRUE, int nTextLen = 0, ::ca::brush* pBrush = NULL);
      WINBOOL DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      WINBOOL DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
         LPARAM lData, UINT nFlags, ::ca::brush* pBrush = NULL);

   // Ellipse and Polygon Functions
      WINBOOL Chord(int x1, int y1, int x2, int y2, int x3, int y3,
         int x4, int y4);
      WINBOOL Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      void DrawFocusRect(LPCRECT lpRect);
      WINBOOL Ellipse(int x1, int y1, int x2, int y2);
      WINBOOL Ellipse(LPCRECT lpRect);
      WINBOOL Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
      WINBOOL Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd);
      WINBOOL Polygon(const POINT* lpPoints, int nCount);   
      WINBOOL PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int nCount);
      WINBOOL Rectangle(int x1, int y1, int x2, int y2);
      WINBOOL Rectangle(LPCRECT lpRect);
      WINBOOL RoundRect(int x1, int y1, int x2, int y2, int x3, int y3);
      WINBOOL RoundRect(LPCRECT lpRect, POINT point);

   // Bitmap Functions
      WINBOOL PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop);
      WINBOOL BitBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, DWORD dwRop);
      WINBOOL StretchBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);
      COLORREF GetPixel(int x, int y) const;
      COLORREF GetPixel(POINT point) const;
      COLORREF SetPixel(int x, int y, COLORREF crColor);
      COLORREF SetPixel(POINT point, COLORREF crColor);
      WINBOOL FloodFill(int x, int y, COLORREF crColor);
      WINBOOL ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType);
      WINBOOL MaskBlt(int x, int y, int nWidth, int nHeight, ::ca::graphics * pgraphicsSrc,
         int xSrc, int ySrc, ::ca::bitmap& maskBitmap, int xMask, int yMask,
         DWORD dwRop);
      WINBOOL PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc,
         int nWidth, int nHeight, ::ca::bitmap& maskBitmap, int xMask, int yMask);
      WINBOOL SetPixelV(int x, int y, COLORREF crColor);
      WINBOOL SetPixelV(POINT point, COLORREF crColor);
      WINBOOL GradientFill(TRIVERTEX* pVertices, ULONG nVertices, 
        void * pMesh, ULONG nMeshElements, DWORD dwMode);
      WINBOOL TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, 
        UINT clrTransparent);
      bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::ca::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, 
        BLENDFUNCTION blend);

   // Text Functions
      virtual WINBOOL TextOut(int x, int y, const char * lpszString, int nCount);
            WINBOOL TextOut(int x, int y, const string & str);
      virtual WINBOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
               const char * lpszString, UINT nCount, LPINT lpDxWidths);
            WINBOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
               const string & str, LPINT lpDxWidths);
      virtual size TabbedTextOut(int x, int y, const char * lpszString, int nCount,
               int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
            size TabbedTextOut(int x, int y, const string & str,
               int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

   #pragma push_macro("DrawText")
   #pragma push_macro("DrawTextEx")
   #undef DrawText
   #undef DrawTextEx
      virtual int _AFX_FUNCNAME(DrawText)(const char * lpszString, int nCount, LPRECT lpRect,
               UINT nFormat);
            int _AFX_FUNCNAME(DrawText)(const string & str, LPRECT lpRect, UINT nFormat);

      virtual int _AFX_FUNCNAME(DrawTextEx)(LPTSTR lpszString, int nCount, LPRECT lpRect,
               UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
            int _AFX_FUNCNAME(DrawTextEx)(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);

            int DrawText(const char * lpszString, int nCount, LPRECT lpRect,
               UINT nFormat);
            int DrawText(const string & str, LPRECT lpRect, UINT nFormat);

            int DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect,
               UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
            int DrawTextEx(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
   #pragma pop_macro("DrawText")
   #pragma pop_macro("DrawTextEx")

      size GetTextExtent(const char * lpszString, int nCount) const;
      size GetTextExtent(const string & str) const;
      size GetOutputTextExtent(const char * lpszString, int nCount) const;
      size GetOutputTextExtent(const string & str) const;
      size GetTabbedTextExtent(const char * lpszString, int nCount,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      size GetTabbedTextExtent(const string & str,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      size GetOutputTabbedTextExtent(const char * lpszString, int nCount,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      size GetOutputTabbedTextExtent(const string & str,
         int nTabPositions, LPINT lpnTabStopPositions) const;
      virtual WINBOOL GrayString(::ca::brush* pBrush,
         WINBOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData,
            int nCount, int x, int y, int nWidth, int nHeight);
      UINT GetTextAlign() const;
      UINT SetTextAlign(UINT nFlags);
      int GetTextFace(__in int nCount, __out_ecount_part_z(nCount, return + 1) LPTSTR lpszFacename) const;
      int GetTextFace(string & rString) const;
   #pragma push_macro("GetTextMetrics")
   #undef GetTextMetrics
      WINBOOL _AFX_FUNCNAME(GetTextMetrics)(LPTEXTMETRIC lpMetrics) const;
      WINBOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) const;
   #pragma pop_macro("GetTextMetrics")
      WINBOOL GetOutputTextMetrics(LPTEXTMETRIC lpMetrics) const;
      int SetTextJustification(int nBreakExtra, int nBreakCount);
      int GetTextCharacterExtra() const;
      int SetTextCharacterExtra(int nCharExtra);

      DWORD GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
      DWORD GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;

   #if (_WIN32_WINNT >= 0x0500)

      WINBOOL GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      WINBOOL GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE lpSize) const;

   #endif



   // Advanced Drawing
      WINBOOL DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);
      WINBOOL DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);

   // Scrolling Functions
      WINBOOL ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip,
         ::ca::rgn* pRgnUpdate, LPRECT lpRectUpdate);

   // font Functions
      WINBOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      WINBOOL GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      DWORD SetMapperFlags(DWORD dwFlag);
      size GetAspectRatioFilter() const;

      WINBOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
      DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const;
      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const;
      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
      DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
         DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      WINBOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
         LPABCFLOAT lpABCF) const;
      WINBOOL GetCharWidth(UINT nFirstChar, UINT nLastChar,
         float* lpFloatBuffer) const;

      DWORD GetFontLanguageInfo() const;

   #if (_WIN32_WINNT >= 0x0500)

      WINBOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      WINBOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

   #endif

   // Printer/Device Escape Functions
      virtual int Escape(__in int nEscape, __in int nCount,
         __in_bcount(nCount) const char * lpszInData, __in LPVOID lpOutData);
      int Escape(__in int nEscape, __in int nInputSize, __in_bcount(nInputSize) const char * lpszInputData,
         __in int nOutputSize, __out_bcount(nOutputSize) char * lpszOutputData);
      int DrawEscape(int nEscape, int nInputSize, const char * lpszInputData);

      // Escape helpers
      int StartDoc(const char * lpszDocName);  // old Win3.0 version
      int StartDoc(LPDOCINFO lpDocInfo);
      int StartPage();
      int EndPage();
      int SetAbortProc(WINBOOL (CALLBACK* lpfn)(HDC, int));
      int AbortDoc();
      int EndDoc();

   // MetaFile Functions
      WINBOOL PlayMetaFile(HMETAFILE hMF);
      WINBOOL PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);
      WINBOOL AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
         // can be used for enhanced metafiles only

   // Path Functions
      WINBOOL AbortPath();
      WINBOOL BeginPath();
      WINBOOL CloseFigure();
      WINBOOL EndPath();
      WINBOOL FillPath();
      WINBOOL FlattenPath();
      WINBOOL StrokeAndFillPath();
      WINBOOL StrokePath();
      WINBOOL WidenPath();
      float GetMiterLimit() const;
      WINBOOL SetMiterLimit(float fMiterLimit);
      int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const;
      WINBOOL SelectClipPath(int nMode);

   // Misc Helper Functions
      static ::ca::brush* PASCAL GetHalftoneBrush(::ca::application * papp);
      void DrawDragRect(LPCRECT lpRect, SIZE size,
         LPCRECT lpRectLast, SIZE sizeLast,
         ::ca::brush* pBrush = NULL, ::ca::brush* pBrushLast = NULL);
      void FillSolidRect(const __rect64 * lpRect, COLORREF clr);
      void FillSolidRect(LPCRECT lpRect, COLORREF clr);
      void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr);
      void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      void Draw3dRect(int x, int y, int cx, int cy,
         COLORREF clrTopLeft, COLORREF clrBottomRight);

   // Implementation
   public:
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      // advanced use and implementation
      WINBOOL m_bPrinting;
      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

   protected:
      // used for implementation of non-virtual SelectObject calls
      static ::ca::graphics_object* PASCAL SelectGdiObject(::ca::application * papp, HDC hDC, HGDIOBJ h);
   };

} // namespace win
