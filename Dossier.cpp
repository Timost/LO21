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

std::vector<Inscription> Dossier::getSemestreInscritpion(Semestre s)
{
    std::vector<Inscription> res;
    for(std::vector<Inscription>::iterator it = inscri.begin(); it!=inscri.end();it++)
    {
        if (it->getSemestre()==s)
        {
            qDebug()<<"Test getSemestreInscritpion "<<it->getSemestre().getCode()<< " s :"<< s.getCode();
            res.push_back(*it);
        }
    }
    return res;
}


void Dossier::addInscription(Inscription i)//ajoute une inscription au dossier
{
    if(containsInscription(i))
    {
        throw DossierException("Erreur : cette Inscription fait déjà partie du dossier.");
    }
    if(getSemestreInscritpion(i.getSemestre()).size()<NB_MAX_INSCR)
    {
        inscri.push_back(i);
    }
    else
    {
         throw DossierException("Erreur : Le nombre maximum d'inscription est atteint");
    }
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

std::map<Formation*,std::vector<Condition> > Dossier::getNotvalidatedConditions()
{
    bool testRes;
    std::map<Formation*,std::vector<Condition> > res;
    for(std::vector<Formation*>::iterator it=forma.begin();it!=forma.end();it++)
    {
        std::vector<Condition> condsToTest= (*it)->getConditions();
        std::vector<Condition> condsNotValidated;

        for(std::vector<Condition>::iterator it2=condsToTest.begin();it2!=condsToTest.end();it2++)
        {
            std::vector<Condition>temp;
            temp.push_back(*it2);
            testRes= ConditionChecker( temp,"cc",*this).evaluate();
            if(!testRes)
            {
                condsNotValidated.push_back(*it2);
            }
        }
        if(condsNotValidated.size()>0)
        {
            res[(*it)]=condsNotValidated;
        }
    }
    return res;
}

unsigned int Dossier::getCreditsCategorieOneLevel(QString s)//retourne le nombre de crédits pour une catégorie donnée sans prendre en compte ses sous catégories
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
//        if(it2==uvCreditCat.end())
//        {
//            throw DossierException("Erreur getCreditsCategorieOneLevel, aucune inscription ne contient la catégorie : "+ct.getCode().toStdString());
//        }
    }
    return res;
}
unsigned int Dossier::getValidatedCredits(QString c)//retourne le nombre de crédits validé pour une catégorie et toutes ces sous catégories
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
        throw DossierException("Erreur findUVInscription : cette UV n'est pas dans les inscriptions :"+u.getCode());
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
        //qDebug()<<"echec isUvValidated";
        return false;
    }
    else
    {
        //qDebug()<<"succes isUvValidated :"<<res->getCode();
        return res->validee();
    }
}
bool Dossier::isUvEnCours(UV u)
{
    typedef std::vector<Inscription>::iterator myIT;
    myIT begin = inscri.begin();
    myIT end = inscri.end();
    myIT res = findUVInscription(u,begin,end);
    if(res==end)
    {
        //qDebug()<<"echec isUvValidated";
        return false;
    }
    else
    {
        //qDebug()<<"succes isUvValidated :"<<res->getCode();
        return res->EnCours();
    }
}
bool Dossier::isCompletelyValidated()
{
     std::map< std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > profileToBeCompleted=getDossierCurrentStatus();
     typedef std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> >::iterator my_it;
     for(my_it it=profileToBeCompleted.begin();it!=profileToBeCompleted.end();it++ )
     {
         if(std::get<0>(it->second)>0)
         {
             return false;
         }
     }
    qDebug()<<"Conditions complexes non validées : "<<getNotvalidatedConditions().size();
     return  getNotvalidatedConditions().size()==0;
}

bool Dossier::conditionsChecked(std::vector<Condition> c)
{
    return ConditionChecker( c,"cc",*this).evaluate();
}

QString Dossier::getLastSemestre()
{
    TemplateManager<Saison>& tSaison=TemplateManager<Saison>::getInstance();
    QString res;
    std::vector<Inscription>::iterator it = inscri.begin();
    unsigned int year=it->getSemestre().getAnnee() ;
    QString Saison=it->getSemestre().getSaison().getNom() ;

    it++;
    for(; it!=inscri.end() ; it++)
    {
        if((it->getSemestre().getAnnee() > year)&&(tSaison.getElement(it->getSemestre().getSaison().getNom()) > tSaison.getElement(Saison)))
        {
                year=it->getSemestre().getAnnee() ;
                Saison=it->getSemestre().getSaison().getNom();
        }
    }

    res=Saison+QString::number(year);

    return res;
}

