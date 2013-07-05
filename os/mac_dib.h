#pragma once

namespace mac
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_mac dib :
      virtual public ::ca2::dib
   {
   public:

      static float Cosines[360];
      static float Sines[360];
      static int64_t CosN[360]; // * 1 << 31
      static int64_t SinN[360];
      static int64_t Cos10N[10]; // until 10 degress
      static int64_t Sin10N[10]; // more precision * 1 << 34
      static double dPi;
      
      COLORREF *              m_pcolorref;
      BITMAPINFO              m_info;
      ::ca2::bitmap_sp        m_spbitmap;
      ::ca2::graphics_sp      m_spgraphics;
      class size              m_size;
      bool                    m_bMapped;
      //HBITMAP               m_hbitmapOriginal;
      
      virtual ::ca2::graphics * get_graphics();
      virtual ::ca2::bitmap_sp get_bitmap();
      virtual ::ca2::bitmap_sp detach_bitmap();
      
      
      virtual COLORREF * get_data();
      
      dib(::ca2::application * papp);
      virtual void construct(int32_t cx, int32_t cy);
      virtual ~dib();
      
      static void s_initialize();
      void stretch_dib(::ca2::dib * pdib);
      
      bool dc_select(bool bSelect = true);
      
      COLORREF GetAverageColor();
      bool Blend(::ca2::dib *pdib, ::ca2::dib * pdibA, int32_t A);
      bool color_blend(COLORREF cr, BYTE bAlpha);
      void BitBlt(::ca2::dib * pdib, int32_t op);
      int32_t cos(int32_t i, int32_t iAngle);
      int32_t sin(int32_t i, int32_t iAngle);
      int32_t cos10(int32_t i, int32_t iAngle);
      int32_t sin10(int32_t i, int32_t iAngle);
      
      bool is_rgb_black();
      void _xor(::ca2::dib * pdib);
      
      void ToAlpha(int32_t i);
      void ToAlphaAndFill(int32_t i, COLORREF cr);
      void GrayToARGB(COLORREF cr);
      
      void from_alpha();
      void mult_alpha(::ca2::dib * pdibWork, bool bPreserveAlpha = true);
      void set_rgb(int32_t R, int32_t G, int32_t B);
      
      void rotate(::ca2::dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      void rotate(::ca2::dib * pdib, double dAngle, double dScale);
      void Rotate034(::ca2::dib * pdib, double dAngle, double dScale);
      
      
      void SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy);
      void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int32_t x, int32_t y, int32_t iRadius);
      void RadialFill(
                      BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
                      BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
                      int32_t x, int32_t y, int32_t iRadius);
      
      DWORD GetPixel(int32_t x, int32_t y);
      void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      void transparent_color(color color);
      
      
      bool create(class size size);
      bool create(int32_t iWidth, int32_t iHeight);
      bool create(::ca2::graphics * pdc);
      bool Destroy();
      
      
      void DivideRGB(int32_t iDivide);
      void DivideARGB(int32_t iDivide);
      void DivideA(int32_t iDivide);
      
      bool from(::ca2::graphics * pdc);
      bool from(point ptDest, ::ca2::graphics * pdc, point pt, class size sz);
      
      bool to(::ca2::graphics * pgraphics, point pt, class size size, point ptSrc);
      
      virtual void fill_channel(int32_t C, visual::rgba::echannel echannel);
      void Fill (int32_t A, int32_t R, int32_t G, int32_t B );
      void Fill ( int32_t R, int32_t G, int32_t B );
      void FillGlass ( int32_t R, int32_t G, int32_t B, int32_t A );
      void FillStippledGlass ( int32_t R, int32_t G, int32_t B );
      void Invert();
      void channel_invert(visual::rgba::echannel echannel);
      void channel_multiply(visual::rgba::echannel echannel, double dRate);
      
      void Map (int32_t ToRgb, int32_t FromRgb );
      
      void copy( ::ca2::dib *dib );
      void Paste ( ::ca2::dib *dib );
      
      void Blend ( ::ca2::dib *dib, int32_t A );
      void Darken ( ::ca2::dib *dib );
      void Difference ( ::ca2::dib *dib );
      void Lighten ( ::ca2::dib *dib );
      void Multiply ( ::ca2::dib *dib );
      void Screen ( ::ca2::dib *dib );
      
      void copy ( ::ca2::dib *dib, int32_t x, int32_t y );
      void PasteRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      
      void FillRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B );
      void FillGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B, int32_t A );
      void FillStippledGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B );
      
      void BlendRect ( ::ca2::dib *dib, int32_t x, int32_t y, int32_t A );
      void DarkenRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      void DifferenceRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      void LightenRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      void MultiplyRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      void ScreenRect ( ::ca2::dib *dib, int32_t x, int32_t y );
      
      void Line ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B );
      void LineGlass ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B, int32_t A );
      
      void create_frame(class size size, int32_t iFrameCount);
      void set_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      void set_frame1(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      void get_frame(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      void xor_dib_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      
      
      int32_t width();
      int32_t height();
      double pi();
      
      virtual bool from(::ca2::graphics * pgraphics, FIBITMAP *pfibitmap, bool bUnloadFI);
      
      virtual void map();
      virtual void unmap();
      
      
   };

} // namespace mac