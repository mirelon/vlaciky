#ifndef AUDIOSENSOR_H
#define AUDIOSENSOR_H

#include<QAudioInput>
#include<QFile>
#include "sensor.h"
#include "audioinfo.h"
#include "settings.h"

class AudioSensor : public Sensor
{
	Q_OBJECT
public:
	AudioSensor(qreal sp=0.5);
	void startRecording();
	void stopRecording();
	bool check();
public slots:
	int readAudio();
public:
	bool moved;
	QAudioInput* audioInput;
	QIODevice* input;
	QFile outputFile;
	QAudioFormat format;
	AudioInfo* audioInfo;
	char* buffer;
	Settings* s;
	qreal volume;
};

#endif // AUDIOSENSOR_H
