#pragma once



#include "app-core/appseed/multimedia/multimedia/multimedia.h"
#include <mmsystem.t.h>


#if defined(_AUDIO_MIXER_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AUDIO_MIXER_MMSYSTEM  CLASS_DECL_IMPORT
#endif





namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      class callback;
      class device;
      class source;
      class destination;
      class thread;
      class audio_mixer;
      class section;


   } // namespace audio_mixer_audio_core


} // namespace multimedia


#include "audio_mixer_audio_core_window.h"
#include "audio_mixer_audio_core_mixer.h"
#include "audio_mixer_audio_core_control.h"
#include "audio_mixer_audio_core_source.h"
#include "audio_mixer_audio_core_destination.h"
#include "audio_mixer_audio_core_device.h"
#include "audio_mixer_audio_core_line_info.h"


#include "audio_mixer_audio_core_callback.h"


#include "audio_mixer_audio_core_thread.h"          


#include "audio_mixer_audio_core_section.h"



#include "audio_mixer_audio_core_factory_exchange.h"








