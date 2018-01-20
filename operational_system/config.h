//
//  config.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once



#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG 1
#endif


//#ifdef __cplusplus
//typedef wchar_t unichar;
//#else
//#endif

//#define STORE_LAST_BLOCK 1
//#define MEMDFREE 1
//#define MEMDLEAK 1


#define BSD_STYLE_SOCKETS
#define HAVE_OPENSSL
#define VARIADIC_TEMPLATE_FORMAT2


#define __PLATFORM   "macos"



#ifndef APPLEOS
#define APPLEOS
#endif



#ifndef MACOS
#define MACOS
#endif




#define CLASS_DECL_IMPORT
#define CLASS_DECL_EXPORT
#define CLASS_DECL_THREAD __thread


#ifndef OSBIT
#include "nodeapp/operational_system/bit.h"
#endif



#define static_inline inline


#define AXIS_FREEIMAGE


#define FONT_SANS "Helvetica"
#define FONT_SERIF "Times"
#define FONT_SANS_EX "Arial"
#define FONT_SERIF_EX "Times New Roman"
#define FONT_SANS_FX "Verdana"
#define FONT_SERIF_FX "Georgia"
#define FONT_MONO "Menlo"





