#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QFile>

class Settings
{
public:
    Settings();
	void init();
	void load();
	QVariant getProp(QString propName,QVariant def=NULL);
	bool isset(QString propName);
	bool getBool(QString propName);
	int getInt(QString propName);
	QString getString(QString propName);
	void setProp(QString propName,QVariant value=1);
	/**
	  * toggles value of property between 0 and 1
	  *
	  */
	void toggle(QString propName);
	void increment(QString propName,int value=1);
	void decrement(QString propName,int value=1);
private:
	QSettings* s;
	QMap<QString,QVariant> prop;
};

#endif // SETTINGS_H