QString Dossier::getNextSemestre()
{
    TemplateManager<Saison>& tSaison=TemplateManager<Saison>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    QString currentSemestre = getLastSemestre();
    QString saison;
    QString res;
    unsigned int year;
    saison=tSemestre.getElement(currentSemestre).getSaison().getNom();
    year=tSemestre.getElement(currentSemestre).getAnnee();

    if(saison =="Automne")
    {
        saison="Printemps";

        year++;
    }
    else
    {
        saison="Automne";
    }
    try
    {
        res=tSemestre.getElement(saison+QString::number(year)).getCode();
    }
    catch(std::exception& e)
    {
        if(QString(e.what()).contains("Erreur getElement : Valeur introuvable. "))
        {
            Semestre(tSaison.getElement(saison),year);
            res=tSemestre.getElement(saison+QString::number(year)).getCode();
        }
        else
        {
            throw DossierException("Erreur getNextSemestre : "+std::string(e.what()));
        }
    }
    return res;
}

QString getUVgivingCredits(Categorie c,Dossier& d)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();

    for(std::vector<UV>::iterator it= tUV.getIterator(); it!= tUV.end();it++)
    {
        if((!d.isUvValidated(*it))&&(!d.isUvEnCours(*it)))
        {
            if(it->hasCategorie(c))
            {
                return it->getCodeQString();
            }
        }
    }
    return "";
}
Dossier completeDossier(Dossier& d, std::map<UV,int> preferences)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    Dossier res=d;

    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > profileToBeCompleted=res.getDossierCurrentStatus();
    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > ::iterator it=profileToBeCompleted.begin();
    while((it!=profileToBeCompleted.end())&&(!res.isCompletelyValidated()))
    {
        std::vector<Inscription> temp=res.getInscription();
        qDebug()<<"****** Debut Dossier ******";
        for(std::vector<Inscription>::iterator it=temp.begin();it!=temp.end();it++)
        {
            qDebug()<<"Inscription "<<it->getCode()<<" Semestre : "<<it->getSemestre().getCode();
        }

        for(std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > ::iterator it2=profileToBeCompleted.begin();it2!=profileToBeCompleted.end();it2++)
        {
            qDebug()<<"Formation : "<< std::get<0>(it2->first)->getNom()<<"Catégorie : "<< std::get<1>(it2->first).getCode()<<", crédits à valider : "<< std::get<0>(it2->second)<<" crédits supplémentaires : "<<std::get<1>(it2->second);
        }

        qDebug()<<"****** Fin Dossier ******";
        //qDebug()<<"Test";
        if(std::get<0>(it->second)>0)// si on est en manque de crédis dans cette Catégorie pour cette Formation
        {

            QString uvPossible=getUVgivingCredits(std::get<1>(it->first),res);
            if(uvPossible != "")
            {
                qDebug()<<"Test2"<<getUVgivingCredits(std::get<1>(it->first),res);
                qDebug()<<"Test2"<<tSemestre.getElement(res.getNextSemestre()).getCode();
                if(res.getSemestreInscritpion(tSemestre.getElement(res.getLastSemestre())).size() > NB_MAX_INSCR)
                {
                    Inscription temp( tUV.getElement(getUVgivingCredits(std::get<1>(it->first),res)),tSemestre.getElement(res.getNextSemestre()),tNote.getElement("A"));
                    res.addInscription(temp);
                }
                else
                {
                    Inscription temp( tUV.getElement(getUVgivingCredits(std::get<1>(it->first),res)),tSemestre.getElement(res.getLastSemestre()),tNote.getElement("B"));
                    res.addInscription(temp);
                }

                //qDebug()<<"Test3";

//               qDebug()<<"Test4";
                profileToBeCompleted= res.getDossierCurrentStatus();

                it=profileToBeCompleted.begin();
            }
            else
            {


                throw DossierException("Le dossier ne peux pas être complété. Pas d'uvs disponibles dans la catégorie : "+std::get<1>(it->first).getCodeStdString()+" Credits manquant :"+std::to_string(std::get<0>(it->second)));
            }
        }
        else
        {
            it++;
        }
    }
    if(!res.isCompletelyValidated())
    {
        std::map<Formation*,std::vector<Condition > > res333=res.getNotvalidatedConditions();
        for( std::map<Formation*,std::vector<Condition > >::iterator it=res333.begin();it!=res333.end();it++)
        {
            qDebug()<<"Test int"<<it->second.size();
            for(std::vector<Condition >::iterator it2 =it->second.begin() ; it2 != it->second.end() ; it2++ )
            {
                qDebug()<<"Formation : "<< it->first->getNom()<<"Condition Non validée: "<< it2->getCond();
            }
        }
        qDebug()<<"Test "<<res333.size();
        throw DossierException("Une ou des conditions complexes de la formation dossier ne peuvent pas être remplie.");
    }
    return res;
}
