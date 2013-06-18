#pragma once


namespace mac
{
   
   
   class CLASS_DECL_mac graphics_object :
   virtual public ::ca2::graphics_object
   {
   public:
      
      
      graphics_object();
      virtual ~graphics_object();
      
      
      virtual void * get_os_data() const;
      
      
      bool delete_object();
      
      
      int32_t get_object(int32_t nCount, LPVOID lpObject) const;
      UINT GetObjectType() const;
      bool CreateStockObject(int32_t nIndex);
      bool UnrealizeObject();
      bool operator==(const ::ca2::graphics_object& obj) const;
      bool operator!=(const ::ca2::graphics_object& obj) const;
      
      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;
      
   };
   
   
} // namespace mac
