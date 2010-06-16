#include "audiothread.h"

AudioThread::AudioThread()
{
}

void AudioThread::run(){
	stopped = false;
	while(!stopped){
		if(audioSensor->audioInput->bytesReady()>0 || audioSensor->audioInfo->bytesAvailable()>0)
			audioSensor->volume=audioSensor->readAudio();
		this->msleep(50);
	}
}
