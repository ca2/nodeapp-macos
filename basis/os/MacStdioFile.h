#pragma once

#include "WinFile.h"

/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation

class WinStdioFile : 
   virtual public WinFile,
   virtual public ex1::text_file
{
public:
   WinStdioFile(::ca::application * papp);

// Attributes
   FILE* m_pStream;    // stdio FILE
                  // m_hFile from base class is _fileno(m_pStream)

// Operations
   // reading and writing strings
   virtual void write_string(const char * lpsz);
   virtual char * read_string(char * lpsz, UINT nMax);
//   virtual void write_string(const char * lpsz);
//   virtual wchar_t * read_string(wchar_t * lpsz, UINT nMax);
   virtual UINT read_string(string & rString);

// ementation
public:
   virtual ~WinStdioFile();
#ifdef _DEBUG
   void dump(dump_context & dumpcontext) const;
#endif
   virtual dword_ptr GetPosition() const;
   virtual WINBOOL open(const char * lpszFileName, UINT nOpenFlags,
      ex1::file_exception_sp * pError = NULL);
   virtual dword_ptr read(void * lpBuf, dword_ptr nCount);
   virtual void write(const void * lpBuf, dword_ptr nCount);
   virtual int_ptr seek(int_ptr lOff, UINT nFrom);
   virtual void Abort();
   virtual void Flush();
   virtual void close();
   virtual dword_ptr get_length() const;

   // Unsupported APIs
   virtual ex1::file * Duplicate() const;
   virtual void LockRange(dword_ptr dwPos, dword_ptr dwCount);
   virtual void UnlockRange(dword_ptr dwPos, dword_ptr dwCount);
};
