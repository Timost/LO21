#include "ajouteruvformation_fen.h"
#include "ui_ajouteruvformation_fen.h"

Ajouteruvformation_fen::Ajouteruvformation_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ajouteruvformation_fen)
{
    ui->setupUi(this);
}

Ajouteruvformation_fen::~Ajouteruvformation_fen()
{
    delete ui;
}
