#include "Semestre.h"

Semestre::Semestre(Saison s, unsigned int a):saison(s)
{
    if (a<1972||a>2099)
    {
        throw SemestreException("annee "+std::to_string(a)+" non valide");
    }

    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();

    QString test = ""+s.getNom()+QString::number(a);

   if(!tSemestre.alreadyExist(test))
    {
        code=test;
        annee=a;
        tSemestre.New(*this);
    }
    else
    {
        throw SaisonException("Erreur : le semestre "+test.toStdString()+" existe deja !");
    }

}
