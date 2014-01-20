#include "framework.h"
#include "mac_implementation.h"

/*
namespace gen
{

   Resource::Resource()
   {

   }

   Resource::~Resource()
   {

   }


   bool Resource::ReadResource(
      primitive::memory & storage, 
      UINT nID, 
      const char * lpcszType)
   {

      HINSTANCE hinst = ::AfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
      if(hinst == NULL)
         return false;
      return ReadResource(hinst, storage, nID, lpcszType);
   }

   bool Resource::ReadResource(
      HINSTANCE hinst,
      primitive::memory & storage, 
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
   //           ::ca2::filesp f(lpcszFilePath, ::file::mode_create | ::file::mode_write );

              // write the ::fontopus::user-defined resource to the .mdb file
              storage.set_data(lpnRes, dwResSize);
           }
           catch(::ca2::file_exception_sp * pe)
           {
         #ifdef _DEBUG
              //
            //afxdump << "File could not be opened " << (*pe)->m_cause << "\n";
         #endif
           }
           

         #ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
            ::UnlockResource(hres);
         #endif
               ::FreeResource(hres);
      }
      return true;

   }

} //namespace gen


HINSTANCE CLASS_DECL_mac vfxFindResourceHandle(const char * lpszName, const char * lpszType)
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
   return System.m_hInstance;
}

HINSTANCE CLASS_DECL_mac vfxFindResourceHandle(const wchar_t * lpszName, const wchar_t * lpszType)
{
   ASSERT(lpszName != NULL);
   ASSERT(lpszType != NULL);

   HINSTANCE hInst;

   // first check the main module state
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   if (!pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResourceW(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   CDynLinkLibrary* pDLL = NULL;
   // check for non-system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL;
      pDLL = pDLL->m_pNextDLL)
   {
      if (!pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResourceW(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // check language specific resource next
   hInst = pModuleState->m_appLangDLL;
   if (hInst != NULL && ::FindResourceW(hInst, lpszName, lpszType) != NULL)
      return hInst;

   // check the main system module state
   if (pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResourceW(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   // check for system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
   {
      if (pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResourceW(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // if failed to find resource, return application resource
   return AfxGetResourceHandle();
}
*/