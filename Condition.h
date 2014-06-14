#ifndef CONDITION_H
#define CONDITION_H

#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QScriptValue>

/**
 * @brief Condition class permet de créer des conditions.
 */
class Condition{

private:
    /**
     * @brief cond nom de la condition
     */
    QString cond;
public:
    /**
     * @brief Condition
     * @param c condition
     */
    Condition(QString c):cond(c){}

    /**
     * @brief getCond getter de la condition
     * @return
     */
    QString getCond()const{return cond;}

    /**
     * @brief setCond setter de la condition
     * @param c
     */
    void setCond(QString c){cond=c;}
};

#endif // CONDITION_H
