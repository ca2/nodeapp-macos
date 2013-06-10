#include "framework.h"
#include <math.h>


namespace mac
{
   
   
   graphics::graphics(::ca::application * papp) :
   ca(papp)
   {
      
      m_bPrinting       = FALSE;
      m_pdibAlphaBlend  = NULL;
//      m_pdc             = NULL;
      /*      m_hdc             = NULL;
       m_ppath           = NULL;
       m_ppathPaint      = NULL;
       */
      m_etextrendering  = ::ca::text_rendering_anti_alias_grid_fit;
      
   }
   
   graphics::graphics()
   {
      
      m_bPrinting       = FALSE;
//      m_pdc             = NULL;
      /*      m_pgraphics       = NULL;
       m_hdc             = NULL;
       m_ppath           = NULL;
       m_ppathPaint      = NULL;*/
      m_etextrendering  = ::ca::text_rendering_anti_alias_grid_fit;
      
      
   }
   
   
   void graphics::assert_valid() const
   {
      ::ca::object::assert_valid();
   }
   
   void graphics::dump(dump_context & dumpcontext) const
   {
      ::ca::object::dump(dumpcontext);
      
      //      dumpcontext << "get_handle1() = " << get_handle1();
      //    dumpcontext << "\nm_hAttribDC = " << get_handle2();
      //  dumpcontext << "\nm_bPrinting = " << m_bPrinting;
      
      dumpcontext << "\n";
   }
   
   
   graphics::~graphics()
   {
      
      /*      HDC hdc = Detach();
       
       if(hdc != NULL)
       {
       bool bDeleted = ::DeleteDC(hdc) != FALSE;
       if(!bDeleted)
       {
       TRACE("Failed to delete GDI device context");
       }
       }*/
      
//      if(m_pdc != NULL)
  //    {
    //     cairo_destroy(m_pdc);
      //   m_pdc = NULL;
      //}
      
      /*      if(m_ppath != NULL)
       {
       delete m_ppath;
       m_ppath = NULL;
       }
       
       if(m_ppathPaint != NULL)
       {
       delete m_ppathPaint;
       m_ppathPaint = NULL;
       }*/
      
   }
   
   
   /*   ::ca::window * graphics::GetWindow() const
    {
    ASSERT(get_handle1() != NULL); return ::win::window::from_handle(::WindowFromDC(get_handle1()));
    }
    */
   
   bool graphics::IsPrinting() const
   {
      return m_bPrinting;
   }
   
   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      throw not_supported_exception(get_app());
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }
   
   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      throw not_supported_exception(get_app());
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }
   
   bool graphics::CreateCompatibleDC(::ca::graphics * pgraphics)
   {
      
      return true;
      
//      if(m_pdc != NULL)
//      {
//         
//         cairo_destroy(m_pdc);
//         
//         m_pdc = NULL;
//         
//      }
//      
//      if(pgraphics == NULL)
//      {
//         
//         cairo_surface_t * psurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
//         
//         if(psurface == NULL)
//            return false;
//         
//         m_pdc = cairo_create(psurface);
//         
//         cairo_surface_destroy(psurface);
//         
//         return m_pdc != NULL;
//         
//      }
//      else
//      {
//         
//         cairo_surface_t * psurface = cairo_get_target(LNX_DC(pgraphics)->m_pdc);
//         
//         if(cairo_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
//            return false;
//         
//         cairo_surface_t * psurfaceNew = cairo_surface_create_similar(psurface, cairo_surface_get_content(psurface), 1, 1);
//         
//         if(psurfaceNew == NULL)
//            return false;
//         
//         m_pdc = cairo_create(psurfaceNew);
//         
//         cairo_surface_destroy(psurfaceNew);
//         
//         return m_pdc != NULL;
//         
//      }
//      /*
//       HDC hdc = NULL;
//       
//       if(pgraphics == NULL)
//       {
//       hdc = ::CreateCompatibleDC(NULL);
//       }
//       else
//       {
//       hdc = ::CreateCompatibleDC((HDC)(dynamic_cast<::win::graphics * >(pgraphics))->get_handle1());
//       }
//       
//       if(!Attach(hdc))
//       {
//       ::DeleteDC(hdc);
//       return FALSE;
//       }
//       */
//      
//      return true;
//      
   }
   
   int32_t graphics::ExcludeUpdateRgn(::ca::window * pWnd)
   {
      //    ASSERT(get_handle1() != NULL);
      //      return ::ExcludeUpdateRgn(get_handle1(), WIN_WINDOW(pWnd)->get_handle());
      throw not_implemented(get_app());
      return 0;
   }
   
   int32_t graphics::GetDeviceCaps(int32_t nIndex) const
   {
      /*      ASSERT(get_handle2() != NULL);
       return ::GetDeviceCaps(get_handle2(), nIndex);*/
      throw not_implemented(get_app());
      return 0;
   }
   
   point graphics::GetBrushOrg() const
   {
      /*      ASSERT(get_handle1() != NULL);
       POINT point;
       VERIFY(::GetBrushOrgEx(get_handle1(), &point));
       return point;*/
      throw not_implemented(get_app());
      return point(0, 0);
      
   }
   
   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {
      /*      ASSERT(get_handle1() != NULL);
       POINT point;
       VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
       return point;*/
      throw not_implemented(get_app());
      return point(0, 0);
      
   }
   
   point graphics::SetBrushOrg(POINT point)
   {
      /*      ASSERT(get_handle1() != NULL);
       VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
       return point;*/
      throw not_implemented(get_app());
      return ::point(0, 0);
      
   }
   
   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      /*      ASSERT(get_handle2() != NULL);
       return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);*/
      throw not_implemented(get_app());
      return 0;
      
   }
   
   ::ca::bitmap* graphics::SelectObject(::ca::bitmap* pbitmap)
   {
      
//      
//      if(pbitmap == NULL)
//         return NULL;
//      
//      /*      if(get_handle1() == NULL)
//       return NULL;
//       if(pbitmap == NULL)
//       return NULL;
//       return dynamic_cast < ::ca::bitmap* > (SelectGdiObject(get_app(), get_handle1(), pbitmap->get_os_data()));*/
//      if(m_pdc != NULL)
//      {
//         cairo_destroy(m_pdc);
//      }
//      
//      m_pdc = cairo_create((cairo_surface_t *) pbitmap->get_os_data());
//      
//      set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
//      
//      m_bitmap = pbitmap;
      
      return m_bitmap;
   }
   
   
   ::ca::graphics_object* graphics::SelectObject(::ca::graphics_object* pObject)
   {
      /*      ASSERT(get_handle1() != NULL);
       if(pObject == NULL)
       return NULL;
       return SelectGdiObject(get_app(), get_handle1(), pObject->get_os_data()); */
      return NULL;
   }
   
   /*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
    {
    
    UINT uiType = GetObjectType(hObject);
    
    if(uiType == OBJ_BITMAP)
    {
    
    HBITMAP hbitmap = (HBITMAP) hObject;
    
    if(m_bitmap.is_null())
    m_bitmap.create(get_app());
    
    if(m_bitmap.is_null())
    return NULL;
    
    (dynamic_cast < ::win::bitmap * > (m_bitmap.m_p))->m_pbitmap = new Gdiplus::Bitmap(hbitmap, NULL);
    
    if(m_pgraphics != NULL)
    {
    delete m_pgraphics;
    }
    
    m_pgraphics = new Gdiplus::Graphics((Gdiplus::Bitmap *) m_bitmap->get_os_data());
    
    set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
    
    return hbitmap;
    
    }
    
     ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
    //return (hObject != NULL) ? ::SelectObject(get_handle1(), hObject) : NULL; */
   /*    return NULL;
    }*/
   
   COLORREF graphics::GetNearestColor(COLORREF crColor) const
   {
      //throw not_implemented(get_app());
      return crColor;
      //      return ::GetNearestColor(get_handle2(), crColor);
   }
   
   UINT graphics::RealizePalette()
   {
      //      return ::RealizePalette(get_handle1());
      return 0;
   }
   
   void graphics::UpdateColors()
   {
      //::UpdateColors(get_handle1());
      
   }
   
   COLORREF graphics::GetBkColor() const
   {
      //return ::GetBkColor(get_handle2());
      return 0;
   }
   
   int32_t graphics::GetBkMode() const
   {
      //return ::GetBkMode(get_handle2());
      return 0;
   }
   
   int32_t graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(get_handle2());
//      return cairo_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::ca::fill_mode_winding : ::ca::fill_mode_alternate;
      return 0;
   }
   
   int32_t graphics::GetROP2() const
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }
   
   int32_t graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }
   
   COLORREF graphics::GetTextColor() const
   {
      //return ::GetTextColor(get_handle2());
      return 0;
   }
   
   int32_t graphics::GetMapMode() const
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }
   
   int32_t graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }
   
   bool graphics::GetWorldTransform(XFORM* pXform) const
   {
      
      //return ::GetWorldTransform(get_handle2(),pXform) != FALSE;
      return 0;
      
   }
   
   size graphics::GetViewportExt() const
   {
      /*SIZE size;
       ::GetViewportExtEx(get_handle2(), &size);
       return size;*/
      
      return ::size(0, 0);
   }
   
   point graphics::GetWindowOrg() const
   {
      /*POINT point;
       ::GetWindowOrgEx(get_handle2(), &point);
       return point;*/
      return ::point(0, 0);
   }
   
   size graphics::GetWindowExt() const
   {
      /*SIZE size;
       ::GetWindowExtEx(get_handle2(), &size);
       return size;*/
      return ::size(0, 0);
   }
   
   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {
      //return SetViewportOrg(point.x, point.y);
      return ::point(0, 0);
   }
   
   size graphics::SetViewportExt(SIZE size)
   {
      //return SetViewportExt(size.cx, size.cy);
      return ::size(0, 0);
   }
   
   point graphics::SetWindowOrg(POINT point)
   {
      //return SetWindowOrg(point.x, point.y);
      return ::point(0, 0);
   }
   
   size graphics::SetWindowExt(SIZE size)
   {
      //return SetWindowExt(size.cx, size.cy);
      return ::size(0, 0);
   }
   
   void graphics::DPtoLP(LPPOINT lpPoints, int32_t nCount) const
   {
      //::DPtoLP(get_handle2(), lpPoints, nCount);
   }
   
   void graphics::DPtoLP(LPRECT lpRect) const
   {
      //::DPtoLP(get_handle2(), (LPPOINT)lpRect, 2);
   }
   
   void graphics::LPtoDP(LPPOINT lpPoints, int32_t nCount) const
   {
      //::LPtoDP(get_handle2(), lpPoints, nCount);
   }
   
   void graphics::LPtoDP(LPRECT lpRect) const
   {
      //::LPtoDP(get_handle2(), (LPPOINT)lpRect, 2);
   }
   
   bool graphics::FillRgn(::ca::region* pRgn, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;
      return false;
      
   }
   
   bool graphics::FrameRgn(::ca::region* pRgn, ::ca::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {
      
      //      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;
      throw not_implemented(get_app());
      return false;
      
   }
   
   bool graphics::InvertRgn(::ca::region* pRgn)
   {
      
      //    ASSERT(get_handle1() != NULL);
      
      //      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;
      throw not_implemented(get_app());
      return false;
      
      
   }
   
   bool graphics::PaintRgn(::ca::region* pRgn)
   {
      
      //      ASSERT(get_handle1() != NULL);
      
      //    return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;
      throw not_implemented(get_app());
      return false;
      
   }
   
   bool graphics::PtVisible(int32_t x, int32_t y) const
   {
      
      //    ASSERT(get_handle1() != NULL);
      
      //      return ::PtVisible(get_handle1(), x, y) != FALSE;
      throw not_implemented(get_app());
      return false;
      
   }
   
   bool graphics::PtVisible(POINT point) const
   {
      
      //      ASSERT(get_handle1() != NULL);
      
      //      return PtVisible(point.x, point.y);
      
      throw not_implemented(get_app());
      return false;
      
   }
   
   bool graphics::RectVisible(LPCRECT lpRect) const
   {
      
      //      ASSERT(get_handle1() != NULL);
      
      //      return ::RectVisible(get_handle1(), lpRect) != FALSE;
      
      throw not_implemented(get_app());
      return false;
      
   }
   
   point graphics::GetCurrentPosition() const
   {
      //      ASSERT(get_handle2() != NULL);
      //      POINT point;
      //      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      //      return point;
      throw not_implemented(get_app());
      return ::point(0, 0);
      
   }
   
   bool graphics::Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      
//      double centerx    = (x2 + x1) / 2.0;
//      double centery    = (y2 + y1) / 2.0;
//      
//      double radiusx    = abs(x2 - x1) / 2.0;
//      double radiusy    = abs(y2 - y1) / 2.0;
//      
//      if(radiusx == 0.0 || radiusy == 0.0)
//         return false;
//      
//      double start      = atan2(y3 - centery, x3 - centerx);
//      double end        = atan2(y4 - centery, x4 - centerx);
//      
//      
//      cairo_translate(m_pdc, centerx, centery);
//      
//      cairo_scale(m_pdc, radiusx, radiusy);
//      
//      cairo_arc(m_pdc, 0.0, 0.0, 1.0, start, end);
//      
//      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
//      
//      cairo_translate(m_pdc, -centerx,  -centery);
//      
      return true;
      
   }
   
   bool graphics::Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      
      return Arc(
                 lpRect->left,
                 lpRect->top,
                 lpRect->right,
                 lpRect->bottom,
                 ptStart.x,
                 ptStart.y,
                 ptEnd.x,
                 ptEnd.y);
      
   }
   
   bool graphics::Polyline(const POINT* lpPoints, int32_t nCount)
   {
      
      /*ASSERT(get_handle1() != NULL);
       
       return ::Polyline(get_handle1(), lpPoints, nCount) != FALSE;*/
      
      throw not_implemented(get_app());
      return false;
      
   }
   
   void graphics::FillRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      return;
      
      //      ASSERT(get_handle1() != NULL); ::FillRect(get_handle1(), lpRect, (HBRUSH)pBrush->get_os_data());
      
   }
   void graphics::FrameRect(LPCRECT lpRect, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      return;
      
      //       ASSERT(get_handle1() != NULL); ::FrameRect(get_handle1(), lpRect, (HBRUSH)pBrush->get_os_data());
      
   }
   
   void graphics::InvertRect(LPCRECT lpRect)
   {
      
      throw not_implemented(get_app());
      return;
      
      //      ASSERT(get_handle1() != NULL); ::InvertRect(get_handle1(), lpRect);
      
   }
   
   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {
      
      throw not_implemented(get_app());
      return false;
      
      
      //    ASSERT(get_handle1() != NULL);
      
      //  if(picon == NULL)
      //   return false;
      
      //      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != FALSE;
      
   }
   
   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {
      
      throw not_implemented(get_app());
      return false;
      /*      ASSERT(get_handle1() != NULL);
       
       if(picon == NULL)
       return false;
       
       return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != FALSE;*/
      
   }
   
   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {
      
      return false;
      
      /*      try
       {
       
       if(picon == NULL)
       return FALSE;
       
       if(m_pgraphics == NULL)
       return FALSE;
       
       bool bOk = FALSE;
       
       BITMAPINFO info;
       COLORREF * pcolorref;
       
       ZeroMemory(&info, sizeof (BITMAPINFO));
       
       info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
       info.bmiHeader.biWidth         = cx;
       info.bmiHeader.biHeight        = - cy;
       info.bmiHeader.biPlanes        = 1;
       info.bmiHeader.biBitCount      = 32;
       info.bmiHeader.biCompression   = BI_RGB;
       info.bmiHeader.biSizeImage     = cx * cy * 4;
       
       HBITMAP hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **) &pcolorref, NULL, NULL);
       
       HDC hdc = ::CreateCompatibleDC(NULL);
       
       HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);
       
       if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, NULL, DI_IMAGE | DI_MASK))
       {
       
       ::SelectObject(hdc, hbitmapOld);
       
       try
       {
       
       Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);
       
       bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel) == Gdiplus::Ok;
       
       }
       catch(...)
       {
       }
       
       }
       
       ::DeleteDC(hdc);
       
       ::DeleteObject(hbitmap);
       
       return bOk;
       
       }
       catch(...)
       {
       return FALSE;
       }
       */
      //return ::DrawIconEx(get_handle1(), x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
      
   }
   
   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
      
   }
   
   bool graphics::DrawState(point pt, size size, ::ca::bitmap* pBitmap, UINT nFlags, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)pBitmap->get_os_data(), 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
      
   }
   
   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;
      
   }
   
   
   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;
      
   }
   
   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush,  NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
      
   }
   
   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::ca::brush* pBrush)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
      
   }
   
   /*
    
    bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
    
    }
    
    bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::ca::brush* pBrush)
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
    
    }
    
    */
   
   bool graphics::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawEdge(get_handle1(), lpRect, nEdge, nFlags) != FALSE;
      
   }
   
   bool graphics::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
   {
      
      throw not_implemented(get_app());
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawFrameControl(get_handle1(), lpRect, nType, nState) != FALSE;
      
   }
   
   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }
   
   bool graphics::Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //ASSERT(get_handle1() != NULL);
      //return ::Chord(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;
      
   }
   
   void graphics::DrawFocusRect(LPCRECT lpRect)
   {
      
      throw not_implemented(get_app());
      
      //ASSERT(get_handle1() != NULL); ::DrawFocusRect(get_handle1(), lpRect);
      
   }
   
   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
