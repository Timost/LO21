#include "modifieretudiant.h"
#include "ui_modifieretudiant.h"

ModifierEtudiant::ModifierEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtudiant)
{
    ui->setupUi(this);
}

ModifierEtudiant::~ModifierEtudiant()
{
    delete ui;
}
