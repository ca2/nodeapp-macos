#include "framework.h"


namespace mac
{
   
   
   
   graphics_object::graphics_object()
   {
      //set_handle(NULL);
   }
   
   graphics_object::~graphics_object()
   {
      //delete_object();
   }
   
   int32_t graphics_object::get_object(int32_t nCount, LPVOID lpObject) const
   {
      //return ::GetObject(get_handle(), nCount, lpObject);
      return 0;
   }
   
   bool graphics_object::CreateStockObject(int32_t nIndex)
   {
      //return (set_handle(::GetStockObject(nIndex))) != NULL;
      return 0;
   }
   bool graphics_object::UnrealizeObject()
   {
      //ASSERT(get_handle() != NULL); return ::UnrealizeObject(get_handle());
      return 0;
   }
   UINT graphics_object::GetObjectType() const
   {
      //return (UINT)::GetObjectType(get_handle());
      return 0;
   }
   bool graphics_object::operator==(const ::ca2::graphics_object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle();
      return FALSE;
   }
   bool graphics_object::operator!=(const ::ca2::graphics_object& obj) const
   {
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle();
      return TRUE;
   }
   
   
   graphics_object * graphics_object_allocator(::ca2::application * papp, HANDLE h)
   {
      /*switch(::GetObjectType(h))
       {
       case OBJ_BITMAP:
       return dynamic_cast < graphics_object * > (new bitmap(papp));
       case OBJ_REGION:
       return dynamic_cast < graphics_object * > (new region(papp));
       case OBJ_PEN:
       return dynamic_cast < graphics_object * > (new pen(papp));
       case OBJ_BRUSH:
       return dynamic_cast < graphics_object * > (new brush(papp));
       case OBJ_PAL:
       return dynamic_cast < graphics_object * > (new palette(papp));
       case OBJ_FONT:
       return dynamic_cast < graphics_object * > (new font(papp));
       }
       return new graphics_object();*/
      return NULL;
   }
   
   /*graphics_object* PASCAL graphics_object::from_handle(::ca2::application * papp, HGDIOBJ h)
    {
    hgdiobj_map* pMap = afxMapHGDIOBJ(TRUE); //create ::collection::map if not exist
    ASSERT(pMap != NULL);
    graphics_object* pObject = (::win::graphics_object*)pMap->from_handle(h, &graphics_object_allocator, papp);
    ASSERT(pObject == NULL || pObject->get_os_data() == h);
    return pObject;
    }
    
    bool graphics_object::Attach(HGDIOBJ hObject)
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
    }*/
   
   bool graphics_object::delete_object()
   {
      //if (get_os_data() == NULL)
      // return FALSE;
      //return ::DeleteObject(Detach());
      return FALSE;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // ::ca2::graphics_object
   
   
   void graphics_object::dump(dump_context & dumpcontext) const
   {
      ::ca2::object::dump(dumpcontext);
      
      //      dumpcontext << "get_handle() = " << get_handle();
      //    dumpcontext << "\n";
   }
   
   void graphics_object::assert_valid() const
   {
      ::ca2::object::assert_valid();
      //ASSERT(get_handle() == NULL ||
      // (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
   }
   
   
   /*void * graphics_object::detach_os_data()
    {
    return Detach();
    }*/
   
   /*void * graphics_object::get_os_data() const
    {
    return get_os_data();
    }*/
   
   
   void * graphics_object::get_os_data() const
   {
      
      return NULL;
      
   }
   
   
} // namespace mac


/*hgdiobj_map * PASCAL afxMapHGDIOBJ(bool bCreate)
 {
 UNREFERENCED_PARAMETER(bCreate);
 try
 {
 __MODULE_STATE* pState = __get_module_state();
 if(pState == NULL)
 return NULL;
 return pState->m_pmapHGDIOBJ;
 }
 catch(...)
 {
 return NULL;
 }
 
 }
 */




