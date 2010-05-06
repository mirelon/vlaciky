#include "rail.h"

Rail::Rail(int n,int maxSpeed,int sen)
{
	int p_change=0.2;

	//vytvorime stavy
	for(int i=0;i<n;i++){
		QMap<int,Node*> pos;
		for(int j=-maxSpeed;j<=maxSpeed;j++){
			pos[j] = new Node();
			pos[j]->pr = 1.0/(n*(maxSpeed*2+1));
		}
		nodes.push_back(pos);
	}


	//poprepajame stavy
	for(int i=0;i<n;i++){
		for(int j=-maxSpeed;j<=maxSpeed;j++){
			nodes[i][j]->addNext(nodes[plus(i,j)][j],1.0-p_change);
			if(j!=maxSpeed)
				nodes[i][j]->addNext(nodes[plus(i,j+1)][j+1],p_change/((j==-maxSpeed)?1:2));
			if(j!=-maxSpeed)
				nodes[i][j]->addNext(nodes[plus(i,j-1)][j-1],p_change/((j==maxSpeed)?1:2));
		}
	}

	//pridame senzory
	for(int i=0;i<sen;i++){
		Sensor* s = new Sensor(0.5);
		for(int j=-maxSpeed;j<=maxSpeed;j++)
			sensors.insert(s,nodes[(i*5)%n][j]);
	}
}

Rail::~Rail(){
	for(int i=0;i<nodes.size();i++)
		foreach(Node* node,nodes[i].values())
			delete node;
	foreach(Sensor* s,sensors.uniqueKeys())
		delete s;
}

int Rail::plus(int a, int b){
	return (a+b+nodes.size())%nodes.size();
}

void Rail::updateProbabilities(){
	for(int i=0;i<nodes.size();i++){
		foreach(Node* node,nodes[i].values()){
			foreach(Node* nextNode,node->next.keys()){
				nextNode->newpr += node->pr * node->next.value(nextNode) + (qrand()%20)/20000.0;
			}
		}
	}
	for(int i=0;i<nodes.size();i++){
		foreach(Node* node,nodes[i].values()){
			node->pr = node->newpr;
			node->newpr = 0.0;
		}
	}
}

qreal Rail::getProb(int pos){
	qreal sum = 0.0;
	foreach(Node* node,nodes[pos].values())
		sum += node->pr;
	return sum;
}
