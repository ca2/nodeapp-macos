#pragma once

namespace mac
{

   class CLASS_DECL_mac palette : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::palette
   {
   public:
      
      palette(::ca::application * papp);
      virtual ~palette();
      
      
      //      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      //      bool CreateHalftonePalette(::ca::graphics * pgraphics);
      
      // Attributes
      operator HPALETTE() const;
      int32_t GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors);
      
      // Operations
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                          LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      //      bool ResizePalette(UINT nNumEntries);
      
      // Implementation
   };

} // namespace mac