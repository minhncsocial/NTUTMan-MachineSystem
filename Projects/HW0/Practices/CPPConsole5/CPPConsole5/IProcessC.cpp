//   IProcessC.cpp

#include "stdafx.h"
     
#ifndef		_INC_IPROCESSCC
#define		_INC_IPROCESSCC

void ColorToGray(CImage *pImgn,CImage *pImgm) 
{
 	int			i, x, y;
	int			gray[256];
	BYTE		*cbuf,*gbuf;
	RGBQUAD		ColorTab[256];
 	CImage		gpImg;
 	CString		str1;
 	struct		IMAGEPARAMENT P;

	GetImageParament(pImgm,&P);             
	if (P.nBitCount<8) return;
 
 	gpImg.Create(P.nWidth,P.nHeight,8,0);   
	for (i=0; i<256; i++)
	{
		ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = 
			                  ColorTab[i].rgbRed   = i;
	}
	gpImg.SetColorTable(0,256,ColorTab);    

	if (pImgm->GetBPP()<=8) {               
 		pImgm->GetColorTable(0,P.nNumColors,ColorTab);
		for (i=0; i<P.nNumColors; i++)
		{
			gray[i] = (int) (0.11*ColorTab[i].rgbBlue + 
				     0.59*ColorTab[i].rgbGreen + 0.30*ColorTab[i].rgbRed);
		}
		for (y=0; y<P.nHeight; y++) {
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y); 
			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
			for (x=0; x<P.nWidth; x++) 
				gbuf[x] = (BYTE) gray[cbuf[x]];         
 		}
	} 
	else {   
		for (y=0; y<P.nHeight; y++) {
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y); 
			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
			for (x=0,i=0; x<P.nWidth; x++,i+=P.nBytesPerPixel) {
				gbuf[x] = (BYTE) (0.11*cbuf[i] + 0.59*cbuf[i+1] + 0.30*cbuf[i+2]);
			}
		}
	}

 	ImageCopy(pImgn,&gpImg);
 	gpImg.Destroy();
}

void ImageInvert(CImage *pImgm)   
{
	int		i,y,k,m;
	BYTE	*buf;
 	RGBQUAD ColorTab[256];
 	struct	IMAGEPARAMENT P;

	GetImageParament(pImgm,&P);  
	k=ImageType(pImgm);
	if (k%2==0) {     
		if (k==0) m=1;
		else m=255;
		for (y=0; y<P.nHeight; y++) {
			buf = (BYTE*) pImgm->GetPixelAddress(0,y); 
			for (i=0; i<P.nBytesPerLine; i++) buf[i] = m - buf[i];
		}
	} 
	else {   
 		pImgm->GetColorTable(0,P.nNumColors,ColorTab);
		for (i=0; i<P.nNumColors; i++)
		{
			ColorTab[i].rgbBlue  = 255 - ColorTab[i].rgbBlue;
			ColorTab[i].rgbGreen = 255 - ColorTab[i].rgbGreen;
			ColorTab[i].rgbRed   = 255 - ColorTab[i].rgbRed;
		}
		pImgm->SetColorTable(0,P.nNumColors,ColorTab);
 	}
}

void ColorToMonochrom(CImage *pImgm)  
{
 	int		i,m,x,y,gray;
	BYTE	*buf;
 	RGBQUAD ColorTab[256];
 	struct	IMAGEPARAMENT P;

	GetImageParament(pImgm,&P);   
	if (pImgm->GetBPP()>8) {
		for (y=0; y<P.nHeight; y++) {
			buf = (BYTE*) pImgm->GetPixelAddress(0,y);
			for (x=0,i=0; x<P.nWidth; x++,i+=P.nBytesPerPixel) { 
				m=(int)(0.11*buf[i]+0.59*buf[i+1]+0.30*buf[i+2]);
 				buf[i] = buf[i+1] = buf[i+2] = m;
			}  
		}
	} 
	else {
 		pImgm->GetColorTable(0,P.nNumColors,ColorTab);
		for (i=0; i<P.nNumColors; i++)
		{
			gray = (int) (0.11*ColorTab[i].rgbBlue + 0.59*ColorTab[i].rgbGreen + 
				         0.30*ColorTab[i].rgbRed);
			ColorTab[i].rgbBlue = (BYTE)gray;
			ColorTab[i].rgbGreen = (BYTE)gray;
			ColorTab[i].rgbRed = (BYTE)gray; 
		}
		pImgm->SetColorTable(0,P.nNumColors,ColorTab);
 	}
}

