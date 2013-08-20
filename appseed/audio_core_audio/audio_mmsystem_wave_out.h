#pragma once


namespace multimedia
{


   namespace audio_mmsystem
   {


      class  CLASS_DECL_AUDIO_MMSYSTEM wave_out :
         virtual public ::multimedia::audio::wave_out
      {
      public:


         HWAVEOUT                         m_hwaveout;
         WAVEFORMATEX                     m_waveformatex;


         wave_out(sp(::ca2::application) papp);
         virtual ~wave_out();


         void install_message_handling(::ca2::message::dispatch * pinterface);

         virtual imedia::time wave_out_get_position_millis();
         imedia::position wave_out_get_position();
         virtual void wave_out_buffer_ready(int iBuffer);
         virtual void wave_out_buffer_ready(LPWAVEHDR lpwavehdr);

         virtual ::multimedia::result wave_out_open(::ca2::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount);
         virtual ::multimedia::result wave_out_open_ex(::ca2::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample);
         virtual bool wave_out_stop();
         virtual ::multimedia::result wave_out_close();
         virtual bool wave_out_pause();
         virtual bool wave_out_restart();
         virtual void * get_os_data();
         HWAVEOUT wave_out_get_safe_HWAVEOUT();

         virtual void wave_out_on_playback_end();
         virtual void wave_out_free(int iBuffer);
         virtual void wave_out_free(LPWAVEHDR lpwavehdr);

         virtual bool initialize_instance();
         virtual int32_t exit_instance();

         DECL_GEN_SIGNAL(OnMultimediaOpen)
         DECL_GEN_SIGNAL(OnMultimediaDone)
         DECL_GEN_SIGNAL(OnMultimediaClose)

//         virtual void wave_out_out_buffer_done(int iBuffer);
  //       virtual void wave_out_out_buffer_done(LPWAVEHDR lpwavehdr);

         WAVEFORMATEX * wave_format();
         LPWAVEHDR wave_hdr(int iBuffer);

      };


   } // namespace audio_mmsystem


} // namespace multimedia



