#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>
#include "audiosensor.h"

class AudioThread : public QThread
{
public:
    AudioThread();
	void run();

	bool stopped;
	qreal volume;
	AudioSensor* audioSensor;
};

#endif // AUDIOTHREAD_H
