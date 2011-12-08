#include "StdAfx.h"

namespace win
{

   rgn::rgn(::ca::application * papp) :
      ca(papp)
   { }
   rgn::~rgn()
   { }
   rgn::operator HRGN() const
   { 
      return (HRGN)(this == NULL ? NULL : get_os_data()); 
   }
   rgn* PASCAL rgn::from_handle(::ca::application * papp, HRGN hRgn)
   { 
      return dynamic_cast < rgn * > (::win::graphics_object::from_handle(papp, hRgn));
   }
   BOOL rgn::CreateRectRgn(int x1, int y1, int x2, int y2)
   { return Attach(::CreateRectRgn(x1, y1, x2, y2)); }
   BOOL rgn::CreateRectRgnIndirect(LPCRECT lpRect)
   { return Attach(::CreateRectRgnIndirect(lpRect)); }
   BOOL rgn::CreateEllipticRgn(int x1, int y1, int x2, int y2)
   { return Attach(::CreateEllipticRgn(x1, y1, x2, y2)); }
   BOOL rgn::CreateEllipticRgnIndirect(LPCRECT lpRect)
   { return Attach(::CreateEllipticRgnIndirect(lpRect)); }
   BOOL rgn::CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode)
   { return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode)); }
   BOOL rgn::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
   { return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode)); }
   BOOL rgn::CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
   { return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3)); }
   BOOL rgn::CreateFromPath(::ca::graphics * pgraphics)
   { ASSERT(pgraphics != NULL); return Attach(::PathToRegion((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1())); }
   BOOL rgn::CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
   { return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData)); }
   int rgn::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   { ASSERT(get_os_data() != NULL); return (int)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
   void rgn::SetRectRgn(int x1, int y1, int x2, int y2)
   { ASSERT(get_os_data() != NULL); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }
   
   void rgn::SetRectRgn(LPCRECT lpRect)
   { 
      ::SetRectRgn((HRGN)get_os_data(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); 
   }

   int rgn::CombineRgn(const ::ca::rgn* pRgn1, const ::ca::rgn* pRgn2, int nCombineMode)
   { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
   (HRGN)pRgn2->get_os_data(), nCombineMode); }
   int rgn::CopyRgn(const ::ca::rgn* pRgnSrc)
   { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), NULL, RGN_COPY); }
   BOOL rgn::EqualRgn(const ::ca::rgn* pRgn) const
   { ASSERT(get_os_data() != NULL); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
   int rgn::OffsetRgn(int x, int y)
   { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
   int rgn::OffsetRgn(POINT point)
   { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
   int rgn::GetRgnBox(LPRECT lpRect) const
   { ASSERT(get_os_data() != NULL); return ::GetRgnBox((HRGN)get_os_data(), lpRect); }
   BOOL rgn::PtInRegion(int x, int y) const
   { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), x, y); }
   BOOL rgn::PtInRegion(POINT point) const
   { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
   BOOL rgn::RectInRegion(LPCRECT lpRect) const
   { ASSERT(get_os_data() != NULL); return ::RectInRegion((HRGN)get_os_data(), lpRect); }

} // namespace win