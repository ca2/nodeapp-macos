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

typedef struct tagPOINT
{
   int32_t  x;
   int32_t  y;
} POINT, *PPOINT;

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
   
   
   void post_nc_destroy();
   
   
   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int32_t nCmdShow);
   int32_t get_window_long(int32_t nIndex);
   int32_t set_window_long(int32_t nIndex, int32_t l);
   bool client_to_screen(POINT * lppoint);
   bool screen_to_client(POINT * lppoint);
   
   
   
   bool is_null() const
   {
      return m_pdata == NULL;
   }
   
};




inline bool IsWindow(oswindow oswindow)
{
   return oswindow.get_user_interaction() != NULL;
}

inline bool IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
{
   return oswindowParent.is_child(oswindowCandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow oswindow)
{
   return oswindow.get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{
   return oswindow.set_parent(oswindowNewParent);
}

inline bool ShowWindow(::oswindow oswindow, int32_t nCmdShow)
{
   return oswindow.show_window(nCmdShow);
}

inline int32_t GetWindowLongA(::oswindow oswindow, int32_t nIndex)
{
   return oswindow.get_window_long(nIndex);
}

inline int32_t SetWindowLongA(::oswindow oswindow, int32_t nIndex, int32_t l)
{
   return oswindow.set_window_long(nIndex, l);
}

inline bool ClientToScreen(::oswindow oswindow, POINT * lppoint)
{
   return oswindow.client_to_screen(lppoint);
}

inline bool ScreenToClient(::oswindow oswindow, POINT * lppoint)
{
   return oswindow.screen_to_client(lppoint);
}

inline int32_t IsIconic(::oswindow oswindow)
{
   return oswindow.is_iconic();
}

inline int32_t IsWindowVisible(::oswindow oswindow)
{
   return oswindow.is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA
