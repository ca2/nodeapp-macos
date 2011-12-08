#include "StdAfx.h"

class keep_event_reset
{
public:
   
   
   CEvent * m_pevent;


   keep_event_reset(CEvent * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }


};

namespace win
{

   window_draw::window_draw(::ca::application * papp) : 
      ca(papp),
      message_window_simple_callback(papp),
      m_twrenderclienttool(papp)
   {
      m_dwLastRedrawRequest = ::GetTickCount();
      m_bRender = false;
      m_pbuffer = new user::buffer(papp);
      m_pbuffer->m_spdib.create(papp);
      m_dwLastUpdate = false;
   }

   extern void _001DeferPaintLayeredWindowBackground(HWND hwnd, ::ca::graphics * pdc);
   window_draw::~window_draw()
   {

   }


   bool window_draw::start()
   {
      AfxBeginThread(get_app(), &window_draw::ThreadProcRedraw, (LPVOID) this);
      return true;
   }

   /*
   void window_draw::OnPaint(HWND hwnd, CPaintDC & spgraphics)
   {
      UNREFERENCED_PARAMETER(hwnd);
      UNREFERENCED_PARAMETER(spgraphics);
   }
   */

   void window_draw::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_USER + 1984 + 1977))
      {
         _synch_redraw();
      }
   }

   void window_draw::asynch_redraw()
   {
      DWORD dwTick = ::GetTickCount();
      if(m_iFramesPerSecond == 0)
      {
         if(dwTick - m_dwLastUpdate < 1000)
            return;
      }
      else
      {
         if(dwTick - m_dwLastUpdate < natural(1000 / m_iFramesPerSecond))
            return;
      }
      _asynch_redraw();
   }

   void window_draw::_asynch_redraw()
   {
      if(!m_bProDevianMode)
      {
         m_spwindowMessage->PostMessage(WM_USER + 1984 + 1977);
      }
   }

   void window_draw::synch_redraw()
   {
      if(!m_bProDevianMode && ::IsWindow((HWND) m_spwindowMessage->get_os_data()))
      {
         m_spwindowMessage->SendMessage(WM_USER + 1984 + 1977);
      }
   }

   void window_draw::_synch_redraw()
   {
      
      keep_event_reset keepeventreset(&m_eventFree);

      static DWORD s_dwLastAnalysisFrame = 0;
      static DWORD s_dwLastFrameFrame = 0;
      static int s_iAnalysisFrameFailureCount = 0;
      static int s_iFrameFailureCount = 0;
      int iFailureTime;
      if(m_iFramesPerSecond == 0)
      {
         iFailureTime = 1000 / 12;
      }
      else
      {
         iFailureTime = 1000 / m_iFramesPerSecond;
      }
      m_dwLastUpdate = ::GetTickCount();
      UpdateBuffer();
      if(m_pbuffer->GetBuffer()->get_os_data() != NULL)
      {
         ScreenOutput();
      }
      DWORD dwTakeTime = ::GetTickCount() - m_dwLastUpdate;
      if(dwTakeTime > iFailureTime)
      {
         s_dwLastAnalysisFrame += dwTakeTime;
         s_dwLastFrameFrame += dwTakeTime;
         TRACE("window_draw::_synch_redraw :: System has exceeded prodevian performance failure time - %d milliseconds", iFailureTime);
         s_iAnalysisFrameFailureCount++;
         int iTimeFrame = 2000;
         int iMaxFailureCount = 3;
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
         int iMaxFrameFailureCount = 3;
         int iFrameTimeFrame = iTimeFrame * iMaxFrameFailureCount;
         if(s_dwLastFrameFrame > iFrameTimeFrame)
         {
            s_dwLastFrameFrame = 0;
            if(s_iFrameFailureCount > iMaxFailureCount)
            {
               TRACE("window_draw::_synch_redraw :: during prodevian Performance Analysis Time Frame - %d milliseconds -,", iTimeFrame);
               TRACE("window_draw::_synch_redraw :: failure count has exceeded the maximum count - %d", iMaxFailureCount);
               TRACE("window_draw::_synch_redraw :: Going to try to save some resource that may favor drawing perfomance");
               if(!System.savings().is_trying_to_save(gen::resource_blur_background))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blur background\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blur background\" resource");
                  System.savings().try_to_save(gen::resource_blur_background);
               }
               else if(!System.savings().is_trying_to_save(gen::resource_blurred_text_embossing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blurred text embossing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blurred text embossing\" resource");
                  System.savings().try_to_save(gen::resource_blurred_text_embossing);
               }
               else if(!System.savings().is_warning(gen::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not warning to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to warn to save \"processing\" resource");
                  System.savings().warn(gen::resource_processing);
               }
               else if(!System.savings().is_trying_to_save(gen::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"processing\" resource");
                  System.savings().try_to_save(gen::resource_blur_background);
               }
            }
            s_iFrameFailureCount = 0;
         }

      }
   }

   bool window_draw::to(
      ::ca::graphics *          pdc,
      LPCRECT        lpcrectUpdate,
      user::HwndTree::Array & hwndtreea,
      bool           bGdiLocked,
      bool           bExcludeParamWnd)
   {
      UNREFERENCED_PARAMETER(bGdiLocked);
      UNREFERENCED_PARAMETER(bExcludeParamWnd);
      CSingleLock sl(&m_mutexRender, TRUE);
      rect rectUpdate(*lpcrectUpdate);

      rect rectChild;

      rect rectNewUpdate;
      
      for(INT_PTR i = hwndtreea.get_size() - 1; i >= 0; i--)
      {
         user::HwndTree & hwndtreeChild = hwndtreea[i];
         HWND hwndChild = hwndtreeChild.m_hwnd;
         ::GetWindowRect(hwndChild, rectChild);
         if(rectNewUpdate.intersect(rectChild, rectUpdate))
         {
            to(pdc, rectNewUpdate, hwndtreeChild, true, false);
         }
       }
       return true;
   }

   bool window_draw::to(
      ::ca::graphics *          pdc,
      LPCRECT        lpcrectUpdate,
      user::HwndTree & hwndtree,
      bool           bGdiLocked,
      bool           bExcludeParamWnd)
   {
      UNREFERENCED_PARAMETER(bGdiLocked);
      CSingleLock sl(&m_mutexRender, TRUE);
      rect rectUpdate(*lpcrectUpdate);

//      DWORD dwTimeIn = GetTickCount();

      HWND hwndParam = hwndtree.m_hwnd;

      if(hwndParam == NULL)
      {
         return false;
      }

      if(!::IsWindow(hwndParam))
      {
         return false;
      }

      
            


      if(!::IsWindowVisible(hwndParam))
      {
         return true;
      }




      if(hwndtree.m_dwUser & 1)
      {
         ASSERT(TRUE);
      }
      else
      {
         ::user::window_interface * ptwi = System.window_map().get((INT_PTR) hwndParam);
         ::user::interaction * pguie = dynamic_cast < ::user::interaction * > (ptwi);
         rect rectWindow;
         ::GetWindowRect(hwndParam, rectWindow);
         //::GetClientRect(hwndParam, rectWindow);
         //::ClientToScreen(hwndParam, &rectWindow.top_left());
         //::ClientToScreen(hwndParam, &rectWindow.bottom_right());
         
         (dynamic_cast<::win::graphics * >(pdc))->SetViewportOrg(rectWindow.left, rectWindow.top);

      
         if(ptwi != NULL)
         {

       
            if(!bExcludeParamWnd &&
               pguie != NULL )
            {
               m_twrenderclienttool.FastClear();
               pguie->TwiRender(m_twrenderclienttool);
               if(m_twrenderclienttool.IsSignalizedRenderResult(
                  user::RenderDoNotProceedWithChildren))
                   return true;
            }


         }
         else
         {
            BOOL bWin4 = FALSE;
         //_AfxFillPSOnStack();
            ::DefWindowProc(
               hwndParam,
               (bWin4 ? WM_PRINT : WM_PAINT),
               (WPARAM)((dynamic_cast<::win::graphics * >(pdc))->get_os_data()),
               (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
            //::RedrawWindow(hwndParam, NULL, rgnClient, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
         }
      }


      

//      DWORD dwTimeOut = GetTickCount();
   //   TRACE("// Average Window Rendering time\n");
   //   TRACE("// Window Class: %s\n", (pwnd!=NULL) ? pwnd->GetRuntimeClass()->m_lpszClassName : "(Not available)");
   //   TRACE("// TickCount: %d \n", dwTimeOut - dwTimeIn);
   //   TRACE("// \n");


      return to(
         pdc,
         rectUpdate,
         hwndtree.m_hwndtreea,
         true,
         false);

   }


   UINT window_draw::RedrawProc()
   {
      if(!initialize_message_window("ca2::twf - ca2 Transparent Window Framework"))
      {
         TRACE("Could not initialize ca2::twf - ca2 Transparent Window Framework!");
         return 0;
      }
      ::AttachThreadInput(::GetCurrentThreadId(), WIN_THREAD(System.::ca::thread_sp::m_p)->m_nThreadID, TRUE);
      MSG msg;
      s_bRunning = true;
      while(m_bRun)
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
         while(::PeekMessageA(&msg, NULL, NULL, NULL, PM_NOREMOVE))
         {
            AfxGetThread()->pump_message();
         }
         if(m_iFramesPerSecond == 0)
         {
            Sleep(1000);
         }
         else
         {
            Sleep(1000 / m_iFramesPerSecond);
         }
      }
      //delete this;
      s_bRunning = false;
      return 0;
   }

   UINT AFX_CDECL window_draw::ThreadProcRedraw(LPVOID lpv)
   {
      window_draw * pdraw = (window_draw *) lpv;
      return pdraw->RedrawProc();
   }


   DWORD g_dwLastWindowDraw;
   // lprect should be in screen coordinates
   bool window_draw::UpdateBuffer()
   {
      if(m_bRender)
         return false;
      CSingleLock sl(&m_mutexRender, FALSE);
      if(!sl.Lock(0))
         return false;
      keeper<bool> keepRender(&m_bRender, true, false, true);
   //   TRACE("////////////////////////////////////////////////////\n");
   //   TRACE("// window_draw::TwfRender\n");
   //   TRACE("//\n");

//      DWORD dwTimeIn = GetTickCount();

      static bool bTest = false;
      ::ca::rgn & rgnClip = m_twrenderclienttool.GetClipRgn();
      rect rectClip;
/*      if(lpcrgn != NULL)
      {
         rgnClip.CopyRgn((::ca::rgn *) lpcrgn);
         rect rect;
         rgnClip.GetRgnBox(rect);
   //      TRACE("// Region");
   //      TRACE("// rgnClip.GetRgnBox:\n");
   //      TRACE("// width = %d\n", rect.width());
   //      TRACE("// height = %d\n", rect.height());
   //      TRACE("// top = %d\n", rect.top);
   //      TRACE("// left = %d\n", rect.left);
         
         if(rect.width() == 1024
            && rect.height() == 768)
         {
            ASSERT(TRUE);
         }
      }
      else if(lpcrect != NULL)
      {
         rect rect(lpcrect);
         if(rect.width() == 1024
            && rect.height() == 768)
         {
            ASSERT(TRUE);
         }
         rgnClip.SetRectRgn(
            lpcrect->left,
            lpcrect->top,
            lpcrect->right,
            lpcrect->bottom);
   //      TRACE("// Rectangle\n");
   //      TRACE("// width = %d\n", rect.width());
   //      TRACE("// height = %d\n", rect.height());
   //      TRACE("// top = %d\n", rect.top);
   //      TRACE("// left = %d\n", rect.left);
      }
      else*/
      {
   //      TRACE("// WARNING!!!\n");
   //      TRACE("// Screen as clip region\n");
   //      TRACE("// END WARNING!!!\n");
         rgnClip.SetRectRgn(
            0,
            0,
            GetSystemMetrics(SM_CXSCREEN),
            GetSystemMetrics(SM_CYSCREEN));
      }

      //TRACE("\n");


      rgnClip.GetRgnBox(rectClip);
      

      if(bTest)
      {
         //ASSERT(FALSE);
         //return VMSR_E_FAIL;
      }

   /*   CSingleLock slRendering(&m_mutexRendering, FALSE);
      if(!slRendering.Lock(0))
      {
   //xxx      AddUpdateRect(rectClip, true);
   //      return false;
      }

     */ 
      semaphore * psemaphore = TwfGetBufferSemaphore();
      CSingleLock slSemaphoreBuffer(psemaphore, FALSE);
      if(!slSemaphoreBuffer.Lock(0))
      {
   //xxx      AddUpdateRect(rectClip, true);
   //      return false;
      }



      // Turn clip rgn into its box
      rect rectClipBox;
      rgnClip.GetRgnBox(rectClipBox);
      rgnClip.SetRectRgn(
         rectClipBox.left, rectClipBox.top,
         rectClipBox.right, rectClipBox.bottom);

//      DWORD dwTime1 = GetTickCount();
   /*   TRACE("//\n");
      TRACE("// Initialization (Clip Region Creation) \n");
      TRACE("// TickCount; %d \n", dwTime1 - dwTimeIn);
      TRACE("//\n");
      TRACE("// Region");
      TRACE("// rgnClip.GetRgnBox:\n");
      TRACE("// width = %d\n", rectClipBox.width());
      TRACE("// height = %d\n", rectClipBox.height());
      TRACE("// top = %d\n", rectClipBox.top);
      TRACE("// left = %d\n", rectClipBox.left);*/


      rect rectScreen;
      System.get_screen_rect(&rectScreen);
      m_pbuffer->UpdateBuffer(rectScreen.bottom_right());
      if(m_pbuffer->GetBuffer()->get_os_data() == NULL)
         return true;

      ::ca::graphics * pdc = (dynamic_cast<::win::graphics * >(m_pbuffer->GetBuffer()));
      m_twrenderclienttool.SetDC(pdc);
      m_twrenderclienttool.GetClipRgn().CopyRgn(&rgnClip);



      if(pdc == NULL)
      {
         return false;
      }


      user::HWNDArray hwnda;

      get_wnda(hwnda);

      user::LPWndArray wndpa;

      

      get_wnda(wndpa);


      user::WndUtil::SortByZOrder(hwnda);

      user::HwndTree::Array hwndtreea;
      //hwndtreea = hwnda;
      //hwndtreea.EnumDescendants();


      

      rect rectUpdate;
      rgnClip.GetRgnBox(rectUpdate);

      rect rectOptimize;

      rectOptimize = rectUpdate;
      //TwfOptimizeRender(hwndtreea, rectOptimize);

      rect rectWindow;
      rect rect9;

/*      for(int i = hwnda.get_upper_bound(); i >= 0; i--)
      {

         if(pwnd != NULL)
         {
            pwnd->GetWindowRect(rectWindow);
         }

         if(pwnd == NULL)
            continue;

         ::GetWindowRect(hwnda[i], rectWindow);
         if(rectUpdate.is_null())
         {
            rect9 = rectWindow;
         }
         else
         {
            rect9.intersect(rectWindow, rectUpdate);
         }
         if(::GetWindowLong(hwnda[i], GWL_EXSTYLE) & WS_EX_LAYERED)
         {
         ::ca::window * pwnd = dynamic_cast < ::ca::window * > (window::FromHandlePermanent(hwnda[i]));
         if(pwnd == NULL)
         {
            for(int j = 0; j < wndpa.get_count(); j++)
            {
               if(wndpa[j]->get_safe_handle() == hwnda[i])
               {
                  pwnd = dynamic_cast < ::ca::window * > (wndpa[j]->m_pimpl);
                  break;
               }
            }
         }
            point pt;
            size sz;
            pt = rectWindow.top_left();
            sz = rectWindow.size();
            
            
            ::ca::dib_sp dib(get_app());
            dib->create(rectWindow.width(), rectWindow.height());
            DWORD_PTR dwptrResult = 0;
            ::SendMessageTimeout(
               hwnda[i],
               WM_PRINTCLIENT, 
               (WPARAM) (HDC) *dynamic_cast < ::win::graphics *> (dib->get_graphics()),
               0,
               0, 
               184,
               &dwptrResult);
            point ptDc(0, 0);


            if(pwnd == NULL)
            {
               ::UpdateLayeredWindowX(hwnda[i], NULL, NULL, NULL,
                  *dynamic_cast < ::win::graphics *> (dib->get_graphics()),
                  &ptDc, 0, NULL, ULW_OPAQUE);
            }
            else
            {
               ::UpdateLayeredWindowX(hwnda[i], NULL, &pt, &sz,
                  *dynamic_cast < ::win::graphics *> (dib->get_graphics()),
                  &ptDc, 0, NULL, ULW_OPAQUE);
            }
            
         }
         else
         {
            ::ScreenToClient(hwnda[i], &rect9.top_left());
            ::ScreenToClient(hwnda[i], &rect9.bottom_right());
            ::RedrawWindow(hwnda[i], NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
         }
      }
      return true;*/

   //   rectOptimize = rectUpdate;
   //   TwfOptimizeRender2(hwndtreea, rectOptimize);

//      DWORD dwTime2 = GetTickCount();
   //   TRACE("//\n");
   //   TRACE("// Initialization (Window Tree Creation)\n");
   //   TRACE("// TickCount = %d \n", dwTime2 - dwTime1);
   //   TRACE("//\n");
      user::HWNDArray wndaApp;

      m_wndpaOut.remove_all();


      rect rectIntersect;
      ::ca::rgn_sp rgnUpdate(get_app());
      rgnUpdate->CreateRectRgnIndirect(rectUpdate);
      HWND hwndOrder = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
      for(;;)
      {
            if(hwndOrder == NULL ||
               !::IsWindow(hwndOrder))
               break;
            BOOL bVisible = ::IsWindowVisible(hwndOrder);
            BOOL bIconic = ::IsIconic(hwndOrder);
            if(!bVisible
            || bIconic
            || wndaApp.contains(hwndOrder))
            {
            }
   /*         else if(::GetWindowLong(wndaApp[j], GWL_EXSTYLE) & WS_EX_LAYERED)
            {
               j++;
            }*/
            else
            {
               rect rectWindow;
               ::GetWindowRect(hwndOrder, rectWindow);
               ::ca::rgn_sp rgnWindow(get_app());
               rgnWindow->CreateRectRgnIndirect(rectWindow);
               ::ca::rgn_sp rgnIntersect(get_app());
               rgnIntersect->CreateRectRgn(0, 0, 0, 0);
               rgnIntersect->CombineRgn(rgnUpdate, rgnWindow, RGN_AND);
               rect rectIntersectBox;
               rgnIntersect->GetRgnBox(rectIntersectBox);
               if(rectIntersectBox.is_empty())
               {
               }
               else
               {
                  rgnUpdate->CombineRgn(rgnUpdate, rgnWindow, RGN_DIFF);
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
         for(int j = wndaApp.get_upper_bound(); j >= 0; j--)
         {
            HWND hwndTopic = wndaApp[j];

            ::ca::window * pwnd = NULL;
            //::ca::window * pwnd = dynamic_cast < ::ca::window * > (System.window_map().get((INT_PTR) hwndTopic));
            //if(pwnd == NULL)
            //{
            for(int l = 0; l < wndpa.get_count(); l++)
            {
               if(wndpa[l]->get_safe_handle() == hwndTopic)
               {
                  pwnd = dynamic_cast < ::ca::window * > (wndpa[l]->m_pimpl);
                  break;
               }
            }
            if(!::IsWindowVisible(wndaApp[j]) ||
            ::IsIconic(wndaApp[j]) || pwnd == NULL)
               continue;
            pwnd->GetWindowRect(rectWindow);
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



               /*simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pwnd);
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
            }
            pwnd->GetWindowRect(rectWindow);
            rectIntersect.intersect(rectWindow, rectUpdate);
            if(rectIntersect.area() > 0)
            {
               m_pbuffer->GetBuffer()->SetViewportOrg(0, 0);
               pwnd->_001Print(m_pbuffer->GetBuffer());
               m_wndpaOut.add(pwnd);
            }
         }

         HDC hdc = (HDC) m_pbuffer->GetBuffer()->get_os_data();
         ::SetViewportOrgEx(hdc, 0, 0, NULL);

         if(m_bDrawCursor)
         {
            point ptCursor;
            System.get_cursor_pos(&ptCursor);
            ::visual::cursor * pcursor = System.get_cursor();
            if(pcursor != NULL)
            {
               pcursor->to(m_pbuffer->GetBuffer(), ptCursor); 
            }
         }




   //   if(TwfIsBuffered())
         /*{
            ScreenOutput(
               m_pbuffer,
               rgnClip);
         }*/

   //    TwfReleaseDC(pdc);

//      DWORD dwTimeOut = GetTickCount();
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
      CSingleLock sl(&m_mutexRender, FALSE);
      if(!sl.Lock(0))
         return false;
      keeper<bool> keepRender(&m_bRender, true, false, true);
   //   TRACE("////////////////////////////////////////////////////\n");
   //   TRACE("// window_draw::TwfRender\n");
   //   TRACE("//\n");

//      DWORD dwTimeIn = GetTickCount();

      static bool bTest = false;
      ::ca::rgn & rgnClip = m_twrenderclienttool.GetClipRgn();
      rect rectClip;

      for(int i = 0; i < m_wndpaOut.get_count(); i++)
      {
         ::user::interaction* pwnd = m_wndpaOut[i];

         ScreenOutput(m_pbuffer, pwnd, rgnClip);
      
      }

      return true;

   }


   semaphore * window_draw::TwfGetBufferSemaphore()
   {
      return &m_semaphoreBuffer;
   }

   // The first ::ca::window handle in the base_array must belong
   // to the higher z order ::ca::window.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.



   // Remark: this optimization eliminates top level windows
   // that are lower z order siblings of a higher z order
   // top level ::ca::window that contains all
   // the update region in a opaque area.
   // It doesn´t eliminates from the update parent windows
   // obscured by opaque children.

   window_draw::EOptimize window_draw::TwfOptimizeRender(
      user::HwndTree::Array & hwndtreea,
      LPCRECT lpcrect)
   {
      const rect rectUpdate(*lpcrect);

      rect rectClient;
      for(int i = 0; i < hwndtreea.get_size();)
      {
         user::HwndTree & hwndtree = hwndtreea[i];
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
               HWND hwnd = hwndtreea[i].m_hwnd;
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
      user::HwndTree::Array & hwndtreea,
      int iIndex,
      LPCRECT lpcrect)
   {

      
      const rect rectOptimize(*lpcrect);
      rect rectClient;
      for(int i = iIndex; i < hwndtreea.get_size();)
      {
         user::HwndTree & hwndtree = hwndtreea[i];
         HWND hwnd = hwndtree.m_hwnd;
         rect rect;
         ::GetClientRect(hwnd, rect);
         ::ClientToScreen(hwnd, &rect.top_left());
         ::ClientToScreen(hwnd, &rect.bottom_right());
         if(rectOptimize.contains(rect))
         {
            hwndtreea.remove_at(i);
         }
         else
         {
            TwfOptimizeRenderRemoveNextProper(
               hwndtree.m_hwndtreea,
               0,
               lpcrect);

            i++;
         }
      }
      return OptimizeNone;

   }


   window_draw::EOptimize window_draw::TwfOptimizeRender(
      user::HwndTree & hwndtree,
      LPCRECT lpcrect)
   {

      hwndtree.m_dwUser = 0;

      HWND hwnd = hwndtree.m_hwnd;

      ::user::window_interface * ptwi = System.window_map().get((INT_PTR) hwnd);

      if(!::IsWindowVisible(hwnd))
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

   //    ::ca::window * pwnd = window::FromHandlePermanent(hwnd);
       
      
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

      EOptimize eoptimizeChildren = TwfOptimizeRender(
            hwndtree.m_hwndtreea,
            lpcrect);

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
      HWND hwnd,
      user::HWNDArray & hwnda,
      base_array < HRGN, HRGN > & hrgna,
      user::HwndTree::Array & hwndtreea,
      HRGN hrgn)
   {
      rect rectClient;
      for(int i = 0; i < hwndtreea.get_size(); i++)
      {
         user::HwndTree & hwndtree = hwndtreea[i];
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
      HWND hwndParam,
      user::HWNDArray & hwnda,
      base_array < HRGN, HRGN > & hrgna,
      user::HwndTree & hwndtree,
      HRGN hrgn)
   {
      HWND hwnd = hwndtree.m_hwnd;


      if(!::IsWindowVisible(hwnd))
      {
         return true;
      }




      rect rectWindow;

      ::GetWindowRect(hwnd, rectWindow);


   //   ::ca::window * pwnd = ::win::window::from_handle(hwnd);

      if(!TwfGetTopWindow(
            hwndParam,
            hwnda,
            hrgna,
            hwndtree.m_hwndtreea,
            hrgn))
      {
         return false;
      }

      HRGN hrgnIntersect;

      hrgnIntersect = ::CreateRectRgnIndirect(rectWindow);

      int iCombine = ::CombineRgn(hrgnIntersect, hrgn, hrgnIntersect, RGN_AND);

      if(iCombine == NULLREGION)
      {
         ::DeleteObject(hrgnIntersect);
         return true;
      }

      

      ::user::window_interface * pwndi = System.window_map().get((INT_PTR) hwnd);

      if(pwndi == NULL)
      {
         ::SendMessage(
            hwnd,
            ::user::window_interface::MessageBaseWndGetProperty, 
            ::user::window_interface::PropertyDrawBaseWndInterface, 
            (LPARAM) &pwndi);
      }

      if(hwndParam == hwnd ||
         (pwndi != NULL && 
            pwndi->_001HasTranslucency()))
      {
      

         iCombine = ::CombineRgn(hrgn, hrgn, hrgnIntersect, RGN_DIFF);

         point ptOffset(0, 0);

         ::ScreenToClient(hwnd, &ptOffset);

         hwnda.add(hwnd);
         ::OffsetRgn(hrgnIntersect, ptOffset.x, ptOffset.y);
         hrgna.add(hrgnIntersect);

         if(iCombine == NULLREGION)
         {
            return false;
         }
         
      }
      else
      {
         ::DeleteObject(hrgnIntersect);
         TwfGetTopWindowOptimizeOpaque(
            hwnd,
            hwnda,
            hrgna);

      }
      if(hwndParam == hwnd)
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   // lpcrect must be in screen coordinates
   void window_draw::TwfGetTopWindow(
      HWND hwnd,
      user::HWNDArray & hwnda,
      base_array < HRGN, HRGN > & hrgna,
      user::HwndTree::Array & hwndtreea,
      LPCRECT lpcrect)
   {
      HRGN hrgn = ::CreateRectRgnIndirect(lpcrect);
      TwfGetTopWindow(
         hwnd,
         hwnda, 
         hrgna, 
         hwndtreea, 
         hrgn);
      ::DeleteObject(hrgn);
   }

   void window_draw::TwfGetTopWindowOptimizeOpaque(
      HWND hwndOpaque,
      user::HWNDArray & hwnda,
      base_array < HRGN, HRGN > & hrgna)
   {
      rect rectWindow;

   //   ::ca::window * pwndOpaque = window::FromHandlePermanent(hwndOpaque);

      ::GetWindowRect(hwndOpaque, rectWindow);

      HRGN hrgnOpaque = ::CreateRectRgnIndirect(rectWindow);

      point ptOffset;
      for(int i = 0; i < hrgna.get_size(); )
      {
         HWND hwnd = hwnda[i];
         HRGN hrgn = hrgna[i];
         ptOffset.x = 0;
         ptOffset.y = 0;
         ::ClientToScreen(hwnd, &ptOffset);
         ::OffsetRgn(hrgn, ptOffset.x, ptOffset.y);
         if(::CombineRgn(hrgn, hrgn, hrgnOpaque, RGN_DIFF) == NULLREGION)
         {
            ::DeleteObject(hrgn);
            hrgna.remove_at(i);
            hwnda.remove_at(i);
         }
         else
         {
            ::OffsetRgn(hrgn, -ptOffset.x, -ptOffset.y);
            i++;
         }
      }

      ::DeleteObject(hrgnOpaque);

   }


   void window_draw::get_wnda(user::LPWndArray & wndpa)
   {
      wndpa = System.frames();
   }

   void window_draw::get_wnda(user::HWNDArray & hwnda)
   {
      System.frames().get_wnda(hwnda);
   }

   // Both the device context and clip region
   // should be in screen coordinates

   bool window_draw::ScreenOutput(
      user::buffer * pbuffer,
      ::ca::rgn & rgnUpdate)
   {
      UNREFERENCED_PARAMETER(pbuffer);
      UNREFERENCED_PARAMETER(rgnUpdate);
   //   TRACE("//\n");
   //   TRACE("window_draw::TwfScreenOutput\n");
   //   TRACE("//\n");

//      DWORD dwTimeIn = GetTickCount();

      user::HWNDArray hwnda;
      
      get_wnda(hwnda);

      user::WndUtil::SortByZOrder(hwnda);

      ASSERT(FALSE);
      /*for(int i = 0; i  < hwnda.get_size(); i++)
      {
         HWND hwnd = hwnda[i];
         ScreenOutput(
            pbuffer,
            hwnd,
            rgnUpdate);
      }*/
//      DWORD dwTimeOut = GetTickCount();
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
      // hwndParam ::ca::window device context
      // is used from screen output
      ::user::interaction* pwnd,
      // rgnUpdate is the region in screen coordinates
      // to be screen output
      ::ca::rgn & rgnUpdate 
      )
   {
      UNREFERENCED_PARAMETER(rgnUpdate);
      if(pwnd != NULL)
      {
         if(pwnd->m_bVoidPaint)
         {
            return true;
         }
      }

      HWND hwndParam = (HWND) pwnd->_get_handle();

      //////////////////////////////////
      //
      // Routine:
      // hwndParam handle ::ca::window
      // device context retrieve
      //
      //////////////////////////////////.

      // Try to get ::ca::window owned
      // device context.

      HDC hdcScreen = ::GetDCEx(
         hwndParam,
         NULL,
         DCX_CLIPSIBLINGS | DCX_WINDOW);
      /*HDC hdcScreen = ::GetDCEx(
         NULL,
         NULL,
         0);*/

   /*   HDC hdcScreen = ::GetDCEx(
         hwndParam,
         NULL,
         DCX_WINDOW);*/
      if(hdcScreen == NULL)
      {
         // If it has failed to get ::ca::window
         // owned device context, try to get
         // a device context from the cache.
         hdcScreen = ::GetDCEx(
            hwndParam,
            NULL,
            DCX_CACHE 
            | DCX_CLIPSIBLINGS | DCX_WINDOW);

         // If no device context could be retrieved,
         // nothing can be drawn at the screen.
         // The function failed.
         if(hdcScreen == NULL)
            return false;
      }

      ::SelectClipRgn(hdcScreen, NULL);


      // Debug
   #ifdef _DEBUG
//      DWORD dw = GetLastError();
   #endif

      ////////////////////////////////////////
      //
      // Routine:
      // Preparation for the
      // bit blitting screen output.
      //
      ////////////////////////////////////////

      // get the update region bound box.
      // rect rectUpdate;
      // rgnUpdate.GetRgnBox(rectUpdate);

      // get the ::ca::window client area box
      // in screen coordinates.
      rect64 rectWindow;
      rectWindow = pwnd->m_rectParentClient;

      // Output rectangle receive the intersection
      // of ::ca::window box and update box.
      //rect rectOutput;
      //rectOutput.intersect(rectWnd, rectUpdate);

      // OutputClient rectangle receive the Output
      // rectangle in client coordinates.
      //rect rectOutputClient(rectOutput);
      //rectOutputClient -= rectWnd.top_left();
   //   ::ScreenToClient(hwndParam, &rectOutputClient.top_left());
   //   ::ScreenToClient(hwndParam, &rectOutputClient.bottom_right());

      rect64 rectOutputClient(rectWindow);
      rectOutputClient -= rectWindow.top_left();

      // The ::ca::window owned device context is clipped
      // with the update region in screen coordinates
      // translated to ::ca::window client coordinates.
      //::ca::rgn_sp rgnClip(get_app());
      //rgnClip->CreateRectRgn(0, 0, 0, 0);
      //rgnClip->CopyRgn(&rgnUpdate);
      //rgnClip->OffsetRgn( - rectWnd.top_left());

   //   ::SelectClipRgn(hdcScreen, rgnClip);
      
      // Debug
   #ifdef _DEBUG
      //rect rectClip;
      //rgnClip->GetRgnBox(rectClip);
   #endif

      pbuffer->GetBuffer()->SetViewportOrg(0, 0);

      point pt(0, 0);

      ::SetViewportOrgEx(hdcScreen, 0, 0, &pt);

      /////////////////////////////
      //
      // Routine:
      // Bit blitting screen output.
      //
      /////////////////////////////

   /*   if(!::DrawDibDraw ( pbuffer->m_drawdib.m_hdrawdib, 
         hdcScreen, 
         rectOutputClient.left,
         rectOutputClient.top,
         rectOutputClient.width(),
         rectOutputClient.height(), 
         &(pbuffer->m_spdib.m_Info.bmiHeader), pbuffer->m_spdib.m_pcolorref, 
         rectOutput.left,
         rectOutput.top,
         rectOutput.width(),
         rectOutput.height(), 
         0))
      {
         TRACE0("Bitmap not painted.\n");
      }*/

      if(::GetWindowLong(hwndParam, GWL_EXSTYLE) & WS_EX_LAYERED)
      {
         BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, 0 };

         rect64 rectWindow;
         rectWindow = pwnd->m_rectParentClient;

         point pt;
         size sz;

         pt = point(rectWindow.top_left());
         sz = size(rectWindow.size());

         if(pt.x < 0)
         {
            pt.x = 0;
            sz.cx += pt.x;
         }

         if(pt.y < 0)
         {
            pt.y = 0;
            sz.cy += pt.y;
         }
         
         sz.cx = (LONG) min(rectWindow.right - pt.x, System.m_monitorinfoa[0].rcMonitor.right - pt.x);
         sz.cy = (LONG) min(rectWindow.bottom - pt.y, System.m_monitorinfoa[0].rcMonitor.bottom - pt.y);

         ::UpdateLayeredWindow(hwndParam, hdcScreen, &pt, &sz,
            (HDC)(dynamic_cast<::win::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
            &pt, 0, &blendPixelFunction, ULW_OPAQUE);

         /*
         class rect rectWin;
         ::GetWindowRect(hwndParam, rectWin);
         if(rectWindow != rectWin)
         {
            ::SetWindowPos(hwndParam, NULL, rectWin.left, rectWin.top, rectWin.width(), rectWin.height(),  SWP_NOZORDER | SWP_NOACTIVATE);
         }
         */
      }
      else
      {
         ::BitBlt(
         hdcScreen,
         (int) rectOutputClient.left,
         (int) rectOutputClient.top,
         (int) rectOutputClient.width(),
         (int) rectOutputClient.height(), 
         (HDC)(dynamic_cast<::win::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
         (int) rectWindow.left,
         (int) rectWindow.top,
         SRCCOPY);
      }


      /*::Rectangle(hdcScreen,
         rectOutputClient.left,
         rectOutputClient.top,
         rectOutputClient.width(),
         rectOutputClient.height());*/

      ::ReleaseDC(hwndParam, hdcScreen);

//      DWORD dwTimeOut = GetTickCount();
   //   TRACE("//\n");
   //   TRACE("// window_draw::TwfOuputScreen\n");
   //   TRACE("// TickCount = %d \n", dwTimeOut - dwTimeIn);
   //   TRACE("//\n");

      return true;
   }




   // The first ::ca::window handle in the base_array must belong
   // to the higher z order ::ca::window.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.



   // Remark: this optimization eliminates top level windows
   // that are lower z order siblings of a higher z order
   // top level ::ca::window that contains all
   // the update region in a opaque area.
   // It doesn´t eliminates from the update parent windows
   // obscured by opaque children.



} // namespace win