void LowTypeToIndex(CImage *pImgn,CImage *pImgm)  
{                                 
	int			i,k,t,y,nBytesPerLine;
	RGBQUAD		ColorTab[256];
	CImage		gpImg;
 	BYTE		*cbuf,*gbuf;
 	struct		IMAGEPARAMENT P;
 
 	GetImageParament(pImgm,&P);              
	if (P.nBitCount>4) return;

 	gpImg.Create(P.nWidth,P.nHeight,8,0);      
    memset(ColorTab,0,1024);                    
 	pImgm->GetColorTable(0,P.nNumColors,ColorTab);  
	gpImg.SetColorTable(0,256,ColorTab);          

	nBytesPerLine = (P.nWidth*P.nBitCount+7)/8;
  	if (P.nBitCount==1)                               
	{
		for (y=0;y<P.nHeight;y++) 
		{
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y);    
			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
			for (i=0;i<nBytesPerLine;i++) 
			{
				for (k=0,t=0x80;k<8;k++)         
				{
					if (cbuf[i]&t)
						gbuf[8*i+k]=1;
					else
						gbuf[8*i+k]=0;
					t = t>>1;
				}
			}
  		}
	} 
	else if (P.nBitCount==4)                          
	{
		for (y=0; y<P.nHeight; y++) 
		{
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y);    
			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
			for (i=0; i<nBytesPerLine; i++) 
			{
				gbuf[2*i+1]= cbuf[i] & 0xf;      
				gbuf[2*i]  = cbuf[i]>>4;
			}
		}
	}
	if (pImgm==pImgn)                                    
 		ImageCopy(pImgm,&gpImg);
 	else                                        
 		ImageCopy(pImgn,&gpImg);
 	gpImg.Destroy();
}

void IndexToLowType(CImage *pImgn,CImage *pImgm)
{
 	struct	IMAGEPARAMENT P,Pg;
 	RGBQUAD ColorTab[256];
	CImage	gImg,*pImg;
	int		i,k,n,s,t,y;
 	BYTE	*cbuf,*gbuf;
 
	if (pImgm==pImgn) pImg=&gImg;
	else              pImg=pImgn;
 	GetImageParament(pImgm,&P);
 	if (ImageType(pImgm)==0) {
		pImg->Create(P.nWidth,P.nHeight,1,0);
		GetAllPalette(pImgm,ColorTab);
		SetPalette(pImg,0,ColorTab[0].rgbRed,
			ColorTab[0].rgbGreen,ColorTab[0].rgbBlue);
		SetPalette(pImg,1,ColorTab[1].rgbRed,
			ColorTab[1].rgbGreen,ColorTab[1].rgbBlue);
  		GetImageParament(pImg,&Pg);
 		for (y=0;y<P.nHeight;y++) {
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y);
			gbuf = (BYTE*) pImg->GetPixelAddress(0,y);
			memset(gbuf,0,Pg.nBytesPerLine);
			for (i=0,k=0;i<P.nWidth;i+=8) {
				for (n=0,t=0,s=0x80;n<8;n++) {
					if (cbuf[i+n]==1) t |= s;
					s = s  >> 1;
				}
				gbuf[k++]=t;
			}
		}
	}
	else if (ImageType(pImgm)==1) {
		pImg->Create(P.nWidth,P.nHeight,4,0);
		GetAllPalette(pImgm,ColorTab);
		SetAllPalette(pImg,ColorTab);
 		for (y=0;y<P.nHeight;y++) {
			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y);
			gbuf = (BYTE*) pImg->GetPixelAddress(0,y);
 			for (i=0,k=0;i<P.nWidth;i+=2,k++) {
				gbuf[k]=(cbuf[i]<<4)+(cbuf[i+1]&0x0f);  
			}
		}
	}
	if (pImgm==pImgn) {   
 		ImageCopy(pImgm,pImg);
  		pImg->Destroy();
	}
}

