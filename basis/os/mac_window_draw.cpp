#include "framework.h"


class keep_event_reset
{
public:
   
   
   event * m_pevent;
   
   
   keep_event_reset(event * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }
   
   
};


namespace mac
{

   
   window_draw::window_draw(base_application * papp) :
   element(papp),
   ::thread(papp),
   ::user::window_draw(papp),
   message_queue(papp),
   m_mutexRendering(papp),
   m_mutexRgnUpdate(papp),
   m_semaphoreBuffer(papp),
   m_mutexRender(papp),
   m_wndpaOut(papp)
   {
      m_dwLastRedrawRequest = ::get_tick_count();
      m_bRender = false;
      m_pbuffer = new user::buffer(papp);
      m_pbuffer->m_spdib.create(allocer());
      m_dwLastUpdate = false;
      m_bProDevianMode = true;
      
   }
   
   extern void _001DeferPaintLayeredWindowBackground(void * hwnd, ::draw2d::graphics * pdc);
   window_draw::~window_draw()
   {
      
      //      ::DestroyWindow((oswindow) m_spwindowMessage->Detach());
      
   }
   
   
   
   /*
    void window_draw::OnPaint(void * hwnd, CPaintDC & spgraphics)
    {
    UNREFERENCED_PARAMETER(hwnd);
    UNREFERENCED_PARAMETER(spgraphics);
    }
    */
   
