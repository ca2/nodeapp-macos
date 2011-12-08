#pragma once

namespace user
{
   class ::user::window_interface;
} // namespace user

namespace win
{

   class CLASS_DECL_VMSWIN window_draw : 
      virtual public ::ca::window_draw,
      virtual public ::ca::message_window_simple_callback
   {
   public:


      enum EOptimize
      {
         OptimizeNone,
         OptimizeThis,
         OptimizeAllNext,
      };

      user::LPWndArray                       m_wndpaOut;
      user::window_draw_client_tool          m_twrenderclienttool;
      mutex                                  m_mutexRendering;
      mutex                                  m_mutexRgnUpdate;
      semaphore                              m_semaphoreBuffer;
      bool                                   m_bRender;
      DWORD                                  m_dwLastRedrawRequest;
      mutex                                  m_mutexRender;
      critical_section                       m_csWndInterfaceMap;
      typed_pointer_map <
         CMapPtrToPtr,
         HWND, 
         ::user::window_interface *>
                                             m_wndinterfacemap;
      DWORD                                  m_dwLastUpdate;


      window_draw(::ca::application * papp);
      virtual ~window_draw();


      virtual bool start();

      bool UpdateBuffer(LPCRECT lpcrect);
      //void OnPaint(HWND hwnd, CPaintDC & spgraphics);

      semaphore * TwfGetBufferSemaphore();

      // Bit blitting spread functions
      virtual bool ScreenOutput(
         user::buffer *,
         ::ca::rgn & rgnUpdate);

      virtual bool ScreenOutput();

      virtual bool ScreenOutput(
         user::buffer *,
         ::user::interaction* pwnd,
         ::ca::rgn & rgnUpdate);

      // Transparent drawing operations
      // controllers
      virtual bool UpdateBuffer();

      virtual bool to(
         ::ca::graphics *       pdc,
         LPCRECT     lprectUpdate,
         user::HwndTree & hwndtree,
         bool        bGdiLocked,
         bool        bExcludeParamWnd);

      virtual bool to(
         ::ca::graphics *       pdc,
         LPCRECT     lprectUpdate,
         user::HwndTree::Array & hwndtreea,
         bool        bGdiLocked,
         bool        bExcludeParamWnd);

   /*     EOptimize TwfOptimizeRender2(
         user::HwndTree::Array & hwndtreea,
         LPCRECT lpcrect);

      EOptimize TwfOptimizeRender2(
         user::HwndTree & hwndtree,
         LPCRECT lpcrect);*/


      EOptimize TwfOptimizeRender(
         user::HwndTree::Array & hwndtreea,
         LPCRECT lpcrect);

      EOptimize TwfOptimizeRender(
         user::HwndTree & hwndtree,
         LPCRECT lpcrect);

      void TwfGetTopWindow(
         HWND hwnd,
         user::HWNDArray & hwnda,
         base_array < HRGN, HRGN > & hrgna,
         user::HwndTree::Array & hwndtreea,
         LPCRECT lpcrect);

      bool TwfGetTopWindow(
         HWND hwnd,
         user::HWNDArray & hwnda,
         base_array < HRGN, HRGN > & hrgna,
         user::HwndTree::Array & hwndtreea,
         HRGN hrgn);

      bool TwfGetTopWindow(
         HWND hwnd,
         user::HWNDArray & hwnda,
         base_array < HRGN, HRGN > & hrgna,
         user::HwndTree & hwndtree,
         HRGN hrgn);

      void TwfGetTopWindowOptimizeOpaque(
         HWND hwndOpaque,
         user::HWNDArray & hwnda,
         base_array < HRGN, HRGN > & hrgna);


      EOptimize TwfOptimizeRenderRemoveNextProper(
         user::HwndTree::Array & hwndtreea,
         int iIndex,
         LPCRECT lpcrect);

      void get_wnda(user::LPWndArray & wndpa);
      void get_wnda(user::HWNDArray & hwnda);
      
      static UINT AFX_CDECL ThreadProcRedraw(LPVOID lpv);

      virtual UINT RedrawProc();

      virtual void asynch_redraw();
      virtual void _asynch_redraw();
      virtual void synch_redraw();
      virtual void _synch_redraw();

      virtual void message_window_message_handler(gen::signal_object * pobj);

   };

} // namespace win