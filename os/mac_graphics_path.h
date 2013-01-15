//
//  mac_graphics_path.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 1/15/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


namespace mac
{
   
   
   class CLASS_DECL_mac graphics_path :
   virtual public ::ca::graphics_path
   {
   public:
      
      
      class CLASS_DECL_c arc
      {
      public:
         
         
         double   m_xCenter;
         double   m_yCenter;
         double   m_dRadiusX;
         double   m_dRadiusY;
         double   m_dAngle1;
         double   m_dAngle2;
         
         
      };
      
      class CLASS_DECL_c move
      {
      public:
         
         double   m_x;
         double   m_y;
         
      };
      
      
      class CLASS_DECL_c line
      {
      public:
         
         double   m_x;
         double   m_y;
         
      };
      
      
      class CLASS_DECL_c element
      {
      public:
         
         
         enum e_type
         {
            type_begin,
            type_arc,
            type_line,
            type_move,
            type_close,
         };
         
         
         union
         {
            
            
            arc      m_arc;
            move     m_move;
            line     m_line;
            
         };
         
         e_type m_etype;
         
         
      };
      
      simple_array < element >      m_elementa;
      bool                          m_bFill;
      ::ca::e_fill_mode             m_efillmode;
      bool                          m_bHasPoint;
      point                         m_pt;
      
      
      graphics_path(::ca::application * papp);
      virtual ~graphics_path();
      
      
      virtual bool has_current_point();
      virtual point last_point();
      
      virtual bool begin_figure(bool bFill, ::ca::e_fill_mode efillmode);
      virtual bool end_figure(bool bClose);
      
      virtual bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);
      virtual bool add_line(int32_t x, int32_t y);
      
      virtual bool add_move(int32_t x, int32_t y);
      
      
      
   };
   
   
   
   
   
   
   
   
   
} // namespace mac



