#include "framework.h"


#ifndef WINDOWS
#include <sys/stat.h>
#include <ctype.h>
#endif


struct PROCESS_INFO_t
{
   string csProcess;
   uint32_t dwImageListIndex;
};


namespace mac
{
   
   
   file_system::file_system(base_application * papp) :
      element(papp)
   {
   }
   

   bool file_system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
   {
      string stra(lpszFilPathA);
      string wstrb(lpszFilPathB);
      
      //   ::str::international::ACPToUnicode(stra, lpszFilPathA);
      //   ::str::international::ACPToUnicode(wstrb, lpszFilPathB);
      if(stra == wstrb)
         return true;
      
      /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
       return false;
       if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
       return false;*/
      return stra == wstrb;
      
   }
   
   
   bool file_system::path::eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator)
   {
      
      strsize iLast = str.length() - 1;
      
      if(iLast < 0)
         return iLevelCount <= 0;
      
      while(str[iLast] == '/' || str[iLast] == '\\')
         iLast--;
      
      for(int32_t i = 0; i < iLevelCount; i++)
      {
         
         strsize iFind1 = str.reverse_find('/', iLast);
         
         strsize iFind2 = str.reverse_find('\\', iLast);
         
         strsize iFind = max(iFind1, iFind2);
         
         if(iFind >= iLast)
            return false;
         
         if(iFind < 0)
            return false;
         
         iLast = iFind;
         
         while(str[iLast] == '/' || str[iLast] == '\\')
            iLast--;
         
      }
      
      str.Truncate(iLast + 1);
      
      return true;
      
   }
   
   bool file_system::path::is_relative(const char * psz)
   {
      string strPath(psz);
      if(strPath.find(':') != -1 && strPath.find(':') < 10)
         return false;
      if(strPath.find('/') == 0 || strPath.find('\\') == 0)
         return false;
      return true;
   }
   
   void file_system::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
      bool bUrl = System.url().is_url(lpcsz);
#ifdef LINUX
      bool bLinux = true;
      str += "/";
#else
      bool bLinux = false;
#endif
      
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         str += stra[i];
         if(stra[i].find('/') < 0 && stra[i].find('\\') < 0)
         {
            str += "\\";
         }
         if(bUrl || bLinux)
         {
            str.replace("\\", "/");
         }
         else
         {
            str.replace("/", "\\");
         }
         straParam.add(str);
      }
   }
   
   void file_system::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {
      stringa straSeparator;
      straSeparator.add("/");
      straSeparator.add("\\");
      straParam.add_smallest_tokens(lpcsz, straSeparator, FALSE);
      if(straParam.get_count() > 0)
      {
         strsize iFind = straParam[0].find(':');
         if(iFind >= 2)
         {
            straParam[0] += "//";
         }
         else if(iFind == 1)
         {
            straParam[0] += "\\";
         }
      }
   }
   
   var file_system::length(const char * pszPath)
   {
      
      var varRet;
      
#ifdef WINDOWS
      
      WIN32_FILE_ATTRIBUTE_DATA data;
      
      if(!GetFileAttributesExW(::str::international::utf8_to_unicode(pszPath), GetFileExInfoStandard, &data))
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = (uint32_t) data.nFileSizeLow;
      }
      
#else
      
      struct stat stat;
      
      if(::stat(pszPath, &stat)  == -1)
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = stat.st_size;
      }
      
