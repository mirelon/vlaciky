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
	status = new QGraphicsTextItem("0");
	status->setPos(50,90);
	status->setScale(1.0);
	graphicsView->scene()->addItem(status);
	loadMap();
}

void Graphics::loadMap(){
	track = s->getString("map");
	alpha = 360.0/(track.count('-')-track.count('+'));
	qreal smer = 0.0;
	QPoint pos = QPoint(80,280);
	step = 3000.0/track.length();
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

QBrush Graphics::getBrush(int opacity){
	QRadialGradient radial(0.5,0.5,0.5);
	if(opacity<=160)
		radial.setColorAt(0,Qt::blue);
	else radial.setColorAt(0,QColor::fromHsl(200+opacity/5,255,80-opacity/10));
	radial.setColorAt(1,Qt::transparent);
	radial.setCoordinateMode(QGradient::ObjectBoundingMode);
	return QBrush(radial);
}

void Graphics::setOpacity(int i, int opacity){
	if(i<0 || i>=n){qDebug() << "setOpacity out of range: " << i;return;}
	item.value(i)->setOpacity(1.0-30.0/(opacity+30.0));
	return;
	if(opacity<160){
		item.value(i)->setOpacity(opacity/160.0);
	}else{
		item.value(i)->setOpacity(1.0);
	}
	item.value(i)->setBrush(getBrush(opacity));
}

void Graphics::updateStatus(QString stat){
	status->setPlainText(stat);
}

