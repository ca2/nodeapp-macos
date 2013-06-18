#pragma once


namespace mac
{
   
   
   class CLASS_DECL_mac font :
      virtual public ::ca2::font
   {
   public:
      
      
      font(::ca2::application * papp);
      virtual ~font();
      
      
      virtual void * get_os_data() const;
      
      virtual void dump(dump_context & dumpcontext) const;
      
      
   };
   
   
} // namespace mac



