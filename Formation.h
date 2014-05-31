#ifndef FORMATION_H
#define FORMATION_H

#include "uv.h"
#include "enums.h"
#include <map>
#include <QString>
#include "Exception.h"
#include "EntityStd.h"
#include <QDebug>

class FormationException : public std::exception
{
protected :
    std::string info;
public:
    FormationException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~FormationException()throw() {}
};


class Formation:public EntityStd
{
        QString nom;
        QString description;
        std::map<UV*,bool> uvs;//contient les Uvs Faisant partie de la formation et si elles sont obligatoires ou pas.
        //std::vector<UV*> uvsObligatoires;//contient les UVS obligatoires pour une formation donnée
        std::map<Categorie, unsigned int> nbCredits;//Contient le nombre de crédits à valider pour chaque catégories d'UVS
    public:
        //Formation(std::string n,std::string d,std::vector<UV*> uvs,std::vector<UV*> uvsO,std::map<Categorie, int> nbCred):nom(n),description(d),uvs(uvs),uvsObligatoires(uvsO),nbCredits(nbCred){}
        Formation(QString n,QString d,std::map<UV*,bool> uvs,std::map<Categorie,unsigned int> nbCred):nom(n),description(d),uvs(uvs),nbCredits(nbCred){}
        std::string getStrLabel() const
        {
           return getDescription().toStdString();
        }
        QString getNom() const
        {
            return nom;
        }
        QString getDescription()const
        {
            return description;
        }

        void setNom(QString name)
        {
            nom=name;
        }

        void setDescription(QString desc)
        {
            description=desc;
        }

        int getNbCreditsCat(const Categorie cat)
        {
            return nbCredits[cat];
        }
        int getNbCreditsTotal()const;
        void addUv(UV* uv, bool required);
        void removeUv(UV* uv)
        {
            uvs.erase(uv);
        }

        void addCategorie(Categorie c, unsigned int creds)
        {
            nbCredits[c]=creds;
        }

        void display()
        {
            qDebug()<<"Nom : "<<getNom()<<" Description :"<<getDescription()<<" Nbcredits CS :"<<getNbCreditsCat(Categorie::CS)<<" Nbcredits TM :"<<getNbCreditsCat(Categorie::TM)<<" NbcreditsTotal :"<<getNbCreditsTotal();
        }
};



#endif // FORMATION_H
