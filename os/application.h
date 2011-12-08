#pragma once

namespace gen
{
   class command_line;
}

namespace win
{

   class CLASS_DECL_VMSWIN main_init_data
   {
   public:
      HINSTANCE   m_hInstance;
      HINSTANCE   m_hPrevInstance;
      string      m_strCmdLine;
      int         m_nCmdShow;
   };

   class CLASS_DECL_VMSWIN application :
      virtual public ::ex2::application
   {
   public:

      WCHAR *              m_pszCmdLine;
      int                  m_argc;
      WCHAR **             m_argv;
      WCHAR *              m_pwszExeName;

      USHORT               m_atomApp;
      USHORT               m_atomSystemTopic;

      main_init_data *     m_pmaininitdata;


      application(::ca::application * papp);
      virtual ~application();
      
      virtual HINSTANCE GetHinstance();
      BOOL _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::document * _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();

      virtual void _001ParseCommandLine(gen::command_line& rCmdInfo);
      virtual bool _001ProcessShellCommand(gen::command_line& rCmdInfo);

      // Loads a cursor resource.
      HCURSOR LoadCursor(const char * lpszResourceName) const;
      HCURSOR LoadCursor(UINT nIDResource) const;

      // Loads a stock cursor resource; for for IDC_* values.
      HCURSOR LoadStandardCursor(const char * lpszCursorName) const;

      // Loads an OEM cursor; for all OCR_* values.
      HCURSOR LoadOEMCursor(UINT nIDCursor) const;

      // Loads an icon resource.
      HICON LoadIcon(const char * lpszResourceName) const;
      HICON LoadIcon(UINT nIDResource) const;

      // Loads an icon resource; for stock IDI_ values.
      HICON LoadStandardIcon(const char * lpszIconName) const;

      // Loads an OEM icon resource; for all OIC_* values.
      HICON LoadOEMIcon(UINT nIDIcon) const;

      virtual string get_version();

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual BOOL DeferRegisterClass(LONG fToRegister, const char ** ppszClass);
      virtual void LockTempMaps();
      virtual BOOL UnlockTempMaps(BOOL bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);
      virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);


      virtual void SetCurrentHandles();

      virtual bool set_main_init_data(void * pdata);

      virtual bool process_initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual int  exit_instance();



      
      virtual bool win_init(main_init_data * pdata);































      /*virtual void construct(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

      virtual bool Begin(int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
         DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
         LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual void * get_os_data();
      virtual INT_PTR get_os_int();


      int GetThreadPriority();
      BOOL SetThreadPriority(int nPriority);

   // Operations
      DWORD SuspendThread();
      DWORD ResumeThread();
      BOOL PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);
      bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an se_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::ca::exception & e);

   // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual ::user::win::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual BOOL pump_message();     // low level message pump
      virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
      virtual BOOL is_idle_message(MSG* pMsg);  // checks for special messages

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual LRESULT ProcessWndProcException(base_exception* e, const MSG* pMsg);

      // Advanced: handling messages sent to message filter hook
      virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction* GetMainWnd();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      virtual void CommonConstruct();
      virtual void Delete();
         // 'delete this' only if m_bAutoDelete == TRUE



      BOOL DispatchThreadMessageEx(MSG* msg);  // helper*/

      ::ca::graphics * graphics_from_os_data(void * pdata);

      ::ca::window * window_from_os_data(void * pdata);
      ::ca::window * window_from_os_data_permanent(void * pdata);

      virtual ::radix::thread * GetThread();
      virtual void set_thread(::radix::thread * pthread);

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual void get_time(struct timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual unsigned long application::get_thread_id();
   };

} // namespace win