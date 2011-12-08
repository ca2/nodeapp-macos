#include "StdAfx.h"

#undef USERNAME_LENGTH // mysql one

#include <Wtsapi32.h>
#include <Psapi.h>

namespace win
{
   osi::osi(::ca::application * papp) :
      ca(papp)
   {
   }

   bool osi::shutdown(bool bIfPowerOff)
   {
      bool retval = true;
      HANDLE hToken;
      TOKEN_PRIVILEGES tkp;
      if (!OpenProcessToken(GetCurrentProcess(),
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      if (bIfPowerOff)
         retval = ExitWindowsEx(EWX_POWEROFF, 0) != FALSE;
      else
         retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != FALSE;

      //reset the previlages
      tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      return retval;
   }

   bool osi::reboot()
   {
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;
   if (!OpenProcessToken(GetCurrentProcess(),
      TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return false;
   if(!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
   {
      TRACELASTERROR();
      return false;
   }
   tkp.PrivilegeCount = 1;
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
   {
      TRACELASTERROR();
      return false;
   }
   if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
   {
      return false;
   }
   if(!LookupPrivilegeValue(NULL, SE_REMOTE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
   {
      TRACELASTERROR();
      return false;
   }
   tkp.PrivilegeCount = 1;
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
   {
      TRACELASTERROR();
      return false;
   }
   if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
   {
      return false;
   }


   if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE, WTS_WSD_REBOOT))
   {
      TRACELASTERROR();
      return false;
   }
   /*if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
      SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
   {
      DWORD dwLastError = ::GetLastError();
      return false;
   }*/
   //reset the previlages
   tkp.Privileges[0].Attributes = 0;
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
   return true;
   }

   void osi::terminate_processes_by_title(const char * pszName)
   {
      DWORD dwPid;
      while(get_pid_by_title(pszName, dwPid))
      {
         HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                      PROCESS_VM_READ,
                                      FALSE, dwPid );
         TerminateProcess(hProcess, (UINT) -1);
         CloseHandle(hProcess);
  /*::EnumWindows((WNDENUMPROC)
            CKillProcessHelper::TerminateAppEnum,
            (LPARAM) dwId);
        // Wait on the handle. If it signals, great.

        //If it times out, then you kill it.

        if(WaitForSingleObject(hProcess, 5000)
            !=WAIT_OBJECT_0)
            bResult = TerminateProcess(hProcess,0);
        else
            bResult = TRUE;
        CloseHandle(hProcess);
        return bResult == TRUE;*/

      }
   }

   bool osi::get_pid_by_path(const char * pszName, DWORD & dwPid)
   {
      dword_array dwa;
      get_all_processes(dwa);
      for(int i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).CompareNoCase(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   bool osi::get_pid_by_title(const char * pszName, DWORD & dwPid)
   {
      dword_array dwa;
      get_all_processes(dwa);
      for(int i = 0; i < dwa.get_count(); i++)
      {
         if(System.file().title_(get_process_path(dwa[i]))
            .CompareNoCase(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   string osi::get_process_path(DWORD dwPid)
   {
      string strName = ":<unknown>";
      // get a handle to the process.
      HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, dwPid );

      // get the process name.

      if (NULL != hProcess )
      {
         HMODULE hMod;
         DWORD cbNeeded;

         if(EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
         {
            strName = get_module_path(hMod);
         }
      }

      CloseHandle( hProcess );
      return strName;
   }

   void osi::get_all_processes(dword_array & dwa )
   {
      dwa.set_size(0);
      DWORD cbNeeded = 0;
      while(cbNeeded == natural(dwa.get_count()))
      {
         dwa.set_size(dwa.get_count() + 1024);
         if(!EnumProcesses(
            dwa.get_data(),
            dwa.get_count() * sizeof(DWORD),
            &cbNeeded))
         {
            return;
         }
         dwa.set_size(cbNeeded / sizeof(DWORD));
      }
   }

   string osi::get_module_path(HMODULE hmodule)
   {
      string strPath;
      DWORD dwSize = 1;
      while(natural(strPath.get_length() + 1) == dwSize)
      {
         dwSize = ::GetModuleFileName(
                     hmodule,
                     strPath.GetBufferSetLength(dwSize + 1024),
                     (dwSize + 1024));
         strPath.ReleaseBuffer();
      }
      return strPath;
   }

} // namespace win
