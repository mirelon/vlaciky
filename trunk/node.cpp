#include "node.h"

Node::Node(QString meno)
{
	pr = 0.0;
	newpr = 0.0;
        name = meno;
}

void Node::addNext(Node *n, qreal prob){
	next.insert(n,prob);
	n->prev.insert(this,prob);
}

QString Node::dump(){
  QString d = name + ": " + QString::number(pr);
  QMapIterator<Node*, qreal> i(next);
  while(i.hasNext()){
    i.next();
    d += "|" + i.key()->name + ": " + QString::number(i.value());
  }
  return d;
}
