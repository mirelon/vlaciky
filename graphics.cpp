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
	r = 70;
	alpha = 360.0/n;
	epoch = new QGraphicsTextItem("0");
	graphicsView->scene()->addItem(epoch);
	loadMap();
}

void Graphics::loadMap(){
	track = s->getString("map");
	qreal smer = 180.0;
	QPoint pos = QPoint(80,280);
	step = 35.0;
	if(track.length()<n)
		for(int i=0;i<n-track.length();i++)
			track.append('=');
	for(int i=0;i<n;i++){
		pos += QPoint(step * cos(M_PI*smer/180.0),step * sin(M_PI*smer/180.0));
		if(track[i]=='-')smer+=alpha;
		if(track[i]=='+')smer-=alpha;
		QGraphicsEllipseItem* it = new QGraphicsEllipseItem(pos.x(),pos.y(),r,r);
		it->setBrush(getBrush(0.0));
		it->setPen(QPen(Qt::NoPen));
		it->setOpacity(0.0);
		item.insert(i,it);
		graphicsView->scene()->addItem(it);
	}
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

