#include "StdAfx.h"
#include "sal.h"

CLASS_DECL_ca int ca2_main();

//CLASS_DECL_ca extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_ca fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_VMSWIN __cdecl _ca2_purecall(void)
{
    throw simple_exception();
}

void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);


//::ca::application *     win_application_create(::ca::application * pappSystem, const char * pszId);
::ca::application *     win_instantiate_application(::ca::application * pappSystem, const char * pszId);
//int                     win_application_procedure(::ca::application * pappSystem)
//UINT AFX_CDECL          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as 'AfxWinInit' is called first

int CLASS_DECL_VMSWIN AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
   _set_purecall_handler(_ca2_purecall);

   set_heap_mutex(new mutex());

   ::icube::set_heap_itema(new class ::icube::system::heap_item_array());

   ::icube::system * psystem = ::icube::create_system();


   ASSERT(hPrevInstance == NULL);

   int nReturnCode = 0;

   ::win::main_init_data * pinitmaindata  = new ::win::main_init_data;

   pinitmaindata->m_hInstance             = hInstance;
   pinitmaindata->m_hPrevInstance         = hPrevInstance;
   pinitmaindata->m_strCmdLine            = lpCmdLine;
   pinitmaindata->m_nCmdShow              = nCmdShow;

   psystem->init_main_data(pinitmaindata);



//   if(!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
  //    return -1;

   nReturnCode = psystem->main();


   AfxWinTerm();

   // wish temporary dirty workaround to wait for other threads to exit
   Sleep(1984);

   delete AfxGetModuleState()->m_pmapHWND;

   ::icube::destroy_system(psystem);

   mutex * pmutex = get_heap_mutex();
   set_heap_mutex(NULL);


   BOOL bElevated = FALSE;
   if(VistaTools::IsVista() && SUCCEEDED(VistaTools::IsElevated(&bElevated)) && bElevated)
   {
      ::ExitProcess(nReturnCode);
   }
   


   return nReturnCode;
}


void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}






::ca::application * win_instantiate_application(::ca::application * pappSystem, const char * pszId)
{

   ::ca::application * papp = NULL;

   string strId(pszId);
   string strLibrary;
   strLibrary = strId + ".dll";
   HMODULE hmodule = LoadCa2Library(strLibrary);
   bool bRawCube = false;
   if(hmodule == NULL)
   {
      hmodule = LoadCa2Library("cube.dll");
      bRawCube = true;
   }
   LP_GET_NEW_APP  lpgetnewapp = NULL;
   if(hmodule != NULL && lpgetnewapp == NULL)
   {
#ifdef _M_X64
      lpgetnewapp = (LP_GET_NEW_APP) ::GetProcAddress(hmodule, "?get_new_app@@YAPEAVapplication@ca@@XZ");
#else
      lpgetnewapp = (LP_GET_NEW_APP) ::GetProcAddress(hmodule, "?get_new_app@@YAPAVapplication@ca@@XZ");
#endif
   }
   if(lpgetnewapp != NULL)
   {

      papp = lpgetnewapp();


      if(pappSystem != NULL)
         papp->set_app(pappSystem);
      else
         papp->set_app(papp);


      if(bRawCube)
      {
         papp->construct(strId);
      }

   }

   return papp;

}

