#include "framework.h"





namespace music
{
   
   
   namespace midi
   {
      
      
      namespace port
      {
      
      
      sequence::sequence(::aura::application * papp) :
      ::object(papp),
      ::music::midi::object(papp),
      ::ikaraoke::karaoke(papp),
      ::music::midi::sequence(papp)
      {
         
         m_buffera.Initialize(16, 4 * 1024, 0);
         m_midicallbackdata.m_psequence = this;
         
      }
      
      sequence::~sequence()
      {
         
         close_file();
         
      }
      
      
      
      
      
      
      
      /***************************************************************************
       *
       * seqPreroll
       *
       * Prepares the file for playback at the given position.
       *
       * pSeq                      - The sequencer instance.
       *
       * lpPreroll                 - Specifies the starting and ending tick
       *                             positions to play between.
       *
       * Returns
       *   ::multimedia::result_success If the operation is successful.
       *
       *   ::music::EFunctionNotSupported If the sequencer instance is not
       *     opened or prerolled.
       *
       * open the device so we can initialize channels.
       *
       * Loop through the tracks. For each track, seek to the given position and
       * send the init data SMF gives us to the handle.
       *
       * Wait for all init buffers to finish.
       *
       * Unprepare the buffers (they're only ever sent here; the sequencer
       * engine merges them into a single stream during normal playback) and
       * refill them with the first chunk of data from the track.
       *
       *
       ****************************************************************************/
      ::multimedia::e_result sequence::Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow)
      {
         
         UNREFERENCED_PARAMETER(pthread);
         
         single_lock sl(m_pmutex, TRUE);
         
         ::music::e_result          smfrc;
         
         ::multimedia::e_result     mmrc = ::multimedia::result_success;
         
         LPMIDIHDR                  lpmh = NULL;
         
         ASSERT(m_iOpenMode == ::music::midi::file::OpenForPlaying || IsInSpecialModeV001());
         
         m_flags.unsignalize(FlagEOF);
         
         m_mmrcLastErr = ::multimedia::result_success;
         
         if(get_status() != status_opened && get_status() != status_pre_rolled && !IsInSpecialModeV001())
            return ::music::translate(::music::EFunctionNotSupported);
         
         m_tkBase = lpPreroll->tkBase;
         
         m_tkEnd = lpPreroll->tkEnd;

         set_status(::music::midi::sequence::status_reset);
            
         set_status(::music::midi::sequence::status_pre_rolling);
         
         //
         // We've successfully opened the file and all of the tracks; now
         // open the MIDI device and set the time division.
         //
         // NOTE: seqPreroll is equivalent to seek; device might already be open
         //
         
         
         mmrc = ::multimedia::result_success;
         
         
         
         m_buffera.Reset();
         lpmh = &m_buffera[0].m_midihdr;
         
         if(IsInSpecialModeV001())
         {
            
            if(m_uiSpecialModeV001Operation == SPMV001GMReset)
            {
               /*const uchar gmModeOn[] = {
                //        0x00, 0x00, 0x00, 0x00,
                //        0x00, 0x00, 0x00, 0x00,
                //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x06, 0x00, 0x00, MEVT_LONGMSG,
                0xf0, 0x7e, 0x7f, 0x09,
                0x01, 0xf7, 0x00, 0x00};
                char * lpch = lpmh->lpData + lpmh->dwBytesRecorded;
                lpmh->dwBytesRecorded += sizeof(gmModeOn);
                memcpy(lpch, gmModeOn, sizeof(gmModeOn));
                SetSpecialModeV001Flag(false);*/
            }
            
         }
         
         smfrc = file()->WorkSeek(m_tkBase);
         
         m_tkPrerollBase = get_file()->GetPosition();
         
         m_flags.unsignalize(FlagEOF);
         
         file()->m_flags &= ~::music::midi::file::EndOfFile;
         
         
         
         if (mmrc != ::multimedia::result_success)
         {
            TRACE( "midiOutPrepare(preroll) -> %lu!", (uint32_t)mmrc);
            //mmrc = MCIERR_DEVICE_NOT_READY;
            if(bThrow)
            {
               set_status(status_opened);
               throw new exception(get_app(), ::music::EMidiPlayerPrerollPrepareHeader);
            }
            else
            {
               goto seq_Preroll_Cleanup;
            }
         }
         //         m_uBuffersInMMSYSTEM +=(uint32_t)  m_buffera.get_size();
         
      seq_Preroll_Cleanup:
         
         if (mmrc != ::multimedia::result_success)
         {
            set_status(status_opened);
            m_flags.unsignalize(::music::midi::sequence::FlagWaiting);
         }
         else
         {
            set_status(status_pre_rolled);
         }
         
         return mmrc;
      }
      
      /***************************************************************************
       *
       * seqStart
       *
       * Starts playback at the current position.
       *
       * pSeq                      - The sequencer instance.
       *
       * Returns
       *   ::multimedia::result_success If the operation is successful.
       *
       *   ::music::EFunctionNotSupported If the sequencer instance is not
       *     stopped.
       *
       *   MCIERR_DEVICE_NOT_READY If the underlying MIDI device could
       *     not be opened or fails any call.
       *
       * The sequencer must be prerolled before seqStart may be called.
       *
       * Just feed everything in the ready queue to the device.
       *
       ***************************************************************************/
      ::multimedia::e_result sequence::Start()
      {
         
         single_lock sl(m_pmutex, TRUE);
         
         if (::music::midi::sequence::status_pre_rolled != get_status())
         {
            
            TRACE( "seqStart(): State is wrong! [%u]", get_status());
            
            return ::music::translate(::music::EFunctionNotSupported);
            
         }
         
         m_evMmsgDone.ResetEvent();
         
         ::multimedia::e_result mmrc = ::multimedia::result_success;
         
         sl.unlock();
         
         if(mmrc == ::multimedia::result_success)
         {
            
            thread()->PostMidiSequenceEvent(this, ::music::midi::sequence::EventMidiPlaybackStart);
            
         }
         
         return mmrc;
         
      }
      
      ::multimedia::e_result sequence::seq_start()
      {
         
         single_lock sl(m_pmutex, TRUE);
         
         if(get_status() != status_pre_rolled)
            return ::music::translate(::music::EFunctionNotSupported);
         
         fork([=]()
              {
                 seq_dump();
                 
              });
         
         return ::multimedia::result_success;
         
      }
      
