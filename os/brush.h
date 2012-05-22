#pragma once

namespace win
{

   class CLASS_DECL_VMSWIN brush : 
      virtual public ::win::graphics_object,
      virtual public ::ca::brush
   {
   public:
      static brush* PASCAL from_handle(::ca::application * papp, HBRUSH hBrush);

      // Constructors
      brush(::ca::application * papp);
      virtual void construct(COLORREF crColor);                // CreateSolidBrush
      virtual void construct(int nIndex, COLORREF crColor);    // CreateHatchBrush
      virtual void construct(::ca::bitmap * pbitmap);                // CreatePatternBrush

      virtual ~brush();

      WINBOOL CreateSolidBrush(COLORREF crColor);
      WINBOOL CreateHatchBrush(int nIndex, COLORREF crColor);
      WINBOOL CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      WINBOOL CreatePatternBrush(::ca::bitmap* pBitmap);
      WINBOOL CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      WINBOOL CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      WINBOOL CreateSysColorBrush(int nIndex);

      // Attributes
      operator HBRUSH() const;
      int GetLogBrush(LOGBRUSH* pLogBrush);

      // Implementation
   public:
#ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
#endif
   };


} // namespace win