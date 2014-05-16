#pragma once


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM line_info :
         virtual public ::multimedia::audio_mixer::line_info
      {
      public:


         MIXERLINE       m_mixerLine;


         line_info(sp(::base::application) papp);
         virtual ~line_info();


      };


   } // namespace audio_mixer_audio_core


} // namespace multimedia