void Flip(CImage *pImgm,int n)         
{
	int		i,j,k,m;
	DWORD	dd;
	BYTE	*buff1,*buff2;
 	struct	IMAGEPARAMENT P;

  	GetImageParament(pImgm,&P);              
 
 	buff1=(BYTE*) malloc(P.nBytesPerLine);
	buff2=(BYTE*) malloc(P.nBytesPerLine);
	if ((n&0x1)==1) {
		m=(P.nWidth-1)*P.nBytesPerPixel;
		for (i=0;i<P.nHeight;i++) {
			GetRectValue(pImgm,0,i,P.nWidth,1,buff1);
			for (j=0,k=0;j<P.nWidth/2;j++,k+=P.nBytesPerPixel) {  
 				memcpy(&dd,&buff1[k],P.nBytesPerPixel);
				memcpy(&buff1[k],&buff1[m-k],P.nBytesPerPixel);
				memcpy(&buff1[m-k],&dd,P.nBytesPerPixel);
			}
 			SetRectValue(pImgm,0,i,P.nWidth,1,buff1);
		}
	}

	if ((n&0x2)==2) {
		for (i=0;i<P.nHeight/2;i++) {
			GetRectValue(pImgm,0,i    ,P.nWidth,1,buff1);     
			GetRectValue(pImgm,0,P.nHeight-1-i,P.nWidth,1,buff2);
			SetRectValue(pImgm,0,i    ,P.nWidth,1,buff2);
			SetRectValue(pImgm,0,P.nHeight-1-i,P.nWidth,1,buff1);
		}
	}
	free(buff1);
	free(buff2);
}

void Rotate90(CImage *pImgn,CImage *pImgm,int n)      
{
  	int			i,j,k,m;
	RGBQUAD		ColorTab[256];
	DWORD		dd;
	BYTE		*buff;
 	struct		IMAGEPARAMENT P;

	GetImageParament(pImgm,&P);              
	pImgn->Destroy();
	pImgn->Create(P.nHeight,P.nWidth,P.nBitCount,0);        

 	buff=(BYTE*) malloc(P.nBytesPerLine);
 	m=(P.nWidth-1)*P.nBytesPerPixel;
	for (i=0;i<P.nHeight;i++) {
		GetRectValue(pImgm,0,i,P.nWidth,1,buff);    
		if (n==1)
			SetRectValue(pImgn,P.nHeight-1-i,0,1,P.nWidth,buff);   
		                                         
		else
		{
			for (j=0,k=0;j<P.nWidth/2;j++,k+=P.nBytesPerPixel) {
				memcpy(&dd,&buff[k],P.nBytesPerPixel);      
				memcpy(&buff[k],&buff[m-k],P.nBytesPerPixel);
				memcpy(&buff[m-k],&dd,P.nBytesPerPixel);
			}
			SetRectValue(pImgn,i,0,1,P.nWidth,buff);  
		}
	}
	free(buff);
 	if (P.nNumColors>0)
	{
		pImgm->GetColorTable(0,P.nNumColors,ColorTab);         
		pImgn->SetColorTable(0,P.nNumColors,ColorTab);
	}
}

void ImageMasaic(CImage *pImgm,int n)
{
  	struct	IMAGEPARAMENT P;
	int     Dx,Dy,i,j,s,t;
	BYTE	*buf,*buf1;
 
	GetImageParament(pImgm,&P);              
	Dx=P.nWidth/n*n;
	Dy=P.nHeight/n*n;
 	for (j=0;j<Dy;j+=n)          
	{
		buf=(BYTE*) pImgm->GetPixelAddress(0,j); 
		for (i=0;i<Dx;i+=n)
		{
			for (s=1;s<n;s++)		
				memcpy(&buf[(i+s)*P.nBytesPerPixel],&buf[i*P.nBytesPerPixel],P.nBytesPerPixel);   
		}
		for (t=1;t<n;t++) {                             
			buf1=(BYTE*) pImgm->GetPixelAddress(0,j+t);
			memcpy(buf1,buf,P.nBytesPerLine);
		}
 	}
}