//      double centerx    = (x2 + x1) / 2.0;
//      double centery    = (y2 + y1) / 2.0;
//      
//      double radiusx    = abs(x2 - x1) / 2.0;
//      double radiusy    = abs(y2 - y1) / 2.0;
//      
//      if(radiusx == 0.0 || radiusy == 0.0)
//         return false;
//      
//      cairo_translate(m_pdc, centerx, centery);
//      
//      cairo_scale(m_pdc, radiusx, radiusy);
//      
//      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
//      
//      draw();
//      
//      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
//      
//      cairo_translate(m_pdc, -centerx,  -centery);
      
      return true;
      
   }
   
   bool graphics::DrawEllipse(LPCRECT lprect)
   {
      
      return DrawEllipse(lprect->left, lprect->top, lprect->right, lprect->bottom);
      
      /*return ::Ellipse(get_handle1(), lpRect->left, lpRect->top,
       lpRect->right, lpRect->bottom); */
      
      
   }
   
   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
//      double centerx    = (x2 + x1) / 2.0;
//
//      double centery    = (y2 + y1) / 2.0;
//      
//      double radiusx    = abs(x2 - x1) / 2.0;
//      
//      double radiusy    = abs(y2 - y1) / 2.0;
//      
//      if(radiusx == 0.0 || radiusy == 0.0)
//         return false;
//      
//      cairo_translate(m_pdc, centerx, centery);
//      
//      cairo_scale(m_pdc, radiusx, radiusy);
//      
//      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
//      
//      fill();
//      
//      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
//      
//      cairo_translate(m_pdc, -centerx,  -centery);
      
      return true;
   }
   
   bool graphics::FillEllipse(LPCRECT lpRect)
   {
      
      /*return ::Ellipse(get_handle1(), lpRect->left, lpRect->top,
       lpRect->right, lpRect->bottom); */
      
      return FillEllipse(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
      
   }
   
   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*      ASSERT(get_handle1() != NULL);
       return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;*/
      
   }
   
   bool graphics::Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      
      throw not_implemented(get_app());
      return false;
      
      
      /*      ASSERT(get_handle1() != NULL);
       return ::Pie(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;*/
      
   }
   
   bool graphics::fill_polygon(const POINTD * pa, int32_t nCount)
   {
//      
//      if(nCount <= 0)
//         return TRUE;
//      
//      
//      cairo_move_to(m_pdc, pa[0].x, pa[0].y);
//      
//      for(int32_t i = 1; i < nCount; i++)
//      {
//         cairo_line_to(m_pdc, pa[i].x, pa[i].y);
//      }
//      
//      fill();
      
      return true;
      
   }
   
   bool graphics::fill_polygon(const POINT* pa, int32_t nCount)
   {
//      
//      if(nCount <= 0)
//         return TRUE;
//      
//      
//      cairo_move_to(m_pdc, pa[0].x, pa[0].y);
//      
//      for(int32_t i = 1; i < nCount; i++)
//      {
//         cairo_line_to(m_pdc, pa[i].x, pa[i].y);
//      }
//      
//      fill();
      
      return true;
      
   }
   
   
   bool graphics::Polygon(const POINT* pa, int32_t nCount)
   {
//      
//      
//      if(nCount <= 0)
//         return TRUE;
//      
//      
//      cairo_move_to(m_pdc, pa[0].x, pa[0].y);
//      
//      for(int32_t i = 1; i < nCount; i++)
//      {
//         
//         cairo_line_to(m_pdc, pa[i].x, pa[i].y);
//         
//      }
      
      return fill_and_draw();
      
      
      
   }
   
   
   bool graphics::PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return false;
      //   ASSERT(get_handle1() != NULL); return ::PolyPolygon(get_handle1(), lpPoints, lpPolyCounts, nCount) != FALSE;
      
   }
   
   bool graphics::Rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
      /*      Gdiplus::RectF rectf((Gdiplus::REAL) x1, (Gdiplus::REAL) y1, (Gdiplus::REAL) (x2 - x1), (Gdiplus::REAL) (y2 - y1));
       
       bool bOk1 = m_pgraphics->FillRectangle(gdiplus_brush(), rectf) == Gdiplus::Status::Ok;
       
       bool bOk2 = m_pgraphics->DrawRectangle(gdiplus_pen(), rectf) == Gdiplus::Status::Ok;
       
       return bOk1 && bOk2;*/
//      
//      
//      cairo_rectangle(m_pdc, x1, y1, x2, y2);
//      
//      
      return fill_and_draw();
      
      
      
      
   }
   
   bool graphics::Rectangle(LPCRECT lpRect)
   {
      
      return Rectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
      
   }
   
   bool graphics::DrawRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
//      
//      cairo_rectangle(m_pdc, x1, y1, x2, y2);
//      
      return draw();
      
   }
   
   bool graphics::DrawRectangle(LPCRECT lpRect)
   {
      
      return DrawRectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
      
   }
   
   bool graphics::FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
