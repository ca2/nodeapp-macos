#include "framework.h"
//#include <cairo/cairo-xlib.h>

//#define COMPILE_MULTIMON_STUBS
//#include <multimon.h>

//#include "sal.h"

CLASS_DECL_mac void hook_window_create(::user::interaction * pWnd);
CLASS_DECL_mac bool unhook_window_create();
void CLASS_DECL_mac __pre_init_dialog(
                                      ::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld);
void CLASS_DECL_mac __post_init_dialog(
                                       ::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld);
LRESULT CALLBACK
__activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam);

//const char gen_OldWndProc[] = "::ca2::OldWndProc423";

/*const char gen_WndControlBar[] = __WNDCONTROLBAR;
 const char gen_WndMDIFrame[] = __WNDMDIFRAME;
 const char gen_WndFrameOrView[] = __WNDFRAMEORVIEW;
 const char gen_WndOleControl[] = __WNDOLECONTROL;
 */
struct __CTLCOLOR
{
   oswindow hWnd;
   HDC hDC;
   UINT nCtlType;
};

WINBOOL PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);


WINBOOL GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);

/*
 const char gen_Wnd[] = __WND;
 */
namespace mac
{
   
   void window::mouse_hover_add(sp(::user::interaction) pinterface)
   {
      m_guieptraMouseHover.add_unique(pinterface);
   }
   
   void window::mouse_hover_remove(sp(::user::interaction) pinterface)
   {
      m_guieptraMouseHover.remove(pinterface);
   }
   
   
   window::window()
   {
      
      m_pcallback          = NULL;
      m_pui              = this;
      //set_handle(NULL);
      m_puiOwner         = NULL;
      m_pui->m_nFlags    = 0;
      //m_pfnSuper         = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_pfont              = NULL;
      m_pguieCapture       = NULL;
      m_oswindow           = NULL;
      
   }
   
   
   void window::construct(oswindow hWnd)
   {
      
      m_pcallback          = NULL;
      m_pui              = this;
      m_oswindow           = hWnd;
      //set_handle(hWnd);
      m_pui->m_nFlags    = 0;
      //m_pfnSuper         = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_pfont              = NULL;
      m_pguieCapture       = NULL;
      m_oswindow           = NULL;
      
   }
   
   
   window::window(base_application * papp) :
   element(papp),
   ::user::interaction(papp)
   {
      
      m_pcallback          = NULL;
      m_pui              = this;
      //set_handle(NULL);
      m_puiOwner         = NULL;
      m_pui->m_nFlags    = 0;
      //m_pfnSuper         = NULL;
      m_nModalResult       = 0;
      m_bMouseHover        = false;
      m_pfont              = NULL;
      m_pguieCapture       = NULL;
      m_oswindow           = NULL;
      
   }
   
   
   sp(::window) window::from_os_data(void * pdata)
   {
      
      return dynamic_cast < ::window * >(from_handle((oswindow) pdata));
      
   }
   
   
   void * window::get_os_data() const
   {
      
      return ((oswindow &) m_oswindow);
      
   }
   
   
   
   // Change a window's style
   
   /*__STATIC bool CLASS_DECL_mac __modify_style(oswindow hWnd, int32_t nStyleOffset,
    DWORD dwRemove, DWORD dwAdd, UINT nFlags)
    {
    ASSERT(hWnd != NULL);
    DWORD dwStyle = ::GetWindowLong(hWnd, nStyleOffset);
    DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if (dwStyle == dwNewStyle)
    return FALSE;
    
    ::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
    if (nFlags != 0)
    {
    ::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
    SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
    }
    return TRUE;
    }*/
   
   
   bool  window::ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      
//      throw todo(::get_thread_app());
      
      if(!::IsWindow(hWnd))
         return false;
      
      DWORD dw = hWnd->get_window_long(GWL_STYLE);
      
      dw &= ~dwRemove;
      
      dw |= dwAdd;
      
      hWnd->set_window_long(GWL_STYLE, dw);
      
      //return __modify_style(hWnd, GWL_STYLE, dwRemove, dwAdd, nFlags);
      
      return true;
      
   }
   
   
   bool window::ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      
//      throw todo(::get_thread_app());

      if(!::IsWindow(hWnd))
         return false;
      
      DWORD dw = hWnd->get_window_long(GWL_EXSTYLE);
      
      dw &= ~dwRemove;
      
      dw |= dwAdd;
      
      hWnd->set_window_long(GWL_EXSTYLE, dw);
      
      return true;
      
      //      return __modify_style(hWnd, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);
      
   }
   
   
   
   const MESSAGE* PASCAL window::GetCurrentMessage()
   {
      // fill in time and position when asked for
      /*    ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
       pThreadState->m_lastSentMsg.time = ::GetMessageTime();
       pThreadState->m_lastSentMsg.pt = point(::GetMessagePos());
       return &pThreadState->m_lastSentMsg;*/
      return NULL;
   }
   
   LRESULT window::Default()
   {
      // call DefWindowProc with the last message
      /*      ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
       return DefWindowProc(pThreadState->m_lastSentMsg.message,
       pThreadState->m_lastSentMsg.wparam, pThreadState->m_lastSentMsg.lparam);*/
      return 0;
   }
   
   
   ::mac::window * window::from_handle(oswindow oswindow)
   {
      
      if(oswindow == NULL)
         return NULL;
      
      return dynamic_cast < ::mac::window * > (oswindow->get_user_interaction()->m_pimpl.m_p);
      
   }
   
   
   window * PASCAL window::FromHandlePermanent(oswindow oswindow)
   {
      return dynamic_cast < ::mac::window * > (oswindow->get_user_interaction()->m_pimpl.m_p);
   }
   
   bool window::Attach(oswindow hWndNew)
   {
      
      ASSERT(get_handle() == NULL);     // only attach once, detach on destroy
      //  ASSERT(FromHandlePermanent(hWndNew) == NULL);
      // must not already be in permanent ::collection::map
      
      if (hWndNew == NULL)
         return FALSE;
      //single_lock sl(afxMutexHwnd(), TRUE);
      //hwnd_map * pMap = afxMapHWND(TRUE); // create ::collection::map if not exist
      //ASSERT(pMap != NULL);
      
      //pMap->set_permanent(set_handle(hWndNew), this);
      //if(m_pui == NULL)
      {
         //m_pui = this;
      }
      
      m_oswindow = hWndNew;
      
      return TRUE;
      
   }
   
   oswindow window::Detach()
   {
      oswindow hWnd = (oswindow) get_handle();
      if (hWnd != NULL)
      {
         //         single_lock sl(afxMutexHwnd(), TRUE);
         //  ;;       hwnd_map * pMap = afxMapHWND(); // don't create if not exist
         //     if (pMap != NULL)
         //      pMap->remove_handle(get_handle());
         //         set_handle(NULL);
         m_oswindow = NULL;
      }
      
      return hWnd;
   }
   
   void window::pre_subclass_window()
   {
      // no default processing
   }
   
   
   /////////////////////////////////////////////////////////////////////////////
   // window creation
   
   bool window::CreateEx(DWORD dwExStyle, const char * lpszClassName,
                         const char * lpszWindowName, DWORD dwStyle,
                         const RECT& rect, sp(::user::interaction) pParentWnd, id id,
                         LPVOID lpParam /* = NULL */)
   {
      return CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle,
                      rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                      pParentWnd->get_safe_handle(), id, lpParam);
   }
   
   
   bool window::CreateEx(DWORD dwExStyle, const char * lpszClassName,
                         const char * lpszWindowName, DWORD dwStyle,
                         int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
                         oswindow hWndParent, id id, LPVOID lpParam)
   {
      
      if(::IsWindow(get_handle()))
      {
         
         DestroyWindow();
            
      }

      m_pthread = ::get_thread();
      
      if(m_pthread == NULL)
         m_pthread = get_app();
         
      if(m_pthread == NULL)
         return false;
         
      m_pthread->add(this);
      m_pui->m_pthread = m_pthread;
         m_pui->m_pthread->add(m_pui);
         
      
      UNREFERENCED_PARAMETER(id);
      //      ASSERT(lpszClassName == NULL || __is_valid_string(lpszClassName) ||
      //       __is_valid_atom(lpszClassName));
      ENSURE_ARG(lpszWindowName == NULL || __is_valid_string(lpszWindowName));
      
      // allow modification of several common create parameters
      CREATESTRUCT cs;
      cs.dwExStyle = dwExStyle;
      cs.lpszClass = lpszClassName;
      cs.lpszName = lpszWindowName;
      cs.style = dwStyle;
      cs.x = x;
      cs.y = y;
      cs.cx = nWidth;
      cs.cy = nHeight;
      //      cs.hwndParent = hWndParent;
      //   cs.hMenu = hWndParent == NULL ? NULL : nIDorHMenu;
      cs.hMenu = NULL;
      //      cs.hInstance = System.m_hInstance;
      cs.lpCreateParams = lpParam;
      
      if(m_pui != NULL && m_pui != this)
      {
         
         if(!m_pui->pre_create_window(cs))
         {
            
            PostNcDestroy();
            
            return FALSE;
            
         }
         
      }
      else
      {
         
         if (!pre_create_window(cs))
         {
            
            PostNcDestroy();
            
            return FALSE;
            
         }
         
      }
      
      if(cs.hwndParent == NULL)
      {
         
         cs.style &= ~WS_CHILD;
         
      }
      
      hook_window_create(this);
      
      CGRect rect;
      
      rect.origin.x = x;
      rect.origin.y = y;
      rect.size.width = nWidth;
      rect.size.height = nHeight;
      

      if(hWndParent == MESSAGE_WINDOW_PARENT)
      {
      
         return true;
         
      }
      else
      {
         
         m_oswindow = oswindow_get(new_round_window(this, rect));
         
         m_oswindow->set_user_interaction(m_pui);
         
      }
      
      send_message(WM_CREATE, 0, (LPARAM) &cs);      
      
//      throw todo(get_app());
      
/*      Display *dpy;
      Window rootwin;
      XEvent e;
      int32_t scr;
      //      cairo_surface_t *cs;
      
      if(!(dpy=XOpenDisplay(NULL))) {
         fprintf(stderr, "ERROR: Could not open display\n");
         exit(1);
      }
      
      scr=DefaultScreen(dpy);
      rootwin=RootWindow(dpy, scr);
      
      if(cs.cx <= 0)
         cs.cx = 1;
      if(cs.cy <= 0)
         cs.cy = 1;
      
      Window window = XCreateSimpleWindow(dpy, rootwin, 1, 1, cs.cx, cs.cy, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));
      
      
      
      */
      /*oswindow hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
       cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
       cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);*/
      
//#ifdef DEBUG
/*      if (window == 0)
      {
         DWORD dwLastError = GetLastError();
         string strLastError = FormatMessageFromSystem(dwLastError);
         string strMessage;
         strMessage.Format("%s\n\nSystem Error Code: %d", strLastError, dwLastError);
         
         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: oswindow creation failed: GetLastError returned:\n");
         TRACE(::ca2::trace::category_AppMsg, 0, "%s\n", strMessage);
         try
         {
            if(dwLastError == 0x0000057e)
            {
               System.simple_message_box(NULL, "Cannot create a top-level child window.");
            }
            else
            {
               System.simple_message_box(NULL, strMessage);
            }
         }
         catch(...)
         {
         }
         return false;
      }
#endif
      
      m_oswindow = oswindow(dpy, window);
      
      XStoreName(m_oswindow.display(), m_oswindow.window(), "hello");
      XSelectInput(m_oswindow.display(), m_oswindow.window(), ExposureMask|ButtonPressMask);
      XMapWindow(m_oswindow.display(), m_oswindow.window());
      
      */
      if (!unhook_window_create())
         PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
      
      //    if (mac == NULL)
      //return FALSE;
      ///      WNDCLASS wndcls;
      /*      if(lpszClassName != NULL &&
       GetClassInfo(System.m_hInstance, lpszClassName, &wndcls) &&
       wndcls.hIcon != NULL)
       {
       m_pui->set_icon(new ::visual::icon(wndcls.hIcon), false);
       m_pui->set_icon(new ::visual::icon(wndcls.hIcon), true);
       }*/
      //      oswindow hwndHandle = get_handle();
      /*      if(mac != get_handle())
       {
       ASSERT(FALSE); // should have been set in send msg hook
       }*/
      return TRUE;
   }
   
   // for child windows
   bool window::pre_create_window(CREATESTRUCT& cs)
   {
      /*      if (cs.lpszClass == NULL)
       {
       // make sure the default window class is registered
       VERIFY(__end_defer_register_class(__WND_REG, &cs.lpszClass));
       
       // no WNDCLASS provided - use child window default
       ASSERT(cs.style & WS_CHILD);
       }*/
      return TRUE;
   }
   
   bool window::create(const char * lpszClassName,
                       const char * lpszWindowName, DWORD dwStyle,
                       const RECT& rect,
                       sp(::user::interaction) pParentWnd, id id,
                       ::create_context * pContext)
   {
      // can't use for desktop or pop-up windows (use CreateEx instead)
      ASSERT(pParentWnd != NULL);
      ASSERT((dwStyle & WS_POPUP) == 0);
      
      return CreateEx(0, lpszClassName, lpszWindowName,
                      dwStyle | WS_CHILD,
                      rect.left, rect.top,
                      rect.right - rect.left, rect.bottom - rect.top,
                      pParentWnd->get_handle(), id, (LPVOID)pContext);
   }
   
   bool window::create_message_queue(const char * pszName, ::message_queue_listener * pcallback)
   {
      m_pcallback = pcallback;
      if(IsWindow())
      {
         SetWindowText(pszName);
      }
      else
      {
         string strName = "ca2::fontopus::message_wnd::winservice_1";
         if(!CreateEx(0, NULL, pszName, WS_CHILD, 0, 0, 0, 0, MESSAGE_WINDOW_PARENT, "", NULL))
         {
            return false;
         }
      }
      return true;
   }
   
   
   window::~window()
   {
      
      if(m_pbaseapp != NULL && m_pbaseapp->m_pplaneapp != NULL && m_pbaseapp->m_pplaneapp->m_psystem != NULL && Sys(m_pbaseapp).user()->m_pwindowmap != NULL)
      {
         Sys(m_pbaseapp).user()->m_pwindowmap->m_map.remove_key((int_ptr) get_handle());
      }
      
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if(m_pfont != NULL)
      {
         delete m_pfont;
      }
      sl.unlock();
      if (get_handle() != NULL)
      {
         TRACE(::core::trace::category_AppMsg, 0, "Warning: calling DestroyWindow in window::~window; "
               "OnDestroy or PostNcDestroy in derived class will not be called.\n");
         m_pcallback = NULL;
         DestroyWindow();
      }
   }
   
   void window::install_message_handling(::message::dispatch * pinterface)
   {
      //m_pbuffer->InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_DESTROY           , pinterface, this, &window::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_NCDESTROY         , pinterface, this, &window::_001OnNcDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT             , pinterface, this, &window::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_PRINT             , pinterface, this, &window::_001OnPrint);
      if(m_pui != NULL && m_pui != this)
      {
         m_pui->install_message_handling(pinterface);
      }
      IGUI_WIN_MSG_LINK(WM_CAPTURECHANGED    , pinterface, this, &window::_001OnCaptureChanged);
      IGUI_WIN_MSG_LINK(WM_CREATE            , pinterface, this, &window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR         , pinterface, this, &window::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND        , pinterface, this, &window::_001OnEraseBkgnd);
      IGUI_WIN_MSG_LINK(WM_MOVE              , pinterface, this, &window::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_SIZE              , pinterface, this, &window::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW        , pinterface, this, &window::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(ca2m_PRODEVIAN_SYNCH , pinterface, this, &window::_001OnProdevianSynch);
      IGUI_WIN_MSG_LINK(WM_TIMER             , pinterface, this, &window::_001OnTimer);
   }
   
   void window::_001OnMove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      /*      if(!m_bRectOk && !(GetExStyle() & WS_EX_LAYERED))
       {
       class rect rectWindow;
       ::GetWindowRect(get_handle(), rectWindow);
       m_pui->m_rectParentClient = rectWindow;
       m_rectParentClient = rectWindow;
       }*/
   }
   
   void window::_001OnSize(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      
      
      /*      if(!m_bRectOk && !(GetExStyle() & WS_EX_LAYERED))
       {
       class rect rectWindow;
       ::GetWindowRect(get_handle(), rectWindow);
       m_pui->m_rectParentClient = rectWindow;
       m_rectParentClient = rectWindow;
       }*/
      
      /*      if(m_spdibMultAlphaWork.is_null())
       {
       m_spdibMultAlphaWork.create(get_app());
       }
       
       if(m_spdib.is_null())
       {
       m_spdib.create(get_app());
       }
       
       if(m_spdib.is_set() && m_rectParentClient.area() > 0)
       {
       m_spdib->create(m_rectParentClient.size());
       }*/
      
      m_pui->layout();
      
      
      
   }
   
   void window::_001OnShowWindow(signal_details * pobj)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pobj);
      
      m_bVisible = pshowwindow->m_bShow != FALSE;
      
      if(m_pui != NULL && m_pui != this)
         m_pui->m_bVisible = m_bVisible;
      
      if(m_bVisible)
      {
         
         round_window_show();
         
      }
      
   }
   
   void window::_001OnDestroy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Default();
      ::mac::window_draw * pdraw = dynamic_cast < ::mac::window_draw * > (System.get_twf().m_p);
      if(pdraw != NULL)
      {
         retry_single_lock sl(&pdraw->m_eventFree, millis(84), millis(84));
         pdraw->m_wndpaOut.remove(this);
         pdraw->m_wndpaOut.remove(m_pui);
      }
   }
   
   void window::_001OnCaptureChanged(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pguieCapture = NULL;
   }
   
   // WM_NCDESTROY is the absolute LAST message sent.
   void window::_001OnNcDestroy(signal_details * pobj)
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      pobj->m_bRet = true;
      // cleanup main and active windows
      ::thread* pThread = System.GetThread();
      if (pThread != NULL)
      {
         if (pThread->GetMainWnd() == this)
         {
            if (!afxContextIsDLL)
            {
               // shut down current thread if possible
               if (pThread != &System)
                  __post_quit_message(0);
            }
            pThread->SetMainWnd(NULL);
         }
         if (pThread->get_active_ui() == this)
            pThread->set_active_ui(NULL);
      }
      
      // cleanup tooltip support
      if(m_pui != NULL)
      {
         if (m_pui->m_nFlags & WF_TOOLTIPS)
         {
         }
      }
      
      // call default, unsubclass, and detach from the ::collection::map
      /*      WNDPROC pfnWndProc = WNDPROC(GetWindowLongPtr(get_handle(), GWLP_WNDPROC));
       Default();
       if (WNDPROC(GetWindowLongPtr(get_handle(), GWLP_WNDPROC)) == pfnWndProc)
       {
       WNDPROC pfnSuper = *GetSuperWndProcAddr();
       if (pfnSuper != NULL)
       SetWindowLongPtr(get_handle(), GWLP_WNDPROC, reinterpret_cast<int_ptr>(pfnSuper));
       }*/
      Detach();
      ASSERT(get_handle() == NULL);
      m_pfnDispatchWindowProc = &window::_start_user_message_handler;
      // call special post-cleanup routine
      PostNcDestroy();
      if(m_pui != NULL && m_pui != this)
      {
         m_pui->PostNcDestroy();
      }
   }
   
   void window::PostNcDestroy()
   {
      //set_handle(NULL);
//      m_oswindow.post_nc_destroy();
      // default to nothing
   }
   
   void window::on_final_release()
   {
      if (get_handle() != NULL)
         DestroyWindow();    // will call PostNcDestroy
      else
         PostNcDestroy();
   }
   
   void window::assert_valid() const
   {
      if (get_handle() == NULL)
         return;     // null (unattached) windows are valid
      
      // check for special wnd??? values
      //      ASSERT(oswindow_TOP == NULL);       // same as desktop
      /*      if (get_handle() == oswindow_BOTTOM)
       {
       }
       else if (get_handle() == oswindow_TOPMOST)
       {
       }
       else if (get_handle() == oswindow_NOTOPMOST)
       {
       }
       else
       {
       // should be a normal window
       ASSERT(::IsWindow(get_handle()));
       
       // should also be in the permanent or temporary handle ::collection::map
       single_lock sl(afxMutexHwnd(), TRUE);
       hwnd_map * pMap = afxMapHWND();
       if(pMap == NULL) // inside thread not having windows
       return; // let go
       ASSERT(pMap != NULL);
       
       //         ::ca2::object* p=NULL;
       if(pMap)
       {
       ASSERT( (p = pMap->lookup_permanent(get_handle())) != NULL ||
       (p = pMap->lookup_temporary(get_handle())) != NULL);
       }*/
      
      //ASSERT(dynamic_cast < ::window * > (p) == this);   // must be us
      
      // Note: if either of the above asserts fire and you are
      // writing a multithreaded application, it is likely that
      // you have passed a C++ object from one thread to another
      // and have used that object in a way that was not intended.
      // (only simple inline wrapper functions should be used)
      //
      // In general, window objects should be passed by oswindow from
      // one thread to another.  The receiving thread can wrap
      // the oswindow with a window object by using ::mac::window::from_handle.
      //
      // It is dangerous to pass C++ objects from one thread to
      // another, unless the objects are designed to be used in
      // such a manner.
      //      }*/
   }
   
   
   void window::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);
      
      dumpcontext << "\nm_hWnd = " << (void *)get_handle();
      
      /*      if (get_handle() == NULL || get_handle() == oswindow_BOTTOM ||
       get_handle() == oswindow_TOPMOST || get_handle() == oswindow_NOTOPMOST)
       {
       // not a normal window - nothing more to dump
       return;
       }*/
      
      /*      if (!::IsWindow(get_handle()))
       {
       // not a valid window
       dumpcontext << " (illegal oswindow)";
       return; // don't do anything more
       }*/
      
      ::window * pWnd = (::window *) this;
      if (pWnd != this)
         dumpcontext << " (Detached or temporary window)";
      else
         dumpcontext << " (permanent window)";
      
      // dump out window specific statistics
      char szBuf [64];
