#pragma once


namespace draw2d_cocoa
{

   
   class CLASS_DECL_DRAW2D_COCOA brush : 
      virtual public ::draw2d_cocoa::object,
      virtual public ::draw2d::brush
   {
   public:
      
      
      CGGradientRef     m_gradient;
      CGColorRef        m_color;
      CGColorSpaceRef   m_colorspace;
      
      
      brush(::ca2::application * papp);
      virtual ~brush();
      
      
      virtual void * get_os_data() const;
      
      virtual bool create();

      virtual bool destroy();
      
      virtual void dump(dump_context & dumpcontext) const;
      

   };


} // namespace draw2d_cocoa





