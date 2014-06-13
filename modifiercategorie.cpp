#include "modifiercategorie.h"
#include "ui_modifiercategorie.h"

ModifierCategorie::ModifierCategorie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierCategorie)
{
    ui->setupUi(this);
}

ModifierCategorie::ModifierCategorie(Categorie& cat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierCategorie)
{
    ui->setupUi(this);
}

ModifierCategorie::~ModifierCategorie()
{
    delete ui;
}
