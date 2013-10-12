#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO wave_out :
         virtual public toolbox,
         virtual public ::multimedia::audio::wave_out
      {
      public:


         UInt32                                    m_NumPacketsToRead;
         array < AudioStreamPacketDescription * >  m_PacketDescs;
         bool                                      m_bDone;


         wave_out(sp(base_application) papp);
         virtual ~wave_out();


         void install_message_handling(::message::dispatch * pinterface);

         virtual imedia::time wave_out_get_position_millis();
         imedia::position wave_out_get_position();
         virtual void wave_out_buffer_ready(int iBuffer);

         virtual ::multimedia::result wave_out_open(::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount);
         virtual ::multimedia::result wave_out_open_ex(::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample);
         virtual bool wave_out_stop();
         virtual ::multimedia::result wave_out_close();
         virtual bool wave_out_pause();
         virtual bool wave_out_restart();
         virtual void * get_os_data();
         AudioQueueRef wave_out_get_safe_AudioQueueRef();

         virtual void wave_out_on_playback_end();

         virtual bool initialize_instance();
         virtual int32_t exit_instance();


         static void AudioQueueBufferCallback(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);
         
         void AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);
       

      };


   } // namespace audio_core_audio


} // namespace multimedia



