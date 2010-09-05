//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	ht_main.cpp
//	
//**************************************************************************************************

#include "includes.h"
	
int main(int argc,char* argv[]){
	BITMAPFILEHEADER filehead;
	BITMAPINFOHEADER infohead;

	FILE * fpr;
	FILE * fpw;
//	unsigned int xsize;
	unsigned int i;
//	unsigned int j;
//	unsigned int k;
//	long lhistogram[256];

	unsigned char zero=0;
	
	char readfile[20];
	char writefile[20];
	
	if (argc <= 1){
		strcpy(readfile,"readfile.bmp");
		strcpy(writefile,"writefile.bmp");
	}else if (argc == 2){
		strcpy(readfile,argv[1]);
		strcpy(writefile,"writefile.bmp");
	}else if (argc >= 3){
		strcpy(readfile,argv[1]);
		strcpy(writefile,argv[2]);
	}
	 
	//test
	//printf("%s,%s\n",readfile,writefile);

	/*open file in binary format!*/
	if(!(fpr=fopen(readfile,"rb"))){
		printf("%s\n",readfile);
		printf("read file open error!!!\n");
		exit(0);
	}
	if(!(fpw=fopen(writefile,"wb"))){
		printf("%s\n",writefile);
		printf("write file open error!!!\n");
		exit(0);
	}
	
	
	unsigned char * image = (unsigned char *)malloc(IMAGE_WIDTH*IMAGE_HEIGHT*sizeof(unsigned char));
	//****************read image infomation and matrix from read file*********************************
	fread(&filehead,sizeof(BITMAPFILEHEADER),1,fpr);
	fread(&infohead,sizeof(BITMAPINFOHEADER),1,fpr);
	
	if(infohead.biWidth != 640 || infohead.biHeight != 480 || infohead.biBitCount != 8){
		printf("Image Format is not supported! Please make sure:\n");
		printf("Width		:	640\n");//how to print "define"ed number?fg,IMAGE_WIDTH
		printf("Height		:	480\n");
		printf("BitCount	:	8\n");
		exit(0);
	}
	
	fseek(fpr,filehead.bfOffBits,0);
	
	// how to detect the size of image ?
	fread(image,sizeof(unsigned char),IMAGE_WIDTH*IMAGE_HEIGHT,fpr); // only 640*480 is valid

//************************* Test draw a straight line **********************************************
//	for(i = 0; i < IMAGE_HEIGHT; i++){
//		for(j = 0; j < IMAGE_WIDTH; j++){
//			*(image +  i*IMAGE_WIDTH + j) = 0xFF;
//		}
//	}
	//LineDDA(0,0,480,480,0x00,image);
	//************************************* edge detection *******************************************
	//edge_detection(image, 640, 480);

#ifdef _TIME_MEASURE_
	StartCounter();
#endif

	//************************************* hough transform ******************************************
	hough_transform(image);	

#ifdef _TIME_MEASURE_
	double T = GetCounter();
	printf("Time consume == %10.30f\n",T);
#endif

	//****************write image infomation and matrix from read file********************************
	//write file header info
	fwrite(&filehead,sizeof(filehead),1,fpw);
	fwrite(&infohead,sizeof(infohead),1,fpw);
	//write indexed color
	for(i=0;i<256;i++){
		putc(i, fpw);
		putc(i, fpw);
		putc(i, fpw);
		putc(0, fpw);
	}
	


	fseek(fpw,filehead.bfOffBits,0);
	//write matrix data
	fwrite(image,sizeof(unsigned char),IMAGE_WIDTH*IMAGE_HEIGHT,fpw);
	
	//*************************************** end ****************************************************
	fclose(fpr);
	fclose(fpw);
	free(image);
	return 0;
}