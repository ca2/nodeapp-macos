#pragma once


WINBOOL AfxInternalPreTranslateMessage(MESSAGE* pMsg);


namespace mac
{

   
   struct thread_startup
   {
      
      
      ::thread *           m_pthread;    // thread for new thread
      event                hEvent;          // event triggered after success/non-success
      event                hEvent2;         // event triggered after thread is resumed
      
      
      thread_startup();
      ~thread_startup();
      
      
   };
   
   
   class CLASS_DECL_mac thread :
      virtual public ::thread,
      virtual public ::message_queue
   {
   public:
      
      
      /// thread ID, used to ensure that the thread that calls one of the WaitForEvents
		/// methods is really the thread represented by the Thread class
		//pthread_t			thread_;
      
		HTHREAD           m_hThread;
		UINT              m_nID;
      
		/// true only for the main thread that is represented by pal::MainThread
		bool				isMainThread_;
		/// true only for external threads (e.g. a thread of a linked SIP-stack that calls the pal::wait-function).
		bool				isExternalThread_;
		/// condition used to wake up the thread if an event for which the thread
		/// is waiting is signaled
		//pthread_cond_t		wakeUpCondition_;
		/// ensures that the thread function is not called before the Thread class
		/// (e.g. thread_) is initialized
		//pthread_mutex_t		startMutex_;
		/// result of last wait operation
		int32_t					waitResult_;
		/// true if waiting should be done on all items
		bool				waitForAllItems_;
		/// a list of items this threads waits for
		list < waitable * >	itemsToWaitFor_;
      
      
      // list of frame_window objects for thread
      list < ::user::frame_window * > m_frameList;
      
      // temporary/permanent ::collection::map state
      DWORD m_nTempMapLock;           // if not 0, temp maps locked
      //hmenu_map      * m_pmapHMENU;
      //hdc_map        * m_pmapHDC;
      //hgdiobj_map    * m_pmapHGDIOBJ;
      
      
      
      LPVOID                              m_pThreadParams; // generic parameters passed to starting function
      __THREADPROC                      m_pfnThreadProc;
      
      ::event                              m_evFinish;
      //::event                              m_peventReady;
      UINT                                m_nDisablePumpCount;
      mutex                               m_mutexUiPtra;
      
      ::thread *                      m_pAppThread;
      
      UINT                                m_dwFinishTimeout;
      
      
      thread(base_application * papp);
      virtual ~thread();
      
      
      void CommonConstruct();
      virtual void Delete();
      
      
      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);
      
      
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif
      
      
      
      virtual void * get_os_data() const;
      virtual int_ptr get_os_int() const;
      
      void set_os_data(void * pvoidOsData);
      void set_os_int(int_ptr iData);
      
      virtual void set_p(::thread * p);
      
      
      virtual bool begin(int32_t epriority = get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
      
      virtual bool create_thread(int32_t epriority = get_scheduling_priority_normal(), uint32_t dwCreateFlagsParam = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
      
      virtual sp(::user::interaction)  SetMainWnd(sp(::user::interaction)  pui);
      
      virtual int32_t thread_entry(::mac::thread_startup * pstartup);
      virtual int32_t main();
      virtual int32_t thread_term(int32_t nResult);
      
      
      virtual void add(sp(::user::interaction)  pui);
      virtual void remove(::user::interaction *  pui);
      virtual ::count get_ui_count();
      virtual sp(::user::interaction)  get_ui(int32_t iIndex);
      virtual void set_timer(sp(::user::interaction)  pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(sp(::user::interaction)  pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual ::thread * get_app_thread();
      virtual sp(::user::interaction) get_active_ui();
      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
      virtual void step_timer();
      virtual bool on_run_step();
      
      
//      virtual void on_delete(::ca2::ca2 * poc);
      
      int32_t get_thread_priority();
      bool set_thread_priority(int32_t epriority);
      
      // Operations
      DWORD SuspendThread();
      DWORD ResumeThread();
      bool post_thread_message(UINT message, WPARAM wParam = 0, lparam lParam = NULL);
      bool post_message(sp(::user::interaction)  pguie, UINT message, WPARAM wParam = 0, lparam lParam = NULL);
      
      virtual bool PreInitInstance();
      
      // called when occurs an se_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::exception::exception & e);
      
      // Overridables
      // thread initialization
      virtual bool initialize_instance();
      
      virtual ::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);
      
      // running and idle processing
      virtual int32_t run();
      virtual void pre_translate_message(signal_details * pobj);
      virtual bool pump_message();     // low level message pump
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual bool is_idle_message(signal_details * pobj);  // checks for special messages
      virtual WINBOOL is_idle_message(LPMESSAGE lpmsg);  // checks for special messages
      virtual void message_handler(signal_details * pobj);
      
      // thread termination
      virtual int32_t exit_instance(); // default will 'delete this'
      
      // Advanced: exception handling
      virtual void ProcessWndProcException(::exception::base * e, signal_details * pMsg);
      
      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int32_t code, signal_details * pobj);
      
      // Advanced: virtual access to GetMainWnd()
      virtual sp(::user::interaction) GetMainWnd();
      
      // 'delete this' only if m_bAutoDelete == TRUE
      
      
      
      virtual void DispatchThreadMessageEx(signal_details * pobj);  // helper
      virtual void message_queue_message_handler(signal_details * pobj);
      
      virtual void delete_temp();
      
      
      virtual void LockTempMaps();
      virtual WINBOOL UnlockTempMaps(WINBOOL bDeleteTemp);
      
      operator pthread_t() const;
      
      
   };
   
   
   CLASS_DECL_mac ::thread * get_thread();
   
   
} // namespace mac



