//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	timestamp.cpp
//	
//**************************************************************************************************

#include "timestamp.h"

#ifdef _WINDOWS_
	clock_t start,finish;
#else
	double T1,T2;
	struct rusage stRusage;
	struct timeval stTimeval;
#endif

void StartCounter()
{
	#ifdef _WINDOWS_
//		__int64 li;
//		if(!QueryPerformanceFrequency(&li))
//			printf("QueryPerformanceFrequency failed!\n");
//	
//		PCFreq = double(li.QuadPart)/1000.0;
//		QueryPerformanceCounter(&li);
//		CounterStart = li.QuadPart;
		start = clock();
	#else
		getrusage(RUSAGE_SELF, &stRusage);
		stTimeval = stRusage.ru_utime;
	
		T1 = stTimeval.tv_sec + (double)stTimeval.tv_usec*1E-6;
	#endif
}
double GetCounter()
{
	#ifdef _WINDOWS_
//		LARGE_INTEGER li;
//		QueryPerformanceCounter(&li);
//		return double(li.QuadPart-CounterStart)/PCFreq;
		finish = clock();
		return (double)(double)(finish - start) / CLOCKS_PER_SEC;
	#else
		getrusage(RUSAGE_SELF, &stRusage);
		stTimeval = stRusage.ru_utime;
	
		T2 = stTimeval.tv_sec + (double)stTimeval.tv_usec*1E-6;
		
		return T2 - T1;
	#endif

}

//this function is copied from http://cookiebear.info/archives/351
/*
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
 
#define TEST_BY_CLOCK		   (char)(0x00)
#define TEST_BY_TIMES		   (char)(0x01)
#define TEST_BY_GETTIMEOFDAY	(char)(0x02)
#define TEST_BY_GETRUSAGE	   (char)(0x03)
#define TEST_METHOD			 (TEST_BY_GETTIMEOFDAY)
 
#define COORDINATION_X		  (int)(1024)
#define COORDINATION_Y		  (int)(1024)
 
static int g_Matrix[COORDINATION_X][COORDINATION_Y];
 
double getTimeval(){
	struct rusage stRusage;
	struct timeval stTimeval;
	if (TEST_METHOD == TEST_BY_GETTIMEOFDAY) {
		gettimeofday(&stTimeval, NULL);
	} else if (TEST_METHOD == TEST_BY_GETRUSAGE) {
		getrusage(RUSAGE_SELF, &stRusage);
		stTimeval = stRusage.ru_utime;
	}
	return stTimeval.tv_sec + (double)stTimeval.tv_usec*1E-6;
}
int main(){
	int i, j;
	int n = 0;
	clock_t clockT1, clockT2;
	double doubleT1, doubleT2;
 
	if (TEST_METHOD == TEST_BY_CLOCK) {
		clockT1 = clock();
	} else if (TEST_METHOD == TEST_BY_TIMES) {
		times(&clockT1);
	} else if (TEST_METHOD == TEST_BY_GETTIMEOFDAY) {
		doubleT1 = getTimeval();
	} else if (TEST_METHOD == TEST_BY_GETRUSAGE) {
		doubleT1 = getTimeval();
	}
 
	for (i = 0; i < COORDINATION_X; i++) {
		for (j = 0; j < COORDINATION_Y; j++) {
			g_Matrix[i][j] = i * j;
		}
	}
 
	if (TEST_METHOD == TEST_BY_CLOCK) {
		clockT2 = clock();
		printf("Time result tested by clock = %10.30f\n",
				(double)(clockT2 - clockT1)/CLOCKS_PER_SEC);
	} else if (TEST_METHOD == TEST_BY_TIMES) {
		times(&clockT2);
		printf("Time result tested by times = %10.30f\n",
				(double)(clockT2 - clockT1)/sysconf(_SC_CLK_TCK));
	} else if (TEST_METHOD == TEST_BY_GETTIMEOFDAY) {
		doubleT2 = getTimeval();
		printf("Time result tested by gettimeofday = %10.30f\n",
				(double)(doubleT2 - doubleT1));
	} else if (TEST_METHOD == TEST_BY_GETRUSAGE) {
		doubleT2 = getTimeval();
		printf("Time result tested by getrusage = %10.70f\n",
				(double)(doubleT2 - doubleT1));
	}
 
	return 0;
}
*/
