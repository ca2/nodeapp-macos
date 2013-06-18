#pragma once


namespace mac
{
   
   
   class CLASS_DECL_mac graphics_path :
      virtual public ::ca2::graphics_path,
      virtual public graphics_object
   {
   public:
      
      
      CGMutablePathRef        m_path;
      bool                    m_bBegin;
      
      
      graphics_path(::ca2::application * papp);
      virtual ~graphics_path();
      
      
      virtual bool internal_begin_figure(bool bFill, ::ca2::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);
      virtual bool internal_add_arc(const RECT & rect, int iStart, int iAngle);
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x, int y);
      
      virtual void * get_os_data() const;
      
      virtual bool create();

      virtual bool destroy();

      virtual void * detach();
      
      bool set(const ::ca2::graphics_path::element & e);
      bool set(const ::ca2::graphics_path::arc & arc);
      bool set(const ::ca2::graphics_path::move & move);
      bool set(const ::ca2::graphics_path::line & line);
   
      
      
      
   };
   
   
} // namespace mac





