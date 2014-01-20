#pragma once



namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D pen :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::pen
   {
   public:
      
      
      
      //int32_t                  m_iStock;
      //int32_t                  m_iStyle;
      //int32_t                  m_iWidth;
      //COLORREF             m_cr;
      
      
      pen(sp(base_application) papp);
      virtual ~pen();
      /*virtual void construct(int32_t nPenStyle, double nWidth, COLORREF crColor);
       virtual void construct(int32_t nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int32_t nStyleCount = 0, const DWORD* lpStyle = NULL);
       bool CreatePen(int32_t nPenStyle, double nWidth, COLORREF crColor);
       bool CreatePen(int32_t nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int32_t nStyleCount = 0, const DWORD* lpStyle = NULL);*/
      
      
      //      virtual void * get_os_data() const;
      
      
      virtual void dump(dump_context & dumpcontext) const;
      
   };
   
   
} // namespace draw2d_quartz2d





