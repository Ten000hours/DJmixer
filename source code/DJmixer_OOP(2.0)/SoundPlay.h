#ifndef PLAY_H
#define PLAY_H
#include "subprocess.hpp"

using namespace std;
using namespace subprocess;

#define MS 1000

typedef enum
{
	PLAY_STATUS_PLAY = 0x1,
	PLAY_STATUS_PAUSE,
	PLAY_STATUS_STOP,
	PLAY_STATUS_RESERV,
}PLAY_STATUS_S;

class SoundPlay
{
public:
	SoundPlay(void);
	~SoundPlay(void);


	int playmusic(const char *musicname);

	int sendMsg(const char *msg);
	int pausemusic();
	int stopmusic();


private:
	PLAY_STATUS_S play_state;
	int beginplay(char *path);
        auto p;

};


#endif
