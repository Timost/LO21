#ifndef FORMATION_H
#define FORMATION_H

#include "uv.h"
#include <map>
#include <QString>
#include "EntityStd.h"
#include <QDebug>
#include "Condition.h"

/**
* @file Formation.h
* @version 1
* @brief Ce fichier est le header de la classe Formation.
**/

/**
 * @brief FormationException class gère les exceptions de Formation
 */
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

/**
 * @brief Formation class permet de créer des Formations hérite de EntityStd
 */
class Formation:public EntityStd
{
    /**
     * @brief nom de la formation
     */
    QString nom;

    /**
     * @brief description de la formation
     */
    QString description;

    /**
     * @brief uvs contient les Uvs Faisant partie de la formation et si elles sont obligatoires ou pas. (std::map<UV*,bool>)
     */
    std::map<UV*,bool> uvs;

    /**
     * @brief nbCredits contient le nombre de crédits à valider pour chaque catégories d'UVS std::map<Categorie, unsigned int>
     */
    std::map<Categorie, unsigned int> nbCredits;

    /**
     * @brief critereValidation contient les critèrs de validation de la formation std::vector<Condition>
     */
    std::vector<Condition> critereValidation;

public:
    /**
     * @brief Formation Constructeur de formation. Met automatiquement la Formation dans son manager associé.
     * @param n nom
     * @param d Description
     * @param uv uvs
     * @param nbCred nbCredits
     */
    Formation(QString n,QString d,std::map<UV*,bool> uv,std::map<Categorie,unsigned int> nbCred);

    /**
     * @brief Formation Constructeur de formation. Met automatiquement la Formation dans son manager associé.
     * @param n nom
     * @param d Description
     * @param uv uvs
     * @param nbCred nbCredits
     * @param cv critereValidation
     */
    Formation(QString n,QString d,std::map<UV*,bool> uv,std::map<Categorie,unsigned int> nbCred,std::vector<Condition> cv);

    ~Formation()
    {
        uvs.clear();
        nbCredits.clear();
    }

    /**
     * @brief getStrLabel ici utilisera le nom
     * @return nom
     */
    std::string getStrLabel() const
    {
       return getNom().toStdString();
    }

    /**
     * @brief getNom getter sur le nom
     * @return nom
     */
    QString getNom() const
    {
        return nom;
    }

    /**
     * @brief getDescription getter sur la description
     * @return description
     */
    QString getDescription()const
    {
        return description;
    }

    /**
     * @brief getUVs getters sur uvs
     * @return uvs
     */
    std::map<UV*,bool> getUVs() const
    {
        return uvs;
    }

    /**
     * @brief setNom setter sur le nom
     * @param n
     */
    void setNom(QString n);

    /**
     * @brief setDescription setter sur la description
     * @param desc
     */
    void setDescription(QString desc)
    {
        description=desc;
    }

    /**
     * @brief setUVs setter sur uvs
     * @param uv
     */
    void setUVs(std::map<UV*,bool> uv)
    {
        uvs=uv;
    }

    /**
     * @brief setNbsCredsRequired setter sur nbCredits
     * @param nbcreds
     */
    void setNbsCredsRequired(std::map<Categorie, unsigned int> nbcreds)
    {
        nbCredits=nbcreds;
    }

    /**
     * @brief setConditions setter surcritereValidation
     * @param c
     */
    void setConditions(std::vector<Condition> c)
    {
        critereValidation=c;
    }

    /**
     * @brief addCondition ajoute un critère de validation
     * @param c
     */
    void addCondition(Condition c)
    {
        critereValidation.push_back(c);
    }

    /**
     * @brief getNbCreditsCat
     * @param cat
     * @return retourne le nombre de credits pour la Categorie cat
     */
    unsigned int getNbCreditsCat(const Categorie cat)
    {
        return nbCredits[cat];
    }

    /**
     * @brief getNbCreditsByCat
     * @returnretourne nbCredits
     */
    std::map<Categorie, unsigned int> getNbCreditsByCat() const
    {
        return nbCredits;
    }

    /**
     * @brief getConditions
     * @return retourne critèreValidation
     */
    std::vector<Condition> getConditions()const{return critereValidation;}

    /**
     * @brief getNbCreditsTotal
     * @return retourne le nombre de crédits total nécessaire pour la formation
     */
    int getNbCreditsTotal()const;

    /**
     * @brief addUv permet l'ajout d'une UV à uvs
     * @param uv
     * @param required
     */
    void addUv(UV* uv, bool required);

    /**
     * @brief removeUv permet la suppression d'une UV à uvs
     * @param uv
     */
    void removeUv(UV* uv)
    {
        uvs.erase(uv);
    }

    /**
     * @brief addCategorie permet l'ajout d'une Categorie et d'un nombre de credits à nbCredits
     * @param c
     * @param creds
     */
    void addCategorie(Categorie c, unsigned int creds)
    {
        nbCredits[c]=creds;
    }

    /**
     * @brief display affiche la formation
     */
    void display()
    {
        qDebug()<<"Nom : "<<getNom()<<" Description :"<<getDescription();//<<" Nbcredits CS :"<<getNbCreditsCat(Categorie::CS)<<" Nbcredits TM :"<<getNbCreditsCat(Categorie::TM)<<" NbcreditsTotal :"<<getNbCreditsTotal();
    }
};
/**
 * @brief uvNotIn
 * @param thisVector
 * @return retourne les uv qui ne sont pas dans thisVector
 */
std::vector<UV*> uvNotIn(std::vector<UV*> thisVector);

/**
 * @brief getCategorieOfUV
 * @param uvs
 * @return retourne pour une liste d'UV les crédits obtenues si ont les a toutes validé.
 */
std::map<Categorie, unsigned int> getCategorieOfUV(std::vector<UV*> uvs);

/**
 * @brief operator ==
 * @param f1
 * @param f2
 * @return
 */
bool operator==(Formation f1, Formation f2 );


#endif // FORMATION_H
