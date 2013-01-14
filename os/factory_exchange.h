#pragma once

namespace mac
{

   class CLASS_DECL_VMSMAC factory_exchange :
      virtual public ::radix::object
   {
   public:
      factory_exchange(::ca::application * papp);
      virtual ~factory_exchange();
   };

} // namespace mac