      /***************************************************************************
       *
       * seqPause
       *
       * Pauses playback of the instance.
       *
       * pSeq                      - The sequencer instance.
       *
       * Returns
       *   ::multimedia::result_success If the operation is successful.
       *
       *   ::music::EFunctionNotSupported If the sequencer instance is not
       *     playing.
       *
       * The sequencer must be playing before seqPause may be called.
       * Pausing the sequencer will cause all currently on notes to be turned
       * off. This may cause playback to be slightly inaccurate on restart
       * due to missing notes.
       *
       ***************************************************************************/
      ::multimedia::e_result sequence::Pause()
      {
         single_lock sl(m_pmutex, TRUE);
         
         //    assert(NULL != pSeq);
         
         if (status_playing != get_status())
            return ::music::translate(::music::EFunctionNotSupported);
         
         set_status(status_paused);
         
         SetLevelMeter(0);
         
         return ::multimedia::result_success;
      }
      
      /***************************************************************************
       *
       * seqRestart
       *
       * Restarts playback of an instance after a pause.
       *
       * pSeq                      - The sequencer instance.
       *
       * Returns
       *    ::multimedia::result_success If the operation is successful.
       *
       *    ::music::EFunctionNotSupported If the sequencer instance is not
       *     paused.
       *
       * The sequencer must be paused before seqRestart may be called.
       *
       ***************************************************************************/
      ::multimedia::e_result sequence::Restart()
      {
         //    assert(NULL != pSeq);
         
         single_lock sl(m_pmutex, TRUE);
         
         if (status_paused != get_status())
            return ::music::translate(::music::EFunctionNotSupported);
         
         set_status(status_playing);
         m_evMmsgDone.ResetEvent();
         
         //    ::multimedia::e_result mmrc = 0;
         //    single_lock slStream(&m_csStream, false);
         //  slStream.lock();
//         if(m_pseq != NULL)
         {
  //          seq_start_timer(m_pseq);
         }
         //slStream.unlock();
         return ::multimedia::result_success;
      }
      
      /***************************************************************************
       *
       * seqStop
       *
       * Totally stops playback of an instance.
       *
       * pSeq                      - The sequencer instance.
       *
       * Returns
       *   ::multimedia::result_success If the operation is successful.
       *
       *   ::music::EFunctionNotSupported If the sequencer instance is not
       *     paused or playing.
       *
       * The sequencer must be paused or playing before seqStop may be called.
       *
       ***************************************************************************/
      ::multimedia::e_result sequence::Stop()
      {
         
         single_lock sl(m_pmutex, TRUE);
         
         if(get_status() == status_stopping)
            return ::multimedia::result_success;
         
         // Automatic success if we're already stopped
         if (get_status() != status_playing
             && get_status() != status_paused)
         {
            m_flags.unsignalize(::music::midi::sequence::FlagWaiting);
            GetPlayerLink().OnFinishCommand(::music::midi::player::command_stop);
            return ::multimedia::result_success;
         }
         
         set_status(status_stopping);
         m_flags.signalize(::music::midi::sequence::FlagWaiting);
         
         m_eventMidiPlaybackEnd.ResetEvent();
         
//         if(m_pseq != NULL)
  //       {
    //        seq_stop_timer(m_pseq);
      //      if(::multimedia::result_success != m_mmrcLastErr)
        //    {
          //     TRACE( "::music::midi::sequence::Stop() -> midiOutStop() returned %lu in seqStop()!\n", (uint32_t)m_mmrcLastErr);
            //   m_flags.unsignalize(FlagWaiting);
              // return ::multimedia::result_not_ready;
            //}
        // }
         
         //m_eventMidiPlaybackEnd.lock();
         
         SetLevelMeter(0);
         
         return ::multimedia::result_success;
      }
      
      /***************************************************************************
       *
       * seqTime
       *
       * Determine the current position in playback of an instance.
       *
       * pSeq                      - The sequencer instance.
       *
       * pTicks                    - A pointer to a uint32_t where the current position
       *                             in ticks will be returned.
       *
       * Returns
       *   ::multimedia::result_success If the operation is successful.
       *
       *   MCIERR_DEVICE_NOT_READY If the underlying device fails to report
       *     the position.
       *
       *   ::music::EFunctionNotSupported If the sequencer instance is not
       *     paused or playing.
       *
       * The sequencer must be paused, playing or prerolled before seqTime
       * may be called.
       *
       ***************************************************************************/
      ::multimedia::e_result sequence::get_ticks(imedia_position &  pTicks)
      {
         
         synch_lock sl(m_pmutex);
         
         if (::music::midi::sequence::status_playing != get_status() &&
             ::music::midi::sequence::status_paused != get_status() &&
             ::music::midi::sequence::status_pre_rolling != get_status() &&
             ::music::midi::sequence::status_pre_rolled != get_status() &&
             ::music::midi::sequence::status_opened != get_status() &&
             ::music::midi::sequence::status_stopping != get_status())
         {
            TRACE( "seqTime(): State wrong! [is %u]", get_status());
            return ::music::translate(::music::EFunctionNotSupported);
         }
         
         pTicks = 0;
         if (status_opened != get_status())
         {
            pTicks = m_tkBase;
            if (status_pre_rolled != get_status())
            {
               //               mmt.wType = TIME_TICKS;
               //            single_lock slStream(&m_csStream, false);
               //          slStream.lock();
//               snd_seq_tick_time_t ticks;
  //             if(m_pseq == NULL)
    //           {
      //            TRACE("m_hmidi == NULL!!!!");
        //          return ::multimedia::result_not_ready;
          //     }
            //   else
               {
                  try
                  {
                     
              //       snd_seq_queue_status_t * pstatus = NULL;
                     
                    // snd_seq_queue_status_malloc(&pstatus);
                     
                    // if(pstatus == NULL)
                      //  return ::multimedia::result_internal;
                     
                //     if(snd_seq_get_queue_status(m_pseq->handle, m_pseq->queue, pstatus) < 0)
                  //      return ::multimedia::result_internal;
                     
                    // ticks = snd_seq_queue_status_get_tick_time(pstatus);
                     
                    // snd_seq_queue_status_free(pstatus);
                     
                  }
                  catch(...)
                  {
                     return ::multimedia::result_internal;
                  }
//                  pTicks += ticks;
               }
               //        slStream.unlock();
            }
         }
         
         return ::multimedia::result_success;
      }
      
      void sequence::get_time(imedia_time & time)
      {
         get_millis(time);
      }
      
