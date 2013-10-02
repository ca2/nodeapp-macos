#include "framework.h"


#include <fcntl.h>

#ifdef LINUX
#include <dlfcn.h>
#include <link.h>
#include <ctype.h>
#elif defined(MACOS)
#include <dlfcn.h>
#include <sys/stat.h>
#endif

__STATIC inline bool IsDirSep(WCHAR ch)
{
   
   return (ch == '\\' || ch == '/');
   
}


namespace mac
{
   
   
   file::file(base_application * papp) :
   element(papp)
   {
      
      m_iFile = (UINT) hFileNull;
      
      m_bCloseOnDelete = TRUE;
      
   }
   
   file::file(base_application * papp, int32_t hFile) :
   element(papp)
   {
      
      m_iFile = hFile;
      
      m_bCloseOnDelete = TRUE;
      
   }
   
   file::file(base_application * papp, const char * lpszFileName, UINT nOpenFlags) :
   element(papp)
   {
      
      ASSERT(__is_valid_string(lpszFileName));
      
      if(!open(lpszFileName, nOpenFlags))
         throw ::file::exception(papp, ::file::exception::none, -1, lpszFileName);
      
   }
   
   file::~file()
   {
      
      if (m_iFile != (UINT)hFileNull && m_bCloseOnDelete)
         close();
      
   }
   
   sp(::file::stream_buffer) file::Duplicate() const
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      int32_t iNew = dup(m_iFile);
      
      if(iNew == -1)
         return NULL;
      
