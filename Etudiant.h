#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Dossier.h"
#include <QString>
#include <QDate>
#include "templatemanager.h"
class EtudiantException : public std::exception
{
protected :
    std::string info;
public:
    EtudiantException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~EtudiantException()throw() {}
};

class Etudiant: public EntityStd
{
private :
    Dossier dos;
    unsigned int ine;
    QString login;
    QString nom;
    QString prenom;
    QDate dateNaissance;

    public :
    std::string getStrLabel() const
    {
        return login.toStdString();
    }

    Etudiant(Dossier doss, unsigned int i, QString n, QString p, QDate d):dos(doss),ine(i),nom(n),prenom(p),dateNaissance(d)
    {
        if(nom.length()>=7)
        {
          login=prenom;
          login.insert(1, nom);
          login.resize(8);
        }
        else
        {
          login=nom;
          login.insert(nom.length(), prenom);
          login.resize(8);
        }
        int t=0;
        try {
            while(TemplateManager<Etudiant>::getInstance().alreadyExist(login.toStdString()))
            {
                login.resize(8);
                login+=QString::number(t);
                t++;
            }
            login=login.toLower();
            TemplateManager<Etudiant>::getInstance().New(*this);
        }
        catch(TemplateManagerException<Etudiant>& e)
        {
            qDebug()<<e.what()<<"\n";
        }
    }

    Etudiant(Dossier doss, unsigned int i, QString n, QString p, QDate d,  QString log):dos(doss),ine(i),nom(n),prenom(p),dateNaissance(d)
    {
        QString test;
        if(nom.length()>=7)
        {
          test=prenom;
          test.insert(1, nom);
          test.resize(8);
        }
        else
        {
          test=nom;
          test.insert(nom.length(), prenom);
          test.resize(8);
        }
        try
        {
            if(test!=log.left(8) || TemplateManager<Etudiant>::getInstance().alreadyExist(log.toStdString()))
            {
                throw EtudiantException("Login non valide.");
            }
            else
            {
                login=log;
                TemplateManager<Etudiant>::getInstance().New(*this);
            }
        }
        catch(TemplateManagerException<Etudiant>& e)
        {
            qDebug()<<e.what()<<"\n";
        }
    }

    Etudiant(unsigned int i, QString n, QString p, QDate d)
    {
        Etudiant(Dossier(std::vector<Inscription>(),std::vector<Formation*>()),i,n,p,d);
    }
    Dossier getDossier() const
    {
        return dos;
    }

    unsigned int getIne()const
    {
        return ine;
    }

    const QString getLogin()const
    {
        return login;
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
        prenom = p;
    }
    void setDateNaissance(QDate da)
    {
        dateNaissance=da;
    }
};
#endif // ETUDIANT_H
