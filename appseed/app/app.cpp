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

