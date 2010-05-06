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
	R = 60;
	r = 40;
	alpha = 2.0*M_PI/n;

	for(int i=0;i<n;i++){
		int xpos = X-R*sin(i*alpha);
		int ypos = Y+R*cos(i*alpha);

		QRadialGradient radial(0.5,0.5,0.5);
		radial.setColorAt(0,Qt::blue);
		radial.setColorAt(1,Qt::transparent);
		radial.setCoordinateMode(QGradient::ObjectBoundingMode);

		QGraphicsEllipseItem* it = new QGraphicsEllipseItem(xpos,ypos,r,r);
		it->setBrush(QBrush(radial));
		it->setPen(QPen(Qt::NoPen));

		it->setOpacity(0.0);

		item.insert(i,it);
		graphicsView->scene()->addItem(it);
	}

	epoch = new QGraphicsTextItem("0");
	graphicsView->scene()->addItem(epoch);
}

void Graphics::setOpacity(int i, qreal opacity){
	if(i<0 || i>=n){qDebug("setOpacity out of range");return;}
	item.value(i)->setOpacity(opacity);
}

void Graphics::updateEpoch(){
	epoch->setPlainText(QString::number(epoch->toPlainText().toInt()+1));
}