      ::multimedia::e_result sequence::get_millis(imedia_time & time)
      {
         
         synch_lock sl(m_pmutex);
         
         if (status_playing != get_status() &&
             status_paused != get_status() &&
             status_pre_rolling != get_status() &&
             status_pre_rolled != get_status() &&
             status_opened != get_status() &&
             status_stopping != get_status())
         {
            TRACE( "seqTime(): State wrong! [is %u]", get_status());
            return ::music::translate(::music::EFunctionNotSupported);
         }
         
         time = 0;
         if (status_opened != get_status())
         {
            time = (int_ptr) TicksToMillisecs(m_tkBase);
            if (status_pre_rolled != get_status())
            {
//               const snd_seq_real_time_t * prt = NULL;
               //            single_lock slStream(&m_csStream, false);
               //          slStream.lock();
    //           if(m_pseq == NULL)
  //             {
      //            TRACE("m_hmidi == NULL!!!!");
        //          return ::multimedia::result_not_ready;
          //     }
            //   else
               {
                  try
                  {
                     
              //       snd_seq_queue_status_t * pstatus = NULL;
                     
                //     snd_seq_queue_status_malloc(&pstatus);
                     
                  //   if(pstatus == NULL)
                    //    return ::multimedia::result_internal;
                     
                    // if(snd_seq_get_queue_status(m_pseq->handle, m_pseq->queue, pstatus) < 0)
                      //  return ::multimedia::result_internal;
                     
                 //    prt = snd_seq_queue_status_get_real_time(pstatus);
                     
                   //  snd_seq_queue_status_free(pstatus);
                     
                  }
                  catch(...)
                  {
                     return ::multimedia::result_internal;
                  }
//                  if(prt == NULL)
  //                   return ::multimedia::result_internal;;
//                  time += (prt->tv_nsec / (1000 * 1000)) + (prt->tv_sec * 1000);
               }
               //        slStream.unlock();
            }
         }
         
         return ::multimedia::result_success;
      }
      
      /***************************************************************************
       *
       * seqMillisecsToTicks
       *
       * Given a millisecond offset in the output stream, returns the associated
       * tick position.
       *
       * pSeq                      - The sequencer instance.
       *
       * msOffset                  - The millisecond offset into the stream.
       *
       * Returns the number of ticks into the stream.
       *
       ***************************************************************************/
      imedia_position sequence::MillisecsToTicks(imedia_time msOffset)
      {
         return file()->MillisecsToTicks(msOffset);
      }
      
      /***************************************************************************
       *
       * seqTicksToMillisecs
       *
       * Given a tick offset in the output stream, returns the associated
       * millisecond position.
       *
       * pSeq                      - The sequencer instance.
       *
       * tkOffset                  - The tick offset into the stream.
       *
       * Returns the number of milliseconds into the stream.
       *
       ***************************************************************************/
      imedia_time sequence::TicksToMillisecs(imedia_position tkOffset)
      {
         
         return file()->TicksToMillisecs(tkOffset);
         
      }

      
      void sequence::OnPositionCB(LPMIDIHDR lpmidihdr)
      {
         
      }
      

      bool sequence::IsPlaying()
      {
         
         return get_status() == status_playing || get_status() == status_stopping;
         
      }
      

      void sequence::SetSpecialModeV001Flag(bool bSet)
      {
         if(m_flags.is_signalized(FlagIsInSpecialModeV001))
            m_flags.signalize(FlagWasInSpecialModeV001);
         else
            m_flags.unsignalize(FlagWasInSpecialModeV001);
         
         if(bSet)
            m_flags.signalize(FlagIsInSpecialModeV001);
         else
            m_flags.unsignalize(FlagIsInSpecialModeV001);
      }
         
      
      bool sequence::IsInSpecialModeV001()
      {
         
         return m_flags.is_signalized(FlagIsInSpecialModeV001);
         
      }
         
      
      bool sequence::WasInSpecialModeV001()
      {
         
         return m_flags.is_signalized(FlagWasInSpecialModeV001);
         
      }
      
      
      int32_t sequence::GetKeyShift()
      {
         
         if(m_pfile == NULL)
            return 0;
         
         return file()->GetKeyShift();
         
      }
         
      
      int32_t sequence::SetKeyShift(int32_t iKeyShift)
      {
         
         bool bPlay = IsPlaying();
         
         imedia_position ticks = 0;
         
         if(bPlay)
         {
            
            get_position(ticks);
            
            Stop();
            
         }
         
         get_file()->SetKeyShift(iKeyShift);
         
         if(bPlay)
         {
            
            m_pthread->PrerollAndWait(ticks);
            
            Start();
            
         }
         
         return true;
         
      }
      
      
      double sequence::GetTempoShift()
      {
         
         return file()->GetTempoShift();
         
      }
      
      
      int32_t sequence::SetTempoShift(int32_t iTempoShift)
      {
         
         //midiStreamPause(m_hstream);
         if(::music::failed(file()->SetTempoShift(iTempoShift)))
            return false;
         //midiStreamRestart(m_hstream);
         return true;
      }
      
      
      bool sequence::SetMidiOutDevice(uint32_t uiDevice)
      {
         
         if(uiDevice == ::music::midi::device_default)
         {
            
            //m_uiDeviceID = MIDI_MAPPER;
            
         }
         else
         {
            
            m_uiDeviceID = uiDevice;
            
         }
         
         return true;
      }
      
      ::multimedia::e_result sequence::CloseStream()
      {
         single_lock sl(m_pmutex, TRUE);
         if(IsPlaying())
         {
            Stop();
         }
         
         
         set_status(status_opened);
         
         return ::multimedia::result_success;
      }
      
      void sequence::SetLevelMeter(int32_t iLevel)
      {
         for(int32_t i = 0; i < m_iaLevel.get_size(); i++)
         {
            m_iaLevel.element_at(i) = iLevel;
         }
      }
      
      void sequence::OnMidiPlaybackEnd(::music::midi::sequence::event * pevent)
      {
         UNREFERENCED_PARAMETER(pevent);

         single_lock sl(m_pmutex, TRUE);
         
         
         //         if(0 == m_uBuffersInMMSYSTEM)
         {
            TRACE( "seqBufferDone: normal sequencer shutdown.");
            
            /* Totally done! Free device and notify.
             */
//            if(m_pseq != NULL)
            {
               /*if((mmrc = m_buffera.midiOutUnprepareHeader((HMIDIOUT) m_hstream))
                != ::multimedia::result_success)
                {
                TRACE( "midiOutUnprepareHeader failed in seqBufferDone! (%lu)", (uint32_t)mmrc);
  //              }*/
    //           seq_free_context(m_pseq);
      //         m_pseq = NULL;
            }
            
            m_mmrcLastErr = ::multimedia::result_success;
            m_flags.unsignalize(FlagWaiting);
            
            m_evMmsgDone.SetEvent();
         }
      }
      