#endif
      
      return varRet;
      
   }
   
   
   string file_system::time_square(base_application * papp, const char * pszPrefix, const char * pszSuffix)
   {
      string str;
      System.dir().time_square(str);
      return time(papp, str, 25, pszPrefix, pszSuffix);
   }
   
   string file_system::time_log(base_application * papp, const char * pszId)
   {
      return time(papp, System.dir().time_log(pszId), 9);
   }
   
   string file_system::time(base_application * papp, const char * psz, int32_t iMaxLevel, const char * pszPrefix, const char * pszSuffix)
   {
      single_lock lockMachineEvent(
                                  (&System.machine_event_central() != NULL) ?
                                  &System.machine_event_central().m_machineevent.m_mutex
                                  : ((mutex *) NULL), true);
      int32_t iIncLevel = -1;
      string str;
      string strPrefix(pszPrefix);
      string strSuffix(pszSuffix);
   restart:
      str.Empty();
      str = psz;
      System.dir().mk(str, papp);
      stringa straTitle;
      string strFormat;
      for(int32_t i = 1; i <= iMaxLevel;)
      {
         System.dir().mk(str, papp);
         if(!System.dir().is(str, papp))
            throw "time square dir does not exist";
         straTitle.remove_all();
         System.dir().ls(papp, str, NULL, &straTitle);
         if(i < iMaxLevel)
         {
            int32_t iMax = filterex_time_square("", straTitle);
            if(iMax == -1)
            {
               str = System.dir().path(str, "00");
               System.dir().mk(str, papp);
            }
            else if(iMax == 99)
            {
               iIncLevel = i - 1;
               goto restart;
            }
            else
            {
               if(i == iIncLevel)
               {
                  iMax++;
               }
               strFormat.Format("%02d", iMax);
               str = System.dir().path(str, strFormat);
               if(i == iIncLevel)
               {
                  System.dir().mk(str, papp);
               }
            }
            i++;
         }
         else // if i == iMaxLevel
         {
            System.dir().ls(papp, str, NULL, &straTitle);
            int32_t iMax = filterex_time_square(pszPrefix, straTitle);
            if(iMax == -1)
            {
               str = System.dir().path(str, strPrefix+"00"+strSuffix);
               if(file_system::mk_time(str))
                  break;
            }
            else if(iMax == 99)
            {
               iIncLevel = iMaxLevel - 1;
               goto restart;
            }
            else
            {
               iMax++;
               strFormat.Format("%02d", iMax);
               str = System.dir().path(str, strPrefix+strFormat+strSuffix);
               if(file_system::mk_time(str))
                  break;
            }
            return "";
         }
      }
      return str;
   }
   
   int32_t file_system::filterex_time_square(const char * pszPrefix, stringa & stra)
   {
      int32_t iMax = -1;
      int32_t iIndex;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string str = stra[i];
         if(::str::begins_eat_ci(str, pszPrefix))
         {
            if(str.get_length() < 2)
            {
               stra.remove_at(i);
               i--;
               continue;
            }
            if(!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
            {
               stra.remove_at(i);
               i--;
               continue;
            }
            iIndex = atoi(str.Mid(0, 2));
            if(iIndex > iMax)
               iMax = iIndex;
         }
      }
      return iMax;
   }
   
   // fail if exists, create if not exists
   bool file_system::mk_time(const char * lpcszCandidate)
   {
      ::file::binary_buffer_sp spfile(allocer());
      if(System.file().exists(lpcszCandidate, get_app()))
         return false;
      try
      {
         if(!spfile->open(lpcszCandidate, ::file::mode_create | ::file::type_binary))
            return false;
      }
      catch(...)
      {
         return false;
      }
      return true;
   }
   
   string file_system::as_string(var varFile, base_application * papp)
   {
      var varQuery;
      return as_string(varFile, varQuery, papp);
   }
   
   string file_system::as_string(var varFile, var & varQuery, base_application * papp)
   {
      primitive::memory storage;
      if(varFile.cast < ::file::reader > () != NULL)
      {
         storage.transfer_from(*varFile.cast < ::file::reader >());
      }
      else
      {
         string strFilePath(varFile);
         if(papp->m_pplaneapp->m_bZipIsDir && (::str::find_ci(".zip:", strFilePath) >= 0))
         {
            ::file::memory_buffer memfile(papp, &storage);
            zip::InFile infile(get_app());
            if(!infile.unzip_open(strFilePath, 0))
               return "";
            if(!infile.dump(&memfile))
               return "";
         }
         else if(::str::begins_eat_ci(strFilePath, "file:///"))
         {
            as_memory(strFilePath, storage, papp);
         }
         else if(::str::begins_eat_ci(strFilePath, "file:\\\\\\"))
         {
            as_memory(strFilePath, storage, papp);
         }
         else if(::str::begins_ci(strFilePath, "http://")
                 || ::str::begins_ci(strFilePath, "https://"))
         {
            
            if(varQuery.has_property("in_headers"))
            {
            
               varQuery["headers"] = varQuery["in_headers"].propset();
               
            }
            
            varQuery.propset().set_app(papp);

            if(strFilePath.contains("/matter.ca2.cc/") || strFilePath.contains(".matter.ca2.cc/"))
            {
            
               try
               {
               
                  storage.transfer_from(*App(papp).file().get_file(strFilePath, ::file::type_binary | ::file::mode_read));
               
               }
               catch(...)
               {
               
               }
               
            }
            else
            {
               
               App(papp).http().get(strFilePath, storage, varQuery.propset());
               
            }
            
            varQuery["out_headers"] = varQuery["get_headers"];
            
         }
         else
         {
         
            as_memory(strFilePath, storage, papp);
            
         }
         
      }
      
      string strResult;
      
      if(storage.get_size() >= 2
         && storage.get_data()[0] == 255
         && storage.get_data()[1] == 60)
      {
         ::str::international::unicode_to_utf8(strResult, (const wchar_t *) &storage.get_data()[2], (int32_t)(storage.get_size() - 2));
      }
      else if(storage.get_size() >= 3
              && storage.get_data()[0] == 0xef
              && storage.get_data()[1] == 0xbb
              && storage.get_data()[2] == 0xbf)
      {
         strResult = string((const char *) (const wchar_t *) &storage.get_data()[3], (int32_t) (storage.get_size() - 3));
      }
      else
      {
         strResult = string((const char *) storage.get_data(), (int32_t) storage.get_size());
      }
      
      return strResult;
   }
   
   void file_system::as_memory(var varFile, primitive::memory_base & mem, base_application * papp)
   {
      
      mem.allocate(0);
      
      if(varFile.get_type() == var::type_string)
      {
         
         string strPath = varFile.get_string();
         
         if(strPath.is_empty())
         {
            
            TRACE("::file::file_system::as_memory varFile is a empty file name!!");
            
            return;
            
         }
         
         strPath.trim("\"'");
         
         if((::str::begins(strPath, "http://") || ::str::begins(strPath, "https://")))
         {
         
            property_set set(papp);
            
            App(papp).http().get(strPath, mem, set);
            
            return;
            
         }
         
      }
      
      ::file::buffer_sp spfile;
      
      try
      {
         
         spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);
         
         mem.transfer_from(*spfile);
         
      }
      catch(...)
      {
      }
      
      
      
   }
   
   void file_system::lines(stringa & stra, var varFile, base_application * papp)
   {
      
      UNREFERENCED_PARAMETER(papp);
      
      ::file::text_buffer_sp spfile(allocer());
      
      try
      {
         if(!spfile->open(varFile, ::file::type_text | ::file::mode_read))
         {
            return;
         }
      }
      catch(...)
      {
         return;
      }
      string strLine;
      while(spfile->read_string(strLine))
      {
         stra.add(strLine);
      }
      
   }
   
   bool file_system::put_contents(var varFile, const void * pvoidContents, count count, base_application * papp)
   {
      
      ::file::buffer_sp spfile;
      
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      
      if(spfile.is_null())
         return false;
      
      spfile->write(pvoidContents, count);
      
      return true;
      
   }
   
   bool file_system::put_contents(var varFile, const char * lpcszContents, base_application * papp)
   {
      if(lpcszContents == NULL)
      {
         return put_contents(varFile, "", 0, papp);
      }
      else
      {
         return put_contents(varFile, lpcszContents, strlen(lpcszContents), papp);
      }
   }
   
   bool file_system::put_contents(var varFile, ::file::reader & reader, base_application * papp)
   {
      ::file::buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      primitive::memory mem;
      mem.allocate(1024 * 1024 * 8);
      ::primitive::memory_size uiRead;
      while((uiRead = reader.read(mem.get_data(), mem.get_size())) > 0)
      {
         spfile->write(mem.get_data(), uiRead);
      }
      return true;
   }
   
   bool file_system::put_contents(var varFile, primitive::memory & mem, base_application * papp)
   {
      return put_contents(varFile, mem.get_data(), (count) mem.get_size(), papp);
   }
   
   bool file_system::put_contents_utf8(var varFile, const char * lpcszContents, base_application * papp)
   {
      ::file::buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      
      string str("\xef\xbb\xbf");
      spfile->write(str, str.length());
      
      spfile->write(lpcszContents, strlen(lpcszContents));
      return true;
   }
   
   void file_system::path::split(stringa & stra, const char * lpcszPath)
   {
      stringa straSeparator;
      straSeparator.add("\\");
      straSeparator.add("/");
      stra.add_smallest_tokens(lpcszPath, straSeparator, FALSE);
   }
   
   class file_system::path & file_system::path()
   {
      return m_path;
   }
   

   string file_system::title_(const char * path)
   {
      
      string str = name_(path);
      
      strsize iPos = str.reverse_find('.');
      
      if(iPos >= 0)
      {
         return str.Mid(0, iPos);
      }
      else
      {
         return str;
      }
      
   }
   
   
   string file_system::name_(const char * path)
   {
      
      string str(path);
      
      while(::str::ends_eat(str, "\\"));
      
      while(::str::ends_eat(str, "/"));
      
      strsize iPos;
      
      strsize iPos1 = str.reverse_find('\\');
      
      strsize iPos2 = str.reverse_find('/');
      
      if(iPos1 >= 0 && iPos2 >= 0)
      {
         
         if(iPos1 > iPos2)
         {
            
            iPos = iPos1 + 1;
            
         }
         else
         {
            
            iPos = iPos2 + 1;
            
         }
         
      }
      else if(iPos1 >= 0)
      {
         
         iPos = iPos1 + 1;
         
      }
      else if(iPos2 >= 0)
      {
         
         iPos = iPos2 + 1;
         
      }
      else
      {
         
         iPos = 0;
         
      }
      
      return str.Mid(iPos);
      
   }
   
   string file_system::extension(const char * path)
   {
      
      string str = name_(path);
      
      strsize iPos = str.reverse_find('.');
      
      if(iPos >= 0)
      {
         
         return str.Mid(iPos + 1);
         
      }
      else
      {
         
         return "";
         
      }
      
   }
   
   void file_system::copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, base_application * papp)
   {
      if(bFailIfExists)
      {
         if(exists(pszNew, papp))
            throw "Failed to copy file";
      }
      if(System.dir().is(psz, papp) && (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(psz, ".zip"))))
      {
         stringa straPath;
         System.dir().rls(papp, psz, &straPath);
         string strDst;
         string strSrc;
         string strDirSrc(psz);
         string strDirDst(pszNew);
         if(papp->m_pplaneapp->m_bZipIsDir && (::str::ends(strDirSrc, ".zip")))
         {
            strDirSrc += ":";
         }
         for(int32_t i = 0; i < straPath.get_size(); i++)
         {
            strSrc = straPath[i];
            strDst = strSrc;
            ::str::begins_eat_ci(strDst, strDirSrc);
            strDst = System.dir().path(strDirDst, strDst);
            if(System.dir().is(strSrc, papp))
            {
               if((eextract == extract_first || eextract == extract_none) && (::str::ends_ci(psz, ".zip")))
               {
               }
               else
               {
                  System.dir().mk(strDst, papp);
               }
            }
            else
            {
               if(!System.dir().is(System.dir().name(strDst), papp))
               {
                  System.dir().mk(System.dir().name(strDst), papp);
               }
               copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none, papp);
            }
         }
      }
      else
      {
         
         string strNew;
         
         if(System.dir().is(pszNew, papp))
         {
            strNew = System.dir().path(pszNew, name_(psz));
         }
         else
         {
            strNew = pszNew;
         }
         
         ::file::buffer_sp ofile;
         ofile = App(papp).file().get_file(strNew, ::file::mode_write | ::file::type_binary | ::file::mode_create | ::file::defer_create_directory | ::file::share_deny_write);
         if(ofile.is_null())
         {
            string strError;
            strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", psz, pszNew, bFailIfExists);
            throw strError;
         }
         
         ::file::buffer_sp ifile;
         ifile = App(papp).file().get_file(psz, ::file::mode_read | ::file::type_binary | ::file::share_deny_none);
         if(ifile.is_null())
         {
            string strError;
            strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", psz, pszNew, bFailIfExists);
            throw strError;
         }
         
         ::file::output_stream ostream(ofile);
         
         ::file::input_stream istream(ifile);
         
         System.compress().null(ostream, istream);
         
         
         
         bool bOutputFail = false;
         bool bInputFail = false;
         try
         {
            ofile->close();
         }
         catch(...)
         {
            bOutputFail = true;
         }
         
         ::file::file_status st;
         
         ifile->GetStatus(st);
         
         System.os().set_file_status(strNew, st);
         
         try
         {
            ifile->close();
         }
         catch(...)
         {
            bInputFail = true;
         }
         if(bInputFail)
         {
            if(bOutputFail)
            {
               string strError;
               strError.Format("During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d", psz, pszNew, bFailIfExists);
               throw strError;
            }
            else
            {
               string strError;
               strError.Format("During copy, failed to close input file \"%s\" bFailIfExists=%d", psz, bFailIfExists);
               throw strError;
            }
         }
         else if(bOutputFail)
         {
            string strError;
            strError.Format("During copy, failed to close output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);
            throw strError;
         }
         
      }
      
   }
   
   void file_system::move(const char * pszNew, const char * psz)
   {
#ifdef WINDOWSEX
      if(!::MoveFileW(
                      ::str::international::utf8_to_unicode(psz),
                      ::str::international::utf8_to_unicode(pszNew)))
      {
         uint32_t dwError = ::GetLastError();
         string strError;
         strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
         throw strError;
      }
#elif defined(METROWIN)
      
      ::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, NULL, OPEN_EXISTING, 0, NULL);
      
      if(file == nullptr)
         throw "file::file_system::move Could not move file, could not open source file";
      
      string strDirOld     = System.dir().name(psz);
      string strDirNew     = System.dir().name(pszNew);
      string strNameOld    = System.file().name_(psz);
      string strNameNew    = System.file().name_(pszNew);
      
      if(strDirOld == strDirNew)
      {
         if(strNameOld == strNameNew)
         {
            return;
         }
         else
         {
            ::wait(file->RenameAsync(strNameNew));
         }
      }
      else
      {
         ::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
         if(strNameOld == strNameNew)
         {
            ::wait(file->MoveAsync(folder));
         }
         else
         {
            ::wait(file->MoveAsync(folder, strNameNew));
         }
      }
      
      
