//
//  round_window.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


class round_window
{
public:
   
   
   NSWindow * m_nswindow;
   
   virtual void round_window_draw(CGContextRef cgc) = 0;
   
   
};


void ns_shared_application();
NSWindow * new_round_window(round_window * pwindow, CGRect rect);
void ns_app_run();
