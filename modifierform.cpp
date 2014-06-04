#include "modifierform.h"
#include "ui_modifierform.h"

modifierform::modifierform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifierform)
{
    ui->setupUi(this);
}

modifierform::~modifierform()
{
    delete ui;
}
