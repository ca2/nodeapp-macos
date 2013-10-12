#include "framework.h"



/////////////////////////////////////////////////////////////////////////////
// no_track_object

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
#undef new
void * PASCAL no_track_object::operator new(size_t nSize, const char *, int32_t)
{
   return no_track_object::operator new(nSize);
}
#define new BASE_NEW
void PASCAL no_track_object::operator delete(void * pObject, const char *, int32_t)
{
   if (pObject != NULL)
      ::free(pObject);
}
#endif

#undef new
void * PASCAL no_track_object::operator new(size_t nSize)
{
   void * p = ::malloc(nSize);
   if (p == NULL)
      throw memory_exception(::get_thread_app());
   return p;
}
#define new BASE_NEW

void PASCAL no_track_object::operator delete(void * p)
{
   if (p != NULL)
      ::free(p);
}


struct thread_data : public no_track_object
{
   thread_data* pNext; // required to be member of simple_list
   int32_t nCount;         // current size of pData
   LPVOID* pData;      // actual thread local data (indexed by nSlot)
};

struct slot_data
{
   DWORD dwFlags;      // slot flags (allocated/not allocated)
   HINSTANCE hInst;    // module which owns this slot
};

// flags used for slot_data::dwFlags above
#define SLOT_USED   0x01    // slot is allocated

//static
//static pthread_once_t key_once = PTHREAD_ONCE_INIT;

//static void
//make_key()
//{
//  (void)
///}

/*func()
 {
 void *ptr;
 
 if ((ptr = pthread_getspecific(key)) == NULL) {
 ptr = malloc(OBJECT_SIZE);
 ...
 (void) pthread_setspecific(key, ptr);
 }
 ...
 }*/


thread_local_storage::thread_local_storage()
{
   if(pthread_key_create(&key, NULL) != 0)
      throw memory_exception(NULL);
   //   m_tlsIndex = TlsAlloc();
   
   
}


thread_local_storage::~thread_local_storage()
{
   //if (m_tlsIndex != (DWORD)-1)
   {
      //TlsFree(m_tlsIndex);
      // DEBUG_ONLY(m_tlsIndex = (DWORD)-1);
   }
}

void thread_local_storage::delete_data()
{
   get_slot_data()->delete_data();
}

#undef new

thread_slot_data * thread_local_storage::get_slot_data()
{
   thread_slot_data * pdata = (thread_slot_data *) pthread_getspecific(key);
   if(pdata == NULL)
   {
      void * p = malloc(sizeof(thread_slot_data));
      pdata = ::new(p) thread_slot_data();
      pthread_setspecific(key, (LPVOID) pdata);
   }
   return pdata;
}
#define new BASE_NEW


thread_slot_data::thread_slot_data()
{
   memset(m_pa, 0, sizeof(m_pa));
}

void thread_slot_data::delete_data()
{
   for(int32_t i = 0; i < 1024; i++)
   {
      if(m_pa[i] != NULL)
      {
         delete m_pa[i];
      }
   }
   free(this);
}


/////////////////////////////////////////////////////////////////////////////
// thread_local_object


/////////////////////////////////////////////////////////////////////////////
// CProcessLocalData

no_track_object* process_local_object::get_data(
                                                no_track_object* ( * pfnCreateObject)())
{
   if (m_pObject == NULL)
   {
      single_lock sl(&m_mutex, TRUE);
      try
      {
         if (m_pObject == NULL)
            m_pObject = (*pfnCreateObject)();
      }
      catch(::exception::base * pe)
      {
         ::exception::rethrow(pe);
      }
      
   }
   return m_pObject;
}

process_local_object::~process_local_object()
{
   if (m_pObject != NULL)
      delete m_pObject;
}

/////////////////////////////////////////////////////////////////////////////
// Init/Term for thread/process local data

/*void CLASS_DECL_lnx ::ca2::InitLocalData(HINSTANCE hInst)
 {
 if (__thread_data != NULL)
 __thread_data->AssignInstance(hInst);
 }
 
 void CLASS_DECL_lnx __term_local_data(HINSTANCE hInst, bool bAll)
 {
 if (__thread_data != NULL)
 __thread_data->DeleteValues(hInst, bAll);
 }*/

// This reference count is needed to support Win32s, such that the
// thread-local and process-local data is not destroyed prematurely.
// It is basically a reference count of the number of processes that
// have attached to the ca2 API DLL.

long gen_TlsRef = 0;

void CLASS_DECL_mac __tls_add_ref()
{
   ++gen_TlsRef;
}

void CLASS_DECL_mac __tls_release()
{
   if (gen_TlsRef == 0 || --gen_TlsRef == 0)
   {
      if (__thread_data != NULL)
      {
         __thread_data->~thread_local_storage();
         __thread_data = NULL;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// thread_slot_data

// global __thread_data used to allocate thread local indexes
BYTE _gen_ThreadData[sizeof(thread_local_storage)];
thread_local_storage * __thread_data;


