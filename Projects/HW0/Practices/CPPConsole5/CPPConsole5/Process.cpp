#include "stdafx.h"
     
#ifndef		_INC_PROCESSC
#define		_INC_PROCESSC

extern	RGBQUAD  D_pal[256];

void WINAPI histog(BYTE **list,long *pg,int x, int y, int Dx, int Dy)
{                                                               
	int   i,j;

  	for (i=0;i<256;i++)  pg[i]=0;

	for(i=y;i<y+Dy;i++) 
 		for (j=x;j<x+Dx;j++)  
			pg[list[i][j]]++;	
}

void WINAPI GT(BYTE **list,int Dx,int Dy,int* T_gray)
{                                                
  int  i,j;

  for (i=0;i<Dy;i++) {                                 
    for (j=0;j<Dx;j++) {
       list[i][j]=T_gray[list[i][j]];      
    }
  }
}

void WINAPI GT_Equal(long* pg,int* T_gray)          
{
  long tt[256],sum;
  int  i;

  sum=0;                                             
  for (i=0;i<256;i++) {
     sum+=pg[i];	                                 
     tt[i]=sum;                                      
  }
  for (i=0;i<256;i++) {
     T_gray[i]=(int) (255*tt[i]/sum);                
  }
}

void WINAPI Border_Equal(long* pg,int* T_gray)     
{
	long tt[256],sum;
	int  i,k,m,max,no;

	pg[0]=pg[255]=0;
	HistogSmooth(pg,10);
	no=1;
	max=pg[1];
	for (i=2;i<255;i++) {
 		if (pg[i]>max) {
			max=pg[i];
			no=i;
 		}
	}
	no+=2;

	k=pg[no]/120+1;
	for (i=0;i<256;i++) pg[i]/=k;

	if (no<128) {
		for (k=no+1;k<250;k++) 
			if (pg[k-1]-pg[k]>=pg[k]-pg[k+3]) break;
 		m=k;
		sum=0;                                       
		for (i=m;i<256;i++) {
			sum+=pg[i];	                             
			tt[i]=sum;                               
		}
		for (i=0;i<m;i++) T_gray[i]=i;
		for (i=m;i<256;i++) {
			T_gray[i]=(int) (m+(255-m)*tt[i]/sum);   
		}
 	}
  	else
	{
		for (k=no-1;k>5;k--) 
			if (pg[k+1]-pg[k]>=pg[k]-pg[k-3]) break;
 		m=k;
		sum=0;                                       
		for (i=0;i<m;i++) {
			sum+=pg[i];	                             
			tt[i]=sum;                               
		}
		for (i=m;i<256;i++) T_gray[i]=i;
		for (i=0;i<m;i++) {
			T_gray[i]=(int) (m*tt[i]/sum);           
		}
	}
}

void WINAPI GT_histo_eq(long *pg,long *Hista,int* T_gray)    
{
   int    i,j,k;
   long   la,lb,sum,suma;
   double hist[256],hista[256];

   sum=suma=0;
   for (i=0;i<256;i++) {
      sum +=pg[i];
	  suma+=Hista[i];
   }
   la=lb=0;
   for (i=0;i<256;i++) {
      la+=pg[i];
      hist[i] =(double) la/sum;
      lb+=Hista[i];
      hista[i]=(double) lb/suma;
   }
   for (i=0,k=0;i<256;i++) {
	  for (j=255;j>k;j--) {
         if (hista[j]<=hist[i])  break;
	  }
      T_gray[i]=k=j;
   }
}

void WINAPI GT_linear(int* T_gray)                 
{
   int i;

   for (i=0;i<64;i++)
      T_gray[i]=i/2;
   for (i=64;i<192;i++)
      T_gray[i]=32+3*(i-64)/2;
   for (i=192;i<256;i++)
      T_gray[i]=128+i/2;
}

void WINAPI GT_square(int* T_gray)                 
{
   int i;

   for (i=0;i<256;i++)
      T_gray[i]=(long) i*i /255;
}

void WINAPI GT_sqrt(int* T_gray)                  
{
   int i;

   for (i=0;i<256;i++)
      T_gray[i]=(int) (sqrt((double) i/255)*255);
}

void WINAPI GT_log(int* T_gray)                 
{
   int i;

   for (i=0;i<256;i++)
      T_gray[i]=(int) ((log((double) (i+1))/log(256.0))*255);
}

void WINAPI GT_exp(int* T_gray)                  
{
   int i;

   for (i=0;i<256;i++)
	T_gray[i]=(int)exp(log(256.0)*i/255)-1;
}

void WINAPI GT_nega(int* T_gray)                 
{
   int i;

   for (i=0;i<256;i++)
      T_gray[i]=255-i;
}

void WINAPI DensitySegment(RGBQUAD *pal)                            
{
  int  i;

  for (i=1;i<255;i++) {
    pal[i].rgbBlue =D_pal[32+i/4*9/8].rgbBlue;
	pal[i].rgbGreen=D_pal[32+i/4*9/8].rgbGreen;
    pal[i].rgbRed  =D_pal[32+i/4*9/8].rgbRed;			
  }
  pal[0].rgbBlue=pal[0].rgbGreen=pal[0].rgbRed=0;
  pal[255].rgbBlue=pal[255].rgbGreen=pal[255].rgbRed=255;
}

void WINAPI PsendoColor(RGBQUAD *pal)                             
{
  int  i,j;

  for (i=0,j=0;i<64;i++,j+=4) {
    pal[i].rgbRed=0;			pal[i].rgbGreen=j;
    pal[i].rgbBlue=255;
  }
  for (i=64,j=0;i<128;i++,j+=4) {
    pal[i].rgbRed=0;			pal[i].rgbGreen=255;
    pal[i].rgbBlue=255-j;
  }
  for (i=128,j=0;i<192;i++,j+=4) {
    pal[i].rgbRed=j;			pal[i].rgbGreen=255;
    pal[i].rgbBlue=0;
  }
  for (i=192,j=0;i<256;i++,j+=4) {
    pal[i].rgbRed=255;		pal[i].rgbGreen=255-j;
    pal[i].rgbBlue=0;
  }
}

//---------------------------------------------------------------------------

int		Mask[3][3],Mask5[5][5],Scale,Offset; 

int  Tkirsch[72]={
     5,5,5,-3,0,-3,-3,-3,-3,
     5,5,-3,5,0,-3,-3,-3,-3,
     5,-3,-3,5,0,-3,5,-3,-3,
     -3,-3,-3,5,0,-3,5,5,-3,
     -3,-3,-3,-3,0,-3,5,5,5,
     -3,-3,-3,-3,0,5,-3,5,5,
     -3,-3,5,-3,0,5,-3,-3,5,
     -3,5,5,-3,0,5,-3,-3,-3 };
 
//   Robinson  
int  Trobinson[72]={
     1,2,1,0,0,0,-1,-2,-1,
     2,1,0,1,0,-1,0,-1,-2,
     1,0,-1,2,0,-2,1,0,-1,
     0,-1,-2,1,0,-1,2,1,0,
     -1,-2,-1,0,0,0,1,2,1,
     -2,-1,0,-1,0,1,0,1,2,
     -1,0,1,-2,0,2,-1,0,1,
     0,1,2,-1,0,1,-2,-1,0 };

//   Prewitt  
int  Tprewitt[72]={
     1,1,1,1,-2,1,-1,-1,-1,
     1,1,1,1,-2,-1,1,-1,-1,
     1,1,-1,1,-2,-1,1,1,-1,
     1,-1,-1,1,-2,-1,1,1,1,
     -1,-1,-1,1,-2,1,1,1,1,
     -1,-1,1,-1,-2,1,1,1,1,
     -1,1,1,-1,-2,1,-1,1,1,
     1,1,1,-1,-2,1,-1,-1,1 };


int  TLineDetect[36]={
     -1,2,-1,-2,4,-2,-1,2,-1,
     -1,-2,-1,2,4,2,-1,-2,-1,
     -2,-1,2,-1,4,-1,2,-1,-2,
     2,-1,-2,-1,4,-1,-2,-1,2 };


void Sobel0(BYTE **list0,BYTE **list1,int Dx,int Dy,char ch)
{
  int  i,j,A,B,C;
  
  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      A = abs((list1[i-1][j+1]+2*list1[i][j+1]+list1[i+1][j+1])-
	          (list1[i-1][j-1]+2*list1[i][j-1]+list1[i+1][j-1]));
      B = abs((list1[i+1][j-1]+2*list1[i+1][j]+list1[i+1][j+1])-
	          (list1[i-1][j-1]+2*list1[i-1][j]+list1[i-1][j+1]));
      switch(ch) {
	    case 'M' :
		  C = (int) sqrt((double)(A*A+B*B));
//	      if (A>B) C = A;
//	      else     C = B;
          break;
	    case 'H' :
	      C = A;
	      break;
	    case 'V' :
	      C = B;
	      break;
 	    default :
	      break;
	  }
      C /= Scale;
      if (C>255) C=255;
	  list0[i][j] = C;
	}
  }
}

void WINAPI Sobel(BYTE **list0,BYTE **list1,int Dx,int Dy)  //  Sobel 
{
  Scale=4;
  Sobel0(list0,list1,Dx,Dy,'M');
}

void Gradiant0(BYTE **list0,BYTE **list1,int Dx,int Dy,char ch)
{
  int  i,j,A,B,C;
  
  for (i=0;i<Dy-1;i++) {
    for (j=0;j<Dx-1;j++) {
      if (ch=='R') {
	    A = abs(list1[i][j]-list1[i+1][j+1]);
	    B = abs(list1[i+1][j]-list1[i][j+1]);
        C = A + B;
	  }
      else {
	    A = abs(list1[i][j]-list1[i][j+1]);
	    B = abs(list1[i][j]-list1[i+1][j]);
 	    switch(ch) {
	      case 'M' :
            C = A + B;
            break;
	      case 'H' :
	        C = A;
	        break;
	      case 'V' :
	        C = B;
	        break;
	      default :
	        break;
		}
	  }
      C *= Scale;
	  if (C>255) C=255;
  	  list0[i][j] = C;
	}
  }
}

void WINAPI Gradiant(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                                           
   Scale=2;
   Gradiant0(list0,list1,Dx,Dy,'M');
}

void WINAPI Roberts(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                                      //  roberts 
   Scale=2;
   Gradiant0(list0,list1,Dx,Dy,'R');
}

void WINAPI Template(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,g;
  
  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      g = (Mask[0][0]*list1[i-1][j-1]+Mask[0][1]*list1[i-1][j]
	      +Mask[0][2]*list1[i-1][j+1]+Mask[1][0]*list1[i][j-1]
	      +Mask[1][1]*list1[i][j]    +Mask[1][2]*list1[i][j+1]
	      +Mask[2][0]*list1[i+1][j-1]+Mask[2][1]*list1[i+1][j]
	      +Mask[2][2]*list1[i+1][j+1])/Scale+Offset;  
	  if (g>0xff) g=0xff;
	  else if (g<0) g=0;
	  list0[i][j] = (BYTE) g;   
    }
  }
}

void WINAPI Laplacian(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   Scale=1;
   Offset=1;               
   Mask[0][0]=Mask[0][2]=Mask[2][0]=Mask[2][2]=-1;
   Mask[0][1]=Mask[2][1]=Mask[1][0]=Mask[1][2]=-1;
   Mask[1][1]=8;
   Template(list0,list1,Dx,Dy);                 
   Offset=0;
}

void WINAPI LapSketch(BYTE **list0,BYTE **list1,int Dx,int Dy)
{  
   Scale=1;		
   Offset=254;               
   Mask[0][0]=Mask[0][2]=Mask[2][0]=Mask[2][2]=-1;  
   Mask[0][1]=Mask[2][1]=Mask[1][0]=Mask[1][2]=-1;
   Mask[1][1]=8;
   Template(list0,list1,Dx,Dy);                 
   Offset=0;
}

void WINAPI BoundEnhance(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   Scale=4;
   Mask[0][0]=Mask[0][2]=Mask[2][0]=Mask[2][2]=0;
   Mask[0][1]=Mask[2][1]=Mask[1][0]=Mask[1][2]=-1;
   Mask[1][1]=Scale+4;
   Template(list0,list1,Dx,Dy);                 
}

void  WINAPI RemoveLineNoise(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   Scale=3;
   Mask[0][1]=Mask[1][1]=Mask[2][1]=1;
   Mask[0][0]=Mask[0][2]=0;
   Mask[1][0]=Mask[1][2]=0;
   Mask[2][0]=Mask[2][2]=0;
   Template(list0,list1,Dx,Dy);
}

void WINAPI Smooth5(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   Scale=5;
   Mask[0][0]=Mask[0][2]=Mask[2][0]=Mask[2][2]=0;
   Mask[0][1]=Mask[2][1]=Mask[1][0]=Mask[1][2]=1;
   Mask[1][1]=1;
   Template(list0,list1,Dx,Dy);
}

void WINAPI Smooth9(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   Scale=9;
   Mask[0][0]=Mask[0][2]=Mask[2][0]=Mask[2][2]=1;
   Mask[0][1]=Mask[2][1]=Mask[1][0]=Mask[1][2]=1;
   Mask[1][1]=1;
   Template(list0,list1,Dx,Dy);
}

void  WINAPI RemoveWhiteDot(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   int	i,j,k,m,s,t;

   m=2;
   for (i=0;i<Dy;i++)
	   memcpy(list0[i],list1[i],Dx);

   for (i=1;i<Dy-1;i++) {
      for (j=1;j<Dx-1;j++) {
		 if (list1[i][j]) {
			k=0;
			for (t=-1;t<2;t++) {
			   for (s=-1;s<2;s++) {
				   if (list1[i+t][j+s]) k++;
				   if (k>m) break;
			   }
			   if (k>m) break;
			}
			if (k<m+1) list0[i][j]=0; 
		 }
	  }
   }
}

void  WINAPI RemoveBlackDot(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   int	i,j,k,s,t;

   for (i=0;i<Dy;i++)
	   memcpy(list0[i],list1[i],Dx);

   for (i=1;i<Dy-1;i++) {
      for (j=1;j<Dx-1;j++) {
		 if (list1[i][j]==0) {
			k=0;
			for (t=-1;t<2;t++) {
			   for (s=-1;s<2;s++) {
				   if (list1[i+t][j+s]==0) k++;
				   if (k>3) break;
			   }
			   if (k>3) break;
			}
			if (k<4) list0[i][j]=255; 
		 }
	  }
   }
}

