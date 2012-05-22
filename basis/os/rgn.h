#pragma once

namespace win
{

   class rgn :
      virtual public ::win::graphics_object,
      virtual public ::ca::rgn
   {
   public:
      static rgn * PASCAL from_handle(::ca::application * papp, HRGN hRgn);
      operator HRGN() const;

      rgn(::ca::application * papp);
      virtual ~rgn();

      WINBOOL CreateRectRgn(int x1, int y1, int x2, int y2);
      WINBOOL CreateRectRgnIndirect(LPCRECT lpRect);
      WINBOOL CreateEllipticRgn(int x1, int y1, int x2, int y2);
      WINBOOL CreateEllipticRgnIndirect(LPCRECT lpRect);
      WINBOOL CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode);
      WINBOOL CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts,
            int nCount, int nPolyFillMode);
      WINBOOL CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
      WINBOOL CreateFromPath(::ca::graphics * pgraphics);
      WINBOOL CreateFromData(const XFORM* lpXForm, int nCount,
         const RGNDATA* pRgnData);

   // Operations
      void SetRectRgn(int x1, int y1, int x2, int y2);
      void SetRectRgn(LPCRECT lpRect);
      int CombineRgn(const ::ca::rgn* pRgn1, const ::ca::rgn* pRgn2, int nCombineMode);
      int CopyRgn(const ::ca::rgn* pRgnSrc);
      WINBOOL EqualRgn(const ::ca::rgn* pRgn) const;
      int OffsetRgn(int x, int y);
      int OffsetRgn(POINT point);
      int GetRgnBox(LPRECT lpRect) const;
      WINBOOL PtInRegion(int x, int y) const;
      WINBOOL PtInRegion(POINT point) const;
      WINBOOL RectInRegion(LPCRECT lpRect) const;
      int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;

   };

} // namespace win