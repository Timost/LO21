/**
\file Categorie.h
\version 1
\brief Ce fichier est le header de la classe Catégorie.
**/
#ifndef CATEGORIE_H
#define CATEGORIE_H
#include <QString>
#include <QTextStream>
#include "EntityStd.h"
#include <string>

/**
 * @brief CategorieException class permet de récupérerles exceptions sur Catégorie.
 */
class CategorieException : public std::exception
{
protected :
    std::string info;
public:
    /**
     * @brief CategorieException récupère les info sur l'exception.
     * @param i
     */
    CategorieException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~CategorieException()throw() {}
};

/**
 * @brief Categorie class permet de définir les différentes catégories d'une UV tel que CS, TM, SP, TSH.
 */
class Categorie : public EntityStd
{
private :
    /**
     * @brief code est le code de la catégorie.
     */
    QString code;
    /**
     * @brief description est la description de la catégorie
     */
    QString description;
    /**
     * @brief sousCategorie si l'uv à des sous catégorie on les mets dans ce vecteur.
     */
    std::vector<Categorie> sousCategorie;
    /**
     * @brief Categorie le constructeur vide est privé.
     */
    Categorie(){}
public :
    /**
     * @brief getStrLabel fonction défini dans EntityStd. Elle permet de récupérer l'entité principale de la classe.
     * @return Code de la Categorie (std::string)
     */
    std::string getStrLabel() const
    {
        return code.toStdString();
    }
    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     * @param sc sous categorie
     */
    Categorie(std::string c,std::string d,std::vector<Categorie>sc);

    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     * @param sc sous categorie std::vector<Categorie>
     */
    Categorie(QString c,QString d,std::vector<Categorie>sc);

    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     * @param sc sous categorie
     */
    Categorie(const char* c,const char* d,std::vector<Categorie>sc);

    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     */
    Categorie(std::string c,std::string d);

    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     */
    Categorie(QString c,QString d);

    /**
     * @brief Categorie constructeur de Categorie
     * @param c code
     * @param d description
     */
    Categorie(const char* c, const char*d);

    /**
     * @brief getCode getter sur le code
     * @return code
     */
    QString getCode() const {return code;}

    /**
     * @brief getCodeStdString getter sur le code
     * @return code
     */
    std::string getCodeStdString() const {return code.toStdString();}

    /**
     * @brief getDescription getter sur la description
     * @return description
     */
    QString getDescription() const {return description;}

    /**
     * @brief getDescriptionStdString getter sur description
     * @return description
     */
    std::string getDescriptionStdString() const {return description.toStdString();}

    /**
     * @brief setDescription permet de changer la description.
     * @param d description
     */
    void setDescription(QString d){description = d;}
    /**
     * @brief setDescription permet de changer la descirption.
     * @param d description
     */
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}

    /**
     * @brief setDescription permet de changer la descirption.
     * @param d description
     */
    void setDescription(const char* d){setDescription(std::string(d));}

    /**
     * @brief setSousCategorie permet de mettre un ensemble de sous catégorie.
     * @param sc sous categorie
     */
    void setSousCategorie(std::vector<Categorie> sc){sousCategorie=sc;}

    /**
     * @brief addSousCategorie permet de rajouter une sous Catégorie.
     * @param c Categorie à ajouter
     */
    void addSousCategorie(Categorie c);
    void removeSousCategorie(Categorie c);

    /**
     * @brief hasSousCategorie permet de vérifier si c est une sous catégorie de la catégorie courante.
     * @param c Categorie à vérifier
     * @return booléen vrai si c est une  sous Categorie.
     */
    bool hasSousCategorie(Categorie c);

    /**
     * @brief hasSousCategorie permet de regarder si la catégorie courante possède des sous catégorie.
     * @return booléen vrai si la Categorie possède des sous categorie.
     */
    bool hasSousCategorie(){return(sousCategorie.size()>0);}

    /**
     * @brief getSousCategorie permet de récupérer l'ensemple des sous catégorie.
     * @return sousCategorie
     */
    std::vector<Categorie> getSousCategorie()const {return sousCategorie;}
};

/**
 * @brief getFullSousCat permet de récupérer l'ensemple des sous catégorie de c.
 * @param c QString associer à un code de Categorie
 * @return sousCategorie de la categorie associer à c
 */
std::vector<Categorie> getFullSousCat(QString c);

/**
 * @brief getCatsWithSousCat permet de récupérer un map de catégorie et de leur sous catégorie.
 * @return ensemble des categories et leurs sous categories.
 */
std::map<Categorie,std::vector<Categorie> > getCatsWithSousCat();
std::vector<Categorie> getFullSousCat(QString c);//retourne toutes les sous catégories d'une catégorie dans une représentation à plat
std::map<Categorie,std::vector<Categorie> > getCatsWithSousCat();//retourne un map des catégories possedant des sous catégories (retourne tous les niveaux de sous catégories)
std::vector<Categorie> getCatsWithoutSousCat();//retourne un vector contenant les catégories sans sous catégories
QString getParentCat(QString c);//retourne le code de la catégorie parente d'une catégorie, "" si pas de parent
std::vector<Categorie> getOriginCat();//retourne l'ensemble des catégories n'ayant pas de parents

/**
 * @brief operator < de comparaison sur deux catégories. Compare les codes.
 * @param c1
 * @param c2
 * @return
 */
bool operator<(const Categorie c1, const Categorie c2);

/**
 * @brief operator == regarder si les codes de deux catégories sont égaux.
 * @param c1
 * @param c2
 * @return
 */
bool operator==(const Categorie c1, const Categorie c2);

/**
 * @brief StringToCategorie
 * @param s
 * @return Categorie associer à la chaine de caractère.
 */
Categorie StringToCategorie(const QString& s);

#endif // CATEGORIE_H
