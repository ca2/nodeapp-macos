#pragma once


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D path :
      virtual public ::draw2d::path,
      virtual public object
   {
   public:
      
      
      CGMutablePathRef        m_path;
      bool                    m_bBegin;
      
      
      path(sp(base_application) papp);
      virtual ~path();
      
      
      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);
      virtual bool internal_add_arc(const RECT & rect, int iStart, int iAngle);
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x, int y);
      
      virtual void * get_os_data() const;
      
      virtual bool create();

      virtual bool destroy();

      virtual void * detach();
      
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
   
      
      
      
   };
   
   
} // namespace draw2d_quartz2d





