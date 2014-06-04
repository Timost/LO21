#include "ajouteretudiant_fen.h"
#include "ui_ajouteretudiant_fen.h"

AjouterEtudiant_fen::AjouterEtudiant_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterEtudiant_fen)
{
    ui->setupUi(this);
}

AjouterEtudiant_fen::~AjouterEtudiant_fen()
{
    delete ui;
}
