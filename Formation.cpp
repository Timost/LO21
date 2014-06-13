#include "Formation.h"
Formation::Formation(QString n,QString d,std::map<UV*,bool> uv,std::map<Categorie,unsigned int> nbCred)
{
   TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
   if(!tFormation.alreadyExist(n))
    {
        nom=n;
        description=d;
        uvs=uv;
        nbCredits=nbCred;

        tFormation.New(*this);
    }
    else
    {
        throw FormationException("Erreur : la formation "+n.toStdString()+" existe deja !");
    }
}
Formation::Formation(QString n,QString d,std::map<UV*,bool> uv,std::map<Categorie,unsigned int> nbCred,std::vector<Condition> cv)
{
    Formation(n,d,uv,nbCred).setConditions(cv);
}


int Formation::getNbCreditsTotal()const
{
    int sum=0;
    typedef std::map<Categorie, unsigned int>::const_iterator it_type;
    for(it_type iterator = nbCredits.begin(); iterator != nbCredits.end(); iterator++)
    {
        sum += iterator->second;
    }
    return sum;
}

void Formation::addUv(UV* uv, bool required)
{
      std::pair<std::map<UV*,bool>::iterator,bool> ret = uvs.insert ( std::pair<UV*,bool>(uv,required) );
      if (ret.second==false) //echec lors de l'insertion
      {
        throw FormationException("Erreur, l'Uv appartient déjà à la formation.");
      }

      if(required)//ajouter les crédits dans les crédits à valider pour chaque catégorie de l'UV si il n'y en a pas assez
      {
         std::map<Categorie, unsigned int> cat=uv->getCredits();

         typedef std::map<Categorie, unsigned int>::iterator it_type;

         for(it_type iterator = cat.begin(); iterator != cat.end(); iterator++)
         {
             if(nbCredits[iterator->first]<iterator->second)//si il n'y a pas assez de crédits obligatoires dans les catégories d'une Uv obligatoire
             {
                 nbCredits[iterator->first]=iterator->second;
             }

         }
      }
}

void Formation::setNom(QString n)
{
    TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
    if(!tFormation.alreadyExist(n))
     {
         tFormation.erase(*this);
         nom=n;
         tFormation.New(*this);
     }
     else
     {
         throw FormationException("Erreur : la formation "+n.toStdString()+" existe deja !");
     }
}


std::vector<UV*> uvNotIn(std::vector<UV*> thisVector)
{
    std::vector<UV*> res;
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();

    for(std::vector<UV>::iterator it=tUV.getIterator();it != tUV.end() ; it++)
    {
        if(std::find(thisVector.begin(),thisVector.end(),&(*it))==thisVector.end())
        {
            res.push_back(&(*it));
        }
    }

    return res;
}

bool operator==(Formation f1, Formation f2 ){return (f1.getStrLabel()==f2.getStrLabel());}
