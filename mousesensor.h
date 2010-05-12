#ifndef MOUSESENSOR_H
#define MOUSESENSOR_H

#include "sensor.h"

class MouseSensor : public Sensor
{
public:
	MouseSensor(qreal sp=0.5);
	bool check();
	bool moved;
};

#endif // MOUSESENSOR_H