//      if (!const_cast < window * > (this)->send_message(WM_QUERYAFXWNDPROC, 0, 0) && pWnd == this)
//         ((::window *) this)->GetWindowText(szBuf, _countof(szBuf));
      //    else
      //         ::DefWindowProc(get_handle(), WM_GETTEXT, _countof(szBuf), (LPARAM)&szBuf[0]);
      dumpcontext << "\ncaption = \"" << szBuf << "\"";
      
      //      ::GetClassName(get_handle(), szBuf, _countof(szBuf));
      //    dumpcontext << "\nclass name = \"" << szBuf << "\"";
      
      rect rect;
      ((::window *) this)->GetWindowRect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::window * = " << (void *)((::window *) this)->get_parent();
      
      //      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      //    if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
      //     dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());
      
      dumpcontext << "\n";
   }
   
   bool window::DestroyWindow()
   {
      single_lock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      ::window * pWnd;
      hwnd_map * pMap;
      oswindow hWndOrig;
      bool bResult;
      
      if ((get_handle() == NULL) )
         return FALSE;
      
      bResult = FALSE;
      pMap = NULL;
      pWnd = NULL;
      hWndOrig = NULL;
      if (get_handle() != NULL)
      {
         //         single_lock sl(afxMutexHwnd(), TRUE);
         //       pMap = afxMapHWND();
         //     if(pMap != NULL)
         {
            //      pWnd = dynamic_cast < ::window * > (pMap->lookup_permanent(get_handle()));
#ifdef DEBUG
            //    hWndOrig = get_handle();
#endif
         }
      }
      sl.unlock();
      //    if (get_handle() != NULL)
      //         bResult = ::DestroyWindow(get_handle()) != FALSE;
      sl.lock();
      if (hWndOrig != NULL)
      {
         // Note that 'this' may have been deleted at this point,
         //  (but only if pWnd != NULL)
         if (pWnd != NULL)
         {
            // Should have been detached by OnNcDestroy
#ifdef DEBUG
            //            ::window * pWndPermanent = dynamic_cast < ::window * > (pMap->lookup_permanent(hWndOrig));;
            //          ASSERT(pWndPermanent == NULL);
            // It is important to call base class, including ca2 core
            // base classes implementation of install_message_handling
            // inside derived class install_message_handling
#endif
         }
         else
         {
#ifdef DEBUG
            ASSERT(get_handle() == hWndOrig);
#endif
            // Detach after DestroyWindow called just in case
            Detach();
         }
      }
      
      return bResult;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Default window implementation
   
   
   LRESULT window::DefWindowProc(UINT nMsg, WPARAM wparam, LPARAM lparam)
   {
      /*  if (m_pfnSuper != NULL)
       return ::CallWindowProc(m_pfnSuper, get_handle(), nMsg, wparam, lparam);
       
       WNDPROC pfnWndProc;
       if ((pfnWndProc = *GetSuperWndProcAddr()) == NULL)
       return ::DefWindowProc(get_handle(), nMsg, wparam, lparam);
       else
       return ::CallWindowProc(pfnWndProc, get_handle(), nMsg, wparam, lparam);*/
      
      return 0;
   }
   
   /*
    WNDPROC* window::GetSuperWndProcAddr()
    {
    // Note: it is no longer necessary to override GetSuperWndProcAddr
    //  for each control class with a different WNDCLASS.
    //  This implementation now uses instance data, such that the previous
    //  WNDPROC can be anything.
    
    return &m_pfnSuper;
    }
    */
   void window::pre_translate_message(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // no default processing
   }
   
   
   void window::GetWindowText(string & rString)
   {
      /*ASSERT(::IsWindow(get_handle()));
       
       int32_t nLen = ::GetWindowTextLength(get_handle());
       ::GetWindowText(get_handle(), rString.GetBufferSetLength(nLen), nLen+1);
       rString.ReleaseBuffer();*/
      rString = m_strWindowText;
      
   }
   
   /*
    int32_t window::GetDlgItemText(int32_t nID, string & rString) const
    {
    ASSERT(::IsWindow(get_handle()));
    rString = "";    // is_empty without deallocating
    
    oswindow hWnd = ::GetDlgItem(get_handle(), nID);
    if (hWnd != NULL)
    {
    int32_t nLen = ::GetWindowTextLength(hWnd);
    ::GetWindowText(hWnd, rString.GetBufferSetLength(nLen), nLen+1);
    rString.ReleaseBuffer();
    }
    
    return (int32_t)rString.get_length();
    }
    */
   
   bool window::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      /*    ASSERT(::IsWindow(get_handle()));
       lpwndpl->length = sizeof(WINDOWPLACEMENT);
       return ::GetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
      return false;
   }
   
   bool window::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      /*      ASSERT(::IsWindow(get_handle()));
       ((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);
       return ::SetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
      return false;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // window will delegate owner draw messages to self drawing controls
   
   // Drawing: for all 4 control types
   // /*   void window::OnDrawItem(int32_t /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
   // {
   
   // reflect notification to child window control
   //  if (ReflectLastMsg(lpDrawItemStruct->hwndItem))
   //   return;     // eat it
   
   // not handled - do default
   //      Default();
   // }
   
   // Drawing: for all 4 control types
   //   int32_t window::OnCompareItem(int32_t /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   // {
   //  // reflect notification to child window control
   //LRESULT lResult;
   //      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
   //       return (int32_t)lResult;        // eat it
   
   // not handled - do default
   //  return (int32_t)Default();
   //   }
   
   // void window::OnDeleteItem(int32_t /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
   //{
   // reflect notification to child window control
   // if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
   //  return;     // eat it
   // not handled - do default
   //      Default();
   // }
   
   bool window::_EnableToolTips(bool bEnable, UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      return FALSE;
   }
   
   
   // Measure item implementation relies on unique control/menu IDs
   //   void window::OnMeasureItem(int32_t /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
   /* {
    if (lpMeasureItemStruct->CtlType == ODT_MENU)
    {
    ASSERT(lpMeasureItemStruct->CtlID == 0);
    }
    else
    {
    ::user::interaction * pChild = GetDescendantWindow(lpMeasureItemStruct->CtlID);
    if (pChild != NULL && pChild->SendChildNotifyLastMsg())
    return;     // eaten by child
    }
    // not handled - do default
    Default();
    }*/
   
   /*   bool window::GetWindowInfo(PWINDOWINFO pwi) const
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::GetWindowInfo((oswindow)get_handle(), pwi) != FALSE;
    }*/
   
   /*   ::window * window::GetAncestor(UINT gaFlags) const
    { ASSERT(::IsWindow((oswindow)get_handle())); return  ::mac::window::from_handle(::GetAncestor((oswindow)get_handle(), gaFlags)); }
    
    */
   
   /*   bool window::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    ASSERT(psbi != NULL);
    return ::GetScrollBarInfo((oswindow)get_handle(), idObject, psbi) != FALSE;
    }
    */
   /*   bool window::GetTitleBarInfo(PTITLEBARINFO pti) const
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    ASSERT(pti != NULL);
    return ::GetTitleBarInfo((oswindow)get_handle(), pti) != FALSE;
    }
    */
   /*   bool window::AnimateWindow(DWORD dwTime, DWORD dwFlags)
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::AnimateWindow((oswindow)get_handle(), dwTime, dwFlags) != FALSE;
    }
    
    bool window::FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout)
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    FLASHWINFO fwi;
    fwi.cbSize = sizeof(fwi);
    fwi.hwnd = (oswindow)get_handle();
    fwi.dwFlags = dwFlags;
    fwi.uCount = uCount;
    fwi.dwTimeout = dwTimeout;
    
    return ::FlashWindowEx(&fwi) != FALSE;
    }
    */
   
   /*
    bool window::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::SetLayeredWindowAttributes((oswindow)get_handle(), crKey, bAlpha, dwFlags) != FALSE;
    }
    
    bool window::UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
    ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::UpdateLayeredWindow((oswindow)get_handle(), WIN_HDC(pDCDst), pptDst, psize,
    WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;
    }
    
    */
   /*
    bool window::GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::GetLayeredWindowAttributes((oswindow)get_handle(), pcrKey, pbAlpha, pdwFlags) != FALSE;
    }
    
    bool window::PrintWindow(::draw2d::graphics * pgraphics, UINT nFlags) const
    {
    ASSERT(::IsWindow((oswindow)get_handle()));
    return ::PrintWindow((oswindow)get_handle(), (HDC)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), nFlags) != FALSE;
    }
    
    */
   LRESULT window::OnNTCtlColor(WPARAM wparam, LPARAM lparam)
   {
      // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
      /*    __CTLCOLOR ctl;
       ctl.hDC = (HDC)wparam;
       ctl.hWnd = (oswindow)lparam;
       ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
       ctl.nCtlType = pThreadState->m_lastSentMsg.message - WM_CTLCOLORMSGBOX;
       //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
       ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);
       
       // Note: We call the virtual message_handler for this window directly,
       //  instead of calling ::ca2::CallWindowProc, so that Default()
       //  will still work (it will call the Default window proc with
       //  the original Win32 WM_CTLCOLOR message).
       
       return message_handler(WM_CTLCOLOR, 0, (LPARAM)&ctl);*/
      return 0;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // window extensions for help support
   
   /*   void window::WinHelp(dword_ptr dwData, UINT nCmd)
    {
    UNREFERENCED_PARAMETER(dwData);
    UNREFERENCED_PARAMETER(nCmd);
    throw not_implemented(get_app());
    
         application* pApp = &System;
    ASSERT_VALID(pApp);
    ASSERT(pApp->m_pszHelpFilePath != NULL);
    ASSERT(pApp->m_eHelpType == afxWinHelp);
    
    wait_cursor wait(get_app());
    
    PrepareForHelp();
    
    // need to use top level parent (for the case where get_handle() is in DLL)
    ::user::interaction * pWnd = EnsureTopLevelParent();
    
    TRACE(::ca2::trace::category_AppMsg, 0, "WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);
    
    // finally, run the oswindows Help engine
     trans   if (!::WinHelp(MAC_WINDOW(pWnd)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
    {
    // linux System.simple_message_box(__IDP_FAILED_TO_LAUNCH_HELP);
    System.simple_message_box("Failed to launch help");
    }*/
   //}
   
   //void window::HtmlHelp(dword_ptr dwData, UINT nCmd)
   //{
   // throw not_implemented(get_app());
   /*
    application* pApp = &System;
    ASSERT_VALID(pApp);
    ASSERT(pApp->m_pszHelpFilePath != NULL);
    // to call HtmlHelp the m_fUseHtmlHelp must be set in
    // the application's constructor
    ASSERT(pApp->m_eHelpType == afxHTMLHelp);
    
    wait_cursor wait(get_app());
    
    PrepareForHelp();
    
    // need to use top level parent (for the case where get_handle() is in DLL)
    ::user::interaction * pWnd = EnsureTopLevelParent();
    
    TRACE(::ca2::trace::category_AppMsg, 0, "HtmlHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n", pApp->m_pszHelpFilePath, dwData, nCmd);
    
    // run the HTML Help engine
     trans   if (!::ca2::HtmlHelp(MAC_WINDOW(pWnd)->get_handle(), pApp->m_pszHelpFilePath, nCmd, dwData))
    {
    // linux System.simple_message_box(__IDP_FAILED_TO_LAUNCH_HELP);
    System.simple_message_box("Failed to launch help");
    }*/
   //}
   
   void window::PrepareForHelp()
   {
      /*if (IsFrameWnd())
       {
       // frame_window windows should be allowed to exit help mode first
       frame_window* pFrameWnd = dynamic_cast < frame_window * >(this);
       pFrameWnd->ExitHelpMode();
       }
       
       // cancel any tracking modes
       send_message(WM_CANCELMODE);
       SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
       
       // need to use top level parent (for the case where get_handle() is in DLL)
       ::user::interaction * pWnd = EnsureTopLevelParent();
       MAC_WINDOW(pWnd)->send_message(WM_CANCELMODE);
       MAC_WINDOW(pWnd)->SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
       
       // attempt to cancel capture
       oswindow hWndCapture = ::GetCapture();
       if (hWndCapture != NULL)
       ::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);*/
   }
   
   
   /*void window::WinHelpInternal(dword_ptr dwData, UINT nCmd)
    {
    UNREFERENCED_PARAMETER(dwData);
    UNREFERENCED_PARAMETER(nCmd);
    throw not_implemented(get_app());
    
    application* pApp = &System;
    ASSERT_VALID(pApp);
    if (pApp->m_eHelpType == afxHTMLHelp)
    {
    // translate from WinHelp commands and data to to HtmlHelp
    ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
    if (nCmd == HELP_CONTEXT)
    nCmd = HH_HELP_CONTEXT;
    else if (nCmd == HELP_CONTENTS)
    nCmd = HH_DISPLAY_TOC;
    else if (nCmd == HELP_FINDER)
    nCmd = HH_HELP_FINDER;
    HtmlHelp(dwData, nCmd);
    }
    else
    WinHelp(dwData, nCmd);*/
   //}
   
   
   
   bool window::_001OnCmdMsg(base_cmd_msg * pcmdmsg)
   {
      if(command_target_interface::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      
      //      bool b;
      
      //if(_iguimessageDispatchCommandMessage(pcommand, b))
      // return b;
      
      command_target * pcmdtarget = dynamic_cast < command_target * > (this);
      return pcmdtarget->command_target::_001OnCmdMsg(pcmdmsg);
   }
   
   
   bool window::BaseOnControlEvent(::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }
   
   void window::_002OnDraw(::draw2d::graphics * pdc)
   {
      
      //      ::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));
      
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // main message_handler implementation
   
   void window::message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      
      if(pbase->m_uiMessage == WM_SIZE || pbase->m_uiMessage == WM_MOVE)
      {
         
//         win_update_graphics();
         
      }
      
      if(pbase->m_uiMessage == WM_KEYDOWN ||
         pbase->m_uiMessage == WM_KEYUP ||
         pbase->m_uiMessage == WM_CHAR)
      {
         
         SCAST_PTR(::message::key, pkey, pobj);
         
//         Application.user()->keyboard().translate_os_key_message(pkey);
         
         if(pbase->m_uiMessage == WM_KEYDOWN)
         {
            try
            {
               Application.set_key_pressed(pkey->m_ekey, true);
            }
            catch(...)
            {
            }
         }
         else if(pbase->m_uiMessage == WM_KEYUP)
         {
            try
            {
               Application.set_key_pressed(pkey->m_ekey, false);
            }
            catch(...)
            {
            }
         }
      }
      
      if(m_pui != NULL)
      {
         m_pui->pre_translate_message(pobj);
         if(pobj->m_bRet)
            return;
      }
      
      if(m_pcallback != NULL)
      {
         m_pcallback->message_queue_message_handler(pobj);
         if(pobj->m_bRet)
            return;
      }
      if(pbase->m_uiMessage == WM_TIMER)
      {
//         m_pthread->m_pthread->step_timer();
      }
      else if(pbase->m_uiMessage == WM_LBUTTONDOWN)
      {
         g_pwndLastLButtonDown = this;
      }
      else if(pbase->m_uiMessage == WM_SIZE)
      {
         m_bUpdateGraphics = true;
      }
      /*      else if(pbase->m_uiMessage == CA2M_BERGEDGE)
       {
       if(pbase->m_wparam == BERGEDGE_GETAPP)
       {
       ::application ** ppapp= (::application **) pbase->m_lparam;
       *ppapp = get_app();
       pbase->m_bRet = true;
       return;
       }
       }*/
      pbase->set_lresult(0);
      
      /*      if(pbase->m_uiMessage == WM_MOUSELEAVE)
       {
       m_bMouseHover = false;
       for(int32_t i = 0; i < m_guieptraMouseHover.get_size(); i++)
       {
       if(m_guieptraMouseHover[i] == this
       || m_guieptraMouseHover[i]->m_pimpl == this
       || m_guieptraMouseHover[i]->m_pui == this)
       continue;
       m_guieptraMouseHover[i]->send_message(WM_MOUSELEAVE);
       }
       m_guieptraMouseHover.remove_all();
       }*/
      
      if(pbase->m_uiMessage == WM_LBUTTONDOWN ||
         pbase->m_uiMessage == WM_LBUTTONUP ||
         pbase->m_uiMessage == WM_MBUTTONDOWN ||
         pbase->m_uiMessage == WM_MBUTTONUP ||
         pbase->m_uiMessage == WM_RBUTTONDOWN ||
         pbase->m_uiMessage == WM_RBUTTONUP ||
         pbase->m_uiMessage == WM_MOUSEMOVE ||
         pbase->m_uiMessage == WM_MOUSEMOVE)
         //         pbase->m_uiMessage == WM_MOUSEWHEEL)
      {
         // user presence status activity reporting
         if(pbase->m_uiMessage == WM_LBUTTONDOWN
            || pbase->m_uiMessage == WM_RBUTTONDOWN
            || pbase->m_uiMessage == WM_MBUTTONDOWN
            || pbase->m_uiMessage == WM_MOUSEMOVE)
         {
            if(Application.fontopus()->m_puser != NULL)
            {
               if(&ApplicationUser != NULL)
               {
                  if(ApplicationUser.m_ppresence != NULL)
                  {
                     try
                     {
                        ApplicationUser.m_ppresence->report_activity();
                     }
                     catch(...)
                     {
                     }
                  }
               }
            }
         }
         ::message::mouse * pmouse = (::message::mouse *) pbase;
         
         Application.m_ptCursor = pmouse->m_pt;
         if(m_pbaseapp->m_pplaneapp->m_psession != NULL)
         {
            Session.m_ptCursor = pmouse->m_pt;
         }
         if(m_pui != NULL && m_pui != this && m_pui->m_pbaseapp->m_pplaneapp->m_psession != NULL && m_pui->m_pbaseapp->m_pplaneapp->m_psession != m_pbaseapp->m_pplaneapp->m_psession)
         {
            Sess(m_pui->m_pbaseapp->m_pplaneapp->m_psession).m_ptCursor = pmouse->m_pt;
         }
         
         sp(base_session) psession;
         
         if(m_pbaseapp->m_pplaneapp->is_system())
         {
            psession = System.query_session(0);
            if(psession != NULL && psession->m_bSessionSynchronizedCursor)
            {
               psession->m_ptCursor = pmouse->m_pt;
            }
         }
         
         if(m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
         {
            pmouse->m_bTranslated = true;
            rect64 rectWindow;
            if(m_bOSNativeMouseMessagePosition)
            {
               class rect rectWindow32;
               //               ::GetWindowRect(get_handle(), &rectWindow32);
               ::copy(rectWindow, rectWindow32);
            }
            else
            {
               m_pui->GetWindowRect(rectWindow);
            }
            if(System.get_monitor_count() > 0)
            {
               rect rcMonitor;
               System.get_monitor_rect(0, &rcMonitor);
               if(rectWindow.left >= rcMonitor.left)
                  pmouse->m_pt.x += (LONG) rectWindow.left;
               if(rectWindow.top >= rcMonitor.top)
                  pmouse->m_pt.y += (LONG) rectWindow.top;
            }
            else
            {
               if(rectWindow.left >= 0)
                  pmouse->m_pt.x += (LONG) rectWindow.left;
               if(rectWindow.top >= 0)
                  pmouse->m_pt.y += (LONG) rectWindow.top;
            }
         }
         
         if(pbase->m_uiMessage == WM_MOUSEMOVE)
         {
            // We are at the message_handler procedure.
            // mouse messages originated from message_handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = visual::cursor_default;
         }
      restart_mouse_hover_check:
         for(int32_t i = 0; i < m_guieptraMouseHover.get_size(); i++)
         {
            if(!m_guieptraMouseHover[i]._001IsPointInside(pmouse->m_pt))
            {
               ::user::interaction * pui = &m_guieptraMouseHover[i];
               //               pui->send_message(WM_MOUSELEAVE);
               m_guieptraMouseHover.remove(pui);
               goto restart_mouse_hover_check;
            }
         }
         if(!m_bMouseHover)
         {
            m_pui->_001OnTriggerMouseInside();
         }
         if(m_pguieCapture != NULL)
         {
            if(m_pguieCapture->m_pimpl != NULL)
            {
               //m_pguieCapture->m_pimpl->SendMessage(pbase);
               try
               {
                  (m_pguieCapture->m_pimpl->*m_pguieCapture->m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pmouse));
                  if(pmouse->get_lresult() != 0)
                     return;
               }
               catch(...)
               {
               }
               return;
            }
            else
            {
               //m_pguieCapture->SendMessage(pbase);
               try
               {
                  (m_pguieCapture->*m_pguieCapture->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pmouse));
                  if(pmouse->get_lresult() != 0)
                     return;
               }
               catch(...)
               {
               }
               return;
            }
         }
         user::oswindow_array hwnda;
         user::interaction_ptr_array wnda(get_app());
         wnda = System.frames();
         wnda.get_wnda(hwnda);
         user::window_util::SortByZOrder(hwnda);
         for(int32_t i = 0; i < hwnda.get_size(); i++)
         {
            ::user::interaction * pguie = wnda.find_first(hwnda[i]);
            if(pguie != NULL && pguie->m_pui != NULL)
            {
               pguie->m_pui->_000OnMouse(pmouse);
               if(pmouse->m_bRet)
                  return;
            }
         }
         pbase->set_lresult(DefWindowProc(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
         return;
      }
      else if(pbase->m_uiMessage == WM_KEYDOWN ||
              pbase->m_uiMessage == WM_KEYUP ||
              pbase->m_uiMessage == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;

//         Application.user()->keyboard().translate_os_key_message(pkey);
         /*
         if(pbase->m_uiMessage == WM_KEYDOWN)
         {
            try
            {
               Application.set_key_pressed(pkey->m_ekey, true);
            }
            catch(...)
            {
            }
         }
         else if(pbase->m_uiMessage == WM_KEYUP)
         {
            try
            {
               Application.set_key_pressed(pkey->m_ekey, false);
            }
            catch(...)
            {
            }
         }
         */
         
         ::user::interaction * puiFocus = dynamic_cast < ::user::interaction * > (Application.user()->get_keyboard_focus().m_p);
         if(puiFocus != NULL
            && puiFocus->IsWindow()
            && puiFocus->GetTopLevelParent() != NULL)
         {
            puiFocus->send(pkey);
            if(pbase->m_bRet)
               return;
         }
         else if(!pkey->m_bRet)
         {
            if(m_pui != this && m_pui != NULL)
            {
               m_pui->_000OnKey(pkey);
               if(pbase->m_bRet)
                  return;
            }
            else
            {
               _000OnKey(pkey);
               if(pbase->m_bRet)
                  return;
            }
         }
         pbase->set_lresult(DefWindowProc(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
         return;
      }
      if(pbase->m_uiMessage == ::message::message_event)
      {
         if(m_pui != this && m_pui != NULL)
         {
            m_pui->BaseOnControlEvent((::user::control_event *) pbase->m_lparam);
         }
         else
         {
            BaseOnControlEvent((::user::control_event *) pbase->m_lparam);
         }
         return;
      }
      (this->*m_pfnDispatchWindowProc)(pobj);
      if(pobj->m_bRet)
         return;
      /*
       if(m_pui != NULL && m_pui != this)
       {
       m_pui->_user_message_handler(pobj);
       if(pobj->m_bRet)
       return;
       }
       */
      pbase->set_lresult(DefWindowProc(pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
   }
   
   /*
    bool window::OnWndMsg(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
    {
    LRESULT lResult = 0;
    union MessageMapFunctions mmf;
    mmf.pfn = 0;
    CInternalGlobalLock winMsgLock;
    // special case for commands
    if (message == WM_COMMAND)
    {
    if (OnCommand(wparam, lparam))
    {
    lResult = 1;
    goto LReturnTrue;
    }
    return FALSE;
    }
    
    // special case for notifies
    if (message == WM_NOTIFY)
    {
    NMHDR* pNMHDR = (NMHDR*)lparam;
    if (pNMHDR->hwndFrom != NULL && OnNotify(wparam, lparam, &lResult))
    goto LReturnTrue;
    return FALSE;
    }
    
    // special case for activation
    if (message == WM_ACTIVATE)
    __handle_activate(this, wparam, ::mac::window::from_handle((oswindow)lparam));
    
    // special case for set cursor HTERROR
    if (message == WM_SETCURSOR &&
    __handle_set_cursor(this, (short)LOWORD(lparam), HIWORD(lparam)))
    {
    lResult = 1;
    goto LReturnTrue;
    }
    
    // special case for windows that contain windowless ActiveX controls
    bool bHandled;
    
    bHandled = FALSE;
    
    const __MSGMAP* pMessageMap; pMessageMap = GetMessageMap();
    UINT iHash; iHash = (LOWORD((dword_ptr)pMessageMap) ^ message) & (iHashMax-1);
    winMsgLock.lock(CRIT_WINMSGCACHE);
    __MSG_CACHE* pMsgCache; pMsgCache = &gen_MsgCache[iHash];
    const __MSGMAP_ENTRY* lpEntry;
    if (message == pMsgCache->nMsg && pMessageMap == pMsgCache->pMessageMap)
    {
    // cache hit
    lpEntry = pMsgCache->lpEntry;
    winMsgLock.unlock();
    if (lpEntry == NULL)
    return FALSE;
    
    // cache hit, and it needs to be handled
    if (message < 0xC000)
    goto LDispatch;
    else
    goto LDispatchRegistered;
    }
    else
    {
    // not in cache, look for it
    pMsgCache->nMsg = message;
    pMsgCache->pMessageMap = pMessageMap;
       for ( pMessageMap already init'ed */ /*; pMessageMap->pfnGetBaseMap != NULL;
                                            pMessageMap = (*pMessageMap->pfnGetBaseMap)())
                                            {
                                            // Note: catch not so common but fatal mistake!!
                                            //       // BEGIN_MESSAGE_MAP(CMyWnd, CMyWnd)
                                            ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
                                            if (message < 0xC000)
                                            {
                                            // constant window message
                                            if ((lpEntry = ::ca2::FindMessageEntry(pMessageMap->lpEntries,
                                            message, 0, 0)) != NULL)
                                            {
                                            pMsgCache->lpEntry = lpEntry;
                                            winMsgLock.unlock();
                                            goto LDispatch;
                                            }
                                            }
                                            else
                                            {
                                            // registered windows message
                                            lpEntry = pMessageMap->lpEntries;
                                            while ((lpEntry = ::ca2::FindMessageEntry(lpEntry, 0xC000, 0, 0)) != NULL)
                                            {
                                            UINT* pnID = (UINT*)(lpEntry->nSig);
                                            ASSERT(*pnID >= 0xC000 || *pnID == 0);
                                            // must be successfully registered
                                            if (*pnID == message)
                                            {
                                            pMsgCache->lpEntry = lpEntry;
                                            winMsgLock.unlock();
                                            goto LDispatchRegistered;
                                            }
                                            lpEntry++;      // keep looking past this one
                                            }
                                            }
                                            }
                                            
                                            pMsgCache->lpEntry = NULL;
                                            winMsgLock.unlock();
                                            return FALSE;
                                            }
                                            
                                            LDispatch:
                                            ASSERT(message < 0xC000);
                                            
                                            mmf.pfn = lpEntry->pfn;
                                            
                                            switch (lpEntry->nSig)
                                            {
                                            default:
                                            ASSERT(FALSE);
                                            break;
                                            case ::ca2::Sig_l_p:
                                            {
                                            point point(lparam);
                                            lResult = (this->*mmf.pfn_l_p)(point);
                                            break;
                                            }
                                            case ::ca2::Sig_b_D_v:
                                            lResult = (this->*mmf.pfn_b_D)(::draw2d_quartz2d::graphics::from_handle(reinterpret_cast<HDC>(wparam)));
                                            break;
                                            
                                            case ::ca2::Sig_b_b_v:
                                            lResult = (this->*mmf.pfn_b_b)(static_cast<bool>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_b_u_v:
                                            lResult = (this->*mmf.pfn_b_u)(static_cast<UINT>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_b_h_v:
                                            lResult = (this->*mmf.pfn_b_h)(reinterpret_cast<HANDLE>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_i_u_v:
                                            lResult = (this->*mmf.pfn_i_u)(static_cast<UINT>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_C_v_v:
                                            lResult = reinterpret_cast<LRESULT>((this->*mmf.pfn_C_v)());
                                            break;
                                            
                                            case ::ca2::Sig_v_u_W:
                                            (this->*mmf.pfn_v_u_W)(static_cast<UINT>(wparam),
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)));
                                            break;
                                            
                                            case ::ca2::Sig_u_u_v:
                                            lResult = (this->*mmf.pfn_u_u)(static_cast<UINT>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_b_v_v:
                                            lResult = (this->*mmf.pfn_b_v)();
                                            break;
                                            
                                            case ::ca2::Sig_b_W_uu:
                                            lResult = (this->*mmf.pfn_b_W_u_u)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)),
                                            LOWORD(lparam), HIWORD(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_b_W_COPYDATASTRUCT:
                                            lResult = (this->*mmf.pfn_b_W_COPYDATASTRUCT)(
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)),
                                            reinterpret_cast<COPYDATASTRUCT*>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_b_v_HELPINFO:
                                            lResult = (this->*mmf.pfn_b_HELPINFO)(reinterpret_cast<LPHELPINFO>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_CTLCOLOR:
                                            {
                                            // special case for OnCtlColor to avoid too many temporary objects
                                            ASSERT(message == WM_CTLCOLOR);
                                            __CTLCOLOR* pCtl = reinterpret_cast<__CTLCOLOR*>(lparam);
                                            ::draw2d::graphics_sp dcTemp;
                                            dcTemp.set_handle1(pCtl->hDC);
                                            window wndTemp;
                                            wndTemp.set_handle(pCtl->hWnd);
                                            UINT nCtlType = pCtl->nCtlType;
                                            // if not coming from a permanent window, use stack temporary
                                            ::window * pWnd = ::mac::window::FromHandlePermanent(wndTemp.get_handle());
                                            if (pWnd == NULL)
                                            {
                                            pWnd = &wndTemp;
                                            }
                                            HBRUSH hbr = (this->*mmf.pfn_B_D_W_u)(&dcTemp, pWnd, nCtlType);
                                            // fast detach of temporary objects
                                            dcTemp.set_handle1(NULL);
                                            wndTemp.set_handle(NULL);
                                            lResult = reinterpret_cast<LRESULT>(hbr);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_CTLCOLOR_REFLECT:
                                            {
                                            // special case for CtlColor to avoid too many temporary objects
                                            ASSERT(message == WM_REFLECT_BASE+WM_CTLCOLOR);
                                            __CTLCOLOR* pCtl = reinterpret_cast<__CTLCOLOR*>(lparam);
                                            ::draw2d::graphics_sp dcTemp;
                                            dcTemp.set_handle1(pCtl->hDC);
                                            UINT nCtlType = pCtl->nCtlType;
                                            HBRUSH hbr = (this->*mmf.pfn_B_D_u)(&dcTemp, nCtlType);
                                            // fast detach of temporary objects
                                            dcTemp.set_handle1(NULL);
                                            lResult = reinterpret_cast<LRESULT>(hbr);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_i_u_W_u:
                                            lResult = (this->*mmf.pfn_i_u_W_u)(LOWORD(wparam),
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)), HIWORD(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_i_uu_v:
                                            lResult = (this->*mmf.pfn_i_u_u)(LOWORD(wparam), HIWORD(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_i_W_uu:
                                            lResult = (this->*mmf.pfn_i_W_u_u)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)),
                                            LOWORD(lparam), HIWORD(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_i_v_s:
                                            lResult = (this->*mmf.pfn_i_s)(reinterpret_cast<LPTSTR>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_l_w_l:
                                            lResult = (this->*mmf.pfn_l_w_l)(wparam, lparam);
                                            break;
                                            
                                            
                                            
                                            case ::ca2::Sig_v_b_h:
                                            (this->*mmf.pfn_v_b_h)(static_cast<bool>(wparam),
                                            reinterpret_cast<HANDLE>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_h_v:
                                            (this->*mmf.pfn_v_h)(reinterpret_cast<HANDLE>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_h_h:
                                            (this->*mmf.pfn_v_h_h)(reinterpret_cast<HANDLE>(wparam),
                                            reinterpret_cast<HANDLE>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_v_v:
                                            (this->*mmf.pfn_v_v)();
                                            break;
                                            
                                            case ::ca2::Sig_v_u_v:
                                            (this->*mmf.pfn_v_u)(static_cast<UINT>(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_u_u:
                                            (this->*mmf.pfn_v_u_u)(static_cast<UINT>(wparam), static_cast<UINT>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_uu_v:
                                            (this->*mmf.pfn_v_u_u)(LOWORD(wparam), HIWORD(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_v_ii:
                                            (this->*mmf.pfn_v_i_i)(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_u_uu:
                                            (this->*mmf.pfn_v_u_u_u)(static_cast<UINT>(wparam), LOWORD(lparam), HIWORD(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_u_ii:
                                            (this->*mmf.pfn_v_u_i_i)(static_cast<UINT>(wparam), LOWORD(lparam), HIWORD(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_w_l:
                                            (this->*mmf.pfn_v_w_l)(wparam, lparam);
                                            break;
                                            
                                            case ::ca2::Sig_MDIACTIVATE:
                                            (this->*mmf.pfn_v_b_W_W)(get_handle() == reinterpret_cast<oswindow>(lparam),
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)),
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)));
                                            break;
                                            
                                            case ::ca2::Sig_v_D_v:
                                            (this->*mmf.pfn_v_D)(::draw2d_quartz2d::graphics::from_handle(reinterpret_cast<HDC>(wparam)));
                                            break;
                                            
                                            
                                            case ::ca2::Sig_v_W_v:
                                            (this->*mmf.pfn_v_W)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)));
                                            break;
                                            
                                            case ::ca2::Sig_v_v_W:
                                            (this->*mmf.pfn_v_W)(::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)));
                                            break;
                                            
                                            case ::ca2::Sig_v_W_uu:
                                            (this->*mmf.pfn_v_W_u_u)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)), LOWORD(lparam),
                                            HIWORD(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_W_p:
                                            {
                                            point point(lparam);
                                            (this->*mmf.pfn_v_W_p)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)), point);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_v_W_h:
                                            (this->*mmf.pfn_v_W_h)(::mac::window::from_handle(reinterpret_cast<oswindow>(wparam)),
                                            reinterpret_cast<HANDLE>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_ACTIVATE:
                                            (this->*mmf.pfn_v_u_W_b)(LOWORD(wparam),
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)), HIWORD(wparam));
                                            break;
                                            
                                            case ::ca2::Sig_SCROLL:
                                            case ::ca2::Sig_SCROLL_REFLECT:
                                            {
                                            // special case for WM_VSCROLL and WM_HSCROLL
                                            ASSERT(message == WM_VSCROLL || message == WM_HSCROLL ||
                                            message == WM_VSCROLL+WM_REFLECT_BASE || message == WM_HSCROLL+WM_REFLECT_BASE);
                                            int32_t nScrollCode = (short)LOWORD(wparam);
                                            int32_t nPos = (short)HIWORD(wparam);
                                            if (lpEntry->nSig == ::ca2::Sig_SCROLL)
                                            (this->*mmf.pfn_v_u_u_W)(nScrollCode, nPos,
                                            ::mac::window::from_handle(reinterpret_cast<oswindow>(lparam)));
                                            else
                                            (this->*mmf.pfn_v_u_u)(nScrollCode, nPos);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_v_v_s:
                                            (this->*mmf.pfn_v_s)(reinterpret_cast<LPTSTR>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_u_cs:
                                            (this->*mmf.pfn_v_u_cs)(static_cast<UINT>(wparam), reinterpret_cast<const char *>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_OWNERDRAW:
                                            (this->*mmf.pfn_v_i_s)(static_cast<int32_t>(wparam), reinterpret_cast<LPTSTR>(lparam));
                                            lResult = TRUE;
                                            break;
                                            
                                            case ::ca2::Sig_i_i_s:
                                            lResult = (this->*mmf.pfn_i_i_s)(static_cast<int32_t>(wparam), reinterpret_cast<LPTSTR>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_u_v_p:
                                            {
                                            point point(lparam);
                                            lResult = (this->*mmf.pfn_u_p)(point);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_u_v_v:
                                            lResult = (this->*mmf.pfn_u_v)();
                                            break;
                                            
                                            case ::ca2::Sig_v_b_NCCALCSIZEPARAMS:
                                            (this->*mmf.pfn_v_b_NCCALCSIZEPARAMS)(static_cast<bool>(wparam),
                                            reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_v_WINDOWPOS:
                                            (this->*mmf.pfn_v_v_WINDOWPOS)(reinterpret_cast<WINDOWPOS*>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_uu_M:
                                            (this->*mmf.pfn_v_u_u_M)(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HMENU>(lparam));
                                            break;
                                            
                                            case ::ca2::Sig_v_u_p:
                                            {
                                            point point(lparam);
                                            (this->*mmf.pfn_v_u_p)(static_cast<UINT>(wparam), point);
                                            }
                                            break;
                                            
                                            case ::ca2::Sig_SIZING:
                                            (this->*mmf.pfn_v_u_pr)(static_cast<UINT>(wparam), reinterpret_cast<LPRECT>(lparam));
                                            lResult = TRUE;
                                            break;
                                            
                                            case ::ca2::Sig_MOUSEWHEEL:
                                            lResult = (this->*mmf.pfn_b_u_s_p)(LOWORD(wparam), (short)HIWORD(wparam),
                                            point(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)));
                                            if (!lResult)
                                            return FALSE;
                                            break;
                                            case ::ca2::Sig_l:
                                            lResult = (this->*mmf.pfn_l_v)();
                                            if (lResult != 0)
                                            return FALSE;
                                            break;
                                            }
                                            goto LReturnTrue;
                                            
                                            LDispatchRegistered:    // for registered windows messages
                                            ASSERT(message >= 0xC000);
                                            ASSERT(sizeof(mmf) == sizeof(mmf.pfn));
                                            mmf.pfn = lpEntry->pfn;
                                            lResult = (this->*mmf.pfn_l_w_l)(wparam, lparam);
                                            
                                            LReturnTrue:
                                            if (pResult != NULL)
                                            *pResult = lResult;
                                            return TRUE;
                                            }
                                            */
   
   
   /////////////////////////////////////////////////////////////////////////////
   // window command handling
   
   bool window::OnCommand(WPARAM wparam, LPARAM lparam)
   // return TRUE if command invocation was attempted
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      /*   UINT nID = LOWORD(wparam);
       oswindow hWndCtrl = (oswindow)lparam;
       int32_t nCode = HIWORD(wparam);
       
       // default routing for command messages (through closure table)
       
       if (hWndCtrl == NULL)
       {
       // zero IDs for normal commands are not allowed
       if (nID == 0)
       return FALSE;
       
       // make sure command has not become disabled before routing
       CTestCmdUI state;
       state.m_id = nID;
       _001OnCommand(nID, CN_UPDATE_COMMAND_UI, &state, NULL);
       if (!state.m_bEnabled)
       {
       TRACE(::ca2::trace::category_AppMsg, 0, "Warning: not executing disabled command %d\n", nID);
       return TRUE;
       }
       
       // menu or accelerator
       nCode = CN_COMMAND;
       }
       else
       {
       // control notification
       ASSERT(nID == 0 || ::IsWindow(hWndCtrl));
       
       if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
       return TRUE;        // locked out - ignore control notification
       
       // reflect notification to child window control
       if (ReflectLastMsg(hWndCtrl))
       return TRUE;    // eaten by child
       
       // zero IDs for normal commands are not allowed
       if (nID == 0)
       return FALSE;
       }
       
       #ifdef DEBUG
       if (nCode < 0 && nCode != (int32_t)0x8000)
       TRACE(::ca2::trace::category_AppMsg, 0, "Implementation Warning: control notification = $%X.\n",
       nCode);
       #endif
       
       return _001OnCommand(nID, nCode, NULL, NULL);*/
      return FALSE;
   }
   
   bool window::OnNotify(WPARAM, LPARAM lparam, LRESULT* pResult)
   {
      /*    ASSERT(pResult != NULL);
       NMHDR* pNMHDR = (NMHDR*)lparam;
       oswindow hWndCtrl = pNMHDR->hwndFrom;
       
       // get the child ID from the window itself
       //      uint_ptr nID = __get_dialog_control_id(hWndCtrl);
       //      int32_t nCode = pNMHDR->code;
       
       ASSERT(hWndCtrl != NULL);
       ASSERT(::IsWindow(hWndCtrl));
       
       if (gen_ThreadState->m_hLockoutNotifyWindow == get_handle())
       return true;        // locked out - ignore control notification
       
       // reflect notification to child window control
       if (ReflectLastMsg(hWndCtrl, pResult))
       return true;        // eaten by child
       
       //      __NOTIFY notify;
       //    notify.pResult = pResult;
       //  notify.pNMHDR = pNMHDR;
       //xxx   return _001OnCommand((UINT)nID, MAKELONG(nCode, WM_NOTIFY), &notify, NULL);*/
      return false;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // window extensions
   
   sp(::user::frame_window) window::GetParentFrame()
   {
      if (get_handle() == NULL) // no oswindow attached
      {
         return NULL;
      }
      
      ASSERT_VALID(this);
      
      ::user::interaction * pParentWnd = get_parent();  // start with one parent up
      while (pParentWnd != NULL)
      {
         if (pParentWnd->is_frame_window())
         {
            return dynamic_cast < ::user::frame_window * > (pParentWnd);
         }
         pParentWnd = pParentWnd->get_parent();
      }
      return NULL;
   }
   
   /* trans oswindow CLASS_DECL_mac __get_parent_owner(::user::interaction * hWnd)
    {
    // check for permanent-owned window first
    ::window * pWnd = ::mac::window::FromHandlePermanent(hWnd);
    if (pWnd != NULL)
    return MAC_WINDOW(pWnd)->GetOwner();
    
    // otherwise, return parent in the oswindows sense
    return (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) ?
    ::GetParent(hWnd) : ::GetWindow(hWnd, GW_OWNER);
    }*/
   
   
   sp(::user::interaction) window::GetTopLevelParent()
   {
      if (get_handle() == NULL) // no oswindow attached
         return NULL;
      
      ASSERT_VALID(this);
//      
//      ::user::interaction * hWndParent = this;
//      ::user::interaction * hWndT;
      //while ((hWndT = __get_parent_owner(hWndParent)) != NULL)
      // hWndParent = hWndT;
      
//      return hWndParent;
      return m_pui;
      
   }
   
   
   sp(::user::interaction) window::GetTopLevelOwner()
   {
      if (get_handle() == NULL) // no oswindow attached
         return NULL;
      
      ASSERT_VALID(this);
      
      //      oswindow hWndOwner = get_handle();
      //    oswindow hWndT;
      //  while ((hWndT = ::GetWindow(hWndOwner, GW_OWNER)) != NULL)
      //   hWndOwner = hWndT;
      
      //      return ::mac::window::from_handle(hWndOwner);
      return NULL;
   }
   
   sp(::user::interaction) window::GetParentOwner()
   {
      if (get_handle() == NULL) // no oswindow attached
         return NULL;
      
      ASSERT_VALID(this);
      
      /*      oswindow hWndParent = get_handle();
       oswindow hWndT;
       while ((::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) &&
       (hWndT = ::GetParent(hWndParent)) != NULL)
       {
       hWndParent = hWndT;
       }
       
       return ::mac::window::from_handle(hWndParent);*/
      
      return NULL;
   }
   
   bool window::IsTopParentActive()
   {
      ASSERT(get_handle() != NULL);
      ASSERT_VALID(this);
      
      ::user::interaction *pWndTopLevel=EnsureTopLevelParent();
      
      return window::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();
   }
   
   void window::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
//      ::window * pActiveWnd = GetForegroundWindow();
      //      if (pActiveWnd == NULL || !(MAC_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(MAC_WINDOW(pActiveWnd)->get_handle(), get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevelParent()->SetForegroundWindow();
      }
   }
   
   sp(::user::frame_window) window::GetTopLevelFrame()
   {
      if (get_handle() == NULL) // no oswindow attached
         return NULL;
      
      ASSERT_VALID(this);
      
      ::user::frame_window* pFrameWnd = NULL;
      if(m_pui != this)
         pFrameWnd = dynamic_cast < ::user::frame_window * > (m_pui.m_p);
      else
         pFrameWnd = dynamic_cast < ::user::frame_window * > (this);
      if (pFrameWnd == NULL || !pFrameWnd->is_frame_window())
         pFrameWnd = GetParentFrame();
      
      if (pFrameWnd != NULL)
      {
         ::user::frame_window* pTemp;
         while ((pTemp = pFrameWnd->GetParentFrame()) != NULL)
            pFrameWnd = pTemp;
      }
      return pFrameWnd;
   }
   
   /*   ::window * window::GetSafeOwner(::window * pParent, oswindow* pWndTop)
    {
    oswindow hWnd = GetSafeOwner_((oswindow) pParent->get_handle(), pWndTop);
    return ::mac::window::from_handle(hWnd);
    }
    */
   int32_t window::message_box(const char * lpszText, const char * lpszCaption, UINT nType)
   {
      if (lpszCaption == NULL)
         lpszCaption = __get_app_name();
      int32_t nResult = ::MessageBox((oswindow)get_handle(), lpszText, lpszCaption, nType);
      return nResult;
   }
   
   sp(::user::interaction) PASCAL window::GetDescendantWindow(sp(::user::interaction) hWnd, id id)
   {
      single_lock sl(&hWnd->m_pthread->m_mutex, TRUE);
      // GetDlgItem recursive (return first found)
      // breadth-first for 1 level, then depth-first for next level
      
      // use GetDlgItem since it is a fast USER function
//      ::user::interaction * pWndChild;
      /*      if ((pWndChild = hWnd->GetDlgItem(id)) != NULL)
       {
       if (pWndChild->GetTopWindow() != NULL)
       {
       // children with the same ID as their parent have priority
       pWndChild = GetDescendantWindow(pWndChild, id);
       if (pWndChild != NULL)
       return pWndChild;
       }
       if (pWndChild != NULL)
       return pWndChild;
       }*/
      
      for(int32_t i = 0; i < hWnd->m_uiptraChild.get_count(); i++)
      {
         if(hWnd->m_uiptraChild[i].GetDlgCtrlId() == id)
         {
            if(hWnd->m_uiptraChild[i].GetDescendantWindow(id))
               return hWnd->m_uiptraChild[i].GetDescendantWindow(id);
            else
               return &hWnd->m_uiptraChild[i];
         }
      }
//      
//      if(pWndChild == NULL)
//         return NULL;
//      
//      // walk each child
//      for (pWndChild = pWndChild->GetTopWindow(); pWndChild != NULL;
//           pWndChild = pWndChild->GetNextWindow(GW_HWNDNEXT))
//      {
//         pWndChild = GetDescendantWindow(pWndChild, id);
//         if (pWndChild != NULL)
//            return pWndChild;
//      }
      return NULL;    // not found
   }
   
   void PASCAL window::SendMessageToDescendants(void * hWnd, UINT message,
                                                WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {
      // walk through oswindows to avoid creating temporary window objects
      // unless we need to call this function recursively
      /*for (oswindow hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))*/
      {
         // if bOnlyPerm is TRUE, don't send to non-permanent windows
         /*if (bOnlyPerm)
          {
          ::window * pWnd = ::mac::window::FromHandlePermanent(hWndChild);
          if (pWnd != NULL)
          {
          // call window proc directly since it is a C++ window
          __call_window_procedure(dynamic_cast < ::user::interaction * > (pWnd), MAC_WINDOW(pWnd)->get_handle(), message, wparam, lparam);
          }
          }
          else
          {
          try
          {
          // send message with oswindows SendMessage API
          ::SendMessage(hWndChild, message, wparam, lparam);
          }
          catch(...)
          {
          }
          }
          if (bDeep && ::GetTopWindow(hWndChild) != NULL)
          {
          // send to child windows after parent
          try
          {
          SendMessageToDescendants(hWndChild, message, wparam, lparam,
          bDeep, bOnlyPerm);
          }
          catch(...)
          {
          }
          } */
      }
      
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for window functions
   //    only works for derived class (eg: ::view) that override 'GetScrollBarCtrl'
   // if the window doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID
   
//   CScrollBar* window::GetScrollBarCtrl(int32_t) const
  // {
    //  return NULL;        // no special scrollers supported
  // }
   
   int32_t window::SetScrollPos(int32_t nBar, int32_t nPos, bool bRedraw)
   {
      //      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
      return 0;
   }
   
   int32_t window::GetScrollPos(int32_t nBar) const
   {
      //return ::GetScrollPos(get_handle(), nBar);
      return 0;
   }
   
   void window::SetScrollRange(int32_t nBar, int32_t nMinPos, int32_t nMaxPos, bool bRedraw)
   {
      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
   }
   
   void window::GetScrollRange(int32_t nBar, LPINT lpMinPos, LPINT lpMaxPos) const
   {
      //::GetScrollRange(get_handle(), nBar, lpMinPos, lpMaxPos);
   }
   
   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void window::EnableScrollBarCtrl(int32_t nBar, bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar, bEnable);
   }
   
   /*
    bool window::SetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, bool bRedraw)
    {
    ASSERT(lpScrollInfo != NULL);
    
    oswindow hWnd = get_handle();
    lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
    ::SetScrollInfo(hWnd, nBar, lpScrollInfo, bRedraw);
    return true;
    }
    
    bool window::GetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
    {
    UNREFERENCED_PARAMETER(nMask);
    ASSERT(lpScrollInfo != NULL);
    
    oswindow hWnd = get_handle();
    return ::GetScrollInfo(hWnd, nBar, lpScrollInfo) != FALSE;
    }
    */
   int32_t window::GetScrollLimit(int32_t nBar)
   {
      int32_t nMin, nMax;
      GetScrollRange(nBar, &nMin, &nMax);
      /*      SCROLLINFO info;
       if (GetScrollInfo(nBar, &info, SIF_PAGE))
       {
       nMax -= __max(info.nPage-1,0);
       }*/
      return nMax;
   }
   
   void window::ScrollWindow(int32_t xAmount, int32_t yAmount,
                             LPCRECT lpRect, LPCRECT lpClipRect)
   {
      /*      ASSERT(::IsWindow(get_handle()));
       
       if (IsWindowVisible() || lpRect != NULL || lpClipRect != NULL)
       {
       // When visible, let oswindows do the scrolling
       ::ScrollWindow(get_handle(), xAmount, yAmount, lpRect, lpClipRect);
       }
       else
       {
       // oswindows does not perform any scrolling if the window is
       // not visible.  This leaves child windows unscrolled.
       // To account for this oversight, the child windows are moved
       // directly instead.
       oswindow hWndChild = ::GetWindow(get_handle(), GW_CHILD);
       if (hWndChild != NULL)
       {
       for (; hWndChild != NULL;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
       {
       rect rect;
       ::GetWindowRect(hWndChild, &rect);
       ScreenToClient(&rect);
       ::SetWindowPos(hWndChild, NULL,
       rect.left+xAmount, rect.top+yAmount, 0, 0,
       SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
       }
       }
       }
       */
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // minimal layout support
   
   /*
    void window::RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
    UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
    {
    ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
    (nFlags & ~reposNoPosLeftOver) == reposExtra);
    
    // walk kids in order, control bars get the resize notification
    //   which allow them to shrink the client area
    // remaining size goes to the 'nIDLeftOver' pane
    // NOTE: nIDFirst->nIDLast are usually 0->0xffff
    
    __SIZEPARENTPARAMS layout;
    ::user::interaction * hWndLeftOver = NULL;
    
    layout.bStretch = bStretch;
    layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
    if (lpRectClient != NULL)
    layout.rect = *lpRectClient;    // starting rect comes from parameter
    else
    {
    if(m_pui != this)
    m_pui->GetClientRect(&layout.rect);    // starting rect comes from client rect
    else
    GetClientRect(&layout.rect);    // starting rect comes from client rect
    }
    
    if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
    layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
    else
    layout.hDWP = NULL; // not actually doing layout
    
    if(m_pui != this && m_pui != NULL)
    {
    for (::user::interaction * hWndChild = m_pui->GetTopWindow(); hWndChild != NULL;
    hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
    {
    string strIdc = hWndChild->GetDlgCtrlId();
    ::user::interaction * pWnd = hWndChild;
    if (strIdc == pszIdLeftOver)
    hWndLeftOver = hWndChild;
    else if (::str::begins(strIdc, pszPrefix) && pWnd != NULL)
    hWndChild->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
    }
    for (int32_t i = 0; i < m_pui->m_uiptra.get_count();   i++)
    {
    ::user::interaction * hWndChild = m_pui->m_uiptra[i];
    string strIdc = hWndChild->GetDlgCtrlId();
    ::user::interaction * pWnd = hWndChild;
    if (strIdc == pszIdLeftOver)
    hWndLeftOver = hWndChild;
    else if (::str::begins(strIdc, pszPrefix) && pWnd != NULL)
    hWndChild->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
    }
    }
    else
    {
    for (::user::interaction * hWndChild = GetTopWindow(); hWndChild != NULL;
    hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
    {
    string strIdc = hWndChild->GetDlgCtrlId();
    ::user::interaction * pWnd = hWndChild;
    if (strIdc == pszIdLeftOver)
    hWndLeftOver = hWndChild;
    else if (::str::begins(strIdc, pszPrefix) && pWnd != NULL)
    hWndChild->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
    }
    for (int32_t i = 0; i < m_uiptra.get_count();   i++)
    {
    ::user::interaction * hWndChild = m_uiptra[i];
    string strIdc = hWndChild->GetDlgCtrlId();
    ::user::interaction * pWnd = hWndChild;
    if (strIdc == pszIdLeftOver)
    hWndLeftOver = hWndChild;
    else if (::str::begins(strIdc, pszPrefix) && pWnd != NULL)
    hWndChild->SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
    }
    }
    
    // if just getting the available rectangle, return it now...
    if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
    {
    ASSERT(lpRectParam != NULL);
    if (bStretch)
    ::copy(lpRectParam, &layout.rect);
    else
    {
    lpRectParam->left = lpRectParam->top = 0;
    lpRectParam->right = layout.sizeTotal.cx;
    lpRectParam->bottom = layout.sizeTotal.cy;
    }
    return;
    }
    
    // the rest is the client size of the left-over pane
    if (pszIdLeftOver != NULL && hWndLeftOver != NULL)
    {
    ::user::interaction * pLeftOver = hWndLeftOver;
    // allow extra space as specified by lpRectBorder
    if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
    {
    ASSERT(lpRectParam != NULL);
    layout.rect.left += lpRectParam->left;
    layout.rect.top += lpRectParam->top;
    layout.rect.right -= lpRectParam->right;
    layout.rect.bottom -= lpRectParam->bottom;
    }
    // reposition the window
    if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
    {
    pLeftOver->CalcWindowRect(&layout.rect);
    __reposition_window(&layout, pLeftOver, &layout.rect);
    }
    }
    
    // move and resize all the windows at once!
    if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
    TRACE(::ca2::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");
    }
    
    */
   
   void window::RepositionBars(UINT nIDFirst, UINT nIDLast, id nIdLeftOver,
                               UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch)
   {
      UNREFERENCED_PARAMETER(nIDFirst);
      UNREFERENCED_PARAMETER(nIDLast);
      
      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
             (nFlags & ~reposNoPosLeftOver) == reposExtra);
      
      // walk kids in order, control bars get the resize notification
      //   which allow them to shrink the client area
      // remaining size goes to the 'nIDLeftOver' pane
      // NOTE: nIDFirst->nIDLast are usually 0->0xffff
      
      __SIZEPARENTPARAMS layout;
      ::user::interaction * hWndLeftOver = NULL;
      
      layout.bStretch = bStretch;
      layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
      if (lpRectClient != NULL)
         layout.rect = *lpRectClient;    // starting rect comes from parameter
      else
      {
         if(m_pui != this)
            m_pui->GetClientRect(&layout.rect);    // starting rect comes from client rect
         else
            GetClientRect(&layout.rect);    // starting rect comes from client rect
      }
      
//      if ((nFlags & ~reposNoPosLeftOver) != reposQuery)
//         layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
//      else
         layout.hDWP = NULL; // not actually doing layout
       
      if(m_pui != this && m_pui != NULL)
      {
         
         for(::user::interaction * hWndChild = m_pui->GetTopWindow(); hWndChild != NULL; hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
         {
            
            id id = hWndChild->GetDlgCtrlId();
       
            ::user::interaction * pWnd = hWndChild;
            
            if (id == nIdLeftOver)
               hWndLeftOver = hWndChild;
            else if (pWnd != NULL)
               hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
         }
         
         for(::user::interaction * hWndChild = m_pui->get_top_child(); hWndChild != NULL; hWndChild = hWndChild->under_sibling())
         {
            
            id id = hWndChild->GetDlgCtrlId();
       
            ::user::interaction * pWnd = hWndChild;

            if (id == nIdLeftOver)
               hWndLeftOver = hWndChild;
            else if (pWnd != NULL)
               hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
         }
         
       }
       else
       {
          
          for(::user::interaction * hWndChild = GetTopWindow(); hWndChild != NULL; hWndChild = hWndChild->GetNextWindow(GW_HWNDNEXT))
          {
             
             id id = hWndChild->GetDlgCtrlId();
       
             ::user::interaction * pWnd = hWndChild;
       
             if (id == nIdLeftOver)
               hWndLeftOver = hWndChild;
             else if (pWnd != NULL)
                hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
             
          }
          
          for(::user::interaction * hWndChild = m_pui->get_top_child(); hWndChild != NULL; hWndChild = hWndChild->under_sibling())
          {
             
             id id = hWndChild->GetDlgCtrlId();
       
             ::user::interaction * pWnd = hWndChild;
       
             if(id == nIdLeftOver)
                hWndLeftOver = hWndChild;
             else if (pWnd != NULL)
                hWndChild->send_message(WM_SIZEPARENT, 0, (LPARAM)&layout);
             
          }
          
       }
       
       // if just getting the available rectangle, return it now...
       if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
       {
          
          ASSERT(lpRectParam != NULL);
          
          if(bStretch)
             ::CopyRect(lpRectParam, &layout.rect);
          else
          {
            lpRectParam->left = lpRectParam->top = 0;
             lpRectParam->right = layout.sizeTotal.cx;
             lpRectParam->bottom = layout.sizeTotal.cy;
          }
          return;
       }
       
       // the rest is the client size of the left-over pane
       if(!nIdLeftOver.is_null() && hWndLeftOver != NULL)
       {
       
          ::user::interaction * pLeftOver = hWndLeftOver;
          
          // allow extra space as specified by lpRectBorder
          
          if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
          {
             ASSERT(lpRectParam != NULL);
             layout.rect.left += lpRectParam->left;
             layout.rect.top += lpRectParam->top;
             layout.rect.right -= lpRectParam->right;
             layout.rect.bottom -= lpRectParam->bottom;
          }
       
          // reposition the window
          if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
          {
             
             pLeftOver->CalcWindowRect(&layout.rect);
             __reposition_window(&layout, pLeftOver, &layout.rect);
          }
       }
       
       // move and resize all the windows at once!
//       if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
  //     TRACE(::ca2::trace::category_AppMsg, 0, "Warning: DeferWindowPos failed - low system resources.\n");*/
   }
   
   
   
   void window::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {
      /*DWORD dwExStyle = GetExStyle();
       if (nAdjustType == 0)
       dwExStyle &= ~WS_EX_CLIENTEDGE;
       ::AdjustWindowRectEx(lpClientRect, GetStyle(), FALSE, dwExStyle);*/
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing
   
   bool window::HandleFloatingSysCommand(UINT nID, LPARAM lparam)
   {
      /*      ::user::interaction* pParent = GetTopLevelParent();
       switch (nID & 0xfff0)
       {
       case SC_PREVWINDOW:
       case SC_NEXTWINDOW:
       if (LOWORD(lparam) == VK_F6 && pParent != NULL)
       {
       pParent->SetFocus();
       return true;
       }
       break;
       
       case SC_CLOSE:
       case SC_KEYMENU:
       // Check lparam.  If it is 0L, then the ::fontopus::user may have done
       // an Alt+Tab, so just ignore it.  This breaks the ability to
       // just press the Alt-key and have the first menu selected,
       // but this is minor compared to what happens in the Alt+Tab
       // case.
       if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
       {
       if (pParent != NULL)
       {
       // Sending the above WM_SYSCOMMAND may destroy the cast,
       // so we have to be careful about restoring activation
       // and focus after sending it.
       oswindow hWndSave = get_handle();
       oswindow hWndFocus = ::GetFocus();
       pParent->SetActiveWindow();
       pParent->send_message(WM_SYSCOMMAND, nID, lparam);
       
       // be very careful here...
       if (::IsWindow(hWndSave))
       ::SetActiveWindow(hWndSave);
       if (::IsWindow(hWndFocus))
       ::SetFocus(hWndFocus);
       }
       }
       return true;
       }
       return false;*/
      return false;
   }
   
   void window::WalkPreTranslateTree(sp(::user::interaction) puiStop, signal_details * pobj)
   {
      ASSERT(puiStop == NULL || puiStop->IsWindow());
      ASSERT(pobj != NULL);
      
      SCAST_PTR(::message::base, pbase, pobj);
      // walk from the target window up to the hWndStop window checking
      //  if any window wants to translate this message
      
      for (::user::interaction * pui = pbase->m_pwnd; pui != NULL; pui->get_parent())
      {
         
         pui->pre_translate_message(pobj);
         
         if(pobj->m_bRet)
            return; // trapped by target window (eg: accelerators)
         
         // got to hWndStop window without interest
         if(pui == puiStop)
            break;
         
      }
      // no special processing
   }
   
   bool window::SendChildNotifyLastMsg(LRESULT* pResult)
   {
      ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
      return OnChildNotify(pThreadState->m_lastSentMsg.message, pThreadState->m_lastSentMsg.wParam, pThreadState->m_lastSentMsg.lParam, pResult);
   }
   
   bool PASCAL window::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
   {
      // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
      /*      single_lock sl(afxMutexHwnd(), TRUE);
       hwnd_map * pMap = afxMapHWND();
       if (pMap == NULL)
       return FALSE;
       
       // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
       ::window * pWnd = dynamic_cast < ::window * > (pMap->lookup_permanent(hWndChild)); */
      ::window * pWnd = dynamic_cast < ::window * > (FromHandlePermanent(hWndChild));
      ASSERT(pWnd == NULL || MAC_WINDOW(pWnd)->get_handle() == hWndChild);
      if (pWnd == NULL)
      {
         return FALSE;
      }
      
      // only OLE controls and permanent windows will get reflected msgs
      ASSERT(pWnd != NULL);
      return MAC_WINDOW(pWnd)->SendChildNotifyLastMsg(pResult);
   }
   
   bool window::OnChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
   {
      
      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
   }
   
   bool window::ReflectChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(wparam);
      // Note: reflected messages are send directly to window::OnWndMsg
      //  and window::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)
      
      switch (uMsg)
      {
            // normal messages (just wparam, lparam through OnWndMsg)
         case WM_HSCROLL:
         case WM_VSCROLL:
         case WM_PARENTNOTIFY:
         case WM_DRAWITEM:
         case WM_MEASUREITEM:
         case WM_DELETEITEM:
         case WM_VKEYTOITEM:
         case WM_CHARTOITEM:
         case WM_COMPAREITEM:
            // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
            //return window::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
            return FALSE;
            
            // special case for WM_COMMAND
         case WM_COMMAND:
         {
            // reflect the message through the message ::collection::map as OCM_COMMAND
            /* xxx         int32_t nCode = HIWORD(wparam);
             if (window::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), NULL, NULL))
             {
             if (pResult != NULL)
             *pResult = 1;
             return TRUE;
             } */
         }
            break;
            
            // special case for WM_NOTIFY
            /*      case WM_NOTIFY:
             {
             // reflect the message through the message ::collection::map as OCM_NOTIFY
             NMHDR* pNMHDR = (NMHDR*)lparam;
             //            int32_t nCode = pNMHDR->code;
             //            __NOTIFY notify;
             //          notify.pResult = pResult;
             //        notify.pNMHDR = pNMHDR;
             // xxxx         return window::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, NULL);
             }
             
             // other special cases (WM_CTLCOLOR family)*/
         default:
            if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
            {
               // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
               /*__CTLCOLOR ctl;
                ctl.hDC = (HDC)wparam;
                ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
                //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
                ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);
                
                // reflect the message through the message ::collection::map as OCM_CTLCOLOR
                bool bResult = window::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
                if ((HBRUSH)*pResult == NULL)
                bResult = FALSE;
                return bResult;*/
               return false;
            }
            break;
      }
      
      return false;   // let the parent handle it
   }
   
   void window::OnParentNotify(UINT message, LPARAM lparam)
   {
      if ((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
      {
         if (ReflectLastMsg((oswindow)lparam))
            return;     // eat it
      }
      // not handled - do default
      Default();
   }
   
   void window::OnSetFocus(::window *)
   {
      bool bHandled;
      
      bHandled = FALSE;
      if( !bHandled )
      {
         Default();
      }
   }
   
   LRESULT window::OnActivateTopLevel(WPARAM wparam, LPARAM)
   {
      if (LOWORD(wparam) == WA_INACTIVE)
      {
         //         __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
      }
      
      return 0;
   }
   
   void window::OnSysColorChange()
   {
      throw not_implemented(get_app());
      
      /*      application* pApp = &System;
       if (pApp != NULL && pApp->GetMainWnd() == this)
       {
       // recolor global brushes used by control bars
       afxData.UpdateSysColors();
       }
       
       // forward this message to all other child windows
       if (!(GetStyle() & WS_CHILD))
       SendMessageToDescendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);
       
       Default();*/
   }
   
   bool gen_GotScrollLines;
   
   void window::OnSettingChange(UINT uFlags, const char * lpszSection)
   {
      //      UNUSED_ALWAYS(uFlags);
      //    UNUSED_ALWAYS(lpszSection);
      
      // force refresh of settings that we cache
      gen_GotScrollLines = FALSE;
      
      
      window::OnDisplayChange(0, 0);    // to update system metrics, etc.
   }
   
   /*   void window::OnDevModeChange(__in LPTSTR lpDeviceName)
    {
    UNREFERENCED_PARAMETER(lpDeviceName);
    throw not_implemented(get_app());
    application* pApp = &System;
    if (pApp != NULL && pApp->GetMainWnd() == this)
    pApp->DevModeChange(lpDeviceName);
    
    // forward this message to all other child windows
    if (!(GetStyle() & WS_CHILD))
    {
    const MESSAGE* pMsg = GetCurrentMessage();
    SendMessageToDescendants(pMsg->message, pMsg->wparam, pMsg->lparam,
    TRUE, TRUE);
    }*/
   //}
   
   
   //
   //   bool window::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      if (!(GetStyle() & WS_CHILD))
   //      {
   //         ::user::interaction* pMainWnd = System.GetMainWnd();
   //         if (pMainWnd != NULL &&
   //            GetKeyState(VK_SHIFT) >= 0 &&
   //            GetKeyState(VK_CONTROL) >= 0 &&
   //            GetKeyState(VK_MENU) >= 0)
   //         {
   //            //            pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
   //            return TRUE;
   //         }
   //      }
   //      return Default() != 0;
   //   }
   //
   LRESULT window::OnDisplayChange(WPARAM, LPARAM)
   {
      // update metrics if this window is the main window
      if (System.GetMainWnd() == this)
      {
         // update any system metrics cache
         //         afxData.UpdateSysMetrics();
      }
      
      // forward this message to all other child windows
      if (!(GetStyle() & WS_CHILD))
      {
         const MESSAGE* pMsg = GetCurrentMessage();
         SendMessageToDescendants(pMsg->message, pMsg->wParam, pMsg->lParam, TRUE, TRUE);
      }
      
      return Default();
   }
   
   LRESULT window::OnDragList(WPARAM, LPARAM lparam)
   {
      
      throw not_implemented(get_app());
      //
      //      LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lparam;
      //      ASSERT(lpInfo != NULL);
      //
      //      LRESULT lResult;
      //      if (ReflectLastMsg(lpInfo->hWnd, &lResult))
      //         return (int32_t)lResult;    // eat it
      //
      //      // not handled - do default
      //      return (int32_t)Default();
   }
   
   
   void window::_001OnCreate(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
      Default();
      
//      if(!System.get_twf()->m_bProDevianMode)
      {
         SetTimer(2049, 184, NULL);
      }
      
   }
   

   void window::_001OnTimer(signal_details * pobj)
   {
      
      SCAST_PTR(::message::timer, ptimer, pobj);
      
      if(ptimer->m_nIDEvent == 2049)
      {

         _001RedrawWindow();
         
      }
      
   }
   
   
   void window::_001RedrawWindow()
   {
      
      RedrawWindow();
      
   }
/*

   
   void window::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
      UNREFERENCED_PARAMETER(pScrollBar);
      Default();
   }
   
   void window::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
   {
      UNREFERENCED_PARAMETER(pScrollBar);
      Default();
   }
   */
   bool CALLBACK window::GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
      phwnda->add(hwnd);
      return TRUE;
   }
   
   void window::get_app_wnda(user::oswindow_array & wnda)
   {
      throw not_implemented(::get_thread_app());
      //      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   }
   
   /*   void window::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
    {
    _001DeferPaintLayeredWindowBackground(pdc);
    }*/
   
   
   class print_window :
   virtual ::object
   {
   public:
      
      
      
      manual_reset_event m_event;
      oswindow m_hwnd;
      HDC m_hdc;
      
      print_window(base_application * papp, oswindow hwnd, HDC hdc, DWORD dwTimeout) :
      element(papp),
      m_event(papp)
      
      {
         m_event.ResetEvent();
         m_hwnd = hwnd;
         m_hdc = hdc;
         __begin_thread(papp, &print_window::s_print_window, (LPVOID) this, ::core::scheduling_priority_normal);
         if(m_event.wait(millis(dwTimeout)).timeout())
         {
            TRACE("print_window::time_out");
         }
      }
      
      
      static UINT c_cdecl s_print_window(LPVOID pvoid)
      {
//         print_window * pprintwindow = (print_window *) pvoid;
//         try
//         {
//            HANDLE hevent = (HANDLE) pprintwindow->m_event.get_handle();
//            throw not_implemented(pprintwindow->get_app());
//            /*            ::PrintWindow(pprintwindow->m_hwnd, pprintwindow->m_hdc, 0);
//             ::SetEvent(hevent);*/
//         }
//         catch(...)
//         {
//         }
         return 0;
      }
   };
   
   void window::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {
      
      rect rectClient;
      
      GetClientRect(rectClient);
      
      
      //pdc->FillSolidRect(rectClient, 0x00000000);
      
      //return;
      rect rectUpdate;
      GetWindowRect(rectUpdate);
      //      SetViewportOrgEx(hdc, 0, 0, NULL);
      rect rectPaint;
      rectPaint = rectUpdate;
      ScreenToClient(rectPaint);
      user::oswindow_array wndaApp;
      
      
//      HRGN rgnWindow;
//      HRGN rgnIntersect;
//      HRGN rgnUpdate = NULL;
      
      throw not_implemented(get_app());
      /*
       rgnWindow = CreateRectRgn(0, 0, 0, 0);
       rgnIntersect = CreateRectRgn(0, 0, 0, 0);
       */
      //      int32_t iCount = wndaApp.get_count();
      
      throw not_implemented(get_app());
      //      try
      //      {
      //
      //         if(GetWindowLong(GWL_EXSTYLE) & WS_EX_LAYERED)
      //         {
      //            rect rect5;
      //            rect rect9;
      //
      //            rgnUpdate = CreateRectRgnIndirect(&rectUpdate);
      //            oswindow hwndOrder = ::GetWindow(get_handle(), GW_HWNDNEXT);
      //            for(;;)
      //            {
      //               //            char szText[1024];
      //               //::GetWindowTextA(hwndOrder, szText, sizeof(szText));
      //               if(hwndOrder == NULL ||
      //                  !::IsWindow(hwndOrder))
      //                  break;
      //               if(!::IsWindowVisible(hwndOrder) ||
      //                  ::IsIconic(hwndOrder) ||
      //                  hwndOrder == get_handle()
      //                  || wndaApp.contains(hwndOrder))
      //               {
      //                  if(hwndOrder == get_handle())
      //                  {
      //                     // add as bookmark - doesn't paint it
      //                     wndaApp.add(hwndOrder);
      //                  }
      //               }
      //               else
      //               {
      //                  rect rectWindow;
      //                  ::GetWindowRect(hwndOrder, rectWindow);
      //                  SetRectRgn(rgnWindow, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom);
      //                  SetRectRgn(rgnIntersect, 0, 0, 0, 0);
      //                  CombineRgn(rgnIntersect, rgnUpdate, rgnWindow, RGN_AND);
      //                  rect rectIntersectBox;
      //                  GetRgnBox(rgnIntersect, rectIntersectBox);
      //                  if(rectIntersectBox.is_empty())
      //                  {
      //                  }
      //                  else
      //                  {
      //                     CombineRgn(rgnUpdate, rgnUpdate, rgnWindow, RGN_DIFF);
      //                     rect rectDiffBox;
      //                     GetRgnBox(rgnUpdate, rectDiffBox);
      //                     wndaApp.add(hwndOrder);
      //                     if(rectDiffBox.is_empty())
      //                     {
      //                        break;
      //                     }
      //                  }
      //               }
      //               hwndOrder = ::GetWindow(hwndOrder, GW_HWNDNEXT);
      //
      //
      //            }
      //            for(index j = wndaApp.get_upper_bound(); j >= 0; j--)
      //            {
      //               oswindow hWnd = wndaApp[j];
      //               if(hWnd == get_handle())
      //                  break;
      //               if(!::IsWindowVisible(hWnd) || ::IsIconic(hWnd))
      //                  continue;
      //               ::GetWindowRect(hWnd, rect5);
      //               rect9.intersect(rect5, rectUpdate);
      //               if(rect9.width() >0 && rect9.height() > 0)
      //               {
      //                  /*::window * pwnd = dynamic_cast < ::window * > (window::FromHandlePermanent(hWnd));
      //                  if(pwnd == NULL)
      //                  {
      //                  for(int32_t l = 0; l < wndpa.get_count(); l++)
      //                  {
      //                  if(wndpa[l]->get_safe_handle() == hWnd)
      //                  {
      //                  pwnd = dynamic_cast < ::window * > (wndpa[l]->m_pimpl);
      //                  break;
      //                  }
      //                  }
      //                  }
      //                  if(pwnd != NULL)
      //                  {
      //                  pwnd->_001Print(pdc);
      //                  }*/
      //                  //if(::GetWindowLong(wndaApp[j], GWL_EXSTYLE) & WS_EX_LAYERED)
      //                  if(true)
      //                  {
      //                     HDC hDCMem = CreateCompatibleDC(NULL);
      //                     HBITMAP hBmp = NULL;
      //                     {
      //                        HDC hDC = ::GetWindowDC(hWnd);
      //                        hBmp = CreateCompatibleBitmap(hDC, rect5.width(), rect5.height());
      //                        ::ReleaseDC(hWnd, hDC);
      //                     }
      //                     HGDIOBJ hOld = SelectObject(hDCMem, hBmp);
      //                     //print_window printwindow(get_app(), hWnd, hDCMem, 284);
      //                     ::PrintWindow(hWnd, hDCMem, 0);
      //                     ::BitBlt(
      //                        hdc ,
      //                        //rect5.left,
      //                        //rect5.top,
      //                        0, 0,
      //                        rect5.width(), rect5.height(),
      //                        hDCMem,
      //                        rectUpdate.left - rect5.left,
      //                        rectUpdate.top - rect5.top,
      //                        SRCCOPY);
      //                     ::SelectObject(hDCMem, hOld);
      //                     ::DeleteObject(hDCMem);
      //                     ::DeleteObject(hBmp);
      //                  }
      //                  else
      //                  {
      //                     SetViewportOrgEx(hdc, 0, 0, NULL);
      //                     HDC hdcWindow = ::GetDCEx(wndaApp[j], NULL, DCX_WINDOW);
      //                     if(hdcWindow == NULL)
      //                        hdcWindow = ::GetDCEx(wndaApp[j], NULL, DCX_WINDOW | DCX_CACHE);
      //                     if(hdcWindow != NULL)
      //                     {
      //                        ::BitBlt(
      //                           hdc,
      //                           rect5.left - rectUpdate.left,
      //                           rect5.top - rectUpdate.top,
      //                           rect5.width(), rect5.height(),
      //                           hdcWindow,
      //                           rect5.left - rect5.left,
      //                           rect5.top - rect5.top,
      //                           SRCCOPY);
      //                        ::ReleaseDC(wndaApp[j], hdcWindow);
      //                     }
      //                     else
      //                     {
      //                        TRACE0("WARNING: failed to draw a background. this surface probably will be black.");
      //                     }
      //                  }
      //               }
      //            }
      //         }
      //      }
      //      catch(...)
      //      {
      //
      //      }
      //
      //      ::DeleteObject(rgnWindow);
      //      ::DeleteObject(rgnIntersect);
      //      ::DeleteObject(rgnUpdate);
   }
   
   void window::_001OnProdevianSynch(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      System.get_event(m_pthread->m_pthread)->SetEvent();
      //    System.get_event(System.get_twf())->wait(millis(8400));
   }
   
   void window::_001OnPaint(signal_details * pobj)
   {
      
      //lock lock(m_pui, 1984);
      
      throw not_implemented(get_app());
      
      //      SCAST_PTR(::message::base, pbase, pobj);
      //
      //      PAINTSTRUCT paint;
      //      memset(&paint, 0, sizeof(paint));
      //      HDC hdc = ::BeginPaint(get_handle(), &paint);
      //      ::SelectClipRgn(hdc, NULL);
      //
      //      try
      //      {
      //
      //         ::draw2d::dib_sp dib(get_app());
      //
      //         rect rectWindow;
      //         GetWindowRect(rectWindow);
      //
      //         if(!dib->create(rectWindow.bottom_right()))
      //            return;
      //
      //         ::draw2d::graphics * pdc = dib->get_graphics();
      //
      //         if((dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->get_handle() == NULL
      //            || (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->get_os_data2() == NULL)
      //            return;
      //
      //         rect rectPaint;
      //         rect rectUpdate;
      //         rectPaint = paint.rcPaint;
      //         if(rectPaint.is_null() || (GetExStyle() & WS_EX_LAYERED))
      //         {
      //            rectUpdate = rectWindow;
      //            rectPaint = rectWindow;
      //            ScreenToClient(rectPaint);
      //         }
      //         else
      //         {
      //            rectUpdate = rectPaint;
      //            ClientToScreen(rectUpdate);
      //         }
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         if(m_pui != NULL && m_pui != this)
      //         {
      //            m_pui->_001OnDeferPaintLayeredWindowBackground(pdc);
      //         }
      //         else
      //         {
      //            _001OnDeferPaintLayeredWindowBackground(pdc);
      //         }
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //         _000OnDraw(pdc);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //         //(dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //         BitBlt(hdc, rectPaint.left, rectPaint.top,
      //            rectPaint.width(), rectPaint.height(),
      //            (HDC) pdc->get_handle(), rectUpdate.left, rectUpdate.top,
      //            SRCCOPY);
      //
      //      }
      //      catch(...)
      //      {
      //      }
      //
      //      ::EndPaint(get_handle(), &paint);
      //      pobj->m_bRet = true;
      //      pbase->set_lresult(0);
   }
   
   
   void window::_001OnPrint(signal_details * pobj)
   {
      throw not_implemented(get_app());
      //      SCAST_PTR(::message::base, pbase, pobj);
      //
      //      if(pbase->m_wparam == NULL)
      //         return;
      //
      //      ::draw2d::graphics_sp graphics(get_app());
      //      WIN_DC(graphics.m_p)->Attach((HDC) pbase->m_wparam);
      //      rect rectx;
      //      ::draw2d::bitmap * pbitmap = &graphics->GetCurrentBitmap();
      //      ::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);
      //      //      DWORD dw = ::GetLastError();
      //      class size size = pbitmap->get_size();
      //      rectx.left = 0;
      //      rectx.top = 0;
      //      rectx.right = size.cx;
      //      rectx.bottom = size.cy;
      //      try
      //      {
      //         rect rectWindow;
      //         GetWindowRect(rectWindow);
      //
      //         ::draw2d::dib_sp dib(get_app());
      //         if(!dib->create(rectWindow.bottom_right()))
      //            return;
      //
      //         ::draw2d::graphics * pdc = dib->get_graphics();
      //
      //         if(pdc->get_handle() == NULL)
      //            return;
      //
      //         rect rectPaint;
      //         rect rectUpdate;
      //         rectUpdate = rectWindow;
      //         rectPaint = rectWindow;
      //         rectPaint.offset(-rectPaint.top_left());
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         if(m_pui != NULL && m_pui != this)
      //         {
      //            m_pui->_001OnDeferPaintLayeredWindowBackground(pdc);
      //         }
      //         else
      //         {
      //            _001OnDeferPaintLayeredWindowBackground(pdc);
      //         }
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //         _000OnDraw(pdc);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //         //(dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pdc))->SetViewportOrg(point(0, 0));
      //
      //         graphics->SelectClipRgn( NULL);
      //         graphics->BitBlt(rectPaint.left, rectPaint.top,
      //            rectPaint.width(), rectPaint.height(),
      //            pdc, rectUpdate.left, rectUpdate.top,
      //            SRCCOPY);
      //
      //         graphics->TextOut(0, 0, "Te Amo TBS", 11);
      //      }
      //      catch(...)
      //      {
      //      }
      //      graphics->FillSolidRect(rectx, RGB(255, 255, 255));
      //      WIN_DC(graphics.m_p)->Detach();
      //      pobj->m_bRet = true;
      //      pbase->set_lresult(0);
   }
   
   
   void window::OnEnterIdle(UINT /*nWhy*/, ::window * /*pWho*/)
   {
      // In some OLE inplace active scenarios, OLE will post a
      // message instead of sending it.  This causes so many WM_ENTERIDLE
      // messages to be sent that tasks running in the background stop
      // running.  By dispatching the pending WM_ENTERIDLE messages
      // when the first one is received, we trick oswindows into thinking
      // that only one was really sent and dispatched.
      {
//         MESSAGE msg;
         throw not_implemented(get_app());
         //while (PeekMessage(&msg, NULL, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
         //while (PeekMessage(&msg, ::caNULL, WM_ENTERIDLE, WM_ENTERIDLE, TRUE))
         // DispatchMessage(&msg);
      }
      
      Default();
   }
   
   HBRUSH window::OnCtlColor(::draw2d::graphics *, ::window * pWnd, UINT)
   {
      ASSERT(pWnd != NULL && MAC_WINDOW(pWnd)->get_handle() != NULL);
      LRESULT lResult;
      if (MAC_WINDOW(pWnd)->SendChildNotifyLastMsg(&lResult))
         return (HBRUSH)lResult;     // eat it
      return (HBRUSH)Default();
   }
   
   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any window containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   bool PASCAL window::GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
                                    HBRUSH hbrGray, COLORREF clrText)
   {
      throw not_implemented(::get_thread_app());
      //      if (hDC == NULL)
      //      {
      //         // sometimes Win32 passes a NULL hDC in the WM_CTLCOLOR message.
      //         //         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: hDC is NULL in window::GrayCtlColor; WM_CTLCOLOR not processed.\n");
      //         return FALSE;
      //      }
      //
      //      if (hbrGray == NULL ||
      //         nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
      //         nCtlColor == CTLCOLOR_SCROLLBAR)
      //      {
      //         return FALSE;
      //      }
      //
      //      if (nCtlColor == CTLCOLOR_LISTBOX)
      //      {
      //         // only handle requests to draw the space between edit and drop button
      //         //  in a drop-down combo (not a drop-down list)
      //         if (!__is_combo_box_control(hWnd, (UINT)CBS_DROPDOWN))
      //            return FALSE;
      //      }
      //
      //      // set background color and return handle to brush
      //      LOGBRUSH logbrush;
      //      VERIFY(::GetObject(hbrGray, sizeof(LOGBRUSH), (LPVOID)&logbrush));
      //      ::SetBkColor(hDC, logbrush.lbColor);
      //      if (clrText == (COLORREF)-1)
      //         clrText = ::GetSysColor(COLOR_WINDOWTEXT);  // normal text
      //      ::SetTextColor(hDC, clrText);
      //      return TRUE;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support
   
   /*bool window::UpdateData(bool bSaveAndValidate)
    {
    ASSERT(::IsWindow(get_handle())); // calling UpdateData before DoModal?
    
    CDataExchange dx(this, bSaveAndValidate);
    
    // prevent control notifications from being dispatched during UpdateData
    ___THREAD_STATE* pThreadState = __get_thread_state();
    oswindow hWndOldLockout = pThreadState->m_hLockoutNotifyWindow;
    ASSERT(hWndOldLockout != get_handle());   // must not recurse
    pThreadState->m_hLockoutNotifyWindow = get_handle();
    
    bool bOK = FALSE;       // assume failure
    try
    {
    DoDataExchange(&dx);
    bOK = TRUE;         // it worked
    }
    catch(user_exception * pe)
    {
    // validation failed - ::fontopus::user already alerted, fall through
    ASSERT(!bOK);
    // Note: DELETE_EXCEPTION_(e) not required
    }
    catch(::exception::base * pe)
    {
    // validation failed due to OOM or other resource failure
    //e->ReportError(MB_ICONEXCLAMATION, __IDP_INTERNAL_FAILURE);
    pe->ReportError(MB_ICONEXCLAMATION, "falha interna");
    ASSERT(!bOK);
    pe->Delete();
    }
    
    
    pThreadState->m_hLockoutNotifyWindow = hWndOldLockout;
    return bOK;
    }*/
   
   
   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child window)
   
   void window::CenterWindow(sp(::user::interaction) pAlternateOwner)
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //
      //      // determine owner window to center against
      //      DWORD dwStyle = GetStyle();
      //      ::user::interaction * hWndCenter = pAlternateOwner;
      //      if (pAlternateOwner == NULL)
      //      {
      //         if (dwStyle & WS_CHILD)
      //            hWndCenter = GetParent();
      //         else
      //            hWndCenter = GetWindow(GW_OWNER);
      //         if (hWndCenter != NULL)
      //         {
      //            // let parent determine alternate center window
      //            ::user::interaction * hWndTemp =
      //               (::user::interaction * )hWndCenter->send_message(WM_QUERYCENTERWND, 0, 0);
      //            if (hWndTemp != NULL)
      //               hWndCenter = hWndTemp;
      //         }
      //      }
      //
      //      // get coordinates of the window relative to its parent
      //      rect rcDlg;
      //      GetWindowRect(&rcDlg);
      //      rect rcArea;
      //      rect rcCenter;
      //      ::user::interaction * hWndParent;
      //      if (!(dwStyle & WS_CHILD))
      //      {
      //         // don't center against invisible or minimized windows
      //         if (hWndCenter != NULL)
      //         {
      //            DWORD dwAlternateStyle = hWndCenter->GetWindowLong(GWL_STYLE);
      //            if (!(dwAlternateStyle & WS_VISIBLE) || (dwAlternateStyle & WS_MINIMIZE))
      //               hWndCenter = NULL;
      //         }
      //
      //         MONITORINFO mi;
      //         mi.cbSize = sizeof(mi);
      //
      //         // center within appropriate monitor coordinates
      //         if (hWndCenter == NULL)
      //         {
      //            oswindow hwDefault = System.GetMainWnd()->get_handle();
      //
      //            GetMonitorInfo(
      //               MonitorFromWindow(hwDefault, MONITOR_DEFAULTTOPRIMARY), &mi);
      //            rcCenter = mi.rcWork;
      //            rcArea = mi.rcWork;
      //         }
      //         else
      //         {
      //            hWndCenter->GetWindowRect(&rcCenter);
      //            GetMonitorInfo(
      //               MonitorFromWindow(hWndCenter->get_handle(), MONITOR_DEFAULTTONEAREST), &mi);
      //            rcArea = mi.rcWork;
      //         }
      //      }
      //      else
      //      {
      //         // center within parent client coordinates
      //         hWndParent = GetParent();
      //         ASSERT(hWndParent->IsWindow());
      //
      //         hWndParent->GetClientRect(&rcArea);
      //         ASSERT(hWndCenter->IsWindow());
      //         hWndCenter->GetClientRect(&rcCenter);
      //         ::MapWindowPoints(hWndCenter->get_handle(), hWndParent->get_handle(), (POINT*)&rcCenter, 2);
      //      }
      //
      //      // find dialog's upper left based on rcCenter
      //      int32_t xLeft = (rcCenter.left + rcCenter.right) / 2 - rcDlg.width() / 2;
      //      int32_t yTop = (rcCenter.top + rcCenter.bottom) / 2 - rcDlg.height() / 2;
      //
      //      // if the dialog is outside the screen, move it inside
      //      if (xLeft < rcArea.left)
      //         xLeft = rcArea.left;
      //      else if (xLeft + rcDlg.width() > rcArea.right)
      //         xLeft = rcArea.right - rcDlg.width();
      //
      //      if (yTop < rcArea.top)
      //         yTop = rcArea.top;
      //      else if (yTop + rcDlg.height() > rcArea.bottom)
      //         yTop = rcArea.bottom - rcDlg.height();
      //
      //      // ::collection::map screen coordinates to child coordinates
      //      SetWindowPos(NULL, xLeft, yTop, -1, -1,
      //         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }
   
   bool window::CheckAutoCenter()
   {
      return TRUE;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support
   
   bool window::ExecuteDlgInit(const char * lpszResourceName)
   {
      // find resource handle
      LPVOID lpResource = NULL;
      HGLOBAL hResource = NULL;
      if (lpszResourceName != NULL)
      {
         //         HINSTANCE hInst = ::ca2::FindResourceHandle(lpszResourceName, RT_DLGINIT);
         //       HRSRC hDlgInit = ::FindResource(hInst, lpszResourceName, RT_DLGINIT);
         /*     if (hDlgInit != NULL)
          {
          // load it
          hResource = LoadResource(hInst, hDlgInit);
          if (hResource == NULL)
          return FALSE;
          // lock it
          lpResource = LockResource(hResource);
          ASSERT(lpResource != NULL);
          }*/
      }
      
      // execute it
      bool bResult = ExecuteDlgInit(lpResource);
      
      // cleanup
      if (lpResource != NULL && hResource != NULL)
      {
         throw not_implemented(get_app());
         //         UnlockResource(hResource);
         //         FreeResource(hResource);
      }
      return bResult;
   }
   
   bool window::ExecuteDlgInit(LPVOID lpResource)
   {
      throw not_implemented(get_app());
      //      bool bSuccess = TRUE;
      //      if (lpResource != NULL)
      //      {
      //         UNALIGNED WORD* lpnRes = (WORD*)lpResource;
      //         while (bSuccess && *lpnRes != 0)
      //         {
      //            WORD nIDC = *lpnRes++;
      //            WORD nMsg = *lpnRes++;
      //            DWORD dwLen = *((UNALIGNED DWORD*&)lpnRes)++;
      //
      //            // In Win32 the WM_ messages have changed.  They have
      //            // to be translated from the 32-bit values to 16-bit
      //            // values here.
      //
      //#define WIN16_LB_ADDSTRING  0x0401
      //#define WIN16_CB_ADDSTRING  0x0403
      //#define __CB_ADDSTRING   0x1234
      //
      //            // unfortunately, WIN16_CB_ADDSTRING == CBEM_INSERTITEM
      //            if (nMsg == __CB_ADDSTRING)
      //               nMsg = CBEM_INSERTITEM;
      //            else if (nMsg == WIN16_LB_ADDSTRING)
      //               nMsg = LB_ADDSTRING;
      //            else if (nMsg == WIN16_CB_ADDSTRING)
      //               nMsg = CB_ADDSTRING;
      //
      //            // check for invalid/unknown message types
      //            ASSERT(nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING ||
      //               nMsg == CBEM_INSERTITEM);
      //
      //#ifdef DEBUG
      //            // For AddStrings, the count must exactly delimit the
      //            // string, including the NULL termination.  This check
      //            // will not catch all mal-formed ADDSTRINGs, but will
      //            // catch some.
      //            if (nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING || nMsg == CBEM_INSERTITEM)
      //               ASSERT(*((LPBYTE)lpnRes + (UINT)dwLen - 1) == 0);
      //#endif
      //
      //            if (nMsg == CBEM_INSERTITEM)
      //            {
      //               COMBOBOXEXITEM item = {0};
      //               item.mask = CBEIF_TEXT;
      //               item.iItem = -1;
      //               string strText(reinterpret_cast<LPTSTR>(lpnRes));
      //               item.pszText = const_cast<LPTSTR>(strText.GetString());
      //               if (::SendDlgItemMessage(get_handle(), nIDC, nMsg, 0, (LPARAM) &item) == -1)
      //                  bSuccess = FALSE;
      //            }
      //            {
      //               // List/Combobox returns -1 for error
      //               if (::SendDlgItemMessageA(get_handle(), nIDC, nMsg, 0, (LPARAM) lpnRes) == -1)
      //                  bSuccess = FALSE;
      //            }
      //
      //
      //            // skip past data
      //            lpnRes = (WORD*)((LPBYTE)lpnRes + (UINT)dwLen);
      //         }
      //      }
      //
      //      // send update message to all controls after all other siblings loaded
      //      if (bSuccess)
      //         SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, FALSE, FALSE);
      //
      //      return bSuccess;
   }
   
   void window::UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      cmd_ui state(get_app());
      window wndTemp;       // very temporary window just for CmdUI update
      
      // walk all the kids - assume the IDs are for buttons
      /* xxx   for (oswindow hWndChild = ::GetTopWindow(get_handle()); hWndChild != NULL;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
       {
       // send to buttons
       wndTemp.set_handle(hWndChild); // quick and dirty attach
       state.m_nID = __get_dialog_control_id(hWndChild);
       state.m_pOther = &wndTemp;
       
       // check for reflect handlers in the child window
       ::window * pWnd = ::mac::window::FromHandlePermanent(hWndChild);
       if (pWnd != NULL)
       {
       // call it directly to disable any routing
       if (MAC_WINDOW(pWnd)->window::_001OnCommand(0, MAKELONG(0xffff,
       WM_COMMAND+WM_REFLECT_BASE), &state, NULL))
       continue;
       }
       
       // check for handlers in the parent window
       if (window::_001OnCommand((UINT)state.m_nID, CN_UPDATE_COMMAND_UI, &state, NULL))
       continue;
       
       // determine whether to disable when no handler exists
       bool bDisableTemp = bDisableIfNoHndler;
       if (bDisableTemp)
       {
       if ((wndTemp.SendMessage(WM_GETDLGCODE) & DLGC_BUTTON) == 0)
       {
       // non-button controls don't get automagically disabled
       bDisableTemp = FALSE;
       }
       else
       {
       // only certain button controls get automagically disabled
       UINT nStyle = (UINT)(wndTemp.GetStyle() & 0x0F);
       if (nStyle == (UINT)BS_AUTOCHECKBOX ||
       nStyle == (UINT)BS_AUTO3STATE ||
       nStyle == (UINT)BS_GROUPBOX ||
       nStyle == (UINT)BS_AUTORADIOBUTTON)
       {
       bDisableTemp = FALSE;
       }
       }
       }
       // check for handlers in the target (owner)
       state.DoUpdate(pTarget, bDisableTemp);
       }
       wndTemp.set_handle(NULL);      // quick and dirty detach */
   }
   
   
   id window::RunModalLoop(DWORD dwFlags, ::core::live_object * pliveobject)
   {
      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      bool bShowIdle = (dwFlags & MLF_SHOWONIDLE) && !(GetStyle() & WS_VISIBLE);
      oswindow hWndParent = ::GetParent(get_handle());
      m_iModal = m_iModalCount;
      int32_t iLevel = m_iModal;
      oprop(string("RunModalLoop.thread(") + ::str::from(iLevel) + ")") = System.GetThread();
      m_iModalCount++;
      
                  m_iaModalThread.add(::GetCurrentThreadId());
            ::application * pappThis1 = dynamic_cast < ::application * > (m_pthread->m_p.m_p);
            ::application * pappThis2 = dynamic_cast < ::application * > (m_pthread.m_p);
            // acquire and dispatch messages until the modal state is done
            MESSAGE msg;
            for (;;)
            {
               if (!ContinueModal(iLevel))
                  goto ExitModal;
                     // phase1: check to see if we can do idle work
               while (bIdle && !::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
               {
                  if (!ContinueModal(iLevel))
                     goto ExitModal;
                        // show the dialog when the message queue goes idle
                  if (bShowIdle)
                  {
                     ShowWindow(SW_SHOWNORMAL);
                     UpdateWindow();
                     bShowIdle = FALSE;
                  }
                        // call on_idle while in bIdle state
                  if (!(dwFlags & MLF_NOIDLEMSG) && hWndParent != NULL && lIdleCount == 0)
                  {
                     // send WM_ENTERIDLE to the parentpbrush
//                     hWndParent->get_user_interaction()->send_message(WM_ENTERIDLE, MESSAGEF_DIALOGBOX, (LPARAM)get_handle());
                  }
//                  if ((dwFlags & MLF_NOKICKIDLE) ||
  //                   !__call_window_procedure(this, get_handle(), WM_KICKIDLE, MESSAGEF_DIALOGBOX, lIdleCount++))
        //          {
          //           // stop idle processing next time
            //         bIdle = FALSE;
              //    }
                        m_pthread->m_p->m_dwAlive = m_pthread->m_dwAlive = ::get_tick_count();
                  if(pappThis1 != NULL)
                  {
                     pappThis1->m_dwAlive = m_pthread->m_dwAlive;
                  }
                  if(pappThis2 != NULL)
                  {
                     pappThis2->m_dwAlive = m_pthread->m_dwAlive;
                  }
                  if(pliveobject != NULL)
                  {
                     pliveobject->keep_alive();
                  }
                  {
                     m_pui->m_pthread->step_timer();
                  }               }
                           // phase2: pump messages while available
               do
               {
                  if (!ContinueModal(iLevel))
                     goto ExitModal;
                        // pump message, but quit on WM_QUIT
                  if (!m_pthread->pump_message())
                  {
                     __post_quit_message(0);
                     return -1;
                  }
                        // show the window when certain special messages rec'd
                  if (bShowIdle &&
                     (msg.message == 0x118 || msg.message == WM_SYSKEYDOWN))
                  {
                     ShowWindow(SW_SHOWNORMAL);
                     UpdateWindow();
                     bShowIdle = FALSE;
                  }
                        if (!ContinueModal(iLevel))
                     goto ExitModal;
                        // reset "no idle" state after pumping "normal" message
                  if (__is_idle_message(&msg))
                  {
                     bIdle = TRUE;
                     lIdleCount = 0;
                  }
                        m_pthread->m_p->m_dwAlive = m_pthread->m_dwAlive = ::get_tick_count();
                  if(pappThis1 != NULL)
                  {
                     pappThis1->m_dwAlive = m_pthread->m_dwAlive;
                  }
                  if(pappThis2 != NULL)
                  {
                     pappThis2->m_dwAlive = m_pthread->m_dwAlive;
                  }
                  if(pliveobject != NULL)
                  {
                     pliveobject->keep_alive();
                  }
                        /*            if(pliveobject != NULL)
                  {
                  pliveobject->keep();
                  }*/
                     }
               while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) != FALSE);
                           if(m_pui->m_pthread != NULL)
               {
                  m_pui->m_pthread->step_timer();
               }
               if (!ContinueModal(iLevel))
                  goto ExitModal;
                        }
   ExitModal:
      
      m_iaModalThread.remove_first(::GetCurrentThreadId());
      
      m_iModal = m_iModalCount;
      
      return m_nModalResult;
      
   }
   
   bool window::ContinueModal(int32_t iLevel)
   {
      return iLevel < m_iModalCount;
   }
   
   void window::EndModalLoop(id nResult)
   {
      
      ASSERT(::IsWindow(get_handle()));
      
      // this result will be returned from window::RunModalLoop
      m_nModalResult = (int32_t) nResult;
      
      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {
         
         m_iModalCount--;
         
         for(index i = 0; i < m_iaModalThread.get_count(); i++)
         {
         
            ::PostThreadMessage((DWORD) m_iaModalThread[i], WM_NULL, 0, 0);
            
         }
               
         post_message(WM_NULL);
               
         System.GetThread()->post_thread_message(WM_NULL, 0, 0);
               
      }
      
   }
   
   void window::EndAllModalLoops(id nResult)
   {
      ASSERT(::IsWindow(get_handle()));
      
      // this result will be returned from window::RunModalLoop
      m_idModalResult = nResult;
      
      // make sure a message goes through to exit the modal loop
      if(m_iModalCount > 0)
      {
         int32_t iLevel = m_iModalCount - 1;
         m_iModalCount = 0;
         
         
         for(index i = 0; i < m_iaModalThread.get_count(); i++)
         {
            
            ::PostThreadMessage((DWORD) m_iaModalThread[i], WM_NULL, 0, 0);
            
         }
         
         post_message(WM_NULL);
         
         System.GetThread()->post_thread_message(WM_NULL);
         
         for(int32_t i = iLevel; i >= 0; i--)
         {
            ::thread * pthread = oprop(string("RunModalLoop.thread(") + ::str::from(i) + ")").cast < ::thread > ();
            try
            {
               pthread->post_thread_message(WM_NULL);
            }
            catch(...)
            {
            }
         }
      }
   }
   
   
   /////////////////////////////////////////////////////////////////////////////
   // frame_window (here for library granularity)
   
   bool window::IsFrameWnd()
   {
      return FALSE;
   }
   /////////////////////////////////////////////////////////////////////////////
   // Extra window support for dynamic subclassing of controls
   
   bool window::SubclassWindow(oswindow hWnd)
   {
      if (!Attach(hWnd))
         return FALSE;
      
      // allow any other subclassing to occur
      pre_subclass_window();
      
      throw not_implemented(get_app());
      //      m_pfnSuper = (WNDPROC)::GetWindowLongPtr(hWnd, GWLP_WNDPROC);
      
      // now hook into the AFX WndProc
      //      WNDPROC* lplpfn = GetSuperWndProcAddr();
      //      WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC,
      //         (int_ptr)__get_window_procedure());
      //      ASSERT(oldWndProc != __get_window_procedure());
      //
      //      if (*lplpfn == NULL)
      //         *lplpfn = oldWndProc;   // the first control of that type created
      //#ifdef DEBUG
      //      else if (*lplpfn != oldWndProc)
      //      {
      //         TRACE(::ca2::trace::category_AppMsg, 0, "p: Trying to use SubclassWindow with incorrect window\n");
      //         TRACE(::ca2::trace::category_AppMsg, 0, "\tderived class.\n");
      //         TRACE(::ca2::trace::category_AppMsg, 0, "\thWnd = $%08X (nIDC=$%08X) is not a %hs.\n", (UINT)(uint_ptr)hWnd,
      //            __get_dialog_control_id(hWnd), typeid(*this).name());
      //         ASSERT(FALSE);
      //         // undo the subclassing if continuing after assert
      //         ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (int_ptr)oldWndProc);
      //      }
      //#endif
      //      ::message::size size(get_app());
      //      _001OnSize(&size);
      //      return TRUE;
      //   }
      //
      //   bool window::SubclassDlgItem(UINT nID, ::window * pParent)
      //   {
      //      ASSERT(pParent != NULL);
      //      ASSERT(::IsWindow(MAC_WINDOW(pParent)->get_handle()));
      //
      //      // check for normal dialog control first
      //      oswindow hWndControl = ::GetDlgItem(MAC_WINDOW(pParent)->get_handle(), nID);
      //      if (hWndControl != NULL)
      //         return SubclassWindow(hWndControl);
      //
      //
      //      return FALSE;   // control not found
   }
   
   oswindow window::UnsubclassWindow()
   {
      ASSERT(::IsWindow(get_handle()));
      
      throw not_implemented(get_app());
      //      // set WNDPROC back to original value
      //      WNDPROC* lplpfn = GetSuperWndProcAddr();
      //      SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (int_ptr)*lplpfn);
      //      *lplpfn = NULL;
      //
      //      // and Detach the oswindow from the window object
      //      return Detach();
   }
   
   
   /*   view_update_hint::view_update_hint(base_application * papp) :
    element(papp)
    {
    }
    */
   
   
   
   bool window::IsChild(sp(::user::interaction) pWnd)
   {
      ASSERT(::IsWindow(get_handle()));
      if(MAC_WINDOW(pWnd.m_p)->get_handle() == NULL)
      {
         return ::user::interaction::IsChild(pWnd);
      }
      else
      {
//         return ::IsChild(get_handle(), MAC_WINDOW(pWnd)->get_handle()) != FALSE;
         return FALSE;
      }
   }
   
   bool window::IsWindow()
   {
      return ::IsWindow(m_oswindow) != FALSE;
   }
   
   oswindow window::get_handle() const
   {
      
      return m_oswindow;
      
   }
   
   sp(::window) window::get_wnd() const
   {
      
      return (::window *) this;
      
   }
   
   
   bool window::SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags)
   {
      
      /*
         bool b;
         bool * pb = &b;
         if(m_pbaseapp->m_pplaneapp->s_ptwf != NULL)
         pb = &m_pbaseapp->m_pplaneapp->s_ptwf->m_bProDevianMode;
         keeper < bool > keepOnDemandDraw(pb, false, *pb, true);
      */
      
      if(!::IsWindow(get_handle()))
         return false;
      
      /*
         return ::SetWindowPos(get_handle(), pWndInsertAfter->get_handle(),
         x, y, cx, cy, nFlags) != FALSE;
      */

      rect64 rectWindowOld = m_rectParentClient;
      
      if(nFlags & SWP_NOMOVE)
      {
         if(nFlags & SWP_NOSIZE)
         {
         }
         else
         {
            m_rectParentClient.right   = m_rectParentClient.left + cx;
            m_rectParentClient.bottom  = m_rectParentClient.top + cy;
         }
      }
      else
      {
         if(nFlags & SWP_NOSIZE)
         {
            m_rectParentClient.offset(x - m_rectParentClient.left, y - m_rectParentClient.top);
         }
         else
         {
            m_rectParentClient.left    = x;
            m_rectParentClient.top     = y;
            m_rectParentClient.right   = m_rectParentClient.left + cx;
            m_rectParentClient.bottom  = m_rectParentClient.top + cy;
         }
      }
      
      if(m_pui != this && m_pui != NULL)
      {
         
         m_pui->m_rectParentClient = m_rectParentClient;
         
      }
      
      ::SetWindowPos(m_oswindow,
                     0,
                     (int) m_rectParentClient.left,
                     (int) m_rectParentClient.top,
                     (int) m_rectParentClient.width(),
                     (int) m_rectParentClient.height(),
                     0);
      
      if(rectWindowOld.top_left() != m_rectParentClient.top_left())
      {
      
         send_message(WM_MOVE);
      
      }

      if(rectWindowOld.size() != m_rectParentClient.size())
      {
      
         send_message(WM_SIZE);
      
      }
      
      
      if(nFlags & SWP_SHOWWINDOW)
      {
         
         if(!IsWindowVisible())
         {
            
            round_window_show();
            
         }
         
      }
      
      
//      throw not_implemented(get_app());
      
      /*
       if(GetExStyle() & WS_EX_LAYERED)
       {
       if(rectWindowOld.top_left() != m_rectParentClient.top_left())
       {
       send_message(WM_MOVE, 0, 0);
       }
       if(rectWindowOld.size() != m_rectParentClient.size())
       {
       send_message(WM_SIZE, 0, 0);
       }
       
       }
       if(GetExStyle() & WS_EX_LAYERED)
       {
       nFlags |= SWP_NOCOPYBITS;
       nFlags |= SWP_NOREDRAW;
       nFlags |= SWP_NOMOVE;
       nFlags |= SWP_NOSIZE;
       //nFlags |= SWP_NOZORDER;
       //nFlags |= SWP_FRAMECHANGED;
       if(nFlags & SWP_SHOWWINDOW)
       {
       ::SetWindowPos(get_handle(), (oswindow) z, x, y, cx, cy, nFlags);
       ShowWindow(SW_SHOW);
       }
       else
       {
       ::SetWindowPos(get_handle(), (oswindow) z, x, y, cx, cy, nFlags);
       }
       if(m_pui != NULL)
       {
       m_pui->oprop("pending_layout") = true;
       m_pui->oprop("pending_zorder") = z;
       }*/
      /*if(&System != NULL && System.get_twf() != NULL)
       {
       System.get_twf()->synch_redraw();
       }*/
      /*    }
       else
       {
       if(z == -3)
       {
       ::SetWindowPos(get_handle(), (oswindow) 0, x, y, cx, cy, nFlags);
       }
       else
       {
       ::SetWindowPos(get_handle(), (oswindow) z, x, y, cx, cy, nFlags);
       }
       }*/
      
      //      if(nFlags & SWP_REDRAWWINDOW)
      {
         
         _001RedrawWindow();

      }
      
      return true;
      
   }
   
   
   void window::MoveWindow(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, bool bRepaint)
   {
      
      ASSERT(::IsWindow(get_handle()));
      
      SetWindowPos(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);
      
   }
   
   
   void window::ClientToScreen(LPRECT lprect)
   {
      
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lprect->left   += (LONG) rectWindow.left;
      lprect->right  += (LONG) rectWindow.left;
      lprect->top    += (LONG) rectWindow.top;
      lprect->bottom += (LONG) rectWindow.top;
      
   }
   
   void window::ClientToScreen(LPPOINT lppoint)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lppoint->x     += (LONG) rectWindow.left;
      lppoint->y     += (LONG) rectWindow.top;
   }
   
   
   void window::ClientToScreen(__rect64 * lprect)
   {
      class rect rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lprect->left   += rectWindow.left;
      lprect->right  += rectWindow.left;
      lprect->top    += rectWindow.top;
      lprect->bottom += rectWindow.top;
      
   }
   
   void window::ClientToScreen(__point64 * lppoint)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lppoint->x     += rectWindow.left;
      lppoint->y     += rectWindow.top;
   }
   
   
   void window::ScreenToClient(LPRECT lprect)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lprect->left   -= (LONG) rectWindow.left;
      lprect->right  -= (LONG) rectWindow.left;
      lprect->top    -= (LONG) rectWindow.top;
      lprect->bottom -= (LONG) rectWindow.top;
      
   }
   
   void window::ScreenToClient(LPPOINT lppoint)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lppoint->x     -= (LONG) rectWindow.left;
      lppoint->y     -= (LONG) rectWindow.top;
   }
   
   
   void window::ScreenToClient(__rect64 * lprect)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lprect->left   -= rectWindow.left;
      lprect->right  -= rectWindow.left;
      lprect->top    -= rectWindow.top;
      lprect->bottom -= rectWindow.top;
      
   }
   
   void window::ScreenToClient(__point64 * lppoint)
   {
      class rect64 rectWindow;
      m_pui->GetWindowRect(rectWindow);
      
      lppoint->x     -= rectWindow.left;
      lppoint->y     -= rectWindow.top;
   }
   
   
   void window::GetWindowRect(__rect64 * lprect)
   {
      if(!::IsWindow(get_handle()))
         throw simple_exception(get_app(), "no more a window");
      // if it is temporary window - probably not ca2 wrapped window
      if(m_pui == NULL || m_pui == this)
      {
         rect rect32;
         ::GetWindowRect(get_handle(), rect32);
         ::copy(lprect, rect32);
      }
      else
      {
         interaction::GetWindowRect(lprect);
      }
   }
   
   void window::GetClientRect(__rect64 * lprect)
   {
      ASSERT(::IsWindow(get_handle()));
      // if it is temporary window - probably not ca2 wrapped window
      if(m_pui == NULL || m_pui == this)
      {
         rect rect32;
         ::GetClientRect(get_handle(), rect32);
         ::copy(lprect, rect32);
      }
      else
      {
         interaction::GetClientRect(lprect);
      }
   }
   
   id window::SetDlgCtrlId(id id)
   {
      m_id = id;
      return m_id;
   }
   
   id window::GetDlgCtrlId()
   {
      return m_id;
   }
   
   /*   guie_message_wnd::guie_message_wnd(base_application * papp) :
    element(papp)
    {
    m_pguieForward = NULL;
    }
    
    LRESULT guie_message_wnd::message_handler(signal_details * pobj)
    {
    if(m_pguieForward != NULL)
    {
    return m_pguieForward->message_handler(uiMessage, wparam, lparam);
    }
    else
    {
    return 0;
    }
    }*/
   
   void window::_001WindowMaximize()
   {
      ::user::interaction::_001WindowMaximize();
   }
   
   void window::_001WindowRestore()
   {
      m_eappearance = user::AppearanceNormal;
      if(m_pui != NULL)
         m_pui->m_eappearance = user::AppearanceNormal;
//      ::ShowWindow(get_handle(), SW_RESTORE);
   }
   
   bool window::ShowWindow(int32_t nCmdShow)
   {
      if(!::IsWindow(get_handle()))
         return false;
      
      /*
       if(GetExStyle() & WS_EX_LAYERED)
       {
       if(nCmdShow == SW_HIDE)
       {
       ModifyStyle(get_handle(), WS_VISIBLE, 0, 0);
       }
       else
       {
       ModifyStyle(get_handle(), 0, WS_VISIBLE, 0);
       }
       if(nCmdShow == SW_MAXIMIZE)
       {
       _001WindowMaximize();
       }
       else if(nCmdShow == SW_RESTORE)
       {
       _001WindowRestore();
       }
       else
       {
       if(nCmdShow == SW_MINIMIZE)
       {
       m_pui->m_eappearance = appearance_iconic;
       m_eappearance = appearance_iconic;
       }
       ::ShowWindow(get_handle(), nCmdShow);
       }
       m_bVisible = ::IsWindowVisible(get_handle()) != FALSE;
       if(m_pui!= NULL && m_pui != this)
       m_pui->m_bVisible = m_bVisible;
       if(!m_bVisible || IsIconic())
       {
       ::UpdateLayeredWindow(get_handle(), NULL, NULL, NULL, NULL, NULL, 0, NULL, 0);
       }
       return m_bVisible;
       }
       else*/
      {
//         ::ShowWindow(get_handle(), nCmdShow);
         m_bVisible = ::IsWindowVisible(get_handle()) != FALSE;
         if(m_pui!= NULL && m_pui != this)
            m_pui->m_bVisible = m_bVisible;
         return m_bVisible;
      }
   }
   
   
   bool window::WfiIsIconic()
   {
      ASSERT(::IsWindow(get_handle()));
      if(GetExStyle() & WS_EX_LAYERED)
      {
         return m_pui->m_eappearance == user::AppearanceIconic;
      }
      else
      {
         return ::IsIconic(get_handle()) != FALSE;
      }
   }
   
   bool window::WfiIsZoomed()
   {
      ASSERT(::IsWindow(get_handle()));
      return m_pui->m_eappearance == user::AppearanceZoomed;
   }
   
   
   sp(::user::interaction) window::get_parent() const
   {
      return NULL;
//      if(!::IsWindow(get_handle()))
  //       return NULL;
    //  if(get_handle() == NULL)
      //   return NULL;
     // return ::mac::window::from_handle(::GetParent(get_handle()));
   }
   
   
   LONG window::GetWindowLong(int32_t nIndex)
   {
      
      return ::GetWindowLong(get_handle(), nIndex);
      
   }
   
   
   LONG window::SetWindowLong(int32_t nIndex, LONG lValue)
   {

      return ::SetWindowLong(get_handle(), nIndex, lValue);
      
   }
   
   
   sp(::user::interaction) window::release_capture()
   {
            oswindow hwndCapture = ::GetCapture();
            if(hwndCapture == NULL)
               return NULL;
            if(hwndCapture == get_handle())
            {
               ::user::interaction * puieCapture = get_capture();
               if(::ReleaseCapture())
               {
                  m_pguieCapture = NULL;
                  return puieCapture;
               }
               else
               {
                  return NULL;
               }
            }
            else
            {
               return window::GetCapture()->release_capture();
            }
   }
   
   sp(::user::interaction) window::get_capture()
   {
            oswindow hwndCapture = ::GetCapture();
            if(hwndCapture == NULL)
               return NULL;
            if(hwndCapture == get_handle())
            {
               if(m_pguieCapture != NULL)
               {
                  return m_pguieCapture;
               }
               else
               {
                  if(m_pui != NULL)
                  {
                     if(m_pui->get_wnd() != NULL && MAC_WINDOW(m_pui->get_wnd())->m_pguieCapture != NULL)
                     {
                        return MAC_WINDOW(m_pui->get_wnd())->m_pguieCapture;
                     }
                     else
                     {
                        return m_pui;
                     }
                  }
                  else
                  {
                     return this;
                  }
               }
            }
            else
            {
               return window::GetCapture()->get_capture();
            }
   }
   
   
   
   // window
   /* window::operator oswindow() const
    { return this == NULL ? NULL : get_handle(); }*/
   bool window::operator==(const ::window& wnd) const
   {
      return MAC_WINDOW(const_cast < ::window * > (&wnd))->get_handle() == get_handle();
   }
   
   bool window::operator!=(const ::window& wnd) const
   {
      return MAC_WINDOW(const_cast < ::window * > (&wnd))->get_handle() != get_handle();
   }
   
   DWORD window::GetStyle()
   {
      ASSERT(::IsWindow(get_handle()));
      return (DWORD)::GetWindowLong(get_handle(), GWL_STYLE);
   }
   
   DWORD window::GetExStyle()
   {
      ASSERT(::IsWindow(get_handle()));
      return (DWORD)::GetWindowLong(get_handle(), GWL_EXSTYLE);
   }
   
   bool window::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      ASSERT(::IsWindow(get_handle()));
      return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);
   }
   
   bool window::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      ASSERT(::IsWindow(get_handle()));
      return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);
   }
   
   void window::set_owner(sp(::user::interaction) pOwnerWnd)
   {
      m_puiOwner = pOwnerWnd;
   }
   
   LRESULT window::send_message(UINT message, WPARAM wparam, lparam lparam)
   {
      
      ::smart_pointer < ::message::base > spbase;
      
      spbase = get_base(m_pui, message, wparam, lparam);
      
      /*      try
       {
       ::user::interaction * pui = m_pui;
       while(pui != NULL)
       {
       try
       {
       pui->pre_translate_message(spbase);
       }
       catch(...)
       {
       break;
       }
       if(spbase->m_bRet)
       return spbase->get_lresult();
       try
       {
       pui = pui->get_parent();
       }
       catch(...)
       {
       break;
       }
       }
       }
       catch(...)
       {
       }*/
      message_handler(spbase);
      return spbase->get_lresult();
      
      //throw todo(get_app());
      
      ////ASSERT(::IsWindow(get_handle()));
      //return ::SendMessage(get_handle(), message, wParam, lParam);
   }
   
   bool window::post_message(UINT message, WPARAM wparam, lparam lparam)
   {
      if(m_pthread != NULL)
      {
         return m_pthread->post_message(m_pui, message, wparam, lparam);
      }
      else
      {
         return FALSE;
      }
   }
   
   bool window::DragDetect(POINT pt) const
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      
      //return ::DragDetect(get_handle(), pt) != FALSE;
      
   }
   
   void window::SetWindowText(const char * lpszString)
   {
      m_strWindowText = lpszString;
   }
   
   strsize window::GetWindowText(LPTSTR lpszString, strsize nMaxCount)
   {
      strncpy(lpszString, m_strWindowText, nMaxCount);
      return min(nMaxCount, m_strWindowText.get_length());
   }
   
   strsize window::GetWindowTextLength()
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      
      //return ::GetWindowTextLength(get_handle());
      
   }
   
   void window::SetFont(::draw2d::font* pfont, bool bRedraw)
   {
      UNREFERENCED_PARAMETER(bRedraw);
      ASSERT(::IsWindow(get_handle())); m_pfont = new ::draw2d::font(*pfont);
   }
   
   ::draw2d::font* window::GetFont()
   {
      ASSERT(::IsWindow(get_handle()));
      return m_pfont;
   }
   
   void window::DragAcceptFiles(bool bAccept)
   {
      
      throw not_implemented(get_app());
      
      //ASSERT(::IsWindow(get_handle()));
      //::DragAcceptFiles(get_handle(), bAccept);
      
   }
   
   sp(::user::frame_window) window::EnsureParentFrame()
   {
      ::user::frame_window * pFrameWnd=GetParentFrame();
      ENSURE_VALID(pFrameWnd);
      return pFrameWnd;
   }
   
   sp(::user::interaction) window::EnsureTopLevelParent()
   {
      
      ::user::interaction * pWnd = GetTopLevelParent();
      
      ENSURE_VALID(pWnd);
      
      return pWnd;
      
   }
   
   void window::MoveWindow(LPCRECT lpRect, bool bRepaint)
   {
      MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
   }
   
   UINT window::ArrangeIconicWindows()
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle())); return ::ArrangeIconicWindows(get_handle());
   }
   
   int32_t window::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle())); return ::SetWindowRgn(get_handle(), hRgn, bRedraw);
   }
   
   int32_t window::GetWindowRgn(HRGN hRgn)
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()) && hRgn != NULL); return ::GetWindowRgn(get_handle(), hRgn);
   }
   
   
   bool window::BringWindowToTop()
   {
      
      bool b = ::BringWindowToTop(get_handle()) != FALSE;
      
      round_window_show();
      
      return b;
      
   }
   
   
   void window::MapWindowPoints(::window * pwndTo, LPPOINT lpPoint, UINT nCount)
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), lpPoint, nCount);
   }
   
   void window::MapWindowPoints(::window * pwndTo, LPRECT lpRect)
   {
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::MapWindowPoints(get_handle(), (oswindow) pwndTo->get_handle(), (LPPOINT)lpRect, 2);
   }
   
   ::draw2d::graphics * window::GetDC()
   {
      ::draw2d::graphics_sp g(allocer());
      oswindow oswindow;
      if(get_handle() == NULL)
      {
//         oswindow = ::GetDesktopWindow();
         
      }
      else
      {
         oswindow = (::oswindow) get_handle();
      }
      rect rectClient;
      //oswindow.get_client_rect(rectClient);
      rectClient.left = 0;
      rectClient.top = 0;
      rectClient.right = 500;
      rectClient.bottom = 500;
//      (dynamic_cast < ::draw2d_quartz2d::graphics * >(g.m_p))->attach(cairo_create(cairo_xlib_surface_create(oswindow.display(), oswindow.window(), DefaultVisual(oswindow.display(), 0), rectClient.width(), rectClient.height())));
      return g.detach();
   }
   
   ::draw2d::graphics * window::GetWindowDC()
   {
      ASSERT(::IsWindow(get_handle()));
      ::draw2d::graphics_sp g(allocer());
      g->attach(::GetWindowDC(get_handle()));
      return g.detach();
   }
   
   bool window::ReleaseDC(::draw2d::graphics * pgraphics)
   {
      
      if(pgraphics == NULL)
         return false;
      
//      cairo_t * pcairo = (cairo_t *) pgraphics->get_handle();
//      
//      cairo_surface_t * psurface = cairo_get_target(pcairo);
//      
//      cairo_destroy(pcairo);
//      
//      cairo_surface_destroy(psurface);
      
      //      if(((Gdiplus::Graphics *)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle()) == NULL)
      //       return false;
      
      //::ReleaseDC(get_handle(), (dynamic_cast < ::draw2d_quartz2d::graphics * > (pgraphics))->detach());
      
      //      (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->m_hdc = NULL;
      
      //      pgraphics->release();
      
      return true;
      
   }
   
   void window::UpdateWindow()
   {
      throw not_implemented(get_app());
      //::UpdateWindow(get_handle());
   }
   
   void window::SetRedraw(bool bRedraw)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::SendMessage(get_handle(), WM_SETREDRAW, bRedraw, 0);
   }
   
   bool window::GetUpdateRect(LPRECT lpRect, bool bErase)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::GetUpdateRect(get_handle(), lpRect, bErase) != FALSE;
   }
   
   int32_t window::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::GetUpdateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   }
   
   void window::Invalidate(bool bErase)
   {
      m_bNeedsUpdate = true;
      //      round_window_invalidate();
//      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::InvalidateRect(get_handle(), NULL, bErase);
   }
   
   void window::InvalidateRect(LPCRECT lpRect, bool bErase)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::InvalidateRect(get_handle(), lpRect, bErase);
   }
   
   void window::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::InvalidateRgn(get_handle(), (HRGN)pRgn->get_handle(), bErase);
   }
   
   void window::ValidateRect(LPCRECT lpRect)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::ValidateRect(get_handle(), lpRect);
   }
   
   void window::ValidateRgn(::draw2d::region* pRgn)
   {
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::ValidateRgn(get_handle(), (HRGN)pRgn->get_handle());
   }
   
   bool window::IsWindowVisible()
   {
      
      if(!::IsWindow(get_handle()))
         return false;
      
      if(m_pui != NULL)
      {
         
         if(!m_pui->m_bVisible)
            return false;
         
         if(m_pui->get_parent() != NULL && !m_pui->get_parent()->IsWindowVisible())
            return false;
         
      }
      
      if(!::IsWindowVisible(get_handle()))
         return false;
      
      return true;
      
   }
   
   
   void window::ShowOwnedPopups(bool bShow)
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::ShowOwnedPopups(get_handle(), bShow);
      
   }
   
   void window::SendMessageToDescendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {
      ASSERT(::IsWindow(get_handle()));
      //window::SendMessageToDescendants(get_handle(), message, wparam, lparam, bDeep, bOnlyPerm);
      
      // walk through oswindows to avoid creating temporary window objects
      // unless we need to call this function recursively
      user::interaction * pui = m_pui->get_top_child();
      while(pui != NULL)
      {
         try
         {
            pui->send_message(message, wparam, lparam);
         }
         catch(...)
         {
         }
         if (bDeep)
         {
            // send to child windows after parent
            try
            {
               pui->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);
            }
            catch(...)
            {
            }
         }
         try
         {
            pui = pui->under_sibling();
         }
         catch(...)
         {
            break;
         }
      }
   }
   
   sp(::user::interaction) window::GetDescendantWindow(id id)
   {
//      ASSERT(::IsWindow(get_handle()));
  //    return window::GetDescendantWindow(this, id);
      
      single_lock sl(&m_pthread->m_mutex, TRUE);
      for(int32_t i = 0; i < m_pui->m_uiptraChild.get_count(); i++)
      {
         if(m_pui->m_uiptraChild[i].GetDlgCtrlId() == id)
         {
            if(m_pui->m_uiptraChild[i].GetDescendantWindow(id))
               return m_pui->m_uiptraChild[i].GetDescendantWindow(id);
            else
               return m_pui->m_uiptraChild(i);
         }
      }
      
      return NULL;
   }
   
   
   ::draw2d::graphics * window::GetDCEx(::draw2d::region* prgnClip, DWORD flags)
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::draw2d::graphics_sp g(get_app());
      //g->attach(::GetDCEx(get_handle(), (HRGN)prgnClip->get_handle(), flags));
      //return g.detach();
      
   }
   
   bool window::LockWindowUpdate()
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::LockWindowUpdate(get_handle()) != FALSE;
      
   }
   
   void window::UnlockWindowUpdate()
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //::LockWindowUpdate(NULL);
      
   }
   
   bool window::RedrawWindow(LPCRECT lpRectUpdate, ::draw2d::region* prgnUpdate, UINT flags)
   {
      
      round_window_redraw();
      
      return true;
      
   }
   
   /*
    bool window::EnableScrollBar(int32_t nSBFlags, UINT nArrowFlags)
    {
    
    ASSERT(::IsWindow(get_handle()));
    
    return ::EnableScrollBar(get_handle(), nSBFlags, nArrowFlags) != FALSE;
    
    }
    */
   
   bool window::DrawAnimatedRects(int32_t idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo)
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::DrawAnimatedRects(get_handle(), idAni, lprcFrom, lprcTo) != FALSE;
      
   }
   
   bool window::DrawCaption(::draw2d::graphics * pgraphics, LPCRECT lprc, UINT uFlags)
   {
      
      throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::DrawCaption(get_handle(), (HDC)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), lprc, uFlags) != FALSE;
      
   }
   
   uint_ptr window::SetTimer(uint_ptr nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, DWORD))
   {

      UNREFERENCED_PARAMETER(lpfnTimer);
      
      m_pui->m_pthread->set_timer(m_pui, nIDEvent, nElapse);
      
      return nIDEvent;
      
      //throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::SetTimer(get_handle(), nIDEvent, nElapse, lpfnTimer);
      //return true;
      
   }
   
   bool window::KillTimer(uint_ptr nIDEvent)
   {
      
      //throw not_implemented(get_app());
      //ASSERT(::IsWindow(get_handle()));
      //return ::KillTimer(get_handle(), nIDEvent)  != FALSE;
      
      m_pui->m_pthread->unset_timer(m_pui, nIDEvent);
      

      return true;
      
   }
   
   bool window::IsWindowEnabled()
   {
      
      return true;
      
      /*      if(!::IsWindow(get_handle()))
       return false;
       
       return ::IsWindowEnabled(get_handle()) != FALSE;
       */
      
   }
   
   
   bool window::EnableWindow(bool bEnable)
   {
      
      /*      ASSERT(::IsWindow(get_handle()));
       
       return ::EnableWindow(get_handle(), bEnable) != FALSE;
       */
      
      return true;
      
   }
   
   sp(::user::interaction) window::GetActiveWindow()
   {
      
      return ::mac::window::from_handle(::GetActiveWindow());
      
   }
   
   sp(::user::interaction) window::SetActiveWindow()
   {
      
      ASSERT(::IsWindow(get_handle()));
      return ::mac::window::from_handle(::SetActiveWindow(get_handle()));
      
   }
   
   
   ::window * PASCAL window::GetCapture()
   {
      
      return ::mac::window::from_handle(::GetCapture());
      
   }
   
   
   sp(::user::interaction) window::set_capture(sp(::user::interaction) pinterface)
   {
      
      ASSERT(::IsWindow(get_handle()));
      
      if(pinterface != NULL)
         m_pguieCapture = pinterface;
      
      return dynamic_cast < ::window * > (::mac::window::from_handle(::SetCapture(get_handle())));
      
   }
   
   
   ::window * PASCAL window::GetFocus()
   {
      
      return ::mac::window::from_handle(::GetFocus());
      
   }
   
   
   sp(::user::interaction) window::SetFocus()
   {
      
      if(!::IsWindow(get_handle()))
         return NULL;
      
      return ::mac::window::from_handle(::SetFocus(get_handle()));
      
   }
   
   
   ::window * PASCAL window::GetDesktopWindow()
   {
      
      /*
       return ::mac::window::from_handle(::GetDesktopWindow());
       */
      
      return NULL;
      
   }
   
   
   // Helper for radio buttons
   int32_t window::GetCheckedRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton)
   {
      
      for (int32_t nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {
         if (IsDlgButtonChecked(nID))
            return nID; // id that matched
      }
      return 0; // invalid ID
   }
   
   void window::CheckDlgButton(int32_t nIDButton, UINT nCheck)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CheckDlgButton(get_handle(), nIDButton, nCheck);
      
   }
   
   void window::CheckRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton, int32_t nIDCheckButton)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CheckRadioButton(get_handle(), nIDFirstButton, nIDLastButton, nIDCheckButton);
      
   }
   
   int32_t window::DlgDirList(LPTSTR lpPathSpec, int32_t nIDListBox, int32_t nIDStaticPath, UINT nFileType)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::DlgDirList(get_handle(), lpPathSpec, nIDListBox, nIDStaticPath, nFileType);
      
   }
   
   int32_t window::DlgDirListComboBox(LPTSTR lpPathSpec, int32_t nIDComboBox, int32_t nIDStaticPath, UINT nFileType)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::DlgDirListComboBox(get_handle(), lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);
      
   }
   
   bool window::DlgDirSelect(LPTSTR lpString, int32_t nSize, int32_t nIDListBox)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::DlgDirSelectEx(get_handle(), lpString, nSize, nIDListBox) != FALSE;
      
   }
   
   bool window::DlgDirSelectComboBox(LPTSTR lpString, int32_t nSize, int32_t nIDComboBox)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::DlgDirSelectComboBoxEx(get_handle(), lpString, nSize, nIDComboBox) != FALSE;
      
   }
   
   /*
    void window::GetDlgItem(id id, oswindow* phWnd) const
    {
    
    ASSERT(::IsWindow(get_handle()));
    ASSERT(phWnd != NULL);
    *phWnd = ::GetDlgItem(get_handle(), (int32_t) id);
    
    }
    */
   
   /*
    UINT window::GetDlgItemInt(int32_t nID, WINBOOL * lpTrans, bool bSigned) const
    {
    
    ASSERT(::IsWindow(get_handle()));
    
    return ::GetDlgItemInt(get_handle(), nID, lpTrans, bSigned);
    
    }
    */
   
   //   int32_t window::GetDlgItemText(int32_t nID, LPTSTR lpStr, int32_t nMaxCount) const
   //   {
   //
   //      throw not_implemented(get_app());
   //      ASSERT(::IsWindow(get_handle())); return ::GetDlgItemText(get_handle(), nID, lpStr, nMaxCount);}
   
   ::window * window::GetNextDlgGroupItem(::window * pWndCtl, bool bPrevious) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::GetNextDlgGroupItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
      
   }
   
   ::window * window::GetNextDlgTabItem(::window * pWndCtl, bool bPrevious) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::GetNextDlgTabItem(get_handle(), (oswindow) pWndCtl->get_handle(), bPrevious));
      
   }
   
   UINT window::IsDlgButtonChecked(int32_t nIDButton) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::IsDlgButtonChecked(get_handle(), nIDButton);
      
   }
   
   LPARAM window::SendDlgItemMessage(int32_t nID, UINT message, WPARAM wparam, LPARAM lparam)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::SendDlgItemMessage(get_handle(), nID, message, wparam, lparam);
      
   }
   
   void window::SetDlgItemInt(int32_t nID, UINT nValue, bool bSigned)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::SetDlgItemInt(get_handle(), nID, nValue, bSigned);
      
   }
   
   void window::SetDlgItemText(int32_t nID, const char * lpszString)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::SetDlgItemText(get_handle(), nID, lpszString);
      
   }
   
   int32_t window::ScrollWindowEx(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::ScrollWindowEx(get_handle(), dx, dy, lpRectScroll, lpRectClip, (HRGN)prgnUpdate->get_handle(), lpRectUpdate, flags);
      
   }
   
   void window::ShowScrollBar(UINT nBar, bool bShow)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::ShowScrollBar(get_handle(), nBar, bShow);
      
   }
   
   sp(::user::interaction) window::ChildWindowFromPoint(POINT point)
   {
      
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::ChildWindowFromPoint(get_handle(), point));
      
   }
   
   sp(::user::interaction) window::ChildWindowFromPoint(POINT point, UINT nFlags)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::ChildWindowFromPointEx(get_handle(), point, nFlags));
      
   }
   
   ::window * PASCAL window::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      
      //      throw not_implemented(get_app());
      //      return ::mac::window::from_handle(::FindWindow(lpszClassName, lpszWindowName));
      return NULL;
      
   }
   
   ::window * window::FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      
      throw not_implemented(::get_thread_app());
      //      return ::mac::window::from_handle(::FindWindowEx(hwndParent, hwndChildAfter, lpszClass, lpszWindow));
      
   }
   
   sp(::user::interaction) window::GetNextWindow(UINT nFlag)
   {
      
      return NULL;
      
   }
   
   sp(::user::interaction) window::GetTopWindow()
   {
      
      if(m_pui->m_uiptraChild.get_size() <= 0)
         return NULL;
      
      return m_pui->m_uiptraChild(0);
      
   }
   
   sp(::user::interaction) window::GetWindow(UINT nCmd)
   {
      
      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::GetWindow(get_handle(), nCmd));
      return NULL;
      
   }
   
   sp(::user::interaction) window::GetLastActivePopup()
   {
      
      
      throw todo(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::mac::window::from_handle(::GetLastActivePopup(get_handle()));
      
   }
   
   ::window * window::set_parent(::window * pWndNewParent)
   {
      
      ASSERT(::IsWindow(get_handle()));
      return ::mac::window::from_handle(::SetParent(get_handle(), (oswindow) pWndNewParent->get_handle()));
      
   }
   
   ::window * PASCAL window::oswindowFromPoint(POINT point)
   {
      
      
      throw not_implemented(::get_thread_app());
      //      return ::mac::window::from_handle(::oswindowFromPoint(point));
      
   }
   
   bool window::FlashWindow(bool bInvert)
   {
      
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::FlashWindow(get_handle(), bInvert) != FALSE;
      
   }
   
   bool window::ChangeClipboardChain(oswindow hWndNext)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;
      
   }
   
   oswindow window::SetClipboardViewer()
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::SetClipboardViewer(get_handle());
      
   }
   
   bool window::OpenClipboard()
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::OpenClipboard(get_handle()) != FALSE;
      
   }
   
   ::window * PASCAL window::GetOpenClipboardWindow()
   {
      
      throw not_implemented(::get_thread_app());
      //      return ::mac::window::from_handle(::GetOpenClipboardWindow());
      
   }
   
   ::window * PASCAL window::GetClipboardOwner()
   {
      
      throw not_implemented(::get_thread_app());
      //      return ::mac::window::from_handle(::GetClipboardOwner());
      
   }
   
   ::window * PASCAL window::GetClipboardViewer()
   {
      
      throw not_implemented(::get_thread_app());
      //      return ::mac::window::from_handle(::GetClipboardViewer());
      
   }
   
   void window::CreateCaret(::draw2d::bitmap* pBitmap)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)pBitmap->get_handle(), 0, 0);
      
   }
   
   void window::CreateSolidCaret(int32_t nWidth, int32_t nHeight)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)0, nWidth, nHeight);
      
   }
   
   void window::CreateGrayCaret(int32_t nWidth, int32_t nHeight)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)1, nWidth, nHeight);
      
   }
   
   point PASCAL window::GetCaretPos()
   {
      
      throw not_implemented(::get_thread_app());
      //      point point;
      //      ::GetCaretPos((LPPOINT)&point); return point;
      
   }
   
   void PASCAL window::SetCaretPos(POINT point)
   {
      
      throw not_implemented(::get_thread_app());
      //      ::SetCaretPos(point.x, point.y);
      
   }
   
   void window::HideCaret()
   {
      
      throw not_implemented(get_app());
      //      ::HideCaret(get_handle());
      
   }
   
   void window::ShowCaret()
   {
      
      throw not_implemented(get_app());
      //    ::ShowCaret(get_handle());
      
   }
   
   bool window::SetForegroundWindow()
   {
      
      bool b = ::SetForegroundWindow(get_handle()) != FALSE;
      
      round_window_show();
      
      return b;
      
   }
   
   ::window * PASCAL window::GetForegroundWindow()
   {
      
      return NULL;
      // return ::mac::window::from_handle(::GetForegroundWindow());
      
   }
   
   bool window::SendNotifyMessage(UINT message, WPARAM wparam, LPARAM lparam)
   {
      
      throw not_implemented(get_app());
      //      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != FALSE;
      
   }
   
   // Win4
   HICON window::SetIcon(HICON hIcon, bool bBigIcon)
   {
      
      throw not_implemented(get_app());
      //return (HICON)send_message(WM_SETICON, bBigIcon, (LPARAM)hIcon);
      
   }
   
   HICON window::GetIcon(bool bBigIcon) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return (HICON)const_cast < window * > (this)->send_message(WM_GETICON, bBigIcon, 0);
      
   }
   
   void window::Print(::draw2d::graphics * pgraphics, DWORD dwFlags) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      const_cast < window * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);
      
   }
   
   void window::PrintClient(::draw2d::graphics * pgraphics, DWORD dwFlags) const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      const_cast < window * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);
      
   }
   
   bool window::SetWindowContextHelpId(DWORD dwContextHelpId)
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;
      
   }
   
   DWORD window::GetWindowContextHelpId() const
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::GetWindowContextHelpId(get_handle());
      
   }
   
   
   // Default message ::collection::map implementations
   void window::OnActivateApp(bool, DWORD)
   { Default(); }
   void window::OnActivate(UINT, ::window *, bool)
   { Default(); }
   void window::OnCancelMode()
   { Default(); }
   void window::OnChildActivate()
   { Default(); }
   void window::OnClose()
   { Default(); }
   void window::OnContextMenu(::window *, point)
   { Default(); }
   
   bool window::OnCopyData(::window *, COPYDATASTRUCT*)
   {
      
      return Default() != FALSE;
      
   }
   
   void window::OnEnable(bool)
   { Default(); }
   void window::OnEndSession(bool)
   { Default(); }
   
   bool window::OnEraseBkgnd(::draw2d::graphics *)
   {
      
      return Default() != FALSE;
      
   }
   
   void window::OnGetMinMaxInfo(MINMAXINFO*)
   { Default(); }
   void window::OnIconEraseBkgnd(::draw2d::graphics *)
   { Default(); }
   void window::OnKillFocus(::window *)
   { Default(); }
   LRESULT window::OnMenuChar(UINT, UINT, ::user::menu*)
   { return Default(); }
   void window::OnMenuSelect(UINT, UINT, HMENU)
   { Default(); }
   void window::OnMove(int32_t, int32_t)
   { Default(); }
   HCURSOR window::OnQueryDragIcon()
   { return (HCURSOR)Default(); }
   
   bool window::OnQueryEndSession()
   {
      
      return Default() != FALSE;
      
   }
   
   bool window::OnQueryNewPalette()
   {
      
      return Default() != FALSE;
      
   }
   
   bool window::OnQueryOpen()
   {
      
      return Default() != FALSE;
      
   }
   
   void window::_001OnSetCursor(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(Session.get_cursor() != NULL
         && Session.get_cursor()->m_ecursor != ::visual::cursor_system)
      {
         
         throw not_implemented(get_app());
         //         ::SetCursor(NULL);
      }
      pbase->set_lresult(1);
      pbase->m_bRet = true;
      //(bool)Default();
   }
   void window::OnShowWindow(bool, UINT)
   { Default(); }
   void window::OnSize(UINT, int32_t, int32_t)
   { Default(); }
   void window::OnTCard(UINT, DWORD)
   { Default(); }
   void window::OnWindowPosChanging(WINDOWPOS*)
   { Default(); }
   void window::OnWindowPosChanged(WINDOWPOS*)
   { Default(); }
   void window::OnDropFiles(HDROP)
   { Default(); }
   void window::OnPaletteIsChanging(::window *)
   { Default(); }
   
   bool window::OnNcActivate(bool)
   {
      
      return Default() != FALSE;
      
   }
   
   void window::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   { Default(); }
   
   bool window::OnNcCreate(LPCREATESTRUCT)
   {
      
      return Default() != FALSE;
      
   }
   
   LRESULT window::OnNcHitTest(point)
   { return Default(); }
   void window::OnNcLButtonDblClk(UINT, point)
   { Default(); }
   void window::OnNcLButtonDown(UINT, point)
   { Default(); }
   void window::OnNcLButtonUp(UINT, point)
   { Default(); }
   void window::OnNcMButtonDblClk(UINT, point)
   { Default(); }
   void window::OnNcMButtonDown(UINT, point)
   { Default(); }
   void window::OnNcMButtonUp(UINT, point)
   { Default(); }
   void window::OnNcMouseMove(UINT, point)
   { Default(); }
   void window::OnNcPaint()
   { Default(); }
   void window::OnNcRButtonDblClk(UINT, point)
   { Default(); }
   void window::OnNcRButtonDown(UINT, point)
   { Default(); }
   void window::OnNcRButtonUp(UINT, point)
   { Default(); }
   void window::OnSysChar(UINT, UINT, UINT)
   { Default(); }
   void window::OnSysCommand(UINT, LPARAM)
   { Default(); }
   void window::OnSysDeadChar(UINT, UINT, UINT)
   { Default(); }
   void window::OnSysKeyDown(UINT, UINT, UINT)
   { Default(); }
   void window::OnSysKeyUp(UINT, UINT, UINT)
   { Default(); }
   void window::OnCompacting(UINT)
   { Default(); }
   void window::OnFontChange()
   { Default(); }
   void window::OnPaletteChanged(::window *)
   { Default(); }
   void window::OnSpoolerStatus(UINT, UINT)
   { Default(); }
   void window::OnTimeChange()
   { Default(); }
   void window::OnChar(UINT, UINT, UINT)
   { Default(); }
   void window::OnDeadChar(UINT, UINT, UINT)
   { Default(); }
   void window::OnKeyDown(UINT, UINT, UINT)
   { Default(); }
   void window::OnKeyUp(UINT, UINT, UINT)
   { Default(); }
   void window::OnLButtonDblClk(UINT, point)
   { Default(); }
   void window::OnLButtonDown(UINT, point)
   { Default(); }
   void window::OnLButtonUp(UINT, point)
   { Default(); }
   void window::OnMButtonDblClk(UINT, point)
   { Default(); }
   void window::OnMButtonDown(UINT, point)
   { Default(); }
   void window::OnMButtonUp(UINT, point)
   { Default(); }
   int32_t window::OnMouseActivate(::window *, UINT, UINT)
   { return (int32_t)Default(); }
   void window::OnMouseMove(UINT, point)
   { Default(); }
   
   bool window::OnMouseWheel(UINT, short, point)
   {
      
      return Default() != FALSE;
      
   }
   
   LRESULT window::OnRegisteredMouseWheel(WPARAM, LPARAM)
   { return Default(); }
   void window::OnRButtonDblClk(UINT, point)
   { Default(); }
   void window::OnRButtonDown(UINT, point)
   { Default(); }
   void window::OnRButtonUp(UINT, point)
   { Default(); }
   void window::OnTimer(uint_ptr)
   { Default(); }
   void window::OnInitMenu(::user::menu*)
   { Default(); }
   void window::OnInitMenuPopup(::user::menu*, UINT, bool)
   { Default(); }
   void window::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
   {
//      (nMaxCount);
      if(nMaxCount>0)
      {
         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
         pszName[0]='\0';
      }
      Default();
   }
   void window::OnChangeCbChain(oswindow, oswindow)
   { Default(); }
   void window::OnDestroyClipboard()
   { Default(); }
   void window::OnDrawClipboard()
   { Default(); }
   void window::OnHScrollClipboard(::window *, UINT, UINT)
   { Default(); }
   void window::OnPaintClipboard(::window *, HGLOBAL)
   { Default(); }
   void window::OnRenderAllFormats()
   { Default(); }
   void window::OnRenderFormat(UINT)
   { Default(); }
   void window::OnSizeClipboard(::window *, HGLOBAL)
   { Default(); }
   void window::OnVScrollClipboard(::window *, UINT, UINT)
   { Default(); }
   UINT window::OnGetDlgCode()
   { return (UINT)Default(); }
   void window::OnMDIActivate(bool, ::window *, ::window *)
   { Default(); }
   void window::OnEnterMenuLoop(bool)
   { Default(); }
   void window::OnExitMenuLoop(bool)
   { Default(); }
   // Win4 support
   //   void window::OnStyleChanged(int32_t, LPSTYLESTRUCT)
   //   { Default(); }
   //   void window::OnStyleChanging(int32_t, LPSTYLESTRUCT)
   //   { Default(); }
   void window::OnSizing(UINT, LPRECT)
   { Default(); }
   void window::OnMoving(UINT, LPRECT)
   { Default(); }
   void window::OnCaptureChanged(::window *)
   { Default(); }
   
   bool window::OnDeviceChange(UINT, uint_ptr)
   {
      
      return Default() != FALSE;
      
   }
   
   void window::OnWinIniChange(const char *)
   { Default(); }
   void window::OnChangeUIState(UINT, UINT)
   { Default(); }
   void window::OnUpdateUIState(UINT, UINT)
   { Default(); }
   
   UINT window::OnQueryUIState()
   {
      
      return (UINT)Default();
      
   }
   
   // window dialog data support
   //    void window::DoDataExchange(CDataExchange*)
   //   { } // default does nothing
   
   // window modality support
   
   void window::BeginModalState()
   {
      
      throw todo(get_app());
      
      //::EnableWindow(get_handle(), FALSE);
      
   }
   
   void window::EndModalState()
   {
      
      throw todo(get_app());
      
      //::EnableWindow(get_handle(), TRUE);
      
   }
   
   // frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
    { m_nIdleFlags |= idleTitle; }
    void frame_window::DelayRecalcLayout(bool bNotify)
    { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
    bool frame_window::InModalState() const
    { return m_cModalStack != 0; }
    void frame_window::set_title(const char * lpszTitle)
    { m_strTitle = lpszTitle; }
    string frame_window::get_title() const
    { return m_strTitle; }
    */
   
   
   
   void window::CloseWindow()
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      ::CloseWindow(get_handle());
      
   }
   
   bool window::OpenIcon()
   {
      
      throw not_implemented(get_app());
      //      ASSERT(::IsWindow(get_handle()));
      //      return ::OpenIcon(get_handle()) != FALSE;
      
   }
   
   ////////////////////////////////////////////////////////////////////////////
   // UI related ::window functions
   
   oswindow PASCAL window::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
   {
      // get ::window to start with
      oswindow hWnd = hParent;
      if (hWnd == NULL)
      {
         /* trans      frame_window* pFrame = command_target::GetRoutingFrame_();
          if (pFrame != NULL)
          hWnd = pFrame->get_handle();
          else
          hWnd = System.GetMainWnd()->get_handle();*/
      }
      
      // a popup ::window cannot be owned by a child ::window
      while (hWnd != NULL && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
         hWnd = ::GetParent(hWnd);
      
      // determine toplevel ::window to disable as well
      oswindow hWndTop = hWnd, hWndTemp = hWnd;
      for (;;)
      {
         if (hWndTemp == NULL)
            break;
         else
            hWndTop = hWndTemp;
         hWndTemp = ::GetParent(hWndTop);
      }
      
      throw todo(::get_thread_app());
      // get last active popup of first non-child that was found
      //    if (hParent == NULL && hWnd != NULL)
      //       hWnd = ::GetLastActivePopup(hWnd);
      
      // disable and store top level parent ::window if specified
      if (pWndTop != NULL)
      {
         /*         if (hWndTop != NULL && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
          {
          *pWndTop = hWndTop;
          ::EnableWindow(hWndTop, FALSE);
          }
          else
          *pWndTop = ::caNULL;*/
      }
      
      return hWnd;    // return the owner as oswindow
   }
   
   /*
   void window::on_delete(::ca2::ca2 * pui)
   {
      UNREFERENCED_PARAMETER(pui);
   }
   */
   
   /////////////////////////////////////////////////////////////////////////////
   // Official way to send message to a window
   
   CLASS_DECL_mac LRESULT __call_window_procedure(::user::interaction * pinteraction, oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam)
   {
      ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
//      MESSAGE oldState = pThreadState->m_lastSentMsg;   // save for nesting
      
      throw not_implemented(pinteraction->get_app());
      
      //      pThreadState->m_lastSentMsg.m_pwnd = pinteraction;
      pThreadState->m_lastSentMsg.message = nMsg;
      pThreadState->m_lastSentMsg.wParam = wparam;
      pThreadState->m_lastSentMsg.lParam = lparam;
      
      // Catch exceptions thrown outside the scope of a callback
      // in debug builds and warn the ::fontopus::user.
      //      ::ca2::smart_pointer < ::message::base > spbase;
      //
      //      spbase(pinteraction->get_base(pinteraction, nMsg, wparam, lparam));
      //
      //      __trace_message("WndProc", spbase);
      //
      //      try
      //      {
      //
      //         // special case for WM_INITDIALOG
      //         rect rectOld;
      //         DWORD dwStyle = 0;
      //         if (nMsg == WM_INITDIALOG)
      //            __pre_init_dialog(pinteraction, &rectOld, &dwStyle);
      //
      //         // delegate to object's message_handler
      //         if(pinteraction->m_pui != NULL && pinteraction->m_pui != pinteraction)
      //         {
      //            pinteraction->m_pui->message_handler(spbase);
      //         }
      //         else
      //         {
      //            pinteraction->message_handler(spbase);
      //         }
      //         // more special case for WM_INITDIALOG
      //         if (nMsg == WM_INITDIALOG)
      //            __post_init_dialog(pinteraction, rectOld, dwStyle);
      //      }
      //      catch(const ::exception::exception & e)
      //      {
      //         try
      //         {
      //            if(App(pinteraction->m_pbaseapp->m_pplaneapp).on_run_exception((::exception::exception &) e))
      //               goto run;
      //         }
      //         catch(...)
      //         {
      //         }
      //         return -1;
      //      }
      //      catch(::exception::base * pe)
      //      {
      //         __process_window_procedure_exception(pe, spbase);
      //         //         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: Uncaught exception in message_handler (returning %ld).\n", spbase->get_lresult());
      //         pe->Delete();
      //      }
      //      catch(...)
      //      {
      //      }
      //run:
      //      try
      //      {
      //         pThreadState->m_lastSentMsg = oldState;
      //         LRESULT lresult = spbase->get_lresult();
      //         return lresult;
      //      }
      //      catch(...)
      //      {
      //         return 0;
      //      }
   }
   
   
   /*CDataExchange::CDataExchange(::window * pDlgWnd, bool bSaveAndValidate)
    {
    ASSERT_VALID(pDlgWnd);
    m_bSaveAndValidate = bSaveAndValidate;
    m_pDlgWnd = pDlgWnd;
    m_idLastControl = 0;
    }*/
   
   /////////////////////////////////////////////////////////////////////////////
   // oswindow creation hooks
   
   LRESULT CALLBACK __cbt_filter_hook(int32_t code, WPARAM wparam, LPARAM lparam)
   {
      
      throw not_implemented(::get_thread_app());
      
      //      ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
      //      if (code != HCBT_CREATEWND)
      //      {
      //         // wait for HCBT_CREATEWND just pass others on...
      //         return CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code,
      //            wparam, lparam);
      //      }
      //
      //      ASSERT(lparam != NULL);
      //      LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lparam)->lpcs;
      //      ASSERT(lpcs != NULL);
      //
      //      ::user::interaction * pWndInit = pThreadState->m_pWndInit;
      //      bool bContextIsDLL = afxContextIsDLL;
      //      if (pWndInit != NULL || (!(lpcs->style & WS_CHILD) && !bContextIsDLL))
      //      {
      //         // Note: special check to avoid subclassing the IME window
      //         //if (gen_DBCS)
      //         {
      //            // check for cheap CS_IME style first...
      //            if (GetClassLong((oswindow)wparam, GCL_STYLE) & CS_IME)
      //               goto lCallNextHook;
      //
      //            // get class name of the window that is being created
      //            const char * pszClassName;
      //            char szClassName[_countof("ime")+1];
      //            if (dword_ptr(lpcs->lpszClass) > 0xffff)
      //            {
      //               pszClassName = lpcs->lpszClass;
      //            }
      //            else
      //            {
      //               szClassName[0] = '\0';
      //               GlobalGetAtomName((ATOM)lpcs->lpszClass, szClassName, _countof(szClassName));
      //               pszClassName = szClassName;
      //            }
      //
      //            // a little more expensive to test this way, but necessary...
      //            if (::__invariant_stricmp(pszClassName, "ime") == 0)
      //               goto lCallNextHook;
      //         }
      //
      //         ASSERT(wparam != NULL); // should be non-NULL oswindow
      //         oswindow hWnd = (oswindow)wparam;
      //         WNDPROC oldWndProc;
      //         if (pWndInit != NULL)
      //         {
      //            // the window should not be in the permanent ::collection::map at this time
      //            ASSERT(::mac::window::FromHandlePermanent(hWnd) == NULL);
      //
      //            pWndInit->m_pthread = dynamic_cast < ::thread * > (::mac::get_thread());
      //            pWndInit->m_pthread->add(pWndInit);
      //            pWndInit->m_pui->m_pthread = pWndInit->m_pthread;
      //            pWndInit->m_pui->m_pthread->add(pWndInit->m_pui);
      //            pWndInit->m_pui->m_pimpl = pWndInit;
      //
      //            // connect the oswindow to pWndInit...
      //            pWndInit->Attach(hWnd);
      //            // allow other subclassing to occur first
      //            pWndInit->pre_subclass_window();
      //
      //            WNDPROC *pOldWndProc = pWndInit->GetSuperWndProcAddr();
      //            ASSERT(pOldWndProc != NULL);
      //
      //            // subclass the window with standard __window_procedure
      //            WNDPROC afxWndProc = __get_window_procedure();
      //            oldWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC,
      //               (dword_ptr)afxWndProc);
      //            ASSERT(oldWndProc != NULL);
      //            if (oldWndProc != afxWndProc)
      //               *pOldWndProc = oldWndProc;
      //
      //            pThreadState->m_pWndInit = NULL;
      //         }
      //         else
      //         {
      //            ASSERT(!bContextIsDLL);   // should never get here
      //
      //            static ATOM s_atomMenu = 0;
      //            bool bSubclass = true;
      //
      //            if (s_atomMenu == 0)
      //            {
      //               WNDCLASSEX wc;
      //               memset(&wc, 0, sizeof(WNDCLASSEX));
      //               wc.cbSize = sizeof(WNDCLASSEX);
      //               s_atomMenu = (ATOM)::GetClassInfoEx(NULL, "#32768", &wc);
      //            }
      //
      //            // Do not subclass menus.
      //            if (s_atomMenu != 0)
      //            {
      //               ATOM atomWnd = (ATOM)::GetClassLongPtr(hWnd, GCW_ATOM);
      //               if (atomWnd == s_atomMenu)
      //                  bSubclass = false;
      //            }
      //            else
      //            {
      //               char szClassName[256];
      //               if (::GetClassName(hWnd, szClassName, 256))
      //               {
      //                  szClassName[255] = NULL;
      //                  if (_tcscmp(szClassName, "#32768") == 0)
      //                     bSubclass = false;
      //               }
      //            }
      //            if (bSubclass)
      //            {
      //               // subclass the window with the proc which does gray backgrounds
      //               oldWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
      //               if (oldWndProc != NULL && GetProp(hWnd, gen_OldWndProc) == NULL)
      //               {
      //                  SetProp(hWnd, gen_OldWndProc, oldWndProc);
      //                  if ((WNDPROC)GetProp(hWnd, gen_OldWndProc) == oldWndProc)
      //                  {
      //                     GlobalAddAtom(gen_OldWndProc);
      //                     SetWindowLongPtr(hWnd, GWLP_WNDPROC, (dword_ptr)__activation_window_procedure);
      //                     ASSERT(oldWndProc != NULL);
      //                  }
      //               }
      //            }
      //         }
      //      }
      //
      //lCallNextHook:
      //      LRESULT lResult = CallNextHookEx(pThreadState->m_hHookOldCbtFilter, code,
      //         wparam, lparam);
      //
      //      return lResult;
   }
   
   
   
   void window::_001OnEraseBkgnd(signal_details * pobj)
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }
   
   void window::_001BaseWndInterfaceMap()
   {
      System.user()->window_map().set((int_ptr)get_handle(), this);
   }
   
   
   void window::_001OnTriggerMouseInside()
   {
      
      
      //throw not_implemented(get_app());
      //      m_bMouseHover = true;
      //      TRACKMOUSEEVENT tme = { sizeof(tme) };
      //      tme.dwFlags = TME_LEAVE;
      //      tme.hwndTrack = get_handle();
      //      TrackMouseEvent(&tme);
      
   }
   

   void window::round_window_draw(CGContextRef cgc)
   {
      
      if(m_bUpdateGraphics)
      {
         
         update_graphics_resources();
         
         _001UpdateWindow();
         
      }

      single_lock sl(mutex_display(), true);
      
      if(m_spdibFlip.is_null())
         return;
      
      if(m_spdibFlip->get_data() == NULL)
         return;

      ::draw2d::graphics_sp g(allocer());
      
      g->attach(cgc);
 
      g->BitBlt(0, 0, m_spdibFlip->m_size.cx, m_spdibFlip->m_size.cy, m_spdibFlip->get_graphics(), 0, 0, SRCCOPY);
      
   }
   
   
   bool window::round_window_key_down(::user::e_key ekey)
   {
      
      sp(::message::base) spbase;
      
      ::message::key * pkey = canew(::message::key(get_app()));
      
      pkey->m_uiMessage = WM_KEYDOWN;
      pkey->m_ekey = ekey;
      
      spbase = pkey;
      
      send(spbase);
      
      return spbase->m_bRet;
      
   }

   
   bool window::round_window_key_up(::user::e_key ekey)
   {
      
      sp(::message::base) spbase;
      
      ::message::key * pkey = canew(::message::key(get_app()));
      
      pkey->m_uiMessage = WM_KEYUP;
      pkey->m_ekey = ekey;
      
      spbase = pkey;
      
      send(spbase);
      
      return spbase->m_bRet;
      
   }
   
   
   void window::round_window_mouse_down(double x, double y)
   {
      
      sp(::message::base) spbase;
      
      if(::GetActiveWindow() != get_handle())
      {
         
         try
         {
            
            ::message::mouse_activate * pmouseactivate = canew(::message::mouse_activate(get_app()));
            
            pmouseactivate->m_uiMessage = WM_MOUSEACTIVATE;
            
            spbase = pmouseactivate;
            
            send(spbase);
            
            if(spbase->get_lresult() == MA_ACTIVATE || spbase->get_lresult() == MA_ACTIVATEANDEAT)
            {
            
               ::message::activate * pactivate = canew(::message::activate(get_app()));
            
               pactivate->m_uiMessage = WM_ACTIVATE;
               pactivate->m_wparam = WA_CLICKACTIVE;
               pactivate->m_nState = WA_CLICKACTIVE;
               pactivate->m_bMinimized = false;
            
               spbase = pactivate;
            
               send(spbase);
            
            }
            
         }
         catch(...)
         {
         }
         
      }
      
      {
      
         ::message::mouse * pmouse = canew(::message::mouse(get_app()));
      
         pmouse->m_uiMessage = WM_LBUTTONDOWN;
         pmouse->m_pt.x = (LONG) x;
         pmouse->m_pt.y = (LONG) y;
         pmouse->m_bTranslated = true;
         //pmouse->m_bTranslateMouseMessageCursor = true;
      
         spbase = pmouse;
      
         send(spbase);
         
      }
      
   }
   
   
   void window::round_window_mouse_up(double x, double y)
   {
      
      sp(::message::base) spbase;
      
      ::message::mouse * pmouse = canew(::message::mouse(get_app()));
      
      pmouse->m_uiMessage = WM_LBUTTONUP;
      pmouse->m_pt.x = (LONG) x;
      pmouse->m_pt.y = (LONG) y;
      pmouse->m_bTranslated = true;
//      pmouse->m_bTranslateMouseMessageCursor = true;
      
      spbase = pmouse;
      
      send(spbase);
      
   }

   
   void window::round_window_mouse_moved(double x, double y)
   {
      
      sp(::message::base) spbase;
      
      ::message::mouse * pmouse = canew(::message::mouse(get_app()));
      
      pmouse->m_uiMessage = WM_MOUSEMOVE;
      pmouse->m_pt.x = (LONG) x;
      pmouse->m_pt.y = (LONG) y;
      pmouse->m_bTranslated = true;
//      pmouse->m_bTranslateMouseMessageCursor = true;
      
      spbase = pmouse;
      
      send(spbase);
      
   }
   
   
   void window::round_window_mouse_dragged(double x, double y)
   {
      
      sp(::message::base) spbase;
      
      ::message::mouse * pmouse = canew(::message::mouse(get_app()));
      
      pmouse->m_uiMessage = WM_MOUSEMOVE;
      pmouse->m_pt.x = (LONG) x;
      pmouse->m_pt.y = (LONG) y;
      pmouse->m_bTranslated = true;
      //      pmouse->m_bTranslateMouseMessageCursor = true;
      
      spbase = pmouse;
      
      send(spbase);
      
   }
   
   
   
   
} // namespace mac



