#include "framework.h"


namespace music
{

   namespace midi_mmsystem
   {

      ::multimedia::result TranslateSMFResult(::music::midi::e_file_result               smfrc)
      {
         switch(smfrc)
         {
         case ::music::midi::Success:
            return MMSYSERR_NOERROR;

         case ::music::midi::ENoMemory:
            return MCIERR_OUT_OF_MEMORY;

         case ::music::midi::EInvalidFile:
         case ::music::midi::EOpenFailed:
         case ::music::midi::EInvalidTrack:
            return MCIERR_INVALID_FILE;

         default:
            return MCIERR_UNSUPPORTED_FUNCTION;
         }
      }



   } // namespace midi_mmsystem


} // namespace music      