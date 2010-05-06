#ifndef RAIL_H
#define RAIL_H

#include<QList>
#include<QMap>
#include "node.h"
#include "sensor.h"

class Rail
{
public:
	Rail(int n,int maxSpeed,int sen);
	~Rail();
	//plus modulo n
	int plus(int a,int b);
	void updateProbabilities();
	qreal getProb(int pos);
	QList<QMap<int,Node*> > nodes;
	QMap<Sensor*,Node*> sensors;
};

#endif // RAIL_H
