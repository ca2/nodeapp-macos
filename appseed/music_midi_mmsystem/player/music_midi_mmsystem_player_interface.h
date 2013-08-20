#pragma once


namespace music
{


   namespace midi_mmsystem
   {


      namespace player
      {



         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM player_interface :
            virtual public callback,
            virtual public ::music::midi::player::player_interface
         {
         public:


            player_interface(sp(::ca2::application) papp);
            virtual ~player_interface();


            virtual bool OnOpenMidiPlayer();


            virtual bool Initialize(sp(::music::midi::midi) pcentral);
            virtual bool Finalize();


            virtual bool OpenMidiPlayer();

            virtual void OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata);

         };


      } // namespace player


   } // namespace midi_mmsystem


} // namespace music


