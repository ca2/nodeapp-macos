#pragma once


#include "round_window.h"


namespace mac
{
   
   
   CLASS_DECL_mac LRESULT CALLBACK __send_message_hook(int32_t, WPARAM, LPARAM);
   //CLASS_DECL_lnx void _gen::StandardSubclass(oswindow);
   CLASS_DECL_mac LRESULT CALLBACK __cbt_filter_hook(int32_t, WPARAM, LPARAM);
   CLASS_DECL_mac LRESULT __call_window_procedure(sp(::user::interaction)  pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
   
   
   class CLASS_DECL_mac window :
      virtual public ::window,
      virtual public ::round_window
   {
   public:
      
      
      spa(::user::interaction)      m_guieptraMouseHover;
      ::message_queue_listener *   m_pcallback;
      string                        m_strWindowText;
      oswindow                      m_oswindow;
      ::user::window_interface *    m_pbasewnd;
      sp(::user::interaction)       m_pguieCapture;
      bool                          m_bNeedsUpdate;
      
      //visual::dib_sp              m_spdib;
      //visual::dib_sp              m_spdibMultAlphaWork;
      
      
      window();
      window(base_application * papp);
      virtual void construct(oswindow hwnd);
      
//      virtual void on_delete(::ca2::ca2 * poc);
      
      virtual void mouse_hover_add(sp(::user::interaction)  pinterface);
      virtual void mouse_hover_remove(sp(::user::interaction)  pinterface);
      
      virtual bool create_message_queue(const char * pszName, ::message_queue_listener * pcallback = NULL);
      
      static const MESSAGE* PASCAL GetCurrentMessage();
      
      virtual void install_message_handling(::message::dispatch * pinterface);
      
      bool operator==(const ::window& wnd) const;
      bool operator!=(const ::window& wnd) const;
      
      DWORD GetStyle();
      DWORD GetExStyle();
      bool ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      bool ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      
      //virtual sp(::user::interaction)  GetOwner();
      virtual void set_owner(sp(::user::interaction)  pOwnerWnd);
      
      virtual oswindow get_handle() const;
      
      virtual sp(::window) get_wnd() const;
      
      virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);
      
      virtual bool BaseOnControlEvent(::user::control_event * pevent);
      
      void _002OnDraw(::draw2d::graphics * pdc);
      
       DECL_GEN_SIGNAL(_001OnEraseBkgnd);
       DECL_GEN_SIGNAL(_001OnMove);
       DECL_GEN_SIGNAL(_001OnSize);
       DECL_GEN_SIGNAL(_001OnShowWindow);
       DECL_GEN_SIGNAL(_001OnProdevianSynch);
      
      
#if(WINVER >= 0x0500)
      
      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
      
#endif   // WINVER >= 0x0500
      
      virtual sp(::window) from_os_data(void * pdata);
      virtual void * get_os_data() const;
      
      static window * from_handle(oswindow hWnd);
      static window * FromHandlePermanent(oswindow hWnd);
      //static void DeleteTempMap();
      bool Attach(oswindow hWndNew);
      oswindow Detach();
      
      // subclassing/unsubclassing functions
      virtual void pre_subclass_window();
      bool SubclassWindow(oswindow hWnd);
      //bool SubclassDlgItem(UINT nID, ::window * pParent);
      oswindow UnsubclassWindow();
      
      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName);
      bool ExecuteDlgInit(LPVOID lpResource);
      
      using ::user::interaction::create;
      // for child windows, views, panes etc
      virtual bool create(const char * lpszClassName,
                          const char * lpszWindowName, DWORD dwStyle,
                          const RECT& rect,
                          sp(::user::interaction)  pParentWnd, id id,
                          ::create_context * pContext = NULL);
      
      // advanced creation (allows access to extended styles)
      virtual bool CreateEx(DWORD dwExStyle, const char * lpszClassName,
                            const char * lpszWindowName, DWORD dwStyle,
                            int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
                            oswindow hWndParent, id id, LPVOID lpParam = NULL);
      
      virtual bool CreateEx(DWORD dwExStyle, const char * lpszClassName,
                            const char * lpszWindowName, DWORD dwStyle,
                            const RECT& rect,
                            sp(::user::interaction)  pParentWnd, id id,
                            LPVOID lpParam = NULL);
      
