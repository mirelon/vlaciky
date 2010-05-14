#ifndef RAIL_H
#define RAIL_H

#include<QList>
#include<QMap>
#include<QString>
#include "node.h"
#include "sensor.h"
#include "mousesensor.h"
#include "audiosensor.h"

class Rail
{
public:
	Rail(int n,int maxSpeed,int sen);
	~Rail();
	//plus modulo n
	int plus(int a,int b);
	void checkSensors();
	void moveTrain();
	void updateProbabilities();
	qreal sumProb();
	qreal getProb(int pos);
        QString dump(bool all=false);
	QList<QMap<int,Node*> > nodes;
	QMap<Sensor*,Node*> sensors;
	AudioSensor* audioSensor;
};

#endif // RAIL_H
