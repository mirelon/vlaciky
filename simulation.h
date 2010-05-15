#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include "rail.h"
#include "settings.h"
#include "mythread.h"

class Simulation : public QThread
{
	Q_OBJECT
public:
    Simulation();
	~Simulation();
	void init();
	void run();
signals:
	void setOpacity(int i,int opacity);
	void updateEpoch();

public:
	MyThread* myThread;
	Rail* rail;
	bool stopped;
	Settings* s;
};

#endif // SIMULATION_H