      void sequence::OnEvent(::music::midi::sequence::event * pevent)
      {
         switch(pevent->m_eevent)
         {
            case EventSpecialModeV001End:
            {
               SetSpecialModeV001Flag(false);
               OnMidiPlaybackEnd(pevent);
               set_status(m_estatusPreSpecialModeV001);
            }
               break;
            case EventMidiPlaybackEnd:
            {
               OnMidiPlaybackEnd(pevent);
               set_status(status_opened);
            }
               break;
            default:
               break;
         }
      }
      
      /*imedia_position sequence::GetPositionTicks()
       {
       single_lock sl(m_pmutex);
       if(!sl.lock(millis(0)))
       return -1;
       MMTIME mmt;
       mmt.wType = TIME_TICKS;
       if(::multimedia::result_success ==
       midiStreamPosition(
       m_hstream,
       &mmt,
       sizeof(mmt)))
       return mmt.u.ticks + m_tkPrerollBase;
       else
       return -1;
       }*/
      
      
      bool sequence::IsChangingTempo()
      {
         return m_flags.is_signalized(::music::midi::sequence::FlagTempoChange);
      }
      void sequence::SetTempoChangeFlag(bool bSet)
      {
         if(bSet)
            m_flags.signalize(::music::midi::sequence::FlagTempoChange);
         else
            m_flags.unsignalize(::music::midi::sequence::FlagTempoChange);
      }
      
      
      bool sequence::IsNull()
      {
      
         if(is_null(this))
            return true;
         
         return false;
         
      }
      
      
      imedia_position sequence::TimeToPosition(imedia_time millis)
      {
         return imedia_position(MillisecsToTicks((int_ptr) millis));
      }
      
      imedia_time sequence::PositionToTime(imedia_position tk)
      {
         return imedia_time(TicksToMillisecs((imedia_position) (int_ptr) tk));
      }
      
      void sequence::GetPosition(imedia_position & position)
      {
         get_ticks(position);
      }
      
      bool sequence::IsOpened()
      {
         return get_status() != status_no_file;
      }
      
