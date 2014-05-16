#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM destination :
         virtual public ::multimedia::audio_mixer_audio_core::source,
         virtual public ::multimedia::audio_mixer::destination
      {
      public:


         destination(sp(::base::application) papp);
         destination(const destination & destination);
         virtual ~destination();


         uint32_t get_component_type();
         void update_all_controls();
         ::multimedia::e_result initialize_all_controls();
         ::multimedia::e_result initialize_source_info();

         ::multimedia::audio_mixer::source_array & get_source_info();
         void operator delete(void *);

         destination & operator = (const destination & device);

         ::multimedia::audio_mixer::device * get_device();
         void set_device(::multimedia::audio_mixer::device * pdevice);


         virtual uint32_t get_mixer_line_id();

      };


   } // namespace audio_mixer_audio_core



} // namespace multimedia




