#pragma once



namespace mac
{
   
   
   class CLASS_DECL_mac pen :
   virtual public ::mac::graphics_object,
   virtual public ::ca2::pen
   {
   public:
      
      
      
      //int32_t                  m_iStock;
      //int32_t                  m_iStyle;
      //int32_t                  m_iWidth;
      //COLORREF             m_cr;
      
      
      pen(::ca2::application * papp);
      virtual ~pen();
      /*virtual void construct(int32_t nPenStyle, double nWidth, COLORREF crColor);
       virtual void construct(int32_t nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int32_t nStyleCount = 0, const DWORD* lpStyle = NULL);
       bool CreatePen(int32_t nPenStyle, double nWidth, COLORREF crColor);
       bool CreatePen(int32_t nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int32_t nStyleCount = 0, const DWORD* lpStyle = NULL);*/
      
      
      //      virtual void * get_os_data() const;
      
      
      virtual void dump(dump_context & dumpcontext) const;
      
   };
   
   
} // namespace mac