void ZoomIn(CImage *pImgn,CImage *pImgm,int n)   
{
 	int		i, j, k;
	RGBQUAD	ColorTab[256];
	BYTE	*buf,*buf0,*buf1;
  	struct	IMAGEPARAMENT P;
 
	GetImageParament(pImgm,&P);              
 	pImgn->Destroy();
	pImgn->Create(P.nWidth*n,P.nHeight*n,P.nBitCount,0);      

 	if (P.nNumColors>0)
	{
		pImgm->GetColorTable(0,P.nNumColors,ColorTab);    
		pImgn->SetColorTable(0,P.nNumColors,ColorTab);    
	}

  	for (i=0;i<P.nHeight;i++) {
		buf0 = (BYTE*) pImgm->GetPixelAddress(0,i);    
		buf  = (BYTE*) pImgn->GetPixelAddress(0,i*n);
		for (j=0;j<P.nWidth;j++,buf0+=P.nBytesPerPixel)
		{
			for (k=0;k<n;k++,buf+=P.nBytesPerPixel)
    			memcpy(buf,buf0,P.nBytesPerPixel);          
  		}
	}

	GetImageParament(pImgn,&P);              
  	for (i=0;i<P.nHeight;i+=n) 
	{
		buf  = (BYTE*) pImgn->GetPixelAddress(0,i);
		for (j=1;j<n;j++) {
 			buf1=(BYTE*) pImgn->GetPixelAddress(0,i+j);
			memcpy(buf1,buf,P.nBytesPerLine);
		}
   	}
}

void ZoomOut(CImage *pImgn,CImage *pImgm,int n) 
{  
	int			i, j;
	RGBQUAD		ColorTab[256];
	BYTE		*buf,*buf0;
 	struct		IMAGEPARAMENT P;

	GetImageParament(pImgm,&P);              
 	pImgn->Destroy();
	pImgn->Create(P.nWidth/n,P.nHeight/n,P.nBitCount,0);     
 
 	if (P.nNumColors>0)
	{
		pImgm->GetColorTable(0,P.nNumColors,ColorTab);
		pImgn->SetColorTable(0,P.nNumColors,ColorTab);
	}
  
 	for (i=0;i<P.nHeight/n;i++) {
		buf0 = (BYTE*) pImgm->GetPixelAddress(0,i*n);
		buf  = (BYTE*) pImgn->GetPixelAddress(0,i);
		for (j=0;j<P.nWidth/n;j++)
		{
 			memcpy(buf, buf0, P.nBytesPerPixel);
			buf+=P.nBytesPerPixel;
			buf0+=n*P.nBytesPerPixel;
  		}
 	}
}

void ImageRotate(CImage *pImgn,CImage *pImgm,double alpha)
{  
 	struct	IMAGEPARAMENT P;
	int     i,j,ww,Xd,Yd,Dx,Dy;
	double  centerx,centery,sintheta,costheta;
	double  X1,Y1,X2,Y2,theta,xx,yy,rr;
	RGBQUAD ColorTab[256];
	BYTE    **list,*sc;
 	int		x1,y1,x2,y2,flag;
	double	p,q,a,b,c,d,t1,t2,t3;
 
	if (ImageType(pImgm)==2) flag=1;
	else  flag=0;
   	GetImageParament(pImgm,&P);              
 
	Dx=P.nWidth;		Dy=P.nHeight;
	sc=(BYTE*) malloc(2*P.nBytesPerLine);
	list=(BYTE**)malloc(Dy*sizeof(BYTE*));
	for (i=0;i<Dy;i++)  
		list[i]=(BYTE*) pImgm->GetPixelAddress(0,i);
 
	centerx=Dx/2;    centery=Dy/2;
	rr=sqrt(centerx*centerx+centery*centery);
	theta=atan((double) centery/(double) centerx);
	X1=fabs(rr*cos(alpha+theta))+0.5;
	Y1=fabs(rr*sin(alpha+theta))+0.5;
	X2=fabs(rr*cos(alpha-theta))+0.5;
	Y2=fabs(rr*sin(alpha-theta))+0.5;
	if (X2>X1)  X1=X2;
	if (Y2>Y1)  Y1=Y2;
	ww=(int) (2*X1);
 
	pImgn->Destroy();
	pImgn->Create(ww,(int) (2*Y1),P.nBitCount);

	if (P.nBitCount==8) {
 		GetAllPalette(pImgm,ColorTab);
		SetAllPalette(pImgn,ColorTab);
 	}
	sintheta=sin(alpha);
	costheta=cos(alpha);

	for (j=(int)(centery-Y1),Yd=0;j<=centery+Y1;j++,Yd++) {
		if (P.nBitCount==8)
			memset(sc,0,ww);
		else
			memset(sc,0,ww*P.nBytesPerPixel);
		for (i=(int)(centerx-X1),Xd=0;i<=centerx+X1;i++,Xd+=P.nBytesPerPixel) {
			xx=centerx+costheta*(i-centerx)+sintheta*(j-centery);
			yy=centery-sintheta*(i-centerx)+costheta*(j-centery);
			x1=(int) xx;      
			x2=x1+1;       
			p=xx-x1;
			y1=(int) yy;
			y2=y1+1;       
			q=yy-y1;
			if (((x1<0)||(x2>=P.nWidth)||(y1<0)||(y2>=P.nHeight))) continue;
 			if (flag==0) {     
				if (q>0.5) y1=y2;
				if (p>0.5) x1=x2;
  				memcpy(&sc[Xd],&list[y1][P.nBytesPerPixel*x1],P.nBytesPerPixel);
			}
			else {             
				a=(double) list[y1][x1];	
				b=(double) list[y1][x2];	
				c=(double) list[y2][x1];
				d=(double) list[y2][x2];
				t1=(1-p)*a+p*b;
				t2=(1-p)*c+p*d;
				t3=(1-q)*t1+q*t2;
				sc[Xd]=(BYTE) t3;
			}
 		}
		SetRectValue(pImgn,0,Yd,ww,1,sc);
	}
	free(list);
	free(sc);
}

