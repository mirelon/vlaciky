#ifndef SIMULATION_H
#define SIMULATION_H

#include <QThread>
#include "graphics.h"
#include "rail.h"
#include "settings.h"

class Simulation : public QThread
{
	Q_OBJECT
public:
    Simulation();
	~Simulation();
	void init();
	void run();
signals:
	void setOpacity(int i,qreal opacity);
	void updateEpoch();

public:
	Graphics* graphics;
	Rail* rail;
	bool stopped;
	Settings* s;
};

#endif // SIMULATION_H
