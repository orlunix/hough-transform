//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	edge_detection.cpp
//	
//**************************************************************************************************
#include "includes.h"
/*
// 3x3 Template Isotropic Horizontal  Sobel
double TH[] = { -1, -1.414, -1,
                 0,  0,      0,
                 1,  1.414,  1 };
// 3x3 Template Isotropic Vertical Sobel
double TV[] = {  -1,     0, 1,
                 -1.414, 0, 1.414,
                 -1,     0, 1 };
*/
// 3x3 Template Horizontal  Sobel
double TH_3x3[] = { -1.0, -2.0, -1.0,
                     0.0,  0.0,  0.0,
                     1.0,  2.0,  1.0  };
// 3x3 Template Vertical Sobel
double TV_3x3[] = {  -1.0, 0.0, 1.0,
                     -2.0, 0.0, 2.0,
                     -1.0, 0.0, 1.0  };
// 5x5 Template Horizontal  Sobel
double TH_5x5[] = {  -2.0, -3.0, -4.0, -3.0, -2.0,
                     -1.0, -2.0, -3.0, -2.0, -1.0,
                      0.0,  0.0,  0.0,  0.0,  0.0,
                      1.0,  2.0,  3.0,  2.0,  1.0,
                      2.0,  3.0,  4.0,  3.0,  2.0  };
// 5x5 Template Vertical Sobel
double TV_5x5[] = {  -2.0, -1.0, 0.0, 1.0, 2.0,
                     -3.0, -2.0, 0.0, 2.0, 3.0,
                     -4.0, -3.0, 0.0, 3.0, 4.0,
                     -3.0, -2.0, 0.0, 2.0, 3.0,
                     -2.0, -1.0, 0.0, 1.0, 2.0  };
// 7x7 Template Horizontal  Sobel
double TH_7x7[] = {  -3.0, -4.0, -5.0, -6.0, -5.0, -4.0, -3.0,
                     -2.0, -3.0, -4.0, -5.0, -4.0, -3.0, -2.0,
                     -1.0, -2.0, -3.0, -4.0, -3.0, -2.0, -1.0,
                      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                      1.0,  2.0,  3.0,  4.0,  3.0,  2.0,  1.0,
                      2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0,
                      3.0,  4.0,  5.0,  6.0,  5.0,  4.0,  3.0  };
// 7x7 Template Vertical Sobel
double TV_7x7[] = {  -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0,
                     -4.0, -3.0, -2.0, 0.0, 2.0, 3.0, 4.0,
                     -5.0, -4.0, -3.0, 0.0, 3.0, 4.0, 5.0,
                     -6.0, -5.0, -4.0, 0.0, 4.0, 5.0, 6.0,
                     -5.0, -4.0, -3.0, 0.0, 3.0, 4.0, 5.0,
                     -4.0, -3.0, -2.0, 0.0, 2.0, 3.0, 4.0,
                     -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0  };
// 9x9 Template Horizontal  Sobel
double TH_9x9[] = {  -4.0, -5.0, -6.0, -7.0, -8.0, -7.0, -6.0, -5.0, -4.0,
                     -3.0, -4.0, -5.0, -6.0, -7.0, -6.0, -5.0, -4.0, -3.0,
                     -2.0, -3.0, -4.0, -5.0, -6.0, -5.0, -4.0, -3.0, -2.0,
                     -1.0, -2.0, -3.0, -4.0, -5.0, -4.0, -3.0, -2.0, -1.0,
                      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                      1.0,  2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0,  1.0,
                      2.0,  3.0,  4.0,  5.0,  6.0,  5.0,  4.0,  3.0,  2.0,
                      3.0,  4.0,  5.0,  6.0,  7.0,  6.0,  5.0,  4.0,  3.0,
                      4.0,  5.0,  6.0,  7.0,  8.0,  7.0,  6.0,  5.0,  4.0  };
// 9x9 Template Vertical Sobel
double TV_9x9[] = {  -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0,
                     -5.0, -4.0, -3.0, -2.0, 0.0, 2.0, 3.0, 4.0, 5.0,
                     -6.0, -5.0, -4.0, -3.0, 0.0, 3.0, 4.0, 5.0, 6.0,
                     -7.0, -6.0, -5.0, -4.0, 0.0, 4.0, 5.0, 6.0, 7.0,
                     -8.0, -7.0, -6.0, -5.0, 0.0, 5.0, 6.0, 7.0, 8.0,
                     -7.0, -6.0, -5.0, -4.0, 0.0, 4.0, 5.0, 6.0, 7.0,
                     -6.0, -5.0, -4.0, -3.0, 0.0, 3.0, 4.0, 5.0, 6.0,
                     -5.0, -4.0, -3.0, -2.0, 0.0, 2.0, 3.0, 4.0, 5.0,
                     -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0  };

	int maskSize = 9;

