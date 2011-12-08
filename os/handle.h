// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

/////////////////////////////////////////////////////////////////////////////
// CHandleMap
//
//  Note: Do not access the members of this class directly.
//      Use ::win::window::from_handle, ::win::graphics::from_handle, etc.
//      The actual definition is only included because it is
//      necessary for the definition of WindowsThread.
//
//  Most Windows objects are represented with a HANDLE, including
//      the most important ones, HWND, HDC, HPEN, HFONT etc.
//  We want C++ objects to wrap these handle based objects whenever we can.
//  Since Windows objects can be created outside of C++ (eg: calling
//      ::CreateWindow will return an HWND with no C++ wrapper) we must
//      support a reasonably uniform mapping from permanent handles
//      (i.e. the ones allocated in C++) and temporary handles (i.e.
//      the ones allocated in C, but passed through a C++ interface.
//  We keep two dictionaries for this purpose.  The permanent dictionary
//      stores those C++ objects that have been explicitly created by
//      the developer.  The C++ constructor for the wrapper class will
//      insert the mapping into the permanent dictionary and the C++
//      destructor will remove it and possibly free up the associated
//      Windows object.
//  When a handle passes through a C++ interface that doesn't exist in
//      the permanent dictionary, we allocate a temporary wrapping object
//      and store that mapping into the temporary dictionary.
//  At idle time the temporary wrapping objects are flushed (since you better
//      not be holding onto something you didn't create).
//

#pragma once

namespace win
{

   class window;
   class graphics;
   class graphics_object;

template < int t_iHandleCount >
class handle_base
{
public:
   HANDLE m_handlea[t_iHandleCount];
   static const int s_iHandleCount = t_iHandleCount;
};

template < class H >
class handle1 : public handle_base < 1 >
{
public:
   handle1() { m_handlea[0] = NULL; }
   typedef handle_base < 1 > HANDLE_BASE_TYPE;
   inline H get_handle() const { return static_cast < H > (m_handlea[0]); }
   inline operator H () const { return get_handle(); }
   inline H set_handle(H h) { return static_cast < H > (m_handlea[0] = static_cast < HANDLE > (h)); }
};

template < class H1, class H2 >
class handle2 : public handle_base < 2 >
{
public:
   handle2() { m_handlea[0] = NULL; m_handlea[1] = NULL; }
   typedef handle_base < 2 > HANDLE_BASE_TYPE;
   inline H1 get_os_data() const { return static_cast < H1 > (m_handlea[0]); }
   inline H2 get_handle2() const { return static_cast < H2 > (m_handlea[0]); }
   inline H1 set_handle1(H1 h) { return static_cast < H1 > (m_handlea[0] = static_cast < HANDLE > (h)); }
   inline H2 set_handle2(H2 h) { return static_cast < H2 > (m_handlea[1] = static_cast < HANDLE > (h)); }
};

   typedef handle1 < HWND > hwnd_handle;
   typedef handle1 < HMENU > hmenu_handle;
   typedef handle2 < HDC, HDC > hdc_handle;
   typedef handle1 < HGDIOBJ > hgdiobj_handle;
   typedef handle1 < HIMAGELIST > himagelist_handle;

} // namespace win


#include "radix/fixed_alloc.h"

