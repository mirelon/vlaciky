#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMap>
#include <queue>
#include "graphics.h"

class OpacityEvent{
public:
	OpacityEvent(){}
	~OpacityEvent(){}
	bool operator <(OpacityEvent &oe);
	int epoch;
	int pos;
	float value;
	float priority;
};

class MyThread : public QThread
{
	Q_OBJECT
public:
    MyThread();
	void init();
	void run();
public slots:
	void setOpacity(int i,qreal opacity);
	void updateEpoch();
signals:
	void ssetOpacity(int i,qreal opacity);
	void uupdateEpoch();
public:
	bool stopped;
	//je to opacne kvoli priorite
	//chcem skor vykreslit veci s vacsou opacitou
	std::priority_queue<OpacityEvent*> opac;
	QMap<int,int> lastEpoch;
	QMap<int,float> lastOpacity;
	float avgPriority;
	int epoch;
	Graphics* graphics;
};

#endif // MYTHREAD_H
