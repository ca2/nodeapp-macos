#include "framework.h"
#include <math.h>


namespace draw2d_quartz2d
{
   
   
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////
   
   
   
/*   float dib::Cosines[360];
   float dib::Sines[360];
   
   
   int64_t dib::CosN[360]; // * 1 << 31
   int64_t dib::SinN[360];
   
   
   int64_t dib::Cos10N[10]; // until 10 degressa
   int64_t dib::Sin10N[10]; // more precision * 1 << 34
   
   
   double dib::dPi;*/
   
   
   dib::dib(sp(::base::application) papp) :
      element(papp),
      m_spbitmap(allocer()),
      m_spgraphics(allocer())
   {
      m_bMapped            = false;
   }
   
   COLORREF * dib::get_data()
   {
      return m_pcolorref;
   }
   ::draw2d::bitmap_sp dib::get_bitmap()
   {
      return m_spbitmap;
   }
   
   ::draw2d::bitmap_sp dib::detach_bitmap()
   {
      return m_spbitmap.detach();
   }
   
   
/*   CLASS_DECL_DRAW2D_QUARTZ2D void dib::s_initialize()
   {
      double dCos;
      double dSin;
      double d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;;
      int32_t i;
      for ( i=0; i<360; i++ )
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cosines[i]=float(dCos);
         Sines[i]=float(dSin);
         CosN[i] = (int64_t) (dCos * d32);
         SinN[i] = (int64_t) (dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for(i = 0; i < 10; i++)
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cos10N[i] = (int64_t) (dCos * d32);
         Sin10N[i] = (int64_t) (dSin * d32);
      }
   }*/
   
   void    dib::construct (int32_t cx,  int32_t cy)
   {
      m_pcolorref    = NULL;
      m_size.cx = 0;
      m_size.cy = 0;
      m_iScan = 0;
      create(cx, cy);
   }
   
   dib::~dib ()
   {
      //      Destroy ();
   }
   
   
   bool dib::create(class size size)
   {
      
      return create(size.cx, size.cy);
      
   }
   
   
   bool dib::create(int32_t width, int32_t height)
   {
      
      if(m_spbitmap.is_set()
         && m_spbitmap->get_os_data() != NULL
         && width == m_size.cx
         && height == m_size.cy)
         return true;
      
      Destroy();
      
      if(width <= 0 || height <= 0)
         return false;
      
      memset(&m_info, 0, sizeof (BITMAPINFO));
      
      m_info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      m_info.bmiHeader.biWidth         = width;
      m_info.bmiHeader.biHeight        = -height;
      m_info.bmiHeader.biPlanes        = 1;
      m_info.bmiHeader.biBitCount      = 32;
      m_info.bmiHeader.biCompression   = BI_RGB;
      m_info.bmiHeader.biSizeImage     = width * height * 4;
      
      m_spbitmap.create(allocer());
      m_spgraphics.create(allocer());
      
      if(m_spbitmap.m_p == NULL)
      {
         m_size.cx = 0;
         m_size.cy = 0;
         m_iScan = 0;
         return false;
      }
      
      if(!m_spbitmap->CreateDIBSection(NULL, &m_info, DIB_RGB_COLORS, (void **) &m_pcolorref, &m_iScan, NULL,  0))
      {
         m_size.cx = 0;
         m_size.cy = 0;
         m_iScan = 0;
         return false;
      }
      
      if(m_spbitmap->get_os_data() != NULL)
      {

         m_spgraphics->attach(m_spbitmap->get_os_data());
         
         m_spgraphics->m_pdib = this;

         m_size.cx = width;
         
         m_size.cy = height;
         
         return true;
         
      }
      else
      {
         
         Destroy();
         
         return false;
         
      }
      
   }
   
   bool dib::dc_select(bool bSelect)
   {
      /*      if(bSelect)
       {
       return m_spgraphics->SelectObject(m_spbitmap) != NULL;
       }
       else
       {
       return m_spgraphics->SelectObject(m_hbitmapOriginal) != NULL;
       }*/
      return true;
   }
   
   
   bool dib::create(::draw2d::graphics * pdc)
   {
      
      ::draw2d::bitmap * pbitmap = & (dynamic_cast < ::draw2d_quartz2d::graphics * > (pdc))->GetCurrentBitmap();
      
      if(pbitmap == NULL)
         return false;
      
      ::size size = pbitmap->get_size();
      
      if(!create(size.cx, size.cy))
      {
         
         return false;
         
      }
      
      from(pdc);
      
      return true;
      
   }
   
   
   bool dib::Destroy ()
   {
      
      if(m_spgraphics.is_set())
         m_spgraphics->detach();
         
      m_spbitmap.release();
      
      m_spgraphics.release();
      
      m_size.cx             = 0;
      
      m_size.cy             = 0;
      
      m_pcolorref    = NULL;
      
      return true;
      
   }
   
   
   bool dib::to(::draw2d::graphics * pgraphics, point pt, ::size size, point ptSrc)
   {
      
      return pgraphics->BitBlt(pt.x, pt.y, size.cx, size.cy, get_graphics(), ptSrc.x, ptSrc.y, SRCCOPY) != FALSE;
      
      /*  return SetDIBitsToDevice(
       (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(),
       pt.x, pt.y,
       size.cx, size.cy,
       ptSrc.x, ptSrc.y, ptSrc.y, cy - ptSrc.y,
       m_pcolorref, &m_info, 0)
       != FALSE; */
      
   }
   
