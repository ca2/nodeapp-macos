#pragma once


namespace mac
{


   class CLASS_DECL_mac copydesk :
      virtual public ::ca2::copydesk,
      virtual public ::ca2::window_sp
   {
   public:


      copydesk(::ca2::application * papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(stringa & stra);

      virtual int32_t get_file_count();
      virtual void get_filea(stringa & stra);

      virtual void set_plain_text(const char * psz);
      virtual string get_plain_text();


      virtual bool desk_to_dib(::ca2::dib * pdib);
      // todo
      //bool dib_to_desk(::ca2::dib * pdib);

   };


} // namespace mac



