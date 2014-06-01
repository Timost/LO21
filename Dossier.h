#ifndef DOSSIER_H
#define DOSSIER_H

#include "Formation.h"
#include "Inscription.h"
#include <algorithm>

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

class Dossier {//dossier d'un étudiant cf. etuProfiler
    std::vector<Formation*> forma;
    std::vector<Inscription> inscri;

public:
    Dossier(std::vector<Inscription> i,std::vector<Formation*> f):forma(f),inscri(i){}
    Dossier(){}
    bool containsFormation(Formation* f)
    {
        return (std::find(forma.begin(), forma.end(), f)!=forma.end());
    }
    void addFormation(Formation* f);//ajoute une formation
    void deleteFormation(Formation* f);//supprime la formation du dossier
    const std::vector<Formation*> getFormation() const
    {
        return forma;
    }

    bool containsInscription(Inscription i)
    {
        return (std::find(inscri.begin(), inscri.end(), i)!=inscri.end());
    }
    void addInscription(Inscription f);//ajoute une inscription au dossier
    void deleteInscription(Inscription f);//supprime une inscription du dossier
    const std::vector<Inscription> getInscription() const{return inscri;}


    std::map<Categorie, unsigned int> getInscriptionCurrentStatus();//retourne le nombre de crédits validés par l'étudiant dans chaque catégorie.
    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > getDossierCurrentStatus();//retourne le nombre de crédits restant à valider par l'étudiant dans chaque catégorie pour chaque formation. le premier entier est pour les crédits restant à valider le deuxième pour les crédits en trop
};
#endif // DOSSIER_H
