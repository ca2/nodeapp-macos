#include "StdAfx.h"

namespace win
{

   pen::pen(::ca::application * papp) :
      ca(papp)
   { 
   }
   pen::~pen()
   { 
   }
   pen::operator HPEN() const
   { 
      return (HPEN)(this == NULL ? NULL : get_handle()); 
   }
   pen* PASCAL pen::from_handle(::ca::application * papp, HPEN hPen)
   { 
      return dynamic_cast < pen* > (::win::graphics_object::from_handle(papp, hPen));
   }
   BOOL pen::CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
   { return Attach(::CreatePen(nPenStyle, nWidth, crColor)); }
   BOOL pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   { return Attach(::CreatePenIndirect(lpLogPen)); }
   BOOL pen::CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
      int nStyleCount, const DWORD* lpStyle)
   { return Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
   lpStyle)); }
   int pen::GetExtLogPen(EXTLOGPEN* pLogPen)
   { ASSERT(get_handle() != NULL);
   return ::GetObject(get_handle(), sizeof(EXTLOGPEN), pLogPen); }
   
   int pen::GetLogPen(LOGPEN* pLogPen)
   { 
      if(get_handle() == NULL)
         return 0;
      return ::GetObject(get_handle(), sizeof(LOGPEN), pLogPen); 
   }


   void pen::construct(int nPenStyle, int nWidth, COLORREF crColor)
   {
      if (!Attach(::CreatePen(nPenStyle, nWidth, crColor)))
         AfxThrowResourceException();
   }

   void pen::construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
      int nStyleCount, const DWORD* lpStyle)
   {
      if (!Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
         lpStyle)))
         AfxThrowResourceException();
   }

   /////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
   void pen::dump(dump_context & dumpcontext) const
   {
      ::ca::graphics_object::dump(dumpcontext);

      if (get_handle() == NULL)
         return;

      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
      {
         // not a valid object
         dumpcontext << "has ILLEGAL HPEN!";
         return;
      }

      LOGPEN lp;
      VERIFY(GetObject(sizeof(lp), &lp));
      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
      dumpcontext << "\nlgpn.lopnColor = " << (void *)(DWORD_PTR)lp.lopnColor;

      dumpcontext << "\n";
   }
#endif




      // IMPLEMENT_DYNAMIC(resource_exception, base_exception)
      //resource_exception _simpleResourceException(FALSE, AFX_IDS_RESOURCE_EXCEPTION);

      // IMPLEMENT_DYNAMIC(user_exception, base_exception)
      //user_exception _simpleUserException(FALSE, AFX_IDS_USER_EXCEPTION);

      // IMPLEMENT_DYNCREATE(::ca::graphics_sp, ::radix::object)
      // IMPLEMENT_DYNAMIC(CClientDC, ::ca::graphics_sp)
      // IMPLEMENT_DYNAMIC(CWindowDC, ::ca::graphics_sp)
      // IMPLEMENT_DYNAMIC(CPaintDC, ::ca::graphics_sp)
      // IMPLEMENT_DYNCREATE(::ca::graphics_object, ::radix::object)

      // IMPLEMENT_DYNAMIC(pen, ::ca::graphics_object)
      // IMPLEMENT_DYNAMIC(::ca::brush, ::ca::graphics_object)
      // IMPLEMENT_DYNAMIC(::ca::font, ::ca::graphics_object)
      // IMPLEMENT_DYNAMIC(::ca::bitmap, ::ca::graphics_object)
      // IMPLEMENT_DYNAMIC(::ca::palette, ::ca::graphics_object)
      // IMPLEMENT_DYNAMIC(::ca::rgn, ::ca::graphics_object)

      /////////////////////////////////////////////////////////////////////////////
      // Standard exception processing



} // namespace win