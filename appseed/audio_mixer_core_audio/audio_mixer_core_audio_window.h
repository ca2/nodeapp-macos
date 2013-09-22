#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class audio_mixer;


      class window : 
         public ::user::interaction
      {
      public:


         ::multimedia::audio_mixer::audio_mixer                    * m_pmixer;


         window(sp(base_application) papp);
         virtual ~window();


         void install_message_handling(::message::dispatch * pinterface);


         DECL_GEN_SIGNAL(_001OnMixerControlChange)
            DECL_GEN_SIGNAL(_001OnMixerLineChange)


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia



