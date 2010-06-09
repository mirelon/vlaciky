#ifndef MOUSEUPSENSOR_H
#define MOUSEUPSENSOR_H

#include <QCursor>
#include "mousesensor.h"

class MouseUpSensor : public MouseSensor
{
public:
    MouseUpSensor(qreal sp=0.5);
	bool check();
};

#endif // MOUSEUPSENSOR_H
