#pragma once


#include "music_midi_core_audio_player_callback.h"


namespace music
{


   namespace midi
   {
      
      namespace port
      {


      class sequence_thread;


      namespace player
      {

         class player_callback;
         class player_interface;

         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI player :
            virtual public ::music::midi::player::player
         {
         public:


            player(::aura::application * papp);
            virtual ~player();


            void install_message_routing(::message::sender * pinterface) override;


            bool PlayRate(double dRate = 0.0, uint32_t dwEllapse = 584) override;
            bool Play(imedia_position tkStart, uint32_t dwEllapse = 584) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;
            virtual void pre_translate_message(::message::message * pobj) override;
            void OnMmsgDone(::music::midi::sequence *pSeq) override;
            DECL_GEN_SIGNAL(OnUserMessage);
            void SaveFile(const char * lpszPathName) override;
            void SetPosition(double dRate) override;
            void pause() override;
            void close_file() override;
            void SendReset();
            bool ExecuteCommand(::music::midi::player::e_command ecommand, uint32_t dwEllapse) override;
            virtual void OnMidiOutDeviceChange() override;

            uint32_t GetMidiOutDevice() override;
            void PostNotifyEvent(::music::midi::player::e_notify_event eevent) override;

            imedia_position RateToTicks(double dRate) override;

            bool SetTempoShift(int32_t iTempoShift);

            bool SetMidiOutDevice(uint32_t uiDevice) override;

            //::multimedia::e_result SetInterface(player_interface * pinterface);

            //::multimedia::e_result Initialize(::thread * pthread);

            bool IsPlaying() override;

            void PostGMReset() override;
            void PostTempoChange() override;
            void SendTempoChange() override; // verificar


            DECL_GEN_SIGNAL(OnNotifyEvent);
            DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone);
            DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB);

            // midi central listener
            DECL_GEN_SIGNAL(on_attribute_change);


            
            //virtual bool OnOpenMidiPlayer();
            
            
//            virtual bool Initialize(::music::midi::midi * pmidi);
//            virtual bool Finalize();
            
            
//            virtual bool OpenMidiPlayer();
//            
//            virtual void OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata);

         };


      } // namespace player

   } // namespace port

   } // namespace midi


} // namespace music






