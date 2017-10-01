	#include "framework.h"

extern
void InstallUncaughtExceptionHandler();

void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);




namespace multimedia
{
   
   
   namespace audio_core_audio
   {
      
      
      wave_out::wave_out(::aura::application * papp) :
      object(papp),
      ::thread(papp),
      wave_base(papp),
      toolbox(papp),
      ::multimedia::audio::wave_out(papp)
      {
         
         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_iBufferedCount     = 0;
         m_mmr                = ::multimedia::result_success;
         m_peffect            = NULL;
         m_bDone              = false;
         m_eventRunning.ResetEvent();
         
      }
      
      wave_out::~wave_out()
      {
         
      }
      
      void wave_out::install_message_routing(::message::sender * pinterface)
      {
         
         ::multimedia::audio::wave_out::install_message_routing(pinterface);
         
         //         IGUI_WIN_MSG_LINK(MM_WOM_OPEN, pinterface, this, &wave_out::OnMultimediaOpen);
         //       IGUI_WIN_MSG_LINK(MM_WOM_DONE, pinterface, this, &wave_out::OnMultimediaDone);
         //     IGUI_WIN_MSG_LINK(MM_WOM_CLOSE, pinterface, this, &wave_out::OnMultimediaClose);
         
         //         IGUI_WIN_MSG_LINK(message_open, pinterface, this, &wave_out::OnOpen);
         
      }
      
      
      void wave_out::OnOpen()
      {
         
         set_event_on_exit set_event_on_exitOpened(m_eventOpened);
         
         if(succeeded(m_mmr = translate(AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, NULL, kCFRunLoopCommonModes, 0, &m_Queue))))
            return;
         
         uint32_t uiBufferSizeLog2;
         memory_size_t uiBufferSize;
         uint32_t uiAnalysisSize;
         memory_size_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         memory_size_t uiBufferCount = m_iBufferCount;
         
         //   if(m_pwaveformat->nSamplesPerSec == 44100)
         if(true)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * m_iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(m_iBufferCount > 0)
            {
               uiAllocationSize = m_iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
         
         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);
         
         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, m_iBufferSampleCount);
         
         /*
          
          int32_t i, iSize;
          
          iSize = wave_out_get_buffer()->GetBufferCount();
          
          for(i = 0; i < iSize; i++)
          {
          
          if(::multimedia::result_success != (mmr =  waveOutPrepareHeader(m_Queue, create_new_WAVEHDR(wave_out_get_buffer(), i), sizeof(WAVEHDR))))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return mmr;
          }
          
          //wave_out_add_buffer(i);
          
          }
          
          */
         
         m_pprebuffer->SetMinL1BufferCount(wave_out_get_buffer()->GetBufferCount() + 4);
         
         m_estate = state_opened;
         
