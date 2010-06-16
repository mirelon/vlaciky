#include "audiosensor.h"
#include<QDebug>
#define BUFFER_SIZE 4096

AudioSensor::AudioSensor(qreal sp){
	spolahlivost = sp;
	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	qDebug() << info.supportedCodecs();
	qDebug() << info.supportedChannels();
	qDebug() << info.supportedFrequencies();
	qDebug() << info.supportedSampleSizes();
}

void AudioSensor::startRecording(){
	qDebug() << "start recording";
	format.setFrequency(11025);
	format.setChannels(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	if(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).empty())
		qWarning() << "No input device";
	QAudioDeviceInfo info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput)[0];
	if (!info.isFormatSupported(format)) {
		qWarning()<<"default format not supported try to use nearest";
		format = info.nearestFormat(format);
	}
	audioInput = new QAudioInput(format);
	audioInfo = new AudioInfo(audioInput);
	audioInfo->start();
	input = audioInput->start();
	//audioInput->start(audioInfo);
	buffer = new char[BUFFER_SIZE];
}

void AudioSensor::stopRecording(){
	audioInput->stop();
	outputFile.close();
	delete audioInput;
}

bool AudioSensor::check(){
	//qDebug() << "check audio: " << audioInfo->bytesAvailable() << audioInput->bytesReady();
	int volume=0;
	if(audioInput->bytesReady()>0)volume=readAudio();
	if(audioInfo->bytesAvailable()>0)volume=readAudio();
	qDebug() << "volume: " << volume;
	return volume>s->getInt("volume_threshold");
}

int AudioSensor::readAudio(){
	if(!audioInput)return 0;
	qint64 len = audioInput->bytesReady();
	if(len > 4096)len = 4096;
	qint64 l = input->read(buffer,len);
	if(l > 0) {
		audioInfo->write(buffer,l);
	}
	return audioInfo->LinearMax();
}
