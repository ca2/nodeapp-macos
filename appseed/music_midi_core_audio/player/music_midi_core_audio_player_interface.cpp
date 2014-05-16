#include "framework.h"


namespace music
{


   namespace midi_core_midi
   {


      namespace player
      {


         player_interface::player_interface(sp(::base::application) papp) :
            element(papp),
            callback(papp),
            ::music::midi::player::player_interface(papp)
            
         {
            m_psection = NULL;
            m_pmidiplayer = NULL;
         }

         player_interface::~player_interface()
         {

         }

         bool player_interface::Initialize(sp(::music::midi::midi) pcentral)
         {

            if(!initialize())
               return false;

            m_psection = pcentral;

            return true;
         }


         bool player_interface::Finalize()
         {

            if(!finalize())
               return false;

            return true;
         }


         bool player_interface::OpenMidiPlayer()
         {
            try
            {
               m_pmidiplayer = dynamic_cast < ::music::midi::player::player * > (__begin_thread < player >(
                  get_app(),
                  ::core::scheduling_priority_normal,
                  0,
                  CREATE_SUSPENDED));
            }
            catch(memory_exception *pe)
            {
               System.simple_message_box(NULL, _T("No primitive::memory to perform this operation." ));
               pe->Delete();
               return false;        
            }

            m_pmidiplayer->SetMidiCentral(m_psection);

//            m_pmidiplayer->SetCallbackWindow(&m_wnd);
            if(::multimedia::failed(m_pmidiplayer->Initialize(
               GetMidiPlayerCallbackThread())))
            {
               return false;
            }



            if(!OnOpenMidiPlayer())
            {
               return false;
            }
            m_pmidiplayer->ResumeThread();
            m_pmidiplayer->m_evInitialized.wait();
            return true;
         }

         bool player_interface::OnOpenMidiPlayer()
         {
            GetMidiPlayer()->SetInterface(this);
//            m_wnd.set_callback(m_composite);
            return true;
         }


         // Event handling
         void player_interface::OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata)
         {
            callback::OnMidiPlayerNotifyEvent(pdata);
  //          switch(pdata->m_enotifyevent)
    //        {
      //      case music::midi::player::notify_event_set_sequence:
        //       //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
          //     break;
            //}

         }


      } // namespace player


   } // namespace midi_core_midi


} // namespace music









