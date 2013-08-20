#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM thread :
         public ::ca2::thread,
         public ::database::client
      {
      public:


         enum e_message
         {
            MessageMixerThread = WM_USER + 113,
         };

         bool                                m_bPendingShowCommand;

         sp(::multimedia::audio_mixer::section) m_psection;


         thread(sp(::ca2::application) papp);
         virtual ~thread();


         static LRESULT CALLBACK MessageProc(
            int32_t code,       // hook code
            WPARAM wParam,  // undefined
            LPARAM lParam   // address of structure with message data
            );


         void install_message_handling(::ca2::message::dispatch * pinterface);

         virtual bool initialize_instance();
         virtual int32_t exit_instance();
         virtual bool on_idle(LONG lCount);
         virtual void pre_translate_message(::ca2::signal_object * pobj);


         DECL_GEN_SIGNAL(OnMixerMessage)
            DECL_GEN_SIGNAL(OnVmsmException)
            DECL_GEN_SIGNAL(OnUserMessage)


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia





