// ImageFile.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
    
//--------------------------------------------------------------
//  BMP

BOOL CImage::LoadBMP(LPCSTR lpstrFileName)
{
	BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
	RGBQUAD  ColorTab[256];
    FILE	*fp;

	std::cout << "LoadBMP(LPCSTR lpstrFileName)" << " | " << lpstrFileName << std::endl;
        
	fp=fopen(lpstrFileName,"rb");
	if (fp==NULL)
		return(FALSE);

    fread(&BFH,sizeof(BITMAPFILEHEADER),1,fp);
    fread(&BIH,sizeof(BITMAPINFOHEADER),1,fp);

	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) {
		fclose(fp);   
 		return(FALSE);
	}
 
	Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0);

    if (nNumColors>0) {
 		fread(ColorTab,4,nNumColors,fp);
		SetColorTable(0,nNumColors,ColorTab);
	}

	fseek(fp,BFH.bfOffBits,SEEK_SET);
    fread(lpBits,nSize,1,fp);
	fclose(fp);   
   	return(TRUE);
}

BOOL CImage::SaveBMP(LPCSTR lpstrFileName)
{
	BITMAPFILEHEADER BFH={'MB',0,0,0,0};
    BITMAPINFOHEADER Bmih={40,1,1,1,8,0,0,0,0,0,0};
	RGBQUAD	ColorTab[256];
	DWORD	dwBmiSize;
 	FILE	*fp;
      
    dwBmiSize=40+4*nNumColors;

	fp=fopen(lpstrFileName,"w+b");
	if (fp==NULL)
		return(FALSE);

	BFH.bfSize   =sizeof(BITMAPFILEHEADER)+dwBmiSize+nSize;
	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+nNumColors*sizeof(RGBQUAD);

	Bmih.biWidth = nWidth;
	Bmih.biHeight = nHeight;
	Bmih.biBitCount = nBitCount;

    fwrite(&BFH,1,sizeof(BITMAPFILEHEADER),fp);
    fwrite((BYTE*)&Bmih,1,40,fp);
	if (nBitCount<=8) {
		GetColorTable(0,nNumColors,ColorTab);
		fwrite(ColorTab,4,nNumColors,fp);
	}
    fwrite(lpBits,1,nSize,fp);
	fclose(fp);
   	return(TRUE);
}
//  BMP

//--------------------------------------------------------------
//  TIF

BOOL CImage::LoadTIF(LPCSTR lpstrFileName)
{
	DWORD	ColorMap;
	FILE	*fp;
	struct	TIF_IFH head;
	struct	TIF_DE dir[25];
 	WORD	tif_pal[768];
	WORD	k,m,n,t,nn,c1,c2,Dx,Dy,Bits;
 	WORD	TifBytesPerLine,OffBits,ImageType,Compression;
    BYTE 	VgaPal[768],BmpPal[1024],*buf,*p;
 	int		i,j,flag=0;
 
	fp=fopen(lpstrFileName,"rb"); 
	if (fp==NULL)
		return(FALSE);

    fread(&head,1,8,fp); 
    fseek(fp,head.FirstIFD,SEEK_SET);
    fread(&nn,2,1,fp);
    fread(dir,12,nn,fp);
 
    for (i=0;i<nn;i++) { 
		switch(dir[i].Tag) {
			case IMAGEWIDTH :
				Dx=(WORD) dir[i].ValOff;
				break;
			case IMAGELENGTH :
				Dy=(WORD) dir[i].ValOff;
				break;
			case BITSPERSAMPLE :
				if (dir[i].Length>2)  Bits=24;
				else Bits=(WORD) dir[i].ValOff;
				break;
			case COMPRESSION :
				Compression=(WORD) dir[i].ValOff;  
				break;
			case PHOTOMETRICINTERP :
				ImageType=(WORD) dir[i].ValOff;    
				break;
			case STRIPOFFSETS :
				if (dir[i].Length==1)
					OffBits=(WORD) dir[i].ValOff;
				else {
					fseek(fp,dir[i].ValOff,SEEK_SET);
					fread(&OffBits,4,1,fp);
				}
				break;
			case COLORMAP :
				ColorMap=dir[i].ValOff;
				n=(WORD) dir[i].Length;
				fseek(fp,ColorMap,SEEK_SET);
				fread(tif_pal,2,n,fp);
  				p=(BYTE *) VgaPal;    
				n/=3;
				for (m=0;m<n;m++) {  	
					for (j=0,k=0;j<3;j++,k+=n)
						p[3*m+j] = (tif_pal[m+k] >> 8) & 0xff;
				}
				break;
			default :  
				break;
		}
		if (ImageType<2) {		  
			p=(BYTE *) VgaPal;
			if (Bits==1) {
				if (ImageType==0)  {  c1=0;    c2=255;  }
				else               {  c1=255;  c2=0;    }
				for (j=0;j<3;j++)   p[j]  =(BYTE) c2;
				for (j=0;j<3;j++)   p[3+j]=(BYTE) c1;
			}
			else {
				for (t=0;t<256;t++) {
					k=t;
					if (ImageType==0)   k=255-k;
					for (j=0;j<3;j++)   p[3*t+j]=(BYTE) k;
				}
			}
		}
	}

	if (Compression!=1) {
		fclose(fp);
		return(FALSE);
	}

	nWidth   =Dx;
	nHeight  =Dy;
	nBitCount=Bits;

	Create(nWidth,nHeight,nBitCount,0);

    if (nBitCount==1)       TifBytesPerLine=(nWidth+7)/8;
    else if (nBitCount==4)  TifBytesPerLine=(nWidth+1)/2;
    else if (nBitCount==8)  TifBytesPerLine=nWidth;
    else if (nBitCount==24) TifBytesPerLine=3*nWidth;
  
	for (i=0;i<nNumColors;i++) {
		for (j=0;j<3;j++) { 
			BmpPal[4*i+j]=VgaPal[3*i+2-j]; 
		}
		SetColorTable(0,nNumColors,(RGBQUAD*)BmpPal);
	}
 
	buf=lpBits+(nHeight-1)*nBytesPerLine;
 	fseek(fp,OffBits,SEEK_SET);
 	for (i=0;i<nHeight;i++) {
		fread(buf,1,TifBytesPerLine,fp);
 		if (nBitCount==24) {
 			for (j=0,k=0;j<nWidth;j++,k+=3) {
				m=buf[k+2];
 				buf[k+2]=buf[k];
				buf[k]=(BYTE) m;		     
			}
		}
 		buf-=nBytesPerLine;
	}
  
    fclose(fp);
   	return(TRUE);
}

BOOL CImage::SaveTIF(LPCSTR lpstrFileName)
{
	struct TIF_IFH head;
	struct TIF_DE dir[]={
	       0x100,4,1,0,    0x101,4,1,0,
	       0x102,3,1,0,    0x103,3,1,1,
	       0x106,3,1,0,    0x111,4,1,0,
	       0x115,3,1,0,    0x140,3,0x300,0
	};
	RGBQUAD ColorTab[256];
	long	long2,ll;
	WORD	tif_pal[768];
	int		i,j,k,m,n,t,flag=0;
	int		OffBits,ImageType,TifBytesPerLine;
    BYTE 	*buf,*buf1,*p;
   	FILE	*fp;
 	
	fp=fopen(lpstrFileName,"w+b");
	if (fp==NULL)
		return(FALSE);

	if (nBitCount<=8) 
		GetColorTable(0,nNumColors,ColorTab);
 
 	switch(nBitCount){
	case 1:
   		if (ColorTab[0].rgbBlue==255) 
			ImageType=0;
		else
			ImageType=1;
		TifBytesPerLine=(nWidth+7)/8;
 		break;
	case 4:;
		ImageType=3;	
		TifBytesPerLine=(nWidth+1)/2;
		break;
	case 8:
		ImageType=3;;
		TifBytesPerLine=nWidth;
		break;
	case 24:
		ImageType=2;;
		TifBytesPerLine=3*nWidth;
		break;
	}

    memset(head.ByteOrder,'I',2);
    head.Version  = 0x2a;     
	head.FirstIFD = 8;
    dir[0].ValOff = nWidth;    
	dir[1].ValOff = nHeight;
  	dir[4].ValOff = ImageType;
    if (nBitCount==24) 	dir[6].ValOff = 3;
	else  dir[6].ValOff = 1;
	
    n=7;
    if (dir[4].ValOff==3) n++;

    long2=10+12*n+4;
    if (nBitCount==24) {
		dir[2].Length = 3;      
		dir[2].ValOff = long2;
		long2+=6;
    }
    else dir[2].ValOff = nBitCount;

    OffBits=long2;
    if (dir[4].ValOff==3) {
		if (nBitCount==8)
			OffBits+=768*2;
		else if (nBitCount==4) {
			OffBits+=48*2;
			dir[7].Length=0x30;
		}
		dir[7].ValOff=long2;
    }

    dir[5].ValOff=OffBits;    
	ll=0;
    fwrite(&head,8,1,fp);
    fwrite(&n,2,1,fp);	
    fwrite(dir,12,n,fp);
    fwrite(&ll,4,1,fp);	
    if (nBitCount==24) {		
		for (j=0,m=8;j<3;j++)
			fwrite(&m,2,1,fp);
    }
    if (dir[4].ValOff==3) {
 		p=(BYTE *) ColorTab;
 		if (nBitCount==4) k=16;
		else k=256;
		for (i=0;i<3;i++) {
			for (j=0;j<k;j++) {
				n=((int) p[4*j+2-i]) & 0xff;    
				m=n | (n<<8);
				tif_pal[k*i+j]=m;
			}
		}
		if (nBitCount==8)
			fwrite(tif_pal,2,768,fp);
		else if (nBitCount==4)  
			fwrite(tif_pal,2,48,fp);
    }

	buf1=lpBits+(nHeight-1)*nBytesPerLine;
	buf =(BYTE*) malloc(4*(nWidth+1));	
 	fseek(fp,OffBits,SEEK_SET);		
	for (i=0;i<nHeight;i++) {
		memcpy(buf,buf1,nBytesPerLine);
 		if (nBitCount==24) {			    
			for (j=0,k=0;j<nWidth;j++,k+=3) {
				t=buf[k];
 				buf[k]=buf[k+2];    
				buf[k+2]=(BYTE) t;	
			}
		}
 		fwrite(buf,1,TifBytesPerLine,fp);
 		buf1-=nBytesPerLine;
	}
	fclose(fp);					      
	free(buf);

   	return(TRUE);
}
//  TIF

//--------------------------------------------------------------
//  GIF

int   index,rement;
char  rem;
char  *CTfirst,*CTlast,strbuf[256];
int   *CTnext,*CTlink,CLEAR,EOI,len,max,next;

int  LoadCode(int len,FILE *fp)
{
  int value,mask,start,used;

  start=value=0;
  while(len > 0) {
    if (rement == 0) {
      while(index == 0) index=getc(fp);
      index--;
      rem=(unsigned char) getc(fp);
      rement=8;
    }
    if (len > rement)  used = rement;
    else               used = len;
    rement -= used;
    mask = (0xff>>(8-used));
    mask &= rem;       rem  >>= used;
    mask <<= start;    start += used;
    value |= mask;     len   -= used;
  }
  return(value);
}

void InitStringTable(int size,int flag)
{
  int i;

  len=size+1;        max=1<<len;
  CLEAR=1<<size;     EOI=CLEAR+1;
  next=CLEAR+2;
  for (i=0;i<CLEAR;i++) {
    CTfirst[i]=i;    CTlast[i]=i;
    if (flag==1)     CTlink[i]=-1;
    else {
      CTlink[i]=-2;  CTnext[i]=-1;
    }
  }
  for (i=CLEAR;i<4096;i++) {
    CTlink[i]=-2;
    if (flag==2) CTnext[i]=-1;
  }
}

void AddStringToTable(int S,int K)
{
  CTlast[next] =CTfirst[K];
  CTlink[next] =S;
  CTfirst[next]=CTfirst[S];
  if (++next == max) {
    if (len < 12) {
      len++;	         max<<=1;
    }
  }
}

int  StringFromCode(int i,int K,BYTE *buff)
{
  while(K != -1) {
    buff[i++]=CTlast[K];   K=CTlink[K];
  }
  return(i);
}

int  WriteString(int xx,int i,BYTE *buff,BYTE *buffer)
{
  for (i--;i>=0;i--)  buffer[xx++]=buff[i];
  return(xx);
}

void unpack_LZWline(FILE *fp,int width,BYTE *buffer,int flag)
{
  static int  size,K,S,xx;
  int  i;
  BYTE buff[1024];

  if (flag > 0) {
    CTfirst=(char*) malloc(4096);
	CTlast =(char*) malloc(4096);
	CTnext =(int *) malloc(4096*sizeof(int));
	CTlink =(int *) malloc(4096*sizeof(int));
    rement=0;        rem=0; 
    index=0;
    S=-1;            xx=0;
    fread(&size,1,1,fp);
    InitStringTable(size,1);
  }
  else if (flag==0) {                                                  
    if (xx >= width) {
      if (xx>width)
	for (i=0;i<xx-width;i++) buffer[i]=buffer[i+width];
      xx-=width;
    }
    while((K=LoadCode(len,fp)) != EOI) { 
      if (K == CLEAR) {                  
	    InitStringTable(size,1);         
	    S=-1;                            
      }
      else {
	    if (S != -1) {                   
	      if (CTlink[K] == -2)           
	        AddStringToTable(S,S);       
	      else  AddStringToTable(S,K);
		}
	    i =StringFromCode(0,K,buff);     
	    xx=WriteString(xx,i,buff,buffer); 
	    S=K;                              
	    if (xx >= width)  break;          
      }
    }
  }
  else {
    free(CTfirst);
	free(CTlast);
	free(CTnext);
	free(CTlink);
  }
}

void WriteCode(int code,int len,FILE *fp)    
{                                      
  int  aln,used,cl;

  cl=len;                     aln=rement+len;
  while(aln >= 8) {
    if (rement > 0) {
      used=8-rement;
      strbuf[index++]=rem|(code<<rement);
      code=code >> used;
      cl -= used;             rement=0;
    }
    else {
      strbuf[index++]=code;
      cl -= 8;                code=code >> 8;
    }
    aln-=8;
    if (index == 256) {
      strbuf[0]=(char) 0xff;
      fwrite(strbuf,index,1,fp);
      index=1;
    }
  }
  if (rement == 0) {
    rem=code;                 rement=cl;
  }
  else {
    rem|=(code << rement);    rement+=cl;
  }
}

int IsInTable(int S,BYTE K)            
{
  int  code;

  if (S==-1)  code=K;                  
  else if (CTlink[S]==-2) {            
    CTlink[S]=next;      CTlast[next++]=K;      
    code=-1;
  }
  else {                                        
    code=CTlink[S];
    while((CTnext[code]!=-1) && (CTlast[code]!=K))  
      code=CTnext[code];
    if (CTlast[code] != K) {              
      CTnext[code]=next;    CTlast[next++]=K; 
      code=-1;
    }
  }
  return(code);
}

void pack_LZWline(FILE *fp,int width,BYTE *buffer,int flag)
{						       
  static int  size,S;
  BYTE   K,*ptr;
  int    j,SK;

  if (flag > 0) {              
    CTfirst=(char*) malloc(4096);
	CTlast =(char*) malloc(4096);
	CTnext =(int *) malloc(4096*sizeof(int));
	CTlink =(int *) malloc(4096*sizeof(int));
	rement=0;        rem=0;
    index=1;
    S=-1;            size=flag;
    fwrite(&size,1,1,fp);
    InitStringTable(size,2);
    WriteCode(CLEAR,len,fp);   
  }
  else if (flag==0) {                   
    for (j=0,ptr=buffer;j<width;j++) {
      K=*ptr++;                         
      SK=IsInTable(S,K);                
      if (SK != -1)  S=SK;              
      else {
	    WriteCode(S,len,fp);            
	    S=K;                            
      }
      if (next > max) {                 
	    if (len == 12) {
	      WriteCode(S,len,fp);
	      WriteCode(CLEAR,len,fp);      
	      InitStringTable(size,2);
	      S=-1;
        }
	    else {
	      len++;	      max=max<<1;
	      if (len == 12)      max--;
		}
      }
    }
  }
  else {                                
    WriteCode(S,len,fp);                
    WriteCode(EOI,len,fp);              
    if (rement != 0)  strbuf[index++]=rem;     
    if (index != 1) {
      strbuf[0]=(unsigned char) (index-1);
      fwrite(strbuf,index,1,fp);
    }
    fputc(0,fp);
    fputc(';',fp);                             
    free(CTfirst);
	free(CTlast);
	free(CTnext);
	free(CTlink);
  }
}

