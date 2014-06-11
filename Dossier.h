#ifndef DOSSIER_H
#define DOSSIER_H

#include "Formation.h"
#include "Inscription.h"
#include <algorithm>
#include "ConditionChecker.h"
#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QScriptValue>
#include "Condition.h"
#include <string>

class DossierException : public std::exception
{
protected :
    std::string info;
public:
    DossierException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~DossierException()throw() {}
};

class Dossier {
private:
    std::vector<Formation*> forma;
    std::vector<Inscription> inscri;
    std::vector<Inscription>::iterator findUVInscription(UV u,std::vector<Inscription>::iterator begin, std::vector<Inscription>::iterator end);
    unsigned int getCreditsCategorieOneLevel(QString s);
public:
    Dossier(std::vector<Inscription> i,std::vector<Formation*> f):forma(f),inscri(i){}
    Dossier(){}

    bool conditionsChecked(std::vector<Condition> c);

    bool containsFormation(Formation* f)
    {
        return (std::find(forma.begin(), forma.end(), f)!=forma.end());
    }
    void addFormation(Formation* f);//ajoute une formation
    void deleteFormation(Formation* f);//supprime la formation du dossier
    void deleteFormation(QString f);//supprime la formation du dossier
    std::vector<Formation*> getFormation() const
    {
        return forma;
    }

    bool containsInscription(Inscription i)
    {
        return ((find_if(inscri.begin(),inscri.end(), [i] (const Inscription& i2) { return ((i==i2)||((i.getUV() == i2.getUV())&&(i.getResultat().isValidatory()==i2.getResultat().isValidatory()))); }))!=inscri.end());
    }

    std::vector<Inscription>::iterator findUVInscription(UV u);

    bool isUvValidated(UV u);
    void addInscription(Inscription f);//ajoute une inscription au dossier
    void deleteInscription(Inscription f);//supprime une inscription du dossier
    const std::vector<Inscription> getInscription() const{return inscri;}
    std::vector<Formation*> getFormationsNotInDossier();
    unsigned int getValidatedCredits(QString c);//retourne le nombre de crédits validés pour une catégorie donnée

    std::map<Categorie, unsigned int> getInscriptionCurrentStatus();//retourne le nombre de crédits validés par l'étudiant dans chaque catégorie.
    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > getDossierCurrentStatus();//retourne le nombre de crédits restant à valider par l'étudiant dans chaque catégorie pour chaque formation. le premier entier est pour les crédits restant à valider le deuxième pour les crédits en trop
};




#endif // DOSSIER_H
