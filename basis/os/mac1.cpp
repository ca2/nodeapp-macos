#include "framework.h"
#include "mac1.h"


namespace mac
{
   
   int32_t function()
   {
      return 0;
   }
   
   
   DWORD GetTempPath(string & str)
   {
      return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));
   }
   
   
} // namespace mac


