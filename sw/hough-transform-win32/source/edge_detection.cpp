//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	edge_detection.cpp
//	
//**************************************************************************************************
#include "includes.h"
// 3x3 Template Isotropic Horizontal  Sobel
double TH[] = { -1, -1.414, -1,
                 0,  0,      0,
                 1,  1.414,  1 };
// 3x3 Template Isotropic Vertical Sobel
double TV[] = {  -1,     0, 1,
                 -1.414, 0, 1.414,
                 -1,     0, 1 };
	int maskSize = 3;

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
	
unsigned char edge_pixels_cal(int x,int y,int size,unsigned char *image){
	int i, j;
	unsigned char matrix_data[9];
	double SumX,SumY;
	
	unsigned char edge_pixel_data;
	
	int pos_x,pos_y;//to avoid index less than zero
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			pos_x = (x-size/2+j < 0)? 0 : ((x-size/2+j>IMAGE_WIDTH)?IMAGE_WIDTH:(x-size/2+j));
			pos_y = (y-size/2+i < 0)? 0 : ((y-size/2+i>IMAGE_HEIGHT)?IMAGE_HEIGHT:(y-size/2+i));
			matrix_data[i*size+j]=*(image + IMAGE_WIDTH*pos_y + pos_x );
//			if (4 == i*size + j)
//			{
//				printf("index==%d\n",IMAGE_WIDTH*pos_y + x+pos_x);
//				printf("pos_x==%d,pos_y==%d\n",pos_x,pos_y);
//			}
		}
	}
	
//	if(matrix_data[4]!=*(image + y*640 +x))printf("wrong here!!!x==%d,y=%d",x,y);
//	getchar();

	SumX = multi_mask(matrix_data,TH,3);
	SumY = multi_mask(matrix_data,TV,3);
	
	SumX = (SumX > 255.0)?255.0:((SumX < 0.0)?0:SumX);
	SumY = (SumY > 255.0)?255.0:((SumY < 0.0)?0:SumY);
	
	edge_pixel_data = (unsigned char)sqrt(SumX*SumX + SumY*SumY);
	
	
	return edge_pixel_data;
}

void edge_detection(unsigned char * image, int width, int height){
	int i,j;
	unsigned char * temp = (unsigned char *)malloc(width*height*sizeof(unsigned char));
	for(i=0; i < height; i++){
		for(j=0; j < width; j++){
			*(temp + i*width + j)=edge_pixels_cal(j,i,maskSize,image);
		}
	}
	
	for(i=0; i < height; i++){
		for(j=0; j < width; j++){
			*(image + i*width + j)=*(temp + i*width +j);
		}
	}
	
	free(temp);
}