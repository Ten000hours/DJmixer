#ifndef MAINBUSI_H
#define MAINBUSI_H

#include "MeasureCtrl.h"
#include "SoundPlay.h"

#define Trig1  9
#define Echo1  8
#define Trig2  2
#define Echo2  0
#define Trig3  13
#define Echo3  12
#define Trig4  11
#define Echo4  10

class MainBusiness
{
public:
	MainBusiness(void);
	~MainBusiness(void);

	void startGame();
	void InitData();

private:
	MeasureCtrl m_MeasureCtrl_music1,m_MeasureCtrl_music2,m_MeasureCtrl_volume1,m_MeasureCtrl_volume2;
	SoundPlay m_SoundPlay1,m_SoundPlay2;


	vector<string> soundpath_vec1 ,soundpath_vec2,volumepath_vec1, volumepath_vec2;
	vector<float> musicDistence_vec1 ,musicDistence_vec2 ,volumeDistence_vec1, volumeDistence_vec2; 


	bool isInitData;

};

#endif

