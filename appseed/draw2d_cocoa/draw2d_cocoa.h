#pragma once


#define SECURITY_WIN32


#include "app/appseed/ca2/ca2.h"


#define CLASS_DECL_DRAW2D_COCOA


#include "draw2d_cocoa_graphics.h"
#include "draw2d_cocoa_object.h"
#include "draw2d_cocoa_path.h"
#include "draw2d_cocoa_bitmap.h"
#include "draw2d_cocoa_dib.h"
#include "draw2d_cocoa_palette.h"
#include "draw2d_cocoa_pen.h"
#include "draw2d_cocoa_font.h"
#include "draw2d_cocoa_brush.h"
#include "draw2d_cocoa_region.h"



#include "draw2d_cocoa_factory_exchange.h"





#define COCOA_DC(pgraphics) (dynamic_cast < ::draw2d_cocoa::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::draw2d_cocoa::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define COCOA_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_cocoa::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_cocoa::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define COCOA_DIB(pdib) (dynamic_cast < ::mac::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))