BOOL CImage::LoadGIF(LPCSTR lpstrFileName)
{
	struct	GIF_GLOBAL gifglobal;
	struct	GIF_LOCAL  giflocal;
    BYTE 	VgaPal[768],BmpPal[1024],*buf2,*buf3;
  	FILE	*fp;
	int		i,j,flag=0;
 
	fp=fopen(lpstrFileName,"rb"); 
	if (fp==NULL)
		return(FALSE);

    fread(&gifglobal,13,1,fp);    
    nWidth   = gifglobal.screen_width;
    nHeight  = gifglobal.screen_depth;
	flag     = gifglobal.global_flag;;
    nBitCount= (flag & 7)+1;
 
	Create(nWidth,nHeight,nBitCount,0);

    fread(VgaPal,3,nNumColors,fp); 
 	for (i=0;i<nNumColors;i++) {
		for (j=0;j<3;j++) { 
			BmpPal[4*i+j]=VgaPal[3*i+2-j]; 
		}
		SetColorTable(0,nNumColors,(RGBQUAD*)BmpPal);
	}
    fread(&giflocal,10,1,fp);
 
	buf2=lpBits+(nHeight-1)*nBytesPerLine;
 	buf3=(BYTE*) malloc(2*nWidth);
	unpack_LZWline(fp,nWidth,buf3,1);   
	for (i=0;i<nHeight;i++) {
		unpack_LZWline(fp,nWidth,buf3,0);
		if (nBitCount==1)
			Trans8To1(buf2,buf3,nWidth);
		else if (nBitCount==4)
			Trans8To4c(buf2,buf3,nWidth);
		else
			memcpy(buf2,buf3,nBytesPerLine);
		buf2-=nBytesPerLine;
	}
	unpack_LZWline(fp,nWidth,buf3,-1);
 	free(buf3);
	fclose(fp);  

   	return(TRUE);
}

BOOL CImage::SaveGIF(LPCSTR lpstrFileName)
{
 	struct GIF_GLOBAL gifglobal = {
	            'G','I','F','8','7','a',0,0,0,0,0 };
	struct GIF_LOCAL  giflocal = {
		        ',',0,0,0,0,0 };
	RGBQUAD ColorTab[256];
 	FILE	*fp;
    BYTE 	buf[1024],*buf1,*buf2,*lpDibPal,ch=';';
	int		i,j;
       
	if (nBitCount>8) return(FALSE);
  
	fp=fopen(lpstrFileName,"w+b");
	if (fp==NULL)
		return(FALSE);

	gifglobal.screen_width = nWidth;
	gifglobal.screen_depth = nHeight;
	gifglobal.global_flag  =(BYTE)((nBitCount-1) | 0xf0);
    fwrite(&gifglobal,13,1,fp);
 
	GetColorTable(0,nNumColors,ColorTab);
	lpDibPal=(BYTE*) ColorTab;
  
	for (i=0;i<nNumColors;i++) {
		for (j=0;j<3;j++)
			buf[3*i+j]=lpDibPal[4*i+2-j];
	}
	fwrite(buf,3,nNumColors,fp);
 
	memcpy(buf,&giflocal,10);
//	giflocal.image_wide = wid;
 	buf[5]=nWidth & 0xff;	
	buf[6]=nWidth>>8;
//	giflocal.image_deep = hei;
	buf[7]=nHeight & 0xff;	
	buf[8]=nHeight>>8;
//	giflocal.local_flag =(BYTE)((bits-1) | 0xf0);
	buf[9]=(nBitCount-1) | 0xf0;
//  fwrite(&giflocal,10,1,fp);
    fwrite(buf,10,1,fp);

	buf1=lpBits+(nHeight-1)*nBytesPerLine;
	buf2=(BYTE*)malloc(nWidth+3);
 	pack_LZWline(fp,nWidth,buf1,8);
	for (j=0;j<nHeight;j++) {
		if (nBitCount==1) 
			Trans1To8(buf2,buf1,(nWidth+7)/8);
 		else if (nBitCount==4) 
			Trans4cTo8(buf2,buf1,(nWidth+1)/2);
		else 
  			memcpy(buf2,buf1,nBytesPerLine);
  		pack_LZWline(fp,nWidth,buf2,0);
		buf1-=nBytesPerLine;
	}
	pack_LZWline(fp,nWidth,buf1,-1);
	fwrite(&ch,1,1,fp);
	free(buf2);
 	fclose(fp);

   	return(TRUE);
}
//  GIF

