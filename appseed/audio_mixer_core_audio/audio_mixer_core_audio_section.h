#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM section :
         virtual public ::ca2::section,
         virtual public ::user::interaction
      {
      public:



         enum EIds
         {

            IdsMuteAll,
            IdsMute

         };


         section(sp(::base::application) papp);
         virtual ~section();


         virtual bool initialize1();



         bool initialize();


         bool finalize();





      };


   } // namespace mixguserbase


} // namespace multimedia






