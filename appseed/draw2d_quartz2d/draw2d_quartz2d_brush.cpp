#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   brush::brush(sp(base_application) papp) :
      ::element(papp)
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
         
         components[0] = argb_get_r_value(m_cr1) / 255.f;
         components[1] = argb_get_g_value(m_cr1) / 255.f;
         components[2] = argb_get_b_value(m_cr1) / 255.f;
         components[3] = argb_get_a_value(m_cr1) / 255.f;
         components[4] = argb_get_r_value(m_cr2) / 255.f;
         components[5] = argb_get_g_value(m_cr2) / 255.f;
         components[6] = argb_get_b_value(m_cr2) / 255.f;
         components[7] = argb_get_a_value(m_cr2) / 255.f;
         
         locations[0] = 0.0;
         locations[1] = 1.0;
         
         m_gradient = CGGradientCreateWithColorComponents(m_colorspace, components, locations, 2);
         
      }
      else if(m_etype == type_solid)
      {

         CGFloat components[4];
         
         m_colorspace= CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         components[0] = argb_get_r_value(m_cr) / 255.f;
         components[1] = argb_get_g_value(m_cr) / 255.f;
         components[2] = argb_get_b_value(m_cr) / 255.f;
         components[3] = argb_get_a_value(m_cr) / 255.f;
         
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



