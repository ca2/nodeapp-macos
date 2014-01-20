#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   palette::palette(sp(base_application) papp) :
   element(papp)
   {
      
   }
   
   
   palette::~palette()
   {
      
   }
   
   
   // palette
/*   palette::operator HPALETTE() const
   {
      
      //return (HPALETTE)(this == NULL ? NULL : get_os_data());
      
      return NULL;
      
   }
  */ 
   
   /*
    
    palette* PASCAL palette::from_handle(base_application * papp, HPALETTE hPalette)
    {
    
    //return dynamic_cast < palette * > (::win::object::from_handle(papp, hPalette));
    
    return NULL;
    
    }
    
    */
   
   
   /*
    
    WINBOOL palette::CreatePalette(LPLOGPALETTE lpLogPalette)
    {
    
    //   return Attach(::CreatePalette(lpLogPalette));
    
    return FALSE;
    
    }
    
    */
   
   
   
   /*
    
    WINBOOL palette::CreateHalftonePalette(::draw2d::graphics * pgraphics)
    {
    
    //ASSERT(pgraphics != NULL && (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() != NULL);
    //return Attach(::CreateHalftonePalette((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1()));
    
    return FALSE;
    
    }
    
    */
   
   
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
   {
      
      //ASSERT(get_os_data() != NULL);
      //return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);
      
      return 0;
      
   }
   
   
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      
      //ASSERT(get_os_data() != NULL);
      //return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);
      
      return 0;
      
   }
   
   
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      
      //ASSERT(get_os_data() != NULL);
      
      //::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);
      
   }
   
   
   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {
      
      //ASSERT(get_os_data() != NULL);
      
      //return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);
      
      return 0;
      
   }
   
   
   /*
    
    WINBOOL palette::ResizePalette(UINT nNumEntries)
    {
    
    //ASSERT(get_os_data() != NULL);
    
    //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries);
    
    return FALSE;
    
    }
    
    */
   
   
   int32_t palette::GetEntryCount()
   {
      
      //ASSERT(get_os_data() != NULL);
      
      //WORD nEntries;
      
      //::GetObject(get_os_data(), sizeof(WORD), &nEntries); return (int32_t)nEntries;
      
      return 0;
      
   }
   
   
} // namespace draw2d_quartz2d







