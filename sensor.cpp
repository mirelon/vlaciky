#include "sensor.h"

Sensor::Sensor(qreal sp)
{
	spolahlivost = sp;
}

bool Sensor::check(){
	return (qrand()%10==0);
}
