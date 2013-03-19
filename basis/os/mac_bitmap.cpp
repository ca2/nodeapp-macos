#include "framework.h"


namespace mac
{
   
   
   bitmap::bitmap(::ca::application * papp) :
   ca(papp)
   {
      
//      m_psurface = NULL;
      
   }
   
   bitmap::~bitmap()
   {
      
//    if(m_psurface != NULL)
      {
         
         destroy();
         
      }
      
   }
   
   bool bitmap::CreateBitmap(::ca::graphics * pdc, int32_t cx, int32_t cy, UINT nPlanes, UINT nBitcount, const void * pdata)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         throw not_implemented(get_app());
         
      }
      
//      if(m_psurface != NULL)
      {
         
         destroy();
         
      }
      
  //    int32_t iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cx);
      
    //  m_mem.allocate(iStride * cy);
      
      //if(cx * 4 != iStride)
      {
         
//         int32_t iW = cx * 4;
         
         for(int32_t i = 0; i < cy; i++)
         {
            
        //    memcpy(&((byte *) m_mem.get_data())[iStride * i], &((byte *) pdata)[iW * i], iW);
            
         }
         
      }
//      else
      {
        // memcpy(m_mem.get_data(), pdata, iStride * cy);
      }
      
      
//      m_psurface = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cx.., cy, iStride);
      
    //  if(m_psurface == NULL)
      {
         
         return false;
         
      }
      
      
      m_size.cx = cx;
      m_size.cy = cy;
      
      return true;
      
   }
   
   bool bitmap::CreateBitmapIndirect(::ca::graphics * pdc, LPBITMAP lpBitmap)
   {
      return FALSE;
   }
   
   
   bool bitmap::CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void ** ppdata, HANDLE hSection, DWORD offset)
   {
      
      /*BITMAPINFO m_Info;
       
       m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
       m_Info.bmiHeader.biWidth=cx;
       m_Info.bmiHeader.biHeight=cy;
       m_Info.bmiHeader.biPlanes=1;
       m_Info.bmiHeader.biBitCount=32;
       m_Info.bmiHeader.biCompression=BI_RGB;
       m_Info.bmiHeader.biSizeImage=cx*cy*4;*/
      
      m_mem.allocate(abs(lpbmi->bmiHeader.biWidth) * abs(lpbmi->bmiHeader.biHeight) * 4);
      
      memset(m_mem.get_data(), 0, m_mem.get_size());
      
      if(!CreateBitmap(pdc, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, 1, 32, (COLORREF *) m_mem.get_data()))
      {
         
         m_mem.allocate(0);
         
         return false;
         
      }
      
      if(ppdata != NULL)
      {
         
         *ppdata = (COLORREF *) m_mem.get_data();
         
      }
      
      
      
      return true;
      
   }
   
   
   bool bitmap::CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage)
   {
      return FALSE;
   }
   
   
   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {
      
      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;
      
   }
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {
      //return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;
   }
   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {
      //   return Attach(::LoadBitmap(::ca::FindResourceHandle(
      //lpszResourceName, RT_BITMAP), lpszResourceName));
      return FALSE;
      
   }
   
   size bitmap::SetBitmapDimension(int32_t nWidth, int32_t nHeight)
   {
      
      
      throw not_implemented(get_app());
      
      //SIZE size;
      //VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      //return size;
      return ::size(0, 0);
      
   }
   
   size bitmap::GetBitmapDimension() const
   {
//      if(m_psurface == NULL)
  //       return ::size(0, 0);
      
      return m_size;
      
   }
   
   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      //return Attach(::LoadBitmap(::ca::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return FALSE;
   }
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {
      //return Attach(::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap)));
      return FALSE;
   }
   bool bitmap::CreateCompatibleBitmap(::ca::graphics * pgraphics, int32_t cx, int32_t cy)
   {
      
      m_mem.allocate(cx * cy * 4);
      
      memset(m_mem.get_data(), 0, m_mem.get_size());
      
      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, (COLORREF *) m_mem.get_data()))
      {
         
         m_mem.allocate(0);
         
         return false;
         
      }
      
      
      return true;
      
      /*
       if(m_pdata != NULL)
       {
       ca2_free(m_pdata);
       m_pdata = NULL;
       }
       
       if(m_pbitmap != NULL)
       {
       delete m_pbitmap;
       m_pbitmap = NULL;
       }
       
       m_pbitmap = new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);
       */
      
      //      return TRUE;
      
   }
   bool bitmap::CreateDiscardableBitmap(::ca::graphics * pgraphics, int32_t nWidth, int32_t nHeight)
   {
      
      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   
   
   int32_t bitmap::GetBitmap(BITMAP* pBitMap)
   {
      //   ASSERT(get_handle() != NULL);
      // return ::GetObject(get_handle(), sizeof(BITMAP), pBitMap);
      return 0;
   }
   
   
   /////////////////////////////////////////////////////////////////////////////
   
   
   void bitmap::dump(dump_context & dumpcontext) const
   {
      ::ca::graphics_object::dump(dumpcontext);
      
      /*         if (get_handle() == NULL)
       return;
       
       if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_BITMAP)
       {
       // not a valid object
       dumpcontext << "has ILLEGAL HBITMAP!";
       return;
       }*/
      
      /*BITMAP bm;
       VERIFY(GetObject(sizeof(bm), &bm));
       dumpcontext << "bm.bmType = " << bm.bmType;
       dumpcontext << "\nbm.bmHeight = " << bm.bmHeight;
       dumpcontext << "\nbm.bmWidth = " << bm.bmWidth;
       dumpcontext << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
       dumpcontext << "\nbm.bmPlanes = " << bm.bmPlanes;
       dumpcontext << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;
       */
      dumpcontext << "\n";
   }
   
   
   
   
   void * bitmap::get_os_data() const
   {
      
//      return (void *) m_psurface;
      return NULL;
      
   }
   
/*   void get_surface_size (cairo_surface_t * psurface, LONG * plongWidth, LONG * plongHeight)
	{
      
      if(plongWidth != NULL)
      {
         
         *plongWidth = cairo_image_surface_get_width(psurface);
         
      }
      
      if(plongHeight != NULL)
      {
         
         *plongHeight = cairo_image_surface_get_height(psurface);
         
      }
      
      
	}*/
   
   
   bool bitmap::Attach(void * psurface)
   {
      
/*      if(m_psurface != 0)
      {
         
         destroy();
         
         m_psurface = NULL;
         
      }
      
      m_psurface = (cairo_surface_t *) psurface;
      
      get_surface_size((cairo_surface_t *) psurface, &m_size.cx, &m_size.cy);
*/
      return true;
      
   }
   
   void bitmap::destroy()
   {
      
/*      if(m_psurface == NULL)
         return;
      
      cairo_surface_destroy(m_psurface);
  */
      
      
   }
   
   
} // namespace mac



