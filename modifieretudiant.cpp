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
    QObject::connect(ui->Dossier, SIGNAL(clicked()), this, SLOT(editDossier()));
}

ModifierEtudiant::ModifierEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtudiant)
{
    Dossier dos=Dossier();
    etudiant=new Etudiant(dos);
    b=0;
    ui->setupUi(this);
    QObject::connect(ui->OK, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
    QObject::connect(ui->Dossier, SIGNAL(clicked()), this, SLOT(editDossier()));
}

ModifierEtudiant::~ModifierEtudiant()
{
    delete ui;
}

void ModifierEtudiant::ok()
{
    if(!b)
    {
        Dossier dos=etudiant->getDossier();
        Etudiant(dos, ui->INE->text().toUInt(), ui->Nom->text(), ui->Prenom->text(), ui->dateNaissance->date());
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

void ModifierEtudiant::editDossier()
{
    creerDossier* fenModif=new creerDossier(*etudiant);
    fenModif->exec();
    delete fenModif;
}

void ModifierEtudiant::closeEvent(QCloseEvent *event)
{
    if(!b) delete etudiant;
}