      file* pFile = new file(get_app(), iNew);
      pFile->m_iFile = (UINT)iNew;
      ASSERT(pFile->m_iFile != (UINT)hFileNull);
      pFile->m_bCloseOnDelete = m_bCloseOnDelete;
      return pFile;
   }
   
   bool file::open(const char * lpszFileName, UINT nOpenFlags)
   {
      
      if (m_iFile != (UINT)hFileNull)
         close();
      
      ASSERT_VALID(this);
      ASSERT(__is_valid_string(lpszFileName));
      ASSERT((nOpenFlags & ::file::type_text) == 0);   // text mode not supported
      
      // file objects are always binary and CreateFile does not need flag
      nOpenFlags &= ~(UINT)::file::type_binary;
      
      
      if(nOpenFlags & ::file::defer_create_directory)
      {
         System.dir_mk(System.dir_name(lpszFileName));
      }
      
      m_bCloseOnDelete = FALSE;
      m_iFile = (UINT)hFileNull;
      m_strFileName.Empty();
      
      m_strFileName     = lpszFileName;
      m_wstrFileName    = ::str::international::utf8_to_unicode(m_strFileName);
      
      ASSERT(sizeof(HANDLE) == sizeof(uint_ptr));
      ASSERT(::file::share_compat == 0);
      
      // ::collection::map read/write mode
      ASSERT((::file::mode_read|::file::mode_write|::file::mode_read_write) == 3);
      DWORD dwFlags =  0;
      switch (nOpenFlags & 3)
      {
         case ::file::mode_read:
            dwFlags |=  O_RDONLY;
            break;
         case ::file::mode_write:
            dwFlags |=  O_WRONLY ;
            break;
         case ::file::mode_read_write:
            dwFlags |=  O_RDWR;
            break;
         default:
            dwFlags |=  O_RDONLY;
            break;
      }
      
      // ::collection::map share mode
//      DWORD dwShareMode = 0;
      switch (nOpenFlags & 0x70)    // ::collection::map compatibility mode to exclusive
      {
         default:
            ASSERT(FALSE);  // invalid share mode?
         case ::file::share_compat:
         case ::file::share_exclusive:
            //dwShareMode = 0;
            break;
         case ::file::share_deny_write:
            //dwFlags |= O_SHLOCK;
            break;
         case ::file::share_deny_read:
            //         dwFlags |= O_EXLOCK;
            break;
         case ::file::share_deny_none:
            //dwFlags = FILE_SHARE_WRITE|FILE_SHARE_READ;
            break;
      }
      
      if (nOpenFlags & ::file::mode_create)
      {
         dwFlags |= O_CREAT;
         if(!(nOpenFlags & ::file::mode_no_truncate))
            dwFlags |= O_TRUNC;
      }
      
      
      DWORD dwPermission = 0;
      
      
      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;
      
      
      // attempt file creation
      //HANDLE hFile = shell::CreateFile(::str::international::utf8_to_unicode(m_strFileName), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
      int32_t hFile = ::open(m_strFileName, dwFlags, dwPermission); //::open(m_strFileName, dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
      if(hFile == -1)
      {
         DWORD dwLastError = ::GetLastError();
         
         if(dwLastError != ERROR_FILE_NOT_FOUND && dwLastError != ERROR_PATH_NOT_FOUND)
         {
            /*         if (pException != NULL)
             {
             pException->create(get_app());
             ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
             if(pfe != NULL)
             {
             pfe->m_lOsError = dwLastError;
             pfe->m_cause = ::win::file_exception::OsErrorToException(pfe->m_lOsError);
             pfe->m_strFileName = lpszFileName;
             }
             return FALSE;
             }
             else
             {*/
            
            
            vfxThrowFileException(get_app(), ::mac::file_exception::OsErrorToException(dwLastError), dwLastError, m_strFileName);
            
            //}
            
         }
         
         /*try
          {
          m_papp->m_psystem->m_spfilesystem.m_p->FullPath(m_wstrFileName, m_wstrFileName);
          }
          catch(...)
          {
          return FALSE;
          }
          
          m_strFileName = ::str::international::unicode_to_utf8(m_wstrFileName);
          
          hFile = ::open(m_strFileName, nOpenFlags);*/
         
         if (hFile == -1)
         {
            /*if (pException != NULL)
             {
             pException->create(get_app());
             ::file::exception * pfe = dynamic_cast < ::file::exception * > (pException->m_p);
             if(pfe != NULL)
             {
             pfe->m_lOsError = ::GetLastError();
             pfe->m_cause = ::win::file_exception::OsErrorToException(pfe->m_lOsError);
             pfe->m_strFileName = lpszFileName;
             }
             return FALSE;
             }
             else
             {*/
            
            
            DWORD dwLastError = ::GetLastError();
            vfxThrowFileException(get_app(), ::mac::file_exception::OsErrorToException(dwLastError), dwLastError, m_strFileName);
            
            
            //}
            
         }
         
      }
      
      m_iFile = (int32_t)hFile;
      
      m_bCloseOnDelete = TRUE;
      
      return TRUE;
   }
   
   ::primitive::memory_size file::read(void * lpBuf, ::primitive::memory_size nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"
      
      ASSERT(lpBuf != NULL);
      ASSERT(__is_valid_address(lpBuf, nCount));
      
      ::primitive::memory_position pos = 0;
      ::primitive::memory_size sizeRead = 0;
      ::primitive::memory_size readNow;
      while(nCount > 0)
      {
         readNow = (size_t) min(0x7fffffff, nCount);
         size_t iRead = ::read(m_iFile, &((byte *)lpBuf)[pos], readNow);
         if(iRead == ::numeric_info::get_allset_value < size_t >())
         {
            int32_t iError = errno;
            if(iError == EAGAIN)
            {
               
            }
            ::mac::file_exception::ThrowOsError(get_app(), errno);
         }
         else if(iRead == 0)
         {
            break;
         }
         
         nCount -= iRead;
         pos += iRead;
         sizeRead += iRead;
      }
      
      return sizeRead;
   }
   
   void file::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      if (nCount == 0)
         return;     // avoid Win32 "null-write" option
      
      ASSERT(lpBuf != NULL);
      ASSERT(__is_valid_address(lpBuf, nCount, FALSE));
      
      ::primitive::memory_position pos = 0;
      while(nCount > 0)
      {
         size_t iWrite = ::write(m_iFile, &((const byte *)lpBuf)[pos], (size_t) min(0x7fffffff, nCount));
         if(iWrite == ::numeric_info::get_allset_value < size_t >())
            ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError(), m_strFileName);
         nCount -= iWrite;
         pos += iWrite;
      }
      
      // Win32s will not return an error all the time (usually DISK_FULL)
      //if (iWrite != nCount)
      //vfxThrowFileException(get_app(), ::file::exception::diskFull, -1, m_strFileName);
   }
   
   
   file_position file::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      
      if(m_iFile == (UINT)hFileNull)
         ::mac::file_exception::ThrowOsError(get_app(), (LONG)0);
      
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == SEEK_SET && ::file::seek_end == SEEK_END && ::file::seek_current == SEEK_CUR);
      
      LONG lLoOffset = lOff & 0xffffffff;
      //LONG lHiOffset = (lOff >> 32) & 0xffffffff;
      
      file_position posNew = ::lseek(m_iFile, lLoOffset, (DWORD)nFrom);
      //      posNew |= ((file_position) lHiOffset) << 32;
      if(posNew  == (file_position)-1)
         ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
      
      return posNew;
   }
   
   file_position file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      LONG lLoOffset = 0;
      //      LONG lHiOffset = 0;
      
      file_position pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);
      //    pos |= ((file_position)lHiOffset) << 32;
      if(pos  == (file_position)-1)
         ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
      
      return pos;
   }
   
   void file::Flush()
   {
      
      /*      ::open
       ::read
       ::write
       
       access the system directly no buffering : direct I/O - efficient for large writes - innefficient for lots of single byte writes
       
       */
      
      /*ASSERT_VALID(this);
       
         if (m_iFile == (UINT)hFileNull)
       return;
       
       if (!::FlushFileBuffers((HANDLE)m_iFile))
       ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());*/
   }
   
   void file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      bool bError = FALSE;
      if (m_iFile != (UINT)hFileNull)
         bError = !::close(m_iFile);
      
      m_iFile = (UINT) hFileNull;
      m_bCloseOnDelete = FALSE;
      m_strFileName.Empty();
      
      if (bError)
         ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
   }
   
   void file::Abort()
   {
      ASSERT_VALID(this);
      if (m_iFile != (UINT)hFileNull)
      {
         // close but ignore errors
         ::close(m_iFile);
         m_iFile = (UINT)hFileNull;
      }
      m_strFileName.Empty();
   }
   
   void file::LockRange(file_position dwPos, file_size dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      /*if (!::LockFile((HANDLE)m_iFile, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
       ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());*/
   }
   
   void file::UnlockRange(file_position dwPos, file_size dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      /*      if (!::UnlockFile((HANDLE)m_iFile,  LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
       ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());*/
   }
   
   void file::set_length(file_size dwNewLen)
   {
      ASSERT_VALID(this);
      ASSERT(m_iFile != (UINT)hFileNull);
      
      seek((LONG)dwNewLen, (::file::e_seek)::file::seek_begin);
      
      if (!::ftruncate(m_iFile, dwNewLen))
         ::mac::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
   }
   
   file_size file::get_length() const
   {
      ASSERT_VALID(this);
      
      file_position dwLen, dwCur;
      
      // seek is a non const operation
      file* pFile = (file*)this;
      dwCur = pFile->seek(0L, ::file::seek_current);
      dwLen = pFile->seek_to_end();
      VERIFY(dwCur == (uint64_t)pFile->seek((file_offset) dwCur, ::file::seek_begin));
      
      return (file_size) dwLen;
   }
   
   // file does not support direct buffering (CMemFile does)
   uint64_t file::GetBufferPtr(UINT nCommand, uint64_t /*nCount*/,
                               void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   {
      ASSERT(nCommand == bufferCheck);
//      UNUSED(nCommand);    // not used in retail build
      
      return 0;   // no support
   }
   
   /*
    void PASCAL file::Rename(const char * lpszOldName, const char * lpszNewName)
    {
    if (!::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
    }
    
    void PASCAL file::remove(const char * lpszFileName)
    {
    if (!::DeleteFile((LPTSTR)lpszFileName))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
    }
    */
   
   
   
   
   
   /////////////////////////////////////////////////////////////////////////////
   // file diagnostics
   
   
   void file::assert_valid() const
   {
      ::object::assert_valid();
      // we permit the descriptor m_iFile to be any value for derived classes
   }
   
   void file::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);
      
      dumpcontext << "with handle " << (UINT)m_iFile;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }
   
   
   
   
   /////////////////////////////////////////////////////////////////////////////
   // FileException helpers
   
