#include "framework.h"


/* Windows sleep in 100ns units */
//BOOLEAN nanosleep(LONGLONG ns)
//{
//   manual_reset_event ev(::get_thread_app());
//
//   TimeSpan delay;
//   delay.Duration = MAX((ns / 100), 1) - 1;
//   ThreadPoolTimer ^ PeriodicTimer =
//      ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler([&](ThreadPoolTimer ^) {ev.SetEvent(); }), delay);
//
//   ev.wait();
//
//   return TRUE;
//
//}

uint64_t get_micro()
{

   return get_nanos() / 1000;

}

namespace music
{


   namespace midi
   {

namespace port
      {


         thread::thread(::aura::application * papp) :
            ::object(papp),
            ::thread(papp),
            m_evRun(papp)
         {

            m_pseq = NULL;

            m_evRun.SetEvent();

            m_tkPosition = 0;

         }

         thread::~thread()
         {
            if (m_pseq->m_pthreadPlay == this)
            {

               m_pseq->m_pthreadPlay = NULL;

            }

         }


         void thread::run()
         {

            RtMidiOut *midiout = new RtMidiOut();

            std::vector<unsigned char> message;
            // Check available ports.
            unsigned int nPorts = midiout->getPortCount();
            if ( nPorts == 0 ) {
               output_debug_string("No ports available!\n");
               delete midiout;
               return;
            }
            {
               // Open first available port.
               midiout->openPort( 0 );
               // Send out a series of MIDI messages.
               // Program change: 192, 5
               message.push_back( 192 );
               message.push_back( 5 );
               midiout->sendMessage( &message );
               // Control Change: 176, 7, 100 (volume)
               message[0] = 176;
               message[1] = 7;
               message.push_back( 100 );
               midiout->sendMessage( &message );
               // Note On: 144, 64, 90
               message[0] = 144;
               message[1] = 64;
               message[2] = 90;
               midiout->sendMessage( &message );
               Sleep( 500 ); // Platform-dependent ... see example in tests directory.
               // Note Off: 128, 64, 40
               message[0] = 128;
               message[1] = 64;
               message[2] = 40;
               midiout->sendMessage( &message );
               // Clean up
            }
            e_result       smfrc;
            ::music::midi::event *           pevent = NULL;
            imedia_position tkMax = ::numeric_info <imedia_position>::get_maximum_value();
            imedia_position tkPosition;
            bool bGotEvent = false;
            sequence_thread * pthread = dynamic_cast < sequence_thread * > (m_pseq->m_pthread);
            uint64_t dwStart = ::get_micro() - m_pseq->TicksToMillisecs(m_pseq->m_tkBase) * 1000;
            imedia_position tkLastBend = 0;
            m_tkPosition = 0;
            uint64_t dwNow;
            uint64_t dwFile;

            int_map < int_map < int > > map;

            bool bProcessed;

            //bool bEqual = false;

            m_evRun.wait();

            if (!thread_get_run())
            {

               goto end_playback;

            }



            while (thread_get_run())
            {

               if (m_pseq->file()->m_flags & file::EndOfFile)
               {

                  break;

               }


               bProcessed = true;

               if (!bGotEvent)
               {

                  smfrc = m_pseq->file()->WorkGetNextEvent(pevent, tkMax, TRUE);

                  if (::music::success != smfrc)
                  {

                     break;

                  }

                  bGotEvent = true;

               }

               tkPosition = m_pseq->file()->GetPosition();



               dwNow = ::get_tick_count()- dwStart;
               dwFile = m_pseq->TicksToMillisecs(tkPosition);

               if (dwNow < dwFile)
               {

                  if (dwFile - dwNow >= 2000)
                  {

                     Sleep(1);

                  }
                  else
                  {
                     Sleep(0);
                  }

               }
               else
               {
                  if (dwNow - dwFile >= 20)
                  {

                     for (auto & p1 : map)
                     {
                        for (auto & p2 : p1.m_element2)
                        {
                           if (p2.m_element2 >= 0)
                           {
                              //m_pseq->m_io->note_off(p1.m_element1, p2.m_element1, p2.m_element2);
                              p2.m_element2 = -1;
                           }
                        }
                     }


                  }

                  m_tkPosition = tkPosition;

                  if (pevent->GetType() == ::music::midi::NoteOn)
                  {

                     if (dwNow - dwFile < 20)
                     {

                        //m_pseq->m_io->note_on(pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());

                        map[pevent->GetTrack()][pevent->GetNotePitch()] = pevent->GetNoteVelocity();

                     }

                  }
                  else if (pevent->GetType() == ::music::midi::NoteOff)
                  {

                     if (dwNow - dwFile < 20 )
                     {

                        //m_pseq->m_io->note_off(pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());

                        map[pevent->GetTrack()][pevent->GetNotePitch()] = -1;

                     }

                  }
                  else if (pevent->GetType() == ::music::midi::ProgramChange)
                  {

                     //m_pseq->m_io->program_change(pevent->GetTrack(), pevent->GetProgram());

                  }
                  else if (pevent->GetType() == ::music::midi::ControlChange)
                  {

                     //m_pseq->m_io->control_change(pevent->GetTrack(), pevent->GetController(), pevent->GetControllerValue());

                  }
                  else if (pevent->GetType() == ::music::midi::PitchBend)
                  {

                     //if (tkLastBend == tkPosition)
                     //{

                     //   bEqual = true;

                     //}
                     //else
                     //{
                     int iChannel = pevent->GetTrack();


                     uint16_t uiBend = pevent->GetPitchBendLevel();
                     uint16_t uiBend2;

                     BYTE b1 = ((BYTE*)&uiBend)[0];
                     BYTE b2 = ((BYTE*)&uiBend)[1];

                     ((BYTE*)&uiBend2)[0] = b2;
                     ((BYTE*)&uiBend2)[1] = b1;

                     TRACE("pitch_bend ch=%02d bend1=%05d bend2=%05d", iChannel, uiBend, uiBend2);

                     tkLastBend = tkPosition;

                     //m_pseq->m_io->pitch_bend(iChannel, MIN(16383, uiBend));


                     //}

                  }

                  bGotEvent = false;

               }






               if (::music::success != smfrc)
               {

                  break;

               }


            }

end_playback:
            delete midiout;
            pthread->PostMidiSequenceEvent(
            m_pseq,
            ::music::midi::sequence::EventMidiPlaybackEnd,
            NULL);
            if (m_pseq->m_pthreadPlay == this)
            {

               m_pseq->m_pthreadPlay = NULL;

            }

         }

      } // namespace port


   } // namespace midi


} // namespace music





