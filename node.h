#ifndef NODE_H
#define NODE_H

#include<QMap>
#include<QString>
#include<QMapIterator>
class Node
{
public:
    Node(QString meno="Node");
	void addNext(Node* n,qreal prob=0.0);
        QString dump();
	qreal pr;
	qreal newpr;
        QString name;
	QMap<Node*,qreal> prev;
	QMap<Node*,qreal> next;
};

#endif // NODE_H
