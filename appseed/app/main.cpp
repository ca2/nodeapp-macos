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
   
   
   if(!defer_base_init())
      return -1;
   
   
   int32_t nReturnCode = 0;
   
   
   sp(::plane::system) psystem = canew(::plane::system());
   
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
   
   bool bOk = true;
   
   try
   {
      
      if(psystem->pre_run())
      {
         
         bOk = true;
         
      }
      
   }
   catch(...)
   {
      
   }
   
   try
   {
      
      if(!bOk)
      {
         
         if(psystem->m_iReturnCode == 0)
         {
            
            return -1;
            
         }
         
         return psystem->m_iReturnCode;
         
      }
      
      
   }
   catch(...)
   {
      
      return -1;
      
   }
   
   
   nReturnCode = psystem->main();
   
   
   
   
   
   try
   {
      psystem.release();
   }
   catch(...)
   {
   }
   
   

   defer_base_term();
   
   exit(nReturnCode);
   
   return nReturnCode;
   
   
   
}


uint32_t __run_system(void * p);


int32_t CLASS_DECL_mac __mac_main(int32_t argc, char * argv[])
{
   
   setlocale(LC_ALL,"");
   
   ::base::static_start::init();
   
   ::multithreading::init_multithreading();
   
   ns_shared_application();
   
   main_param * pparam = new main_param;
   
   pparam->argc = argc;
   pparam->argv = argv;
   
   
   CreateThread(NULL, 0, __run_system, pparam, 0, 0);
   
   ns_app_run();
   
   return 0;
   
   
}



