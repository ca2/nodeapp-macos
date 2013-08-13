#pragma once


namespace mac
{


   class CLASS_DECL_DRAW2D_COCOA crypt :
      virtual public ::ca2::crypt
   {
   public:


      crypt(::ca2::application * papp);
      virtual ~crypt();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);


      virtual string get_crypt_key_file_path();



   };

   
} // namespace mac





