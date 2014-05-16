#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      factory_exchange::factory_exchange(sp(::base::application) papp) :
         element(papp)
      {

         //System.factory().cloneable_large < callback                    >  (System.type_info < ::multimedia::audio_mixer::callback                 > ());
         System.factory().creatable_small < control                     >  (System.type_info < ::multimedia::audio_mixer::control                  > ());
         //System.factory().creatable_small < control_data                >  (System.type_info < ::multimedia::audio_mixer::control_data             > ());
         System.factory().creatable_small < destination                 >  (System.type_info < ::multimedia::audio_mixer::destination              > ());
         System.factory().creatable_small < device                      >  (System.type_info < ::multimedia::audio_mixer::device                   > ());
         System.factory().creatable_small < line_info                   >  (System.type_info < ::multimedia::audio_mixer::line_info                > ());
         System.factory().cloneable_large < audio_mixer                     >  (System.type_info < ::multimedia::audio_mixer::audio_mixer                   > ());
         //System.factory().cloneable_large < section                   >  (System.type_info < ::multimedia::audio_mixer::font                     > ());
         System.factory().creatable_small < source                      >  (System.type_info < ::multimedia::audio_mixer::source                   > ());
         System.factory().creatable_small < thread                      >  (System.type_info < ::multimedia::audio_mixer::thread                   > ());
         /*System.factory().creatable_small < user::label                 >  (System.type_info < ::multimedia::audio_mixer::user::label              > ());
         System.factory().creatable_small < user::control               >  (System.type_info < ::multimedia::audio_mixer::user::control            > ());
         System.factory().creatable_small < user::level_control         >  (System.type_info < ::multimedia::audio_mixer::user::level_control      > ());
         System.factory().creatable_small < user::toggle_control        >  (System.type_info < ::multimedia::audio_mixer::user::toggle_control     > ());*/

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace audio_core_audio


} // namespace multimedia


extern "C"
void ca2_factory_exchange(sp(::base::application) papp)
{
   ::multimedia::audio_mixer_audio_core::factory_exchange factoryexchange(papp);
}



