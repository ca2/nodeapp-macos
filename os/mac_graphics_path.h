#pragma once


namespace mac
{
   
   
   class CLASS_DECL_mac graphics_path :
      virtual public ::ca::graphics_path,
      virtual public graphics_object
   {
   public:
      
      
      os_simple_path * m_pospath;
      
      
      graphics_path(::ca::application * papp);
      virtual ~graphics_path();
      
      
      virtual bool internal_begin_figure(bool bFill, ::ca::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);
      
      
      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();
      
      virtual bool internal_add_arc(const RECT & rect, int iStart, int iAngle);
      
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      
      virtual bool internal_add_line(int x, int y);
      
      virtual bool internal_add_move(int x, int y);
      
      //virtual bool internal_add_rect(int x1, int y1, int x2, int y2);
      
      virtual void * get_os_data();
      virtual void * detach();
      
      bool update();
      bool set(const ::ca::graphics_path::element & e);
      bool set(const ::ca::graphics_path::arc & arc);
      bool set(const ::ca::graphics_path::move & move);
      bool set(const ::ca::graphics_path::line & line);
      
      
      
   };
   
   
} // namespace mac



