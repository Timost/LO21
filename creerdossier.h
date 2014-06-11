#ifndef CREERDOSSIER_H
#define CREERDOSSIER_H

#include <QDialog>
#include <QObject>
#include "Formation.h"
#include "templatemanager.h"
#include <QCheckBox>
#include "Etudiant.h"
#include <QMessageBox>
#include <QComboBox>
#include "Inscription.h"
namespace Ui {
class creerDossier;
}

class MyCheckBox : public QCheckBox
{
     Q_OBJECT

private:
    int numero;
public:
    MyCheckBox(int i): QCheckBox(),numero(i){}
    int getNumero(){return numero;}
public slots:
    void isChecked(int s)
    {
        if(s==2)
        {
            emit addMyNumber(numero);
        }
        else if(s==0)
        {
            emit removeMyNumber(numero);
        }
    }
signals:
    void addMyNumber(int i);
    void removeMyNumber(int i);
};

class creerDossier : public QDialog
{
    Q_OBJECT

public:
    explicit creerDossier(Etudiant& etu,QWidget *parent = 0);


    ~creerDossier();

private slots:
    void ajouterFormation(int i);
    void supprimerFormation(int i);
    void validerFormation();
    void ajouterInscription(int i);
    void supprimerInscription(int i);
    void fillInscriptionTable(int i);
    void addRowInscription();
    void validerInscription();
    void suivant();

private:
    Ui::creerDossier *ui;
    Etudiant& e;
    std::vector<int> formationToBeAdded;
    std::vector<int> inscriptionsToBeAdded;
};

#endif // CREERDOSSIER_H
