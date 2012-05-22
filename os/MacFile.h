#pragma once


class FileException;
struct FileStatus;

void CLASS_DECL_VMSWIN vfxGetRoot(const wchar_t * lpszPath, string& wstrRoot);

/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O

class CLASS_DECL_VMSWIN WinFile :
   virtual public ex1::file
{
public:

   enum Attribute {
      normal =    0x00,
      readOnly =  0x01,
      hidden =    0x02,
      system =    0x04,
      volume =    0x08,
      directory = 0x10,
      archive =   0x20
      };

   enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

   enum { hFileNull = -1 };

   zip::Util  * m_pziputil;

// Constructors
   WinFile(::ca::application * papp);
   WinFile(::ca::application * papp, int hFile);
   WinFile(::ca::application * papp, const char * lpszFileName, UINT nOpenFlags);

// Attributes
   UINT m_hFile;
   operator HFILE() const;

   virtual dword_ptr GetPosition() const;
   WINBOOL GetStatus(ex1::file_status & rStatus) const;
   virtual string GetFileName() const;
   virtual string GetFileTitle() const;
   virtual string GetFilePath() const;
   virtual void SetFilePath(const char * lpszNewName);

// Operations
   virtual WINBOOL open(const char * lpszFileName, UINT nOpenFlags,
      ex1::file_exception_sp * pError = NULL);

/*
   static void PASCAL Rename(const char * lpszOldName,
            const char * lpszNewName);
   static void PASCAL remov(const char * lpszFileName);*/
   virtual WINBOOL PASCAL GetStatus(const char * lpszFileName,
            ::ex1::file_status& rStatus);
   /*static void PASCAL SetStatus(const char * lpszFileName,
            const ::ex1::file_status& status);
*/

   dword_ptr seek_to_end();
   void seek_to_begin();

   // backward compatible ReadHuge and WriteHuge
   dword_ptr ReadHuge(void * lpBuffer, dword_ptr dwCount);
   void WriteHuge(const void * lpBuffer, dword_ptr dwCount);

// Overridables
   virtual ex1::file * Duplicate() const;

   virtual int_ptr seek(int_ptr lOff, UINT nFrom);
   virtual void SetLength(dword_ptr dwNewLen);
   virtual dword_ptr get_length() const;

   virtual dword_ptr read(void * lpBuf, dword_ptr nCount);
   virtual void write(const void * lpBuf, dword_ptr nCount);

   virtual void LockRange(dword_ptr dwPos, dword_ptr dwCount);
   virtual void UnlockRange(dword_ptr dwPos, dword_ptr dwCount);

   virtual void Abort();
   virtual void Flush();
   virtual void close();

// ementation
public:
   virtual bool IsOpened();
   virtual ~WinFile();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
   enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
   virtual dword_ptr GetBufferPtr(UINT nCommand, dword_ptr nCount = 0,
      void ** ppBufStart = NULL, void ** ppBufMax = NULL);

protected:
   WINBOOL m_bCloseOnDelete;
   string m_strFileName;
};

class CLASS_DECL_VMSWIN WinFileException :
   virtual public ex1::file_exception
{
public:
   enum
   {
      none,
      generic,
      fileNotFound,
      badPath,
      tooManyOpenFiles,
      accessDenied,
      invalidFile,
      removeCurrentDir,
      directoryFull,
      badSeek,
      hardIO,
      sharingViolation,
      lockViolation,
      diskFull,
      endOfFile
   };

// Constructor
   WinFileException(::ca::application * papp, int cause = none, LONG lOsError = -1,
      const char * lpszArchiveName = NULL);

// Attributes
   int      m_cause;
   LONG     m_lOsError;
   string   m_strFileName;


   virtual int get_cause();
   virtual LONG get_os_error();
   virtual string get_file_path();


// Operations
   // convert a App dependent error code to a Cause
   static int PASCAL OsErrorToException(LONG lOsError);
   static int PASCAL ErrnoToException(int nErrno);

   // helper functions to throw exception after converting to a Cause
   static void PASCAL ThrowOsError(::ca::application * papp, LONG lOsError, const char * lpszFileName = NULL);
   static void PASCAL ThrowErrno(::ca::application * papp, int nErrno, const char * lpszFileName = NULL);

// ementation
public:
   virtual ~WinFileException();
#ifdef _DEBUG
   virtual void dump(dump_context&) const;
#endif
   virtual WINBOOL GetErrorMessage(string & str, PUINT pnHelpContext = NULL);
};

inline WinFileException::WinFileException(::ca::application * papp, int cause, LONG lOsError,
                                          const char * pstrFileName /* = NULL */) :
   ca(papp),
   ex1::file_exception(papp)
   { m_cause = cause; m_lOsError = lOsError; m_strFileName = pstrFileName; }
inline WinFileException::~WinFileException()
   { }


// ex1::filesp
inline WinFile::operator HFILE() const
   { return m_hFile; }
inline dword_ptr WinFile::ReadHuge(void * lpBuffer, dword_ptr dwCount)
   { return (dword_ptr) read(lpBuffer, (UINT)dwCount); }
inline void WinFile::WriteHuge(const void * lpBuffer, dword_ptr dwCount)
   { write(lpBuffer, (UINT)dwCount); }
inline dword_ptr WinFile::seek_to_end()
   { return seek(0, WinFile::end); }
inline void WinFile::seek_to_begin()
   { seek(0, WinFile::begin); }

/////////////////////////////////////////////////////////////////////////////
// File status

/*struct FileStatus
{
   class time m_ctime;          // creation date/time of file
   class time m_mtime;          // last modification date/time of file
   class time m_atime;          // last access date/time of file
   LONG m_size;            // logical size of file in bytes
   BYTE m_attribute;       // logical OR of ex1::filesp::Attribute enum values
   BYTE _m_padding;        // pad the structure to a WORD
   WCHAR m_szFullName[_MAX_PATH]; // absolute path name

#ifdef _DEBUG
   void dump(dump_context & dumpcontext) const;
#endif
};*/
