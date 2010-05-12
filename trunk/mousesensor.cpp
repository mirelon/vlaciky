#include <QCursor>
#include "mousesensor.h"

MouseSensor::MouseSensor(qreal sp){
	spolahlivost = sp;
}

bool MouseSensor::check(){
	if(QCursor::pos().y()!=300){
		moved=true;
		QCursor::setPos(400,300);
	}
	if(moved){
		moved = false;
		return true;
	}
	return false;
}
