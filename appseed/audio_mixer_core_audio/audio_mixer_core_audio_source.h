#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM source :
         virtual public ::multimedia::audio_mixer::source
      {
      public:


         MIXERLINE                     m_mixerline;
         MIXERLINECONTROLS             m_mixerlinecontrols;


         source(sp(base_application) papp);
         source(source & source);
         virtual ~source();


         ::multimedia::e_result mixerGetLineInfo(uint32_t dwSource, uint32_t dwDestination, uint32_t fdwInfo);
         ::multimedia::e_result mixerGetLineInfo(uint32_t dwSource, ::multimedia::audio_mixer::destination * pdestination);

         uint32_t GetLineID();
         const char * GetSZName();
         void update_all_controls();
         MIXERLINECONTROLS & get_mixer_line_controls();
         MIXERLINE & get_mixer_line();
         ::multimedia::audio_mixer::control_array & get_control_array();

         ::multimedia::audio_mixer::device * get_device();

         void SetDestination(::multimedia::audio_mixer::destination * pdestination);
         ::multimedia::audio_mixer::destination * get_destination();

         void OnMixerLineChange();
         //void OnArrayReallocation(void *pNewPointer);
         //::multimedia::e_result GetControl(uint32_t dwControlType, uint32_t dwControlFlags, ::multimedia::audio_mixer::control ** ppControl);
         ::multimedia::e_result GetLineControls();

         inline bool HasV001Controls();

         source & operator = (const source & source);


      };


   } // namespace audio_mixer_audio_core


} // namespace multimedia