#ifdef DEBUG
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
   
   
   /*void CLASS_DECL_mac vfxThrowFileException(int32_t cause, LONG lOsError,
    //   const char * lpszFileName  == NULL */
   /*{
    #ifdef DEBUG
    const char * lpsz;
    if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
    lpsz = rgszFileExceptionCause[cause];
    else
    lpsz = szUnknown;
    TRACE3("file exception: %hs, file %W, App error information = %ld.\n",
    lpsz, (lpszFileName == NULL) ? L"Unknown" : lpszFileName, lOsError);
    #endif
    THROW(new FileException(cause, lOsError, lpszFileName));
    }*/
   
   /* Error Codes */
   
   
   /////////////////////////////////////////////////////////////////////////////
   // file name handlers
   
   string file::GetFileName() const
   {
      ASSERT_VALID(this);
      
      ::file::file_status status;
      GetStatus(status);
      return System.file().name_(status.m_strFullName);
   }
   
   string file::GetFileTitle() const
   {
      ASSERT_VALID(this);
      
      ::file::file_status status;
      GetStatus(status);
      return System.file().title_(status.m_strFullName);
   }
   
   string file::GetFilePath() const
   {
      ASSERT_VALID(this);
      
      ::file::file_status status;
      GetStatus(status);
      return status.m_strFullName;
   }
   
   
   
   
   /////////////////////////////////////////////////////////////////////////////
   // FileException
   
   
   namespace file_exception
   {
   
   void ThrowOsError(base_application * papp, LONG lOsError, const char * lpszFileName /* = NULL */)
   {
      if (lOsError != 0)
         vfxThrowFileException(papp, ::mac::file_exception::OsErrorToException(lOsError), lOsError, lpszFileName);
   }
   
   void ThrowErrno(base_application * papp, int32_t nErrno, const char * lpszFileName /* = NULL */)
   {
      if (nErrno != 0)
         vfxThrowFileException(papp, ::mac::file_exception::ErrnoToException(nErrno), errno, lpszFileName);
   }
   
   
   
   int32_t OsErrorToException(LONG lOsErr)
   {
      // NT Error codes
      switch ((UINT)lOsErr)
      {
         case NO_ERROR:
            return ::file::exception::none;
         case ERROR_FILE_NOT_FOUND:
            return ::file::exception::fileNotFound;
         case ERROR_PATH_NOT_FOUND:
            return ::file::exception::badPath;
         case ERROR_TOO_MANY_OPEN_FILES:
            return ::file::exception::tooManyOpenFiles;
         case ERROR_ACCESS_DENIED:
            return ::file::exception::accessDenied;
         case ERROR_INVALID_HANDLE:
            return ::file::exception::fileNotFound;
         case ERROR_BAD_FORMAT:
            return ::file::exception::invalidFile;
         case ERROR_INVALID_ACCESS:
            return ::file::exception::accessDenied;
         case ERROR_INVALID_DRIVE:
            return ::file::exception::badPath;
         case ERROR_CURRENT_DIRECTORY:
            return ::file::exception::removeCurrentDir;
         case ERROR_NOT_SAME_DEVICE:
            return ::file::exception::badPath;
         case ERROR_NO_MORE_FILES:
            return ::file::exception::fileNotFound;
         case ERROR_WRITE_PROTECT:
            return ::file::exception::accessDenied;
         case ERROR_BAD_UNIT:
            return ::file::exception::hardIO;
         case ERROR_NOT_READY:
            return ::file::exception::hardIO;
         case ERROR_BAD_COMMAND:
            return ::file::exception::hardIO;
         case ERROR_CRC:
            return ::file::exception::hardIO;
         case ERROR_BAD_LENGTH:
            return ::file::exception::badSeek;
         case ERROR_SEEK:
            return ::file::exception::badSeek;
         case ERROR_NOT_DOS_DISK:
            return ::file::exception::invalidFile;
         case ERROR_SECTOR_NOT_FOUND:
            return ::file::exception::badSeek;
         case ERROR_WRITE_FAULT:
            return ::file::exception::accessDenied;
         case ERROR_READ_FAULT:
            return ::file::exception::badSeek;
         case ERROR_SHARING_VIOLATION:
            return ::file::exception::sharingViolation;
         case ERROR_LOCK_VIOLATION:
            return ::file::exception::lockViolation;
         case ERROR_WRONG_DISK:
            return ::file::exception::badPath;
         case ERROR_SHARING_BUFFER_EXCEEDED:
            return ::file::exception::tooManyOpenFiles;
         case ERROR_HANDLE_EOF:
            return ::file::exception::endOfFile;
         case ERROR_HANDLE_DISK_FULL:
            return ::file::exception::diskFull;
         case ERROR_DUP_NAME:
            return ::file::exception::badPath;
         case ERROR_BAD_NETPATH:
            return ::file::exception::badPath;
         case ERROR_NETWORK_BUSY:
            return ::file::exception::accessDenied;
         case ERROR_DEV_NOT_EXIST:
            return ::file::exception::badPath;
         case ERROR_ADAP_HDW_ERR:
            return ::file::exception::hardIO;
         case ERROR_BAD_NET_RESP:
            return ::file::exception::accessDenied;
         case ERROR_UNEXP_NET_ERR:
            return ::file::exception::hardIO;
         case ERROR_BAD_REM_ADAP:
            return ::file::exception::invalidFile;
         case ERROR_NO_SPOOL_SPACE:
            return ::file::exception::directoryFull;
         case ERROR_NETNAME_DELETED:
            return ::file::exception::accessDenied;
         case ERROR_NETWORK_ACCESS_DENIED:
            return ::file::exception::accessDenied;
         case ERROR_BAD_DEV_TYPE:
            return ::file::exception::invalidFile;
         case ERROR_BAD_NET_NAME:
            return ::file::exception::badPath;
         case ERROR_TOO_MANY_NAMES:
            return ::file::exception::tooManyOpenFiles;
         case ERROR_SHARING_PAUSED:
            return ::file::exception::badPath;
         case ERROR_REQ_NOT_ACCEP:
            return ::file::exception::accessDenied;
         case ERROR_FILE_EXISTS:
            return ::file::exception::accessDenied;
         case ERROR_CANNOT_MAKE:
            return ::file::exception::accessDenied;
         case ERROR_ALREADY_ASSIGNED:
            return ::file::exception::badPath;
         case ERROR_INVALID_PASSWORD:
            return ::file::exception::accessDenied;
         case ERROR_NET_WRITE_FAULT:
            return ::file::exception::hardIO;
         case ERROR_DISK_CHANGE:
            return ::file::exception::fileNotFound;
         case ERROR_DRIVE_LOCKED:
            return ::file::exception::lockViolation;
         case ERROR_BUFFER_OVERFLOW:
            return ::file::exception::badPath;
         case ERROR_DISK_FULL:
            return ::file::exception::diskFull;
         case ERROR_NO_MORE_SEARCH_HANDLES:
            return ::file::exception::tooManyOpenFiles;
         case ERROR_INVALID_TARGET_HANDLE:
            return ::file::exception::invalidFile;
         case ERROR_INVALID_CATEGORY:
            return ::file::exception::hardIO;
         case ERROR_INVALID_NAME:
            return ::file::exception::badPath;
         case ERROR_INVALID_LEVEL:
            return ::file::exception::badPath;
         case ERROR_NO_VOLUME_LABEL:
            return ::file::exception::badPath;
         case ERROR_NEGATIVE_SEEK:
            return ::file::exception::badSeek;
         case ERROR_SEEK_ON_DEVICE:
            return ::file::exception::badSeek;
         case ERROR_DIR_NOT_ROOT:
            return ::file::exception::badPath;
         case ERROR_DIR_NOT_EMPTY:
            return ::file::exception::removeCurrentDir;
         case ERROR_LABEL_TOO_LONG:
            return ::file::exception::badPath;
         case ERROR_BAD_PATHNAME:
            return ::file::exception::badPath;
         case ERROR_LOCK_FAILED:
            return ::file::exception::lockViolation;
         case ERROR_BUSY:
            return ::file::exception::accessDenied;
         case ERROR_INVALID_ORDINAL:
            return ::file::exception::invalidFile;
         case ERROR_ALREADY_EXISTS:
            return ::file::exception::accessDenied;
         case ERROR_INVALID_EXE_SIGNATURE:
            return ::file::exception::invalidFile;
         case ERROR_BAD_EXE_FORMAT:
            return ::file::exception::invalidFile;
         case ERROR_FILENAME_EXCED_RANGE:
            return ::file::exception::badPath;
         case ERROR_META_EXPANSION_TOO_LONG:
            return ::file::exception::badPath;
         case ERROR_DIRECTORY:
            return ::file::exception::badPath;
         case ERROR_OPERATION_ABORTED:
            return ::file::exception::hardIO;
         case ERROR_IO_INCOMPLETE:
            return ::file::exception::hardIO;
         case ERROR_IO_PENDING:
            return ::file::exception::hardIO;
         case ERROR_SWAPERROR:
            return ::file::exception::accessDenied;
         default:
            return ::file::exception::type_generic;
      }
   }
      
         } //      namespace file_exception
   
   
   // IMPLEMENT_DYNAMIC(WinFileException, ::exception::base)
   
   /////////////////////////////////////////////////////////////////////////////
   
   
   
   
   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation
   
   bool file::GetStatus(::file::file_status& rStatus) const
   {
      ASSERT_VALID(this);
      
      //memset(&rStatus, 0, sizeof(::ca2::file_status));
      
      // copy file name from cached m_strFileName
      rStatus.m_strFullName = m_strFileName;
      
      if (m_iFile != hFileNull)
      {
         struct ::stat st;
         if(fstat(m_iFile, &st) == -1)
            return FALSE;
         // get time ::ca2::seek_current file size
         /*FILETIME ftCreate, ftAccess, ftModify;
          if (!::GetFileTime((HANDLE)m_iFile, &ftCreate, &ftAccess, &ftModify))
          return FALSE;*/
         
         rStatus.m_size = st.st_size;
         
         //if ((rStatus.m_size = ::GetFileSize((HANDLE)m_iFile, NULL)) == (DWORD)-1L)
         // return FALSE;
         
         
         //if (m_strFileName.is_empty())
         // throw todo(get_app());
         rStatus.m_attribute = 0;
         /*         else
          {
          DWORD dwAttribute = ::GetFileAttributesW(::str::international::utf8_to_unicode(m_strFileName));
          
          // don't return an error for this because previous versions of ca2 API didn't
          if (dwAttribute == 0xFFFFFFFF)
          rStatus.m_attribute = 0;
          else
          {
          rStatus.m_attribute = (BYTE) dwAttribute;
          #ifdef DEBUG
          // ca2 API BUG: m_attribute is only a BYTE wide
          if (dwAttribute & ~0xFF)
          TRACE0("Warning: file::GetStatus() returns m_attribute without high-order flags.\n");
          #endif
          }
          }*/
         
         // convert times as appropriate
         //rStatus.m_ctime = ::datetime::time(ftCreate);
         //rStatus.m_atime = ::datetime::time(ftAccess);
         //rStatus.m_mtime = ::datetime::time(ftModify);
         rStatus.m_ctime = ::datetime::time(st.st_mtime);
         rStatus.m_atime = ::datetime::time(st.st_atime);
         rStatus.m_mtime = ::datetime::time(st.st_ctime);
         
         if (rStatus.m_ctime.get_time() == 0)
            rStatus.m_ctime = rStatus.m_mtime;
         
         if (rStatus.m_atime.get_time() == 0)
            rStatus.m_atime = rStatus.m_mtime;
      }
      return TRUE;
   }
   
   
   bool PASCAL file::GetStatus(const char * lpszFileName, ::file::file_status& rStatus)
   {
      // attempt to fully qualify path first
      wstring wstrFullName;
      wstring wstrFileName;
      wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
//      if (!vfxFullPath(wstrFullName, wstrFileName))
  //    {
    //     rStatus.m_strFullName.Empty();
      //   return FALSE;
      //}
      
      wstrFullName = wstrFileName;
      
      ::str::international::unicode_to_utf8(rStatus.m_strFullName, wstrFullName);
      
      struct ::stat st;
      if(stat(lpszFileName, &st) == -1)
         return false;
      //if (hFind == INVALID_HANDLE_VALUE)
      // return FALSE;
      //VERIFY(FindClose(hFind));
      
      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      //rStatus.m_attribute = (BYTE) (findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);
      
      rStatus.m_attribute = 0;
      
      // get just the low DWORD of the file size
      //ASSERT(findFileData.nFileSizeHigh == 0);
      //rStatus.m_size = (LONG)findFileData.nFileSizeLow;
      
      rStatus.m_size = st.st_size;
      
      // convert times as appropriate
      /*rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
       rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
       rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);*/
      rStatus.m_ctime = ::datetime::time(st.st_mtime);
      rStatus.m_atime = ::datetime::time(st.st_atime);
      rStatus.m_mtime = ::datetime::time(st.st_ctime);
      
      if (rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;
      
      if (rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;
      
      return TRUE;
   }
      

   
   /*
    UINT CLASS_DECL_mac vfxGetFileTitle(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax)
    {
    ASSERT(lpszTitle == NULL ||
    __is_valid_address(lpszTitle, _MAX_FNAME));
    ASSERT(__is_valid_string(lpszPathName));
    
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
    
    
    bool vfxComparePath(const wchar_t * lpszPath1, const wchar_t * lpszPath2)
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
    int32_t nLen = lstrlenW(lpszPath1);
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
    #ifdef DEBUG
    WORD aCharType23[_MAX_PATH];
    VERIFY(GetStringTypeExW(lcid, CT_CTYPE3, lpszPath2, -1, aCharType23));
    #endif
    
    // for every C3_FULLWIDTH character, make sure it has same C1 value
    int32_t i = 0;
    for (const wchar_t * lpsz = lpszPath1; *lpsz != 0; lpsz = _wcsinc(lpsz))
    {
    // check for C3_FULLWIDTH characters only
    if (aCharType13[i] & C3_FULLWIDTH)
    {
    #ifdef DEBUG
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
    void PASCAL file::SetStatus(const char * lpszFileName, const ::ca2::file_status& status)
    {
    DWORD wAttr;
    FILETIME creationTime;
    FILETIME lastAccessTime;
    FILETIME lastWriteTime;
    LPFILETIME lpCreationTime = NULL;
    LPFILETIME lpLastAccessTime = NULL;
    LPFILETIME lpLastWriteTime = NULL;
    
    if ((wAttr = GetFileAttributes((LPTSTR)lpszFileName)) == (DWORD)-1L)
    ::win::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());
    
    if ((DWORD)status.m_attribute != wAttr && (wAttr & readOnly))
    {
    // Set file attribute, only if currently readonly.
    // This way we will be able to modify the time assuming the
    // caller changed the file from readonly.
    
    if (!SetFileAttributes((LPTSTR)lpszFileName, (DWORD)status.m_attribute))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());
    }
    
    // last modification time
    if (status.m_mtime.get_time() != 0)
    {
    ::ca2::TimeToFileTime(status.m_mtime, &lastWriteTime);
    lpLastWriteTime = &lastWriteTime;
    
    // last access time
    if (status.m_atime.get_time() != 0)
    {
    ::ca2::TimeToFileTime(status.m_atime, &lastAccessTime);
    lpLastAccessTime = &lastAccessTime;
    }
    
    // create time
    if (status.m_ctime.get_time() != 0)
    {
    ::ca2::TimeToFileTime(status.m_ctime, &creationTime);
    lpCreationTime = &creationTime;
    }
    
    HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ|GENERIC_WRITE,
    FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
    NULL);
    
    if (hFile == INVALID_HANDLE_VALUE)
    ::win::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
    
    if (!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
    
    if (!::CloseHandle(hFile))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());
    }
    
    if ((DWORD)status.m_attribute != wAttr && !(wAttr & readOnly))
    {
    if (!SetFileAttributes((LPTSTR)lpszFileName, (DWORD)status.m_attribute))
    ::win::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());
    }
    }
    */
   
   bool file::IsOpened()
   {
      return m_iFile != hFileNull;
   }
   
   
   void file::SetFilePath(const char * lpszNewName)
   {
      ASSERT_VALID(this);
      ASSERT(__is_valid_string(lpszNewName));
      m_strFileName = lpszNewName;
   }
   
   uint64_t file::ReadHuge(void * lpBuffer, uint64_t dwCount)
   {
      
      return  read(lpBuffer, dwCount);
      
   }
   
   void file::WriteHuge(const void * lpBuffer, uint64_t dwCount)
   {
      
      write(lpBuffer, dwCount);
      
   }
   
   
   
} // namespace win




#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)




// turn a file, relative path or other into an absolute path
bool CLASS_DECL_mac vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
// lpszPathOut = buffer of _MAX_PATH
// lpszFileIn = file, relative path or absolute path
// (both in ANSI character set)
{
   
   
   wstrFullPath = wstrPath;
   
   
   return true;
   
   /*
    
    strsize dwAllocLen = wstrPath.get_length() + _MAX_PATH;
    
    wstrFullPath.alloc(dwAllocLen);
    
    // first, fully qualify the path name
    wchar_t * lpszFilePart;
    
    strsize dwLen = GetFullPathNameW(wstrPath, (DWORD) dwAllocLen, wstrFullPath, &lpszFilePart);
    
    if(dwLen == 0)
    {
    #ifdef DEBUG
    //      if (lpszFileIn[0] != '\0')
    //       TRACE1("Warning: could not parse the path '%s'.\n", lpszFileIn);
    #endif
    wstrFullPath = wstrPath; // take it literally
    return FALSE;
    }
    else if(dwLen > dwAllocLen)
    {
    
    dwAllocLen = dwLen + _MAX_PATH;
    
    dwLen = GetFullPathNameW(wstrPath, (DWORD) dwAllocLen, wstrFullPath, &lpszFilePart);
    
    if(dwLen == 0 || dwLen > dwAllocLen)
    {
    #ifdef DEBUG
    //      if (lpszFileIn[0] != '\0')
    //       TRACE1("Warning: could not parse the path '%s'.\n", lpszFileIn);
    #endif
    wstrFullPath = wstrPath; // take it literally
    return FALSE;
    }
    
    }
    
    wstring wstrRoot;
    // determine the root name of the volume
    vfxGetRoot(wstrRoot, wstrFullPath);
    
    // get file system information for the volume
    DWORD dwFlags, dwDummy;
    if (!GetVolumeInformationW(wstrRoot, NULL, 0, NULL, &dwDummy, &dwFlags, NULL, 0))
    {
    //      TRACE1("Warning: could not get volume information '%s'.\n", strRoot);
    return FALSE;   // preserving case may not be correct
    }
    
    // not all characters have complete uppercase/lowercase
    if (!(dwFlags & FS_CASE_IS_PRESERVED))
    CharUpperW(wstrFullPath);
    
    // assume non-UNICODE file systems, use OEM character set
    if (!(dwFlags & FS_UNICODE_STORED_ON_DISK))
    {
    WIN32_FIND_DATAW data;
    HANDLE h = FindFirstFileW(wstrPath, &data);
    if (h != INVALID_HANDLE_VALUE)
    {
    FindClose(h);
    int32_t iLenFileName = lstrlenW(data.cFileName);
    if(iLenFileName >=  MAX_PATH)
    {
    wstring wstrBackup = wstrFullPath;
    strsize iFilePart = lpszFilePart - wstrFullPath;
    wstrFullPath.alloc(iFilePart + iLenFileName + 32); // arrange more space with more 32 extra wchars
    lstrcpynW(wstrFullPath, wstrBackup, (int32_t) iFilePart);
    lpszFilePart = (wchar_t *) wstrFullPath + iFilePart;
    }
    lstrcpyW(lpszFilePart, data.cFileName);
    wstrFullPath.release_buffer();
    }
    }
    return TRUE;*/
}

/*void CLASS_DECL_mac __get_root_path(const char * lpszPath, string & strRoot)
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

/*bool CLASS_DECL_mac ::ca2::ComparePath(const char * lpszPath1, const char * lpszPath2)
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
 int32_t nLen = lstrlen(lpszPath1);
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
 #ifdef DEBUG
 WORD aCharType23[_MAX_PATH];
 VERIFY(GetStringTypeEx(lcid, CT_CTYPE3, lpszPath2, -1, aCharType23));
 #endif
 
 // for every C3_FULLWIDTH character, make sure it has same C1 value
 int32_t i = 0;
 for (const char * lpsz = lpszPath1; *lpsz != 0; lpsz = _tcsinc(lpsz))
 {
 // check for C3_FULLWIDTH characters only
 if (aCharType13[i] & C3_FULLWIDTH)
 {
 #ifdef DEBUG
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

/*UINT CLASS_DECL_mac __get_file_title(const char * lpszPathName, LPTSTR lpszTitle, UINT nMax)
 {
 ASSERT(lpszTitle == NULL ||
 __is_valid_address(lpszTitle, _MAX_FNAME));
 ASSERT(__is_valid_string(lpszPathName));
 
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
 return ::ca2::GetFileName(lpszPathName, lpszTitle, nMax);
 }
 return lpszTitle == NULL ? lstrlen(lpszTemp)+1 : 0;
 }*/

CLASS_DECL_mac void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{
   throw todo(::get_thread_app());
   //link_map * plm;
   
   //dlinfo(hInst, RTLD_DI_LINKMAP, &plm);
   
   //strShortName = plm->l_name;
   
   
   /*   WCHAR szLongPathName[_MAX_PATH];
    wstring wstrShortName;
    ::GetModuleFileNameW(hInst, szLongPathName, _MAX_PATH);
    if(::GetShortPathNameW(szLongPathName, wstrShortName.alloc(_MAX_PATH * 4), _MAX_PATH * 4) == 0)
    {
    // rare failure case (especially on not-so-modern file systems)
    ::str::international::unicode_to_utf8(strShortName, szLongPathName);
    }
    else
    {
    wstrShortName.release_buffer();
    ::str::international::unicode_to_utf8(strShortName, wstrShortName);
    }*/
}




CLASS_DECL_mac string vfxStringFromCLSID(REFCLSID rclsid)
{
   CHAR szCLSID[256];
   sprintf(szCLSID, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
           rclsid.Data1, rclsid.Data2, rclsid.Data3,
           rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3],
           rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);
   return szCLSID;
}

