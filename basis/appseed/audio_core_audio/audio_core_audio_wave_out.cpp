#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      wave_out::wave_out(sp(base_application) papp) :
         element(papp),
         ::thread(papp),
         wave_base(papp),
         toolbox(papp),
         ::multimedia::audio::wave_out(papp)
      {
         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_iBufferedCount     = 0;
         m_mmr                = MMSYSERR_NOERROR;
         m_peffect            = NULL;
         m_dwLostSampleCount  = 0;
      }

      wave_out::~wave_out()
      {

      }

      void wave_out::install_message_handling(::message::dispatch * pinterface)
      {

         ::multimedia::audio::wave_out::install_message_handling(pinterface);

//         IGUI_WIN_MSG_LINK(MM_WOM_OPEN, pinterface, this, &wave_out::OnMultimediaOpen);
  //       IGUI_WIN_MSG_LINK(MM_WOM_DONE, pinterface, this, &wave_out::OnMultimediaDone);
    //     IGUI_WIN_MSG_LINK(MM_WOM_CLOSE, pinterface, this, &wave_out::OnMultimediaClose);

      }


      bool wave_out::initialize_instance()
      {

         if(!::multimedia::audio::wave_out::initialize_instance())
            return false;

         return true;

      }

      int32_t wave_out::exit_instance()
      {

         ::multimedia::audio::wave_out::exit_instance();

         return thread::exit_instance();

      }

      ::multimedia::result wave_out::wave_out_open(thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount)
      {
         
         single_lock sLock(&m_mutex, TRUE);
         
         if(m_Queue != NULL &&
            m_estate != state_initial)
            return MMSYSERR_NOERROR;
         
         m_pthreadCallback = pthreadCallback;
         
//         ::multimedia::result mmr;
         
         OSStatus status = 0;
         
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

         translate(m_DataFormat, m_pwaveformat);
         if(0 == (status = AudioQueueNewOutput(                              // 1
                                                           &m_DataFormat,                          // 2
                                                           &AudioQueueBufferCallback,                            // 3
                                                           this,                                      // 4
                                                           NULL,                                         // 5
                                                           kCFRunLoopCommonModes,                        // 6
                                                           0,                                            // 7
                                                           &m_Queue                                // 8
                                                           )))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(0 == (status = AudioQueueNewOutput(                              // 1
                                               &m_DataFormat,                          // 2
                                               &AudioQueueBufferCallback,                            // 3
                                               this,                                      // 4
                                               NULL,                                         // 5
                                               kCFRunLoopCommonModes,                        // 6
                                               0,                                            // 7
                                               &m_Queue                                // 8
                                               )))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(0 == (status = AudioQueueNewOutput(                              // 1
                                               &m_DataFormat,                          // 2
                                               &AudioQueueBufferCallback,                            // 3
                                               this,                                      // 4
                                               NULL,                                         // 5
                                               kCFRunLoopCommonModes,                        // 6
                                               0,                                            // 7
                                               &m_Queue                                // 8
                                               )))
            goto Opened;

         if(status !=0)
         {
/*            if(mmr == MMSYSERR_ALLOCATED)
            {
               TRACE("Specified resource is already allocated.");
            }
            else if(mmr == MMSYSERR_BADDEVICEID)
            {
               TRACE("Specified device identifier is out of range.");
            }
            else if(mmr == WAVERR_BADFORMAT)
            {
               TRACE("Attempted to open with an unsupported waveform-audio_core_audio format.");
            }
            TRACE("ERROR OPENING WAVE INPUT DEVICE");*/
            return MMSYSERR_ERROR;
         }

Opened:
         uint32_t uiBufferSizeLog2;
         uint32_t uiBufferSize;
         uint32_t uiAnalysisSize;
         uint32_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         uint32_t uiBufferCount = iBufferCount;

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
         
         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, m_pwaveformat, m_pwaveformat);

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
               return MMSYSERR_ERROR;
            }
            
            m_Buffers.add(buf);

         }*/
         m_estate = state_opened;
         return MMSYSERR_NOERROR;
      }

      ::multimedia::result wave_out::wave_out_open_ex(thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample)
      {
         single_lock sLock(&m_mutex, TRUE);
         if(m_Queue != NULL &&
            m_estate != state_initial)
            return MMSYSERR_NOERROR;
         m_pthreadCallback = pthreadCallback;
         //::multimedia::result mmr;
         ASSERT(m_Queue == NULL);
         ASSERT(m_estate == state_initial);
         
         OSStatus status = 0;

//         m_pwaveformat->wFormatTag        = WAVE_FORMAT_PCM;

         m_pwaveformat->wFormatTag        = 0;
m_pwaveformat->nChannels         = (WORD) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (WORD) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize            = sizeof(m_waveformatex);
         m_pwaveformat->cbSize            = 0;

         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         try
         {
            if(0 == (status = AudioQueueNewOutput(                              // 1
                                                  &m_DataFormat,                          // 2
                                                  &AudioQueueBufferCallback,                            // 3
                                                  this,                                      // 4
                                                  NULL,                                         // 5
                                                  kCFRunLoopCommonModes,                        // 6
                                                  0,                                            // 7
                                                  &m_Queue                                // 8
                                                  )))
               goto Opened;
         }
         catch(const ::exception::exception &)
         {
            return MMSYSERR_ERROR;
         }
         catch(...)
         {
            return MMSYSERR_ERROR;
         }

         if(status != 0)
         {
/*            if(mmr == MMSYSERR_ALLOCATED)
            {
               TRACE("Specified resource is already allocated.");
            }
            else if(mmr == MMSYSERR_BADDEVICEID)
            {
               TRACE("Specified device identifier is out of range.");
            }
            else if(mmr == WAVERR_BADFORMAT)
            {
               TRACE("Attempted to open with an unsupported waveform-audio_core_audio format.");
            }*/
            TRACE("ERROR OPENING WAVE INPUT DEVICE");
            return MMSYSERR_ERROR;
         }

Opened:
         uint32_t uiBufferSizeLog2;
         uint32_t uiBufferSize;
         uint32_t uiAnalysisSize;
         uint32_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         uint32_t uiBufferCount = iBufferCount;

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
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, iBufferSampleCount); 

