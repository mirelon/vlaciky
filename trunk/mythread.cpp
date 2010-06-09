#include "mythread.h"
#include <QDebug>

bool OpacityEvent::operator <(OpacityEvent &oe){
	return priority < oe.priority;
}

MyThread::MyThread()
{
	stopped = true;
}

void MyThread::init(){
	connect(this,SIGNAL(ssetOpacity(int,int)),graphics,SLOT(setOpacity(int,int)));
	connect(this,SIGNAL(updateStatus(QString)),graphics,SLOT(updateStatus(QString)));
	epoch = 0;
	avgPriority=0;
	sumPriority=0;
}

void MyThread::run(){
	stopped = false;
	while(!stopped){
		if(!opac.empty()){
			OpacityEvent* oe = opac.top();
			//qDebug() << "top: " << oe->priority;
			sumPriority -= oe->priority;
			if(opac.size()<2)avgPriority=0;else
				avgPriority = (float)sumPriority/opac.size();
			opac.pop();
			if(lastEpoch[oe->pos]<oe->epoch){
				lastOpacity[oe->pos]=oe->value;
				lastEpoch[oe->pos]=oe->epoch;
				emit ssetOpacity(oe->pos,oe->value);
			}
			delete oe;
		}
		this->msleep(2);
	}
}

void MyThread::setOpacity(int i, int opacity){
	//ak je halda velka, tak to do nej pridam
	//len ak to ma vacsiu prioritu ako je polovica priemeru v halde
	if(abs(opacity-lastOpacity.value(i,0)) <= avgPriority/2)
		return;
	OpacityEvent* oe = new OpacityEvent();
	oe->priority = abs(opacity-lastOpacity.value(i,0));
	oe->epoch = epoch;
	oe->pos = i;
	oe->value = opacity;
	opac.push(oe);
	sumPriority += oe->priority;
	avgPriority = (float)sumPriority/opac.size();
}

void MyThread::updateEpoch(){
	qDebug() << "avg priority: " << avgPriority;
	qDebug() << "heap: " << opac.size();
	epoch++;
	emit updateStatus("Epoch: "+QString::number(epoch)+"\nAverage priority: "+QString::number(avgPriority)+"\nHeap size: "+QString::number(opac.size()));
}