/*
 bool CLASS_DECL_mac vfxGetInProcServer(const char * lpszCLSID, string & str)
 {
 HKEY hKey = NULL;
 bool b = FALSE;
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
 //#endif  //!___NO_OLE_SUPPORT
 */

CLASS_DECL_mac bool vfxResolveShortcut(string & strTarget, const char * pszSource, ::user::interaction * puiMessageParentOptional)
{
   
   
   
   char realname[_POSIX_PATH_MAX * 4];
//   int32_t rc = 0;
   
   if(realpath(pszSource, realname) == 0)
      return false;
   
   strTarget = realname;
   
   return true;
   
   /*
    
    ::user::interaction * pui = puiMessageParentOptional;
    
    wstring wstrFileOut;
    wstring wstrFileIn = ::str::international::utf8_to_unicode(pszSource);
    
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
    
    bool bNativeUnicode;
    if (dwVersion < 0x80000000)              // Windows NT
    bNativeUnicode = TRUE;
    else if (dwWindowsMajorVersion < 4)      // Win32s
    bNativeUnicode = FALSE;
    else                                     // Windows Me/98/95
    bNativeUnicode = FALSE;
    
    
    //   __COM com;
    IShellLinkW* psl;
    wstrFileOut = L"";
    
    SHFILEINFOW info;
    if ((::win::shell::SHGetFileInfo(wstrFileIn, 0, &info, sizeof(info),
    SHGFI_ATTRIBUTES) == 0) || !(info.dwAttributes & SFGAO_LINK))
    {
    return FALSE;
    }
    
    HRESULT hr ;
    if (FAILED(hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
    (LPVOID*)&psl)))
    {
    return FALSE;
    }
    
    IPersistFile *ppf;
    if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf)))
    {
    if (SUCCEEDED(ppf->Load(wstrFileIn, STGM_READ)))
    {
     Resolve the link, this may post UI to find the link */
   /*       if (SUCCEEDED(psl->Resolve(pui == NULL ? NULL : (oswindow) pui->get_os_data(),
    SLR_ANY_MATCH | (pui == NULL ? (SLR_NO_UI | (8400 << 16)) : 0))))
    {
    wstrFileOut.alloc(MAX_PATH);
    bool bOk;
    if(SUCCEEDED(psl->GetPath(wstrFileOut, MAX_PATH, NULL, 0)))
    {
    bOk = true;
    wstrFileOut.release_buffer();
    strTarget = ::str::international::unicode_to_utf8((LPCWSTR) wstrFileOut);
    }
    else
    {
    bOk = false;
    }
    ppf->Release();
    psl->Release();
    return bOk;
    }
    }
    ppf->Release();
    }
    psl->Release();
    return FALSE;*/
}

