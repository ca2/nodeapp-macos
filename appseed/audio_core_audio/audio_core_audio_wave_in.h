#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO wave_in :
         virtual public toolbox,
         virtual public ::multimedia::audio::wave_in
      {
      public:


         bool                             m_bIsRunning;
         

         wave_in(sp(::aura::application) papp);
         virtual ~wave_in();


         virtual bool wave_in_initialize_encoder() override;

         
         virtual ::multimedia::e_result wave_in_add_buffer(int32_t iBuffer) override;

         
         virtual void * get_os_data();
         
         
         AudioQueueRef wave_in_get_safe_AudioQueueRef();
         
         
         ::multimedia::e_result wave_in_open(int32_t iBufferCount, int32_t iBufferSampleCount) override;
         ::multimedia::e_result wave_in_close() override;
         ::multimedia::e_result wave_in_stop() override;
         ::multimedia::e_result wave_in_start() override;
         ::multimedia::e_result wave_in_reset() override;

         
         virtual bool initialize_thread() override;
         virtual int32_t exit_thread() override;
         virtual void pre_translate_message(::message::message * pmessage) override;
         

         static void HandleInputBuffer(void                                 *aqData,
                                       AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       UInt32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc);
         
         
         void HandleInputBuffer(AudioQueueRef                        inAQ,
                                AudioQueueBufferRef                  inBuffer,
                                const AudioTimeStamp                 *inStartTime,
                                UInt32                               inNumPackets,
                                const AudioStreamPacketDescription   *inPacketDesc);
         
         
      };


   } // namespace audio_core_audio


} // namespace multimedia




