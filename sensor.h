#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor
{
public:
	Sensor(qreal sp=0.5);
	bool check();
	qreal spolahlivost;
};

#endif // SENSOR_H