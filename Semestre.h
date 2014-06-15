#ifndef SEMESTRE_H
#define SEMESTRE_H

#include "Saison.h"
/**
* @file Semestre.h
* @version 1
* @brief Ce fichier est le header de la classe semestre.
**/

/**
 * @brief SemestreException class gere les exceptions de semestre.
 */
class SemestreException : public std::exception
{
protected :
    std::string info;
public:
    SemestreException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~SemestreException()throw() {}
};

/**
 * @brief Semestre class hérite de EntityStd
 */
class Semestre : public EntityStd
{
    /**
     * @brief code
     */
    QString code;
    /**
     * @brief saison
     */
    Saison saison;
    /**
     * @brief annee
     */
    unsigned int annee;
public:

    /**
     * @brief getStrLabel
     * @return retourne le code
     */
    std::string getStrLabel() const
    {
        return code.toStdString();
    }

    /**
     * @brief Semestre
     * @param s saison
     * @param a annee
     */
    Semestre(Saison s, unsigned int a);

    /**
     * @brief getSaison getter de saison
     * @return
     */
    Saison getSaison() const { return saison; }

    /**
     * @brief getCode getter de code
     * @return
     */
    QString getCode() const { return code; }

    /**
     * @brief getAnnee getter de année
     * @return
     */
    unsigned int getAnnee() const { return annee; }
};

/**
 * @brief operator ==
 * @param s1
 * @param s2
 * @return
 */
inline bool operator==(Semestre s1, Semestre s2)
{
    return ((s1.getSaison()==s2.getSaison())&&(s1.getAnnee()==s2.getAnnee()));
}

/**
 * @brief operator <<
 * @param f
 * @param s
 * @return
 */
inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison().getNom()<<s.getAnnee()%100; }


#endif // SEMESTRE_H
