#pragma once


namespace music
{


   namespace midi_mmsystem
   {


      namespace player
      {


         class callback;


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM window :
            public ::user::interaction
         {
         public:


            ::music::midi::player::callback_interface * m_pcallback;


            window(sp(::ca2::application) papp);
            virtual ~window();

            ::music::midi::player::callback_interface * get_callback();

            using ::user::interaction::create;
            virtual bool create();

            void set_callback(::music::midi::player::callback_interface * pcallback);

            void install_message_handling(::ca2::message::dispatch * pinterface);

            DECL_GEN_SIGNAL(_001OnNotifyEvent)
               DECL_GEN_SIGNAL(_001OnMmsgDone)
               DECL_GEN_SIGNAL(_001OnUserMessage)
               DECL_GEN_SIGNAL(_001OnApp3388Message)
         };

      
      } // namespace player


   } // namespace midi_mmsystem


} // namespace music



