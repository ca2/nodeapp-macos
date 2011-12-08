#include "StdAfx.h"

namespace win
{

   brush::brush(::ca::application * papp) :
      ca(papp)
   { 
   }

   brush::~brush()
   { 
   }

   // brush
    brush::operator HBRUSH() const
   { 
      return (HBRUSH)(this == NULL ? NULL : get_os_data()); 
   }
    brush* PASCAL brush::from_handle(::ca::application * papp, HBRUSH hBrush)
   {
      return dynamic_cast < brush * > (::win::graphics_object::from_handle(papp, hBrush));
   }
    BOOL brush::CreateSolidBrush(COLORREF crColor)
      { return Attach(::CreateSolidBrush(crColor)); }
    BOOL brush::CreateHatchBrush(int nIndex, COLORREF crColor)
      { return Attach(::CreateHatchBrush(nIndex, crColor)); }
    BOOL brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
      { return Attach(::CreateBrushIndirect(lpLogBrush)); }
    BOOL brush::CreatePatternBrush(::ca::bitmap* pBitmap)
      { return Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())); }
    BOOL brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
      { return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage)); }
    BOOL brush::CreateSysColorBrush(int nIndex)
      { return Attach(::GetSysColorBrush(nIndex)); }
    int brush::GetLogBrush(LOGBRUSH* pLogBrush)
      { ASSERT(get_os_data() != NULL);
         return ::GetObject(get_os_data(), sizeof(LOGBRUSH), pLogBrush); }

      /////////////////////////////////////////////////////////////////////////////
      // brush

      void brush::construct(COLORREF crColor)
      {
         if (!Attach(::CreateSolidBrush(crColor)))
            AfxThrowResourceException();
      }

      void brush::construct(int nIndex, COLORREF crColor)
      {
         if (!Attach(::CreateHatchBrush(nIndex, crColor)))
            AfxThrowResourceException();
      }

      void brush::construct(::ca::bitmap* pBitmap)
      {
         ASSERT_VALID(pBitmap);

         if (!Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())))
            AfxThrowResourceException();
      }

      BOOL brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
      {
         ASSERT(hPackedDIB != NULL);
         const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
         ASSERT(lpPackedDIB != NULL);
         BOOL bResult = Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
         ::GlobalUnlock(hPackedDIB);
         return bResult;
      }

#ifdef _DEBUG
      void brush::dump(dump_context & dumpcontext) const
      {
         ::ca::graphics_object::dump(dumpcontext);

         if (get_os_data() == NULL)
            return;

         if (!afxData.bWin95 && ::GetObjectType(get_os_data()) != OBJ_BRUSH)
         {
            // not a valid ::ca::window
            dumpcontext << "has ILLEGAL HBRUSH!";
            return;
         }

         LOGBRUSH lb;
         VERIFY(GetObject(sizeof(lb), &lb));
         dumpcontext << "lb.lbStyle = " << lb.lbStyle;
         dumpcontext << "\nlb.lbHatch = " << lb.lbHatch;
         dumpcontext << "\nlb.lbColor = " << (void *)(DWORD_PTR)lb.lbColor;

         dumpcontext << "\n";
      }
#endif


   /////////////////////////////////////////////////////////////////////////////
   // brush




} // namespace win