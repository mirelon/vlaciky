#include "audioinfo.h"
#include <cmath>
#include <cstdlib>

AudioInfo::AudioInfo(QAudioInput* device)
	:QIODevice()
{
	input = device;

	m_maxValue = 0;
}

AudioInfo::~AudioInfo()
{
}

void AudioInfo::start()
{
	open(QIODevice::WriteOnly);
}

void AudioInfo::stop()
{
	close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
	Q_UNUSED(data)
	Q_UNUSED(maxlen)

	return 0;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
	int samples = len/2; // 2 bytes per sample
	int maxAmp = 32768; // max for S16 samples
	bool clipping = false;

	m_maxValue = 0;

	qint16* s = (qint16*)data;

	// sample format is S16LE, only!

	for(int i=0;i<samples;i++) {
		qint16 sample = *s;
		s++;
		if(abs(sample) > m_maxValue) m_maxValue = abs(sample);
	}
	// check for clipping
	if(m_maxValue>=(maxAmp-1)) clipping = true;

	float value = ((float)m_maxValue/(float)maxAmp);
	if(clipping) m_maxValue = 100.0;
	else m_maxValue = value*100.0;

	emit update();

	return len;
}

qreal AudioInfo::LinearMax()
{
	return m_maxValue;
}