//--------------------------------------------------------------
//  TGA

static int PaletteType(RGBQUAD  *ColorTab)
{
 	int		i,k,m,n,r,g,b;
 
	m=n=0;
	for (i=0; i<256; i++)
	{
		r = ColorTab[i].rgbRed;
		g = ColorTab[i].rgbGreen;
		b = ColorTab[i].rgbBlue;
		if ((r != g)||(r != b)) m=0;
		if ((i>0)&&(r>ColorTab[i-1].rgbRed)) m++;
		if (r+g+b==0) n++;
	}
	k=3;
 	if (m == 255) k=2;    
	else  if (256-n==1) k=0;                     
	else  if (256-n==15) k=1;                     
 	return(k);
}

BOOL CImage::LoadTGA(LPCSTR lpstrFileName)
{
	struct	TGA_HEAD tgahead;
  	FILE	*fp;
    BYTE 	buf[18],Pal[1024],*buf1;
	int		type,i,j,n;
         
	fp=fopen(lpstrFileName,"rb"); 
	if (fp==NULL)
		return(FALSE);

    fread(&tgahead,18,1,fp);
	if ((tgahead.ImageType & 0x08)||
		(tgahead.AttribBit & 0x30)) {
		fclose(fp);
		return(FALSE);
	}

	memcpy(buf,&tgahead,18);
 	nWidth   = buf[12]+256*buf[13];
//	wid =bmi.biWidth   =(int) tgahead.Width;
	nHeight  = buf[14]+256*buf[15];
//	hei =bmi.biHeight  =(int) tgahead.Height;
	nBitCount= buf[16]; 
//	bits=Bmih.biBitCount=(int) tgahead.Bits; 
 
	Create(nWidth,nHeight,nBitCount,0);

    if (nNumColors>0) {
		type=(BYTE)(tgahead.ImageType & 0x7);
 		if (type==1) {
			fread(Pal,3*nNumColors,1,fp); 
  			for (i=255;i>=0;i--) {
 				for (j=0;j<3;j++) Pal[4*i+j]=Pal[3*i+j];
				Pal[4*i+3]=0;
			}
		}
		else if (type==3) {
 			for (i=0;i<256;i++) {
 				for (j=0;j<3;j++) Pal[4*i+j]=i;
				Pal[4*i+3]=0;
			}
		}
		SetColorTable(0,nNumColors,(RGBQUAD*)Pal);
	}
 
	buf1=lpBits;
	n=nWidth*nBytesPerPixel;
	for (i=0;i<nHeight;i++) {
		fread(buf1,1,n,fp);
 		buf1+=nBytesPerLine;
	}
	fclose(fp);
 
   	return(TRUE);
}