template<class TYPE>
struct ConstructDestruct
{
   static void PASCAL Construct(::radix::object* pObject)
   { 
      new (pObject) TYPE; 
   }
   static void PASCAL Destruct(::radix::object* pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
   static void PASCAL Construct(TYPE * pObject)
   { 
#undef new
      new (pObject) TYPE; 
#define new DEBUG_NEW
   }
   static void PASCAL Destruct(TYPE * pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
};

class WindowsThread;       // forward reference for friend declaration


template < class HT, class CT >
class handle_map
{
public:
    // implementation
   fixed_alloc_no_sync     m_alloc;
   mutex                   m_mutex;
   void (PASCAL* m_pfnConstructObject)(CT* pObject);
   void (PASCAL* m_pfnDestructObject)(CT* pObject);
   ::collection::map < HANDLE, HANDLE, CT *, CT *> m_permanentMap;
   ::collection::map < HANDLE, HANDLE, CT *, CT *> m_temporaryMap;
   //::ca::type_info m_pClass;
   //size_t m_nOffset;       // offset of handles in the object
   //int m_nHandles;         // 1 or 2 (for ::ca::graphics_sp)

// Constructor/Destructor
   handle_map();
#ifdef _ApplicationFrameworkDLL
   ~handle_map()
#else
   virtual ~handle_map()
#endif
      { delete_temp(); }

// Operations
public:
   CT * from_handle(HANDLE h, CT * (* pfnAllocator) (::ca::application *, HANDLE) = NULL, ::ca::application * papp = NULL);
   void delete_temp();

   void set_permanent(HANDLE h, CT * permOb);
   void remove_handle(HANDLE h);

   CT * lookup_permanent(HANDLE h);
   CT * lookup_temporary(HANDLE h);

   friend class ::radix::thread;
};

class CLASS_DECL_VMSWIN hwnd_map :
   public handle_map < ::win::hwnd_handle, ::win::window >
{
public:
};

class CLASS_DECL_VMSWIN hdc_map :
   public handle_map < ::win::hdc_handle, ::win::graphics >
{
public:
};

class hgdiobj_map : 
   public handle_map < ::win::hgdiobj_handle, ::win::graphics_object >
{
public:
};



/////////////////////////////////////////////////////////////////////////////
// CHandleMap implementation

template < class HT, class CT >
handle_map < HT, CT > ::handle_map() : 
      m_permanentMap(10), 
      m_temporaryMap(4), // small block size for temporary ::collection::map
      m_alloc(sizeof(CT), 64)
{

   /*ENSURE_ARG(pClass != NULL);
   ENSURE_ARG(pfnConstructObject != NULL);
   ENSURE_ARG(pfnDestructObject != NULL);*/
   ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);

   m_temporaryMap.InitHashTable(7, FALSE); // small table for temporary ::collection::map
//   m_pClass = &typeid(CT);
   m_pfnConstructObject = ConstructDestruct<CT>::Construct;
   m_pfnDestructObject = ConstructDestruct<CT>::Destruct;
//   m_nOffset = nOffset;
//   m_nHandles = nHandles;
}

template < class HT, class CT >
CT* handle_map < HT, CT >::from_handle(HANDLE h, CT * (*pfnAllocator) (::ca::application *, HANDLE), ::ca::application * papp)
{
   
   CSingleLock sl(&m_mutex, TRUE);

//   ASSERT(m_pClass != NULL);
   ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);

   if (h == NULL)
      return NULL;

   CT* pObject = lookup_permanent(h);
   if (pObject != NULL && pObject->get_os_data() == h)
      return pObject;   // return permanent one
   else if ((pObject = lookup_temporary(h)) != NULL && pObject->get_os_data() == h)
   {
      HANDLE* ph = pObject->m_handlea;
      ASSERT(ph[0] == h || ph[0] == NULL);
      ph[0] = h;
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == NULL);
         ph[1] = h;
      }
      return pObject;   // return current temporary one
   }

   // This handle wasn't created by us, so we must create a temporary
   // C++ object to wrap it.  We don't want the ::fontopus::user to see this primitive::memory
   // allocation, so we turn tracing off.

   BOOL bEnable = AfxEnableMemoryTracking(FALSE);
#ifndef _AFX_PORTABLE
   _PNH pnhOldHandler = AfxSetNewHandler(&AfxCriticalNewHandler);
#endif

   CT* pTemp = NULL;
   try
   {
      if(pfnAllocator != NULL)
      {
         pTemp = pfnAllocator(papp, h);
         if (pTemp == NULL)
            AfxThrowMemoryException();
      }
      else
      {
         // get primitive::memory for the object from the fixed allocator
   //      ASSERT((UINT)m_pClass->m_nObjectSize == m_alloc.GetAllocSize());
         pTemp = (CT*)m_alloc.Alloc();
         if (pTemp == NULL)
            AfxThrowMemoryException();

         // now construct the object in place
         ASSERT(m_pfnConstructObject != NULL);
         (*m_pfnConstructObject)(pTemp);
      }

      // set it in the ::collection::map
      m_temporaryMap.set_at(h, pTemp);
   }
   catch(base_exception * pe)
   {
#ifndef _AFX_PORTABLE
      AfxSetNewHandler(pnhOldHandler);
#endif
      AfxEnableMemoryTracking(bEnable);
      ::ca::rethrow(pe);
   }
   

#ifndef _AFX_PORTABLE
   AfxSetNewHandler(pnhOldHandler);
#endif
   AfxEnableMemoryTracking(bEnable);

   // now set the handle in the object
   HANDLE* ph = pTemp->m_handlea;  // after ::radix::object
   ph[0] = h;
   if (HT::s_iHandleCount == 2)
      ph[1] = h;

   return pTemp;
}

