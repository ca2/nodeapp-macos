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
         
         
//         enum e_message
//         {
//            message_open = WM_APP + 5555,
//         };


         UInt32                                    m_NumPacketsToRead;
         array < AudioStreamPacketDescription * >  m_PacketDescs;
         bool                                      m_bDone;
//         ::manual_reset_event                      m_eventOpened;
         int32_t                                   m_iBufferCount;
         int32_t                                   m_iBufferSampleCount;


         wave_out(sp(::base::application) papp);
         virtual ~wave_out();


         void install_message_handling(::message::dispatch * pinterface);

         virtual imedia::time wave_out_get_position_millis();
         imedia::position wave_out_get_position();
         virtual void wave_out_buffer_ready(int iBuffer);

         virtual ::multimedia::e_result wave_out_open(::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount);
         virtual ::multimedia::e_result wave_out_open_ex(::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample);
         virtual ::multimedia::e_result wave_out_stop();
         virtual ::multimedia::e_result wave_out_close();
         virtual ::multimedia::e_result wave_out_pause();
         virtual ::multimedia::e_result wave_out_restart();
         virtual void * get_os_data();
         AudioQueueRef wave_out_get_safe_AudioQueueRef();
         
         ::multimedia::e_result wave_out_start(const imedia::position & position);
         

         virtual void wave_out_on_playback_end();

         virtual bool initialize_instance();
         virtual int32_t exit_instance();


         void AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);
       
         //int run();
         
         
         virtual void on_run_step();
         
         
         void OnOpen();

      } ;


   } // namespace audio_core_audio


} // namespace multimedia



