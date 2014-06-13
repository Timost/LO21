#include "ConditionChecker.h"
#include "Dossier.h"
bool ConditionChecker::evaluate()//évalue toutes les conditions du checker et retourne vrai si elles le sont toutes
{
    bool allChecked=true;
    QObject *cc = this;
    QScriptValue objectValue = engine.newQObject(cc);
    engine.globalObject().setProperty(name, objectValue);

    typedef std::vector<Condition>::iterator Cond_iter;

    for(Cond_iter it=cond.begin();it != cond.end() ;it++)
    {
        if(!engine.evaluate(it->getCond()).toBool())
        {
            allChecked=false;
            break;
        }
        if(engine.hasUncaughtException())
        {
            throw ConditionCheckerException ("Erreur ConditionChecker :"+ engine.uncaughtException().toString().toStdString());
        }
    }

    return allChecked;
}

bool ConditionChecker::isUvValidated(QString u)
{
    //qDebug()<<"#####################inside : ";//<<dossier.isUvValidated(u);

        TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
        if(tUV.alreadyExist(u.toStdString()))
        {
            return dossier.isUvValidated(StringToUV(u));
        }
        else
        {
            throw ConditionCheckerException ("Erreur ConditionChecker : l'UV "+ u.toStdString() +" n'éxiste pas");
        }

}

 unsigned int ConditionChecker::getValidatedCredits(QString c)
 {
     return dossier.getValidatedCredits(c);
 }
