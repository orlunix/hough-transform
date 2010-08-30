//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	bmpread.h
//	
//**************************************************************************************************

#ifndef _BMP_READ_H_
#define _BMP_READ_H_

//#include "stdio.h"

#pragma pack (2)
typedef struct tagBITMAPFILEHEADER { 
	unsigned short	bfType; 
	unsigned int	bfSize;
	unsigned short	bfReserved1; 
	unsigned short	bfReserved2;
	unsigned int	bfOffBits; 
}BITMAPFILEHEADER, *PBITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER{
	unsigned int	biSize; //表示本结构的大小
	unsigned int	biWidth; //位图的宽度
	unsigned int	biHeight; //位图的高度
	unsigned short	biPlanes; //永远为1 ,由于没有用过所以 没做研究 附msdn解释
							//Specifies the number of planes for the target device. This value must be set to 1. 
	unsigned short	biBitCount;//位图的位数  分为1 4 8 16 24 32 本文没对1 4 进行研究
	unsigned int	biCompression; //本以为压缩类型，但是却另外有作用，稍候解释
	unsigned int	iSizeImage; //表示位图数据区域的大小以字节为单位
	unsigned int	biXPelsPerMeter; 
	unsigned int	biYPelsPerMeter; 
	unsigned int	biClrUsed; 
	unsigned int	biClrImportant; 
}BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD{
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
//	unsigned char	rgbReserved;
}RGBQUAD;

typedef struct tagRGBQUADg{
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
	unsigned char	rgbReserved;
}RGBQUADg;
#pragma pack ()

//void read_8bit_bmp(char * filename,unsigned char * image);

#endif
