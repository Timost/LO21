#include "modifiersaison.h"
#include "ui_modifiersaison.h"

ModifierSaison::ModifierSaison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSaison)
{
    ui->setupUi(this);
}

ModifierSaison::ModifierSaison(Saison& s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSaison)
{
    ui->setupUi(this);
}

ModifierSaison::~ModifierSaison()
{
    delete ui;
}
