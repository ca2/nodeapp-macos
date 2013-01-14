//
//  oswindow.h
//  os
//
//  Created by Thomas Borregaard Sørensen on 11/4/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//


// backlink at inha-ubuntu at veriverse at Curitiba near Finados Holyday 2012-11-03 from ca.dylib/ca.so/ca.dll
// and now on 2012-11-04, backlink at inha macos mountain lion
namespace ca // Thommy Gustavinho Cecynzinho Lundgrenzinho
{
   
   class CLASS_DECL_c null
   {
   public:
      
      
      null() {}
      
      
   };
   
} // namespace ca

namespace user
{
    
    
    class interaction_base;
    class interaction;
    
    
} // namespace user


class oswindow_dataptra;

#ifdef __MM
typedef NSWindow * nswindow;
#else
typedef void * nswindow;
#endif

class CLASS_DECL_c oswindow
{
public:
   
   
   class CLASS_DECL_c data
   {
   public:
      
      nswindow                m_nswindow;
      ::user::interaction_base *    m_pui;
      
   };
   
private:
   
   
   
   
   
   
   data *   m_pdata;
   
   
   static oswindow_dataptra * s_pdataptra;
   static int find(nswindow window);
   static data * get(nswindow window);
   
   
   
public:
   
   
   oswindow();
   oswindow(const ::ca::null & null);
   oswindow(nswindow window);
   oswindow(const void * p);
   oswindow(const oswindow & oswindow);
   oswindow(const LPARAM & lparam);
   oswindow(const WPARAM & wparam);
   
   
   
   operator void * ()
   {
      
      return m_pdata;
      
   }
   
#ifdef __MM
   
   operator ::nswindow ()
   {
      return window();
   }
   
#endif
   
   static bool remove(nswindow window);
   
   
   oswindow & operator = (const oswindow & window);
   
   bool operator == (const void * p) const
   {
      return m_pdata == p;
   }
   bool operator != (const void * p) const
   {
      return m_pdata != p;
   }
   bool operator == (const oswindow & w) const
   {
      return m_pdata == w.m_pdata;
   }
   bool operator != (const oswindow & w) const
   {
      return m_pdata != w.m_pdata;
   }
   
   nswindow window()
   {
      return m_pdata == NULL ? NULL : m_pdata->m_nswindow;
   }
   
    void set_user_interaction(::user::interaction_base * pui);
    ::user::interaction_base * get_user_interaction_base();
    ::user::interaction_base * get_user_interaction_base() const;
    ::user::interaction * get_user_interaction();
    ::user::interaction * get_user_interaction() const;
   
   
   
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   
};

inline oswindow GetParent(::oswindow oswindow)
{
   return oswindow.get_parent();
}

