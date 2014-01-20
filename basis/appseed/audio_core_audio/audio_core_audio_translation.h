#pragma once


namespace multimedia
{


   namespace audio_core_audio
   {

      

      void translate(AudioStreamBasicDescription & formatex, ::multimedia::audio::wave_format * pwaveformat);
      ::multimedia::e_result translate(OSStatus status);
      
/*
 
      void translate(WAVEHDR & wavehdr, ::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      LPWAVEHDR create_new_WAVEHDR(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      LPWAVEHDR get_os_data(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
 
*/
      

   } // namespace audio_core_audio


} // namespace multimedia





