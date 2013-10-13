#pragma once


#define C_TEMPO_MAP_CHK     16


namespace music
{


   namespace midi_core_audio
   {

      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_MMSYSTEM file :
         virtual public ::music::midi::file::buffer
      {
      public:



         file(sp(base_application) papp);
         virtual ~file();


         double GetTempoShiftRate();

         bool IsTrackMute(int32_t iIndex);

         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);

         void MuteTrack(int32_t iIndex, bool bMute = true);

         ::music::midi::file::e_result WorkSeekBegin();

         ::music::midi::file::e_result CalcTkLength();

         ::music::midi::file::e_result CreateTempoMap();

         ::multimedia::e_result ImmediatePutTempoChange();

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
         
         ::music::midi::file::e_result RebuildIndex();

         ::music::midi::file::e_result WriteHeader(MIDIFILEHDR * lpmfh);

         ::music::midi::file::e_result ChangeEventDelta(::music::midi::event_base *pEvent, imedia::position tkNewDelta);

         ::music::midi::file::e_result ReplaceSameDeltaEvent(::music::midi::event_base & pEventNew);

         ::music::midi::file::e_result GetPreviousEvent(::music::midi::event_base * pPreviousEvent, ::music::midi::event_base * pEvent);

         ::music::midi::file::e_result SaveFile(const char * lpFilePath);

         ::music::midi::file::e_result WorkWriteXFTracks(stringa & tokena, imedia::position_array & positiona, ::music::xf::info_header & xfinfoheader);

         int32_t CalcMelodyTrack(::music::midi::events_v1 ** ppEvents, imedia::position_array * pTicks);

         int32_t WorkCalcMelodyTrack(::music::midi::events_v1 ** ppEvents, imedia::position_array & positiona, int_array & iaTokenLine);

         int32_t GetFormat();

         ::music::midi::file::e_result MergeTracks();

         ::music::midi::file::e_result WorkMergeTracks();

         ::music::midi::file::e_result WorkStreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         ::music::midi::file::e_result WorkGetNextEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::file::e_result WorkGetNextRawEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::file::e_result WorkGetNextRawMidiEvent(::music::midi::event_v5 * & pevent, imedia::position tkMax, bool bTkMaxInclusive);

         ::music::midi::file::e_result WorkSeek(::imedia::position tkPosition, LPMIDIHDR lpmh);

         void delete_contents();

         int32_t GetDivision();

         imedia::position get_position();

         void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);

         bool IsNull();

         void WorkSeekEnd();

         ::music::midi::file::e_result OpenFile(::music::midi::file::buffer &file, int32_t openMode);

         ::music::midi::file::e_result OpenFile(::ca2::file & file, int32_t openMode);

         ::music::midi::file::e_result OpenFile(primitive::memory * pmemstorage, int32_t openMode, ::music::e_storage);

         ::music::midi::file::e_result OpenFile(primitive::memory * pmemstorage, ::music::midi::e_file_open_mode eopenmode, ::music::e_storage estorage);

         ::music::midi::file::e_result SaveFile(::ca2::file & file);

         ::music::midi::file::e_result CloseFile();

         ::music::midi::file::e_result GetFileInfo(PSMFFILEINFO psfi);

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

         ::music::midi::file::e_result StreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         VMSRESULT StreamEvent(imedia::position tkDelta, ::music::midi::event_base * Event, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         VMSRESULT StreamEventF1(imedia::position tkDelta, array < ::music::midi::event_v5 *, ::music::midi::event_v5 * > & eventptra, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);

         ::music::midi::file::e_result seek(imedia::position tkPosition, LPMIDIHDR lpmh);

         ::music::midi::file::e_result seek(imedia::position tkPosition);

         ::music::midi::file::e_result Build();

         ::music::midi::file::e_result GetNextEvent(::music::midi::event_v1 *& pevent, imedia::position tkMax, bool   bTkMaxInclusive);

         ::music::midi::file::e_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

         void _SyncSeek(imedia::position tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);

         void _SyncSeek(imedia::position tkPosition);

         ::music::midi::file::e_result InsertParmData(imedia::position tkDelta, LPMIDIHDR lpmh);

         VMSRESULT InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);

         ::music::midi::file::e_result InsertPadEvent(imedia::position tkDelta, LPMIDIHDR lpmh);

         void SetOpened(bool bOpened = true);


      };


   } // namespace midi_core_audio


} // namespace music





