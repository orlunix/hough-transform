//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	hough_transform.cpp
//**************************************************************************************************
#include "includes.h"
//Greek letter 
//rho
//theta
//pi

#define pi 3.1415926535

//****************************** Draw a line on a picture ******************************************
//This function is designed by me. ^_^
void SetPixel(unsigned char * image, int x, int y, unsigned char color){
	if(x > 0 && x < IMAGE_WIDTH && y > 0 && y < IMAGE_HEIGHT)
	*(image + y*IMAGE_WIDTH + x) = color;
};
//****************************** Draw a line on a picture ******************************************
//The only function copied from the net.
void LineDDA(int x0,int y0,int x1,int y1,int color,unsigned char * hdc){
	float dy,dx,x,y,m;
	dx=(float)(x1-x0);
	dy=(float)(y1-y0);
	m=dy/dx;
	if(x0<x1){
		if(m<=1&&m>=-1){
			y=y0;
			for(x=x0;x<=x1;x++){
				SetPixel(hdc,x,int(y+0.5),color);
				y+=m;
			}
		}
	}
	if(x0>x1){
		if(m<=1&&m>=-1){
			y=y0;
			for(x=x0;x>=x1;x--){
				SetPixel(hdc,x,int(y+0.5),color);
				y-=m;
			}
		}
	}
	if(y0<y1){
		if(m>=1||m<=-1){
			m=1/m;
			x=x0;
			for(y=y0;y<=y1;y++){
				SetPixel(hdc,int(x+0.5),y,color);
				x+=m;
			}
		}
	}
	if(y0>y1){
		if(m<=-1||m>=1){
			m=1/m;
			x=x0;
			for(y=y0;y>=y1;y--){
				SetPixel(hdc,int(x+0.5),y,color);
				x-=m;
			}
		}
	}
}
//******************************Hough transform function *******************************************
void hough_transform(unsigned char * image){
	signed double rho;
	//The compiler told me that:"'signed' : can not be used with type 'double'", but I found I if I 
	//don't add "signed" before double the function "LineDDA" will be hanged up. I don't know why.
	int rho_max;
	double rho_step;
	double theta;
	double theta_step;
	
	int x,y;
	
	int rho_y;
	int theta_x;
	
	unsigned int * vote_matrix;
	
//******************************calculate the vote value *******************************************
	rho_max = (int)sqrt(IMAGE_WIDTH*IMAGE_WIDTH + IMAGE_HEIGHT*IMAGE_HEIGHT);
	rho_step = 2.0*rho_max/(double)IMAGE_HEIGHT ;//implicit conversion
	theta_step = pi/IMAGE_WIDTH;

	vote_matrix = (unsigned int *)malloc(IMAGE_WIDTH*IMAGE_HEIGHT*sizeof(unsigned int));
	
	for(rho_y = 0; rho_y < IMAGE_HEIGHT; rho_y++){
		for(theta_x = 0; theta_x < IMAGE_WIDTH; theta_x++){
			*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 0;
		}
	}
	#ifdef _GRADIENT_
	double gradient_theta = 0.0 ;
	double * p_gt = &gradient_theta;
	double theta_ga;//gradient theta absolute
	double deviation_angle = DEVIATION_ANGLE*pi/180.0;
	double min_angle, max_angle;
	for(y = 0; y < IMAGE_HEIGHT; y++){
		for(x = 0; x < IMAGE_WIDTH; x++){
			//if(*(image + y*IMAGE_WIDTH + x) > 200){
			if(edge_pixels_cal_gradient(x,y,image,p_gt) > 200){
				//for(theta = 0.0;theta < pi; theta += theta_step){
				theta_ga = (gradient_theta < 0)?(gradient_theta+pi) : gradient_theta;
				//printf("theta == %f\n",gradient_theta);getchar();
				if(0.0 == deviation_angle){
					theta = theta_ga;
					rho = (x*cos(theta)) + (y*sin(theta));
					rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
					theta_x = (int)(theta/theta_step + 0.5);
					*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
						*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
				}
				else if(theta_ga - deviation_angle < 0){
						min_angle = 0.0;  max_angle = theta_ga+deviation_angle;
						for(theta = min_angle; theta < max_angle; theta += theta_step){
							rho = (x*cos(theta)) + (y*sin(theta));
							rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
							theta_x = (int)(theta/theta_step + 0.5);
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
									*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
						}
						min_angle = pi+theta_ga-deviation_angle ;  max_angle = pi;
						for(theta = min_angle; theta < max_angle; theta += theta_step){
							rho = (x*cos(theta)) + (y*sin(theta));
							rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
							theta_x = (int)(theta/theta_step + 0.5);
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
									*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
						}
				}else if(theta_ga - deviation_angle >= pi) {
						min_angle = theta_ga-deviation_angle;  max_angle = pi;
						for(theta = min_angle; theta < max_angle; theta += theta_step){
							rho = (x*cos(theta)) + (y*sin(theta));
							rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
							theta_x = (int)(theta/theta_step + 0.5);
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
									*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
						}
						min_angle = 0.0 ;  max_angle = theta_ga+deviation_angle-pi;
						for(theta = min_angle; theta < max_angle; theta += theta_step){
							rho = (x*cos(theta)) + (y*sin(theta));
							rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
							theta_x = (int)(theta/theta_step + 0.5);
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
									*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
						}
				}else {
						min_angle = theta_ga-deviation_angle;  max_angle = theta_ga+deviation_angle;
						for(theta = min_angle; theta < max_angle; theta += theta_step){
							rho = (x*cos(theta)) + (y*sin(theta));
							rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
							theta_x = (int)(theta/theta_step + 0.5);
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
									*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
						}
				}
			
			}
		}
	}
	#else
	for(y = 0; y < IMAGE_HEIGHT; y++){
		for(x = 0; x < IMAGE_WIDTH; x++){
			//if(*(image + y*IMAGE_WIDTH + x) > 200){
			if(edge_pixels_cal(x,y,image) > 200){
				for(theta = 0.0;theta < pi; theta += theta_step){
					rho = (x*cos(theta)) + (y*sin(theta));
					rho_y = (int)(rho/rho_step + IMAGE_HEIGHT/2 + 0.5);
					theta_x = (int)(theta/theta_step + 0.5);
					*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 
							*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) + 1;
					// should define a variable 
					//vote_line_offset = vote_matrix + rho_y*IMAGE_WIDTH
				}
			}
		}
	}
	#endif
