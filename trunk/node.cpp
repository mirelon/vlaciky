#include "node.h"

Node::Node()
{
	pr = 0.0;
	newpr = 0.0;
}

void Node::addNext(Node *n, qreal prob){
	next.insert(n,prob);
	n->prev.insert(this,prob);
}
