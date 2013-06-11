#pragma once


namespace mac
{

   
   class CLASS_DECL_mac bitmap : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::bitmap
   {
   public:
      
      
      simple_memory           m_mem;
      ::size                  m_size;
      
      
      bitmap(::ca::application * papp);
      virtual ~bitmap();
      
      
      void * get_os_data() const;
      
      
      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
#ifndef ___NO_AFXCMN_SUPPORT
      // xxx      bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = NULL, int32_t nMapSize = 0);
#endif
      bool CreateBitmap(::ca::graphics * pdc, int32_t nWidth, int32_t nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits);
      bool CreateBitmapIndirect(::ca::graphics * pdc, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::ca::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDiscardableBitmap(::ca::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
      bool CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);
      
      int32_t GetBitmap(BITMAP* pBitMap);
      
      DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
      class size SetBitmapDimension(int32_t nWidth, int32_t nHeight);
      class size GetBitmapDimension() const;
      
      virtual void dump(dump_context & dumpcontext) const;
      
      virtual bool Attach(void * posdata);
      
      bool destroy();

      
   };

   
} // namespace mac




