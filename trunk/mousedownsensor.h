#ifndef MOUSEDOWNSENSOR_H
#define MOUSEDOWNSENSOR_H

#include <QCursor>
#include "mousesensor.h"

class MouseDownSensor : public MouseSensor
{
public:
    MouseDownSensor(qreal sp=0.5);
	bool check();
};

#endif // MOUSEDOWNSENSOR_H
