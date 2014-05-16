#pragma once


#define C_TEMPO_MAP_CHK     16


namespace music
{


   namespace midi_core_midi
   {

      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI file :
         virtual public ::music::midi::file::buffer
      {
      public:


         
         file(sp(::base::application) papp);
         virtual ~file();
         
         
         /*         double GetTempoShiftRate();
          
          bool IsTrackMute(int32_t iIndex);
          
          void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);
          
          void MuteTrack(int32_t iIndex, bool bMute = true);
          
          ::music::e_result WorkSeekBegin();
          
          ::music::e_result CalcTkLength();
          
          ::music::e_result CreateTempoMap();
          
          ::multimedia::e_result ImmediatePutTempoChange();
          
          ::music::e_result GetTempoEvent(::music::midi::event & event);
          
          void OnStop();
          
          uint32_t GetImageSize();
          
          LPBYTE GetImage();
          
          ::music::e_result Format0();
          
          ::music::e_result InsertTempoEvent();
          
          ::music::midi::tempo_map_entry * GetTempoMapEntry(const imedia::position & position);
          
          int32_t GetTempoShift();
          
          ::music::e_result SetTempoShift(int32_t iTempoShift);
          
          void ToWorkStorage();
          
          void FromWorkStorage();
          
          int32_t GetKeyShift();
          
          int32_t SetKeyShift(int32_t iKeyShift);
          
          bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);
          
          bool IsXFFile();
          
          bool IsTune1000File();
          
          bool IsOpened();
          
          ::music::e_result RebuildIndex();
          
          ::music::e_result WriteHeader(MIDIFILEHDR * lpmfh);
          
          ::music::e_result ChangeEventDelta(::music::midi::event *pEvent, imedia::position tkNewDelta);
          
          ::music::e_result ReplaceSameDeltaEvent(::music::midi::event & pEventNew);
          
          ::music::e_result GetPreviousEvent(::music::midi::event * pPreviousEvent, ::music::midi::event * pEvent);
          
          ::music::e_result SaveFile(const char * lpFilePath);
          
          ::music::e_result WorkWriteXFTracks(stringa & tokena, imedia::position_array & positiona, ::music::xf::info_header & xfinfoheader);
          
          int32_t CalcMelodyTrack(::music::midi::events ** ppEvents, imedia::position_array * pTicks);
          
          int32_t WorkCalcMelodyTrack(::music::midi::events ** ppEvents, imedia::position_array & positiona, int_array & iaTokenLine);
          
          int32_t GetFormat();
          
          ::music::e_result WorkMergeTracks();
          
          ::music::e_result WorkStreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);
          
          ::music::e_result WorkGetNextEvent(::music::midi::event * & pevent, imedia::position tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkGetNextRawEvent(::music::midi::event * & pevent, imedia::position tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkGetNextRawMidiEvent(::music::midi::event * & pevent, imedia::position tkMax, bool bTkMaxInclusive);
          
          ::music::e_result WorkSeek(::imedia::position tkPosition, LPMIDIHDR lpmh);
          
          void delete_contents();
          
          int32_t GetDivision();
          
          imedia::position GetPosition();
          
          void AttachSeekSync(::ikaraoke::events_tracks_v1 * ptracksv1);
          
          bool IsNull();
          
          void WorkSeekEnd();
          
          ::music::e_result OpenFile(::music::midi::file::buffer &file, int32_t openMode);
          
          ::music::e_result OpenFile(::file::stream_buffer & file, int32_t openMode);
          
          ::music::e_result OpenFile(primitive::memory * pmemstorage, int32_t openMode, ::music::e_storage);
          
          ::music::e_result OpenFile(primitive::memory * pmemstorage, ::music::midi::file::e_open eopenmode, ::music::e_storage estorage);
          
          ::music::e_result SaveFile(::file::stream_buffer & file);
          
          ::music::e_result CloseFile();
          
          ::music::e_result GetFileInfo(PSMFFILEINFO psfi);
          
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
          
          ::music::e_result StreamRender(LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);
          
          ::multimedia::e_result StreamEvent(imedia::position tkDelta, ::music::midi::event * Event, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);
          
          ::multimedia::e_result StreamEventF1(imedia::position tkDelta, array < ::music::midi::event *, ::music::midi::event * > & eventptra, LPMIDIHDR lpmh, imedia::position tkMax, uint32_t cbPrerollNomimalMax);
          
          ::music::e_result seek(imedia::position tkPosition, LPMIDIHDR lpmh);
          
          ::music::e_result seek(imedia::position tkPosition);
          
          ::music::e_result Build();
          
          ::music::e_result GetNextEvent(::music::midi::event *& pevent, imedia::position tkMax, bool   bTkMaxInclusive);
          
          ::music::e_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);
          
          void _SyncSeek(imedia::position tkPosition, ::ikaraoke::events_tracks_v1 * ptracksv1);
          
          void _SyncSeek(imedia::position tkPosition);
          
          ::music::e_result InsertParmData(imedia::position tkDelta, LPMIDIHDR lpmh);
          
          ::multimedia::e_result InsertLyricEvents(::ikaraoke::lyric_event_v1 * pLyricEvent, LPMIDIHDR lpmh);
          
          ::music::e_result InsertPadEvent(imedia::position tkDelta, LPMIDIHDR lpmh);
          
          void SetOpened(bool bOpened = true);
          */
         

      };


   } // namespace midi_core_midi


} // namespace music