#else
      if(rename(psz, pszNew) != 0)
      {
         int32_t err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         throw strError;
      }
#endif
   }
   
   void file_system::del(const char * psz)
   {
#ifdef WINDOWS
      if(!::DeleteFileW(
                        ::str::international::utf8_to_unicode(psz)))
      {
         uint32_t dwError = ::GetLastError();
         if(dwError == 2) // the file does not exist, so delete "failed"
            return;
         string strError;
         strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
         throw strError;
      }
#else
      if(remove(psz) != 0)
      {
         int32_t err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         throw strError;
      }
#endif
      
   }
   
   
   string file_system::copy(const char * psz, base_application * papp)
   {
      string strCopy("copy");
      string strNew;
      if(System.dir().is(psz, papp))
      {
         int32_t i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d", psz, strCopy.c_str(), i);
            if(!exists(strNew, papp))
            {
               copy(strNew, psz, false, extract_all, papp);
               return strNew;
            }
            i++;
         }
      }
      else
      {
         string strExt = extension(psz);
         if(!strExt.is_empty())
         {
            strExt = "-" + strExt;
         }
         int32_t i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d%s", psz, strCopy.c_str(), i, strExt.c_str());
            if(!exists(strNew, papp))
            {
               copy(strNew, psz, false, extract_all, papp);
               return strNew;
            }
            i++;
         }
      }
      return "";
   }
   
   
   bool file_system::exists(const char * pszPath, base_application * papp)
   {
      
      if(::str::begins_ci_iws(pszPath, "uifs://"))
      {
         return AppUser(papp).m_pifs->file_exists(pszPath);
      }
      else if(::str::begins_ci_iws(pszPath, "http://") || ::str::begins_ci_iws(pszPath, "https://"))
      {
      
         property_set set(papp);
      
         return App(papp).http().exists(pszPath, set);
         
      }
      
      if(papp->m_pplaneapp->m_bZipIsDir)
      {
         
         strsize iFind = ::str::find_ci(".zip:", pszPath);
         
         zip::Util ziputil;
         
         if(iFind >= 0)
            return ziputil.exists(papp, pszPath);
         
         if(!Sys(papp).dir().name_is(pszPath, papp))
            return false;
         
      }
      
#ifdef WINDOWS
      
      
      return file_exists_dup(pszPath);
      
      //return ::GetFileAttributesW(::str::international::utf8_to_unicode(pszPath)) != INVALID_FILE_ATTRIBUTES;
      
#else
      
      struct stat st;
      
      if(stat(pszPath, &st) != 0)
         return false;
      
      return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);
      
#endif
      
   }
   
   
   bool file_system::exists(const string & strPath, base_application * papp)
   {
      
      if(::str::begins_ci_iws(strPath, "uifs://"))
      {
         return AppUser(papp).m_pifs->file_exists(strPath);
      }
      
      if(::str::begins_ci_iws(strPath, "http://")
         || ::str::begins_ci_iws(strPath, "https://"))
      {
      
         property_set set(papp);
      
         return App(papp).http().exists(strPath, set);
         
      }
      
      
      if(papp->m_pplaneapp->m_bZipIsDir)
      {
         
         strsize iFind = ::str::find_ci(".zip:", strPath);
         
         zip::Util ziputil;
         
         if(iFind >= 0)
         {
            
            if(!exists(strPath.Mid(0, iFind + 4), papp))
               return false;
            
            return ziputil.exists(papp, strPath);
            
         }
         
         
      }
      
      //if(!papp->m_psystem->dir().name_is(strPath, papp))
      // return false;
      
#ifdef WINDOWS
      
      
      return file_exists_dup(strPath);
      // return true;
      
      //return App(papp).m_spfsdata->file_exists(strPath);
      //return ::GetFileAttributesW(::str::international::utf8_to_unicode(strPath)) != INVALID_FILE_ATTRIBUTES;
      
#else
      
      struct stat st;
      
      if(stat(strPath, &st) != 0)
         return false;
      
      return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);
      
