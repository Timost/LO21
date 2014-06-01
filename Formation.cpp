#include "Formation.h"

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

