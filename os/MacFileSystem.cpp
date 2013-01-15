#include "framework.h"



namespace mac
{
   
   
   file_system::file_system(::ca::application * papp) :
   ca(papp)
   {
      
   }
   
   
   file_system::~file_system()
   {
      
   }
   
   /*
    bool file_system::FullPath(string &str, const char * lpszFileIn)
    {
    
    //if(::ex1::file_system::FullPath(str, lpszFileIn))
    // return true;
    
    if(gen::str::begins_ci(lpszFileIn, "http://"))
    {
    
    str = lpszFileIn;
    
    return true;
    
    }
    else if(gen::str::begins_ci(lpszFileIn, "https://"))
    {
    
    str = lpszFileIn;
    
    return true;
    
    }
    wstring wstrFileIn;
    wstrFileIn = gen::international::utf8_to_unicode(lpszFileIn);
    wstring wstrFileOut;
    bool b = vfxFullPath(wstrFileOut.alloc(MAX_PATH * 8), wstrFileIn) != FALSE;
    if(b)
    {
    gen::international::unicode_to_utf8(str, wstrFileOut);
    }
    return b;
    }
    
    
    
    UINT file_system::GetFileName(const char * lpszPathName, string & str)
    {
    
    str = System.file().name_(lpszPathName);
    
    return str.get_length();
    
    }
    
    void file_system::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
    {
    vfxGetModuleShortFileName(hInst, strShortName);
    }
    
    */
   
} // namespace mac


