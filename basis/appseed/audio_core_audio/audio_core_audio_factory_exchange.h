#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {


      class CLASS_DECL_AUDIO_CORE_AUDIO factory_exchange :
         virtual public ::object
      {
      public:


         factory_exchange(sp(base_application) papp);
         virtual ~factory_exchange();

      };


   } // namespace audio_core_audio


} // namespace multimedia






