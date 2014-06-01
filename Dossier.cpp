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

std::map<Categorie, unsigned int> Dossier::getInscriptionCurrentStatus()
{
    std::map<Categorie, unsigned int> res;
    std::map<Categorie, unsigned int> uvCreds;

    typedef std::vector<Inscription>::iterator iter_inscr;

    for(iter_inscr it= inscri.begin(); it!= inscri.end(); it++)
    {
        if(it->validee())
        {
        uvCreds=it->getUV().getCredits();

        typedef std::map<Categorie, unsigned int>::iterator iter_creds;

        for(iter_creds it2=uvCreds.begin();it2!=uvCreds.end();it2++)
        {
            res[it2->first]+=it2->second;
        }

        }
    }
    return res;
}

std::map<std::pair<Formation*,Categorie>, unsigned int> Dossier::getDossierCurrentStatus()
{
    std::map<std::pair<Formation*,Categorie>, unsigned int> res;

    std::map<Categorie, unsigned int> uvsCreds=getInscriptionCurrentStatus();

    for(std::vector<Formation*>::iterator it1=forma.begin();it1!=forma.end();it1++)
    {
        Formation* temp=*it1;
        std::map<Categorie, unsigned int> credsToGet= temp->getNbCreditsByCat();

        for(std::map<Categorie, unsigned int>::iterator it=uvsCreds.begin();it!=uvsCreds.end();it++)
        {
            if(credsToGet[it->first]-it->second >0)
            {
                res[std::pair<Formation*,Categorie>(temp,it->first)]= credsToGet[it->first]-it->second;
            }
            else
            {
                res[std::pair<Formation*,Categorie>(temp,it->first)]=0;
            }

        }
    }

    return res;
}







