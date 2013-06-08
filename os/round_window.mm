//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "RoundWindow.h"
#include "round_window.h"



NSWindow * new_round_window(CGRect rect)
{
   
   rect.origin.x = 100;
   rect.origin.x = 100;
   rect.size.width = 500;
   rect.size.height = 500;
   
   return [[RoundWindow alloc] initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered  defer : false ];

}


void ns_shared_application()
{

   [NSApplication sharedApplication];
   
}


void ns_app_run()
{

   [NSApp run];
   
}