int  MedValue(int *buf, int n, int m)	           
{
   int i,j,k,f;

   for (i=1;i<n;i++) {	                               
      f=0;	                                   
      for (j=n-1;j>=i;j--) {
		  if (buf[j]>buf[j+1]) {	                           
		     k=buf[j];    buf[j]=buf[j+1];  
		     buf[j+1]=k;    f=1;
	      }
      }
      if (f==0) break;	                           
   }
   return(buf[m]);	                             
}

void Median(BYTE **list0, BYTE **list1, int Dx, int Dy, int flag)
{
  int  i,j,buff1[20];
  
  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
	 buff1[0] = list1[i-1][j];                        
	 buff1[1] = list1[i][j];
	 buff1[2] = list1[i+1][j];         
	 buff1[3] = list1[i][j-1];
	 buff1[4] = list1[i][j+1];               
	 if (flag==9) {
	   buff1[5] = list1[i-1][j-1];              
	   buff1[6] = list1[i-1][j+1];  	  
	   buff1[7] = list1[i+1][j-1];      
	   buff1[8] = list1[i+1][j+1];
     }
     list0[i][j] = (BYTE) MedValue(buff1, flag, flag/2);
	}
  }
}

void WINAPI Median5(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                          //  3x3
   Median(list0,list1,Dx,Dy,5);
}

void WINAPI Median9(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                          //  3x3
   Median(list0,list1,Dx,Dy,9);
}

int  WINAPI LineWidthW(BYTE **list,int x,int y,int n)
{
  int  i,t;
  int  Mask3[9][2] ={{ 1, 0},{ 1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1, 1},{ 0, 1},{ 1, 1},{ 1, 0}};

  for (i=0,t=0; i<=8; i++) {
    if (list[y+Mask3[i][1]][x+Mask3[i][0]]>=n) {
	  t++; 
	  if (t>1) break;
	}
	else t=0;
  }
  return(t);
}

void WINAPI OnePWidthW(BYTE **list0,BYTE **list1,int Dx,int Dy)	
{
  int  i,j,n,l,k,p,t;
  
  for(i=0;i<Dy;i++)
    memset(list0[i],0,Dx);	 

  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      if (list1[i][j]==0) continue;	 
      n=0;	 
      p=list1[i][j];	 
      for (l=-1;l<2;l++) {
        for (k=-1;k<2;k++) 
          if (list1[i+l][j+k]>=p) n++;	 
	  }
      if (n>3) {                         
        t=LineWidthW(list1,j,i,p);
        if (t<2) list0[i][j]=p;
	  }
	  else if (n==3) {	 
		  if (list1[i][j-1]>p) {	 
          if ((list1[i-1][j]>p)||(list1[i+1][j]>p)) n--;
		}
        else if (list1[i][j+1]>p) {
          if ((list1[i-1][j]>p)||(list1[i+1][j]>p)) n--;  
		}
        if (n==3) list0[i][j]=p;	 
      }
      else list0[i][j]=p;
	}
  }

  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      if (list0[i][j]==0) continue;	
      for (l=-1,n=0;l<2;l++) {
        for (k=-1;k<2;k++) 
          if (list0[i+l][j+k]>0) n++;
	  }
	  if (n==1) list0[i][j]=0;
	}
  }
}

void KRP_op(BYTE **list0,BYTE **list1,int Dx,int Dy,int *pp,int bb)
{          
  BYTE t[8];
  int  i,j,k,p,g,m,tab[8][3][3];
   
  for (k=0;k<8;k++)
    for (i=0;i<3;i++)
	  for (j=0;j<3;j++)
		tab[k][i][j]=*pp++;

  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
		for (p=0;p<8;p++) {	               
	    g = (tab[p][0][0]*list1[i-1][j-1]+tab[p][0][1]*list1[i-1][j]
		    +tab[p][0][2]*list1[i-1][j+1]+tab[p][1][0]*list1[i][j-1]
		    +tab[p][1][1]*list1[i][j]    +tab[p][1][2]*list1[i][j+1]
		    +tab[p][2][0]*list1[i+1][j-1]+tab[p][2][1]*list1[i+1][j]
		    +tab[p][2][2]*list1[i+1][j+1])/Scale;     
		if (g<0)  g=0;	                       
		else if (g>0xff)  g=0xff;
		t[p]= (BYTE) g;	       
	  }
	  m=0;
	  for (p=0;p<8;p++) {	   
	    if (t[p]>m)  m=t[p];
	  }
      if ((bb==0)||(m==t[bb-1]))
	    list0[i][j] = (BYTE) m;         
 	  else  list0[i][j] = 0;
	}
  }
}

void WINAPI Kirsch(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction)
{                                      //  Kirsch
   Scale=8;                                        
   KRP_op(list0,list1,Dx,Dy,Tkirsch,direction);    
}

void WINAPI Robinson(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction)
{                                    //  Robinson
   Scale=2;                                        
   KRP_op(list0,list1,Dx,Dy,Trobinson,direction);  
}

void WINAPI Prewitt(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction)
{                                     //  Prewitt
   Scale=2;                                        
   KRP_op(list0,list1,Dx,Dy,Tprewitt,direction);   
}

void WINAPI TemplateB(BYTE **list0,BYTE **list1,int Dx,int Dy,int t)
{                                          	//  t x t(t = 3 or 5)
	int   i,j,g,m,n,*p;
 
	for (i=t/2;i<Dy-t/2;i++) {
		for (j=t/2;j<Dx-t/2;j++) {
			g=0;
			p=&Mask5[0][0];
			for (m=i-t/2;m<=i+t/2;m++) {	
				for (n=j-t/2;n<=j+t/2;n++) 
					g+=(*p++)*list1[m][n];
 
            }
			g=g/Scale+Offset;	
			if (g>0xff)   g=0xff;	
			else if (g<0) g=0;
			list0[i][j] = g;           

		}
	}
}

void WINAPI LoG(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                               
	int  mask[25]={ 0, 0,-1, 0, 0,
		            0,-1,-2,-1, 0,
		           -1,-2,16,-2,-1,
		            0,-1,-2,-1, 0,
				    0, 0,-1, 0, 0};

  Scale=1;		Offset=254;
  memcpy(Mask5,mask,25*sizeof(int));
  TemplateB(list0,list1,Dx,Dy,5);
  Offset=0;
}

void LineDetectA(BYTE **list0,BYTE **list1,int Dx,int Dy,int *pp,int bb)
{          
  BYTE t[8];
  int  i,j,k,p,g,m,tab[8][3][3];
   
  for (k=0;k<4;k++)
    for (i=0;i<3;i++)
	  for (j=0;j<3;j++)
		tab[k][i][j]=*pp++;

  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
		for (p=0;p<4;p++) {	               
	    g = (tab[p][0][0]*list1[i-1][j-1]+tab[p][0][1]*list1[i-1][j]
		    +tab[p][0][2]*list1[i-1][j+1]+tab[p][1][0]*list1[i][j-1]
		    +tab[p][1][1]*list1[i][j]    +tab[p][1][2]*list1[i][j+1]
		    +tab[p][2][0]*list1[i+1][j-1]+tab[p][2][1]*list1[i+1][j]
		    +tab[p][2][2]*list1[i+1][j+1])/Scale;     
		if (g<0)  g=0;	                       
		else if (g>0xff)  g=0xff;
		t[p]= (BYTE) g;	       
	  }
	  m=0;
	  for (p=0;p<4;p++) {	   
	    if (t[p]>m)  m=t[p];
	  }
      if (bb==0)
	    list0[i][j] = (BYTE) m;         
	  else if (m==t[bb-1]) 
		list0[i][j] = (BYTE) m;         
	  else  list0[i][j] = 0;
	}
  }
}

void WINAPI LineDetect(BYTE **list0,BYTE **list1,int Dx,int Dy)
{                                      
	Scale=2;                                        
	LineDetectA(list0,list1,Dx,Dy,TLineDetect,0);   
}

void WINAPI SobelThinning(BYTE **list0,BYTE **list1,int Dx,int Dy) 	
{
  int  i,j,g;

  Sobel(list0,list1,Dx,Dy); 	 
  for (i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      g = list1[i][j]-list0[i][j]; 	 
      if ((list1[i][j-1]+list1[i][j+1]==0)|| 	 
          (list1[i-1][j]+list1[i+1][j]==0)) {	 
        list0[i][j]=list1[i][j];	 
      }
      else {
        if (g<0) list0[i][j]=0; 	 
        else     list0[i][j]=g; 	 
	  }
	}
  }
}

void WINAPI SobelThin(BYTE **list0,BYTE **list1,int Dx,int Dy) 	
{
  BYTE *bufu,*bufv;
  BYTE **listu,**listv;
  int  i,j,g;
 
  bufu =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  for (i=0;i<Dy;i++) 
	listu=(BYTE**) malloc(Dy*sizeof(BYTE*));
  for(i=0;i<Dy;i++) listu[i]=bufu+i*Dx;

  bufv =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  for (i=0;i<Dy;i++) 
	listv=(BYTE**) malloc(Dy*sizeof(BYTE*));
  for(i=0;i<Dy;i++) listv[i]=bufv+i*Dx;

  SobelThinning(list0,list1,Dx,Dy);
  SobelThinning(listu,list0,Dx,Dy);
  SobelThinning(listv,listu,Dx,Dy);

  for (i=1;i<Dy-1;i++) {
	for (j=0;j<Dx-1;j++) {
	  g=list0[i][j];
	  g=(g+listu[i][j]+listv[i][j])/3;
	  listu[i][j]=g;
	}
  }
  OnePWidthW(list0,listu,Dx,Dy);

  free(bufu);  
  free(listu);  
  free(bufv);  
  free(listv);  
}

//--------------------------------------------------------------------------------

void HistogSmooth(long *pg,int n)
{
   int  i,j,k;

   for (j=0;j<n;j++) {
      k=pg[0];
	  for (i=1;i<255;i++) 
		 pg[i-1]=(pg[i-1]+pg[i]+pg[i+1])/3;
      for (i=254;i>0;i--) pg[i]=pg[i-1];
	  pg[0]=k;
   }
}

int  MaxMin(double *tab,int flag)
{
   double  max,min;
   int     i,p,q;

   max=min=tab[128];		
   p=q=128;
   for (i=0;i<256;i++) {
      if (tab[i]>max) {
	     max=tab[i];	
		 p=i;
      }
	  if (tab[i]<min) {
		 min=tab[i];	
		 q=i;
	  }
   }
   if (flag==1) {
      for (i=0;i<256;i++) 
         tab[i]=120*(max-tab[i])/(max-min);
   }
   else {         
      for (i=0;i<256;i++) 
         tab[i]=120*(tab[i]-min)/(max-min);
	  p=q;
   } 
   return(p);
}

int  ValleyAnalyse(long *pg)
{
   int  i,j,k,t,tab[10][2],n,min,g;

   HistogSmooth(pg,2);
   g=2;
   min=pg[0];      k=0;
   for (i=1;i<256;i++) {
	  if (pg[i]<min) {
	     k=i;
		 min=pg[i];
	  }
   }
   t=i=j=k;
   while((pg[i]<=g)&&(i<255)) i++;
   while((pg[j]<=g)&&(j>0))   j--;
   if ((i<250)||(j>5)) k=(i+j)/2;
   tab[1][0]=j;		tab[1][1]=i;

   tab[2][0]=0;     tab[2][1]=255;
   n=i+10;
   if (n>220) n=220;
   min=pg[n];      k=n;
   for (i=n+1;i<256;i++) {
	  if (pg[i]<min) {
	     k=i;
		 min=pg[i];
	  }
   }
   i=j=k;
   while((pg[i]-min<=g)&&(i<255)) i++;
   while((pg[j]-min<=g)&&(j>0))   j--;
   if ((i<250)||(j>5)) k=(i+j)/2;
    if ((i<224)||(j>5)) {
	  k=(i+j)/2;
      tab[2][0]=j;		tab[2][1]=i;
   }

   tab[0][0]=0;         tab[0][1]=255;
   n=t-10;
   if (n<20) n=20;
   min=pg[n];     k=n;
   for (i=n-1;i>0;i--) {
	  if (pg[i]<min) {
	     k=i;
		 min=pg[i];
	  }
   }
   i=j=k;
   while((pg[i]-min<=g)&&(i<255)) i++;
   while((pg[j]-min<=g)&&(j>0))   j--;
   if ((i<250)||(j>5)) k=(i+j)/2;
    if ((i<224)||(j>5)) {
	  k=(i+j)/2;
      tab[0][0]=j;		tab[0][1]=i;
   }

   if (tab[0][1]-tab[0][0]>80) tab[0][1]=255;
   if (tab[2][1]-tab[2][0]>80) tab[2][0]=0;
   if (tab[0][0]==0)   tab[0][1]=255;
   if (tab[2][1]==255) tab[2][0]=0;
   n=1;
   if (tab[0][1]<tab[1][0]) 
      if (tab[0][1]-tab[0][0]>tab[1][1]-tab[1][0]) n=0; 
   if (tab[2][0]>tab[1][1]) 
      if (tab[2][1]-tab[2][0]>tab[1][1]-tab[1][0]) n=2; 
   k=(tab[n][1]+tab[n][0])/2;
   return(k);
}

int  WINAPI Otsu(long *pg)      
{
   int  i,j,p;
   double m0,m1,M0,M1,u,v,w[256];

   M0=M1=0;
   for (i=0;i<256;i++) {
      M0+=pg[i];     M1+=pg[i]*i;
   }
   for (j=0;j<256;j++) {
      m0=m1=0;
      for (i=0;i<=j;i++) {
	 m0+=pg[i];	 m1+=pg[i]*i;
      }
      if (m0) u=m1/m0;
      else   u=0;
      if (M0-m0) v=(M1-m1)/(M0-m0);
      else      v=0;
      w[j]=m0*(M0-m0)*(u-v)*(u-v);
   }

   p=MaxMin(w,1);
   return(p);
}

int  WINAPI Minimum(long *pg) 
{
   double u1,u2,tab[256];
   double s1,s2,P1,P2,PP1,PP2,SS1,SS2;
   int    i,g,p;

   for (i=0;i<256;i++) {
	   for (g=0,  P1=0;g<=i; g++) 
		   P1 += (double) pg[g];
	   for (g=i+1,P2=0;g<256;g++) 
		   P2 += (double) pg[g];
	   for (g=0,  u1=0;g<=i; g++) 
		   u1 += (double) pg[g]*g;
	   for (g=i+1,u2=0;g<256;g++) 
		   u2 += (double) pg[g]*g;
       u1 /= P1;		
	   u2 /= P2;
	   for (g=0,  s1=0;g<=i; g++) 
		   s1 += (double) pg[g]*(g-u1)*(g-u1);
	   for (g=i+1,s2=0;g<256;g++)
		   s2 += (double) pg[g]*(g-u2)*(g-u2);
	   s1 = sqrt(s1/P1);	
	   s2 = sqrt(s2/P2);
	   SS1=SS2=PP1=PP2=0;
       if (s1) SS1=P1*log(s1);
       if (s2) SS2=P2*log(s2);
       if (P1) PP1=P1*log(P1);
       if (P2) PP2=P2*log(P2);
       tab[i]=1+2*(SS1+SS2)-2*(PP1+PP2);
   }

   p=MaxMin(tab,0);
   return(p);
}

