//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	hough_transform.h
//**************************************************************************************************
#ifndef	_HOUGH_TRANSFORM_H_
#define	_HOUGH_TRANSFORM_H_

void SetPixel(unsigned char * image, int x, int y, unsigned char color);
void LineDDA(int x0,int y0,int x1,int y1,int color,unsigned char * hdc);
void hough_transform(unsigned char * image);

#endif