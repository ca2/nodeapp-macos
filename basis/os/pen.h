#pragma once

namespace win
{

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::graphics_object subclasses (drawing tools)

   class CLASS_DECL_VMSWIN pen : 
      virtual public ::win::graphics_object,
      virtual public ::ca::pen
   {
   public:
      static pen* PASCAL from_handle(::ca::application * papp, HPEN hPen);

      pen(::ca::application * papp);
      virtual void construct(int nPenStyle, int nWidth, COLORREF crColor);
      virtual void construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL);
      BOOL CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
      BOOL CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL);
      BOOL CreatePenIndirect(LPLOGPEN lpLogPen);

   // Attributes
      operator HPEN() const;
      int GetLogPen(LOGPEN* pLogPen);
      int GetExtLogPen(EXTLOGPEN* pLogPen);

   // Implementation
   public:
      virtual ~pen();
   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace win