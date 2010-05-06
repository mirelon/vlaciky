#ifndef NODE_H
#define NODE_H

#include<QMap>

class Node
{
public:
    Node();
	void addNext(Node* n,qreal prob=0.0);
	qreal pr;
	qreal newpr;
	QMap<Node*,qreal> prev;
	QMap<Node*,qreal> next;
};

#endif // NODE_H
