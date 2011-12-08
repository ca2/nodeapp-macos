#include "StdAfx.h"
#include <stddef.h>



/////////////////////////////////////////////////////////////////////////////
// no_track_object

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
#undef new
void * PASCAL no_track_object::operator new(size_t nSize, const char *, int)
{
   return no_track_object::operator new(nSize);
}
#define new DEBUG_NEW
void PASCAL no_track_object::operator delete(void * pObject, const char *, int)
{
   if (pObject != NULL)
      ::LocalFree(pObject);
}
#endif

#undef new
void * PASCAL no_track_object::operator new(size_t nSize)
{
   void * p = ::LocalAlloc(LPTR, nSize);
   if (p == NULL)
      AfxThrowMemoryException();
   return p;
}
#define new DEBUG_NEW

void PASCAL no_track_object::operator delete(void * p)
{
   if (p != NULL)
      ::LocalFree(p);
}

/////////////////////////////////////////////////////////////////////////////
// thread_slot_data

// global _afxThreadData used to allocate thread local indexes
BYTE __afxThreadData[sizeof(thread_slot_data)];
thread_slot_data* _afxThreadData;

struct thread_data : public no_track_object
{
   thread_data* pNext; // required to be member of simple_list
   int nCount;         // current size of pData
   LPVOID* pData;      // actual thread local data (indexed by nSlot)
};

struct slot_data
{
   DWORD dwFlags;      // slot flags (allocated/not allocated)
   HINSTANCE hInst;    // module which owns this slot
};

// flags used for slot_data::dwFlags above
#define SLOT_USED   0x01    // slot is allocated

thread_slot_data::thread_slot_data()
{
   m_list.Construct(offsetof(thread_data, pNext));

   // initialize state and allocate TLS index
   m_nAlloc = 0;
   m_nRover = 1;   // first slot (0) is always reserved
   m_nMax = 0;
   m_pSlotData = NULL;

   // init m_tlsIndex to -1 if !bThreadLocal, otherwise TlsAlloc
   m_tlsIndex = TlsAlloc();
   if (m_tlsIndex == (DWORD)-1)
      AfxThrowMemoryException();

   InitializeCriticalSection(&m_sect);
}

thread_slot_data::~thread_slot_data()
{
   thread_data* pData = m_list;
   while (pData != NULL)
   {
      thread_data* pDataNext = pData->pNext;
      DeleteValues(pData, NULL);
      pData = pDataNext;
   }

   if (m_tlsIndex != (DWORD)-1)
   {
      TlsFree(m_tlsIndex);
      DEBUG_ONLY(m_tlsIndex = (DWORD)-1);
   }

   if (m_pSlotData != NULL)
   {
      HGLOBAL hSlotData = GlobalHandle(m_pSlotData);
      GlobalUnlock(hSlotData);
      GlobalFree(hSlotData);
      DEBUG_ONLY(m_pSlotData = NULL);
   }

   DeleteCriticalSection(&m_sect);
}

int thread_slot_data::AllocSlot()
{
   EnterCriticalSection(&m_sect);
   int nAlloc = m_nAlloc;
   int nSlot = m_nRover;
   if (nSlot >= nAlloc || (m_pSlotData[nSlot].dwFlags & SLOT_USED))
   {
      // search for first free slot, starting at beginning
      for (nSlot = 1;
         nSlot < nAlloc && (m_pSlotData[nSlot].dwFlags & SLOT_USED); nSlot++)
         ;

      // if none found, need to allocate more space
      if (nSlot >= nAlloc)
      {
         // realloc primitive::memory for the bit base_array and the slot primitive::memory
         int nNewAlloc = m_nAlloc+32;
         HGLOBAL hSlotData;
         if (m_pSlotData == NULL)
         {
            hSlotData = GlobalAlloc(GMEM_MOVEABLE, static_cast<UINT>(::_template::multiply_throw(static_cast<UINT>(nNewAlloc),static_cast<UINT>(sizeof(slot_data)))));
         }
         else
         {
            hSlotData = GlobalHandle(m_pSlotData);
            GlobalUnlock(hSlotData);
            hSlotData = GlobalReAlloc(hSlotData, static_cast<UINT>(::_template::multiply_throw(static_cast<UINT>(nNewAlloc),static_cast<UINT>(sizeof(slot_data)))), GMEM_MOVEABLE|GMEM_SHARE);
         }

         if (hSlotData == NULL)
         {
            if (m_pSlotData != NULL)
               GlobalLock(GlobalHandle(m_pSlotData));
            LeaveCriticalSection(&m_sect);
            AfxThrowMemoryException();
         }
         slot_data* pSlotData = (slot_data*)GlobalLock(hSlotData);

         // always zero initialize after success
         memset(pSlotData+m_nAlloc, 0, (nNewAlloc-m_nAlloc)*sizeof(slot_data));
         m_nAlloc = nNewAlloc;
         m_pSlotData = pSlotData;
      }
   }
   ASSERT(nSlot != 0); // first slot (0) is reserved

   // adjust m_nMax to largest slot ever allocated
   if (nSlot >= m_nMax)
      m_nMax = nSlot+1;

   ASSERT(!(m_pSlotData[nSlot].dwFlags & SLOT_USED));
   m_pSlotData[nSlot].dwFlags |= SLOT_USED;
   // update m_nRover (likely place to find a free slot is next one)
   m_nRover = nSlot+1;

   LeaveCriticalSection(&m_sect);
   return nSlot;   // slot can be used for FreeSlot, get_value, SetValue
}