BOOL CImage::SaveTGA(LPCSTR lpstrFileName)
{
 	struct	TGA_HEAD tgahead;
	RGBQUAD ColorTab[256];
 	FILE	*fp;
    BYTE 	buf[18],Pal[1024],*buf1;
	int		type,i,j,ImageType;
      
	if (nBitCount<8) return(FALSE);
  
	fp=fopen(lpstrFileName,"w+b");
	if (fp==NULL)
		return(FALSE);

 	memset(buf,0,18);
//	tgahead.Width=wid;
	buf[12]=nWidth & 0xff;	
	buf[13]=nWidth>>8;
//	tgahead.Height=hei;
	buf[14]=nHeight & 0xff;	
	buf[15]=nHeight>>8;
//	tgahead.Bits=(BYTE)bits; 
	buf[16]=(BYTE) nBitCount;
	memcpy(&tgahead,buf,18);

 	if (nBitCount==8) {
		GetColorTable(0,nNumColors,ColorTab);
 		type=PaletteType(ColorTab);
		if (type==3) {
			tgahead.ColorType=1;
 			ImageType=1;  
			tgahead.ColorLength=256;
 			tgahead.ColorBit=24;
		}
		else ImageType=3;	
	}
	else if (nBitCount==24) ImageType=2;	

	tgahead.ImageType=(BYTE) ImageType;
 
    fwrite(&tgahead,1,18,fp);
  	if (type==3) { 
		memcpy(Pal,ColorTab,1024);
 		for (i=0;i<256;i++) {
			for (j=0;j<3;j++) Pal[3*i+j]=Pal[4*i+j];
		}
		fwrite(Pal,1,768,fp);
	}

	buf1=lpBits;
	for (i=0;i<nHeight;i++) {
 		fwrite(buf1,nBytesPerPixel,nWidth,fp);
		buf1+=nBytesPerLine;
	}
 	fclose(fp);

   	return(TRUE);
}
//  TGA

//--------------------------------------------------------------
//  PCX

void loadPCXline(BYTE *p,int wid,FILE *fp)
{  
	int n=0,i,c;
 
	memset(p,0,wid);
	do{
		c=fgetc(fp); 
		if((c&0xc0)==0xc0) {
			i=c&0x3f;       
			c=fgetc(fp);    
			while(i--)  p[n++]=c;  
		}
		else  p[n++]=c;
	}
	while(n<wid);
}

BOOL CImage::LoadPCX(LPCSTR lpstrFileName)
{
	struct	PCX_HEAD PCX_head;
 	FILE	*fp;
    BYTE 	*buf,*buf1,VgaPal[768],BmpPal[1024];
 	int		i,j,k,Version,Planes;
	int		Lbits,PcxBytesPerLine,TotalBytesPerLine;
 
	fp=fopen(lpstrFileName,"rb");
	if (fp==NULL)
		return(FALSE);

 	fread(&PCX_head,128,1,fp);

	Version            =(int) PCX_head.Version;
	if (Version != 5) 
 		return(FALSE);

    nWidth   =(int) PCX_head.X2-PCX_head.X1+1;
    nHeight  =(int) PCX_head.Y2-PCX_head.Y1+1;
    Lbits              =(int) PCX_head.BitPerPixel;
    Planes             =(int) PCX_head.NumOfPlanes;
    PcxBytesPerLine    =(int) PCX_head.BytesPerLine;
	nBitCount= Lbits*Planes; 
 
	Create(nWidth,nHeight,nBitCount,0);
 
  	TotalBytesPerLine  = PcxBytesPerLine*Planes;
	buf =(BYTE*) malloc(TotalBytesPerLine);
  	buf1=lpBits+(nHeight-1)*nBytesPerLine;
   	for (j=0;j<nHeight;j++) {
 		loadPCXline(buf,TotalBytesPerLine,fp);
 		if (Planes==4) {
			Trans4pTo4c(buf1,buf,PcxBytesPerLine,nBytesPerLine);
		}
		else if (Planes==3) {
			for (i=0,k=0;i<PcxBytesPerLine;i++,k+=3) {
				buf1[k+2]=buf[i];
				buf1[k+1]=buf[PcxBytesPerLine+i];
				buf1[k]  =buf[2*PcxBytesPerLine+i];
			}
		}
		if (Planes==1)
			memcpy(buf1,buf,nBytesPerLine);
		buf1-=nBytesPerLine;
	}
	free(buf);
  
    if (nNumColors>0) {
		if (nBitCount==8) {
			fseek(fp,-768,SEEK_END);
			fread(VgaPal,3,nNumColors,fp);
		}
		else {
			memcpy(VgaPal,&PCX_head,128);
   			for (i=0;i<48;i++) VgaPal[i]=VgaPal[i+16];
		}
		memset(BmpPal,0,1024);
   		for (i=0;i<nNumColors;i++) {
 			for (j=0;j<3;j++) BmpPal[4*i+j]=VgaPal[3*i+2-j];
		}
 		SetColorTable(0,nNumColors,(RGBQUAD*) BmpPal);
	}
    fclose(fp);

   	return(TRUE);
}

