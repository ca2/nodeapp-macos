#pragma once


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D font :
      virtual public ::draw2d::font
   {
   public:
      
      
      font(sp(base_application) papp);
      virtual ~font();
      
      
      virtual void * get_os_data() const;
      
      virtual void dump(dump_context & dumpcontext) const;
      
      
   };
   
   
} // namespace draw2d_quartz2d



