#include "mousedownsensor.h"

MouseDownSensor::MouseDownSensor(qreal sp)
{
	spolahlivost = sp;
}

bool MouseDownSensor::check(){
	if(QCursor::pos().y()>300){
		moved=true;
		QCursor::setPos(400,300);
	}
	if(moved){
		moved = false;
		return true;
	}
	return false;
}
