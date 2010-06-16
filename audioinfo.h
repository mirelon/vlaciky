#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include<QAudioInput>

class AudioInfo : public QIODevice
{
	Q_OBJECT
public:
	AudioInfo(QAudioInput* device);
	~AudioInfo();

	void start();
	void stop();

	qreal LinearMax();

	qint64 readData(char *data, qint64 maxlen);
	qint64 writeData(const char *data, qint64 len);

	QAudioInput* input;

private:
	qreal m_maxValue;

signals:
	void update();
};

#endif // AUDIOINFO_H
