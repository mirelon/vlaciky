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
	epoch = new QGraphicsTextItem("0");
	epoch->setPos(75,80);
	epoch->setScale(2.0);
	graphicsView->scene()->addItem(epoch);
	loadMap();
}

void Graphics::loadMap(){
	track = s->getString("map");
	alpha = 360.0/(track.count('-')-track.count('+'));
	qreal smer = 180.0;
	QPoint pos = QPoint(80,280);
	step = 1000.0/track.length();
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
	if(opacity<160){
		item.value(i)->setOpacity(opacity/160.0);
	}else{
		item.value(i)->setOpacity(1.0);
	}
	item.value(i)->setBrush(getBrush(opacity));
}

void Graphics::updateEpoch(){
	epoch->setPlainText(QString::number(epoch->toPlainText().toInt()+1));
}

