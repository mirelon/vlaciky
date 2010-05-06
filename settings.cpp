#include "settings.h"
#include<QDebug>
#include<QStringList>

Settings::Settings()
{
}

void Settings::init(){
	if(!QFile::exists("settings.ini"))
		qDebug("File settings.ini does not exist.");
	QFile::copy("settings.ini","custom.ini");
}

void Settings::load(){
	if(!QFile::exists("custom.ini"))init();
	s = new QSettings("custom.ini",QSettings::IniFormat);
}

QVariant Settings::getProp(QString propName, QVariant def){
	return s->value(propName,def);
}

bool Settings::isset(QString propName){
	return s->contains(propName);
}

bool Settings::getBool(QString propName){
	return s->value(propName,false).toBool();
}

int Settings::getInt(QString propName){
	return s->value(propName,0).toInt();
}

QString Settings::getString(QString propName){
	return s->value(propName,"").toString();
}

void Settings::setProp(QString propName, QVariant value){
	s->setValue(propName,value);
}

void Settings::toggle(QString propName){
	setProp(propName,getProp(propName,"0").toInt()==0?1:0);
}

void Settings::increment(QString propName, int value){
	setProp(propName,getProp(propName,"0").toInt()+value);
}

void Settings::decrement(QString propName, int value){
	increment(propName,-value);
}
