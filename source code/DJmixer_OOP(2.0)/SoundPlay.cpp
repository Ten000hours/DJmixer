#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>  
#include <string>

#include "SoundPlay.h"

using namespace std;


SoundPlay::SoundPlay(void)
{
	
	p=Popen({"omxplayer","-o","local","dingdong.mp3"},output{PIPE},input{PIPE}); 
	play_state =PLAY_STATUS_PLAY;  
	usleep(400 * MS);
}


SoundPlay::~SoundPlay(void)
{
}




/* play music */
int SoundPlay::playmusic(const char *musicname)
{
	if(play_state != PLAY_STATUS_STOP)
	{
		sendMsg("q");  //stop
	}

	play_state = PLAY_STATUS_PLAY;
        p=Popen({"omxplayer","-o","local","--loop",musicname},output{PIPE},input{PIPE});
	usleep(400 * 1000);
	return 0;
}




/* stop music */
int SoundPlay::stopmusic()
{
	if(play_state != PLAY_STATUS_STOP)
	{
		play_state = PLAY_STATUS_STOP;
  		
		p.send("q", strlen("q")); 
		return 0;
	}
	return -1;
}

	int SoundPlay::sendMsg(const char *msg)
	{
		if(strcmp(msg,"q"))
		{
			if(play_state != PLAY_STATUS_STOP)
			{
				p.send("q", strlen("q"));
				play_state =PLAY_STATUS_STOP;
			}
		}
		else
		{
			if(play_state != PLAY_STATUS_STOP)
			{
				p.send(msg, strlen(msg));
			}
		}
		usleep(400 * 1000);
	}