//      cairo_rectangle(m_pdc, x1, y1, x2, y2);
      
      return fill();
      
   }
   
   bool graphics::FillRectangle(LPCRECT lpRect)
   {
      
      return FillRectangle(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
      
   }
   
   bool graphics::RoundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::RoundRect(get_handle1(), x1, y1, x2, y2, x3, y3) != FALSE;
      
   }
   
   bool graphics::RoundRect(LPCRECT lpRect, POINT point)
   {
      
      //ASSERT(get_handle1() != NULL);
      //return ::RoundRect(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y) != FALSE;
      throw not_implemented(get_app());
      return false;
      
      
   }
   
   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, DWORD dwRop)
   {
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;
      
      throw not_implemented(get_app());
      return false;
      
      
   }
   
   
   bool graphics::BitBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, DWORD dwRop)
   {
      
      
      if(m_pdibAlphaBlend != NULL)
      {
         throw not_implemented(get_app());
         
         /*rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
          
          
          ::ca::dib * pdibWork = NULL;
          ::ca::dib * pdibWork2 = NULL;
          //         ::ca::dib * pdibWork3 = NULL;
          ::ca::dib * pdibWork4 = NULL;
          
          
          class point ptSrc(xSrc, ySrc);
          class point ptDest(x, y);
          class size size(nWidth, nHeight);
          
          
          
          ::ca::dib_sp spdib;
          if(pdibWork == NULL)
          {
          spdib.create(get_app());
          pdibWork = spdib;
          }
          if(pdibWork == NULL)
          return false;
          if(!pdibWork->create(size))
          return false;
          
          pdibWork->Fill(0, 0, 0, 0);
          
          pdibWork->get_graphics()->set_alpha_mode(::ca::alpha_mode_set);
          
          if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
          return false;
          
          
          
          
          ::ca::dib_sp spdib2;
          if(pdibWork2 == NULL)
          {
          spdib2.create(get_app());
          pdibWork2 = spdib2;
          }
          
          
          ::ca::dib_sp spdib4;
          if(pdibWork4 == NULL)
          {
          spdib4.create(get_app());
          pdibWork4 = spdib4;
          }
          if(pdibWork4 == NULL)
          return false;
          if(!pdibWork4->create(size))
          return false;
          
          
          pdibWork4->Fill(255, 0, 0, 0);
          
          pdibWork4->get_graphics()->set_alpha_mode(::ca::alpha_mode_set);
          
          pdibWork4->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
          m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
          class size(max(0, m_pdibAlphaBlend->width() - max(0, x - m_ptAlphaBlend.x)), max(0, m_pdibAlphaBlend->height() - max(0, y - m_ptAlphaBlend.y))));
          
          pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);
          
          pdibWork->get_graphics()->set_alpha_mode(::ca::alpha_mode_blend);
          
          pdibWork->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
          m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
          class size(max(0, size.cx - max(0, x - m_ptAlphaBlend.x)), max(0, size.cy - max(0, y - m_ptAlphaBlend.y))));*/
         
         //keeper < ::ca::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
         
         /*Gdiplus::CompositingMode mode = m_pgraphics->GetCompositingMode();
          
          //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
          
          bool bOk = m_pgraphics->DrawImage(
          (Gdiplus::Bitmap *) pdibWork->get_graphics()->GetCurrentBitmap().get_os_data(),
          x, y , 0, 0, nWidth, nHeight, Gdiplus::UnitPixel) == Gdiplus::Status::Ok;
          
          
          m_pgraphics->SetCompositingMode(mode);
          
          return bOk;
          
          //return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), null_point());
          */
         
      }
      
      
      try
      {
         
//         if(pgraphicsSrc == NULL)
//            return false;
//         
//         cairo_pattern_t * ppattern = cairo_get_source((cairo_t *) pgraphicsSrc->get_os_data());
//         
//         if(ppattern == NULL)
//            return false;
//         
//         cairo_set_source(m_pdc, ppattern);
//         
//         cairo_paint(m_pdc);
         
         return true;
         
      }
      catch(...)
      {
         
         return false;
         
      }
      
      //return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, dwRop);
      
   }
   
   
   bool graphics::StretchBlt(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, DWORD dwRop)
   {
      
//      if(pgraphicsSrc == NULL)
//         return false;
//      
//      if(nSrcWidth == 0 || nSrcHeight == 0 || nDstWidth == 0 || nDstHeight == 0)
//         return false;
//      
//      cairo_pattern_t * ppattern = cairo_get_source((cairo_t *) pgraphicsSrc->get_os_data());
//      
//      if(ppattern == NULL)
//         return false;
//      
//      cairo_translate(m_pdc, xDst, yDst);
//      
//      cairo_scale(m_pdc, (double) nDstWidth / (double) nSrcWidth, (double) nDstHeight / (double) nSrcHeight);
//      
//      cairo_set_source(m_pdc, ppattern);
//      
//      cairo_paint(m_pdc);
//      
//      cairo_scale(m_pdc, (double) nSrcWidth / (double) nDstWidth, (double) nSrcHeight / (double) nDstHeight);
//      
//      cairo_translate(m_pdc, -xDst, -yDst);
      
      return true;
      
      //return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);
      
   }
   
   
   COLORREF graphics::GetPixel(int32_t x, int32_t y) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetPixel(get_handle1(), x, y);
      
   }
   
   COLORREF graphics::GetPixel(POINT point) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetPixel(get_handle1(), point.x, point.y);
      
   }
   
   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixel(get_handle1(), x, y, crColor);
      
   }
   
   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixel(get_handle1(), point.x, point.y, crColor);
      
   }
   
   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::FloodFill(get_handle1(), x, y, crColor) != FALSE;
      
   }
   
   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != FALSE;
      
   }
   
   
   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST
   
   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST
   
   bool graphics::TextOut(int32_t x, int32_t y, const string & str)
   {
      
      if(m_pdibAlphaBlend != NULL)
      {
         throw not_implemented(get_app());
         //if(GetBkMode() == TRANSPARENT)
         /*         {
          //   return TRUE;
          rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
          rect rectText(point(x, y), GetTextExtent(str));
          if(rectIntersect.intersect(rectIntersect, rectText))
          {
          ::ca::dib_sp dib0(get_app());
          dib0->create(rectText.size());
          dib0->Fill(0, 0, 0, 0);
          dib0->get_graphics()->SetTextColor(ARGB(255, 255, 255, 255));
          dib0->get_graphics()->SelectObject(&GetCurrentFont());
          dib0->get_graphics()->SetBkMode(TRANSPARENT);
          dib0->get_graphics()->TextOut(0, 0, str);
          dib0->ToAlpha(0);*/
         /*             ::ca::dib_sp dib1(get_app());
          dib1->create(rectText.size());
          dib1->Fill(0, 0, 0, 0);
          dib1->get_graphics()->set_color(m_crColor);
          dib1->get_graphics()->SelectObject(&GetCurrentFont());
          dib1->get_graphics()->SetBkMode(TRANSPARENT);
          dib1->get_graphics()->TextOut(0, 0, str);
          //dib1->channel_from(visual::rgba::channel_alpha, dib0);
          ::ca::dib_sp dib2(get_app());
          dib2->create(rectText.size());
          dib2->Fill(255, 0, 0, 0);
          dib2->get_graphics()->set_alpha_mode(::ca::alpha_mode_set);
          dib2->from(point(max(0, m_ptAlphaBlend.x - x), max(0, m_ptAlphaBlend.y - y)),
          m_pdibAlphaBlend->get_graphics(), point(max(0, x - m_ptAlphaBlend.x), max(0, y - m_ptAlphaBlend.y)),
          size(max(0, m_pdibAlphaBlend->width()-max(0, x - m_ptAlphaBlend.x)),
          max(0, m_pdibAlphaBlend->height()-max(0, y - m_ptAlphaBlend.y))));
          dib1->channel_multiply(visual::rgba::channel_alpha, dib2);
          ::ca::dib_sp dib3(get_app());
          dib1->mult_alpha(dib3);*/
         
         /*           keeper < ::ca::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
          
          return System.imaging().true_blend(this, point(x, y), rectText.size(), dib1->get_graphics(), null_point());
          
          BLENDFUNCTION bf;
          bf.BlendOp     = AC_SRC_OVER;
          bf.BlendFlags  = 0;
          bf.SourceConstantAlpha = 0xFF;
          bf.AlphaFormat = AC_SRC_ALPHA;
          return ::AlphaBlend(get_handle1(), x, y,
          rectText.width(), rectText.height(), WIN_HDC(dib1->get_graphics()), 0, 0, rectText.width(),
          rectText.height(), bf) != FALSE; */
         //      }
         // }
      }
      
      //ASSERT(get_handle1() != NULL);
      //wstring wstr = ::ca::international::utf8_to_unicode(str);
      return TextOut(x, y, str, (int32_t) str.get_length());
      
   } // call virtual
   
   bool graphics::TextOut(double x, double y, const string & str)
   {
      if(m_pdibAlphaBlend != NULL)
      {
         if(GetBkMode() == TRANSPARENT)
         {
            //   return TRUE;
            rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
            rect rectText(point((int64_t) x, (int64_t) y), GetTextExtent(str));
            if(rectIntersect.intersect(rectIntersect, rectText))
            {
               ::ca::dib_sp dib0(allocer());
               dib0->create(rectText.size());
               dib0->get_graphics()->SetTextColor(RGB(255, 255, 255));
               dib0->get_graphics()->SelectObject(&GetCurrentFont());
               dib0->get_graphics()->SetBkMode(TRANSPARENT);
               dib0->get_graphics()->TextOut(0, 0, str);
               dib0->ToAlpha(0);
               ::ca::dib_sp dib1(allocer());
               dib1->create(rectText.size());
               dib1->get_graphics()->SetTextColor(GetTextColor());
               dib1->get_graphics()->SelectObject(&GetCurrentFont());
               dib1->get_graphics()->SetBkMode(TRANSPARENT);
               dib1->get_graphics()->TextOut(0, 0, str);
               dib1->channel_from(visual::rgba::channel_alpha, dib0);
               ::ca::dib_sp dib2(allocer());
               dib2->create(rectText.size());
               dib2->Fill(255, 0, 0, 0);
               dib2->from(point((int64_t) max(0, m_ptAlphaBlend.x - x), (int64_t) max(0, m_ptAlphaBlend.y - y)),
                          m_pdibAlphaBlend->get_graphics(), point((int64_t) max(0, x - m_ptAlphaBlend.x), (int64_t) max(0, y - m_ptAlphaBlend.y)), rectText.size());
               dib1->channel_multiply(visual::rgba::channel_alpha, dib2);
               /*::ca::dib_sp dib3(get_app());
                dib1->mult_alpha(dib3);*/
               
               keeper < ::ca::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
               
               return System.visual().imaging().true_blend(this, point((int64_t) x, (int64_t) y), rectText.size(), dib1->get_graphics(), null_point());
               
               /*BLENDFUNCTION bf;
                bf.BlendOp     = AC_SRC_OVER;
                bf.BlendFlags  = 0;
                bf.SourceConstantAlpha = 0xFF;
                bf.AlphaFormat = AC_SRC_ALPHA;
                return ::AlphaBlend(get_handle1(), x, y,
                rectText.width(), rectText.height(), WIN_HDC(dib1->get_graphics()), 0, 0, rectText.width(),
                rectText.height(), bf) != FALSE; */
            }
         }
      }
      
      //ASSERT(get_handle1() != NULL);
      //wstring wstr = ::ca::international::utf8_to_unicode(str);
      return TextOut(x, y, str, (int32_t) str.get_length());
      
   } // call virtual
   
   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths) != FALSE;
      
   }
   
   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, LPCRECT lpRect, const string & str, LPINT lpDxWidths)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, str, (UINT)str.get_length(), lpDxWidths) != FALSE;
      
   }
   
   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::TabbedTextOut(get_handle1(), x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
      
   }
   
   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::TabbedTextOut(get_handle1(), x, y, str, (int32_t)str.get_length(), nTabPositions, lpnTabStopPositions, nTabOrigin);
      
   }
   
   
   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTabbedTextExtent(get_handle2(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);
      
   }
   
   size graphics::GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTabbedTextExtent(get_handle2(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);
      
   }
   
   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTabbedTextExtent(get_handle1(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);
      
   }
   
   size graphics::GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTabbedTextExtent(get_handle1(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);
      
   }
   
   bool graphics::GrayString(::ca::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount,int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != FALSE;
      
   }
   
   UINT graphics::GetTextAlign() const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextAlign(get_handle2());
      
   }
   
   int32_t graphics::GetTextFace(int32_t nCount, LPTSTR lpszFacename) const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextFace(get_handle2(), nCount, lpszFacename);
      
   }
   
   int32_t graphics::GetTextFace(string & rString) const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      int32_t nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256)); rString.ReleaseBuffer();
      //      return nResult;
      
   }
   
   bool graphics::get_text_metrics(LPTEXTMETRIC lpMetrics) const
   {
//      //ASSERT(get_handle2() != NULL); return ::GetTextMetrics(get_handle2(), lpMetrics);
//      /*wstring wstr(L"123AWZwmc");
//       Gdiplus::RectF rect;
//       Gdiplus::RectF rect2;
//       Gdiplus::PointF origin(0, 0);
//       m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect);
//       
//       wstr = L"123AWZwmcpQçg";
//       m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect2);
//       
//       lpMetrics->tmAveCharWidth = rect.width / (double) wstr.get_length();
//       lpMetrics->tmAscent = rect.height;
//       lpMetrics->tmDescent = rect2.height - rect.height;*/
//      
//      
//      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));
//      
//      ((::lnx::graphics *) this)->set(&m_fontxyz);
//      
//      cairo_font_extents_t e;
//      
//      cairo_font_extents(m_pdc, &e);
//      
//      //Gdiplus::FontFamily family;
//      
//      
//      //if(((graphics * )this)->gdiplus_font() == NULL)
//      //   return FALSE;
//      
//      //((graphics * )this)->gdiplus_font()->GetFamily(&family);
//      
//      //double dHeight = family.GetEmHeight(((graphics * )this)->gdiplus_font()->GetStyle());
//      
//      //lpMetrics->tmAscent              = (LONG) (((graphics * )this)->gdiplus_font()->GetSize() * family.GetCellAscent(((graphics * )this)->gdiplus_font()->GetStyle()) / dHeight);
//      //lpMetrics->tmDescent             = (LONG) (((graphics * )this)->gdiplus_font()->GetSize() * family.GetCellDescent(((graphics * )this)->gdiplus_font()->GetStyle()) / dHeight);
//      //lpMetrics->tmHeight              = (LONG) (((graphics * )this)->gdiplus_font()->GetSize());
//      lpMetrics->tmAscent              = (LONG) e.ascent;
//      lpMetrics->tmDescent             = (LONG) e.descent;
//      lpMetrics->tmHeight              = (LONG) e.height;
//      
//      lpMetrics->tmInternalLeading     = (LONG) lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight;
//      lpMetrics->tmExternalLeading     = (LONG) (e.height * 0.25);
//      //                                                (e.family.GetLineSpacing(((graphics * )this)->gdiplus_font()->GetStyle())
//      //                                              - family.GetCellAscent(((graphics * )this)->gdiplus_font()->GetStyle())
//      //                                            - family.GetCellDescent(((graphics * )this)->gdiplus_font()->GetStyle())) / dHeight);
//      
//      //      m_spfont->
//      
//      //     ::Gdiplus::Font font2(pfamilyMono, pfamilyMono->GetEmHeight(((graphics * )this)->gdiplus_font()->GetStyle()));
//      //
//      string str(L"123AWZwmc123AWZwmcpQçg");
//      /*      Gdiplus::RectF rect;
//       Gdiplus::RectF rect2;
//       Gdiplus::PointF origin(0, 0);
//       
//       m_pgraphics->MeasureString(wstr, (INT) wstr.get_length(), ((graphics * )this)->gdiplus_font(), origin, &rect);*/
//      
//      ::size size = GetTextExtent(str);
//      
//      
//      /*wstr = L"";
//       m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect2);*/
//      
//      lpMetrics->tmAveCharWidth        = (LONG) (size.cx * m_fontxyz.m_dFontWidth / (double) str.get_length());
//      
//      
      return TRUE;
   }
   
   
   bool graphics::get_output_text_metrics(LPTEXTMETRIC lpMetrics) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;
      
   }
   
   
   int32_t graphics::GetTextCharacterExtra() const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextCharacterExtra(get_handle2());
      
   }
   
   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;
      
   }
   
   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;
      
   }
   
   DWORD graphics::GetFontLanguageInfo() const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetFontLanguageInfo(get_handle1());
      
   }
   
   /*
    
    DWORD graphics::GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);
    
    }
    
    DWORD graphics::GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (int32_t) str.get_length(), nMaxExtent, lpResults, dwFlags);
    
    }
    
    */
   
   size graphics::GetAspectRatioFilter() const
   {
      
      throw not_implemented(get_app());
      return size(0, 0);
      
      //      ASSERT(get_handle2() != NULL);
      //      SIZE size;
      //      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
      //      return size;
      
   }
   
   
   bool graphics::ScrollDC(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::ca::region* pRgnUpdate, LPRECT lpRectUpdate)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;
      
   }
   
   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);
      
   }
   
   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetBoundsRect(get_handle1(), lpRectBounds, flags);
      
   }
   
   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetBoundsRect(get_handle2(), lpRectBounds, flags);
      
   }
   
   /*
    
    bool graphics::ResetDC(const DEVMODE* lpDevMode)
    {
    
    throw not_implemented(get_app());
    return false;
    
    //    ASSERT(get_handle2() != NULL);
    //    return ::ResetDC(get_handle2(), lpDevMode) != NULL;
    
    }
    
    UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);
    
    }
    
    bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != FALSE;
    
    }
    
    */
   
   DWORD graphics::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);
      
   }
   
   /*
    
    int32_t graphics::GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);
    
    }
    
    DWORD graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetGlyphOutline(get_handle2(), nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
    
    }
    
    */
   
   /*
    
    // ::userbase::document handling functions
    int32_t graphics::StartDoc(LPDOCINFO lpDocInfo)
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::StartDoc(get_handle1(), lpDocInfo);
    
    }
    
    */
   
   int32_t graphics::StartPage()
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::StartPage(get_handle1());
      
   }
   
   int32_t graphics::EndPage()
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::EndPage(get_handle1());
      
   }
   
   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);
      
   }
   
   int32_t graphics::AbortDoc()
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::AbortDoc(get_handle1());
      
   }
   
   int32_t graphics::EndDoc()
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::EndDoc(get_handle1());
      
   }
   
   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask, DWORD dwRop)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;
      
   }
   
   bool graphics::PlgBlt(LPPOINT lpPoint, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nWidth, int32_t nHeight, ::ca::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != FALSE;
      
   }
   
   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;
      
   }
   
   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;
      
   }
   
   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;
      
   }
   
   bool graphics::ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ArcTo(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
      
   }
   
   int32_t graphics::GetArcDirection() const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetArcDirection(get_handle2());
      
   }
   
   bool graphics::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;
      
   }
   
   /*
    
    bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
    
    }
    
    */
   
   ::ca::pen & graphics::GetCurrentPen() const
   {
      
      return *m_sppen.m_p;
      
   }
   
   ::ca::brush & graphics::GetCurrentBrush() const
   {
      
      return *m_spbrush.m_p;
      
   }
   
   ::ca::palette & graphics::GetCurrentPalette() const
   {
      
      return *(::ca::palette *)NULL;
      
   }
   
   ::ca::font & graphics::GetCurrentFont() const
   {
      
      return *m_spfont.m_p;
      
   }
   
   ::ca::bitmap & graphics::GetCurrentBitmap() const
   {
      
      return *m_bitmap.m_p;
      
   }
   
   bool graphics::PolyBezier(const POINT* lpPoints, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::PolyBezier(get_handle1(), lpPoints, nCount) != FALSE;
      
   }
   
   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);
      
   }
   
   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData,  int32_t nOutputSize, char * lpszOutputData)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //       ASSERT(get_handle1() != NULL);
      //       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
      
   }
   
   /*
    
    bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle2() != NULL);
    //      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;
    
    }
    
    */
   
   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle2() != NULL);
      //      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;
      
   }
   
   bool graphics::AbortPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       if(m_ppath != NULL)
       {
       delete m_ppath;
       m_ppath = NULL;
       }
       return true;
       */
      
   }
   
   bool graphics::BeginPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       if(m_ppath != NULL)
       delete m_ppath;
       
       m_ppath = new Gdiplus::GraphicsPath;
       
       return m_ppath != NULL;
       */
      
   }
   
   bool graphics::CloseFigure()
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       ASSERT(m_ppath != NULL);
       return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
       */
   }
   
   bool graphics::EndPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       if(m_ppath == NULL)
       return FALSE;
       
       m_ppathPaint   = m_ppath;
       m_ppath        = NULL;
       
       return true;
       */
   }
   
   bool graphics::FillPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;
      
   }
   
   bool graphics::FlattenPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      return m_ppath->Flatten() == Gdiplus::Status::Ok;
      
   }
   
   float graphics::GetMiterLimit() const
   {
      
      throw not_implemented(get_app());
      return 0.f;
      
      //      ASSERT(get_handle1() != NULL);
      //      float fMiterLimit;
      //      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //      return fMiterLimit;
      
   }
   
   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);
      
   }
   
   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::SetMiterLimit(get_handle1(), fMiterLimit, NULL) != FALSE;
      
   }
   
   bool graphics::StrokeAndFillPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;
      
      //      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;
      
      //      return bOk1 && bOk2;
      
   }
   
   bool graphics::StrokePath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;
      
   }
   
   bool graphics::WidenPath()
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;
      
   }
   
   
   bool graphics::draw_path(::ca::graphics_path * ppath)
   {
      
      if(!set(ppath))
         return false;
      
      return draw();
      
   }
   
   bool graphics::fill_path(::ca::graphics_path * ppath)
   {
      
      if(!set(ppath))
         return false;
      
      return fill();
      
   }
   
   
   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;
      
   }
   
   
   /*bool CALLBACK metaCallback(
    EmfPlusRecordType recordType,
    uint32_t flags,
    uint32_t dataSize,
    const unsigned char* pStr,
    void* callbackData)
    {
    // Play only EmfPlusRecordTypeFillEllipse records.
    if (recordType == EmfPlusRecordTypeFillEllipse)
    {
    // Explicitly cast callbackData as a metafile pointer, and use it to call
    // the PlayRecord method.
    static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
    }
    return TRUE;
    }
    
    VOID Example_EnumerateMetafile9(HDC hdc)
    {
    Graphics graphics(hdc);
    // Create a Metafile object from an existing disk metafile.
    Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
    {
    // Fill a rectangle and an ellipse in pMeta.
    Graphics metaGraphics(pMeta);
    metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
    metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
    }
    // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
    graphics.EnumerateMetafile(
    pMeta,
    Rect(0, 0, 300, 50),
    metaCallback,
    pMeta);
    // Draw pMeta as an image.
    graphics.DrawImage(pMeta, Point(0, 150));
    delete pMeta;;
    }*/
   
   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, LPCRECT lpBounds)
   {
      
      throw not_implemented(get_app());
      return false;
      
      
      /*      Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));
       
       Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);
       
       //m_pgraphcis->EnumerateMetafile(pMeta, rect, metaCallback, PMETAHEADER);
       
       bool bOk = m_pgraphics->DrawImage(pMeta, rect) == Gdiplus::Status::Ok;
       
       delete pMeta;
       
       return bOk ? TRUE : FALSE;*/
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);
      
   }
   
   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST
   
   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST
   
   // Thank you
   // Jiju George T
   // Web Developer
   // India India
   // Member
   
   bool graphics::alpha_blend(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dRate)
   {
      
      if(m_pdibAlphaBlend != NULL)
      {
         
         throw not_implemented(get_app());
         
         /*
          rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
          
          
          ::ca::dib * pdibWork = NULL;
          ::ca::dib * pdibWork2 = NULL;
          //         ::ca::dib * pdibWork3 = NULL;
          ::ca::dib * pdibWork4 = NULL;
          
          
          class point ptSrc(xSrc, ySrc);
          class point ptDest(xDest, yDest);
          class size size(nDestWidth, nDestHeight);
          
          
          
          ::ca::dib_sp spdib;
          if(pdibWork == NULL)
          {
          spdib.create(get_app());
          pdibWork = spdib;
          }
          if(pdibWork == NULL)
          return false;
          if(!pdibWork->create(size))
          return false;
          if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
          return false;
          
          
          
          
          ::ca::dib_sp spdib2;
          if(pdibWork2 == NULL)
          {
          spdib2.create(get_app());
          pdibWork2 = spdib2;
          }
          
          
          ::ca::dib_sp spdib4;
          if(pdibWork4 == NULL)
          {
          spdib4.create(get_app());
          pdibWork4 = spdib4;
          }
          if(pdibWork4 == NULL)
          return false;
          if(!pdibWork4->create(size))
          return false;
          
          
          pdibWork4->Fill(255, 0, 0, 0);
          
          pdibWork4->from(point(max(0, m_ptAlphaBlend.x - xDest), max(0, m_ptAlphaBlend.y - yDest)),
          m_pdibAlphaBlend->get_graphics(), point(max(0, xDest - m_ptAlphaBlend.x), max(0, yDest - m_ptAlphaBlend.y)), size);
          
          pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);
          
          
          keeper < ::ca::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
          
          
          return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);
          
          */
      }
//      
//      if(pgraphicsSrc == NULL)
//         return false;
//      
//      
//      if(nSrcWidth == 0 || nSrcHeight == 0 || nDstWidth == 0 || nDstHeight == 0)
//         return false;
//      
//      cairo_pattern_t * ppattern = cairo_get_source((cairo_t *) pgraphicsSrc->get_os_data());
//      
//      if(ppattern == NULL)
//         return false;
//      
//      cairo_translate(m_pdc, xDst, yDst);
//      
//      cairo_scale(m_pdc, (double) nDstWidth / (double) nSrcWidth, (double) nDstHeight / (double) nSrcHeight);
//      
//      cairo_set_source(m_pdc, ppattern);
//      
//      cairo_paint_with_alpha(m_pdc, dRate);
//      
//      cairo_scale(m_pdc, (double) nSrcWidth / (double) nDstWidth, (double) nSrcHeight / (double) nDstHeight);
//      
//      cairo_translate(m_pdc, -xDst, -yDst);
      
      return true;
      
   }
   
   
   /*bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
    ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
    {
    
    throw not_implemented(get_app());
    //if(get_handle1() == NULL)
    // return false;
    
    
    if(m_pdibAlphaBlend != NULL)
    {
    
    
    rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
    
    
    ::ca::dib * pdibWork = NULL;
    ::ca::dib * pdibWork2 = NULL;
    //         ::ca::dib * pdibWork3 = NULL;
    ::ca::dib * pdibWork4 = NULL;
    
    
    class point ptSrc(xSrc, ySrc);
    class point ptDest(xDest, yDest);
    class size size(nDestWidth, nDestHeight);
    
    
    
    ::ca::dib_sp spdib;
    if(pdibWork == NULL)
    {
    spdib.create(get_app());
    pdibWork = spdib;
    }
    if(pdibWork == NULL)
    return false;
    if(!pdibWork->create(size))
    return false;
    if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
    return false;
    
    
    
    
    ::ca::dib_sp spdib2;
    if(pdibWork2 == NULL)
    {
    spdib2.create(get_app());
    pdibWork2 = spdib2;
    }
    
    
    ::ca::dib_sp spdib4;
    if(pdibWork4 == NULL)
    {
    spdib4.create(get_app());
    pdibWork4 = spdib4;
    }
    if(pdibWork4 == NULL)
    return false;
    if(!pdibWork4->create(size))
    return false;
    
    
    pdibWork4->Fill(255, 0, 0, 0);
    
    pdibWork4->from(point(max(0, m_ptAlphaBlend.x - xDest), max(0, m_ptAlphaBlend.y - yDest)),
    m_pdibAlphaBlend->get_graphics(), point(max(0, xDest - m_ptAlphaBlend.x), max(0, yDest - m_ptAlphaBlend.y)), size);
    
    pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);
    
    
    keeper < ::ca::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
    
    
    return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);
    
    
    }
    
    return ::AlphaBlend(get_handle1(), xDest, yDest,
    nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
    nSrcHeight, blend) != FALSE;
    }*/
   
   
   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::ca::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != FALSE;
      
   }
   
   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, DWORD dwMode)
   {
      
      throw not_implemented(get_app());
      return false;
      
      //      ASSERT(get_handle1() != NULL);
      //      return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != FALSE;
      
   }
   
   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //
   
   // Always Inline. Functions only in Win98/Win2K or later
   
   /*
    
    COLORREF graphics::GetDCBrushColor() const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetDCBrushColor(get_handle1());
    
    }
    
    COLORREF graphics::SetDCBrushColor(COLORREF crColor)
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::SetDCBrushColor(get_handle1(), crColor);
    
    }
    
    COLORREF graphics::GetDCPenColor() const
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //       ASSERT(get_handle1() != NULL);
    //       return ::GetDCPenColor(get_handle1());
    }
    
    COLORREF graphics::SetDCPenColor(COLORREF crColor)
    {
    
    throw not_implemented(get_app());
    return 0;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::SetDCPenColor(get_handle1(), crColor);
    
    }
    
    bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != FALSE;
    
    }
    
    bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != FALSE;
    
    }
    
    bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ENSURE(lpSize != NULL);
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize) != FALSE;
    
    }
    bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize) const
    {
    
    throw not_implemented(get_app());
    return false;
    
    //      ENSURE(lpSize != NULL);
    //      ASSERT(get_handle1() != NULL);
    //      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, lpSize) != FALSE;
    
    }
    
    
    */
   
   
   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)
   
