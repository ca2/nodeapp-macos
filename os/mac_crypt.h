#pragma once


namespace mac
{


   class CLASS_DECL_mac crypt :
      virtual public ::ca::crypt
   {
   public:


      crypt(::ca::application * papp);
      virtual ~crypt();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);


      virtual string get_crypt_key_file_path();



   };

   
} // namespace mac





