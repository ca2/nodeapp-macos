//
//  main.m
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "app.h"
#include "aura/aura/node/macos/macos.h"


extern int32_t __mac_main(int32_t argc, char * argv[]);


int main(int argc, char *argv[])
{
   
   pid_t processid;
   
   processid=getpid();
   
   printf("%d\n", processid);
   
   bool bInstall = false;
   
   bool bUninstall = false;
   
   for(index i = 0; i < argc; i++)
   {

      if(strcmp(argv[i], "install") == 0)
      {
         
         bInstall = true;
         
      }
      else if(strcmp(argv[i], "install") == 0)
      {
         
         bUninstall = true;
         
      }
      
   }
   
   if(bInstall)
   {
     
//      if(setuid(0) != 0)
  //    {
//
  //       return -3;
    //
      //}

   }
   else if(bUninstall)
   {
    
//      if(setuid(0) != 0)
  //    {
    //
      //   return -3;
        //
      //}
      
   }
   
//   fwrite(&processid,sizeof(processid),1,stdout);
  // fflush(stdout);

   
   if(!defer_core_init())
      return -1;
   
   int iResult = __mac_main(argc, argv);
   
   try
   {
      
      defer_core_term();
      
   }
   catch(...)
   {
      
   }

   return iResult;
   
}


int32_t ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{
   
   

   try
   {
      
      ::core::system * psystem = new ::core::system();
      
      ASSERT(hPrevInstance == NULL);
      
      int32_t nReturnCode = 0;
      
      ::macos::main_init_data * pinitmaindata  = new ::macos::main_init_data;
      
      pinitmaindata->m_hInstance             = hInstance;
      
      pinitmaindata->m_hPrevInstance         = hPrevInstance;
      
      pinitmaindata->m_strCommandLine        = lpCmdLine;

      pinitmaindata->m_nCmdShow              = nCmdShow;
      
      psystem->init_main_data(pinitmaindata);

      bool bOk = false;
      
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
         
         delete psystem;
         
      }
      catch(...)
      {
      
      }
      
      psystem = NULL;
      
      return nReturnCode;
      
   }
   catch(...)
   {
      
   }
   
   return -1;
   
}