#endif
      
   }
   
   string file_system::paste(const char * pszLocation, const char * path, base_application * papp)
   {
      string strDir = System.dir().name(path);
      string strDest = System.dir().path(pszLocation, "");
      string strSrc = System.dir().path(strDir, "");
      if(strDest == strSrc)
      {
         return copy(path, papp);
      }
      else
      {
         string strNew = System.dir().path(strDest, name_(path));
         copy(strNew, path, false, extract_all, papp);
         return strNew;
      }
   }
   
   void file_system::trash_that_is_not_trash(stringa & stra, base_application * papp)
   {
      
      if(stra.get_size() <= 0)
         return;
      
      string strDir = System.dir().trash_that_is_not_trash(stra[0]);
      
      System.dir().mk(strDir, papp);
      
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
#ifdef WINDOWS
         move(System.dir().path(strDir, name_(stra[i])), stra[i]);
#else
         ::rename(stra[i], System.dir().path(strDir, name_(stra[i])));
#endif
      }
      
   }
   
   void file_system::trash_that_is_not_trash(const char * psz, base_application * papp)
   {
      
      string strDir = System.dir().trash_that_is_not_trash(psz);
      
      System.dir().mk(strDir, papp);
      
#ifdef WINDOWS
      //         ::MoveFile(psz, System.dir().path(strDir, name_(psz)));
      move(System.dir().path(strDir, name_(psz)), psz);
#else
      ::rename(psz, System.dir().path(strDir, name_(psz)));
#endif
      
   }
   
   void file_system::replace(const char * pszContext, const char * pszFind, const char * pszReplace, base_application * papp)
   {
      stringa straTitle;
      System.dir().ls(papp, pszContext, NULL, &straTitle);
      string strOld;
      string strNew;
      for(int32_t i = 0; i < straTitle.get_size(); i++)
      {
         strOld = straTitle[i];
         strNew = strOld;
         strNew.replace(pszFind, pszReplace);
         if(strNew != strOld)
         {
#ifdef WINDOWS
            //               ::MoveFileW(
            //                ::str::international::utf8_to_unicode(System.dir().path(pszContext, strOld)),
            //              ::str::international::utf8_to_unicode(System.dir().path(pszContext, strNew)));
            move(System.dir().path(pszContext, strNew), System.dir().path(pszContext, strOld));
#else
            ::rename(
                     System.dir().path(pszContext, strOld),
                     System.dir().path(pszContext, strNew));
#endif
         }
      }
   }
   
   bool file_system::is_read_only(const char * psz)
   {
      
#ifdef WINDOWSEX
      
      uint32_t dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(psz));
      if(dwAttrib & FILE_ATTRIBUTE_READONLY)
         return true;
      return false;
      
