#pragma once

namespace mac
{

   class CLASS_DECL_DRAW2D_COCOA factory_exchange :
      virtual public ::ca2::object
   {
   public:
      factory_exchange(::ca2::application * papp);
      virtual ~factory_exchange();
   };

} // namespace mac