   bool dib::from(::draw2d::graphics * pdc)
   {
      ::draw2d::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdc, 1, 1);
      ::draw2d::bitmap * pbitmap = COCOA_DC(pdc)->SelectObject(bitmap);
      if(pbitmap == NULL)
         return false;
      class size size = pbitmap->get_size();
      if(!create(size))
      {
         COCOA_DC(pdc)->SelectObject(pbitmap);
         return false;
      }
      throw todo(get_app());
      // xxx bool bOk = GetDIBits(COCOA_HDC(pdc), (HBITMAP) pbitmap->get_os_data(), 0, cy, m_pcolorref, &(m_info), DIB_RGB_COLORS) != FALSE;
      // xxx COCOA_DC(pdc)->SelectObject(pbitmap);
      // xxx return bOk;
   }
   
   bool dib::from(point ptDest, ::draw2d::graphics * pdc, point pt, class size sz)
   {
      return m_spgraphics->BitBlt(ptDest.x, ptDest.y, sz.cx, sz.cy, pdc, pt.x, pt.y, SRCCOPY) != FALSE;
   }
   

   
   void dib::SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy)
   {
      create(cx, cy);
      
      if(cx <= 0 || cy <= 0)
         return;
      
      
      
      
      // White blend dib
      dib dib1(get_app());
      dib1.create(cx, cy);
      dib1.set(255, 255, 255);
      
      dib1.m_spgraphics->DrawIcon(
                                  0, 0,
                                  picon,
                                  cx, cy,
                                  0,
                                  NULL,
                                  DI_IMAGE | DI_MASK);
      
      // Black blend dib
      ::draw2d::dib_sp spdib2(allocer());
      spdib2->create(cx, cy);
      spdib2->Fill(0, 0, 0, 0);
      
      spdib2->get_graphics()->DrawIcon(
                                       0, 0,
                                       picon,
                                       cx, cy,
                                       0,
                                       NULL,
                                       DI_IMAGE | DI_MASK);
      
      // Mask dib
      dib dibM(get_app());
      dibM.create(cx, cy);
      
      dibM.m_spgraphics->DrawIcon(
                                  0, 0,
                                  picon,
                                  cx, cy,
                                  0,
                                  NULL,
                                  DI_MASK);
      
      BYTE * r1=(BYTE*)dib1.m_pcolorref;
      BYTE * r2=(BYTE*)spdib2->get_data();
      BYTE * srcM=(BYTE*)dibM.m_pcolorref;
      BYTE * dest=(BYTE*)m_pcolorref;
      int32_t iSize = cx*cy;
      
      BYTE b;
      BYTE bMax;
      while ( iSize-- > 0)
      {
         if(srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b =(BYTE)(r1[0]  - r2[0]);
            bMax = max(b, bMax);
            b =(BYTE)(r1[1]  - r2[1]);
            bMax = max(b, bMax);
            b =(BYTE)(r1[2]  - r2[2]);
            bMax = max(b, bMax);
            bMax = 255 - bMax;
         }
         dest[0]  =  bMax;
         dest[1]  =  bMax;
         dest[2]  =  bMax;
         dest     += 4;
         srcM     += 4;
         r1       += 4;
         r2       += 4;
      }
      
      
      
   }
   void dib::set_mapped()
   {
      m_bMapped = true;
   }
   
   
   void dib::stretch_dib(::draw2d::dib * pdib)
   {
      
      throw todo(get_app());
      
   }
   
   ::draw2d::graphics * dib::get_graphics()
   {
      unmap();
      return m_spgraphics;
   }
   
   
   
   void dib::map(bool bApplyTransform)
   {
      
      if(m_bMapped)
         return;
      
      
      byte * pdata = (byte *) m_pcolorref;
      
      if(bApplyTransform)
      {
      
      int size = m_iScan * m_size.cy / sizeof(COLORREF);
      while(size > 0)
      {
         if(pdata[3] != 0)
         {
            pdata[0] = pdata[0] * 255 / pdata[3];
            pdata[1] = pdata[1] * 255 / pdata[3];
            pdata[2] = pdata[2] * 255 / pdata[3];
         }
         pdata += 4;
         size--;
      }
      
      }
      
      m_bMapped = true;
      
      
   }
   
   void dib::unmap()
   {
      
      if(!m_bMapped)
         return;
      
      byte * pdata =  (byte *) m_pcolorref;
      int size = m_iScan * m_size.cy / sizeof(COLORREF);
      while(size > 0)
      {
         pdata[0] = pdata[0] * pdata[3] / 255;
         pdata[1] = pdata[1] * pdata[3] / 255;
         pdata[2] = pdata[2] * pdata[3] / 255;
         pdata += 4;
         size--;
      }
      
      m_bMapped = false;

         
   }

} // namespace draw2d_quartz2d





