//
//  oswindow.h
//  os
//
//  Created by Thomas Borregaard Sørensen on 11/4/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//




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

#ifndef __MM

struct NSWindow;

#endif


typedef NSWindow * nswindow;


class oswindow_data;


typedef oswindow_data * oswindow;


#define MESSAGE_WINDOW_PARENT (::oswindow((void *) (int_ptr) 1))


template < class KEY, class VALUE > class simple_map;


typedef simple_map < int32_t, int32_t > simple_long_map;


class CLASS_DECL_c oswindow_data
{
public:
   
   
   nswindow                      m_nswindow;
   ::user::interaction_base *    m_pui;
   
   
   static oswindow_dataptra *    s_pdataptra;
   simple_long_map *             m_plongmap;
   
   
   oswindow_data();
   oswindow_data(nswindow window);
   oswindow_data(const oswindow_data & oswindow);
   ~oswindow_data();
   
   
   operator void * ()
   {
      
      return this;
      
   }
   
   operator void * () const
   {
      
      return (void *) this;
      
   }
   
#ifdef __MM
   
   operator ::nswindow ()
   {
      return window();
   }
   
#endif
   
   oswindow_data & operator = (const oswindow_data & window);
   
   bool operator == (const void * p) const
   {
      return this == p;
   }
   bool operator != (const void * p) const
   {
      return this != p;
   }
   
   nswindow window()
   {
      return this == NULL ? NULL : m_nswindow;
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
      return this == NULL;
   }
   
};
   
   



int oswindow_find(nswindow window);
oswindow_data * oswindow_get(nswindow window);
bool oswindow_remove(nswindow window);




inline bool IsWindow(oswindow oswindow)
{
   return oswindow->get_user_interaction() != NULL;
}

inline bool IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
{
   return oswindowParent->is_child(oswindowCandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow oswindow)
{
   return oswindow->get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{
   return oswindow->set_parent(oswindowNewParent);
}

inline bool ShowWindow(::oswindow oswindow, int32_t nCmdShow)
{
   return oswindow->show_window(nCmdShow);
}

inline int32_t GetWindowLongA(::oswindow oswindow, int32_t nIndex)
{
   return oswindow->get_window_long(nIndex);
}

inline int32_t SetWindowLongA(::oswindow oswindow, int32_t nIndex, int32_t l)
{
   return oswindow->set_window_long(nIndex, l);
}

inline bool ClientToScreen(::oswindow oswindow, POINT * lppoint)
{
   return oswindow->client_to_screen(lppoint);
}

inline bool ScreenToClient(::oswindow oswindow, POINT * lppoint)
{
   return oswindow->screen_to_client(lppoint);
}

inline int32_t IsIconic(::oswindow oswindow)
{
   return oswindow->is_iconic();
}

inline int32_t IsWindowVisible(::oswindow oswindow)
{
   return oswindow->is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA
