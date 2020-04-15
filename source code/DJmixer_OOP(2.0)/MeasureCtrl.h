#ifndef MEASURE_H
#define MEASURE_H



#include <vector>
#include <string>
using namespace std;

class MeasureCtrl
{
public:
	MeasureCtrl(void);
	MeasureCtrl(int echo,int trig ,const char* name);
	~MeasureCtrl(void);


	const char* Ctrlname;

	string GetplayPath(int &playflag);
	bool SetEcho_Trig(int echo,int trig);
	bool SetmusicDistence(vector<float> & mudis);
	bool Setsoundpath(vector<string> & spath);

private:
	
	int flag ; 
	int oldflag ;
	int Echo , Trig ;  //GPIO
	bool isInit_Echo ;  //Whether to initialize GPIO
	bool isInit_mudis;
	bool isInit_spath;

	vector<float> musicDistence; 
	vector<string> soundpath;   
	

	float disMeasure(void);

};



#endif

