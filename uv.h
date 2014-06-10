#ifndef UV_H
#define UV_H
#include <string>
#include <map>
#include "EntityStd.h"
#include "enums.h"
#include "Categorie.h"
#include <QTextStream>
#include <QString>
#include <QDebug>
#include "templatemanager.h"

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


class UV : public EntityStd
{
    std::string code;
    std::string titre;
    std::map<Categorie, unsigned int> credits;//voirs enums.h pour Categorie

    bool automne;
    bool printemps;

public:
    UV(std::string c, std::string t, std::map<Categorie, unsigned int> cre, bool a, bool p);
    UV(QString c, QString t, std::map<Categorie, unsigned int> cre, bool a, bool p);
    UV(const char* c,const char*t, std::map<Categorie, unsigned int> cre, bool a, bool p);
    ~UV(){credits.clear();}

    std::string getCode() const
    {
        return code;
    }



    std::string getStrLabel() const
    {
       return getCode();
    }

    std::string getTitre() const
    {
        return titre;
    }

    const std::map<Categorie, unsigned int> getCredits() const
    {
        return credits;
    }



    bool ouvertureAutomne() const
    {
        return automne;
    }

    bool ouverturePrintemps() const
    {
        return printemps;
    }

    void setCode(std::string c);
    void setTitre(std::string t)
    {
        titre=t;
    }

    void setCredits(Categorie t, unsigned int nb)
    {
        credits[t]=nb;
    }

    void setAutomne(bool b)
    {
        automne=b;
    }

    void setPrintemps(bool b)
    {
        printemps=b;
    }

    void addCategorie(Categorie c, unsigned int creds)
    {
        if(credits.find(c) != credits.end())//si la catégorie existe déjà
        {
            throw UvException("Erreur, cette catégorie existe déjà, utilisez setCredits()");
        }

        credits[c]=creds;
    }

    void display()
    {
        qDebug()<<"Code :"<<QString(getCode().c_str())<<" titre, "<<QString(getTitre().c_str());//c_str pour les types string
    }
};

inline bool operator==(UV u1, UV u2)
{
    return (u1.getCode()==u2.getCode());
}

UV StringToUV(const QString& str);
QTextStream& operator<<(QTextStream& f, const UV& uv);

#endif // UV_H