/////////////////////////////////////////////////////////////////////////////
// Map from oswindow to ::window *

hwnd_map* PASCAL afxMapHWND(bool bCreate)
{
   UNREFERENCED_PARAMETER(bCreate);
   try
   {
      __MODULE_STATE* pState = __get_module_state();
      if(pState == NULL)
         return NULL;
      return pState->m_pmapHWND;
   }
   catch(...)
   {
      return NULL;
   }
}


mutex * PASCAL afxMutexHwnd()
{
   try
   {
      __MODULE_STATE* pState = __get_module_state();
      if(pState == NULL)
         return NULL;
      return pState->m_pmutexHwnd;
   }
   catch(...)
   {
      return NULL;
   }
}

/////////////////////////////////////////////////////////////////////////////
// The WndProc for all window's and derived classes

#undef __window_procedure

LRESULT CALLBACK __window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam)
{
   // special message which identifies the window as using __window_procedure
//   if (nMsg == WM_QUERYAFXWNDPROC)
  //    return 1;
   
   throw not_implemented(::get_thread_app());
   
   //   // all other messages route through message ::collection::map
   //   ::window * pWnd = ::mac::window::FromHandlePermanent(hWnd);
   //   //ASSERT(pWnd != NULL);
   //   //ASSERT(pWnd==NULL || MAC_WINDOW(pWnd)->get_handle() == hWnd);
   //   if (pWnd == NULL || MAC_WINDOW(pWnd)->get_handle() != hWnd)
   //      return ::DefWindowProc(hWnd, nMsg, wparam, lparam);
   //   return mac::__call_window_procedure(pWnd, hWnd, nMsg, wparam, lparam);
}

