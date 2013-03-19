#pragma once


namespace mac2
{


   class CLASS_DECL_mac2 printer :
      virtual public ::user::printer
   {
   public:


      class CLASS_DECL_mac2 document_properties :
         virtual public ::ca::object
      {
      public:


//         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::ca::application * papp);
         virtual ~document_properties();


  //       virtual bool initialize(::win2::printer * pprinter, DEVMODE * pdevmode = NULL);
         virtual bool initialize(::mac2::printer * pprinter);
         virtual bool close();
         virtual ::ca::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::ca::application * papp);
      virtual ~printer();


      virtual bool open(const char * pszDeviceName);
      virtual ::ca::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };
   
   
} // namespace macU