int  WINAPI Ptile(long *pg,double nn)       
{
   int  i;
   double mm,kk;

   for (i=0,mm=0;i<256;i++) mm+=pg[i];
   kk=0;
   for (i=0;i<256;i++) {
	  kk+=(double) pg[i]/mm;
      if (kk>=nn)  break;
   }
   return i;
}

int  WINAPI KSW_Entropic(long *pg)            
{
   long   i,t,s;
   double p[256],Pt[256],Ht[256],HT,H[256];
   double A,B,C;
  
   for (i=0,s=0;i<256;i++) s+=pg[i];
   for (i=0;i<256;i++) p[i]=((double) pg[i])/s;

   Pt[0]=p[0];
   for (i=1;i<256;i++) Pt[i]=Pt[i-1]+p[i];

   for (i=0;i<256;i++) {
      if (p[i]==0) Ht[i]=0;
	  else  Ht[i]=-p[i]*log(p[i]);
   }
   for (i=1;i<256;i++) Ht[i]+=Ht[i-1];
   HT=Ht[255];

   for (i=0;i<256;i++) {
	  A=Pt[i]*(1-Pt[i]);
      if (A>0) A=log(A);
	  B=Pt[i];
	  if (B>0) B=Ht[i]/B;
	  C=1-Pt[i];
	  if (C>0) C=(HT-Ht[i])/C;
	  H[i]=A+B+C;
   }

   t=MaxMin(H,1);
   return(t);
}

int  WINAPI Moment(long *pg)               
{
   long   i,t;
   double m0,m1,m2,m3,p0,C0,C1;

   m0=m1=m2=m3=0;
   for (i=0;i<256;i++) {
      m0+=(double) pg[i];		
	  m1+=(double) pg[i]*i;
      m2+=(double) pg[i]*i*i;
	  m3+=(double) pg[i]*i*i*i;
   }
   C0=(m1*m3-m2*m2)/(m0*m2-m1*m1);
   C1=(m1*m2-m0*m3)/(m0*m2-m1*m1);
   p0=0.5-(m1/m0+C1/2)/sqrt(C1*C1-4*C0);
   t=Ptile(pg,p0);
   return(t);
}

int  WINAPI BiasNormal(long *pg)
{
   int  i,j,p;
   double u,u1,u2,t,t1,t2,tab[256];
   double k1,k2;

   t=u=0;
   for (i=0;i<256;i++) {
      t+=pg[i];		u+=i*pg[i];
   }
   for (j=0;j<256;j++) {
      t1=u1=0;
      for (i=0;i<=j;i++) {
	     t1+=pg[i];		u1+=i*pg[i];
      }
      t2=t-t1;
      u2=u-u1;
      if (t1)	u1=u1/t1;
      else		u1=0;
      if (t2)	u2=u2/t2;
      else		u2=0;

	  for (i=0,k1=0;i<j;i++)   
		  k1+=(i-u1)*(i-u1)*(i-u1)*pg[i];
      for (i=j,k2=0;i<256;i++) 
		  k2+=(i-u2)*(i-u2)*(i-u2)*pg[i];
	  k1=k1*t1;
	  k2=k2*t2;

	  tab[j]=fabs(k1)+fabs(k2);
   }

   p=MaxMin(tab,0);
   return(p);
}
int  WINAPI ColligationThreshold(long *pg)
{
	int		thre,list[256],buf[20],bn;
	int		i,j,k,m,n,tab[10];

	thre=FormAnalysis(pg,list,buf,&bn);
	if (bn<4) return(thre);

	tab[0]=Otsu(pg);
	tab[1]=KSW_Entropic(pg);
	tab[2]=Minimum(pg);
	tab[3]=BiasNormal(pg);
	tab[4]=Moment(pg);

	m=5;
	for (i=0;i<m-1;i++) {                  
       k=i;      
	   n=tab[i];
       for (j=i+1;j<m;j++) {
	      if (tab[j]<n) {
	          k=j;	
			  n=tab[j];
		  }
       }
       tab[k]=tab[i];
       tab[i]=n;      
	}
	k=tab[m/2];
	if ((bn>3)&&(bn<6)&&(buf[3]-buf[1]>100)) {
		for (i=2;i<bn;i+=2) {
			if (abs(buf[i]-k)<40) k=buf[i];
		}
	}
	return(k);
}

int  WINAPI SimpleThreshold(long *pg)
{
	if (pg[254]>pg[1]) return(255);
	else return(1);
}

void HistogramSmooth(long *pg,int n)
{
	TableSmooth(pg,256,n);
}

int  GrayImageType(long *pg)
{
	int i,k,t;
	long pga[256],max,a,b;

	memcpy(pga,pg,256*sizeof(long));
	pga[0]=pga[255]=0;
	HistogSmooth(pga,15);
	max=pga[0];
	k=0;
	for (i=0;i<256;i++) {
		if (pga[i]>max) {
			max=pga[i];
			k=i;
		}
	}
	a=b=0;
	for (i=0;i<k;i++) a+=pg[i];
	for (i=k+1;i<256;i++) b+=pg[i];
	if (a>b) t=0;
	else t=1;
	return(t);
}

int  WINAPI FormAnalysis(long *pg,int *tab,int *buf,int *bn)
{
	int		num=20,h=120,a=10,b=5,g=20; 
 	long	pga[256];
	int		i,j,m,n,k,f,v,s,t;
	int		thre,buf2[20];
 
 	memcpy(pga,pg,256*sizeof(long));
	pga[0]=pga[255]=0;
	HistogSmooth(pga,num);

	m=SearchScale(pga,5);
	k=m/h+1;
	for(i=0;i<256;i++) 
	{
 		n=pga[i]/k;
		if (n>h) n=h;
		tab[i]=n;
 	}

	m=n=0;
	buf[0]=0;
	k=tab[0];
	f=j=1;
	for (i=0;i<255;i++) {
		if (tab[i]==k) n++;
		else {
    		if (f==1) {
				if (tab[i]<k) {
					buf[j++]=m+n/2;
					f=0;
				}
			}
			else {
				if (tab[i]>k) {
					buf[j++]=m+n/2;
					f=1;
				}
			}
			m=i;
			n=1;
			k=tab[i];
		}
	}
	buf[j++]=i;
 
	for (i=2;i<j-2;i+=2) {
 	   m=buf[i-1];
	   n=buf[i];
       if ((n-m<a)||(abs(tab[m]-tab[n])<b)) {
 		   if (tab[m]>tab[buf[i+1]]) buf[i+1]=buf[i-1];
 		   if (tab[n]>tab[buf[i-2]]) buf[i]=buf[i-2];
		   for (k=i;k<j;k++) buf[k-2]=buf[k];
 		   j-=2;
		   i-=2;
		   continue;
	   }
	   m=buf[i+1];
	   n=buf[i];
       if ((m-n<a)||(abs(tab[m]-tab[n])<b)) {
 		   if (tab[m]<tab[buf[i-1]]) buf[i+1]=buf[i-1];
 		   if (tab[n]<tab[buf[i+2]]) buf[i+2]=buf[i];
		   for (k=i;k<j;k++) buf[k]=buf[k+2];
 		   j-=2;
		   i-=2;
	   }
	}

	if (j>5) {
		for (i=2;i<j-1;i+=2) {
		   m=n=0;
           for (k=0;k<buf[i];k++)   m+=tab[k];
           for (k=buf[i];k<256;k++) n+=tab[k];
			buf2[i]=abs(m-n);
 		}
		m=buf2[2];
		n=2;
		for (i=4;i<j-1;i+=2) {
			if (buf2[i]<m) {
				m=buf2[i];
				n=i;
			}
		}
		thre=buf[n];
	}
	else if (j>3) thre=buf[2];
	else {
 		if (buf[1]<10) n=buf[0]; 
 		else
		{
			for (k=buf[1]-3;k>5;k--) { 
				if (tab[k]>h/2) continue;
				if (tab[k+1]-tab[k]>=tab[k]-tab[k-2]) {
 					for (v=k-3;v>k-g;v--)
						if (tab[v+1]<tab[v]) break;
					if ((v>k-g)&&(tab[k]-tab[v]>g/2)) k=v+2;
					if (tab[k]<60) break;
				}
  			}
  			n=k;
			if (k>5) buf[0]=k;
		}
 		if (buf[1]>245) m=buf[2];
 		else 
		{
			for (k=buf[1]+3;k<250;k++) { 
				if (tab[k]>h/2) continue;
				if (tab[k-1]-tab[k]>=tab[k]-tab[k+2]) {
 					for (v=k+3;v<k+g;v++)
						if (tab[v-1]<tab[v]) break;
					if ((v<k+g)&&(tab[k]-tab[v]>g/2)) k=v-2;
					break;
				}
  			}
 			m=k;
			if (k<250) buf[2]=k;
		}
		s=t=0;
		for (i=0;i<n;i++)   s+=tab[i];
		if (m>0) 
 			for (i=m;i<256;i++) t+=tab[i];
		if (s>t) thre=n;
		else thre=m;
 	}
	*bn=j;
 	return(thre);
}

//---------------------------------------------------------------------------------

void WINAPI LogPrewitt(BYTE **list0,BYTE **list,int Dx,int Dy,double pi)
{	
  int    i,j,k,a,b;
  double buffer[3][2048],table[256],A,B;
 
  for (i=0;i<256;i++) table[i]=log(i+1.0);
 
  for (k=0;k<Dx;k++) buffer[0][k]=table[list[0][k]];
  for (k=0;k<Dx;k++) buffer[1][k]=table[list[1][k]];
  for (i=1;i<Dy-1;i++) {
    for (k=0;k<Dx;k++) buffer[2][k]=table[list[i+1][k]];
    for (j=1;j<Dx-1;j++) {
      if (list[i][j]>30) {
        A = (buffer[0][j+1]+buffer[1][j+1]+buffer[2][j+1])-
            (buffer[0][j-1]+buffer[1][j-1]+buffer[2][j-1]);	
        B = (buffer[2][j-1]+buffer[2][j]  +buffer[2][j+1])-
            (buffer[0][j-1]+buffer[0][j]  +buffer[0][j+1]); 	
        if (fabs(A)+fabs(B)<pi) list0[i][j] = 0;  
        else                    list0[i][j] = 1;
	  }
      else {
        a = (list[i-1][j+1]+list[i][j+1]+list[i+1][j+1])-
            (list[i-1][j-1]+list[i][j-1]+list[i+1][j-1]);	
        b = (list[i+1][j-1]+list[i+1][j]+list[i+1][j+1])-
            (list[i-1][j-1]+list[i-1][j]+list[i-1][j+1]); 	
        if (abs(a)+abs(b)<12) list0[i][j] = 0; 
        else                  list0[i][j] = 1;
	  }
    }
    memcpy(buffer[0],buffer[1],Dx*sizeof(double));
    memcpy(buffer[1],buffer[2],Dx*sizeof(double));
  }
}

#define  COLOR	0

int WINAPI Cross(int* f)
{
	int  i,sum;

	for (i=1,sum=0; i<=7; i+=2) {
      if ((!f[i]) && (f[i+1] || f[i+2]))  sum++;
	}                         
	return(sum);
}

void WINAPI Hilditch(BYTE **list,int Dx,int Dy)
{
   int  i,j,k,m,n,flag;
   int  sum=0, x[10];
   char *buf0,**list0;
 
   buf0 =(char*)  malloc(Dx*Dy*sizeof(char));
   list0=(char**) malloc(Dy*sizeof(char*));
   for(k=0;k<Dy;k++) {
      list0[k]=buf0+k*Dx;
	  memcpy(list0[k],list[k],Dx);
   }
 
   i=1;		                                
   do {
      flag=0;		                      
      for (k=1; k<Dy-1; k++) {		      
		 for (j=1; j<Dx-1; j++) {	
			if (list0[k][j] != 1)  continue;       
			x[1]=list0[k][j+1];	x[2]=list0[k-1][j+1];
			x[3]=list0[k-1][j]; x[4]=list0[k-1][j-1];
			x[5]=list0[k][j-1];	x[6]=list0[k+1][j-1];
			x[7]=list0[k+1][j];	x[8]=list0[k+1][j+1];
						
			for (m=1,n=0; m<=8; m++) {
				if (x[m]==-i) {
					x[m]=1;  		  
					n++;		      
				}
				else if (x[m]<0)  x[m]=0;
			}

			sum=x[1]+x[3]+x[5]+x[7];	
			if (sum>=4) continue;      

			x[9]=x[1];
			for (m=1, sum=0; m<=8; m++)
				if (x[m]==1)   sum++;
			if ((sum<=1)||(sum-n==0))  continue;
 
			sum=Cross(x);
			if (sum!=1)  continue;
			if (list0[k-1][j]== -i) {
				x[3]=0;
				sum=Cross(x);		
				if (sum!=1)  continue;
			}
			if (list0[k][j-1]== -i) {
				x[5]=0;
				sum=Cross(x);		
				if (sum!=1)  continue;
			}

			list[k][j]=0;
			list0[k][j]=-i;   
			flag=1; 		 
		 }
      }
      i++;		         
   }
   while(flag==1);	     

   free(list0);                   
   free(buf0);
}

