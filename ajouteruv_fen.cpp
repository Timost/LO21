#include "ajouteruv_fen.h"
#include "ui_ajouteruv_fen.h"

AjouterUv_fen::AjouterUv_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterUv_fen)
{
    ui->setupUi(this);
}

AjouterUv_fen::~AjouterUv_fen()
{
    delete ui;
}
