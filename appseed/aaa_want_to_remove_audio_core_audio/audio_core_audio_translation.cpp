#include "framework.h"


namespace multimedia
{

   
   namespace audio_core_audio
   {
      
      
      void translate(AudioStreamBasicDescription & waveformatex, ::multimedia::audio::wave_format * pwaveformat)
      {
         
         ZERO(waveformatex);
         waveformatex.mReserved         = 0;
         FillOutASBDForLPCM (
                                         waveformatex,
                                         (Float64) pwaveformat->nSamplesPerSec,
                                         pwaveformat->nChannels,
                                         8 * sizeof(::multimedia::audio::WAVEBUFFERDATA),
                                         8 * sizeof(::multimedia::audio::WAVEBUFFERDATA),
                                         false,
                             false);


/*         waveformatex.mSampleRate       = (Float64) ;
         waveformatex.mFormatID         = kAudioFormatLinearPCM;
         waveformatex.mFormatFlags      = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked | kAudioFormatFlagsNativeEndian;
         waveformatex.mChannelsPerFrame = ;
         waveformatex.mBytesPerFrame    = waveformatex.mChannelsPerFrame * sizeof(::multimedia::audio::WAVEBUFFERDATA);
         waveformatex.mFramesPerPacket  = 1;
         waveformatex.mBytesPerPacket   = waveformatex.mBytesPerFrame * waveformatex.mFramesPerPacket;
         waveformatex.mBitsPerChannel   = 8 * sizeof(::multimedia::audio::WAVEBUFFERDATA);
         waveformatex.mReserved         = 0;
  
 */
      }
      
      
      ::multimedia::e_result translate(OSStatus status)
      {
         
         switch(status)
         {
         case 0:
            return ::multimedia::result_success;
               
         case kAudioFormatUnsupportedDataFormatError:
            return ::multimedia::result_bad_format;
               
         default:
            return ::multimedia::result_error;
            
         };
         
      }


      /*

      void translate(WAVEHDR & wavehdr, ::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwavebuffer->get_buffer(iBuffer);
            
         pbuffer->m_posdata            = &wavehdr;

         wavehdr.lpData                = (LPSTR) pbuffer->m_pData;
         wavehdr.dwBufferLength        = pwavebuffer->m_uiBufferSize;
         wavehdr.dwBytesRecorded       = 0;
         wavehdr.dwUser                = pbuffer->m_iIndex;
         wavehdr.dwFlags               = 0;

      }


      LPWAVEHDR create_new_WAVEHDR(::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {

         LPWAVEHDR lpwavehdr = new WAVEHDR;

         translate(*lpwavehdr, pwavebuffer, iBuffer);

         return lpwavehdr;

      }

      LPWAVEHDR get_os_data(::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {
         
         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwavebuffer->get_buffer(iBuffer);

         LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

         return pwavehdr;

      }
       
*/


   } // namespace audio_core_audio


} // namespace multimedia