      void sequence::GetTimeLength(imedia_time & time)
      {
         time = m_msLength;
      }
      
      
      
//      void sequence::Prepare(
//                             string2a & str2a,
//                             imedia_position_2darray & tka2DTokensTicks,
//                             int32_t iMelodyTrack,
//                             int2a & ia2TokenLine,
//                             ::ikaraoke::data & data)
//      {
//         UNREFERENCED_PARAMETER(str2a);
//         ::music::midi_core_midi::buffer & file = *this->file();
//         ::music::midi::tracks & tracks = file.GetTracks();
//
//         ASSERT(!file.IsNull());
//         file.GetTracks().seek_begin();
//         imedia_position               tkMax = file.m_tkLength;
//         imedia_position               tkLastPosition = 0;
//
//
//         ::ikaraoke::static_data & staticdata = data.GetStaticData();
//
//         if(staticdata.m_LyricsDisplayOffset < 480)
//         {
//            staticdata.m_LyricsDisplayOffset = 480;
//         }
//         if(staticdata.m_LyricsDisplayOffset > 720)
//         {
//            staticdata.m_LyricsDisplayOffset = 720;
//         }
//         staticdata.m_LyricsDisplay = 30;
//
//         imedia_position_2darray tk2DNoteOnPositions(get_app());
//         imedia_position_2darray tk2DNoteOffPositions(get_app());
//         imedia_position_2darray tk2DBegPositions(get_app());
//         imedia_position_2darray tk2DEndPositions(get_app());
//         imedia_time_2darray ms2DTokensMillis(get_app());
//         imedia_time_2darray ms2DNoteOnMillis(get_app());
//         imedia_time_2darray ms2DNoteOffMillis(get_app());
//         imedia_time_2darray ms2DBegMillis(get_app());
//         imedia_time_2darray ms2DEndMillis(get_app());
//         ::music::midi::events midiEvents;
//
//
//
//
//         // Note on and off events
//         // and maximum and minimum
//         // pitch bend peaks.
//         ::music::midi::events midiEventsLevel2;
//
//         ::music::midi::events noteOnEvents;
//         ::music::midi::events noteOffEvents;
//
//         ::music::midi::events eventsLevel2Beg;
//         ::music::midi::events eventsLevel2End;
//         ::ikaraoke::events_tracks_v1 lyricEventsForPositionCB;
//         ::ikaraoke::events_tracks_v1 lyricEventsForBouncingBall;
//         ::ikaraoke::events_tracks_v1 lyricEventsForScoring;
//         ::ikaraoke::events_tracks_v1 lyricEvents;
//
//         //   tracks.seek_begin();
//         // tracks.GetXFInfoHeaders(
//         //  &m_xfInfoHeaders);
//
//
//
//         file.PositionToTime(
//                             ms2DTokensMillis,
//                             tka2DTokensTicks,
//                             0);
//
//         ::ikaraoke::lyric_events_v2 *pLyricEventsV2;
//         ::ikaraoke::lyric_events_v2 *pLyricEventsV2_;
//         ::ikaraoke::lyric_events_v2 *pLyricEventsV2B;
//         ::ikaraoke::lyric_events_v2 *pLyricEventsV2C;
//         ::music::midi::events *pMidiEventsV1;
//
//         tk2DNoteOnPositions.set_size_create(tka2DTokensTicks.get_size());
//         tk2DNoteOffPositions.set_size_create(tka2DTokensTicks.get_size());
//         tk2DBegPositions.set_size_create(tka2DTokensTicks.get_size());
//         tk2DEndPositions.set_size_create(tka2DTokensTicks.get_size());
//         int32_t i;
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV2 = new ::ikaraoke::lyric_events_v2();
//            pLyricEventsV2B = new ::ikaraoke::lyric_events_v2();
//            pLyricEventsV2C = new ::ikaraoke::lyric_events_v2();
//            pLyricEventsV2_ = new ::ikaraoke::lyric_events_v2();
//            staticdata.m_eventsv1.add(pLyricEventsV2);
//            staticdata.m_eventsv1.add(pLyricEventsV2B);
//            staticdata.m_eventsv1.add(pLyricEventsV2C);
//            staticdata.m_eventsv1.add(pLyricEventsV2_);
//            lyricEvents.add(pLyricEventsV2_);
//            lyricEventsForScoring.add(pLyricEventsV2);
//            lyricEventsForPositionCB.add(pLyricEventsV2B);
//            lyricEventsForBouncingBall.add(pLyricEventsV2C);
//            pLyricEventsV2->m_iType = 0;
//            pLyricEventsV2->m_iOrder = i;
//            pLyricEventsV2->m_iType = 2;
//            pLyricEventsV2->m_iOrder = i;
//            pLyricEventsV2B->m_iType = ikaraoke::EventRunningElement;
//            pLyricEventsV2B->m_iOrder = i;
//            pLyricEventsV2C->m_iType = 4;
//            pLyricEventsV2C->m_iOrder = i;
//            pMidiEventsV1 = NULL;
//            if(iMelodyTrack < 0)
//            {
//               pLyricEventsV2->m_iTrack =
//               file.WorkCalcMelodyTrack(
//                                        &pMidiEventsV1,
//                                        tka2DTokensTicks.operator[](i),
//                                        ia2TokenLine[i]);
//            }
//            else
//            {
//               pLyricEventsV2->m_iTrack = iMelodyTrack;
//            }
//            pLyricEventsV2B->m_iTrack = pLyricEventsV2->m_iTrack;
//            pLyricEventsV2C->m_iTrack = pLyricEventsV2->m_iTrack;
//            pLyricEventsV2_->m_iTrack = pLyricEventsV2->m_iTrack;
//            if(pLyricEventsV2->m_iTrack < 0)
//            {
//               pLyricEventsV2->m_iTrack = tracks.m_iMelodyTrackTipA;
//               pLyricEventsV2B->m_iTrack = tracks.m_iMelodyTrackTipA;
//               pLyricEventsV2C->m_iTrack = tracks.m_iMelodyTrackTipA;
//               pLyricEventsV2_->m_iTrack = tracks.m_iMelodyTrackTipA;
//            }
//            staticdata.SetGuessMelodyTrack(pLyricEventsV2->m_iTrack);
//            if(pLyricEventsV2->m_iTrack >= 0)
//            {
//               if(file.GetFormat() == 0)
//               {
//                  tracks.TrackAt(0)->WorkSeekBegin();
//                  ((::music::midi::track *)tracks.TrackAt(0))->WorkGetNoteOnOffEventsV1(
//                                                                                        &midiEvents,
//                                                                                        (int32_t) pLyricEventsV2->m_iTrack,
//                                                                                        file.GetFormat() == 1);
//                  tracks.TrackAt(0)->WorkSeekBegin();
//                  ((::music::midi::track *)tracks.TrackAt(0))->WorkGetLevel2Events(
//                                                                                   &midiEventsLevel2,
//                                                                                   (int32_t) pLyricEventsV2->m_iTrack,
//                                                                                   file.GetFormat() == 1);
//               }
//               else
//               {
//                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
//                  ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
//                                                                                                      &midiEvents,
//                                                                                                      (int32_t) pLyricEventsV2->m_iTrack,
//                                                                                                      file.GetFormat() == 1);
//                  tracks.TrackAt(pLyricEventsV2->m_iTrack)->seek_begin();
//                  ((::music::midi::track *)tracks.TrackAt(pLyricEventsV2->m_iTrack))->GetLevel2Events(
//                                                                                                      &midiEventsLevel2,
//                                                                                                      (int32_t) pLyricEventsV2->m_iTrack,
//                                                                                                      file.GetFormat() == 1);
//               }
//            }
//
//            ::music::midi::util miditutil(get_app());
//
//            miditutil.PrepareNoteOnOffEvents(
//                                             &noteOnEvents,
//                                             &noteOffEvents,
//                                             (int32_t) pLyricEventsV2->m_iTrack,
//                                             file.GetFormat(),
//                                             &midiEvents,
//                                             tka2DTokensTicks.operator[](i));
//
//            miditutil.PrepareLevel2Events(
//                                          &eventsLevel2Beg,
//                                          &eventsLevel2End,
//                                          (int32_t) pLyricEventsV2->m_iTrack,
//                                          file.GetFormat(),
//                                          &midiEventsLevel2,
//                                          tka2DTokensTicks.operator[](i));
//
//
//            tk2DNoteOnPositions[i]     = noteOnEvents.m_tkaEventsPosition;
//            tk2DNoteOffPositions[i]    = noteOffEvents.m_tkaEventsPosition;
//            tk2DBegPositions[i]        = eventsLevel2Beg.m_tkaEventsPosition;
//            tk2DEndPositions[i]        = eventsLevel2End.m_tkaEventsPosition;
//            pLyricEventsV2->m_dwaNotesData.copy(noteOnEvents.m_dwaEventsData);
//            pLyricEventsV2B->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
//            pLyricEventsV2C->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
//            pLyricEventsV2_->m_dwaNotesData.copy(eventsLevel2Beg.m_dwaEventsData);
//            midiEvents.remove_all();
//            noteOnEvents.remove_all();
//            noteOffEvents.remove_all();
//            midiEventsLevel2.remove_all();
//            eventsLevel2Beg.remove_all();
//            eventsLevel2End.remove_all();
//            delete pMidiEventsV1;
//         }
//
//         file.PositionToTime(
//                             ms2DNoteOnMillis,
//                             tk2DNoteOnPositions,
//                             0);
//
//         file.PositionToTime(
//                             ms2DNoteOffMillis,
//                             tk2DNoteOffPositions,
//                             0);
//
//         file.PositionToTime(
//                             ms2DBegMillis,
//                             tk2DBegPositions,
//                             0);
//
//         file.PositionToTime(
//                             ms2DEndMillis,
//                             tk2DEndPositions,
//                             0);
//
//
//         ::ikaraoke::lyric_events_v1 *pLyricEventsV1;
//
//
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEvents.get_at(i);
//            staticdata.m_eventstracks.add(pLyricEventsV2);
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaTokensPosition,
//                                ms2DTokensMillis[i],
//                                0);
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaNotesPosition,
//                                ms2DNoteOnMillis[i],
//                                0);
//
//            imedia_time time1(0);
//            imedia_time time2(0);
//
//            pLyricEventsV2->m_msaTokensPosition.CopySorted(
//                                                           ms2DTokensMillis[i],
//                                                           time1,
//                                                           time2);
//
//            pLyricEventsV2->m_msaNotesDuration.Diff(
//                                                    ms2DNoteOffMillis[i],
//                                                    ms2DNoteOnMillis[i]);
//
//            imedia_time time3(0);
//            imedia_time time4(0);
//
//            pLyricEventsV2->m_msaNotesPosition.CopySorted(
//                                                          ms2DNoteOnMillis[i],
//                                                          time3,
//                                                          time4);
//
//            imedia_time time5(0x7fffffff);
//
//            pLyricEventsV2->m_msaTokensDuration.ElementDiff(
//                                                            ms2DTokensMillis[i],
//                                                            time5);
//
//         }
//
//
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV1 = new ::ikaraoke::lyric_events_v1();
//            pLyricEventsV1->m_iType = ikaraoke::EventAdvanceShow;
//            pLyricEventsV1->m_iOrder = i;
//            //staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV1);
//            file.TimeToPosition(
//                                pLyricEventsV1->m_tkaTokensPosition,
//                                ms2DTokensMillis[i],
//                                -1000);
//            //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
//            //pLyricTrk->Prepare(*pLyricEventsV1);
//         }
//
//
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForScoring.get_at(i);
//            staticdata.m_eventsTracksForScoring.add(pLyricEventsV2);
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaTokensPosition,
//                                ms2DTokensMillis[i],
//                                0);
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaNotesPosition,
//                                ms2DNoteOnMillis[i],
//                                0);
//
//            imedia_time time1(-100);
//            imedia_time time2(0);
//
//            pLyricEventsV2->m_msaTokensPosition.CopySorted(
//                                                           ms2DTokensMillis[i],
//                                                           time1,
//                                                           time2);
//
//            pLyricEventsV2->m_msaNotesDuration.Diff(
//                                                    ms2DNoteOffMillis[i],
//                                                    ms2DNoteOnMillis[i]);
//
//            imedia_time time3(-100);
//            imedia_time time4(0);
//
//            pLyricEventsV2->m_msaNotesPosition.CopySorted(
//                                                          ms2DNoteOnMillis[i],
//                                                          time3,
//                                                          time4);
//
//            imedia_time time5(0x7fffffff);
//
//            pLyricEventsV2->m_msaTokensDuration.ElementDiff(
//                                                            ms2DTokensMillis[i],
//                                                            time5);
//
//            pLyricEventsV2->PrepareForScoring(this);
//         }
//
//
//
//
//
//
//
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForPositionCB.get_at(i);
//            staticdata.m_eventsTracksForPositionCB.add(pLyricEventsV2);
//
//            staticdata.m_eventstracksV002.add(pLyricEventsV2);
//
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaTokensPosition,
//                                ms2DTokensMillis[i],
//                                -100);
//
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaNotesPosition,
//                                ms2DNoteOnMillis[i],
//                                -100);
//
//            imedia_time time1(-100);
//            imedia_time time2(0);
//
//            pLyricEventsV2->m_msaTokensPosition.CopySorted(
//                                                           ms2DTokensMillis[i],
//                                                           time1,
//                                                           time2);
//
//            pLyricEventsV2->m_msaNotesDuration.Diff(
//                                                    ms2DNoteOffMillis[i],
//                                                    ms2DNoteOnMillis[i]);
//
//            /*
//             pLyricEventsV2->m_msaNotesDuration.Diff(
//             ms2DNoteOffMillis[i],
//             ms2DNoteOnMillis[i]);
//             */
//
//
//            imedia_time time3(-100);
//            imedia_time time4(0);
//
//            pLyricEventsV2->m_msaNotesPosition.CopySorted(
//                                                          ms2DNoteOnMillis[i],
//                                                          time3,
//                                                          time4);
//
//            imedia_time time5(0x7fffffff);
//
//            pLyricEventsV2->m_msaTokensDuration.ElementDiff(
//                                                            ms2DTokensMillis[i],
//                                                            time5);
//
//            pLyricEventsV2->PrepareForLyricsDisplay(this);
//            //lyric_track * pLyricTrk = file.GetTracks().CreateLyricTrack();
//            //pLyricTrk->Prepare(*pLyricEventsV2);
//         }
//
//
//
//
//
//
//
//
//
//
//         for(i = 0; i < tka2DTokensTicks.get_size(); i++)
//         {
//            pLyricEventsV2 = (::ikaraoke::lyric_events_v2 *) lyricEventsForBouncingBall.get_at(i);
//            staticdata.m_eventsTracksForBouncingBall.add(pLyricEventsV2);
//
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaTokensPosition,
//                                ms2DTokensMillis[i],
//                                -100);
//
//            file.TimeToPosition(
//                                pLyricEventsV2->m_tkaNotesPosition,
//                                ms2DNoteOnMillis[i],
//                                -100);
//
//            imedia_time time1(-100);
//            imedia_time time2(0);
//
//            pLyricEventsV2->m_msaTokensPosition.CopySorted(
//                                                           ms2DTokensMillis[i],
//                                                           time1,
//                                                           time2);
//
//            pLyricEventsV2->m_msaNotesDuration.Diff(
//                                                    ms2DEndMillis[i],
//                                                    ms2DBegMillis[i]);
//
//            /*
//             pLyricEventsV2->m_msaNotesDuration.Diff(
//             ms2DNoteOffMillis[i],
//             ms2DNoteOnMillis[i]);
//             */
//
//            imedia_time time3(-100);
//            imedia_time time4(0);
//
//            pLyricEventsV2->m_msaNotesPosition.CopySorted(
//                                                          ms2DNoteOnMillis[i],
//                                                          time3,
//                                                          time4);
//
//            imedia_time time5(0x7fffffff);
//
//            pLyricEventsV2->m_msaTokensDuration.ElementDiff(
//                                                            ms2DTokensMillis[i],
//                                                            time5);
//
//            pLyricEventsV2->PrepareForBouncingBall(this);
//         }
//
//      }
//
//      void sequence::Prepare(int32_t iTrack, ::ikaraoke::data & data)
//      {
//         ::music::midi_core_midi::file & file = *this->file();
//         ::music::midi::tracks & tracks = file.GetTracks();
//         string2a & str2a = data.GetStaticData().m_str2aRawTokens;
//         imedia_position_2darray position2a;
//         int2a ia2TokenLine;
//
//
//         ia2TokenLine.add_new();
//
//         tracks.WorkSeekBegin();
//         tracks.WorkGetEmptyXFTokens(
//                                     iTrack,
//                                     str2a,
//                                     position2a,
//                                     NULL);
//
//         Prepare(
//                 str2a,
//                 position2a,
//                 iTrack,
//                 ia2TokenLine,
//                 data);
//
//      }
//
//      void sequence::Prepare(::ikaraoke::data & data)
//      {
//         ::music::midi_core_midi::file & file = *this->file();
//         ::music::midi::tracks & tracks = file.GetTracks();
//         string2a & str2a = data.GetStaticData().m_str2aRawTokens;
//         imedia_position_2darray position2a;
//         int2a i2aTokenLine;
//
//         ::music::xf::info_headers xfihs;
//         get_file()->GetTracks().GetXFInfoHeaders(&xfihs);
//
//         ::ikaraoke::static_data & staticdata = data.GetStaticData();
//         string str;
//
//         // add Title
//         staticdata.m_straTitleFormat.add("%0");
//         staticdata.m_str2aTitle.set_app(get_app());
//         staticdata.m_str2aTitle.add_new();
//         staticdata.m_str2aTitle[0].add(xfihs.m_strSongName);
//
//         if(xfihs.m_xfInfoHeader.m_straComposer.get_size() > 0)
//         {
//            // add Performer
//            staticdata.m_straTitleFormat.add("Performer: %0");
//            xfihs.m_xfInfoHeader.m_straPerformer.get_format_string(str, ", ");
//            staticdata.m_str2aTitle.add_new();
//            staticdata.m_str2aTitle[1].add(str);
//
//            // add Composer
//            staticdata.m_straTitleFormat.add("Composer: %0");
//            xfihs.m_xfInfoHeader.m_straComposer.get_format_string(str, ", ");
//            staticdata.m_str2aTitle.add_new();
//            staticdata.m_str2aTitle[1].add(str);
//
//
//            //      staticdata.m_straPerformer = xfihs.m_xfInfoHeader.m_straPerformer;
//            //    staticdata.m_straArtist = xfihs.m_xfInfoHeader.m_straPerformer;
//         }
//
//         staticdata.m_dwDefaultCodePage = 1252; // Latin (Default of All Default Code Pages)
//
//         if(xfihs.m_xfaInfoHeaderLS.get_count())
//         {
//            staticdata.m_dwDefaultCodePage = ::music::xf::SymbolCharCodeToCodePage(xfihs.m_xfaInfoHeaderLS[0].m_strLanguage);
//         }
//
//         tracks.WorkSeekBegin();
//         //tracks.WorkGetXFTokens(staticdata.m_dwDefaultCodePage, str2a, position2a, i2aTokenLine, NULL);
//         tracks.WorkGetXFTokens((uint32_t) -1, str2a, position2a, i2aTokenLine, NULL, false);
//
//         Prepare(
//                 str2a,
//                 position2a,
//                 -1,
//                 i2aTokenLine,
//                 data);
//
//         tracks.WorkSeekBegin();
//         tracks.WorkGetLongestXFLyrics(staticdata.m_strLyrics, false);
//         tracks.WorkGetLongestXFLyrics(staticdata.m_strLyricsEx1, true);
//
//
//
//      }
      
      
      void sequence::GetPositionLength(imedia_position &position)
      {
         position = m_tkLength;
      }
      
