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
	int value;
	int priority;
};

class MyThread : public QThread
{
	Q_OBJECT
public:
    MyThread();
	void init();
	void run();
public slots:
	void setOpacity(int i,int opacity);
	void updateEpoch();
signals:
	void ssetOpacity(int i,int opacity);
	void uupdateEpoch();
public:
	bool stopped;
	//je to opacne kvoli priorite
	//chcem skor vykreslit veci s vacsou opacitou
	std::priority_queue<OpacityEvent*> opac;
	QMap<int,int> lastEpoch;
	QMap<int,int> lastOpacity;
	float avgPriority;
	int sumPriority;
	int epoch;
	Graphics* graphics;
};

#endif // MYTHREAD_H
