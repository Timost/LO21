#ifndef DOSSIER_H
#define DOSSIER_H

#include "Formation.h"
#include "Inscription.h"
#include <algorithm>
#include "ConditionChecker.h"
#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QScriptValue>
#include "Condition.h"
#include <string>
/**
* @file Dossier.h
* @version 1
* @brief Ce fichier est le header de la classe Dossier.
**/

/**
 * @brief DossierException class renvoie les exceptionsde la classe Dossier
 */
class DossierException : public std::exception
{
protected :
    std::string info;
public:
    DossierException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~DossierException()throw() {}
};

/**
 * @brief Dossier class permet de récupérer et gérer les dossiers étudiants.
 */
class Dossier {
private:
    /**
     * @brief forma vecteur de pointeurs vers les différentes formation associé au dossier.
     */
    std::vector<Formation*> forma;

    /**
     * @brief inscri vecteur des différentes inscriptions associé au dossier.
     */
    std::vector<Inscription> inscri;

    /**
     * @brief findUVInscription fonction privée pour récupérer un itérateur vers une uv
     * @param u UV cherché.
     * @param begin itérateur de départ sur les incriptions
     * @param end itérateur de fin sur les incriptions
     * @return
     */
    std::vector<Inscription>::iterator findUVInscription(UV u,std::vector<Inscription>::iterator begin, std::vector<Inscription>::iterator end);

    /**
     * @brief getCreditsCategorieOneLevel
     * @param s QString associé à une catédorie
     * @return retourne le nombre de crédits  int pour une catégorie donnée sans prendre en compte ses sous catégories
     */
    unsigned int getCreditsCategorieOneLevel(QString s);
public:

    /**
     * @brief Dossier constructeur
     * @param i vecteur d'inscription
     * @param f vecteur de formation
     */
    Dossier(std::vector<Inscription> i,std::vector<Formation*> f):forma(f),inscri(i){}

    /**
     * @brief Dossier constructeur vide
     */
    Dossier(){}

    /**
     * @brief conditionsChecked verifie que les condition du vecteur soit bien rempli.
     * @param c vecteur de condition
     * @return booleen
     */
    bool conditionsChecked(std::vector<Condition> c);

    /**
     * @brief containsFormation vérifie si le dossier contien une formation particulière.
     * @param f pointeur vers Formation
     * @return booleen
     */
    bool containsFormation(Formation* f)
    {
        return (std::find(forma.begin(), forma.end(), f)!=forma.end());
    }

    /**
     * @brief addFormation ajoute une formation
     * @param f pointeur vers une Formation
     */
    void addFormation(Formation* f);

    /**
     * @brief deleteFormation supprime la formation du dossier
     * @param f pointeur vers une Formation
     */
    void deleteFormation(Formation* f);

    /**
     * @brief deleteFormation supprime la formation du dossier
     * @param f associer à la formation
     */
    void deleteFormation(QString f);

    /**
     * @brief getFormation getter des formation
     * @return ensemble des formations du dossier sous forme de vecteur de pointeur vers des formations.
     */
    std::vector<Formation*> getFormation() const
    {
        return forma;
    }

    /**
     * @brief containsInscription vérifie si un dossier possède déjà cette inscription
     * @param i
     * @return
     */
    bool containsInscription(Inscription i)
    {
        return ((find_if(inscri.begin(),inscri.end(), [i] (const Inscription& i2) { return ((i==i2)||((i.getUV() == i2.getUV())&&(i.getResultat().isValidatory()==i2.getResultat().isValidatory()))); }))!=inscri.end());
    }

    /**
     * @brief findUVInscription fonction privée pour récupérer un itérateur vers une uv
     * @param u UV cherché.
     * @return
     */
    std::vector<Inscription>::iterator findUVInscription(UV u);

    /**
     * @brief isUvValidated vérifie si l'uv est validé
     * @param u
     * @return
     */
    bool isUvValidated(UV u);
    /**
     * @brief isUvEnCours permet de savoir si une UV est en cours
     * @param u L'uv qui nous intéresse
     * @return vrai si le dossier contient une inscription dont la note n'est pas déterminante
     */
    bool isUvEnCours(UV u);

    /**
     * @brief addInscription ajoute une inscription au dossier
     * @param f
     */
    void addInscription(Inscription f);

    /**
     * @brief deleteInscription supprime une inscription du dossier
     * @param f
     */
    void deleteInscription(Inscription f);

    /**
     * @brief getInscription getter sur inscriptions.
     * @return
     */
    const std::vector<Inscription> getInscription() const{return inscri;}

    /**
     * @brief getFormationsNotInDossier recuere les formations qui ne sont pas dans le  Dossier
     * @return
     */
    std::vector<Formation*> getFormationsNotInDossier();
    /**
     * @brief getSemestreInscritpion permet de récupérer l'ensemble des inscriptions pour un semestre dinné
     * @param s Semestre pour lequel on souhaite filtrer les inscriptions
     * @return  std::vector<Inscription> contenant les inscriptions du semestre.
     */
    std::vector<Inscription> getSemestreInscritpion(Semestre s);

    /**
     * @brief getValidatedCredits
     * @param c associé à une Categorie.
     * @return le nombre de crédits validés pour une catégorie donnée
     */
    unsigned int getValidatedCredits(QString c);

    /**
     * @brief getInscriptionCurrentStatus
     * @return le nombre de crédits validés par l'étudiant dans chaque catégorie
     */
    std::map<Categorie, unsigned int> getInscriptionCurrentStatus();

    /**
     * @brief getDossierCurrentStatus
     * @return retourne le nombre de crédits restant à valider par l'étudiant dans chaque catégorie pour chaque formation. le premier entier est pour les crédits restant à valider le deuxième pour les crédits en trop.
     */
    std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > getDossierCurrentStatus();
    /**
     * @brief getNotvalidatedConditions permet de connaître les conditions qui empêche de valider une formation
     * @return std::map<Formation*,std::vector<Condition> > qui contient les conditions blocantes par formations
     */
    std::map<Formation*,std::vector<Condition> > getNotvalidatedConditions();

    /**
     * @brief isCompletelyValidated permet de savoir si un dossier à valider toutes ces formations
     * @return vrai si les formations sont validée
     */
    bool isCompletelyValidated();

    /**
     * @brief getLastSemestre permet de trouver le semestre le plus récent d'un dossier
     * @return retourne le code du semestre
     */
    QString getLastSemestre();
    QString getNextSemestre();
};
/**
 * @brief getUVgivingCredits permet de récupérer le code d'une UV qui pourrait améliorer le dossier vis-à-vis d'une catégorie
 * @param c la catégorie dans laquelle on souhaite avoir des crédits
 * @param d le dossier pour vérifier qu'on ne retourne pas une UV déjà validée
 * @return  Le code de l'UV si on en a trouvée une, La chaine vide "" sinon.
 */
QString getUVgivingCredits(Categorie c, Dossier &d);
Dossier completeDossier(Dossier& d, std::map<UV,int> preferences);



#endif // DOSSIER_H
