#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   brush::brush(sp(::ca2::application) papp) :
      ca2(papp)
   {
      
      m_colorspace = NULL;
      
      m_color = NULL;
      
      m_gradient = NULL;
      
   }
   
   
   brush::~brush()
   {
   }
   
   
   
   void brush::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);
      
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
   
   
   bool brush::destroy()
   {
      
      if(m_gradient != NULL)
      {
         
         CGGradientRelease(m_gradient);
         
         m_gradient = NULL;
         
      }
      
      if(m_color != NULL)
      {
         
         CGColorRelease(m_color);
         
         m_color = NULL;
         
      }
      
      if(m_colorspace != NULL)
      {
         
         CGColorSpaceRelease(m_colorspace);
         
         m_colorspace = NULL;
         
      }
      
      return true;
      
   }

   
   bool brush::create()
   {
      
      
      if(m_etype == type_linear_gradient_point_color)
      {
         CGFloat locations[2];
         CGFloat components[8];
         
         m_colorspace= CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         components[0] = GetRValue(m_cr1);
         components[1] = GetGValue(m_cr1);
         components[2] = GetBValue(m_cr1);
         components[3] = GetAValue(m_cr1);
         components[4] = GetRValue(m_cr2);
         components[5] = GetGValue(m_cr2);
         components[6] = GetBValue(m_cr2);
         components[7] = GetAValue(m_cr2);
         
         locations[0] = 0.0;
         locations[1] = 1.0;
         
         m_gradient = CGGradientCreateWithColorComponents(m_colorspace, components, locations, 2);
         
      }
      else if(m_etype == type_solid)
      {

         CGFloat components[4];
         
         m_colorspace= CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         components[0] = GetRValue(m_cr);
         components[1] = GetGValue(m_cr);
         components[2] = GetBValue(m_cr);
         components[3] = GetAValue(m_cr);
         
         m_color = CGColorCreate(m_colorspace, components);
         
      }
      
      
      return true;
      
   }
   
   
   void * brush::get_os_data() const
   {
      
      defer_update();
      
      if(m_etype == type_null)
      {
         return NULL;
      }
      else if(m_etype == type_linear_gradient_point_color)
      {
         return m_gradient;
      }
      else if(m_etype == type_solid)
      {
         return m_color;
      }
      else
      {
         return NULL;
      }
   
      
   }
   
   
} // namespace draw2d_quartz2d



