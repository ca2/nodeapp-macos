#pragma once

#include <vfw.h>

namespace mac
{

   //////////////////////////////////////////////////////////////////////
   //
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_VMSMAC draw_dib :
      virtual public ::ca::draw_dib
   {
   public:
      HDRAWDIB m_hdrawdib;

      draw_dib(::ca::application * papp);
      virtual ~draw_dib ();

      virtual void * get_os_data();

      WINBOOL open ();
      WINBOOL close ();
      
      WINBOOL Begin ( ::ca::graphics * pdc, int dxDest, int dyDest,
         LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags );
      WINBOOL End ();

      WINBOOL draw(::ca::graphics * pdc, int xDst, int yDst,
         int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits,
         int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );
      WINBOOL draw(::ca::dib * pdib, ::ca::graphics * pdc, int xDst, int yDst,
         int dxDst, int dyDst, UINT wFlags );

      WINBOOL draw(::ca::graphics * pdc, int xDst, int yDst,
         int dxDst, int dyDst, 
          ::ca::dib * dib, int xSrc, int ySrc,
         int dxSrc, int dySrc, UINT wFlags );
      
      LPVOID GetBuffer ( LPBITMAPINFOHEADER lpbi,
         DWORD dwSize, DWORD dwFlags );
      
      WINBOOL ProfileDisplay ( LPBITMAPINFOHEADER lpbi );

      ::ca::palette * get_palette();
      WINBOOL set_palette ( ::ca::palette * ppal );
      WINBOOL ChangePalette ( ::ca::draw_dib * pdd, int iStart, int iLen,
         LPPALETTEENTRY lppe );
      UINT Realize ( ::ca::graphics * pdc, WINBOOL fBackground );

      WINBOOL Start ( LONG rate );
      WINBOOL Stop ();
      WINBOOL time ( LPDRAWDIBTIME lpddtime );

   };

} // namespace mac