void WINAPI Deutch(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,l,ii,flag;
  int  sum=0, sum1=0, f[10];
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }
 
  i=1;
  do {
    flag=0;
    for (k=1; k<Dy-1; k++) {
      for (j=1; j<Dx-1; j++) {
	if (list[k][j] != 1)  continue;
	else if (i==1) {
	  f[1]=list[k][j+1];
	  f[2]=list[k-1][j+1];
	  f[3]=list[k-1][j];
	  f[4]=list[k-1][j-1];
	  f[5]=list[k][j-1];
	  f[6]=list[k+1][j-1];
	  f[7]=list[k+1][j];
	  f[8]=list[k+1][j+1];
	}
	else {
	  f[1]=list[k][j-1];
	  f[2]=list[k+1][j-1];
	  f[3]=list[k+1][j];
	  f[4]=list[k+1][j+1];
	  f[5]=list[k][j+1];
	  f[6]=list[k-1][j+1];
	  f[7]=list[k-1][j];
	  f[8]=list[k-1][j-1];
	}
	for (ii=1; ii<=8; ii++) {
	  if (f[ii]==-i)    f[ii]=1;
	  else if(f[ii]<0)  f[ii]=0;
	}
	f[9]=f[1];

	sum=sum1=0;
	for (l=1; l<9; l++) {
	  if ((f[l+1]-f[l])!=0)  sum++;
	  sum1+=f[l];
	}
	if (sum1==1)  continue;
	if (sum>4)    continue;
	if (sum==1 || sum==3)     continue;
	if ((f[1]*f[3]*f[5])!=0)  continue;
	if ((f[1]*f[3]*f[7])!=0)  continue;
	if (sum==4) {
	  if (f[1]*f[7]!=1 || f[2]+f[6]!=1 ||
		 f[3]+f[4]+f[5]+f[8]!=0)  continue;
	  if (f[1]*f[3]!=1 || f[4]+f[8]!=1 ||
	    f[2]+f[5]+f[6]+f[7]!=0)  continue;
	}
	list[k][j] = -i;
	list0[k][j]= COLOR;
	flag=1;
      }
    }
    i++;
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI FastThin(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,flag;
  int  f[11],ap1,bp1;
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }
 
  do {
    flag=0;
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if  (list[j][i] != 1)  continue;
	f[1]=list[j][i];
	f[2]=list[j][i-1];
	f[3]=list[j+1][i-1];
	f[4]=list[j+1][i];
	f[5]=list[j+1][i+1];
	f[6]=list[j][i+1];
	f[7]=list[j-1][i+1];
	f[8]=list[j-1][i];
	f[9]=list[j-1][i-1];
	f[10]=f[2];

	for (k=2; k<=10; k++)
	  f[k] = (f[k]>0) ? 1 : 0;
	if (f[4]&&f[6])
	  if (f[2]||f[8])  continue;
	bp1=0;
	for (k=2; k<=9; k++)
	  bp1+=f[k];
	if ((bp1<2)||(bp1>6))  continue;
	ap1=0;
	for (k=2; k<=9; k++)
	  if ((f[k]==0) && (f[k+1]==1))
	    ap1++;
	if (ap1!=1)  continue;
	list[j][i]=3;
		}
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i] == 3) {
	  list[j][i] = 0;
	  list0[j][i]= COLOR;
	  flag=1;
	}
      }
    }
    if (flag==0)  break;
    flag=0;
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if  (list[j][i] != 1)  continue;
	f[1]=list[j][i];
	f[2]=list[j][i-1];
	f[3]=list[j+1][i-1];
	f[4]=list[j+1][i];
	f[5]=list[j+1][i+1];
	f[6]=list[j][i+1];
	f[7]=list[j-1][i+1];
	f[8]=list[j-1][i];
	f[9]=list[j-1][i-1];
	f[10]=f[2];

	for (k=2; k<=10; k++)
	  f[k] = (f[k]>0) ? 1 : 0;
	if (f[2]&&f[8])
	  if (f[4]||f[6])  continue;
	bp1=0;
	for (k=2; k<=9; k++)
	  bp1+=f[k];
	if ((bp1<2)||(bp1>6))  continue;
	ap1=0;
	for (k=2; k<=9; k++)
	  if ((f[k]==0) && (f[k+1]==1))
	    ap1++;
	if (ap1!=1)  continue;
	list[j][i] = 3;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i] == 3) {
	  list[j][i] = 0;
	  list0[j][i]=COLOR;
	  flag=1;
	}
      }
	 }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI Naccache(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,flag;
  int  N[8];
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }
 
  do {
    flag=0;
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if  (list[j][i] != 1)  continue;
	N[0]=list[j+1][i];
	N[1]=list[j+1][i-1];
	N[2]=list[j][i-1];
	N[3]=list[j-1][i-1];
	N[4]=list[j-1][i];
	N[5]=list[j-1][i+1];
	N[6]=list[j][i+1];
	N[7]=list[j+1][i+1];

	if (N[0]&&N[4])  continue;
	for (k=0;k<8;k++)
	  if (N[k]==2)  N[k]=0;
	if (N[0]&&(N[1]||N[2]||N[6]||N[7])&&
	     (N[2]||(!N[3]))&&(N[6]||(!N[5]))) {
	  list[j][i]=2;
	  continue;
	}
	if (N[4]&&(N[5]||N[6]||N[2]||N[3])&&
	     (N[6]||(!N[7]))&&(N[2]||(!N[1]))) {
	  list[j][i]=2;
	  continue;
	}
	list[j][i]=3;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i]==2) {
	  list[j][i] = 0;
	  list0[j][i] = COLOR;
	  flag=1;
	}
	else if (list[j][i]==3)
	  list[j][i] = 1;
      }
    }
    if (flag==0) break;
    flag=0;
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i] != 1)  continue;
	N[0]=list[j+1][i];
	N[1]=list[j+1][i-1];
	N[2]=list[j][i-1];
	N[3]=list[j-1][i-1];
	N[4]=list[j-1][i];
	N[5]=list[j-1][i+1];
	N[6]=list[j][i+1];
	N[7]=list[j+1][i+1];

	if (N[2]&&N[6])  continue;
	for (k=0;k<8;k++)
	  if (N[k]==2)  N[k]=0;
	if (N[2]&(N[3]||N[4]||N[0]||N[1])&&
	     (N[4]||(!N[5]))&&(N[0]||(!N[7]))) {
	  list[j][i]=2;
	  continue;
	}
	if (N[6]&(N[7]||N[0]||N[4]||N[5])&&
	     (N[0]||(!N[1]))&&(N[4]||(!N[3]))) {
	  list[j][i]=2;
	  continue;
	}
	list[j][i] = 3;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i] == 2) {
	  list[j][i] = 0;
	  list0[j][i]=COLOR;
	  flag=1;
	}
	else if (list[j][i]==3)
	  list[j][i] = 1;
      }
    }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI Pavlidis1(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,flag,flag1;
  int  N[8],neighb;
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }
 
  do {
    flag=0;
    for (neighb=0;neighb<=7;neighb+=2) {
      for (j=1; j<Dy-1; j++) {
	for (i=1; i<Dx-1; i++) {
	  N[0]=list[j+1][i];
	  N[1]=list[j+1][i-1];
	  N[2]=list[j][i-1];
	  N[3]=list[j-1][i-1];
	  N[4]=list[j-1][i];
	  N[5]=list[j-1][i+1];
	  N[6]=list[j][i+1];
	  N[7]=list[j+1][i+1];

	  if ((list[j][i]==1)&&(N[neighb]==0)) {
	    flag1=0;
	    if ((N[3]||N[2]||N[1])&&(N[5]||
	      N[6]||N[7])&&(N[4]!=1)&&(N[0]!=1)) {
		flag1=1;
	    }
	    else if ((N[3]||N[4]||N[5])&&(N[1]||
	      N[0]||N[7])&&(N[2]!=1)&&(N[6]!=1)) {
		flag1=1;
	    }
	    else if ((N[1]==2)&&(N[0]!=1)&&(N[2]!=1)&&
		(N[3]||N[4]||N[5]||N[6]||N[7])) {
		  flag1=1;
	    }
	    else if ((N[3]==2)&&(N[2]!=1)&&(N[4]!=1)
		&&(N[0]||N[1]||N[7]||N[6]||N[5])) {
		  flag1=1;
	    }
	    else if ((N[5]==2)&&(N[4]!=1)&&(N[6]!=1)
		&&(N[7]||N[0]||N[1]||N[2]||N[3])) {
		  flag1=1;
	    }
	    else if ((N[7]==2)&&(N[6]!=1)&&(N[0]!=1)
		&&(N[1]||N[2]||N[3]||N[4]||N[5])) {
		  flag1=1;
	    }
	    if (flag1==1)  list[j][i]=2;
	    else {
	      list[j][i]=3;
	      flag=1;
	    }
	  }
	}
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i] == 3) {
	  list[j][i] = 0;
	  list0[j][i]= COLOR;
	}
      }
    }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI Pavlidis2(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,c,flag,xx;
  int  N[8];
  unsigned char bdr1,bdr2,bdr4,bdr5;
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }

  c=5;
  do {
    flag=0;
    c++;
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i]!=1)  continue;
	N[0]=list[j+1][i];
	N[1]=list[j+1][i-1];
	N[2]=list[j][i-1];
	N[3]=list[j-1][i-1];
	N[4]=list[j-1][i];
	N[5]=list[j-1][i+1];
	N[6]=list[j][i+1];
	N[7]=list[j+1][i+1];
	bdr1=0;
	for (k=0;k<=7;k++)
	  if (N[k]>=1)  bdr1 |= 0x80 >> k;
	if ((bdr1&0252)==0252)  continue;
	list[j][i]=2;
	flag=1;
	xx=0;
	for (k=0;k<=7;k++)
	  xx+= bdr1 & (0x80 >> k);
	if (xx<=1)  list[j][i]=3;
	else if ((bdr1&0160)&&(bdr1&7)
		       &&(!(bdr1&0210)))
	   list[j][i]=3;
	else if ((bdr1&0301)&&(bdr1&034)
				 &&(!(bdr1&042)))
	   list[j][i]=3;
	else if ((!(bdr1&0202))&&(bdr1&1))
	   list[j][i]=3;
	else if ((!(bdr1&0240))&&(bdr1&0100))
	   list[j][i]=3;
	else if ((!(bdr1&050))&&(bdr1&020))
	   list[j][i]=3;
	else if ((!(bdr1&012))&&(bdr1&04))
	   list[j][i]=3;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i]!=2)  continue;
	N[0]=list[j+1][i];
	N[1]=list[j+1][i-1];
	N[2]=list[j][i-1];
	N[3]=list[j-1][i-1];
	N[4]=list[j-1][i];
	N[5]=list[j-1][i+1];
	N[6]=list[j][i+1];
	N[7]=list[j+1][i+1];
	bdr1=0;   bdr2=0;
	for (k=0;k<=7;k++) {
	  if (N[k]>=1)  bdr1 |= 0x80 >> k;
	  if (N[k]>=2)  bdr2 |= 0x80 >> k;
	}
	if ((bdr1==bdr2)&&(bdr1&0201)
	   &&(bdr1&07)&&(bdr1&03))
	  list[j][i]=4;
	if (((bdr2&0200)&&(!(bdr1&010)))
	  &&(((bdr1&01)&&(bdr1&0100))
	  ||(((bdr1&06)&&(bdr1&060))&&
	  (((bdr1&01)&&(!(bdr1&0100)))
	  ||((!(bdr1&01))&&(bdr1&0100))))))
	   list[j][i]=4;
	else if (((bdr2&040)&&(!(bdr1&02)))
	  &&(((bdr1&020)&&(bdr1&0100))
	  ||(((bdr1&014)&&(bdr1&0201))&&
	  (((bdr1&020)&&(!(bdr1&0100)))
	  ||((!(bdr1&020))&&(bdr1&0100)))))
	  &&(bdr1&07)&&(bdr1&03))
	   list[j][i]=4;
	else if (((bdr2&010)&&(!(bdr1&0200)))
	  &&(((bdr1&04)&&(bdr1&020))
	  ||(((bdr1&03)&&(bdr1&0140))&&
	  (((bdr1&04)&&(!(bdr1&020)))
	  ||((!(bdr1&04))&&(bdr1&020)))))
	  &&(bdr1&0201))
	   list[j][i]=4;
	else if (((bdr2&02)&&(!(bdr1&040)))
	  &&(((bdr1&01)&&(bdr1&04))
	  ||(((bdr1&0300)&&(bdr1&030))&&
	  (((bdr1&01)&&(!(bdr1&04)))
	  ||((!(bdr1&01))&&(bdr1&04))))))
	   list[j][i]=4;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if (list[j][i]!=2)  continue;
	N[0]=list[j+1][i];
	N[1]=list[j+1][i-1];
	N[2]=list[j][i-1];
	N[3]=list[j-1][i-1];
	N[4]=list[j-1][i];
	N[5]=list[j-1][i+1];
	N[6]=list[j][i+1];
	N[7]=list[j+1][i+1];
	bdr4=0;   bdr5=0;
	for (k=0;k<=7;k++) {
	  if (N[k]>=4)  bdr4 |= 0x80 >> k;
	  if (N[k]>=5)  bdr5 |= 0x80 >> k;
	}
	if (!(bdr4&010)) {
	  list[j][i]=5;
	  flag=1;
	}
	else if ((!(bdr4&040))&&(!bdr5)) {
	  list[j][i]=5;
	  flag=1;
	}
	else if ((list[j][i]==3)||(list[j][i]==4))
	  list[j][i]=c;
      }
    }
    for (j=1; j<Dy-1; j++) {
      for (i=1; i<Dx-1; i++) {
	if ((list[j][i]==2)||(list[j][i]==5)) {
	  list[j][i] = 0;
	  list0[j][i]= COLOR;
	}
      }
    }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI Rosenfeld4(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,ii,jj,kk,flag;
  int  N[10];
  int  jbd[5]={0,-1,1,0,0};
  int  ibd[5]={0,0,0,1,-1};
  char NRND,N48,N26,N24,N46,N68,N82;
  char N123,N345,N567,N781;
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }

  do {
    flag=0;
    for (kk=1;kk<=4;kk++) {
      jj=jbd[kk];
      for (j=1; j<Dy-1; j++) {
	for (i=1; i<Dx-1; i++) {
	  ii=ibd[kk];
	  if (!list[j][i])  continue;
	  if (list[j+jj][i+ii])  continue;
	  N[1]=list[j+1][i-1];
	  N[2]=list[j][i-1];
	  N[3]=list[j-1][i-1];
	  N[4]=list[j-1][i];
	  N[5]=list[j-1][i+1];
	  N[6]=list[j][i+1];
	  N[7]=list[j+1][i+1];
	  N[8]=list[j+1][i];

	  NRND=N[2]+N[4]+N[6]+N[8];
	  if (NRND<=1)  continue;
	  N48=N[4]+N[8];
	  N567=N[5]+N[6]+N[7];
	  if (N[2]==1 && N48==0 && N567>0)
	    continue;
	  N123=N[1]+N[2]+N[3];
	  if (N[6]==1 && N48==0 && N123>0)
	    continue;
	  N26=N[2]+N[6];
	  N345=N[3]+N[4]+N[5];
	  if (N[8]==1 && N26==0 && N345>0)
	    continue;
	  N781=N[7]+N[8]+N[1];
	  if (N[4]==1 && N26==0 && N781>0)
	    continue;
	  N46=N[4]+N[6];
	  if (N[5]==1 && N46==0)  continue;
	  N68=N[6]+N[8];
	  if (N[7]==1 && N68==0)  continue;
	  N82=N[8]+N[2];
	  if (N[1]==1 && N82==0)  continue;
	  N24=N[2]+N[4];
	  if (N[3]==1 && N24==0)  continue;
	  if (N[5]==0 && N46==2)  continue;
	  if (N[7]==0 && N68==2)  continue;
	  if (N[1]==0 && N82==2)  continue;
	  if (N[3]==0 && N24==2)  continue;

	  list0[j][i]=COLOR;
	  flag=1;
	}
      }
      for (i=0;i<Dy;i++) {
        memcpy(list[i],list0[i],Dx);
 	 for (j=0;j<Dx;j++)
	    if (list[i][j]!=1)  list[i][j]=0;
      }
    }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI Rosenfeld8(BYTE **list0,int Dx,int Dy)
{
  int  i,j,k,ii,jj,kk,flag;
  int  N[10];
  int  jbd[5]={0,-1,1,0,0};
  int  ibd[5]={0,0,0,1,-1};
  char NRND,N48,N26,N24,N46,N68,N82;
  char N123,N345,N567,N781;
  char *buf,**list;
 
  buf =(char*)  malloc(Dx*Dy*sizeof(char));
  list=(char**) malloc(Dy*sizeof(char*));
  for(k=0;k<Dy;k++) {
    list[k]=buf+k*Dx;
    memcpy(list[k],list0[k],Dx);
  }

  do {
    flag=0;
    for (kk=1;kk<=4;kk++) {
      jj=jbd[kk];
      for (j=1; j<Dy-1; j++) {
	for (i=1; i<Dx-1; i++) {
	  ii=ibd[kk];
	  if (!list[j][i])  continue;
	  if (list[j+jj][i+ii])  continue;
	  N[1]=list[j+1][i-1];
	  N[2]=list[j][i-1];
	  N[3]=list[j-1][i-1];
	  N[4]=list[j-1][i];
	  N[5]=list[j-1][i+1];
	  N[6]=list[j][i+1];
	  N[7]=list[j+1][i+1];
	  N[8]=list[j+1][i];

	  NRND=0;
	  for (k=1; k<=8; k++)
	    NRND += N[k];
	  if (NRND<=1)  continue;
	  N48=N[4]+N[8];
	  N567=N[5]+N[6]+N[7];
	  if (N[2]==1 && N48==0 && N567>0)
	    continue;
	  N123=N[1]+N[2]+N[3];
	  if (N[6]==1 && N48==0 && N123>0)
	    continue;
	  N26=N[2]+N[6];
	  N345=N[3]+N[4]+N[5];
	  if (N[8]==1 && N26==0 && N345>0)
		 continue;
	  N781=N[7]+N[8]+N[1];
	  if (N[4]==1 && N26==0 && N781>0)
	    continue;
	  N46=N[4]+N[6];
	  if (N[5]==1 && N46==0)  continue;
	  N68=N[6]+N[8];
	  if (N[7]==1 && N68==0)  continue;
	  N82=N[8]+N[2];
	  if (N[1]==1 && N82==0)  continue;
	  N24=N[2]+N[4];
	  if (N[3]==1 && N24==0)  continue;
	  list0[j][i]=COLOR;
 	  flag=1;
	}
      }
      for (i=0;i<Dy;i++) {
		  memcpy(list[i],list0[i],Dx);
 	 for (j=0;j<Dx;j++)
	    if (list[i][j]!=1)  list[i][j]=0;
      }
    }
  }
  while(flag==1);

  free(list);                   
  free(buf);
}

void WINAPI RemoveNoise(BYTE **list,int Dx,int Dy)
{
   long i,j,k,m,n;
   BYTE **list0;

   list0=(BYTE**)malloc(Dy*sizeof(BYTE*));
   for(j=0;j<Dy;j++) { 
	  list0[j]=(BYTE*) malloc(Dx);
	  memset(list0[j],0,Dx);
   }
 
   for (j=1;j<Dy-1;j++) {
	  for (i=1;i<Dx-1;i++) {
		 for (m=-1,k=0;m<2;m++) {
			for (n=-1;n<2;n++) {
               if (list[j+m][i+n]) k++;
			}
	     }
		 if (k>4) list0[j][i]=1;
 	  }
   }

   for(j=0;j<Dy;j++) {
      memcpy(list[j],list0[j],Dx);
      if (list0[j]) free(list0[j]);
   }
   free(list0);  
}

int  WINAPI Distance(BYTE **list1,int Dx,int Dy)
{ 
	int  i,j,k,ii,jj,g,t,max,m,n;
	short **list;                          
	BYTE *lists;
	int Mask1[3][3]={7,5,7,5,-1,0,0,0,0};
 	int Mask2[3][3]={0,0,0,0,-1,5,7,5,7};
 
	m=3;			
	n=m/2;
	list=(short**)malloc(Dy*sizeof(short*));    
                                                  
	for(i=0;i<Dy;i++) {
		list[i]=(short *) malloc(Dx*sizeof(short));
		lists=(BYTE*) list[i];
		memcpy(lists,list1[i],Dx);             
		for (j=Dx-1,k=2*(Dx-1);j>=0;j--,k-=2) {
			if (lists[j]>1) lists[k+1]=16;
			else lists[k+1]=0;
 			lists[k]=lists[j];    
 		}
	}
  
	for (i=n;i<Dy-n;i++) {
		for (j=n;j<Dx-n;j++) {
			if (list[i][j]==0) continue;
			g=Dx+Dy;
			for (ii=0;ii<m;ii++) {
				for (jj=0;jj<m;jj++) {
 					if (Mask1[ii][jj]<0) break;
 					if (Mask1[ii][jj]==0) continue;
					t=list[i-n+ii][j-n+jj]+Mask1[ii][jj];
					if (t<g) g=t;
				}
				if (Mask1[ii][jj]<0) break;
			}
 			list[i][j]= g;
		}
	}

	for (i=Dy-n-1;i>n-1;i--) {
		for (j=Dx-n-1;j>n-1;j--) {
			if (list[i][j]==0) continue;
			g=Dx+Dy;
			for (ii=m-1;ii>=0;ii--) {
				for (jj=m-1;jj>=0;jj--) {
 					if (Mask1[ii][jj]<0) break;
 					if (Mask2[ii][jj]==0) continue;
					t=list[i-n+ii][j-n+jj]+Mask2[ii][jj];
					if (t<g) g=t;
				}
				if (Mask1[ii][jj]<0) break;
			}
			if (list[i][j]>g) list[i][j]= g; 
		}
	}

	max=0;
	for (i=0;i<Dy;i++) {
		for (j=0;j<Dx;j++) {
			list[i][j] /= 5;
 			if (list[i][j]>max) max=list[i][j];
		}
	}

	for(i=0;i<Dy;i++) {
		lists=(BYTE*) list[i];
		for (j=0,k=0;j<Dx;j++,k+=2) lists[j]=lists[k];    
		memcpy(list1[i],lists,Dx);             
	}
   
	for(i=0;i<Dy;i++) 
		if (list[i]) free(list[i]); 
	free(list);  
	return(max);
}  

int EDMask[9][2]={{ 0, 0},{-1,0},{ 0,-1},{0,1},{1,0},
				  {-1,-1},{-1,1},{ 1,-1},{1,1}};

void WINAPI erosion(BYTE **list0,BYTE **list1,int Dx,int Dy,int Mask[][2],int MaskLen)
{
  int  i,j,k;

  for(k=0;k<Dy;k++) 
    memset(list0[k],0,Dx);                           
 
  for(j=1;j<Dy-1;j++) {
    for(i=1;i<Dx-1;i++){ 
		for(k=0;k<MaskLen;k++) {                      
		if (list1[j+Mask[k][1]][i+Mask[k][0]]==0)                
	      break;
	  }
      if (k==MaskLen) list0[j][i]=1;                
	}
  }
}

void WINAPI dilation(BYTE **list0,BYTE **list1,int Dx,int Dy,int Mask[][2],int MaskLen)
{
  int  i,j,k;

  for(k=0;k<Dy;k++) 
    memset(list0[k],0,Dx);                           
 
  for(j=1;j<Dy-1;j++) {
    for(i=1;i<Dx-1;i++){ 
		for(k=0;k<MaskLen;k++) {                      
			if (list1[j+Mask[k][1]][i+Mask[k][0]]==1) {                
          list0[j][i]=1;                          
	      break;
		}
	  }
	}
  }
}

void WINAPI Erosion(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   erosion(list0,list1,Dx,Dy,EDMask,9);
}

void WINAPI Dilation(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   dilation(list0,list1,Dx,Dy,EDMask,9);
}

void WINAPI Inneredge(BYTE **list0,BYTE **list1,int Dx,int Dy)
{ 
   long i, j;

   erosion(list0,list1,Dx,Dy,EDMask,9);

   for (j=0;j<Dy;j++) {
	  for (i=0;i<Dx;i++) {
         list0[j][i] ^= list1[j][i];   
	  }
   }
} 

void WINAPI Outteredge(BYTE **list0,BYTE **list1,int Dx,int Dy)
{ 
   long i, j;

   dilation(list0,list1,Dx,Dy,EDMask,9);

   for (j=0;j<Dy;j++) {
	  for (i=0;i<Dx;i++) {
         list0[j][i] ^= list1[j][i];   
	  }
   }
} 

void WINAPI Morphologyedge(BYTE **list0,BYTE **list1,int Dx,int Dy)
{ 
   long i,j,mark=1;
   BYTE **listw;

   listw=(BYTE**)malloc(Dy*sizeof(BYTE*));
   for(j=0;j<Dy;j++) 
	  listw[j]=(BYTE*) malloc(Dx);
 
   erosion(list0,list1,Dx,Dy,EDMask,9);
   dilation(listw,list1,Dx,Dy,EDMask,9);

   for (j=0;j<Dy;j++) {
	  for (i=0;i<Dx;i++) {
         list0[j][i] ^= listw[j][i];   
	  }
   }

   for(j=0;j<Dy;j++) 
      if (listw[j]) free(listw[j]);
   free(listw);  
} 

void WINAPI Skeleton(BYTE **list0,BYTE **list1,int Dx,int Dy)
{ 
   long i,j,k,m,mark=1;
   BYTE **listw,**listu;
   BYTE **lista,**listb,**listc;

   listw=(BYTE**)malloc(Dy*sizeof(BYTE*));
   listu=(BYTE**)malloc(Dy*sizeof(BYTE*));
   for(k=0;k<Dy;k++) {
  	  listw[k]=(BYTE*) malloc(Dx);
 	  listu[k]=(BYTE*) malloc(Dx);
      memset(list0[k],0,Dx);              
   }
  
   lista=list1;
   listb=listw;
   while(mark) {
	  erosion(listb,lista,Dx,Dy,EDMask,9);

	  listc=lista;
	  lista=listb;
	  listb=listc;
      erosion(listb,lista,Dx,Dy,EDMask,9);
      dilation(listu,listb,Dx,Dy,EDMask,9);

      mark=0;
  	  for (j=0;j<Dy;j++) {
		 for (i=0;i<Dx;i++) {
			m=lista[j][i] ^ listu[j][i];
            list0[j][i] |= m;
			mark |= m;
		 }
	  }
   }
   
   for(k=0;k<Dy;k++) {
      if (listw[k]) free(listw[k]);
      if (listu[k]) free(listu[k]);
   }
   free(listw);  
   free(listu);  
}

int  hMask[8][9][2]={{{1,1},{0,1},{1,0},{0,0},},
                     {{-1,0},{-1,-1},{0,-1},{0,0},},
                     {{-1,0},{-1,1},{0,1},{0,0},},
                     {{0,-1},{1,-1},{1,0},{0,0},},
                     {{1,1},{0,1},{-1,1},{0,0},},
                     {{-1,-1},{0,-1},{1,-1},{0,0},},
                     {{-1,0},{-1,1},{-1,-1},{0,0},},
                     {{1,-1},{1,0},{1,1},{0,0}} };
int  mMask[8][9][2]={{{-1,0},{-1,-1},{0,-1},},
                     {{1,1},{0,1},{1,0},},
                     {{0,-1},{1,-1},{1,0},},
                     {{-1,0},{-1,1},{0,1},},
                     {{-1,-1},{0,-1},{1,-1},},
                     {{1,1},{0,1},{-1,1},},
                     {{1,-1},{1,0},{1,1},},
                     {{-1,0},{-1,1},{-1,-1}} };
int  hMaskLen[8]={4,4,4,4,4,4,4,4};
int  mMaskLen[8]={3,3,3,3,3,3,3,3};

void hmt(BYTE **list0,BYTE **list1,int Dx,int Dy,
		int hMask[][2],int hMaskLen,int mMask[][2],int mMaskLen)
{
	int  i,j,k;
	BYTE **listw,**listu;
 
	listw=(BYTE**)malloc(Dy*sizeof(BYTE*));             
	listu=(BYTE**)malloc(Dy*sizeof(BYTE*));
	for(k=0;k<Dy;k++) {
		listw[k]=(BYTE*) malloc(Dx);
		for (i=0;i<Dx;i++) listw[k][i]=1-list1[k][i];
		listu[k]=(BYTE*) malloc(Dx);
	}

	erosion(list0,list1,Dx,Dy,hMask,hMaskLen);
	erosion(listu,listw,Dx,Dy,mMask,mMaskLen);

	for (j=0;j<Dy;j++) {
		for (i=0;i<Dx;i++) {
			if (!list0[j][i]) continue; 
			if (!listu[j][i]) list0[j][i]=0;
		}
	}
   
	for(k=0;k<Dy;k++) {
		if (listw[k]) free(listw[k]);
		if (listu[k]) free(listu[k]);
	}
	free(listw);  
	free(listu);  
}

void WINAPI MorphologyThin(BYTE **list0,BYTE **list1,int Dx,int Dy)
{ 
	long i,j,k,mark=1,m=0;
 
	while(mark) {
		mark=0;
		for (k=0;k<8;k++) {
			hmt(list0,list1,Dx,Dy,hMask[k],hMaskLen[k],
		                   mMask[k],mMaskLen[k]);
			for (j=0;j<Dy;j++) {
				for (i=0;i<Dx;i++) {
					if (list0[j][i]==1) {
						mark=1;
						list1[j][i]=0;
					}
				}
			}
		}
	}
}

void CreateDeleteTable(int *tab)
{ 
   int  Mask[8][8]={{1,2,0,0,0,2,1,1},{0,2,1,1,1,2,0,0},
                    {0,0,0,2,1,1,1,2},{1,1,1,2,0,0,0,2},
                    {2,0,0,0,2,1,1,1},{2,1,1,1,2,0,0,0},
                    {0,0,2,1,1,1,2,0},{1,1,2,0,0,0,2,1}};
   int	Table[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
   int  i,j,k,n,s,t[4],tn;
  
   for (i=0;i<256;i++) tab[i]=0;
 
   for (i=0;i<8;i++) {
   	  s=0;
	  tn=0;
	  for (j=0;j<8;j++) {
		 if (Mask[i][j]==1) s |= Table[j]; 
		 else if (Mask[i][j]==2) {
			 t[tn++] = Table[j];
		 }
	  }
	  for (j=0;j<2;j++) {
         n=s;
		 if (j) n |= t[0];
		 for (k=0;k<2;k++) {
			if (k) n |= t[1];
			tab[n]=8*(i+1)+2*j+k;
		 }
	  }
   }
}
   
int  CrossM(BYTE **list,int x,int y)
{
  int  i,t;
  int  Mask3[9][2] ={{ 1, 0},{ 1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1, 1},{ 0, 1},{ 1, 1},{ 1, 0}};

  for (i=0,t=0; i<8; i++) {
    if ((list[y+Mask3[i][1]][x+Mask3[i][0]]==0)&& 
        (list[y+Mask3[i+1][1]][x+Mask3[i+1][0]]>=1)) t++;
  }
  return(t);
}

void WINAPI PatternThin(BYTE **list,int Dx,int Dy)
{ 
   int  DeleteTab[256],mark=1;
   int  Mask[8][2]={{ 1, 0},{ 1,-1},{ 0,-1},{-1,-1},
                    {-1, 0},{-1, 1},{ 0, 1},{ 1, 1}};
   int	Table[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
   long i,j,k,n,model,a,b,c;
   BYTE **listw,*bufw;

   bufw =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
   listw=(BYTE**) malloc(Dy*sizeof(BYTE*));
   for(j=0;j<Dy;j++) {
      listw[j]=bufw+j*Dx;
	  memcpy(listw[j],list[j],Dx);
   }

   CreateDeleteTable(DeleteTab);
  
   n=0;
   while(mark) { 
 	  mark=0;
	  if (n%2==0) {
	     a=c=b=1;
	  }
	  else {
		 a=Dx-2;
		 c=Dy-2;
		 b=-1;
	  }
      for (j=c;j<Dy-1 && j>0;j+=b) {
         for (i=a;i<Dx-1 && i>0;i+=b) {
            if (list[j][i]==0) continue;
            model=0;
		    for (k=0;k<8;k++) {
		       if (list[j+Mask[k][1]][i+Mask[k][0]])
			      model |= Table[k];
			}
		    if (DeleteTab[model]) {
			   if (CrossM(listw,i,j)<2) {
                  mark=1;
		          listw[j][i]=0;
			   }
			}
		 }
	  }
	  n++;
      for (j=1;j<Dy-1;j++) 
	     memcpy(list[j],listw[j],Dx);
   }
  
   free(bufw);
   free(listw);  
}

void WINAPI gerosion(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,k,m,n,g;
  BYTE *bp,*p;
  BYTE Mask[25];

  memset(Mask,1,9);
  for(i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      p=Mask;	
      for (m=0,g=255;m<3;m++) {	
        bp=list1[i-1+m]+j-1;	
		for (n=0;n<3;n++) {
		  if (*p++) {
			k=(*bp++);
			if (k<g) g=k;
		  }
 		}
      }
      list0[i][j] = g;           
    }
  }
}

void WINAPI gdilation(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,k,m,n,g;
  BYTE *bp,*p;
  BYTE Mask[25];

  memset(Mask,1,9);
  for(i=1;i<Dy-1;i++) {
    for (j=1;j<Dx-1;j++) {
      p=Mask;	
      for (m=0,g=0;m<3;m++) {	
        bp=list1[i-1+m]+j-1;	
		for (n=0;n<3;n++) {
		  if (*p++) {
			k=(*bp++);
			if (k>g) g=k;
		  }
 		}
      }
      list0[i][j] = g;           
	}
  }
}

void WINAPI GErosion(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   gerosion(list0,list1,Dx,Dy);
}

void WINAPI GDilation(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
   gdilation(list0,list1,Dx,Dy);
}

void WINAPI GGrad(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  BYTE *bufw;
  BYTE **listw;
  int  i,j;
 
  bufw =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  listw=(BYTE**) malloc(Dy*sizeof(BYTE*));
  for(i=0;i<Dy;i++) listw[i]=bufw+i*Dx;
  
  gdilation(list0,list1,Dx,Dy);
  gerosion(listw,list1,Dx,Dy); 
 
  for (i=1;i<Dy-1;i++) {
	for (j=1;j<Dx-1;j++) {
      list0[i][j]=list0[i][j]-listw[i][j];
 	}
  }

  free(bufw);  
  free(listw);  
}  

void WINAPI GIBorder(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j;
 
  gerosion(list0,list1,Dx,Dy);
  for (i=1;i<Dy-1;i++) {
	for (j=1;j<Dx-1;j++) {
      list0[i][j] = list1[i][j]-list0[i][j];
	}
  }
}  

void WINAPI GOBorder(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j;
 
  gdilation(list0,list1,Dx,Dy);
  for (i=1;i<Dy-1;i++) {
	for (j=1;j<Dx-1;j++) {
      list0[i][j] = list0[i][j]-list1[i][j];
	}
  }
}  

int		G_Thre=1;

void WINAPI GTopHat(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  BYTE *bufw;
  BYTE **listw;
  int  i,j,k;
 
  bufw =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  listw=(BYTE**) malloc(Dy*sizeof(BYTE*));
  for(i=0;i<Dy;i++) listw[i]=bufw+i*Dx;
 
  gerosion(list0,list1,Dx,Dy); 
  gdilation(listw,list0,Dx,Dy);

  for (i=1;i<Dy-1;i++) {
	for (j=1;j<Dx-1;j++) {
      k=(int) list1[i][j]-listw[i][j];
	  if (k>=G_Thre) k=1;
	  else k=0;
      list0[i][j]=k;
 	}
  }
  free(bufw);  
  free(listw);  
}  

void WINAPI GBlackTopHat(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  BYTE *bufw;
  BYTE **listw;
  int  i,j,k;
 
  bufw =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  listw=(BYTE**) malloc(Dy*sizeof(BYTE*));
  for(i=0;i<Dy;i++) listw[i]=bufw+i*Dx;
 
  gdilation(list0,list1,Dx,Dy); 
  gerosion(listw,list0,Dx,Dy);

  for (i=1;i<Dy-1;i++) {
	for (j=1;j<Dx-1;j++) {
      k=(int) listw[i][j]-list1[i][j];
	  if (k>=G_Thre) k=0;
	  else k=1;
      list0[i][j]=k;
 	}
  }
  free(bufw);  
  free(listw);  
}  

long WINAPI SearchScale(long *pg,int n)
{
	int  i,j,k,m;
	int  tab[256];
	long max;

	for (i=0;i<256;i++) tab[i]=i;                  
	for (i=0;i<255;i++) {           
		max=pg[tab[i]];    
		k=i;
		for (j=i+1;j<256;j++) {
			if (pg[tab[j]]>max) {
				max=pg[tab[j]];   
				k=j;
			}
		}
		m=tab[k];     tab[k]=tab[i];
		tab[i]=m;
	}
	if (n>0) n--;
	return(pg[tab[n]]);
}

void TableSmooth(long *pg, int m, int n)	//  曲线平滑
{
  int i,j,k;

  for (j=0;j<n;j++) {
    k=pg[0];
    for (i=1;i<m-1;i++) pg[i-1]=(pg[i-1]+pg[i]+pg[i+1])/3;	 
    for (i=m-1;i>0;i--) pg[i]=pg[i-1];	 
    pg[0]=k;
  }
}

//----------------------------------------------------------------------

#define	BOUND(x,mn,mx)	((x)<(mn)?(mn):((x)>(mx)?(mx):(x)))

int  calchue(int angle,int col1,int col2,int min)  
{
   int  rcode;

   rcode=(int) (256.0*(angle+((120.0)*(col1-min)/
		(col1+col2-(min+min))))/360.0+0.5);
   return(rcode);
}

void maxmin(int val1,int val2,int val3,int *max,int *min)
{                                    
   if (val1>=val2) {
      if (val1>=val3) {
	 *max = val1;
	 *min = (val2<=val3) ? val2 : val3;
      }
      else {
	 *max=val3;	*min=val2;
      }
   }
   else {
      if (val2>=val3) {
	 *max = val2;
	 *min = (val1<=val3) ? val1 :val3;
      }
      else {
	 *max=val3;     *min=val1;
      }
   }
}

void WINAPI RgbToHsv(BYTE *hsvpal,BYTE *rgbpal,int count)
{                                      //  RGB 模式转换成 HSV 模式
   int  hue,sat,red,grn,blu,col1,col2,angle;
   int  j,max,min;

   for (j=0;j<count;j++) {
      blu=*rgbpal++;	grn=*rgbpal++;             
      red=*rgbpal++;
      maxmin(red,grn,blu,&max,&min);             
      if (max==min) {                  
	     hue=0;    sat=0;
      }
      else {                                             
		  if (min==blu) {                         
	    angle=0;    col1=grn;    col2=red;
	 }
		  else if (min==red) {                    
	    angle=120;  col1=blu;    col2=grn;
	 }
		  else if (min==grn) {                    
	    angle=240;  col1=red;    col2=blu;
	 }
	 hue=calchue(angle,col1,col2,min);           
	 sat=(int) (255.0*(max-min)/max);            
      }
      *hsvpal++=(BYTE) hue;                         
      *hsvpal++=(BYTE) sat;
      *hsvpal++=(BYTE) max;
   }
}

void WINAPI HsvToRgb(BYTE *rgbpal,BYTE *hsvpal,int count)
{                                      
   int  j,red,grn,blu,hue,sat,max,min;

   for (j=0;j<count;j++) {
      hue=*hsvpal++;	sat=*hsvpal++;             
      max=*hsvpal++;
      hue=(int)(360.0*hue/255.0);              
      if (sat==0) {                       
	 red=grn=blu=max;                            
      }
      else {                                       
	 min=(int)((255.0-sat)*max/255.0);         
	 if (hue<=120) {                           
	    blu=min;                                 
	    if (hue<=60) {
	       red=max;                              
	       grn=(int)(min+(double)hue*(max-min)/(120.0-hue));
	    }
	    else {
	       grn=max;                              
	       red=(int)(min+(120.0-hue)*(max-min)/hue);
	    }
	 }
	 else if (hue<=240) {                      
	    red=min;                                 
	    if (hue<=180) {
	       grn=max;                              
	       blu=(int)(min+(hue-120.0)*(max-min)/(240.0-hue));
	    }
	    else {
	       blu=max;                              
	       grn=(int)(min+(240.0-hue)*(max-min)/(hue-120.0));
	    }
	 }
	 else {                                    
	    grn=min;                                 
	    if (hue<=300) {
	       blu=max;                              
	       red=(int)(min+(hue-240.0)*(max-min)/(360.0-hue));
	    }
	    else {
	       red=max;                              
	       blu=(int)(min+(360.0-hue)*(max-min)/(hue-240.0));
	    }
	 }
      }
      *rgbpal++=(BYTE) blu;                         
      *rgbpal++=(BYTE) grn;
      *rgbpal++=(BYTE) red;
   }
}

int  WINAPI HueHistogShift(long *pg)
{
   int  i,j,p,dp;
   long pg0[256],kk;
   BYTE *buf1,*buf0;
   
   p=42;
   for (i=0;i<256;i++) {
	  pg0[i]=0;
      for (j=i-p;j<i+p;j++) pg0[i]+=pg[(j+256)%256];
   }
 
   kk=pg0[0];		dp=0;
   for (i=0;i<256;i+=85) { 
      if (pg0[i]<kk) {
	     kk=pg0[i];
		 dp=i;
	  }
   }

   buf0=(BYTE*) (&pg0[256-dp]);
   buf1=(BYTE*) (&pg[0]);
   memcpy(buf0,buf1,sizeof(long)*dp);
   buf0=(BYTE*) (&pg0[0]);
   buf1=(BYTE*) (&pg[dp]);
   memcpy(buf0,buf1,sizeof(long)*(256-dp));
   buf0=(BYTE*) (&pg0[0]);
   buf1=(BYTE*) (&pg[0]);
   memcpy(buf1,buf0,sizeof(long)*256);
   return(dp);
}

double	DoubleTab[256];

void WINAPI RgbToYiq(BYTE *yiqpal,BYTE *rgbpal,int count)
{
	int		i,x;
	double	B,G,R,Y,I,Q;

	for (x=0,i=0;x<count;x++,i+=3) {
		B=DoubleTab[rgbpal[i]];
		G=DoubleTab[rgbpal[i+1]];
		R=DoubleTab[rgbpal[i+2]];
		Y=0.29889531*R+0.58662247*G+0.11448223*B;
		I=0.59597799*R-0.27417610*G-0.32180189*B;
		Q=0.21147017*R-0.52261711*G+0.31114694*B;
		yiqpal[i]  =(BYTE) (255*Y);
		yiqpal[i+1]=(BYTE) ((I/0.595978+1)*127);
		yiqpal[i+2]=(BYTE) ((I/0.522617+1)*127);
	}
}

double fPow3(double xyz)
{
	double t;

	if (xyz>0.008856) t=pow(xyz,0.333333);
 	else  t=7.787*xyz+0.1379;
 	return(t);
}

void WINAPI RgbToLab(BYTE *labpal,BYTE *rgbpal,int count)
{
	int		i,x;
	double	B,G,R,X,Y,Z,L,a,b;

 	for (x=0,i=0;x<count;x++,i+=3) {
		B=DoubleTab[rgbpal[i]];
		G=DoubleTab[rgbpal[i+1]];
		R=DoubleTab[rgbpal[i+2]];
		X=0.49018626*R+0.30987954*G+0.19993420*B;
		Y=0.17701522*R+0.81232418*G+0.01066060*B;
		Z=0.00000000*R+0.01007720*G+0.98992280*B;
		if (Y>0.008856) 
			L=116*pow(Y,0.333333)-16;
		else 
			L=903.3*Y;
		a=500*(fPow3(X)-fPow3(Y));
		b=200*(fPow3(X)-fPow3(Z));
		labpal[i]  =(BYTE) (255*L/100);
		labpal[i+1]=(BYTE) (255*(a+128.179003)/310.505326);
		labpal[i+2]=(BYTE) (255*(b+ 82.377974)/224.847274);
	}
}

//------------------------------------------------

int	   ThreTable[256];
int    *code;
POINT  *dot;
int	   code_n,dot_n;
int    inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1,+1},{ 0,+1},{+1,+1}  };
int    Trx1,Try1,Trx2,Try2;
int    ppp;
long   sss;
double factor;
struct TAB *tab;

