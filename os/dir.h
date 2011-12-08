#pragma once

namespace win
{

   class CLASS_DECL_VMSWIN dir :
      virtual public ::ca::dir::system
   {
   public:

      dir(::ca::application * papp);
      class CLASS_DECL_VMSWIN path :
         virtual public ::ca::dir::system::path
      {
      public:
         path(::ca::application * papp);
         virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
      };

      virtual class ::ca::dir::system::path & path();
      
      virtual string path(const char * lpcszFolder, const char * lpcszRelative, const char * lpcsz2 = NULL);
      virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = NULL);
      virtual void  ls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
      virtual void  ls(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
      virtual void  rls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
      virtual void  rls(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
      virtual void  rls_dir(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
      virtual void  ls_dir(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      virtual bool  has_subdir(const char * lpcsz);
      virtual void  ls_file(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
      virtual bool  is(const char * lpcsz);
      virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath);
      virtual bool  is_inside_time(const char * lpcsz);
      virtual void root_ones(stringa & stra);
      virtual bool mk(const char * lpcsz);
      virtual bool rm(const char * psz, bool bRecursive = true);
      

      virtual string name(const char * psz);

      virtual string votagus(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string time(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string stage(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string stageapp(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string netseed(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      // stage in ccvotagus spalib
      virtual string ca2(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string ca2module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual void time_square(string &str);
      virtual string time_log(const char * pszId);

      virtual string locale_style(::ca::application * papp, const char * pszLocale = NULL, const char * pszStyle = NULL);
      virtual string locale_style_matter(::ca::application * papp, const char * pszLocale = NULL, const char * pszStyle = NULL);
      virtual string matter(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);

      virtual string trash_that_is_not_trash(const char * psz);

      virtual string appdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);

      virtual string usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userappdata(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userdata(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string userfolder(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
      virtual string default_os_user_path_prefix(::ca::application * papp);
      virtual string default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
      virtual string default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
      virtual string default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
      virtual string userquicklaunch(::ca::application * papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
      virtual string userprograms(::ca::application * papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);

      virtual string commonprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);

      virtual bool initialize();
   protected:
      class path     m_path;
      string         m_strTimeFolder;
      string         m_strNetSeedFolder;
   };

} // namespace win