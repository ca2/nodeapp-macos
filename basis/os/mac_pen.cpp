#include "framework.h"


namespace mac
{
   
   
   pen::pen(::ca::application * papp) :
   ca(papp)
   {
   }
   pen::~pen()
   {
   }
   /*   pen::operator HPEN() const
    {
    return (HPEN)(this == NULL ? NULL : get_handle());
    }*/
   /*   pen* PASCAL pen::from_handle(::ca::application * papp, HPEN hPen)
    {
    return dynamic_cast < pen* > (::win::graphics_object::from_handle(papp, hPen));
    }*/
   /*   WINBOOL pen::CreatePen(int32_t nPenStyle, int32_t nWidth, COLORREF crColor)
    { return Attach(::CreatePen(nPenStyle, nWidth, crColor)); }*/
   /*   WINBOOL pen::CreatePenIndirect(LPLOGPEN lpLogPen)
    { return Attach(::CreatePenIndirect(lpLogPen)); }*/
   /*   WINBOOL pen::CreatePen(int32_t nPenStyle, int32_t nWidth, const LOGBRUSH* pLogBrush,
    int32_t nStyleCount, const DWORD* lpStyle)
    { return Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
    lpStyle)); }*/
   /*   int32_t pen::GetExtLogPen(EXTLOGPEN* pLogPen)
    { ASSERT(get_handle() != NULL);
    return ::GetObject(get_handle(), sizeof(EXTLOGPEN), pLogPen); }
    */
   /*   int32_t pen::GetLogPen(LOGPEN* pLogPen)
    {
    if(get_handle() == NULL)
    return 0;
    return ::GetObject(get_handle(), sizeof(LOGPEN), pLogPen);
    }
    */
   
   /*   void pen::construct(int32_t nPenStyle, int32_t nWidth, COLORREF crColor)
    {
    if (!Attach(::CreatePen(nPenStyle, nWidth, crColor)))
    AfxThrowResourceException();
    }
    */
   /*
    void pen::construct(int32_t nPenStyle, int32_t nWidth, const LOGBRUSH* pLogBrush,
    int32_t nStyleCount, const DWORD* lpStyle)
    {
    if (!Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
    lpStyle)))
    AfxThrowResourceException();
    }
    */
   /////////////////////////////////////////////////////////////////////////////
   
   
#ifdef DEBUG
   
   void pen::dump(dump_context & dumpcontext) const
   {
      
      ::ca::graphics_object::dump(dumpcontext);
      //
      //    if (get_handle() == NULL)
      //     return;
      
      /*      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
       {
       // not a valid object
       dumpcontext << "has ILLEGAL HPEN!";
       return;
       }
       */
      /*    LOGPEN lp;
       VERIFY(GetObject(sizeof(lp), &lp));
       dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
       dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
       dumpcontext << "\nlgpn.lopnColor = " << (void *)(dword_ptr)lp.lopnColor;
       
       dumpcontext << "\n";
       */
   }
   
#endif
   
   
   
   
   // IMPLEMENT_DYNAMIC(resource_exception, base_exception)
   //resource_exception _simpleResourceException(FALSE, __IDS_RESOURCE_EXCEPTION);
   
   // IMPLEMENT_DYNAMIC(user_exception, base_exception)
   //user_exception _simpleUserException(FALSE, __IDS_USER_EXCEPTION);
   
   // IMPLEMENT_DYNCREATE(::ca::graphics_sp, ::ca::object)
   // IMPLEMENT_DYNAMIC(CClientDC, ::ca::graphics_sp)
   // IMPLEMENT_DYNAMIC(CWindowDC, ::ca::graphics_sp)
   // IMPLEMENT_DYNAMIC(CPaintDC, ::ca::graphics_sp)
   // IMPLEMENT_DYNCREATE(::ca::graphics_object, ::ca::object)
   
   // IMPLEMENT_DYNAMIC(pen, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::brush, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::font, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::bitmap, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::palette, ::ca::graphics_object)
   // IMPLEMENT_DYNAMIC(::ca::rgn, ::ca::graphics_object)
   
   /////////////////////////////////////////////////////////////////////////////
   // Standard exception processing
   
   
   
} // namespace mac




