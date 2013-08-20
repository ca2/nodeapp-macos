#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((uint32_t)(WORD)((BYTE)VERSION_MINOR | (((WORD)(BYTE)VERSION_MAJOR) << 8)))

#define MMSG_DONE                   (WM_USER+20)


namespace music
{

   
   namespace midi_mmsystem
   {
      

      class file;
      class sequence;
      class sequence_thread;


      class CLASS_DECL_VERIWELL_MULTIMEDIA midi_callback_data
      {
      public:


         sequence *          m_psequence;


      };


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM sequence :
         virtual public ::music::midi::sequence
      {
      public:

         class buffer_array;


         class buffer
         {
         public:
            
            
            MIDIHDR              m_midihdr;
            primitive::memory    m_storage;
            bool                 m_bPrepared;
            
            bool IsPrepared();
            void Reset();
            void Initialize(int32_t iSize, uint32_t dwUser);

            ::multimedia::result midiStreamOut(HMIDISTRM hmidiout);
            ::multimedia::result midiOutPrepareHeader(HMIDIOUT hmidiout);
            ::multimedia::result midiOutUnprepareHeader(HMIDIOUT hmidiout);


            inline LPMIDIHDR GetMidiHdr() { return &m_midihdr; }

            void SetNextMidiHdr(LPMIDIHDR lpNext);


         };


         class buffer_array :
            public array < buffer, buffer >
         {
         public:


            void Reset();
            void Initialize(int32_t iCount, int32_t iSize, uint32_t dwUser);


            ::multimedia::result midiStreamOut(HMIDISTRM hmidiout);
            ::multimedia::result midiOutPrepareHeader(HMIDIOUT hmidiout);
            ::multimedia::result midiOutUnprepareHeader(HMIDIOUT hmidiout);

         };

         class event :
            public ::music::midi::sequence::event
         {
         public:


            LPMIDIHDR                     m_lpmh;


         };


         buffer_array                  m_buffera;

         HMIDISTRM                     m_hstream;

         midi_callback_data            m_midicallbackdata;




         sequence(sp(::ca2::application) papp);
         virtual ~sequence();


         inline uint32_t GetState();
         inline uint32_t GetPreviousState();
         uint32_t SetState(uint32_t uiState);

         void SetSpecialModeV001Flag(bool bSet = true);

         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);
         void MuteTrack(int32_t iIndex, bool bMute = true);


         virtual int32_t GetDefaultCodePage();

         void Prepare(::ikaraoke::data & data);
         void Prepare(int32_t iTrack, ::ikaraoke::data & data);
         void Prepare(
            string2a & str2a,
            imedia::position_2darray & tka2DTokensTicks,
            int32_t iMelodyTrack,
            int2a & ia2TokenLine,
            ::ikaraoke::data & data);

         imedia::position GetPositionTicks();
         void SetLevelMeter(int32_t iLevel);
         ::multimedia::result CloseStream();
         bool SetMidiOutDevice(uint32_t uiDevice);
         int32_t SetKeyShift(int32_t iKeyShift);
         int32_t GetKeyShift();

         void OnMidiPlaybackEnd(::music::midi::sequence::event * pevent);
         int32_t SetTempoShift(int32_t iTempoShift);

         void OnPositionCB(LPMIDIHDR lpmidihdr);
         void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
         virtual void GetTimeLength(imedia::time & time);
         virtual void GetPositionLength(imedia::position & position);

         using ::ikaraoke::karaoke::TimeToPosition;
         using ::ikaraoke::karaoke::PositionToTime;

         virtual imedia::position TimeToPosition(imedia::time time);
         virtual imedia::time PositionToTime(imedia::position position);

         virtual bool IsOpened();

         virtual bool IsNull();
         virtual void SetTempoChangeFlag(bool bSet = true);
         virtual bool IsChangingTempo();

         virtual int32_t GetTempoShift();
         virtual void GetMidiDoneData(::music::midi::LPMIDIDONEDATA lpmdd);
         virtual bool IsInSpecialModeV001();
         virtual bool WasInSpecialModeV001();
         virtual void SetSpecialModeV001Operation(uint32_t uiOperation);

         virtual void OnEvent(::music::midi::sequence::event * pevent);


         ::multimedia::result AllocBuffers();

         VOID FreeBuffers();

         //::multimedia::result OpenFile(const char * lpFileName, int32_t openMode);
         ::multimedia::result OpenFile(::music::midi::sequence & sequence, int32_t iOpenMode);
         ::multimedia::result OpenFile(::ca2::file & ar, int32_t openMode);
         ::multimedia::result OpenFile(const char * lpFileName, int32_t openMode);
         ::multimedia::result OpenFile(primitive::memory * pmemorystorage, int32_t openMode, ::music::e_storage estorage);

         ::multimedia::result CloseFile();
         ::multimedia::result SaveFile(const char * lpFileName);
         ::multimedia::result SaveFile();
         ::multimedia::result SaveFile(::ca2::filesp &ar);
         ::multimedia::result Preroll(::ca2::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
         ::multimedia::result Start();

         ::multimedia::result Pause();

         ::multimedia::result Restart();

         //::multimedia::result Stop(uint32_t dwEllapse);
         ::multimedia::result Stop();

         void get_position(imedia::position  & time);
         void get_time(imedia::time  & time);

         ::multimedia::result get_ticks(imedia::position & time);
         ::multimedia::result get_millis(imedia::time & time);


         imedia::position MillisecsToTicks(imedia::time msOffset);

         imedia::time TicksToMillisecs(imedia::position tkOffset);

         bool IsPlaying();

         static void CALLBACK MidiOutProc(HMIDIOUT hmo, uint32_t wMsg, uint32_t dwInstance, uint32_t dwParam1, uint32_t dwParam2);
         

         bool IsSettingPosition();
         void SetSettingPositionFlag(bool bSet = TRUE);

         imedia::position GetQuarterNote();


         inline sp(::music::midi_mmsystem::file) file()
         {
            return get_file();
         }

         inline sp(::music::midi_mmsystem::sequence_thread) thread()
         {
            return m_pthread;
         }

         using ::music::midi::sequence::create_new_event;
         virtual ::music::midi::sequence::event * create_new_event(::music::midi::sequence::e_event eevent, LPMIDIHDR lpmidihdr);

      };



   } // namespace midi_mmsystem


} // namespace music







