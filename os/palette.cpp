#include "StdAfx.h"

namespace win
{

   palette::palette(::ca::application * papp) :
      ca(papp)
   { }
   palette::~palette()
   { }
   // palette
   palette::operator HPALETTE() const
   { 
      return (HPALETTE)(this == NULL ? NULL : get_os_data()); 
   }
   palette* PASCAL palette::from_handle(::ca::application * papp, HPALETTE hPalette)
   { 
      return dynamic_cast < palette * > (::win::graphics_object::from_handle(papp, hPalette)); 
   }
   BOOL palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   { return Attach(::CreatePalette(lpLogPalette)); }
   BOOL palette::CreateHalftonePalette(::ca::graphics * pgraphics)
   { ASSERT(pgraphics != NULL && (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() != NULL); return Attach(
   ::CreateHalftonePalette((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1())); }
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors) const
   { ASSERT(get_os_data() != NULL); return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
   nNumEntries, lpPaletteColors); }
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors)
   { ASSERT(get_os_data() != NULL); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
   nNumEntries, lpPaletteColors); }
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors)
   { ASSERT(get_os_data() != NULL); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
   lpPaletteColors); }
   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   { ASSERT(get_os_data() != NULL); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor); }
   BOOL palette::ResizePalette(UINT nNumEntries)
   { ASSERT(get_os_data() != NULL); return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries); }
   int palette::GetEntryCount()
   { ASSERT(get_os_data() != NULL); WORD nEntries;
   ::GetObject(get_os_data(), sizeof(WORD), &nEntries); return (int)nEntries; }

} // namespace win