void ImageScale(CImage *pImgn,CImage *pImgm,double alpha) 
{
 	struct	IMAGEPARAMENT P;
	RGBQUAD ColorTab[256];
	int     i,j,nSize;
    BYTE    **list,*sc;
	int     Dx,Dy,x1,y1,x2,y2,flag;
 	double	p,q,a,b,c,d,t1,t2,t3;
     
 	if (ImageType(pImgm)==2) flag=1;
	else  flag=0;
 	GetImageParament(pImgm,&P);              
    Dx=(int) (alpha*P.nWidth);
	Dy=(int) (alpha*P.nHeight);
 	pImgn->Destroy();
	pImgn->Create(Dx,Dy,P.nBitCount);
 
	if (P.nBytesPerPixel==1) 
	{                                            
 		for (i=0;i<P.nNumColors;i++) 
		{
			GetAllPalette(pImgm,ColorTab);
			SetAllPalette(pImgn,ColorTab);
 		}
	}
 
	nSize=(int)((P.nBytesPerLine+P.nHeight*P.nBytesPerPixel)*alpha);
	sc  =(BYTE*) malloc(nSize);
	list=(BYTE**)malloc(Dy*sizeof(BYTE*));       
	for (i=0;i<P.nHeight;i++) 
		list[i]=(BYTE*) pImgm->GetPixelAddress(0,0)-i*P.nBytesPerLine;     

	for (j=0;j<Dy;j++) 
	{
		q=j/alpha;    
		y1=(int) q;
		y2=y1+1;       
		q=q-y1;
		for (i=0;i<Dx;i++) 
		{
			p=i/alpha;    
			x1=(int) p;                          
			x2=x1+1;       
			p=p-x1;                              
 			if (x2==P.nWidth) x2--;
			if (y2==P.nHeight) y2--;
 			if (flag==0) 
			{                                    
				if (q>0.5) y1=y2;
				if (p>0.5) x1=x2;
 				memcpy(&sc[i*P.nBytesPerPixel],&list[y1][x1*P.nBytesPerPixel],P.nBytesPerPixel);
			}
			else 
			{                                    
				a=(double) list[y1][x1];	
				b=(double) list[y1][x2];	
				c=(double) list[y2][x1];
				d=(double) list[y2][x2];
				t1=(1-p)*a+p*b;
				t2=(1-p)*c+p*d;
				t3=(1-q)*t1+q*t2;
				sc[i]=(BYTE) t3;
			}
  		}
		SetRectValue(pImgn,0,j,Dx,1,sc);     
	}
	free(sc);
	free(list);
}

#endif  //!_INC_IPROCESSCC
 