void savePCXline(BYTE *buf,int pwide,FILE *fp)
{
  int   j,k,gray,n=0;
  BYTE  *buf1;

  buf1=(BYTE*) malloc(2*pwide);
  for (j=0;j<pwide;j++) {
    gray=buf[j];              k=1;  
    j++;
    while((j<pwide)&&(gray==buf[j])) {
      k++;                    j++;
    }
    j--;
    while(k>63) {                     
      buf1[n++]=0xff;         buf1[n++]=gray;
      k-=63;
    }
    if (k==1) {                       
      if (gray<0xc0)          buf1[n++]=gray;   
      else {                                    
	    buf1[n++]=0xc1;       buf1[n++]=gray;
      }
	}
    else { buf1[n++]=0xc0+k;  buf1[n++]=gray;   }
  }
  fwrite(buf1,1,n,fp);
  free(buf1);
}

BOOL CImage::SavePCX(LPCSTR lpstrFileName)
{
 	struct	PCX_HEAD PCX_head;
	RGBQUAD ColorTab[256];
 	int		i,j,k,flag=0,P_flag=12;
	int		Planes,PcxBytesPerLine,TotalBytesPerLine;
	FILE	*fp;
    BYTE 	VgaPal[1024],*lpDibPal;
	BYTE	*buf,*buf1,*sc,*buf0;
 
	fp=fopen(lpstrFileName,"w+b");
	if (fp==NULL)
		return(FALSE);
 
	memset(&PCX_head,0,128);
	Planes=1;
	if (nBitCount==4) Planes=4;
	else if (nBitCount==24) Planes=3;
 	if (nBitCount<8)  
		PcxBytesPerLine  = (nWidth+7)/8; 
	else PcxBytesPerLine = nWidth;
	PcxBytesPerLine = (PcxBytesPerLine+1)/2*2;
	TotalBytesPerLine=PcxBytesPerLine*Planes;

	if (nBitCount<=8) {
		GetColorTable(0,nNumColors,ColorTab);
		lpDibPal=(BYTE*) ColorTab;
	}
    if (nBitCount<8) {
		for (i=0;i<nNumColors;i++) {
			for (j=0;j<3;j++)
				VgaPal[3*i+j]=lpDibPal[4*i+2-j];
		}
		memcpy(PCX_head.pal,VgaPal,48);
	}

    PCX_head.Header       = 10;
    PCX_head.Version      = 5;
    PCX_head.Encode       = 1;
    PCX_head.BitPerPixel  = (BYTE) nBitCount/Planes;
    PCX_head.X1           = 0;
    PCX_head.Y1           = 0;
    PCX_head.X2           = nWidth-1;
    PCX_head.Y2           = nHeight-1;
    PCX_head.NumOfPlanes  = (BYTE) Planes;
    PCX_head.BytesPerLine = PcxBytesPerLine;
    fwrite(&PCX_head,128,1,fp);

	buf0=lpBits+(nHeight-1)*nBytesPerLine;
	sc =(BYTE*)malloc(4*nWidth);
	buf=(BYTE*)malloc(4*nWidth);
	buf1=buf;
	for(i=0;i<nHeight;i++) {
		memcpy(sc,buf0,nBytesPerLine);
 		if (Planes==1) buf1=sc;
 		else if (Planes==4) {
			Trans4cTo4p(buf,sc,PcxBytesPerLine,nBytesPerLine);
		}
		else if (Planes==3) {
			for (j=0,k=0;j<PcxBytesPerLine;j++,k+=nBytesPerPixel) {
				buf[j]=sc[k+2];       
				buf[j+PcxBytesPerLine]=sc[k+1];
				buf[j+2*PcxBytesPerLine]=sc[k];
			}
		}
		savePCXline(buf1,TotalBytesPerLine,fp); 
		buf0-=nBytesPerLine;
	}
	free(sc);
	free(buf);

    if (nBitCount==8) {
 		fwrite(&P_flag,1,1,fp);
		for (i=0;i<256;i++) {
			for (j=0;j<3;j++)
				VgaPal[3*i+j]=lpDibPal[4*i+2-j];
		}
		fwrite(VgaPal,768,1,fp);
	}
	fclose(fp); 

   	return(TRUE);
}

//  PCX
//--------------------------------------------------------------
