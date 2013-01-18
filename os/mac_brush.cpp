#include "framework.h"


namespace mac
{
   
   
   brush::brush(::ca::application * papp) :
   ca(papp)
   {
      
      m_iStock = -1;
      
      m_etype = type_solid;
      
      m_cr = 0;
      
   }
   
   
   brush::~brush()
   {
   }
   
   //bool brush::CreateSolidBrush(COLORREF crColor)
   //{
   
   //   if(m_pbrush != NULL)
   //   {
   //      delete m_pbrush;
   //   }
   
   //   m_pbrush = new Gdiplus::SolidBrush(Gdiplus::Color(GetAValue(crColor), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor)));
   
   //   return m_pbrush != NULL;
   //
   //}
   
   // bool brush::CreateHatchBrush(int32_t nIndex, COLORREF crColor)
   // {
   //    //return Attach(::CreateHatchBrush(nIndex, crColor));
   //    return FALSE;
   // }
   //    bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
   //  {
   //return Attach(::CreateBrushIndirect(lpLogBrush));
   //   return FALSE;
   //}
   //bool brush::CreatePatternBrush(::ca::bitmap* pBitmap)
   //{
   //   //return Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data()));
   //   return FALSE;
   //}
   //bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
   //{
   //   //return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
   //   return FALSE;
   //}
   //bool brush::CreateSysColorBrush(int32_t nIndex)
   //{
   //   //return Attach(::GetSysColorBrush(nIndex));
   //   return FALSE;
   
   //}
   /*    int32_t brush::GetLogBrush(LOGBRUSH* pLogBrush)
    {
    //ASSERT(get_os_data() != NULL);
    //return ::GetObject(get_os_data(), sizeof(LOGBRUSH), pLogBrush);
    return FALSE;
    }*/
   
   
   //   void brush::construct(COLORREF crColor)
   //   {
   ////      if (!Attach(::CreateSolidBrush(crColor)))
   //  //       throw resource_exception();
   //   }
   //
   //   void brush::construct(int32_t nIndex, COLORREF crColor)
   //   {
   //    //  if (!Attach(::CreateHatchBrush(nIndex, crColor)))
   //      //   throw resource_exception();
   //   }
   //
   //   void brush::construct(::ca::bitmap* pBitmap)
   //   {
   //      //ASSERT_VALID(pBitmap);
   //
   //      //if (!Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())))
   //        // throw resource_exception();
   //   }
   //
   //   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
   //   {
   //      //ASSERT(hPackedDIB != NULL);
   //      //const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
   //      //ASSERT(lpPackedDIB != NULL);
   //      //bool bResult = Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
   //      //::GlobalUnlock(hPackedDIB);
   //      //return bResult;
   //      return FALSE;
   //   }
   
   
   void brush::dump(dump_context & dumpcontext) const
   {
      ::ca::graphics_object::dump(dumpcontext);
      
      //if (get_os_data() == NULL)
      // return;
      
      /*      LOGBRUSH lb;
       VERIFY(GetObject(sizeof(lb), &lb));
       dumpcontext << "lb.lbStyle = " << lb.lbStyle;
       dumpcontext << "\nlb.lbHatch = " << lb.lbHatch;
       dumpcontext << "\nlb.lbColor = " << (void *)(dword_ptr)lb.lbColor;
       
       dumpcontext << "\n";
       */
   }
   
   
   
   void * brush::get_os_data() const
   {
      
      if(!m_bUpdated)
      {
         if(m_etype == type_solid)
         {
            
            ((brush *) this)->m_iStock = -1;
            
            ((brush *) this)->m_etype = type_solid;
            
         }
         else if(m_etype == type_linear_gradient_point_color)
         {
            /*
             ((brush *) this)->m_pbrush = new Gdiplus::LinearGradientBrush(
             Gdiplus::Point(m_pt1.x, m_pt1.y),
             Gdiplus::Point(m_pt2.x, m_pt2.y),
             Gdiplus::Color(GetAValue(m_cr1), GetRValue(m_cr1), GetGValue(m_cr1), GetBValue(m_cr1)),
             Gdiplus::Color(GetAValue(m_cr2), GetRValue(m_cr2), GetGValue(m_cr2), GetBValue(m_cr2)));
             */
         }
         else
         {
            
            ((brush *) this)->m_iStock = -1;
            
            ((brush *) this)->m_etype = type_solid;
            
         }
      }
      
      ((brush *) this)->m_bUpdated = true;
      
      return (void *) (brush*) this;
      
   }
   
   
} // namespace mac



