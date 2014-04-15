#include "framework.h"


namespace mac
{

   
   factory_exchange::factory_exchange(base_application * papp) :
      element(papp)
   {
      
      System.factory().cloneable_large < stdio_file           >   (System.type_info < ::file::text_buffer     > ());
      System.factory().cloneable_large < file                 >   (System.type_info < ::file::binary_buffer   > ());
      System.factory().creatable_large < file_set             >   (System.type_info < ::file::set             > ());
      System.factory().cloneable < file_system                >   (System.type_info < ::file::system          > (), 1);
//    System.factory().cloneable_small < file_exception       >   (System.type_info < ::file::exception   > ());
//    System.factory().cloneable <    WinResource             >   (System.type_info < ::ca2::resource         > (), 1);
      System.factory().cloneable < application                >   (System.type_info < ::base_application      > (), 1);
      System.factory().cloneable < dir                        >   (System.type_info < ::file::dir::system     > (), 1);
//    System.factory().cloneable_small < folder_watch         >   (System.type_info < ::ca2::folder_watch     > ());
      System.factory().creatable < window_draw                >   (System.type_info < ::user::window_draw     > (), 1);
      System.factory().creatable_large < thread               >   (System.type_info < ::thread                > ());
      System.factory().creatable_large < window               >   (System.type_info < ::window          > ());
      System.factory().creatable < os                         >   (System.type_info < ::core::os              > (), 1);
      System.factory().creatable < port_forward               >   (System.type_info < ::net::port_forward     > (), 1);
      System.factory().creatable < crypto                      >   (System.type_info < ::crypto::crypto           > (), 1);
      System.factory().creatable < copydesk                   >   (System.type_info < ::core::copydesk        > (), 1);
      System.factory().creatable < ::mac2::printer                   >   (System.type_info < ::user::printer        > (), 1);
      
   }

    
   factory_exchange::~factory_exchange()
   {
       
   }

    
} // namespace mac


extern "C" void ca2_factory_exchange(sp(base_application) papp)
{
   mac::factory_exchange factoryexchange(papp);
}