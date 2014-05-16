#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_audio_core
   {


      section::section(sp(::base::application) papp) :
         element(papp),
         ::ca2::section(papp)
      {

      }


      section::~section()
      {

      }


      bool section::initialize1()
      {

         return true;

      }


      bool section::finalize() 
      {

         DestroyWindow();


         return true;

      }



      /*::multimedia::e_result section::CreateNewDevice(uint32_t uiMixerID)
      {
      ::multimedia::e_result mmrc;
      if(MMSYSERR_NOERROR != (mmrc = m_pmixer->set_new_device(
      uiMixerID,
      (uint32_t) m_oswindow_,
      0,
      CALLBACK_WINDOW)))
      {
      System.simple_message_box("Could not open audio_mixer device!");
      PostMessage(WM_CLOSE);
      return mmrc;
      }
      m_pmixer->m_pdevice->initialize_capabilities();
      return mmrc;
      }

      ::multimedia::e_result section::CreateNewDestination(uint32_t dwComponentType)
      {
      ::multimedia::e_result mmrc;
      ::multimedia::audio_mixer::destination * pdestination = NULL;

      if(MMSYSERR_NOERROR != (mmrc =  m_pmixer->m_pdevice->get_destination(
      dwComponentType,
      &pdestination)))
      {
      System.simple_message_box("Could not open default audio_mixer destination!");
      PostMessage(WM_CLOSE);
      return mmrc;
      }

      m_destinationpa.add(pdestination);

      pdestination->initialize_source_info();

      pdestination->initialize_all_controls();

      m_pmixer->m_pdevice->map_lines();
      m_pmixer->m_pdevice->map_controls();

      pdestination->update_all_controls();

      return mmrc;
      }*/


      bool section::initialize()
      {
         //   m_pmixerthread = (::multimedia::audio_mixer::thread *) __begin_thread(System.type_info < ::multimedia::audio_mixer::thread > ());
         //   if(m_pmixerthread == NULL)
         //      return false;
         //   return true«
         return true;
      }


   } // namespace audio_mixer_audio_core


} // namespace multimedia




