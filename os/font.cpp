#include "framework.h"


namespace mac
{
   
   
   font::font(::ca::application * papp) :
   ca(papp)
   {
      
   }
   
   
   font::~font()
   {
      
   }
   
   
   void font::dump(dump_context & dumpcontext) const
   {
      
      ::ca::font::dump(dumpcontext);
      
   }
   
   
   void * font::get_os_data() const
   {
      
      throw interface_only_exception(get_app());
      
      return NULL;
      
   }
   
   
} // namespace mac





