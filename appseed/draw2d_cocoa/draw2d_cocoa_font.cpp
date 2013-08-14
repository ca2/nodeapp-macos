#include "framework.h"


namespace draw2d_cocoa
{
   
   
   font::font(sp(::ca2::application) papp) :
   ca2(papp)
   {
      
   }
   
   
   font::~font()
   {
      
   }
   
   
   void font::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::font::dump(dumpcontext);
      
   }
   
   
   void * font::get_os_data() const
   {
      
      throw interface_only_exception(get_app());
      
      return NULL;
      
   }
   
   
} // namespace draw2d_cocoa





