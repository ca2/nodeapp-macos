//
//  main.m
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "app.h"
#include "aura/aura/os/macos/macos.h"



int main(int argc, char *argv[])
{
   
   pid_t processid;
   
   processid=getpid();
   
   printf("\napplication_process_id=%d\n", processid);
   
   if(!defer_core_init())
   {

//      printf("app.exe failed miserably : !defer_core_init() < C lang... progamming is all about coding, verbs, and good (or perfect and precise, doesn't need enoughly \"good\", I let you choose... how powerful I think I am...) language...");
      
      return -1;
      
   }


      
      int iResult = base_main_command_line(":", argc, argv);
      
      try
      {
         
         defer_core_term();
         
      }
      catch(...)
      {
         
      }
      
      return iResult;
      
   }

////   ::output_debug_string("*****app.exe going on : defer_core_init() < C lang... progamming is all about coding, verbs, and good (or perfect and precise, doesn't need enoughly \"good\", I let you choose... how powerful I think I am...) language...");
//   
//   bool bInstall = false;
//   
//   bool bUninstall = false;
//   
//   output_debug_string("app.exe main()\n\n\n\n\n");
//   
//   for(index i = 0; i < argc; i++)
//   {
//
//      if(strcmp(argv[i], "install") == 0)
//      {
//         
//         bInstall = true;
//         
//      }
//      else if(strcmp(argv[i], "install") == 0)
//      {
//         
//         bUninstall = true;
//         
//      }
//      
//      output_debug_string("arg(" + ::str::from(i) + ") => " + string(argv[i]));
//      output_debug_string("\n");
//      
//   }
//   
//   output_debug_string("\n\n\n\n\n");
//
//   
//   if(bInstall)
//   {
//     
////      if(setuid(0) != 0)
//  //    {
////
//  //       return -3;
//    //
//      //}
//
//   }
//   else if(bUninstall)
//   {
//    
////      if(setuid(0) != 0)
//  //    {
//    //
//      //   return -3;
//        //
//      //}
//      
//   }
//   
////   fwrite(&processid,sizeof(processid),1,stdout);
//  // fflush(stdout);
//
//   
//   
//   main_param * v = new main_param;
//   
//   v->argc = argc;
//   
//   v->argv = argv;
//   
//   int iResult = __run_system_main_param(v);
//   
//   try
//   {
//      
//      defer_core_term();
//      
//   }
//   catch(...)
//   {
//      
//   }
//
//   return iResult;
//   
//}


//int32_t ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
//{
//   
//   
//
//   try
//   {
//      
//      ::core::system * psystem = new ::core::system();
//      
//      ASSERT(hPrevInstance == NULL);
//      
//      int32_t nReturnCode = 0;
//      
//      ::macos::main_init_data * pinitmaindata  = new ::macos::main_init_data;
//      
//      pinitmaindata->m_hInstance             = hInstance;
//      
//      pinitmaindata->m_hPrevInstance         = hPrevInstance;
//      
//      pinitmaindata->m_strCommandLine        = lpCmdLine;
//
//      pinitmaindata->m_nCmdShow              = nCmdShow;
//      
//      psystem->init_main_data(pinitmaindata);
//
//      bool bOk = false;
//      
//      try
//      {
//      
//         if(psystem->pre_run())
//         {
//            
//            bOk = true;
//         
//         }
//         
//      }
//      catch(...)
//      {
//         
//      }
//      
//      try
//      {
//         
//         if(!bOk)
//         {
//      
//            if(psystem->m_iErrorCode == 0)
//            {
//         
//               return -1;
//            
//            }
//            
//            return psystem->m_iErrorCode;
//            
//         }
//         
//         
//      }
//      catch(...)
//      {
//         
//         return -1;
//         
//      }
// 
//      
//      nReturnCode = psystem->main();
//      
//      try
//      {
//         
//         delete psystem;
//         
//      }
//      catch(...)
//      {
//      
//      }
//      
//      psystem = NULL;
//      
//      return nReturnCode;
//      
//   }
//   catch(...)
//   {
//      
//   }
//   
//   return -1;
//   
//}
//
//
//
//

