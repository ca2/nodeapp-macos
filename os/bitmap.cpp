#include "StdAfx.h"

namespace mac
{
   bitmap::bitmap(::ca::application * papp) :
      ca(papp)
   { 
   }

   bitmap::operator HBITMAP() const
   { 
      return (HBITMAP)(this == NULL ? NULL : get_handle()); 
   }
   bitmap* PASCAL bitmap::from_handle(::ca::application * papp, HBITMAP hBitmap)
   { 
      return dynamic_cast < bitmap * > (::mac::graphics_object::from_handle(papp, hBitmap)); 
   }
   bitmap::~bitmap()
   { }
   WINBOOL bitmap::CreateBitmap(int nWidth, int nHeight, UINT nPlanes,
      UINT nBitcount, const void * lpBits)
   { return Attach(::CreateBitmap(nWidth, nHeight, nPlanes, nBitcount, lpBits)); }
   WINBOOL bitmap::CreateBitmapIndirect(LPBITMAP lpBitmap)
   { return Attach(::CreateBitmapIndirect(lpBitmap)); }
   WINBOOL bitmap::CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)
   { return Attach(::CreateDIBSection(*WIN_DC(pdc), lpbmi, usage, ppvBits, hSection, offset)); }
   WINBOOL bitmap::CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage)
   { return Attach(::CreateDIBitmap(*WIN_DC(pdc), pbmih, flInit, pjBits, pbmi, iUsage)); }


   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   { return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits); }
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   { return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits); }
   WINBOOL bitmap::LoadBitmap(const char * lpszResourceName)
   { return Attach(::LoadBitmap(AfxFindResourceHandle(
   lpszResourceName, RT_BITMAP), lpszResourceName));}
   size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {
      SIZE size;
      VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      return size;
   }
   size bitmap::GetBitmapDimension() const
   {
      SIZE size;
      VERIFY(::GetBitmapDimensionEx((HBITMAP)get_handle(), &size));
      return size;
   }

   WINBOOL bitmap::LoadBitmap(UINT nIDResource)
   { return Attach(::LoadBitmap(AfxFindResourceHandle(
   MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource))); }
   WINBOOL bitmap::LoadOEMBitmap(UINT nIDBitmap)
   { return Attach(::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap))); }
   WINBOOL bitmap::CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight)
   { return Attach(::CreateCompatibleBitmap((dynamic_cast<::mac::graphics * >(pgraphics))->get_handle1(), nWidth, nHeight)); }
   WINBOOL bitmap::CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight)
   { return Attach(::CreateDiscardableBitmap((dynamic_cast<::mac::graphics * >(pgraphics))->get_handle1(), nWidth, nHeight)); }
   int bitmap::GetBitmap(BITMAP* pBitMap)
   { ASSERT(get_handle() != NULL);
   return ::GetObject(get_handle(), sizeof(BITMAP), pBitMap); }


      /////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
      void bitmap::dump(dump_context & dumpcontext) const
      {
         ::ca::graphics_object::dump(dumpcontext);

         if (get_handle() == NULL)
            return;

         if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_BITMAP)
         {
            // not a valid object
            dumpcontext << "has ILLEGAL HBITMAP!";
            return;
         }

         BITMAP bm;
         VERIFY(GetObject(sizeof(bm), &bm));
         dumpcontext << "bm.bmType = " << bm.bmType;
         dumpcontext << "\nbm.bmHeight = " << bm.bmHeight;
         dumpcontext << "\nbm.bmWidth = " << bm.bmWidth;
         dumpcontext << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
         dumpcontext << "\nbm.bmPlanes = " << bm.bmPlanes;
         dumpcontext << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;

         dumpcontext << "\n";
      }
#endif


} // namespace mac