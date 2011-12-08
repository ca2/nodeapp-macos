#pragma once

namespace win
{

   /////////////////////////////////////////////////////////////////////////////
   // graphics_object abstract class for ::ca::graphics_sp SelectObject

   class CLASS_DECL_VMSWIN graphics_object :
      virtual public ::ca::graphics_object,
      virtual public hgdiobj_handle
   {
      // // DECLARE_DYNCREATE(::ca::graphics_object)
   public:

   // Attributes
   //   HGDIOBJ m_hObject;                  // must be first data member
      operator HGDIOBJ() const;
      HGDIOBJ get_os_data() const;

      static graphics_object* PASCAL from_handle(::ca::application * papp, HGDIOBJ hObject);
      static void PASCAL DeleteTempMap();
      BOOL Attach(HGDIOBJ hObject);
      HGDIOBJ Detach();

   // Constructors
      ::ca::graphics_object(); // must create a derived class object
      BOOL delete_object();

   // Operations
   #pragma push_macro("GetObject")
   #undef GetObject
      int _AFX_FUNCNAME(GetObject)(int nCount, LPVOID lpObject) const;
      int GetObject(int nCount, LPVOID lpObject) const;
   #pragma pop_macro("GetObject")
      UINT GetObjectType() const;
      BOOL CreateStockObject(int nIndex);
      BOOL UnrealizeObject();
      BOOL operator==(const ::ca::graphics_object& obj) const;
      BOOL operator!=(const ::ca::graphics_object& obj) const;

   // Implementation
   public:
      virtual ~graphics_object();
   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;
   #endif

      void * detach_os_data();
   };

} // namespace ca