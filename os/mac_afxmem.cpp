#include "framework.h"




_PNH CLASS_DECL_mac __set_new_handler(_PNH pfnNewHandler)
{
   __MODULE_THREAD_STATE* pState = __get_module_thread_state();
   _PNH pfnOldHandler = pState->m_pfnNewHandler;
   pState->m_pfnNewHandler = pfnNewHandler;
   return pfnOldHandler;
}



/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Obsolete API
/*
 void CLASS_DECL_mac __set_alloc_stop(LONG lRequestNumber)
 {
 _CrtSetBreakAlloc(lRequestNumber);
 }
 */
#ifdef DEBUG
bool CLASS_DECL_mac __check_memory()
// check all of primitive::memory (look for primitive::memory tromps)
{
//   return _CrtCheckMemory() != FALSE;
   return false;
}
#endif
/*
 // -- true if block of exact size, allocated on the heap
 // -- set *plRequestNumber to request number (or 0)
 bool CLASS_DECL_mac __is_memory_block(const void * pData, UINT nBytes,
 LONG* plRequestNumber)
 {
 return _CrtIsMemoryBlock(pData, nBytes, plRequestNumber, NULL, NULL);
 }
 
 */
