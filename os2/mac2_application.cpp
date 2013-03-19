#include "framework.h"


namespace mac2
{


   application::application(::ca::application * papp) :
      ca(papp)
   {

      m_bLicense = false;

   }

   application::~application()
   {

   }



   ::user::printer * application::get_printer(const char * pszDeviceName)
   {
      
      ::mac2::printer * pprinter = new ::mac2::printer(get_app());
      
      if(!pprinter->open(pszDeviceName))
      {
         
         delete pprinter;
         
         return NULL;
         
      }
      
      return pprinter;
      
   }


} // namespace mac2
