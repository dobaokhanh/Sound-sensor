// this file contains the main function of our project

#include "sound.h"
#include<stdlib.h>
#include<signal.h>

int main(void){
	int ret;
	while(1){	//loop forever
		//run system command "arecord" to record 1 sec of wav
		ret=system("arecord -q -r16000 -c1 -f S16_LE -d1 test.wav");
		if(WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT)) break;
		//display wav header
		dispWAVHeader("test.wav");
		//display wav strength as decibel value
		dispWAVData("test.wav");
	}
	return 0;
}
