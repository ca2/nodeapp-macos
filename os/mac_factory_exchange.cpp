#include "framework.h"


namespace mac
{

   
   factory_exchange::factory_exchange(::ca::application * papp) :
      ca(papp)
   {
      
      System.factory().cloneable_large < stdio_file           >  (typeid(::ex1::text_file        ));
      System.factory().cloneable_large < file                 >  (typeid(::ex1::file             ));
      System.factory().cloneable_large < file_set             >  (typeid(::ex2::file_set         ));
      System.factory().cloneable < file_system                >  (typeid(::ca::file::system      ), 1);
//    System.factory().cloneable_small < file_exception       >  (typeid(::ex1::file_exception   ));
//    System.factory().cloneable <    WinResource             >  (typeid(::ex1::resource         ), 1);
      System.factory().cloneable < application                >  (typeid(::ex2::application      ), 1);
      System.factory().cloneable < dir                        >  (typeid(::ca::dir::system       ), 1);
//    System.factory().cloneable_small < folder_watch         >  (typeid(::ex2::folder_watch     ));
      System.factory().cloneable_large < dib                  >  (typeid(::ca::dib               ));
      System.factory().cloneable_large < graphics             >  (typeid(::ca::graphics          ));
      System.factory().cloneable_large < bitmap               >  (typeid(::ca::bitmap            ));
      System.factory().cloneable_large < pen                  >  (typeid(::ca::pen               ));
      System.factory().cloneable_large < brush                >  (typeid(::ca::brush             ));
      System.factory().cloneable_large < palette              >  (typeid(::ca::palette           ));
      System.factory().cloneable_large < region               >  (typeid(::ca::region            ));
      System.factory().cloneable_large < font                 >  (typeid(::ca::font              ));
      System.factory().creatable < window_draw                >  (typeid(::ca::window_draw       ), 1);
      System.factory().creatable_large < thread               >  (typeid(::ca::thread            ));
      System.factory().creatable_large < window               >  (typeid(::ca::window            ));
//    System.factory().cloneable_small < draw_dib             >  (typeid(::ca::draw_dib          ));
      System.factory().creatable < os                         >  (typeid(::ca::os                ), 1);
      System.factory().creatable < port_forward               >  (typeid(::ca4::port_forward     ), 1);
      System.factory().creatable < crypt                      >  (typeid(::ca4::crypt            ), 1);
      System.factory().creatable < copydesk                   >  (typeid(::ca4::copydesk         ), 1);
      
      ::mac::dib::s_initialize();
      
   }

   factory_exchange::~factory_exchange()
   {
   }

} // namespace mac



extern "C" void ca2_factory_exchange(::ca::application * papp)
{
   mac::factory_exchange factoryexchange(papp);
}