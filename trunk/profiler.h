#ifndef PROFILER_H
#define PROFILER_H

#include <QDebug>
#include <QString>
#include <QMap>
#include <QTime>
#include <QDateTime>

class Profiler
{
public:
    Profiler();
	int getTime();
	void reset();
	void start(QString name);
	void stop(QString name);
	QString getStats(QString name);
	QMap<QString, qreal> totals;
	QMap<QString, int> counts;
	QMap<QString, int> timers;
};

#endif // PROFILER_H
