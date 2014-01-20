#pragma once


#define SECURITY_WIN32


#include "base/base/base/base.h"


#define CLASS_DECL_DRAW2D_QUARTZ2D


#include "draw2d_quartz2d_graphics.h"
#include "draw2d_quartz2d_object.h"
#include "draw2d_quartz2d_path.h"
#include "draw2d_quartz2d_bitmap.h"
#include "draw2d_quartz2d_dib.h"
#include "draw2d_quartz2d_palette.h"
#include "draw2d_quartz2d_pen.h"
#include "draw2d_quartz2d_font.h"
#include "draw2d_quartz2d_brush.h"
#include "draw2d_quartz2d_region.h"



#include "draw2d_quartz2d_factory_exchange.h"





#define COCOA_DC(pgraphics) (dynamic_cast < ::draw2d_quartz2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::draw2d_quartz2d::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define COCOA_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_quartz2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_quartz2d::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define COCOA_DIB(pdib) (dynamic_cast < ::mac::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))
