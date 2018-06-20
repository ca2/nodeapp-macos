#include "framework.h"


namespace music
{

   namespace midi_core_midi
   {
      
      CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI ::multimedia::e_result translate_os_status(OSStatus status)
      {
         
         switch(status)
         {
            case noErr:
               return ::multimedia::result_success;
            default:
               break;
         }
         return ::multimedia::result_midi_error;
         
      }

/*
      ::multimedia::e_result TranslateSMFResult(::music::e_result               smfrc)
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
      
      */



   } // namespace midi_core_midi


} // namespace music      