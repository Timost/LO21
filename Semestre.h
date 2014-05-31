#ifndef SEMESTRE_H
#define SEMESTRE_H

#include "enums.h"

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

class Semestre {
    Saison saison;
    unsigned int annee;
public:
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw SemestreException("annee non valide"); }
    Saison getSaison() const { return saison; }
    unsigned int getAnnee() const { return annee; }
};

inline bool operator==(Semestre s1, Semestre s2)
{
    return ((s1.getSaison()==s2.getSaison())&&(s1.getAnnee()==s2.getAnnee()));
}


inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }


#endif // SEMESTRE_H
