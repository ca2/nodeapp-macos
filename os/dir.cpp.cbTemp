#include "StdAfx.h"

namespace win
{
   dir::dir(::ca::application * papp) :
      ca(papp),
      ::ca::dir::system(papp),
      m_path(papp)
   {
   }

   dir::path::path(::ca::application * papp) :
      ca(papp)
   {
   }

   bool is_url(const char * pszCandidate, const char ** ppszRequest = NULL)
   {
      const char * psz = pszCandidate;
      count count = 0;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || gen::ch::is_letter_or_digit(psz)))
      {
         psz = gen::str::utf8_inc(psz);
         count++;
      }
      if(count <= 0)
         return false;
      if(*psz != ':')
         return false;
      psz++;
      if(*psz != '/')
         return false;
      psz++;
      if(*psz != '/')
         return false;
      psz++;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || gen::ch::is_letter_or_digit(psz)))
      {
         psz = gen::str::utf8_inc(psz);
      }
      if(*psz != '\0' && *psz != '/')
         return false;
      if(ppszRequest != NULL)
      {
         *ppszRequest = psz;
      }
      return true;
   }

   string dir::path(const char * lpcszFolder, const char * lpcszRelative, const char * psz2)
   {
      bool bUrl = is_url(lpcszFolder);
      if(lpcszRelative == NULL)
      {
         if(psz2 == NULL)
            return lpcszFolder;
         psz2 = lpcszRelative;
         psz2 = NULL;
      }
      string strPath;
      string strFolder(lpcszFolder);
      string strRelative(lpcszRelative);
      strFolder.trim();
      gen::str::ends_eat(strFolder, "\\");
      gen::str::ends_eat(strFolder, "/");
      gen::str::begins_eat(strRelative, "\\");
      gen::str::begins_eat(strRelative, "/");
      if(strFolder.is_empty())
      {
         strPath = strRelative;
      }
      else if(bUrl)
      {
         strPath = strFolder + "/" + strRelative;
      }
      else
      {
         strPath = strFolder + "\\" + strRelative;
      }
      if(psz2 != NULL)
      {
         strPath = path(strPath, psz2);
      }

      if(bUrl)
      {
         strPath.replace("\\", "/");
      }
      else
      {
         strPath.replace("/", "\\");
      }
      return strPath;
   }

   string dir::relpath(const char * lpcszSource, const char * lpcszRelative, const char * psz2)
   {
      const char * pszRequest;
      if(is_url(lpcszSource, &pszRequest))
      {
         if(gen::str::begins(lpcszRelative, "/"))
         {
            return path(string(lpcszSource, pszRequest - lpcszSource), lpcszRelative);
         }
         else if(*pszRequest == '\0' || gen::str::ends(lpcszSource, "/"))
         {
            return path(lpcszSource, lpcszRelative, psz2);
         }
         else
         {
            return path(name(lpcszSource), lpcszRelative, psz2);
         }
      }
      else
      {
         if(gen::str::ends(lpcszSource, "\\") || gen::str::ends(lpcszSource, "/"))
         {
            return path(lpcszSource, lpcszRelative, psz2);
         }
         else
         {
            return path(name(lpcszSource), lpcszRelative, psz2);
         }
      }
   }

   bool dir::path::is_equal(const char * lpcsz1, const char * lpcsz2)
   {
      return System.file_system().ComparePath(lpcsz1, lpcsz2);
   }

   void dir::root_ones(stringa & stra)
   {
      DWORD dwSize = ::GetLogicalDriveStrings(0, NULL);
      LPTSTR lpszAlloc = (LPTSTR) malloc(dwSize + 1);
      LPTSTR lpsz = lpszAlloc;
      dwSize = ::GetLogicalDriveStrings(dwSize + 1, lpsz);

      string str;
      while(*lpsz)
      {
         str.Empty();
         while(*lpsz)
         {
            str += *lpsz;
            lpsz++;
         }
         stra.add(str);
         lpsz++;
      }

      free(lpszAlloc);
   }

   void dir::ls_pattern(const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      if(::ca::dir::system::is(lpcsz)) // if base class "already" "says" it is a dir, let it handle it: may be not a operational system dir, e.g., zip or compressed directory...
      {
         return ::ca::dir::system::ls_pattern(lpcsz, pszPattern, pstraPath, pstraTitle, pbaIsDir, piaSize);
      }
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(System.dir().path(lpcsz, pszPattern));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
            if(pbaIsDir != NULL)
            {
               pbaIsDir->add(filefind.IsDirectory() != FALSE);
            }
            if(piaSize != NULL)
            {
               piaSize->add(filefind.get_length());
            }
         }
      }
   }

   void dir::rls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
   {
      rls_pattern(lpcsz, "*.*", pstraPath, pstraTitle, pstraRelative, NULL, NULL);
   }

   void dir::rls_pattern(const char * lpcsz, const char * lpszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      stringa straDir;
      ls_dir(lpcsz, &straDir);
      for(int i = 0; i < straDir.get_count(); i++)
      {
         string strDir = straDir[i];
         int iStart = 0;
         if(pstraRelative != NULL)
         {
            iStart = pstraRelative->get_size();
         }
         rls_pattern(strDir, lpszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize);
         if(pstraRelative != NULL)
         {
            for(int i = iStart; i < pstraRelative->get_size(); i++)
            {
               pstraRelative->element_at(i) = System.dir().path(System.file().name_(strDir), pstraRelative->element_at(i));
            }
         }
      }

      FileFind filefind;
      bool bWorking = filefind.FindFile(System.dir().path(lpcsz, lpszPattern));
      if(bWorking)
      {
         while(bWorking)
         {
            bWorking = filefind.FindNextFileA();
            if(!filefind.IsDots() && filefind.GetFilePath() != lpcsz)
            {
               if(pstraPath != NULL)
               {
                  pstraPath->add(filefind.GetFilePath());
               }
               if(pstraTitle != NULL)
               {
                  pstraTitle->add(filefind.GetFileName());
               }
               if(pstraRelative != NULL)
               {
                  pstraRelative->add(filefind.GetFileName());
               }
               if(pbaIsDir != NULL)
               {
                  pbaIsDir->add(filefind.IsDirectory() != FALSE);
               }
               if(piaSize != NULL)
               {
                  piaSize->add(filefind.get_length());
               }
               /*if(filefind.IsDirectory())
               {
                  int iStart = 0;
                  if(pstraRelative != NULL)
                  {
                     iStart = pstraRelative->get_size();
                  }
                  rls_pattern(filefind.GetFilePath(), lpszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize);
                  if(pstraRelative != NULL)
                  {
                     for(int i = iStart; i < pstraRelative->get_size(); i++)
                     {
                        pstraRelative->element_at(i) = System.dir().path(filefind.GetFileName(), pstraRelative->element_at(i));
                     }
                  }
               }*/
            }
         }
      }
      else
      {
         ::ca::dir::system::rls(lpcsz, pstraPath, pstraTitle, pstraRelative);
      }
   }

   void dir::rls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(System.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDots() && filefind.IsDirectory())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
            if(pstraRelative != NULL)
            {
               pstraRelative->add(filefind.GetFileName());
            }
            if(filefind.IsDirectory())
            {
               int iStart = 0;
               if(pstraRelative != NULL)
               {
                  iStart = pstraRelative->get_size();
               }
               rls_dir(filefind.GetFilePath(), pstraPath, pstraTitle, pstraRelative);
               if(pstraRelative != NULL)
               {
                  for(int i = iStart; i < pstraRelative->get_size(); i++)
                  {
                     pstraRelative->element_at(i) = System.dir().path(filefind.GetFileName(), pstraRelative->element_at(i));
                  }
               }
            }
         }
      }
   }

   void dir::ls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(System.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(filefind.IsDirectory() && !filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
         }
      }
   }

   void dir::ls_file(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(System.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDirectory() && !filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
         }
      }
   }

   void dir::ls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      return ls_pattern(lpcsz, "*.*", pstraPath, pstraTitle, pbaIsDir, piaSize);
   }

   bool dir::is(const char * lpcszPath)
   {
      string strPath(lpcszPath);
      if(strPath.get_length() >= MAX_PATH)
      {
         if(gen::str::begins(strPath, "\\\\"))
         {
            strPath = "\\\\?\\UNC" + strPath.Mid(1);
         }
         else
         {
            strPath = "\\\\?\\" + strPath;
         }
      }
      DWORD dwAttrib;
      dwAttrib = GetFileAttributesW(gen::international::utf8_to_unicode(strPath));
      if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
         dwAttrib = GetFileAttributes(lpcszPath);
      }
      if((dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
         return true;
      return ::ca::dir::system::is(lpcszPath);
   }



   string dir::votagus(const char * lpcsz, const char * lpcsz2)
   {
      string strVotagusFolder = System.get_ca2_module_folder();
      System.file().path().eat_end_level(strVotagusFolder, 2, "\\");
      return dir::path(strVotagusFolder, lpcsz, lpcsz2);
   }

   string dir::time(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(m_strTimeFolder, lpcsz, lpcsz2);
   }

   string dir::stage(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(ca2("stage"), lpcsz, lpcsz2);
   }

   string dir::stageapp(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(stage("basis", lpcsz), lpcsz2);
   }

   string dir::netseed(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(m_strNetSeedFolder, lpcsz, lpcsz2);
   }

   // stage in ccvotagus spalib
   string dir::ca2(const char * lpcsz, const char * lpcsz2)
   {
      string str = ca2module();
      System.file().path().eat_end_level(str, 2, "\\");
      return dir::path(str, lpcsz, lpcsz2);
   }

   string dir::module(const char * lpcsz, const char * lpcsz2)
   {
      string str = System.get_module_folder();
      return dir::path(str, lpcsz, lpcsz2);
   }

   string dir::ca2module(const char * lpcsz, const char * lpcsz2)
   {
      string str = System.get_ca2_module_folder();
      return dir::path(str, lpcsz, lpcsz2);
   }


   void dir::time_square(string &str)
   {
      str = time("time");
   }

   string dir::time_log(const char * pszId)
   {
      string strLogBaseDir;
      strLogBaseDir = appdata("log");
      return path(strLogBaseDir, pszId);
   }

   bool dir::mk(const char * lpcsz)
   {
      if(is(lpcsz))
         return true;
      stringa stra;
      System.file().get_ascendants_path(lpcsz, stra);
      for(int i = 0; i < stra.get_size(); i++)
      {
         if(!is(stra[i]))
         {
            if(!::CreateDirectoryW(gen::international::utf8_to_unicode(stra[i]), NULL))
            {
               DWORD dwError = ::GetLastError();
               char * pszError;
               FormatMessage(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     dwError,
     0,
     (LPTSTR) &pszError,
     8,
     NULL);

               TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
               ::LocalFree(pszError);
            }

            if(!is(stra[i]))
            {
               return false;
            }
         }
      }
      return true;
   }

   bool dir::rm(const char * psz, bool bRecursive)
   {
      if(bRecursive)
      {
         stringa straPath;
         stringa straTitle;
         ls(psz, &straPath, &straTitle);
         for(int i = 0; i < straPath.get_count(); i++)
         {
            if(is(straPath[i]))
            {
               rm(path(psz, straTitle[i]), true);
            }
            else
            {
               ::DeleteFile(straPath[i]);
            }
         }
      }
      return RemoveDirectory(psz) != FALSE;
   }


   string dir::name(const char * path1)
   {
      const char * psz = path1 + strlen(path1);
      const char * pszPrevious = psz;
      string strChar;
      while((psz = gen::str::utf8_dec(path1, pszPrevious)) != NULL)
      {
         strChar = gen::str::utf8_char(psz);
         if(strChar != "\\" && strChar != "/" && strChar != ":")
            break;
         pszPrevious = psz;
      }
      while((psz = gen::str::utf8_dec(path1, pszPrevious)) != NULL)
      {
         strChar = gen::str::utf8_char(psz);
         if(strChar == "\\" || strChar == "/" || strChar == ":")
            break;
         pszPrevious = psz;
      }
      if(psz != NULL) // strChar == "\\" || strChar == "/"
      {
         pszPrevious = psz;
         while((psz = gen::str::utf8_dec(path1, pszPrevious)) != NULL)
         {
            string strChar = gen::str::utf8_char(psz);
            if(strChar != "\\" && strChar != "/" && strChar != ":")
               break;
            pszPrevious = psz;
         }
         return string(path1, pszPrevious - path1 + 1);
      }
      else
      {
         return "";
      }
   }

   string dir::locale_style(::ca::application * papp, const char * pszLocale, const char * pszStyle)
   {
      return App(papp).get_locale_style_dir(pszLocale, pszStyle);
   }

   string dir::locale_style_matter(::ca::application * papp, const char * pszLocale, const char * pszStyle)
   {
      return path(votagus(), "app\\appmatter\\main", App(papp).get_locale_style_dir(pszLocale, pszStyle));
   }

   string dir::matter(::ca::application * papp, const char * psz, const char * psz2)
   {
      string strPath;
      strPath = path(locale_style_matter(papp), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, "en"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, "_std"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, NULL, App(papp).get_locale()), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, NULL, "en"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, NULL, "_std"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, "en", "en"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, "_std", "_std"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      strPath = path(locale_style_matter(papp, "se", "se"), psz, psz2);
      if(System.file().exists(strPath))
         return strPath;
      return path(locale_style_matter(papp), psz, psz2);
   }


   class ::ca::dir::system::path & dir::path()
   {
      return m_path;
   }


   bool dir::initialize()
   {
      xml::node node(get_app());
      node.load(Application.file().as_string(appdata("configuration\\directory.xml")));
      if(node.m_strName == "directory_configuration")
      {
         m_strTimeFolder = node.get_child_value("time");
         m_strNetSeedFolder = node.get_child_value("netseed");
      }
      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = appdata("time");
      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = ca2("net/netseed");
      mk(m_strTimeFolder);
      if(!is(m_strTimeFolder))
         return false;
      mk(path(m_strTimeFolder, "time"));
      return true;
   }

   string dir::trash_that_is_not_trash(const char * psz)
   {
      if(psz == NULL)
         return "";

      if(psz[1] == ':')
      {
         string strDir = name(psz);
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         class time time;
         time = time::get_current_time();
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if(strDir[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";
   }

   string dir::appdata(const char * lpcsz, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_COMMON_APPDATA,
         FALSE);
      string strRelative;
      strRelative = ca2();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
         int iFind1 = strRelative.reverse_find("\\", iFind);
         int iFind2 = strRelative.reverse_find("/", iFind);
         int iStart = max(iFind1 + 1, iFind2 + 1);
         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
      }
      return path(path(str, "ca2\\appdata", strRelative), lpcsz, lpcsz2);
   }

   string dir::usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
   {
      return path(appdata(lpcszPrefix), lpcsz, lpcsz2);
   }

   string dir::userappdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
   {
      return path(userfolder(papp, "appdata"), lpcsz, lpcsz2);
   }

   string dir::userdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
   {
      return path(userfolder(papp, "data"), lpcsz, lpcsz2);
   }

   string dir::userfolder(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
   {
      if(&AppUser(papp) == NULL)
      {
         string str;
         SHGetSpecialFolderPath(
            NULL,
            str,
            CSIDL_PROFILE,
            FALSE);
         return path(path(str, "ca2\\_____default"), lpcsz);
      }
      else
      {
         return path(AppUser(papp).m_strPath, lpcsz, lpcsz2);
      }
   }

   string dir::default_os_user_path_prefix(::ca::application * papp)
   {
      wchar_t buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }
      return gen::international::unicode_to_utf8(buf);
   }

   string dir::default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
   }

   string dir::default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "data"), pszRelativePath);
   }

   string dir::default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_APPDATA,
         FALSE);
      return path(path(str, "ca2\\user", lpcszPrefix), lpcszLogin, pszRelativePath);
   }

   string dir::userquicklaunch(::ca::application * papp, const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_APPDATA,
         FALSE);
      str = path(str, "Microsoft\\Internet Explorer\\Quick Launch");
      return path(str, lpcszRelativePath, lpcsz2);
   }

   string dir::userprograms(::ca::application * papp, const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_PROGRAMS,
         FALSE);
      return path(str, lpcszRelativePath, lpcsz2);
   }

   string dir::commonprograms(const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_COMMON_PROGRAMS,
         FALSE);
      return path(str, lpcszRelativePath, lpcsz2);
   }

   bool dir::is_inside_time(const char * pszPath)
   {
      return is_inside(time(), pszPath);
   }

   bool dir::is_inside(const char * pszDir, const char * pszPath)
   {
      return gen::str::begins_ci(pszDir, pszPath);
   }

   bool dir::has_subdir(const char * pszDir)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(path(pszDir, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(filefind.IsDirectory() && !filefind.IsDots())
         {
            return true;
         }
      }
      return false;
   }

} // namespace win
