#include "ajouterformation_fen.h"
#include "ui_ajouterformation_fen.h"

ajouterformation_fen::ajouterformation_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterformation_fen)
{
    ui->setupUi(this);
}

ajouterformation_fen::~ajouterformation_fen()
{
    delete ui;
}
