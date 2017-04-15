#pragma once

#ifndef		_INC_PROCESSH
#define		_INC_PROCESSH

struct TAB {                                
  int  label,x1,x2,y,flag;                  
                                            
};

#define  MAX_DOTN  10000
#define	 MAX_NUM   6000

void  WINAPI histog(BYTE **list,long *pg,int x, int y, int Dx, int Dy);  
void  HistogSmooth(long *pg,int n);

void  WINAPI GT(BYTE **list,int Dx,int Dy,int* T_gray);     
void  WINAPI GT_Equal(long* pg,int* T_gray);                
void  WINAPI Border_Equal(long* pg,int* T_gray);            
void  WINAPI GT_histo_eq(long *pg,long *Hista,int* T_gray); 
void  WINAPI GT_linear(int* T_gray);                        
void  WINAPI GT_square(int* T_gray);                        
void  WINAPI GT_sqrt(int* T_gray);                          
void  WINAPI GT_log(int* T_gray);                           
void  WINAPI GT_exp(int* T_gray);                           
void  WINAPI GT_nega(int* T_gray);                          
void  WINAPI DensitySegment(RGBQUAD *pal);                  
void  WINAPI PsendoColor(RGBQUAD *pal);                     

int   WINAPI FormAnalysis(long *pg,int *tab,int *buf,int *bn);  
int   WINAPI Otsu(long *pg);                                
int   WINAPI Minimum(long *pg);                            
int   WINAPI KSW_Entropic(long *pg);                        
int   WINAPI Moment(long *pg);                              
int   WINAPI BiasNormal(long *pg);                         
int   WINAPI ColligationThreshold(long *pg);
int   WINAPI SimpleThreshold(long *pg);
int   WINAPI Ptile(long *pg,double nn);                     
 
void  WINAPI Gradiant(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Roberts(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Sobel(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Laplacian(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI LapSketch(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Kirsch(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction);
void  WINAPI Robinson(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction);
void  WINAPI Prewitt(BYTE **list0,BYTE **list1,int Dx,int Dy,int direction);
void  WINAPI RemoveLineNoise(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Smooth5(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Smooth9(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI BoundEnhance(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Median5(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Median9(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI SobelThinning(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI SobelThin(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI LogPrewitt(BYTE **list0,BYTE **list,int Dx,int Dy,double pi);

void  WINAPI RemoveWhiteDot(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI RemoveBlackDot(BYTE **list0,BYTE **list1,int Dx,int Dy);
int   WINAPI LineWidthW(BYTE **list,int x,int y,int n);
int   WINAPI LineWidthB(BYTE **list,int x,int y,int n);
void  WINAPI OnePWidthW(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI OnePWidthB(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI LapSketch8(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI LoG(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI LineDetect(BYTE **list0,BYTE **list1,int Dx,int Dy);
 
void  WINAPI Hilditch(BYTE **list,int Dx,int Dy);
void  WINAPI Deutch(BYTE **list,int Dx,int Dy);
void  WINAPI FastThin(BYTE **list,int Dx,int Dy);
void  WINAPI Naccache(BYTE **list,int Dx,int Dy);
void  WINAPI Pavlidis1(BYTE **list,int Dx,int Dy);
void  WINAPI Pavlidis2(BYTE **list,int Dx,int Dy);
void  WINAPI Rosenfeld4(BYTE **list,int Dx,int Dy);
void  WINAPI Rosenfeld8(BYTE **list,int Dx,int Dy);
void  WINAPI RemoveNoise(BYTE **list,int Dx,int Dy);

int   WINAPI Distance(BYTE **list,int Dx,int Dy);

void  WINAPI erosion(BYTE **list0,BYTE **list1,int Dx,int Dy,int Mask[][2],int MaskLen);
void  WINAPI dilation(BYTE **list0,BYTE **list1,int Dx,int Dy,int Mask[][2],int MaskLen);
 
void  WINAPI Erosion(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Dilation(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Inneredge(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Outteredge(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Morphologyedge(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI Skeleton(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI MorphologyThin(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI PatternThin(BYTE **list,int Dx,int Dy);
 
void  WINAPI gerosion(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI gdilation(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GErosion(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GDilation(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GOpen(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GClose(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GTopHat(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GBlackTopHat(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GIBorder(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GOBorder(BYTE **list0,BYTE **list1,int Dx,int Dy);
void  WINAPI GGrad(BYTE **list0,BYTE **list1,int Dx,int Dy);
 
void  WINAPI RgbToHsv(BYTE *hsvpal,BYTE *rgbpal,int count);
void  WINAPI HsvToRgb(BYTE *rgbpal,BYTE *hsvpal,int count);
int   WINAPI HueHistogShift(long *pg);
void  WINAPI RgbToYiq(BYTE *yiqpal,BYTE *rgbpal,int count);
void  WINAPI RgbToLab(BYTE *labpal,BYTE *rgbpal,int count);
 
long  WINAPI SearchScale(long *pg,int n);
void  TableSmooth(long *pg, int m, int n);
void  HistogramSmooth(long *pg,int n);
int   GrayImageType(long *pg);

void  set_thre(int track_f, int isr);
int   WINAPI SingleTrack(BYTE **list,int i,int j,int iop,int *code,int flag);
int   WINAPI Code4To8(int  *code);
int   WINAPI CodeToTable(int *code,POINT *dot);    
int   WINAPI fillarea(BYTE **list,POINT *dot, int dot_n,int n);
int   WINAPI fillareaA(BYTE **list,POINT *dot, int dot_n,int m,int n);
int   WINAPI perimeter(int *code);  
long  WINAPI area(POINT *dot,int dot_n);  
double WINAPI form_factor(int ppp,long sss);  
void  WINAPI MutiTrack(BYTE **list,int Dx,int Dy);
int   CreateLineTableIndex(struct TAB *tab,int num,int area[][2],int a_n);
void  LineCoding(BYTE **list,int Dx,int Dy);
void  LimitErosing(BYTE **list1,int Dx,int Dy);
void  ConditionDilating(BYTE **list,BYTE **list1,int Dx,int Dy,int time);
int   SearchKernel(BYTE **list1,int Dx,int Dy);
int   ParaMeasure(BYTE **list1,int Dx,int Dy,CPoint point,int flag);
void  GetAreaParament(int *prm,int *ar,double *fac);
void  MakingMask(int x,int y,int flag);
void  GetMaskSize(int *x,int *y,int *Dx,int *Dy);
void  GetMaskImage(BYTE **list,int x,int y);
  
#endif  //!_INC_PROCESSH


 