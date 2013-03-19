#include "framework.h"


CLASS_DECL_ca int32_t ca2_main();

//CLASS_DECL_ca extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_ca fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_mac __cdecl _ca2_purecall()
{
   throw simple_exception(::ca::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);


//::ca::application *     win_application_create(::ca::application * pappSystem, const char * pszId);
//::ca::application *     win_instantiate_application(::ca::application * pappSystem, const char * pszId);
//int32_t                     win_application_procedure(::ca::application * pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as '::ca::WinInit' is called first

int32_t CLASS_DECL_mac __mac_main(int32_t argc, char * argv[])
{
   
   //   UNREFERENCED_PARAMETER(lpCmdLine);
   
   
   
   
   //   ::CoInitialize(NULL);
   
   
   //throw todo(::ca::get_thread_app());
   
   if(!main_initialize())
      return -1;
   
   
   //   _set_purecall_handler(_ca2_purecall);
   
   ::plane::system * psystem = new ::plane::system();
   
   //   ASSERT(hPrevInstance == NULL);
   
   int32_t nReturnCode = 0;
   
   
   ::mac::main_init_data * pinitmaindata  = new ::mac::main_init_data;
   
   
   pinitmaindata->m_hInstance             = NULL;
   pinitmaindata->m_hPrevInstance         = NULL;
   for(int32_t i = 0; i < argc; i++)
   {
      pinitmaindata->m_strCommandLine     += argv[i];
   }
   pinitmaindata->m_nCmdShow              = SW_SHOW;
   
   
   psystem->init_main_data(pinitmaindata);
   
   //MessageBox(NULL, "box1", "box1", MB_ICONINFORMATION);
   
   nReturnCode = psystem->main();
   
   
   try
   {
      main_finalize();
   }
   catch(...)
   {
   }
   
   try
   {
      __mac_term();
   }
   catch(...)
   {
   }
   
   
   try
   {
      delete psystem;
   }
   catch(...)
   {
   }
   
   psystem = NULL;
   
   
   try
   {
      //      delete __get_module_state()->m_pmapHWND;
   }
   catch(...)
   {
   }
   /*   try
    {
    delete __get_module_state()->m_pmapHDC;
    }
    catch(...)
    {
    }*/
   /*   try
    {
    delete __get_module_state()->m_pmapHGDIOBJ;
    }
    catch(...)
    {
    }*/
   //      delete __get_module_state()->m_pmapHMENU;
   
   try
   {
      __get_module_state()->m_pmapHWND     = NULL;
   }
   catch(...)
   {
   }
   /*   try
    {
    __get_module_state()->m_pmapHDC      = NULL;
    }
    catch(...)
    {
    }*/
   /*   try
    {
    __get_module_state()->m_pmapHGDIOBJ  = NULL;
    }
    catch(...)
    {
    }*/
   
   
   set_heap_mutex(NULL);
   
   return nReturnCode;
   
   
}


int32_t CLASS_DECL_mac ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{
   try
   {
      
      //      _set_purecall_handler(_ca2_purecall);
      
      ::plane::system * psystem = new ::plane::system();
      
      
      //Sleep(30 * 1000);
      
      
      ASSERT(hPrevInstance == NULL);
      
      int32_t nReturnCode = 0;
      
      ::mac::main_init_data * pinitmaindata  = new ::mac::main_init_data;
      
      pinitmaindata->m_hInstance             = hInstance;
      pinitmaindata->m_hPrevInstance         = hPrevInstance;
      pinitmaindata->m_strCommandLine        = lpCmdLine;
      pinitmaindata->m_nCmdShow              = nCmdShow;
      
      
      psystem->init_main_data(pinitmaindata);
      
      
      nReturnCode = psystem->main();
      
      
      __mac_term();
      
      
      try
      {
         delete psystem;
      }
      catch(...)
      {
      }
      
      psystem = NULL;
      
      try
      {
         //         delete __get_module_state()->m_pmapHWND;
      }
      catch(...)
      {
      }
      /*      try
       {
       delete __get_module_state()->m_pmapHDC;
       }
       catch(...)
       {
       }*/
      /*      try
       {
       delete __get_module_state()->m_pmapHGDIOBJ;
       }
       catch(...)
       {
       }*/
      //      delete __get_module_state()->m_pmapHMENU;
      try
      {
         __get_module_state()->m_pmapHWND     = NULL;
      }
      catch(...)
      {
      }
      /*      try
       {
       __get_module_state()->m_pmapHDC      = NULL;
       }
       catch(...)
       {
       }
       try
       {
       __get_module_state()->m_pmapHGDIOBJ  = NULL;
       }
       catch(...)
       {
       }*/
      
      set_heap_mutex(NULL);
      
      
      return nReturnCode;
   }
   catch(...)
   {
   }
   return -1;
}



void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}
