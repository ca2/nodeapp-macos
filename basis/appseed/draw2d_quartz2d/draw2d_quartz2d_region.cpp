#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   region::region(sp(base_application) papp) :
      ::element(papp)
   {
      
   }
   
   
   region::~region()
   {
      
   }
   
   
   
   /*   region::operator HRGN() const
    {
    return (HRGN)(this == NULL ? NULL : get_os_data());
    }
    region* PASCAL region::from_handle(base_application * papp, HRGN hRgn)
    {
    return dynamic_cast < region * > (::win::object::from_handle(papp, hRgn));
    }
    WINBOOL region::CreateRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    { return Attach(::CreateRectRgn(x1, y1, x2, y2)); }
    WINBOOL region::CreateRectRgnIndirect(LPCRECT lpRect)
    { return Attach(::CreateRectRgnIndirect(lpRect)); }
    WINBOOL region::CreateEllipticRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    { return Attach(::CreateEllipticRgn(x1, y1, x2, y2)); }
    WINBOOL region::CreateEllipticRgnIndirect(LPCRECT lpRect)
    { return Attach(::CreateEllipticRgnIndirect(lpRect)); }
    WINBOOL region::CreatePolygonRgn(LPPOINT lpPoints, int32_t nCount, int32_t nMode)
    { return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode)); }
    WINBOOL region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int32_t nCount, int32_t nPolyFillMode)
    { return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode)); }
    WINBOOL region::CreateRoundRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
    { return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3)); }
    WINBOOL region::CreateFromPath(::draw2d::graphics * pgraphics)
    { ASSERT(pgraphics != NULL); return Attach(::PathToRegion((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1())); }
    WINBOOL region::CreateFromData(const XFORM* lpXForm, int32_t nCount, const RGNDATA* pRgnData)
    { return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData)); }
    int32_t region::GetRegionData(LPRGNDATA lpRgnData, int32_t nDataSize) const
    { ASSERT(get_os_data() != NULL); return (int32_t)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
    void region::SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    { ASSERT(get_os_data() != NULL); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }
    
    void region::SetRectRgn(LPCRECT lpRect)
    {
    ::SetRectRgn((HRGN)get_os_data(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }
    
    int32_t region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int32_t nCombineMode)
    { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
    (HRGN)pRgn2->get_os_data(), nCombineMode); }
    int32_t region::CopyRgn(const ::draw2d::region* pRgnSrc)
    { ASSERT(get_os_data() != NULL); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), NULL, RGN_COPY); }
    WINBOOL region::EqualRgn(const ::draw2d::region* pRgn) const
    { ASSERT(get_os_data() != NULL); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
    int32_t region::OffsetRgn(int32_t x, int32_t y)
    { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
    int32_t region::OffsetRgn(POINT point)
    { ASSERT(get_os_data() != NULL); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
    int32_t region::GetRgnBox(LPRECT lpRect) const
    { ASSERT(get_os_data() != NULL); return ::GetRgnBox((HRGN)get_os_data(), lpRect); }
    WINBOOL region::PtInRegion(int32_t x, int32_t y) const
    { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), x, y); }
    WINBOOL region::PtInRegion(POINT point) const
    { ASSERT(get_os_data() != NULL); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
    WINBOOL region::RectInRegion(LPCRECT lpRect) const
    { ASSERT(get_os_data() != NULL); return ::RectInRegion((HRGN)get_os_data(), lpRect); }*/
   
   /*
   
   bool region::get(cairo_t * pdc)
   {
      
      cairo_set_source_rgba(pdc, 0.0, 0.0, 0.0, 0.0);
      
      cairo_set_operator(pdc, CAIRO_OPERATOR_SOURCE);
      
      switch(m_etype)
      {
         case type_none:
            return true;
         case type_rect:
            return get_rect(pdc);
         case type_oval:
            return get_oval(pdc);
         case type_polygon:
            return get_polygon(pdc);
         case type_poly_polygon:
            return get_polygon(pdc);
         case type_combine:
            return get_combine(pdc);
         default:
            throw not_implemented(get_app());
      }
      
      return false;
      
   }
   
   bool region::get_rect(cairo_t * pdc)
   {
      
      cairo_rectangle(pdc, m_x1, m_y1, m_x2, m_y2);
      
      cairo_fill(pdc);
      
      return true;
      
   }
   
   bool region::get_oval(cairo_t * pdc)
   {
      
      double centerx    = (m_x2 + m_x1) / 2.0;
      double centery    = (m_y2 + m_y1) / 2.0;
      
      double radiusx    = abs(m_x2 - m_x1) / 2.0;
      double radiusy    = abs(m_y2 - m_y1) / 2.0;
      
      if(radiusx == 0.0 || radiusy == 0.0)
         return false;
      
      cairo_translate(pdc, centerx, centery);
      
      cairo_scale(pdc, radiusx, radiusy);
      
      cairo_arc(pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
      
      cairo_fill(pdc);
      
      cairo_scale(pdc, 1.0 / radiusx, 1.0 / radiusy);
      
      cairo_translate(pdc, -centerx,  -centery);
      
      return true;
      
   }
   
   bool region::get_polygon(cairo_t * pdc)
   {
      
      if(m_nCount <= 0)
         return true;
      
      
      cairo_move_to(pdc, m_lppoints[0].x, m_lppoints[0].y);
      
      for(int32_t i = 1; i < m_nCount; i++)
      {
         
         cairo_line_to(pdc, m_lppoints[i].x, m_lppoints[i].y);
         
      }
      cairo_fill(pdc);
      
      return true;
      
   }
   
   bool region::get_poly_polygon(cairo_t * pdc)
   {
      
      int32_t n;
      
      for(int32_t i = 0; i < m_nCount; i++)
      {
         int32_t jCount = m_lppolycounts[i];
         if(jCount > 0)
         {
            cairo_move_to(pdc, m_lppoints[n].x, m_lppoints[n].y);
            n++;
            for(int32_t j = 1; i < jCount; j++)
            {
               cairo_line_to(pdc, m_lppoints[n].x, m_lppoints[n].y);
               n++;
            }
         }
         
      }
      cairo_fill(pdc);
      
      return true;
      
   }
   
   bool region::get_combine(cairo_t * pdc)
   {
      
      cairo_push_group( pdc);
      
      dynamic_cast < ::lnx::region * >(m_pregion1)->get( pdc);
      
      cairo_pop_group_to_source(pdc);
      
      cairo_paint(pdc);
      
      cairo_push_group(pdc);
      
      dynamic_cast < ::lnx::region * >(m_pregion2)->get( pdc);
      
      cairo_pop_group_to_source(pdc);
      
      if(m_ecombine == ::draw2d::region::combine_add)
      {
         cairo_set_operator(pdc, CAIRO_OPERATOR_SOURCE);
      }
      else if(m_ecombine == ::draw2d::region::combine_exclude)
      {
         cairo_set_operator(pdc, CAIRO_OPERATOR_CLEAR);
      }
      else if(m_ecombine == ::draw2d::region::combine_intersect)
      {
         cairo_set_operator(pdc, CAIRO_OPERATOR_IN);
      }
      else
      {
         cairo_set_operator(pdc, CAIRO_OPERATOR_SOURCE);
      }
      
      cairo_paint(pdc);
      
   }
   
   */
   
} // namespace draw2d_quartz2d



