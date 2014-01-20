#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      wave_in::wave_in(sp(base_application) papp) :
         element(papp),
         ::thread(papp),
         wave_base(papp),
         toolbox(papp),
         ::multimedia::audio::wave_in(papp)
      {

         m_pencoder = NULL;
         m_estate = state_initial;
         m_bResetting = false;


      }

      wave_in::~wave_in()
      {
      }

      bool wave_in::initialize_instance()
      {
         TRACE("wave_in::initialize_instance %X\n", get_os_int());
         //SetMainWnd(NULL);
         //ASSERT(GetMainWnd() == NULL);
         ::core::set_thread_priority(::core::scheduling_priority_highest);
         m_evInitialized.SetEvent();
         
         
         if(!::multimedia::audio::wave_in::initialize_instance())
            return false;
         
         
         
         if(!toolbox::initialize_instance())
            return false;

         
         return true;
      }

      int32_t wave_in::exit_instance()
      {
         m_eventExitInstance.SetEvent();
         return thread::exit_instance();
      }

      void wave_in::pre_translate_message(signal_details * pobj)
      {
         SCAST_PTR(::message::base, pbase, pobj);
         //ASSERT(GetMainWnd() == NULL);
/*         if(pbase->m_uiMessage == MM_WIM_OPEN ||
            pbase->m_uiMessage == MM_WIM_CLOSE ||
            pbase->m_uiMessage == MM_WIM_DATA)
         {
            translate_wave_in_message(pbase);
            if(pbase->m_bRet)
               return;
         }*/
         return thread::pre_translate_message(pbase);
      }

      ::multimedia::e_result wave_in::wave_in_open(int32_t iBufferCount, int32_t iBufferSampleCount)
      {
         
         if(m_Queue != NULL && m_estate != state_initial)
         {
            wave_in_initialize_encoder();
            return ::multimedia::result_success;
         }
         
         
         return ::multimedia::result_error;

         single_lock sLock(&m_mutex, TRUE);
         ASSERT(m_Queue == NULL);
         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag = 0;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();
         m_iBuffer = 0;

         if(::multimedia::result_success == (m_mmr  = translate(AudioQueueNewInput(                              // 1
                                                          &m_dataformat,                          // 2
                                                          &HandleInputBuffer,                            // 3
                                                          this,                                      // 4
                                                          NULL,                                         // 5
                                                          kCFRunLoopCommonModes,                        // 6
                                                          0,                                            // 7
                                                          &m_Queue                                // 8
                                                          ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::multimedia::result_success == (m_mmr  = translate(AudioQueueNewInput(                              // 1
                                                            &m_dataformat,                          // 2
                                                            &HandleInputBuffer,                            // 3
                                                            this,                                      // 4
                                                            NULL,                                         // 5
                                                            kCFRunLoopCommonModes,                        // 6
                                                            0,                                            // 7
                                                            &m_Queue                                // 8
                                                            ))))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(::multimedia::result_success == (m_mmr  = translate(AudioQueueNewInput(                              // 1
                                                            &m_dataformat,                          // 2
                                                            &HandleInputBuffer,                            // 3
                                                            this,                                      // 4
                                                            NULL,                                         // 5
                                                            kCFRunLoopCommonModes,                        // 6
                                                            0,                                            // 7
                                                            &m_Queue                                // 8
                                                            ))))
            goto Opened;

         return m_mmr;

Opened:
         uint32_t uiBufferSizeLog2;
         uint32_t uiBufferSize;
         uint32_t uiAnalysisSize;
         uint32_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;

         if(m_pwaveformat->nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiBufferSize;
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
            uiBufferSizeLog2 = 9;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 600;
            uiSkippedSamplesCount = 1;
         }
//         else if(m_pwaveformat->nSamplesPerSec == 11025)
         else
         {
            uiBufferSizeLog2 = 9;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 600;
            uiSkippedSamplesCount = 1;
         }
         wave_in_get_buffer()->FFTOpen(
            uiAllocationSize,
            uiBufferSize,
            uiAnalysisSize,
            uiInterestSize,
            uiSkippedSamplesCount);
         
/*         int32_t i, iSize;
         
         iSize = (int32_t) wave_in_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {
            
            if(::multimedia::result_success != (mmr =  waveInPrepareHeader(m_Queue, create_new_WAVEHDR(wave_in_get_buffer(), i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }

            wave_in_add_buffer(i);

         }*/

         if(m_pencoder != NULL && !wave_in_initialize_encoder())
         {

            m_estate = state_opened;

            wave_in_close();

            return (::multimedia::e_result) -1;

         }

         m_estate = state_opened;

         return ::multimedia::result_success;

      }


      ::multimedia::e_result wave_in::wave_in_close()
      {

         single_lock sLock(&m_mutex, TRUE);

         ::multimedia::e_result mmr;

         if(m_estate != state_opened && m_estate != state_stopped)
            return ::multimedia::result_success;

         mmr = wave_in_reset();
         
         
         free_buffers();

/*         int32_t i, iSize;

         iSize = (int32_t) wave_in_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {

            if(::multimedia::result_success != (mmr = waveInUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
               //return mmr;
            }

            delete wave_hdr(i);

         }*/

         m_mmr = translate(AudioQueueDispose(m_Queue, 1));
         
         m_Queue = NULL;

         m_estate = state_initial;

         return mmr;

      }

      
      ::multimedia::e_result wave_in::wave_in_start()
      {

         single_lock sLock(&m_mutex, TRUE);
         
         if(m_estate == state_recording)
            return ::multimedia::result_success;
         
         if(m_estate != state_opened && m_estate != state_stopped)
            return ::multimedia::result_success;
         
         if(::multimedia::result_success != (m_mmr = translate(AudioQueueStart(m_Queue, NULL))))
         {
            
            TRACE("ERROR starting INPUT DEVICE ");
            
            return m_mmr;
            
         }
         
         m_estate = state_recording;
         
         return ::multimedia::result_success;

      }

      
      ::multimedia::e_result wave_in::wave_in_stop()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate != state_recording)
            return ::multimedia::result_error;

         OSStatus status;

         m_estate = state_stopping;

         try
         {
            if(0 != (status = AudioQueueStop(m_Queue, 1)))
            {
               TRACE("wave_in::wave_in_stop : ERROR OPENING stopping INPUT DEVICE ");
            }
         }
         catch(...)
         {
            TRACE("wave_in::wave_in_stop : Exception OPENING stopping INPUT DEVICE ");
         }
         m_estate = state_stopped;

         m_eventStopped.SetEvent();

         return ::multimedia::result_success;

      }

/*
      void CALLBACK wave_in::wave_in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
      {

         UNREFERENCED_PARAMETER(hwi);
         UNREFERENCED_PARAMETER(dwInstance);
         UNREFERENCED_PARAMETER(dwParam1);
         UNREFERENCED_PARAMETER(dwParam2);
         if(uMsg == WIM_DATA)
         {
            ASSERT(FALSE);
                 uint32_t msSampleTime = timeGetTime();
            thread * pthread = (thread *) dwInstance;
            ASSERT(pthread != NULL);
            LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
            LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
            lpxfwm->bDelete = TRUE;
            lpxfwm->msSampleTime = msSampleTime;
            //      lpxfwm->tkSamplePosition = tkPosition;
            lpxfwm->lpWaveHdr = lpWaveHdr;
            pthread->post_thread_message(
            WM_USER,
            (WPARAM) WAVM_WAVE_PROC_DATA,
            (LPARAM) lpxfwm);
            //      i++;
            //      if( i > 2)
            //         i = 0;
//         }
  //    }*/

      ::multimedia::e_result wave_in::wave_in_reset()
      {
         single_lock sLock(&m_mutex, TRUE);
         m_bResetting = true;
         if(m_Queue == NULL)
         {
            return ::multimedia::result_error;
         }

         ::multimedia::e_result mmr;
//         OSStatus status;
         if(m_estate == state_recording)
         {
            if(::multimedia::result_success != (mmr = wave_in_stop()))
            {
               TRACE("wave_in::Reset error stopping input device");
               return mmr;
            }
         }
         try
         {
//            if(0 != (status = AudioQueueReset(m_Queue)))
            if(0 != (AudioQueueReset(m_Queue)))
            {
               TRACE("wave_in::Reset error resetting input device");
               return ::multimedia::result_error;
            }
         }
         catch(...)
         {
         }
         
         m_estate = state_opened;

         m_bResetting = false;

         return mmr;

      }



      ::multimedia::e_result wave_in::wave_in_add_buffer(int32_t iBuffer)
      {
         
         AudioQueueBufferRef buf = audio_buffer(iBuffer);
         
         AudioQueueEnqueueBuffer(m_Queue, buf, 0, NULL);
         
         return ::multimedia::result_success;

      }





      bool wave_in::wave_in_initialize_encoder()
      {

         if(m_pencoder == NULL)
            return false;

         if(!::multimedia::audio::wave_in::wave_in_initialize_encoder())
            return false;

         return true;

      }

     
      AudioQueueRef wave_in::wave_in_get_safe_AudioQueueRef()
      {
         
         if(this == NULL)
            return NULL;

         return m_Queue;

      }

      
      void * wave_in::get_os_data()
      {
         
         return m_Queue;
         
      }

      
      void wave_in::HandleInputBuffer(void                                 *aqData,
                                     AudioQueueRef                        inAQ,
                                     AudioQueueBufferRef                  inBuffer,
                                     const AudioTimeStamp                 *inStartTime,
                                     UInt32                               inNumPackets,
                                     const AudioStreamPacketDescription   *inPacketDesc)
      {
         
         wave_in * pwavein = (wave_in *) aqData;               // 1
         
         pwavein->HandleInputBuffer(inAQ, inBuffer, inStartTime, inNumPackets, inPacketDesc);
         
      }
      
      
      void wave_in::HandleInputBuffer( AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       UInt32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc)
      {

         if(inNumPackets == 0 && m_dataformat.mBytesPerPacket != 0)
            inNumPackets = inBuffer->mAudioDataByteSize / m_dataformat.mBytesPerPacket;
         
         m_iBuffer--;
            
         uint32_t msSampleTime = get_tick_count();
         
         int iBuffer = (int) m_Buffers.find_first(inBuffer);
            
         m_listenerset.wave_in_data_proc(this, msSampleTime, iBuffer);
            
         if(m_pencoder != NULL)
         {
         
            m_pencoder->EncoderWriteBuffer(inBuffer->mAudioData, inBuffer->mAudioDataByteSize);
            
         }
            
         if(!wave_in_is_resetting() && wave_in_is_recording())
         {
         
            wave_in_add_buffer(iBuffer);
         
         }
         
         
         if (m_bIsRunning == 0)                                         // 5
            return;
         
         
      }
      

   } // namespace audio_core_audio


} // namespace multimedia






