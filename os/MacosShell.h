#pragma once

#define WH_SHSTDAPI(type) type

class CLASS_DECL_VMSWIN WindowsShell  
{
public:
   WindowsShell();
   virtual ~WindowsShell();

   
   static WindowsShell theWindowsShell;

   static bool Initialize();
   static BOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, wchar_t * pszPath);
   static HANDLE WINAPI _FindFirstFile(const wchar_t * lpcsz, WIN32_FIND_DATAW * lpdata);
   static BOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
   static BOOL WINAPI _MoveFile(const wchar_t * lpExistingFileName, const wchar_t * lpNewFileName);
   static DWORD WINAPI _GetFullPathName(const wchar_t * lpFileName, DWORD nBufferLength, wchar_t * lpBuffer, wchar_t ** lpFilePart);
   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   static BOOL WINAPI _GetVolumeInformation(
      const wchar_t * lpRootPathName,           // root directory
      wchar_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wchar_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer
   static DWORD_PTR __stdcall _SHGetFileInfo(      
      const wchar_t * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);
   static BOOL __stdcall _GetStringTypeEx(      
      LCID Locale,
      DWORD dwInfoType,
      const wchar_t * lpSrcStr,
      int cchSrc,
      LPWORD lpCharType);
   static DWORD WINAPI  _GetTempPath(
      DWORD nBufferLength,
      wchar_t * lpBuffer);
   static UINT WINAPI _GetTempFileName(
      const wchar_t * lpPathName,
      const wchar_t * lpPrefixString,
      UINT uUnique,
      wchar_t * lpTempFileName);
   static HANDLE WINAPI _CreateFile(
      const wchar_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
   static DWORD WINAPI _GetModuleFileName(
       HMODULE hModule,
       wchar_t * lpFilename,
       DWORD nSize
       );
   static BOOL WINAPI _GetClassInfo(
       HINSTANCE hInstance ,
       const wchar_t * lpClassName,
       LPWNDCLASSW lpWndClass);
   static ATOM WINAPI _RegisterClass(
         CONST WNDCLASSW *lpWndClass);

   static HWND WINAPI _CreateWindowEx(
      DWORD dwExStyle,
      const wchar_t * lpClassName,
      const wchar_t * lpWindowName,
      DWORD dwStyle,
      int x,
      int y,
      int nWidth,
      int nHeight,
      HWND hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);





   BOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, wchar_t * pszPath);
   HANDLE (WINAPI * m_pfnFindFirstFile)(const wchar_t * lpcsz, WIN32_FIND_DATAW * lpdata);
   BOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
   BOOL (WINAPI * m_pfnMoveFile)(const wchar_t * lpExistingFileName, const wchar_t * lpNewFileName);
   WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   DWORD (WINAPI * m_pfnGetFullPathName)(const wchar_t * lpFileName, DWORD nBufferLength, wchar_t * lpBuffer, wchar_t ** lpFilePart);
   BOOL (WINAPI * m_pfnGetVolumeInformation)(
      const wchar_t * lpRootPathName,           // root directory
      wchar_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wchar_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer

   DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(      
      const wchar_t * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);
   BOOL (__stdcall * m_pfnGetStringTypeEx)(      
      LCID Locale,
      DWORD dwInfoType,
      const wchar_t * lpSrcStr,
      int cchSrc,
      LPWORD lpCharType);
   DWORD (WINAPI * m_pfnGetTempPath)(
      DWORD nBufferLength,
      wchar_t * lpBuffer);
   UINT (WINAPI * m_pfnGetTempFileName)(
      const wchar_t * lpPathName,
      const wchar_t * lpPrefixString,
      UINT uUnique,
      wchar_t * lpTempFileName);
   HANDLE (WINAPI * m_pfnCreateFile)(
      const wchar_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );

   DWORD (WINAPI * m_pfnGetModuleFileName)(
       HMODULE hModule,
       wchar_t * lpFilename,
       DWORD nSize
       );

   BOOL (WINAPI * m_pfnGetClassInfo)(
       HINSTANCE hInstance ,
       const wchar_t * lpClassName,
       LPWNDCLASSW lpWndClass);

   ATOM (WINAPI * m_pfnRegisterClass)(
         CONST WNDCLASSW *lpWndClass);

   HWND (WINAPI * m_pfnCreateWindowEx)(
      DWORD dwExStyle,
      const wchar_t * lpClassName,
      const wchar_t * lpWindowName,
      DWORD dwStyle,
      int x,
      int y,
      int nWidth,
      int nHeight,
      HWND hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);








   static BOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
   static BOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, wchar_t * pszPath);
   static HANDLE FindFirstFile(const wchar_t * lpcsz, WIN32_FIND_DATAW * lpdata);
   static BOOL WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
   static BOOL MoveFile(const wchar_t * lpExistingFileName, const wchar_t * lpNewFileName);
   static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   static DWORD GetFullPathName(const wchar_t * lpFileName, DWORD nBufferLength, wchar_t * lpBuffer, wchar_t ** lpFilePart);
   static BOOL GetVolumeInformation(
      const wchar_t * lpRootPathName,           // root directory
      wchar_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wchar_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer

   static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
      const wchar_t * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFOW *psfi,
      UINT cbFileInfo,
      UINT uFlags);

   static BOOL  GetStringTypeEx(      
      LCID Locale,
      DWORD dwInfoType,
      const char * lpSrcStr,
      int cchSrc,
      LPWORD lpCharType);

   static DWORD GetTempPathW(
      DWORD nBufferLength,
      wchar_t * lpBuffer);

   static UINT GetTempFileNameW(
      const wchar_t * lpPathName,
      const wchar_t * lpPrefixString,
      UINT uUnique,
      wchar_t * lpTempFileName);

   static HANDLE CreateFile(
      const wchar_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile);

   static DWORD WINAPI GetModuleFileName(
       HMODULE hModule,
       wchar_t * lpFilename,
       DWORD nSize
       );

   static BOOL WINAPI GetClassInfo(
       HINSTANCE hInstance ,
       const wchar_t * lpClassName,
       LPWNDCLASSW lpWndClass);

   static ATOM WINAPI RegisterClass(
         CONST WNDCLASSW *lpWndClass);

   static HWND WINAPI CreateWindowEx(
      DWORD dwExStyle,
      const wchar_t * lpClassName,
      const wchar_t * lpWindowName,
      DWORD dwStyle,
      int x,
      int y,
      int nWidth,
      int nHeight,
      HWND hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);


   static WH_SHSTDAPI(DWORD) SHGetFileInfo(      
      const char * pszPath,
      DWORD dwFileAttributes,
      SHFILEINFO *psfi,
      UINT cbFileInfo,
      UINT uFlags);

   static DWORD GetTempPath(string & str);

   static UINT GetTempFileName(
      const char * lpPathName,
      const char * lpPrefixString,
      UINT uUnique,
      string & str);
   
   static BOOL MoveFile(const char * lpExistingFileName, const char * lpNewFileName);

};

