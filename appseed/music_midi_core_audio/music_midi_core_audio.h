#pragma once


#include "app-veriwell/appseed/multimedia/multimedia/multimedia.h"

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFByteOrder.h>
#include <CoreServices/CoreServices.h>
#include <AudioToolbox/AudioToolbox.h>
#include <AudioToolbox/MusicPlayer.h>
#include <AudioUnit/AudioUnit.h>
#include <CoreMIDI/CoreMIDI.h>
#include <CoreMIDI/MIDIServices.h>


#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI_LIBRARY)
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_IMPORT
#endif


#include "CAStreamBasicDescription.h"
#include "OutputBase.h"
#include "CoreMIDIOutput.h"
#include "AudioUnitOutput.h"
#include "AUOutputBL.h"


//#include "PreferencesData.h"


#include "music_midi_core_audio_translation.h"

#include "music_midi_core_audio_exception.h"

#include "music_midi_core_audio_sequence.h"

#include "player/music_midi_core_audio_player.h"

#include "music_midi_core_audio_file.h"
          
#include "music_midi_core_audio_sequence_thread.h"

#include "music_midi_core_audio_midi.h"

#include "music_midi_core_audio_factory_exchange.h"