#elif defined(METROWIN)
      
      throw todo(get_app());
      
#else
      
      struct stat st;
      
      if(stat(psz, &st) != 0)
         return true;
      
      return !(st.st_mode & S_IWUSR);
      
#endif
      
   }
   
   string file_system::sys_temp(const char * pszName, const char * pszExtension, base_application * papp)
   {
      
      string strTempDir = get_sys_temp_path();
      
      if(!::str::ends(strTempDir, "\\") && !::str::ends(strTempDir, "/"))
      {
         
         strTempDir += "\\";
         
      }
      
      string str;
      
      char buf[30];
      
      for(int32_t i = 0; i < 1000; i++)
      {
         
         sprintf(buf, "%d", i);
         
         str = strTempDir;
         str += pszName;
         str += "-";
         str += buf;
         str += ".";
         str += pszExtension;
         if(!exists(str, papp))
            return str;
      }
      
      return "";
      
   }
   
   string file_system::sys_temp_unique(const char * pszName)
   {
      
      return System.dir().path(get_sys_temp_path(), pszName);
      
   }
   
   ::file::buffer_sp file_system::time_square_file(base_application * papp, const char * pszPrefix, const char * pszSuffix)
   {
      
      return get(time_square(papp, pszPrefix, pszSuffix), papp);
      
   }
   
   ::file::buffer_sp file_system::get(const char * name, base_application * papp)
   {
      
      System.dir().mk(System.dir().name(name), papp);
      
      ::file::buffer_sp fileOut = App(papp).file().get_file(name, ::file::mode_create | ::file::type_binary | ::file::mode_write);
      
      if(fileOut.is_null())
         throw ::file::exception(papp, -1, ::file::exception::none, name);
      
      return fileOut;
      
   }
   
   string file_system::replace_extension(const char * pszFile, const char * pszExtension)
   {
      string strFile(pszFile);
      set_extension(strFile, pszExtension);
      return strFile;
   }
   
   void file_system::set_extension(string & strFile, const char * pszExtension)
   {
      strsize iEnd = strFile.reverse_find('.');
      if(iEnd < 0)
         iEnd = strFile.get_length();
      strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");
   }
   

} // namespace mac






