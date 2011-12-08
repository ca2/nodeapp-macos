#include "StdAfx.h"


namespace win
{

   void PASCAL window::DeleteTempMap()
   {
      hwnd_map* pMap = AfxGetModuleState()->m_pmapHWND;
      if (gen::is_null(pMap))
         return;
      CSingleLock sl(&pMap->m_mutex, TRUE);

      raw_array < HWND > hwndaRemove;
      raw_array < ::win::window * > wndptraRemove;

      POSITION pos = pMap->m_temporaryMap.get_start_position();
      while (pos != NULL)
      {
         HANDLE h; // just used for asserts
         ::win::window * pTemp;
         pMap->m_temporaryMap.get_next_assoc(pos, h, pTemp);

         if(!::IsWindow((HWND) h))
         {
            hwndaRemove.add((HWND) h);
            wndptraRemove.add(pTemp);
         }

      }

      for(int i = 0; i < wndptraRemove.get_count(); i++)
      {
         wndptraRemove[i]->m_handlea[0] = NULL;
         wndptraRemove[i]->m_handlea[1] = NULL;

         (*pMap->m_pfnDestructObject)(wndptraRemove[i]);   // destruct the object
      }

      for(int i = 0; i < hwndaRemove.get_count(); i++)
      {
         pMap->m_temporaryMap.remove_key(hwndaRemove[i]);
      }

   }


   void PASCAL graphics::DeleteTempMap()
   {
      hdc_map* pMap = AfxGetModuleThreadState()->m_pCurrentWinThread->m_pmapHDC;
      pMap->delete_temp();
   }

   void PASCAL graphics_object::DeleteTempMap()
   {
      hgdiobj_map* pMap = AfxGetModuleThreadState()->m_pCurrentWinThread->m_pmapHGDIOBJ;
      pMap->delete_temp();
   }

} // namespace win