      void sequence::buffer::Initialize(int32_t iSize, uint32_t dwUser)
      {
         m_storage.allocate(iSize);
         m_midihdr.lpData           = (char *) m_storage.get_data();
         m_midihdr.dwBufferLength   = (uint32_t) m_storage.get_size();
         m_midihdr.dwUser           = dwUser;
         m_bPrepared                = false;
         
      }
      
      void sequence::buffer_array::Initialize(int32_t iCount, int32_t iSize, uint32_t dwUser)
      {
         set_size(iCount);
         
         int32_t i;
         
         /*   for(int32_t i = 0; i < this->get_size() - 1; i++)
          {
          this->element_at(i).SetNextMidiHdr(this->element_at(i + 1).GetMidiHdr());
          }
          
          if(this->get_size() > 1)
          {
          this->element_at(get_upper_bound()).SetNextMidiHdr(this->element_at(0).GetMidiHdr());
          }
          else
          {
          this->element_at(0).SetNextMidiHdr(NULL);
          }*/
         
         for(i = 0; i < this->get_size(); i++)
         {
            this->element_at(i).Initialize(iSize, dwUser);
         }
      }
      
      void sequence::buffer_array::Reset()
      {
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            this->element_at(i).Reset();
         }
      }
      
      void sequence::buffer::Reset()
      {
         m_midihdr.dwBytesRecorded  = 0;
         m_midihdr.dwFlags          = 0;
      }
      
