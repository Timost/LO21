#include "ConditionChecker.h"
#include "Dossier.h"

void Dossier::addFormation(Formation* f)//ajoute une formation
{
    if(containsFormation(f))
    {
        throw DossierException("Erreur : la formation "+f->getStrLabel()+"fait déjà partie du dossier.");
    }
    forma.push_back(f);
}

void Dossier::deleteFormation(Formation* f)//supprime la formation du dossier
{
    std::vector<Formation*>::iterator it = std::find(forma.begin(), forma.end(), f);

    if(it==forma.end())
    {
        throw DossierException("Erreur : la formation "+f->getStrLabel()+"fait pas partie du dossier.");
    }

    forma.erase(it);
}
void Dossier::deleteFormation(QString f)
{
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
    deleteFormation(&(tForm.getElement(f)));
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

std::vector<Formation*>  Dossier::getFormationsNotInDossier()
{
        std::vector<Formation*> res;
     TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();

     for(std::vector<Formation>::iterator it=tForm.getIterator();it != tForm.end() ; it++)
     {
         if(!containsFormation(&(*it)))
         {
             res.push_back(&(*it));
         }
     }

     return res;
}

std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > Dossier::getDossierCurrentStatus()
{
    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > res;

    std::map<Categorie, unsigned int> uvsCreds=getInscriptionCurrentStatus();//uvs validées

    for(std::vector<Formation*>::iterator it1=forma.begin();it1!=forma.end();it1++)
    {
        Formation* temp= *it1;
        std::map<Categorie, unsigned int> credsToGet= temp->getNbCreditsByCat();//crédits obligatoires à valider

        for(std::map<Categorie, unsigned int>::iterator it=uvsCreds.begin();it!=uvsCreds.end();it++)
        {
            //qDebug()<<"credsToGet :"<<credsToGet[it->first]<<"credsGotten :"<<it->second;
            if(credsToGet[it->first] > it->second )
            {
                res[std::pair<Formation*,Categorie>(temp,it->first)]= std::pair<unsigned int,unsigned int>(credsToGet[it->first]-it->second,0);
            }
            else
            {
                res[std::pair<Formation*,Categorie>(temp,it->first)]=std::pair<unsigned int,unsigned int>(0,it->second -credsToGet[it->first] );
            }

        }
    }

    return res;
}

unsigned int Dossier::getCreditsCategorieOneLevel(QString s)
{
    unsigned int res=0;
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    Categorie& ct=tCat.getElement(s);

    for(std::vector<Inscription>::iterator it=inscri.begin();it!=inscri.end();it++)
    {
        std::map<Categorie, unsigned int> uvCreditCat = it->getUV().getCredits() ;
        std::map<Categorie, unsigned int>::iterator it2;
        for(it2=uvCreditCat.begin(); it2!=uvCreditCat.end();it2++ )
        {
            if(it2->first.getCode()==ct.getCode())
            {
                res = it2->second;
            }
        }
        if(it2==uvCreditCat.end())
        {
            throw DossierException("Erreur getValidatedCredits, cette aucune inscription ne contient la catégorie : "+ct.getCode().toStdString());
        }
    }
    return res;
}
unsigned int Dossier::getValidatedCredits(QString c)//retourne le nombre de crédits validé pour un catégorie et toutes ces sous catégories
{
    unsigned int res=0;
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    Categorie& ct=tCat.getElement(c);

    if(!ct.hasSousCategorie())
    {
        return getCreditsCategorieOneLevel(ct.getCode());
    }
    else
    {
        std::vector<Categorie> souscat=getFullSousCat(ct.getCode());

        for(std::vector<Categorie>::iterator it=souscat.begin();it!=souscat.end();it++)
        {
            res+=getCreditsCategorieOneLevel(it->getCode());
        }

        res+=getCreditsCategorieOneLevel(ct.getCode());
        return res;
    }
}

std::vector<Inscription>::iterator Dossier::findUVInscription(UV u,std::vector<Inscription>::iterator begin, std::vector<Inscription>::iterator end)
{
     return find_if(begin,end, [u] (const Inscription& i) { return i.getUV() == u; });
}
std::vector<Inscription>::iterator Dossier::findUVInscription(UV u)
{
    typedef std::vector<Inscription>::iterator myIT;
    myIT begin = inscri.begin();
    myIT end = inscri.end();
    myIT res = findUVInscription(u,begin,end);
    if(res==end)
    {
        throw DossierException("Erreur findUVInscription : cette UV n'est pas dans les inscriptions");
    }
    else
    {
        return res;
    }
}


bool Dossier::isUvValidated(UV u)
{
    typedef std::vector<Inscription>::iterator myIT;
    myIT begin = inscri.begin();
    myIT end = inscri.end();
    myIT res = findUVInscription(u,begin,end);
    if(res==end)
    {
        qDebug()<<"echec isUvValidated";
        return false;
    }
    else
    {
        qDebug()<<"succes isUvValidated :"<<res->getCode();
        return res->validee();
    }
}

bool Dossier::conditionsChecked(std::vector<Condition> c)
{
    return ConditionChecker( c,"cc",*this).evaluate();
}