      virtual bool DestroyWindow();
      
      // special pre-creation and ::window rect adjustment hooks
      virtual bool pre_create_window(CREATESTRUCT& cs);
      
      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
      
      
      // get immediate child with given ID
      using ::user::interaction::get_child_by_id;
      void get_child_by_id(id id, oswindow* phWnd) const;
      // as above, but returns oswindow
      using ::user::interaction::GetDescendantWindow;
      sp(::user::interaction) GetDescendantWindow(id id);
      // like get_child_by_id but recursive
      void SendMessageToDescendants(UINT message, WPARAM wParam = 0,
                                    lparam lParam = NULL, bool bDeep = TRUE, bool bOnlyPerm = FALSE);
      sp(::user::frame_window) GetParentFrame();
      sp(::user::frame_window) EnsureParentFrame();
      sp(::user::interaction) GetTopLevelParent();
      sp(::user::interaction) EnsureTopLevelParent();
      sp(::user::interaction) GetTopLevelOwner();
      sp(::user::interaction) GetParentOwner();
      sp(::user::frame_window) GetTopLevelFrame();
      static ::window * PASCAL GetSafeOwner(::window * pParent = NULL, oswindow* pWndTop = NULL);
      
      virtual bool IsWindow();
      
#if(WINVER >= 0x0500)
      
      ::window * GetAncestor(UINT gaFlags) const;
      
#endif   // WINVER >= 0x0500
      
      LRESULT send_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
      bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
      
      bool SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam);
      bool SendChildNotifyLastMsg(LRESULT* pResult = NULL);
      
      bool DragDetect(POINT pt) const;
      
      
      
      // oswindow Text Functions
      void SetWindowText(const char * lpszString);
      strsize GetWindowText(LPTSTR lpszStringBuf, strsize nMaxCount);
      void GetWindowText(string & rString);
      strsize GetWindowTextLength();
      void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      ::draw2d::font* GetFont();
      
      
      // oswindow size and position Functions
      virtual bool WfiIsIconic();
      virtual bool WfiIsZoomed();
      void MoveWindow(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight,
                      bool bRepaint = TRUE);
      void MoveWindow(LPCRECT lpRect, bool bRepaint = TRUE);
      int32_t SetWindowRgn(HRGN hRgn, bool bRedraw);
      int32_t GetWindowRgn(HRGN hRgn);
      
      //static const ::window wndTop; // SetWindowPos's pWndInsertAfter
      //static const ::window wndBottom; // SetWindowPos's pWndInsertAfter
      //static const ::window wndTopMost; // SetWindowPos pWndInsertAfter
      //static const ::window wndNoTopMost; // SetWindowPos pWndInsertAfter
      
      virtual bool SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags);
      virtual UINT ArrangeIconicWindows();
      virtual bool BringWindowToTop();
      using interaction::GetWindowRect;
      virtual void GetWindowRect(__rect64 * lpRect);
      using interaction::GetClientRect;
      virtual void GetClientRect(__rect64 * lpRect);
      
      void ClientToScreen(LPRECT lprect);
      void ClientToScreen(LPPOINT lppoint);
      void ClientToScreen(__rect64 * lprect);
      void ClientToScreen(__point64 * lppoint);
      void ScreenToClient(LPRECT lprect);
      void ScreenToClient(LPPOINT lppoint);
      void ScreenToClient(__rect64 * lprect);
      void ScreenToClient(__point64 * lppoint);
      
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);
      
      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::window * pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::window * pwndTo, LPRECT lpRect);
      
      // Update/Painting Functions
      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      virtual bool ReleaseDC(::draw2d::graphics * pgraphics);
      virtual void Print(::draw2d::graphics * pgraphics, DWORD dwFlags) const;
      virtual void PrintClient(::draw2d::graphics * pgraphics, DWORD dwFlags) const;
      
      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(LPRECT lpRect, bool bErase = FALSE);
      virtual int32_t GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE);
      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect, bool bErase = TRUE);
      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool ShowWindow(int32_t nCmdShow);
      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual bool IsWindowVisible();
      virtual void ShowOwnedPopups(bool bShow = TRUE);
      
      virtual void round_window_draw(CGContextRef cgc);
      virtual void round_window_mouse_down(double x, double y);
      virtual void round_window_mouse_up(double x, double y);
      virtual void round_window_mouse_moved(double x, double y);
      virtual void round_window_mouse_dragged(double x, double y);
      virtual bool round_window_key_down(::user::e_key ekey);
      virtual bool round_window_key_up(::user::e_key ekey);
      
      
      void set_view_port_org(::draw2d::graphics * pgraphics);
      void offset_view_port_org(LPRECT lprectScreen);
      
      
      virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, DWORD flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();
      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,
                                ::draw2d::region* prgnUpdate = NULL,
                                UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
      // xxx      virtual bool EnableScrollBar(int32_t nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);
      
      virtual bool DrawAnimatedRects(int32_t idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo);
      virtual bool DrawCaption(::draw2d::graphics * pgraphics, LPCRECT lprc, UINT uFlags);
      
