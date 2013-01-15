#pragma once

namespace mac
{

   class CLASS_DECL_mac brush : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::brush
   {
   public:
      
      
      int32_t                  m_iStyle;
      COLORREF             m_cr;
      int32_t                  m_iStock;
      
      
      //xxx      Gdiplus::Brush * m_pbrush;
      
      
      brush(::ca::application * papp);
      //virtual void construct(COLORREF crColor);                // CreateSolidBrush
      //virtual void construct(int32_t nIndex, COLORREF crColor);    // CreateHatchBrush
      //virtual void construct(::ca::bitmap * pbitmap);                // CreatePatternBrush
      virtual ~brush();
      
      
      virtual void * get_os_data() const;
      
      
      //bool CreateSolidBrush(COLORREF crColor);
      //bool CreateHatchBrush(int32_t nIndex, COLORREF crColor);
      //bool CreatePatternBrush(::ca::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      //bool CreateSysColorBrush(int32_t nIndex);
      
      
      virtual void dump(dump_context & dumpcontext) const;
      

   };


} // namespace mac