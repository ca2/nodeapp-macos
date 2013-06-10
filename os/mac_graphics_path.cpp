#include "framework.h"


namespace mac
{
   
   
   
   
   graphics_path::graphics_path(::ca::application * papp) :
   ca(papp)
   {
      
      m_pospath = NULL;
      
   }
   
   graphics_path::~graphics_path()
   {
      
      if(m_pospath != NULL)
      {
         
         delete m_pospath;
         
      }
      
   }
   
   
   bool graphics_path::internal_begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
   {
      
      m_pospath->begin_figure(bFill, efillmode);
      
      return true;
      
   }
   
   
   bool graphics_path::internal_end_figure(bool bClose)
   {
      
      m_pospath->end_figure(bClose);
      
      return true;
      
   }
   
   bool graphics_path::internal_add_arc(const RECT & rect, int iStart, int iAngle)
   {
      
      m_pospath->add_arc(rect, iStart, iAngle);
      
      return true;
      
   }
   
   
   bool graphics_path::internal_add_line(int x1, int y1, int x2, int y2)
   {
      
      return m_pospath->add_line(x1, y1, x2, y2);
      
   }
   
   
   bool graphics_path::internal_add_line(int x, int y)
   {
      
      return m_pospath->add_line(x, y);
      
   }
   
   
   bool graphics_path::internal_add_move(int x, int y)
   {
      
      end_figure(false);
      
      return m_pospath->add_line(x, y);
      
   }
   
   
   
   void * graphics_path::detach()
   {
      
      void * ppath = get_os_data();
      
      m_pospath->m_ppath = NULL;
      
      delete m_pospath;
      
      m_pospath = NULL;
      
      return ppath;
      
   }
   
   
   void * graphics_path::get_os_data()
   {
      
      defer_update();
      
      if(m_pospath == NULL)
         return NULL;
      
      return m_pospath->m_ppath;
         
      
   }
   
   
   bool graphics_path::update()
   {
      
      if(m_pospath != NULL)
      {
         
         delete m_pospath;
         
      }
      
      m_pospath = new os_simple_path();
      
      for(int32_t i = 0; i < m_elementa.get_count(); i++)
      {
         
         set(m_elementa[i]);
         
      }
      
      return true;
      
   }

   
   bool graphics_path::set(const ::ca::graphics_path::element & e)
   {
      
      switch(e.m_etype)
      {
         case ::ca::graphics_path::element::type_move:
            set(e.m_move);
            break;
         case ::ca::graphics_path::element::type_arc:
            set(e.m_arc);
            break;
         case ::ca::graphics_path::element::type_line:
            set(e.m_line);
            break;
         case ::ca::graphics_path::element::type_end:
            internal_end_figure(e.m_end.m_bClose);
            break;
         default:
            throw "unexpected simple os graphics element type";
      }
      
      return false;
      
   }
   
   
   bool graphics_path::set(const ::ca::graphics_path::arc & arc)
   {
   
      rect rect;
      rect.left = arc.m_xCenter - arc.m_dRadiusX;
      rect.right = arc.m_xCenter + arc.m_dRadiusX;
      rect.top = arc.m_yCenter - arc.m_dRadiusY;
      rect.bottom = arc.m_yCenter + arc.m_dRadiusY;
      
      return internal_add_arc(rect, arc.m_dAngle1, arc.m_dAngle2);
      
   }
   
   
   bool graphics_path::set(const ::ca::graphics_path::move & move)
   {
      
      return internal_add_move(move.m_x, move.m_y);
      
   }
   
   bool graphics_path::set(const ::ca::graphics_path::line & line)
   {
      
      return internal_add_line(line.m_x, line.m_y);
      
   }
   
   
} // namespace metrowin




