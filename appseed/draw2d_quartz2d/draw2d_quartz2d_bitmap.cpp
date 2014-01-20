#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap(sp(base_application) papp) :
      element(papp)
   {
      
      m_context = NULL;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   bool bitmap::CreateBitmap(::draw2d::graphics * pdc, int32_t cx, int32_t cy, UINT nPlanes, UINT nBitcount, const void * pdata)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         throw not_implemented(get_app());
         
      }
      
      destroy();
      
      scan = cx * 4;
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
      
      m_context = CGBitmapContextCreate(NULL, cx, cy, 8, scan, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_context == NULL)
      {
         
         m_size.cx = 0;
         
         m_size.cy = 0;
         
         scan = 0;
         
         return false;
         
      }
      
      m_pdata = (COLORREF *) CGBitmapContextGetData(m_context);
      
      
      if(m_pdata == NULL)
      {
         
         destroy();
         
         return false;
         
      }
      
      if(pdata != NULL)
      {
      
         memcpy(m_pdata, pdata, cy * scan);
         
      }
      
      m_size.cx = cx;
      
      m_size.cy = cy;
      
      return true;
      
   }
   
   
   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pdc, LPBITMAP lpBitmap)
   {
      
      return FALSE;
      
   }
   
   
   bool bitmap::CreateDIBSection(::draw2d::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void ** ppdata, int * piStride, HANDLE hSection, uint32_t offset)
   {
      
      int32_t cx = abs(lpbmi->bmiHeader.biWidth);
      
      int32_t cy = abs(lpbmi->bmiHeader.biHeight);
      
      if(!CreateBitmap(pdc, cx, cy, 1, 32, NULL))
      {
         
         return false;
         
      }
      
      if(ppdata != NULL)
      {
         
         *ppdata = m_pdata;
         
      }
      
      if(piStride)
      {
         
         *piStride = scan;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDIBitmap(::draw2d::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage)
   {
      
      return false;
      
   }
   
   
   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {

      return 0;
      
   }
   
   
   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {

      return FALSE;
      
   }
   
   
   size bitmap::SetBitmapDimension(int32_t nWidth, int32_t nHeight)
   {
      
      return ::size(0, 0);
      
   }
   
   
   size bitmap::GetBitmapDimension() const
   {
      
      if(get_os_data() == NULL)
         return ::size(0, 0);
      
      return m_size;
      
   }
   
   
   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      
      //return Attach(::LoadBitmap(::ca2::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return FALSE;
      
   }
   
   
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      //return Attach(::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap)));
      return FALSE;
      
   }
   
   
   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int32_t cx, int32_t cy)
   {
      
      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, NULL))
      {
         
         return false;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight)
   {
      
      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   
   
   int32_t bitmap::GetBitmap(BITMAP* pBitMap)
   {
      
      return 0;
      
   }
   
   
   void bitmap::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);
      
      if(get_os_data() == NULL)
         return;
       
      //dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << m_size.cy;
      dumpcontext << "\nbm.bmWidth = " << m_size.cx;
      dumpcontext << "\nbm.bmWidthBytes = " << scan;
      dumpcontext << "\nbm.bmPlanes = " << 1;
      dumpcontext << "\nbm.bmBitsPixel = " << 32;
      dumpcontext << "\n";
      
   }
   
   
   void * bitmap::get_os_data() const
   {
      
      return m_context;
      
   }
   
   
   bool bitmap::Attach(void * pbitmapcontext)
   {
      
      if(m_context != NULL)
      {
         
         destroy();
         
         m_context = NULL;
         
      }
      
      m_context   = (CGContextRef) pbitmapcontext;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_context);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_context);
      
      scan        = (int) CGBitmapContextGetBytesPerRow(m_context);
      
      m_pdata     = (COLORREF *) CGBitmapContextGetData(m_context);
      
      return true;
      
   }
   
   
   bool bitmap::destroy()
   {
      
      if(m_context == NULL)
         return true;
      
      CGContextRelease(m_context);
      
      m_context = NULL;
      
      m_pdata = NULL;
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      scan = 0;
      
      return true;
      
   }
   
   
} // namespace draw2d_quartz2d