// turn a file, relative path or other into an absolute path
//bool CLASS_DECL_mac vfxFullPath(wchar_t * lpszPathOut, const wchar_t * lpszFileIn)
// lpszPathOut = buffer of _MAX_PATH
// lpszFileIn = file, relative path or absolute path
// (both in ANSI character set)
//{
/*
 ASSERT(__is_valid_address(lpszPathOut, _MAX_PATH));
 
 // first, fully qualify the path name
 wchar_t * lpszFilePart;
 if (!GetFullPathNameW(lpszFileIn, _MAX_PATH, lpszPathOut, &lpszFilePart))
 {
 #ifdef DEBUG
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
 if (!GetVolumeInformationW(::str::international::utf8_to_unicode(strRoot), NULL, 0, NULL, &dwDummy, &dwFlags, NULL, 0))
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
 return TRUE;*/
//}



/*
 void CLASS_DECL_mac vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath)
 {
 //   ASSERT(lpszPath != NULL);
 // determine the root name of the volume
 wstrRoot = wstrPath;
 wchar_t * lpszRoot = wstrRoot;
 wchar_t * lpsz;
 for (lpsz = lpszRoot; *lpsz != L'\0'; lpsz = _wcsinc(lpsz))
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
 wstrRoot.release_buffer();
 }*/

