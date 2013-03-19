#pragma once

namespace mac
{

   class CLASS_DECL_mac factory_exchange :
      virtual public ::ca::object
   {
   public:
      factory_exchange(::ca::application * papp);
      virtual ~factory_exchange();
   };

} // namespace mac