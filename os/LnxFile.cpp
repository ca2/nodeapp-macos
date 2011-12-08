#include "StdAfx.h"

#include "WinFile.h"
#include "WindowsShell.h"


AFX_STATIC inline BOOL IsDirSep(WCHAR ch)
{
   return (ch == '\\' || ch == '/');
}


WinFile::WinFile(::ca::application * papp) :
   ca(papp)
{
   m_hFile = (UINT) hFileNull;
   m_bCloseOnDelete = FALSE;
}

WinFile::WinFile(::ca::application * papp, int hFile) :
   ca(papp)
{
   m_hFile = hFile;
   m_bCloseOnDelete = FALSE;
}

WinFile::WinFile(::ca::application * papp, const char * lpszFileName, UINT nOpenFlags) :
   ca(papp)
{
   ASSERT(AfxIsValidString(lpszFileName));

   ex1::file_exception_sp e(get_app());
   if(!open(lpszFileName, nOpenFlags, &e))
      //xxx vfxThrowFileException(e);
      throw &e;
}

WinFile::~WinFile()
{
   if (m_hFile != (UINT)hFileNull && m_bCloseOnDelete)
      close();
}

ex1::file * WinFile::Duplicate() const
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   WinFile* pFile = new WinFile(get_app(), hFileNull);
   HANDLE hFile;
   if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
      ::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
   {
      delete pFile;
//xxx      Ex1WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
      throw 0;
   }
   pFile->m_hFile = (UINT)hFile;
   ASSERT(pFile->m_hFile != (UINT)hFileNull);
   pFile->m_bCloseOnDelete = m_bCloseOnDelete;
   return pFile;
}

BOOL WinFile::open(const char * lpszFileName, UINT nOpenFlags, ex1::file_exception_sp* pException)
{
   if (m_hFile != (UINT)hFileNull)
      close();
   ASSERT_VALID(this);
   ASSERT(AfxIsValidString(lpszFileName));
   ASSERT(pException == NULL ||
      fx_is_valid_address(pException, sizeof(ex1::file_exception_sp)));
   ASSERT((nOpenFlags & type_text) == 0);   // text mode not supported

   // WinFile objects are always binary and CreateFile does not need flag
   nOpenFlags &= ~(UINT)type_binary;


   if(nOpenFlags & ex1::file::defer_create_directory)
   {
      System.dir_mk(System.dir_name(lpszFileName));
   }

   m_bCloseOnDelete = FALSE;
   m_hFile = (UINT)hFileNull;
   m_strFileName.Empty();

   try
   {
      System.file_system().FullPath(m_strFileName, lpszFileName);
   }
   catch(...)
   {
      return FALSE;
   }

   ASSERT(sizeof(HANDLE) == sizeof(UINT_PTR));
   ASSERT(shareCompat == 0);

   // ::collection::map read/write mode
   ASSERT((mode_read|mode_write|mode_read_write) == 3);
   DWORD dwAccess = 0;
   switch (nOpenFlags & 3)
   {
   case mode_read:
      dwAccess = GENERIC_READ;
      break;
   case mode_write:
      dwAccess = GENERIC_WRITE;
      break;
   case mode_read_write:
      dwAccess = GENERIC_READ|GENERIC_WRITE;
      break;
   default:
      dwAccess = GENERIC_READ;
      break;
   }

   // ::collection::map share mode
   DWORD dwShareMode = 0;
   switch (nOpenFlags & 0x70)    // ::collection::map compatibility mode to exclusive
   {
   default:
      ASSERT(FALSE);  // invalid share mode?
   case shareCompat:
   case shareExclusive:
      dwShareMode = 0;
      break;
   case shareDenyWrite:
      dwShareMode = FILE_SHARE_READ;
      break;
   case shareDenyRead:
      dwShareMode = FILE_SHARE_WRITE;
      break;
   case shareDenyNone:
      dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
      break;
   }

   // Note: type_text and type_binary are used in derived classes only.

   // ::collection::map modeNoInherit flag
   SECURITY_ATTRIBUTES sa;
   sa.nLength = sizeof(sa);
   sa.lpSecurityDescriptor = NULL;
   sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;

   // ::collection::map creation flags
   DWORD dwCreateFlag;
   if (nOpenFlags & mode_create)
   {
      if (nOpenFlags & modeNoTruncate)
         dwCreateFlag = OPEN_ALWAYS;
      else
         dwCreateFlag = CREATE_ALWAYS;
   }
   else
      dwCreateFlag = OPEN_EXISTING;

   // attempt file creation
   HANDLE hFile = WindowsShell::CreateFile(gen::international::utf8_to_unicode(m_strFileName), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFile == INVALID_HANDLE_VALUE)
   {
      if (pException != NULL)
      {
         WinFileException * pfe = dynamic_cast < WinFileException * > (pException->m_p);
         if(pfe != NULL)
         {
            pfe->m_lOsError = ::GetLastError();
            pfe->m_cause = WinFileException::OsErrorToException(pfe->m_lOsError);
            pfe->m_strFileName = lpszFileName;
         }
         return FALSE;
      }
      else
      {
         DWORD dwLastError = ::GetLastError();
         vfxThrowFileException(get_app(), WinFileException::OsErrorToException(dwLastError), dwLastError, m_strFileName);
      }
   }
   m_hFile = (HFILE)hFile;
   m_bCloseOnDelete = TRUE;

   return TRUE;
}

DWORD_PTR WinFile::read(void * lpBuf, DWORD_PTR nCount)
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   if (nCount == 0)
      return 0;   // avoid Win32 "null-read"

   ASSERT(lpBuf != NULL);
   ASSERT(fx_is_valid_address(lpBuf, nCount));

   DWORD dwRead;
   if (!::ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());

   return (UINT)dwRead;
}

void WinFile::write(const void * lpBuf, DWORD_PTR nCount)
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   if (nCount == 0)
      return;     // avoid Win32 "null-write" option

   ASSERT(lpBuf != NULL);
   ASSERT(fx_is_valid_address(lpBuf, nCount, FALSE));

   DWORD nWritten;
   if (!::WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError(), m_strFileName);

   // Win32s will not return an error all the time (usually DISK_FULL)
   if (nWritten != nCount)
      vfxThrowFileException(get_app(), ::ex1::file_exception::diskFull, -1, m_strFileName);
}

