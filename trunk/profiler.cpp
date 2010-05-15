#include "profiler.h"

Profiler::Profiler()
{
}

int Profiler::getTime(){
	return QDateTime::currentDateTime().toTime_t()*1000 + QTime::currentTime().msec();
}

void Profiler::reset(){
	counts.clear();
	timers.clear();
	totals.clear();
}

void Profiler::start(QString name){
	//QTime* t = new QTime();
	//t->start();
	//timers.insert(name,t);
	timers.insert(name,getTime());
}

void Profiler::stop(QString name){
	int time = getTime();
	if(timers.count(name)==0){
		qDebug() << name << " timer has not started";
		return;
	}
	if(timers.count(name)>1)
		qDebug() << "timer stop warning: " << name << " has multiple starts";

	counts.insert(name,counts.value(name,0) + 1);
	totals.insert(name,totals.value(name,0) + time-timers.value(name));
	//this is weird - removing the timer has influence on qrand
	//(check it by print a qrand() before and after this)
	//timers.remove(name);
}

QString Profiler::getStats(QString name){
	return name + ": count=" + QString::number(counts.value(name)) +
			", total=" + QString::number(totals.value(name)) +
			", avg=" + QString::number(totals.value(name) / counts.value(name));
}
