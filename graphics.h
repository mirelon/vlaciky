#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<QThread>
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsEllipseItem>
#include<QPoint>
#include<QColor>
#include "settings.h"

class Graphics : public QObject
{
	Q_OBJECT
public:
    Graphics();
	void init();
	void loadMap();
	QBrush getBrush(int opacity);
public slots:
	void setOpacity(int i,int opacity);
	void updateEpoch();
public:
	QGraphicsView* graphicsView;
	QMap<int,QGraphicsEllipseItem*> item;
	QGraphicsTextItem* epoch;
	Settings* s;
	int r,n;
	qreal alpha,step;
	QString track;
};

#endif // GRAPHICS_H