      bool sequence::buffer::IsPrepared()
      {
         return m_bPrepared;
      }
      
      
      /*      ::multimedia::e_result sequence::buffer::midiOutPrepareHeader(HMIDIOUT hmidiout)
       {
       ::multimedia::e_result mmr = 0;
       if(hmidiout == NULL)
       return mmr;
       if(m_bPrepared)
       return mmr;
       mmr = ::midiOutPrepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
       if(mmr == ::multimedia::result_success)
       {
       m_bPrepared = true;
       }
       return mmr;
       }
       
       ::multimedia::e_result sequence::buffer::midiOutUnprepareHeader(HMIDIOUT hmidiout)
       {
       ::multimedia::e_result mmr = 0;
       if(hmidiout == NULL)
       return mmr;
       if(!m_bPrepared)
       return mmr;
       mmr = ::midiOutUnprepareHeader(hmidiout, &m_midihdr, sizeof(m_midihdr));
       if(mmr == ::multimedia::result_success)
       {
       m_bPrepared = false;
       }
       return mmr;
       }
       
       ::multimedia::e_result sequence::buffer_array::midiOutUnprepareHeader(HMIDIOUT hmidiout)
       {
       ::multimedia::e_result mmr = ::multimedia::result_success;
       
       for (int32_t i = 0; i < this->get_size(); i++)
       {
       ::multimedia::e_result mmrBuffer = this->element_at(i).midiOutUnprepareHeader(hmidiout);
       if(mmrBuffer != ::multimedia::result_success)
       {
       mmr = mmrBuffer;
       }
       }
       return mmr;
       }
       
       ::multimedia::e_result sequence::buffer_array::midiOutPrepareHeader(HMIDIOUT hmidiout)
       {
       ::multimedia::e_result mmrc = ::multimedia::result_success;
       for(int32_t i = 0; i < this->get_size(); i++)
       {
       mmrc = this->element_at(i).midiOutPrepareHeader(
       hmidiout);
       if(mmrc != ::multimedia::result_success)
       {
       for(; i >= 0; i--)
       {
       this->element_at(i).midiOutUnprepareHeader(hmidiout);
       }
       return mmrc;
       }
       }
       return mmrc;
       }*/
      
