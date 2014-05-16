//
//  main.cpp
//  app
//
//  Created by Thomas Borregaard Sørensen on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "app.h"


uint32_t __run_system(void * p)
{
   
   
   main_param * pparam = (main_param *) p;
   
   
   
   on_init_thread();
   
   int32_t nReturnCode = 0;
   
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
   
   
   
   on_term_thread();
   
   
   //   set_heap_mutex(NULL);
   
   exit(nReturnCode);
   
   return nReturnCode;
   
   
   
}


uint32_t __run_system(void * p);


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


