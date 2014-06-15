#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Dossier.h"
#include <QString>
#include <QDate>
#include "templatemanager.h"
/**
* @file Etudiant.h
* @version 1
* @brief Ce fichier est le header de la classe Etudiant.
**/

/**
 * @brief EtudiantException class gère les exceptions d'etudiant.
 */
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

/**
 * @brief Etudiant class permet de créer des étudiants hérite de EntityStd
 */
class Etudiant: public EntityStd
{
private :
    /**
     * @brief dos dossier associé à l'étudiant.
     */
    Dossier dos;
    /**
     * @brief ine numéro ine de l'Etudiant
     */
    unsigned int ine;
    /**
     * @brief login de l'Etudiant
     */
    QString login;
    /**
     * @brief nom de l'Etudiant
     */
    QString nom;
    /**
     * @brief prenom de l'Etudiant
     */
    QString prenom;
    /**
     * @brief dateNaissance , Date de Naissance de l'étudiant.
     */
    QDate dateNaissance;

    public :
    /**
     * @brief getStrLabel
     * @return login
     */
    std::string getStrLabel() const
    {
        return login.toStdString();
    }

    /**
     * @brief Etudiant constructeur de l'Etudiant. Le login sera généré automatiquement. L'étudiant sera automatiquement mis dans le manager.
     * @param doss
     * @param i numero ine
     * @param n nom
     * @param p prenom
     * @param d date de naissance
     */
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

    /**
     * @brief Etudiant constructeur de l'Etudiant. Le login sera vérifié. L'étudiant sera automatiquement mis dans le manager.
     * @param doss Dossier
     * @param i numero ine
     * @param n nom
     * @param p prenom
     * @param d date de naissance
     * @param log login
     */
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

    /**
     * @brief Etudiant cree un Etudiant factice avec un seul dossier nécessaire pour l'interface graphique...
     * @param dos
     */
    Etudiant(Dossier dos):dos(dos){}

    /**
     * @brief Etudiant constructeur d'un Etudiant ayant un dossier vide.  L'étudiant sera automatiquement mis dans le manager.
     * @param i numero ine
     * @param n nom
     * @param p prenom
     * @param d date de naissance
     */
    Etudiant(unsigned int i, QString n, QString p, QDate d)
    {
        Etudiant(Dossier(std::vector<Inscription>(),std::vector<Formation*>()),i,n,p,d);
    }

    /**
     * @brief getDossier getter du Dossier
     * @return
     */
    Dossier getDossier() const
    {
        return dos;
    }

    /**
     * @brief getIne getter de l'INE
     * @return
     */
    unsigned int getIne()const
    {
        return ine;
    }

    /**
     * @brief getLogin getter de login
     * @return
     */
    const QString getLogin()const
    {
        return login;
    }

    /**
     * @brief getNom getter de nom
     * @return
     */
    const QString getNom()const
    {
        return nom;
    }

    /**
     * @brief getPrenom getter de prenom
     * @return
     */
    const QString getPrenom()const
    {
        return prenom;
    }

    /**
     * @brief getDateNaissance getter de dateNaissance
     * @return
     */
    const QDate getDateNaissance()const
    {
        return dateNaissance;
    }

    /**
     * @brief setDossier setter du Dossier (pour en remplacer un autre).
     * @param d
     */
    void setDossier(Dossier d)
    {
        dos=d;
    }

    /**
     * @brief setIne setter de l'INE
     * @param i
     */
    void setIne(unsigned int i)
    {
        ine = i;
    }

    /**
     * @brief setNom setter de nom
     * @param n
     */
    void setNom(QString n)
    {
        nom = n;
    }

    /**
     * @brief setPrenom setter de prenom
     * @param pv
     */
    void setPrenom(QString p)
    {
        prenom = p;
    }

    /**
     * @brief setDateNaissance setter de dateNaissance
     * @param da
     */
    void setDateNaissance(QDate da)
    {
        dateNaissance=da;
    }
};
#endif // ETUDIANT_H
