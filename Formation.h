#ifndef FORMATION_H
#define FORMATION_H

#include "uv.h"
#include "enums.h"
#include <map>
#include "Exception.h"
#include "EntityStd.h"

class Formation:public EntityStd
{
        std::string nom;
        std::string description;
        std::map<UV*,bool> uvs;//contient les Uvs Faisant partie de la formation et si elles sont obligatoires ou pas.
        //std::vector<UV*> uvsObligatoires;//contient les UVS obligatoires pour une formation donnée
        std::map<Categorie, unsigned int> nbCredits;//Contient le nombre de crédits à valider pour chaque catégories d'UVS
    public:
            //Formation(std::string n,std::string d,std::vector<UV*> uvs,std::vector<UV*> uvsO,std::map<Categorie, int> nbCred):nom(n),description(d),uvs(uvs),uvsObligatoires(uvsO),nbCredits(nbCred){}
            Formation(std::string n,std::string d,std::map<UV*,bool> uvs,std::map<Categorie,unsigned int> nbCred):nom(n),description(d),uvs(uvs),nbCredits(nbCred){}
            std::string getStrLabel() const
            {
               return getDescription();
            }

            std::string getNom() const
            {
                return nom;
            }
            std::string getDescription()const
            {
                return description;
            }
            int getNbCreditsCat(const Categorie cat)
            {
                return nbCredits[cat];
            }
            int getNbCreditsTotal()const;
            void addUv(UV* uv, bool required)
            {
                  std::pair<std::map<UV*,bool>::iterator,bool> ret = uvs.insert ( std::pair<UV*,bool>(uv,required) );
                  if (ret.second==false) //echec lors de l'insertion
                  {
                    throw new UException("Erreur, l'Uv appartient déjà à la formation.");
                  }
            }
            void removeUv(UV* uv)
            {
                uvs.erase(uv);
            }
};

#endif // FORMATION_H
