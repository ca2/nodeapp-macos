#pragma once

namespace mac
{

   class CLASS_DECL_VMSMAC palette : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::palette
   {
   public:
      static palette* PASCAL from_handle(::ca::application * papp, HPALETTE hPalette);

      palette(::ca::application * papp);
      WINBOOL CreatePalette(LPLOGPALETTE lpLogPalette);
      WINBOOL CreateHalftonePalette(::ca::graphics * pgraphics);

   // Attributes
      operator HPALETTE() const;
      int GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);

   // Operations
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      WINBOOL ResizePalette(UINT nNumEntries);

   // Implementation
      virtual ~palette();
   };

} // namespace mac