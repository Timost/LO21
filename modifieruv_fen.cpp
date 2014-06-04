#include "modifieruv_fen.h"
#include "ui_modifieruv_fen.h"

Modifieruv_fen::Modifieruv_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modifieruv_fen)
{
    ui->setupUi(this);
}

Modifieruv_fen::~Modifieruv_fen()
{
    delete ui;
}
