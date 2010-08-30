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
	unsigned int	biSize; //��ʾ���ṹ�Ĵ�С
	unsigned int	biWidth; //λͼ�Ŀ��
	unsigned int	biHeight; //λͼ�ĸ߶�
	unsigned short	biPlanes; //��ԶΪ1 ,����û���ù����� û���о� ��msdn����
							//Specifies the number of planes for the target device. This value must be set to 1. 
	unsigned short	biBitCount;//λͼ��λ��  ��Ϊ1 4 8 16 24 32 ����û��1 4 �����о�
	unsigned int	biCompression; //����Ϊѹ�����ͣ�����ȴ���������ã��Ժ����
	unsigned int	iSizeImage; //��ʾλͼ��������Ĵ�С���ֽ�Ϊ��λ
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
