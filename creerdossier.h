#ifndef CREERDOSSIER_H
#define CREERDOSSIER_H

#include <QDialog>
#include "Formation.h"
#include "templatemanager.h"
#include <QCheckBox>
#include "Etudiant.h"
#include <QMessageBox>
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
    void ajouterInscription();
    void suivant();

private:
    Ui::creerDossier *ui;
    Etudiant& e;
    std::vector<int> formationToBeAdded;
};

#endif // CREERDOSSIER_H