void set_thre(int track_f, int isr)
{            	      
   int  k;

   for (k=0;k<256;k++) {
      if (track_f==0) {
	 if (k>isr) ThreTable[k]=0;
	 else       ThreTable[k]=1;	     
      }
      else {
	 if (k<isr) ThreTable[k]=0;
	 else       ThreTable[k]=1;         
      }
   }
}

int  WINAPI SingleTrack(BYTE **list,int i,int j,int iop,int *code,int flag)
{               
   int  kw,code_n;
   int  curr[2],next[2];               
   int  n,n1,u,ki,kj,ns,ne;
  
   if (flag==4) u=2;
   else         u=1;

   code[0]=curr[0]=next[0]=i;    
   code[1]=curr[1]=next[1]=j;	                     
   code_n=3;	                       
   code[3]=-1;
   do {
      kw=0;	                     
      ns=iop;    ne=ns-8;            
      for (n=ns;n>ne;n-=u) {    
	     n1 = (n+8) % 8;	         
	     ki=curr[0]+inc[n1][0];
 	     kj=curr[1]+inc[n1][1];
         if ((ki>=Trx1)&&(kj>=Try1)&&(ki<=Trx2)&&(kj<=Try2)) {	
 	        if (ThreTable[list[kj][ki]]==1) break;	             
		 }
	  }
      if (n!=ne) {                               
	     next[0]=ki;  next[1]=kj;          
	     iop=n1;	                   
	  }
      else  kw = 1;	                 
  
      if ((curr[0]==i)&&(curr[1]==j)&&(iop==code[3]))  break;   
      code[code_n++]=iop;	                   
      curr[0]=next[0];   curr[1]=next[1];      
      if ((flag==8)&&(iop%2==0)) iop--; 
      iop=(iop+2)%8;	               
   }
   while(kw==0);	                         

   code[2]=code_n-3;	                       
   return(code_n-3);
}

