#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include "MeasureCtrl.h"
using namespace std;


MeasureCtrl::MeasureCtrl(void)
{
	flag =-1;  
	oldflag =-1;
	isInit_Echo =false;
	isInit_mudis=false;
	isInit_spath=false;


}

MeasureCtrl::MeasureCtrl(int echo,int trig ,const char* name)
{
	Ctrlname =name;
	flag =-1;  
	oldflag =-1;
	Echo =echo;
	Trig=trig;
	isInit_Echo =true;
	isInit_mudis=false;
	isInit_spath=false;
}


MeasureCtrl::~MeasureCtrl(void)
{

}


bool MeasureCtrl::SetEcho_Trig(int echo,int trig)
{
	Echo =echo;
	Trig=trig;
	isInit_Echo =true;
}


bool MeasureCtrl::SetmusicDistence(vector<float> & mudis)
{
	for(int i=0;i<mudis.size();i++)
	{
		musicDistence.push_back(mudis[i]);
	}
  	isInit_mudis=true;
}	

bool MeasureCtrl::Setsoundpath(vector<string> & spath)
{
	for(int i=0;i<spath.size();i++)
	{
		soundpath.push_back(spath[i]);
	}
	isInit_spath=true;
}



float MeasureCtrl::disMeasure(void)
{
	if(!isInit_Echo)
	{
		throw string("float MeasureCtrl::disMeasure(void) ERRor, do not SetEcho_Trig");
		return -1;
	}
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);

	while(!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis;
}

string MeasureCtrl::GetplayPath(int &playflag)  //playflag 1:play  0:do_nothing  -1:stop
{
	if(!isInit_mudis&&!isInit_spath)
	{
		throw string("char * MeasureCtrl::GetplayPath(int &playflag)ERRor，not isInit_mudis or isInit_spath！");
	}

	string *temp_path;
	float dis = disMeasure();
	printf("%s = %0.2f cm\n",Ctrlname,dis);
	bool isInside =false;  
	for(int i=0;i<musicDistence.size()-1;i++)
	{
		if(dis>=musicDistence[i] &&dis< musicDistence[i+1])
		{
			temp_path=&soundpath[i];
			flag =i+1;
			isInside =true;
			break;
		}
	}
	if(!isInside)
	{
		oldflag =0;
		flag =0;

		playflag =0; //do_nothing
		return "";
		
	}

	if(oldflag <=0)
	{
		oldflag=flag;
		if(flag>0)
		{
			playflag =1;
			return *temp_path;
		}
		else
		{
			playflag =0;
			return "";
		}
	}
	else
	{
		if(oldflag!=flag) 
		{
			oldflag =flag;
			if(flag<=0)
			{
				playflag =0;
				return "";
			}
			else
			{
				playflag =1;
				return *temp_path;
			}
		}
		else
		{
			playflag =0;
			return "";
		}
	}
}


