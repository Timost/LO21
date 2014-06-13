#ifndef CONDITIONCHECKER_H
#define CONDITIONCHECKER_H
#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QScriptValue>
#include "Condition.h"
#include <string>
#include "uv.h"
#include <vector>
class Dossier;

class ConditionCheckerException : public std::exception
{
protected :
    std::string info;
public:
    ConditionCheckerException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~ConditionCheckerException()throw() {}
};

class ConditionChecker: public QObject
{
    Q_OBJECT

private:
    QString name;
    std::vector<Condition> cond;
    QScriptEngine engine;
    Dossier& dossier;
public:
    ConditionChecker(std::vector<Condition> c,QString n,Dossier& d):name(n),cond(c),dossier(d){}

    bool evaluate();
public slots:
    /*
     *Warning !!! Les slots ne peuvent prendre en paramêtre que les types supporté par QScript : faire un maximum de conversion dans les fonctions C++(ou implémenter la conversion des customs types si besoin)
     */
    bool isUvValidated(QString u);
    unsigned int getValidatedCredits(QString c);

     //UV test(int x){qDebug()<<"##################### test "<<x<<" UV "<<QString::fromStdString( StringToUV("EE32").getCode()); return StringToUV("EE32");}

};


#endif // CONDITIONCHECKER_H
