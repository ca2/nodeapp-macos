#include "StdAfx.h"
#include "WinFileSystem.h"


#include "WinFile.h"

WinFileSystem::WinFileSystem(::ca::application * papp) :
   ca(papp)
{

}

WinFileSystem::~WinFileSystem()
{

}

bool WinFileSystem::FullPath(string &str, const char * lpszFileIn)
{
   if(::ex1::file_system::FullPath(str, lpszFileIn))
      return true;
   if(gen::str::begins_ci(lpszFileIn, "http://"))
   {
      str = lpszFileIn;
      return true;
   }
   else if(gen::str::begins_ci(lpszFileIn, "https://"))
   {
      str = lpszFileIn;
      return true;
   }
   wstring wstrFileIn;
   wstrFileIn = gen::international::utf8_to_unicode(lpszFileIn);
   wstring wstrFileOut;
   bool b = vfxFullPath(wstrFileOut.alloc(MAX_PATH * 8), wstrFileIn) != FALSE;
   if(b)
   {
      gen::international::unicode_to_utf8(str, wstrFileOut);
   }
   return b;
}


UINT WinFileSystem::GetFileName(const char * lpszPathName, string & str)
{
   int nMax = MAX_PATH * 8;
   wstring wstrPathName;
   wstrPathName = gen::international::utf8_to_unicode(lpszPathName);
   wstring wstrTitle;
   UINT user = vfxGetFileName(wstrPathName, wstrTitle.alloc(nMax), nMax);
   str = gen::international::unicode_to_utf8(wstrTitle);
   return user;
}

void WinFileSystem::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
{
   vfxGetModuleShortFileName(hInst, strShortName);
}
