#pragma once


// Classes declared in this file

//class simple_list;
class thread_slot_data;                  // for manipulationg thread local storage
template < int32_t iSlot >
class thread_local_object;               // for storing thread local data
class process_local_object;              // for storing thread local data
class no_track_object;

// template class typed_simple_list<>
// template class thread_local<>
// template class process_local<>

/////////////////////////////////////////////////////////////////////////////
// thread_slot_data - manages owned array of "slots" for thread local storage

struct thread_data; // private to implementation
struct slot_data;   // private to implementation


class CLASS_DECL_mac thread_slot_data
{
public:
   
   
   no_track_object *                           m_pa[1024]; // state of each slot (allocated or not)
   
   
   thread_slot_data();
   void delete_data();
   
};


class CLASS_DECL_mac thread_local_storage
{
public:
   
   pthread_key_t key;   // used to access system thread-local storage
   thread_slot_data *               m_pthreadslotdata;
   
   
   thread_local_storage();
   ~thread_local_storage();
   void delete_data();
   
   thread_slot_data * get_slot_data();
#undef new
   void * PASCAL operator new(size_t, void * p)
   { return p; }
#define new BASE_NEW
};


extern BYTE _gen_ThreadData[sizeof(thread_local_storage)];
extern thread_local_storage * __thread_data;


class CLASS_DECL_mac no_track_object
{
public:
#undef new
   void * PASCAL operator new(size_t nSize);
#define new BASE_NEW
   void PASCAL operator delete(void *);
   
#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
#undef new
   void * PASCAL operator new(size_t nSize, const char *, int32_t);
#define new BASE_NEW
   void PASCAL operator delete(void * pObject, const char *, int32_t);
#endif
   virtual ~no_track_object() {};
};

template < int32_t iSlot >
class thread_local_object
{
public:
   // Attributes
   no_track_object* get_data(no_track_object* ( * pfnCreateObject)());
   no_track_object* GetDataNA();
   
   // Implementation
   //int32_t m_nSlot;
   ~thread_local_object();
};


template < int32_t iSlot >
no_track_object* thread_local_object < iSlot> ::get_data(no_track_object* ( * pfnCreateObject)())
{
   
   if (__thread_data == NULL)
   {
#undef new
      __thread_data = new(_gen_ThreadData) thread_local_storage;
#define new BASE_NEW
      ENSURE(__thread_data != NULL);
   }
   
   no_track_object * pValue = (no_track_object *) __thread_data->get_slot_data()->m_pa[iSlot];
   
   if(pValue == NULL)
   {
      
      // allocate zero-init object
      pValue =  (*pfnCreateObject)();
      
      // set tls data to newly created object
      __thread_data->get_slot_data()->m_pa[iSlot] = pValue;
      ASSERT(__thread_data->get_slot_data()->m_pa[iSlot] == pValue);
      
   }
   
   return pValue;
   
}
template < int32_t iSlot >
no_track_object* thread_local_object < iSlot > ::GetDataNA()
{
   return __thread_data->get_slot_data()->m_pa[iSlot];
}
template < int32_t iSlot >
thread_local_object < iSlot > ::~thread_local_object()
{
   //   if (m_nSlot != 0 && __thread_data != NULL)
   //    __thread_data->FreeSlot(m_nSlot);
   //m_nSlot = 0;
}


class CLASS_DECL_mac process_local_object
{
public:
   
   
   mutex                         m_mutex;
   no_track_object * volatile    m_pObject;
   
   
   // Implementation
   process_local_object() : m_mutex(NULL) { }
   ~process_local_object();
   
   
   // Attributes
   no_track_object* get_data(no_track_object* (* pfnCreateObject)());
   
   
};


template < class TYPE, int32_t iSlot >
class thread_slot :
public thread_local_object < iSlot >
{
   // Attributes
public:
   inline TYPE* get_data()
   {
      return (TYPE *) thread_local_object < iSlot >::get_data(&CreateObject);
      //ENSURE(pData != NULL);
      //return pData;
   }
   inline TYPE* GetDataNA()
   {
      TYPE* pData = (TYPE*)thread_local_object < iSlot >::GetDataNA();
      return pData;
   }
   inline operator TYPE*()
   {
      return get_data();
   }
   inline TYPE* operator->()
   {
      return get_data();
   }
   
   // Implementation
public:
   static no_track_object* CreateObject()
   { return new TYPE; }
};

#define THREAD_LOCAL(class_name, ident_name, slot) \
thread_slot < class_name, slot > ident_name;
#define EXTERN_THREAD_LOCAL(class_name, ident_name, slot) \
extern CLASS_DECL_mac thread_slot<class_name, slot> ident_name;

template<class TYPE>
class process_local : public process_local_object
{
   // Attributes
public:
   inline TYPE* get_data()
   {
      TYPE* pData = (TYPE*)process_local_object::get_data(&CreateObject);
      ENSURE(pData != NULL);
      return pData;
   }
   inline TYPE* GetDataNA()
   { return (TYPE*)m_pObject; }
   inline operator TYPE*()
   { return get_data(); }
   inline TYPE* operator->()
   { return get_data(); }
   
   // Implementation
public:
   static no_track_object* CreateObject()
   { return new TYPE; }
};

#define PROCESS_LOCAL(class_name, ident_name) \
process_local < class_name > ident_name;
#define EXTERN_PROCESS_LOCAL(class_name, ident_name) \
extern process_local < class_name > ident_name;

/////////////////////////////////////////////////////////////////////////////

void CLASS_DECL_mac __init_local_data(HINSTANCE hInstInit);
void CLASS_DECL_mac __term_local_data(HINSTANCE hInstTerm, bool bAll = FALSE);
void CLASS_DECL_mac __tls_add_ref();
void CLASS_DECL_mac __tls_release();

