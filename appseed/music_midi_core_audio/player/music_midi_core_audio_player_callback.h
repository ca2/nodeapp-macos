#pragma once


namespace music
{


   namespace midi_core_midi
   {


      namespace player
      {


         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI callback :
            virtual public ::music::midi::player::callback_interface
         {
         public:



            friend class window;

            callback(sp(::base::application) papp);
            virtual ~callback();

            virtual bool initialize();
            virtual bool finalize();

            virtual void OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd);
            virtual void OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata); 
            virtual void OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents);


         };


      } // namespace player


   } // namespace midi_core_midi


} // namespace music








