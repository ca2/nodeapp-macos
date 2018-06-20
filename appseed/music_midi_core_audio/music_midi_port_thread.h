#pragma once



namespace music
{


   namespace midi
      {
         
         namespace port
         {

         class sequence;

         class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI thread :
            virtual public ::thread
         {
         public:


            sequence *              m_pseq;

            manual_reset_event      m_evRun;

            imedia_position         m_tkPosition;


            thread(::aura::application * papp);
            virtual ~thread();


            virtual void run() override;


         };

         } // namespace port


   } // namespace midi


} // namespace music





