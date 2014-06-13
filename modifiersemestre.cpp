#include "modifiersemestre.h"
#include "ui_modifiersemestre.h"

ModifierSemestre::ModifierSemestre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSemestre)
{
    ui->setupUi(this);
}

ModifierSemestre::ModifierSemestre(Semestre& s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSemestre)
{
    ui->setupUi(this);
}

ModifierSemestre::~ModifierSemestre()
{
    delete ui;
}
