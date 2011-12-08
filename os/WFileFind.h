#pragma once

class CLASS_DECL_VMSWIN FileFind : public ::radix::object
{
public:
   FileFind();
   virtual ~FileFind();

// Attributes
public:
   __int64 get_length() const;
   virtual string GetFileName() const;
   virtual string GetFilePath() const;
   virtual string GetFileTitle() const;
   virtual string GetFileURL() const;
   virtual string GetRoot() const;

   virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp) const;
   virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp) const;
   virtual BOOL GetCreationTime(FILETIME* pTimeStamp) const;
   virtual BOOL GetLastWriteTime(class time& refTime) const;
   virtual BOOL GetLastAccessTime(class time& refTime) const;
   virtual BOOL GetCreationTime(class time& refTime) const;

   virtual BOOL MatchesMask(DWORD dwMask) const;

   virtual BOOL IsDots() const;
   // these aren't virtual because they all use MatchesMask(), which is
   BOOL IsReadOnly() const;
   BOOL IsDirectory() const;
   BOOL IsCompressed() const;
   BOOL IsSystem() const;
   BOOL IsHidden() const;
   BOOL IsTemporary() const;
   BOOL IsNormal() const;
   BOOL IsArchived() const;

// Operations
   void close();
   virtual BOOL FindFile(const char * pstrName = NULL, DWORD dwUnused = 0);
   virtual BOOL FindNextFile();

protected:
   virtual void CloseContext();

// ementation
protected:
   WIN32_FIND_DATAW * m_pFoundInfo;
   WIN32_FIND_DATAW * m_pNextInfo;
   HANDLE m_hContext;
   BOOL m_bGotLast;
   string m_strRoot;
   char m_chDirSeparator;     // not '\\' for Internet classes

#ifdef _DEBUG
   void dump(dump_context & dumpcontext) const;
   void assert_valid() const;
#endif

   
};

// FileFind
inline BOOL FileFind::IsReadOnly() const
   { return MatchesMask(FILE_ATTRIBUTE_READONLY); }
inline BOOL FileFind::IsDirectory() const
   { return MatchesMask(FILE_ATTRIBUTE_DIRECTORY); }
inline BOOL FileFind::IsCompressed() const
   { return MatchesMask(FILE_ATTRIBUTE_COMPRESSED); }
inline BOOL FileFind::IsSystem() const
   { return MatchesMask(FILE_ATTRIBUTE_SYSTEM); }
inline BOOL FileFind::IsHidden() const
   { return MatchesMask(FILE_ATTRIBUTE_HIDDEN); }
inline BOOL FileFind::IsTemporary() const
   { return MatchesMask(FILE_ATTRIBUTE_TEMPORARY); }
inline BOOL FileFind::IsNormal() const
   { return MatchesMask(FILE_ATTRIBUTE_NORMAL); }
inline BOOL FileFind::IsArchived() const
   { return MatchesMask(FILE_ATTRIBUTE_ARCHIVE); }
