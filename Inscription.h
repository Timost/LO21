#ifndef INSCRIPTION_H
#define INSCRIPTION_H
#include "Note.h"
#include "enums.h"
#include "Semestre.h"
#include "uv.h"

#define NB_MAX_INSCR 7
/**
* @file inscription.h
* @version 1
* @brief Ce fichier est le header de la classe inscription.
**/

/**
 * @brief Inscription class permet de créer des inscription
 */
class Inscription
{
    /**
     * @brief uv dans laquelle il y a eu inscription
     */
    const UV* uv;
    /**
     * @brief semestre
     */
    Semestre semestre;
    /**
     * @brief resultat
     */
    Note resultat;
public:
    /**
     * @brief Inscription constructeur
     * @param u uv
     * @param s semestre
     * @param res resultat
     */
    Inscription(const UV& u, const Semestre& s, Note res=StringToNote("EC")):uv(&u),semestre(s),resultat(res){}

    /**
     * @brief getUV getter de UV
     * @return
     */
    UV getUV() const { return *uv; }

    /**
     * @brief getCode
     * @return retourne le code de l'UV
     */
    QString getCode() const { return QString(uv->getCode().c_str());}

    /**
     * @brief getSemestre getter du semestre
     * @return
     */
    Semestre getSemestre() const { return semestre; }

    /**
     * @brief getResultat getter du resultat
     * @return
     */
    Note getResultat() const { return resultat; }

    /**
     * @brief setResultat setter du resultat
     * @param newres
     */
    void setResultat(Note newres) { resultat=newres; }

    /**
     * @brief validee
     * @return retourne true si l'uv a été validé
     */
    bool validee()//retourne vrai si une inscription a été validée
    {
        return (resultat.isValidatory());
    }

    bool EnCours()
    {
        return((!resultat.isEliminatory())&&(!resultat.isValidatory()));
    }

    /**
     * @brief display affiche l'inscription
     */
    void display()
    {
        qDebug()<<"UV : "<<uv->getCode().c_str() <<" Semestre :"<<semestre.getSaison().getNom()<<semestre.getAnnee();//<<" Resultat : "<<getResultat();
    }
};

/**
 * @brief operator ==
 * @param i1
 * @param i2
 * @return
 */
inline bool operator==(Inscription i1, Inscription i2)
{
    return ((i1.getUV()==i2.getUV())&&(i1.getSemestre()==i2.getSemestre())&&(i1.getResultat()==i2.getResultat()));
}

#endif // INSCRIPTION_H
