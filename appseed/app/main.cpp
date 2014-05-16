//
//  main.cpp
//  app
//
//  Created by Thomas Borregaard Sørensen on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "app.h"


void __node_init_app_state();



uint32_t __run_system(void * p)
{
   
   
   main_param * pparam = (main_param *) p;
   
   
   
   on_init_thread();
   
   __node_init_app_state();
   
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
   
   for(int32_t i = 0; i < pparam->argc; i++)
   {
      
      if(i > 0)
      {
         
         pinitmaindata->m_strCommandLine += " ";
         
      }
      
      if(strcmp(pparam->argv[i], ":") == 0)
      {
         
         pinitmaindata->m_strCommandLine     += ":";
         
         bColon = true;
         
      }
      else if(bColon)
      {
         
         pinitmaindata->m_strCommandLine     += pparam->argv[i];
         
         
      }
      else
      {
         
         pinitmaindata->m_strCommandLine     += "\"";
         
         pinitmaindata->m_strCommandLine     += pparam->argv[i];
         
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
   
   
   on_term_thread();
   
   
   //   set_heap_mutex(NULL);
   
   exit(nReturnCode);
   
   return nReturnCode;
   
   
   
}





uint32_t __run_system(void * p);

//::base::application *     win_application_create(::application * pappSystem, const char * pszId);
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
   
   main_param * pparam = new main_param;
   
   pparam->argc = argc;
   pparam->argv = argv;
   
   
   CreateThread(NULL, 0, __run_system, pparam, 0, 0);
   
   ns_app_run();
   
   return 0;
   
   
}



