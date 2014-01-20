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

/*namespace user
{
    
    
    class interaction_base;
    class interaction;
    
    
} // namespace user
*/

struct oswindow_data;


typedef struct oswindow_data * oswindow;


#define MESSAGE_WINDOW_PARENT (::oswindow((void *) (int_ptr) 1))

/*
 #ifdef __cplusplus

template < class KEY, class VALUE > class simple_map;


typedef int_to_int simple_long_map;

#endif*/
//class oswindow_data;

   
   
inline int32_t IsWindow(oswindow oswindow);
inline int32_t IsChild(oswindow oswindowParent, oswindow oswindowCandidateChildOrDescendant);
inline oswindow GetParent(oswindow oswindow);
inline oswindow SetParent(oswindow window, oswindow windowNewParent);
inline int32_t ShowWindow(oswindow oswindow, int32_t nCmdShow);
inline int32_t GetWindowLongA(oswindow oswindow, int32_t nIndex);
inline int32_t SetWindowLongA(oswindow oswindow, int32_t nIndex, int32_t l);
inline int32_t ClientToScreen(oswindow oswindow, POINT * lppoint);
inline int32_t ScreenToClient(oswindow oswindow, POINT * lppoint);
inline int32_t IsIconic(oswindow oswindow);
inline int32_t IsWindowVisible(oswindow oswindow);


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA
