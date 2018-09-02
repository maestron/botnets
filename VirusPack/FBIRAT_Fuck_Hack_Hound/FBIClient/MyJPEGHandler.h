#include <jpeglib.h>
#include <olectl.h>
#include <ole2.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <Tlhelp32.h>
#include <userenv.h>
#include <olectl.h>
#include <ole2.h>
#include <objbase.h>
#include <vfw.h>
#include <gdiplus.h>
#include <gdiplusenums.h>
/* **************************************************************** */
/* * FUNCTION LoadAnImage:                                        * */
/* * INPUT: path to the JPEG picture file                         * */ 
/* * OUTPUT: HBITMAP of loaded JPEG picture or 0 on error loading * */
/* **************************************************************** */
HBITMAP LoadJPEG(char* FileName)
   {
   // Use IPicture stuff to use JPG / GIF files
   IPicture* p;
   IStream* s;
//   IPersistStream* ps;
   HGLOBAL hG;
   void* pp;
   FILE* fp;

   
   // Read JPEG file in memory
   fp = fopen(FileName,"rb");
   if (!fp) return NULL;

   fseek(fp,0,SEEK_END);
   int fs = ftell(fp);
   fseek(fp,0,SEEK_SET);
   hG = GlobalAlloc(GPTR,fs);
   if (!hG){ fclose(fp); return NULL; }
   pp = (void*)hG;
   fread(pp,1,fs,fp);
   fclose(fp);

   // Create an IStream so IPicture can
   CreateStreamOnHGlobal(hG,false,&s);
   if (!s){ GlobalFree(hG); return NULL; }

   OleLoadPicture(s,0,false,IID_IPicture,(void**)&p);

   if (!p){  s->Release(); GlobalFree(hG); return NULL; }
   s->Release();
   GlobalFree(hG);

   HBITMAP hB = 0;
   p->get_Handle((unsigned int*)&hB);

   // Copy the image. Necessary, because upon p's release,
   // the handle is destroyed.
   HBITMAP hBB = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,LR_COPYRETURNORG);

   p->Release();
   return hBB;
   }
   
   
