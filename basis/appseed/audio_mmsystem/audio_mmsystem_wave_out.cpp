#include "framework.h"


namespace multimedia
{


   namespace audio_mmsystem
   {


      wave_out::wave_out(sp(::ca2::application) papp) :
         ca2(papp),
         ::ca2::thread(papp),
         ::multimedia::audio::wave_out(papp)
      {
         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_hwaveout           = NULL;
         m_iBufferedCount     = 0;
         m_mmr                = MMSYSERR_NOERROR;
         m_peffect            = NULL;
         m_dwLostSampleCount  = 0;
      }

      wave_out::~wave_out()
      {

      }

      void wave_out::install_message_handling(::ca2::message::dispatch * pinterface)
      {

         ::multimedia::audio::wave_out::install_message_handling(pinterface);

         IGUI_WIN_MSG_LINK(MM_WOM_OPEN, pinterface, this, &wave_out::OnMultimediaOpen);
         IGUI_WIN_MSG_LINK(MM_WOM_DONE, pinterface, this, &wave_out::OnMultimediaDone);
         IGUI_WIN_MSG_LINK(MM_WOM_CLOSE, pinterface, this, &wave_out::OnMultimediaClose);

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
         if(m_hwaveout != NULL &&
            m_estate != state_initial)
            return MMSYSERR_NOERROR;
         m_pthreadCallback = pthreadCallback;
         ::multimedia::result mmr;
         ASSERT(m_hwaveout == NULL);
         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(multimedia::audio::WAVEBUFFERDATA) * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
            &m_hwaveout,
            audiowave->m_uiWaveInDevice,
            wave_format(),
            get_os_int(),
            (uint32_t) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
            &m_hwaveout,
            WAVE_MAPPER,
            wave_format(),
            (uint32_t) get_os_int(),
            (uint32_t) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
            &m_hwaveout,
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
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         
         wave_out_get_buffer()->PCMOutOpen(uiBufferSize, uiBufferCount, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(
            this, // callback thread (thread)
            m_pwaveformat->nChannels, // channel count
            uiBufferCount, // group count
            iBufferSampleCount); // group sample count

         int32_t i, iSize;
         iSize = wave_out_get_buffer()->GetBufferCount();
         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr =  waveOutPrepareHeader(m_hwaveout, create_new_WAVEHDR(m_pwavebuffer, i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }
         }
         m_estate = state_opened;
         return MMSYSERR_NOERROR;
      }

      ::multimedia::result wave_out::wave_out_open_ex(thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample)
      {
         single_lock sLock(&m_mutex, TRUE);
         if(m_hwaveout != NULL &&
            m_estate != state_initial)
            return MMSYSERR_NOERROR;
         m_pthreadCallback = pthreadCallback;
         ::multimedia::result mmr;
         ASSERT(m_hwaveout == NULL);
         ASSERT(m_estate == state_initial);

         m_pwaveformat->wFormatTag        = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels         = (WORD) uiChannelCount;
         m_pwaveformat->nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample    = (WORD) uiBitsPerSample;
         m_pwaveformat->nBlockAlign       = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec   = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize            = sizeof(m_waveformatex);

         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         try
         {
            if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
               &m_hwaveout,
               audiowave->m_uiWaveInDevice,
               wave_format(),
               get_os_int(),
               (uint32_t) 0,
               CALLBACK_THREAD)))
               goto Opened;
         }
         catch(const ::ca2::exception &)
         {
            return MMSYSERR_ERROR;
         }
         catch(...)
         {
            return MMSYSERR_ERROR;
         }

         if(mmr != MMSYSERR_NOERROR)
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

         wave_out_get_buffer()->PCMOutOpen(uiBufferSize, uiBufferCount, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, uiBufferCount, iBufferSampleCount); 

         int32_t i, iSize;
         
         iSize = wave_out_get_buffer()->GetBufferCount();
         
         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr =  waveOutPrepareHeader(m_hwaveout, create_new_WAVEHDR(wave_out_get_buffer(), i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }

            //wave_out_add_buffer(i);

         }

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

         ::multimedia::result mmr;

         int32_t i, iSize;

