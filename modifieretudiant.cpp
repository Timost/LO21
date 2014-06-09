#include "modifieretudiant.h"
#include "ui_modifieretudiant.h"
#include <QDebug>

ModifierEtudiant::ModifierEtudiant(Etudiant& etu, QWidget *parent) :
    QDialog(parent), etudiant(&etu),
    ui(new Ui::ModifierEtudiant)
{
    ui->setupUi(this);
    b=1;
    ui->INE->setText(QString::number(etu.getIne()));
    ui->Prenom->setText(etu.getPrenom());
    ui->Nom->setText(etu.getNom());
    ui->dateNaissance->setDate(etu.getDateNaissance());
    QObject::connect(ui->OK, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
}

ModifierEtudiant::ModifierEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtudiant)
{
    etudiant=NULL;
    b=0;
    ui->setupUi(this);
    QObject::connect(ui->OK, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
}

ModifierEtudiant::~ModifierEtudiant()
{
    delete ui;
}

void ModifierEtudiant::ok()
{
    if(!b)
    {
        Dossier dos=Dossier();
        etudiant = new Etudiant(dos, ui->INE->text().toUInt(), ui->Nom->text(), ui->Prenom->text(), ui->dateNaissance->date());
        delete etudiant;
    }
    else
    {
        etudiant->setIne(ui->INE->text().toInt());
        etudiant->setNom(ui->Nom->text());
        etudiant->setPrenom(ui->Prenom->text());
        etudiant->setDateNaissance(ui->dateNaissance->date());
    }
    this->close();
}

void ModifierEtudiant::cancel()
{
    this->close();
}
