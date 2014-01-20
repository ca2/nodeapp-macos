#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      factory_exchange::factory_exchange(sp(base_application) papp) :
         element(papp)
      {

         System.factory().cloneable_large < wave_in               >  (System.type_info < ::multimedia::audio::wave_in                  > (), true, true);
         System.factory().cloneable_large < wave_out              >  (System.type_info < ::multimedia::audio::wave_out                 > (), true, true);

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace audio_core_audio


} // namespace multimedia

extern "C"
void ca2_factory_exchange(sp(base_application) papp)
{

   ::multimedia::audio_core_audio::factory_exchange factoryexchange(papp);

}









