#include "framework.h"

/***
 *int32_t _validdrive( unsigned drive ) -
 *
 *Purpose: returns non zero if drive is a valid drive number.
 *
 *Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
 *
 *Exit:  0 => drive does not exist.
 *
 *Exceptions:
 *
 *******************************************************************************/
/*
 int32_t __cdecl _validdrive (
 unsigned drive
 )
 {
 unsigned retcode;
 char drvstr[4];
 
 if ( drive == 0 )
 return 1;
 
 drvstr[0] = (char) ('A' + drive - 1);
 drvstr[1] = ':';
 drvstr[2] = '\\';
 drvstr[3] = '\0';
 
 if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
 (retcode == DRIVE_NO_ROOT_DIR) )
 return 0;
 
 return 1;
 }*/

/*WCHAR * __cdecl _wgetdcwd (
 int32_t drive,
 WCHAR *pnbuf,
 int32_t maxlen
 );
 
 */
/***
 *_TSCHAR *_getcwd(pnbuf, maxlen) - get current working directory of default drive
 *
 *Purpose:
 *       _getcwd gets the current working directory for the ::fontopus::user,
 *       placing it in the buffer pointed to by pnbuf.  It returns
 *       the length of the string put in the buffer.  If the length
 *       of the string exceeds the length of the buffer, maxlen,
 *       then NULL is returned.  If pnbuf = NULL, maxlen is ignored.
 *       An entry point "_getdcwd()" is defined with takes the above
 *       parameters, plus a drive number.  "_getcwd()" is implemented
 *       as a call to "_getcwd()" with the default drive (0).
 *
 *       If pnbuf = NULL, maxlen is ignored, and a buffer is automatically
 *       allocated using malloc() -- a pointer to which is returned by
 *       _getcwd().
 *
 *       side effects: no global data is used or affected
 *
 *Entry:
 *       _TSCHAR *pnbuf = pointer to a buffer maintained by the ::fontopus::user;
 *       int32_t maxlen = length of the buffer pointed to by pnbuf;
 *
 *Exit:
 *       Returns pointer to the buffer containing the c.w.d. name
 *       (same as pnbuf if non-NULL; otherwise, malloc is
 *       used to allocate a buffer)
 *
 *Exceptions:
 *
 *******************************************************************************/

/*WCHAR * __cdecl _wgetcwd (
 WCHAR *pnbuf,
 int32_t maxlen
 )
 {
 WCHAR *retval;
 
 
 retval = _wgetdcwd(0, pnbuf, maxlen);
 
 return retval;
 }*/


/***
 *_TSCHAR *_getdcwd(drive, pnbuf, maxlen) - get c.w.d. for given drive
 *
 *Purpose:
 *       _getdcwd gets the current working directory for the ::fontopus::user,
 *       placing it in the buffer pointed to by pnbuf.  It returns
 *       the length of the string put in the buffer.  If the length
 *       of the string exceeds the length of the buffer, maxlen,
 *       then NULL is returned.  If pnbuf = NULL, maxlen is ignored,
 *       and a buffer is automatically allocated using malloc() --
 *       a pointer to which is returned by _getdcwd().
 *
 *       side effects: no global data is used or affected
 *
 *Entry:
 *       int32_t drive   - number of the drive being inquired about
 *                     0 = default, 1 = 'a:', 2 = 'b:', etc.
 *       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::fontopus::user;
 *       int32_t maxlen  - length of the buffer pointed to by pnbuf;
 *
 *Exit:
 *       Returns pointer to the buffer containing the c.w.d. name
 *       (same as pnbuf if non-NULL; otherwise, malloc is
 *       used to allocate a buffer)
 *
 *Exceptions:
 *
 *******************************************************************************/


/*WCHAR * __cdecl _wgetdcwd (
 int32_t drive,
 WCHAR *pnbuf,
 int32_t maxlen
 )
 {
 WCHAR *p;
 WCHAR dirbuf[_MAX_PATH];
 WCHAR drvstr[4];
 int32_t len;
 WCHAR *pname;  only used as argument to GetFullPathName */

