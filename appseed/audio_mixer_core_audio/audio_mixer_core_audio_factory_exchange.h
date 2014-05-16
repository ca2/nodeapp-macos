#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM factory_exchange :
         virtual public ::ca2::object
      {
      public:


         factory_exchange(sp(::base::application) papp);
         virtual ~factory_exchange();


      };


   } // namespace audio_mixer_audio_core


} // namespace multimedia




