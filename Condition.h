#ifndef CONDITION_H
#define CONDITION_H

#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QScriptValue>

class Condition{

private:
    QString cond;
public:
    Condition(QString c):cond(c){}

    QString getCond()const{return cond;}

    void setCond(QString c){cond=c;}
};

#endif // CONDITION_H