#define HIMETRIC_INCH   2540    // HIMETRIC units per inch
   
   void graphics::DPtoHIMETRIC(LPSIZE lpSize) const
   {
      
      throw not_implemented(get_app());
      
      /*
       ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
       
       int32_t nMapMode;
       if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
       {
       // when using a constrained ::collection::map mode, ::collection::map against physical inch
       ((::ca::graphics *)this)->SetMapMode(MM_HIMETRIC);
       DPtoLP(lpSize);
       ((::ca::graphics *)this)->SetMapMode(nMapMode);
       }
       else
       {
       // ::collection::map against logical inch for non-constrained mapping modes
       int32_t cxPerInch, cyPerInch;
       if (this != NULL)
       {
       ASSERT_VALID(this);
       ASSERT(get_handle1() != NULL);  // no HDC attached or created?
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
       }
       else
       {
       //            cxPerInch = afxData.cxPixelsPerInch;
       //          cyPerInch = afxData.cyPixelsPerInch;
       }
       ASSERT(cxPerInch != 0 && cyPerInch != 0);
       lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
       lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
       }
       
       */
      
   }
   
   void graphics::HIMETRICtoDP(LPSIZE lpSize) const
   {
      
      throw not_implemented(get_app());
      
      /*      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
       
       int32_t nMapMode;
       if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
       nMapMode != MM_TEXT)
       {
       // when using a constrained ::collection::map mode, ::collection::map against physical inch
       ((::ca::graphics *)this)->SetMapMode(MM_HIMETRIC);
       LPtoDP(lpSize);
       ((::ca::graphics *)this)->SetMapMode(nMapMode);
       }
       else
       {
       // ::collection::map against logical inch for non-constrained mapping modes
       int32_t cxPerInch, cyPerInch;
       if (this != NULL)
       {
       ASSERT_VALID(this);
       ASSERT(get_handle1() != NULL);  // no HDC attached or created?
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
       }
       else
       {
       //            cxPerInch = afxData.cxPixelsPerInch;
       //          cyPerInch = afxData.cyPixelsPerInch;
       }
       ASSERT(cxPerInch != 0 && cyPerInch != 0);
       lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
       lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
       }
       
       */
      
   }
   
   void graphics::LPtoHIMETRIC(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
      
      LPtoDP(lpSize);
      DPtoHIMETRIC(lpSize);
   }
   
   void graphics::HIMETRICtoLP(LPSIZE lpSize) const
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
      
      HIMETRICtoDP(lpSize);
      DPtoLP(lpSize);
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers
   
   ::ca::brush* PASCAL graphics::GetHalftoneBrush(::ca::application * papp)
   {
      /*      ::ca::LockGlobals(CRIT_HALFTONEBRUSH);
       if (gen_HalftoneBrush == NULL)
       {
       WORD grayPattern[8];
       for (int32_t i = 0; i < 8; i++)
       grayPattern[i] = (WORD)(0x5555 << (i & 1));
       HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
       if (grayBitmap != NULL)
       {
       gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
       ::DeleteObject(grayBitmap);
       }
       }
       if (!gen_WingdixTerm)
       gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
       ::ca::UnlockGlobals(CRIT_HALFTONEBRUSH);
       
       //      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return NULL;
   }
   
   void graphics::DrawDragRect(LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, ::ca::brush* pBrush, ::ca::brush* pBrushLast)
   {
      
      throw not_implemented(get_app());
      
      /*
       ASSERT(__is_valid_address(lpRect, sizeof(RECT), FALSE));
       ASSERT(lpRectLast == NULL ||
       __is_valid_address(lpRectLast, sizeof(RECT), FALSE));
       
       // first, determine the update region and select it
       ::ca::region rgnNew;
       ::ca::region rgnOutside, rgnInside;
       rgnOutside.CreateRectRgnIndirect(lpRect);
       rect rect = *lpRect;
       rect.inflate(-size.cx, -size.cy);
       rect.intersect(rect, lpRect);
       rgnInside.CreateRectRgnIndirect(rect);
       rgnNew.CreateRectRgn(0, 0, 0, 0);
       rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);
       
       ::ca::brush* pBrushOld = NULL;
       if (pBrush == NULL)
       {
       pBrush = graphics::GetHalftoneBrush(get_app());
       }
       
       ENSURE(pBrush);
       
       if (pBrushLast == NULL)
       {
       pBrushLast = pBrush;
       }
       
       ::ca::region rgnLast, rgnUpdate;
       if (lpRectLast != NULL)
       {
       // find difference between new region and old region
       rgnLast.CreateRectRgn(0, 0, 0, 0);
       rgnOutside.SetRectRgn(lpRectLast);
       rect = *lpRectLast;
       rect.inflate(-sizeLast.cx, -sizeLast.cy);
       rect.intersect(rect, lpRectLast);
       rgnInside.SetRectRgn(rect);
       rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);
       
       // only diff them if brushes are the same
       if (pBrush->get_os_data() == pBrushLast->get_os_data())
       {
       rgnUpdate.CreateRectRgn(0, 0, 0, 0);
       rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
       }
       }
       if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != NULL)
       {
       // brushes are different -- erase old region first
       SelectClipRgn(&rgnLast);
       GetClipBox(&rect);
       pBrushOld = SelectObject(pBrushLast);
       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
       SelectObject(pBrushOld);
       pBrushOld = NULL;
       }
       
       // draw into the update/new region
       SelectClipRgn(rgnUpdate.get_os_data() != NULL ? &rgnUpdate : &rgnNew);
       GetClipBox(&rect);
       pBrushOld = SelectObject(pBrush);
       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
       
       // cleanup DC
       if (pBrushOld != NULL)
       SelectObject(pBrushOld);
       SelectClipRgn(NULL);
       
       */
      
   }
   
   /*void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
    {
    ::SetBkColor(get_handle1(), clr);
    ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
    }*/
   
   void graphics::FillSolidRect(const __rect64 * lpRect, COLORREF clr)
   {
      rect rect32;
      ::copy(rect32, lpRect);
      FillSolidRect(rect32, clr);
   }
   
   
   /*
    
    void graphics::FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
    {
    ::SetBkColor(get_handle1(), clr);
    rect rect(x, y, x + cx, y + cy);
    ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
    }
    
    */
   
   void graphics::Draw3dRect(LPCRECT lpRect,
                             COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
                 lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
   }
   
   void graphics::Draw3dRect(int32_t x, int32_t y, int32_t cx, int32_t cy,
                             COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
      FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
      FillSolidRect(x + cx - 1, y, 1, cy, clrBottomRight);
      FillSolidRect(x, y + cy - 1, cx, 1, clrBottomRight);
   }
   
   
   
   
   
   //::ca::graphics * PASCAL ::win::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = afxMapHDC(TRUE); //create ::collection::map if not exist
   //ASSERT(pMap != NULL);
   //      ::ca::graphics * pgraphics = (::ca::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == NULL || (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() == hDC);
   //  return pgraphics;
   // return NULL;
   //}
   
   /*
    
    bool graphics::Attach(HDC hdc)
    {
    
    if(hdc == NULL)
    return false;
    
    if(m_hdc == hdc)
    {
    
    if(m_pgraphics != NULL)
    return true;
    
    }
    
    if(hdc != NULL)
    {
    
    m_pgraphics = new ::Gdiplus::Graphics(hdc);
    
    set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
    
    m_hdc = hdc;
    
    }
    
    return m_pgraphics != NULL;
    
    ASSERT(get_handle1() == NULL);      // only attach once, detach on destroy
    ASSERT(get_handle2() == NULL);    // only attach to an is_empty DC
    
    if (hDC == NULL)
    {
    return FALSE;
    }
    // remember early to avoid leak
    set_handle1(hDC);
    hdc_map* pMap = afxMapHDC(TRUE); // create ::collection::map if not exist
    ASSERT(pMap != NULL);
    pMap->set_permanent(get_handle1(), this);
    
    SetAttribDC(get_handle1());     // Default to same as output
    return TRUE;*/
   //   }
   
   /* HDC graphics::Detach()
    {
    
    if(m_hdc == NULL)
    return NULL;
    
    if(m_pgraphics == NULL)
    return NULL;
    
    delete m_pgraphics;
    m_pgraphics = NULL;
    
    HDC hdc = m_hdc;
    m_hdc = NULL;
    
    return hdc;
    
    }
    */
   
   bool graphics::DeleteDC()
   {
//      
//      if(m_pdc == NULL)
//         return true;
//      
//      
//      cairo_destroy(m_pdc);
//      
//      m_pdc = NULL;
      
      return true;
      
   }
   
   
   /*
    
    void graphics::SetAttribDC(HDC hDC)  // Set the Attribute DC
    {
    //      set_handle2(hDC);
    }
    
    void graphics::SetOutputDC(HDC hDC)  // Set the Output DC
    {
    #ifdef DEBUG
          hdc_map* pMap = afxMapHDC();
    if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca::trace::category_AppMsg, 0, "Cannot Set Output hDC on Attached graphics.\n");
    ASSERT(FALSE);
    }*/
   //#endif
   //    set_handle1(hDC);
   //}
   /*
    void graphics::ReleaseAttribDC()     // Release the Attribute DC
    {
    //      set_handle2(NULL);
    }
    
    void graphics::ReleaseOutputDC()     // Release the Output DC
    {
    #ifdef DEBUG
          hdc_map* pMap = afxMapHDC();
    if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca::trace::category_AppMsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
    ASSERT(FALSE);
    }*/
   //#endif
   //set_handle1(NULL);
   //
   
   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines
   
   int32_t graphics::StartDoc(const char * lpszDocName)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       DOCINFO di;
       memset(&di, 0, sizeof(DOCINFO));
       di.cbSize = sizeof(DOCINFO);
       di.lpszDocName = lpszDocName;
       return StartDoc(&di);
       */
      
   }
   
   int32_t graphics::SaveDC()
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = 0;
       if(get_handle2() != NULL)
       nRetVal = ::SaveDC(get_handle2());
       if(get_handle1() != NULL && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
       nRetVal = -1;   // -1 is the only valid restore value for complex DCs
       return nRetVal;
       */
      
   }
   
   bool graphics::RestoreDC(int32_t nSavedDC)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       bool bRetVal = TRUE;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != FALSE;
       if(get_handle2() != NULL)
       bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != FALSE);
       return bRetVal;
       */
      
   }
   
   //   ::ca::graphics_object* PASCAL graphics::SelectGdiObject(::ca::application * papp, HDC hDC, HGDIOBJ h)
   // {
   //      return ::win::graphics_object::from_handle(papp, ::SelectObject(hDC, h));
   //}
   
   ::ca::graphics_object* graphics::SelectStockObject(int32_t nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
       HGDIOBJ hOldObj = NULL;
       ASSERT(hObject != NULL);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), hObject);
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), hObject);
       return ::win::graphics_object::from_handle(get_app(), hOldObj);*/
      
      return NULL;
   }
   
   ::ca::pen* graphics::SelectObject(::ca::pen* pPen)
   {
      /*HGDIOBJ hOldObj = NULL;
       if(pPen == NULL)
       return NULL;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
       return dynamic_cast < pen * > (::win::graphics_object::from_handle(get_app(), hOldObj));*/
      m_penxyz = *pPen;
      return &m_penxyz;
   }
   
   ::ca::brush* graphics::SelectObject(::ca::brush* pBrush)
   {
      /*      HGDIOBJ hOldObj = NULL;
       if(pBrush == NULL)
       return NULL;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), pBrush->get_os_data());
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), pBrush->get_os_data());
       return dynamic_cast < ::ca::brush * > (::win::graphics_object::from_handle(get_app(), hOldObj));*/
      m_brushxyz = *pBrush;
      return &m_brushxyz;
      
   }
   
   ::ca::font* graphics::SelectObject(::ca::font* pfont)
   {
      /*      HGDIOBJ hOldObj = NULL;
       if(pFont == NULL)
       return NULL;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), pFont->get_os_data());
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), pFont->get_os_data());
       return dynamic_cast < ::ca::font * > (::win::graphics_object::from_handle(get_app(), hOldObj));*/
      
      /*ASSERT(pFont != NULL);
       
       if(pFont == NULL)
       return NULL;
       
       m_fontxyz = *pFont;
       return &m_fontxyz;*/
      
      if(!select_font(pfont))
         return NULL;
      
      return &m_fontxyz;
      
   }
   
   int32_t graphics::SelectObject(::ca::region* pRgn)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       int32_t nRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
       if(get_handle2() != NULL)
       nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
       return nRetVal;
       */
      
   }
   
   ::ca::palette* graphics::SelectPalette(::ca::palette* pPalette, bool bForceBackground)
   {
      return NULL;
      //      return dynamic_cast < ::ca::palette * > (::win::graphics_object::from_handle(get_app(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }
   
   COLORREF graphics::SetBkColor(COLORREF crColor)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      
      /*
       COLORREF crRetVal = CLR_INVALID;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       crRetVal = ::SetBkColor(get_handle1(), crColor);
       if(get_handle2() != NULL)
       crRetVal = ::SetBkColor(get_handle2(), crColor);
       return crRetVal;
       */
      
   }
   
   int32_t graphics::SetBkMode(int32_t nBkMode)
   {
      
      return 0;
      
      /*      int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetBkMode(get_handle1(), nBkMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetBkMode(get_handle2(), nBkMode);
       return nRetVal;*/
   }
   
   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::SetROP2(int32_t nDrawMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetROP2(get_handle1(), nDrawMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetROP2(get_handle2(), nDrawMode);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      
      /*
       if(nStretchMode == 0)
       {
       m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
       }
       else if(nStretchMode == HALFTONE)
       {
       m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
       }
       else
       {
       m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
       }
       return 1;
       */
      /*int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
       return nRetVal;*/
   }
   
   COLORREF graphics::SetTextColor(COLORREF crColor)
   {
      return set_color(crColor);
      //COLORREF crRetVal = m_crColor;
      //m_crColor = crColor;
      /*      COLORREF crRetVal = CLR_INVALID;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       crRetVal = ::SetTextColor(get_handle1(), crColor);
       if(get_handle2() != NULL)
       crRetVal = ::SetTextColor(get_handle2(), crColor);*/
      //return crRetVal;
   }
   
   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
       }
       return nRetVal;
       */
      
   }
   
   bool graphics::SetWorldTransform(const XFORM* pXform)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       bool nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::SetWorldTransform(get_handle1(), pXform) != FALSE;
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::SetWorldTransform(get_handle2(), pXform) != FALSE;
       }
       return nRetVal;
       */
      
   }
   
   bool graphics::ModifyWorldTransform(const XFORM* pXform,DWORD iMode)
   {
      
      throw not_implemented(get_app());
      return false;
      
      
      /*
       bool nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != FALSE;
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != FALSE;
       }
       return nRetVal;
       */
      
   }
   
   int32_t graphics::SetMapMode(int32_t nMapMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      
      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetMapMode(get_handle1(), nMapMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetMapMode(get_handle2(), nMapMode);
       return nRetVal;
       */
      
   }
   
   point graphics::GetViewportOrg() const
   {
      //POINT point;
      //::GetViewportOrgEx(get_handle2(), &point);
      
//      double x = 0.0;
//      
//      double y = 0.0;
//      
//      cairo_user_to_device(m_pdc, &x, &y);
      
//      return point((int64_t) x, (int64_t) y);
      return point(0, 0);
      
   }
   
   
   
   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {
      /*point point(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetViewportOrgEx(get_handle1(), x, y, &point);
       if(get_handle2() != NULL)
       ::SetViewportOrgEx(get_handle2(), x, y, &point);*/
//      
//      cairo_matrix_t m;
//      
//      cairo_matrix_translate(&m, x, y);
//      
//      cairo_transform(m_pdc, &m);
      
      //return point;
      return point(x, y);
      
   }
   
   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {
      
      point point = GetViewportOrg();
      
//      cairo_translate(m_pdc, nWidth, nHeight);
      
      return ::point(point.x + nWidth, point.y + nHeight);
      
   }
   
   size graphics::SetViewportExt(int32_t x, int32_t y)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetViewportExtEx(get_handle1(), x, y, &size);
       if(get_handle2() != NULL)
       ::SetViewportExtEx(get_handle2(), x, y, &size);
       return size;
       */
   }
   
   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::ScaleViewportExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
       if(get_handle2() != NULL)
       ::ScaleViewportExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
       return size;
       */
      
   }
   
   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {
      
      throw not_implemented(get_app());
      return ::point(0, 0);
      
      /*
       point point(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetWindowOrgEx(get_handle1(), x, y, &point);
       if(get_handle2() != NULL)
       ::SetWindowOrgEx(get_handle2(), x, y, &point);
       return point;
       */
   }
   
   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {
      
      throw not_implemented(get_app());
      return ::point(0, 0);
      
      /*
       point point(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
       if(get_handle2() != NULL)
       ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
       return point;
       */
      
   }
   
   size graphics::SetWindowExt(int32_t x, int32_t y)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetWindowExtEx(get_handle1(), x, y, &size);
       if(get_handle2() != NULL)
       ::SetWindowExtEx(get_handle2(), x, y, &size);
       return size;
       */
      
   }
   
   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
       if(get_handle2() != NULL)
       ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
       return size;
       */
      
   }
   
   int32_t graphics::GetClipBox(LPRECT lpRect) const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*      return ::GetClipBox(get_handle1(), lpRect);*/
   }
   
   int32_t graphics::SelectClipRgn(::ca::region * pregion)
   {
      
      if(pregion == NULL)
      {
         
//         cairo_reset_clip(m_pdc);
         
      }
      else
      {
         
         *m_spregion.m_p = *pregion;
         
         //cairo_clip(m_pdc);
         
      }
      
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SelectClipRgn(get_handle1(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
       if(get_handle2() != NULL)
       nRetVal = ::SelectClipRgn(get_handle2(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
       return nRetVal;
       */
      
   }
   
   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
       if(get_handle2() != NULL)
       nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::ExcludeClipRect(LPCRECT lpRect)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::ExcludeClipRect(get_handle1(), lpRect->left, lpRect->top,
       lpRect->right, lpRect->bottom);
       if(get_handle2() != NULL)
       nRetVal = ::ExcludeClipRect(get_handle2(), lpRect->left, lpRect->top,
       lpRect->right, lpRect->bottom);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
       if(get_handle2() != NULL)
       nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::IntersectClipRect(LPCRECT lpRect)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*      int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::IntersectClipRect(get_handle1(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
       if(get_handle2() != NULL)
       nRetVal = ::IntersectClipRect(get_handle2(), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
       if(get_handle2() != NULL)
       nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::OffsetClipRgn(SIZE size)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
       if(get_handle2() != NULL)
       nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
       return nRetVal;
       */
   }
   
   /*point graphics::MoveTo(int32_t x, int32_t y)
    {
    point point(0, 0);
    if(get_handle1() != NULL && get_handle1() != get_handle2())
    ::MoveToEx(get_handle1(), x, y, &point);
    if(get_handle2() != NULL)
    ::MoveToEx(get_handle2(), x, y, &point);
    return point;
    }*/
   
   UINT graphics::SetTextAlign(UINT nFlags)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       UINT nRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetTextAlign(get_handle1(), nFlags);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextAlign(get_handle2(), nFlags);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
       return nRetVal;
       */
      
   }
   
   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       int32_t nRetVal = 0x8000000;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
       return nRetVal;
       */
      
   }
   
   DWORD graphics::SetMapperFlags(DWORD dwFlag)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       DWORD dwRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
       if(get_handle2() != NULL)
       dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
       return dwRetVal;
       */
      
   }
   
   //   typedef DWORD (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   //   typedef DWORD (CALLBACK* __GDISETLAYOUTPROC)(HDC, DWORD);
   
   DWORD graphics::GetLayout() const
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != NULL);
       DWORD dwGetLayout = LAYOUT_LTR;
       __GDIGETLAYOUTPROC pfn;
       pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
       // if they API is available, just call it. If it is not
       // available, indicate an error.
       if (pfn != NULL)
       dwGetLayout = (*pfn)(get_handle1());
       else
       {
       dwGetLayout = GDI_ERROR;
       SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
       }
       return dwGetLayout;
       */
      
   }
   
   DWORD graphics::SetLayout(DWORD dwSetLayout)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != NULL);
       DWORD dwGetLayout = LAYOUT_LTR;
       __GDISETLAYOUTPROC pfn;
       pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
       // If the API is availalbe, just call it. If it's not available,
       // setting anything other than LAYOUT_LTR is an error.
       if (pfn != NULL)
       dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
       else if (dwSetLayout != LAYOUT_LTR)
       {
       dwGetLayout = GDI_ERROR;
       SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
       }
       return dwGetLayout;
       */
      
   }
   /*
    void window::ScreenToClient(LPRECT lpRect)
    {
    ASSERT(::IsWindow(get_handle1()));
    ::ScreenToClient(get_handle1(), (LPPOINT)lpRect);
    ::ScreenToClient(get_handle1(), ((LPPOINT)lpRect)+1);
    if (GetExStyle() & WS_EX_LAYOUTRTL)
    rect::swap_left_right(lpRect);
    }
    
    void window::ClientToScreen(LPRECT lpRect)
    {
    ASSERT(::IsWindow(get_handle1()));
    ::ClientToScreen(get_handle1(), (LPPOINT)lpRect);
    ::ClientToScreen(get_handle1(), ((LPPOINT)lpRect)+1);
    if (GetExStyle() & WS_EX_LAYOUTRTL)
    rect::swap_left_right(lpRect);
    }*/
   
   
   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions
   
   bool graphics::ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */
      
   }
   
   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {
      
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       int32_t nResult = 0;
       if (get_handle1() != get_handle2())
       nResult = ::SetArcDirection(get_handle1(), nArcDirection);
       if (get_handle2() != NULL)
       nResult = ::SetArcDirection(get_handle2(), nArcDirection);
       return nResult;
       */
      
   }
   
   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */
      
   }
   
   bool graphics::PolylineTo(const POINT* lpPoints, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return false;
      
      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolylineTo(get_handle1(), lpPoints, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */
      
   }
   
   /*
    bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
    {
    
    throw not_implemented(get_app());
    return false;
    
    
    ASSERT(get_handle1() != NULL);
    bool bResult = FALSE;
    if (get_handle1() != get_handle2())
    bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != FALSE;
    if (get_handle2() != NULL)
    bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
    return bResult;
    */
   
   //   }
   
   bool graphics::PolyBezierTo(const POINT* lpPoints, int32_t nCount)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolyBezierTo(get_handle1(), lpPoints, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */
      
   }
   
   bool graphics::SelectClipPath(int32_t nMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       
       // output DC always holds the current path
       if (!::SelectClipPath(get_handle1(), nMode))
       return FALSE;
       
       // transfer clipping region into the attribute DC
       bool bResult = TRUE;
       if (get_handle1() != get_handle2())
       {
       HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
       if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
       {
       TRACE(::ca::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
       bResult = FALSE;
       }
       ::DeleteObject(hRgn);
       }
       return bResult;
       */
      
   }
   
   int32_t graphics::SelectClipRgn(::ca::region* pRgn, int32_t nMode)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*      ASSERT(get_handle1() != NULL);
       int32_t nRetVal = ERROR;
       if (get_handle1() != get_handle2())
       nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
       if (get_handle2() != NULL)
       nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
       return nRetVal;
       */
      
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
   /*
    int32_t CALLBACK __enum_meta_file_procedure(HDC hDC,
    HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int32_t nHandles, LPARAM lParam)
    {
    ::ca::graphics * pgraphics = (::ca::graphics *)lParam;
    ASSERT_VALID(pgraphics);
    
    switch (pMetaRec->rdFunction)
    {
    // these records have effects different for each graphics derived class
    case META_SETMAPMODE:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetMapMode((int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SETWINDOWEXT:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowExt(
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SETWINDOWORG:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowOrg(
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SETVIEWPORTEXT:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportExt(
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SETVIEWPORTORG:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportOrg(
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SCALEWINDOWEXT:
    (dynamic_cast<::win::graphics * >(pgraphics))->ScaleWindowExt(
    (int32_t)(short)pMetaRec->rdParm[3], (int32_t)(short)pMetaRec->rdParm[2],
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SCALEVIEWPORTEXT:
    (dynamic_cast<::win::graphics * >(pgraphics))->ScaleViewportExt(
    (int32_t)(short)pMetaRec->rdParm[3], (int32_t)(short)pMetaRec->rdParm[2],
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_OFFSETVIEWPORTORG:
    (dynamic_cast<::win::graphics * >(pgraphics))->OffsetViewportOrg(
    (int32_t)(short)pMetaRec->rdParm[1], (int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SAVEDC:
    (dynamic_cast<::win::graphics * >(pgraphics))->SaveDC();
    break;
    case META_RESTOREDC:
    (dynamic_cast<::win::graphics * >(pgraphics))->RestoreDC((int32_t)(short)pMetaRec->rdParm[0]);
    break;
    case META_SETBKCOLOR:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetBkColor(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
    break;
    case META_SETTEXTCOLOR:
    (dynamic_cast<::win::graphics * >(pgraphics))->SetTextColor(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
    break;
    
    // need to watch out for SelectObject(HFONT), for custom font mapping
    case META_SELECTOBJECT:
    {
    HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
    UINT nObjType = GetObjectType(hObject);
    if (nObjType == 0)
    {
    // object type is unknown, determine if it is a font
    HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
    HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hStockFont);
    HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObject);
    if (hObjOld == hStockFont)
    {
    // got the stock object back, so must be selecting a font
    throw not_implemented(::ca::get_thread_app());
    //                  (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
    break;  // don't play the default record
    }
    else
    {
    // didn't get the stock object back, so restore everything
    ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hFontOld);
    ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObjOld);
    }
    // and fall through to PlayMetaFileRecord...
    }
    else if (nObjType == OBJ_FONT)
    {
    // play back as graphics::SelectObject(::ca::font*)
    //               (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
    throw not_implemented(::ca::get_thread_app());
    break;  // don't play the default record
    }
    }
    // fall through...
    
    default:
    ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
    break;
    }
    
    return 1;
    }*/
   
   /*
    
    bool graphics::PlayMetaFile(HMETAFILE hMF)
    {
    
    throw not_implemented(get_app());
    return false;
    
    
    if (::GetDeviceCaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
    {
    // playing metafile in metafile, just use core windows API
    return ::PlayMetaFile(get_handle1(), hMF) != FALSE;
    }
    
    // for special playback, lParam == pgraphics
    return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != FALSE;
    */
   
   //   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms
   
   void graphics::LPtoDP(LPSIZE lpSize) const
   {
      
      throw not_implemented(get_app());
      return;
      
      /*
       ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
       
       size sizeWinExt = GetWindowExt();
       size sizeVpExt = GetViewportExt();
       lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
       lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
       */
      
   }
   
   void graphics::DPtoLP(LPSIZE lpSize) const
   {
      
      throw not_implemented(get_app());
      return;
      
      /*
       ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));
       
       size sizeWinExt = GetWindowExt();
       size sizeVpExt = GetViewportExt();
       lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
       lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
       */
      
   }
   
   
   
   int32_t graphics::draw_text(const char * lpszString, int32_t nCount, LPRECT lpRect, UINT nFormat)
   {
      /*if(get_handle1() == NULL)
       return -1;
       // these flags would modify the string
       ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
       ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
       wstring wstr = ::ca::international::utf8_to_unicode(string(lpszString, nCount));
       return ::DrawTextW(get_handle1(), wstr, (int32_t) wcslen(wstr), lpRect, nFormat); */
      
      return draw_text(string(lpszString, nCount), lpRect, nFormat);
      
   }
   
   int32_t graphics::draw_text(const string & str, LPRECT lpRect, UINT nFormat)
   {
      
      /*if(get_handle1() == NULL)
       return -1;
       // these flags would modify the string
       ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
       ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       return ::DrawTextW(get_handle1(), (const wchar_t *)wstr, (int32_t)wcslen(wstr), lpRect, nFormat); */
      
      /*
       try
       {
       
       if(m_pgraphics == NULL)
       return FALSE;
       
       switch(m_etextrendering)
       {
       case ::ca::text_rendering_anti_alias:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
       break;
       case ::ca::text_rendering_anti_alias_grid_fit:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
       break;
       case ::ca::text_rendering_single_bit_per_pixel:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
       break;
       case ::ca::text_rendering_clear_type_grid_fit:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
       break;
       }
       
       }
       catch(...)
       {
       }
       */
      
      /*
       
       Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());
       
       
       format.SetFormatFlags(format.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);
       
       if(nFormat & DT_LEFT)
       {
       format.SetAlignment(Gdiplus::StringAlignmentNear);
       }
       else if(nFormat & DT_RIGHT)
       {
       format.SetAlignment(Gdiplus::StringAlignmentFar);
       }
       else if(nFormat & DT_CENTER)
       {
       format.SetAlignment(Gdiplus::StringAlignmentCenter);
       }
       else
       {
       format.SetAlignment(Gdiplus::StringAlignmentNear);
       }
       
       if(nFormat & DT_BOTTOM)
       {
       format.SetLineAlignment(Gdiplus::StringAlignmentFar);
       }
       else if(nFormat & DT_TOP)
       {
       format.SetLineAlignment(Gdiplus::StringAlignmentNear);
       }
       else if(nFormat & DT_VCENTER)
       {
       format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
       }
       else
       {
       format.SetLineAlignment(Gdiplus::StringAlignmentNear);
       }
       
       //m_dFontSize             = fontSrc.m_dFontSize;
       
       Gdiplus::Matrix m;
       m_pgraphics->GetTransform(&m);
       
       Gdiplus::Matrix * pmNew = m.Clone();
       
       pmNew->Translate((Gdiplus::REAL) lpRect->left, (Gdiplus::REAL) lpRect->top);
       pmNew->Scale((Gdiplus::REAL) m_fontxyz.m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);
       
       Gdiplus::RectF rectf(0, 0, (Gdiplus::REAL) ((lpRect->right - lpRect->left) * m_fontxyz.m_dFontWidth), (Gdiplus::REAL) (lpRect->bottom - lpRect->top));
       
       m_pgraphics->SetTransform(pmNew);
       
       m_pgraphics->DrawString(::ca::international::utf8_to_unicode(str), -1, gdiplus_font(), rectf, &format, gdiplus_brush());
       
       m_pgraphics->SetTransform(&m);
       
       delete pmNew;*/
//      
//      cairo_translate(m_pdc, lpRect->left, lpRect->top);
//      
//      cairo_scale(m_pdc, m_fontxyz.m_dFontWidth, 1.0);
//      
//      set(m_spfont);
//      
//      cairo_show_text(m_pdc, str);
//      
//      cairo_scale(m_pdc, 1.0 / m_fontxyz.m_dFontWidth, 1.0);
//      
//      cairo_translate(m_pdc, -lpRect->left, -lpRect->top);
//      
      
      return 1;
      
   }
   
   int32_t graphics::draw_text_ex(LPTSTR lpszString, int32_t nCount, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      
      throw not_implemented(get_app());
      return 0 ;
      
      /*
       if(get_handle1() == NULL)
       return -1;
       // these flags would modify the string
       ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
       ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
       wstring wstr = ::ca::international::utf8_to_unicode(string(lpszString, nCount));
       return ::DrawTextExW(get_handle1(), const_cast<wchar_t *>((const wchar_t *)wstr), (int32_t)wcslen(wstr), lpRect, nFormat, lpDTParams);
       */
   }
   
   int32_t graphics::draw_text_ex(const string & str, LPRECT lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      
      throw not_implemented(get_app());
      return 0;
      
      /*
       ASSERT(get_handle1() != NULL);
       // these flags would modify the string
       ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
       ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       return ::DrawTextExW(get_handle1(), const_cast<wchar_t *>((const wchar_t *)wstr), (int32_t)wcslen(wstr), lpRect, nFormat, lpDTParams);
       */
      
   }
   
   size graphics::GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex) const
   {
      
      
      string str(&lpszString[iIndex], nCount);
      
      
      ((graphics *) this)->set(m_spfont);
      
//      cairo_text_extents_t ex;
//      
//      cairo_text_extents(m_pdc, str, &ex);
//      
//      SIZE size;
//      
//      size.cx = ex.width;
//      
//      size.cy = ex.height;
      
      SIZE size;
      size.cx = 0;
      size.cy = 0;
      
      return size;
      
      
      /*      if(lpszString == NULL || *lpszString == '\0')
       return size(0, 0);
       
       if(nCount < 0)
       nCount = strlen(lpszString);
       
       if(iIndex > nCount)
       return size(0, 0);
       
       if(iIndex < 0)
       return size(0, 0);
       
       wstring wstr = ::ca::international::utf8_to_unicode(lpszString, nCount);
       
       strsize iRange = 0;
       strsize i = 0;
       strsize iLen;
       const char * psz = lpszString;
       while(i < iIndex)
       {
       iLen = ::ca::str::utf8_char(psz).length();
       iRange++;
       i += iLen;
       psz = ::ca::str::utf8_inc(psz);
       if(psz == NULL)
       break;
       if(*psz == '\0')
       break;
       }
       
       Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT) iRange) };
       
       Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
       //Gdiplus::StringFormat strFormat;
       
       strFormat.SetMeasurableCharacterRanges(1, charRanges);
       
       strFormat.SetFormatFlags(strFormat.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);
       
       int32_t count = strFormat.GetMeasurableCharacterRangeCount();
       
       Gdiplus::Region * pCharRangeRegions = new Gdiplus::Region[count];
       
       Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);
       
       Gdiplus::PointF origin(0, 0);
       
       //m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), ((graphics *)this)->gdiplus_font(), origin, Gdiplus::StringFormat::GenericTypographic(), &box);
       
       ((graphics *)this)->m_pgraphics->MeasureCharacterRanges(wstr, (INT) wstr.get_length(), ((graphics *)this)->gdiplus_font(), box, &strFormat, (INT) count, pCharRangeRegions);
       
       Gdiplus::Region * pregion = NULL;
       
       
       if(count > 0)
       {
       
       pregion = pCharRangeRegions[0].Clone();
       
       }
       
       
       
       for(i = 1; i < count; i++)
       {
       pregion->Union(&pCharRangeRegions[i]);
       }
       
       
       if(pregion == NULL)
       return size(0, 0);
       
       delete [] pCharRangeRegions;
       
       
       Gdiplus::RectF rectBound;
       
       pregion->GetBounds(&rectBound, m_pgraphics);
       
       delete pregion;
       
       
       
       Gdiplus::SizeF size;
       
       rectBound.GetSize(&size);
       
       return class ::size((int64_t) (size.Width * m_fontxyz.m_dFontWidth), (int64_t) (size.Height));
       */
   }
   
   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {
      
      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));
      
      string str(lpszString, nCount);
      
      
      ((graphics *) this)->set(m_spfont);
      
