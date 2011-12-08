
#ifndef __AFXTLS_H__
#define __AFXTLS_H__

#pragma once

// Classes declared in this file

class simple_list;
class thread_slot_data;                  // for manipulationg thread local storage
class thread_local_object;               // for storing thread local data
class process_local_object;              // for storing thread local data
class no_track_object;

// template class typed_simple_list<>
// template class thread_local<>
// template class process_local<>

/////////////////////////////////////////////////////////////////////////////
// thread_slot_data - manages owned base_array of "slots" for thread local storage

struct thread_data; // private to implementation
struct slot_data;   // private to implementation

class CLASS_DECL_VMSWIN thread_slot_data
{
public:
   thread_slot_data();

// Operations
   int AllocSlot();
   void FreeSlot(int nSlot);   
   void SetValue(int nSlot, void * pValue);
   // delete all values in process/thread
   void DeleteValues(HINSTANCE hInst, BOOL bAll = FALSE);
   // assign instance handle to just constructed slots
   void AssignInstance(HINSTANCE hInst);

// Implementation
   DWORD m_tlsIndex;   // used to access system thread-local storage

   int m_nAlloc;       // number of slots allocated (in UINTs)
   int m_nRover;       // (optimization) for quick finding of free slots
   int m_nMax;         // size of slot table below (in bits)
   slot_data* m_pSlotData; // state of each slot (allocated or not)
   typed_simple_list<thread_data*> m_list;  // list of thread_data structures
   CRITICAL_SECTION m_sect;

   void * GetThreadValue(int nSlot); // special version for threads only!
#undef new
   void * PASCAL operator new(size_t, void * p)
      { return p; }
#define new DEBUG_NEW
   void DeleteValues(thread_data* pData, HINSTANCE hInst);
   ~thread_slot_data();
};

class CLASS_DECL_VMSWIN AFX_NOVTABLE no_track_object
{
public:
#undef new
   void * PASCAL operator new(size_t nSize);
#define new DEBUG_NEW
   void PASCAL operator delete(void *);

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
#undef new
   void * PASCAL operator new(size_t nSize, const char *, int);
#define new DEBUG_NEW
   void PASCAL operator delete(void * pObject, const char *, int);
#endif
    virtual ~no_track_object() {};
};

class CLASS_DECL_VMSWIN AFX_NOVTABLE thread_local_object
{
public:
// Attributes
   no_track_object* get_data(no_track_object* ( * pfnCreateObject)());
   no_track_object* GetDataNA();

// Implementation
   int m_nSlot;
   ~thread_local_object();
};

class CLASS_DECL_VMSWIN AFX_NOVTABLE process_local_object
{
public:
// Attributes
   no_track_object* get_data(no_track_object* (* pfnCreateObject)());

// Implementation
   no_track_object* volatile m_pObject;
   ~process_local_object();
};

template<class TYPE>
class thread_local : public thread_local_object
{
// Attributes
public:
   inline TYPE* get_data()
   {
      TYPE* pData = (TYPE*)thread_local_object::get_data(&CreateObject);
      ENSURE(pData != NULL);
      return pData;
   }
   inline TYPE* GetDataNA()
   {
      TYPE* pData = (TYPE*)thread_local_object::GetDataNA();
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

#define THREAD_LOCAL(class_name, ident_name) \
   AFX_COMDAT thread_local<class_name> ident_name;
#define EXTERN_THREAD_LOCAL(class_name, ident_name) \
   extern CLASS_DECL_VMSWIN thread_local<class_name> ident_name;

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
   AFX_COMDAT process_local<class_name> ident_name;
#define EXTERN_PROCESS_LOCAL(class_name, ident_name) \
   extern process_local<class_name> ident_name;

/////////////////////////////////////////////////////////////////////////////

void CLASS_DECL_VMSWIN AfxInitLocalData(HINSTANCE hInstInit);
void CLASS_DECL_VMSWIN AfxTermLocalData(HINSTANCE hInstTerm, BOOL bAll = FALSE);
void CLASS_DECL_VMSWIN AfxTlsAddRef();
void CLASS_DECL_VMSWIN AfxTlsRelease();

#endif //__AFXTLS_H__

/////////////////////////////////////////////////////////////////////////////