//******************************Find the maximum value point ***************************************
	struct Maxpoint{
		unsigned int value;
		unsigned int column;
		unsigned int row;
	}maxpoint={0,0,0};

	for(rho_y = 0; rho_y < IMAGE_HEIGHT; rho_y++){
		for(theta_x = 0; theta_x < IMAGE_WIDTH; theta_x++){
				if(maxpoint.value < *(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x)){
						maxpoint.value = *(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x);
						maxpoint.column = theta_x;   
						maxpoint.row = rho_y;
				}
			//*(vote_matrix +  rho_y*IMAGE_WIDTH + theta_x) = 0;
		}
	}
	
	theta=theta_step * maxpoint.column;
//Actually, when computing vote value maxpoint can be found
//****************************************** data test *********************************************
#ifdef PRINT_HT_PARAMETER
	printf("hough-transform:theta == %f\n",theta);
	printf("max value==%d\n",maxpoint.value);
	printf("maxpoint.column==%d\n",maxpoint.column);
	printf("maxpoint.row==%d\n",maxpoint.row);
	printf("theta_step == %f ",theta_step);
	printf("rho_step == %f ",rho_step);
	printf("rho_max == %d \n",rho_max);
#endif

//************************ Test show the vote matrix data in a image********************************
//	for(y=0; y < IMAGE_HEIGHT; y++){
//		for(x=0; x < IMAGE_WIDTH; x++){
//			*(image + y*IMAGE_WIDTH + x)=*(vote_matrix + y*IMAGE_WIDTH +x);
//		}
//	}	
	
	rho = (int)rho_step*(maxpoint.row - (IMAGE_HEIGHT/2));
	
	int x0,y0,x1,y1;
	x0 = 0;
	y0 = (int)(rho/sin(theta));
	//y0 = (y0 < 0) ? 0 : ((y0 >= IMAGE_HEIGHT) ? (IMAGE_HEIGHT - 1) : y0);
	
	//x0 = (int)(rho - y0*sin(theta))/cos(theta);
	
	x1 = IMAGE_WIDTH - 1;
	y1 = (int)(((rho - ((IMAGE_WIDTH - 1) * cos(theta)))/sin(theta)));
	//y1 = (y1 < 0) ? 0 : ((y1 >= IMAGE_HEIGHT) ? (IMAGE_HEIGHT - 1) : y1);
	
	//x1 = (int)((rho - y1*sin(theta))/cos(theta));
	
	LineDDA(x0,y0,x1,y1,0x00,image);
	//LineDDA(0,0,480,480,0xFF,image);
	
	free(vote_matrix);

}