/*
 * GetCurrentDirectory only works for the default drive in Win32
 */
/*      if ( drive != 0 ) {
 *
 * Not the default drive - make sure it's valid.
 */
/*        if ( !_validdrive(drive) ) {
 _doserrno = ERROR_INVALID_DRIVE;
 //                errno = EACCES;
 return NULL;
 }
 
 *
 * get the current directory string on that drive and its length
 */
/*      drvstr[0] = (char) ('A' - 1 + drive);
 drvstr[1] = ':';
 drvstr[2] = '.';
 drvstr[3] = '\0';
 len = shell::GetFullPathName( drvstr,
 sizeof(dirbuf) / sizeof(_TSCHAR),
 dirbuf,
 &pname );
 
 } else {
 
 *
 * get the current directory string and its length
 */
/*            len = GetCurrentDirectory( sizeof(dirbuf) / sizeof(_TSCHAR),
 (LPTSTR)dirbuf );
 }
 
 * API call failed, or buffer not large enough */
/*      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
 return NULL;
 
 *
 * Set up the buffer.
 */
/*    if ( (p = pnbuf) == NULL ) {
 *
 * allocate a buffer for the ::fontopus::user.
 */
/*      if ( (p = (WCHAR *)malloc(__max(len, maxlen) * sizeof(WCHAR)))
 == NULL )
 {
 //                errno = ENOMEM;
 return NULL;
 }
 }
 else if ( len > maxlen ) {
 *
 * Won't fit in the ::fontopus::user-supplied buffer!
 */
//            errno = ERANGE; /* Won't fit in ::fontopus::user buffer */
/*    return NULL;
 }
 
 *
 * Place the current directory string into the ::fontopus::user buffer
 */
/*
 return wcscpy(p, dirbuf);
 }
 
 *#ifndef WPRFLAG
 
 ***
 *int32_t _validdrive( unsigned drive ) -
 *
 *Purpose: returns non zero if drive is a valid drive number.
 *
 *Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
 *
 *Exit:  0 => drive does not exist.
 *
 *Exceptions:
 *
 *******************************************************************************/

/*int32_t __cdecl _validdrive (
 unsigned drive
 )
 {
 unsigned retcode;
 char drvstr[4];
 
 if ( drive == 0 )
 return 1;
 
 drvstr[0] = 'A' + drive - 1;
 drvstr[1] = ':';
 drvstr[2] = '\\';
 drvstr[3] = '\0';
 
 if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
 (retcode == DRIVE_NO_ROOT_DIR) )
 return 0;
 
 return 1;
 }*/

namespace mac{
   
   
   shell shell::theLinuxShell;
   
   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////
   
   shell::shell()
   {
      
   }
   
   shell::~shell()
   {
      
   }
   
