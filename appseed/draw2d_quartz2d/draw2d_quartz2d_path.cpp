#include "framework.h"


#define MATH_PI 3.14159265359


namespace draw2d_quartz2d
{
   
   
   path::path(sp(::base::application) papp) :
      ::element(papp)
   {
      
      m_path = NULL;
      
      m_bBegin = true;
      
   }
   
   
   path::~path()
   {
      
      
   }
   
   
   bool path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_end_figure(bool bClose)
   {
      
      if(bClose)
      {
         
         CGPathCloseSubpath(m_path);
         
      }
      
      m_bBegin = true;
      
      return true;
      
   }
   
   bool path::internal_add_arc(const RECT & rect, int iStart, int iAngle)
   {
      
      CGFloat d1 = rect.right - rect.left;
      
      if(d1 <= 0)
         return true;
      
      CGFloat d2 = rect.bottom - rect.top;
      
      if(d2 <= 0)
         return true;
      
      CGAffineTransform t = CGAffineTransformMakeScale(1.0, d2 / d1);
      CGFloat x = (rect.right + rect.left) / 2.0;
      CGFloat y = (rect.bottom + rect.top) / 2.0;
      CGFloat x1 = x + d1 * sin(iStart * MATH_PI / 180.0f);
      CGFloat y1 = y + d1 * cos(iStart * MATH_PI / 180.0f);
      CGFloat x2 = x + d1 * sin((iStart + iAngle) * MATH_PI / 180.0f);
      CGFloat y2 = y + d1 * cos((iStart + iAngle) * MATH_PI / 180.0f);
      
      if(CGPathIsEmpty(m_path))
      {

         internal_add_move(x1, y1);
         
      }
      
      CGPathAddArcToPoint(m_path, &t, x1, y1, x2, y2, d1);
      
      return true;
      
   }
   
   
   bool path::internal_add_line(int x1, int y1, int x2, int y2)
   {

      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x1, y1);
         
      }
      else
      {
      
         CGPathAddLineToPoint(m_path, NULL, x1, y1);
         
      }

      CGPathAddLineToPoint(m_path, NULL, x2, y2);
      
      return true;
      
   }
   
   
   bool path::internal_add_line(int x, int y)
   {
      
      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x, y);
         
      }
      else
      {
         
         CGPathAddLineToPoint(m_path, NULL, x, y);
         
      }
      
      return true;
      
   }
   
   
   bool path::internal_add_move(int x, int y)
   {

      CGPathMoveToPoint(m_path, NULL, x, y);
      
      m_bBegin = false;
      
      return true;
      
   }
   
   
   
   void * path::detach()
   {
      
      void * ppath = get_os_data();
      
      m_path = NULL;
      
      return ppath;
      
   }
   
   
   void * path::get_os_data() const
   {
      
      defer_update();
      
      return m_path;
         
      
   }
   
   bool path::destroy()
   {
      
      if(m_path != NULL)
      {
         
         CGPathRelease(m_path);
         
         m_path = NULL;
         
      }
      
      return true;
      
   }
   
   
   bool path::create()
   {
      
      m_path = CGPathCreateMutable();
      
      for(int32_t i = 0; i < m_elementa.get_count(); i++)
      {
         
         set(m_elementa[i]);
         
      }
      
      return true;
      
   }

   
   bool path::set(const ::draw2d::path::element & e)
   {
      
      switch(e.m_etype)
      {
         case ::draw2d::path::element::type_move:
            set(e.m_move);
            break;
         case ::draw2d::path::element::type_arc:
            set(e.m_arc);
            break;
         case ::draw2d::path::element::type_line:
            set(e.m_line);
            break;
         case ::draw2d::path::element::type_end:
            internal_end_figure(e.m_end.m_bClose);
            break;
         default:
            throw "unexpected simple os graphics element type";
      }
      
      return false;
      
   }
   
   
   bool path::set(const ::draw2d::path::arc & arc)
   {
   
      rect rect;
      rect.left = arc.m_xCenter - arc.m_dRadiusX;
      rect.right = arc.m_xCenter + arc.m_dRadiusX;
      rect.top = arc.m_yCenter - arc.m_dRadiusY;
      rect.bottom = arc.m_yCenter + arc.m_dRadiusY;
      
      return internal_add_arc(rect, arc.m_dAngle1, arc.m_dAngle2);
      
   }
   
   
   bool path::set(const ::draw2d::path::move & move)
   {
      
      return internal_add_move(move.m_x, move.m_y);
      
   }
   
   bool path::set(const ::draw2d::path::line & line)
   {
      
      return internal_add_line(line.m_x, line.m_y);
      
   }
   
   
} // namespace metrowin




