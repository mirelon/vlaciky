#include "simulation.h"
#include<QDebug>

Simulation::Simulation()
{
	stopped=true;
}

Simulation::~Simulation(){
	delete rail;
}

void Simulation::init(){
	rail = new Rail();
	rail->s = s;
	rail->init();
	connect(this,SIGNAL(updateEpoch()),graphics,SLOT(updateEpoch()));
	connect(this,SIGNAL(setOpacity(int,qreal)),graphics,SLOT(setOpacity(int,qreal)));
}

void Simulation::run(){
	stopped=false;
	rail->audioSensor->startRecording();
		//qDebug() << rail->dump();
	while(!stopped){
		rail->updateProbabilities();
		for(int i=0;i<s->getString("map").length();i++){
			emit setOpacity(i,rail->getProb(i));
		}
		emit updateEpoch();
		this->msleep(50);
	}
	rail->audioSensor->stopRecording();
}
