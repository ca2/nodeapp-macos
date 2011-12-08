#include "StdAfx.h"

namespace win
{

   graphics_object::operator HGDIOBJ() const
   { 
      return this == NULL ? NULL : get_handle(); 
   }
   
   HGDIOBJ graphics_object::get_os_data() const
   {
      return this == NULL ? NULL : get_handle(); 
   }
   
   graphics_object::graphics_object()
   {
      set_handle(NULL); 
   }
   
   graphics_object::~graphics_object()
   { 
      delete_object(); 
   }
   
   int graphics_object::_AFX_FUNCNAME(GetObject)(int nCount, LPVOID lpObject) const
   { 
      return ::GetObject(get_handle(), nCount, lpObject); 
   }

#pragma push_macro("GetObject")
#undef GetObject
   int graphics_object::GetObject(int nCount, LPVOID lpObject) const
   { return _AFX_FUNCNAME(GetObject)(nCount, lpObject); }
#pragma pop_macro("GetObject")
   BOOL graphics_object::CreateStockObject(int nIndex)
   { return (set_handle(::GetStockObject(nIndex))) != NULL; }
   BOOL graphics_object::UnrealizeObject()
   { ASSERT(get_handle() != NULL); return ::UnrealizeObject(get_handle()); }
   UINT graphics_object::GetObjectType() const
   { return (UINT)::GetObjectType(get_handle()); }
   BOOL graphics_object::operator==(const ::ca::graphics_object& obj) const
   { return ((HGDIOBJ) obj.get_os_data()) == get_handle(); }
   BOOL graphics_object::operator!=(const ::ca::graphics_object& obj) const
   { return ((HGDIOBJ) obj.get_os_data()) != get_handle(); }


   graphics_object * graphics_object_allocator(::ca::application * papp, HANDLE h)
   {
      switch(::GetObjectType(h))
      {
      case OBJ_BITMAP:
         return dynamic_cast < graphics_object * > (new bitmap(papp));
      case OBJ_REGION:
         return dynamic_cast < graphics_object * > (new rgn(papp));
      case OBJ_PEN:
         return dynamic_cast < graphics_object * > (new pen(papp));
      case OBJ_BRUSH:
         return dynamic_cast < graphics_object * > (new brush(papp));
      case OBJ_PAL:
         return dynamic_cast < graphics_object * > (new palette(papp));
      case OBJ_FONT:
         return dynamic_cast < graphics_object * > (new font(papp));
      }
      return new graphics_object();
   }

   graphics_object* PASCAL graphics_object::from_handle(::ca::application * papp, HGDIOBJ h)
   {
      hgdiobj_map* pMap = afxMapHGDIOBJ(TRUE); //create ::collection::map if not exist
      ASSERT(pMap != NULL);
      graphics_object* pObject = (::win::graphics_object*)pMap->from_handle(h, &graphics_object_allocator, papp);
      ASSERT(pObject == NULL || pObject->get_os_data() == h);
      return pObject;
   }

   BOOL graphics_object::Attach(HGDIOBJ hObject)
   {
      if (hObject == NULL)
      {
         return FALSE;
      }
      if(get_os_data() != NULL)
      {
         delete_object();
      }
      // remember early to avoid leak
      set_handle(hObject);
      hgdiobj_map* pMap = afxMapHGDIOBJ(TRUE); // create ::collection::map if not exist
      ASSERT(pMap != NULL);
      pMap->set_permanent(get_os_data(), this);
      return TRUE;
   }

   HGDIOBJ graphics_object::Detach()
   {
      HGDIOBJ hObject = get_os_data();
      if (hObject != NULL)
      {
         hgdiobj_map* pMap = afxMapHGDIOBJ(); // don't create if not exist
         if (pMap != NULL)
            pMap->remove_handle(get_os_data());
      }

      set_handle(NULL);
      return hObject;
   }

   BOOL graphics_object::delete_object()
   {
      if (get_os_data() == NULL)
         return FALSE;
      return ::DeleteObject(Detach());
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::graphics_object

#ifdef _DEBUG
   void graphics_object::dump(dump_context & dumpcontext) const
   {
      ::radix::object::dump(dumpcontext);

      dumpcontext << "get_handle() = " << get_handle();
      dumpcontext << "\n";
   }

   void graphics_object::assert_valid() const
   {
      ::radix::object::assert_valid();
      ASSERT(get_handle() == NULL ||
         (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
   }
#endif

   void * graphics_object::detach_os_data()
   {
      return Detach();
   }

   /*void * graphics_object::get_os_data() const
   {
   return get_os_data();
   }*/

} // namespace win

hgdiobj_map * PASCAL afxMapHGDIOBJ(BOOL bCreate)
{
   try
   {
      AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
      if(pState == NULL)
         return NULL;
      if(pState->m_pCurrentWinThread == NULL)
         return NULL;
      return pState->m_pCurrentWinThread->m_pmapHGDIOBJ;
   }
   catch(...)
   {
      return NULL;
   }
}
