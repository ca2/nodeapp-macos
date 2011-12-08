#pragma once

#define LINUX

#ifndef _DEBUG
#define _DEBUG
#endif

#if defined(_M_X64)

#define _AMD64_

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/linux_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>


typedef std::type_info std_type_info;


#include "include/inttypes.h"

#else


#define _X86_

//#pragma pointers_to_members( full_generality, virtual_inheritance )
//#include "os/include/linux32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo>


typedef std::type_info std_type_info;


#include <inttypes.h>





#endif


typedef __int64_t __int64;









#define WINAPI



#include "operational_system.h"        // Target version control

