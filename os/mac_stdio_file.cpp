#include "framework.h"

#include <fcntl.h>

namespace mac
{
   
   
   
   stdio_file::stdio_file(base_application * papp) :
   element(papp),
   ::mac::file(papp)
   {
      m_pStream = NULL;
   }
   
   stdio_file::~stdio_file()
   {
      //   ASSERT_VALID(this);
      
      //   if (m_pStream != NULL && m_bCloseOnDelete)
      //close();
      if (m_pStream != NULL)
         close();
   }
   
   bool stdio_file::open(const char * lpszFileName, UINT nOpenFlags)
   {
      ASSERT(lpszFileName != NULL);
      //ASSERT(AfxIsValidString(lpszFileName));
      
      if(nOpenFlags  & ::file::defer_create_directory)
      {
         Application.dir().mk(System.dir().name(lpszFileName));
      }
      
      m_pStream = NULL;
      //if (!::lnx::file::open(lpszFileName, (nOpenFlags & ~::file::type_text)))
      // return FALSE;
      
      //   ASSERT(m_hFile != hFileNull);
      // ASSERT(m_bCloseOnDelete);
      
      char szMode[4]; // C-runtime open string
      int32_t nMode = 0;
      
      // determine read/write mode depending on ::ca2::filesp mode
      if (nOpenFlags & ::file::mode_create)
      {
         if (nOpenFlags & ::file::mode_no_truncate)
            szMode[nMode++] = 'a';
         else
            szMode[nMode++] = 'w';
      }
      else if (nOpenFlags & ::file::mode_write)
         szMode[nMode++] = 'a';
      else
         szMode[nMode++] = 'r';
      
      // add '+' if necessary (when read/write modes mismatched)
      if ((szMode[0] == 'r' && (nOpenFlags & ::file::mode_read_write)) ||
          (szMode[0] != 'r' && !(nOpenFlags & ::file::mode_write)))
      {
         // current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }
      
      // will be inverted if not necessary
      int32_t nFlags = O_RDONLY;
      if (nOpenFlags & (::file::mode_write | ::file::mode_read_write))
         nFlags ^= O_RDONLY;
      
      if (nOpenFlags & ::file::type_binary)
         szMode[nMode++] = 'b'; // , nFlags ^= _O_TEXT;
      else
         szMode[nMode++] = 't';
      szMode[nMode++] = '\0';
      
      // open a C-runtime low-level file handle
      //int32_t nHandle = _open_osfhandle(m_hFile, nFlags);
      
      // open a C-runtime stream from that handle
      //if (nHandle != -1)
      m_pStream = fopen(lpszFileName, szMode);
      
      
      if (m_pStream == NULL)
      {
         vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
         // an error somewhere along the way...
         //if (pException != NULL)
         {
            //         pException->m_lOsError = errno;
            //         pException->m_cause = ::file::exception::OsErrorToException(errno);
         }
         
         ::mac::file::Abort(); // close m_hFile
         return FALSE;
      }
      
      m_strFileName = lpszFileName;
      
      return TRUE;
   }
   
   uint_ptr stdio_file::read(void * lpBuf, uint_ptr nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"
      
      //   ASSERT(fx_is_valid_address(lpBuf, nCount));
      
      size_t nRead = 0;
      
      if ((nRead = fread(lpBuf, sizeof(BYTE), nCount, m_pStream)) == 0 && !feof(m_pStream))
         vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
      if (ferror(m_pStream))
      {
         clearerr(m_pStream);
         vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
      }
      return nRead;
   }
   
   void stdio_file::write(const void * lpBuf, uint_ptr nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      //   ASSERT(fx_is_valid_address(lpBuf, nCount, FALSE));
      
      if (fwrite(lpBuf, sizeof(BYTE), nCount, m_pStream) != nCount)
         vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
   }
   
   void stdio_file::write_string(const char * lpsz)
   {
      ASSERT(lpsz != NULL);
      ASSERT(m_pStream != NULL);
      
      if (fputs(lpsz, m_pStream) == EOF)
         vfxThrowFileException(get_app(), ::file::exception::diskFull, errno, m_strFileName);
   }
   
   LPTSTR stdio_file::read_string(LPTSTR lpsz, UINT nMax)
   {
      ASSERT(lpsz != NULL);
      //   ASSERT(fx_is_valid_address(lpsz, nMax));
      ASSERT(m_pStream != NULL);
      
      LPTSTR lpszResult = fgets(lpsz, nMax, m_pStream);
      if (lpszResult == NULL && !feof(m_pStream))
      {
         clearerr(m_pStream);
         vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
      }
      
      return lpszResult;
   }
   
   
   bool stdio_file::read_string(string & rString)
   {
      
      ASSERT_VALID(this);
      
      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.Empty();
      const int32_t nMaxSize = 128;
      char * lpsz = rString.GetBuffer(nMaxSize);
      char * lpszResult;
      strsize nLen = 0;
      for (;;)
      {
         lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
         rString.ReleaseBuffer();
         
         // handle error/eof case
         if (lpszResult == NULL && !feof(m_pStream))
         {
            clearerr(m_pStream);
            vfxThrowFileException(get_app(), ::file::exception::type_generic, errno,
                                  m_strFileName);
         }
         
         // if string is read completely or EOF
         if (lpszResult == NULL ||
             (nLen = strlen(lpsz)) < nMaxSize ||
             lpsz[nLen-1] == '\n')
            break;
         
         nLen = rString.get_length();
         lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;
      }
      
      // remov '\n' from end of string if present
      lpsz = rString.GetBuffer(0);
      nLen = rString.get_length();
      if (nLen != 0 && lpsz[nLen-1] == '\n')
         rString.GetBufferSetLength(nLen-1);
      
      return lpszResult != NULL;
   }
   
   /*void stdio_file::write_string(const char * lpsz)
    {
    ASSERT(lpsz != NULL);
    ASSERT(m_pStream != NULL);
    
    if (fputws(lpsz, m_pStream) == _TEOF)
    vfxThrowFileException(get_app(), ::file::exception::diskFull, errno, m_strFileName);
    }*/
   
   /*wchar_t * stdio_file::read_string(wchar_t * lpsz, UINT nMax)
    {
    ASSERT(lpsz != NULL);
    ASSERT(fx_is_valid_address(lpsz, nMax));
    ASSERT(m_pStream != NULL);
    
    wchar_t * lpszResult = fgetws(lpsz, nMax, m_pStream);
    if (lpszResult == NULL && !feof(m_pStream))
    {
    clearerr(m_pStream);
    vfxThrowFileException(get_app(), ::file::exception::type_generic, errno, m_strFileName);
    }
    return lpszResult;
    }*/
   
   file_position stdio_file::seek(file_offset lOff, ::file::e_seek eseek)
   {
      ASSERT_VALID(this);
      ASSERT(eseek == ::file::seek_begin || eseek== ::file::seek_end || eseek== ::file::seek_current);
      ASSERT(m_pStream != NULL);
      
      int32_t nFrom;
      switch(eseek)
      {
         case ::file::seek_begin:
            nFrom = SEEK_SET;
            break;
         case ::file::seek_end:
            nFrom = SEEK_END;
            break;
         case ::file::seek_current:
            nFrom = SEEK_CUR;
            break;
         default:
            vfxThrowFileException(get_app(), ::file::exception::badSeek, -1, m_strFileName);
      }
      
      if (fseek(m_pStream, lOff, nFrom) != 0)
         vfxThrowFileException(get_app(), ::file::exception::badSeek, errno,
                               m_strFileName);
      
      long pos = ftell(m_pStream);
      return pos;
   }
   
   file_position stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      long pos = ftell(m_pStream);
      if (pos == -1)
         vfxThrowFileException(get_app(), ::file::exception::invalidFile, errno,
                               m_strFileName);
      return pos;
   }
   