// always indirectly accessed via __get_window_procedure
//WNDPROC CLASS_DECL_mac __get_window_procedure()
//{
//   return __get_module_state()->m_pfn_window_procedure;
//}
/////////////////////////////////////////////////////////////////////////////
// Special helpers for certain windows messages

__STATIC void CLASS_DECL_mac __pre_init_dialog(
                                               ::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld)
{
   ASSERT(lpRectOld != NULL);
   ASSERT(pdwStyleOld != NULL);
   
   MAC_WINDOW(pWnd)->GetWindowRect(lpRectOld);
   *pdwStyleOld = MAC_WINDOW(pWnd)->GetStyle();
}

__STATIC void CLASS_DECL_mac __post_init_dialog(
                                                ::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld)
{
   // must be hidden to start with
   if (dwStyleOld & WS_VISIBLE)
      return;
   
   // must not be visible after WM_INITDIALOG
   if (MAC_WINDOW(pWnd)->GetStyle() & (WS_VISIBLE|WS_CHILD))
      return;
   
   // must not move during WM_INITDIALOG
   rect rect;
   MAC_WINDOW(pWnd)->GetWindowRect(rect);
   if (rectOld.left != rect.left || rectOld.top != rect.top)
      return;
   
   // must be unowned or owner disabled
   ::user::interaction * pParent = MAC_WINDOW(pWnd)->GetWindow(GW_OWNER);
   if (pParent != NULL && pParent->is_window_enabled())
      return;
   
   if (!MAC_WINDOW(pWnd)->CheckAutoCenter())
      return;
   
   // center modal dialog boxes/message boxes
   //MAC_WINDOW(pWnd)->CenterWindow();
}