int  WINAPI Code4To8(int  *code)
{
   int i,k,m,n,t;
 
   n=code[2];
   code[n+3]=code[3];
   for (i=0,k=0;i<n;i++) {
	  t=code[i+3];
      m=(code[i+4]-t+8)%8;
	  if ((m==2)||(m==-6)) {
		 m=t+1;	    i++;
	  }
	  else  m=t;    
      code[k+3]=m;	k++;
   }

   if ((code[3]%2==0)&&
	   (code[3]-code[k+2]==1)) {
     code[3]=code[k+2];
	 k--;
   }
   code[2]=k;
   return(k);
}

int  WINAPI CodeToTable(int *code,POINT *dot)      
{  
   int  tab[8][8]={
      // 0 1 2 3 4 5 6 7  
       { 0,0,0,0,2,2,2,2 },     // 0    
       { 1,1,1,1,0,3,3,3 },     // 1   
       { 1,1,1,1,0,0,3,3 },     // 2  
       { 1,1,1,1,0,0,0,3 },     // 3  
       { 1,1,1,1,0,0,0,0 },     // 4  
       { 0,3,3,3,2,2,2,2 },     // 5  
       { 0,0,3,3,2,2,2,2 },     // 6  
       { 0,0,0,3,2,2,2,2 }  };  // 7  
   int  i,j,n,k,k1,ki,kj,d;
   int  dot_n;

   dot_n=0;	                             

   ki=code[0];   kj=code[1];	                 
   n=code[2];
   if (n==1) {
      dot[0].x=ki;	  dot[0].y=kj;                    
      dot[1].x=ki;	  dot[1].y=kj;                    
      return(2);                                    
   }
   code[n+3]=code[3];	             
   for (i=3;i<n+3;i++) {	           
      k=code[i]%8;   k1=code[i+1]%8;   
      d=tab[k][k1];	                   
      ki+=inc[k][0];   kj+=inc[k][1];	         
      if (d!=0) {	                   
	    dot[dot_n].x  =ki;
	    dot[dot_n++].y=kj;                    
	    if (d==3) {
	      dot[dot_n].x  =ki;
	      dot[dot_n++].y=kj;                      
		}
      }
   }

   for (i=0;i<dot_n-1;i++) {                  
      k=i;      n=dot[i].y;
      for (j=i+1;j<dot_n;j++) {
	    if (dot[j].y<n) {
	      k=j;	n=dot[j].y;
		}
      }
      ki=dot[i].x;          kj=dot[i].y;
      dot[i].x=dot[k].x;    dot[i].y=n;
      dot[k].x=ki;          dot[k].y=kj;
   }
   for (i=1;i<dot_n;i++) {	          
      for (j=dot_n-1;j>=i;j--) {
	    if (dot[j-1].y!=dot[j].y) continue; 
	    if (dot[j-1].x>dot[j].x) {
	      ki=dot[j-1].x;          kj=dot[j-1].y;
	      dot[j-1].x=dot[j].x;    dot[j-1].y=dot[j].y;
	      dot[j].x=ki;            dot[j].y=kj;
		}
      }
   }
   return(dot_n);                                    
}