   void window_draw::message_queue_message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_USER + 1984 + 1977))
      {
         _synch_redraw();
      }
   }
   
   void window_draw::asynch_redraw()
   {
      DWORD dwTick = ::get_tick_count();
      if(m_iFramesPerSecond == 0)
      {
         if(dwTick - m_dwLastUpdate < 1000)
            return;
      }
      else
      {
         if(dwTick - m_dwLastUpdate < 1000 / m_iFramesPerSecond)
            return;
      }
      _asynch_redraw();
   }
   
   void window_draw::_asynch_redraw()
   {
      if(!m_bProDevianMode)
      {
         m_spuiMessage->post_message(WM_USER + 1984 + 1977);
      }
   }
   
   void window_draw::synch_redraw()
   {
      
      /*      if(!m_bProDevianMode && ::IsWindow((oswindow) m_spwindowMessage->get_os_data()))
       {
       m_spwindowMessage->send_message(WM_USER + 1984 + 1977);
       }*/
   }
   
   void window_draw::_synch_redraw()
   {
      
      keep_event_reset keepeventreset(&m_eventFree);
      
      static DWORD s_dwLastAnalysisFrame = 0;
      static DWORD s_dwLastFrameFrame = 0;
      static DWORD s_iAnalysisFrameFailureCount = 0;
      static DWORD s_iFrameFailureCount = 0;
      DWORD iFailureTime;
      if(m_iFramesPerSecond == 0)
      {
         iFailureTime = 1000 / 12;
      }
      else
      {
         iFailureTime = 1000 / m_iFramesPerSecond;
      }
      m_dwLastUpdate = ::get_tick_count();
      UpdateBuffer();
      return;
      if(m_pbuffer->GetBuffer()->get_os_data() != NULL)
      {
         //m_pbuffer->m_spdib->fill_channel(255, visual::rgba::channel_alpha);
         //ScreenOutput();
      }
      DWORD dwTakeTime = ::get_tick_count() - m_dwLastUpdate;
      m_dwLastDelay = dwTakeTime;
      if(dwTakeTime > iFailureTime)
      {
         s_dwLastAnalysisFrame += dwTakeTime;
         s_dwLastFrameFrame += dwTakeTime;
         TRACE("window_draw::_synch_redraw :: System has exceeded prodevian performance failure time - %d milliseconds", iFailureTime);
         TRACE("window_draw::_synch_redraw :: took - %d milliseconds", dwTakeTime);
         s_iAnalysisFrameFailureCount++;
         DWORD iTimeFrame = 2000;
         DWORD iMaxFailureCount = 3;
         if(s_dwLastAnalysisFrame > iTimeFrame ||
            dwTakeTime > (iFailureTime * iMaxFailureCount))
         {
            s_dwLastAnalysisFrame = 0;
            if(s_iAnalysisFrameFailureCount > iMaxFailureCount
               || (dwTakeTime > (iFailureTime * iMaxFailureCount)))
            {
               s_iFrameFailureCount++;
            }
            s_iAnalysisFrameFailureCount = 0;
         }
         DWORD iMaxFrameFailureCount = 3;
         DWORD iFrameTimeFrame = iTimeFrame * iMaxFrameFailureCount;
         if(s_dwLastFrameFrame > iFrameTimeFrame)
         {
            s_dwLastFrameFrame = 0;
            if(s_iFrameFailureCount > iMaxFailureCount)
            {
               TRACE("window_draw::_synch_redraw :: during prodevian Performance Analysis Time Frame - %d milliseconds -,", iTimeFrame);
               TRACE("window_draw::_synch_redraw :: failure count has exceeded the maximum count - %d", iMaxFailureCount);
               TRACE("window_draw::_synch_redraw :: Going to try to save some resource that may favor drawing perfomance");
               if(!System.savings().is_trying_to_save(::core::resource_blur_background))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blur background\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blur background\" resource");
                  System.savings().try_to_save(::core::resource_blur_background);
               }
               else if(!System.savings().is_trying_to_save(::core::resource_blurred_text_embossing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blurred text embossing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blurred text embossing\" resource");
                  System.savings().try_to_save(::core::resource_blurred_text_embossing);
               }
               else if(!System.savings().is_warning(::core::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not warning to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to warn to save \"processing\" resource");
                  System.savings().warn(::core::resource_processing);
               }
               else if(!System.savings().is_trying_to_save(::core::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"processing\" resource");
                  System.savings().try_to_save(::core::resource_blur_background);
               }
            }
            s_iFrameFailureCount = 0;
         }
         
      }
   }
   
   bool window_draw::to(
                        ::draw2d::graphics *          pdc,
                        LPCRECT        lpcrectUpdate,
                        user::oswindow_tree::Array & hwndtreea,
                        bool           bGdiLocked,
                        bool           bExcludeParamWnd)
   {
      UNREFERENCED_PARAMETER(bGdiLocked);
      UNREFERENCED_PARAMETER(bExcludeParamWnd);
      single_lock sl(&m_mutexRender, TRUE);
      rect rectUpdate(*lpcrectUpdate);
      
      rect rectChild;
      
      rect rectNewUpdate;
      
      for(int_ptr i = hwndtreea.get_size() - 1; i >= 0; i--)
      {
         user::oswindow_tree & hwndtreeChild = hwndtreea[i];
         void * hwndChild = hwndtreeChild.m_oswindow;
         ::GetWindowRect((oswindow) hwndChild, rectChild);
         if(rectNewUpdate.intersect(rectChild, rectUpdate))
         {
            to(pdc, rectNewUpdate, hwndtreeChild, true, false);
         }
      }
      return true;
   }
   
   bool window_draw::to(
                        ::draw2d::graphics *          pdc,
                        LPCRECT        lpcrectUpdate,
                        user::oswindow_tree & hwndtree,
                        bool           bGdiLocked,
                        bool           bExcludeParamWnd)
   {
      UNREFERENCED_PARAMETER(bGdiLocked);
      single_lock sl(&m_mutexRender, TRUE);
      rect rectUpdate(*lpcrectUpdate);
      
      //      DWORD dwTimeIn = get_tick_count();
      
      void * hwndParam = hwndtree.m_oswindow;
      
      if(hwndParam == NULL)
      {
         return false;
      }
      
      /*      if(!::IsWindow((oswindow) hwndParam))
       {
       return false;
       }*/
      
      
      
      
      
      if(!::IsWindowVisible((oswindow) hwndParam))
      {
         return true;
      }
      
      
      
      
      if(hwndtree.m_dwUser & 1)
      {
         ASSERT(TRUE);
      }
      else
      {
         ::user::window_interface * ptwi = System.user()->window_map().get((int_ptr) hwndParam);
         ::user::interaction * pguie = dynamic_cast < ::user::interaction * > (ptwi);
         rect rectWindow;
         ::GetWindowRect((oswindow) hwndParam, rectWindow);
         //::GetClientRect(hwndParam, rectWindow);
         //::ClientToScreen(hwndParam, &rectWindow.top_left());
         //::ClientToScreen(hwndParam, &rectWindow.bottom_right());
         
         pdc->SetViewportOrg(rectWindow.left, rectWindow.top);
         
         
         if(ptwi != NULL)
         {
            
            
            if(!bExcludeParamWnd &&
               pguie != NULL )
            {
               pguie->_001OnDraw(pdc);
            }
            
            
         }
         else
         {
//            bool bWin4 = FALSE;
            //_gen::FillPSOnStack();
            /*            ::DefWindowProc(
             (oswindow) hwndParam,
             (bWin4 ? WM_PRINT : WM_PAINT),
             (WPARAM)((dynamic_cast<::lnx::graphics * >(pdc))->get_os_data()),
             (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
            //::RedrawWindow(hwndParam, NULL, rgnClient, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
         }
      }
      
      
      
      
      //      DWORD dwTimeOut = get_tick_count();
      //   TRACE("// Average Window Rendering time\n");
      //   TRACE("// Window Class: %s\n", (pwnd!=NULL) ? pwnd->GetRuntimeClass()->m_lpszClassName : "(Not available)");
      //   TRACE("// TickCount: %d \n", dwTimeOut - dwTimeIn);
      //   TRACE("// \n");
      
      
      return to(
                pdc,
                rectUpdate,
                hwndtree.m_oswindowtreea,
                true,
                false);
      
   }
   
   
   UINT window_draw::RedrawProc()
   {
      if(!create_message_queue("ca2::twf - ca2 Transparent Window Framework"))
      {
         TRACE("Could not initialize ca2::twf - ca2 Transparent Window Framework!");
         return 0;
      }
      //      ::AttachThreadInput(::GetCurrentThreadId(), WIN_THREAD(System.::ca2::thread_sp::m_p)->m_nThreadID, TRUE);
      MESSAGE msg;
      s_bRunning = true;
      while(m_bRun && ::get_thread()->m_bRun)
      {
         try
         {
            if(m_bProDevianMode)
            {
               _synch_redraw();
            }
         }
         catch(...)
         {
         }
         //         while(::PeekMessage(&msg, ::caNULL, NULL, NULL, PM_NOREMOVE))
         while(::PeekMessage(&msg, NULL, 0, 0, 0))
         {
            __get_thread()->pump_message();
         }
         int32_t iUiDataWriteWindowTimeForTheApplicationInThisMachine = 8;
         if(m_iFramesPerSecond == 0)
         {
            Sleep(1000);
         }
         else if((1000 / m_iFramesPerSecond) > m_dwLastDelay)
         {
            Sleep(max((DWORD) max(0, iUiDataWriteWindowTimeForTheApplicationInThisMachine), (1000 / m_iFramesPerSecond) - m_dwLastDelay));
         }
         else
         {
            Sleep(iUiDataWriteWindowTimeForTheApplicationInThisMachine);
         }
      }
      //delete this;
      s_bRunning = false;
      return 0;
   }
   
   int32_t window_draw::run()
   {
      return RedrawProc();
   }
   
   
   DWORD g_dwLastWindowDraw;
   // lprect should be in screen coordinates
   bool window_draw::UpdateBuffer()
   {
      if(m_bRender)
         return false;
      single_lock sl(&m_mutexRender, FALSE);
      if(!sl.lock(duration::zero()))
         return false;
      keeper<bool> keepRender(&m_bRender, true, false, true);
      //   TRACE("////////////////////////////////////////////////////\n");
      //   TRACE("// window_draw::TwfRender\n");
      //   TRACE("//\n");
      
      //      DWORD dwTimeIn = get_tick_count();
      
//      static bool bTest = false;
    //  semaphore * psemaphore = TwfGetBufferSemaphore();
  //    single_lock slSemaphoreBuffer(psemaphore, FALSE);
//      if(!slSemaphoreBuffer.lock(duration::zero()))
      {
         //xxx      AddUpdateRect(rectClip, true);
         //      return false;
      }
      
      
      
      
      
      rect rectScreen;
      System.get_screen_rect(&rectScreen);
      m_pbuffer->UpdateBuffer(rectScreen.bottom_right());
      if(m_pbuffer->GetBuffer()->get_os_data() == NULL)
         return true;
      
      ::draw2d::graphics * pdc = (dynamic_cast < ::draw2d::graphics * > (m_pbuffer->GetBuffer()));
      
      if(pdc == NULL)
      {
         return false;
      }
      
      
      user::oswindow_array hwnda;
      
      get_wnda(hwnda);
      
      user::interaction_ptr_array wndpa(get_app());
      
      
      
      get_wnda(wndpa);
      
      
      user::window_util::SortByZOrder(hwnda);
      
      user::oswindow_tree::Array hwndtreea;
      //hwndtreea = hwnda;
      //hwndtreea.EnumDescendants();
      
      
      
      
      rect rectUpdate;
      
      rectUpdate = rectScreen;
      
      rect rectOptimize;
      
      rectOptimize = rectUpdate;
      
      rect rectWindow;
      rect rect9;
      
      user::oswindow_array wndaApp;
      
      m_wndpaOut.remove_all();
      
      //      ::draw2d::region_sp rgnWindow(get_app());
      //    ::draw2d::region_sp rgnIntersect(get_app());
      
      //      rgnWindow->create_rect(0, 0, 0, 0);
      //    rgnIntersect->create_rect(0, 0, 0, 0);
      
      /*rect rectIntersect;
       ::draw2d::region_sp rgnUpdate(get_app());
       rgnUpdate->create_rect(rectUpdate);
       void * hwndOrder = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
       for(;;)
       {
       if(hwndOrder == NULL)
       break;
       //bool bVisible = ::IsWindowVisible(hwndOrder);
       bool bVisible = ::IsWindowVisible(hwndOrder);
       bool bIconic = ::IsIconic(hwndOrder);
       if(!bVisible
       || bIconic
       || wndaApp.contains(hwndOrder))
       {
       }
       else
       {
       rect rectWindow;
       ::GetWindowRect(hwndOrder, rectWindow);
       char text[256];
       //::GetWindowText(hwndOrder, text, sizeof(text));
       bool bLayered = ::GetWindowLong(hwndOrder, GWL_EXSTYLE);
       rgnWindow->create_rect(rectWindow);
       rgnIntersect->create_rect(rect(0, 0, 0, 0));
       rgnIntersect->CombineRgn(rgnUpdate, rgnWindow, RGN_AND);
       rect rectIntersectBox;
       rgnIntersect->GetRgnBox(rectIntersectBox);
       if(rectIntersectBox.is_empty())
       {
       }
       else
       {
       if(!bLayered)
       {
       rgnUpdate->CombineRgn(rgnUpdate, rgnWindow, ::draw2d::region::combine_exclude);
       }
       rect rectDiffBox;
       rgnUpdate->GetRgnBox(rectDiffBox);
       wndaApp.add(hwndOrder);
       if(rectDiffBox.is_empty())
       {
       break;
       }
       }
       }
       hwndOrder = ::GetWindow(hwndOrder, GW_HWNDNEXT);
       }
       */
      
      for(int32_t l = 0; l < wndpa.get_count();)
      {
         try
         {
            if(wndpa[l].oprop("session").is_new())
            {
               dynamic_cast < ::window * > (wndpa[l].m_pimpl.m_p)->_001UpdateWindow();
            }
            l++;
         }
         catch(simple_exception & se)
         {
            if(se.m_strMessage == "no more a window")
            {
               System.frames().remove(&wndpa[l]);
               wndpa.remove_at(l);
               
            }
         }
         catch(...)
         {
            System.frames().remove(&wndpa[l]);
            wndpa.remove_at(l);
         }
      }
      return true;
      
      for(index j = wndaApp.get_upper_bound(); j >= 0; j--)
      {
         oswindow hwndTopic = wndaApp[j];
         
         ::window * pwnd = NULL;
         //::window * pwnd = dynamic_cast < ::window * > (System.window_map().get((int_ptr) hwndTopic));
         //if(pwnd == NULL)
         //{
         for(int32_t l = 0; l < wndpa.get_count(); l++)
         {
            if(wndpa[l].get_safe_handle() == hwndTopic)
            {
               pwnd = dynamic_cast < ::window * > (wndpa[l].m_pimpl.m_p);
               break;
            }
         }
         if(!::IsWindowVisible((oswindow) wndaApp[j]) || ::IsIconic((oswindow) wndaApp[j]) || pwnd == NULL)
            continue;
         
         
         
         /*pwnd->GetWindowRect(rectWindow);
          rectIntersect.intersect(rectWindow, rectUpdate);
          if(rectIntersect.area() <= 0)
          {
          pwnd->PostMessage(WM_USER + 184, 0, 0);
          // TODO: should use iMaxMonitor information to set window
          // to a more visible position in the monitor iMaxMonitor with greatest
          // area.
          
          //
          //
          // !!!! Warning !!!!
          //
          //
          
          // The implementation below potentially uses functions like SendMessage.
          // window_draw - The Transparent Window Interface - should never call
          // SendMessage or other functions that may lock other threads.
          // This also applies to every _001OnDraw, _000OnDraw implementation.
          //
          // e.g.: If the user interface thread waits for twf - wait_twf -
          //       which is a very common task for avoiding simultaneous
          //       access to user interface resources that may be
          //       updated by the user interface thread and drawn by
          //       by twf thread - following the prodevian painting model,
          //       where any time twf can request to draw a new frame
          //       to obbey certain rules like frames per second -
          //       and twf sends a message to the user interface thread,
          //       both threads get deadlocked.
          
          
          
imple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pwnd);
          if(pframe != NULL)
          {
          pframe->InitialFramePosition(true);
          }
          else
          {
          class rect rect = System.m_monitorinfoa[0].rcMonitor;
          rect.deflate(rect.width() / 4, rect.height() / 4);
          pwnd->SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), 0);
          }*/
         /*}
          pwnd->GetWindowRect(rectWindow);
          rectIntersect.intersect(rectWindow, rectUpdate);
          if(rectIntersect.area() > 0)
          {
          m_pbuffer->GetBuffer()->SetViewportOrg(0, 0);
          pwnd->_001Print(m_pbuffer->GetBuffer());
          m_wndpaOut.add(pwnd);
          }*/
      }
      
      //HDC hdc = (HDC) m_pbuffer->GetBuffer()->get_os_data();
      //::SetViewportOrgEx(hdc, 0, 0, NULL);
      
      
      
      
      
      //   if(TwfIsBuffered())
      /*{
       ScreenOutput(
       m_pbuffer,
       rgnClip);
       }*/
      
      //    TwfReleaseDC(pdc);
      
      //      DWORD dwTimeOut = get_tick_count();
      //   TRACE("//\n");
      //   TRACE("// Rendering Finished\n");
      //   TRACE("// TickCount: %d \n", dwTimeOut - dwTimeIn);
      //   TRACE("////////////////////////////////////////////////////\n");
      
      return true;
   }
   
   bool window_draw::ScreenOutput()
   {
      
      if(m_bRender)
         return false;
      
      single_lock sl(&m_mutexRender, FALSE);
      
      if(!sl.lock(duration::zero()))
         return false;
      
      keeper<bool> keepRender(&m_bRender, true, false, true);
      
//      static bool bTest = false;
      
      for(int32_t i = 0; i < m_wndpaOut.get_count(); i++)
      {
         ::user::interaction* pwnd = m_wndpaOut(i);
         
         ScreenOutput(m_pbuffer, pwnd);
         
      }
      
      return true;
      
   }
   
   
   semaphore * window_draw::TwfGetBufferSemaphore()
   {
      return &m_semaphoreBuffer;
   }
   
   // The first ::window handle in the array must belong
   // to the higher z order ::window.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.
   
   
   
   // Remark: this optimization eliminates top level lnxdows
   // that are lower z order siblings of a higher z order
   // top level ::window that contains all
   // the update region in a opaque area.
   // It doesn´t eliminates from the update parent lnxdows
   // obscured by opaque children.
   
   window_draw::EOptimize window_draw::TwfOptimizeRender(
                                                         user::oswindow_tree::Array & hwndtreea,
                                                         LPCRECT lpcrect)
   {
      const rect rectUpdate(*lpcrect);
      
      rect rectClient;
      for(int32_t i = 0; i < hwndtreea.get_size();)
      {
         user::oswindow_tree & hwndtree = hwndtreea[i];
         switch(TwfOptimizeRender(
                                  hwndtree,
                                  lpcrect))
         {
            case OptimizeNone:
               i++;
               break;
            case OptimizeThis:
               hwndtreea.remove_at(i);
               break;
            case OptimizeAllNext:
            {
               while(hwndtreea.get_size() > i + 1)
               {
                  hwndtreea.remove_at(i + 1);
               }
               /*hwndtreea.remove_at(i + 1);
                void * hwnd = hwndtreea[i].m_hwnd;
                rect rect;
                ::GetClientRect(hwnd, rect);
                ::ClientToScreen(hwnd, &rect.top_left());
                ::ClientToScreen(hwnd, &rect.bottom_right());
                rect.union(rect, lpcrect);
                TwfOptimizeRenderRemoveNextProper(
                hwndtreea,
                i + 1,
                rect);*/
            }
               return OptimizeAllNext;
         }
      }
      return OptimizeNone;
      
   }
   
   window_draw::EOptimize window_draw::TwfOptimizeRenderRemoveNextProper(
                                                                         user::oswindow_tree::Array & hwndtreea,
                                                                         int32_t iIndex,
                                                                         LPCRECT lpcrect)
   {
      
      
      const rect rectOptimize(*lpcrect);
      rect rectClient;
      for(int32_t i = iIndex; i < hwndtreea.get_size();)
      {
         user::oswindow_tree & hwndtree = hwndtreea[i];
         ::oswindow oswindow = hwndtree.m_oswindow;
         rect rect;
         ::GetClientRect((::oswindow) oswindow, rect);
         throw todo(::get_thread_app());
//         ::ClientToScreen((::oswindow) oswindow, &rect.top_left());
  //       ::ClientToScreen((::oswindow) oswindow, &rect.bottom_right());
         if(rectOptimize.contains(rect))
         {
            hwndtreea.remove_at(i);
         }
         else
         {
            TwfOptimizeRenderRemoveNextProper(
                                              hwndtree.m_oswindowtreea,
                                              0,
                                              lpcrect);
            
            i++;
         }
      }
      return OptimizeNone;
      
   }
   
   
   window_draw::EOptimize window_draw::TwfOptimizeRender(
                                                         user::oswindow_tree & hwndtree,
                                                         LPCRECT lpcrect)
   {
      
      hwndtree.m_dwUser = 0;
      
      ::oswindow oswindow = hwndtree.m_oswindow;
      
      ::user::window_interface * ptwi = oswindow->get_user_interaction();
      
      if(!::IsWindowVisible(oswindow))
      {
         return OptimizeThis;
      }
      const rect rectUpdate(*lpcrect);
      
      rect rectClient;
      
      ::user::interaction * pguie = dynamic_cast < ::user::interaction * > (ptwi);
      
      pguie->GetClientRect(rectClient);
      pguie->ClientToScreen(rectClient);
      
      
      
      
      rect rectIntersect;
      
      if(!rectIntersect.intersect(rectClient, rectUpdate))
      {
         return OptimizeThis;
      }
      
      if(!rectClient.contains(rectUpdate))
      {
         
         return OptimizeNone;
      }
      
      //    ::window * pwnd = window::FromHandlePermanent(hwnd);
      
      
      if(ptwi == NULL)
      {
         
         //      ::user::window_interface::GetProperty getp;
         //      getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
         //      ::SendMessage(hwnd, CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
         //      ptwi = getp.m_pinterface;
         //      if(ptwi != NULL)
         //      {
         //         pwnd = ptwi->TwiGetWnd();
         //      }
      }
      
      EOptimize eoptimize = OptimizeNone;
      if(ptwi != NULL)
      {
         if(!ptwi->_001HasTranslucency())
            eoptimize = OptimizeAllNext;
      }
      
      EOptimize eoptimizeChildren = TwfOptimizeRender(hwndtree.m_oswindowtreea, lpcrect);
      
      if(eoptimizeChildren == OptimizeAllNext)
      {
         hwndtree.m_dwUser |= 1; // exclude from drawing;
         return OptimizeAllNext;
      }
      else if(eoptimize == OptimizeAllNext)
      {
         return OptimizeAllNext;
      }
      else
      {
         return OptimizeNone;
      }
      
      
   }
   
   
   bool window_draw::TwfGetTopWindow(
                                     void * hwnd,
                                     user::oswindow_array & hwnda,
                                     array < HRGN, HRGN > & hrgna,
                                     user::oswindow_tree::Array & hwndtreea,
                                     HRGN hrgn)
   {
      rect rectClient;
      for(int32_t i = 0; i < hwndtreea.get_size(); i++)
      {
         user::oswindow_tree & hwndtree = hwndtreea[i];
         if(!TwfGetTopWindow(
                             hwnd,
                             hwnda,
                             hrgna,
                             hwndtree,
                             hrgn))
            return false;
         
      }
      return true;
      
   }
   
   bool window_draw::TwfGetTopWindow(
                                     void * hwndParam,
                                     user::oswindow_array & hwnda,
                                     array < HRGN, HRGN > & hrgna,
                                     user::oswindow_tree & hwndtree,
                                     HRGN hrgn)
   {
      
      ::oswindow oswindow = hwndtree.m_oswindow;
      
      
      if(!::IsWindowVisible((::oswindow) oswindow))
      {
         return true;
      }
      
      
      
      
      rect rectWindow;
      
      ::GetWindowRect((::oswindow) oswindow, rectWindow);
      
      
      //   ::window * pwnd = ::lnx::window::from_handle(oswindow);
      
      if(!TwfGetTopWindow(
                          hwndParam,
                          hwnda,
                          hrgna,
                          hwndtree.m_oswindowtreea,
                          hrgn))
      {
         return false;
      }
      
//      HRGN hrgnIntersect;
      
      throw not_implemented(get_app());
      
      //      hrgnIntersect = ::CreateRectRgnIndirect(rectWindow);
      //
      //      int32_t iCombine = ::CombineRgn(hrgnIntersect, hrgn, hrgnIntersect, RGN_AND);
      //
      //      if(iCombine == NULLREGION)
      //      {
      //         ::DeleteObject(hrgnIntersect);
      //         return true;
      //      }
      //
      //
      //
      //      ::user::window_interface * pwndi = System.window_map().get((int_ptr) hwnd);
      //
      //      if(pwndi == NULL)
      //      {
      //         ::SendMessage(
      //            (oswindow) hwnd,
      //            ::user::window_interface::MessageBaseWndGetProperty,
      //            ::user::window_interface::PropertyDrawBaseWndInterface,
      //            (LPARAM) &pwndi);
      //      }
      //
      //      if(hwndParam == hwnd ||
      //         (pwndi != NULL &&
      //            pwndi->_001HasTranslucency()))
      //      {
      //
      //
      //         iCombine = ::CombineRgn(hrgn, hrgn, hrgnIntersect, ::draw2d::region::combine_exclude);
      //
      //         point ptOffset(0, 0);
      //
      //         ::ScreenToClient((oswindow) hwnd, &ptOffset);
      //
      //         hwnda.add(hwnd);
      //         ::OffsetRgn(hrgnIntersect, ptOffset.x, ptOffset.y);
      //         hrgna.add(hrgnIntersect);
      //
      //         if(iCombine == NULLREGION)
      //         {
      //            return false;
      //         }
      //
      //      }
      //      else
      //      {
      //         ::DeleteObject(hrgnIntersect);
      //         TwfGetTopWindowOptimizeOpaque(
      //            hwnd,
      //            hwnda,
      //            hrgna);
      //
      //      }
      //      if(hwndParam == hwnd)
      //      {
      //         return false;
      //      }
      //      else
      //      {
      //         return true;
      //      }
   }
   
   // lpcrect must be in screen coordinates
   void window_draw::TwfGetTopWindow(
                                     void * hwnd,
                                     user::oswindow_array & hwnda,
                                     array < HRGN, HRGN > & hrgna,
                                     user::oswindow_tree::Array & hwndtreea,
                                     LPCRECT lpcrect)
   {
      throw not_implemented(get_app());
      //      HRGN hrgn = ::CreateRectRgnIndirect(lpcrect);
      //      TwfGetTopWindow(
      //         hwnd,
      //         hwnda,
      //         hrgna,
      //         hwndtreea,
      //         hrgn);
      //      ::DeleteObject(hrgn);
   }
   
   void window_draw::TwfGetTopWindowOptimizeOpaque(
                                                   void * hwndOpaque,
                                                   user::oswindow_array & hwnda,
                                                   array < HRGN, HRGN > & hrgna)
   {
      rect rectWindow;
      
      //   ::window * pwndOpaque = window::FromHandlePermanent(hwndOpaque);
      
      ::GetWindowRect((oswindow) hwndOpaque, rectWindow);
      
      throw not_implemented(get_app());
      //      HRGN hrgnOpaque = ::CreateRectRgnIndirect(rectWindow);
      //
      //      point ptOffset;
      //      for(int32_t i = 0; i < hrgna.get_size(); )
      //      {
      //         void * hwnd = hwnda[i];
      //         HRGN hrgn = hrgna[i];
      //         ptOffset.x = 0;
      //         ptOffset.y = 0;
      //         ::ClientToScreen((oswindow) hwnd, &ptOffset);
      //         ::OffsetRgn(hrgn, ptOffset.x, ptOffset.y);
      //         if(::CombineRgn(hrgn, hrgn, hrgnOpaque, ::draw2d::region::combine_exclude) == NULLREGION)
      //         {
      //            ::DeleteObject(hrgn);
      //            hrgna.remove_at(i);
      //            hwnda.remove_at(i);
      //         }
      //         else
      //         {
      //            ::OffsetRgn(hrgn, -ptOffset.x, -ptOffset.y);
      //            i++;
      //         }
      //      }
      //
      //      ::DeleteObject(hrgnOpaque);
      
   }
   
   
   void window_draw::get_wnda(user::interaction_ptr_array & wndpa)
   {
      wndpa = System.frames();
   }
   
   void window_draw::get_wnda(user::oswindow_array & hwnda)
   {
      System.frames().get_wnda(hwnda);
   }
   
   // Both the device context and clip region
   // should be in screen coordinates
   
   bool window_draw::ScreenOutput(
                                  user::buffer * pbuffer,
                                  ::draw2d::region & rgnUpdate)
   {
      UNREFERENCED_PARAMETER(pbuffer);
      UNREFERENCED_PARAMETER(rgnUpdate);
      //   TRACE("//\n");
      //   TRACE("window_draw::TwfScreenOutput\n");
      //   TRACE("//\n");
      
      //      DWORD dwTimeIn = get_tick_count();
      
      user::oswindow_array hwnda;
      
      get_wnda(hwnda);
      
      user::window_util::SortByZOrder(hwnda);
      
      ASSERT(FALSE);
      /*for(int32_t i = 0; i  < hwnda.get_size(); i++)
       {
       void * hwnd = hwnda[i];
       ScreenOutput(
       pbuffer,
       hwnd,
       rgnUpdate);
       }*/
      //      DWORD dwTimeOut = get_tick_count();
      //   TRACE("//\n");
      //   TRACE("// window_draw::TwfRender\n");
      //   TRACE("// TickCount = %d \n", dwTimeOut - dwTimeIn);
      //   TRACE("//\n");
      
      return true;
   }
   
   
   
   bool window_draw::ScreenOutput(
                                  // pdc is the source primitive::memory device context
                                  // from which bitmap the screen is updated.
                                  user::buffer * pbuffer,
                                  // hwndParam ::window device context
                                  // is used from screen output
                                  ::user::interaction* pwnd)
   {
      if(pwnd != NULL)
      {
         if(pwnd->m_bVoidPaint)
         {
            return true;
         }
         if(!pwnd->m_bVisible)
         {
            return true;
         }
         if(pwnd->WfiIsIconic())
         {
            return true;
         }
         if(pwnd->m_pui != NULL && pwnd->m_pui != pwnd && !pwnd->m_pui->m_bVisible)
         {
            return true;
         }
         if(pwnd->m_pimpl != NULL && pwnd->m_pimpl != pwnd && !pwnd->m_pimpl->m_bVisible)
         {
            return true;
         }
      }
      
//      oswindow oswindowParam = pwnd->get_handle();
      
      throw not_implemented(get_app());
      //      HDC hdcScreen = ::GetDCEx((oswindow) hwndParam, NULL,  DCX_CLIPSIBLINGS | DCX_WINDOW);
      //
      //      if(hdcScreen == NULL)
      //      {
      //         // If it has failed to get ::window
      //         // owned device context, try to get
      //         // a device context from the cache.
      //         hdcScreen = ::GetDCEx((oswindow) hwndParam, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
      //
      //         // If no device context could be retrieved,
      //         // nothing can be drawn at the screen.
      //         // The function failed.
      //         if(hdcScreen == NULL)
      //            return false;
      //      }
      //
      //      ::SelectClipRgn(hdcScreen, NULL);
      //
      //
      //
      //      ////////////////////////////////////////
      //      //
      //      // Routine:
      //      // Preparation for the
      //      // bit blitting screen output.
      //      //
      //      ////////////////////////////////////////
      //
      //      // get the update region bound box.
      //      // rect rectUpdate;
      //      // rgnUpdate.get_bounding_box(rectUpdate);
      //
      //      // get the ::window client area box
      //      // in screen coordinates.
      //      rect64 rectWindow;
      //      rectWindow = pwnd->m_rectParentClient;
      //
      //      // Output rectangle receive the intersection
      //      // of ::window box and update box.
      //      //rect rectOutput;
      //      //rectOutput.intersect(rectWnd, rectUpdate);
      //
      //      // OutputClient rectangle receive the Output
      //      // rectangle in client coordinates.
      //      //rect rectOutputClient(rectOutput);
      //      //rectOutputClient -= rectWnd.top_left();
      //   //   ::ScreenToClient(hwndParam, &rectOutputClient.top_left());
      //   //   ::ScreenToClient(hwndParam, &rectOutputClient.bottom_right());
      //
      //      rect64 rectOutputClient(rectWindow);
      //      rectOutputClient -= rectWindow.top_left();
      //
      //      // The ::window owned device context is clipped
      //      // with the update region in screen coordinates
      //      // translated to ::window client coordinates.
      //      //::draw2d::region_sp rgnClip(get_app());
      //      //rgnClip->create_rect(0, 0, 0, 0);
      //      //rgnClip->CopyRgn(&rgnUpdate);
      //      //rgnClip->translate( - rectWnd.top_left());
      //
      //   //   ::SelectClipRgn(hdcScreen, rgnClip);
      //
      //      // Debug
      //   #ifdef DEBUG
      //      //rect rectClip;
      //      //rgnClip->GetRgnBox(rectClip);
      //   #endif
      //
      //      pbuffer->GetBuffer()->SetViewportOrg(0, 0);
      //
      //      point pt(0, 0);
      //
      //      ::SetViewportOrgEx(hdcScreen, 0, 0, &pt);
      //
      //      /////////////////////////////
      //      //
      //      // Routine:
      //      // Bit blitting screen output.
      //      //
      //      /////////////////////////////
      //
      //   /*   if(!::DrawDibDraw ( pbuffer->m_drawdib.m_hdrawdib,
      //         hdcScreen,
      //         rectOutputClient.left,
      //         rectOutputClient.top,
      //         rectOutputClient.width(),
      //         rectOutputClient.height(),
      //         &(pbuffer->m_spdib.m_Info.bmiHeader), pbuffer->m_spdib.m_pcolorref,
      //         rectOutput.left,
      //         rectOutput.top,
      //         rectOutput.width(),
      //         rectOutput.height(),
      //         0))
      //      {
      //         TRACE0("Bitmap not painted.\n");
      //      }*/
      //
      //      if(::GetWindowLong((oswindow) hwndParam, GWL_EXSTYLE) & WS_EX_LAYERED)
      //      {
      //         BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
      //
      //         rect64 rectWindow;
      //         rectWindow = pwnd->m_rectParentClient;
      //
      //         point pt;
      //         size sz;
      //
      //         pt = point(rectWindow.top_left());
      //         sz = size(rectWindow.size());
      //
      //         if(pt.x < 0)
      //         {
      //            pt.x = 0;
      //            sz.cx += pt.x;
      //         }
      //
      //         if(pt.y < 0)
      //         {
      //            pt.y = 0;
      //            sz.cy += pt.y;
      //         }
      //
      //         class rect rcMonitor;
      //
      //         System.get_monitor_rect(0, &rcMonitor);
      //
      //         sz.cx = (LONG) min(rectWindow.right - pt.x, rcMonitor.right - pt.x);
      //         sz.cy = (LONG) min(rectWindow.bottom - pt.y, rcMonitor.bottom - pt.y);
      //
      ////         m_pbuffer->m_spdib->fill_channel(0xc0, visual::rgba::channel_alpha);
      //
      //         ::UpdateLayeredWindow((oswindow) hwndParam, hdcScreen, &pt, &sz,
      //            (HDC)(dynamic_cast<::lnx::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
      //            &pt, 0, &blendPixelFunction, ULW_ALPHA);
      //
      //         class rect rectWin;
      //         ::GetWindowRect((oswindow) hwndParam, rectWin);
      //         if(rect(rectWindow) != rectWin || (pwnd->m_pui != NULL && (bool) pwnd->m_pui->oprop("pending_layout")))
      //         {
      //
      //
      //            if(pwnd->m_pui != NULL && (bool) pwnd->m_pui->oprop("pending_layout"))
      //            {
      //               void * hwndZOrder = (void *) pwnd->m_pui->oprop("pending_zorder").get_integer();
      //               ::SetWindowPos((oswindow) hwndParam, HWND_TOPMOST,
      //                  (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      //               ::SetWindowPos((oswindow) hwndParam, HWND_NOTOPMOST,
      //                  (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      //               ::SetWindowPos((oswindow) hwndParam, (oswindow) hwndZOrder,
      //                  (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW | SWP_FRAMECHANGED);
      //               /*simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pwnd->m_pui);
      //               if(pframe != NULL)
      //               {
      //                  pframe->ActivateFrame();
      //               }*/
      //               pwnd->m_pui->oprop("pending_layout") = false;
      //            }
      //            else
      //            {
      //               ::SetWindowPos((oswindow) hwndParam, NULL, (int32_t) rectWindow.left, (int32_t) rectWindow.top, (int32_t) rectWindow.width(), (int32_t) rectWindow.height(), SWP_SHOWWINDOW);
      //            }
      //         }
      //
      //      }
      //      else
      //      {
      //         ::BitBlt(
      //         hdcScreen,
      //         (int32_t) rectOutputClient.left,
      //         (int32_t) rectOutputClient.top,
      //         (int32_t) rectOutputClient.width(),
      //         (int32_t) rectOutputClient.height(),
      //         (HDC)(dynamic_cast<::lnx::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
      //         (int32_t) rectWindow.left,
      //         (int32_t) rectWindow.top,
      //         SRCCOPY);
      //      }
      //
      //
      //      /*::Rectangle(hdcScreen,
      //         rectOutputClient.left,
      //         rectOutputClient.top,
      //         rectOutputClient.width(),
      //         rectOutputClient.height());*/
      //
      //      ::ReleaseDC((oswindow) hwndParam, hdcScreen);
      //
      ////      DWORD dwTimeOut = get_tick_count();
      //   //   TRACE("//\n");
      //   //   TRACE("// window_draw::TwfOuputScreen\n");
      //   //   TRACE("// TickCount = %d \n", dwTimeOut - dwTimeIn);
      //   //   TRACE("//\n");
      //
      //      return true;
   }
   
   
   
   
   // The first ::window handle in the array must belong
   // to the higher z order ::window.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.
   
   
   
   // Remark: this optimization eliminates top level lnxdows
   // that are lower z order siblings of a higher z order
   // top level ::window that contains all
   // the update region in a opaque area.
   // It doesn´t eliminates from the update parent lnxdows
   // obscured by opaque children.
   
   
   
} // namespace mac



