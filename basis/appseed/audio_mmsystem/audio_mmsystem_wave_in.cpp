#include "framework.h"


namespace multimedia
{


   namespace audio_mmsystem
   {


      wave_in::wave_in(sp(::ca2::application) papp) :
         ca2(papp),
         ::ca2::thread(papp),
         ::multimedia::audio::wave_in(papp)
      {
         m_pencoder = NULL;
         m_hwavein = NULL;
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
         set_thread_priority(::ca2::scheduling_priority_highest);
         m_evInitialized.SetEvent();
         return true;
      }

      int32_t wave_in::exit_instance()
      {
         m_eventExitInstance.SetEvent();
         return thread::exit_instance();
      }

      void wave_in::pre_translate_message(::ca2::signal_object * pobj)
      {
         SCAST_PTR(::ca2::message::base, pbase, pobj);
         //ASSERT(GetMainWnd() == NULL);
         if(pbase->m_uiMessage == MM_WIM_OPEN ||
            pbase->m_uiMessage == MM_WIM_CLOSE ||
            pbase->m_uiMessage == MM_WIM_DATA)
         {
            translate_wave_in_message(pbase);
            if(pbase->m_bRet)
               return;
         }
         return thread::pre_translate_message(pbase);
      }

      ::multimedia::result wave_in::wave_in_open(int32_t iBufferCount, int32_t iBufferSampleCount)
      {
         if(m_hwavein != NULL && m_estate != state_initial)
         {
            wave_in_initialize_encoder();
            return MMSYSERR_NOERROR;
         }

         single_lock sLock(&m_mutex, TRUE);
         ::multimedia::result mmr;
         ASSERT(m_hwavein == NULL);
         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();
         m_iBuffer = 0;

         if(MMSYSERR_NOERROR == (mmr = waveInOpen(
            &m_hwavein,
            audiowave->m_uiWaveInDevice,
            wave_format(),
            get_os_int(),
            (uint32_t) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(MMSYSERR_NOERROR == (mmr = waveInOpen(
            &m_hwavein,
            WAVE_MAPPER,
            wave_format(),
            (uint32_t) get_os_int(),
            (uint32_t) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(MMSYSERR_NOERROR == (mmr = waveInOpen(
            &m_hwavein,
            WAVE_MAPPER,
            wave_format(),
            (uint32_t) get_os_int(),
            (uint32_t) 0,
            CALLBACK_THREAD)))
            goto Opened;

         if(mmr !=MMSYSERR_NOERROR)
         {
            if(mmr == MMSYSERR_ALLOCATED)
            {
               TRACE("Specified resource is already allocated.");
            }
            else if(mmr == MMSYSERR_BADDEVICEID)
            {
               TRACE("Specified device identifier is out of range.");
            }
            else if(mmr == WAVERR_BADFORMAT)
            {
               TRACE("Attempted to open with an unsupported waveform-audio_mmsystem format.");
            }
            TRACE("ERROR OPENING WAVE INPUT DEVICE");
            return mmr;
         }

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
         else if(m_pwaveformat->nSamplesPerSec == 11025)
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
         
         int32_t i, iSize;
         
         iSize = (int32_t) wave_in_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {
            
            if(MMSYSERR_NOERROR != (mmr =  waveInPrepareHeader(m_hwavein, create_new_WAVEHDR(wave_in_get_buffer(), i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }

            wave_in_add_buffer(i);

         }

         if(m_pencoder != NULL && !wave_in_initialize_encoder())
         {

            m_estate = state_opened;

            wave_in_close();

            return (::multimedia::result) -1;

         }

         m_estate = state_opened;

         return MMSYSERR_NOERROR;

      }


      ::multimedia::result wave_in::wave_in_close()
      {

         single_lock sLock(&m_mutex, TRUE);

         ::multimedia::result mmr;

         if(m_estate != state_opened && m_estate != state_stopped)
            return MMSYSERR_NOERROR;

         mmr = wave_in_reset();

         int32_t i, iSize;

         iSize = (int32_t) wave_in_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr = waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
               //return mmr;
            }

            delete wave_hdr(i);

         }

         mmr = waveInClose(m_hwavein);

         m_hwavein = NULL;

         m_estate = state_initial;

         return MMSYSERR_NOERROR;

      }

      ::multimedia::result wave_in::wave_in_start()
      {
         single_lock sLock(&m_mutex, TRUE);
         if(m_estate == state_recording)
            return MMSYSERR_NOERROR;
         //ASSERT(m_estate == state_opened || m_estate == state_stopped);
         if(m_estate != state_opened &&
            m_estate != state_stopped)
            return MMSYSERR_NOERROR;
         ::multimedia::result mmr;
         if(MMSYSERR_NOERROR != (mmr = waveInStart(
            m_hwavein)))
         {
            TRACE("ERROR starting INPUT DEVICE ");
            return mmr;
         }
         m_estate = state_recording;
         return MMSYSERR_NOERROR;

      }

      ::multimedia::result wave_in::wave_in_stop()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate != state_recording)
            return MMSYSERR_ERROR;

         ::multimedia::result mmr;

         m_estate = state_stopping;

         try
         {
            if(MMSYSERR_NOERROR != (mmr = waveInStop(m_hwavein)))
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

         return MMSYSERR_NOERROR;

      }


      void CALLBACK wave_in::wave_in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
      {

         UNREFERENCED_PARAMETER(hwi);
         UNREFERENCED_PARAMETER(dwInstance);
         UNREFERENCED_PARAMETER(dwParam1);
         UNREFERENCED_PARAMETER(dwParam2);
         if(uMsg == WIM_DATA)
         {
            ASSERT(FALSE);
            /*      uint32_t msSampleTime = timeGetTime();
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
            //         i = 0;*/
         }
      }

      ::multimedia::result wave_in::wave_in_reset()
      {
         single_lock sLock(&m_mutex, TRUE);
         m_bResetting = true;
         if(m_hwavein == NULL)
         {
            return MMSYSERR_ERROR;
         }

         ::multimedia::result mmr;
         if(m_estate == state_recording)
         {
            if(MMSYSERR_NOERROR != (mmr = wave_in_stop()))
            {
               TRACE("wave_in::Reset error stopping input device");
               return mmr;
            }
         }
         try
         {
            if(MMSYSERR_NOERROR != (mmr = waveInReset(
               m_hwavein)))
            {
               TRACE("wave_in::Reset error resetting input device");
               return mmr;
            }
         }
         catch(...)
         {
         }

         m_estate = state_opened;

         m_bResetting = false;

         return MMSYSERR_NOERROR;

      }


      void wave_in::translate_wave_in_message(::ca2::signal_object * pobj)
      {

         SCAST_PTR(::ca2::message::base, pbase, pobj);

         ASSERT(
            pbase->m_uiMessage == MM_WIM_OPEN ||
            pbase->m_uiMessage == MM_WIM_CLOSE ||
            pbase->m_uiMessage == MM_WIM_DATA);

         if(pbase->m_uiMessage == MM_WIM_DATA)
         {
            
            m_iBuffer--;
            
            uint32_t msSampleTime = timeGetTime();
            
            LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam.m_lparam;

            wave_in_get_buffer()->get_buffer((int32_t) lpwavehdr->dwUser)->OnMultimediaDone();

            m_listenerset.wave_in_data_proc(this, msSampleTime, lpwavehdr->dwUser);

            if(m_pencoder != NULL)
            {
               m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
            }

            if(!wave_in_is_resetting() && wave_in_is_recording())
            {
               wave_in_add_buffer((int32_t) lpwavehdr->dwUser);
            }

         }
         pbase->m_bRet = true;
      }


      ::multimedia::result wave_in::wave_in_add_buffer(int32_t iBuffer)
      {
         
         return wave_in_add_buffer(wave_hdr(iBuffer));

      }


      ::multimedia::result wave_in::wave_in_add_buffer(LPWAVEHDR lpwavehdr)
      {

         ::multimedia::result mmr;

         if(MMSYSERR_NOERROR != (mmr = waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR))))
         {

            TRACE("ERROR OPENING Adding INPUT DEVICE buffer");

         }

         m_iBuffer++;

         return mmr;

      }


      bool wave_in::wave_in_initialize_encoder()
      {

         if(m_pencoder == NULL)
            return false;

         if(!::multimedia::audio::wave_in::wave_in_initialize_encoder())
            return false;

         return true;

      }

      WAVEFORMATEX * wave_in::wave_format()
      {

         translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }

      HWAVEIN wave_in::wave_in_get_safe_HWAVEIN()
      {
         
         if(this == NULL)
            return NULL;

         return m_hwavein;

      }

      void * wave_in::get_os_data()
      {
         return m_hwavein;
      }

      LPWAVEHDR wave_in::wave_hdr(int iBuffer)
      {
         return ::multimedia::audio_mmsystem::get_os_data(wave_in_get_buffer(), iBuffer);
      }


   } // namespace audio_mmsystem


} // namespace multimedia






