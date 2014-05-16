#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM device :
         virtual public ::multimedia::audio_mixer::device
      {
      public:


         HMIXER                        m_hMixer;
         MIXERCAPS                     m_mixercaps;


         device(sp(::base::application) papp);
         virtual ~device();

         virtual bool initialize(::multimedia::audio_mixer::audio_mixer * pmixer);

         ::multimedia::audio_mixer::audio_mixer * get_mixer();
         const char * GetSZPName();
         bool OnCommand(WPARAM wparam, LPARAM lparam);
         ::multimedia::e_result close();
         void MapDlgCtrlIDToLineControls(::multimedia::audio_mixer::source * pSource);
         void MapDlgCtrlIDToControls();
         void MapLineControls(::multimedia::audio_mixer::source * pSource);
         void OnMixerControlChange(uint32_t dwControlID);
         void OnMixerLineChange(uint32_t dwLineID);
         void map_lines();
         void map_controls();
         ::multimedia::e_result get_destination(::multimedia::audio_mixer::e_destination edestination, ::multimedia::audio_mixer::destination ** ppDestination);
         ::multimedia::e_result initialize_destinations();
         ::multimedia::e_result initialize_capabilities();
         ::multimedia::e_result open(uint32_t uiMixerId, uint32_t dwCallback, uint32_t dwInstance, uint32_t fdwOpen);


      };


   } // namespace audio_mixer_audio_core


} // namespace multimedia





