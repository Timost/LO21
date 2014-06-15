#ifndef SAISON_H
#define SAISON_H

#include <QString>
#include "EntityStd.h"
#include "templatemanager.h"

/**
* @file Saison.h
* @version 1
* @brief Ce fichier est le header de la classe saison.
**/

/**
 * @brief SaisonException class gère les exceptions sur Saison
 */
class SaisonException : public std::exception
{
protected :
    std::string info;
public:
    SaisonException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~SaisonException()throw() {}
};

/**
 * @brief Saison class gère les saisons hérite de EntityStd
 */
class Saison : public EntityStd
{
private:
    /**
     * @brief nom
     */
    QString nom;

    /**
     * @brief description
     */
    QString description;

public:
    /**
     * @brief getStrLabel
     * @return retourne le nom
     */
    std::string getStrLabel() const
    {
        return nom.toStdString();
    }

    /**
     * @brief Saison
     * @param n nom
     * @param d descritption
     */
    Saison(std::string n,std::string d);

    /**
     * @brief Saison
     * @param n nom
     * @param d descritption
     */
    Saison(QString n,QString d);

    /**
     * @brief Saison
     * @param n nom
     * @param d descritption
     */
    Saison(const char* n, const char*d);

    /**
     * @brief getNom getter du nom
     * @return
     */
    QString getNom() const {return nom;}

    /**
     * @brief getNom getter du nom
     * @return
     */
    std::string getNomStdString() const {return nom.toStdString();}

    /**
     * @brief getDescription getter de la description
     * @return
     */
    QString getDescription() const {return description;}

    /**
     * @brief getDescriptionStdString getter de la description
     * @return
     */
    std::string getDescriptionStdString() const {return description.toStdString();}

    /**
     * @brief setNom setter du nom
     * @param n nom
     */
    void setNom(QString n){nom = n;}

    /**
     * @brief setNom setter du nom
     * @param n nom
     */
    void setNom(std::string n){setNom(QString::fromStdString(n));}

    /**
     * @brief setNom setter du nom
     * @param n nom
     */
    void setNom(const char* n){setNom(std::string(n));}

    /**
     * @brief setDescription setter de description
     * @param d
     */
    void setDescription(QString d){description = d;}

    /**
     * @brief setDescription setter de description
     * @param d
     */
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}

    /**
     * @brief setDescription setter de description
     * @param d
     */
    void setDescription(const char* d){setDescription(std::string(d));}
};

/**
 * @brief operator ==
 * @param s1
 * @param s2
 * @return
 */
bool operator ==(Saison s1,Saison s2);

/**
 * @brief StringToSaison
 * @param s
 * @return transforme une chaine de caractères en Saison
 */
Saison StringToSaison(const QString& s);

#endif // SAISON_H
