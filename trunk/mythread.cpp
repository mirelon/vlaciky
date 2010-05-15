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
	connect(this,SIGNAL(ssetOpacity(int,qreal)),graphics,SLOT(setOpacity(int,qreal)));
	connect(this,SIGNAL(uupdateEpoch()),graphics,SLOT(updateEpoch()));
	epoch = 0;
	avgPriority=0;
}

void MyThread::run(){
	stopped = false;
	while(!stopped){
		if(!opac.empty()){
			OpacityEvent* oe = opac.top();
			//qDebug() << "top: " << oe->priority;
			if(opac.size()<2)avgPriority=0;else
				avgPriority = ((float)(avgPriority*opac.size()-oe->priority))/((float)(opac.size()-1));
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

void MyThread::setOpacity(int i, qreal opacity){
	//ak je halda velka, tak to do nej pridam
	//len ak to ma vacsiu prioritu ako je polovica priemeru v halde
	if(opac.size()>10 && 4.0*(opacity-lastOpacity.value(i,0))*(opacity-lastOpacity.value(i,0)) < avgPriority*avgPriority)
		return;
	OpacityEvent* oe = new OpacityEvent();
	oe->priority = opacity-lastOpacity.value(i,0);
	if(oe->priority<0)oe->priority*=-1;
	oe->epoch = epoch;
	oe->pos = i;
	oe->value = (float)opacity;
	avgPriority = ((float)((avgPriority*opac.size())+oe->priority))/((float)(opac.size()+1));
	opac.push(oe);
}

void MyThread::updateEpoch(){
	qDebug() << "avg priority: " << avgPriority;
	epoch++;
	emit uupdateEpoch();
}
