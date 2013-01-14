#pragma once

namespace mac
{

   class CLASS_DECL_VMSMAC bitmap : 
      virtual public ::mac::graphics_object,
      virtual public ::ca::bitmap
   {
   public:
      static bitmap * PASCAL from_handle(::ca::application * papp, HBITMAP hBitmap);

      bitmap(::ca::application * papp);

      WINBOOL LoadBitmap(const char * lpszResourceName);
      WINBOOL LoadBitmap(UINT nIDResource);
      WINBOOL LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
   #ifndef _AFX_NO_AFXCMN_SUPPORT
      WINBOOL LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0,
         LPCOLORMAP lpColorMap = NULL, int nMapSize = 0);
   #endif
      WINBOOL CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitcount,
            const void * lpBits);
      WINBOOL CreateBitmapIndirect(LPBITMAP lpBitmap);
      WINBOOL CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      WINBOOL CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      WINBOOL CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
      WINBOOL CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

   // Attributes
      operator HBITMAP() const;
      int GetBitmap(BITMAP* pBitMap);

   // Operations
      DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
      size SetBitmapDimension(int nWidth, int nHeight);
      size GetBitmapDimension() const;

   // Implementation
   public:
      virtual ~bitmap();
   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace mac