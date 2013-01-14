#include "StdAfx.h"

namespace mac
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
      return dynamic_cast < brush * > (::mac::graphics_object::from_handle(papp, hBrush));
   }
    WINBOOL brush::CreateSolidBrush(COLORREF crColor)
      { return Attach(::CreateSolidBrush(crColor)); }
    WINBOOL brush::CreateHatchBrush(int nIndex, COLORREF crColor)
      { return Attach(::CreateHatchBrush(nIndex, crColor)); }
    WINBOOL brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
      { return Attach(::CreateBrushIndirect(lpLogBrush)); }
    WINBOOL brush::CreatePatternBrush(::ca::bitmap* pBitmap)
      { return Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())); }
    WINBOOL brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
      { return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage)); }
    WINBOOL brush::CreateSysColorBrush(int nIndex)
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

      WINBOOL brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
      {
         ASSERT(hPackedDIB != NULL);
         const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
         ASSERT(lpPackedDIB != NULL);
         WINBOOL bResult = Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
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
         dumpcontext << "\nlb.lbColor = " << (void *)(uint_ptr)lb.lbColor;

         dumpcontext << "\n";
      }
#endif


   /////////////////////////////////////////////////////////////////////////////
   // brush




} // namespace mac