int  WINAPI fillarea(BYTE **list,POINT *dot, int dot_n,int n)
{  
   int  i,y,k,s;
  
   for (i=0,s=0;i<dot_n;i+=2) {	         
     y=dot[i].y;
	 k=dot[i+1].x-dot[i].x+1;
	 s+=k;
	 memset(&list[y][dot[i].x],n,k);
   }
   return(s);
}

int  WINAPI fillareaA(BYTE **list,POINT *dot, int dot_n,int m,int n)
{  
   int  i,j,y,s;
  
   for (i=0,s=0;i<dot_n;i+=2) {	         
      y=dot[i].y;
 	  for (j=dot[i].x;j<=dot[i+1].x;j++) {
		 if (list[y][j]==m)	{
			 list[y][j]=n;
			 s++;
		 }
	  }
   }
   return(s);
}

int  WINAPI perimeter(int *code)  
{
  int i,e=0,ppp=0,n;

  n=code[2];
  for (i=3;i<n+3;i++) {
    if (code[i]%2) e++;
    else  ppp++;	   
  }
  ppp=(int) (ppp+(1.414*e+0.5));
  return(ppp);
}

long WINAPI area(POINT *dot, int dot_n)  
{
  int  i;
  long sss=0;

  for (i=0;i<dot_n;i+=2) {	
    sss+=(dot[i+1].x-dot[i].x+1);
  }
  return(sss);
}

double WINAPI form_factor(int ppp,long sss) 
{
  double factor=0;

  if (sss>0)
     factor=(double) ppp*ppp/sss/12.56;
  if (factor<1) factor=1.5;
  return(factor);
}

void WINAPI CentreGravity(POINT *dot,int dot_n,double *px,double *py)
{
   int    i;
   double len,xyu,yyu,sss;

   xyu=yyu=sss=0;
   for (i=0;i<dot_n;i+=2) {
      len=(dot[i+1].x-dot[i].x+1);  
	  sss+=len;                      
	  xyu += len*(dot[i+1].x+dot[i].x)/2;
	  yyu += len*dot[i].y;               
   }
   xyu = xyu/sss;                        
   yyu = yyu/sss;                        
   *px=xyu;			*py=yyu;
}

void WINAPI MutiTrack(BYTE **list,int Dx,int Dy)
{
  int    i,j,n;
  
  Trx1=0;			Try1=0;
  Trx2=Dx-1;		Try2=Dy-1;                   
 
  dot =(POINT*) malloc(sizeof(POINT)*MAX_DOTN);
  code=(int*) malloc(sizeof(int)*MAX_DOTN);      
                                                   
  n=2;
  for (j=0;j<Dy-1;j++) {
    for (i=0;i<Dx-1;i++) {  
 	  if (ThreTable[list[j][i]]==1) {	   
		code_n=SingleTrack(list,i,j,4,code,4);       
        code_n=Code4To8(code);            
		dot_n =CodeToTable(code,dot);         
   	    fillarea(list,dot,dot_n,n++);
 		if (n==7) n+=2;
 		else if (n==15) n+=17;
		else if (n==248) n=2;
	  }
	}
  }
  free(code);                                     
  free(dot);
}

int  WINAPI CreateTab(BYTE **list,int x, int y, int Dx,int Dy,struct TAB *tab)
{                                    
  int   i,j,k,f,num;
   
  for (i=y,num=0;i<y+Dy;i++) {
    for (j=x,k=0,f=0;j<x+Dx;j++) {
	  if (list[i][j]) k++;                    
      else if (k) f=1;
	  if ((j==x+Dx-1)&&(k>0)) {
		j++;	f=1;
	  }
 	  if (f==1) {
	    tab[num].label=0;                
	    tab[num].x1=j-k;                
	    tab[num].y =i;
	    tab[num].x2=j-1;
	    num++;                          
	    f=k=0;                            
	  }
	}
  }
  return(num);                          
}

int  WINAPI MakeLabel(struct TAB *tab,int num,int data[][2],int flag)     
{                                
  int  line[1000];
  int  i,j,k0,k1,k2,t,no,d_num;
  int  m,n,x1l,x1r,x2l,x2r,y,end,color;
 
  if (flag==8) no=1;                    
  else  no=0;                           
  tab[num].y=0;
  y=-1;
  for (i=0,end=0;i<=num;i++) {          
	if (tab[i].y!=y) {                  
	  line[end++]=i;
	  y=tab[i].y;
	}
  }
  color=1;                  
  k0=k1=line[0];            
  d_num=0;                  
  for (t=0;t<end;t++) {
    k2=line[t];                      
	for (i=k0;i<k1;i++) {               
      y=tab[i].y;		m=tab[i].label;      
	  x1l=tab[i].x1;	x1r=tab[i].x2;
      for (j=k1;j<k2;j++) {             
		if (tab[j].y!=y+1) break;
        n=tab[j].label;                                       
        x2l=tab[j].x1;	x2r=tab[j].x2;
		if ((x1l<=x2r+no)&&(x2l<=x1r+no)) {  
		  if (m==n) continue;                          
		  if (n==0) {                          
 			 n=tab[j].label=m;          
		  }
		  else {           
			if (n<m) {
	          data[d_num][0]=n;           
	          data[d_num][1]=m;
			}
			else {
	          data[d_num][0]=m;           
	          data[d_num][1]=n;
			}
	        d_num++;
		  }
		}
	  }
	}
    for (j=k1;j<k2;j++) {               
	  if (tab[j].label==0) tab[j].label=color++;
	} 
	k0=k1;                              
	k1=k2;                              
  }
  return(d_num);
}

void WINAPI UniformLabel(struct TAB *tab,int num,int data[][2],int d_num)
{                                          
  int  i,j,k,m,n;

  for (i=0;i<d_num-1;i++) {             
    k=i;      n=data[i][0];
    for (j=i+1;j<d_num;j++) {
      if (data[j][0]<n) {
	    k=j;		n=data[j][0];
      }
    }
    m=data[i][0];            n=data[i][1];
    data[i][0]=data[k][0];   data[i][1]=data[k][1];
    data[k][0]=m;            data[k][1]=n;
  }

  for (i=d_num-1;i>=0;i--) {            
    m=data[i][0];	n=data[i][1];
    for (j=0;j<num;j++) {
      if (tab[j].label==n) tab[j].label=m;
	}
    for (j=0;j<i;j++) {
      if (data[j][0]==n)  data[j][0]=m;      
      if (data[j][1]==n)  data[j][1]=m;
    }
  }
}

void WINAPI SortLabel(struct TAB * tab,int num) 
{
  int  i,j,k,n;
  struct TAB temp;

  for (i=0;i<num-1;i++) {                    
    k=i;      n=tab[i].label;
    for (j=i+1;j<num;j++) {
      if (tab[j].label<n) {
	    k=j;		n=tab[j].label;
      }
    }
	if (i!=k) {
      memcpy(&temp,&tab[i],sizeof(struct TAB));    
      memcpy(&tab[i],&tab[k],sizeof(struct TAB));
      memcpy(&tab[k],&temp,sizeof(struct TAB));
	}
  }
}
 
void WINAPI SearchArea(struct TAB *tab,int num,int flag)  
{
  int  data[1000][2],d_num;
 
  d_num=MakeLabel(tab,num,data,flag);        
  UniformLabel(tab,num,data,d_num);          
  SortLabel(tab,num);                        
}

int   CreateLineTableIndex(struct TAB *tab,int num,int area[][2],int a_n)
{
	int		i,j,k,m,t;
 
	for (i=0;i<a_n;i++) area[i][0]=num;
 	j=tab[0].label;
	k=m=t=0;
	for (i=0;i<=num;i++) {           
		if (tab[i].label!=j) { 
			area[k][0]=m;      
			area[k][1]=t;      
			j=tab[i].label;
 			k++;
			m=i;
			t=0;
		}
 		t+=tab[i].x2-tab[i].x1+1;
		if (k==a_n-1) break;
	}
	return(k);
}

void  LineCoding(BYTE **list,int nWidth,int nHeight) 
{
 	int		area[1000][2];
	int		i,j,k,m;
	int		num,an;
    
 	tab=(struct TAB *) malloc(sizeof(struct TAB)*MAX_DOTN);
	if (tab==NULL)  return;

	num=CreateTab(list,0,0,nWidth,nHeight,tab);
	SearchArea(tab,num,4);
 
	an=CreateLineTableIndex(tab,num,area,1000);

	m=2;
	for (i=0;i<an;i++) {       
		for (j=area[i][0];j<area[i+1][0];j++) {
			k=tab[j].x2-tab[j].x1+1;
 			memset(&list[tab[j].y][tab[j].x1],m,k);
		}
		m++;
 		if (m==7) m+=2;
 		else if (m==15) m+=17;
		else if (m==248) m=2;
	}
	free(tab);
}

int  SearchObject(BYTE **list,struct TAB *tab,int area[][2],int an)
{
	int    i,j,k,f,f1,t;
  
	f=1;
	for (i=0;i<an;i++) {       
		f1=1;
		for (j=area[i][0];j<area[i+1][0];j++) {
			k=tab[j].x2-tab[j].x1+1;
			for (t=tab[j].x1+1;t<tab[j].x2;t++) {
 				if (list[tab[j].y][t]) {
					f1=0;
					break;
				}
			}
			if (f1==0) break;
		}
		if (f1==1) {
			for (j=area[i][0];j<area[i+1][0];j++) {
				k=tab[j].x2-tab[j].x1+1;
 				memset(&list[tab[j].y][tab[j].x1],1,k);
			}
		}
		else f=0;
	}
	return(f);
}

