#include "StdAfx.h"

//const UINT UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION = ::RegisterWindowMessageA("UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION-{7C29C80A_5712_40e8_A124_A82E4B2795A7}");  
#define UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION (WM_APP + 123) 

namespace win
{

   // forward declaration of global function which is included at the end of this file

   void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName);  


   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   port_forward::port_forward(::ca::application * papp) :
      ca(papp)
   {
	   InitializeMembersToNull();
	   ::InitializeCriticalSection( &m_cs );
   }

   port_forward::~port_forward()
   {
	   StopListeningForUpnpChanges( );
	
	   ::DeleteCriticalSection( &m_cs );
   }

   void port_forward::InitializeMembersToNull()
   {
	   m_piNAT			= NULL;				
	   m_piEventManager	= NULL;	
	   m_piExternalIPAddressCallback= NULL;	
	   m_piNumberOfEntriesCallback	= NULL;	
	
	   m_pChangeCallbackFunctions	= NULL;	
	
	   m_pPortMappingThread = NULL;
	   m_pDeviceInfoThread = NULL;
	   m_pAddMappingThread = NULL;
	   m_pEditMappingThread = NULL;
	   m_pDeleteMappingThread = NULL;
	
	   m_hWndForPortMappingThread = NULL;
	   m_hWndForDeviceInfoThread = NULL;
	   m_hWndForAddMappingThread = NULL;
	   m_hWndForEditMappingThread = NULL;
	   m_hWndForDeleteMappingThread = NULL;
	
	   m_bListeningForUpnpChanges = FALSE;
   }


   void port_forward::DeinitializeCom()
   {
	
	   if ( m_piExternalIPAddressCallback != NULL )
	   {
		   m_piExternalIPAddressCallback->Release();
		   m_piExternalIPAddressCallback = NULL;
	   }
	
	
	   if ( m_piNumberOfEntriesCallback != NULL )
	   {
		   m_piNumberOfEntriesCallback->Release();
		   m_piNumberOfEntriesCallback = NULL;
	   }
	
	   if ( m_piEventManager != NULL )
	   {
		   m_piEventManager->Release();
		   m_piEventManager = NULL;
	   }
	
	   if ( m_piNAT != NULL )
	   {
		   m_piNAT->Release();
		   m_piNAT = NULL;
	   }
	
	   CoUninitialize();  // balancing call for CoInitialize
   }

   HRESULT port_forward::ListenForUpnpChanges(::ca4::port_forward_change_callbacks *pCallbacks /* =NULL */ )
   {
	   // check if we are already listening
	
	   if ( m_bListeningForUpnpChanges == TRUE )
		   return E_FAIL;
	
	   m_bListeningForUpnpChanges = TRUE;
	
	
	   if ( pCallbacks==NULL )
	   {
		   SetChangeEventCallbackPointer(	new ::ca4::port_forward_change_callbacks );
	   }
	   else
	   {
		   SetChangeEventCallbackPointer( pCallbacks );
	   }
	
	   // initialize COM for this thread
	
	   HRESULT result = CoInitialize(NULL);  // STA model
	   if ( !SUCCEEDED(result) )
	   {
		   return E_FAIL;
	   }
	
	   // create COM instance of IUPnPNAT
	
	   result = CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&m_piNAT);
	   if ( !SUCCEEDED(result) || ( m_piNAT==NULL ) )
	   {
		   CoUninitialize();
		   return E_FAIL;
	   }
	
	
	   // Get the INATEventManager interface
	
	   result = m_piNAT->get_NATEventManager(&m_piEventManager);
	   if ( !SUCCEEDED(result) || (m_piEventManager==NULL ) )
	   {
		   m_piNAT->Release();
		   m_piNAT = NULL;
		   CoUninitialize();
		   return E_FAIL;
	   }
	
	   result = m_piEventManager->put_ExternalIPAddressCallback( 
		   m_piExternalIPAddressCallback = new IDerivedNATExternalIPAddressCallback( m_pChangeCallbackFunctions ) );
	
	   if ( !SUCCEEDED(result) )
	   {
		   m_piEventManager->Release();
		   m_piEventManager = NULL;
		   m_piNAT->Release();
		   m_piNAT = NULL;
		   CoUninitialize();
		   return E_FAIL;
	   }
	
	   result = m_piEventManager->put_NumberOfEntriesCallback( 
		   m_piNumberOfEntriesCallback = new IDerivedNATNumberOfEntriesCallback( m_pChangeCallbackFunctions ) );
	
	   if ( !SUCCEEDED(result) )
	   {
		   m_piEventManager->Release();
		   m_piEventManager = NULL;
		   m_piNAT->Release();
		   m_piNAT = NULL;
		   CoUninitialize();
		   return E_FAIL;
	   }
	
	   return S_OK;
   }



   HRESULT port_forward::StopListeningForUpnpChanges( )
   {
	   // Stops listenting for UPnP change events on the router and deletes any 
	   // port_forward_change_callbacks-derived objects that are currently being held
	
	   // check if we are already listening
	
	   if ( m_bListeningForUpnpChanges == FALSE )
		   return E_FAIL;
	
	   m_bListeningForUpnpChanges = FALSE;
	
	
	   DeinitializeCom( );
	
	   if ( m_pChangeCallbackFunctions != NULL )
	   {
		   delete m_pChangeCallbackFunctions;
		   m_pChangeCallbackFunctions = NULL;
	   }
	
	   return S_OK;
   }



   HRESULT port_forward::SetChangeEventCallbackPointer(::ca4::port_forward_change_callbacks *pCallbacks)
   {
	   ASSERT( pCallbacks!=NULL );
	
	   if ( m_pChangeCallbackFunctions != NULL )
	   {
		   delete m_pChangeCallbackFunctions;
		   m_pChangeCallbackFunctions = NULL;
	   }
	
	   m_pChangeCallbackFunctions = pCallbacks;
	
	   return S_OK;
   }



   BOOL port_forward::IsAnyThreadRunning() const
   {
	   BOOL bRet = FALSE;
	   bRet |= ( m_pPortMappingThread != NULL );
	   bRet |= ( m_pDeviceInfoThread != NULL );
	   bRet |= ( m_pAddMappingThread != NULL );
	   bRet |= ( m_pEditMappingThread != NULL );
	   bRet |= ( m_pDeleteMappingThread != NULL );
	
	   return bRet;
   }




   array_ptr_alloc < port_forward::port_map > port_forward::get_port_map() const
   {
	   // returns a copy of the current mappings (note: thread-awareness is needed)
	
	   // cast away const-ness of the critical section (since this is a const function)
	   port_forward* pThis = const_cast< port_forward* >( this );
	
	   ::EnterCriticalSection( &(pThis->m_cs) );
	
	   array_ptr_alloc < port_forward::port_map > retVector;
	   retVector = m_MappingContainer;
	
	   ::LeaveCriticalSection( &(pThis->m_cs) );
	
	   return retVector;
   }

   array_ptr_alloc < port_forward::device > port_forward::get_igd() const
   {	
	   // returns a copy of the current device information (note: thread-awareness is needed)
	
	   // cast away const-ness of the critical section (since this is a const function)
	   port_forward* pThis = const_cast< port_forward* >( this );
	
	   ::EnterCriticalSection( &(pThis->m_cs) );
	
	   array_ptr_alloc < device > retDeviceInfo;
	   retDeviceInfo = m_DeviceInfo;
	
	   ::LeaveCriticalSection( &(pThis->m_cs) );
	
	   return retDeviceInfo;
   }


   ///////////////////////////////////////////////
   //
   // Get Mappings and Device Information Using Threads
   //
   ///////////////////////////////////////////////
   //
   // These comments explain the how to receive notifications from the threads that the
   // Port Forward Engine creates when running COM requests for device information or for
   // retreival/change of port mappings.
   //
   // There are five functions that create threads, and each function takes a HWND as a 
   // parameter.  During execution of the thread, each thread will post messages to this HWND,
   // so as to notify the HWMND of the thread's progress through the needed COM tasks.  The 
   // message is always the same: a UINT named UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION.
   // Encodings of the WPARAM and LPARAM within the message will enable the HWND to determine
   // what's going on inside the thread.  The five functions are:
   //
   //   GetMappingsUsingThread()
   //   EditMappingUsingThread()
   //   AddMappingUsingThread()
   //   DeleteMappingUsingThread()
   //   GetDeviceInformationUsingThread()
   //
   // The comments below explain each how to modify your class to receive the thread's notification
   // message, and also explain how to decode the WPARAM and LPARAM values



   // define the value of the registered Window message.  An arbitrary GUID is included, to ensure uniqueness





   ///////////////////////////////////////////////
   //
   //  GetMappingsUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The GetMappingsUsingThread() function populates a std::vector of port_map's with port
   // mappings that it finds using a thread.  The reason for the thread is that COM retrieval of
   // port mappings is SLOW.  Moreover, retrieval of the port mappings also BLOCKS the message
   // pump, so without a separate thread the application would otherwise appear to be hung/frozen.
   //
   // The thread frees the user interface of your program to do other things.  The price you
   // pay for this convenience is that communication to your application is via Windows messages,
   // which the thread sends to your application and which your application must interpret and process.
   //
   // To use this function, your program must be able to receive (and process)
   // a registered window message posted from the thread when the thread is finished.
   // Thus, you must pass in a HWND of one of your windows that will receive the message.  Typically,
   // you would choose your CMainFrame window (use the ::AfxGetMainWnd() function).  However, you might
   // choose a different window, such as your CView-derived window for SDI applications
   //
   // The window that you choose must be able to process the message, which is a UINT named
   // UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION.  For an MFC application, here are the changes 
   // you must make to your CWnd class:
   //
   // 1. Declare a handler in your .h file using the following signature, in which 
   //    the name "OnMappingThreadNotificationMeesage" is arbitrary (ie, you can use
   //    any name that you want, but you must be consistent):
   //
   //		afx_msg LRESULT OnMappingThreadNotificationMeesage(WPARAM wParam, LPARAM lParam);
   //
   // 2. In your *.cpp file include the following "extern" statement somewhere at the beginning of 
   //    the file.  This statement tells the linker that the value of the message is defined elsewhere:
   //
   //		extern const UINT UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION;  // defined in PortForwadEngine.cpp
   //
   // 3. In your .cpp implementation file, add an entry to the message map as follows:
   //
   //		ON_REGISTERED_MESSAGE( UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, OnMappingThreadNotificationMeesage )
   //
   // 4. Again in your .cpp file, write the body of the OnMappingThreadNotificationMeesage() function.  
   //    Typically, you would check the WPARAM parameter to determine the nature of the notification.
   //      WPARAM == port_forward::EnumPortRetrieveInterval is sent at intervals, where
   //        LPARAM goes from 0 to 10.  You can use this to update a progress control (if you want)
   //      WPARAM == port_forward::EnumPortRetrieveDone is sent when the thread is done, where 
   //        LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).  Call the 
   //        GetPortMappingVector() function to get a copy of the current contents of
   //        std::vector< port_forward::port_map > m_MappingContainer

   BOOL port_forward::GetMappingsUsingThread( HWND hWnd )
   {
	   // returns TRUE if thread was started successfully
	
	   if ( (m_pPortMappingThread!=NULL) || (hWnd==NULL) || (!IsWindow(hWnd)) )
		   return FALSE;
	
	   m_hWndForPortMappingThread = hWnd;
	
	   m_pPortMappingThread = ::AfxBeginThread(get_app(), ThreadForPortRetrieval, this,
		   THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED );
	
	   if ( m_pPortMappingThread != NULL )
	   {
		   m_pPortMappingThread->ResumeThread();
		   return TRUE;
	   }
	   else
	   {
		   return FALSE;
	   }
   }


   ///////////////////////////////////////////////
   //
   //  EditMappingUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the EditMappingUsingThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION 
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumEditMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumEditMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL). 


   BOOL port_forward::EditMappingUsingThread( port_forward::port_map& oldMapping, port_forward::port_map& newMapping, HWND hWnd )
   {
	   // returns TRUE if thread was started successfully
	
	   if ( (m_pEditMappingThread!=NULL) || (hWnd==NULL) || (!IsWindow(hWnd)) )
		   return FALSE;
	
	   m_scratchpadOldMapping = oldMapping;
	   m_scratchpadNewMapping = newMapping;	
	
	   m_hWndForEditMappingThread = hWnd;
	
	   m_pEditMappingThread = ::AfxBeginThread(get_app(), ThreadToEditMapping, this, THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED );
	
	   if ( m_pEditMappingThread != NULL )
	   {
		   m_pEditMappingThread->ResumeThread();
		   return TRUE;
	   }
	   else
	   {
		   return FALSE;
	   }
	
   }



   ///////////////////////////////////////////////
   //
   //  AddMappingUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the AddMappingUsingThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION 
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumAddMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumAddMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL). 

   BOOL port_forward::AddMappingUsingThread( port_forward::port_map& newMapping, HWND hWnd )
   {
	   // returns TRUE if thread was started successfully
	
	   if ( (m_pAddMappingThread!=NULL) || (hWnd==NULL) || (!IsWindow(hWnd)) )
		   return FALSE;
	
	   m_scratchpadAddedMapping = newMapping;	
	
	   m_hWndForAddMappingThread = hWnd;
	
	   m_pAddMappingThread = ::AfxBeginThread(get_app(), ThreadToAddMapping, this, THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED);
	
	   if ( m_pAddMappingThread != NULL )
	   {
		   m_pAddMappingThread->ResumeThread();
		   return TRUE;
	   }
	   else
	   {
		   return FALSE;
	   }
	
   }



   ///////////////////////////////////////////////
   //
   //  DeleteMappingUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the DeleteMappingUsingThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION 
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumDeleteMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumDeleteMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL). 

   BOOL port_forward::DeleteMappingUsingThread( port_forward::port_map& oldMapping, HWND hWnd )
   {
	   // returns TRUE if thread was started successfully
	
	   if ( (m_pDeleteMappingThread!=NULL) || (hWnd==NULL) || (!IsWindow(hWnd)) )
		   return FALSE;
	
	   m_scratchpadDeletedMapping = oldMapping;
	
	   m_hWndForDeleteMappingThread = hWnd;
	
	   m_pDeleteMappingThread = ::AfxBeginThread(get_app(), ThreadToDeleteMapping, this, THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED );
	
	   if ( m_pDeleteMappingThread != NULL )
	   {
		   m_pDeleteMappingThread->ResumeThread();
		   return TRUE;
	   }
	   else
	   {
		   return FALSE;
	   }
	
   }


   ///////////////////////////////////////////////
   //
   //  GetDeviceInformationUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the GetDeviceInformationUsingThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION 
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumDeviceInfoInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumDeviceInfoDone when thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).  Call the 
   //      GetDeviceInformationContainer() function to retrieve a copy of the current contents of 
   //      port_forward::DeviceInformationContainer m_DeviceInfo

   BOOL port_forward::GetDeviceInformationUsingThread( HWND hWnd )
   {	
	   // returns TRUE if thread was started successfully
	
	   if ( (m_pDeviceInfoThread!=NULL) || (hWnd==NULL) || (!IsWindow(hWnd)) )
		   return FALSE;
	
	   m_hWndForDeviceInfoThread = hWnd;
	
	   m_pDeviceInfoThread = ::AfxBeginThread(get_app(), ThreadForDeviceInformationRetrieval, this,  THREAD_PRIORITY_BELOW_NORMAL, 0, CREATE_SUSPENDED );
	
	   if ( m_pDeviceInfoThread != NULL )
	   {
		   m_pDeviceInfoThread->ResumeThread();
		   return TRUE;
	   }
	   else
	   {
		   return FALSE;
	   }
	
   }




   /*   static   */
   UINT port_forward::ThreadForPortRetrieval(LPVOID pVoid)
   {	
	   SetThreadName( -1, "PortRtrv" );  // helps in debugging to see a thread's name

	   BOOL bContinue = TRUE;
	
	   port_forward* pThis = (port_forward*)pVoid;
	
	   // local copies of shared variables
	
	   HWND hWndForPosting = pThis->m_hWndForPortMappingThread;

	   WPARAM wp = EnumPortRetrieveInterval;
	   LPARAM lp = 0;
	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   // initialize COM
	
	   if ( !SUCCEEDED( CoInitialize(NULL) ) )  // STA model
		   bContinue = FALSE;
	
	
	   // create COM instance of IUPnPNAT
	
	   IUPnPNAT* piNAT = NULL;
	   IStaticPortMappingCollection* piPortMappingCollection = NULL;	


      HRESULT hr;
	
	   if ( !bContinue || !SUCCEEDED(hr= CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==NULL ) )
		   bContinue = FALSE;
	
	   // Get the collection of forwarded ports 
	
	   if ( !bContinue || !SUCCEEDED(hr= piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==NULL ) )
		   bContinue = FALSE;
	
	
	   lp = 1;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   // Get mapping enumerator and reset the list of mappings
	
	   IUnknown* piUnk = NULL;
	   IEnumVARIANT* piEnumerator = NULL;
	
	   if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get__NewEnum( &piUnk ) ) || piUnk==NULL )
		   bContinue = FALSE;
	
	   if ( !bContinue || !SUCCEEDED( piUnk->QueryInterface(IID_IEnumVARIANT, (void **)&piEnumerator) ) || piEnumerator==NULL )
		   bContinue = FALSE;
	
	   if ( !bContinue || !SUCCEEDED( piEnumerator->Reset() ) )
		   bContinue = FALSE;
	
	   lp = 2;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // get count of static mappings
	
	   long cMappings = 0;
	
	   if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get_Count( &cMappings ) ) )
		   bContinue = FALSE;
	
	   if ( cMappings <= 0 ) cMappings = 4;  // arbitrary non-zero value, so we can divide by non-zero value
	
	   lp = 3;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   HRESULT result = S_OK;
	   int iii = 0;
	
	   // clear all current mappings (note: thread-awareness is needed)
	
	   ::EnterCriticalSection( &(pThis->m_cs) );
	   pThis->m_MappingContainer.remove_all();
	   ::LeaveCriticalSection( &(pThis->m_cs) );
	
	   port_forward::port_map mapCont;
	
	   while ( bContinue && SUCCEEDED(result) )
	   {
		   result = pThis->GetNextMapping( piEnumerator, mapCont );
		   if ( SUCCEEDED(result) )
		   {
			   ::EnterCriticalSection( &(pThis->m_cs) );
			   pThis->m_MappingContainer.add( mapCont );
			   ::LeaveCriticalSection( &(pThis->m_cs) );
		   }
		
		   lp = 3 + (10-3)*(++iii)/cMappings;
		   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	   }
	
	   // release COM objects and de-initialize COM
	
	   if ( piEnumerator != NULL )
	   {
		   piEnumerator->Release();
		   piEnumerator = NULL;
	   }
	
	   if ( piPortMappingCollection != NULL )
	   {
		   piPortMappingCollection->Release();
		   piPortMappingCollection = NULL;
	   }
	
	   if ( piNAT != NULL )
	   {
		   piNAT->Release();
		   piNAT = NULL;
	   }
	
	
	   CoUninitialize();
	
	   // post completion message
	
	   lp = (bContinue ? S_OK : E_FAIL);
	   wp = EnumPortRetrieveDone;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   pThis->m_pPortMappingThread = NULL;
	   pThis->m_hWndForPortMappingThread = NULL;
	
	
	   return 0;
   }


   /*   static   */
   UINT port_forward::ThreadForDeviceInformationRetrieval( LPVOID pVoid )
   {
	   SetThreadName( -1, "DevInfo" );  // helps in debugging to see a thread's name
	
	   BOOL bContinue = TRUE;

	   port_forward* pThis = (port_forward*)pVoid;

	   // local copies of shared variables

	   HWND hWndForPosting = pThis->m_hWndForDeviceInfoThread;

	   WPARAM wp = EnumDeviceInfoInterval;
	   LPARAM lp = 0;	
	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // initialize COM
	
	   if ( !SUCCEEDED( CoInitialize(NULL) ) )  // STA model
		   bContinue = FALSE;
	
	   // create COM instance of IUPnPDeviceFinder
	
	   IUPnPDeviceFinder* piDeviceFinder = NULL;
	
	   if ( !bContinue || !SUCCEEDED( CoCreateInstance( CLSID_UPnPDeviceFinder, NULL, CLSCTX_ALL, 
		   IID_IUPnPDeviceFinder, (void**) &piDeviceFinder ) ) || ( piDeviceFinder==NULL ) )
		   bContinue = FALSE;
	
	   lp = 1;	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // get devices of the desired type, using the PnP schema
	   // < deviceType>urn:schemas-upnp-org:device:InternetGatewayDevice:1< /deviceType>
	
	   BSTR bStrDev = SysAllocString( L"urn:schemas-upnp-org:device:InternetGatewayDevice:1" );
	   IUPnPDevices* piFoundDevices = NULL;
	
	   if ( !bContinue || !SUCCEEDED( piDeviceFinder->FindByType( bStrDev, 0, &piFoundDevices ) ) 
		   || ( piFoundDevices==NULL ) )
		   bContinue = FALSE;
    
	   SysFreeString( bStrDev );
	
	
	   lp = 5;	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // now traverse the collection of piFoundDevices
	
	   // the following code is based on code provided by MSDN in its Control Point API:
	   // "Device Collections Returned By Synchronous Searches" at
	   // http://msdn.microsoft.com/library/en-us/upnp/upnp/device_collections_returned_by_synchronous_searches.asp
	
	
	   HRESULT result = S_OK;	
      IUnknown * pUnk = NULL;

	   // remove all local devInfo from class member
	
      ::EnterCriticalSection( &(pThis->m_cs) );
	   pThis->m_DeviceInfo.remove_all();
	   ::LeaveCriticalSection( &(pThis->m_cs) );
	   
	
       if ( bContinue && SUCCEEDED( piFoundDevices->get__NewEnum(&pUnk) ) && ( pUnk!=NULL ) )
       {
           IEnumVARIANT * pEnumVar = NULL;
           result = pUnk->QueryInterface(IID_IEnumVARIANT, (void **) &pEnumVar);
           if (SUCCEEDED(result))
           {
               VARIANT varCurDevice;
               VariantInit(&varCurDevice);
               pEnumVar->Reset();
               // Loop through each device in the collection
               while (S_OK == pEnumVar->Next(1, &varCurDevice, NULL))
               {
                   IUPnPDevice * pDevice = NULL;
                   IDispatch * pdispDevice = V_DISPATCH(&varCurDevice);
                   if (SUCCEEDED(pdispDevice->QueryInterface(IID_IUPnPDevice, (void **) &pDevice)))
                   {
					   // finally, post interval notification message and get all the needed information
					
					   lp = 6;
					   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );

	               // allocate and fill local devInfo into class member
                  ::EnterCriticalSection( &(pThis->m_cs) );
                  device * pdevice = pThis->m_DeviceInfo.add_new();
   			      result = pThis->PopulateDeviceInfoContainer( pDevice, *pdevice, hWndForPosting );
            	   ::LeaveCriticalSection( &(pThis->m_cs) );
					
                   }
                   VariantClear(&varCurDevice);
               }
               pEnumVar->Release();
           }
           pUnk->Release();
       }
	
	
	   // release COM objects and de-initialize COM
	
	   if ( piDeviceFinder!=NULL )
	   {
		   piDeviceFinder->Release();
		   piDeviceFinder = NULL;
	   }
	
	   CoUninitialize();
	
	   bContinue = SUCCEEDED( result );
	
	
	
	   // post completion message
	
	   lp = (bContinue ? S_OK : E_FAIL);
	   wp = EnumDeviceInfoDone;
	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   pThis->m_pDeviceInfoThread = NULL;
	   pThis->m_hWndForDeviceInfoThread = NULL;
	
	   return 0;
   }


   /*   static   */
   UINT port_forward::ThreadToEditMapping( LPVOID pVoid )
   {	
	   SetThreadName( -1, "EditMap" );  // helps in debugging to see a thread's name
	
	   BOOL bContinue = TRUE;

	   port_forward* pThis = (port_forward*)pVoid;

	   // local copies of shared variables
	
	   port_map oldMapping = pThis->m_scratchpadOldMapping;
	   port_map newMapping = pThis->m_scratchpadNewMapping;
	   HWND hWndForPosting = pThis->m_hWndForEditMappingThread;
	
	   WPARAM wp = EnumEditMappingInterval;
	   LPARAM lp = 0;
	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   // initialize COM
	
	   if ( !SUCCEEDED( CoInitialize(NULL) ) )  // STA model
		   bContinue = FALSE;
	
	
	   // create COM instance of IUPnPNAT
	
	   IUPnPNAT* piNAT = NULL;
	   IStaticPortMappingCollection* piPortMappingCollection = NULL;	
	
	   if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==NULL ) )
		   bContinue = FALSE;
	
	   // Get the collection of forwarded ports 
	
	   if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==NULL ) )
		   bContinue = FALSE;
	
	
	   lp = 1;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // get the target old mapping from the collection of mappings
	
	   IStaticPortMapping* piStaticPortMapping = NULL;
	
	   if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get_Item( _ttol(oldMapping.ExternalPort), oldMapping.Protocol.AllocSysString(), &piStaticPortMapping ) ) || (piStaticPortMapping==NULL) )
		   bContinue = FALSE;
	
	   oldMapping.Protocol.ReleaseBuffer();
	
	
	   lp = 2;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // update the mapping
	
	   if ( bContinue )
	   {
		   HRESULT hr = S_OK;
		   VARIANT_BOOL vb = ( ( newMapping.Enabled == _T("Yes") ) ? VARIANT_TRUE : VARIANT_FALSE );
		
		   hr |= piStaticPortMapping->Enable( vb );
		   lp = 4;
		   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
		
         hr |= piStaticPortMapping->EditDescription( newMapping.Description.AllocSysString() );
		   lp = 6;
		   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
		
		   hr |= piStaticPortMapping->EditInternalPort( _ttol(newMapping.InternalPort) );
		   lp = 8;
		   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
		
         hr |= piStaticPortMapping->EditInternalClient( newMapping.InternalClient.AllocSysString() );
		   lp = 10;
		   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
		
		   if ( !SUCCEEDED(hr) )
			   bContinue = FALSE;
	   }
	
	
	   // clean up and de-initialize COM
	
	   if ( piStaticPortMapping != NULL )
	   {
		   piStaticPortMapping->Release();
		   piStaticPortMapping = NULL;
	   }
	
	
	   if ( piPortMappingCollection != NULL )
	   {
		   piPortMappingCollection->Release();
		   piPortMappingCollection = NULL;
	   }
	
	   if ( piNAT != NULL )
	   {
		   piNAT->Release();
		   piNAT = NULL;
	   }
	
	
	   CoUninitialize();
	
	   // post completion message
	
	   lp = (bContinue ? S_OK : E_FAIL);
	   wp = EnumEditMappingDone;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   pThis->m_pEditMappingThread = NULL;
	   pThis->m_hWndForEditMappingThread = NULL;
	
	   return 0;
   }

   /*   static   */
   UINT port_forward::ThreadToDeleteMapping( LPVOID pVoid )
   {	
	   SetThreadName( -1, "DelMap" );  // helps in debugging to see a thread's name

	   BOOL bContinue = TRUE;
	
	   port_forward* pThis = (port_forward*)pVoid;
	
	   // local copies of shared variables

	   port_map oldMapping = pThis->m_scratchpadDeletedMapping;
	   HWND hWndForPosting = pThis->m_hWndForDeleteMappingThread;
		
	   WPARAM wp = EnumDeleteMappingInterval;
	   LPARAM lp = 0;
	
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   // initialize COM
	
	   if ( !SUCCEEDED( CoInitialize(NULL) ) )  // STA model
		   bContinue = FALSE;
	
	
	   // create COM instance of IUPnPNAT
	
	   IUPnPNAT* piNAT = NULL;
	   IStaticPortMappingCollection* piPortMappingCollection = NULL;	
	
	   if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==NULL ) )
		   bContinue = FALSE;
	
	   // Get the collection of forwarded ports 
	
	   if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==NULL ) )
		   bContinue = FALSE;
	
	
	   lp = 1;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // get the target old mapping from the collection of mappings
	
	   if ( !bContinue || 
         !SUCCEEDED( piPortMappingCollection->Remove( _ttol(oldMapping.ExternalPort), oldMapping.Protocol.AllocSysString() ) ) )
		   bContinue = FALSE;
	
	   oldMapping.Protocol.ReleaseBuffer();
	   lp = 2;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	
	   // clean up and de-initialize COM
	
	
	   if ( piPortMappingCollection != NULL )
	   {
		   piPortMappingCollection->Release();
		   piPortMappingCollection = NULL;
	   }
	
	   if ( piNAT != NULL )
	   {
		   piNAT->Release();
		   piNAT = NULL;
	   }
	
	
	   CoUninitialize();
	
	   // post completion message
	
	   lp = (bContinue ? S_OK : E_FAIL);
	   wp = EnumDeleteMappingDone;
	   ::PostMessage( hWndForPosting, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   pThis->m_pDeleteMappingThread = NULL;
	   pThis->m_hWndForDeleteMappingThread = NULL;
	
	   return 0;
   }


   /*   static   */
   UINT port_forward::ThreadToAddMapping( LPVOID pVoid )
   {
	   SetThreadName( -1, "AddMap" );  // helps in debugging to see a thread's name
	
	   port_forward* pThis = (port_forward*)pVoid;
	
	   port_map& newMapping = pThis->m_scratchpadAddedMapping;
	
	
	   BOOL bContinue = TRUE;
	   WPARAM wp = EnumAddMappingInterval;
	   LPARAM lp = 0;
	
	   ::PostMessage( pThis->m_hWndForAddMappingThread, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   // initialize COM
	
	   if ( !SUCCEEDED( CoInitialize(NULL) ) )  // STA model
		   bContinue = FALSE;
	
	
	   // create COM instance of IUPnPNAT
	
	   IUPnPNAT* piNAT = NULL;
	   IStaticPortMappingCollection* piPortMappingCollection = NULL;	
	
	   if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), NULL, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==NULL ) )
		   bContinue = FALSE;
	
	   // Get the collection of forwarded ports 
	
	   if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==NULL ) )
		   bContinue = FALSE;
	
	
	   lp = 1;
	   ::PostMessage( pThis->m_hWndForAddMappingThread, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	   // add the new mapping
	
	   IStaticPortMapping* piStaticPortMapping = NULL;
	
	   VARIANT_BOOL vb = ( ( newMapping.Enabled == _T("Yes") ) ? VARIANT_TRUE : VARIANT_FALSE );
	
	   if ( !bContinue || 
         !SUCCEEDED( 
               piPortMappingCollection->Add(
                  _ttol(newMapping.ExternalPort), 
                  newMapping.Protocol.AllocSysString() , 
                  _ttol(newMapping.InternalPort),  
                  newMapping.InternalClient.AllocSysString(),
                  vb,
                  newMapping.Description.AllocSysString(),
		            &piStaticPortMapping ) ) || (piStaticPortMapping==NULL) )
		
		   bContinue = FALSE;
	
	   newMapping.Protocol.ReleaseBuffer();
	   newMapping.InternalClient.ReleaseBuffer();
	   newMapping.Description.ReleaseBuffer();
	
	   lp = 2;
	   ::PostMessage( pThis->m_hWndForAddMappingThread, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	
	
	   // clean up and de-initialize COM
	
	   if ( piStaticPortMapping != NULL )
	   {
		   piStaticPortMapping->Release();
		   piStaticPortMapping = NULL;
	   }
	
	
	   if ( piPortMappingCollection != NULL )
	   {
		   piPortMappingCollection->Release();
		   piPortMappingCollection = NULL;
	   }
	
	   if ( piNAT != NULL )
	   {
		   piNAT->Release();
		   piNAT = NULL;
	   }
	
	
	   CoUninitialize();
	
	   // post completion message
	
	   lp = (bContinue ? S_OK : E_FAIL);
	   wp = EnumAddMappingDone;
	   ::PostMessage( pThis->m_hWndForAddMappingThread, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, lp );
	
	   pThis->m_pAddMappingThread = NULL;
	   pThis->m_hWndForAddMappingThread = NULL;
	
	   return 0;
   }



   HRESULT port_forward::GetNextMapping( IEnumVARIANT* piEnumerator, port_forward::port_map& mappingContainer )
   {
	   // uses the enumerator to get the next mapping and fill in a mapping container structure
	
	   if ( piEnumerator == NULL )
	   {
		   return E_FAIL;
	   }
	
	   VARIANT varCurMapping;
	   VariantInit(&varCurMapping);
	
	   HRESULT result = piEnumerator->Next( 1, &varCurMapping, NULL);
	   if( !SUCCEEDED(result) )
	   {
		   return E_FAIL;
	   }
	
	   if ( varCurMapping.vt == VT_EMPTY )
	   {
		   return E_FAIL;
	   }
	
	   IStaticPortMapping* piMapping = NULL;
	   IDispatch* piDispMap = V_DISPATCH(&varCurMapping);
	   result = piDispMap->QueryInterface(IID_IStaticPortMapping, (void **)&piMapping);
	   if( !SUCCEEDED(result) )
	   {
		   return E_FAIL;
	   }
	
	
	   // get external address
	
	   BSTR bStr = NULL;
	
	   result = piMapping->get_ExternalIPAddress( &bStr );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   if( bStr != NULL )
		   mappingContainer.ExternalIPAddress = string( gen::international::unicode_to_utf8(bStr) );
	
	   SysFreeString(bStr);
	   bStr = NULL;
	
	
	   // get external port
	
	   long lValue = 0;
	
	   result = piMapping->get_ExternalPort( &lValue );
	   if( !SUCCEEDED(result) )
	   {	
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   mappingContainer.ExternalPort.Format( _T("%d"), lValue );
	
	
	   // get internal port
	
	   result = piMapping->get_InternalPort( &lValue );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   mappingContainer.InternalPort.Format( _T("%d"), lValue );
	
	
	   // get protocol
	
	   result = piMapping->get_Protocol( &bStr );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   if( bStr != NULL )
		   mappingContainer.Protocol = gen::international::unicode_to_utf8(bStr);
	
	   SysFreeString(bStr);
	   bStr = NULL;
	
	
	   // get internal client
	
	   result = piMapping->get_InternalClient( &bStr );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   if( bStr != NULL )
		   mappingContainer.InternalClient = gen::international::unicode_to_utf8(bStr);
	
	   SysFreeString(bStr);
	   bStr = NULL;
	
	
	   // determine whether it's enabled
	
	   VARIANT_BOOL bValue = VARIANT_FALSE;
	
	   result = piMapping->get_Enabled( &bValue );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   mappingContainer.Enabled = bValue==VARIANT_FALSE ? "No" : "Yes" ;
	
	
	   // get description
	
	   result = piMapping->get_Description( &bStr );
	   if( !SUCCEEDED(result) )
	   {
		   piMapping->Release();
		   piMapping = NULL;
		   return E_FAIL;
	   }
	
	   if( bStr != NULL )
		   mappingContainer.Description = gen::international::unicode_to_utf8( bStr );
	
	   SysFreeString(bStr);
	   bStr = NULL;
	
	   // clean up
	
	   piMapping->Release();
	   piMapping = NULL;
	
	
	   VariantClear( &varCurMapping );
	
	   return S_OK;
	
   }



   HRESULT port_forward::PopulateDeviceInfoContainer( IUPnPDevice* piDevice, 
				   port_forward::device & deviceInfo, HWND hWnd /* =NULL */ )
   {
	
	   HRESULT result=S_OK, hrReturn=S_OK;
	   long lValue = 0;
	   BSTR bStr = NULL;
	   VARIANT_BOOL bValue = VARIANT_FALSE;
	   IUPnPDevices* piDevices = NULL;
	
	   // parameters for interval notification messages
	
	   double lp = 6.0;
	   double addend = (10.0 - 6.0)/19.0;  // there are 19 parameters that are retrieved, and we already sent 6 notifications
	   WPARAM wp = EnumDeviceInfoInterval;
	
	
	   // get children: We will NOT enumerate through the devices that might be returned.
	   // Rather, we will only indicate how many there are.  So, in this sense, the information
	   // is somewhat redundant to HasChildren
	
	   result = piDevice->get_Children( &piDevices );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) && (piDevices!=NULL) )
	   {
		   piDevices->get_Count( &lValue );
		   if ( lValue==0 )
		   {
			   deviceInfo.Children.Format( _T("No: Zero children") );
		   }
		   else if ( lValue==1 )
		   {
			   deviceInfo.Children.Format( _T("Yes: One child") );
		   }
		   else if ( lValue>=1 )
		   {
			   deviceInfo.Children.Format( _T("Yes: %d children"), lValue );
		   }
		   piDevices->Release();
		   piDevices = NULL;
		   lValue = 0;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get Description
	
	   result = piDevice->get_Description( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.Description = gen::international::unicode_to_utf8( bStr );
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
      {
		   BOOL b = ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
         if(!b)
         {
            DWORD dw = ::GetLastError();
            ::MessageBoxA(NULL, gen::str::itoa(dw), gen::str::itoa(dw), 0);
         }
      }
	
	
	   // Get FriendlyName
	
	   result = piDevice->get_FriendlyName( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.FriendlyName = gen::international::unicode_to_utf8(bStr );	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get HasChildren
	
	   result = piDevice->get_HasChildren( &bValue );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.HasChildren = bValue==VARIANT_FALSE  ? "No" : "Yes";
		   bValue = VARIANT_FALSE;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get IconURL
	
	   BSTR bStrMime = SysAllocString(L"image/png");
	
	   //result = piDevice->IconURL( bStrMime, 32, 32, 8, &bStr );
      result = piDevice->IconURL( bStrMime, 48, 48, 24, &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.IconURL = gen::international::unicode_to_utf8( bStr );	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   SysFreeString(bStrMime);
	   bStrMime = NULL;
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get IsRootDevice
	
	   result = piDevice->get_IsRootDevice( &bValue );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.IsRootDevice = bValue==VARIANT_FALSE ? "No" : "Yes";
		   bValue = VARIANT_FALSE;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ManufacturerName
	
	   result = piDevice->get_ManufacturerName( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.ManufacturerName = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ManufacturerURL
	
	   result = piDevice->get_ManufacturerURL( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.ManufacturerURL = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ModelName
	
	   result = piDevice->get_ModelName( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.ModelName = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ModelNumber
	
	   result = piDevice->get_ModelNumber( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.ModelNumber = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ModelURL
	
	   result = piDevice->get_ModelURL( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.ModelURL = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get ParentDevice.  Actually, we will only get the FriendlyName of the parent device,
	   // if there is one
	
	   IUPnPDevice* piDev = NULL;
	
	   result = piDevice->get_ParentDevice( &piDev );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   if ( piDev==NULL )
		   {
			   deviceInfo.ParentDevice.Format( _T("This is a topmost device") );
		   }
		   else
		   {
			   if ( SUCCEEDED( piDev->get_FriendlyName( &bStr ) ) )
			   {
				   deviceInfo.ParentDevice = gen::international::unicode_to_utf8(bStr);
				   SysFreeString(bStr);
				   bStr = NULL;
			   }
			   piDev->Release();
			   piDev = NULL;
		   }
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get PresentationURL
	
	   result = piDevice->get_PresentationURL( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.PresentationURL = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get RootDevice.  Actually, we will only get the FriendlyName of the root device,
	   // if there is one
	
	   result = piDevice->get_RootDevice( &piDev );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   if ( piDev==NULL )
		   {
			   deviceInfo.RootDevice.Format( _T("This is a topmost device") );
		   }
		   else
		   {
			   if ( SUCCEEDED( piDev->get_FriendlyName( &bStr ) ) )
			   {
				   deviceInfo.RootDevice = gen::international::unicode_to_utf8(bStr );
				   SysFreeString(bStr);
				   bStr = NULL;
			   }
			   piDev->Release();
			   piDev = NULL;
		   }
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	
	   // Get SerialNumber
	
	   result = piDevice->get_SerialNumber( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.SerialNumber = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get Services.  Actually, we will NOT enumerate through all the services that are contained
	   // in the IUPnPServices collection.  Rather, we will only get a count of services
	
	   IUPnPServices* piServices = NULL;
	
	   result = piDevice->get_Services( &piServices );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) && (piServices!=NULL) )
	   {
		   piServices->get_Count( &lValue );
		   if ( lValue==0 )
		   {
			   deviceInfo.Services.Format( _T("No: Zero services") );
		   }
		   else if ( lValue==1 )
		   {
			   deviceInfo.Services.Format( _T("Yes: One service") );
		   }
		   else if ( lValue>=1 )
		   {
			   deviceInfo.Services.Format( _T("Yes: %d services"), lValue );
		   }
		   piServices->Release();
		   piServices = NULL;
		   lValue = 0;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get Type
	
	   result = piDevice->get_Type( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.Type = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get UniqueDeviceName
	
	   result = piDevice->get_UniqueDeviceName( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
         deviceInfo.UniqueDeviceName = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	
	   // Get UPC
	
	   result = piDevice->get_UPC( &bStr );
	   hrReturn |= result;
	   if ( SUCCEEDED(result) )
	   {
		   deviceInfo.UPC = gen::international::unicode_to_utf8(bStr);	
		   SysFreeString(bStr);
		   bStr = NULL;
	   }
	
	   if ( hWnd!=NULL )
		   ::PostMessage( hWnd, UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, wp, (LPARAM)(lp += addend) );
	
	   return hrReturn;
   }











   HRESULT STDMETHODCALLTYPE port_forward::IDerivedNATNumberOfEntriesCallback::QueryInterface(REFIID iid, void ** ppvObject)
   {
	   HRESULT hr = S_OK;
	   *ppvObject = NULL;
	
	   if ( iid == IID_IUnknown ||	iid == IID_INATNumberOfEntriesCallback )
	   {
		   *ppvObject = this;
		   AddRef();
		   hr = NOERROR;
	   }
	   else
	   {
		   hr = E_NOINTERFACE;
	   }
	
	   return hr;
   }


   HRESULT STDMETHODCALLTYPE port_forward::IDerivedNATExternalIPAddressCallback::QueryInterface(REFIID iid, void ** ppvObject)
   {
	   HRESULT hr = S_OK;
	   *ppvObject = NULL;
	
	   if ( iid == IID_IUnknown ||	iid == IID_INATExternalIPAddressCallback )
	   {
		   *ppvObject = this;
		   AddRef();
		   hr = NOERROR;
	   }
	   else
	   {
		   hr = E_NOINTERFACE;
	   }
	
	   return hr;
   }

   /////////////////////////////////////////////////////////////////////
   //
   // SetThreadName -- a function to set the current thread's 8-character name
   // so as to be able to distinguish between the threads during debug operations
   //
   // Usage: SetThreadName (-1, "MainThread");
   // Must be called from the thread you're trying to name
   // For example SetThreadName(-1, "1st Thread");
   // Will truncate name to 8 characters
   //
   // code obtained from 
   // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vsdebug/html/vxtsksettingthreadname.asp
   //


   void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName)
   {
	
	   struct THREADNAME_INFO
	   {
		   DWORD dwType; // must be 0x1000
		   LPCSTR szName; // pointer to name (in user addr space)
		   DWORD dwThreadID; // thread ID (-1=caller thread)
		   DWORD dwFlags; // reserved for future use, must be zero
	   } ;
	
	   THREADNAME_INFO info;
	   info.dwType = 0x1000;
	   info.szName = szThreadName;
	   info.dwThreadID = dwThreadID;
	   info.dwFlags = 0;
	
	   __try
	   {
		   RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR*)&info );
	   }
	   __except(EXCEPTION_CONTINUE_EXECUTION)
	   {
	   }
   }


} // namespace win

