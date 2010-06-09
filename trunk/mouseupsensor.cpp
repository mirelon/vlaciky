#include "mouseupsensor.h"

MouseUpSensor::MouseUpSensor(qreal sp)
{
	spolahlivost = sp;
}

bool MouseUpSensor::check(){
	if(QCursor::pos().y()<300){
		moved=true;
		QCursor::setPos(400,300);
	}
	if(moved){
		moved = false;
		return true;
	}
	return false;
}