INT_PTR WinFile::seek(INT_PTR lOff, UINT nFrom)
{
   
   if(m_hFile == (UINT)hFileNull)
      WinFileException::ThrowOsError(get_app(), (LONG)0);

   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);
   ASSERT(nFrom == begin || nFrom == end || nFrom == current);
   ASSERT(begin == FILE_BEGIN && end == FILE_END && current == FILE_CURRENT);

   DWORD dwNew = ::SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
   if (dwNew  == (DWORD)-1)
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());

   return dwNew;
}

DWORD_PTR WinFile::GetPosition() const
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   DWORD dwPos = ::SetFilePointer((HANDLE)m_hFile, 0, NULL, FILE_CURRENT);
   if (dwPos  == (DWORD)-1)
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());

   return dwPos;
}

void WinFile::Flush()
{
   ASSERT_VALID(this);

   if (m_hFile == (UINT)hFileNull)
      return;

   if (!::FlushFileBuffers((HANDLE)m_hFile))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

void WinFile::close()
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   BOOL bError = FALSE;
   if (m_hFile != (UINT)hFileNull)
      bError = !::CloseHandle((HANDLE)m_hFile);

   m_hFile = (UINT) hFileNull;
   m_bCloseOnDelete = FALSE;
   m_strFileName.Empty();

   if (bError)
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

void WinFile::Abort()
{
   ASSERT_VALID(this);
   if (m_hFile != (UINT)hFileNull)
   {
      // close but ignore errors
      ::CloseHandle((HANDLE)m_hFile);
      m_hFile = (UINT)hFileNull;
   }
   m_strFileName.Empty();
}

void WinFile::LockRange(DWORD_PTR dwPos, DWORD_PTR dwCount)
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   if (!::LockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

void WinFile::UnlockRange(DWORD_PTR dwPos, DWORD_PTR dwCount)
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   if (!::UnlockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

void WinFile::SetLength(DWORD_PTR dwNewLen)
{
   ASSERT_VALID(this);
   ASSERT(m_hFile != (UINT)hFileNull);

   seek((LONG)dwNewLen, (UINT)begin);

   if (!::SetEndOfFile((HANDLE)m_hFile))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

DWORD_PTR WinFile::get_length() const
{
   ASSERT_VALID(this);

   DWORD_PTR dwLen, dwCur;

   // seek is a non const operation
   WinFile* pFile = (WinFile*)this;
   dwCur = pFile->seek(0L, current);
   dwLen = pFile->seek_to_end();
   VERIFY(dwCur == (DWORD_PTR)pFile->seek(dwCur, begin));

   return dwLen;
}

// WinFile does not support direct buffering (CMemFile does)
DWORD_PTR WinFile::GetBufferPtr(UINT nCommand, DWORD_PTR /*nCount*/,
   void ** /*ppBufStart*/, void ** /*ppBufMax*/)
{
   ASSERT(nCommand == bufferCheck);
   UNUSED(nCommand);    // not used in retail build

   return 0;   // no support
}

/*
void PASCAL WinFile::Rename(const char * lpszOldName, const char * lpszNewName)
{
   if (!::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}

void PASCAL WinFile::remove(const char * lpszFileName)
{
   if (!::DeleteFile((LPTSTR)lpszFileName))
      WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
}
*/


string CLASS_DECL_VMSWIN vfxStringFromCLSID(REFCLSID rclsid)
{
   WCHAR szCLSID[256];
   wsprintfW(szCLSID, L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
      rclsid.Data1, rclsid.Data2, rclsid.Data3,
      rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3],
      rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);
   return szCLSID;
}

BOOL CLASS_DECL_VMSWIN vfxGetInProcServer(const char * lpszCLSID, string & str)
{
   HKEY hKey = NULL;
   BOOL b = FALSE;
   if (RegOpenKey(HKEY_CLASSES_ROOT, "CLSID", &hKey) == ERROR_SUCCESS)
   {
      HKEY hKeyCLSID = NULL;
      if (RegOpenKey(hKey, lpszCLSID, &hKeyCLSID) == ERROR_SUCCESS)
      {
         HKEY hKeyInProc = NULL;
         if (RegOpenKey(hKeyCLSID, "InProcServer32", &hKeyInProc) ==
            ERROR_SUCCESS)
         {
            LPTSTR lpsz = str.GetBuffer(_MAX_PATH);
            DWORD dwSize = _MAX_PATH * sizeof(char);
            DWORD dwType;
            LONG lRes = ::RegQueryValueEx(hKeyInProc, "",
               NULL, &dwType, (BYTE*)lpsz, &dwSize);
            str.ReleaseBuffer();
            b = (lRes == ERROR_SUCCESS);
            RegCloseKey(hKeyInProc);
         }
         RegCloseKey(hKeyCLSID);
      }
      RegCloseKey(hKey);
   }
   return b;
}
//#endif  //!_AFX_NO_OLE_SUPPORT


BOOL CLASS_DECL_VMSWIN vfxResolveShortcut(::ca::window * pWnd, const wchar_t * lpszFileIn,
   wchar_t * lpszFileOut, int cchPath)
{
   UNREFERENCED_PARAMETER(pWnd);
   UNREFERENCED_PARAMETER(lpszFileIn);
   UNREFERENCED_PARAMETER(lpszFileOut);
   UNREFERENCED_PARAMETER(cchPath);
   throw not_implemented_exception();
/*
   DWORD dwVersion = GetVersion();
 
   // get the Windows version.

   DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
   DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));

   // get the build number.

   DWORD dwBuild;

   if (dwVersion < 0x80000000)              // Windows NT
       dwBuild = (DWORD)(HIWORD(dwVersion));
   else if (dwWindowsMajorVersion < 4)      // Win32s
       dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
   else                                     // Windows Me/98/95
       dwBuild =  0;

   BOOL bNativeUnicode;
   if (dwVersion < 0x80000000)              // Windows NT
       bNativeUnicode = TRUE;
   else if (dwWindowsMajorVersion < 4)      // Win32s
       bNativeUnicode = FALSE;
   else                                     // Windows Me/98/95
       bNativeUnicode = FALSE;

   
   if(bNativeUnicode)
   {
      AFX_COM com;
      IShellLinkW* psl;
      *lpszFileOut = 0;   // assume failure

      SHFILEINFOW info;
      if ((WindowsShell::SHGetFileInfo(lpszFileIn, 0, &info, sizeof(info),
         SHGFI_ATTRIBUTES) == 0) || !(info.dwAttributes & SFGAO_LINK))
      {
         return FALSE;
      }

      if (FAILED(com.CreateInstance(CLSID_ShellLink, NULL, IID_IShellLink,
         (LPVOID*)&psl)))
      {
         return FALSE;
      }

      IPersistFile *ppf;
      if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf)))
      {
         if (SUCCEEDED(ppf->Load(lpszFileIn, STGM_READ)))
         {
            /* Resolve the link, this may post UI to find the link */
/*            if (SUCCEEDED(psl->Resolve(WIN_WINDOW(pWnd)->GetSafeHwnd(),
               SLR_ANY_MATCH)))
            {
               psl->GetPath(lpszFileOut, cchPath, NULL, 0);
               ppf->Release();
               psl->Release();
               return TRUE;
            }
         }
         ppf->Release();
      }
      psl->Release();
      return FALSE;
   }
   else
   {
      string strFileIn;
      string strFileOut;

      gen::international::UnicodeToMultiByte(gen::international::CodePageAnsi, strFileIn, lpszFileIn);

      AFX_COM com;
      IShellLink* psl;
      *lpszFileOut = 0;   // assume failure

      SHFILEINFO info;
      if ((SHGetFileInfo(strFileIn, 0, &info, sizeof(info),
         SHGFI_ATTRIBUTES) == 0) || !(info.dwAttributes & SFGAO_LINK))
      {
         return FALSE;
      }

      if (FAILED(com.CreateInstance(CLSID_ShellLink, NULL, IID_IShellLink,
         (LPVOID*)&psl)))
      {
         return FALSE;
      }

      IPersistFile *ppf;
      if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf)))
      {
         if (SUCCEEDED(ppf->Load(lpszFileIn, STGM_READ)))
         {
            /* Resolve the link, this may post UI to find the link */
/*            if (SUCCEEDED(psl->Resolve(WIN_WINDOW(pWnd)->GetSafeHwnd(),
               SLR_ANY_MATCH)))
            {
               psl->GetPath(strFileOut.GetBuffer(cchPath), cchPath, NULL, 0);
               gen::international::MultiByteToUnicode(
                  gen::international::CodePageAnsi,
                  lpszFileOut,
                  cchPath,
                  strFileOut);
               ppf->Release();
               psl->Release();
               return TRUE;
            }
         }
         ppf->Release();
      }
      psl->Release();
      return FALSE;
   }*/
}

// turn a file, relative path or other into an absolute path
BOOL CLASS_DECL_VMSWIN vfxFullPath(wchar_t * lpszPathOut, const wchar_t * lpszFileIn)
   // lpszPathOut = buffer of _MAX_PATH
   // lpszFileIn = file, relative path or absolute path
   // (both in ANSI character set)
{
   ASSERT(fx_is_valid_address(lpszPathOut, _MAX_PATH));

   // first, fully qualify the path name
   wchar_t * lpszFilePart;
   if (!GetFullPathNameW(lpszFileIn, _MAX_PATH, lpszPathOut, &lpszFilePart))
   {
#ifdef _DEBUG
//      if (lpszFileIn[0] != '\0')
  //       TRACE1("Warning: could not parse the path '%s'.\n", lpszFileIn);
#endif
      lstrcpynW(lpszPathOut, lpszFileIn, _MAX_PATH); // take it literally
      return FALSE;
   }

   string strRoot;
   // determine the root name of the volume
   vfxGetRoot(lpszPathOut, strRoot);

   // get file system information for the volume
   DWORD dwFlags, dwDummy;
   if (!GetVolumeInformationW(gen::international::utf8_to_unicode(strRoot), NULL, 0, NULL, &dwDummy, &dwFlags, NULL, 0))
   {
//      TRACE1("Warning: could not get volume information '%s'.\n", strRoot);
      return FALSE;   // preserving case may not be correct
   }

   // not all characters have complete uppercase/lowercase
   if (!(dwFlags & FS_CASE_IS_PRESERVED))
      CharUpperW(lpszPathOut);

   // assume non-UNICODE file systems, use OEM character set
   if (!(dwFlags & FS_UNICODE_STORED_ON_DISK))
   {
      WIN32_FIND_DATAW data;
      HANDLE h = FindFirstFileW(lpszFileIn, &data);
      if (h != INVALID_HANDLE_VALUE)
      {
         FindClose(h);
         lstrcpyW(lpszFilePart, data.cFileName);
      }
   }
   return TRUE;
}

/*void CLASS_DECL_VMSWIN AfxGetRoot(const char * lpszPath, string & strRoot)
{
   ASSERT(lpszPath != NULL);
   // determine the root name of the volume
   LPTSTR lpszRoot = strRoot.GetBuffer(_MAX_PATH);
   memset(lpszRoot, 0, _MAX_PATH);
   lstrcpyn(lpszRoot, lpszPath, _MAX_PATH);
   LPTSTR lpsz;
   for (lpsz = lpszRoot; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
   {
      // find first double slash and stop
      if (IsDirSep(lpsz[0]) && IsDirSep(lpsz[1]))
         break;
   }
   if (*lpsz != '\0')
   {
      // it is a UNC name, find second slash past '\\'
      ASSERT(IsDirSep(lpsz[0]));
      ASSERT(IsDirSep(lpsz[1]));
      lpsz += 2;
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _tcsinc(lpsz);
      if (*lpsz != '\0')
         lpsz = _tcsinc(lpsz);
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _tcsinc(lpsz);
      // terminate it just after the UNC root (ie. '\\server\share\')
      if (*lpsz != '\0')
         lpsz[1] = '\0';
   }
   else
   {
      // not a UNC, look for just the first slash
      lpsz = lpszRoot;
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _tcsinc(lpsz);
      // terminate it just after root (ie. 'x:\')
      if (*lpsz != '\0')
         lpsz[1] = '\0';
   }
   strRoot.ReleaseBuffer();
}*/

/*BOOL CLASS_DECL_VMSWIN AfxComparePath(const char * lpszPath1, const char * lpszPath2)
{
   // use case insensitive compare as a starter
   if (lstrcmpi(lpszPath1, lpszPath2) != 0)
      return FALSE;

   // on non-DBCS systems, we are done
   if (!GetSystemMetrics(SM_DBCSENABLED))
      return TRUE;

   // on DBCS systems, the file name may not actually be the same
   // in particular, the file system is case sensitive with respect to
   // "full width" roman characters.
   // (ie. fullwidth-R is different from fullwidth-r).
   int nLen = lstrlen(lpszPath1);
   if (nLen != lstrlen(lpszPath2))
      return FALSE;
   ASSERT(nLen < _MAX_PATH);

   // need to get both CT_CTYPE1 and CT_CTYPE3 for each filename
   LCID lcid = GetThreadLocale();
   WORD aCharType11[_MAX_PATH];
   VERIFY(GetStringTypeEx(lcid, CT_CTYPE1, lpszPath1, -1, aCharType11));
   WORD aCharType13[_MAX_PATH];
   VERIFY(GetStringTypeEx(lcid, CT_CTYPE3, lpszPath1, -1, aCharType13));
   WORD aCharType21[_MAX_PATH];
   VERIFY(GetStringTypeEx(lcid, CT_CTYPE1, lpszPath2, -1, aCharType21));
#ifdef _DEBUG
   WORD aCharType23[_MAX_PATH];
   VERIFY(GetStringTypeEx(lcid, CT_CTYPE3, lpszPath2, -1, aCharType23));
#endif

   // for every C3_FULLWIDTH character, make sure it has same C1 value
   int i = 0;
   for (const char * lpsz = lpszPath1; *lpsz != 0; lpsz = _tcsinc(lpsz))
   {
      // check for C3_FULLWIDTH characters only
      if (aCharType13[i] & C3_FULLWIDTH)
      {
#ifdef _DEBUG
         ASSERT(aCharType23[i] & C3_FULLWIDTH); // should always match!
#endif

         // if CT_CTYPE1 is different then file system considers these
         // file names different.
         if (aCharType11[i] != aCharType21[i])
            return FALSE;
      }
      ++i; // look at next character type
   }
   return TRUE; // otherwise file name is truly the same
}*/

/*UINT CLASS_DECL_VMSWIN AfxGetFileTitle(const char * lpszPathName, LPTSTR lpszTitle, UINT nMax)
{
   ASSERT(lpszTitle == NULL ||
      fx_is_valid_address(lpszTitle, _MAX_FNAME));
   ASSERT(AfxIsValidString(lpszPathName));

   // use a temporary to avoid bugs in ::GetFileTitle when lpszTitle is NULL
   char szTemp[_MAX_PATH];
   LPTSTR lpszTemp = lpszTitle;
   if (lpszTemp == NULL)
   {
      lpszTemp = szTemp;
      nMax = _countof(szTemp);
   }
   if (::GetFileTitle(lpszPathName, lpszTemp, (WORD)nMax) != 0)
   {
      // when ::GetFileTitle fails, use cheap imitation
      return AfxGetFileName(lpszPathName, lpszTitle, nMax);
   }
   return lpszTitle == NULL ? lstrlen(lpszTemp)+1 : 0;
}*/

void CLASS_DECL_VMSWIN vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{
   WCHAR szLongPathName[_MAX_PATH];
   wstring wstrShortName;
   ::GetModuleFileNameW(hInst, szLongPathName, _MAX_PATH);
   if(::GetShortPathNameW(szLongPathName, wstrShortName.alloc(_MAX_PATH * 4), _MAX_PATH * 4) == 0)
   {
      // rare failure case (especially on not-so-modern file systems)
      gen::international::unicode_to_utf8(strShortName, szLongPathName);
   }
   else
   {
      gen::international::unicode_to_utf8(strShortName, wstrShortName);
   }
}

/////////////////////////////////////////////////////////////////////////////
// WinFile diagnostics

#ifdef _DEBUG
void WinFile::assert_valid() const
{
   ::radix::object::assert_valid();
   // we permit the descriptor m_hFile to be any value for derived classes
}

void WinFile::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "with handle " << (UINT)m_hFile;
   dumpcontext << " and name \"" << m_strFileName << "\"";
   dumpcontext << "\n";
}
#endif


// IMPLEMENT_DYNAMIC(WinFile, ::radix::object)

/////////////////////////////////////////////////////////////////////////////

#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

void CLASS_DECL_VMSWIN vfxGetRoot(const wchar_t * lpszPath, string& strRoot)
{
   ASSERT(lpszPath != NULL);
   wstring wstrRoot;
   // determine the root name of the volume
   wchar_t * lpszRoot = wstrRoot.alloc(_MAX_PATH * 4);
   memset(lpszRoot, 0, _MAX_PATH * 4);
   lstrcpynW(lpszRoot, lpszPath, _MAX_PATH * 4);
   wchar_t * lpsz;
   for (lpsz = lpszRoot; *lpsz != '\0'; lpsz = _wcsinc(lpsz))
   {
      // find first double slash and stop
      if (IsDirSep(lpsz[0]) && IsDirSep(lpsz[1]))
         break;
   }
   if (*lpsz != '\0')
   {
      // it is a UNC name, find second slash past '\\'
      ASSERT(IsDirSep(lpsz[0]));
      ASSERT(IsDirSep(lpsz[1]));
      lpsz += 2;
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _wcsinc(lpsz);
      if (*lpsz != '\0')
         lpsz = _wcsinc(lpsz);
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _wcsinc(lpsz);
      // terminate it just after the UNC root (ie. '\\server\share\')
      if (*lpsz != '\0')
         lpsz[1] = '\0';
   }
   else
   {
      // not a UNC, look for just the first slash
      lpsz = lpszRoot;
      while (*lpsz != '\0' && (!IsDirSep(*lpsz)))
         lpsz = _wcsinc(lpsz);
      // terminate it just after root (ie. 'x:\')
      if (*lpsz != '\0')
         lpsz[1] = '\0';
   }
   gen::international::unicode_to_utf8(strRoot, wstrRoot);
}


/*BOOL CLASS_DECL_VMSWIN vfxFullPath(char * lpszPathOut, const char * lpszFileIn)
   // lpszPathOut = buffer of _MAX_PATH
   // lpszFileIn = file, relative path or absolute path
   // (both in ANSI character set)
{
   ASSERT(fx_is_valid_address(lpszPathOut, _MAX_PATH));

   // first, fully qualify the path name
   wchar_t * lpszFilePart;
   if (!WindowsShell::GetFullPathName(lpszFileIn, _MAX_PATH, lpszPathOut, &lpszFilePart))
   {
#ifdef _DEBUG
      if (lpszFileIn[0] != '\0')
         TRACE1("Warning: could not parse the path '%s'.\n", lpszFileIn);
#endif
      lstrcpynW(lpszPathOut, lpszFileIn, _MAX_PATH); // take it literally
      return FALSE;
   }

   string wstrRoot;
   // determine the root name of the volume
   vfxGetRoot(lpszPathOut, wstrRoot);

   // get file system information for the volume
   DWORD dwFlags, dwDummy;
   if (!WindowsShell::GetVolumeInformation(wstrRoot, NULL, 0, NULL, &dwDummy, &dwFlags,
      NULL, 0))
   {
      TRACE1("Warning: could not get volume information '%S'.\n",
         (const char *)wstrRoot);
      return FALSE;   // preserving case may not be correct
   }

   // not all characters have complete uppercase/lowercase
   if (!(dwFlags & FS_CASE_IS_PRESERVED))
      CharUpperW(lpszPathOut);

   // assume non-UNICODE file systems, use OEM character set
   if (!(dwFlags & FS_UNICODE_STORED_ON_DISK))
   {
      WIN32_FIND_DATAW data;
      HANDLE h = WindowsShell::FindFirstFile(lpszFileIn, &data);
      if (h != INVALID_HANDLE_VALUE)
      {
         FindClose(h);
         wcscpy(lpszFilePart, data.cFileName);
      }
   }
   return TRUE;
}*/

/////////////////////////////////////////////////////////////////////////////
// FileException helpers

#ifdef _DEBUG
static const char * rgszFileExceptionCause[] =
{
   "none",
   "generic",
   "fileNotFound",
   "badPath",
   "tooManyOpenFiles",
   "accessDenied",
   "invalidFile",
   "removeCurrentDir",
   "directoryFull",
   "badSeek",
   "hardIO",
   "sharingViolation",
   "lockViolation",
   "diskFull",
   "endOfFile",
};
static const char szUnknown[] = "unknown";
#endif


/*void CLASS_DECL_VMSWIN vfxThrowFileException(int cause, LONG lOsError,
//   const char * lpszFileName /* == NULL */
/*{
#ifdef _DEBUG
   const char * lpsz;
   if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
      lpsz = rgszFileExceptionCause[cause];
   else
      lpsz = szUnknown;
   TRACE3("WinFile exception: %hs, WinFile %W, App error information = %ld.\n",
      lpsz, (lpszFileName == NULL) ? L"Unknown" : lpszFileName, lOsError);
#endif
   THROW(new FileException(cause, lOsError, lpszFileName));
}*/

/* Error Codes */

#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

/*
 * Support EDEADLOCK for compatibiity with older MS-C versions.
 */
#define EDEADLOCK       EDEADLK


/////////////////////////////////////////////////////////////////////////////
// WinFile name handlers

string WinFile::GetFileName() const
{
   ASSERT_VALID(this);

   ::ex1::file_status status;
   GetStatus(status);
   string wstrResult;
   System.file_system().GetFileName(status.m_strFullName, wstrResult);
   return wstrResult;
}

string WinFile::GetFileTitle() const
{
   ASSERT_VALID(this);

   ::ex1::file_status status;
   GetStatus(status);
   string wstrResult;
   System.file_system().GetFileTitle(status.m_strFullName, wstrResult);
   return wstrResult;
}

string WinFile::GetFilePath() const
{
   ASSERT_VALID(this);

   ::ex1::file_status status;
   GetStatus(status);
   return status.m_strFullName;
}


UINT CLASS_DECL_VMSWIN vfxGetFileName(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax)
{
   ASSERT(lpszTitle == NULL ||
      fx_is_valid_address(lpszTitle, _MAX_FNAME));
   ASSERT(AfxIsValidString(lpszPathName));

   // always capture the complete file name including extension (if present)
   wchar_t * lpszTemp = (wchar_t *)lpszPathName;
   for (const wchar_t * lpsz = lpszPathName; *lpsz != '\0'; lpsz = _wcsinc(lpsz))
   {
      // remember last directory/drive separator
      if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
         lpszTemp = (wchar_t *)_wcsinc(lpsz);
   }

   // lpszTitle can be NULL which just returns the number of bytes
   if (lpszTitle == NULL)
      return lstrlenW(lpszTemp)+1;

   // otherwise copy it into the buffer provided
   lstrcpynW(lpszTitle, lpszTemp, nMax);
   return 0;
}


/////////////////////////////////////////////////////////////////////////////
// FileException


int WinFileException::get_cause()
{
   return m_cause;
}

LONG WinFileException::get_os_error()
{
   return m_lOsError;
}

string WinFileException::get_file_path()
{
   return m_strFileName;
}


void PASCAL WinFileException::ThrowOsError(::ca::application * papp, LONG lOsError, const char * lpszFileName /* = NULL */)
{
   if (lOsError != 0)
      vfxThrowFileException(papp, WinFileException::OsErrorToException(lOsError), lOsError, lpszFileName);
}

void PASCAL WinFileException::ThrowErrno(::ca::application * papp, int nErrno, const char * lpszFileName /* = NULL */)
{
   if (nErrno != 0)
      vfxThrowFileException(papp, WinFileException::ErrnoToException(nErrno), _doserrno, lpszFileName);
}

BOOL WinFileException::GetErrorMessage(string & str, PUINT pnHelpContext)
{
   
   if (pnHelpContext != NULL)
      *pnHelpContext = m_cause + AFX_IDP_FILE_NONE;

   string strMessage;
   string strFileName = m_strFileName;
   if(strFileName.is_empty())
      strFileName = "IDS_UNNAMED_FILE";
   strMessage.Format("file error number: %d - %s - file: %s", m_cause, get_error_message(m_lOsError), strFileName);
   str = strMessage;

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// WinFileException diagnostics

#ifdef _DEBUG
void WinFileException::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "m_cause = ";
   if (m_cause >= 0 && m_cause < _countof(rgszFileExceptionCause))
      dumpcontext << rgszFileExceptionCause[m_cause];
   else
      dumpcontext << szUnknown;
   dumpcontext << "\nm_lOsError = " << (void *)m_lOsError;

   dumpcontext << "\n";
}
#endif

/////////////////////////////////////////////////////////////////////////////
// WinFileException helpers

void CLASS_DECL_VMSWIN vfxThrowFileException(::ca::application * papp, int cause, LONG lOsError, const char * lpszFileName /* == NULL */)
{
#ifdef _DEBUG
   const char * lpsz;
   if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
      lpsz = rgszFileExceptionCause[cause];
   else
      lpsz = szUnknown;
//   TRACE3("WinFile exception: %hs, WinFile %s, App error information = %ld.\n", lpsz, (lpszFileName == NULL) ? "Unknown" : lpszFileName, lOsError);
#endif
   throw new WinFileException(papp, cause, lOsError, lpszFileName);
}

int PASCAL WinFileException::ErrnoToException(int nErrno)
{
   switch(nErrno)
   {
   case EPERM:
   case EACCES:
      return ::ex1::file_exception::accessDenied;
   case EBADF:
      return ::ex1::file_exception::invalidFile;
   case EDEADLOCK:
      return ::ex1::file_exception::sharingViolation;
   case EMFILE:
      return ::ex1::file_exception::tooManyOpenFiles;
   case ENOENT:
   case ENFILE:
      return ::ex1::file_exception::fileNotFound;
   case ENOSPC:
      return ::ex1::file_exception::diskFull;
   case EINVAL:
   case EIO:
      return ::ex1::file_exception::hardIO;
   default:
      return ::ex1::file_exception::generic;
   }
}

int PASCAL WinFileException::OsErrorToException(LONG lOsErr)
{
   // NT Error codes
   switch ((UINT)lOsErr)
   {
   case NO_ERROR:
      return ::ex1::file_exception::none;
   case ERROR_FILE_NOT_FOUND:
      return ::ex1::file_exception::fileNotFound;
   case ERROR_PATH_NOT_FOUND:
      return ::ex1::file_exception::badPath;
   case ERROR_TOO_MANY_OPEN_FILES:
      return ::ex1::file_exception::tooManyOpenFiles;
   case ERROR_ACCESS_DENIED:
      return ::ex1::file_exception::accessDenied;
   case ERROR_INVALID_HANDLE:
      return ::ex1::file_exception::fileNotFound;
   case ERROR_BAD_FORMAT:
      return ::ex1::file_exception::invalidFile;
   case ERROR_INVALID_ACCESS:
      return ::ex1::file_exception::accessDenied;
   case ERROR_INVALID_DRIVE:
      return ::ex1::file_exception::badPath;
   case ERROR_CURRENT_DIRECTORY:
      return ::ex1::file_exception::removeCurrentDir;
   case ERROR_NOT_SAME_DEVICE:
      return ::ex1::file_exception::badPath;
   case ERROR_NO_MORE_FILES:
      return ::ex1::file_exception::fileNotFound;
   case ERROR_WRITE_PROTECT:
      return ::ex1::file_exception::accessDenied;
   case ERROR_BAD_UNIT:
      return ::ex1::file_exception::hardIO;
   case ERROR_NOT_READY:
      return ::ex1::file_exception::hardIO;
   case ERROR_BAD_COMMAND:
      return ::ex1::file_exception::hardIO;
   case ERROR_CRC:
      return ::ex1::file_exception::hardIO;
   case ERROR_BAD_LENGTH:
      return ::ex1::file_exception::badSeek;
   case ERROR_SEEK:
      return ::ex1::file_exception::badSeek;
   case ERROR_NOT_DOS_DISK:
      return ::ex1::file_exception::invalidFile;
   case ERROR_SECTOR_NOT_FOUND:
      return ::ex1::file_exception::badSeek;
   case ERROR_WRITE_FAULT:
      return ::ex1::file_exception::accessDenied;
   case ERROR_READ_FAULT:
      return ::ex1::file_exception::badSeek;
   case ERROR_SHARING_VIOLATION:
      return ::ex1::file_exception::sharingViolation;
   case ERROR_LOCK_VIOLATION:
      return ::ex1::file_exception::lockViolation;
   case ERROR_WRONG_DISK:
      return ::ex1::file_exception::badPath;
   case ERROR_SHARING_BUFFER_EXCEEDED:
      return ::ex1::file_exception::tooManyOpenFiles;
   case ERROR_HANDLE_EOF:
      return ::ex1::file_exception::endOfFile;
   case ERROR_HANDLE_DISK_FULL:
      return ::ex1::file_exception::diskFull;
   case ERROR_DUP_NAME:
      return ::ex1::file_exception::badPath;
   case ERROR_BAD_NETPATH:
      return ::ex1::file_exception::badPath;
   case ERROR_NETWORK_BUSY:
      return ::ex1::file_exception::accessDenied;
   case ERROR_DEV_NOT_EXIST:
      return ::ex1::file_exception::badPath;
   case ERROR_ADAP_HDW_ERR:
      return ::ex1::file_exception::hardIO;
   case ERROR_BAD_NET_RESP:
      return ::ex1::file_exception::accessDenied;
   case ERROR_UNEXP_NET_ERR:
      return ::ex1::file_exception::hardIO;
   case ERROR_BAD_REM_ADAP:
      return ::ex1::file_exception::invalidFile;
   case ERROR_NO_SPOOL_SPACE:
      return ::ex1::file_exception::directoryFull;
   case ERROR_NETNAME_DELETED:
      return ::ex1::file_exception::accessDenied;
   case ERROR_NETWORK_ACCESS_DENIED:
      return ::ex1::file_exception::accessDenied;
   case ERROR_BAD_DEV_TYPE:
      return ::ex1::file_exception::invalidFile;
   case ERROR_BAD_NET_NAME:
      return ::ex1::file_exception::badPath;
   case ERROR_TOO_MANY_NAMES:
      return ::ex1::file_exception::tooManyOpenFiles;
   case ERROR_SHARING_PAUSED:
      return ::ex1::file_exception::badPath;
   case ERROR_REQ_NOT_ACCEP:
      return ::ex1::file_exception::accessDenied;
   case ERROR_FILE_EXISTS:
      return ::ex1::file_exception::accessDenied;
   case ERROR_CANNOT_MAKE:
      return ::ex1::file_exception::accessDenied;
   case ERROR_ALREADY_ASSIGNED:
      return ::ex1::file_exception::badPath;
   case ERROR_INVALID_PASSWORD:
      return ::ex1::file_exception::accessDenied;
   case ERROR_NET_WRITE_FAULT:
      return ::ex1::file_exception::hardIO;
   case ERROR_DISK_CHANGE:
      return ::ex1::file_exception::fileNotFound;
   case ERROR_DRIVE_LOCKED:
      return ::ex1::file_exception::lockViolation;
   case ERROR_BUFFER_OVERFLOW:
      return ::ex1::file_exception::badPath;
   case ERROR_DISK_FULL:
      return ::ex1::file_exception::diskFull;
   case ERROR_NO_MORE_SEARCH_HANDLES:
      return ::ex1::file_exception::tooManyOpenFiles;
   case ERROR_INVALID_TARGET_HANDLE:
      return ::ex1::file_exception::invalidFile;
   case ERROR_INVALID_CATEGORY:
      return ::ex1::file_exception::hardIO;
   case ERROR_INVALID_NAME:
      return ::ex1::file_exception::badPath;
   case ERROR_INVALID_LEVEL:
      return ::ex1::file_exception::badPath;
   case ERROR_NO_VOLUME_LABEL:
      return ::ex1::file_exception::badPath;
   case ERROR_NEGATIVE_SEEK:
      return ::ex1::file_exception::badSeek;
   case ERROR_SEEK_ON_DEVICE:
      return ::ex1::file_exception::badSeek;
   case ERROR_DIR_NOT_ROOT:
      return ::ex1::file_exception::badPath;
   case ERROR_DIR_NOT_EMPTY:
      return ::ex1::file_exception::removeCurrentDir;
   case ERROR_LABEL_TOO_LONG:
      return ::ex1::file_exception::badPath;
   case ERROR_BAD_PATHNAME:
      return ::ex1::file_exception::badPath;
   case ERROR_LOCK_FAILED:
      return ::ex1::file_exception::lockViolation;
   case ERROR_BUSY:
      return ::ex1::file_exception::accessDenied;
   case ERROR_INVALID_ORDINAL:
      return ::ex1::file_exception::invalidFile;
   case ERROR_ALREADY_EXISTS:
      return ::ex1::file_exception::accessDenied;
   case ERROR_INVALID_EXE_SIGNATURE:
      return ::ex1::file_exception::invalidFile;
   case ERROR_BAD_EXE_FORMAT:
      return ::ex1::file_exception::invalidFile;
   case ERROR_FILENAME_EXCED_RANGE:
      return ::ex1::file_exception::badPath;
   case ERROR_META_EXPANSION_TOO_LONG:
      return ::ex1::file_exception::badPath;
   case ERROR_DIRECTORY:
      return ::ex1::file_exception::badPath;
   case ERROR_OPERATION_ABORTED:
      return ::ex1::file_exception::hardIO;
   case ERROR_IO_INCOMPLETE:
      return ::ex1::file_exception::hardIO;
   case ERROR_IO_PENDING:
      return ::ex1::file_exception::hardIO;
   case ERROR_SWAPERROR:
      return ::ex1::file_exception::accessDenied;
   default:
      return ::ex1::file_exception::generic;
   }
}


// IMPLEMENT_DYNAMIC(WinFileException, base_exception)

/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// WinFile Status implementation

BOOL WinFile::GetStatus(::ex1::file_status& rStatus) const
{
   ASSERT_VALID(this);

   //memset(&rStatus, 0, sizeof(::ex1::file_status));

   // copy file name from cached m_strFileName
   rStatus.m_strFullName = m_strFileName;

   if (m_hFile != hFileNull)
   {
      // get time current file size
      FILETIME ftCreate, ftAccess, ftModify;
      if (!::GetFileTime((HANDLE)m_hFile, &ftCreate, &ftAccess, &ftModify))
         return FALSE;

      if ((rStatus.m_size = ::GetFileSize((HANDLE)m_hFile, NULL)) == (DWORD)-1L)
         return FALSE;

      if (m_strFileName.is_empty())
         rStatus.m_attribute = 0;
      else
      {
         DWORD dwAttribute = ::GetFileAttributesW(gen::international::utf8_to_unicode(m_strFileName));

         // don't return an error for this because previous versions of ca2 API didn't
         if (dwAttribute == 0xFFFFFFFF)
            rStatus.m_attribute = 0;
         else
         {
            rStatus.m_attribute = (BYTE) dwAttribute;
#ifdef _DEBUG
            // ca2 API BUG: m_attribute is only a BYTE wide
            if (dwAttribute & ~0xFF)
               TRACE0("Warning: WinFile::GetStatus() returns m_attribute without high-order flags.\n");
#endif
         }
      }

      // convert times as appropriate
      rStatus.m_ctime = class time(ftCreate);
      rStatus.m_atime = class time(ftAccess);
      rStatus.m_mtime = class time(ftModify);

      if (rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;

      if (rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;
   }
   return TRUE;
}


BOOL PASCAL WinFile::GetStatus(const char * lpszFileName, ::ex1::file_status& rStatus)
{
   // attempt to fully qualify path first
   wstring wstrFullName;
   wstring wstrFileName;
   wstrFileName = gen::international::utf8_to_unicode(lpszFileName);
   if (!vfxFullPath(wstrFullName.alloc(MAX_PATH * 8), wstrFileName))
   {
      rStatus.m_strFullName.Empty();
      return FALSE;
   }
   gen::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);

   WIN32_FIND_DATA findFileData;
   HANDLE hFind = FindFirstFile((LPTSTR)lpszFileName, &findFileData);
   if (hFind == INVALID_HANDLE_VALUE)
      return FALSE;
   VERIFY(FindClose(hFind));

   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   rStatus.m_attribute = (BYTE) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   // get just the low DWORD of the file size
   ASSERT(findFileData.nFileSizeHigh == 0);
   rStatus.m_size = (LONG)findFileData.nFileSizeLow;

   // convert times as appropriate
   rStatus.m_ctime = class time(findFileData.ftCreationTime);
   rStatus.m_atime = class time(findFileData.ftLastAccessTime);
   rStatus.m_mtime = class time(findFileData.ftLastWriteTime);

   if (rStatus.m_ctime.get_time() == 0)
      rStatus.m_ctime = rStatus.m_mtime;

   if (rStatus.m_atime.get_time() == 0)
      rStatus.m_atime = rStatus.m_mtime;

   return TRUE;
}


/*
UINT CLASS_DECL_VMSWIN vfxGetFileTitle(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax)
{
   ASSERT(lpszTitle == NULL ||
      fx_is_valid_address(lpszTitle, _MAX_FNAME));
   ASSERT(AfxIsValidString(lpszPathName));

   // use a temporary to avoid bugs in ::GetFileTitle when lpszTitle is NULL
   WCHAR szTemp[_MAX_PATH];
   wchar_t * lpszTemp = lpszTitle;
   if (lpszTemp == NULL)
   {
      lpszTemp = szTemp;
      nMax = _countof(szTemp);
   }
   if (::GetFileTitleW(lpszPathName, lpszTemp, (WORD)nMax) != 0)
   {
      // when ::GetFileTitle fails, use cheap imitation
      return vfxGetFileName(lpszPathName, lpszTitle, nMax);
   }
   return lpszTitle == NULL ? lstrlenW(lpszTemp)+1 : 0;
}


BOOL vfxComparePath(const wchar_t * lpszPath1, const wchar_t * lpszPath2)
{
   // use case insensitive compare as a starter
   if (lstrcmpiW(lpszPath1, lpszPath2) != 0)
      return FALSE;

   // on non-DBCS systems, we are done
   if (!GetSystemMetrics(SM_DBCSENABLED))
      return TRUE;

   // on DBCS systems, the file name may not actually be the same
   // in particular, the file system is case sensitive with respect to
   // "full width" roman characters.
   // (ie. fullwidth-R is different from fullwidth-r).
   int nLen = lstrlenW(lpszPath1);
   if (nLen != lstrlenW(lpszPath2))
      return FALSE;
   ASSERT(nLen < _MAX_PATH);

   // need to get both CT_CTYPE1 and CT_CTYPE3 for each filename
   LCID lcid = GetThreadLocale();
   WORD aCharType11[_MAX_PATH];
   VERIFY(GetStringTypeExW(lcid, CT_CTYPE1, lpszPath1, -1, aCharType11));
   WORD aCharType13[_MAX_PATH];
   VERIFY(GetStringTypeExW(lcid, CT_CTYPE3, lpszPath1, -1, aCharType13));
   WORD aCharType21[_MAX_PATH];
   VERIFY(GetStringTypeExW(lcid, CT_CTYPE1, lpszPath2, -1, aCharType21));
#ifdef _DEBUG
   WORD aCharType23[_MAX_PATH];
   VERIFY(GetStringTypeExW(lcid, CT_CTYPE3, lpszPath2, -1, aCharType23));
#endif

   // for every C3_FULLWIDTH character, make sure it has same C1 value
   int i = 0;
   for (const wchar_t * lpsz = lpszPath1; *lpsz != 0; lpsz = _wcsinc(lpsz))
   {
      // check for C3_FULLWIDTH characters only
      if (aCharType13[i] & C3_FULLWIDTH)
      {
#ifdef _DEBUG
         ASSERT(aCharType23[i] & C3_FULLWIDTH); // should always match!
#endif

         // if CT_CTYPE1 is different then file system considers these
         // file names different.
         if (aCharType11[i] != aCharType21[i])
            return FALSE;
      }
      ++i; // look at next character type
   }
   return TRUE; // otherwise file name is truly the same
}
*/

/*
void PASCAL WinFile::SetStatus(const char * lpszFileName, const ::ex1::file_status& status)
{
   DWORD wAttr;
   FILETIME creationTime;
   FILETIME lastAccessTime;
   FILETIME lastWriteTime;
   LPFILETIME lpCreationTime = NULL;
   LPFILETIME lpLastAccessTime = NULL;
   LPFILETIME lpLastWriteTime = NULL;

   if ((wAttr = GetFileAttributes((LPTSTR)lpszFileName)) == (DWORD)-1L)
      WinFileException::ThrowOsError(get_app(), (LONG)GetLastError());

   if ((DWORD)status.m_attribute != wAttr && (wAttr & readOnly))
   {
      // Set file attribute, only if currently readonly.
      // This way we will be able to modify the time assuming the
      // caller changed the file from readonly.

      if (!SetFileAttributes((LPTSTR)lpszFileName, (DWORD)status.m_attribute))
         WinFileException::ThrowOsError(get_app(), (LONG)GetLastError());
   }

   // last modification time
   if (status.m_mtime.get_time() != 0)
   {
      AfxTimeToFileTime(status.m_mtime, &lastWriteTime);
      lpLastWriteTime = &lastWriteTime;

      // last access time
      if (status.m_atime.get_time() != 0)
      {
         AfxTimeToFileTime(status.m_atime, &lastAccessTime);
         lpLastAccessTime = &lastAccessTime;
      }

      // create time
      if (status.m_ctime.get_time() != 0)
      {
         AfxTimeToFileTime(status.m_ctime, &creationTime);
         lpCreationTime = &creationTime;
      }

      HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ|GENERIC_WRITE,
         FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
         NULL);

      if (hFile == INVALID_HANDLE_VALUE)
         WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());

      if (!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
         WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());

      if (!::CloseHandle(hFile))
         WinFileException::ThrowOsError(get_app(), (LONG)::GetLastError());
   }

   if ((DWORD)status.m_attribute != wAttr && !(wAttr & readOnly))
   {
      if (!SetFileAttributes((LPTSTR)lpszFileName, (DWORD)status.m_attribute))
         WinFileException::ThrowOsError(get_app(), (LONG)GetLastError());
   }
}
*/

bool WinFile::IsOpened()
{
   return m_hFile != hFileNull;
}


void WinFile::SetFilePath(const char * lpszNewName)
{
   ASSERT_VALID(this);
   ASSERT(AfxIsValidString(lpszNewName));
   m_strFileName = lpszNewName;
}