double multi_mask(unsigned char * matrix_data, double * mask, int size){
	int i;
	int longth = size*size;
	double sum = 0.0;
	unsigned char * p1;
	double * p2;
	p1 = matrix_data;
	p2 = mask;
	for(i=0;i<longth;i++){
		sum+=(*p1) * (*p2);
		p1++;
		p2++;
	}
	return sum;
}
	
unsigned char edge_pixels_cal(int x, int y, unsigned char *image){
	int i, j;
	unsigned char matrix_data[81];
	double SumX,SumY;
	
	unsigned int pixel_data_tmp;
	unsigned char edge_pixel_data;
	
	int size = maskSize;
	
	int pos_x,pos_y;//to avoid index less than zero
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			pos_x = (x-size/2+j < 0)? 0 : ((x-size/2+j>IMAGE_WIDTH)?IMAGE_WIDTH:(x-size/2+j));
			pos_y = (y-size/2+i < 0)? 0 : ((y-size/2+i>IMAGE_HEIGHT)?IMAGE_HEIGHT:(y-size/2+i));
			matrix_data[i*size+j]=*(image + IMAGE_WIDTH*pos_y + pos_x );
		}
	}
	switch (size){
		case 3:
			SumX = multi_mask(matrix_data,TH_3x3,3);
			SumY = multi_mask(matrix_data,TV_3x3,3);
			break;
		case 5:
			SumX = multi_mask(matrix_data,TH_5x5,5);
			SumY = multi_mask(matrix_data,TV_5x5,5);
			break;
		case 7:
			SumX = multi_mask(matrix_data,TH_7x7,7);
			SumY = multi_mask(matrix_data,TV_7x7,7);
			break;
		case 9:
			SumX = multi_mask(matrix_data,TH_9x9,9);
			SumY = multi_mask(matrix_data,TV_9x9,9);
			break;
		default:
			SumX = multi_mask(matrix_data,TH_3x3,3);
			SumY = multi_mask(matrix_data,TV_3x3,3);
			break;
	}
	pixel_data_tmp = (unsigned int)sqrt(SumX*SumX + SumY*SumY);
	
	edge_pixel_data = (pixel_data_tmp > 255)?255:((pixel_data_tmp < 0)?0:pixel_data_tmp);
	return edge_pixel_data;
}

//***************************** edge-detection based on gradient ***********************************
void edge_detection(unsigned char * image, int width, int height){
	int i,j;
	unsigned char * temp = (unsigned char *)malloc(width*height*sizeof(unsigned char));
	for(i=0; i < height; i++){
		for(j=0; j < width; j++){
			*(temp + i*width + j)=edge_pixels_cal(j,i,image);
		}
	}
	
	for(i=0; i < height; i++){
		for(j=0; j < width; j++){
			*(image + i*width + j)=*(temp + i*width +j);
		}
	}
	
	free(temp);
}
//***************************** edge-detection based on gradient ***********************************
//In order to implent hough-transform based on gradient, I need a parameter of gradient, GX and GY

unsigned char edge_pixels_cal_gradient(int x,int y, unsigned char *image, double * theta){
	int i, j;
	unsigned char matrix_data[81];
	double SumX,SumY;
	
	unsigned int pixel_data_tmp;
	unsigned char edge_pixel_data;
	
	int size = maskSize;
	
	int pos_x,pos_y;//to avoid index less than zero
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			pos_x = (x-size/2+j < 0)? 0 : ((x-size/2+j>IMAGE_WIDTH)?IMAGE_WIDTH:(x-size/2+j));
			pos_y = (y-size/2+i < 0)? 0 : ((y-size/2+i>IMAGE_HEIGHT)?IMAGE_HEIGHT:(y-size/2+i));
			matrix_data[i*size+j]=*(image + IMAGE_WIDTH*pos_y + pos_x );
		}
	}
	
	switch (size){
		case 3:
			SumX = multi_mask(matrix_data,TH_3x3,3);
			SumY = multi_mask(matrix_data,TV_3x3,3);
			break;
		case 5:
			SumX = multi_mask(matrix_data,TH_5x5,5);
			SumY = multi_mask(matrix_data,TV_5x5,5);
			break;
		case 7:
			SumX = multi_mask(matrix_data,TH_7x7,7);
			SumY = multi_mask(matrix_data,TV_7x7,7);
			break;
		case 9:
			SumX = multi_mask(matrix_data,TH_9x9,9);
			SumY = multi_mask(matrix_data,TV_9x9,9);
			break;
		default:
			SumX = multi_mask(matrix_data,TH_3x3,3);
			SumY = multi_mask(matrix_data,TV_3x3,3);
			break;
	}
	
	*theta = atan2(SumY,SumX);
	
	pixel_data_tmp = (unsigned int)sqrt(SumX*SumX + SumY*SumY);
	
	edge_pixel_data = (pixel_data_tmp > 255)?255:((pixel_data_tmp < 0)?0:pixel_data_tmp);
	return edge_pixel_data;
}