//      cairo_text_extents_t ex;
//      
//      cairo_text_extents(m_pdc, str, &ex);
//      
//      SIZE size;
//      
//      size.cx = ex.width;
//      
//      size.cy = ex.height;
      
      SIZE size;
      size.cx = 0;
      size.cy = 0;

      
      return size;
      
      /*wstring wstr = ::ca::international::utf8_to_unicode(lpszString, nCount);
       
       Gdiplus::RectF box;
       
       Gdiplus::PointF origin(0, 0);
       
       Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
       
       strFormat.SetFormatFlags(strFormat.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);
       
       m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), ((graphics *)this)->gdiplus_font(), origin, &strFormat,  &box);
       
       return size((int64_t) (box.Width * m_fontxyz.m_dFontWidth), (int64_t) (box.Height));*/
      
      /*if(get_handle2() == NULL)
       return size(0, 0);
       SIZE size;
       string str(lpszString, nCount);
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       if(!::GetTextExtentPoint32W(get_handle2(), wstr, (int32_t)wstr.get_length(), &size))
       {
       return class size(0, 0);
       }
       return size;*/
   }
   
   size graphics::GetTextExtent(const string & str) const
   {
      /*      if(get_handle2() == NULL)
       return size(0, 0);
       SIZE size;
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       if(!::GetTextExtentPoint32W(get_handle2(), wstr, (int32_t)wstr.get_length(), &size))
       {
       return class size(0, 0);
       }
       return size;*/
      
      class sized size;
      
      if(!GetTextExtent(size, str, str.get_length(), (int32_t) str.get_length()))
         return ::size(0, 0);
      
      return ::size((long) size.cx, (long) size.cy);
      
      /*if(m_pgraphics == NULL)
       return size(0, 0);
       
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       
       Gdiplus::RectF box;
       
       Gdiplus::PointF origin(0, 0);
       
       
       if(m_pgraphics == NULL)
       return size(0, 0);
       
       try
       {
       m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), ((graphics *)this)->gdiplus_font(), origin, &box);
       }
       catch(...)
       {
       return size(0, 0);
       }
       
       return size((int64_t) (box.Width * m_fontxyz.m_dFontWidth), (int64_t) box.Height);*/
      
   }
   
   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       ASSERT(get_handle1() != NULL);
       SIZE size;
       string str(lpszString, nCount);
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size));
       return size;
       */
      
   }
   
   size graphics::GetOutputTextExtent(const string & str) const
   {
      
      throw not_implemented(get_app());
      return ::size(0, 0);
      
      /*
       ASSERT(get_handle1() != NULL);
       SIZE size;
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (int32_t)wstr.get_length(), &size));
       return size;
       */
   }
   
   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) const
   {
      
      string str(&lpszString[iIndex], nCount);
      
      ((graphics *) this)->set(&m_fontxyz);
      
//      cairo_text_extents_t ex;
//      
//      cairo_text_extents(m_pdc, str, &ex);
//      
//      size.cx = ex.width;
//      
//      size.cy = ex.height;
      
      return size;
      
      
      
      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));
      
      /*      if(lpszString == NULL || *lpszString == '\0')
       return false;
       
       if(nCount < 0)
       nCount = strlen(lpszString);
       
       if(iIndex > nCount)
       return false;
       
       if(iIndex < 0)
       return false;
       
       wstring wstr = ::ca::international::utf8_to_unicode(lpszString, nCount);
       
       strsize iRange = 0;
       strsize i = 0;
       strsize iLen;
       const char * psz = lpszString;
       while(i < iIndex)
       {
       try
       {
       iLen = ::ca::str::utf8_char(psz).length();
       }
       catch(...)
       {
       break;
       }
       iRange++;
       i += iLen;
       try
       {
       psz = ::ca::str::utf8_inc(psz);
       }
       catch(...)
       {
       break;
       }
       if(psz == NULL)
       break;
       if(*psz == '\0')
       break;
       }
       
       Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT) iRange) };
       
       Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
       //Gdiplus::StringFormat strFormat;
       
       strFormat.SetMeasurableCharacterRanges(1, charRanges);
       
       strFormat.SetFormatFlags(strFormat.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);
       
       int32_t count = strFormat.GetMeasurableCharacterRangeCount();
       
       Gdiplus::Region * pCharRangeRegions = new Gdiplus::Region[count];
       
       //Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);
       
       Gdiplus::PointF origin(0, 0);
       
       
       // Generate a layout rect for the text
       
       Gdiplus::RectF layoutRect;
       Gdiplus::Status status = ((graphics *)this)->m_pgraphics->MeasureString( wstr, (INT) nCount, ((graphics *)this)->gdiplus_font(), origin, &layoutRect );
       
       
       // Prevent clipping
       
       //StringFormat strFormat( StringFormat::GenericTypographic() );
       //status = ((graphics *)this)->m_pgraphics->SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsNoClip );
       
       
       
       //m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), ((graphics *)this)->gdiplus_font(), origin, Gdiplus::StringFormat::GenericTypographic(), &box);
       
       ((graphics *)this)->m_pgraphics->MeasureCharacterRanges(wstr, (INT) nCount, ((graphics *)this)->gdiplus_font(), layoutRect, &strFormat, (INT) count, pCharRangeRegions);
       
       Gdiplus::Region * pregion = NULL;
       
       
       if(count > 0)
       {
       
       pregion = pCharRangeRegions[0].Clone();
       
       }
       
       for(i = 1; i < count; i++)
       {
       pregion->Union(&pCharRangeRegions[i]);
       }
       
       delete [] pCharRangeRegions;
       
       if(pregion == NULL)
       return false;
       
       Gdiplus::RectF rectBound;
       
       pregion->GetBounds(&rectBound, m_pgraphics);
       
       delete pregion;
       
       Gdiplus::SizeF sizef;
       
       rectBound.GetSize(&sizef);
       
       size.cx = sizef.Width * m_fontxyz.m_dFontWidth;
       
       size.cy = sizef.Height;
       
       return true;*/
   }
   
   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {
      
      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));
      
      
      string str(lpszString, nCount);
      
      
      ((graphics *) this)->set(m_spfont);
