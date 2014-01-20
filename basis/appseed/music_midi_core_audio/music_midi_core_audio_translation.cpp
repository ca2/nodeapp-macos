#include "framework.h"


namespace music
{

   namespace midi_core_audio
   {

      ::multimedia::e_result TranslateSMFResult(::music::midi::file::e_result               smfrc)
      {
         switch(smfrc)
         {
         case ::music::midi::Success:
            return MMSYSERR_NOERROR;

         case ::music::midi::file::ENoMemory:
            return MCIERR_OUT_OF_MEMORY;

         case ::music::midi::file::EInvalidFile:
         case ::music::midi::file::EOpenFailed:
         case ::music::midi::file::EInvalidTrack:
            return MCIERR_INVALID_FILE;

         default:
            return MCIERR_UNSUPPORTED_FUNCTION;
         }
      }



   } // namespace midi_core_audio


} // namespace music      