void thread_slot_data::FreeSlot(int nSlot)
{
   EnterCriticalSection(&m_sect);
   ASSERT(nSlot != 0 && nSlot < m_nMax);
   ASSERT(m_pSlotData != NULL);
   ASSERT(m_pSlotData[nSlot].dwFlags & SLOT_USED);
   if( nSlot <= 0 || nSlot >= m_nMax ) // check for retail builds.
      return;

   // delete the data from all threads/processes
   thread_data* pData = m_list;
   while (pData != NULL)
   {
      if (nSlot < pData->nCount)
      {
         delete (no_track_object*)pData->pData[nSlot];
         pData->pData[nSlot] = NULL;
      }
      pData = pData->pNext;
   }
   // free the slot itself
   m_pSlotData[nSlot].dwFlags &= ~SLOT_USED;
   LeaveCriticalSection(&m_sect);
}

// special version of thread_slot_data::get_data that only works with
// thread local storage (and not process local storage)
// this version is inlined and simplified for speed
inline void * thread_slot_data::GetThreadValue(int nSlot)
{
   EnterCriticalSection(&m_sect);
   ASSERT(nSlot != 0 && nSlot < m_nMax);
   ASSERT(m_pSlotData != NULL);
   ASSERT(m_pSlotData[nSlot].dwFlags & SLOT_USED);
   ASSERT(m_tlsIndex != (DWORD)-1);
   if( nSlot <= 0 || nSlot >= m_nMax ) // check for retail builds.
   {
      LeaveCriticalSection(&m_sect);
      return NULL;
   }

   thread_data* pData = (thread_data*)TlsGetValue(m_tlsIndex);
   if (pData == NULL || nSlot >= pData->nCount)
   {
      LeaveCriticalSection(&m_sect);
      return NULL;
   }
   void * pRetVal = pData->pData[nSlot];
   LeaveCriticalSection(&m_sect);
   return pRetVal;
}

void thread_slot_data::SetValue(int nSlot, void * pValue)
{
   EnterCriticalSection(&m_sect);
   ASSERT(nSlot != 0 && nSlot < m_nMax);
   ASSERT(m_pSlotData != NULL);
   ASSERT(m_pSlotData[nSlot].dwFlags & SLOT_USED);
   if( nSlot <= 0 || nSlot >= m_nMax ) // check for retail builds.
   {
      LeaveCriticalSection(&m_sect);
      return;
   }

   thread_data* pData = (thread_data*)TlsGetValue(m_tlsIndex);
   if (pData == NULL || nSlot >= pData->nCount && pValue != NULL)
   {
      // if pData is NULL then this thread has not been visited yet
      if (pData == NULL)
      {
         try
         {
            pData = new thread_data;
         }
         catch(base_exception * pe)
         {
            LeaveCriticalSection(&m_sect);
            ::ca::rethrow(pe);
         }
         
         pData->nCount = 0;
         pData->pData = NULL;
         DEBUG_ONLY(pData->pNext = NULL);

         m_list.add_head(pData);
      }

      // grow to now current size
      void ** ppvTemp;
      if (pData->pData == NULL)
         ppvTemp = (void **)LocalAlloc(LMEM_FIXED, static_cast<UINT>(::_template::multiply_throw(static_cast<UINT>(m_nMax),static_cast<UINT>(sizeof(LPVOID)))));
      else
         ppvTemp = (void **)LocalReAlloc(pData->pData, static_cast<UINT>(::_template::multiply_throw(static_cast<UINT>(m_nMax),static_cast<UINT>(sizeof(LPVOID)))), LMEM_MOVEABLE);
      if (ppvTemp == NULL)
      {
         LeaveCriticalSection(&m_sect);
         AfxThrowMemoryException();
      }
      pData->pData = ppvTemp;

      // initialize the newly allocated part
      memset(pData->pData + pData->nCount, 0,
         (m_nMax - pData->nCount) * sizeof(LPVOID));
      pData->nCount = m_nMax;
      TlsSetValue(m_tlsIndex, pData);
   }
   ASSERT(pData->pData != NULL && nSlot < pData->nCount);
   if( pData->pData != NULL && nSlot < pData->nCount )
      pData->pData[nSlot] = pValue;
   LeaveCriticalSection(&m_sect);
}

void thread_slot_data::AssignInstance(HINSTANCE hInst)
{
   EnterCriticalSection(&m_sect);
   ASSERT(m_pSlotData != NULL);
   ASSERT(hInst != NULL);

   for (int i = 1; i < m_nMax; i++)
   {
      if (m_pSlotData[i].hInst == NULL && (m_pSlotData[i].dwFlags & SLOT_USED))
         m_pSlotData[i].hInst = hInst;
   }
   LeaveCriticalSection(&m_sect);
}