         m_mmr = ::multimedia::result_success;
         
      }
      
      
      bool wave_out::initialize_thread()
      {
         
         if(!::multimedia::audio::wave_out::initialize_thread())
            return false;
         
         if(!toolbox::initialize_thread())
            return false;
         
         return true;
         
      }
      
      int32_t wave_out::exit_thread()
      {
         
         ::multimedia::audio::wave_out::exit_thread();
         
         toolbox::exit_thread();
         
         return thread::exit_thread();
         
      }
      
      ::multimedia::e_result wave_out::wave_out_open(thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount)
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         if(m_Queue != NULL &&
            m_estate != state_initial)
            return ::multimedia::result_success;
         
         m_pthreadCallback = pthreadCallback;
         
         ASSERT(m_Queue == NULL);
         ASSERT(m_estate == state_initial);
         
         m_pwaveformat->wFormatTag = 0;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(multimedia::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();
         
         translate(*&m_dataformat, m_pwaveformat);
         if(::multimedia::result_success == (m_mmr = translate(AudioQueueNewOutput(                              // 1
                                                                                   &m_dataformat,                          // 2
                                                                                   WaveOutAudioQueueBufferCallback,                            // 3
                                                                                   this,                                      // 4
                                                                                   m_runloop,                                         // 5
                                                                                   kCFRunLoopDefaultMode,                        // 6
                                                                                   0,                                            // 7
                                                                                   &m_Queue                                // 8
                                                                                   ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::multimedia::result_success == (m_mmr = translate(AudioQueueNewOutput(                              // 1
                                                                                   &m_dataformat,                          // 2
                                                                                   WaveOutAudioQueueBufferCallback,                            // 3
                                                                                   this,                                      // 4
                                                                                   m_runloop,                                         // 5
                                                                                   kCFRunLoopDefaultMode,                        // 6
                                                                                   0,                                            // 7
                                                                                   &m_Queue                                // 8
                                                                                   ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::multimedia::result_success == (m_mmr = translate(AudioQueueNewOutput(                              // 1
                                                                                   &m_dataformat,                          // 2
                                                                                   WaveOutAudioQueueBufferCallback,                            // 3
                                                                                   this,                                      // 4
                                                                                   m_runloop,                                         // 5
                                                                                   kCFRunLoopDefaultMode,                        // 6
                                                                                   0,                                            // 7
                                                                                   &m_Queue                                // 8
                                                                                   ))))
            goto Opened;
         
         return m_mmr;
         
      Opened:
         
         uint32_t uiBufferSizeLog2;
         memory_size_t uiBufferSize;
         uint32_t uiAnalysisSize;
         memory_size_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         memory_size_t uiBufferCount = iBufferCount;
         
         if(m_pwaveformat->nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         //         else if(m_pwaveformat->nSamplesPerSec == 11025)
         else
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         
         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);
         
         m_pprebuffer->open(
                            this, // callback thread (thread)
                            m_pwaveformat->nChannels, // channel count
                            uiBufferCount, // group count
                            iBufferSampleCount); // group sample count
         
         /*         int32_t i, iSize;
          iSize = wave_out_get_buffer()->GetBufferCount();
          
          AudioQueueBufferRef buf;
          
          for(i = 0; i < iSize; i++)
          {
          
          buf = NULL;
          
          if(0 != (status = AudioQueueAllocateBuffer (m_Queue, wave_out_get_buffer_size(), &buf))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return ::multimedia::result_error;
          }
          
          m_Buffers.add(buf);
          
          }*/
         m_estate = state_opened;
         return m_mmr;
      }
      
      ::multimedia::e_result wave_out::wave_out_open_ex(thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample, ::multimedia::audio::e_purpose epurpose)
      {
         single_lock sLock(m_pmutex, TRUE);
         
         if(m_Queue != NULL && m_estate != state_initial)
            return ::multimedia::result_success;
         
         m_pthreadCallback = pthreadCallback;
         
         ASSERT(m_Queue == NULL);
         
         ASSERT(m_estate == state_initial);
         
         m_pwaveformat->wFormatTag        = 0;
         m_pwaveformat->nChannels         = (WORD) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (WORD) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize            = 0;
         
         ZEROP(&m_dataformat);
         
         translate(m_dataformat, m_pwaveformat);

         if(epurpose == ::multimedia::audio::purpose_playground)
         {
            
            iBufferCount = 4;
            
            iBufferSampleCount = 1024;
            
         }
         else if(epurpose == ::multimedia::audio::purpose_playback)
         {
            
            iBufferCount = 8;
            
            iBufferSampleCount = 8192;
            
         }
      //   if(epurpose)
         m_epurpose = epurpose;
         m_iBufferCount = iBufferCount;
         m_iBufferSampleCount = iBufferSampleCount;
         
         try
         {
            
            if(failed(m_mmr = translate(AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, NULL, NULL, 0, &m_Queue))))
               return m_mmr;
            
         }
         catch(...)
         {
         
            m_mmr = result_error;
         
            return m_mmr;
         
         }

         uint32_t uiBufferSizeLog2;
         memory_size_t uiBufferSize;
         uint32_t uiAnalysisSize;
         memory_size_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         memory_size_t uiBufferCount = iBufferCount;
         
         //   if(m_pwaveformat->nSamplesPerSec == 44100)
         if(true)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         {
//            uiBufferSizeLog2 = 10;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 1;
//         }
         
         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 64, m_pwaveformat, m_pwaveformat);
         
         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, iBufferSampleCount);
         
         /*         int32_t i, iSize;
          
          iSize = wave_out_get_buffer()->GetBufferCount();
          
          for(i = 0; i < iSize; i++)
          {
          
          if(::multimedia::result_success != (mmr =  waveOutPrepareHeader(m_Queue, create_new_WAVEHDR(wave_out_get_buffer(), i), sizeof(WAVEHDR))))
          {
          TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
          return mmr;
          }
          
          //wave_out_add_buffer(i);
          
          }*/
         
         
         m_estate = state_opened;
         
         return m_mmr;
         
      }
      
      
      
      ::multimedia::e_result wave_out::wave_out_close()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         if(m_estate == state_playing)
         {
            
            wave_out_stop();
            
         }
         
         if(m_estate != state_opened)
         {
            
            return ::multimedia::result_success;
            
         }
         
         m_estate = state_closing;
         
         OSStatus status;
         
         int i = 0;

         UInt32 property_running;
         
         UInt32 size;
         
         while(i < 50)
         {
            
            property_running = 0;
            
            size = sizeof(property_running);
            
            OSStatus status = AudioQueueGetProperty(m_Queue, kAudioQueueProperty_IsRunning, &property_running, &size);
            
            if(status != 0)
            {
             
               break;
               
            }
            
            if(!property_running)
            {
               
               Sleep(50);
             
               break;
               
            }
            
            i++;
            
            Sleep(250);
            
         }
         
         free_buffers();
         
         status = AudioQueueDispose(m_Queue, FALSE);
         
         m_Queue = NULL;
         
         m_pprebuffer->Reset();
         
         m_estate = state_initial;
         
         return ::multimedia::result_success;
         
      }
      
      
      void wave_out::wave_out_buffer_ready(index iBuffer)
      {
         
         if(wave_out_get_state() != state_playing)
         {
            
            TRACE("ERROR wave_out::BufferReady while wave_out_get_state() != state_playing");
            
            return;
            
         }
         
         AudioQueueBufferRef buf = audio_buffer(iBuffer);
         
         OSStatus status;
         
         if(m_peffect != NULL)
         {
            
            m_peffect->Process16bits((int16_t *) buf->mAudioData, wave_out_get_buffer_size() / 2);
            
         }
         
         single_lock sLock(m_pmutex, TRUE);
         
         buf->mAudioDataByteSize = (UInt32) wave_out_get_buffer_size();
         
         status = AudioQueueEnqueueBuffer(m_Queue, buf, 0, NULL);
         
         if(status != 0)
         {
            
            m_iBufferedCount--;
            
         }
         
      }
      
      ::multimedia::e_result wave_out::wave_out_stop()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         if(m_estate != state_playing && m_estate != state_paused)
            return ::multimedia::result_error;
         
         m_eventStopped.ResetEvent();
         
         m_estate = state_stopping;
         
         m_mmr = translate(AudioQueueStop(m_Queue, FALSE));
         
         if(m_mmr == ::multimedia::result_success)
         {
            
            m_estate = state_opened;
            
         }

         m_pprebuffer->Stop();

         return m_mmr;
         
      }
      
      
      ::multimedia::e_result wave_out::wave_out_pause()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         ASSERT(m_estate == state_playing);
         
         if(m_estate != state_playing)
            return ::multimedia::result_error;
         
         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = translate(AudioQueuePause(m_Queue));
         
         ASSERT(m_mmr == ::multimedia::result_success);
         
         if(m_mmr == ::multimedia::result_success)
         {
            m_estate = state_paused;
         }
         
         return m_mmr;
         
      }
      
      
      ::multimedia::e_result wave_out::wave_out_restart()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         ASSERT(m_estate == state_paused);
         
         if(m_estate != state_paused)
         {
            
            m_mmr = ::multimedia::result_error;
            
            return m_mmr;
            
         }
         
         m_mmr = translate(AudioQueuePrime(m_Queue, 0, NULL));
         
         m_mmr = translate(AudioQueueStart(m_Queue, NULL));
         
         ASSERT(m_mmr == ::multimedia::result_success);
         
         if(m_mmr == ::multimedia::result_success)
         {
            
            m_estate = state_playing;
            
         }
         
         return m_mmr;
         
      }
      
      
      imedia_time wave_out::wave_out_get_position_millis()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         OSStatus                status;
         
         AudioTimeStamp          stamp;
         
         if(m_Queue != NULL)
         {
            
            
            AudioQueueTimelineRef timeLine;
            
            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
            if(status != noErr)
               return 0;
            
            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, NULL);
            
            if(status != 0)
               return 0;
            
            

            
            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;
            
            return (imedia_time) stamp.mSampleTime * 1000 / m_pwaveformat->nSamplesPerSec;
            
         }
         else
            return 0;
         
         
      }
      
      
      imedia_position wave_out::wave_out_get_position()
      {
         
         single_lock sLock(m_pmutex, TRUE);
         
         OSStatus                status;
         
         AudioTimeStamp          stamp;
         
         if(m_Queue != NULL)
         {
            
            AudioQueueTimelineRef timeLine;
            
            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
            if(status != noErr)
               return 0;
            
            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, NULL);
            
            if(status != 0)
               return 0;
            
            
            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;
            
            return (imedia_time) stamp.mSampleTime;
            
         }
         else
            return 0;
         
         
      }
      
      void wave_out::wave_out_on_playback_end()
      {
         
         wave_out_stop();
         
         if(m_pprebuffer->m_pstreameffectOut != NULL)
         {
            ::multimedia::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
            m_pprebuffer->m_pstreameffectOut = NULL;
            delete peffect;
         }
         
         m_eventStopped.SetEvent();
         
         m_pplayer->OnEvent(::multimedia::audio::wave_player::EventPlaybackEnd);
         
      }
      
      
      
      
      
      void * wave_out::get_os_data()
      {
         
         return m_Queue;
         
      }
      
      
      
      void wave_out::AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {
         
         if(m_bDone)
            return;
         
         index iBuffer = m_Buffers.find_first(inCompleteAQBuffer);
         
         if(iBuffer < 0)
            return;
          
         //m_iBufferedCount--;
         
         wave_out_out_buffer_done((int) iBuffer);
         
      }
      
      
      AudioQueueRef wave_out::wave_out_get_safe_AudioQueueRef()
      {
         
         return m_Queue;
         
      }
      
      
      bool wave_out::on_run_step()
      {
         
         if(m_estate == state_playing)
         {
            
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);
            
         }
         
         return true;
         
      }

      
      ::multimedia::e_result wave_out::wave_out_start(const imedia_position & position)
      {
         
         ::multimedia::e_result mmr = ::multimedia::audio::wave_out::wave_out_start(position);
         
         if(mmr != 0)
            return mmr;
         
         m_estate = state_paused;
         
         m_mmr = wave_out_restart();
         
         return m_mmr;
         
      }
      
      
   } // namespace audio_core_audio
   
   
} // namespace multimedia







void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
{
   
   ::multimedia::audio_core_audio::wave_out * pwaveout = (::multimedia::audio_core_audio::wave_out *) inUserData;
   
   if(pwaveout == NULL)
      return;
   
   try
   {
      
      pwaveout->AudioQueueBufferCallback(inAQ, inCompleteAQBuffer);
      
   }
   catch(...)
   {
      
   }
   
}
