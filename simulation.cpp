#include "simulation.h"
#include "profiler.h"
#include<QDebug>

Simulation::Simulation()
{
	stopped=true;
	myThread = new MyThread();
}

Simulation::~Simulation(){
	delete rail;
}

void Simulation::init(){
	rail = new Rail();
	rail->s = s;
	rail->init();
	qDebug() << "myThread init";
	myThread->init();
	qDebug() << "myThread init ok";
	connect(this,SIGNAL(updateEpoch()),myThread,SLOT(updateEpoch()));
	connect(this,SIGNAL(setOpacity(int,int)),myThread,SLOT(setOpacity(int,int)));
}

void Simulation::run(){
	qDebug() << "simulation run";
	myThread->start();
	stopped=false;
	Profiler profiler;
	if(s->getInt("audio_sensor")>=0){
		rail->audioSensor->startRecording();
		rail->audioThread->start();
	}
	while(!stopped){
		profiler.start("round");
		profiler.start("update probabilities");
		rail->updateProbabilities();
		profiler.stop("update probabilities");
		profiler.start("emitting");
		for(int i=0;i<s->getString("map").length();i++){
			emit setOpacity(i,(int)(800*rail->getProb(i)));
		}
		emit updateEpoch();
		profiler.stop("emitting");
		this->msleep(100);
		profiler.stop("round");
	}
	qDebug() << "simulation stop";
	if(s->getInt("audio_sensor")>=0){
		rail->audioThread->stopped = true;
		this->msleep(50);
		rail->audioSensor->stopRecording();
	}
	myThread->stopped = true;
	qDebug() << profiler.getStats("round");
	qDebug() << profiler.getStats("update probabilities");
	qDebug() << profiler.getStats("emitting");
}