//      
//      cairo_text_extents_t ex;
//      
//      cairo_text_extents(m_pdc, str, &ex);
//      
//      size.cx = ex.width;
//      
//      size.cy = ex.height;
//      
      return size;
      
      
      /*      wstring wstr = ::ca::international::utf8_to_unicode(lpszString, nCount);
       
       Gdiplus::RectF box;
       
       Gdiplus::PointF origin(0, 0);
       
       Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
       
       strFormat.SetFormatFlags(strFormat.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap);
       bool bOk = true;
       
       try
       {
       if(m_pgraphics->MeasureString(wstr, (int32_t) wstr.get_length(), ((graphics *)this)->gdiplus_font(), origin, &strFormat,  &box) != Gdiplus::Status::Ok)
       bOk = false;
       }
       catch(...)
       {
       bOk = false;
       }
       
       if(!bOk)
       return false;
       
       size.cx = box.Width * m_fontxyz.m_dFontWidth;
       
       size.cy = box.Height;
       
       return true;
       */
   }
   
   bool graphics::GetTextExtent(sized & size, const string & str) const
   {
      
      return GetTextExtent(size, str, str.get_length());
      
   }
   
   
   
   /*
    
    /////////////////////////////////////////////////////////////////////////////
    // Helper DCs
    
    
    void CClientDC::assert_valid() const
    {
    graphics::assert_valid();
    ASSERT(m_hWnd == NULL || ::IsWindow(m_hWnd));
    }
    
    void CClientDC::dump(dump_context & dumpcontext) const
    {
    graphics::dump(dumpcontext);
    
    dumpcontext << "get_handle1() = " << m_hWnd;
    dumpcontext << "\n";
    }
    
    
    CClientDC::CClientDC(window * pWnd)
    {
    ASSERT(pWnd == NULL || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));
    
    if (!Attach(::GetDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
    throw resource_exception();
    }
    
    CClientDC::~CClientDC()
    {
    ASSERT(get_handle1() != NULL);
    ::ReleaseDC(m_hWnd, Detach());
    }
    
    
    void CWindowDC::assert_valid() const
    {
    graphics::assert_valid();
    ASSERT(m_hWnd == NULL || ::IsWindow(m_hWnd));
    }
    
    void CWindowDC::dump(dump_context & dumpcontext) const
    {
    graphics::dump(dumpcontext);
    
    dumpcontext << "get_handle1() = " << m_hWnd;
    dumpcontext << "\n";
    }
    
    
    CWindowDC::CWindowDC(window * pWnd)
    {
    ASSERT(pWnd == NULL || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));
    
    if (!Attach(::GetWindowDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
    throw resource_exception();
    }
    
    CWindowDC::~CWindowDC()
    {
    ASSERT(get_handle1() != NULL);
    ::ReleaseDC(m_hWnd, Detach());
    }
    
    
    void CPaintDC::assert_valid() const
    {
    graphics::assert_valid();
    ASSERT(::IsWindow(m_hWnd));
    }
    
    void CPaintDC::dump(dump_context & dumpcontext) const
    {
    graphics::dump(dumpcontext);
    
    dumpcontext << "get_handle1() = " << m_hWnd;
    dumpcontext << "\nm_ps.hdc = " << m_ps.hdc;
    dumpcontext << "\nm_ps.fErase = " << m_ps.fErase;
    dumpcontext << "\nm_ps.rcPaint = " << (rect)m_ps.rcPaint;
    
    dumpcontext << "\n";
    }
    
    
    CPaintDC::CPaintDC(window * pWnd)
    {
    ASSERT_VALID(pWnd);
    ASSERT(::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));
    
    if (!Attach(::BeginPaint(m_hWnd = WIN_WINDOW(pWnd)->get_handle1(), &m_ps)))
    throw resource_exception();
    }
    
    CPaintDC::~CPaintDC()
    {
    ASSERT(get_handle1() != NULL);
    ASSERT(::IsWindow(m_hWnd));
    
    ::EndPaint(m_hWnd, &m_ps);
    Detach();
    }
    
    */
   
   
   
   
   
   
   
   // IMPLEMENT_DYNAMIC(resource_exception, base_exception)
   //resource_exception _simpleResourceException(FALSE, __IDS_RESOURCE_EXCEPTION);
   
   // IMPLEMENT_DYNAMIC(user_exception, base_exception)
   //user_exception _simpleUserException(FALSE, __IDS_USER_EXCEPTION);
   
   // IMPLEMENT_DYNCREATE(graphics, ::ca::object)
   // IMPLEMENT_DYNAMIC(CClientDC, graphics)
   // IMPLEMENT_DYNAMIC(CWindowDC, graphics)
   // IMPLEMENT_DYNAMIC(CPaintDC, graphics)
   // IMPLEMENT_DYNCREATE(::ca::graphics_object, ::ca::object)
   
   // IMPLEMENT_DYNAMIC(pen, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::brush, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::font, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::bitmap, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::palette, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::region, ::ca::graphics_object)
   
   
   void graphics::FillSolidRect(LPCRECT lpRect, COLORREF clr)
   {
      
      //g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
      //g().SetCompositingMode(Gdiplus::CompositingModeSourceOver);
      //g().SetCompositingQuality(Gdiplus::CompositingQualityGammaCorrected);
      
      set_color(clr);
      
//      cairo_rectangle(m_pdc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
//      
//      cairo_fill(m_pdc);
//      
      //      m_pgraphics->FillRectangle(gdiplus_brush(), lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
      
      //::SetBkColor(get_handle1(), clr);
      //::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
   }
   
   void graphics::FillSolidRect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
   {
      //g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
      //g().SetCompositingMode(Gdiplus::CompositingModeSourceOver);
      //g().SetCompositingQuality(Gdiplus::CompositingQualityGammaCorrected);
      
      
      set_color(clr);
      
//      cairo_rectangle(m_pdc, x, y, cx, cy);
      
//      cairo_fill(m_pdc);
      
   }
   
   
   bool graphics::TextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount)
   {
      string str(lpszString, nCount);
      
      
      ((graphics *) this)->set(m_spfont);
//      
//      cairo_move_to(m_pdc, x, y);
//      
//      cairo_show_text(m_pdc, str);
      
      /*::Gdiplus::PointF origin(0, 0);
       
       string str(lpszString, nCount);
       
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       
       
       try
       {
       
       if(m_pgraphics == NULL)
       return FALSE;
       
       switch(m_etextrendering)
       {
       case ::ca::text_rendering_anti_alias:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
       break;
       case ::ca::text_rendering_anti_alias_grid_fit:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
       break;
       case ::ca::text_rendering_single_bit_per_pixel:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
       break;
       case ::ca::text_rendering_clear_type_grid_fit:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
       break;
       }
       
       }
       catch(...)
       {
       }
       
       
       //
       //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
       
       Gdiplus::Matrix m;
       m_pgraphics->GetTransform(&m);
       
       Gdiplus::Matrix * pmNew;
       
       if(m_ppath != NULL)
       {
       pmNew = new Gdiplus::Matrix();
       }
       else
       {
       pmNew = m.Clone();
       }
       
       pmNew->Translate((Gdiplus::REAL)  (x / m_fontxyz.m_dFontWidth), (Gdiplus::REAL) y);
       pmNew->Scale((Gdiplus::REAL) m_fontxyz.m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);
       
       Gdiplus::Status status;
       
       Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());
       
       format.SetFormatFlags(format.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap
       | Gdiplus::StringFormatFlagsNoFitBlackBox);
       
       
       format.SetLineAlignment(Gdiplus::StringAlignmentNear);
       
       if(m_ppath != NULL)
       {
       
       Gdiplus::GraphicsPath path;
       
       Gdiplus::FontFamily fontfamily;
       
       gdiplus_font()->GetFamily(&fontfamily);
       
       double d1 = gdiplus_font()->GetSize() * m_pgraphics->GetDpiX() / 72.0;
       double d2 = fontfamily.GetEmHeight(gdiplus_font()->GetStyle());
       double d3 = d1 * d2;
       
       status = path.AddString(::ca::international::utf8_to_unicode(str), -1, &fontfamily, gdiplus_font()->GetStyle(), (Gdiplus::REAL) d1, origin, &format);
       
       path.Transform(pmNew);
       
       
       m_ppath->AddPath(&path, FALSE);
       
       }
       else
       {
       
       m_pgraphics->SetTransform(pmNew);
       
       status = m_pgraphics->DrawString(::ca::international::utf8_to_unicode(str), -1, gdiplus_font(), origin, &format, gdiplus_brush());
       
       m_pgraphics->SetTransform(&m);
       
       }
       
       delete pmNew;
       
       return status  == Gdiplus::Status::Ok;
       */
      return true;
   }
   
   bool graphics::TextOut(double x, double y, const char * lpszString, int32_t nCount)
   {
      
      string str(lpszString, nCount);
      
      
      ((graphics *) this)->set(m_spfont);
      
//      cairo_move_to(m_pdc, x, y);
//      
//      cairo_show_text(m_pdc, str);
      
      return true;
      
      /*
       
       ::Gdiplus::PointF origin(0, 0);
       
       string str(lpszString, nCount);
       
       wstring wstr = ::ca::international::utf8_to_unicode(str);
       
       
       try
       {
       
       if(m_pgraphics == NULL)
       return FALSE;
       
       switch(m_etextrendering)
       {
       case ::ca::text_rendering_anti_alias:
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
       break;
       case ::ca::text_rendering_anti_alias_grid_fit:
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
       break;
       case ::ca::text_rendering_single_bit_per_pixel:
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
       break;
       case ::ca::text_rendering_clear_type_grid_fit:
       m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
       break;
       }
       
       }
       catch(...)
       {
       }
       
       
       //
       //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
       //m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
       
       Gdiplus::Matrix m;
       m_pgraphics->GetTransform(&m);
       
       Gdiplus::Matrix * pmNew;
       
       if(m_ppath != NULL)
       {
       pmNew = new Gdiplus::Matrix();
       }
       else
       {
       pmNew = m.Clone();
       }
       
       pmNew->Translate((Gdiplus::REAL)  (x / m_fontxyz.m_dFontWidth), (Gdiplus::REAL) y);
       pmNew->Scale((Gdiplus::REAL) m_fontxyz.m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);
       
       Gdiplus::Status status;
       
       Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());
       
       format.SetFormatFlags(format.GetFormatFlags()
       | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
       | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap
       | Gdiplus::StringFormatFlagsNoFitBlackBox);
       
       
       format.SetLineAlignment(Gdiplus::StringAlignmentNear);
       
       if(m_ppath != NULL)
       {
       
       Gdiplus::GraphicsPath path;
       
       Gdiplus::FontFamily fontfamily;
       
       gdiplus_font()->GetFamily(&fontfamily);
       
       double d1 = gdiplus_font()->GetSize() * m_pgraphics->GetDpiX() / 72.0;
       double d2 = fontfamily.GetEmHeight(gdiplus_font()->GetStyle());
       double d3 = d1 * d2;
       
       status = path.AddString(::ca::international::utf8_to_unicode(str), -1, &fontfamily, gdiplus_font()->GetStyle(), (Gdiplus::REAL) d1, origin, &format);
       
       path.Transform(pmNew);
       
       
       m_ppath->AddPath(&path, FALSE);
       
       }
       else
       {
       
       m_pgraphics->SetTransform(pmNew);
       
       status = m_pgraphics->DrawString(::ca::international::utf8_to_unicode(str), -1, gdiplus_font(), origin, &format, gdiplus_brush());
       
       m_pgraphics->SetTransform(&m);
       
       }
       
       delete pmNew;
       
       return status  == Gdiplus::Status::Ok;
       */
   }
   
   
   
   bool graphics::LineTo(double x, double y)
   {
      
      //      ::Gdiplus::Pen pen(::Gdiplus::Color(GetAValue(m_crColor), GetRValue(m_crColor), GetGValue(m_crColor), GetBValue(m_crColor)), m_dPenWidth);
      
      //gdiplus_pen()->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);
      
      //m_pgraphics->DrawLine(gdiplus_pen(), Gdiplus::Point((FLOAT) m_x, (FLOAT) m_y), Gdiplus::Point((FLOAT) x,(FLOAT) y));
      //string str(lpszString, nCount);
      
      
      
      
//      cairo_line_to(m_pdc, x, y);
      
      draw();
      
      
      m_x = x;
      m_y = y;
      
      return TRUE;
      
   }
   
   
   void graphics::set_alpha_mode(::ca::e_alpha_mode ealphamode)
   {
      
      try
      {
         
//         if(m_pdc == NULL)
//            return;
         
         ::ca::graphics::set_alpha_mode(ealphamode);
         if(m_ealphamode == ::ca::alpha_mode_blend)
         {
//            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
         }
         else if(m_ealphamode == ::ca::alpha_mode_set)
         {
//            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
         }
         
      }
      catch(...)
      {
         return;
      }
      
   }
   
   
   void graphics::set_text_rendering(::ca::e_text_rendering etextrendering)
   {
      m_etextrendering = etextrendering;
      
   }
   
   
   void * graphics::get_os_data() const
   {
      
//      return (void *) m_pdc;
      return NULL;
      
   }
   
   
   /*   HDC graphics::get_handle() const
    {
    return m_hdc;
    }
    
    HDC graphics::get_handle1() const
    {
    return get_handle();
    }
    
    HDC graphics::get_handle2() const
    {
    return get_handle();
    }*/
   
   bool graphics::attach(void * pdata)
   {
      
//      if(m_pdc != NULL)
//      {
//         
//         cairo_destroy(m_pdc);
//         
//      }
//      
//      m_pdc = (cairo_t *) pdata;
      
      return true;
      
   }
   
   /*
    Gdiplus::Font * graphics::gdiplus_font()
    {
    if(m_spfont.is_null())
    {
    m_spfont.create(get_app());
    m_spfont->operator=(m_fontxyz);
    }
    else if(!m_fontxyz.m_bUpdated)
    {
    m_fontxyz.m_bUpdated = true;
    m_spfont->operator=(m_fontxyz);
    }
    return (Gdiplus::Font *) m_spfont->get_os_data();
    }
    
    Gdiplus::Brush * graphics::gdiplus_brush()
    {
    if(m_spbrush.is_null())
    {
    m_spbrush.create(get_app());
    m_spbrush->operator=(m_brushxyz);
    }
    else if(!m_brushxyz.m_bUpdated)
    {
    m_brushxyz.m_bUpdated = true;
    m_spbrush->operator=(m_brushxyz);
    }
    return (Gdiplus::Brush *) m_spbrush->get_os_data();
    }
    
    Gdiplus::Pen * graphics::gdiplus_pen()
    {
    if(m_sppen.is_null())
    {
    m_sppen.create(get_app());
    m_sppen->operator=(m_penxyz);
    }
    else if(!m_penxyz.m_bUpdated)
    {
    m_penxyz.m_bUpdated = true;
    m_sppen->operator=(m_penxyz);
    }
    return (Gdiplus::Pen *) m_sppen->get_os_data();
    }*/
   
   
   //   ::ca::e_fill_mode graphics::gdiplus_get_fill_mode()
   // {
   //      return ::ca::fill_mode_winding;
   // }
   
