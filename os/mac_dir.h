#pragma once


namespace mac
{
   
   class CLASS_DECL_mac path :
   virtual public ::file::path
   {
   public:
      path(sp(base_application)  papp);
      virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
   };
   
   class CLASS_DECL_mac dir :
   virtual public ::file::dir::system
   {
   public:
      
      
      
      
      string      m_strCa2;
      
      
      dir(sp(base_application)  papp);
      
      
      using ::file::dir::system::path;
      virtual class ::file::path & path();
      virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);
      
      virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = NULL);
      virtual void  ls_pattern(sp(base_application)  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
      virtual void  ls(sp(base_application)  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
      virtual void  rls_pattern(sp(base_application)  papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
      virtual void  rls(sp(base_application)  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
      virtual void  rls_dir(sp(base_application)  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
      virtual void  ls_dir(sp(base_application)  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      virtual bool  has_subdir(sp(base_application)  papp, const char * lpcsz);
      virtual void  ls_file(sp(base_application)  papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      virtual bool  is(const char * lpcsz, sp(base_application)  papp);
      virtual bool  is(const string & str, sp(base_application)  papp);
      virtual bool  name_is(const string & str, sp(base_application)  papp);
      virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, sp(base_application)  papp);
      virtual bool  is_inside_time(const char * lpcsz, sp(base_application)  papp);
      virtual void root_ones(stringa & stra, sp(base_application)  papp);
      virtual bool mk(const char * lpcsz, sp(base_application)  papp);
      virtual bool rm(sp(base_application)  papp, const char * psz, bool bRecursive = true);
      
      
      virtual string name(const char * lpcsz);
      virtual string name(const string & str);
      
      virtual string votagus(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string time(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string stage(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string stageapp(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string netseed(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      
      // stage in ccvotagus spalib
      virtual string element(const char * lpcsz, const char * lpcsz2 = NULL);
      virtual string element();
      virtual string element(const string & str);
      virtual string element(const string & str, const string & str2);
      virtual string element(const char * lpcsz, const string & str2);
      virtual string element(const string & str, const char * lpcsz2);
      
      virtual string module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string ca2module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual void time_square(string &str);
      virtual string time_log(const char * pszId);
      
      
      virtual string trash_that_is_not_trash(const char * psz);
      
      virtual string appdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      
      virtual string usersystemappdata(sp(base_application)  papp, const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userappdata(sp(base_application)  papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userdata(sp(base_application)  papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userfolder(sp(base_application)  papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string default_os_user_path_prefix(sp(base_application)  papp);
      virtual string default_userappdata(sp(base_application)  papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
      virtual string default_userdata(sp(base_application)  papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
      virtual string default_userfolder(sp(base_application)  papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
      virtual string userquicklaunch(sp(base_application)  papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
      virtual string userprograms(sp(base_application)  papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
      
      virtual string commonprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
      
      virtual bool initialize();
   protected:
      class path     m_path;
      string         m_strTimeFolder;
      string         m_strNetSeedFolder;
   };
   
} // namespace mac


