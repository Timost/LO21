#include "Dossier.h"

void Dossier::addFormation(Formation* f)//ajoute une formation
{
    if(containsFormation(f))
    {
        throw DossierException("Erreur : cette formation fait déjà partie du dossier.");
    }
    forma.push_back(f);
}

void Dossier::deleteFormation(Formation* f)//supprime la formation du dossier
{
    std::vector<Formation*>::iterator it = std::find(forma.begin(), forma.end(), f);

    if(it==forma.end())
    {
        throw DossierException("Erreur : cette formation ne fait pas partie du dossier.");
    }

    forma.erase(it);
}

void Dossier::addInscription(Inscription i)//ajoute une inscription au dossier
{
    if(containsInscription(i))
    {
        throw DossierException("Erreur : cette Inscription fait déjà partie du dossier.");
    }
    inscri.push_back(i);
}

void Dossier::deleteInscription(Inscription i)//supprime une inscription du dossier
{
    std::vector<Inscription>::iterator it = std::find(inscri.begin(), inscri.end(), i);

    if(it!=inscri.end())
    {
        inscri.erase(it);
    }
    else
    {
        throw DossierException("Erreur : cette inscription ne fait pas partie du dossier.");
    }

}