/*         int32_t i, iSize;
         
         iSize = wave_out_get_buffer()->GetBufferCount();
         
         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr =  waveOutPrepareHeader(m_Queue, create_new_WAVEHDR(wave_out_get_buffer(), i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }

            //wave_out_add_buffer(i);

         }*/

         m_pprebuffer->SetMinL1BufferCount(wave_out_get_buffer()->GetBufferCount() + 4);

         m_estate = state_opened;

         return MMSYSERR_NOERROR;

      }



      ::multimedia::result wave_out::wave_out_close()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate == state_playing)
         {
            wave_out_stop();
         }

         if(m_estate != state_opened)
            return MMSYSERR_NOERROR;
         
         OSStatus status;
         
         free_buffers();

/*         ::multimedia::result mmr;

         int32_t i, iSize;

         iSize =  wave_out_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr = waveOutUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
            }

            delete wave_hdr(i);

         }*/

         status = AudioQueueDispose(m_Queue, 1);

         m_Queue = NULL;

         m_pprebuffer->Reset();

         m_estate = state_initial;

         return MMSYSERR_NOERROR;

      }

/*
      void wave_out::OnMultimediaOpen(signal_details * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }


      void wave_out::OnMultimediaDone(signal_details * pobj)
      {
         
         SCAST_PTR(::message::base, pbase, pobj);
         
         m_iBufferedCount--;

         LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam.m_lparam;

         wave_out_out_buffer_done(lpwavehdr->dwUser);

      }

      void wave_out::OnMultimediaClose(signal_details * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }
*/
      
      /*void wave_out::wave_out_on_buffer_ready(signal_details * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }*/

      
      void wave_out::wave_out_buffer_ready(int iBuffer)
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

         single_lock sLock(&m_mutex, TRUE);
         
         status = AudioQueueEnqueueBuffer(m_Queue, buf, 0, NULL);
         
         VERIFY(status == 0);

         if(status == 0)
         {

            m_iBufferedCount++;

         }

      }

      
      bool wave_out::wave_out_stop()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate != state_playing && m_estate != state_paused)
            return false;

         m_eventStopped.ResetEvent();

         m_pprebuffer->Stop();

         m_estate = state_stopping;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = AudioQueueReset(m_Queue);



         if(m_mmr == MMSYSERR_NOERROR)
         {
            m_estate = state_opened;
         }

         return m_mmr == MMSYSERR_NOERROR;

      }

      bool wave_out::wave_out_pause()
      {

         single_lock sLock(&m_mutex, TRUE);

         ASSERT(m_estate == state_playing);

         if(m_estate != state_playing)
            return false;



         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = AudioQueuePause(m_Queue);


         ASSERT(m_mmr == MMSYSERR_NOERROR);

         if(m_mmr == MMSYSERR_NOERROR)
         {
            m_estate = state_paused;
         }

         return m_mmr == MMSYSERR_NOERROR;

      }

      bool wave_out::wave_out_restart()
      {

         single_lock sLock(&m_mutex, TRUE);

         ASSERT(m_estate == state_paused);

         if(m_estate != state_paused)
            return false;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = AudioQueueStart(m_Queue, NULL);


         ASSERT(m_mmr == MMSYSERR_NOERROR);

         if(m_mmr == MMSYSERR_NOERROR)
         {
            m_estate = state_playing;
         }

         return m_mmr == MMSYSERR_NOERROR;

      }


      imedia::time wave_out::wave_out_get_position_millis()
      {
         
         single_lock sLock(&m_mutex, TRUE);

         OSStatus                status;

         AudioTimeStamp          stamp;

         if(m_Queue != NULL)
         {
            
            status = AudioQueueDeviceGetCurrentTime(m_Queue, &stamp);
            
            if(status != 0)
               return 0;
            
            
            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;
            
            return (imedia::time) stamp.mSampleTime;
            
         }
         else
            return 0;


      }


      imedia::position wave_out::wave_out_get_position()
      {
         
         single_lock sLock(&m_mutex, TRUE);
         
         OSStatus                status;
         
         AudioTimeStamp          stamp;
         
         if(m_Queue != NULL)
         {
            
            status = AudioQueueDeviceGetCurrentTime(m_Queue, &stamp);
            
            if(status != 0)
               return 0;
            
            
            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return 0;
            
            return (imedia::time) stamp.mSampleTime;
            
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
      

      void wave_out::AudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {
         
         wave_out * pwaveout = (wave_out *) inUserData;
         
         pwaveout->AudioQueueBufferCallback(inAQ, inCompleteAQBuffer);
         
      }
      
      
      void wave_out::AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {
         
         if(m_bDone)
            return;
         
         index iBuffer = m_Buffers.find_first(inCompleteAQBuffer);
         
         if(iBuffer < 0)
            return;
         
         wave_out_free((int) iBuffer);
         
      }
      
      
      AudioQueueRef wave_out::wave_out_get_safe_AudioQueueRef()
      {
         
         return m_Queue;
         
      }


   } // namespace audio_core_audio


} // namespace multimedia






