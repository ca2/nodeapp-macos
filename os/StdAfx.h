#pragma once

#if core_level_3
#define IMPLEMENT_VISTA_TOOLS
#endif

#include "mac.h"
#include "mac_internal.h"

CLASS_DECL_VMSWIN void vfxThrowFileException(::ca::application * papp, int cause, LONG lOsError, const char * lpszFileName = NULL);
