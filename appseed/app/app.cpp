//
//  main.m
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 1/19/13.
//  Copyright (c) 2013 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "app.h"


extern int32_t __mac_main(int32_t argc, char * argv[]);


int main(int argc, char *argv[])
{
   
   return __mac_main(argc, argv);
   
}


int32_t CLASS_DECL_mac ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow)
{

   try
   {
      
      ::core::system * psystem = new ::core::system();
      
      ASSERT(hPrevInstance == NULL);
      
      int32_t nReturnCode = 0;
      
      ::mac::main_init_data * pinitmaindata  = new ::mac::main_init_data;
      
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
      
      try
      {
         
         defer_base_term();
         
      }
      catch(...)
      {
         
      }

      return nReturnCode;
      
   }
   catch(...)
   {
      
   }
   
   return -1;
   
}