inline BOOL WindowsShell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
{
   wchar_t * pwszPath = (wchar_t *) malloc(sizeof(wchar_t) * MAX_PATH * 4);
   if(!(*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
   {
      free(pwszPath);
      return FALSE;
   }
   gen::international::unicode_to_utf8(str, pwszPath);
   free(pwszPath);
   return TRUE;
}


inline BOOL WindowsShell::SHGetPathFromIDList(LPCITEMIDLIST pidl, wchar_t * pszPath)
{
   return (*theWindowsShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
}

inline HANDLE WindowsShell::FindFirstFile(const wchar_t * lpcsz, WIN32_FIND_DATAW * lpdata)
{
   return (*theWindowsShell.m_pfnFindFirstFile)(lpcsz, lpdata);
}

inline BOOL WindowsShell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
{
   return (*theWindowsShell.m_pfnFindNextFile)(handle, lpdata);
}

inline WCHAR * WindowsShell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
{
   return (*theWindowsShell.m_pfn_fullpath)(UserBuf, path, maxlen);
}

inline DWORD WindowsShell::GetFullPathName(const wchar_t * lpFileName, DWORD nBufferLength, wchar_t * lpBuffer, wchar_t ** lpFilePart)
{
   return (*theWindowsShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
}


inline BOOL WindowsShell::MoveFile(const wchar_t * lpExistingFileName, const wchar_t * lpNewFileName)
{
   return (*theWindowsShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName);
}

inline BOOL WindowsShell::GetVolumeInformation(
      const wchar_t * lpRootPathName,           // root directory
      wchar_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      wchar_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize)         // length of file system name buffer
{
   return (*theWindowsShell.m_pfnGetVolumeInformation)(
      lpRootPathName,           // root directory
      lpVolumeNameBuffer,        // volume name buffer
      nVolumeNameSize,            // length of name buffer
      lpVolumeSerialNumber,     // volume serial number
      lpMaximumComponentLength, // maximum file name length
      lpFileSystemFlags,        // file system options
      lpFileSystemNameBuffer,    // file system name buffer
      nFileSystemNameSize);         // length of file system name buffer
}

inline DWORD WindowsShell::SHGetFileInfo(
   const wchar_t * pszPath,
   DWORD dwFileAttributes,
   SHFILEINFOW *psfi,
   UINT cbFileInfo,
   UINT uFlags)
{
   return (*theWindowsShell.m_pfnSHGetFileInfo)(
      pszPath,
      dwFileAttributes,
      psfi,
      cbFileInfo,
      uFlags);
}

inline DWORD WindowsShell::GetTempPathW(
   DWORD nBufferLength,
   wchar_t * lpBuffer)
{
     return (*theWindowsShell.m_pfnGetTempPath)(
      nBufferLength,
      lpBuffer);
}

inline UINT WindowsShell::GetTempFileNameW(
   const wchar_t * lpPathName,
   const wchar_t * lpPrefixString,
   UINT uUnique,
   wchar_t * lpTempFileName)
{
   return (*theWindowsShell.m_pfnGetTempFileName)(
      lpPathName,
      lpPrefixString,
      uUnique,
      lpTempFileName);
}

inline HANDLE WindowsShell::CreateFile(
   const wchar_t * lpFileName,
   DWORD dwDesiredAccess,
   DWORD dwShareMode,
   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
   DWORD dwCreationDisposition,
   DWORD dwFlagsAndAttributes,
   HANDLE hTemplateFile)
{
   return (*theWindowsShell.m_pfnCreateFile)(
      lpFileName,
      dwDesiredAccess,
      dwShareMode,
      lpSecurityAttributes,
      dwCreationDisposition,
      dwFlagsAndAttributes,
      hTemplateFile);
}

inline DWORD WindowsShell::GetModuleFileName(
    HMODULE hModule,
    wchar_t * lpFilename,
    DWORD nSize
    )
{
   return (*theWindowsShell.m_pfnGetModuleFileName)(
      hModule,
      lpFilename,
      nSize);
}

inline BOOL WindowsShell::GetClassInfo(
   HINSTANCE hInstance ,
   const wchar_t * lpClassName,
   LPWNDCLASSW lpWndClass)
{
   return (*theWindowsShell.m_pfnGetClassInfo)(
      hInstance ,
      lpClassName,
      lpWndClass);
}

inline ATOM WindowsShell::RegisterClass(
   CONST WNDCLASSW *lpWndClass)
{
   return (*theWindowsShell.m_pfnRegisterClass)(
      lpWndClass);
}

inline HWND WindowsShell::CreateWindowEx(
   DWORD dwExStyle,
   const wchar_t * lpClassName,
   const wchar_t * lpWindowName,
   DWORD dwStyle,
   int x,
   int y,
   int nWidth,
   int nHeight,
   HWND hWndParent,
   HMENU hMenu,
   HINSTANCE hInstance,
   LPVOID lpParam)
{
   return (*theWindowsShell.m_pfnCreateWindowEx)(
      dwExStyle,
      lpClassName,
      lpWindowName,
      dwStyle,
      x,
      y,
      nWidth,
      nHeight,
      hWndParent,
      hMenu,
      hInstance,
      lpParam);

}

inline DWORD WindowsShell::GetTempPath(string & str)
{
   wchar_t * pwsz = (wchar_t *) malloc(sizeof(wchar_t) * MAX_PATH * 4);
   DWORD dwResult = (*theWindowsShell.m_pfnGetTempPath)(sizeof(wchar_t) * MAX_PATH * 4, pwsz);
   gen::international::unicode_to_utf8(str, pwsz);
   free(pwsz);
   return dwResult;
}

inline UINT WindowsShell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, UINT uUnique, string & str)
{
   wstring wstrPathName = gen::international::utf8_to_unicode(lpPathName);
   wstring wstrPrefixString = gen::international::utf8_to_unicode(lpPrefixString);
   wstring wstr;
   wstr.alloc(MAX_PATH * 4);
   UINT uiResult = (*theWindowsShell.m_pfnGetTempFileName)(
      wstrPathName,
      wstrPrefixString,
      uUnique,
      wstr.m_pwsz);
   gen::international::unicode_to_utf8(str, wstr);
   return uiResult;
}

inline BOOL WindowsShell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
{
   return MoveFile(gen::international::utf8_to_unicode(lpExistingFileName), gen::international::utf8_to_unicode(lpNewFileName));
}

