#include "framework.h"



// Note: in separate module so it can be replaced if needed

void CLASS_DECL_mac __abort()
{
   //   TRACE(::ca::trace::category_AppMsg, 0, "__abort called.\n");
   
   __mac_term();
   abort();
}

/////////////////////////////////////////////////////////////////////////////