CLASS_DECL_mac void hook_window_create(::user::interaction * pWnd)
{
   
   //      throw not_implemented(::get_thread_app());
   ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
   if (pThreadState->m_pWndInit == pWnd)
      return;
   
   //   if (pThreadState->m_hHookOldCbtFilter == NULL)
   //   {
   //      pThreadState->m_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT,
   //         mac::__cbt_filter_hook, NULL, ::GetCurrentThreadId());
   //      if (pThreadState->m_hHookOldCbtFilter == NULL)
   //         throw memory_exception();
   //   }
   //   ASSERT(pThreadState->m_hHookOldCbtFilter != NULL);
   //   ASSERT(pWnd != NULL);
   //   // trans   ASSERT(MAC_WINDOW(pWnd)->get_handle() == NULL);   // only do once
   //
   ASSERT(pThreadState->m_pWndInit == NULL);   // hook not already in progress
   //pThreadState->m_pWndInit = pWnd;
}


CLASS_DECL_mac bool unhook_window_create()
{
   ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
   if (pThreadState->m_pWndInit != NULL)
   {
      pThreadState->m_pWndInit = NULL;
      return FALSE;   // was not successfully hooked
   }
   return TRUE;
}



CLASS_DECL_mac const char * __register_window_class(UINT nClassStyle,
                                                    HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
{
   
   return NULL;
   
   throw not_implemented(::get_thread_app());
   
   //   // Returns a temporary string name for the class
   //   //  Save in a string if you want to use it for a long time
   //   LPTSTR lpszName = __get_thread_state()->m_szTempClassName;
   //
   //   // generate a synthetic name for this class
   //   HINSTANCE hInst = Sys(::mac::get_thread()->m_pbaseapp->m_pplaneapp).m_hInstance;
   //
   //   if (hCursor == NULL && hbrBackground == NULL && hIcon == NULL)
   //   {
   //      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, "::ca2:::%p:%x", hInst, nClassStyle));
   //   }
   //   else
   //   {
   //      C_RUNTIME_ERRORCHECK_SPRINTF(_sntprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, "::ca2:::%p:%x:%p:%p:%p", hInst, nClassStyle,
   //         hCursor, hbrBackground, hIcon));
   //   }
   //
   //   // see if the class already exists
   //   WNDCLASS wndcls;
   //   if (::GetClassInfo(hInst, lpszName, &wndcls))
   //   {
   //      // already registered, assert everything is good
   //      ASSERT(wndcls.style == nClassStyle);
   //
   //      // NOTE: We have to trust that the hIcon, hbrBackground, and the
   //      //  hCursor are semantically the same, because sometimes oswindows does
   //      //  some internal translation or copying of those handles before
   //      //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
   //      return lpszName;
   //   }
   //
   //   // otherwise we need to register a new class
   //   wndcls.style = nClassStyle;
   //   wndcls.lpfnWndProc = DefWindowProc;
   //   wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
   //   wndcls.hInstance = hInst;
   //   wndcls.hIcon = hIcon;
   //   //wndcls.hCursor = hCursor;
   //   wndcls.hCursor = NULL;
   //   wndcls.hbrBackground = hbrBackground;
   //   wndcls.lpszMenuName = NULL;
   //   wndcls.lpszClassName = lpszName;
   //   if (!__register_class(&wndcls))
   //      throw resource_exception();
   //
   //   // return thread-local pointer
   //   return lpszName;
}


__STATIC void CLASS_DECL_mac
__handle_activate(::window * pWnd, WPARAM nState, ::window * pWndOther)
{
   
   throw not_implemented(::get_thread_app());
   //   ASSERT(pWnd != NULL);
   //
   //   // send WM_ACTIVATETOPLEVEL when top-level parents change
   //   if (!(MAC_WINDOW(pWnd)->GetStyle() & WS_CHILD))
   //   {
   //      ::user::interaction * pTopLevel= MAC_WINDOW(pWnd)->GetTopLevelParent();
   //      if (pTopLevel && (pWndOther == NULL || !::IsWindow(MAC_WINDOW(pWndOther)->get_handle()) || pTopLevel != MAC_WINDOW(pWndOther)->GetTopLevelParent()))
   //      {
   //         // lparam points to window getting the WM_ACTIVATE message and
   //         //  hWndOther from the WM_ACTIVATE.
   //         oswindow hWnd2[2];
   //         hWnd2[0] = MAC_WINDOW(pWnd)->get_handle();
   //         if(pWndOther == NULL || MAC_WINDOW(pWndOther) == NULL)
   //         {
   //            hWnd2[1] = NULL;
   //         }
   //         else
   //         {
   //            hWnd2[1] = MAC_WINDOW(pWndOther)->get_handle();
   //         }
   //         // send it...
   //         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (LPARAM)&hWnd2[0]);
   //      }
   //   }
}

__STATIC bool CLASS_DECL_mac
__handle_set_cursor(::window * pWnd, UINT nHitTest, UINT nMsg)
{
   
   throw not_implemented(::get_thread_app());
   //   if (nHitTest == HTERROR &&
   //      (nMsg == WM_LBUTTONDOWN || nMsg == WM_MBUTTONDOWN ||
   //      nMsg == WM_RBUTTONDOWN))
   //   {
   //      // activate the last active window if not active
   //      ::user::interaction * pLastActive = MAC_WINDOW(pWnd)->GetTopLevelParent();
   //      if (pLastActive != NULL)
   //         pLastActive = pLastActive->GetLastActivePopup();
   //      if (pLastActive != NULL &&
   //         pLastActive != ::mac::window::GetForegroundWindow() &&
   //         pLastActive->IsWindowEnabled())
   //      {
   //         pLastActive->SetForegroundWindow();
   //         return TRUE;
   //      }
   //   }
   //   return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// Standard init called by WinMain

//__STATIC bool CLASS_DECL_mac __register_with_icon(WNDCLASS* pWndCls,
//                                                  const char * lpszClassName, UINT nIDIcon)
//{
//   pWndCls->lpszClassName = lpszClassName;
//   pWndCls->hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
//   return __register_class(pWndCls);
//}


//bool CLASS_DECL_mac __end_defer_register_class(LONG fToRegisterParam, const char ** ppszClass)
//{
//   // mask off all classes that are already registered
//   __MODULE_STATE* pModuleState = __get_module_state();
//   LONG fToRegister = fToRegisterParam & ~pModuleState->m_fRegisteredClasses;
//   if (fToRegister == 0)
//   {
//      fToRegister = fToRegisterParam;
//      if(ppszClass != NULL)
//      {
//         if(fToRegister & __WND_REG)
//         {
//            *ppszClass = gen_Wnd;
//         }
//         else if (fToRegister & __WNDOLECONTROL_REG)
//         {
//            *ppszClass = gen_WndOleControl;
//         }
//         else if (fToRegister & __WNDCONTROLBAR_REG)
//         {
//            *ppszClass = gen_WndControlBar;
//         }
//         else if(fToRegister & __WNDMDIFRAME_REG)
//         {
//            *ppszClass = gen_WndMDIFrame;
//         }
//         else if(fToRegister & __WNDFRAMEORVIEW_REG)
//         {
//            *ppszClass = gen_WndFrameOrView;
//         }
//      }
//      return TRUE;
//   }
//
//   LONG fRegisteredClasses = 0;
//
//   // common initialization
//   WNDCLASS wndcls;
//   memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL defaults
//   wndcls.lpfnWndProc = DefWindowProc;
//   wndcls.hInstance = Sys(::mac::get_thread()->m_pbaseapp->m_pplaneapp).m_hInstance;
//   //wndcls.hCursor = afxData.hcurArrow;
//
//   INITCOMMONCONTROLSEX init;
//   init.dwSize = sizeof(init);
//
//   // work to register classes as specified by fToRegister, populate fRegisteredClasses as we go
//   if (fToRegister & __WND_REG)
//   {
//      // Child windows - no brush, no icon, safest default class styles
//      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
//      wndcls.lpszClassName = gen_Wnd;
//      if (__register_class(&wndcls))
//      {
//         if(ppszClass != NULL)
//         {
//            *ppszClass = wndcls.lpszClassName;
//         }
//         fRegisteredClasses |= __WND_REG;
//      }
//   }
//   if (fToRegister & __WNDOLECONTROL_REG)
//   {
//      // OLE control windows - use parent DC for speed
//      wndcls.style |= CS_PARENTDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
//      wndcls.lpszClassName = gen_WndOleControl;
//      if (__register_class(&wndcls))
//      {
//         if(ppszClass != NULL)
//         {
//            *ppszClass = wndcls.lpszClassName;
//         }
//         fRegisteredClasses |= __WNDOLECONTROL_REG;
//      }
//   }
//   if (fToRegister & __WNDCONTROLBAR_REG)
//   {
//      // control bar windows
//      wndcls.style = 0;   // control bars don't handle double click
//      wndcls.lpszClassName = gen_WndControlBar;
//      wndcls.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
//      if (__register_class(&wndcls))
//      {
//         if(ppszClass != NULL)
//         {
//            *ppszClass = wndcls.lpszClassName;
//         }
//         fRegisteredClasses |= __WNDCONTROLBAR_REG;
//      }
//   }
//   if (fToRegister & __WNDMDIFRAME_REG)
//   {
//      // MDI Frame window (also used for splitter window)
//      wndcls.style = CS_DBLCLKS;
//      wndcls.hbrBackground = NULL;
//      /*      if (__register_with_icon(&wndcls, gen_WndMDIFrame, __IDI_STD_MDIFRAME))
//      {
//      if(ppszClass != NULL)
//      {
//      *ppszClass = gen_WndMDIFrame;
//      }
//      fRegisteredClasses |= __WNDMDIFRAME_REG;
//      }*/
//   }
//   if (fToRegister & __WNDFRAMEORVIEW_REG)
//   {
//      // SDI Frame or MDI Child windows or views - normal colors
//      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
//      wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
//      if (__register_with_icon(&wndcls, gen_WndFrameOrView, 123))
//      {
//         if(ppszClass != NULL)
//         {
//            *ppszClass = gen_WndFrameOrView;
//         }
//         fRegisteredClasses |= __WNDFRAMEORVIEW_REG;
//      }
//   }
//
//
//   // save new state of registered controls
//   pModuleState->m_fRegisteredClasses |= fRegisteredClasses;
//
//   // special case for all common controls registered, turn on __WNDCOMMCTLS_REG
//   if ((pModuleState->m_fRegisteredClasses & __WIN95CTLS_MASK) == __WIN95CTLS_MASK)
//   {
//      pModuleState->m_fRegisteredClasses |= __WNDCOMMCTLS_REG;
//      fRegisteredClasses |= __WNDCOMMCTLS_REG;
//   }
//
//   // must have registered at least as mamy classes as requested
//   return (fToRegister & fRegisteredClasses) == fToRegister;
//}


/////////////////////////////////////////////////////////////////////////////
// Special WndProcs (activation handling & gray dialogs)


LRESULT CALLBACK
__activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam)
{
   
   throw not_implemented(::get_thread_app());
   //   WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, gen_OldWndProc);
   //   ASSERT(oldWndProc != NULL);
   //
   //   LRESULT lResult = 0;
   //   try
   //   {
   //      bool bCallDefault = TRUE;
   //      switch (nMsg)
   //      {
   //      case WM_INITDIALOG:
   //         {
   //            DWORD dwStyle;
   //            rect rectOld;
   //            ::window * pWnd = ::mac::window::from_handle(hWnd);
   //            __pre_init_dialog(pWnd, &rectOld, &dwStyle);
   //            bCallDefault = FALSE;
   //            lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
   //            __post_init_dialog(pWnd, rectOld, dwStyle);
   //         }
   //         break;
   //
   //      case WM_ACTIVATE:
   //         __handle_activate(::mac::window::from_handle(hWnd), wparam,
   //            ::mac::window::from_handle((oswindow)lparam));
   //         break;
   //
   //      case WM_SETCURSOR:
   //         bCallDefault = !__handle_set_cursor(::mac::window::from_handle(hWnd),
   //            (short)LOWORD(lparam), HIWORD(lparam));
   //         break;
   //
   //      case WM_NCDESTROY:
   //         SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<int_ptr>(oldWndProc));
   //         RemoveProp(hWnd, gen_OldWndProc);
   //         GlobalDeleteAtom(GlobalFindAtom(gen_OldWndProc));
   //         break;
   //      }
   //
   //      // call original wndproc for default handling
   //      if (bCallDefault)
   //         lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
   //   }
   //   catch(::exception::base * pe)
   //   {
   //      // handle exception
   //      MESSAGE msg;
   //      msg.hwnd = hWnd;
   //      msg.message = nMsg;
   //      msg.wparam = wparam;
   //      msg.lparam = lparam;
   //
   //      //lResult = __process_window_procedure_exception(pe, &msg);
   //      //      TRACE(::ca2::trace::category_AppMsg, 0, "Warning: Uncaught exception in __activation_window_procedure (returning %ld).\n",
   //      //       lResult);
   //      pe->Delete();
   //   }
   //
   //
   //   return lResult;
}




/////////////////////////////////////////////////////////////////////////////
// Additional helpers for WNDCLASS init

// like RegisterClass, except will automatically call UnregisterClass
//bool CLASS_DECL_mac __register_class(WNDCLASS* lpWndClass)
//{
//   WNDCLASS wndcls;
//   if (GetClassInfo(lpWndClass->hInstance, lpWndClass->lpszClassName,
//      &wndcls))
//   {
//      // class already registered
//      return TRUE;
//   }
//
//   if (!::RegisterClass(lpWndClass))
//   {
//      //      TRACE(::ca2::trace::category_AppMsg, 0, "Can't register window class named %s\n",
//      //       lpWndClass->lpszClassName);
//      return FALSE;
//   }
//
//   bool bRet = TRUE;
//
//   if (afxContextIsDLL)
//   {
//
//      try
//      {
//         // class registered successfully, add to registered list
//         __MODULE_STATE* pModuleState = __get_module_state();
//         single_lock sl(&pModuleState->m_mutexRegClassList, TRUE);
//         if(pModuleState->m_pstrUnregisterList == NULL)
//            pModuleState->m_pstrUnregisterList = new string;
//         *pModuleState->m_pstrUnregisterList += lpWndClass->lpszClassName;
//         *pModuleState->m_pstrUnregisterList +='\n';
//      }
//      catch(::exception::base * pe)
//      {
//         ::exception::rethrow(pe);
//         // Note: DELETE_EXCEPTION not required.
//      }
//
//   }
//
//   return bRet;
//}


//#u//ndef new
//#include <gdiplus.h>


namespace mac
{
   
   /*   void window::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
    {
    
    
    }*/
   
   void window::_001UpdateWindow()
   {
      
      ::window::_001UpdateWindow();
      
   }
   
   void window::offset_view_port_org(LPRECT lprectScreen)
   {
   }

   
   void window::set_view_port_org(::draw2d::graphics * pgraphics)
   {
      // graphics will be already set its view port to the window for linux - cairo with xlib
      
      pgraphics->SetViewportOrg(point(0, 0));
      
      /*      rect64 rectWindow;
       GetWindowRect(rectWindow);
       get_wnd()->ScreenToClient(rectWindow);
       pgraphics->SetViewportOrg(point(rectWindow.top_left()));
       pgraphics->SelectClipRgn(NULL);
       */
      
   }
   
   
}



