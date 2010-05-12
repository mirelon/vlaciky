#include "graphics.h"
#include<QDebug>
#include<cmath>
#include<QRadialGradient>

Graphics::Graphics()
{
}

void Graphics::init(){
	QGraphicsScene* scene = new QGraphicsScene();
	graphicsView->setScene(scene);

	X = 80;
	Y = 80;
	R = 200;
	r = 70;
	alpha = 2.0*M_PI/n;

	for(int i=0;i<n;i++){
		int xpos = X-R*sin(i*alpha);
		int ypos = Y+R*cos(i*alpha);

		QGraphicsEllipseItem* it = new QGraphicsEllipseItem(xpos,ypos,r,r);
		it->setBrush(getBrush(0.0));
		it->setPen(QPen(Qt::NoPen));

		it->setOpacity(0.0);

		item.insert(i,it);
		graphicsView->scene()->addItem(it);
	}

	epoch = new QGraphicsTextItem("0");
	graphicsView->scene()->addItem(epoch);
}

QBrush Graphics::getBrush(qreal opacity){
	QRadialGradient radial(0.5,0.5,0.5);
	if(opacity<=0.2)
		radial.setColorAt(0,Qt::blue);
	else radial.setColorAt(0,QColor::fromHsl(200+200*opacity,255,80*(1.0-opacity)));
	radial.setColorAt(1,Qt::transparent);
	radial.setCoordinateMode(QGradient::ObjectBoundingMode);
	return QBrush(radial);
}

void Graphics::setOpacity(int i, qreal opacity){
	if(i<0 || i>=n){qDebug("setOpacity out of range");return;}
	if(opacity<0.2){
		item.value(i)->setOpacity(opacity*5);
	}else{
		item.value(i)->setOpacity(1.0);
	}
	item.value(i)->setBrush(getBrush(opacity));
}

void Graphics::updateEpoch(){
	epoch->setPlainText(QString::number(epoch->toPlainText().toInt()+1));
}

