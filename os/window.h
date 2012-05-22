#pragma once

namespace win
{
   
   CLASS_DECL_VMSWIN LRESULT CALLBACK _AfxSendMsgHook(int, WPARAM, LPARAM);
   //CLASS_DECL_VMSWIN void _AfxStandardSubclass(HWND);
   CLASS_DECL_VMSWIN LRESULT CALLBACK _AfxCbtFilterHook(int, WPARAM, LPARAM);
   CLASS_DECL_VMSWIN LRESULT AfxCallWndProc(::user::interaction * pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

   class CLASS_DECL_VMSWIN window : 
      virtual public ::ca::window,
      virtual public hwnd_handle
   {
   public:


      pha(::user::interaction)      m_guieptraMouseHover;
      ::ca::window_callback *       m_pcallback;
      string                        m_strWindowText;
      comparable_array < int >      m_iaModalThread;


      window();
      window(::ca::application * papp);
      virtual void construct(HWND hwnd);

      virtual void on_delete(::ca::ca * poc);

      virtual void mouse_hover_add(::user::interaction* pinterface);
      virtual void mouse_hover_remove(::user::interaction* pinterface);

      bool create_message_window(const char * pszName, ::ca::window_callback * pcallback = NULL);

      static const MSG* PASCAL GetCurrentMessage();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      WINBOOL operator==(const ::ca::window& wnd) const;
      WINBOOL operator!=(const ::ca::window& wnd) const;

      DWORD GetStyle();
      DWORD GetExStyle();
      WINBOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      WINBOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

      //virtual ::user::interaction * GetOwner();
      virtual void SetOwner(::user::interaction * pOwnerWnd);

      virtual HWND _get_handle();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);   

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      DECL_GEN_SIGNAL(_002OnDraw)
      DECL_GEN_SIGNAL(_001OnEraseBkgnd)
      DECL_GEN_SIGNAL(_001OnMove)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnShowWindow)
      DECL_GEN_SIGNAL(_001OnProdevianSynch)

      ::user::window_interface *      m_pbasewnd;
      ::user::interaction *        m_pguieCapture;

   #if(WINVER >= 0x0500)

      WINBOOL GetWindowInfo(PWINDOWINFO pwi) const;
      WINBOOL GetTitleBarInfo(PTITLEBARINFO pti) const;

   #endif   // WINVER >= 0x0500

      virtual ::ca::window * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      static window * PASCAL from_handle(HWND hWnd);
      static window * PASCAL FromHandlePermanent(HWND hWnd);
      static void PASCAL DeleteTempMap();
      WINBOOL Attach(HWND hWndNew);
      HWND Detach();

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window();
      WINBOOL SubclassWindow(HWND hWnd);
      WINBOOL SubclassDlgItem(UINT nID, ::ca::window * pParent);
      HWND UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      WINBOOL ExecuteDlgInit(const char * lpszResourceName);
      WINBOOL ExecuteDlgInit(LPVOID lpResource);

      using ::user::interaction::create;
      // for child windows, views, panes etc
      virtual WINBOOL create(const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         ::user::interaction * pParentWnd, id id,
         create_context* pContext = NULL);

      // advanced creation (allows access to extended styles)
      virtual WINBOOL CreateEx(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         int x, int y, int nWidth, int nHeight,
         HWND hWndParent, id id, LPVOID lpParam = NULL);

      virtual WINBOOL CreateEx(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         ::user::interaction* pParentWnd, id id,
         LPVOID lpParam = NULL);

      virtual WINBOOL DestroyWindow();

