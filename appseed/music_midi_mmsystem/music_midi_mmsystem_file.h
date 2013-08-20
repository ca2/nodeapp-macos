#pragma once


#define C_TEMPO_MAP_CHK     16


namespace music
{


   namespace midi_mmsystem
   {

      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM file :
         virtual public ::music::midi::file
      {
      public:



         file(sp(::ca2::application) papp);
         virtual ~file();


         double GetTempoShiftRate();

         bool IsTrackMute(int32_t iIndex);

         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);

         void MuteTrack(int32_t iIndex, bool bMute = true);

         ::music::midi::e_file_result WorkSeekBegin();

         ::music::midi::e_file_result CalcTkLength();

         ::music::midi::e_file_result CreateTempoMap();

         ::multimedia::result ImmediatePutTempoChange();

         VMSRESULT GetTempoEvent(::music::midi::event_base & event);

         void OnStop();

         uint32_t GetImageSize();

         LPBYTE GetImage();

         VMSRESULT Format0();

         VMSRESULT InsertTempoEvent();

         ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia::position & position);

         int32_t GetTempoShift();

         VMSRESULT SetTempoShift(int32_t iTempoShift);

         void ToWorkStorage();

         void FromWorkStorage();

         int32_t GetKeyShift();

         int32_t SetKeyShift(int32_t iKeyShift);

         bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);

         bool IsXFFile();

         bool IsTune1000File();

         bool IsOpened();
         
         ::music::midi::e_file_result RebuildIndex();

         ::music::midi::e_file_result WriteHeader(MIDIFILEHDR * lpmfh);

         ::music::midi::e_file_result ChangeEventDelta(::music::midi::event_base *pEvent, imedia::position tkNewDelta);

         ::music::midi::e_file_result ReplaceSameDeltaEvent(::music::midi::event_base & pEventNew);

         ::music::midi::e_file_result GetPreviousEvent(::music::midi::event_base * pPreviousEvent, ::music::midi::event_base * pEvent);

         ::music::midi::e_file_result SaveFile(const char * lpFilePath);

         ::music::midi::e_file_result WorkWriteXFTracks(stringa & tokena, imedia::position_array & positiona, ::music::xf::info_header & xfinfoheader);

         int32_t CalcMelodyTrack(::music::midi::events_v1 ** ppEvents, imedia::position_array * pTicks);

         int32_t WorkCalcMelodyTrack(::music::midi::events_v1 ** ppEvents, imedia::position_array & positiona, int_array & iaTokenLine);

         int32_t GetFormat();

         ::music::midi::e_file_result MergeTracks();

         ::music::midi::e_file_result WorkMergeTracks();

         ::music::midi::e_file_result WorkStreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         ::music::midi::e_file_result WorkGetNextEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::e_file_result WorkGetNextRawEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::e_file_result WorkGetNextRawMidiEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::e_file_result WorkSeek(::imedia::position tkPosition, LPMIDIHDR lpmh);

         void delete_contents();

         int32_t GetDivision();

         imedia::position get_position();

         void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);

         bool IsNull();

         void WorkSeekEnd();

         ::music::midi::e_file_result OpenFile(::music::midi::file &file, int32_t openMode);

         ::music::midi::e_file_result OpenFile(::ca2::file & file, int32_t openMode);

         ::music::midi::e_file_result OpenFile(primitive::memory * pmemstorage, int32_t openMode, ::music::e_storage);

         ::music::midi::e_file_result OpenFile(primitive::memory * pmemstorage, ::music::midi::e_file_open_mode eopenmode, ::music::e_storage estorage);

         ::music::midi::e_file_result SaveFile(::ca2::file & file);

         ::music::midi::e_file_result CloseFile();

         ::music::midi::e_file_result GetFileInfo(PSMFFILEINFO psfi);

         int_ptr TicksToMillisecs(imedia::position tkOffset);

         void TicksToMillisecs(imedia::time_array *pMillisArray, imedia::position_array *pTickArray, int_ptr tkOffset);

         void TicksToMillisecs(imedia::time_2darray *p2DMillisArray, imedia::position_2darray * p2DTicksArray, int_ptr tkOffset);

         void PositionToTime(imedia::time_2darray  & timea, imedia::position_2darray  & positiona, int_ptr tkOffset);

         void PositionToTime(imedia::time_array  & timea, imedia::position_array  & positiona, int_ptr tkOffset);

         imedia::position MillisecsToTicks(imedia::time msOffset);

         imedia::time PositionToTime(imedia::position msOffset);

         imedia::position TimeToPosition(imedia::time msOffset);

         void MillisecsToTicks(imedia::position_array * pTickArray, imedia::time_array *pMillisArray, imedia::time msOffset);

         void TimeToPosition(imedia::position_array & positiona, imedia::time_array & timea, imedia::time msOffset);

         ::music::midi::e_file_result StreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         VMSRESULT StreamEvent(imedia::position tkDelta, ::music::midi::event_base * Event, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         VMSRESULT StreamEventF1(imedia::position tkDelta, array < ::music::midi::event_v5 *, ::music::midi::event_v5 * > & eventptra, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         ::music::midi::e_file_result seek(imedia::position tkPosition, LPMIDIHDR lpmh);

         ::music::midi::e_file_result seek(imedia::position tkPosition);

         ::music::midi::e_file_result Build();

         ::music::midi::e_file_result GetNextEvent(::music::midi::event_v1 *& pevent, imedia::position tkMax, bool   bTkMaxInclusive);

         ::music::midi::e_file_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

         void _SyncSeek(imedia::position tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);

         void _SyncSeek(imedia::position tkPosition);

         ::music::midi::e_file_result InsertParmData(imedia::position tkDelta, LPMIDIHDR lpmh);

         VMSRESULT InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);

         ::music::midi::e_file_result InsertPadEvent(imedia::position tkDelta, LPMIDIHDR lpmh);

         void SetOpened(bool bOpened = true);


      };


   } // namespace midi_mmsystem


} // namespace music





