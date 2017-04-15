/******************************************************************
  CreatePal.cpp

  Performing Color Quantization algorithm

******************************************************************/

#include "stdafx.h"
  
#ifndef		_CREATEPAL_C
#define		_CREATEPAL_C

typedef struct _NODE 
{
    BOOL bIsLeaf;               // TRUE if node has no children
    UINT nPixelCount;           // Number of pixels represented by this leaf
    UINT nRedSum;               // Sum of red components
    UINT nGreenSum;             // Sum of green components
    UINT nBlueSum;              // Sum of blue components
    struct _NODE* pChild[8];    // Pointers to child nodes
    struct _NODE* pNext;        // Pointer to next reducible node
} NODE;

void AddColor (NODE**, BYTE, BYTE, BYTE, UINT, UINT, UINT*, NODE**);
NODE* CreateNode (UINT, UINT, UINT*, NODE**);
void ReduceTree (UINT, UINT*, NODE**);
void DeleteTree (NODE**);
void GetPaletteColors (NODE*, RGBQUAD*, UINT*);

void TrueColorToIndex(CImage *pImg0,CImage *pImg1)
{
 	struct	IMAGEPARAMENT P;
	CImage	gpImg;
	RGBQUAD	ColorTab[256];
	HDC		hMemDC;
   
	GetImageParament(pImg1,&P);
 	gpImg.Create(P.nWidth,P.nHeight,8,0);
 
	Create8TreePal(pImg1,ColorTab,256,8);
	SetAllPalette(&gpImg,ColorTab);

	hMemDC = gpImg.GetDC();
	pImg1->BitBlt(hMemDC,0,0,P.nWidth,P.nHeight,0,0,SRCCOPY);
	gpImg.ReleaseDC();

	ImageCopy(pImg0,&gpImg);
	gpImg.Destroy();
}
 
// local function to build optimal palette from CImage
void Create8TreePal(CImage *pImg,RGBQUAD *Pal, UINT nMaxColors, UINT nColorBits)
{
	struct	IMAGEPARAMENT P;
    int		i, j;
    BYTE	*pbBits;
    BYTE	r, g, b;
    NODE	*pTree;
    UINT	nLeafCount,nIndex;
    NODE	*pReducibleNodes[9];
      
 	GetImageParament(pImg,&P);

    // Initialize octree variables
    pTree = NULL;
    nLeafCount = 0;
	for (i=0; i<=(int) nColorBits; i++) pReducibleNodes[i] = NULL;

    for (i=0; i<P.nHeight; i++) {
		pbBits = (BYTE*) pImg->GetPixelAddress(0,i);
        for (j=0; j<P.nWidth; j++) {
            b = *pbBits++;
            g = *pbBits++;
            r = *pbBits++;
			if (P.nBitCount==32) pbBits++;
            AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                      pReducibleNodes);
            while (nLeafCount > nMaxColors)
                ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
        }
    }

	nIndex = 0;
    GetPaletteColors (pTree, Pal, &nIndex);
    DeleteTree (&pTree);
}

// local function to add a color to octree
void AddColor (NODE** ppNode, BYTE r, BYTE g, BYTE b, UINT nColorBits,
    UINT nLevel, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int nIndex, shift;
    static BYTE mask[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

    // If the node doesn't exist, create it
    if (*ppNode == NULL)
        *ppNode = CreateNode (nLevel, nColorBits, pLeafCount,
                              pReducibleNodes);

    // Update color information if it's a leaf node
    if ((*ppNode)->bIsLeaf) {
        (*ppNode)->nPixelCount++;
        (*ppNode)->nRedSum += r;
        (*ppNode)->nGreenSum += g;
        (*ppNode)->nBlueSum += b;
    }

    // Recurse a level deeper if the node is not a leaf
    else {
        shift = 7 - nLevel;
        nIndex = (((r & mask[nLevel]) >> shift) << 2) |
            (((g & mask[nLevel]) >> shift) << 1) |
            ((b & mask[nLevel]) >> shift);
        AddColor (&((*ppNode)->pChild[nIndex]), r, g, b, nColorBits,
                  nLevel + 1, pLeafCount, pReducibleNodes);
    }
}

// local function to create a new node in octree
NODE* CreateNode (UINT nLevel, UINT nColorBits, UINT* pLeafCount,
                  NODE** pReducibleNodes)
{
    NODE* pNode;

    if ((pNode = (NODE*) HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY,
        sizeof (NODE))) == NULL)
        return NULL;

    pNode->bIsLeaf = (nLevel == nColorBits) ? TRUE : FALSE;
    if (pNode->bIsLeaf) (*pLeafCount)++;
    else { // Add the node to the reducible list for this level
        pNode->pNext = pReducibleNodes[nLevel];
        pReducibleNodes[nLevel] = pNode;
    }
    return pNode;
}

// local function to reduce the nodes of octree
void ReduceTree (UINT nColorBits, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int i;
    NODE* pNode;
    UINT nRedSum, nGreenSum, nBlueSum, nChildren;

    // Find the deepest level containing at least one reducible node
    for (i=nColorBits - 1; (i>0) && (pReducibleNodes[i] == NULL); i--);

    // Reduce the node most recently added to the list at level i
    pNode = pReducibleNodes[i];
    pReducibleNodes[i] = pNode->pNext;

    nRedSum = nGreenSum = nBlueSum = nChildren = 0;
    for (i=0; i<8; i++) {
        if (pNode->pChild[i] != NULL) {
            nRedSum += pNode->pChild[i]->nRedSum;
            nGreenSum += pNode->pChild[i]->nGreenSum;
            nBlueSum += pNode->pChild[i]->nBlueSum;
            pNode->nPixelCount += pNode->pChild[i]->nPixelCount;
            HeapFree (GetProcessHeap (), 0, pNode->pChild[i]);
            pNode->pChild[i] = NULL;
            nChildren++;
        }
    }

    pNode->bIsLeaf = TRUE;
    pNode->nRedSum = nRedSum;
    pNode->nGreenSum = nGreenSum;
    pNode->nBlueSum = nBlueSum;
    *pLeafCount -= (nChildren - 1);
}

// local function to delete a node of octree
void DeleteTree (NODE** ppNode)
{
    int i;

    for (i=0; i<8; i++) {
        if ((*ppNode)->pChild[i] != NULL)
            DeleteTree (&((*ppNode)->pChild[i]));
    }
    HeapFree (GetProcessHeap (), 0, *ppNode);
    *ppNode = NULL;
}

// local function to get color entry from a palette
void GetPaletteColors (NODE* pTree, RGBQUAD* Pal, UINT* pIndex)
{
    int i;

    if (pTree->bIsLeaf) {
        Pal[*pIndex].rgbRed =
            (BYTE) ((pTree->nRedSum) / (pTree->nPixelCount));
        Pal[*pIndex].rgbGreen =
            (BYTE) ((pTree->nGreenSum) / (pTree->nPixelCount));
        Pal[*pIndex].rgbBlue =
            (BYTE) ((pTree->nBlueSum) / (pTree->nPixelCount));
        (*pIndex)++;
    }
    else {
        for (i=0; i<8; i++) {
            if (pTree->pChild[i] != NULL)
                GetPaletteColors (pTree->pChild[i], Pal, pIndex);
        }
    }
}

#endif		//!_CREATEPAL_C
