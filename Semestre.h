#ifndef SEMESTRE_H
#define SEMESTRE_H

#include "Saison.h"

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

class Semestre : public EntityStd
{
    QString code;
    Saison saison;
    unsigned int annee;
public:
    std::string getStrLabel() const
    {
        return code.toStdString();
    }
    Semestre(Saison s, unsigned int a);
    Saison getSaison() const { return saison; }
    QString getCode() const { return code; }
    unsigned int getAnnee() const { return annee; }
};


inline bool operator==(Semestre s1, Semestre s2)
{
    return ((s1.getSaison()==s2.getSaison())&&(s1.getAnnee()==s2.getAnnee()));
}


inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison().getNom()<<s.getAnnee()%100; }


#endif // SEMESTRE_H
