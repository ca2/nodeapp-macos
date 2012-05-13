#include "StdAfx.h"


WinResource::WinResource(::ca::application * papp) :
   ca(papp)
{
}

WinResource::~WinResource()
{

}


/*bool WinResource::ReadResource(
   ex1::filesp & file, 
   UINT nID, 
   const char * lpcszType)
{

   HINSTANCE hinst = ::AfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
   if(hinst == NULL)
      return false;
   return ReadResource(hinst, file, nID, lpcszType);
}*/

/*bool WinResource::ReadResource(
   HINSTANCE hinst,
   ex1::filesp & file, 
   UINT nID, 
   const char * lpcszType)
{

   HRSRC hrsrc = ::FindResource(
      hinst,
      MAKEINTRESOURCE(nID), 
      lpcszType);
   if(hrsrc == NULL)
      return false;
    HGLOBAL hres = ::LoadResource(hinst, hrsrc);
   if(hres == NULL)
      return false;
    DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

   if(hres != NULL)
    {
      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
        try
        {
           // create the .mdb file
//           ex1::filesp f(lpcszFilePath, ::ex1::file::mode_create | ::ex1::file::mode_write );

           // write the ::fontopus::user-defined resource to the .mdb file
           spfile->write(lpnRes, dwResSize);
           spfile->Flush();
        }
        catch(ex1::file_exception_sp * pe)
        {
      #ifdef _DEBUG
         afxdump << "File could not be opened " << e->m_cause << "\n";
      #endif
        }
        

      #ifndef WIN32 //Unlock WinResource is obsolete in the Win32 API
         ::UnlockResource(hres);
      #endif
            ::FreeResource(hres);
   }
   return true;

}
*/


bool WinResource::ReadResource(
   string & str, 
   UINT nID, 
   const char * lpcszType)
{
   gen::memory_file file(get_app());
   if(!ReadResource(file, nID, lpcszType))
      return false;
   file.AllocateAddUp(1);
   ((char * )file.GetAllocation())[file.get_length() -1 ] = '\0';
   str = ((char * )file.GetAllocation());
   return true;
}  



bool WinResource::ReadResource(
   ex1::file & file, 
   UINT nID, 
   const char * lpcszType)
{

   HINSTANCE hinst = vfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
   if(hinst == NULL)
      return false;
   return ReadResource(hinst, file, nID, lpcszType);
}

bool WinResource::ReadResource(
   HINSTANCE hinst,
   ex1::file & spfile, 
   UINT nID, 
   const char * lpcszType)
{

   HRSRC hrsrc = ::FindResource(
      hinst,
      MAKEINTRESOURCE(nID), 
      lpcszType);
   if(hrsrc == NULL)
      return false;
    HGLOBAL hres = ::LoadResource(hinst, hrsrc);
   if(hres == NULL)
      return false;
    DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

   if(hres != NULL)
    {
      UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
        try
        {
           // create the .mdb file
//           File f(lpcszFilePath, File::mode_create | File::mode_write );

           // write the ::fontopus::user-defined resource to the .mdb file
           spfile.write(lpnRes, dwResSize);
           spfile.Flush();
        }
        catch(ex1::file_exception_sp *)
        {
      #ifdef _DEBUG
//         afxdump << "File could not be opened " << pe->m_cause << "\n";
      #endif
        }
        

      #ifndef WIN32 //Unlock WinResource is obsolete in the Win32 API
         ::UnlockResource(hres);
      #endif
            ::FreeResource(hres);
   }
   return true;

}

//} //namespace gen


HINSTANCE CLASS_DECL_VMSWIN vfxFindResourceHandle(const char * lpszName, const char * lpszType)
{
   ASSERT(lpszName != NULL);
   ASSERT(lpszType != NULL);

   HINSTANCE hInst;

   // first check the main module state
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   if (!pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   CDynLinkLibrary* pDLL = NULL;
   // check for non-system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL;
      pDLL = pDLL->m_pNextDLL)
   {
      if (!pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // check language specific resource next
   hInst = pModuleState->m_appLangDLL;
   if (hInst != NULL && ::FindResource(hInst, lpszName, lpszType) != NULL)
      return hInst;

   // check the main system module state
   if (pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   // check for system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
   {
      if (pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // if failed to find resource, return application resource
   return CaSys(::win::get_thread()).m_hInstance;
}

/*HINSTANCE CLASS_DECL_VMSWIN vfxFindResourceHandle(const char * lpszName, const char * lpszType)
{
   ASSERT(lpszName != NULL);
   ASSERT(lpszType != NULL);

   HINSTANCE hInst;

   // first check the main module state
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   if (!pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   CDynLinkLibrary* pDLL = NULL;
   // check for non-system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL;
      pDLL = pDLL->m_pNextDLL)
   {
      if (!pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // check language specific resource next
   hInst = pModuleState->m_appLangDLL;
   if (hInst != NULL && ::FindResource(hInst, lpszName, lpszType) != NULL)
      return hInst;

   // check the main system module state
   if (pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   // check for system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
   {
      if (pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // if failed to find resource, return application resource
   return AfxGetResourceHandle();
}*/
