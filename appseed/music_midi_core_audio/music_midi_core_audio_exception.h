#pragma once

#define MIDIPLAYERSTOPEXCEPTION 10000
#define MIDIPLAYERCLOSEEXCEPTION 10010
#define MIDIPLAYERSAVEEXCEPTION 10020

#define MIDIPLAYERPRERROLLSTREAMOPENEXCEPTION 20020
#define MIDIPLAYERPRERROLLSTREAMPROPERTYEXCEPTION 20030
#define MIDIPLAYERPRERROLLNOMEMORY1EXCEPTION 20040
#define MIDIPLAYERPRERROLLNOMEMORY2EXCEPTION 20050
#define MIDIPLAYERPRERROLLPREPAREHEADEREXCEPTION 20060
#define MIDIPLAYERPRERROLLSTREAMOUTEXCEPTION 20070
#define MIDIPLAYERPRERROLLREADEVENTSEXCEPTION 20080
#define MIDIPLAYERPRERROLLPREPAREHEADER2EXCEPTION 20090
#define MIDIPLAYERPRERROLLSTREAMOUT2EXCEPTION 20100

#pragma once


namespace music
{


   namespace midi_core_midi
   {

/*
      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI exception : 
         virtual public ::music::midi::exception
      {
      public:



         exception(sp(base_application) papp);
         exception(sp(base_application) papp, ::multimedia::e_result mmr, int32_t iAppError);
         exception(sp(base_application) papp, ::music::e_result mfr);
         virtual ~exception();

         string GetUserText();
         void SetUserText(const char * lpsz);
         string GetDetailsText();
         void SetMMResult(::multimedia::e_result mmr);


      };

*/
   } // namespace midi_core_midi


} // namespace music




