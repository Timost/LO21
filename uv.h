#ifndef UV_H
#define UV_H
#include <string>
#include <map>
#include "EntityStd.h"
#include "Categorie.h"
#include <QTextStream>
#include <QString>
#include <QDebug>
#include "templatemanager.h"
/**
* @file uv.h
* @version 1
* @brief Ce fichier est le header de la classe uv.
**/

/**
 * @brief UvException class
 */
class UvException : public std::exception
{
protected :
    std::string info;
public:
    UvException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~UvException()throw() {}
};

/**
 * @brief UV class hérite de EntityStd
 */
class UV : public EntityStd
{
    /**
     * @brief code
     */
    std::string code;
    /**
     * @brief titre
     */
    std::string titre;

    /**
     * @brief credits
     */
    std::map<Categorie, unsigned int> credits;

    /**
     * @brief automne l'uv est ouverte en automne
     */
    bool automne;

    /**
     * @brief printemps l'uv est ouverte au printemps
     */
    bool printemps;

public:
    /**
     * @brief UV
     * @param c code
     * @param t titre
     * @param cre credits
     * @param a automne printemps
     * @param p
     */
    UV(std::string c, std::string t, std::map<Categorie, unsigned int> cre, bool a, bool p);

    /**
     * @brief UV
     * @param c code
     * @param t titre
     * @param cre credits
     * @param a automne printemps
     * @param p
     */
    UV(QString c, QString t, std::map<Categorie, unsigned int> cre, bool a, bool p);

    /**
     * @brief UV
     * @param c code
     * @param t titre
     * @param cre credits
     * @param a automne printemps
     * @param p
     */
    UV(const char* c,const char*t, std::map<Categorie, unsigned int> cre, bool a, bool p);
    ~UV(){credits.clear();}

    /**
     * @brief getCode getter de code
     * @return
     */
    std::string getCode() const
    {
        return code;
    }

    /**
     * @brief getCodeQString getter de code
     * @return
     */
    QString getCodeQString()
    {
        return QString::fromStdString(code);
    }

    /**
     * @brief getStrLabel
     * @return retourne code
     */
    std::string getStrLabel() const
    {
       return getCode();
    }

    /**
     * @brief getTitre getter de titre
     * @return
     */
    std::string getTitre() const
    {
        return titre;
    }

    /**
     * @brief getCredits getter de credits
     * @return
     */
    const std::map<Categorie, unsigned int> getCredits() const

    {
        return credits;
    }

    /**
     * @brief ouvertureAutomne verifie si l'uv est ouverte en automne
     * @return
     */
    bool ouvertureAutomne() const
    {
        return automne;
    }

    /**
     * @brief ouverturePrintemps verifie si l'uv est ouverte au printemps
     * @return
     */
    bool ouverturePrintemps() const
    {
        return printemps;
    }

    /**
     * @brief setCode setter de code
     * @param c
     */
    void setCode(std::string c);

    /**
     * @brief setTitre setter de titre
     * @param t
     */
    void setTitre(std::string t)
    {
        titre=t;
    }

    /**
     * @brief setCredits crée ou remplace un éleéments de crédits en créant ou ramplacant une categorie associe à un nombre de credits
     * @param t
     * @param nb
     */
    void setCredits(Categorie t, unsigned int nb)
    {
        credits[t]=nb;
    }

    /**
     * @brief setAutomne setter de automne
     * @param b
     */
    void setAutomne(bool b)
    {
        automne=b;
    }

    /**
     * @brief setPrintemps setter de printemps
     * @param b
     */
    void setPrintemps(bool b)
    {
        printemps=b;
    }

    /**
     * @brief addCategorie ajoute une nouvelle categrorie associé à un nombre de credits. utile si on ne souhaite pas remplacé si  cela existe déjà
     * @param c
     * @param creds
     */
    void addCategorie(Categorie c, unsigned int creds)
    {
        if(credits.find(c) != credits.end())//si la catégorie existe déjà
        {
            throw UvException("Erreur, cette catégorie existe déjà, utilisez setCredits()");
        }

        credits[c]=creds;
    }


    bool hasCategorie(Categorie c)
    {
        return(credits.find(c)!=credits.end());
    }


    /**
     * @brief display effectue un affichage
     */
    void display()
    {
        qDebug()<<"Code :"<<QString(getCode().c_str())<<" titre, "<<QString(getTitre().c_str());//c_str pour les types string
    }
};
/**
 * @brief operator ==
 * @param u1
 * @param u2
 * @return
 */
inline bool operator==(UV u1, UV u2)
{
    return (u1.getCode()==u2.getCode());
}


/**
 * @brief StringToUV retourne une uv à partir d'un string
 * @param str
 * @return
 */
UV StringToUV(const QString& str);

/**
 * @brief operator <<
 * @param f
 * @param uv
 * @return
 */
QTextStream& operator<<(QTextStream& f, const UV& uv);

#endif // UV_H
