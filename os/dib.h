#pragma once

namespace win
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_VMSWIN dib :
      virtual public ::ca::dib
   {
   public:

      static float Cosines[360];
      static float Sines[360];
      static __int64 CosN[360]; // * 1 << 31
      static __int64 SinN[360]; 
      static __int64 Cos10N[10]; // until 10 degress
      static __int64 Sin10N[10]; // more precision * 1 << 34
      static double dPi;

      COLORREF *           m_pcolorref;
      BITMAPINFO           m_info;
      ::ca::bitmap_sp      m_spbitmap;
      ::ca::graphics_sp    m_spgraphics;
      class size           m_size;
      HBITMAP              m_hbitmapOriginal;

      virtual ::ca::graphics * get_graphics();
      virtual ::ca::bitmap_sp get_bitmap();
      virtual ::ca::bitmap_sp detach_bitmap();


      virtual COLORREF * get_data();

      dib(::ca::application * papp);
      virtual void construct(int cx, int cy);
      virtual ~dib();

      static void s_initialize();
      void stretch_dib(::ca::dib * pdib);

      bool dc_select(bool bSelect = true);

      COLORREF GetAverageColor();
      bool Blend(::ca::dib *pdib, ::ca::dib * pdibA, int A);
      bool color_blend(COLORREF cr, BYTE bAlpha);
      void BitBlt(::ca::dib * pdib, int op);
      int cos(int i, int iAngle);
      int sin(int i, int iAngle);
      int cos10(int i, int iAngle);
      int sin10(int i, int iAngle);

      bool is_rgb_black();
      void xor(::ca::dib * pdib);

      void ToAlpha(int i);
      void ToAlphaAndFill(int i, COLORREF cr);
      void GrayToARGB(COLORREF cr);

      void from_alpha();
      void mult_alpha();

      void rotate(::ca::dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      void rotate(::ca::dib * pdib, double dAngle, double dScale);
      void Rotate034(::ca::dib * pdib, double dAngle, double dScale);


      void SetIconMask(::visual::icon * picon, int cx, int cy);
      void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int x, int y, int iRadius);
      void RadialFill(
         BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
         BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
         int x, int y, int iRadius);

      DWORD GetPixel(int x, int y);
      void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      void transparent_color(color color);
      

      BOOL create(class size size);
      BOOL create(int iWidth, int iHeight);
      BOOL create(::ca::graphics * pdc);
      BOOL Destroy();


      void DivideRGB(int iDivide);
      void DivideARGB(int iDivide);
      void DivideA(int iDivide);

      bool from(::ca::graphics * pdc);
      bool from(point ptDest, ::ca::graphics * pdc, point pt, class size sz);

      bool to(::ca::graphics * pgraphics, point pt, class size size, point ptSrc);
      
      virtual void fill_channel(int C, visual::rgba::echannel echannel);
      void Fill (int A, int R, int G, int B );
      void Fill ( int R, int G, int B );
      void FillGlass ( int R, int G, int B, int A );
      void FillStippledGlass ( int R, int G, int B );
      void Invert();
      void channel_invert(visual::rgba::echannel echannel);
      void channel_multiply(visual::rgba::echannel echannel, double dRate);

      void Map (int ToRgb, int FromRgb );

      void copy( ::ca::dib *dib );
      void Paste ( ::ca::dib *dib );

      void Blend ( ::ca::dib *dib, int A );
      void Darken ( ::ca::dib *dib );
      void Difference ( ::ca::dib *dib );
      void Lighten ( ::ca::dib *dib );
      void Multiply ( ::ca::dib *dib );
      void Screen ( ::ca::dib *dib );

      void copy ( ::ca::dib *dib, int x, int y );
      void PasteRect ( ::ca::dib *dib, int x, int y );

      void FillRect ( int x, int y, int w, int h, int R, int G, int B );
      void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
      void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );
      
      void BlendRect ( ::ca::dib *dib, int x, int y, int A );
      void DarkenRect ( ::ca::dib *dib, int x, int y );
      void DifferenceRect ( ::ca::dib *dib, int x, int y );
      void LightenRect ( ::ca::dib *dib, int x, int y );
      void MultiplyRect ( ::ca::dib *dib, int x, int y );
      void ScreenRect ( ::ca::dib *dib, int x, int y );

      void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
      void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );

      void create_frame(class size size, int iFrameCount);
      void set_frame2(void * lpdata, int iFrame, int iFrameCount);
      void set_frame1(void * lpdata, int iFrame, int iFrameCount);
      void get_frame(void * lpdata, int iFrame, int iFrameCount);
      void xor_dib_frame2(void * lpdata, int iFrame, int iFrameCount);


      int width();
      int height();
      double pi();
   };

} // namespace win