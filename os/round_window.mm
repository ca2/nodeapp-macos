//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "RoundWindow.h"
#include "round_window.h"



NSWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   rect.origin.x     = 0;
   rect.origin.x     = 0;
   rect.size.width   = 0;
   rect.size.height  = 0;
   
   RoundWindow * round_window = [RoundWindow alloc];
   
   round_window->m_pwindow = pwindow;
   
   return [round_window initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered  defer : false ];
   
}


void ns_shared_application()
{

   [NSApplication sharedApplication];
   
}


void ns_app_run()
{

   [NSApp run];
   
}