      // special pre-creation and ::ca::window rect adjustment hooks
      virtual WINBOOL PreCreateWindow(CREATESTRUCT& cs);

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);

      
         // get immediate child with given ID
      using ::user::interaction::GetDlgItem;
      void GetDlgItem(id id, HWND* phWnd) const;
         // as above, but returns HWND
      using ::user::interaction::GetDescendantWindow;
      ::user::interaction * GetDescendantWindow(id id);
         // like GetDlgItem but recursive
      void SendMessageToDescendants(UINT message, WPARAM wParam = 0,
         LPARAM lParam = 0, WINBOOL bDeep = TRUE, WINBOOL bOnlyPerm = FALSE);
      frame_window* GetParentFrame();
      frame_window* EnsureParentFrame();
      ::user::interaction* GetTopLevelParent();
      ::user::interaction* EnsureTopLevelParent();
      ::user::interaction* GetTopLevelOwner();
      ::user::interaction* GetParentOwner();
      frame_window* GetTopLevelFrame();
      static ::ca::window * PASCAL GetSafeOwner(::ca::window * pParent = NULL, HWND* pWndTop = NULL);

      virtual WINBOOL IsWindow();

   #if(WINVER >= 0x0500)

      ::ca::window * GetAncestor(UINT gaFlags) const;

   #endif   // WINVER >= 0x0500

   // Message Functions
   #pragma push_macro("SendMessage")
   #undef SendMessage
      LRESULT _AFX_FUNCNAME(SendMessage)(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
   #pragma pop_macro("SendMessage")
      WINBOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

      WINBOOL SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam);
      WINBOOL SendChildNotifyLastMsg(LRESULT* pResult = NULL);

      WINBOOL DragDetect(POINT pt) const;



   // Window Text Functions
      void SetWindowText(const char * lpszString);
      int GetWindowText(__out_ecount_part_z(nMaxCount, return + 1) LPTSTR lpszStringBuf, __in int nMaxCount);
      void GetWindowText(string & rString);
      int GetWindowTextLength();
      void SetFont(::ca::font* pFont, WINBOOL bRedraw = TRUE);
      ::ca::font* GetFont();


   // Window size and position Functions
      virtual bool IsIconic();
      virtual bool IsZoomed();
      void MoveWindow(int x, int y, int nWidth, int nHeight,
               WINBOOL bRepaint = TRUE);
      void MoveWindow(LPCRECT lpRect, WINBOOL bRepaint = TRUE);
      int SetWindowRgn(HRGN hRgn, WINBOOL bRedraw);
      int GetWindowRgn(HRGN hRgn);

      //static const ::ca::window wndTop; // SetWindowPos's pWndInsertAfter
      //static const ::ca::window wndBottom; // SetWindowPos's pWndInsertAfter
      //static const ::ca::window wndTopMost; // SetWindowPos pWndInsertAfter
      //static const ::ca::window wndNoTopMost; // SetWindowPos pWndInsertAfter

      virtual bool SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags);
      virtual UINT ArrangeIconicWindows();
      virtual void BringWindowToTop();
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

      virtual WINBOOL GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual WINBOOL SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

   // Coordinate Mapping Functions
      virtual void MapWindowPoints(::ca::window * pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::ca::window * pwndTo, LPRECT lpRect);

   // Update/Painting Functions
      virtual ::ca::graphics * GetDC();
      virtual ::ca::graphics * GetWindowDC();
      virtual int ReleaseDC(::ca::graphics * pgraphics);
      virtual void Print(::ca::graphics * pgraphics, DWORD dwFlags) const;
      virtual void PrintClient(::ca::graphics * pgraphics, DWORD dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(WINBOOL bRedraw = TRUE);
      virtual WINBOOL GetUpdateRect(LPRECT lpRect, WINBOOL bErase = FALSE);
      virtual int GetUpdateRgn(::ca::rgn* pRgn, WINBOOL bErase = FALSE);
      virtual void Invalidate(WINBOOL bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect, WINBOOL bErase = TRUE);
      virtual void InvalidateRgn(::ca::rgn* pRgn, WINBOOL bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::ca::rgn* pRgn);
      virtual WINBOOL ShowWindow(int nCmdShow);
      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual WINBOOL IsWindowVisible();
      virtual void ShowOwnedPopups(WINBOOL bShow = TRUE);

      virtual ::ca::graphics * GetDCEx(::ca::rgn* prgnClip, DWORD flags);
      virtual WINBOOL LockWindowUpdate();
      virtual void UnlockWindowUpdate();
      virtual WINBOOL RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::ca::rgn* prgnUpdate = NULL,
         UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
      virtual WINBOOL EnableScrollBar(int nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);

      virtual WINBOOL DrawAnimatedRects(int idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo);
      virtual WINBOOL DrawCaption(::ca::graphics * pgraphics, LPCRECT lprc, UINT uFlags);

   #if(WINVER >= 0x0500)

      virtual WINBOOL AnimateWindow(DWORD dwTime, DWORD dwFlags);

   #endif   // WINVER >= 0x0500

   #if(_WIN32_WINNT >= 0x0501)

      virtual WINBOOL PrintWindow(::ca::graphics * pgraphics, UINT nFlags) const;

   #endif   // _WIN32_WINNT >= 0x0501

   // Layered Window

   #if(_WIN32_WINNT >= 0x0500)

      virtual WINBOOL SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
      virtual WINBOOL UpdateLayeredWindow(::ca::graphics * pDCDst, POINT *pptDst, SIZE *psize, 
         ::ca::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);

   #endif   // _WIN32_WINNT >= 0x0500

   #if(_WIN32_WINNT >= 0x0501)

      virtual WINBOOL GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;

   #endif   // _WIN32_WINNT >= 0x0501


   // Timer Functions
      virtual uint_ptr SetTimer(uint_ptr nIDEvent, UINT nElapse,
         void (CALLBACK* lpfnTimer)(HWND, UINT, uint_ptr, DWORD));
      virtual WINBOOL KillTimer(uint_ptr nIDEvent);

   // Window State Functions
      virtual WINBOOL IsWindowEnabled();
      virtual WINBOOL EnableWindow(WINBOOL bEnable = TRUE);

      // the active ::ca::window applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground ::ca::window applies only to top-level windows (frame windows)
      virtual WINBOOL SetForegroundWindow();
      static ::ca::window * PASCAL GetForegroundWindow();

      virtual id SetDlgCtrlId(id id);
      virtual id GetDlgCtrlId();

      

      // capture and focus apply to all windows
      static ::ca::window * PASCAL GetCapture();
      virtual ::user::interaction * set_capture(::user::interaction * pinterface = NULL);
      virtual ::user::interaction * release_capture();
      virtual ::user::interaction * get_capture();
      static ::ca::window * PASCAL GetFocus();
      ::ca::window * SetFocus();

      static ::ca::window * PASCAL GetDesktopWindow();

   // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual WINBOOL OpenIcon();

   // Dialog-Box Item Functions
   // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(int nIDButton, UINT nCheck);
      virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton,
                  int nIDCheckButton);
      virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      virtual int DlgDirList(__inout_z LPTSTR lpPathSpec, __in int nIDListBox,
                  __in int nIDStaticPath, __in UINT nFileType);
      virtual int DlgDirListComboBox(__inout_z LPTSTR lpPathSpec, __in int nIDComboBox,
                  __in int nIDStaticPath, __in UINT nFileType);
      virtual WINBOOL DlgDirSelect(__out_ecount_z(nSize) LPTSTR lpString, __in int nSize, __in int nIDListBox);
      virtual WINBOOL DlgDirSelectComboBox(__out_ecount_z(nSize) LPTSTR lpString, __in int nSize, __in int nIDComboBox);

      virtual UINT GetDlgItemInt(int nID, WINBOOL* lpTrans = NULL, WINBOOL bSigned = TRUE) const;
      virtual int GetDlgItemText(__in int nID, __out_ecount_part_z(nMaxCount, return + 1) LPTSTR lpStr, __in int nMaxCount) const;
      virtual int GetDlgItemText(int nID, string & rString) const;
      virtual ::ca::window * GetNextDlgGroupItem(::ca::window * pWndCtl, WINBOOL bPrevious = FALSE) const;
      virtual ::ca::window * GetNextDlgTabItem(::ca::window * pWndCtl, WINBOOL bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(int nIDButton) const;
      virtual LRESULT SendDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(int nID, UINT nValue, WINBOOL bSigned = TRUE);
      virtual void SetDlgItemText(int nID, const char * lpszString);

   // Scrolling Functions
      virtual int GetScrollPos(int nBar) const;
      virtual void GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
      virtual void ScrollWindow(int xAmount, int yAmount,
                  LPCRECT lpRect = NULL,
                  LPCRECT lpClipRect = NULL);
      virtual int SetScrollPos(int nBar, int nPos, WINBOOL bRedraw = TRUE);
      virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
            WINBOOL bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar, WINBOOL bShow = TRUE);
      virtual void EnableScrollBarCtrl(int nBar, WINBOOL bEnable = TRUE);
      virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
            // return sibling scrollbar control (or NULL if none)

      virtual int ScrollWindowEx(int dx, int dy,
               LPCRECT lpRectScroll, LPCRECT lpRectClip,
               ::ca::rgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
      virtual WINBOOL SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo,
         WINBOOL bRedraw = TRUE);
      virtual WINBOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
      virtual int GetScrollLimit(int nBar);

   #if(WINVER >= 0x0500)

      virtual WINBOOL GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;

   #endif   // WINVER >= 0x0500

   // Window Access Functions
      virtual ::ca::window * ChildWindowFromPoint(POINT point);
      virtual ::ca::window * ChildWindowFromPoint(POINT point, UINT nFlags);
      static ::ca::window * PASCAL FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static ::ca::window * FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetWindow(UINT nCmd);
      virtual ::user::interaction * GetLastActivePopup();

      virtual WINBOOL IsChild(::user::interaction *  pWnd);
      virtual ::user::interaction * GetParent();
      using ::user::interaction::SetParent;
      ::ca::window * SetParent(::ca::window * pWndNewParent);
      static ::ca::window * PASCAL WindowFromPoint(POINT point);

   // Alert Functions
      WINBOOL FlashWindow(WINBOOL bInvert);
   #pragma push_macro("MessageBox")
   #undef MessageBox
      virtual int _AFX_FUNCNAME(MessageBox)(const char * lpszText, const char * lpszCaption = NULL,
            UINT nType = MB_OK);
      virtual int MessageBox(const char * lpszText, const char * lpszCaption = NULL,
            UINT nType = MB_OK);
   #pragma pop_macro("MessageBox")

   #if(WINVER >= 0x0500)

      virtual WINBOOL FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout);

   #endif   // WINVER >= 0x0500

   // Clipboard Functions
      virtual WINBOOL ChangeClipboardChain(HWND hWndNext);
      virtual HWND SetClipboardViewer();
      virtual WINBOOL OpenClipboard();
      static ::ca::window * PASCAL GetClipboardOwner();
      static ::ca::window * PASCAL GetClipboardViewer();
      static ::ca::window * PASCAL GetOpenClipboardWindow();

   // Caret Functions
      virtual void CreateCaret(::ca::bitmap* pBitmap);
      virtual void CreateSolidCaret(int nWidth, int nHeight);
      virtual void CreateGrayCaret(int nWidth, int nHeight);
      static point PASCAL GetCaretPos();
      static void PASCAL SetCaretPos(POINT point);
      virtual void HideCaret();
      virtual void ShowCaret();

   // Shell Interaction Functions
      virtual void DragAcceptFiles(WINBOOL bAccept = TRUE);

   // icon Functions
      virtual HICON SetIcon(HICON hIcon, WINBOOL bBigIcon);
      virtual HICON GetIcon(WINBOOL bBigIcon) const;

   // Context Help Functions
      virtual WINBOOL SetWindowContextHelpId(DWORD dwContextHelpId);
      virtual DWORD GetWindowContextHelpId() const;

   // Dialog Data support
      //virtual WINBOOL UpdateData(WINBOOL bSaveAndValidate = TRUE);
            // data wnd must be same type as this

   // Help Command Handlers
      afx_msg void OnHelp();          // F1 (uses current context)
      afx_msg void OnHelpIndex();     // ID_HELP_INDEX
      afx_msg void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      afx_msg void OnHelpUsing();     // ID_HELP_USING
      virtual void WinHelp(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);
      //virtual void HtmlHelp(dword_ptr dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(dword_ptr dwData, UINT nCmd = HELP_CONTEXT);

   // layout and other functions
   /*   void RepositionBars(const char * pszPrefix, const char * pszIdLeftOver,
         UINT nFlag = reposDefault, LPRECT lpRectParam = NULL,
         LPCRECT lpRectClient = NULL, WINBOOL bStretch = TRUE);*/

      void RepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
         UINT nFlags = reposDefault, LPRECT lpRectParam = NULL,
         LPCRECT lpRectClient = NULL, WINBOOL bStretch = TRUE);


      // dialog support
      void UpdateDialogControls(command_target* pTarget, WINBOOL bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = NULL);
      int RunModalLoop(DWORD dwFlags = 0);
      virtual WINBOOL ContinueModal(int iLevel);
      virtual void EndModalLoop(int nResult);
      virtual void EndAllModalLoops(int nResult);

   // Window-Management message handler member functions
      virtual WINBOOL OnCommand(WPARAM wParam, LPARAM lParam);
      virtual WINBOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      afx_msg void OnActivate(UINT nState, ::ca::window * pWndOther, WINBOOL bMinimized);
      afx_msg void OnActivateApp(WINBOOL bActive, DWORD dwThreadID);
      afx_msg LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      afx_msg void OnCancelMode();
      afx_msg void OnChildActivate();
      afx_msg void OnClose();
      afx_msg void OnContextMenu(::ca::window * pWnd, point pos);
      afx_msg WINBOOL OnCopyData(::ca::window * pWnd, COPYDATASTRUCT* pCopyDataStruct);
      DECL_GEN_SIGNAL(_001OnCreate);


      afx_msg HBRUSH OnCtlColor(::ca::graphics * pgraphics, ::ca::window * pWnd, UINT nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
      afx_msg void OnEnable(WINBOOL bEnable);
      afx_msg void OnEndSession(WINBOOL bEnding);
      afx_msg void OnEnterIdle(UINT nWhy, ::ca::window * pWho);
      afx_msg WINBOOL OnEraseBkgnd(::ca::graphics * pgraphics);
      afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      afx_msg WINBOOL OnHelpInfo(HELPINFO* lpHelpInfo);
      afx_msg void OnIconEraseBkgnd(::ca::graphics * pgraphics);
      afx_msg void OnKillFocus(::ca::window * pNewWnd);
      afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::userbase::menu* pMenu);
      afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      afx_msg void OnMove(int x, int y);
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnPrint)
      virtual void _001Print(::ca::graphics * pgraphics);
      DECL_GEN_SIGNAL(_001OnCaptureChanged)
      afx_msg void OnParentNotify(UINT message, LPARAM lParam);
      afx_msg HCURSOR OnQueryDragIcon();
      afx_msg WINBOOL OnQueryEndSession();
      afx_msg WINBOOL OnQueryNewPalette();
      afx_msg WINBOOL OnQueryOpen();
      afx_msg void OnSetFocus(::ca::window * pOldWnd);
      afx_msg void OnShowWindow(WINBOOL bShow, UINT nStatus);
      afx_msg void OnSize(UINT nType, int cx, int cy);
      afx_msg void OnTCard(UINT idAction, DWORD dwActionData);
      afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);

      afx_msg void OnChangeUIState(UINT nAction, UINT nUIElement);
      afx_msg void OnUpdateUIState(UINT nAction, UINT nUIElement);
      afx_msg UINT OnQueryUIState();

   // Nonclient-Area message handler member functions
      afx_msg WINBOOL OnNcActivate(WINBOOL bActive);
      afx_msg void OnNcCalcSize(WINBOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      afx_msg WINBOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
      DECL_GEN_SIGNAL(_001OnNcDestroy)
      afx_msg LRESULT OnNcHitTest(point point);
      afx_msg void OnNcLButtonDblClk(UINT nHitTest, point point);
      afx_msg void OnNcLButtonDown(UINT nHitTest, point point);
      afx_msg void OnNcLButtonUp(UINT nHitTest, point point);
      afx_msg void OnNcMButtonDblClk(UINT nHitTest, point point);
      afx_msg void OnNcMButtonDown(UINT nHitTest, point point);
      afx_msg void OnNcMButtonUp(UINT nHitTest, point point);
      afx_msg void OnNcMouseMove(UINT nHitTest, point point);
      afx_msg void OnNcPaint();
      afx_msg void OnNcRButtonDblClk(UINT nHitTest, point point);
      afx_msg void OnNcRButtonDown(UINT nHitTest, point point);
      afx_msg void OnNcRButtonUp(UINT nHitTest, point point);

   // System message handler member functions
      afx_msg void OnDropFiles(HDROP hDropInfo);
      afx_msg void OnPaletteIsChanging(::ca::window * pRealizeWnd);
      afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
      afx_msg void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnCompacting(UINT nCpuTime);
      afx_msg void OnDevModeChange(__in_z LPTSTR lpDeviceName);
      afx_msg void OnFontChange();
      afx_msg void OnPaletteChanged(::ca::window * pFocusWnd);
      afx_msg void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      afx_msg void OnSysColorChange();
      afx_msg void OnTimeChange();
      afx_msg void OnSettingChange(UINT uFlags, const char * lpszSection);
      afx_msg void OnWinIniChange(const char * lpszSection);

   // Input message handler member functions
      afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      afx_msg void OnLButtonDblClk(UINT nFlags, point point);
      afx_msg void OnLButtonDown(UINT nFlags, point point);
      afx_msg void OnLButtonUp(UINT nFlags, point point);
      afx_msg void OnMButtonDblClk(UINT nFlags, point point);
      afx_msg void OnMButtonDown(UINT nFlags, point point);
      afx_msg void OnMButtonUp(UINT nFlags, point point);
      afx_msg int OnMouseActivate(::ca::window * pDesktopWnd, UINT nHitTest, UINT message);
      afx_msg void OnMouseMove(UINT nFlags, point point);
      afx_msg WINBOOL OnMouseWheel(UINT nFlags, short zDelta, point pt);
      afx_msg LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      afx_msg void OnRButtonDblClk(UINT nFlags, point point);
      afx_msg void OnRButtonDown(UINT nFlags, point point);
      afx_msg void OnRButtonUp(UINT nFlags, point point);
      DECL_GEN_SIGNAL(_001OnSetCursor)
      afx_msg void OnTimer(uint_ptr nIDEvent);

   // Initialization message handler member functions
      afx_msg void OnInitMenu(::userbase::menu* pMenu);
      afx_msg void OnInitMenuPopup(::userbase::menu* pPopupMenu, UINT nIndex, WINBOOL bSysMenu);

   // Clipboard message handler member functions
      afx_msg void OnAskCbFormatName(__in UINT nMaxCount, __out_ecount_z(nMaxCount) LPTSTR lpszString);
      afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
      afx_msg void OnDestroyClipboard();
      afx_msg void OnDrawClipboard();
      afx_msg void OnHScrollClipboard(::ca::window * pClipAppWnd, UINT nSBCode, UINT nPos);
      afx_msg void OnPaintClipboard(::ca::window * pClipAppWnd, HGLOBAL hPaintStruct);
      afx_msg void OnRenderAllFormats();
      afx_msg void OnRenderFormat(UINT nFormat);
      afx_msg void OnSizeClipboard(::ca::window * pClipAppWnd, HGLOBAL hRect);
      afx_msg void OnVScrollClipboard(::ca::window * pClipAppWnd, UINT nSBCode, UINT nPos);

   // control message handler member functions
      afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      afx_msg void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      afx_msg UINT OnGetDlgCode();
      afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

   // MDI message handler member functions
      afx_msg void OnMDIActivate(WINBOOL bActivate,
         ::ca::window * pActivateWnd, ::ca::window * pDeactivateWnd);

   // menu loop notification messages
      afx_msg void OnEnterMenuLoop(WINBOOL bIsTrackPopupMenu);
      afx_msg void OnExitMenuLoop(WINBOOL bIsTrackPopupMenu);

   // Win4 messages
      afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      afx_msg void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
      afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
      afx_msg void OnCaptureChanged(::ca::window * pWnd);
      afx_msg WINBOOL OnDeviceChange(UINT nEventType, dword_ptr dwData);

   // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
//      virtual void DoDataExchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();

      // for translating Windows messages in main message pump
      virtual void pre_translate_message(gen::signal_object * pobj);


      // for processing Windows messages
      virtual void message_handler(gen::signal_object * pobj);
      //virtual WINBOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      // for notifications from parent
      virtual WINBOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
         // return TRUE if parent should not process this message
      WINBOOL ReflectChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static WINBOOL PASCAL ReflectLastMsg(HWND hWndChild, LRESULT* pResult = NULL);

   // Implementation
      virtual ~window();
      virtual WINBOOL CheckAutoCenter();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      static WINBOOL PASCAL GrayCtlColor(HDC hDC, HWND hWnd, UINT nCtlColor,
         HBRUSH hbrGray, COLORREF clrText);


      // helper routines for implementation
      WINBOOL HandleFloatingSysCommand(UINT nID, LPARAM lParam);
      WINBOOL IsTopParentActive();
      void ActivateTopParent();
      virtual void WalkPreTranslateTree(HWND hWndStop, gen::signal_object * pobj);
      static ::user::interaction * PASCAL GetDescendantWindow(::user::interaction * hWnd, id id);
      static void PASCAL SendMessageToDescendants(HWND hWnd, UINT message,
         WPARAM wParam, LPARAM lParam, WINBOOL bDeep, WINBOOL bOnlyPerm);
      virtual WINBOOL IsFrameWnd(); // is_kind_of(&typeid(frame_window)))
      virtual void on_final_release();
      static WINBOOL PASCAL ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd,
         UINT nFlags);
      static WINBOOL PASCAL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd,
         UINT nFlags);
      static void PASCAL _FilterToolTipMessage(MSG* pMsg, ::ca::window * pWnd);
      WINBOOL _EnableToolTips(WINBOOL bEnable, UINT nFlag);
      static HWND PASCAL GetSafeOwner_(HWND hWnd, HWND* pWndTop);
      void PrepareForHelp();

      //UINT m_nFlags;      // see WF_ flags above

      WNDPROC m_pfnSuper; // for subclassing of controls
      static const UINT m_nMsgDragList;
      int m_nModalResult; // for return values from ::ca::window::RunModalLoop

      ::ca::font * m_pfont;

      friend class frame_window;

      // for creating dialogs and dialog-like windows
      WINBOOL CreateDlg(const char * lpszTemplateName, ::ca::window * pParentWnd);
      //WINBOOL CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::ca::window * pParentWnd,
        // HINSTANCE hInst);


      // implementation of message dispatch/hooking
      CLASS_DECL_VMSWIN friend LRESULT CALLBACK _AfxSendMsgHook(int, WPARAM, LPARAM);
      //CLASS_DECL_VMSWIN friend void _AfxStandardSubclass(HWND);
      CLASS_DECL_VMSWIN friend LRESULT CALLBACK _AfxCbtFilterHook(int, WPARAM, LPARAM);
      CLASS_DECL_VMSWIN friend LRESULT AfxCallWndProc(::user::interaction * pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

      // standard message implementation
      afx_msg LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      afx_msg LRESULT OnDisplayChange(WPARAM, LPARAM);
      afx_msg LRESULT OnDragList(WPARAM, LPARAM);

      static WINBOOL CALLBACK GetAppsEnumWindowsProc(      
            HWND hwnd,
            LPARAM lParam);

      static void get_app_wnda(user::HWNDArray & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(::ca::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc);

      virtual LONG GetWindowLong(int nIndex);
      virtual LONG SetWindowLong(int nIndex, LONG lValue);

      virtual void _001BaseWndInterfaceMap();

   };

} // namespace win
