/*
Module : IPENUM.H
Purpose: Interface for an ca2 API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (c) 1998 by PJ Naughter.


*/


namespace mac
{


   class CLASS_DECL_DRAW2D_COCOA ip_enum :
      virtual public ::ca2::ip_enum
   {
   public:


      ip_enum(::ca2::application * papp);
      virtual ~ip_enum();


      virtual ::count enumerate(stringa & stra);


   };


} // namespace mac