#ifdef _DEBUG   // out-of-line version for primitive::memory tracking
template < class HT, class CT >
void handle_map < HT, CT >::set_permanent(HANDLE h, CT * permOb)
{
   
   CSingleLock sl(&m_mutex, TRUE);

   BOOL bEnable = AfxEnableMemoryTracking(FALSE);
   m_permanentMap[(LPVOID)h] = permOb;
   AfxEnableMemoryTracking(bEnable);

}
#endif //_DEBUG

#ifdef _DEBUG
template < class HT, class CT >
void handle_map < HT, CT > ::remove_handle(HANDLE h)
{
   
   CSingleLock sl(&m_mutex, TRUE);

   // make sure the handle entry is consistent before deleting
   CT* pTemp = lookup_temporary(h);
   if (pTemp != NULL)
   {
      // temporary objects must have correct handle values
      HANDLE* ph = pTemp->m_handlea;
      ASSERT(ph[0] == h || ph[0] == NULL);
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == NULL);
      }
   }
   pTemp = lookup_permanent(h);
   if (pTemp != NULL)
   {
      HANDLE* ph = pTemp->m_handlea;
      ASSERT(ph[0] == h);
      // permanent object may have secondary handles that are different
   }
   // remove only from permanent ::collection::map -- temporary objects are removed
   //  at idle in CHandleMap::delete_temp, always!
   m_permanentMap.remove_key((LPVOID)h);
}
#endif

template < class HT, class CT >
void handle_map < HT, CT >::delete_temp()
{
   
   CSingleLock sl(&m_mutex, TRUE);

   if (gen::is_null(this))
      return;

   POSITION pos = m_temporaryMap.get_start_position();
   while (pos != NULL)
   {
      HANDLE h; // just used for asserts
      CT * pTemp;
      m_temporaryMap.get_next_assoc(pos, h, pTemp);

      // zero out the handles
      ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);
      HANDLE* ph = pTemp->m_handlea;  // after ::radix::object
      ASSERT(ph[0] == h || ph[0] == NULL);
      ph[0] = NULL;
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == NULL);
         ph[1] = NULL;
      }

      ASSERT(m_pfnDestructObject != NULL);
      (*m_pfnDestructObject)(pTemp);   // destruct the object
   }

   m_temporaryMap.remove_all();       // free up dictionary links etc
   m_alloc.FreeAll();   // free all the primitive::memory used for these temp objects
}


// Note: out-of-line _DEBUG version is in winhand.cpp
#ifndef _DEBUG
template < class HT, class CT >
inline void handle_map < HT, CT >::set_permanent(HANDLE h, CT * permOb)
   { m_permanentMap[(HANDLE)h] = permOb; }

template < class HT, class CT >
inline void handle_map < HT, CT >::remove_handle(HANDLE h)
{
   // remove only from permanent ::collection::map -- temporary objects are removed
   //  at idle in CHandleMap::delete_temp, always!
   m_permanentMap.remove_key((HANDLE)h);
}
#endif

template < class HT, class CT >
inline CT* handle_map <HT, CT>::lookup_permanent(HANDLE h)
{ 

   CSingleLock sl(&m_mutex, TRUE);

   CT * pt = m_permanentMap.get(h, (CT*) NULL);
   if(pt != NULL && pt->get_os_data() == h)
      return pt;
   else
      return NULL;

}

template < class HT, class CT >
inline CT* handle_map <HT, CT>::lookup_temporary(HANDLE h)
{

   CSingleLock sl(&m_mutex, TRUE);

   CT * pt = m_temporaryMap.get(h, (CT*) NULL); 
   if(pt != NULL && pt->get_os_data() == h)
      return pt;
   else
      return NULL;

}


CLASS_DECL_VMSWIN hwnd_map * PASCAL afxMapHWND(BOOL bCreate = FALSE);
CLASS_DECL_VMSWIN himagelist_map * PASCAL afxMapHIMAGELIST(BOOL bCreate = FALSE);
CLASS_DECL_VMSWIN hdc_map * PASCAL afxMapHDC(BOOL bCreate = FALSE);
CLASS_DECL_VMSWIN hgdiobj_map * PASCAL afxMapHGDIOBJ(BOOL bCreate = FALSE);
CLASS_DECL_VMSWIN hmenu_map * PASCAL afx_map_HMENU(BOOL bCreate = FALSE);
