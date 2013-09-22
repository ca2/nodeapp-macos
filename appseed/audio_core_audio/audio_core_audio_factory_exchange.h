#pragma once


namespace multimedia
{


   namespace audio_mmsystem
   {


      class CLASS_DECL_AUDIO_MMSYSTEM factory_exchange :
         virtual public ::ca2::object
      {
      public:


         factory_exchange(sp(base_application) papp);
         virtual ~factory_exchange();

      };


   } // namespace audio_mmsystem


} // namespace multimedia






