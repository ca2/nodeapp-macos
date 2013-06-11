#pragma once


namespace mac
{

   
   class CLASS_DECL_mac brush : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::brush
   {
   public:
      
      
      CGGradientRef     m_gradient;
      CGColorRef        m_color;
      CGColorSpaceRef   m_colorspace;
      
      
      brush(::ca::application * papp);
      virtual ~brush();
      
      
      virtual void * get_os_data() const;
      
      virtual bool create();

      virtual bool destroy();
      
      virtual void dump(dump_context & dumpcontext) const;
      

   };


} // namespace mac





