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

      BOOL CreateSolidBrush(COLORREF crColor);
      BOOL CreateHatchBrush(int nIndex, COLORREF crColor);
      BOOL CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      BOOL CreatePatternBrush(::ca::bitmap* pBitmap);
      BOOL CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      BOOL CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      BOOL CreateSysColorBrush(int nIndex);

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