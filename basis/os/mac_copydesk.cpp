#include "framework.h"


namespace mac
{


   copydesk::copydesk(base_application * papp) :
      element(papp),
      ::core::copydesk(papp),
      window_sp(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {
   
      if(m_p == NULL)
         return 0;
   
      if(!m_p->OpenClipboard())
         return 0;
      int32_t iCount = 0;
      throw todo(get_app());
      /* xxx HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      if(hdrop != NULL)
      {
         iCount = ::DragQueryFile(hdrop , 0xFFFFFFFF, NULL, 0);
      }
      ::CloseClipboard(); */
      return iCount;
   }


   void copydesk::get_filea(stringa & stra)
   {
      int32_t iCount = get_file_count();
      if(iCount <= 0)
         return;
      if(!m_p->OpenClipboard())
         return;
      throw todo(get_app());
      /* HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      string str;
      for(int32_t i = 0; i < iCount; i++)
      {
         UINT uiLen = ::DragQueryFileW(hdrop, i, NULL, 0);
         wchar_t * lpwsz = (wchar_t *) malloc(sizeof(wchar_t) * (uiLen + 1));
         ::DragQueryFileW(hdrop, i, lpwsz, uiLen + 1);
         stra.add(::str::international::unicode_to_utf8(lpwsz));
         free(lpwsz);
      }
      ::CloseClipboard();
      */
   }

   void copydesk::set_filea(stringa & stra)
   {

      ASSERT(m_p->IsWindow());

      strsize iLen = 0;

      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         iLen += ::str::international::utf8_to_unicode_count(stra[i]) + 1;
      }

      throw todo(get_app());

/* xxx

      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
      LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglbCopy);
      pDropFiles->pFiles = sizeof(DROPFILES);
      pDropFiles->pt.x = pDropFiles->pt.y = 0;
      pDropFiles->fNC = TRUE;
      pDropFiles->fWide = TRUE; // ANSI charset

      ASSERT(m_p->IsWindow());
      LPTSTR lptstrCopy = (char *) pDropFiles;
      lptstrCopy += pDropFiles->pFiles;
      wchar_t * lpwstrCopy = (wchar_t *) lptstrCopy;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         ASSERT(m_p->IsWindow());
         ::str::international::utf8_to_unicode(lpwstrCopy, ::str::international::utf8_to_unicode_count(stra[i]) + 1, stra[i]);
         ASSERT(m_p->IsWindow());
         lpwstrCopy += (stra[i].get_length() + 1);
      }
      ASSERT(m_p->IsWindow());
      *lpwstrCopy = '\0';    // null character
      ASSERT(m_p->IsWindow());
      ::GlobalUnlock(hglbCopy);
      ASSERT(m_p->IsWindow());
      if(!m_p->OpenClipboard())
      {
         ::GlobalFree(hglbCopy);
         return;
      }
      EmptyClipboard();
      SetClipboardData(CF_HDROP, hglbCopy);
      VERIFY(::CloseClipboard());

*/

   }



   bool copydesk::initialize()
   {

      if(!::core::copydesk::initialize())
         return false;

  //    if(!m_p->CreateEx(0, System.RegisterWndClass(0), NULL, 0, rect(0, 0, 0, 0), NULL, id()))
    //     return false;

//      if(!m_p->CreateEx(0, NULL, NULL, 0, rect(0, 0, 0, 0), NULL, id()))
  //       return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;

      bOk = ::core::copydesk::finalize();

      if(window_sp::is_set() && window_sp::m_p->IsWindow())
      {
         bOk = window_sp::m_p->DestroyWindow() != FALSE;
      }
      else
      {
         bOk = false;
      }

      return bOk;

   }

   void copydesk::set_plain_text(const char * psz)
   {
      ASSERT(m_p->IsWindow());
   //   int32_t iLen = 0;

      string str;
      str = ::str::international::utf8_to_unicode(psz);



      ASSERT(m_p->IsWindow());
      if(!m_p->OpenClipboard())
      {
         return;
      }

      throw todo(get_app());

/*

      EmptyClipboard();


      count iCount = ::str::international::utf8_to_unicode_count(str) + 1;
      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iCount * sizeof(WCHAR));
      wchar_t * lpwstrCopy  = (wchar_t *) ::GlobalLock(hglbCopy);
      ::str::international::utf8_to_unicode(lpwstrCopy, iCount, str);
      ::GlobalUnlock(hglbCopy);

      HGLOBAL hglbCopy2 = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(CHAR) * (strlen(psz) + 1));
      char * lpstrCopy  = (char *) ::GlobalLock(hglbCopy2);
      strcpy(lpstrCopy, psz);
      ::GlobalUnlock(hglbCopy2);


      SetClipboardData(CF_UNICODETEXT, hglbCopy);
      SetClipboardData(CF_TEXT, hglbCopy2);
      VERIFY(::CloseClipboard());

*/

   }


   string copydesk::get_plain_text()
   {
      throw todo(get_app());
      return "";
/* xxx
      if (IsClipboardFormatAvailable(CF_UNICODETEXT))
      {
         if(!m_p->OpenClipboard())
            return "";
         HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
         string str(::str::international::unicode_to_utf8((const wchar_t *) GlobalLock(hglb)));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else if (IsClipboardFormatAvailable(CF_TEXT))
      {
         if(!m_p->OpenClipboard())
            return "";
         HGLOBAL hglb = GetClipboardData(CF_TEXT);
         string str((char *) GlobalLock(hglb));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else
      {
         return "";
      }
*/
   }

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {
      if(!m_p->OpenClipboard())
         return false;
      bool bOk = false;
      throw todo(get_app());
/* xxx
      HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
      try
      {
         ::draw2d::bitmap_sp bitmap(get_app());
         bitmap->Attach(hbitmap);
         //HDC hdc = ::CreateCompatibleDC(NULL);
         //::draw2d::graphics_sp g(get_app());
         //g->Attach(hdc);
         //::draw2d::graphics * pgraphics = Application.graphics_from_os_data(hdc);
         //g->SelectObject(hbitmap);
       //  BITMAP bm;
         //::GetObjectA(hbitmap, sizeof(bm), &bm);
         //if(!pdib->create(bm.bmWidth, bm.bmHeight))
           // return false;
         ::draw2d::graphics_sp g(get_app());
         g->SelectObject(bitmap);
         size sz = bitmap->GetBitmapDimension();
         if(pdib->create(sz))
         {
            bOk = pdib->get_graphics()->BitBlt(0, 0, sz.cx, sz.cy, g, 0, 0, SRCCOPY) != FALSE;
         }
      }
      catch(...)
      {
      }
      ::DeleteObject((HGDIOBJ) hbitmap);
      //::DeleteDC(hdc);
      ::CloseClipboard();

*/

      return bOk;
   }


} // namespace mac