         iSize =  wave_out_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {

            if(MMSYSERR_NOERROR != (mmr = waveOutUnprepareHeader(m_hwaveout, wave_hdr(i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
            }

            delete wave_hdr(i);

         }

         mmr = waveOutClose(m_hwaveout);

         m_hwaveout = NULL;

         m_pprebuffer->Reset();

         m_estate = state_initial;

         return MMSYSERR_NOERROR;

      }


      void wave_out::OnMultimediaOpen(::ca2::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }


      void wave_out::OnMultimediaDone(::ca2::signal_object * pobj)
      {
         
         SCAST_PTR(::ca2::message::base, pbase, pobj);
         
         m_iBufferedCount--;

         LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam.m_lparam;

         wave_out_out_buffer_done(lpwavehdr->dwUser);

      }

      void wave_out::OnMultimediaClose(::ca2::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      /*void wave_out::wave_out_on_buffer_ready(::ca2::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }*/

      void wave_out::wave_out_buffer_ready(int iBuffer)
      {
         
         return wave_out_buffer_ready(wave_hdr(iBuffer));

      }

      void wave_out::wave_out_buffer_ready(LPWAVEHDR lpwavehdr)
      {

         if(wave_out_get_state() != state_playing)
         {
            TRACE("ERROR wave_out::BufferReady while wave_out_get_state() != state_playing");
            return;
         }

         ::multimedia::result mmr;
         if(m_peffect != NULL)
         {
            m_peffect->Process16bits((int16_t *) lpwavehdr->lpData, lpwavehdr->dwBytesRecorded / 2);
         }

         single_lock sLock(&m_mutex, TRUE);
         
         mmr = waveOutWrite(m_hwaveout, lpwavehdr, sizeof(WAVEHDR));
         
         VERIFY(MMSYSERR_NOERROR == mmr);

         if(mmr == MMSYSERR_NOERROR)
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
         // waveform-audio_mmsystem output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = waveOutReset(m_hwaveout);



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
         // waveform-audio_mmsystem output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = waveOutPause(m_hwaveout);


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
         // waveform-audio_mmsystem output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = waveOutRestart(m_hwaveout);


         ASSERT(m_mmr == MMSYSERR_NOERROR);

         if(m_mmr == MMSYSERR_NOERROR)
         {
            m_estate = state_playing;
         }

         return m_mmr == MMSYSERR_NOERROR;

      }


      /*imedia::time wave_out::GetPositionMillisForSynch()
      {
         int64_t dwMillis = GetPositionMillis();
         int64_t dwPosition = m_pprebuffer->m_position * 8;
         dwPosition /= m_pwaveformat->wBitsPerSample;
         dwPosition *= 1000;
         dwPosition /= m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
            return dwMillis + dwPosition - m_pprebuffer->m_pdecoder->DecoderGetLostMillis(dwMillis + dwPosition) - (((int64_t) m_dwLostSampleCount) /  ((int64_t) m_pwaveformat->nSamplesPerSec));
         else
            return dwMillis + dwPosition - ((m_dwLostSampleCount) * 1000 / m_pwaveformat->nSamplesPerSec);
      }*/

      imedia::time wave_out::wave_out_get_position_millis()
      {
         single_lock sLock(&m_mutex, TRUE);



         ::multimedia::result                mmr;
         MMTIME                  mmt;
         mmt.wType = TIME_MS;

         if(m_hwaveout != NULL)
         {
            mmr = waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt));
            try
            {
               if (MMSYSERR_NOERROR != mmr)
               {
                  TRACE( "waveOutGetPosition() returned %lu", (uint32_t)mmr);
                  //      return MCIERR_DEVICE_NOT_READY;
                  return 0;
               }
            }
            catch(...)
            {
               //return MCIERR_DEVICE_NOT_READY;
               return 0;
            }
            if(mmt.wType == TIME_BYTES)
            {
               int64_t i = mmt.u.cb;
               i *= 8 * 1000;
               i /= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
               return i;

            }
            else
            {
               //*pTicks += mmt.u.ticks;
               return (uint32_t) mmt.u.ms;
            }
         }
         else
            return 0;


      }

      /*imedia::position wave_out::get_position_for_synch()
      {
         imedia::position position = get_position();
         if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
            return m_pprebuffer->m_position + position - m_pprebuffer->m_pdecoder->DecoderGetLostPositionOffset(position) - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         else
            return m_pprebuffer->m_position + position - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
      }*/

      imedia::position wave_out::wave_out_get_position()
      {
         single_lock sLock(&m_mutex, TRUE);

         ::multimedia::result                mmr;
         MMTIME                  mmt;
         mmt.wType = TIME_BYTES;

         if(m_hwaveout != NULL)
         {
            mmr = waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt));
            try
            {
               if (MMSYSERR_NOERROR != mmr)
               {
                  TRACE( "waveOutGetPosition() returned %lu", (uint32_t)mmr);
                  return 0;
               }
            }
            catch(...)
            {
               return 0;
            }
            if(mmt.wType == TIME_MS)
            {
               imedia::position position = (uint32_t) mmt.u.ms;
               position *= m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
               position /= 8 * 1000;
               return position;
            }
            else
            {
               return (uint32_t) mmt.u.cb;
            }
         }
         else
            return 0;

      }

      void wave_out::wave_out_free(int iBuffer)
      {

         wave_out_free(wave_hdr(iBuffer));

         multimedia::audio::wave_out::wave_out_free(iBuffer);

      }


      void wave_out::wave_out_free(LPWAVEHDR lpwavehdr)
      {


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



      WAVEFORMATEX * wave_out::wave_format()
      {

         translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }

      HWAVEOUT wave_out::wave_out_get_safe_HWAVEOUT()
      {
         
         if(this == NULL)
            return NULL;

         return m_hwaveout;

      }

      void * wave_out::get_os_data()
      {
         return m_hwaveout;
      }

      LPWAVEHDR wave_out::wave_hdr(int iBuffer)
      {
         return ::multimedia::audio_mmsystem::get_os_data(wave_out_get_buffer(), iBuffer);
      }


   } // namespace audio_mmsystem


} // namespace multimedia






