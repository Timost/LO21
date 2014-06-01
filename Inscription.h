#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "enums.h"
#include "Semestre.h"
#include "uv.h"

class Inscription
{
    const UV* uv;
    Semestre semestre;
    Note resultat;
public:
    Inscription(const UV& u, const Semestre& s, Note res=Note::EC):uv(&u),semestre(s),resultat(res){}
    UV getUV() const { return *uv; }
    std::string getCode() const { return uv->getCode();}
    Semestre getSemestre() const { return semestre; }
    Note getResultat() const { return resultat; }
    void setResultat(Note newres) { resultat=newres; }

    bool validee()//retourne vrai si une inscription a été validée
    {
        return ((resultat>= Note::A)&&(resultat<=Note::E));
    }

    void display()
    {
        qDebug()<<"UV : "<<uv->getCode().c_str() <<" Semestre :"<<semestre.getSaison()<<semestre.getAnnee();//<<" Resultat : "<<getResultat();
    }
};
inline bool operator==(Inscription i1, Inscription i2)
{
    return ((i1.getUV()==i2.getUV())&&(i1.getSemestre()==i2.getSemestre())&&(i1.getResultat()==i2.getResultat()));
}

#endif // INSCRIPTION_H