/*
 void CLASS_DECL_mac vfxGetRoot(const wchar_t * lpszPath, string& strRoot)
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
 ::str::international::unicode_to_utf8(strRoot, wstrRoot);
 }
 */


/*bool CLASS_DECL_mac vfxFullPath(char * lpszPathOut, const char * lpszFileIn)
 // lpszPathOut = buffer of _MAX_PATH
 // lpszFileIn = file, relative path or absolute path
 // (both in ANSI character set)
 {
 ASSERT(__is_valid_address(lpszPathOut, _MAX_PATH));
 
 // first, fully qualify the path name
 wchar_t * lpszFilePart;
 if (!shell::GetFullPathName(lpszFileIn, _MAX_PATH, lpszPathOut, &lpszFilePart))
 {
 #ifdef DEBUG
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
 if (!shell::GetVolumeInformation(wstrRoot, NULL, 0, NULL, &dwDummy, &dwFlags,
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
 HANDLE h = shell::FindFirstFile(lpszFileIn, &data);
 if (h != INVALID_HANDLE_VALUE)
 {
 FindClose(h);
 wcscpy(lpszFilePart, data.cFileName);
 }
 }
 return TRUE;
 }*/




/*CLASS_DECL_mac UINT vfxGetFileName(const char * lpszPathName, char * lpszTitle, UINT nMax)
 {
 ASSERT(lpszTitle == NULL ||
 __is_valid_address(lpszTitle, _MAX_FNAME));
 ASSERT(__is_valid_string(lpszPathName));
 
 // always capture the complete file name including extension (if present)
 const char * lpszTemp = (char *)lpszPathName;
 for (const char * lpsz = lpszPathName; *lpsz != '\0'; lpsz = lpsz++)
 {
 // remember last directory/drive separator
 if (*lpsz == '\\' || *lpsz == '/' || *lpsz == ':')
 lpszTemp = lpsz++;
 }
 
 // lpszTitle can be NULL which just returns the number of bytes
 if (lpszTitle == NULL)
 return strlen_dup(lpszTemp)+1;
 
 // otherwise copy it into the buffer provided
 strncpy(lpszTitle, lpszTemp, nMax);
 return 0;
 }*/






