#include "framework.h"


namespace draw2d_quartz2d
{

   
   factory_exchange::factory_exchange(sp(::base::application) papp) :
      ::element(papp)
   {
      
      System.factory().cloneable_large < dib                   >   (System.type_info < ::draw2d::dib                 > ());
      System.factory().cloneable_large < graphics              >   (System.type_info < ::draw2d::graphics            > ());
      System.factory().cloneable_large < bitmap                >   (System.type_info < ::draw2d::bitmap              > ());
      System.factory().cloneable_large < pen                   >   (System.type_info < ::draw2d::pen                 > ());
      System.factory().cloneable_large < brush                 >   (System.type_info < ::draw2d::brush               > ());
      System.factory().cloneable_large < palette               >   (System.type_info < ::draw2d::palette             > ());
      System.factory().cloneable_large < region                >   (System.type_info < ::draw2d::region              > ());
      System.factory().cloneable_large < font                  >   (System.type_info < ::draw2d::font                > ());
      System.factory().creatable < path                        >   (System.type_info < ::draw2d::path                > (), 1);
      
//      ::draw2d_quartz2d::dib::s_initialize();
      
   }

   factory_exchange::~factory_exchange()
   {
   }

} // namespace draw2d_quartz2d



extern "C" void ca2_factory_exchange(sp(::base::application) papp)
{
   draw2d_quartz2d::factory_exchange factoryexchange(papp);
}