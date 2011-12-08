#include "StdAfx.h"
#include <math.h>

namespace win
{

   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   float dib::Cosines[360];
   float dib::Sines[360];

   __int64 dib::CosN[360]; // * 1 << 31
   __int64 dib::SinN[360]; 

   __int64 dib::Cos10N[10]; // until 10 degress
   __int64 dib::Sin10N[10]; // more precision * 1 << 34

   double dib::dPi;

   dib::dib(::ca::application * papp) :
      ca(papp),
      m_spbitmap(papp),
      m_spgraphics(papp)
   {
      m_pcolorref          = NULL;
      m_size               = class size(0, 0);
      m_hbitmapOriginal    = NULL;
   }

   COLORREF * dib::get_data()
   {
      return m_pcolorref;
   }
   ::ca::bitmap_sp dib::get_bitmap()
   {
      return m_spbitmap;
   }

   ::ca::bitmap_sp dib::detach_bitmap()
   {
      return m_spbitmap.detach();
   }


   CLASS_DECL_VMSWIN void dib::s_initialize()
   {
      double dCos;
      double dSin;
      double d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;;
      int i;
       for ( i=0; i<360; i++ )
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cosines[i]=float(dCos);
         Sines[i]=float(dSin);
         CosN[i] = (__int64) (dCos * d32);
         SinN[i] = (__int64) (dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
       for(i = 0; i < 10; i++)
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cos10N[i] = (__int64) (dCos * d32);
         Sin10N[i] = (__int64) (dSin * d32);
      }
   }

   void    dib::construct (int cx,  int cy)
   {
      m_pcolorref    = NULL;
      m_size         = class size(0, 0);
      create(cx, cy);
   }

   dib::~dib ()
   {
      Destroy ();
   }

   BOOL dib::create(class size size)
   {
      return create(size.cx, size.cy);
   }

   BOOL dib::create(int width, int height)
   {
      if(m_spbitmap.is_set()
      && m_spbitmap->get_os_data() != NULL 
      && class size(width, height) == m_size)
         return TRUE;

      Destroy();

      if(width <= 0 || height <= 0)
         return FALSE;

      ZeroMemory(&m_info, sizeof (BITMAPINFO));

      m_info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      m_info.bmiHeader.biWidth         = width;
      m_info.bmiHeader.biHeight        =- height;
      m_info.bmiHeader.biPlanes        = 1;
      m_info.bmiHeader.biBitCount      = 32; 
      m_info.bmiHeader.biCompression   = BI_RGB;
      m_info.bmiHeader.biSizeImage     = width * height * 4;

      if(m_spbitmap.m_p == NULL)
      {
         m_size = class size(0, 0);
         return FALSE;
      }
      
      if(!m_spbitmap->CreateDIBSection(NULL, &m_info, DIB_RGB_COLORS, (void **) &m_pcolorref, NULL, NULL))
      {
         m_size = class size(0, 0);
         return FALSE;
      }

      if(m_spbitmap->get_os_data() != NULL)
      {
         m_spgraphics->CreateCompatibleDC(NULL);
         ::ca::bitmap * pbitmap = m_spgraphics->SelectObject(m_spbitmap);
         if(pbitmap == NULL || 
            pbitmap->get_os_data() == NULL)
         {
            Destroy();
            return FALSE;
         }
         m_hbitmapOriginal = (HBITMAP) pbitmap->get_os_data();
         m_size = class size(width, height);
         return TRUE;
      }
      else
      {
         Destroy();
         return FALSE;
      }
   }

   bool dib::dc_select(bool bSelect)
   {
      if(bSelect)
      {
         return m_spgraphics->SelectObject(m_spbitmap) != NULL;
      }
      else
      {
         return m_spgraphics->SelectObject(m_hbitmapOriginal) != NULL;
      }
   }

   BOOL dib::create(::ca::graphics * pdc)
   {
      ::ca::bitmap * pbitmap = (dynamic_cast<::win::graphics * >(pdc))->GetCurrentBitmap();
      if(pbitmap == NULL)
         return FALSE;
      BITMAP bm;
      pbitmap->GetObject(sizeof(bm), &bm);
      if(!create(bm.bmWidth, bm.bmHeight))
      {
         return FALSE;
      }
      from(pdc);
      return TRUE;
   }

   BOOL dib::Destroy ()
   {
      if(m_spbitmap.m_p != NULL && m_spbitmap->get_os_data() != NULL)
         m_spbitmap->delete_object();

      
      if(m_spgraphics.is_set() && m_spgraphics->is_set())
      {
         m_spgraphics->SelectObject(m_hbitmapOriginal);
         m_spgraphics->DeleteDC();
      }

      m_size         = class size(0, 0);
      m_pcolorref    = NULL;
      
      return TRUE;
   }

   bool dib::to(::ca::graphics * pgraphics, point pt, class size size, point ptSrc)
   {
      return SetDIBitsToDevice(
         (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), 
         pt.x, pt.y, 
         size.cx, size.cy, 
         ptSrc.x, ptSrc.y, ptSrc.y, m_size.cy - ptSrc.y, 
         m_pcolorref, &m_info, 0)
            != FALSE; 
   }

   bool dib::from(::ca::graphics * pdc)
   {
      ::ca::bitmap_sp bitmap(get_app());
      bitmap->CreateCompatibleBitmap(pdc, 1, 1);
      ::ca::bitmap * pbitmap = WIN_DC(pdc)->SelectObject(bitmap);
      if(pbitmap == NULL)
         return false;
      BITMAP bm;
      memset(&bm, 0, sizeof(bm));
      if(!pbitmap->GetBitmap(&bm))
      {
         WIN_DC(pdc)->SelectObject(pbitmap);
         return false;
      }
      if(!create(bm.bmWidth, bm.bmHeight))
      {
         WIN_DC(pdc)->SelectObject(pbitmap);
         return false;
      }
      bool bOk = GetDIBits(WIN_HDC(pdc), (HBITMAP) pbitmap->get_os_data(), 0, m_size.cy, m_pcolorref, &(m_info), DIB_RGB_COLORS) != FALSE; 
      WIN_DC(pdc)->SelectObject(pbitmap);
      return bOk;
   }