void LimitErosing(BYTE **list1,int Dx,int Dy)
{
	BYTE  *buf0;
	BYTE  **list0,**listw1,**listw0;
	int   k,s,m,n,num,an;
	int	  area[1000][2];
   
 	tab=(struct TAB *) malloc(sizeof(struct TAB)*MAX_DOTN);
	if (tab==NULL)  return;

	buf0 =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
	list0=(BYTE**) malloc(Dy*sizeof(BYTE*));        
	for(k=0;k<Dy;k++) 
		list0[k]=buf0+k*Dx;
 
	for (k=0,s=0;s==0;k++) {
  		if (k%2==0) {
			listw1=list1;		
			listw0=list0;
			n=9;
		}
		else {
			listw0=list1;		
			listw1=list0;
			n=5;
		}
		erosion(listw0,listw1,Dx,Dy,EDMask,n);

		if (k<=4) continue;
		num=CreateTab(listw1,0,0,Dx,Dy,tab);
		SearchArea(tab,num,8);
		an=CreateLineTableIndex(tab,num,area,1000);
		s=SearchObject(listw0,tab,area,an);
	}
 
	if (k%2) {
		for (m=0;m<Dy;m++)
			memcpy(list1[m],list0[m],Dx);
	}
 
	free(buf0);  
	free(list0);  
 
	free(tab);
}

int  CrossHighA(BYTE **list,int x,int y,int n)
{
  int  i,t;
  int  Mask3[9][2] ={{ 1, 0},{ 1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1, 1},{ 0, 1},{ 1, 1},{ 1, 0}};
 
  for (i=0,t=0; i<8; i++) {
     if (list[y+Mask3[i][1]][x+Mask3[i][0]]>=n) t++;
  }
  return(t);
}

int  CrossHighB(BYTE **list,int x,int y,int n)
{
  int  i,t;
  int  Mask3[9][2] ={{ 1, 0},{ 1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1, 1},{ 0, 1},{ 1, 1},{ 1, 0}};
  int  Mask5[17][2]={{ 2, 0},{ 2,-1},{ 2,-2},{ 1,-2},
                     { 0,-2},{-1,-2},{-2,-2},{-2,-1},
                     {-2, 0},{-2, 1},{-2, 2},{-1, 2},
                     { 0, 2},{ 1, 2},{ 2, 2},{ 2, 1},{ 2, 0}};

  for (i=0,t=0; i<8; i++) {
     if ((list[y+Mask3[i][1]][x+Mask3[i][0]]>=n)&& 
        (list[y+Mask3[i+1][1]][x+Mask3[i+1][0]]<n)) t++;
  }
  if (t==1) {
    for (i=0,t=0; i<16; i++) {
      if ((list[y+Mask5[i][1]][x+Mask5[i][0]]>=n)&& 
          (list[y+Mask5[i+1][1]][x+Mask5[i+1][0]]<n)) t++;
	}
  }
  return(t);
}

void ConditionDilating(BYTE **list,BYTE **list1,int Dx,int Dy,int time)
{ 
  BYTE *buf0;
  BYTE **list0,**listw1,**listw0;
  int  i,j,k,t,m=0,n;
  
  buf0 =(BYTE*)  malloc(Dx*Dy*sizeof(BYTE));
  list0=(BYTE**) malloc(Dy*sizeof(BYTE*));        
  for(k=0;k<Dy;k++) list0[k]=buf0+k*Dx;
 
  for (k=0;(k<=5)||(m>0);k++) {
  	if (k%2==0) {
      listw1=list1;		
	  listw0=list0;
	  n=9;
	}
	else {
      listw0=list1;		
	  listw1=list0;
	  n=5;
	}
	dilation(listw0,listw1,Dx,Dy,EDMask,n);

    if (k>=5) {
      for (j=2;j<Dy-2;j++) {
        for (i=2;i<Dx-2;i++) {
	      if (list0[j][i] ^ list1[j][i]) {
 		    t=CrossHighA(listw0,i,j,1);
			if (t==8) listw0[j][i]=0;
		  }
		}
	  }
	}

    for (j=2,m=0;j<Dy-2;j++) {
      for (i=2;i<Dx-2;i++) {
	    if (list0[j][i] ^ list1[j][i]) {
 		  if (list[j][i]==0) listw0[j][i]=0;
 		  else if (k>=5) {
		    t=CrossHighB(listw1,i,j,1);
			if (t>1) listw0[j][i]=0;
			else m++;
		  }
		}
	  }
	}
 	if (k>time) break;
  }

  free(buf0);  
  free(list0);  
}  

int  LineMaximum(BYTE **list,int y,int Dx,struct TAB *tab)
{                             
  int    j,k,num;
 
  for (j=1,num=0,k=0;j<Dx;j++) {
    if (list[y][j-1]<list[y][j]) k=1;               
 	else if ((k)&&(list[y][j-1]==list[y][j])) k++;  
	else if (k) {                         
	  tab[num].flag=list[y][j-1];
	  tab[num].label=0;            
	  tab[num].x1=j-k;
	  tab[num].y=y;
	  tab[num].x2=j-1;
 	  num++;                 
	  k=0;                  
	}
  }
  return(num);              
}

int  SearchSeed(BYTE **list,int Dx,int Dy,struct TAB  *tab)
{                                     
  int  i,j,k,m,n,x1l,x1r,x2l,x2r,y0,t,color;
  int  num0,num,k1,k2;
 
  color=1;
  num0=num=0;
  k1=LineMaximum(list,0,Dx,&tab[num0]);  
  num+=k1;
  for (k=1;k<Dy;k++) {
	k2=LineMaximum(list,k,Dx,&tab[num]); 
    for (i=num0;i<num0+k1;i++) {        
      y0=tab[i].y;		m=tab[i].flag;  
	  x1l=tab[i].x1;	x1r=tab[i].x2;
      t=0;
      for (j=num;j<num+k2;j++) {
        n=tab[j].flag;                  
        x2l=tab[j].x1;	x2r=tab[j].x2;
		if (tab[j].y-1==y0) {           
		  if ((x1l<=x2r+1)&&(x2l<=x1r+1)) {  
			t=1;
			if (m>n) {                     
			  tab[j].label=-1;               
			}
			else {
			  if (n==m)                    
 			    tab[j].label=tab[i].label; 
			  else
  			    tab[j].label=color++;      
 			  tab[i].label=-1;             
			}
		  }
		}
		else break;                        
	  }
	  if (t==0) {
		int  j;
		for (j=x1l-1;j<=x1r+1;j++) {   
		  if (list[y0+1][j]>=m) {    
	        tab[i].label=-1;
		    break;
		  }
		}
	  }
	}
    for (j=num;j<num+k2;j++) {
	  if (tab[j].label==0) tab[j].label=color++;   
	}                       
    num0+=k1;		num+=k2; 
  	k1=k2;
  }
 
  for (j=0,m=0;j<num;j++) {
	if (tab[j].label==-1) continue;
    memcpy(&tab[m],&tab[j],sizeof(struct TAB));
	m++;
  }
  return(m);
}

int  MergeSeed(struct TAB *tab,int num)
{                          
  int    i,j,m,d,x,y,x1,y1,d1,max;
  double dd;

  for (j=1;j<num;j++) {
 	x=tab[j].x1;                      
	y=tab[j].y;
	d=tab[j].flag;
    for (i=0;i<j;i++) {
      if (tab[i].label==-1) continue;
	  x1=tab[i].x1;                   
	  y1=tab[i].y;
	  d1=tab[i].flag;
      dd=sqrt((double)(x1-x)*(x1-x)+(y1-y)*(y1-y));  
	                               
      max= (d1>d) ? d1 : d;
 	  if (dd<1.25*max) {      
		if (d>d1)                  
 	      tab[i].label=-1;
		else
 	      tab[j].label=-1;
 		break;
	  }
	}
  }
  for (j=0,m=0;j<num;j++) {
	if (tab[j].label==-1) continue;
    memcpy(&tab[m],&tab[j],sizeof(struct TAB));
	m++;
  }
  return(m);
}

int  SearchKernel(BYTE **list,int Dx,int Dy)
{
  int  i,n,max,num;
   
  max=Distance(list,Dx,Dy);
   
  tab =(struct TAB *) malloc(sizeof(struct TAB)*MAX_DOTN);
  if (tab==NULL)  return(0);

  num=SearchSeed(list,Dx,Dy,tab);
  num=MergeSeed(tab,num);
  
  n=0;
  for (i=0;i<num;i++) {
	if (tab[i].flag>max/3) {
	   n++;
	   list[tab[i].y][tab[i].x1]=1;
	}
  }
  free(tab);
  return(n);
}

int  ParaMeasure(BYTE **list,int Dx,int Dy,CPoint point,int flag)
{
	int		i,k,x,y,s;

	x=point.x;
	y=point.y;
	k=list[y][x];
	while(list[y][x]==k) x--;
 	x++;

	Trx1=Try1=0;
	Trx2=Dx-1;		
	Try2=Dy-1;                   
 
	dot =(POINT*) malloc(sizeof(POINT)*MAX_DOTN);
	if (dot==NULL)  return(0);
	code=(int*) malloc(sizeof(int)*MAX_DOTN);      
	if (code==NULL) return(0);
 
    for (i=0;i<256;i++) ThreTable[i]=0;
    ThreTable[k]=1;

	code_n=SingleTrack(list,x,y,4,code,8);       
 	dot_n =CodeToTable(code,dot);         

	if (flag==1) { 
		s=fillarea(list,dot,dot_n,15);
	    ppp=perimeter(code);                           
 	    sss=area(dot,dot_n);                           
 	    factor=form_factor(ppp,sss);                   
	}
	else if (flag==2) {
		s=fillareaA(list,dot,dot_n,k,15);
	}

	free(code);
	free(dot);
	return(s);
}

void GetAreaParament(int *prm,int *ar,double *fac)
{
	*prm = ppp;
	*ar  = sss;
	*fac = factor;
}

int	  MaskX,MaskY;

int line_coor(int x1,int y1,int x2,int y2,POINT *dot)
{
  int t,dis,dx,dy,xerr=1,yerr=1,incx,incy;

  dx=x2-x1;        dy=y2-y1;
  if (dx>0)        incx=1;
  else if (dx==0)  incx=0;
  else             incx=-1;
  if (dy>0)        incy=1;
  else if (dy==0)  incy=0;
  else             incy=-1;
  dx=abs(dx);      dy=abs(dy);
  if (dx>dy)       dis=dx;
  else             dis=dy;
  for (t=0;t<dis+1;t++) {
    dot->x=x1;     dot->y=y1;
    dot++;
    xerr+=dx;      yerr+=dy;
    if (xerr>dis) {
      xerr-=dis;   x1+=incx;
    }
    if (yerr>dis) {
      yerr-=dis;   y1+=incy;
    }
  }
  return(dis);
}

int  LineToCode(int x,int y,int x1,int y1,int *code)
{                  
  int  i,k,n,dx,dy;
  POINT *dot;
  int  tab[3][3]={3,2,1,4,0,0,5,6,7};

  dx=abs(x1-x);      dy=abs(y1-y);
  dot=(POINT*) malloc(sizeof(POINT)*(dx+dy+1));	
  n=line_coor(x,y,x1,y1,dot);			  
  k=code[2]+3;
  for (i=0;i<n;i++) {  
    dx=dot[i+1].x-dot[i].x+1; 
    dy=dot[i+1].y-dot[i].y+1;
    if ((dx==1)&&(dy==1))  continue;
    code[k++]=tab[dy][dx];          
  }
  code[2]=k-3;                      
  free(dot);					    
  return(k-3);
}

void CodeRever(int *code)                  
{
   int  i,n,k,x,y;

   x=code[0];			y=code[1];
   n=code[2];
   for (i=0;i<n;i++) {
	  k=code[3+i];
      x+=inc[k][0];		y+=inc[k][1];
   }
   code[0]=x;			code[1]=y;

   for (i=0;i<n/2;i++) {
      k=(code[3+i]+4)%8;            
      code[3+i]=(code[3+n-1-i]+4)%8;
      code[3+n-1-i]=k;
   }
   if (n%2) code[3+n/2]=(code[3+n/2]+4)%8;
}

int CalcAbsolCode(int k1,int k,int m)           
{                                       
   int  i;

   i=(k+8-k1)%8;                                       
   if (i>3) i-=8;                    
   return(m+i);                                        
}

int ContourDirection(int *code)  
{
   int  i,k,k1,m,n;
 
   n=code[2];                       
   for (i=0;i<4;i++)
      code[3+n+i]=code[3+i];        

   k1=code[3];     m=0;
   for (i=0;i<=n;i++) {
      k=code[i+3];
      m=CalcAbsolCode(k1,k,m);      
      k1=k;
   }
   if (m<0)  k=0;                   
   else      k=1;                   
   return(k);
}

void  OutRectangleC(int *code,int *x1,int *y1,int *x2,int *y2)
{                                      
   int  i,n,k,x,y,xi,yi,xa,ya;

   n=code[2];
   xi=xa=x=code[0];			
   yi=ya=y=code[1];
   for (i=0;i<n;i++) {
	  k=code[3+i];
      x+=inc[k][0];		y+=inc[k][1];
      if (x<xi) xi=x;
	  if (x>xa) xa=x;
	  if (y<yi) yi=y;
	  if (y>ya) ya=y;
   }
   *x1=xi;		*y1=yi;
   *x2=xa;		*y2=ya;
}

void  MakingMask(int x,int y,int flag)
{
	if (flag==0) {
		code=(int*) malloc(sizeof(int)*MAX_DOTN);
		dot =(POINT*) malloc(sizeof(POINT)*MAX_DOTN);
		code[0] = MaskX = x;
		code[1] = MaskY = y;
		code[2] = 0;
	}
	else if (flag==1) {
		LineToCode(MaskX,MaskY,x,y,code);
		MaskX = x;
		MaskY = y;
	}
	else if (flag==2) {
  		LineToCode(x,y,code[0],code[1],code);
		if (ContourDirection(code)==1)
			CodeRever(code);
       dot_n=CodeToTable(code,dot);         
	}
}

void  GetMaskSize(int *x,int *y,int *Dx,int *Dy)
{
	int		x1,y1,x2,y2;

	OutRectangleC(code,&x1,&y1,&x2,&y2);
	*x=x1-1;
	*y=y1-1;
	*Dx=abs(x1-x2)+3;
	*Dy=abs(y1-y2)+3;
}

void  GetMaskImage(BYTE **list,int x,int y)
{
	int  i,x1,y1,k;
  
	for (i=0;i<dot_n;i+=2) {	         
		x1=dot[i].x-x;
		y1=dot[i].y-y;
		k=dot[i+1].x-dot[i].x+1;
 		memset(&list[y1][x1],1,k);
	}
	free(code);
	free(dot);
}

#endif  //!_INC_PROCESSC
 