#ifndef SAISON_H
#define SAISON_H

#include <QString>
#include "EntityStd.h"
#include "templatemanager.h"
//enum class Saison { Automne, Printemps, first=Automne, last=Printemps };
//Saison StringToSaison(const QString& s);
//QString SaisonToString(Saison n);
//inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Saison::Automne) f<<"A"; else f<<"P"; return f;}
//inline QTextStream& operator<<(QTextStream& f, Saison& s) { if (s==Saison::Automne) f<<"A"; else f<<"P"; return f;}

//inline QDebug operator<<(QDebug f, const Saison &s) { if (s==Saison::Automne) f<<"A"; else f<<"P"; return f;}
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


class Saison : public EntityStd
{
private:
    QString nom;
    QString description;
public:
    std::string getStrLabel() const
    {
        return nom.toStdString();
    }
    Saison(std::string n,std::string d);
    Saison(QString n,QString d);
    Saison(const char* n, const char*d);

    QString getNom() const {return nom;}
    std::string getNomStdString() const {return nom.toStdString();}

    QString getDescription() const {return description;}
    std::string getDescriptionStdString() const {return description.toStdString();}

    void setNom(QString n){nom = n;}
    void setNom(std::string n){setNom(QString::fromStdString(n));}
    void setNom(const char* n){setNom(std::string(n));}

    void setDescription(QString d){description = d;}
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}
    void setDescription(const char* d){setDescription(std::string(d));}
};

bool operator ==(Saison s1,Saison s2);
Saison StringToSaison(const QString& s);

#endif // SAISON_H
