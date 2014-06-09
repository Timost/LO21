#ifndef CATEGORIE_H
#define CATEGORIE_H
#include <QString>
#include <QTextStream>
#include "EntityStd.h"
#include <string>

class CategorieException : public std::exception
{
protected :
    std::string info;
public:
    CategorieException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~CategorieException()throw() {}
};

class Categorie : public EntityStd
{
private :
    QString code;
    QString description;
    std::vector<Categorie> sousCategorie;
    Categorie(){}
public :
    std::string getStrLabel() const
    {
        return code.toStdString();
    }

    Categorie(std::string c,std::string d,std::vector<Categorie>sc);
    Categorie(QString c,QString d,std::vector<Categorie>sc);
    Categorie(const char* c,const char* d,std::vector<Categorie>sc);
    Categorie(std::string c,std::string d);
    Categorie(QString c,QString d);
    Categorie(const char* c, const char*d);

    QString getCode() const {return code;}
    std::string getCodeStdString() const {return code.toStdString();}

    QString getDescription() const {return description;}
    std::string getDescriptionStdString() const {return description.toStdString();}

    void setCode(QString c){code = c;}
    void setCode(std::string c){setCode(QString::fromStdString(c));}
    void setCode(const char* c){setCode(std::string(c));}

    void setDescription(QString d){description = d;}
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}
    void setDescription(const char* d){setDescription(std::string(d));}

    void setSousCategorie(std::vector<Categorie> sc){sousCategorie=sc;}
    void addSousCategorie(Categorie c);
    bool hasSousCategorie(Categorie c);
    bool hasSousCategorie(){return(sousCategorie.size()>0);}
    std::vector<Categorie> getSousCategorie()const {return sousCategorie;}
};

std::vector<Categorie> getFullSousCat(QString c);
std::map<Categorie,std::vector<Categorie> > getCatsWithSousCat();

bool operator<(const Categorie c1, const Categorie c2);
bool operator==(const Categorie c1, const Categorie c2);
Categorie StringToCategorie(const QString& s);

#endif // CATEGORIE_H
