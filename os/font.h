#pragma once

namespace win
{

   class CLASS_DECL_VMSWIN font : 
      virtual public ::win::graphics_object,
      virtual public ::ca::font
   {
   public:
      static font * PASCAL from_handle(::ca::application * papp, HFONT hFont);

      font(::ca::application * papp);
      virtual ~font();

      virtual void font::construct(const ::ca::font & fontParam);

      virtual BOOL CreateFontIndirect(const LOGFONT* lpLogFont);
      virtual BOOL CreateFont(int nHeight, int nWidth, int nEscapement,
            int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
            BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
            BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
            const char * lpszFacename);
      virtual BOOL CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics = NULL);
      virtual BOOL CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics = NULL);

   // Attributes
      operator HFONT() const;
      virtual int GetLogFont(LOGFONT* pLogFont);

      // Implementation
      public:
      #ifdef _DEBUG
         virtual void dump(dump_context & dumpcontext) const;
      #endif
   };

} // namespace win