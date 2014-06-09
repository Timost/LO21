#include "modifieretudiant.h"
#include "ui_modifieretudiant.h"

ModifierEtudiant::ModifierEtudiant(Etudiant& etu, QWidget *parent) :
    QDialog(parent), etudiant(&etu),
    ui(new Ui::ModifierEtudiant)
{
    b=1;
    ui->setupUi(this);
}

ModifierEtudiant::ModifierEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtudiant)
{
    etudiant=NULL;
    b=0;
    ui->setupUi(this);
}

ModifierEtudiant::~ModifierEtudiant()
{
    if(ui->buttonBox_2->Ok)
    {
        if(!b)
        {
            Dossier dos=Dossier();
            etudiant = new Etudiant(dos, ui->INE->text().toUInt(), ui->Nom->text(), ui->Prenom->text(), ui->dateNaissance->date());
            TemplateManager<Etudiant>& tEtu=TemplateManager<Etudiant>::getInstance();
            tEtu.New(*etudiant);
            delete etudiant;
        }
        else
        {
            etudiant->setIne(ui->INE->text().toInt());
            etudiant->setNom(ui->Nom->text());
            etudiant->setPrenom(ui->Prenom->text());
            etudiant->setDateNaissance(ui->dateNaissance->date());
        }
    }
    delete ui;
}
