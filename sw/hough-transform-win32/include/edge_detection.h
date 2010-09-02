//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	edge_detection.h
//	
//**************************************************************************************************
#ifndef _EDGE_DETECTION_H_
#define _EDGE_DETECTION_H_

unsigned char edge_pixels_cal(int x,int y, unsigned char *image);
void edge_detection(unsigned char * image, int width, int height);
unsigned char edge_pixels_cal_gradient(int x,int y, unsigned char *image, double * theta);


#endif
