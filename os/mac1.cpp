#include "StdAfx.h"
#include "win1.h"

namespace win
{
   int win::function()
   {
      return 0;
   }

   HINSTANCE LoadLibrary(const char * lpsz)
   {
      return ::LoadLibraryW(gen::international::utf8_to_unicode(lpsz));
   }

   BOOL CLASS_DECL_VMSWIN SHGetSpecialFolderPath(HWND hwnd, string &str, int csidl, BOOL fCreate)
   {
      return ::SHGetSpecialFolderPathW(hwnd, wstringtou(str, MAX_PATH * 8), csidl, fCreate);
   }

   DWORD GetFileAttributes(const char * lpFileName)
   {
      return ::GetFileAttributesW(gen::international::utf8_to_unicode(lpFileName));
   }

   BOOL CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
   {
      return ::CreateDirectoryW(gen::international::utf8_to_unicode(lpPathName), lpSecurityAttributes);
   }

   DWORD GetCurrentDirectory(string & str)
   {
      return ::GetCurrentDirectoryW(MAX_PATH * 8, wstringtou(str, MAX_PATH * 8));
   }

   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8, wstringtou(str, MAX_PATH * 8));
   }

   LONG RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str)
   {
      DWORD dwType = 0;
      DWORD dwSize = 0;
      LONG lResult = RegQueryValueEx(hkey, lpszSubKey, NULL, &dwType, NULL, &dwSize);
      if(lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {
         lResult = RegQueryValueEx(hkey, lpszSubKey, NULL, &dwType, (LPBYTE) str.GetBufferSetLength(dwSize), &dwSize);
         str.ReleaseBuffer(dwSize);
         return lResult;
      }
      else
      {
         return ERROR_NOT_SUPPORTED;
      }
   }

   HICON ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex)
   {
      return ::ExtractIconW(hInst, gen::international::utf8_to_unicode(lpszExeFileName), nIconIndex);
   }

   BOOL  DeleteFile(const char * lpFileName)
   {
      return ::DeleteFileW(gen::international::utf8_to_unicode(lpFileName));
   }

/*   int GetMenuString(HMENU hmenu, UINT uIDItem, string & str, UINT flags)
   {
      wstring str;
      int iLen = _GetMenuString(hmenu, uIDItem, wstr, flags);
      gen::international::unicode_to_utf8(str, str);
      return iLen;
   }*/

   CLASS_DECL_VMSWIN void TimeToFileTime(::ca::application * papp, const class time& time, LPFILETIME pFileTime)
   {
         SYSTEMTIME sysTime;
         sysTime.wYear           = (WORD)time.GetYear();
         sysTime.wMonth          = (WORD)time.GetMonth();
         sysTime.wDay            = (WORD)time.GetDay();
         sysTime.wHour           = (WORD)time.GetHour();
         sysTime.wMinute         = (WORD)time.GetMinute();
         sysTime.wSecond         = (WORD)time.GetSecond();
         sysTime.wMilliseconds   = 0;

         // convert system time to local file time
         FILETIME localTime;
         if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
               WinFileException::ThrowOsError(papp, (LONG)::GetLastError());

         // convert local file time to UTC file time
         if (!LocalFileTimeToFileTime(&localTime, pFileTime))
               WinFileException::ThrowOsError(papp, (LONG)::GetLastError());
   }


} // namespace win
