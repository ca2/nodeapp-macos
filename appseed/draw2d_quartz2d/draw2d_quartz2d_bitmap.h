#pragma once


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D bitmap : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::bitmap
   {
   public:
      
      
      COLORREF *              m_pdata;
      ::size                  m_size;
      CGContextRef            m_context;
      int32_t                 scan;
      
      
      bitmap(sp(::base::application) papp);
      virtual ~bitmap();
      
      
      void * get_os_data() const;
      
      
      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
#ifndef ___NO_AFXCMN_SUPPORT
      // xxx      bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = NULL, int32_t nMapSize = 0);
#endif
      bool CreateBitmap(::draw2d::graphics * pdc, int32_t nWidth, int32_t nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits);
      bool CreateBitmapIndirect(::draw2d::graphics * pdc, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      bool CreateDIBSection(::draw2d::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, int * piStride, HANDLE hSection, uint32_t offset);
      bool CreateDIBitmap(::draw2d::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);
      
      int32_t GetBitmap(BITMAP* pBitMap);
      
      DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
      class size SetBitmapDimension(int32_t nWidth, int32_t nHeight);
      class size GetBitmapDimension() const;
      
      virtual void dump(dump_context & dumpcontext) const;
      
      virtual bool Attach(void * posdata);
      
      bool destroy();

      
   };

   
} // namespace draw2d_quartz2d