   void stdio_file::Flush()
   {
      ASSERT_VALID(this);
      
      if (m_pStream != NULL && fflush(m_pStream) != 0)
         vfxThrowFileException(get_app(), ::file::exception::diskFull, errno,
                               m_strFileName);
   }
   
   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      int32_t nErr = 0;
      
      if (m_pStream != NULL)
         nErr = fclose(m_pStream);
      
      //   m_hFile = (UINT) hFileNull;
      m_bCloseOnDelete = FALSE;
      m_pStream = NULL;
      
      if (nErr != 0)
         vfxThrowFileException(get_app(), ::file::exception::diskFull, errno,
                               m_strFileName);
   }
   
   void stdio_file::Abort()
   {
      ASSERT_VALID(this);
      
      if (m_pStream != NULL && m_bCloseOnDelete)
         fclose(m_pStream);  // close but ignore errors
      //   m_hFile = (UINT) hFileNull;
      m_pStream = NULL;
      m_bCloseOnDelete = FALSE;
   }
   
   sp(::file::stream_buffer) stdio_file::Duplicate() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      throw not_supported_exception(get_app());
      return NULL;
   }
   
   void stdio_file::LockRange(uint_ptr /* dwPos */, uint_ptr /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      throw not_supported_exception(get_app());
   }
   
   void stdio_file::UnlockRange(uint_ptr /* dwPos */, uint_ptr /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != NULL);
      
      throw not_supported_exception(get_app());
   }
   
#ifdef _DEBUG
   void stdio_file::dump(dump_context & dumpcontext) const
   {
      ::mac::file::dump(dumpcontext);
      
      dumpcontext << "m_pStream = " << (void *)m_pStream;
      dumpcontext << "\n";
   }
#endif
   
   
   
   uint_ptr stdio_file::get_length() const
   {
      ASSERT_VALID(this);
      
      long nCurrent;
      long nLength;
      long nResult;
      
      nCurrent = ftell(m_pStream);
      if (nCurrent == -1)
         vfxThrowFileException(get_app(), ::file::exception::invalidFile, errno,
                               m_strFileName);
      
      nResult = fseek(m_pStream, 0, SEEK_END);
      if (nResult != 0)
         vfxThrowFileException(get_app(), ::file::exception::badSeek, errno,
                               m_strFileName);
      
      nLength = ftell(m_pStream);
      if (nLength == -1)
         vfxThrowFileException(get_app(), ::file::exception::invalidFile, errno,
                               m_strFileName);
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      if (nResult != 0)
         vfxThrowFileException(get_app(), ::file::exception::badSeek, errno,
                               m_strFileName);
      
      return nLength;
   }
   
   
} // namespace mac
