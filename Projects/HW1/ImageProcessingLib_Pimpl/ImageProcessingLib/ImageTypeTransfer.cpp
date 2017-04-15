#include "ImageTypeTransfer.h"

void Trans1To8(BYTE *sc,BYTE *buf,int BytesPerLine)
{
  int  j,m,n;

  for (j=0;j<BytesPerLine;j++)  {
    for (n=0,m=0x80;n<8;n++) {
      if ((buf[j]) & m)  sc[8*j+n]=1;
      else               sc[8*j+n]=0;
      m=m>>1;
    }
  }
}

void Trans8To1(BYTE *sc,BYTE *buf,int Width)
{
  int  k,j,n,s,t;

  for (j=0,k=0;j<Width;j+=8) {
    for (n=0,t=0,s=0x80;n<8;n++) {
      if (buf[j+n]) t |= s;
      s = s  >> 1;
    }
    sc[k++]=t;
  }
}

void Trans4cTo8(BYTE *sc,BYTE *buf,int BytesPerLine)
{
  int  j;

  for (j=0;j<BytesPerLine;j++)  {
    sc[2*j+1] =  buf[j] & 0xf;
    sc[2*j]   = (buf[j]>>4);
  }
}

void Trans8To4c(BYTE *sc,BYTE *buf,int Width)
{
  int  j;

  for (j=0;j<Width;j+=2)
    sc[j/2] = (buf[j]<<4) | buf[j+1];
}

void Trans4pTo8(BYTE *sc,BYTE *buf,int BytesPerLine)
{
  int  j,k,l,m,n,t;
  BYTE *sc1,*buf1;

  memset(sc,0,8*BytesPerLine);
  for (j=0,m=1,buf1=buf;j<4;j++) {
    for (k=0,sc1=sc;k<BytesPerLine;k++) {
      n=0x80;       t=*buf1++;
      for (l=0;l<8;l++) {
	if (t & n)  *sc1 |= m;
	n=n>>1;      sc1++;
      }
    }
    m=m<<1;
  }
}

void Trans8To4p(BYTE *sc,BYTE *buf,int BytesPerLine)
{
  int  j,k,l,m,n;
  BYTE *sc1,*buf1;

  memset(sc,0,4*BytesPerLine);
  for (j=0,m=1,sc1=sc;j<4;j++) {
    for (k=0,buf1=buf;k<BytesPerLine;k++) {
      for (l=0,n=0x80;l<8;l++) {
	if (m & *buf1++)  *sc1 |= n;
	n=n>>1;
      }
      sc1++;
    }
    m=m<<1;
  }
}

void Trans4pTo4c(BYTE *sc,BYTE *buf,int BytesPerLine,int bpl)
{
	int  j,k,l,m1,m2,n1,n2,t;
	BYTE *sc1,*buf1;

	memset(sc,0,bpl);
	for (j=0,m1=0x10,m2=1;j<4;j++) {
		buf1=buf+j*BytesPerLine;
 		for (k=0,sc1=sc;k<BytesPerLine;k++) {
			t=*buf1++;
			if (4*k==bpl) break;
 			n1=0x80;
			n2=0x40;
 			for (l=0;l<4;l++) {
				if (t & n1)  *sc1 |= m1;
				if (t & n2)  *sc1 |= m2;
				sc1++;
				n1=n1>>2;      
				n2=n2>>2;      
			}
		}
		m1=m1<<1;
		m2=m2<<1;
	}
}

void Trans4cTo4p(BYTE *sc,BYTE *buf,int BytesPerLine,int bpl)
{
	int  j,k,l,m1,m2,n1,n2;
	BYTE *sc1,*buf1;

	memset(sc,0,4*BytesPerLine);
	m1=0x10;		m2=1;
	for (j=0,sc1=sc;j<4;j++) {
		for (k=0,buf1=buf;k<BytesPerLine;k++) {
 			n1=0x80;	n2=0x40;
			for (l=0;l<8;l+=2) {
				if (m1 & *buf1)   *sc1 |= n1;
				if (m2 & *buf1++) *sc1 |= n2;
				n1=n1>>2;		n2=n2>>2;
			}
			sc1++;
		}
		m1=m1<<1;		m2=m2<<1;
	}
}

void Trans24To32(BYTE *sc,BYTE *buf,int Width)
{
  int  k,j,n;

  for (j=0,n=0,k=0;j<Width;j++,n+=3,k+=4) {
    sc[k]  =buf[n];		  sc[k+1]=buf[n+1];
    sc[k+2]=buf[n+2];
  }
}

void Trans32To24(BYTE *sc,BYTE *buf,int Width)
{
  int  k,j,n;

  for (j=0,n=0,k=0;j<Width;j++,n+=3,k+=4) {
    sc[n]  =buf[k];       sc[n+1]=buf[k+1];
    sc[n+2]=buf[k+2];
  }
}

void BmpToVga(BYTE *VgaPal,RGBQUAD *bgr,int n)
{
   int  i;

   for (i=0;i<n;i++) {
      VgaPal[3*i+2] = bgr[i].rgbBlue;      
	  VgaPal[3*i+1] = bgr[i].rgbGreen;
      VgaPal[3*i]   = bgr[i].rgbRed;
   }
}

void VgaToBmp(RGBQUAD *bgr,BYTE *VgaPal,int n)
{
   int  i;

   for (i=0;i<n;i++) {
      bgr[i].rgbBlue  = VgaPal[3*i+2];      
	  bgr[i].rgbGreen = VgaPal[3*i+1];
      bgr[i].rgbRed   = VgaPal[3*i];
   }
}

