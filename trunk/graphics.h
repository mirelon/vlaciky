#ifndef GRAPHICS_H
#define GRAPHICS_H

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsEllipseItem>
#include<QPoint>
#include<QColor>

class Graphics : public QObject
{
	Q_OBJECT
public:
    Graphics();
	void init();
	QBrush getBrush(qreal opacity);
public slots:
	void setOpacity(int i,qreal opacity);
	void updateEpoch();
public:
	QGraphicsView* graphicsView;
	QMap<int,QGraphicsEllipseItem*> item;
	QGraphicsTextItem* epoch;
	int X,Y,R,r,n;
	qreal alpha;
};

#endif // GRAPHICS_H
