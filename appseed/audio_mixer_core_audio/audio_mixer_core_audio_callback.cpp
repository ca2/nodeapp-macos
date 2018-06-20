#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      callback::callback()
      {

      }


      callback::~callback()
      {

      }


      ::multimedia::audio_mixer::user::level_control * callback::allocate_level_control()
      {

         return NULL;

      }


      ::multimedia::audio_mixer::user::toggle_control * callback::allocate_toggle_control()
      {

         return NULL;

      }


      ::multimedia::audio_mixer::user::label * callback::allocate_label()
      {

         return NULL;

      }


   } // namespace audio_mixer_audio_core


} // namespace multimedia

