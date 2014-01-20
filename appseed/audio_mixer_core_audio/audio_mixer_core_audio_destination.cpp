#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_audio_core
   {

      destination::destination(sp(base_application) papp) :
         element(papp),
         ::multimedia::audio_mixer::source(papp),
         ::multimedia::audio_mixer_audio_core::source(papp),
         ::multimedia::audio_mixer::destination(papp)
      {

         m_mixersourcea.set_app(papp);
         m_pdevice = NULL;
         m_pdestination = this;

      }

      destination::destination(const destination & destination) :
         ::ca2::ca2(((class destination &) destination).get_app()),
         ::multimedia::audio_mixer::source(((class destination &)destination).get_app()),
         ::multimedia::audio_mixer_audio_core::source(((class destination &)destination).get_app()),
         ::multimedia::audio_mixer::destination(((class destination &)destination).get_app())
      {

         m_mixersourcea.set_app(((class destination &)destination).get_app());

         operator = (destination);

      }

      destination::~destination()
      {
         //    Carray<::multimedia::audio_mixer::source, ::multimedia::audio_mixer::source &>::~Carray<::multimedia::audio_mixer::source, ::multimedia::audio_mixer::source &>();
         //CMixerLine::~CMixerLine();
      }

      void destination::operator delete(void *it)
      {
         ((destination *) it)->~destination();
         free(it);

      }


      ::multimedia::e_result destination::initialize_source_info()
      {

         sp(::multimedia::audio_mixer_audio_core::source)     lpSource;

         int32_t iConnections = (int32_t) m_mixerline.cConnections;

         m_mixersourcea.set_size_create(iConnections);

         for (int32_t i = 0; i < iConnections; i++)
         {

            lpSource = m_mixersourcea(i);

            lpSource->SetDestination(this);

            lpSource->mixerGetLineInfo(i, this);

         }

         return MMSYSERR_NOERROR;

      }


      ::multimedia::e_result destination::initialize_all_controls()
      {
         GetLineControls();

         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(int32_t i = 0; i < sourcea.get_size(); i++)
         {
            sourcea[i].GetLineControls();
         }
         return true;
      }

      void destination::update_all_controls()
      {
         ::multimedia::audio_mixer::source::update_all_controls();
         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(int32_t i = 0; i < sourcea.get_size(); i++)
         {
            sourcea[i].update_all_controls();
         }
      }


      destination & destination::operator = (const destination & destination)
      {

         m_pdevice = destination.m_pdevice;

         return *this;

      }


      uint32_t destination::get_component_type()
      {

         return m_mixerline.dwComponentType;

      }


      ::multimedia::audio_mixer::device * destination::get_device()
      {

         return m_pdevice;

      }


      void destination::set_device(::multimedia::audio_mixer::device * pdevice)
      {

         m_pdevice = pdevice;

      }


      ::multimedia::audio_mixer::source_array & destination::get_source_info()
      {

         return m_mixersourcea;

      }

      uint32_t destination::get_mixer_line_id()
      {
         return m_mixerline.dwLineID;
      }

   } // namespace audio_mixer_audio_core


} // namespace multimedia







