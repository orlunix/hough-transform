//**************************************************************************************************
//	Author	:	hlren
//	Email		:	hl.ren.pub@gmail.com
//	Website	:	http://www.cnblogs.com/lunix
//==================================================================================================
//	File		:	timestamp.h
//	
//**************************************************************************************************

#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include "includes.h"

#if defined _WINDOWS_
//#include <windows.h>
//#define CLOCKS_PER_SEC ((clock_t)1000)
#include <time.h>
#elif defined _LINUX_

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>

#endif

void StartCounter();
double GetCounter();

#endif