#include "StdAfx.h"

namespace win
{

   factory_exchange::factory_exchange(::ca::application * papp) :
      ca(papp)
   {
      System.factory().cloneable_large < WinStdioFile         >  (typeid(::ex1::text_file        ));
      System.factory().cloneable_large < WinFile              >  (typeid(::ex1::file             ));
      System.factory().cloneable_large < WinFileSet           >  (typeid(::ex2::file_set         ));
      System.factory().cloneable < WinFileSystem        >  (typeid(::ex1::file_system      ), 1);
      System.factory().cloneable_small < WinFileException     >  (typeid(::ex1::file_exception   ));
      System.factory().cloneable < WinResource          >  (typeid(::ex1::resource         ), 1);
      System.factory().cloneable < application          >  (typeid(::ex2::application      ), 1);
      System.factory().cloneable < dir                  >  (typeid(::ca::dir::system            ), 1);
      System.factory().cloneable_small < folder_watch         >  (typeid(::ex2::folder_watch     ));
      System.factory().cloneable_large < dib                  >  (typeid(::ca::dib               ));
      System.factory().cloneable_large < graphics             >  (typeid(::ca::graphics          ));
      System.factory().cloneable_large < bitmap               >  (typeid(::ca::bitmap            ));
      System.factory().cloneable_large < pen                  >  (typeid(::ca::pen               ));
      System.factory().cloneable_large < brush                >  (typeid(::ca::brush             ));
      System.factory().cloneable_large < palette              >  (typeid(::ca::palette           ));
      System.factory().cloneable_large < rgn                  >  (typeid(::ca::rgn               ));
      System.factory().cloneable_large < font                 >  (typeid(::ca::font              ));
      System.factory().creatable < window_draw          >  (typeid(::ca::window_draw       ), 1);
      System.factory().creatable_large < thread               >  (typeid(::ca::thread            ));
      System.factory().creatable_large < window               >  (typeid(::ca::window            ));
      System.factory().cloneable_small < draw_dib             >  (typeid(::ca::draw_dib          ));
      System.factory().creatable < osi                  >  (typeid(::ca::osi               ), 1);
      System.factory().creatable < port_forward         >  (typeid(::ca4::port_forward            ), 1);
      ::win::dib::s_initialize();
   }

   factory_exchange::~factory_exchange()
   {
   }

} // namespace win



void ca2_factory_exchange(::ca::application * papp)
{
   win::factory_exchange factoryexchange(papp);
}