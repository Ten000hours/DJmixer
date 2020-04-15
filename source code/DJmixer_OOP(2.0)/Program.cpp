#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
 
#include<string.h>  
#include<dirent.h>    
#include<sys/stat.h>   
#include<pthread.h>  
#include <iostream>

#include "MainBusiness.h"

using namespace std;


int main(void)
{
	MainBusiness m_MainBusiness;

try
{
	    m_MainBusiness.InitData();
	    m_MainBusiness.startGame();
}
catch(string &str)
{
      cout<<str<<endl;
}
	return 0;
}
