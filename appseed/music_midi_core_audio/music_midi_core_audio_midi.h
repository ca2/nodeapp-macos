#pragma once


namespace music
{


   namespace midi
   {
      
      namespace port
      {


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI midi :
         virtual public ::music::midi::midi
      {
      public:


         midi(::aura::application * papp);
         virtual ~midi();


         virtual ::multimedia::e_result enumerate_midi_devices();


         //void RemoveListener(midi_listener * plistener);
         //void AddListener(midi_listener * plistener);
         //uint32_t GetMidiOutDevice();
         //void SetMidiOutDevice(uint32_t uiDevice);
         //bool Initialize();


         //bool IsSoftKaraokeFile(const char * lpszPathName);
         //bool IsXFFile(const char * lpcszPathName);


         //virtual bool veriwell_multimedia_music_midi_factory_exchange();


/*            void mmsystem_LogMidiInCaps(UINT i, MIDIINCAPSW caps);
         void mmsystem_GetMidiInDeviceInterface(UINT i);
         void mmsystem_LogMidiOutCaps(UINT i, MIDIOUTCAPSW caps);
         void mmsystem_GetMidiOutDeviceInterface(UINT i);*/

         using ::music::midi::midi::translate_os_result;
         virtual ::multimedia::e_result translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, int64_t iOsResult, const string & strContext, const string & strText);


      };
         
         
      } // namespace port


   } // namespace midi


} // namespace music