      void sequence::buffer::SetNextMidiHdr(LPMIDIHDR lpNext)
      {
         m_midihdr.lpNext = lpNext;
      }
      
      
//      ::multimedia::e_result sequence::buffer::midiStreamOut(seq_context_t * hmidiout)
  //    {
         /*         ASSERT(hmidiout != NULL);
          return ::midiStreamOut(hmidiout, &m_midihdr, sizeof(m_midihdr));*/
    //     return ::multimedia::result_success;
      //}
      
  //    ::multimedia::e_result sequence::buffer_array::midiStreamOut(seq_context_t * hmidiout)
    //  {
         /*
          ::multimedia::e_result mmrc = ::multimedia::result_success;
          for(int32_t i = 0; i < this->get_size(); i++)
          {
          mmrc = this->element_at(i).midiStreamOut(
          hmidiout);
          if(mmrc != ::multimedia::result_success)
          {
          //         for(; i >= 0; i--)
          //       {
          //        this->element_at(i).midiOutUnprepareHeader(hmidiout);
          //   }
          return mmrc;
          }
          }
          return mmrc;*/
      //   return ::multimedia::result_success;
     // }
      
      
      
      
      
      void sequence::MuteAll(bool bMute, int32_t iExcludeTrack)
      {
         bool bPlay = IsPlaying();
         imedia_position ticks = 0;
         if(bPlay)
         {
            
            get_position(ticks);
            
            Stop();
            
         }
         get_file()->MuteAll(bMute, iExcludeTrack);
         if(bPlay)
         {
            m_pthread->PrerollAndWait(ticks);
            Start();
         }
      }
      
      void sequence::MuteTrack(int32_t iIndex, bool bMute)
      {
         bool bPlay = IsPlaying();
         imedia_position ticks = 0;
         if(bPlay)
         {
            
            get_position(ticks);
            
            Stop();
            
         }
         get_file()->MuteTrack(iIndex, bMute);
         if(bPlay)
         {
            m_pthread->PrerollAndWait(ticks);
            Start();
         }
      }
      
      imedia_position sequence::GetQuarterNote()
      {
         return get_file()->m_pFileHeader->GetQuarterNoteTicks();
      }
      
      
      int32_t sequence::GetDefaultCodePage()
      {
         return 1252;
      }
      
      
      bool sequence::IsSettingPosition()
      {
         return m_flags.is_signalized(::music::midi::sequence::FlagSettingPos);
      }
      
      
      void sequence::SetSettingPositionFlag(bool bSet)
      {
         if(bSet)
            m_flags.signalize(::music::midi::sequence::FlagSettingPos);
         else
            m_flags.unsignalize(::music::midi::sequence::FlagSettingPos);
      }
      

      
      ::music::midi::sequence::event * sequence::create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr)
      {
         
         ASSERT(this != NULL);
         
         event * pevent          = new event();
         
         pevent->m_eevent        = eevent;
         pevent->m_psequence     = this;
         pevent->m_lpmh          = lpmidihdr;
         
         return pevent;
         
      }
      
      
      ::music::midi::event * sequence::seq_get_next_event()
      {
         
         ::music::midi::event * pevent = NULL;
         
         get_file()->WorkGetNextEvent(pevent, m_tkEnd, false);
         
         return pevent;
         
      }
      
      int sequence::seq_dump()
      {
         
         m_pthreadPlay = new ::music::midi::port::thread(get_app());
         
         m_pthreadPlay->m_pseq = this;
         
         m_pthreadPlay->begin();

         
         return 1;
         
      }
      
      int sequence::seq_play(::music::midi::event * pevent)
      {
         
//         snd_seq_event_t ev;
         
  //       seq_midi_event_init(m_pseq, &ev, pevent->m_tkPosition - m_tkPrerollBase, pevent->GetTrack());
         
         int iCount = 1;
         
         switch (pevent->GetType())
         {
               /*         case ::music::midi::NoteOn:
                seq_midi_note_on(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
                break;
                case ::music::midi::NoteOff:
                seq_midi_note_off(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
                break;*/
            case ::music::midi::NoteOff:
               break;
            case ::music::midi::PolyPressure:
        //       seq_midi_keypress(m_pseq, &ev, pevent->GetTrack(), pevent->GetNotePitch(), pevent->GetNoteVelocity());
               break;
            case ::music::midi::ControlChange:
          //     seq_midi_control(m_pseq, &ev, pevent->GetTrack(), pevent->GetController(), pevent->GetControllerValue());
               break;
            case ::music::midi::ProgramChange:
            //   seq_midi_program(m_pseq, &ev, pevent->GetTrack(), pevent->GetProgram());
               break;
            case ::music::midi::PitchBend:
              // seq_midi_pitchbend(m_pseq, &ev, pevent->GetTrack(), pevent->GetPitchBendLevel());
               break;
            case ::music::midi::ChanPressure:
               //seq_midi_chanpress(m_pseq, &ev, pevent->GetTrack(), pevent->GetChannelPressure());
               break;
            case 0xf0:
            {
               switch(pevent->GetFullType())
               {
                  case ::music::midi::Meta:
                  {
                     switch(pevent->GetMetaType())
                     {
                        case ::music::midi::MetaTempo:
                        {
                           DWORD dwTempo = (((uint32_t)pevent->GetData()[0])<<16)|
                           (((uint32_t)pevent->GetData()[1])<<8)|
                           ((uint32_t)pevent->GetData()[2]);
                           dwTempo = (uint32_t) ((double) dwTempo / get_file()->GetTempoShiftRate());
                           
                 //          seq_midi_tempo(m_pseq, &ev, dwTempo);
                        }
                           break;
                        case ::music::midi::MetaLyric:
                        case ::music::midi::MetaKarLyric:
                        case ::music::midi::MetaTimeSig:
                        case ::music::midi::MetaKeySig:
                           //case MD_TYPE_SMPTEOFFSET:
                           iCount = 0;
                           /* Ones that have no sequencer action */
                           break;
                        default:
                           iCount = 0;
                           printf("WARNING: play: not implemented yet Meta %d\n", pevent->GetMetaType());
                           break;
                     }
                  }
                     break;
                  case ::music::midi::SysEx:
                  case ::music::midi::SysExEnd:
                   //  seq_midi_sysex(m_pseq, &ev, pevent->GetFullType(), pevent->GetParam(), pevent->GetParamSize());
                     break;
                  default:
                     iCount = 0;
                     printf("WARNING: play: not implemented yet %d\n", pevent->GetFullType());
                     break;
               }
            }
               break;
            default:
               iCount = 0;
               printf("WARNING: play: not implemented yet %d\n", pevent->GetType());
               break;
         }
         
         return iCount;
         
      }

         
      } // namespace port
      
      
   } // namespace midi
   
   
} // namespace music









