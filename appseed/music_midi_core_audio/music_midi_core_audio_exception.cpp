#include "framework.h"


namespace music
{


   namespace midi_mmsystem
   {


      exception::exception(sp(base_application) papp) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::music::midi::exception(papp)
      {
         m_etype = TypeUndefined;
      }

      exception::exception(sp(base_application) papp, ::music::midi::e_file_result mfr) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::music::midi::exception(papp, mfr)
      {
         m_etype = TypeMidiFile;
         m_mfr = mfr;
      }

      exception::exception(sp(base_application) papp, ::multimedia::result mmr, int32_t iAppError) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::music::midi::exception(papp, mmr, iAppError)
      {
         m_etype = TypeMultimediaSystem;
         m_mmr = mmr;
         m_iAppError = iAppError;
      }


      exception::~exception()
      {

      }

      void exception::SetMMResult(::multimedia::result mmr)
      {
         m_etype = TypeMultimediaSystem;
         m_mmr = mmr;
      }

      string exception::GetDetailsText()
      {
         string str;
         //switch(m_mmr)
         //{
         //default:
         str.Format("MMSYSTEMERROR = %d, Error = %d", m_mmr, m_iAppError);
         //   break;
         //}
         return str;
      }


      void exception::SetUserText(const char * lpsz)
      {
         m_strUser = lpsz;
      }

      string exception::GetUserText()
      {
         return m_strUser;
      }



   } // namespace midi_mmsystem


} // namespace music