#if(WINVER >= 0x0500)
      
      virtual bool AnimateWindow(DWORD dwTime, DWORD dwFlags);
      
#endif   // WINVER >= 0x0500
      
#if(_WIN32_WINNT >= 0x0501)
      
      virtual bool PrintWindow(::draw2d::graphics * pgraphics, UINT nFlags) const;
      
#endif   // _WIN32_WINNT >= 0x0501
      
      // Layered oswindow
      
#if(_WIN32_WINNT >= 0x0500)
      
      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
      
#endif   // _WIN32_WINNT >= 0x0500
      
#if(_WIN32_WINNT >= 0x0501)
      
      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;
      
#endif   // _WIN32_WINNT >= 0x0501
      
      
      // Timer Functions
      virtual uint_ptr SetTimer(uint_ptr nIDEvent, UINT nElapse,
                                void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, DWORD));
      virtual bool KillTimer(uint_ptr nIDEvent);
      
      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = TRUE);
      
      // the active ::window applies only to top-level (frame windows)
      virtual sp(::user::interaction) GetActiveWindow();
      virtual sp(::user::interaction) SetActiveWindow();
      
      // the foreground ::window applies only to top-level windows (frame windows)
      virtual bool SetForegroundWindow();
      static ::window * PASCAL GetForegroundWindow();
      
      virtual id SetDlgCtrlId(id id);
      virtual id GetDlgCtrlId();
      
      
      
      // capture and focus apply to all windows
      static ::window * PASCAL GetCapture();
      virtual sp(::user::interaction)  set_capture(sp(::user::interaction)  pinterface = NULL);
      virtual sp(::user::interaction) release_capture();
      virtual sp(::user::interaction) get_capture();
      static ::window * PASCAL GetFocus();
      sp(::user::interaction) SetFocus();
      
      static ::window * PASCAL GetDesktopWindow();
      
      // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual bool OpenIcon();
      
      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(int32_t nIDButton, UINT nCheck);
      virtual void CheckRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton,
                                    int32_t nIDCheckButton);
      virtual int32_t GetCheckedRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton);
      virtual int32_t DlgDirList(LPTSTR lpPathSpec, int32_t nIDListBox,
                                 int32_t nIDStaticPath, UINT nFileType);
      virtual int32_t DlgDirListComboBox(LPTSTR lpPathSpec, int32_t nIDComboBox,
                                         int32_t nIDStaticPath, UINT nFileType);
      virtual bool DlgDirSelect(LPTSTR lpString, int32_t nSize, int32_t nIDListBox);
      virtual bool DlgDirSelectComboBox(LPTSTR lpString, int32_t nSize, int32_t nIDComboBox);
      
      //virtual UINT GetChildByIdInt(int32_t nID, bool * lpTrans = NULL, bool bSigned = TRUE) const;
      //virtual int32_t GetChildByIdText(int32_t nID, LPTSTR lpStr, int32_t nMaxCount) const;
      //virtual int32_t GetChildByIdText(int32_t nID, string & rString) const;
      virtual ::window * GetNextDlgGroupItem(::window * pWndCtl, bool bPrevious = FALSE) const;
      virtual ::window * GetNextDlgTabItem(::window * pWndCtl, bool bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(int32_t nIDButton) const;
      virtual LRESULT SendDlgItemMessage(int32_t nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(int32_t nID, UINT nValue, bool bSigned = TRUE);
      virtual void SetDlgItemText(int32_t nID, const char * lpszString);
      
      // Scrolling Functions
      virtual int32_t GetScrollPos(int32_t nBar) const;
      virtual void GetScrollRange(int32_t nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
      virtual void ScrollWindow(int32_t xAmount, int32_t yAmount,
                                LPCRECT lpRect = NULL,
                                LPCRECT lpClipRect = NULL);
      virtual int32_t SetScrollPos(int32_t nBar, int32_t nPos, bool bRedraw = TRUE);
      virtual void SetScrollRange(int32_t nBar, int32_t nMinPos, int32_t nMaxPos,
                                  bool bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE);
      virtual void EnableScrollBarCtrl(int32_t nBar, bool bEnable = TRUE);
//      virtual CScrollBar* GetScrollBarCtrl(int32_t nBar) const;
      // return sibling scrollbar control (or NULL if none)
      
      virtual int32_t ScrollWindowEx(int32_t dx, int32_t dy,
                                     LPCRECT lpRectScroll, LPCRECT lpRectClip,
                                     ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
      //xxx      virtual bool SetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo,
      //xxx         bool bRedraw = TRUE);
      //xxx      virtual bool GetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
      virtual int32_t GetScrollLimit(int32_t nBar);
      
#if(WINVER >= 0x0500)
      
      virtual bool GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;
      
#endif   // WINVER >= 0x0500
      
      // oswindow Access Functions
      virtual sp(::user::interaction) ChildWindowFromPoint(POINT point);
      virtual sp(::user::interaction) ChildWindowFromPoint(POINT point, UINT nFlags);
      static ::window * PASCAL FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static ::window * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
      
      virtual sp(::user::interaction) GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual sp(::user::interaction) GetTopWindow();
      
      virtual sp(::user::interaction) GetWindow(UINT nCmd);
      virtual sp(::user::interaction) GetLastActivePopup();
      
      virtual bool IsChild(sp(::user::interaction)   pWnd);
      virtual sp(::user::interaction) get_parent() const;
      using ::user::interaction::set_parent;
      ::window * set_parent(::window * pWndNewParent);
      static ::window * PASCAL oswindowFromPoint(POINT point);
      
      // Alert Functions
      
      bool FlashWindow(bool bInvert);
      
      virtual int32_t message_box(const char * lpszText, const char * lpszCaption = NULL, UINT nType = MB_OK);
      
      
#if(WINVER >= 0x0500)
      
      virtual bool FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout);
      
#endif   // WINVER >= 0x0500
      
      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext);
      virtual oswindow  SetClipboardViewer();
      virtual bool OpenClipboard();
      static ::window * PASCAL GetClipboardOwner();
      static ::window * PASCAL GetClipboardViewer();
      static ::window * PASCAL GetOpenClipboardWindow();
      
      // Caret Functions
      virtual void CreateCaret(::draw2d::bitmap* pBitmap);
      virtual void CreateSolidCaret(int32_t nWidth, int32_t nHeight);
      virtual void CreateGrayCaret(int32_t nWidth, int32_t nHeight);
      static point PASCAL GetCaretPos();
      static void PASCAL SetCaretPos(POINT point);
      virtual void HideCaret();
      virtual void ShowCaret();
      
      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = TRUE);
      
      // icon Functions
      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
      virtual HICON GetIcon(bool bBigIcon) const;
      
      // Context Help Functions
      virtual bool SetWindowContextHelpId(DWORD dwContextHelpId);
      virtual DWORD GetWindowContextHelpId() const;
      
      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this
      
      // Help Command Handlers
      void OnHelp();          // F1 (uses current context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      // xxx virtual void WinHelp(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);
      //virtual void HtmlHelp(dword_ptr dwData, UINT nCmd = 0x000F);
      // xxx virtual void WinHelpInternal(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);
      
      // layout and other functions
      /*   void RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
       UINT nFlag = reposDefault, LPRECT lpRectParam = NULL,
       LPCRECT lpRectClient = NULL, bool bStretch = TRUE);*/
      
      void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver,
                          UINT nFlags = reposDefault, LPRECT lpRectParam = NULL,
                          LPCRECT lpRectClient = NULL, bool bStretch = TRUE);
      
      
      // dialog support
      void UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHndler);
      void CenterWindow(sp(::user::interaction)  pAlternateOwner = NULL);
      virtual id   RunModalLoop(DWORD dwFlags = 0, ::core::live_object * pliveobject = NULL);
      virtual bool ContinueModal(int32_t iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);
      
      // oswindow-Management message handler member functions
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual bool OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      
      void OnActivate(UINT nState, ::window * pWndOther, bool bMinimized);
      void OnActivateApp(bool bActive, DWORD dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::window * pWnd, point pos);
      bool OnCopyData(::window * pWnd, COPYDATASTRUCT* pCopyDataStruct);
      DECL_GEN_SIGNAL(_001OnCreate);
      
      
      HBRUSH OnCtlColor(::draw2d::graphics * pgraphics, ::window * pWnd, UINT nCtlColor);
      
      DECL_GEN_SIGNAL(_001OnDestroy);
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      void OnEnterIdle(UINT nWhy, ::window * pWho);
      bool OnEraseBkgnd(::draw2d::graphics * pgraphics);
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      //xxx bool OnHelpInfo(HELPINFO* lpHelpInfo);
      void OnIconEraseBkgnd(::draw2d::graphics * pgraphics);
      void OnKillFocus(::window * pNewWnd);
      LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::user::menu* pMenu);
      void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      void OnMove(int32_t x, int32_t y);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
       DECL_GEN_SIGNAL(_001OnCaptureChanged);
      void OnParentNotify(UINT message, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::window * pOldWnd);
      void OnShowWindow(bool bShow, UINT nStatus);
      void OnSize(UINT nType, int32_t cx, int32_t cy);
      void OnTCard(UINT idAction, DWORD dwActionData);
      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      void OnWindowPosChanged(WINDOWPOS* lpwndpos);
      
      void OnChangeUIState(UINT nAction, UINT nUIElement);
      void OnUpdateUIState(UINT nAction, UINT nUIElement);
      UINT OnQueryUIState();
      
      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(LPCREATESTRUCT lpCreateStruct);
      DECL_GEN_SIGNAL(_001OnNcDestroy);
      LRESULT OnNcHitTest(point point);
      void OnNcLButtonDblClk(UINT nHitTest, point point);
      void OnNcLButtonDown(UINT nHitTest, point point);
      void OnNcLButtonUp(UINT nHitTest, point point);
      void OnNcMButtonDblClk(UINT nHitTest, point point);
      void OnNcMButtonDown(UINT nHitTest, point point);
      void OnNcMButtonUp(UINT nHitTest, point point);
      void OnNcMouseMove(UINT nHitTest, point point);
      void OnNcPaint();
      void OnNcRButtonDblClk(UINT nHitTest, point point);
      void OnNcRButtonDown(UINT nHitTest, point point);
      void OnNcRButtonUp(UINT nHitTest, point point);
      
      // System message handler member functions
      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::window * pRealizeWnd);
      void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysCommand(UINT nID, LPARAM lParam);
      void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(LPTSTR lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::window * pFocusWnd);
      void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(UINT uFlags, const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);
      
      // Input message handler member functions
      void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  //    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnLButtonDblClk(UINT nFlags, point point);
      void OnLButtonDown(UINT nFlags, point point);
      void OnLButtonUp(UINT nFlags, point point);
      void OnMButtonDblClk(UINT nFlags, point point);
      void OnMButtonDown(UINT nFlags, point point);
      void OnMButtonUp(UINT nFlags, point point);
      int32_t OnMouseActivate(::window * pDesktopWnd, UINT nHitTest, UINT message);
      void OnMouseMove(UINT nFlags, point point);
      bool OnMouseWheel(UINT nFlags, short zDelta, point pt);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, point point);
      void OnRButtonDown(UINT nFlags, point point);
      void OnRButtonUp(UINT nFlags, point point);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      void OnTimer(uint_ptr nIDEvent);
      
      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu, UINT nIndex, bool bSysMenu);
      
      // Clipboard message handler member functions
      void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::window * pClipAppWnd, UINT nSBCode, UINT nPos);
      void OnPaintClipboard(::window * pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::window * pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::window * pClipAppWnd, UINT nSBCode, UINT nPos);
      
      // control message handler member functions
      //xxx      int32_t OnCompareItem(int32_t nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //xxx      void OnDeleteItem(int32_t nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //xxx      void OnDrawItem(int32_t nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      UINT OnGetDlgCode();
      //xxx      void OnMeasureItem(int32_t nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      
      // MDI message handler member functions
      void OnMDIActivate(bool bActivate,
                         ::window * pActivateWnd, ::window * pDeactivateWnd);
      
      // menu loop notification messages
      void OnEnterMenuLoop(bool bIsTrackPopupMenu);
      void OnExitMenuLoop(bool bIsTrackPopupMenu);
      
      // Win4 messages
      //xxx      void OnStyleChanged(int32_t nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //xxx      void OnStyleChanging(int32_t nStyleType, LPSTYLESTRUCT lpStyleStruct);
      void OnSizing(UINT nSide, LPRECT lpRect);
      void OnMoving(UINT nSide, LPRECT lpRect);
      void OnCaptureChanged(::window * pWnd);
      bool OnDeviceChange(UINT nEventType, uint_ptr dwData);
      
      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      // xxx      virtual WNDPROC* GetSuperWndProcAddr();
      
      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);
      
      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();
      
      // for translating oswindows messages in main message pump
      virtual void pre_translate_message(signal_details * pobj);
      
      
      // for processing oswindows messages
      virtual void message_handler(signal_details * pobj);
      //virtual bool OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      
      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
      
      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();
      
      // for notifications from parent
      virtual bool OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      // return TRUE if parent should not process this message
      bool ReflectChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static bool PASCAL ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = NULL);
      
      // Implementation
      virtual ~window();
      virtual bool CheckAutoCenter();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      static bool PASCAL GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
                                      HBRUSH hbrGray, COLORREF clrText);
      
      
      // helper routines for implementation
      bool HandleFloatingSysCommand(UINT nID, LPARAM lParam);
      bool IsTopParentActive();
      void ActivateTopParent();
      virtual void WalkPreTranslateTree(sp(::user::interaction)  puiStop, signal_details * pobj);
      static sp(::user::interaction)  PASCAL GetDescendantWindow(sp(::user::interaction)  hWnd, id id);
      static void PASCAL SendMessageToDescendants(void*  hWnd, UINT message, WPARAM wParam, lparam lParam, bool bDeep, bool bOnlyPerm);
      virtual bool IsFrameWnd(); // is_kind_of(System.type_info < frame_window > ()))
      virtual void on_final_release();
      static bool PASCAL ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static bool PASCAL ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::window * pWnd);
      bool _EnableToolTips(bool bEnable, UINT nFlag);
      static oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp();
      
      //UINT m_nFlags;      // see WF_ flags above
      
      // xxx      WNDPROC m_pfnSuper; // for subclassing of controls
      static const UINT m_nMsgDragList;
      int32_t m_nModalResult; // for return values from ::window::RunModalLoop
      
      ::draw2d::font * m_pfont;
      
      friend class frame_window;
      
      // for creating dialogs and dialog-like windows
      bool CreateDlg(const char * lpszTemplateName, ::window * pParentWnd);
      //bool CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::window * pParentWnd,
      // HINSTANCE hInst);
      
      
      // implementation of message dispatch/hooking
      CLASS_DECL_mac friend LRESULT CALLBACK __send_message_hook(int32_t, WPARAM, LPARAM);
      //CLASS_DECL_mac friend void _gen::StandardSubclass(oswindow);
      CLASS_DECL_mac friend LRESULT CALLBACK __cbt_filter_hook(int32_t, WPARAM, LPARAM);
      CLASS_DECL_mac friend LRESULT __call_window_procedure(sp(::user::interaction)  pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
      
      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);
      
      static bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);
      
      
      static void get_app_wnda(user::oswindow_array & wnda);
      
      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);
      
      virtual LONG GetWindowLong(int32_t nIndex);
      virtual LONG SetWindowLong(int32_t nIndex, LONG lValue);
      
      virtual void _001BaseWndInterfaceMap();
      
      
      void _001UpdateWindow();
      
      
      void _001OnTriggerMouseInside();
      
      DECL_GEN_SIGNAL(_001OnTimer);
      
      void _001RedrawWindow();
      
      
      
   };
   
   
} // namespace mac