//   void cairo_image_surface_blur( cairo_surface_t* surface, double radius )
//   {
//      // Steve Hanov, 2009
//      // Released into the public domain.
//      
//      // get width, height
//      int32_t width = cairo_image_surface_get_width( surface );
//      int32_t height = cairo_image_surface_get_height( surface );
//      unsigned char* dst = (unsigned char*)malloc(width*height*4);
//      unsigned* precalc =
//      (unsigned*)malloc(width*height*sizeof(unsigned));
//      unsigned char* src = cairo_image_surface_get_data( surface );
//      double mul=1.f/((radius*2)*(radius*2));
//      int32_t channel;
//      
//      // The number of times to perform the averaging. According to wikipedia,
//      // three iterations is good enough to pass for a gaussian.
//      const int32_t MAX_ITERATIONS = 3;
//      int32_t iteration;
//      
//      memcpy( dst, src, width*height*4 );
//      
//      for ( iteration = 0; iteration < MAX_ITERATIONS; iteration++ ) {
//         for( channel = 0; channel < 4; channel++ ) {
//            int32_t x,y;
//            
//            // precomputation step.
//            unsigned char* pix = src;
//            unsigned* pre = precalc;
//            
//            pix += channel;
//            for (y=0;y<height;y++) {
//               for (x=0;x<width;x++) {
//                  int32_t tot=pix[0];
//                  if (x>0) tot+=pre[-1];
//                  if (y>0) tot+=pre[-width];
//                  if (x>0 && y>0) tot-=pre[-width-1];
//                  *pre++=tot;
//                  pix += 4;
//               }
//            }
//            
//            // blur step.
//            pix = dst + (int32_t)radius * width * 4 + (int32_t)radius * 4 + channel;
//            for (y=radius;y<height-radius;y++) {
//               for (x=radius;x<width-radius;x++) {
//                  int32_t l = x < radius ? 0 : x - radius;
//                  int32_t t = y < radius ? 0 : y - radius;
//                  int32_t r = x + radius >= width ? width - 1 : x + radius;
//                  int32_t b = y + radius >= height ? height - 1 : y + radius;
//                  int32_t tot = precalc[r+b*width] + precalc[l+t*width] -
//                  precalc[l+b*width] - precalc[r+t*width];
//                  *pix=(unsigned char)(tot*mul);
//                  pix += 4;
//               }
//               pix += (int32_t)radius * 2 * 4;
//            }
//         }
//         memcpy( src, dst, width*height*4 );
//      }
//      
//      free( dst );
//      free( precalc );
//   }
   
   
   bool graphics::blur(bool bExpand, double dRadius, LPCRECT lpcrect)
   {
      
//      cairo_pattern_t * ppattern = cairo_get_source(m_pdc);
//      
//      if(ppattern == NULL)
//         return false;
//      
//      cairo_surface_t * psurfaceSrc = NULL;
//      
//      cairo_pattern_get_surface(ppattern, &psurfaceSrc);
//      
//      cairo_surface_t * psurface = cairo_surface_create_for_rectangle(psurfaceSrc, lpcrect->left, lpcrect->top, width(lpcrect), height(lpcrect));
//      
//      cairo_image_surface_blur(psurface, dRadius);
      
      return true;
      
   }
   
   
   double graphics::get_dpix() const
   {
      
      //      return m_pgraphics->GetDpiX();
      return 72.0;
      
   }
   
   
   bool graphics::set(const ::ca::brush * pbrush)
   {
      
//      cairo_set_source_rgba(m_pdc, GetRValue(pbrush->m_cr) / 255.0, GetGValue(pbrush->m_cr) / 255.0, GetBValue(pbrush->m_cr) / 255.0, GetAValue(pbrush->m_cr) / 255.0);
      return true;
      
   }
   
   
   bool graphics::set(const ::ca::pen * ppen)
   {
      
//      cairo_set_source_rgba(m_pdc, GetRValue(ppen->m_cr) / 255.0, GetGValue(ppen->m_cr) / 255.0, GetBValue(ppen->m_cr) / 255.0, GetAValue(ppen->m_cr) / 255.0);
//      
//      cairo_set_line_width(m_pdc, ppen->m_dWidth);
      return true;
   }
   
   bool graphics::set(const ::ca::font * pfont)
   {
      
//      cairo_select_font_face(m_pdc, pfont->m_strFontFamilyName, pfont->m_bItalic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL, pfont->m_iFontWeight > 650 ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
//      
//      if(pfont->m_eunitFontSize == ::ca::unit_pixel)
//      {
//         
//         cairo_set_font_size(m_pdc, pfont->m_dFontSize);
//         
//      }
//      else
//      {
//         
//         cairo_set_font_size(m_pdc, pfont->m_dFontSize * 96.0 / 72.0);
//         
//      }
//      
      
          return true;
   }
   
   bool graphics::fill_and_draw()
   {
      
//      bool bPen = m_sppen.is_set() && (m_sppen->m_etype != ::ca::pen::type_null);
//      
//      if(m_spbrush.is_set() && (m_spbrush->m_etype != ::ca::brush::type_null))
//      {
//         
//         set(m_spbrush);
//         
//         if(bPen)
//         {
//            
//            cairo_fill_preserve(m_pdc);
//            
//         }
//         else
//         {
//            
//            cairo_fill(m_pdc);
//            
//         }
//         
//      }
//      
//      if(bPen)
//      {
//         
//         set(m_sppen);
//         
//         cairo_stroke(m_pdc);
//         
//         
//      }
      
      
      return true;
      
   }
   
   
   bool graphics::fill(::ca::brush * pbrush)
   {
      
//      if(pbrush == NULL || pbrush->m_etype == ::ca::brush::type_null)
//         return true;
//      
//      set(pbrush);
//      
//      cairo_fill(m_pdc);
//
      
            return true;
   }
   
   bool graphics::draw(::ca::pen * ppen)
   {
//      
//      if(ppen == NULL || ppen->m_etype == ::ca::pen::type_null)
//         return true;
//      
//      set(ppen);
//      
//      cairo_stroke(m_pdc);
//      
            return true;
      
   }
   
   
   bool graphics::set(const ::ca::graphics_path * ppathParam)
   {
      
//      ::lnx::graphics_path * ppath = dynamic_cast < ::lnx::graphics_path * > ((::ca::graphics_path *) ppathParam);
//      
//      for(int32_t i = 0; i < ppath->m_elementa.get_count(); i++)
//      {
//         
//         set(ppath->m_elementa[i]);
//         
//      }
//      
//      if(ppath->m_efillmode == ::ca::fill_mode_alternate)
//      {
//         
//         cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);
//         
//      }
//      else
//      {
//         
//         cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);
//         
//      }
      
      
      return true;
      
   }
   
   
   bool graphics::set(const ::mac::graphics_path::element & e)
   {
      
      switch(e.m_etype)
      {
         case ::ca::graphics_path::element::type_arc:
            set(e.m_arc);
            break;
         case ::ca::graphics_path::element::type_line:
            set(e.m_line);
            break;
         case ::ca::graphics_path::element::type_end:
//            cairo_close_path(m_pdc);
            break;
         default:
            throw "unexpected simple os graphics element type";
      }
      
      return false;
      
   }
   
   bool graphics::set(const ::mac::graphics_path::arc & a)
   {
      
//      cairo_translate(m_pdc, a.m_xCenter, a.m_yCenter);
//      
//      cairo_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);
//      
//      cairo_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);
//      
//      cairo_scale(m_pdc, 1.0, a.m_dRadiusX / a.m_dRadiusY);
//      
//      cairo_translate(m_pdc, -a.m_xCenter, -a.m_yCenter);
      
      return true;
      
   }
   
   bool graphics::set(const ::mac::graphics_path::line & l)
   {
      
//      if(!cairo_has_current_point(m_pdc))
//      {
//         
//         cairo_move_to(m_pdc, l.m_x, l.m_y);
//         
//      }
//      else
//      {
//         
//         cairo_line_to(m_pdc, l.m_x, l.m_y);
//         
//      }
      
      return true;
      
   }
   
   
   bool graphics::set(const ::mac::graphics_path::move & p)
   {
      
//      cairo_move_to(m_pdc, p.m_x, p.m_y);
      
      
      return true;
      
   }
   
   
   
   bool graphics::fill()
   {
      
      return fill(m_spbrush);
      
   }
   
   bool graphics::draw()
   {
      
      return draw(m_sppen);
      
   }
   
   
} // namespace mac