   bool shell::Initialize()
   {
      
      /*
       DWORD dwVersion = GetVersion();
       
       // get the Windows version.
       
       DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
       //   DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
       
       // get the build number.
       
       DWORD dwBuild;
       
       if (dwVersion < 0x80000000)              // Windows NT
       dwBuild = (DWORD)(HIWORD(dwVersion));
       else if (dwWindowsMajorVersion < 4)      // Win32s
       dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
       else                                     // Windows Me/98/95
       dwBuild =  0;
       
       WINBOOL bNativeUnicode;
       if (dwVersion < 0x80000000)              // Windows NT
       bNativeUnicode = TRUE;
       else if (dwWindowsMajorVersion < 4)      // Win32s
       bNativeUnicode = FALSE;
       else                                     // Windows Me/98/95
       bNativeUnicode = FALSE;
       
       
       if(bNativeUnicode)
       {
       theLinuxShell.m_pfnSHGetPathFromIDList = ::SHGetPathFromIDListW;
       theLinuxShell.m_pfnFindFirstFile = ::FindFirstFileW;
       theLinuxShell.m_pfnFindNextFile = ::FindNextFileW;
       theLinuxShell.m_pfnMoveFile = ::MoveFileW;
       theLinuxShell.m_pfn_fullpath = ::_wfullpath;
       theLinuxShell.m_pfnGetFullPathName = ::GetFullPathNameW;
       theLinuxShell.m_pfnGetVolumeInformation = ::GetVolumeInformationW;
       theLinuxShell.m_pfnSHGetFileInfo = ::SHGetFileInfoW;
       theLinuxShell.m_pfnGetStringTypeEx = ::GetStringTypeExW;
       theLinuxShell.m_pfnGetTempPath = ::GetTempPathW;
       theLinuxShell.m_pfnGetTempFileName = ::GetTempFileNameW;
       theLinuxShell.m_pfnCreateFile = ::CreateFileW;
       theLinuxShell.m_pfnGetModuleFileName = ::GetModuleFileNameW;
       theLinuxShell.m_pfnGetClassInfo = ::GetClassInfoW;
       theLinuxShell.m_pfnRegisterClass = ::RegisterClassW;
       theLinuxShell.m_pfnCreateWindowEx = ::CreateWindowExW;
       }
       else
       {
       theLinuxShell.m_pfnSHGetPathFromIDList = _SHGetPathFromIDList;
       theLinuxShell.m_pfnFindFirstFile = _FindFirstFile;
       theLinuxShell.m_pfnFindNextFile = _FindNextFile;
       theLinuxShell.m_pfnMoveFile = _MoveFile;
       theLinuxShell.m_pfn_fullpath = __fullpath;
       theLinuxShell.m_pfnGetFullPathName = _GetFullPathName;
       theLinuxShell.m_pfnGetVolumeInformation = _GetVolumeInformation;
       theLinuxShell.m_pfnSHGetFileInfo = _SHGetFileInfo;
       theLinuxShell.m_pfnGetStringTypeEx = _GetStringTypeEx;
       theLinuxShell.m_pfnGetTempPath = _GetTempPath;
       theLinuxShell.m_pfnGetTempFileName = _GetTempFileName;
       theLinuxShell.m_pfnCreateFile = _CreateFile;
       theLinuxShell.m_pfnGetModuleFileName = _GetModuleFileName;
       theLinuxShell.m_pfnGetClassInfo = _GetClassInfo;
       theLinuxShell.m_pfnRegisterClass = _RegisterClass;
       theLinuxShell.m_pfnCreateWindowEx = _CreateWindowEx;
       }
       */
      return true;
   }
   
