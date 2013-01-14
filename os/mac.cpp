#include "StdAfx.h"
#include "ca2/radix/cafxdllx.h"

#pragma comment(lib, "version.lib") 


static AFX_EXTENSION_MODULE VmswinDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   // remov this if you use lpReserved
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugString("::ca2:: mac.dll :: initializing!\n");
      
      // Extension DLL one-time initialization
      if (!AfxInitExtensionModule(VmswinDLL, hInstance))
         return 0;

      // Insert this DLL into the resource chain
      // NOTE: If this Extension DLL is being implicitly linked to by
      //  an ca2 API Regular DLL (such as an ActiveX control)
      //  instead of an ca2 API application, then you will want to
      //  remov this line from DllMain and put it in a separate
      //  function exported from this Extension DLL.  The Regular DLL
      //  that uses this Extension DLL should then explicitly call that
      //  function to initialize this Extension DLL.  Otherwise,
      //  the CDynLinkLibrary object will not be attached to the
      //  Regular DLL's resource chain, and serious problems will
      //  result.

      new CDynLinkLibrary(VmswinDLL);

      ::icube::g_lpfn_instantiate_application = &::win_instantiate_application;
      ::ca::g_pfn_get_thread = &::mac::get_thread;

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::OutputDebugString("::ca2:: mac.dll :: terminating!\n");
      // Terminate the library before destructors are called
      AfxTermExtensionModule(VmswinDLL);
   }
   return 1;   // ok
}
