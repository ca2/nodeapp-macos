#include "framework.h"

#include <crt_externs.h>
CLASS_DECL_mac int32_t ca2_main();

//CLASS_DECL_BOOT extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BOOT fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_mac __cdecl _ca2_purecall()
{
   throw simple_exception(::get_thread_app());
}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);


uint32_t __run_system(void * p);

//base_application *     win_application_create(::application * pappSystem, const char * pszId);
//::application *     win_instantiate_application(::application * pappSystem, const char * pszId);
//int32_t                     win_application_procedure(::application * pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as '::ca2::WinInit' is called first

int32_t CLASS_DECL_mac __mac_main(int32_t argc, char * argv[])
{

setlocale(LC_ALL,"");
   
   ns_shared_application();
   
   
   CreateThread(NULL, 0, __run_system, NULL, 0, 0);
   
   ns_app_run();
   
   return 0;
   
   
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
      
//      set_heap_mutex(NULL);
      
      
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



uint32_t __run_system(void * p)
{
   
   
   int32_t nReturnCode = 0;
   
   
   
   //   UNREFERENCED_PARAMETER(lpCmdLine);
   
   
   
   
   //   ::CoInitialize(NULL);
   
   
   //throw todo(::get_thread_app());
   
//   if(!main_initialize())
  //    return -1;
   
   
   //   _set_purecall_handler(_ca2_purecall);
   
   sp(::plane::system) psystem = canew(::plane::system());
   
   //   ASSERT(hPrevInstance == NULL);
   
   ::mac::main_init_data * pinitmaindata  = new ::mac::main_init_data;
   
   
   pinitmaindata->m_hInstance             = NULL;
   
   pinitmaindata->m_hPrevInstance         = NULL;
   
   bool bColon = false;
   
   for(int32_t i = 0; i < *_NSGetArgc(); i++)
   {
      
      if(i > 0)
      {
         
         pinitmaindata->m_strCommandLine += " ";

      }
      
      if(strcmp((*_NSGetArgv())[i], ":") == 0)
      {
      
         pinitmaindata->m_strCommandLine     += ":";
         
         bColon = true;
         
      }
      else if(bColon)
      {

         pinitmaindata->m_strCommandLine     += (*_NSGetArgv())[i];
         
         
      }
      else
      {

         pinitmaindata->m_strCommandLine     += "\"";
         
         pinitmaindata->m_strCommandLine     += (*_NSGetArgv())[i];
         
         pinitmaindata->m_strCommandLine     += "\"";
         
      }
      
   }
   pinitmaindata->m_vssCommandLine = pinitmaindata->m_strCommandLine;
   pinitmaindata->m_nCmdShow              = SW_SHOW;
   
   
   psystem->init_main_data(pinitmaindata);
   
   //MessageBox(NULL, "box1", "box1", MB_ICONINFORMATION);
   
   
   
   nReturnCode = psystem->main();
   
   
   try
   {
//      main_finalize();
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
      psystem.release();
   }
   catch(...)
   {
   }
   
   //   psystem = NULL;
   
   
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
   
   
//   set_heap_mutex(NULL);
   
   exit(nReturnCode);
   
   return nReturnCode;
   
   
   
}