   /*
    WINBOOL shell::_SHGetPathFromIDList(LPCITEMIDLIST pidl, wchar_t * pszPath)
    {
    CHAR pszPathA[MAX_PATH * 2];
    if(!::SHGetPathFromIDListA(pidl, pszPathA))
    return FALSE;
    return ::str::international::ACPToUnicode(pszPath, MAX_PATH * 2, pszPathA) ? TRUE : FALSE;
    }
    
    WINBOOL shell::_MoveFile(const wchar_t * lpExistingFileName, const wchar_t * lpNewFileName)
    {
    string str1, str2;
    ::str::international::UnicodeToACP(str1, lpExistingFileName);
    ::str::international::UnicodeToACP(str2, lpNewFileName);
    return ::MoveFileA(str1, str2);
    }
    
    HANDLE shell::_FindFirstFile(const wchar_t * lpcsz, WIN32_FIND_DATAW * lpdata)
    {
    CHAR pszPathA[MAX_PATH * 2];
    ::str::international::UnicodeToACP(pszPathA, MAX_PATH * 2, lpcsz);
    WIN32_FIND_DATAA data;
    HANDLE handle = ::FindFirstFileA(pszPathA, &data);
    if(handle == INVALID_HANDLE_VALUE)
    return INVALID_HANDLE_VALUE;
    
    lpdata->dwFileAttributes = data.dwFileAttributes;
    lpdata->ftCreationTime = data.ftCreationTime;
    lpdata->ftLastAccessTime = data.ftLastAccessTime;
    lpdata->ftLastWriteTime = data.ftLastWriteTime;
    lpdata->nFileSizeHigh = data.nFileSizeHigh;
    lpdata->nFileSizeLow = data.nFileSizeLow;
    lpdata->dwReserved0 = data.dwReserved0;
    lpdata->dwReserved1 = data.dwReserved1;
    ::str::international::ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
    ::str::international::ACPToUnicode(lpdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);
    
    return handle;
    }
    
    WINBOOL shell::_FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
    {
    WIN32_FIND_DATAA data;
    WINBOOL b = ::FindNextFileA(handle, &data);
    if(b == FALSE)
    return FALSE;
    
    lpdata->dwFileAttributes = data.dwFileAttributes;
    lpdata->ftCreationTime = data.ftCreationTime;
    lpdata->ftLastAccessTime = data.ftLastAccessTime;
    lpdata->ftLastWriteTime = data.ftLastWriteTime;
    lpdata->nFileSizeHigh = data.nFileSizeHigh;
    lpdata->nFileSizeLow = data.nFileSizeLow;
    lpdata->dwReserved0 = data.dwReserved0;
    lpdata->dwReserved1 = data.dwReserved1;
    ::str::international::ACPToUnicode(lpdata->cFileName, MAX_PATH, data.cFileName);
    ::str::international::ACPToUnicode(lpdata->cAlternateFileName, MAX_PATH, data.cAlternateFileName);
    
    return b;
    }
    
    
    WCHAR * __cdecl shell::__fullpath (
    WCHAR *UserBuf,
    const WCHAR *path,
    size_t maxlen
    )
    {
    WCHAR *buf;
    WCHAR *pfname;
    unsigned long count;
    
    
    if ( !path || !*path )  // no work to do
//             return( _wgetcwd( UserBuf, maxlen ) );
    
// allocate buffer if necessary
   
  //    if ( !UserBuf )
    //if ( !(buf = (WCHAR *) malloc(_MAX_PATH * sizeof(WCHAR))) ) {
                    errno = ENOMEM;
    return( NULL );
    }
    else
    maxlen = _MAX_PATH;
    else
    buf = UserBuf;
    
    count = GetFullPathName ( path,
    maxlen,
    buf,
    &pfname );
    
    if ( count >= maxlen ) {
    if ( !UserBuf )
    free(buf);
    //errno = ERANGE;
    return( NULL );
    }
    else if ( count == 0 ) {
    if ( !UserBuf )
    free(buf);
    //_dosmaperr( GetLastError() );
    return( NULL );
    }
    
    return( buf );
    
    }
    
    
    DWORD WINAPI shell::_GetFullPathName(
    const wchar_t * lpFileName,
    DWORD nBufferLength,
    wchar_t * lpBuffer,
    wchar_t ** lpFilePart)
    {
    CHAR pszPathA[MAX_PATH * 2];
    ::str::international::UnicodeToACP(pszPathA, MAX_PATH * 2, lpFileName);
    string str;
    LPTSTR lpsz = str.GetBuffer(nBufferLength * 2);
    LPTSTR lpszFilePart;
    DWORD dw = ::GetFullPathName(pszPathA, nBufferLength, lpsz, &lpszFilePart);
    str.ReleaseBuffer();
    ::str::international::ACPToUnicode(lpBuffer, nBufferLength, str);
    *lpFilePart = lpBuffer + ((int32_t) (lpszFilePart - lpsz));
    return dw;
    }
    
    WINBOOL WINAPI shell::_GetVolumeInformation(
    const wchar_t * lpRootPathName,           // root directory
    wchar_t * lpVolumeNameBuffer,        // volume name buffer
    DWORD nVolumeNameSize,            // length of name buffer
    LPDWORD lpVolumeSerialNumber,     // volume serial number
    LPDWORD lpMaximumComponentLength, // maximum file name length
    LPDWORD lpFileSystemFlags,        // file system options
    wchar_t * lpFileSystemNameBuffer,    // file system name buffer
    DWORD nFileSystemNameSize)         // length of file system name buffer
    {
    string strRootPathName;
    string strVolumeNameBuffer;
    string strFileSystemNameBuffer;
    ::str::international::UnicodeToACP(strRootPathName, lpRootPathName);
    WINBOOL b = ::GetVolumeInformation(
    strRootPathName,
    strVolumeNameBuffer.GetBuffer(nVolumeNameSize),
    nVolumeNameSize,
    lpVolumeSerialNumber,
    lpMaximumComponentLength,
    lpFileSystemFlags,
    strFileSystemNameBuffer.GetBuffer(nFileSystemNameSize),
    nFileSystemNameSize);
    
    strVolumeNameBuffer.ReleaseBuffer();
    strFileSystemNameBuffer.ReleaseBuffer();
    ::str::international::ACPToUnicode(
    lpVolumeNameBuffer,
    nVolumeNameSize,
    strVolumeNameBuffer);
    ::str::international::ACPToUnicode(
    lpFileSystemNameBuffer,
    nFileSystemNameSize,
    strFileSystemNameBuffer);
    return b;
    }
    
    DWORD_PTR shell::_SHGetFileInfo(
    const wchar_t * pszPath,
    DWORD dwFileAttributes,
    SHFILEINFOW *psfi,
    UINT cbFileInfo,
    UINT uFlags)
    {
    UNREFERENCED_PARAMETER(cbFileInfo);
    string strPath;
    ::str::international::UnicodeToACP(strPath, pszPath);
    SHFILEINFOA shia;
    if(!::SHGetFileInfoA(strPath, dwFileAttributes,
    &shia,
    sizeof(shia),
    uFlags))
    return FALSE;
    ::str::international::ACPToUnicode(
    psfi->szDisplayName,
    sizeof(psfi->szDisplayName) / sizeof(WCHAR),
    shia.szDisplayName);
    ::str::international::ACPToUnicode(
    psfi->szTypeName,
    sizeof(psfi->szTypeName) / sizeof(WCHAR),
    shia.szTypeName);
    return TRUE;
    }
    
    
    WINBOOL shell::_GetStringTypeEx(
    LCID uiCodePage,
    DWORD dwInfoType,
    const wchar_t * lpSrcStr,
    int32_t cchSrc,
    LPWORD lpCharType)
    {
    int32_t iCount = cchSrc;
    if(iCount < 0)
    iCount = ::str::international::UnicodeToMultiByteCount(uiCodePage, lpSrcStr);
    string str;
    LPTSTR lpsz = str.GetBuffer(iCount);
    if(::str::international::UnicodeToMultiByte(uiCodePage, lpsz, iCount, lpSrcStr))
    {
    //str.ReleaseBuffer();
    //return true;
    }
    else
    {
    return false;
    }
    if(!GetStringTypeA(uiCodePage, dwInfoType, lpsz, iCount, lpCharType))
    {
    return FALSE;
    }
    return TRUE;
    }
    
    
    DWORD shell::_GetTempPath(
    DWORD nBufferLength,
    wchar_t * lpBuffer)
    {
    string str;
    DWORD dw = ::GetTempPathA(nBufferLength, str.GetBuffer(nBufferLength * 2));
    str.ReleaseBuffer();
    ::str::international::ACPToUnicode(lpBuffer, nBufferLength, str);
    return dw;
    }
    
    UINT shell::_GetTempFileName(
    const wchar_t * lpPathName,
    const wchar_t * lpPrefixString,
    UINT uUnique,
    wchar_t * lpTempFileName)
    {
    string strPathName;
    string strPrefixString;
    string strTempFileName;
    ::str::international::UnicodeToACP(strPathName, lpPathName);
    ::str::international::UnicodeToACP(strPrefixString, lpPrefixString);
    UINT user = ::GetTempFileNameA(
    strPathName,
    strPrefixString,
    uUnique,
    strTempFileName.GetBuffer(MAX_PATH));
    if(user == 0)
    {
    return 0;
    }
    strTempFileName.ReleaseBuffer();
    ::str::international::ACPToUnicode(
    lpTempFileName,
    MAX_PATH,
    strTempFileName);
    return user;
    }
    
    
    HANDLE shell::_CreateFile(
    const wchar_t * lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    )
    {
    string strFileName;
    ::str::international::UnicodeToACP(strFileName, lpFileName);
    HANDLE handle = ::CreateFileA(
    strFileName,
    dwDesiredAccess,
    dwShareMode,
    lpSecurityAttributes,
    dwCreationDisposition,
    dwFlagsAndAttributes,
    hTemplateFile);
    return handle;
    }
    
    
    DWORD shell::_GetModuleFileName(
    HMODULE hModule,
    wchar_t * lpFilename,
    DWORD nSize
    )
    {
    string str;
    DWORD dw = ::GetModuleFileNameA(hModule, str.GetBuffer(nSize * 2), nSize * 2);
    str.ReleaseBuffer();
    ::str::international::ACPToUnicode(lpFilename, nSize, str);
    return dw;
    }
    
    WINBOOL shell::_GetClassInfo(
    HINSTANCE hInstance ,
    const wchar_t * lpClassName,
    LPWNDCLASSW lpWndClass)
    {
    WNDCLASS wndclass;
    
    string strClassName;
    const char * lpszClassName;
    if(((DWORD) lpClassName) >> 16 == 0)
    {
    lpszClassName = (const char *) lpClassName;
    }
    else
    {
    strClassName = lpClassName;
    lpszClassName = strClassName;
    }
    if(!::GetClassInfoA(hInstance, lpszClassName, &wndclass))
    return FALSE;
    
    lpWndClass->style = wndclass.style;
    lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
    lpWndClass->lpfnWndProc = wndclass.lpfnWndProc;
    lpWndClass->cbClsExtra = wndclass.cbClsExtra;
    lpWndClass->cbWndExtra = wndclass.cbWndExtra;
    lpWndClass->hInstance = wndclass.hInstance;
    lpWndClass->hIcon = wndclass.hIcon;
    lpWndClass->hCursor = wndclass.hCursor;
    lpWndClass->hbrBackground = wndclass.hbrBackground;
    
  if(((DWORD) wndclass) >> 16 == 0)
    {
    lpszClassName = (const char *) lpClassName;
    }
    else
    {
    strClassName = lpClassName;
    lpszClassName = strClassName
    }
    string strMenuName;*/
   //strMenuName = wndclass->lpszMenuName;
   /*   lpWndClass->lpszMenuName = (const wchar_t *) wndclass.lpszMenuName;
    
    lpWndClass->lpszClassName = (const wchar_t *) wndclass.lpszClassName;
    
    return TRUE;
    
    }
    ATOM shell::_RegisterClass(
    CONST WNDCLASSW *lpWndClass)
    {
    WNDCLASS wndclass;
    
    wndclass.style = lpWndClass->style;
    wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
    wndclass.lpfnWndProc = lpWndClass->lpfnWndProc;
    wndclass.cbClsExtra = lpWndClass->cbClsExtra;
    wndclass.cbWndExtra = lpWndClass->cbWndExtra;
    wndclass.hInstance = lpWndClass->hInstance;
    wndclass.hIcon = lpWndClass->hIcon;
    wndclass.hCursor = lpWndClass->hCursor;
    wndclass.hbrBackground = lpWndClass->hbrBackground;
    
    string strMenuName;
    strMenuName = lpWndClass->lpszMenuName;
    wndclass.lpszMenuName = strMenuName;
    
    string strClassName;
    strClassName = lpWndClass->lpszClassName;
    wndclass.lpszClassName = strClassName;
    
    return ::RegisterClassA(&wndclass);
    }
    
    
    oswindow shell::_CreateWindowEx(
    DWORD dwExStyle,
    const wchar_t * lpClassName,
    const wchar_t * lpWindowName,
    DWORD dwStyle,
    int32_t x,
    int32_t y,
    int32_t nWidth,
    int32_t nHeight,
    oswindow hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam)
    {
    string strClassName;
    const char * lpszClassName;
    if(((DWORD) lpClassName) >> 16 == 0)
    {
    lpszClassName = (const char *) lpClassName;
    }
    else
    {
    strClassName = lpClassName;
    lpszClassName = strClassName;
    }
    
    string strWindowName;
    strWindowName = lpWindowName;
    
    return ::CreateWindowExA(
    dwExStyle,
    lpszClassName,
    strWindowName,
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
    */
   
} // namespace mac
