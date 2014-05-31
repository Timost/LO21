#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Dossier.h"
#include <QString>
#include <QDate>

class Etudiant
{
private :
    Dossier dos;
    unsigned int ine;
    QString nom;
    QString prenom;
    QDate dateNaissance;

    public :
    Etudiant(Dossier doss, unsigned int i, QString n, QString p, QDate d):dos(doss),ine(i),nom(n),prenom(p),dateNaissance(d){}

    const Dossier getDossier() const
    {
        return dos;
    }
    const unsigned int getIne()const
    {
        return ine;
    }
    const QString getNom()const
    {
        return nom;
    }
    const QString getPrenom()const
    {
        return prenom;
    }
    const QDate getDateNaissance()const
    {
        return dateNaissance;
    }


    void setDossier(Dossier d)
    {
        dos=d;
    }

    void setIne(unsigned int i)
    {
        ine = i;
    }

    void setNom(QString n)
    {
        nom = n;
    }
    void setPrenom(QString p)
    {
        nom = p;
    }
    void setDateNaissance(QDate da)
    {
        dateNaissance=da;
    }
};
#endif // ETUDIANT_H