void thread_slot_data::DeleteValues(thread_data* pData, HINSTANCE hInst)
{
   ASSERT(pData != NULL);

   // free each element in the table
   BOOL bDelete = TRUE;
   for (int i = 1; i < pData->nCount; i++)
   {
      if (hInst == NULL || m_pSlotData[i].hInst == hInst)
      {
         // delete the data since hInst matches (or is NULL)
         delete (no_track_object*)pData->pData[i];
         pData->pData[i] = NULL;
      }
      else if (pData->pData[i] != NULL)
      {
         // don't delete thread data if other modules still alive
         bDelete = FALSE;
      }
   }

   if (bDelete)
   {
      // remove from master list and free it
      EnterCriticalSection(&m_sect);
      m_list.remove(pData);
      LeaveCriticalSection(&m_sect);
      LocalFree(pData->pData);
      delete pData;

      // clear TLS index to prevent from re-use
      TlsSetValue(m_tlsIndex, NULL);
   }
}

void thread_slot_data::DeleteValues(HINSTANCE hInst, BOOL bAll)
{
   EnterCriticalSection(&m_sect);
   if (!bAll)
   {
      // delete the values only for the current thread
      thread_data* pData = (thread_data*)TlsGetValue(m_tlsIndex);
      if (pData != NULL)
         DeleteValues(pData, hInst);
   }
   else
   {
      // delete the values for all threads
      thread_data* pData = m_list;
      while (pData != NULL)
      {
         thread_data* pDataNext = pData->pNext;
         DeleteValues(pData, hInst);
         pData = pDataNext;
      }
   }
   LeaveCriticalSection(&m_sect);
}

/////////////////////////////////////////////////////////////////////////////
// thread_local_object

no_track_object* thread_local_object::get_data(
   no_track_object* ( * pfnCreateObject)())
{
    ENSURE(pfnCreateObject);

   if (m_nSlot == 0)
   {
      if (_afxThreadData == NULL)
      {
#undef new
         _afxThreadData = new(__afxThreadData) thread_slot_data;
#define new DEBUG_NEW
         ENSURE(_afxThreadData != NULL);
      }
      m_nSlot = _afxThreadData->AllocSlot();
      ENSURE(m_nSlot != 0);
   }
   no_track_object* pValue = static_cast<no_track_object*>(_afxThreadData->GetThreadValue(m_nSlot));
   if (pValue == NULL)
   {
      // allocate zero-init object
      pValue = (*pfnCreateObject)();

      // set tls data to newly created object
      _afxThreadData->SetValue(m_nSlot, pValue);
      ASSERT(_afxThreadData->GetThreadValue(m_nSlot) == pValue);
   }
   return pValue;
}

no_track_object* thread_local_object::GetDataNA()
{
   if (m_nSlot == 0 || _afxThreadData == NULL)
      return NULL;

   no_track_object* pValue =
      (no_track_object*)_afxThreadData->GetThreadValue(m_nSlot);
   return pValue;
}

thread_local_object::~thread_local_object()
{
   if (m_nSlot != 0 && _afxThreadData != NULL)
      _afxThreadData->FreeSlot(m_nSlot);
   m_nSlot = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CProcessLocalData

no_track_object* process_local_object::get_data(
   no_track_object* ( * pfnCreateObject)())
{
   if (m_pObject == NULL)
   {
      AfxLockGlobals(CRIT_PROCESSLOCAL);
      try
      {
         if (m_pObject == NULL)
            m_pObject = (*pfnCreateObject)();
      }
      catch(base_exception * pe)
      {
         AfxUnlockGlobals(CRIT_PROCESSLOCAL);
         ::ca::rethrow(pe);
      }
      
      AfxUnlockGlobals(CRIT_PROCESSLOCAL);
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

void CLASS_DECL_VMSWIN AfxInitLocalData(HINSTANCE hInst)
{
   if (_afxThreadData != NULL)
      _afxThreadData->AssignInstance(hInst);
}

void CLASS_DECL_VMSWIN AfxTermLocalData(HINSTANCE hInst, BOOL bAll)
{
   if (_afxThreadData != NULL)
      _afxThreadData->DeleteValues(hInst, bAll);
}

// This reference count is needed to support Win32s, such that the
// thread-local and process-local data is not destroyed prematurely.
// It is basically a reference count of the number of processes that
// have attached to the ca2 API DLL.

AFX_STATIC_DATA long _afxTlsRef = 0;

void CLASS_DECL_VMSWIN AfxTlsAddRef()
{
   ++_afxTlsRef;
}

void CLASS_DECL_VMSWIN AfxTlsRelease()
{
   if (_afxTlsRef == 0 || --_afxTlsRef == 0)
   {
      if (_afxThreadData != NULL)
      {
         _afxThreadData->~thread_slot_data();
         _afxThreadData = NULL;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