   bool dib::from(point ptDest, ::ca::graphics * pdc, point pt, class size sz)
   {
      return m_spgraphics->BitBlt(ptDest.x, ptDest.y, sz.cx, sz.cy, pdc, pt.x, pt.y, SRCCOPY) != FALSE;
   }

   void dib::Fill ( int R, int G, int B )
   {
      COLORREF color=RGB ( B, G, R );
      int size=m_size.cx*m_size.cy;

      COLORREF * pcr;

      int iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &m_pcolorref[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<size; i++ )
      {
         m_pcolorref[i]=color;
      }
   }

   void dib::ToAlpha(int i)
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;

      while ( size-- )
      {
         dst[3] = dst[i];
         dst+=4;
      }
   }

   void dib::from_alpha()
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      __int64 size = m_size.area();

      while ( size-- )
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst+=4;
      }
   }

   void dib::mult_alpha()
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      __int64 size = m_size.area();

      while (size >= 8)
      {
         dst[0] = LOBYTE(((int)dst[0] * (int)dst[3]) / 255);
         dst[1] = LOBYTE(((int)dst[1] * (int)dst[3]) / 255);
         dst[2] = LOBYTE(((int)dst[2] * (int)dst[3]) / 255);

         dst[4+0] = LOBYTE(((int)dst[4+0] * (int)dst[4+3]) / 255);
         dst[4+1] = LOBYTE(((int)dst[4+1] * (int)dst[4+3]) / 255);
         dst[4+2] = LOBYTE(((int)dst[4+2] * (int)dst[4+3]) / 255);

         dst[8+0] = LOBYTE(((int)dst[8+0] * (int)dst[8+3]) / 255);
         dst[8+1] = LOBYTE(((int)dst[8+1] * (int)dst[8+3]) / 255);
         dst[8+2] = LOBYTE(((int)dst[8+2] * (int)dst[8+3]) / 255);

         dst[12+0] = LOBYTE(((int)dst[12+0] * (int)dst[12+3]) / 255);
         dst[12+1] = LOBYTE(((int)dst[12+1] * (int)dst[12+3]) / 255);
         dst[12+2] = LOBYTE(((int)dst[12+2] * (int)dst[12+3]) / 255);

         dst[16+0] = LOBYTE(((int)dst[16+0] * (int)dst[16+3]) / 255);
         dst[16+1] = LOBYTE(((int)dst[16+1] * (int)dst[16+3]) / 255);
         dst[16+2] = LOBYTE(((int)dst[16+2] * (int)dst[16+3]) / 255);

         dst[20+0] = LOBYTE(((int)dst[20+0] * (int)dst[20+3]) / 255);
         dst[20+1] = LOBYTE(((int)dst[20+1] * (int)dst[20+3]) / 255);
         dst[20+2] = LOBYTE(((int)dst[20+2] * (int)dst[20+3]) / 255);

         dst[24+0] = LOBYTE(((int)dst[24+0] * (int)dst[24+3]) / 255);
         dst[24+1] = LOBYTE(((int)dst[24+1] * (int)dst[24+3]) / 255);
         dst[24+2] = LOBYTE(((int)dst[24+2] * (int)dst[24+3]) / 255);

         dst[28+0] = LOBYTE(((int)dst[28+0] * (int)dst[28+3]) / 255);
         dst[28+1] = LOBYTE(((int)dst[28+1] * (int)dst[28+3]) / 255);
         dst[28+2] = LOBYTE(((int)dst[28+2] * (int)dst[28+3]) / 255);

         dst += 4 * 8;
         size -= 8;
      }
      while(size--)
      {
         dst[0] = LOBYTE(((int)dst[0] * (int)dst[3]) / 255);
         dst[1] = LOBYTE(((int)dst[1] * (int)dst[3]) / 255);
         dst[2] = LOBYTE(((int)dst[2] * (int)dst[3]) / 255);
         dst += 4;
      }
   }

   void dib::Map(int ToRgb, int FromRgb)
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;

      while ( size-- )
      {
         *dst = (byte) (*dst == FromRgb ? ToRgb : *dst);
         dst+=4;
      }
   }


   void dib::ToAlphaAndFill(int i, COLORREF cr)
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;

      BYTE uchB = rgba_get_b(cr);
      BYTE uchG = rgba_get_g(cr);
      BYTE uchR = rgba_get_r(cr);

      while ( size-- )
      {
         dst[3] = dst[i];
         dst[0] = uchB;
         dst[1] = uchG;
         dst[2] = uchR;
         dst+=4;
      }
   }

   void dib::GrayToARGB(COLORREF cr)
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;

      DWORD dwB = rgba_get_b(cr);
      DWORD dwG = rgba_get_g(cr);
      DWORD dwR = rgba_get_r(cr);

      while (size-- > 0)
      {
         dst[3] = dst[0];
         dst[0] = (BYTE)(((dwB * dst[3]) / 256) & 0xff);
         dst[1] = (BYTE)(((dwG * dst[3]) / 256) & 0xff);
         dst[2] = (BYTE)(((dwR * dst[3]) / 256) & 0xff);
         dst+=4;
      }
   }


   void dib::BitBlt(::ca::dib *pdib, int op)
   {
      if(op == 123) // zero dest RGB, invert alpha, and OR src RGB
      {
         int isize=m_size.cx*m_size.cy;
         LPDWORD lpbitsSrc= (LPDWORD) WIN_DIB(pdib)->m_pcolorref;
         LPDWORD lpbitsDest= (LPDWORD) m_pcolorref;

         COLORREF _colorref = RGB ( 0, 0, 0 ) | (255 << 24);
         COLORREF colorrefa[2];
         colorrefa[0] = _colorref;
         colorrefa[1] = _colorref;

         COLORREF _colorrefN = RGB ( 255, 255, 255) | (0 << 24);
         COLORREF colorrefaN[2];
         colorrefaN[0] = _colorrefN;
         colorrefaN[1] = _colorrefN;
   #ifdef _AMD64_

         //x64
   #else
         _asm
         {
            emms
            mov      eax, isize
            mov      ebx, lpbitsDest
            mov      ecx, lpbitsSrc
            movq     mm0, colorrefa
            movq     mm7, colorrefaN
      fill_loop:
            cmp      eax, 1
            jle      fill_last
            movq     mm1, [ebx]
            movq     mm2, [ecx]
            pandn    mm1, mm0
            pand     mm2, mm7
            por      mm1, mm2
            movq     [ebx], mm1
            
            sub      eax, 2
            add      ebx, 8
            add      ecx, 8

            jmp      fill_loop

      fill_last:
            emms 
         }
   #endif
      }

   }


   void dib::Invert()
   {
      int size=m_size.cx*m_size.cy;
      LPBYTE lpb = (LPBYTE) m_pcolorref;
      for ( int i=0; i<size; i++ )
      {
         lpb[0] = 255 - lpb[0];
         lpb[1] = 255 - lpb[1];
         lpb[2] = 255 - lpb[2];
         lpb += 4;
      }
   }

   void dib::channel_invert(visual::rgba::echannel echannel)
   {
      __int64 size=m_size.area();
      LPBYTE lpb = (LPBYTE) m_pcolorref;
      lpb += ((int)echannel) % 4;
      for ( int i=0; i<size; i++ )
      {
         *lpb = 255 - *lpb;
         lpb += 4;
      }
   }
   void dib::channel_multiply(visual::rgba::echannel echannel, double dRate)
   {
      if(dRate < 0)
         return;
      register __int64 size = area();
      LPBYTE lpb = (LPBYTE) get_data();
      lpb += ((int)echannel) % 4;
      register int iDiv = 256 * 256;
      register int iMul = (int) (dRate * ((double) iDiv));
      register int iRes;
      for(register __int64 i = 0; i < size; i++)
      {
         iRes = *lpb * iMul / iDiv; 
         *lpb = (byte) (iRes > 255 ? 255 : iRes);
         lpb += 4;
      }
   }

   void dib::FillGlass ( int R, int G, int B, int A )
   {
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);   
         dst+=4;
      }
   }

   void dib::FillStippledGlass ( int R, int G, int B )
   {   
      COLORREF color=RGB ( B, G, R );
      int w=m_size.cx;
      int h=m_size.cy;

      for ( int j=0; j<w; j++ )
      {
         for ( int i=0; i<h; i++ )
         {
            m_pcolorref[j*w+i]=((i+j)&0x1) ? m_pcolorref[j*w+i] : color;
         }
      }
   }

   void dib::copy(::ca::dib * pdib)
   {
      // If DibSize Wrong Re-create dib
      if ( (WIN_DIB(pdib)->m_size.cx!=m_size.cx) || (WIN_DIB(pdib)->m_size.cy!=m_size.cy) )
         WIN_DIB(pdib)->create ( m_size.cx, m_size.cy );
      // do copy
      memcpy ( WIN_DIB(pdib)->m_pcolorref, m_pcolorref, m_size.cx*m_size.cy*4 );
   }


   void dib::Paste ( ::ca::dib * pdib )
   {
      // If DibSize Wrong Re-create dib
      if ( (m_size.cx!=WIN_DIB(pdib)->m_size.cx) || (m_size.cy!=WIN_DIB(pdib)->m_size.cy) )
         create ( WIN_DIB(pdib)->m_size.cx, WIN_DIB(pdib)->m_size.cy );
      // do Paste
      memcpy ( m_pcolorref, WIN_DIB(pdib)->m_pcolorref, m_size.cx*m_size.cy*4 );
   }

   bool dib::color_blend(COLORREF cr, BYTE bAlpha)
   {

      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;

      DWORD dwB = rgba_get_b(cr);
      DWORD dwG = rgba_get_g(cr);
      DWORD dwR = rgba_get_r(cr);
    
      DWORD dwB_ = dwB << 8;
      DWORD dwG_ = dwG << 8;
      DWORD dwR_ = dwR << 8;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
         dst[1]=(BYTE)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
         dst[2]=(BYTE)(((dst[2]-dwG)*bAlpha+dwR_)>>8);   
         dst+=4;
      }
      return true;
   }


   void dib::Blend (::ca::dib * pdib, int A )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);   
         dst+=4;
         src+=4;
      }
   }

   bool dib::Blend(::ca::dib *pdib, ::ca::dib *pdibA, int A)
   {
      if(m_size != WIN_DIB(pdib)->m_size ||
         m_size != WIN_DIB(pdibA)->m_size)
         return false;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      BYTE *alf=(BYTE*)WIN_DIB(pdibA)->m_pcolorref;
      int size=m_size.cx*m_size.cy;

      A = 2 - A;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0]-dst[0])*alf[A]+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((src[1]-dst[1])*alf[A]+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((src[2]-dst[2])*alf[A]+(dst[2]<<8))>>8);   
         dst+=4;
         src+=4;
         alf+=4;
      }

      return true;
   }

   void dib::Darken (::ca::dib * pdib )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
         dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
         dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);   
         dst+=4;
         src+=4;
      }
   }

   void dib::Difference (::ca::dib * pdib )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         int Difference;
         Difference=src[0]-dst[0];
         dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
         Difference=src[1]-dst[1];
         dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
         Difference=src[2]-dst[2];
         dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);   
         dst+=4;
         src+=4;
      }
   }

   void dib::Lighten (::ca::dib * pdib )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
         dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
         dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);   
         dst+=4;
         src+=4;
      }
   }


   void dib::Multiply (::ca::dib * pdib )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
         dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
         dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);   
         dst+=4;
         src+=4;
      }
   }

   void dib::Screen (::ca::dib * pdib )
   {
      if ( m_size!=WIN_DIB(pdib)->m_size )
         return;

      BYTE *src=(BYTE*)WIN_DIB(pdib)->m_pcolorref;
      BYTE *dst=(BYTE*)m_pcolorref;
      int size=m_size.cx*m_size.cy;
         
      while ( size-- )
      {
         dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
         dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
         dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));   
         dst+=4;
         src+=4;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Rectangle Functions
   //////////////////////////////////////////////////////////////////////

   void dib::copy (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to copy return
      if ( (dx<=0) || (dy<=0) )
         return;
      // If DibSize Wrong Re-create dib
      if ( (dx!=WIN_DIB(pdib)->m_size.cx) || (dy!=WIN_DIB(pdib)->m_size.cy) )
         WIN_DIB(pdib)->create ( dx, dy );

      // Prepare buffer Addresses
      COLORREF *src=m_pcolorref+(py*m_size.cx)+px;
      COLORREF *dst=WIN_DIB(pdib)->m_pcolorref;

      // Do copy
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
            dst[i]=src[i];
         src+=m_size.cx;
         dst+=WIN_DIB(pdib)->m_size.cx;
      }
   }

   void dib::PasteRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Paste return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      COLORREF *src=WIN_DIB(pdib)->m_pcolorref+((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x;
      COLORREF *dst=m_pcolorref+(py*m_size.cx)+px;

      // Do Paste
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
            dst[i]=src[i];
         src+=WIN_DIB(pdib)->m_size.cx;
         dst+=m_size.cx;
      }
   }

   void dib::FillRect ( int x, int y, int w, int h, int R, int G, int B )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<m_size.cx) ? w : m_size.cx-x;
      int dy=((y+h)<m_size.cy) ? h : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Fill return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst=m_pcolorref+(py*m_size.cx)+px;
      COLORREF color=RGB ( B, G, R );

      // Do Fill
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[i]=color;   
         }
         dst+=m_size.cx;
      }
   }

   void dib::FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<m_size.cx) ? w : m_size.cx-x;
      int dy=((y+h)<m_size.cy) ? h : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do FillGlass
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);   
            dst+=4;
         }
         dst+=(m_size.cx-dx)<<2;
      }
   }

   void dib::FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<m_size.cx) ? w : m_size.cx-x;
      int dy=((y+h)<m_size.cy) ? h : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillStippledGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst=m_pcolorref+(py*m_size.cx)+px;
      COLORREF color=RGB ( B, G, R );

      // Do FillStippledGlass
      for ( int j=0; j<dy; j++ )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[i]=((i+j)&0x1) ? dst[i] : color;   
         }
         dst+=m_size.cx;
      }
   }

   void dib::BlendRect (::ca::dib * pdib, int x, int y, int A )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Blend return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Blend
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);   
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   void dib::DarkenRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Darken return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Darken
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);   
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   void dib::DifferenceRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Difference return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Difference
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            int Difference;
            Difference=src[0]-dst[0];
            dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[1]-dst[1];
            dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[2]-dst[2];
            dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);   
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   void dib::LightenRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Lighten return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Lighten
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   void dib::MultiplyRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Multiply return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Multiply
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
            dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
            dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   void dib::ScreenRect (::ca::dib * pdib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+WIN_DIB(pdib)->m_size.cx)<m_size.cx) ? WIN_DIB(pdib)->m_size.cx : m_size.cx-x;
      int dy=((y+WIN_DIB(pdib)->m_size.cy)<m_size.cy) ? WIN_DIB(pdib)->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Screen return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)WIN_DIB(pdib)->m_pcolorref+(((py-y)*WIN_DIB(pdib)->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)m_pcolorref+((py*m_size.cx)+px)*4;

      // Do Screen
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
            dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
            dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(WIN_DIB(pdib)->m_size.cx-dx)<<2;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void dib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
   {
      int dx, dy, k1, k2, d, x, y;
      COLORREF color=RGB ( B, G, R );

      dx=x2-x1;
      dy=y2-y1;
      d=(dy<<1)-dx;
      k1=dy<<1;
      k2=(dy-dx)<<1;
      x=x1;
      y=y1;

      m_pcolorref[y*m_size.cx+x]=color;
      while (x<dx) 
      {
         if (d<=0) 
         {
            d+=k1;
            x++;
         } 
         else 
         {
            d+=k2;
            x++;
            y++;
         }
         m_pcolorref[y*m_size.cx+x]=color;
      }
   }*/

   void dib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
   {
      int d, x, y, ax, ay, sx, sy, dx, dy;
      COLORREF color=RGB ( B, G, R );
      
      dx=x2-x1;
      ax=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;
      
      if ( ax>ay )
      {
         d=ay-(ax>>1);
         while ( x!=x2 )
         {
            m_pcolorref[y*m_size.cx+x]=color;
            if ( d>=0 )
            {
               y+=sy;
               d-=ax;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=ax-(ay>>1);
         while ( y!=y2 )
         {
            m_pcolorref[y*m_size.cx+x]=color;
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=ax;
         }
      }
   }

   void dib::LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A )
   {
      int d, x, y, ax, ay, sx, sy, dx, dy;
//      COLORREF color=RGB ( B, G, R );
      BYTE *dst=(BYTE *)m_pcolorref;
      
      dx=x2-x1;
      ax=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;
      
      if ( ax>ay )
      {
         d=ay-(ax>>1);
         while ( x!=x2 )
         {
            dst[(y*m_size.cx+x)<<2]=(BYTE)(((B-dst[(y*m_size.cx+x)<<2])*A+(dst[(y*m_size.cx+x)<<2]<<8))>>8);
            dst[((y*m_size.cx+x)<<2)+1]=(BYTE)(((G-dst[((y*m_size.cx+x)<<2)+1])*A+(dst[((y*m_size.cx+x)<<2)+1]<<8))>>8);
            dst[((y*m_size.cx+x)<<2)+2]=(BYTE)(((R-dst[((y*m_size.cx+x)<<2)+2])*A+(dst[((y*m_size.cx+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               y+=sy;
               d-=ax;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=ax-(ay>>1);
         while ( y!=y2 )
         {
            dst[(y*m_size.cx+x)<<2]=(BYTE)(((B-dst[(y*m_size.cx+x)<<2])*A+(dst[(y*m_size.cx+x)<<2]<<8))>>8);
            dst[((y*m_size.cx+x)<<2)+1]=(BYTE)(((G-dst[((y*m_size.cx+x)<<2)+1])*A+(dst[((y*m_size.cx+x)<<2)+1]<<8))>>8);
            dst[((y*m_size.cx+x)<<2)+2]=(BYTE)(((R-dst[((y*m_size.cx+x)<<2)+2])*A+(dst[((y*m_size.cx+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=ax;
         }
      }
   }

   void dib::Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask)
   {
      COLORREF crFind = RGB(rgba_get_b(crMask), rgba_get_g(crMask), rgba_get_r(crMask));
      COLORREF crSet = RGB(rgba_get_b(crInMask), rgba_get_g(crInMask), rgba_get_r(crInMask));
      COLORREF crUnset  = RGB(rgba_get_b(crOutMask), rgba_get_g(crOutMask), rgba_get_r(crOutMask));

      int size=m_size.cx*m_size.cy;

      for ( int i=0; i<size; i++ )
         if(m_pcolorref[i]== crFind)
            m_pcolorref[i] = crSet;
         else
            m_pcolorref[i] = crUnset;

   }

   void dib::transparent_color(color color)
   {
      COLORREF crFind = color.get_rgb();
      __int64 size = area();

      for ( int i=0; i<size; i++ )
         if((m_pcolorref[i] & 0x00ffffff) == crFind)
            ((LPBYTE)&m_pcolorref[i])[3] = 255;
         else
            ((LPBYTE)&m_pcolorref[i])[3] = 0;
   }

   void dib::channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, visual::rgba::echannel echannel)
   {
      int size = m_size.cx * m_size.cy;
      unsigned char * puch = (unsigned char * ) m_pcolorref;
      puch += ((int) echannel) % 4;

      for(int i = 0; i < size; i++)
      {
         if(*puch == uchFind)
            *puch = uchSet;
         else
            *puch = uchUnset;
         puch += 4;
      }
   }

   DWORD dib::GetPixel(int x, int y)
   {
      DWORD dw = *(m_pcolorref + x + (m_size.cy - y - 1) * m_size.cx);
      return RGB(rgba_get_b(dw), rgba_get_g(dw), rgba_get_r(dw));
   }

   // too slow for animation on AMD XP Atlhon.
   // TOP SUGGESTION:
   // The gradient can´t have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
   void dib::RadialFill(BYTE alpha, BYTE red, BYTE green, BYTE blue, int xCenter, int yCenter, int iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {
         
         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_Size.cx) xU = m_Size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_Size.cy) yU = m_Size.cy - 1;


         BYTE *dst = ((BYTE*)(m_pcolorref + xL + yL * m_Size.cx));
         DWORD dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
         int size=m_Size.cx*m_Size.cy;
         double iLevel;

         int dx, dy;
         int dx0, dy0;
         int dx1, dy1;
         int dx2, dy2;
         int dx3, dy3;
         int dx4, dy4;
         int dx5, dy5;
         int dx6, dy6;
         int dx7, dy7;
         int dx8, dy8;
         int dx9, dy9;
         int dxA, dyA;
         int dxB, dyB;
         int dxC, dyC;
         int dxD, dyD;
         int dxE, dyE;
         int dxF, dyF;

         unsigned long dr;
         unsigned long dq;
         unsigned long dr0, dq0;
         unsigned long dr1, dq1;
         unsigned long dr2, dq2;
         unsigned long dr3, dq3;
         unsigned long dr4, dq4;
         unsigned long dr5, dq5;
         unsigned long dr6, dq6;
         unsigned long dr7, dq7;
         unsigned long dr8, dq8;
         unsigned long dr9, dq9;
         unsigned long drA, dqA;
         unsigned long drB, dqB;
         unsigned long drC, dqC;
         unsigned long drD, dqD;
         unsigned long drE, dqE;
         unsigned long drF, dqF;
         int x, y;

         {
            for(y = yL; y <= yU; y++)
            {
               for(x = xL; x <= xU; x++)
               {
                  dx = abs(x - xCenter);
                  dy = abs(y - yCenter);
                  isqrt((dx * dx) + (dy * dy), &dr, &dq);
                  if(dr < iRadius)
                  {
                     iLevel = 1.0 - dr * 1.0 / iRadius;
                     dst[0] = blue  * iLevel;
                     dst[1] = green * iLevel;
                     dst[2] = red   * iLevel;   
                  }
                  dst += 4;
               }
               dst += dwAdd;
            }
         }
      }
      else if(version == 1)*/
      {

         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
         LPBYTE lpb = (LPBYTE) (((int) lpbAlloc + 3) & ~3);


         int x, y;
         int b;

//         int r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = 255 - b;

               
               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }

         
         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_size.cx) xU = m_size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_size.cy) yU = m_size.cy - 1;
      

         BYTE *dst = ((BYTE*)(m_pcolorref + xL + yL * m_size.cx));
         DWORD dwAdd = ((m_size.cx - 1 - xU) + xL) * 4;
//         int size=m_size.cx*m_size.cy;
      
         int dx, dy;

         // Top Left

         for(y = yL; y <= yU; y++)
         {
            for(x = xL; x <= xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = lpb[dx + dy * iRadius];
               dst[0] = (byte) (blue     * b / 255);
               dst[1] = (byte) (green    * b / 255);
               dst[2] = (byte) (red      * b / 255);   
               dst[3] = (byte) (alpha    * b / 255);   
               dst += 4;
            }
            dst += dwAdd;
         }

         free(lpbAlloc);
      }
   }


   void dib::RadialFill(
      BYTE alpha1, BYTE red1, BYTE green1, BYTE blue1,
      BYTE alpha2, BYTE red2, BYTE green2, BYTE blue2,
      int xCenter, int yCenter, int iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {
         
         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_Size.cx) xU = m_Size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_Size.cy) yU = m_Size.cy - 1;


         BYTE *dst = ((BYTE*)(m_pcolorref + xL + yL * m_Size.cx));
         DWORD dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
         int size=m_Size.cx*m_Size.cy;
         double iLevel;

         int dx, dy;
         int dx0, dy0;
         int dx1, dy1;
         int dx2, dy2;
         int dx3, dy3;
         int dx4, dy4;
         int dx5, dy5;
         int dx6, dy6;
         int dx7, dy7;
         int dx8, dy8;
         int dx9, dy9;
         int dxA, dyA;
         int dxB, dyB;
         int dxC, dyC;
         int dxD, dyD;
         int dxE, dyE;
         int dxF, dyF;

         unsigned long dr;
         unsigned long dq;
         unsigned long dr0, dq0;
         unsigned long dr1, dq1;
         unsigned long dr2, dq2;
         unsigned long dr3, dq3;
         unsigned long dr4, dq4;
         unsigned long dr5, dq5;
         unsigned long dr6, dq6;
         unsigned long dr7, dq7;
         unsigned long dr8, dq8;
         unsigned long dr9, dq9;
         unsigned long drA, dqA;
         unsigned long drB, dqB;
         unsigned long drC, dqC;
         unsigned long drD, dqD;
         unsigned long drE, dqE;
         unsigned long drF, dqF;
         int x, y;

         {
            for(y = yL; y <= yU; y++)
            {
               for(x = xL; x <= xU; x++)
               {
                  dx = abs(x - xCenter);
                  dy = abs(y - yCenter);
                  isqrt((dx * dx) + (dy * dy), &dr, &dq);
                  if(dr < iRadius)
                  {
                     iLevel = 1.0 - dr * 1.0 / iRadius;
                     dst[0] = blue  * iLevel;
                     dst[1] = green * iLevel;
                     dst[2] = red   * iLevel;   
                  }
                  dst += 4;
               }
               dst += dwAdd;
            }
         }
      }
      else if(version == 1)*/
      {

         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
         LPBYTE lpb = (LPBYTE) (((int) lpbAlloc + 3) & ~3);


         int x, y;
         int b;

//         int r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = ~b;

               
               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }

         
         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_size.cx) xU = m_size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_size.cy) yU = m_size.cy - 1;
      

         BYTE *dst = ((BYTE*)(m_pcolorref + xL + yL * m_size.cx));
         DWORD dwAdd = ((m_size.cx - 1 - xU) + xL) * 4;
//         int size=m_size.cx*m_size.cy;
      
         int dx, dy;

         BYTE bComp;

         // Top Left

         for(y = yL; y <= yU; y++)
         {
            for(x = xL; x <= xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = lpb[dx + dy * iRadius];
               bComp = (byte) ~b;
               dst[0] = (byte) (((blue1  * b) + (blue2  * bComp)) / 255);
               dst[1] = (byte) (((green1 * b) + (green2 * bComp)) / 255);
               dst[2] = (byte) (((red1   * b) + (red2   * bComp)) / 255);
               dst[3] = (byte) (((alpha1 * b) + (alpha2 * bComp)) / 255);
               dst += 4;
            }
            dst += dwAdd;
         }

         free(lpbAlloc);
      }
   }

   void dib::SetIconMask(::visual::icon * picon, int cx, int cy)
   {
      create(cx, cy);

      if(cx <= 0 || cy <= 0)
         return;

    
    

      // White blend dib
      dib dib1(get_app());
      dib1.create(cx, cy);
      dib1.Fill(255, 255, 255);

      dib1.m_spgraphics->DrawIcon(
         0, 0,
         picon,
         cx, cy,
         0,
         NULL,
         DI_IMAGE | DI_MASK);
    
      // Black blend dib
      ::ca::dib_sp spdib2(get_app());
      spdib2->create(cx, cy);
      spdib2->Fill(0, 0, 0);

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
      int iSize = m_size.cx*m_size.cy;
    
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

   void dib::rotate(::ca::dib * pdib, double dAngle, double dScale)
   {
     // ::ca::dib_sp spdib(get_app());
   //   spdib->Paste(this);

      int cx = m_size.cx;
      int cy = m_size.cy;

      int l = max(cx, cy);

      
      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      int joff = cy / 2;
      int ioff = cx / 2;

      //int iAngle = iStep % 360;
      //int iAngle = iStep;
      //int iAngle = 1;
      //int k = 0;

   /*     for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
            y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
            m_pcolorref[(j+joff)*cx+(i+ioff)]=
               spdib->m_pcolorref[abs(y%m_size.cy)*m_size.cx+abs(x%m_size.cx)];
            //k++;
         }
         (j+joff)*cx+(i+ioff)
      }*/

      int k = 0;
      double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
      double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
      int cx1 = m_size.cx - 1;
      int cy1 = m_size.cy - 1;
        for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }


            
            m_pcolorref[(j+joff)*cx+(i+ioff)]=
               WIN_DIB(pdib)->m_pcolorref[y * cx + x];
            k++;
         }
      }
   }


   void dib::Rotate034(::ca::dib * pdib, double dAngle, double dScale)
   {
     
      int cx = m_size.cx;
      int cy = m_size.cy;

      int l = max(cx, cy);

      
      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      if((cy % 2) == 1)
         jmax++;

      if((cx % 2) == 1)
         imax++;
      
      int joff = cy / 2;
      int ioff = cx / 2;

      
      int k = 0;
      double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
      double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
      int cx1 = m_size.cx - 1;
      int cy1 = m_size.cy - 1;
        for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }


            
            m_pcolorref[(j+joff)*cx+(i+ioff)]=
               WIN_DIB(pdib)->m_pcolorref[y * cx + x];
            k++;
         }
      }
   }

   void dib::rotate(
      ::ca::dib * pdib,
      LPCRECT lpcrect,
      double dAngle, 
      double dScale)
   {
     // ::ca::dib_sp spdib(get_app());
   //   spdib->Paste(this);



      rect rect(lpcrect);

      int cx = rect.width();
      int cy = rect.height();

      int l = max(cx, cy);
      
      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      int joff = cy / 2 + rect.left;
      int ioff = cx / 2 + rect.top;

      //int iAngle = iStep % 360;
      //int iAngle = iStep;
      //int iAngle = 1;
      //int k = 0;

   /*     for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
            y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
            m_pcolorref[(j+joff)*cx+(i+ioff)]=
               spdib->m_pcolorref[abs(y%m_size.cy)*m_size.cx+abs(x%m_size.cx)];
            //k++;
         }
         (j+joff)*cx+(i+ioff)
      }*/

      int k = 0;
      double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
      double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
      int cx1 = cx - 1;
      int cy1 = cy - 1;
        for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / cx) % 2 == 0)
            {
               x %= cx;
            }
            else
            {
               x = cx1 - (x % cx);
            }

            if((y / cy) % 2 == 0)
            {
               y %= cy;
            }
            else
            {
               y = cy1 - (y % cy);
            }


            
            m_pcolorref[(j+joff)*m_size.cx+(i+ioff)]=
               WIN_DIB(pdib)->m_pcolorref[y * m_size.cx + x];
            k++;
         }
      }
   }

   /*int dib::cos(int i, int iAngle)
   {
      return (int) (((_int64) i * CosN[iAngle]) >> 32);
   }

   int dib::sin(int i, int iAngle)
   {
      return (int) (((_int64) i * SinN[iAngle]) >> 32);
   }*/




   void dib::Fill (int A, int R, int G, int B )
   {
      COLORREF color = RGB ( B, G, R ) | (A << 24);
      int size=m_size.cx*m_size.cy;

      COLORREF * pcr;

      int iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &m_pcolorref[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<size; i++ )
      {
         m_pcolorref[i]=color;
      }

   }

   COLORREF dib::GetAverageColor()
   {
      double dR = 0.0;
      double dG = 0.0;
      double dB = 0.0;
      int iRLine;
      int iGLine;
      int iBLine;
      double dDiv = m_size.cx * m_size.cy;
      if(dDiv > 0)
      {
         LPBYTE lpb = (LPBYTE) m_pcolorref;
         for (int y = 0; y < m_size.cy; y++)
         {
            iRLine = 0;
            iGLine = 0;
            iBLine = 0;
            for (int x = 0; x < m_size.cx; x++)
            {
               iRLine += lpb[2];
               iGLine += lpb[1];
               iBLine += lpb[0];
               lpb += 4;
            }
            dR += iRLine / dDiv;
            dG += iGLine / dDiv;
            dB += iBLine / dDiv;
         }
         int iR = (int) dR;
         int iG = (int) dG;
         int iB = (int) dB;
         return RGB(iR, iG, iB);
      }
      else
      {
         return 0;
      }
      
   }


   void dib::xor(::ca::dib * pdib)
   {
      if(m_size.cx != WIN_DIB(pdib)->m_size.cx
      || m_size.cy != WIN_DIB(pdib)->m_size.cy)
      {
         return;
      }
      int iCount = m_size.cx * m_size.cy;
      LPDWORD lpd1 = (LPDWORD) m_pcolorref;
      LPDWORD lpd2 = (LPDWORD) WIN_DIB(pdib)->m_pcolorref;
      for(int i = 0; i < iCount; i++)
      {
         *lpd1 = *lpd1 ^ *lpd2;
         lpd1++;
         lpd2++;
      }
   }

   void dib::create_frame(class size size, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      int iFrameWidth = size.cx / iSliceCount;
      int iFrameHeight = size.cy / iSliceCount;
      create(iFrameWidth, iFrameHeight);
   }

   void dib::set_frame1(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = m_size.cx / iSliceCount;
      int iFrameHeight = m_size.cy / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = 0; y < iFrameHeight; y++)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int x = 0; x < iFrameWidth; x++)
         {
             *lpDestLine = *lpSrc;
             lpDestLine++;
             lpSrc++;
         }
      }
   }

   void dib::set_frame2(void * lpdata, int iFrame, int iFrameCount)
   {
      if(lpdata == NULL)
         return;
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = m_size.cx / iSliceCount;
      int iFrameHeight = m_size.cy / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int x = 0; x < iFrameWidth; x++)
         {
             *lpDestLine = *lpSrc;
             lpDestLine++;
             lpSrc++;
         }
      }
   }

   void dib::xor_dib_frame2(void * lpdata, int iFrame, int iFrameCount)
   {
      if(lpdata == NULL)
         return;
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = m_size.cx / iSliceCount;
      int iFrameHeight = m_size.cy / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int x = 0; x < iFrameWidth; x++)
         {
             *lpDestLine ^= *lpSrc;
             lpDestLine++;
             lpSrc++;
         }
      }
   }

   void dib::get_frame(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      int iFrameWidth = m_size.cx / iSliceCount;
      int iFrameHeight = m_size.cy / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpSrc = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight *  m_size.cx];
      COLORREF * lpDest = (COLORREF *) lpdata;
      COLORREF * lpSrcLine;
      for(int y = 0; y < iFrameHeight; y++)
      {
         lpSrcLine = &lpSrc[y * m_size.cx];
         for(int x = 0; x < iFrameWidth; x++)
         {
             *lpDest = *lpSrcLine;
             lpDest++;
             lpSrcLine++;
         }
      }
   }

   bool dib::is_rgb_black()
   {
      int iSize = m_size.cx * m_size.cy;
      COLORREF * lp = m_pcolorref;
      for(int i = 0; i < iSize; i++)
      {
         if((*lp & 0x00FFFFFF) != 0)
            return false;
         lp++;
      }
      return true;
   }

   void dib::DivideRGB(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) m_pcolorref);
      int i = 0;
      int iCount1 = iCount - iCount % 8;
      for(; i < iCount1; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;

         lp[4] /= (byte) iDivide;
         lp[5] /= (byte) iDivide;
         lp[6] /= (byte) iDivide;

         lp[8] /= (byte) iDivide;
         lp[9] /= (byte) iDivide;
         lp[10] /= (byte) iDivide;

         lp[12] /= (byte) iDivide;
         lp[13] /= (byte) iDivide;
         lp[14] /= (byte) iDivide;

         lp[16] /= (byte) iDivide;
         lp[17] /= (byte) iDivide;
         lp[28] /= (byte) iDivide;

         lp[20] /= (byte) iDivide;
         lp[21] /= (byte) iDivide;
         lp[22] /= (byte) iDivide;

         lp[24] /= (byte) iDivide;
         lp[25] /= (byte) iDivide;
         lp[26] /= (byte) iDivide;

         lp[28] /= (byte) iDivide;
         lp[29] /= (byte) iDivide;
         lp[30] /= (byte) iDivide;

         lp += 4 * 8;
      }
      for(; i < iCount; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;
         lp +=4;
      }
   }

   void dib::DivideARGB(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) m_pcolorref);
      for(int i = 0; i < iCount; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }

   void dib::DivideA(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) m_pcolorref);
      for(int i = 0; i < iCount; i++)
      {
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }


   void dib::stretch_dib(::ca::dib * pdib)
   {
      ::StretchDIBits(
         SP_HDC(m_spgraphics),
         0, 0,
         m_size.cx, m_size.cy,
         0, 0, 
         WIN_DIB(pdib)->m_size.cx, WIN_DIB(pdib)->m_size.cy,
         WIN_DIB(pdib)->m_pcolorref,
         &WIN_DIB(pdib)->m_info,
         DIB_RGB_COLORS,
         SRCCOPY);
   }

   ::ca::graphics * dib::get_graphics()
   {
      return m_spgraphics;
   }

   double dib::pi()
   {
      return dPi;
   }

   void dib::fill_channel(int intensity, visual::rgba::echannel echannel)
   {
       int offset = ((int)echannel) % 4;
      int size=m_size.cx*m_size.cy;

      BYTE * pb;

      int iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pb = ((BYTE * ) &m_pcolorref[i]) + offset;
         pb[0 * 4] = (byte) intensity;
         pb[1 * 4] = (byte) intensity;
         pb[2 * 4] = (byte) intensity;
         pb[3 * 4] = (byte) intensity;
         pb[4 * 4] = (byte) intensity;
         pb[5 * 4] = (byte) intensity;
         pb[6 * 4] = (byte) intensity;
         pb[7 * 4] = (byte) intensity;
         pb[8 * 4] = (byte) intensity;
         pb[9 * 4] = (byte) intensity;
         pb[10 * 4] = (byte) intensity;
         pb[11 * 4] = (byte) intensity;
         pb[12 * 4] = (byte) intensity;
         pb[13 * 4] = (byte) intensity;
         pb[14 * 4] = (byte) intensity;
         pb[15 * 4] = (byte) intensity;
         pb[16 * 4] = (byte) intensity;
         pb[17 * 4] = (byte) intensity;
         pb[18 * 4] = (byte) intensity;
         pb[19 * 4] = (byte) intensity;
         pb[20 * 4] = (byte) intensity;
         pb[21 * 4] = (byte) intensity;
         pb[22 * 4] = (byte) intensity;
         pb[23 * 4] = (byte) intensity;
         pb[24 * 4] = (byte) intensity;
         pb[25 * 4] = (byte) intensity;
         pb[26 * 4] = (byte) intensity;
         pb[27 * 4] = (byte) intensity;
         pb[28 * 4] = (byte) intensity;
         pb[29 * 4] = (byte) intensity;
         pb[30 * 4] = (byte) intensity;
         pb[31 * 4] = (byte) intensity;
      }

      for (i=0; i<size; i++ )
      {
         *(((BYTE * ) &m_pcolorref[i]) + offset) = (byte) intensity;
      }
  }


   int dib::cos(int i, int iAngle)
   {
      return (int) (((_int64) i * CosN[iAngle]) >> 31);
   }

   int dib::sin(int i, int iAngle)
   {
      return (int) (((_int64) i * SinN[iAngle]) >> 31);
   }

   int dib::cos10(int i, int iAngle)
   {
      return (int) (((_int64) i * Cos10N[iAngle]) >> 34);
   }

   int dib::sin10(int i, int iAngle)
   {
      return (int) (((_int64) i * Sin10N[iAngle]) >> 34);
   }

   int dib::width()
   {
      return m_size.cx;
   }

   int dib::height()
   {
      return m_size.cy;
   }



}