/////////////////////////////////////////////////////////////////////////////
// WinFileException helpers

void CLASS_DECL_mac vfxThrowFileException(base_application * papp, int32_t cause, LONG lOsError, const char * lpszFileName /* == NULL */)
{
#ifdef DEBUG
   const char * lpsz;
   if (cause >= 0 && cause < _countof(::mac::rgszFileExceptionCause))
      lpsz = ::mac::rgszFileExceptionCause[cause];
   else
      lpsz = ::mac::szUnknown;
   //   TRACE3("file exception: %hs, file %s, App error information = %ld.\n", lpsz, (lpszFileName == NULL) ? "Unknown" : lpszFileName, lOsError);
#endif
   throw ::file::exception(papp, cause, lOsError, lpszFileName);
}

namespace mac
{

namespace file_exception {

int32_t PASCAL ErrnoToException(int32_t nErrno)
{
   switch(nErrno)
   {
      case EPERM:
      case EACCES:
         return ::file::exception::accessDenied;
      case EBADF:
         return ::file::exception::invalidFile;
//      case EDEADLOCK:
  //       return ::file::exception::sharingViolation;
      case EMFILE:
         return ::file::exception::tooManyOpenFiles;
      case ENOENT:
      case ENFILE:
         return ::file::exception::fileNotFound;
      case ENOSPC:
         return ::file::exception::diskFull;
      case EINVAL:
      case EIO:
         return ::file::exception::hardIO;
      default:
         return ::file::exception::type_generic;
   }
}



} // namespace file_exception

} // namespace mac